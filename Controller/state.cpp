#include "state.h"
void state::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
	current_flor = 1;
	final_flor = 1;
	free = true;
	sigma = INF;
	stop = false;
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
	if (final_flor != x.0.value && !free){
		current_flor = x.0.value;
		free = false;
		sigma = INF;
		stop = false;
	}
	if (final_flor == x.0.value){
		current_flor = x.0.value;
		free = true;
		sigma = 0;
		stop = true;
	}
	if (free x.1.value != nil){
		final_flor x.1.value;
		free = false;
		sigma = 0;
		stop = false;
	}
	if (!free && x.1.value != nil){
		free = false;
		sigma = INF;
		stop = false;
	}
}
Event state::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
	if (final_flor > current_flor && !free)
		return Event("arriba",0) && Event("ocupado",1);
	if (final_flor < current_flor && !free)
		return Event("abajo",0) && Event("ocupado",1);
	if (final_flor == current_flor && free)
		return Event("parar",0) && Event("libre",1);
}
void state::exit() {
//Code executed at the end of the simulation.

}
