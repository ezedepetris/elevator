#include "priority_panel.h"
void priority_panel::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

}
double priority_panel::ta(double t) {
//This function returns a double.
  return sigma;
}
void priority_panel::dint(double t) {
  if (state_one == 0){
    state_one = 1;
  }
  else{
    state_two = 1;
  }
}
void priority_panel::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
//     NroPort 0 = generator
//     NroPort 1 = controller one
//     NroPort 2 = controller two
  switch (x.port){
    case 0:
      flor_queue.push(x.value);
      if (state_one == 0) || (state_two == 0){
        sigma = 0;
      }
      else{
        sigma = INF;
      }
      break;
    case 1:
      state_one = x.value;
      if (!flor_queue.empty() && (x.value == 0 || state_two == 0){
        sigma = 0
      }
      if (flor_queue.empty() || (x.value == 1 && state_two == 1){
        sigma = INF
      }
      break;
    case 2:
      state_two = x.value;
      if (!flor_queue.empty() && (x.value == 0 || state_one == 0){
        sigma = 0
      }
      if (flor_queue.empty() || (x.value == 1 && state_one == 1){
        sigma = INF
      }
      break;
    default:
    break;
  }
}
Event priority_panel::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
//     NroPort 0 = elevator one
//     NroPort 1 = elevator two
  int flor = flor_queue.pop();
  if (state_one == 0){
    return Event(flor,0);
  }
  else{
    return Event(flor,1);
  }
}
void priority_panel::exit() {
//Code executed at the end of the simulation.

}
