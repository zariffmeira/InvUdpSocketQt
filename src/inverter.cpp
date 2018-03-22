#include "../include/inverter.h"

inverter::inverter(std::string ip_in) : ipaddr(ip_in)
{
	
}

inverter::~inverter() { }

void inverter::setState(int new_state)
{
	state = new_state;
	/*
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
	}*/

	//futur signal
	return;

}

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

void inverter::setToPlus1(int newToPlus1)
{
	if(to_plus1 == newToPlus1) 
		return;
	else
	{
		to_plus1 = newToPlus1;
		//futur signal
		return;
	} 
}

void inverter::setToMinus1(int newToMinus1)
{
	if(to_minus1 == newToMinus1) 
		return;
	else
	{
		to_minus1 = newToMinus1;
		//futur signal
		return;
	} 
}

void inverter::setFromPlus1(int newFromPlus1)
{
	if(from_plus1 == newFromPlus1) 
		return;
	else
	{
		from_plus1 = newFromPlus1;
		//futur signal
		return;
	} 
}

void inverter::setFromMinus1(int newFromMinus1)
{
	if(from_minus1 == newFromMinus1) 
		return;
	else
	{
		from_minus1 = newFromMinus1;
		//futur signal
		return;
	} 
}

void inverter::setIplus1(int newIplus1)
{
	if(i_plus1 == newIplus1) 
		return;
	else
	{
		i_plus1 = newIplus1;
		//futur signal
		return;
	} 
}

void inverter::setIminus1(int newIminus1)
{
	if(i_minus1 == newIminus1) 
		return;
	else
	{
		i_minus1 = newIminus1;
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

int inverter::showToPlus1()
{
	return to_plus1;
}

int inverter::showToMinus1()
{
	return to_minus1;
}

int inverter::showFromPlus1()
{
	return from_plus1;
}

int inverter::showFromMinus1()
{
	return from_minus1;
}

int inverter::showIplus1()
{
	return i_plus1;
}

int inverter::showIminus1()
{
	return i_minus1;
}

void inverter::setIpaddr(std::string new_ipaddr)
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

void inverter::setIpaddrInt (int new_ipaddrInt)
{
	if(ipaddrInt == new_ipaddrInt) 
		return;
	else
	{
		ipaddr = new_ipaddrInt;
		//futur signal
		return;
	} 
}

std::string  inverter::showAddr()
{
	return ipaddr;
}

int  inverter::showAddrInt()
{
	return ipaddrInt;
}