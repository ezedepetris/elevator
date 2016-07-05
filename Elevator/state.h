//CPP:/home/ezequiel/Documents/elevator/Elevator/state.cpp
#if !defined state_h
#define state_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class state: public Simulator { 
// Declare the state,
// output variables
// and parameters
int floor;
int distance_next_floor;
int state;
int time_next_floor;
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
