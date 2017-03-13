//CPP:elevator/elevator.cpp
#if !defined elevator_h
#define elevator_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "elevator/constants.h"


class elevator: public Simulator { 
// Declare the state,
// output variables
// and parameters
  double current_floor;
  double distance_next_floor;
  double state;
  double sigma;
  double inf;
  double output;
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
