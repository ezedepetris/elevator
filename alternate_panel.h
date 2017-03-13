//CPP:elevator/alternate_panel.cpp
#if !defined alternate_panel_h
#define alternate_panel_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "queue"
#include "elevator/constants.h"


class alternate_panel: public Simulator { 
// Declare the state,
// output variables
// and parameters
  std::queue<double> floor_queue;
  double state_one;
  double state_two;
  double last;
  double sigma;
  double inf;
  double output;

public:
	alternate_panel(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
