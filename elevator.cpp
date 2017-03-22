#include "elevator.h"
void elevator::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
number = va_arg(parameters, double);
current_floor = 1.0;
state = 0.0; // { -1 down, 0 stop, 1 up}
sigma = 1e10;
inf = 1e10;
output = 0.0;
}
double elevator::ta(double t) {
//This function returns a double.
  return sigma;
}
void elevator::dint(double t) {
   
  if (state == going_up){
    current_floor++;
    distance_next_floor = 2.0;
    sigma = 2.0;
  }
  if (state == going_down){
    current_floor--;
    distance_next_floor = 2.0;
    sigma = 2.0;
  }
  if (state == stopped){
    distance_next_floor = 0.0;
    sigma = inf;
  }
}
void elevator::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
  double input = *((double*)x.value);
  
  if (state == stopped){
    if (input == go_up){
      printLog("ELEVATOR_%d    :INPUT                     ACTION 'GO UP' - TIME %f\n",number, t);
      distance_next_floor = 2.0;
      state = going_up;
      sigma = 0.0;
    }
    if (input == go_down){
		  printLog("ELEVATOR_%d    :INPUT                     ACTION 'GO DOWN' - TIME %f\n",number, t);
      distance_next_floor = 2.0;
      state = going_down;
      sigma = 0.0;
    }
    if (input == stop){
		  printLog("ELEVATOR_%d    :INPUT                     ACTION 'STOP' - TIME %f\n",number, t);
      distance_next_floor = 0.0;
      sigma = inf;
      state = stopped;      
    }
  }
  else{
    if (input == stop){
      printLog("\n\n");
      printLog("ELEVATOR_%d    :INPUT                     ACTION 'STOP' - TIME %f\n",number, t);
      printLog("\n\n");
      distance_next_floor = 0.0;
      sigma = inf;
      current_floor -= state;
      state = stop;
    }
    else{
      printLog("ELEVATOR_%d    :INPUT                     ACTION '%f' - TIME %f\n",number,input, t);
      distance_next_floor = distance_next_floor - 2*e;
		  sigma  = distance_next_floor - 2*e;
    }
  }
}
Event elevator::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
//     NroPort 0 = controller
//     NroPort 1 = gnuplot
  printLog("ELEVATOR_%d    :OUTPUT                    FLOOR %f - TIME %f \n",number, current_floor, t);
  return Event(&current_floor,0);
}
void elevator::exit() {
//Code executed at the end of the simulation.

}
