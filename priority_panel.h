//CPP:elevator/priority_panel.cpp
#if !defined priority_panel_h
#define priority_panel_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "queue"
#include "elevator/constants.h"

class priority_panel: public Simulator {
// Declare the state,
// output variables
// and parameters
  std::queue<double> floor_queue;
  double state_one;
  double state_two;
  double sigma;
  double inf;
  double output;

public:
	priority_panel(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
