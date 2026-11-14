#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace atk;
using glm::vec3;
using glm::quat;

class Tentacle : public atkui::Framework
{
public:
   Tentacle() : atkui::Framework(atkui::Perspective) {}
   virtual ~Tentacle() {}

   virtual void setup()
   {
      lookAt(vec3(200,200,200), vec3(0));

      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0));
      _tentacle.addJoint(root);

      Joint* joint1  = new Joint("joint1");
      joint1->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint1, root);

      Joint* joint2  = new Joint("joint2");
      joint2->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint2, joint1);

      Joint* joint3  = new Joint("joint3");
      joint3->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint3, joint2);

      Joint* joint4  = new Joint("joint4");
      joint4->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint4, joint3);

      _tentacle.fk();
   }

   virtual void scene()
   {
      for (int i = 0; i < _tentacle.getNumJoints(); i++)
      {
         Joint* joint = _tentacle.getByID(i);
         quat q = glm::angleAxis((float) sin(i+elapsedTime()), vec3(0,0,1)); 
         joint->setLocalRotation(q);
      }
      _tentacle.fk();

      setColor(vec3(0,1,0));
      for (int i = 0; i < _tentacle.getNumJoints(); i++)
      {
         Joint* joint = _tentacle.getByID(i);
         if (joint->getParent() == NULL) continue;
         
         vec3 globalParentPos = joint->getParent()->getGlobalTranslation();
         vec3 globalPos = joint->getGlobalTranslation();
         //drawEllipsoid(globalParentPos, globalPos, 5);
      }
   }

protected:
   Skeleton _tentacle;
};

int main(int argc, char** argv)
{
   Tentacle viewer;
   viewer.run();
} 

