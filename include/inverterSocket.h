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
#include <arpa/inet.h>

#define BUFFLEN 256 
#define SEND_M_SIZE 8
#define SEND_TIMES 3

using namespace std;


class inverterSocket 
{

public:
	inverterSocket(unsigned int);
	~inverterSocket();

	void socketBind(void);
	void receiveDatagram(void);
	void sendDatagram(std::string, unsigned char*);
	string udpAddress(void);
	int udpPortReceived();
	int udpState(void);
	int udpCurrent(void);
	int udpNTC(void);
	void shutdownSocket(void);
	vector<inverter> showInverterVector(void);

	void go_reset(inverter);
	void go_on(inverter);
	void go_lock(inverter);
	void go_off(inverter);
	void go_cc_M(inverter);
	void go_cc_P(inverter);
	void go_reset_all(vector<inverter>);


private:
	// Socket variables
	struct sockaddr_in server, received;
	unsigned int struct_socket_len = sizeof(received);
	int my_socket;
	int PORT;

	// Vector of inverters
	vector<inverter> inverters;

	// Message received variables
	char buffer[BUFFLEN];
	int buff_int;

	// Message send variables
	unsigned char goReset[SEND_M_SIZE] = {1,0,0,0,0,0,1,0};
	unsigned char goOn[SEND_M_SIZE]    = {0,0,22,0,0,0,1,0};
	unsigned char goLock[SEND_M_SIZE]  = {0,0,201,0,0,0,1,0};
	unsigned char goOff[SEND_M_SIZE]   = {0,0,200,0,0,0,1,0};
	unsigned char goCcM[SEND_M_SIZE]  = {0,0,211,0,0,0,1,0};
	unsigned char goCcP[SEND_M_SIZE]  = {0,0,212,0,0,0,1,0};

};
















































#endif