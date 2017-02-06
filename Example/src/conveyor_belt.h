//CPP:src/conveyor_belt.cpp
#if !defined conveyor_belt_h
#define conveyor_belt_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "list"
#include "string"


class conveyor_belt: public Simulator { 
// Define infinite constant
static const double inf	= 1e10;
// Declare the state,
/*distances queue*/
std::list<double> distances;
/*conveyor belt speed*/
double speed;
double sigma;
// output variables
std::string y;
// and parameters
double vc;
double l;
double deltaL;
public:
	conveyor_belt(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
