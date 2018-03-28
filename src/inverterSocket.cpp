#include "../include/inverterSocket.h"

inverterSocket::inverterSocket(unsigned int port) : PORT(port)
{
	my_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (my_socket == -1)
	{
		exit(1);
	}
	int optval = 1;

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//inet_aton("192.168.0.254", &server.sin_addr);
	setsockopt(my_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
	setsockopt(my_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	this->socketBind();
}

inverterSocket::~inverterSocket(){} 

void inverterSocket::socketBind()
{
	if(bind(my_socket, (struct sockaddr*) &server, sizeof(server)) == -1)
	{
		exit(1);
	}
}

void inverterSocket::receiveDatagram()
{
	int receive_len;
	int found = 0;	
	size_t point;
	int address_int;
	start = std::clock();

	// Receive the datagram
	if((receive_len = recvfrom(this->my_socket, this->buffer, BUFFLEN, 0, 
	                          (struct sockaddr *) &this->received, 
	                          &this->struct_socket_len)) == -1)
	{
		std::cout << "problema em receber" << endl;
		exit(1);
	}

	// If there is no problem, start the data processing
	else
	{
	
		if(((std::clock() - start) / (double) CLOCKS_PER_SEC) > 3)
		{
			cout << endl << "Inverter's list cleared " << endl;
			this->inverters.clear();
		}
		
		// Look if the inveter lives
		for(int i=0; i < this->inverters.size(); i++){
			if(this->udpAddress() == this->inverters[i].showAddr())
			{
				this->inverters[i].setCurrent(udpCurrent());
				this->inverters[i].setNTC(udpNTC());
				this->inverters[i].setState(udpState());
				found = 1; 
			}
		}
		// If is a new inverter: create and update data
		if (!found)
		{
			inverter newInverter(this->udpAddress());			
			newInverter.setCurrent(udpCurrent());
			newInverter.setNTC(udpNTC());
			newInverter.setState(udpState());
			point = this->udpAddress().find_last_of(".");
		    address_int = stoi(this->udpAddress().substr(point+1));	
		    newInverter.setIpaddrInt(address_int);
			this->inverters.push_back(newInverter);
			std::cout << std::endl << "Found new inverter ip: " << this->udpAddress() << std::endl;
		}

		/*std::cout << "inverter size: " << inverters.size() << endl;
		std::cout << "this->udpAddress(): " << this->udpAddress() << endl;
		std::cout << "inverters[0].showAddr(): " << inverters[0].showAddr() << endl;	
		buff_int = (int) buffer[2];
		std::cout << "buffer 2: "<< buff_int << endl;
		std::cout << "buffer 3: "<< (int) buffer[3] << endl;
		*/
		//size_t point = this->udpAddress().find_last_of(".");
		//int address = stoi(this->udpAddress().substr(point+1));		
	}

}

void inverterSocket::sendDatagram(std::string ip, unsigned char* mesage)
{

	received.sin_family = AF_INET;
	received.sin_port = htons(PORT);
	received.sin_addr.s_addr = inet_addr(ip.c_str());

	if (sendto(my_socket, mesage, sizeof(mesage), 0,
			  (struct sockaddr*) &received, 
			  sizeof(received)) == -1)
	{
		exit(1);
	}
}

string inverterSocket::udpAddress()
{
	return inet_ntoa(received.sin_addr);
}

int inverterSocket::udpPortReceived()
{
	return ntohs(server.sin_port);
}

int inverterSocket::udpCurrent()
{
	this->buff_int = 0;
	this->buff_int = (this->buffer[1] << 8) + this->buffer[0];	
	return this->buff_int;
}

int inverterSocket::udpState()
{
	this->buff_int = this->buffer[2];
	this->buff_int = (this->buffer[3] << 8) + this->buffer[2];
	return this->buff_int;
}

int inverterSocket::udpNTC()
{
	this->buff_int = 0;
	this->buff_int = (this->buffer[5] << 8) + this->buffer[4];	
	return this->buff_int;
}

void inverterSocket::shutdownSocket()
{
	shutdown(my_socket, 2);	
}

vector<inverter> inverterSocket::showInverterVector()
{
	return this->inverters;
}	

void inverterSocket::go_reset(inverter target)
{
	for(int j = 0; j < SEND_TIMES; j++)
	{
		this->sendDatagram(target.showAddr(), goReset);
	}

	return;
}

void inverterSocket::go_on(inverter target)
{
	for(int j = 0; j < SEND_TIMES; j++)
	{
		this->sendDatagram(target.showAddr(), goOn);
	}
	
	return;
}

void inverterSocket::go_lock(inverter target)
{
	for(int j = 0; j < SEND_TIMES; j++)
	{
		this->sendDatagram(target.showAddr(), goLock);
	}
	
	return;
}

void inverterSocket::go_off(inverter target)
{
	for(int j = 0; j < SEND_TIMES; j++)
	{
		this->sendDatagram(target.showAddr(), goOff);
	}
	
	return;
}

void inverterSocket::go_cc_M(inverter target)
{
	for(int j = 0; j < SEND_TIMES; j++)
	{
		this->sendDatagram(target.showAddr(), goCcM);
	}
	
	return;
}

void inverterSocket::go_cc_P(inverter target)
{
	for(int j = 0; j < SEND_TIMES; j++)
	{
		this->sendDatagram(target.showAddr(), goCcP);
	}
	
	return;
}

void inverterSocket::go_reset_all(vector<inverter> target)
{
	for(int j = 0; j < target.size(); j++)
	{
		usleep(100000);
		this->go_reset(target[j]);
	}
	
	return;
}

void inverterSocket::go_list(void)
{
	bool found = true;
	int list_size = inverters.size();
	int *local_seq;

	if(list_size)
	{
		sequence_list = (int *) malloc(list_size);
		local_seq = (int *) malloc(list_size);
	}

	for(int h = 0; h < list_size; h++)
	{
		local_seq[h] = 0;
	}

	// This for will find the first inverter
	this->go_reset_all(inverters);
	usleep(500000);

	for(int j = 0; j < list_size; j++)
	{
		for(int f = 0; f < list_size; f++)
		{
			if(this->inverters[f].showState() != 1)
			{
				this->go_reset_all(this->inverters);
				//cout << "inverter: " << j << " is not off" << ". Is: " << inverters[j].showState() << endl;
				f = 0;
			}
		}

		while(this->inverters[j].showState() != 3)	{this->go_on(inverters[j]); usleep(1000000);}
		/*
		cout << "go on" <<  endl;
		cout << "State 0 = " << this->showInverterVector()[0].showState() << endl;
		cout << "State 1 = " << this->showInverterVector()[1].showState() << endl;
		cout << "State 2 = " << this->showInverterVector()[2].showState() << endl;
		cout << "State 3 = " << this->showInverterVector()[3].showState() << endl;
		cout << "State 4 = " << this->showInverterVector()[4].showState() << endl;
		*/

		for (int i = 0; i < list_size; i++)
		{
			if(this->inverters[i].showState() == 2)
			{
				//cout << "found" << endl;
				if(local_seq[i] == 1)
				{
					cout << "error list" << endl;
				}
				else
				{
					local_seq[i] = 1;	
				}
				this->go_reset_all(inverters);
				/*
				cout << "go reset" <<  endl;
				cout << "State 0 = " << this->showInverterVector()[0].showState() << endl;
				cout << "State 1 = " << this->showInverterVector()[1].showState() << endl;
				cout << "State 2 = " << this->showInverterVector()[2].showState() << endl;
				cout << "State 3 = " << this->showInverterVector()[3].showState() << endl;
				cout << "State 4 = " << this->showInverterVector()[4].showState() << endl;
				cout << "list 0: " << local_seq[0] << endl;
				cout << "list 1: " << local_seq[1] << endl;
				cout << "list 2: " << local_seq[2] << endl;
				cout << "list 3: " << local_seq[3] << endl;
				cout << "list 4: " << local_seq[4] << endl;
				*/
		//		this->receiveDatagram();
				break;
			}
		}
	}

	// This for will make the sequence list by order

	for(int f = 0; f < list_size; f++)
	{
		if(this->inverters[f].showState() != 1)
		{
			this->go_reset_all(this->inverters);
			//cout << "inverter: " << f << " is not off" << ". Is: " << inverters[f].showState() << endl;
			f = 0;
		}
	}

	int seq = 0;
	for(int j = 0; j < list_size; j++)
	{
		if(local_seq[j] == 0)
		{
			//cout << "achei " << seq << endl;
			local_seq[j] = 1;
			sequence_list[seq] = inverters[j].showAddrInt();

			this->go_reset_all(inverters);
			for(int f = 0; f < list_size; f++)
			{
				if(this->inverters[f].showState() != 1)
				{
					this->go_reset_all(this->inverters);
					//cout << "inverter: " << j << " is not off" << ". Is: " << inverters[j].showState() << endl;
					f = 0;
				}
			}
			
			seq++;
			if(seq == list_size)
			{
				break;
			} 

			while(inverters[j].showState() != 3) {this->go_on(inverters[j]);usleep(1000000);}
			usleep(2000000);
			j = 0;
			
		}
		if(inverters[j].showState() == 2)
		{
			//cout << "achei o proximo" << endl;
			local_seq[j] = 0;
			j--;
			
		}
	}

	this->go_reset_all(inverters);

}

int inverterSocket::showSeqListPos(int pos)
{
	if (pos < inverters.size())
	{
		return sequence_list[pos];	
	}
	else
	{
		std::cout << "Position bigger than max." << std::endl;
		return -1;
	}

}