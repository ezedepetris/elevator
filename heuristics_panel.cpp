#include "heuristics_panel.h"
void heuristics_panel::init(double t,...) {
  //The 'parameters' variable contains the parameters transferred from the editor.
  va_list parameters;
  va_start(parameters,t);
  //To get a parameter: %Name% = va_arg(parameters,%Type%)
  //where:
  //      %Name% is the parameter name
  //	%Type% is the parameter type
  origin_floor_one = 1;
  origin_floor_two = 1;
  destination_floor_one = 1;
  destination_floor_two = 1;
  time_one = 0;
  time_two = 0;
  output_port = 0;
  state_one = vacant;
  state_two = vacant;
  sigma = 1e10;
  inf = 1e10;
}
double heuristics_panel::ta(double t) {
//This function returns a double.
  return sigma;
}
void heuristics_panel::dint(double t) {
  sigma = inf;
  output = floor_queue.front();
  floor_queue.pop();
  if (output_port == 0){
    state_one = busy;
    origin_floor_one = destination_floor_one;
    destination_floor_one = output;  
    time_one = t;
  }
  else{
    state_two = busy;
    origin_floor_two = destination_floor_two;
    destination_floor_two = output;  
    time_two = t;
  }
}
void heuristics_panel::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
//     NroPort 0 = controller_one
//     NroPort 1 = generator
//     NroPort 2 = controller two
  printLog("TESTING FUCTIONS LIBRARY  %i \n", Functions::Add(1, 2));
  printLog("TESTING FUCTIONS LIBRARY  %i \n", Functions::Add(1, 2));
  printLog("TESTING FUCTIONS LIBRARY  %i \n", Functions::Add(1, 2));
  printLog("TESTING FUCTIONS LIBRARY  %i \n", Functions::Add(1, 2));
  printLog("TESTING FUCTIONS LIBRARY  %i \n", Functions::Add(1, 2));



  int  input = *((int*)x.value);
  if (x.port == 1){
    printLog("PANEL:INPUT:GENERATOR - FLOOR %i - TIME %f \n", input, t);
  }
  if (x.port == 0){
    printLog("PANEL:INPUT:CONTROLLER_1 - VALUE 'VACANT' - TIME %f \n", t);
  }
  if (x.port == 2){
    printLog("PANEL:INPUT:CONTROLLER_2 - VALUE 'VACANT' - TIME %f \n", t);
  }
  switch (x.port){
    case 0:
      if (!floor_queue.empty() && funcion() == 1){
        output_port = 1;
        state_one = vacant;
        sigma = 0;
        break;
      }
      if(floor_queue.empty() || (!floor_queue.empty() && funcion() == 2)){
        state_one = vacant;
        sigma = inf;
        break;
      }
    case 1:
      floor_queue.push(input);
      /*printLog("state one %i \n", state_one);
      printLog("state two %i \n", state_two);
      printLog("last %i \n", last);*/
      if ((state_one == vacant && funcion() == 1) || (state_two == vacant && funcion() == 2)){
        //printLog("Panel input - ESTOY AQUI 1 \n");
        output_port = funcion();
        sigma = 0;
        break;
      }
      if ((state_one == busy && funcion() == 1) || (state_two == busy && funcion() == 2)){
        printLog("PANEL:INPUT:GENERATOR - 'WAIT' \n");
        sigma = inf;
        break;
      }
    case 2:
      if (!floor_queue.empty() && funcion() == 2){
        output_port = 2;
        state_two = vacant;
        sigma = 0;
        break;
      }
      if(floor_queue.empty() || (!floor_queue.empty() && funcion() == 1)){
        state_two = vacant;
        sigma = inf;
        break;
      }
    default:
    break;
  }
}
Event heuristics_panel::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
//     NroPort 0 = controller one
//     NroPort 1 = controller two
  output = floor_queue.front();
  printLog("PANEL:OUTPUT:CONTROLLER_%i - FLOOR %i - TIME %f \n", output_port, output, t);
  return Event(&output,output_port-1);
}
void heuristics_panel::exit() {
//Code executed at the end of the simulation.

}
