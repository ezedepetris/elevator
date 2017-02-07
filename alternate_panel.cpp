#include "alternate_panel.h"
void alternate_panel::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
state_one = 0;
state_two = 0;
last = 0;
sigma = 1e10;
inf = 1e10;
}
double alternate_panel::ta(double t) {
//This function returns a double.
  return sigma;
}
void alternate_panel::dint(double t) {
  if (last == 2){
    state_one = 1;
    last = 1;
  }
  else{
    state_two = 1;
    last = 2;
  }
}
void alternate_panel::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
//     NroPort 0 = generator
//     NroPort 1 = controller one
//     NroPort 2 = controller two
  int input;
  input = *(int*)(x.value);
  switch (x.port){
    case 0:
      floor_queue.push(input);
      if ((state_one == 0 && last == 2) || (state_two == 0 && last == 1)){
        sigma = 0;
        break;
      }
      if ((state_one == 1 && last == 2) || (state_two == 1 && last == 1)){
        sigma = inf;
        break;
      }
    case 1:
      if (x.port == 0 && last == 2 && !floor_queue.empty()){
        state_one = 0;
        sigma = 0;
        break;
      }
      if(x.port == 0 && (last == 1 || floor_queue.empty())){
        state_one = 0;
        sigma = inf;
        break;
      }if(x.port == 1){
        state_one = 1;
        sigma = inf;
        break;
      }
    case 2:
      if (x.port == 0 && last == 1 && !floor_queue.empty()){
        state_two = 0;
        sigma = 0;
        break;
      }
      if(x.port == 0 && (last == 2 || floor_queue.empty())){
        state_two = 0;
        sigma = inf;
        break;
      }if(x.port == 1){
        state_two = 1;
        sigma = inf;
        break;
      }
    default:
    break;
  }
}
Event alternate_panel::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
//     NroPort 0 = elevator one
//     NroPort 1 = elevator two
  int floor = floor_queue.front();
  floor_queue.pop();
  return Event(&floor,last-1);
}
void alternate_panel::exit() {
//Code executed at the end of the simulation.

}
