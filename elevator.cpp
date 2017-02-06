#include "elevator.h"
void elevator::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

}
double elevator::ta(double t) {
//This function returns a double.
  return sigma;
}
void elevator::dint(double t) {
  if (state == 1){
    current_floor++;
  }
  else{
    current_floor--;
  }
  sigma = 2;
}
void elevator::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
  int input = x.value;
  state = input;
  if (input != 0){
    sigma = 2000;
  }
  else{
    sigma = INF;
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

return Event(&current_floor,0);
}
void elevator::exit() {
//Code executed at the end of the simulation.

}
