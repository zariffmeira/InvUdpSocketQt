#include "../include/inverterSocket.h"
#include "../include/inverterUSB.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <termios.h>

#define PORT 29000   

using namespace std;

void receiving(inverterSocket*);
void sending(inverterSocket*);
void list_inverters(inverterSocket*);
void usb_receiving(inverterUSB*);

inverterSocket server(PORT);
inverterUSB serial((char*) "/dev/ttyUSB0", B115200);


int main ()
{
	char command[20];
	
	// Socket UDP
	int inverter_list[6];
	int amount_inverters;

	// Threads
	thread rec(receiving, &server);
	//thread usb(usb_receiving, &serial);
	//thread sen(sending,&server);

	usleep(1000000);  
	
	while(1)
	{
		cout << "Command line >> ";
		
		cin >> command;
		

		if(!strncmp (command, "go_reset_all", sizeof("go_reset_all")))
		{
			cout << "Reseting all inverters... ";
			server.go_reset_all(server.showInverterVector());
			cout << "done." << endl;
		}
		else if(!strncmp (command, "go_list", sizeof("go_list")))
		{
			cout << "Ordering the inverters... ";
			thread list(list_inverters, &server);	
			list.join();
			cout << "done." << endl;
			cout << "First inverter is: 192.168.0."<<server.showSeqListPos(0) << endl;
			cout << "Second inverter is: 192.168.0."<<server.showSeqListPos(1) << endl;
			cout << "Third inverter is: 192.168.0."<<server.showSeqListPos(2) << endl;
			cout << "Fourth inverter is: 192.168.0."<<server.showSeqListPos(3) << endl;
			cout << "Fifth inverter is: 192.168.0."<<server.showSeqListPos(4) << endl;
		}
		else if(!strncmp (command, "go_start", sizeof("go_auto")))
		{	
			cout << "Starting USB listening...";	
			thread usb(usb_receiving, &serial);
			cout << " done." << endl;
			usb.join();
		}
		else if(!strncmp (command, "go_show", sizeof("go_show")))
		{
			cout << "State 0 = " << server.showInverterVector()[0].showState() << endl;;
			cout << "State 1 = " << server.showInverterVector()[1].showState() << endl;;
			cout << "State 2 = " << server.showInverterVector()[2].showState() << endl;;
			cout << "State 3 = " << server.showInverterVector()[3].showState() << endl;;
			cout << "State 4 = " << server.showInverterVector()[4].showState() << endl;;

		}
		else 
		{
			cout << "Command not found" << endl;
		}
	}

	rec.join();
	//sen.join();
	

	server.shutdownSocket();

	return 0;
}


void receiving(inverterSocket* target){
	while(1)
	{
		target->receiveDatagram();			
	}
	return;
}

void sending(inverterSocket* target){
	while(1)
	{	
	}
	return;
}

void list_inverters(inverterSocket* target)
{
	target->go_list();
	return;
}


void usb_receiving(inverterUSB* target)
{
	while(1)
	{
		target->serial_read(10000);
		cout << target->show_data() << endl;
	}
}




