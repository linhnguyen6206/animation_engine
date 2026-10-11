#include "agl/window.h"

using namespace glm;
using glm::vec3;

#define WIDTH 500
#define HEIGHT 500

class MyWindow : public agl::Window {
  void setup() {
    setWindowSize(WIDTH, HEIGHT);

    ortho(0, WIDTH, 0, HEIGHT, -1000, 1000);
    background(vec3(0.0));
    setCameraEnabled(false); 

    renderer.loadTexture("particle", "../textures/particle.png", 0);
    renderer.blendMode(agl::ADD);
  }
  
  void draw() {
    renderer.beginShader("sprite");
    renderer.texture("image", "particle");

    // sprites take a position, color (RGBA), and size
    // (optional) For the best-looking blending, use the Z value to place
    // particle in front of the previous
    renderer.sprite(vec3(200,200,0), vec4(1,0,0,0.5), 200.0f);
    renderer.sprite(vec3(250,250,1), vec4(0,1,0,0.5), 200.0f);
    renderer.sprite(vec3(300,300,2), vec4(0,0,1,0.5), 200.0f);

    renderer.endShader();
  }
};

int main() {
  MyWindow window;
  window.run();
}