//CPP:elevator/controller.cpp
#if !defined controller_h
#define controller_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class controller: public Simulator { 
// Declare the state,
// output variables
// and parameters
  int current_floor;
  int final_floor;
  double sigma;
  double inf;
  int output;
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
