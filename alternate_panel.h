//CPP:elevator/alternate_panel.cpp
#if !defined alternate_panel_h
#define alternate_panel_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "queue"


class alternate_panel: public Simulator { 
// Declare the state,
// output variables
// and parameters
  std::queue<int> floor_queue;
  int state_one;
  int state_two;
  int last;
  double sigma;
  double inf;
  int output;

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
