#include <iostream>
#include "../include/inverter.h"
#include "../include/inverterSocket.h"
#include <string> //memset
#include <stdlib.h>
#include <stdio.h>

#define PORT 29000   //The port on which to listen for incoming data

using namespace std;

int main ()
{

	inverter inv1(253), inv2(252);
	inverterSocket server(29000);

	while(1)
	{
		cout << "esperando" << endl;
		server.receiveDatagram();

		cout << "IP recebido: " << server.udpAddress() << endl;

		inv1.setCurrent(server.udpCurrent());
		inv1.setState(server.udpState());
		inv1.setNTC(server.udpNTC());
	
		
		cout << "State: " << inv1.showState() << endl;
		cout << "Corrente: " << inv1.showCurrent() << endl;
		cout << "Temperatura: " << inv1.showNTC() << endl << endl;
	}

	server.shutdownSocket();

	return 0;
	
}