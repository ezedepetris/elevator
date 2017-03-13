// MathFuncsLib.cpp
// compile with: cl /c /EHsc MathFuncsLib.cpp
// post-build command: lib MathFuncsLib.obj

#include "FunctionsLib.h"
#include "elevator/constants.h"
#include <stdexcept>
#include <cmath>

using namespace std;
namespace Elevator{
  double Functions::TimeToDestiny(double origin_floor, double destiny_floor, double time_sended, double time_now){
    double avanced_floor = (time_now - time_sended) / 2;
    double floors_to_destiny;
    if (origin_floor < destiny_floor){
      floors_to_destiny = destiny_floor - (origin_floor + avanced_floor);
    }else{
      floors_to_destiny = (origin_floor - avanced_floor) - destiny_floor;  
    }    
    return floors_to_destiny * 2;
  }
  
  double Functions::ChooseController(double est1, double est2, double of1, double of2, double ff1, double ff2, double t1, double t2, double floor, double t){
  	// est1 = controller one state
  	// est2 = controller two state
  	// of1 = origin floor of controller one
  	// of2 = origin floor of controller two
  	// ff1 = final floor of controller one
  	// ff2 = final floor of controller two
  	// t1 = time to controller one came out
  	// t2 = time to controller one came out
  	// floor = request floor
    if ((est1 == vacant) && (est2 == vacant)){
    	if ((2*std::abs(floor-of1)) <= (2*std::abs(floor-of2))){
    		return 1;
    	}else{
    		return 2;
    	}
    }
    if ((est1 == vacant) && (est2 == busy)){
    	if ((2*std::abs(floor-of1)) <= (TimeToDestiny(of2,ff2,t2,t)+2*std::abs(floor-ff2))){
    		return 1;
    	}else{
    		return 2;
    	}	
    }
    if ((est1 == busy) && (est2 == vacant)){
    	if ((TimeToDestiny(of1,ff1,t1,t)+2*std::abs(floor-ff1)) <= (2*std::abs(floor-of2))){
    		return 1;
    	}else{
    		return 2;
    	}
    }
    if ((est1 == busy) && (est2 == busy)){
    	if ((TimeToDestiny(of1,ff1,t1,t)+2*std::abs(floor-ff1)) <= (TimeToDestiny(of2,ff2,t2,t)+2*std::abs(floor-ff2))){
    		return 1;
    	}else{
    		return 2;
    	}
    }
    return 1;
  }	
}
