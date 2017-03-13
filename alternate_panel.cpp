#include "alternate_panel.h"
void alternate_panel::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
state_one = vacant;
state_two = vacant;
last = 2.0;
sigma = 1e10;
inf = 1e10;
}
double alternate_panel::ta(double t) {
//This function returns a double.
  return sigma;
}
void alternate_panel::dint(double t) {
  sigma = inf;
  if (last == 2.0){
    state_one = busy;
    last = 1.0;
  }
  else{
    state_two = busy;
    last = 2.0;
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
    // controller_one && last_output = port_2
    if (!floor_queue.empty()){
      state_one = vacant;
      sigma = 0.0;
      break;
    }
    if(floor_queue.empty()){
      state_one = vacant;
      sigma = inf;
      break;
    }
  }
  if (x.port == 1.0){
    floor_queue.push(input);
    /*printLog("state one %f \n", state_one);
    printLog("state two %f \n", state_two);
    printLog("last %f \n", last);*/
    if ((state_one == vacant && last == 2.0) || (state_two == vacant && last == 1.0)){
      //printLog("Panel input - ESTOY AQUI 1 \n");
      sigma = 0.0;
      break;
    }
    if ((state_one == busy && last == 2.0) || (state_two == busy && last == 1.0)){
      printLog("PANEL:INPUT:GENERATOR - 'WAIT' \n");
      sigma = inf;
      break;
    }
  }
  if (x.port == 2.0){
    if (!floor_queue.empty()){
      state_two = vacant;
      sigma = 0.0;
      break;
    }
    if(floor_queue.empty()){
      state_two = vacant;
      sigma = inf;
      break;
    }
  }
}
Event alternate_panel::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
//     NroPort 0 = controller one
//     NroPort 1 = controller two
  output = floor_queue.front();
  floor_queue.pop();
  if(last == 2.0){
 	 printLog("PANEL:OUTPUT:CONTROLLER_1 - FLOOR %f - TIME %f \n", output, t);
	  return Event(&output,0);
  }else{
	  printLog("PANEL:OUTPUT:CONTROLLER_2 - FLOOR %f - TIME %f \n", output, t);
	  return Event(&output,1);
  }
}
void alternate_panel::exit() {
//Code executed at the end of the simulation.

}
