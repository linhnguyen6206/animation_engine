#include <cmath>
#include "spline.h"
#include "math.h"

namespace atk {
Spline::Key Spline::getValue(float t) const 
{
  // todo: your code here
  // compute the segment containing t
  // compute the normalized time along the segment
  // compute the value along the segment for interpolation
  return Key(); 
}

glm::vec3 Spline::getB0(int id) const
{
  assert(id >= 0 && id < mKeys.size()-1);
    // todo
  return glm::vec3(0); 
}

glm::vec3 Spline::getB1(int id) const
{
  assert(id >= 0 && id < mKeys.size()-1);
    // todo
  return glm::vec3(0); 

}

glm::vec3 Spline::getB2(int id) const
{
  assert(id >= 0 && id < mKeys.size()-1);
    // todo
  return glm::vec3(0); 

}

glm::vec3 Spline::getB3(int id) const
{
  assert(id >= 0 && id < mKeys.size()-1);
    // todo
  return glm::vec3(0); 

}
}