#include <cmath>
#include "spline.h"
#include "math.h"

namespace atk {
Spline::Spline() {}
Spline::~Spline() {}

void Spline::editKey(int keyID, const glm::vec3& value) 
{
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys[keyID].pos = value;
}

void Spline::editKey(int keyID, const glm::quat& ori) 
{
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys[keyID].ori = ori;
}

int Spline::appendKey(float time, const glm::vec3& value, const glm::quat& ori) 
{
  mKeys.push_back(Key{time, value, ori});
  return mKeys.size();
}

void Spline::deleteKey(int keyID) 
{
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys.erase(mKeys.begin() + keyID);
}

Spline::Key Spline::getKey(int keyID) const 
{
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  return mKeys[keyID];
}

glm::vec3 Spline::getPos(int keyID) const 
{
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  return mKeys[keyID].pos;
}

float Spline::getTime(int keyID) const 
{
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  return mKeys[keyID].time;
}

glm::quat Spline::getOri(int keyID) const 
{
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  return mKeys[keyID].ori;
}

int Spline::getNumKeys() const 
{
  return (int) mKeys.size();
}

void Spline::clear() 
{
  mKeys.clear();
}

float Spline::getDuration() const 
{
  if (mKeys.size() == 0) return 0;
  int lastIdx = mKeys.size() - 1;
  return mKeys[lastIdx].time;
}

int Spline::getNumSegments() const 
{
  if (mKeys.size() > 1) return mKeys.size()-1;
  return 0;
}

}