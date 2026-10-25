#include <cmath>
#include "spline.h"
#include "math.h"

namespace atk {
Spline::Key Spline::getValue(float t) const 
{
  // Handle edge cases
  //Insufficient keys
  if (mKeys.empty()) return Key(); 
  if (mKeys.size() == 1 || t <= mKeys.front().time) return mKeys.front();
  // Out of bounds
  if (t >= mKeys.back().time) return mKeys.back();

  // compute the segment containing t
  size_t i = 0;
  while (i < mKeys.size() - 2 && t > mKeys[i + 1].time) {
    i++;
  }
  // compute the normalized time along the segment
  float t0 = mKeys[i].time;
  float t1 = mKeys[i + 1].time;
  float u = (t - t0) / (t1 - t0);

  // compute the value along the segment for interpolation
  auto p0 = (i > 0) ? mKeys[i - 1].pos : mKeys[i].pos;
  auto p1 = mKeys[i].pos;
  auto p2 = mKeys[i + 1].pos;
  auto p3 = (i + 2 < mKeys.size()) ? mKeys[i + 2].pos : mKeys[i + 1].pos;

  float u2 = u * u;
  float u3 = u2 * u;

  auto interpolated_value = 0.5f * (
        (2.0f * p1) +
        (-p0 + p2) * u +
        (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * u2 +
        (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * u3
    );

    // Compute orientation using SLERP
    glm::quat q0 = mKeys[i].ori;
    glm::quat q1 = mKeys[i + 1].ori;
    glm::quat interpolated_ori = glm::slerp(q0, q1, u);

    Key result;
    result.time = t;
    result.pos = interpolated_value;
    result.ori = interpolated_ori;
  return result; 
}

glm::vec3 Spline::getB0(int id) const
{
  assert(id >= 0 && id < mKeys.size()-1);
  return mKeys[id].pos;
}

glm::vec3 Spline::getB1(int id) const
{
  assert(id >= 0 && id < mKeys.size()-1);

  glm::vec3 p1 = mKeys[id].pos;
  glm::vec3 p2 = mKeys[id + 1].pos;

  glm::vec3 p0 = (id > 0) ? mKeys[id - 1].pos : p1;

  return p1 + (p2 - p0) / 6.0f;

}

glm::vec3 Spline::getB2(int id) const
{
  assert(id >= 0 && id < mKeys.size()-1);
  
  glm::vec3 p1 = mKeys[id].pos;
  glm::vec3 p2 = mKeys[id + 1].pos;

  glm::vec3 p3 = (id + 2 < mKeys.size()) ? mKeys[id + 2].pos : p2;
  return p2 - (p3 - p1) / 6.0f;

}

glm::vec3 Spline::getB3(int id) const
{
  assert(id >= 0 && id < mKeys.size()-1);
  glm::vec3 p2 = mKeys[id + 1].pos;

  return p2;
}
}