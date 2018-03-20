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
	if((receive_len = recvfrom(my_socket, buffer, BUFFLEN, 0, 
	                          (struct sockaddr *) &received, 
	                          &struct_socket_len)) == -1)
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

	




	