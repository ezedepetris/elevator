#include "controller.h"
void controller::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

}
double controller::ta(double t) {
//This function returns a double.
  return sigma;
}
void controller::dint(double t) {
  if (output == 0){
    sigma  = 0;
    output = 1;
  }
  else{
    sigma  = INF;
    output = 0;
  }
}
void controller::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
//     NroPort 0 = panel
//     NroPort 1 = elevator
  if (x.port == 0){
    final_floor = x.value;
  }
  else{
    current_floor = x.value;
    if (x.value == final_floor){
      sigma = 0;
    }
    else{
      sigma = INF;
    }
  }
}
Event controller::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
//     NroPort 0 = elevator
//     NroPort 1 = panel
  if (output == 0){
    if (current_floor < final_floor){
      return Event(1,0)
    }
    else{
      if (current_floor > final_floor){
        return Event(-1,0)
      }
      else{
        return Event(0,0)
      }
    }
  }
  else{
    if (current_floor == final_floor){
      return Event(0,1)
    }
    else{
      return Event(1,1)
    }
  }
}
void controller::exit() {
//Code executed at the end of the simulation.

}
