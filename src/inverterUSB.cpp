#include "../include/inverterUSB.h"

inverterUSB::inverterUSB(char* file, speed_t Baud) : usb(file), baud(Baud)
{
	this->serial = this->serial_open(usb);
    if ( serial == -1) {
            std::cout << "Error opening the serial device" << std::endl;
    }
    size = sizeof(data);
}

inverterUSB::~inverterUSB(){}

int inverterUSB::serial_open(char* serial_name)
{
      struct termios newtermios;
      int fd;
      fd = open(serial_name,O_RDWR | O_NOCTTY);
      newtermios.c_cflag= CBAUD | CS8 | CLOCAL | CREAD;
      newtermios.c_iflag=IGNPAR;
      newtermios.c_oflag=0;
      newtermios.c_lflag=0;
      newtermios.c_cc[VMIN]=1;
      newtermios.c_cc[VTIME]=0;
      cfsetospeed(&newtermios,baud);
      cfsetispeed(&newtermios,baud);
      if (tcflush(fd,TCIFLUSH)==-1) return -1;
      if (tcflush(fd,TCOFLUSH)==-1) return -1;
      if (tcsetattr(fd,TCSANOW,&newtermios)==-1) return -1;
      return fd;
} 

int inverterUSB::serial_read(int timeout_usec)
{
      fd_set fds;
      struct timeval timeout;
      int count=0;
      int ret;
      int n;
      do {
        FD_ZERO(&fds);
        FD_SET (serial, &fds);
        timeout.tv_sec = 0;
        timeout.tv_usec = timeout_usec;
        ret=select (FD_SETSIZE,&fds, NULL, NULL,&timeout);
        if (ret==1) {
          n=read (serial, &data[count], size-count);
          count+=n;
          data[count]=0;
   }
 } while (count<size && ret==1);
 return count;
}

char * inverterUSB::show_data()
{
	return data;
}

