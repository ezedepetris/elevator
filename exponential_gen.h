//CPP:lcgrand.cpp
//CPP:elevator/stoc1.cpp
//CPP:elevator/mersenne.cpp
//CPP:elevator/exponential_gen.cpp
#if !defined exponential_gen_h
#define exponential_gen_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "cmath"
#include "string"
#include "lcgrand.h"
#include "stoc1.h"
#include "mersenne.h"


class exponential_gen: public Simulator { 
// Declare the state,
double sigma;
// output variables
std::string y;
// and parameters
double expLambda;
double initValue;
int seed;
StochasticLib1 *time;
double output;
double lala;

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
