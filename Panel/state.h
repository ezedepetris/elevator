//CPP:/home/gaston/Escritorio/elevator/Panel/state.cpp
#if !defined state_h
#define state_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class state: public Simulator { 
// Declare the state,
// output variables
// and parameters

List request_list;
int current_flor;
double sigma;
bool free;

public:
	state(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
