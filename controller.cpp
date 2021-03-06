#include "controller.h"
void controller::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
number = va_arg(parameters, double);
current_floor = 1.0;
sigma = 1e10;
inf = 1e10;
output = 0.0;
out_value = -1.0;
}
double controller::ta(double t) {
//This function returns a double.
  return sigma;
}
void controller::dint(double t) {
  if (output == 0.0){
    sigma  = 0.0;
    output = 1.0;
  }
  else{
    sigma  = inf;
    output = 0.0;
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
  double  input = *((double*)x.value);

  if (x.port == 0.0){
    final_floor = input;
    sigma = 0.0;
    output = 0.0;
  }
  else{
    if (input == final_floor){
      current_floor = input;
      sigma = 0.0;
      output = 0.0;
    }
    else{
      current_floor = input;
      sigma = inf;
      output = 0.0;
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
  if (output == 0.0){
    if (current_floor < final_floor){
      out_value = go_up;
      return Event(&out_value,0);
    }
    else{
      if (current_floor > final_floor){
        out_value = go_down;
        return Event(&out_value,0);
      }
      else{
        out_value = stop;
        return Event(&out_value,0);
      }
    }
  }
  else{
    if (current_floor == final_floor){
      out_value = vacant;
      return Event(&out_value,1);
    }
  }
}
void controller::exit() {
//Code executed at the end of the simulation.

}
