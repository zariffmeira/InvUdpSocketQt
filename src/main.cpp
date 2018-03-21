#include "../include/inverterSocket.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define PORT 29000   

using namespace std;

int main ()
{

	//inverter inv1(253), inv2(252);
	inverterSocket server(29000);

	while(1)
	{
		//cout << "esperando" << endl;
		server.receiveDatagram();

		cout << endl;
		cout << "IP: " << server.showInverterVector()[0].showAddr() << endl;
		cout << "State: " << server.showInverterVector()[0].showState() << endl;
		cout << "Temperatura: " <<server.showInverterVector()[0].showNTC() << endl;
		cout << "Corrente: " <<server.showInverterVector()[0].showCurrent() << endl;

	}

	server.shutdownSocket();

	return 0;
	
}