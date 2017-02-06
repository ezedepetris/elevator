//CPP:continuous_system/codes/panel/panel.cpp
#if !defined panel_h
#define panel_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"
#include <queue>



class panel: public Simulator {
// Declare the state,
// output variables
// and parameters
  std::queue<int> flor_queue;
  int state_one = 0;
  int state_two = 0;
  int sigma = INF;

public:
	panel(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
