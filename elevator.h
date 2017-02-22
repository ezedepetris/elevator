//CPP:elevator/elevator.cpp
#if !defined elevator_h
#define elevator_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class elevator: public Simulator { 
// Declare the state,
// output variables
// and parameters
  int current_floor;
  int distance_next_floor;
  int state;
  double sigma;
  double inf;
  int output;
public:
	elevator(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
