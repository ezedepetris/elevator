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
}