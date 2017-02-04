//CPP:continuous_system/controller.cpp
#if !defined controller_h
#define controller_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class controller: public Simulator {
// Declare the state,
// output variables
// and parameters
  int current_floor = 1;
  int final_floor;
  int sigma = INF;
public:
	controller(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
