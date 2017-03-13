#include "priority_panel.h"
void priority_panel::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
state_one = vacant;
state_two = vacant;
sigma = 1e10;
inf = 1e10;
}
double priority_panel::ta(double t) {
//This function returns a double.
  return sigma;
}
void priority_panel::dint(double t) {
  sigma = 2.0;
  if (state_one == 0.0){
    state_one = 1.0;
  }
  else{
    state_two = 1.0;
  }
}
void priority_panel::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
//     NroPort 0 = controller_one
//     NroPort 1 = generator
//     NroPort 2 = controller two
  double  input = *((double*)x.value);
  if (x.port == 1.0){
    printLog("PANEL:INPUT:GENERATOR - FLOOR %f - TIME %f \n", input, t);
  }
  if (x.port == 0.0){
    printLog("PANEL:INPUT:CONTROLLER_1 - VALUE 'VACANT' - TIME %f \n", t);
  }
  if (x.port == 2.0){
    printLog("PANEL:INPUT:CONTROLLER_2 - VALUE 'VACANT' - TIME %f \n", t);
  }
  if (x.port == 0.0){
    state_one = input;
    if (!floor_queue.empty() && (input == 0.0 || state_two == 0.0)){
      sigma = 0.0;
    }
    if (floor_queue.empty() || (input == 1.0 && state_two == 1.0)){
      sigma = inf;
    }
  }
  if (x.port == 1.0){
    floor_queue.push(input);
    if ((state_one == 0.0) || (state_two == 0.0)){
      sigma = 0.0;
    }
    else{
      printLog("PANEL:INPUT:GENERATOR - 'WAIT' \n");
      sigma = inf;
    }
  }
  if (x.port == 2.0){
    state_two = input;
    if (!floor_queue.empty() && (input == 0.0 || state_one == 0.0)){
      sigma = 0.0;
    }
    if (floor_queue.empty() || (input == 1.0 && state_one == 1.0)){
      sigma = inf;
    }
    
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
  output = floor_queue.front();
  floor_queue.pop();
  if (state_one == 0.0){
    printLog("PANEL:OUTPUT:CONTROLLER_1 - FLOOR %f - TIME %f \n", output, t);
    return Event(&output,0);
  }
  else{
    printLog("PANEL:OUTPUT:CONTROLLER_2 - FLOOR %f - TIME %f \n", output, t);
    return Event(&output,1);
  }
}
void priority_panel::exit() {
//Code executed at the end of the simulation.

}
