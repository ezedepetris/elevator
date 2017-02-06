//CPP:src/lcgrand.cpp
//CPP:src/robot.cpp
#if !defined robot_h
#define robot_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "string"
#include "src/lcgrand.h"


class robot: public Simulator { 
static const double inf	= 1e10;
// Declare the state,
/*robot status*/
std::string status;
double sigma;
// output variables
std::string y;
// and parameters
double a;
double b;
public:
	robot(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
