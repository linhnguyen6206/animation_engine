#include <string>
#include <iostream>
#include <algorithm>
#include "atkui/framework.h"

using namespace glm;

class DrawCurve : public atkui::Framework
{
 public:
  DrawCurve() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  virtual void scene()
  {
    setColor(vec3(0,0,1));
    drawSphere(B0, 10);
    drawSphere(B3, 10);

    setColor(vec3(1,1,0));
    drawSphere(B1, 10);
    drawSphere(B2, 10);

    setColor(vec3(0.5f, 0.5f, 0.5f));
    drawLine(B0, B1);
    drawLine(B2, B3);
    //curve for selected mode
    if (mode == 0) return;

    setColor(vec3(1, 1, 1));
    const int numSegments = 100;
    vec3 prev = evaluate(0.0f);
    for (int i = 1; i <= numSegments; i++) {
      float t = (float) i / numSegments;
      vec3 next = evaluate(t);
      drawLine(prev, next);
      prev = next;
    }
    // Animation portion
    float duration = 2.0f;
    float loopedTime = std::fmod(elapsedTime(), duration);

    float time = loopedTime/duration;

    vec3 animatedPos = evaluate(time);

    setColor(vec3(1, 0, 0));
    drawSphere(animatedPos, 15);
  }

  void keyUp(int key, int mod) {

    if (key == GLFW_KEY_1) {
      mode = 1; // draw linear
    }
    else if (key == GLFW_KEY_2) {
      mode = 2; // draw cubic with polynomial formula
    }
    else if (key == GLFW_KEY_3) {
      mode = 3; // draw cubic with de Casteljau's algorithm
    }
  }

 private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
  int mode = 0;

  vec3 evaluate(float t) {
    if (mode == 1) return linear(B0, B3, t);
    if (mode == 2) return cubicPolynomial(t);
    return deCasteljau(t);
  }
  vec3 linear(const vec3& a, const vec3& b, float t) {
    return (1.0f - t) * a + t * b;
  }

  vec3 cubicPolynomial(float t) {
    float u = 1.0f - t;
    return u * u * u * B0 +
          3.0f * u * u * t * B1 +
          3.0f * u * t * t * B2 + 
          t * t * t * B3;
  }

  vec3 deCasteljau(float t) {
    vec3 b01 = linear(B0, B1, t);
    vec3 b12 = linear(B1, B2, t);
    vec3 b23 = linear(B2, B3, t);

    vec3 b012 = linear(b01, b12, t);
    vec3 b123 = linear(b12, b23, t);

    return linear(b012, b123, t);
  }
};

int main(int argc, char** argv)
{
  DrawCurve window;
  window.run();
  return 0;
}
