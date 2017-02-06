#include "conveyor_belt_statics.h"
void conveyor_belt_statics::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

print = 0;
status = "RUNNING";
counter = 0;
rejected = 0;
onBelt = 0;
sigma = inf;

}
double conveyor_belt_statics::ta(double t) {
//This function returns a double.
return sigma;
}
void conveyor_belt_statics::dint(double t) {
if (print == 0){
	print=1;
	sigma = 0;
}else {
	print= 0;
	sigma = inf;
}

}
void conveyor_belt_statics::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
int port = x.port;
std::string xv;
xv = *(std::string*)(x.value);

if (port == 0){
	if (xv == "ARRIVE"){
		counter++;
		if (status == "RUNNING"){
			onBelt++;
			sigma = 0;
		}else if (status == "STOPPED"){
			rejected++;
			sigma = 0;
		}
	}
}else if (port == 1){
	if (xv == "START"){
		status = "RUNNING";
	}else if (xv == "STOP"){
		status = "STOPPED";
	}
}else if (port == 2) {
	if (xv == "LEAVE"){
		onBelt--;
		sigma = 0;
	}
}
}
Event conveyor_belt_statics::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
int port;
if (print == 0){
	y = rejected/counter;
	port = 0;	
	//printLog("Conveyor Belt Statics: rate of rejected: %f at %f\n", y, t);
} else {
	y = onBelt;
	port = 1;
	//printLog("Conveyor Belt Statics: jobs on belt: %f at %f\n", y, t);
}
return Event(&y, port);
}
void conveyor_belt_statics::exit() {
//Code executed at the end of the simulation.
printLog("Conveyor Belt Statics: \nTotal of pieces received: %f\n", counter);
printLog("Total of pieces rejected: %f\n", rejected);
printLog("Proportion of pieces rejected: %f %\n", rejected/counter*100);
}
