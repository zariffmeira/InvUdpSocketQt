#include "../include/inverterSocket.h"

inverterSocket::inverterSocket(unsigned int port) : PORT(port)
{
	my_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (my_socket == -1)
	{
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

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

	// Receive the datagram
	if((receive_len = recvfrom(my_socket, buffer, BUFFLEN, 0, 
	                          (struct sockaddr *) &received, 
	                          &struct_socket_len)) == -1)
	{
		std::cout << "problema em receber" << endl;
		exit(1);
	}

	// If there is no problem, start the data processing
	else
	{
		// Look if the inveter lives
		for(int i=0; i < inverters.size(); i++){
			if(this->udpAddress() == inverters[i].showAddr())
			{
				inverters[i].setCurrent(udpCurrent());
				inverters[i].setNTC(udpNTC());
				inverters[i].setState(udpState());
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
			inverters.push_back(newInverter);
			std::cout << "Found new inverter ip: " << this->udpAddress() << std::endl;
		}

		/*std::cout << "inverter size: " << inverters.size() << endl;
		std::cout << "this->udpAddress(): " << this->udpAddress() << endl;
		std::cout << "inverters[0].showAddr(): " << inverters[0].showAddr() << endl;	
		buff_int = (int) buffer[2];
		std::cout << "buffer 2: "<< buff_int << endl;
		std::cout << "buffer 3: "<< (int) buffer[3] << endl;
		*/
		//size_t found = this->udpAddress().find_last_of(".");
		//int address = stoi(this->udpAddress().substr(found+1));		
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
	buff_int = 0;
	buff_int = (buffer[1] << 8) + buffer[0];	
	return buff_int;
}

int inverterSocket::udpState()
{
	buff_int = buffer[2];
	buff_int = (buffer[3] << 8) + buffer[2];
	return buff_int;
}

int inverterSocket::udpNTC()
{
	buff_int = 0;
	buff_int = (buffer[5] << 8) + buffer[4];	
	return buff_int;
}

void inverterSocket::shutdownSocket()
{
	shutdown(my_socket, 2);	
}

vector<inverter> inverterSocket::showInverterVector()
{
	return inverters;
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
		this->go_reset(target[j]);
	}
	
	return;
}