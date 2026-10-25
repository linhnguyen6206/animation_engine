#include <string>
#include <iostream>
#include <algorithm>
#include "atkui/framework.h"
using namespace glm;

class Animation : public atkui::Framework
{
public:
  Animation() : atkui::Framework(atkui::Perspective) { }
  virtual ~Animation() { }

  virtual void setup()
  {
    double d = 200;
    p0 = vec3(d,50,d);
    p1 = vec3(-d,50,d);
    p2 = vec3(-d,50,-d);
    p3 = vec3(d,50,-d);

    vec3 up(0, 1, 0);

    // Calculate the normalized directions for each portion of the run
    vec3 dir01 = normalize(p1 - p0);
    vec3 dir12 = normalize(p2 - p1);
    vec3 dir23 = normalize(p3 - p2);
    vec3 dir30 = normalize(p0 - p3);

    //Generate quaternions facing those directions
    quat q01 = quatLookAt(-dir01, up);
    quat q12 = quatLookAt(-dir12, up);
    quat q23 = quatLookAt(-dir23, up);
    quat q30 = quatLookAt(-dir30, up);

    float t = 0.0f;
    const float moveTime = 3.0f;
    const float turnTime = 1.0f;

    //Portion 1: p0 -> p1
    mAnimation.appendKey(t, p0, q01); // Starting at p0 facing p1
    t+= moveTime;
    mAnimation.appendKey(t, p1, q01); // Arrive at p1
    t += turnTime;
    mAnimation.appendKey(t, p1, q12); // Turn to face p2

    //Portion 2: p1 -> p2
    t += moveTime;
    mAnimation.appendKey(t, p2, q12); // Arrive at p2
    t += turnTime;
    mAnimation.appendKey(t, p2, q23); // Turn to face p3

    //Portion 3: p2 -> p3
    t += moveTime;
    mAnimation.appendKey(t, p3, q23); //Arrive at p3
    t += turnTime;
    mAnimation.appendKey(t, p3, q30); //Turn to face p0

    //Portion 4: p3 -> p0
    t += moveTime;
    mAnimation.appendKey(t, p0, q30); // Arrive at p0
    t += turnTime;
    mAnimation.appendKey(t, p0, q01);
  }

  virtual void scene()
  {
    float u = fmod(elapsedTime(), mAnimation.getDuration());
    atk::Spline::Key key = mAnimation.getValue(u);

    setColor(vec3(1,0,0));
    push();
    translate(key.pos);
    rotate(angle(key.ori), axis(key.ori));

    rotate(glm::radians(90.0f), vec3(0.0f, 0.0f, 1.0f));
    scale(vec3(50, 50, 75));
    drawCone(vec3(0,0,0), 1.0f);
    pop();
  
    setColor(vec3(0,0,1));
    drawSphere(p0, 10.0f);
    drawSphere(p1, 10.0f);
    drawSphere(p2, 10.0f);
    drawSphere(p3, 10.0f);
  }

protected:
  atk::Spline mAnimation;
  vec3 p0, p1, p2, p3;
};

int main(int argc, char** argv)
{
  Animation animation;
  animation.run();
  return 0;
}
