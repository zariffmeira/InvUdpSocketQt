#ifndef INVERTER_SOCKET_H
#define INVERTER_SOCKET_H

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <../include/inverter.h>
#include <vector>

#define BUFFLEN 256

using namespace std;


class inverterSocket 
{

public:
	inverterSocket(unsigned int);
	~inverterSocket();

	void socketBind(void);
	void receiveDatagram(void);
	/*void sendDatagram(void);*/
	string udpAddress(void);
	int udpPortReceived();
	int udpState(void);
	int udpCurrent(void);
	int udpNTC(void);
	void shutdownSocket(void);
	vector<inverter> showInverterVector(void);


private:
	// Socket variables
	struct sockaddr_in server, received;
	unsigned int struct_socket_len = sizeof(received);
	int my_socket;

	vector<inverter> inverters;

	// Message received variables
	char buffer[BUFFLEN];
	int buff_int;

	// Message send variables

};
















































#endif