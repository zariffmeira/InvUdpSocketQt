#include "../include/inverter.h"

inverter::inverter(int ip_in) : ipaddr(ip_in)
{
	
}

inverter::~inverter() { }

void inverter::setCurrent(int new_current)
{
	if(current == new_current) 
		return;
	else
	{
		current = new_current;
		//futur signal
		return;
	} 
}

void inverter::setIpaddr(int new_ipaddr)
{
	if(ipaddr == new_ipaddr) 
		return;
	else
	{
		ipaddr = new_ipaddr;
		//futur signal
		return;
	} 
}

void inverter::setNTC(int new_NTC)
{
	if(NTC == new_NTC) 
		return;
	else
	{
		NTC = new_NTC;
		//futur signal
		return;
	} 
}

void inverter::setState(int new_state)
{
	if(state == new_state) 
		return;
	else
	{
		switch (new_state)
		{
			case 0:
				state = INIT;
			case 1:
				state = off;
			case 2:
				state = cc_at_plus1;
			case 3:
				state = on;
			case 4:
				state = cc_from_on;
			case 5:
				state = cc_at_minus1;																
			case 6:
				state = lock_cmd;
			case 7:
				state = lock_sw;
			case 8:
				state = lock_hw;
			case 9:
				state = lock_emergency;
			case 10:
				state = lock_overheat;																				
			case 11:
				state = reset_oc;
		}
		
		//futur signal
		return;
	} 
}

int inverter::showState()
{
	return state;
}

int  inverter::showCurrent()
{
	return current;
}

int  inverter::showNTC()
{
	return NTC;
}
