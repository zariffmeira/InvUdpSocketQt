#ifndef INVERTER_USB_H
#define INVERTER_USB_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>

class inverterUSB
{
public:
	inverterUSB(char*, speed_t);
	~inverterUSB(); 

	int serial_open(char*);
	int serial_read(int);
	char* show_data();

private:

	// Serial USB0
	int serial;
	char *usb;
	int n;
	char data[8];
	speed_t baud;
	int size;

};

#endif