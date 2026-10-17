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

    mAnimation.appendKey(0, p0, quat());
    mAnimation.appendKey(1, p0, quat());
  }

  virtual void scene()
  {
    float u = fmod(elapsedTime(), mAnimation.getDuration());
    atk::Spline::Key key = mAnimation.getValue(u);

    setColor(vec3(1,0,0));
    push();
    translate(key.pos);
    rotate(angle(key.ori), axis(key.ori));
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
