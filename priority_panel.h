//CPP:continuous_system/codes/priority_panel/priority_panel.cpp
#if !defined priority_panel_h
#define priority_panel_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"
#include <queue>



class priority_panel: public Simulator {
// Declare the state,
// output variables
// and parameters
  std::queue<int> flor_queue;
  int state_one = 0;
  int state_two = 0;
  int sigma = INF;

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
