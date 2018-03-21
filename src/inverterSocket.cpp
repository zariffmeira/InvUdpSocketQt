#include "../include/inverterSocket.h"

inverterSocket::inverterSocket(unsigned int PORT)
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

		//size_t found = this->udpAddress().find_last_of(".");
		//int address = stoi(this->udpAddress().substr(found+1));
		//std::cout << address << endl;
		//std::cout << inverters.size() << endl;
		//if(address)
		
	}

	

	//inverters[0].setCurrent(this->udpCurrent());
	//inv1.setState(server.udpState());
	//inv1.setNTC(server.udpNTC());

}
/*
void inverterSocket::sendDatagram()
{
	if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
	{
		die("sendto()");
	}
}
*/
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
	buff_int = 0;
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




	