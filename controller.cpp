#include "controller.h"
void controller::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
current_floor = 1;
sigma = 1e10;
inf = 1e10;
output = 0;
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
    sigma  = inf;
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
  int  input = *((int*)x.value);
  printLog("Controller input - floor %i in port %i at time %f\n", input, x.port, t);
  
  if (x.port == 0){
    final_floor = input;
    sigma = 0;
  }
  else{
    current_floor = input;
    if (input == final_floor){
      sigma = 0;
    }
    else{
      sigma = inf;
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
      out_value = 1;
      printLog("Controller output in port 0 value %i \n", out_value);
      return Event(&out_value,0);
    }
    else{
      if (current_floor > final_floor){
        out_value = -1;
        printLog("Controller output in port 0 value %i \n", out_value);
        return Event(&out_value,0);
      }
      else{
        out_value = 0;
        printLog("Controller output in port 0 value %i \n", out_value);
        return Event(&out_value,0);
      }
    }
  }
  else{
    if (current_floor == final_floor){
      out_value = 0;
      printLog("Controller output in port 1 value %i \n", out_value);
      return Event(&out_value,1);
    }
    else{
      out_value = 1;
      printLog("Controller output in port 1 value %i \n", out_value);
      return Event(&out_value,1);
    }
  }
}
void controller::exit() {
//Code executed at the end of the simulation.

}
