#include "robot.h"
void robot::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
a = va_arg(parameters,double);
b = va_arg(parameters,double);

status = "NOTBUSY";
sigma = inf;

y = "PICK";

srand(time(NULL));
}
double robot::ta(double t) {
//This function returns a double.
return sigma;
}
void robot::dint(double t) {
status = "NOTBUSY";
sigma = inf;
}
void robot::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
int p = x.port;
std::string xv;
xv = *(std::string*)(x.value);
double r;
//printLog("Robot: %s, port: %i at %f\n", xv.c_str(), p, t);
if ((xv == "READY") && (status == "NOTBUSY")){
	status = "BUSY";
	r = (1 - (double)lcgrand(0) / ((double)RAND_MAX + 1));
	sigma = r * (b - a) + a;
}else {
	sigma = sigma - e;
}
}
Event robot::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
//printLog("Robot: %s at %f\n", y.c_str(), t);
return Event(&y, 0);
}
void robot::exit() {
//Code executed at the end of the simulation.

}
