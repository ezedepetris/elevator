// MathFuncsLib.cpp
// compile with: cl /c /EHsc MathFuncsLib.cpp
// post-build command: lib MathFuncsLib.obj

#include "FunctionsLib.h"

#include <stdexcept>

using namespace std;
namespace Elevator{
  int Functions::Add(int a, int b){
		return a + b;
  }

	double TimeToDestiny(int origin_floor, int destiny_floor, double time_sended, double time_now){
		double avanced_floor = (time_now - time_sended) * 2;
		double floors_to_destiny = destiny_floor - (origin_floor - avanced_floor);
		return floors_to_destiny * 2;
	}
}
