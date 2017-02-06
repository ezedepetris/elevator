//CPP:src/conveyor_belt_statics.cpp
#if !defined conveyor_belt_statics_h
#define conveyor_belt_statics_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "string"


class conveyor_belt_statics: public Simulator { 
static const double inf	= 1e10;
// Declare the state,
/*indicates which port is going to be printed*/
int print;
/*conveyor belt status*/
std::string status;
/*counts arrivals*/
double counter;
/*counts arrivals rejected*/
double rejected;
/*counts jobs on the conveyor belt*/
int onBelt;
double sigma;
// output variables
double y;
// and parameters

public:
	conveyor_belt_statics(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
