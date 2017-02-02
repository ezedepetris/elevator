#include "state.h"
void state::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
	current_floor      = 1;
	distance_next_flor = 0;
	state              = 0; // {down : -1, stop :0, up : 1}
	sigma              = INF;
	moving             = false;
}
double state::ta(double t) {
//This function returns a double.
	return sigma;
}
void state::dint(double t) {
	if (current_floor<10 && state==1 && moving==false){
		current_floor += 1;
		distance_next_flor = 2;
		state  = 1;
		sigma  = 2;
		moving = false;
	}
	if (current_floor>1 && state==-1 && moving==false){
		current_floor -= 1;
		distance_next_flor = 2;
		state  = -1;
		sigma  = 2;
		moving = false;
	}
	if ((current_floor==10 && state==1) || (current_floor==1 && state==-1) && moving==false){
		distance_next_flor = 0;
		state  = 0;
		sigma  = INF;
		moving = true;
	}
	if (state == 1 && moving == true){
		current_floor += 1;
		distance_next_flor = 2;
		state  = 0;
		sigma  = INF;
		moving = false;
	}
	if (state == -1 && moving == true){
		current_floor -= 1;
		distance_next_flor = 2;
		state  = 0;
		sigma  = INF;
		moving = true;
	}	
}
void state::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
	if (state == 0 && x.value == "arriba"){
		distance_next_flor = 2;
		state  = 1;
		sigma  = 2;
		moving = false;
	}
	if (state == 0 && x.value == "abajo"){
		distance_next_flor = 2;
		state  = -1;
		sigma  = 2;
		moving = false;
	}
	if (state == 0 && x.value == "parar"){
		distance_next_flor = 0;
		state  = 0;
		sigma  = INF;
		moving = false;
	}
	if (state != 0 && x.value != "parar"){
		distance_next_flor = 2-velocity*e;
		sigma  = 2-velocity*e;
		moving = false;
	}
	if (state == 0 && x.value == "parar"){
		distance_next_flor = 2-velocity*e;
		state  = 2-velocity*e;
		moving = true;
	}
}
Event state::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)


return Event(current_floor,0);
}
void state::exit() {
//Code executed at the end of the simulation.

}
