//CPP:/home/ezequiel/Documents/elevator/Controller/state.cpp
#if !defined state_h
#define state_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class state: public Simulator { 
// Declare the state,
// output variables
// and parameters
int current_floor;
int next_floor;
int state;
int time_next_arrive;
int stop;
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
