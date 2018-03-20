#ifndef INVERTER_SOCKET_H
#define INVERTER_SOCKET_H

#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFLEN 256

using namespace std;


class inverterSocket 
{

public:
	inverterSocket(unsigned int);
	~inverterSocket();

	void socketBind(void);
	void receiveDatagram(void);
	string udpAddress(void);
	int udpPortReceived();
	int udpState(void);
	int udpCurrent(void);
	int udpNTC(void);
	void shutdownSocket(void);



private:

	struct sockaddr_in server, received;
	unsigned int struct_socket_len = sizeof(received);
	int my_socket;
	int receive_len;
	char buffer[BUFFLEN];
	int buff_int;

};
















































#endif