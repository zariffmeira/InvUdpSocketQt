#ifndef INVERTER_H
#define INVERTER_H

#include <iostream>
#include <string>

class inverter
{

public:

	inverter(std::string);
	~inverter();

	enum status{
		INIT            = 0,
	    off             = 1,
	    cc_at_plus1     = 2,
	    on              = 3,
	    cc_from_on      = 4,
	    cc_at_minus1    = 5,
	    lock_cmd        = 6,
	    lock_sw         = 7,
	    lock_hw         = 8,
	    lock_emergency  = 9,
	    lock_overheat   = 10,
	    reset_oc        = 11
	};

	void setState(int);
	void setCurrent(int);
	void setNTC(int);
	void setToPlus1(int);
	void setToMinus1(int);
	void setFromPlus1(int);
	void setFromMinus1(int);
	void setIplus1(int);
	void setIminus1(int);

	int showState(void);
	int showCurrent(void);
	int showNTC(void);
	int showToPlus1(void);
	int showToMinus1(void);
	int showFromPlus1(void);
	int showFromMinus1(void);
	int showIplus1(void);
	int showIminus1(void);


	void setIpaddr(std::string);
	void setIpaddrInt(int);	
	
	std::string showAddr(void);
	int showAddrInt(void);

private:

	int state;
	int current;
	int NTC;
	int to_plus1;
	int to_minus1;
	int from_plus1;
	int from_minus1;
	int i_plus1;
	int i_minus1;

	std::string ipaddr;
	int ipaddrInt;


};


#endif