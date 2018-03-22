#include "../include/inverterSocket.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <unistd.h>

#define PORT 29000   

using namespace std;

void receiving(inverterSocket*);
void sending(inverterSocket);

int main ()
{
	inverterSocket server(29000);
	
	thread rec(receiving,&server);
	thread sen(sending,server);

	while(1)
	{
		//cout << "esperando" << endl;
		//server.receiveDatagram();
		usleep(10000);

		if(server.showInverterVector().size())
		{
			cout << endl;
			cout << "IP: " << server.showInverterVector()[0].showAddr() << endl;
			cout << "State: " << server.showInverterVector()[0].showState() << endl;
			cout << "Temperatura: " <<server.showInverterVector()[0].showNTC() << endl;
			cout << "Corrente: " <<server.showInverterVector()[0].showCurrent() << endl;				
		}

		//server.go_on(server.showInverterVector()[0]);
		//server.go_reset_all(server.showInverterVector());
		
	}
	rec.join();
	sen.join();

	server.shutdownSocket();

	return 0;
}


void receiving(inverterSocket* target){
	while(1){
		target->receiveDatagram();		
	}
	return;
}

void sending(inverterSocket target){
	while(1){
		target.go_reset_all(target.showInverterVector());		
	}
	return;
}