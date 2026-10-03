#include "atk/motion.h"
#include <cmath>

namespace atk {
Motion::Motion(double fps) :
  mDt(1.0/fps),
  mFps(fps) {
}

Motion::~Motion() {
}

void Motion::update(Skeleton& skeleton, double time, bool loop) const {
  Pose pose = getValue(time, loop); 
  skeleton.setPose(pose);
}

void Motion::setFramerate(double fps) {
  mFps = fps;
  mDt = 1/fps;
}

double Motion::getFramerate() const {
  return mFps;
}

void Motion::setDeltaTime(double dt) {
  mDt = dt;
  mFps = 1/dt;
}

double Motion::getDeltaTime() const {
  return mDt;
}

void Motion::editKey(int keyID, const Pose& value) {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys[keyID] = value;
}

void Motion::appendKey(const Pose& value) {
  mKeys.push_back(value);
}

void Motion::deleteKey(int keyID) {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys.erase(mKeys.begin() + keyID);
}

Pose Motion::getKey(int keyID) const {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  return mKeys[keyID];
}

int Motion::getNumKeys() const {
  return (int) mKeys.size();
}

void Motion::clear() {
  mKeys.clear();
}

double Motion::getDuration() const {
  return 0.0; // todo
}

double Motion::getNormalizedDuration(double t) const {
  return 0.0; // todo
}

int Motion::getKeyID(double t) const {
  return 0; // todo
}

Pose Motion::getValue(double t, bool loop) const {
  return Pose()
} // todo
}
