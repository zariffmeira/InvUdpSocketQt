#ifndef INVERTER_H
#define INVERTER_H

class inverter
{

public:

	inverter(int);
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

	void setCurrent(int);
	void setIpaddr(int);
	void setNTC(int);
	void setState(int);
	int showState(void);
	int showCurrent(void);
	int showNTC(void);

private:

	status state;
	int current;
	int NTC;
	int ipaddr;

};


#endif