#include "conveyor_belt.h"
void conveyor_belt::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//			%Name% is the parameter name
//			%Type% is the parameter type
l 			= va_arg(parameters,double);
vc 		= va_arg(parameters,double);
deltaL 	= va_arg(parameters,double);

speed 	= vc;
sigma	= inf;
y			= "null";

}
double conveyor_belt::ta(double t) {
//This function returns a double.
return sigma;
}
void conveyor_belt::dint(double t) {
double d1;
d1 = distances.back();
double d2;
std::list<double>::iterator iterator;
iterator = distances.begin();
if (d1 < l){
		/*actualiza todas las distancias en la lista distances*/
		while (iterator != distances.end()){
			*iterator += sigma * speed;
			iterator++;
		}
		sigma = deltaL / vc;	
}else{
	distances.pop_back();
	if (distances.size() != 0){
		/*actualiza todas las distancias en la lista distances*/
		while (iterator != distances.end()){
			*iterator += sigma * speed;
			iterator++;
		}
		d2 = distances.back();
		sigma = (l - (d2)) / vc;
	}else{
		sigma = inf;
	}
}
}
void conveyor_belt::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
int p = x.port;
/*xv = valor del evento de entrada*/
std::string xv;
xv = *(std::string*)(x.value);

std::list<double>::iterator it;
it = distances.begin();
double d1;
if (p == 0){
	if ((xv == "ARRIVE") && (speed == vc)){
		if (distances.size() > 0){
			while (it != distances.end()){
				*it += e * speed;
				it++;
			}
		}
		distances.push_front(0);
		d1 = distances.back();
		if (d1 <= l){
			sigma = (l - (d1)) / vc;
		}else{
			sigma = ((l + deltaL) - (d1)) / vc;			
		}
	}
} else {
	if (xv == "STOP"){
		if (distances.size() > 0){
			while (it != distances.end()){
				*it += e * speed;
				it++;
			}
		}
		speed = 0;
		sigma = inf;				
	}else if (xv == "START"){
		/*actualiza todas las distancias en la lista distances*/
		if (distances.size() > 0){
			while (it != distances.end()){
				*it += e * speed;
				it++;
			}
			/*recalcula cuanto le falta al 1er elemento para llegar al final de la cinta*/
			d1 = distances.back();
			if (d1 < l){
				sigma = (l - (d1)) / vc;
			}else{
				sigma = ((l + deltaL) - (d1)) / vc;			
			}
		}
		speed = vc;
	}
}
}
Event conveyor_belt::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
double d1;
d1 	= distances.back();
if (d1 < l){
	y 	= "DETECT";
} else {
	y 	= "LEAVE";
}
//printLog("Conveyor Belt OUTPUT: %s at %f\n", y.c_str(), t);
return Event(&y, 0);
}
void conveyor_belt::exit() {
//Code executed at the end of the simulation.

}
