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
finputs.open("event_inputs.txt");
foutputs.open("event_outputs.txt");
}
double priority_panel::ta(double t) {
//This function returns a double.
  return sigma;
}
void priority_panel::dint(double t) {
  sigma = 2.0;
  if (state_one == vacant){
    state_one = busy;
  }
  else{
    state_two = busy;
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
  if (x.port == 0.0){
    state_one = vacant;
    if (!floor_queue.empty()){
      sigma = 0.0;
    }
    if (floor_queue.empty() ||  state_two == busy){
      sigma = inf;
    }
  }
  if (x.port == 1.0){
    finputs << ("%f\n", t);
    floor_queue.push(input);
    if ((state_one == vacant) || (state_two == vacant)){
      sigma = 0.0;
    }
    else{
      sigma = inf;
    }
  }
  if (x.port == 2.0){
    state_two = vacant;
    if (!floor_queue.empty() || state_one == 0.0){
      sigma = 0.0;
    }
    if (floor_queue.empty() || state_one == 1.0){
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
  foutputs << ("%f\n", t);
  floor_queue.pop();
  if (state_one == vacant){
    return Event(&output,0);
  }
  else{
    return Event(&output,1);
  }
}
void priority_panel::exit() {
//Code executed at the end of the simulation.
  finputs.close();
  foutputs.close();
}
