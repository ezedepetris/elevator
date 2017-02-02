#include "state.h"
void state::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
	request_list = new List();
	next_flor    = -1; 
	sigma        = INF;
	free         = true;

}
double state::ta(double t) {
//This function returns a double.
return sigma;
}
void state::dint(double t) {

}
void state::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
if ((request_list.size() == 0) && free && (x.0 == nil)){
	next_flor = x.value;
	sigma     = 0;
	free      = false;
}
if (!free && x.0 != nil){
	request_list.add(x.value);
	next_flor = -1;
	sigma     = INF;
}
if ((x.1 == true) && (request_list.size() == 0)){
	next_flor = -1;
	sigma     = INF;
	free      = true;
}
if ((x.1 == true) && (request_list.size() == 1)){
	next_flor = request_list.top();
	request_list.remove();
	sigma = 0;
	free  = false;
}
if ((request_list.size()>1) && (next_flor==request_list.top()) && free && (x.1 != nil)){
	request_list.remove();
	sigma = 0;
	free  = false;
}
if ((request_list.size()>1) && (next_flor!=request_list.top()) && free && (x.1 != nil)){
	next_flor = request_list.top();
	request_list.add(x.value);
	sigma = 0;
	free  = false;
}
if (x.1 == false){
	next_flor = -1;
	sigma = INF;
	free  = false;
}
}
Event state::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)


return next_flor;
}
void state::exit() {
//Code executed at the end of the simulation.

}
