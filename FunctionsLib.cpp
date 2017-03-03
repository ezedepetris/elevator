// MathFuncsLib.cpp
// compile with: cl /c /EHsc MathFuncsLib.cpp
// post-build command: lib MathFuncsLib.obj

#include "FunctionsLib.h"

#include <stdexcept>

using namespace std;
namespace Elevator{
  double Fuctions::Add(int a, int b){
      return a + b;
  }
}
