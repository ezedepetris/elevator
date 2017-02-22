#include "elevator.h"
void elevator::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
current_floor = 1;
state = 0; // { -1 down, 0 stop, 1 up}
sigma = 1e10;
inf = 1e10;
output = 0;
}
double elevator::ta(double t) {
//This function returns a double.
  return sigma;
}
void elevator::dint(double t) {
   
  if (state == going_up){
    current_floor++;
    distance_next_floor = 2;
    sigma = 2;
  }
  if (state == going_down){
    current_floor--;
    distance_next_floor = 2;
    sigma = 2;
  }
  if (state == stopped){
    distance_next_floor = 2;
    sigma = inf;
  }
}
void elevator::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
  int input = *((int*)x.value);
  printLog("Elevator input - floor %i in port %i at time %f\n", input, x.port, t);
  
  if (state == stopped){
    distance_next_floor = 2;
    sigma = 2;
    if (input == go_up){
      state = going_up;
    }
    if (input == go_down){
      state = going_down;
    }
  }
  else{
    if (input == stop){
      distance_next_floor = 0;
      sigma = inf;
      state = stopped;
    }
    else{
      distance_next_floor = distance_next_floor - 2*e;
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
  printLog("Elevator output in port 0 value %i \n", current_floor);
  return Event(&current_floor,0);
}
void elevator::exit() {
//Code executed at the end of the simulation.

}
