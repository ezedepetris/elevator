//CPP:src/lcgrand.cpp
//CPP:src/exponential_gen.cpp
#if !defined exponential_gen_h
#define exponential_gen_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "cmath"
#include "string"
#include "src/lcgrand.h"


class exponential_gen: public Simulator { 
// Declare the state,
double sigma;
// output variables
std::string y;
// and parameters
double expLambda;
double initValue;
int seed;

double deltaL;
double vc;
public:
	exponential_gen(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
