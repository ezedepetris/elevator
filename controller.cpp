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
    printLog("CONTROLLER_%d  :INPUT:  PANEL           FLOOR %f - TIME %f \n",number,  input, t);
  }else{
    printLog("CONTROLLER_%d  :INPUT:  ELEVATOR_%d        FLOOR %f - TIME %f \n",number,number, input, x.port, t);
  }
  
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
      printLog("ENTRE POR ACAAAAA, INPUT:%f, CURRENT:%f, FINAL:%f T:%f \n",input,current_floor,final_floor, t);
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
      printLog("CONTROLLER_%d  :OUTPUT:   ELEVATOR_%d     VALUE 'GO UP' - TIME %f\n",number,number, t);
      return Event(&out_value,0);
    }
    else{
      if (current_floor > final_floor){
        out_value = go_down;
        printLog("CONTROLLER_%d  :OUTPUT:   ELEVATOR_%d     VALUE 'GO DOWN' - TIME %f\n",number,number, t);
        return Event(&out_value,0);
      }
      else{
        out_value = stop;
        printLog("CONTROLLER_%d  :OUTPUT:   ELEVATOR_%d     VALUE 'STOP' - TIME %f\n",number,number, t);
        return Event(&out_value,0);
      }
    }
  }
  else{
    if (current_floor == final_floor){
      out_value = vacant;
      printLog("CONTROLLER_%d  :OUTPUT:   PANEL           VALUE 'VACANT' - TIME %f\n",number, t);
      return Event(&out_value,1);
    }
  }
}
void controller::exit() {
//Code executed at the end of the simulation.

}
