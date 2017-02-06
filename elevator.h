//CPP:continuous_system/elevator.cpp
#if !defined elevator_h
#define elevator_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class elevator: public Simulator {
// Declare the state,
// output variables
// and parameters
  int current_floor = 1;
  int state = 0; // { -1 down, 0 stop, 1 up}
  int sigma = INF;
  int output = 0;
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
