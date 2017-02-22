//CPP:elevator/elevator.cpp
#if !defined constants_h
#define constants_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

public:
	int stop       = 0;
	int go_up      = 1;
	int gp_down    = -1;
	int stopped    = 0;
	int going_up   = 1;
	int going_down = -1;
};
#endif
