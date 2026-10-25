#include <string>
#include <iostream>
#include <algorithm>
#include "atk/toolkit.h"
#include "atkui/framework.h"

using glm::vec3;

class CurveEditor : public atkui::Framework
{
public:
  CurveEditor() : atkui::Framework(atkui::Orthographic), 
    mSpline(),
    mRadius(10.0),
    mSelected(-1),
    mButtonState(0),
    mMode(ADD) 
  {
  }

  ~CurveEditor() 
  {
  }

  void setup() 
  {
    listControls();
  }

  void scene() 
  {
    drawState();
      
    int nkeys = mSpline.getNumKeys();
    for (int i = 0; i < nkeys; i++)
    {
      vec3 p = mSpline.getPos(i);
      setColor(vec3(0,0,1));
      drawSphere(p, 10);
    }
      
    int nsegs = mSpline.getNumSegments();
    if (nsegs == 0) return;

    for (int i = 0; i < nsegs; i++)
    {
      vec3 B1 = mSpline.getB1(i);
      vec3 B2 = mSpline.getB2(i);

      setColor(vec3(1,1,0));
      drawSphere(B1, 10);
      drawSphere(B2, 10);
    }

    setColor(vec3(1,1,1));
    float startTime = mSpline.getTime(0);
    vec3 p0 = mSpline.getPos(0);
    vec3 p1;
    for (float t = startTime; t < mSpline.getDuration(); t += 0.1f)
    {
      p1 = mSpline.getValue(t).pos;
      drawLine(p0, p1);
      p0 = p1;
    }
    drawLine(p0, mSpline.getPos(nsegs));
  }

  void addPoint(const vec3& p) 
  {
    //std::cout << "Add key: " << p << std::endl;
    mSpline.appendKey(mSpline.getNumKeys(), p);
  }

  void deletePoint(int key) 
  {
    mSpline.deleteKey(key);
  }

  void drawState() 
  {
    int th = 25;
    switch (mMode) 
    {
      case ADD: drawText("Mode: ADD", 5, th); break;
      case EDIT: drawText("Mode: EDIT", 5, th); break;
      case REMOVE: drawText("Mode: DELETE", 5, th); break;
    }
  }

  void listControls() 
  {
    std::cout << "Key controls:" << std::endl;
    std::cout << "c: Toggle control points" << std::endl;
    std::cout << "a: add mode" << std::endl;
    std::cout << "e: edit mode" << std::endl;
    std::cout << "d: delete mode" << std::endl;
    std::cout << "SPACEBAR: clear" << std::endl;
  }

  void mouseMotion(int pX, int pY, int dx, int dy) 
  {
    if (mMode != EDIT) return;
    if (mSelected == -1) return;
    
    if (mButtonState == GLFW_MOUSE_BUTTON_LEFT) 
    {
      vec3 p = vec3(pX, height() - pY, 0);
      mSpline.editKey(mSelected, p);
    }
  }

  int pickPoint(int x, int y) 
  {
    vec3 tmp = vec3(x, y, 0);
    int num = mSpline.getNumKeys();
    for (int i = 0; i < num; i++) 
    {
      vec3 pt = mSpline.getKey(i).pos;
      if (length(tmp - pt) < mRadius) 
      {
        return i;
      }
    }
    return -1;
  }

  void mouseUp(int pButton, int state) 
  {
    if (mButtonState == GLFW_MOUSE_BUTTON_LEFT) 
    {
      mSelected = -1;
    }
  }

  void mouseDown(int pButton, int state) 
  {
    mButtonState = pButton;
    glm::vec2 p = mousePosition();
    int pX = (int) p.x;
    int pY = (int) p.y;

    if (mButtonState == GLFW_MOUSE_BUTTON_LEFT) 
    {
      if (mMode == ADD) 
      {
        vec3 tmp(p, 0);
        // guard against adding multiple copies of the same point
        // (multiple mouse events may be triggered for the same point)
        bool add = true;
        if (mSpline.getNumKeys() > 0) 
        {
          vec3 lastKey = mSpline.getPos(mSpline.getNumKeys() - 1);
          float d = length(lastKey-tmp);
          if (d < 10) add = false;
        }

        if (add) 
        {
          addPoint(vec3(pX, height()-pY, 0));
        }
      } 
      else if (mMode == REMOVE) 
      {
        mSelected = pickPoint(pX, height() - pY);
        std::cout << "selected: "  << mSelected << std::endl;
        if (mSelected >= 0) deletePoint(mSelected);

      } 
      else if (mMode == EDIT) 
      {
        mSelected = pickPoint(pX, height() - pY);
        //std::cout << "SELECTED: " << mSelected << std::endl;
        mouseMotion(pX, pY, 0, 0);
      }
    }
  }

  void keyUp(int pKey, int mods) 
  {
    if (pKey == 'p') 
    {
      for (int i = 0; i < mSpline.getNumKeys(); i++) 
      {
        std::cout << mSpline.getKey(i).pos << std::endl;
      }
    } 
    else if (pKey == 'A') 
    {
      mMode = ADD;
    } 
    else if (pKey == 'D') 
    {
      mMode = REMOVE;
    } 
    else if (pKey == 'E') 
    {
      mMode = EDIT;
    } 
    else if (pKey == GLFW_KEY_SPACE) 
    {
      mSpline.clear();
    } 
  }
  int mRadius;
  int mSelected;
  int mButtonState;

  enum Mode { ADD, EDIT, REMOVE } mMode;

  atk::Spline mSpline;
};

int main(int argc, char** argv)
{
  CurveEditor viewer;
  viewer.run();
  return 0;
}
