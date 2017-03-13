//CPP:elevator/FunctionsLib.cpp
//CPP:elevator/heuristics_panel.cpp
#if !defined heuristics_panel_h
#define heuristics_panel_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "queue"
#include "elevator/constants.h"
#include "elevator/FunctionsLib.h"


class heuristics_panel: public Simulator { 
// Declare the state,
// output variables
// and parameters
  std::queue<double> floor_queue;
  double state_one;
  double state_two;
  double origin_floor_one;
  double origin_floor_two;
  double destination_floor_one;
  double destination_floor_two;
  double time_one;
  double time_two;
  double sigma;
  double inf;
  double output_port;

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
