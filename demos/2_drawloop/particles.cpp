#include "agl/window.h"

using namespace glm;
using glm::vec3;

#define WIDTH 500
#define HEIGHT 500

struct Particle {
  vec3 position;
  vec4 color;
  vec3 velocity;
};

class MyWindow : public agl::Window {
  void setup() {
    setWindowSize(WIDTH, HEIGHT);

    ortho(0, WIDTH, 0, HEIGHT, -1000, 1000);
    background(vec3(0.0));
    setCameraEnabled(false); 

    renderer.loadTexture("particle", "../textures/particle.png", 0);
    renderer.blendMode(agl::ADD);
    int numParticles = 100;
    for (int i = 0; i < numParticles; i++) {
      Particle p;
      // aglm::random is used to initialize values within the screen
      p.position = vec3(agl::random() * width(), agl::random() * height(), agl::random() * 100.0f);
      p.velocity = vec3(agl::random() * 100.0f - 50.0f, agl::random() * 100.0f - 50.0f, 0.0f);
      p.color = vec4(0.2f + 0.8f * agl::random(),
                      0.2f + 0.8f * agl::random(),
                    0.2f + 0.8f * agl::random(),
                  1.0f);
      particles.push_back(p);
    }
  }
  
  void draw() {
    for (Particle& p : particles) {
      p.position = p.position + p.velocity * dt();

      if (p.position.x < 0)        p.position.x += width();
      if (p.position.x > width())  p.position.x -= width();
      if (p.position.y < 0)        p.position.y += height();
      if (p.position.y > height()) p.position.y -= height();
    }

    std::sort(particles.begin(), particles.end(), [](const Particle& a, const Particle& b) {
      return a.position.z < b.position.z;
    });
    renderer.beginShader("sprite");
    renderer.texture("image", "particle");

    // sprites take a position, color (RGBA), and size
    // (optional) For the best-looking blending, use the Z value to place
    // particle in front of the previous
    for (const Particle&p : particles) {
    renderer.sprite(p.position, p.color, 50.0f);
    }
    renderer.endShader();
  }

  private:
    std::vector<Particle> particles;
};

int main() {
  MyWindow window;
  window.run();
}