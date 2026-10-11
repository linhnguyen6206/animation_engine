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
  }

  void keyUp(int key, int mod) {

    if (key == GLFW_KEY_1) {
      // draw linear
    }
    else if (key == GLFW_KEY_2) {
      // draw Cubic with polynomial formula
    }
    else if (key == GLFW_KEY_3) {
      // draw Cubic with de Casteljau's algorithm
    }
  }

 private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
};

int main(int argc, char** argv)
{
  DrawCurve window;
  window.run();
  return 0;
}
