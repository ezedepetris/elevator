//CPP:continuous_system/codes/panel/panel.cpp
#if !defined panel_h
#define panel_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class panel: public Simulator { 
// Declare the state,
// output variables
// and parameters

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
