//CPP:elevator/heuristics_panel.cpp
#if !defined heuristics_panel_h
#define heuristics_panel_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "queue"
#include "elevator/constants.h"
#include "elevator/Functions.h"
#include "Functions.h"


class heuristics_panel: public Simulator { 
// Declare the state,
// output variables
// and parameters
  std::queue<int> floor_queue;
  int state_one;
  int state_two;
  int origin_floor_one;
  int origin_floor_two;
  int destination_floor_one;
  int destination_floor_two;
  double time_one;
  double time_two;
  double sigma;
  double inf;
  int output_port;

public:
	heuristics_panel(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
