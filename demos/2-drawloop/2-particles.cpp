#include "atkui/framework.h"
#include "agl/aglm.h"

using namespace glm;

struct Particle {
  vec3 position;
  vec4 color;
  vec3 velocity;
};

class Particles : public atkui::Framework
{
 public:
  Particles() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    int numParticles = 100;
    for (int i = 0; i < numParticles; i++) {
      Particle p;
      // aglm::random is used to initialize values within the screen
      p.position = vec3(agl::random() * width(), agl::random() * height(), 0.0f);
      p.velocity = vec3(agl::random() * 100.0f - 50.0f, agl::random() * 100.0f - 50.0f, 0.0f);
      p.color = vec4(0.2f + 0.8f * agl::random(),
                      0.2f + 0.8f * agl::random(),
                    0.2f + 0.8f * agl::random(),
                  1.0f);
      particles.push_back(p);
    }
  }

  virtual void scene() {
    for (Particle& p : particles) {
      p.position = p.position + p.velocity * dt();

      if (p.position.x < 0)        p.position.x += width();
      if (p.position.x > width())  p.position.x -= width();
      if (p.position.y < 0)        p.position.y += height();
      if (p.position.y > height()) p.position.y -= height();
    }

    std::sort(particles.begin(), particles.end(), [](const Particle& a, const Particle& b) {
      return a.position.z > b.position.z;
    });
    for (const Particle& p : particles) {
      setColor(p.color);
      drawSphere(p.position, 5.0f);
    }
  }

  private:
    std::vector<Particle> particles; 
};

int main(int argc, char** argv) {
  Particles viewer;
  viewer.run();
  return 0;
}
