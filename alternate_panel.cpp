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
last = 2;
sigma = 1e10;
inf = 1e10;
}
double alternate_panel::ta(double t) {
//This function returns a double.
  return sigma;
}
void alternate_panel::dint(double t) {
  sigma = 2;
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
//     NroPort 0 = controller_one
//     NroPort 1 = generator
//     NroPort 2 = controller two
  int  input = *((int*)x.value);
  printLog("Panel input - floor %i in port %i at time %f\n", input, x.port, t);
  switch (x.port){
    case 0:
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
    case 1:
      floor_queue.push(input);
      /*printLog("state one %i \n", state_one);
      printLog("state two %i \n", state_two);
      printLog("last %i \n", last);*/
      if ((state_one == 0 && last == 2) || (state_two == 0 && last == 1)){
        //printLog("Panel input - ESTOY AQUI 1 \n");
        sigma = 0;
        break;
      }
      if ((state_one == 1 && last == 2) || (state_two == 1 && last == 1)){
        //printLog("Panel input - ESTOY AQUI 2 \n");
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
  output = floor_queue.front();
  floor_queue.pop();

  printLog("Panel output - floor %i in port %i at time %f\n", output, last-1, t);
  return Event(&output,last-1);
}
void alternate_panel::exit() {
//Code executed at the end of the simulation.

}
