#include "exponential_gen.h"
void exponential_gen::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//			%Name% is the parameter name
//			%Type% is the parameter type

exp_lambda = 9;
time = new StochasticLib1(76);
sigma = time -> exponential(exp_lambda);
}
double exponential_gen::ta(double t) {
//This function returns a double.
return sigma;
}
void exponential_gen::dint(double t) {
sigma = time -> exponential(exp_lambda);
output = time -> uniform(0,9);

}
void exponential_gen::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

}
Event exponential_gen::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
	output++;

return Event(&output,0);
}
void exponential_gen::exit() {
//Code executed at the end of the simulation.

}
