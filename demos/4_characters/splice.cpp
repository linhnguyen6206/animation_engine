#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace atkui;
using namespace glm;

class ASplice : public atkui::Framework
{
public:
   ASplice() : atkui::Framework(atkui::Perspective) {}
   virtual ~ASplice() {}

   void setup()
   {
      _alpha = 0.0f;

      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _lower);
      reader.load("../motions/Beta/gangnam_style.bvh", _skeleton, _upper);
      _splice = spliceUpperBody(_lower, _upper, _alpha);
   }

   Motion spliceUpperBody(const Motion& lower, const Motion& upper, float alpha)
   {
      Motion result;
      result.setFramerate(lower.getFramerate());

      int numKeys = 250;
      for (int i = 0; i < numKeys; i++)
      {
         //Loop the lower walking motion
         Pose origPose = lower.getKey(i % lower.getNumKeys());

         //Start with the lower body and root position from the
         //walking motion
         Pose newPose = origPose;

         if (i >= 120) {
            int upperFrame = (i - 120) % upper.getNumKeys();
            Pose upperPose = upper.getKey(upperFrame);
            //Loop through every joint to check if it is a part of the
            //upper body
            for (int j = 0; j < _skeleton.getNumJoints(); j++)
            {
               Joint* curr = _skeleton.getByID(j);
               bool isUpperBody = false;

               // Traverse up the skeleton hierarchy to see if this joint descends
               //from the spine
               while (curr != nullptr)
               {
                  if (curr->getName() == "Beta:Spine1")
                  {
                     isUpperBody = true;
                     break;
                  }
                  curr = curr->getParent();
               }

               if (isUpperBody) 
               {
                  newPose.jointRots[j] = glm::slerp(origPose.jointRots[j], upperPose.jointRots[j], alpha);
               }
            }
   
         }
         result.appendKey(newPose);
      }
      return result;
   }

   void scene()
   {  
      _splice.update(_skeleton, elapsedTime() * 0.5);
      SkeletonDrawer drawer;
      drawer.draw(_skeleton, *this);
      drawText("alpha: "+std::to_string(_alpha), 10, 15);
   }

   void keyUp(int key, int mods) 
   {
      if (key == GLFW_KEY_UP)
      {
         _alpha = std::min(_alpha+0.05, 1.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
      else if (key == GLFW_KEY_DOWN)
      {
         _alpha = std::max(_alpha-0.05, 0.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
   }

   Skeleton _skeleton;
   Motion _upper;
   Motion _lower;
   Motion _splice;
   float _alpha;
};

int main(int argc, char** argv)
{
   ASplice viewer;
   viewer.run();
   return 0;
}

