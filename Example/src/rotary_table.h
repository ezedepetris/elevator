//CPP:src/rotary_table.cpp
#if !defined rotary_table_h
#define rotary_table_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "string"


class rotary_table: public Simulator { 
static const double inf	= 1e10;
// Declare the state,
/*rotary table status*/
std::string status;
/*rotary table position*/
std::string position;
/*time elapsed while rotating*/
double elapsed;
double sigma;
// output variables
std::string y;
// and parameters
double tMov;
public:
	rotary_table(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
