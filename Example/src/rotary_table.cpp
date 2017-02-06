#include "rotary_table.h"
void rotary_table::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

tMov = va_arg(parameters,double);
status = "NOTPICKING";
position = "DOWNLEFT";
elapsed = 0;
sigma = inf;
}
double rotary_table::ta(double t) {
//This function returns a double.
return sigma;
}
void rotary_table::dint(double t) {
if (status == "PICKING") {
	sigma = inf;
}else if (status == "PICKED") {
	status = "NOTPICKING";
	sigma = inf;
}else if ((position == "UPRIGHT") && (status == "NOTPICKING")) {
	status = "PICKING";
	sigma = 0;
}else {
	elapsed += sigma;
	sigma = inf;
}
}
void rotary_table::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
int p = x.port;
std::string xv;
xv = *(std::string*)(x.value);
if (p == 0){
	if (xv == "ARRIVE") {
		position = "DOWNRIGHT";
		elapsed = 0;
		sigma = tMov;
	}
}else if (p == 1){
	if (xv == "ROTATELEFT") {
		position = "UPLEFT";
		elapsed = 0;
		sigma = tMov;
	}else if (xv == "MOVEUP") {
		position = "UPRIGHT";
		elapsed = 0;
		sigma = tMov;
	}else if (xv == "MOVEDOWN") {
		position = "DOWNLEFT";
		elapsed = 0;
		sigma = tMov;
	}
}else if (p == 2){
	if (xv == "PICK") {
		status = "PICKED";
		sigma = 0;
	}
}else {
	if (elapsed < tMov) {
		position = "UPLEFT";
		elapsed += e;
		sigma = tMov - elapsed;
	}else{
		position = "UPRIGHT";
		elapsed += e;
		sigma = inf;
	}
}
//printLog("Rotary Table INPUT: %s at %f\n", xv.c_str(), t);
}
Event rotary_table::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
//printLog("Rotary Table: %s at %f\n", status.c_str(), t);
int port;
if (status == "PICKING") {
	y = "READY";
	port = 1;
}else if (status == "PICKED") {
	y = "PICKED";
	port = 0;
}else if (position == "DOWNLEFT") {
	y = "DOWN";
	port = 0;
}else if (position == "DOWNRIGHT") {
	y = "RIGHT";
	port = 0;
}else if (position == "UPRIGHT") {
	y = "UP";
	port = 0;
}else if (position == "UPLEFT") {
	y = "LEFT";
	port = 0;
}
//printLog("Rotary Table OUTPUT: %s at %f\n", y.c_str(), t);
return Event(&y, port);
}
void rotary_table::exit() {
//Code executed at the end of the simulation.

}
