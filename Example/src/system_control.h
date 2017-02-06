//CPP:src/system_control.cpp
#if !defined system_control_h
#define system_control_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "string"


class system_control: public Simulator { 
static const double inf	= 1e10;
// Declare the state,
/*incoming events*/
std::string signal;
/*rotary table pposition*/
std::string position;
double sigma;
// output variables
std::string y;
// and parameters

public:
	system_control(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
