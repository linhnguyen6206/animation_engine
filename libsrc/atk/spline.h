#ifndef spline_H_
#define spline_H_

#include "agl/aglm.h"
#include <map>
#include <vector>

namespace atk {
class Spline
{
  public:
    struct Key {float time; glm::vec3 pos; glm::quat ori;};

  public:
    // constructor
    Spline();

    // destructor
    virtual ~Spline();

    // Edit the key with the given ID
    // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
    void editKey(int keyID, const glm::vec3& value); 
    void editKey(int keyID, const glm::quat& value); 

    // Appends a key with the given time and value
    // Triggers a recomputation of control points
    // Time must be larger than all previously added keys
    // (e.g,user must ensure keys are sorted)
    // @param time: a non-negative value
    // @param value: the key's value
    int appendKey(float time, const glm::vec3& value, const glm::quat& ori = glm::quat());

    // Delete the key with the given ID
    // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
    void deleteKey(int keyID);

    // Return the Key of the key with the given ID
    // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
    Key getKey(int keyID) const;

    // Return the position of the key with the given ID
    // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
    glm::vec3 getPos(int keyID) const;

    // Return the time of the key with the given ID
    // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
    float getTime(int keyID) const;

    // Return the orientation of the key with the given ID
    // @param keyID: Valid IDs are in range [0, getNumKeys()-1]
    glm::quat getOri(int keyID) const;

    // Return the number of keys
    int getNumKeys() const;

    // Returns the number of segments (numkeys-1 if numkeys > 1)
    int getNumSegments() const;

    // Removes all keys
    void clear();

    // Returns the duration of the spline
    float getDuration() const;

    // Returns the interpolated key value at realtime t 
    // Position is interpolated with a Catmull-Rom Spline
    // Orientation is interpolated with slerp
    // @param t: a non-negative value
    Key getValue(float t) const;

    // Returns the value of Catmull-Rom control points for the given segment id 
    // @param is: a non-negative value, the segment id
    glm::vec3 getB0(int id) const;
    glm::vec3 getB1(int id) const;
    glm::vec3 getB2(int id) const;
    glm::vec3 getB3(int id) const;

  protected:
    std::vector<Key> mKeys;
};
}
#endif
