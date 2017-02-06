#include "system_control.h"
void system_control::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//			%Name% is the parameter name
//			%Type% is the parameter type

position = "DOWNLEFT";
sigma = inf;
}
double system_control::ta(double t) {
//This function returns a double.
return sigma;
}
void system_control::dint(double t) {
sigma = inf;
}
void system_control::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
int p = x.port;
std::string xv;
xv = *(std::string*)(x.value);

if (p == 0){
	if ((xv == "DETECT") && (position != "DOWNLEFT")){
		signal = "DETECT";
		sigma = 0;
	}else if ((xv == "LEAVE") && (position == "DOWNLEFT")){
		position = "DOWNRIGHT";
		signal = "LEAVE";
		sigma = 0;	
	}
}else if (p == 1){
	if (xv == "LEFT"){
		signal = "LEFT";
		position = "UPLEFT";
		sigma = 0;
	}else if (xv == "DOWN"){
		signal = "DOWN";
		position = "DOWNLEFT";
		sigma = 0;	
	}else if (xv == "RIGHT"){
		signal = "RIGHT";
		position = "DOWNRIGHT";
		sigma = 0;	
	}else if (xv == "UP"){
		signal = "UP";
		position = "UPRIGHT";
		sigma = 0;	
	}else if (xv == "PICKED"){
		signal = "PICKED";
		sigma = 0;	
	}
}
}
Event system_control::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
int port;
if (signal == "DETECT") {
	y = "STOP";
	port = 0;
}else if (signal == "LEAVE"){
	y = "ARRIVE";
	port = 1;
}else if (signal == "LEFT"){
	y = "MOVEDOWN";
	port = 2;
}else if (signal == "DOWN"){
	y = "START";
	port = 0;
}else if (signal == "RIGHT"){
	y = "MOVEUP";
	port = 2;
}else if (signal == "PICKED"){
	y = "ROTATELEFT";
	port = 2;
}
//printLog("System Control: %s at %f\n", y.c_str(), t);
return Event(&y, port);
}
void system_control::exit() {
//Code executed at the end of the simulation.

}
