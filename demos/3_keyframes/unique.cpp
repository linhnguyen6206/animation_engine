#include <string>
#include <iostream>
#include <vector>
#include "atkui/framework.h"
#include "atk/spline.h"

using namespace glm;

struct Particle {
    vec3 origPos;
    vec3 currPos;
    vec3 velocity;
    vec3 color;
};

class MagneticRippleField : public atkui::Framework
{
public:
  MagneticRippleField() : atkui::Framework(atkui::Perspective) { }
  virtual ~MagneticRippleField() { }

  virtual void setup()
  {
    // 1. Setup the particle field (a flat grid that will ripple in 3D)
    float spacing = 20.0f;
    for (float x = -250; x <= 250; x += spacing) {
      for (float z = -250; z <= 250; z += spacing) {
        Particle p;
        p.origPos = vec3(x, 0.0f, z);
        p.currPos = p.origPos;
        p.velocity = vec3(0.0f);
        
        // Base color
        p.color = vec3(0.0f, 0.5f, 0.8f);
        mParticles.push_back(p);
      }
    }

    // 2. Setup the Spline for the magnet
    float t = 0.0f;
    const float legTime = 2.0f;
    
    // Add extra wrap-around keys for Catmull-Rom boundaries
    mAnimation.appendKey(t, vec3(0, 50, 0), quat()); t += legTime;
    mAnimation.appendKey(t, vec3(200, -20, 200), quat()); t += legTime;
    mAnimation.appendKey(t, vec3(0, 50, 0), quat()); t += legTime;
    mAnimation.appendKey(t, vec3(-200, -20, -200), quat()); t += legTime;
    mAnimation.appendKey(t, vec3(0, 50, 0), quat());
  }

  virtual void scene()
  {
    // Get current position of the magnet
    float u = fmod(elapsedTime(), mAnimation.getDuration());
    atk::Spline::Key key = mAnimation.getValue(u);
    vec3 magnetPos = key.pos;

    // Draw the Magnet
    setColor(vec3(1.0f, 0.2f, 0.2f));
    drawSphere(magnetPos, 20.0f);

    // Update and Draw Particles
    float dt_val = dt(); // Delta time for smooth physics
    float influenceRadius = 150.0f;
    float pullStrength = 50.0f;
    float springStiffness = 10.0f;
    float damping = 0.9f;

    for (Particle& p : mParticles) 
    {
      // Calculate distance to the magnet
      vec3 dirToMagnet = magnetPos - p.currPos;
      float dist = length(dirToMagnet);

      vec3 force(0.0f);

      // Apply magnetic pull if within radius
      if (dist < influenceRadius && dist > 0.1f) {
        float intensity = 1.0f - (dist / influenceRadius);
        force += normalize(dirToMagnet) * (intensity * pullStrength);
        
        // Temporarily brighten the color based on magnetic influence
        p.color = mix(vec3(0.0f, 0.5f, 0.8f), vec3(1.0f, 1.0f, 0.0f), intensity);
      } else {
        // Fade back to normal color
        p.color = mix(p.color, vec3(0.0f, 0.5f, 0.8f), 0.05f);
      }

      // Apply spring force to return to original position
      vec3 springForce = (p.origPos - p.currPos) * springStiffness;
      force += springForce;

      // Physics integration
      p.velocity += force * dt_val;
      p.velocity *= damping; // Add friction
      p.currPos += p.velocity * dt_val;

      // Render the particle
      setColor(p.color);
      drawSphere(p.currPos, 3.0f);
    }
  }

protected:
  atk::Spline mAnimation;
  std::vector<Particle> mParticles;
};

int main(int argc, char** argv)
{
  MagneticRippleField animation;
  animation.run();
  return 0;
}