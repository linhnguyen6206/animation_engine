#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;

   double sy = m13;

   if (sy > 1.0) sy = 1.0;
   if (sy < -1.0) sy = -1.0;

   y = std::asin(sy);

   if (std::abs(std::cos(y)) > 0.0001)
   {
      x = std::atan2(-m23, m33);
      z = std::atan2(-m12, m11);
   }
   else
   {
      z = 0.0;
      if (sy > 0.0)
      {
         x = std::atan2(m21, m22);
      }
      else
      {
      x = std::atan2(-m21, m22);
      }
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;

   // 1. Extract Z
   double sz = -m12;

   // Clamp sin of z to [-1.0, 1.0]
   if (sz > 1.0) sz = 1.0;
   if (sz < -1.0) sz = -1.0;

   z = std::asin(sz);
   // if cos(z) is very close to 0, z is near +/- 90 degrees
   if (std::abs(std::cos(z)) > 0.0001)
   {
      // Not in Gimbal Lock
      // X uses Column 2
      x = std::atan2(m32, m22);
      
      // Y uses Row 1
      y = std::atan2(m13, m11);
   }
   else
   {
      // Gimbal lock: X and Y axes are aligned
      y = 0.0;

      // Because Y is 0, m23 is purely -sin(x) and m33 is purely cos(x)
      x = std::atan2(-m23, m33);
   }
   
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;

   // Extract X, and m[1][2] is -sin(theta_x)
   double sx = -m23;

   //Clamp sin of x to [-1.0][1.0]
   if (sx > 1.0) sx = 1.0;
   if (sx < -1.0) sx = -1.0;

   x = std::asin(sx);

   //Check for Gimbal lock
   // if cos(x) is very close to 0, x is near +/- 90 degrees
   if (std::abs(std::cos(x)) > 0.0001)
   {
      z = std::atan2(m21, m22);
      y = std::atan2(m13, m33);
   }
   else
   {
      // Gimbal lock: Y and Z axes are aligned
      // We lose a degree of freedom, so lock Z to 0 and calculate Y.
      z = 0.0;

      // When z is locked to 0, m21 simplifies to -sin(y) and m11
      // simplifies to cos(y)
      y = std::atan2(-m31, m11);
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;

   // m[1][0] is sin(theta_z) - element in the second row and first column
   // of the 3x3 rotation matrix
   double sz = m21;

   // Clamp sin of z to [-1.0, 1.0]
   if (sz > 1.0) sz = 1.0;
   if (sz < -1.0) sz = -1.0;

   z = std::asin(sz);
   // Check for Gimbal lock
   // if cos(z) is very close to 0 then z is near +/- 90 degrees
   if (std::abs(std::cos(z)) > 0.0001) 
   {
      // Not in Gimbal Lock: standard extraction
      // X = atan2(-m12, m11)
      x = std::atan2(-m23, m22);

      // Y = atan2(-m20, m00)
      y = std::atan2(-m31, m11);
   }
   else 
   {
      //Gimbal lock: X and Y axes are aligned.
      //We lose a degree of freedom, so we lock X to 0
      // and calculate the remaining rotation entirely on Y. 
      x = 0.0;

      if (sz > 0.0) 
      {
         // Z is +90 degrees
         // Matrix simplifies: m[0][2] = sin(y-x), m[0][1] = cos(y - x)
         //since x = 0, y = atan2(m[0][2], m[2][2])
         y = std::atan2(m13, m33);
      }
      else {
         // Z is -90 degrees
         // Matrix simplifies: m[0][2] = sin(y-x), m[0][1] = cos(y-x)
         // since x - 0, y = atan2(m[0][2], m[0][1])
         y = std::atan2(m13, m12);
      }
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;

   double sx = m32;
   if (sx > 1.0) sx = 1.0;
   if (sx < -1.0) sx = -1.0;

   x = std::asin(sx);

   if (std::abs(std::cos(x)) > 0.0001)
   {
      y = std::atan2(-m31, m33);
      z = std::atan2(-m12, m22);
   }
   else 
   {
      z = 0.0;
      y = std::atan2(m13, m11);
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;

   double sy = -m31;

   if (sy > 1.0) sy = 1.0;
   if (sy < -1.0) sy = -1.0;

   y = std::asin(sy);

   if (std::abs(std::cos(y)) > 0.0001)
   {
      x = std::atan2(m32, m33);
      z = std::atan2(m21, m11);
   }
   else
   {
      z = 0.0;
      x = std::atan2(-m23, m22);
   }
   return Vector3(x, y, z);
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
   double cx = std::cos(angleRad.x());
   double sx = std::sin(angleRad.x());

   double cy = std::cos(angleRad.y());
   double sy = std::sin(angleRad.y());

   double cz = std::cos(angleRad.z());
   double sz = std::sin(angleRad.z());

   Matrix3 Rx(
      1.0, 0.0, 0.0,
      0.0, cx, -sx,
      0.0, sx, cx
   );

   Matrix3 Ry(
      cy, 0.0, sy,
      0.0, 1.0, 0.0,
      -sy, 0.0, cy
   );

   Matrix3 Rz(
      cz, -sz, 0.0,
      sz, cz, 0.0,
      0.0, 0.0, 1.0
   );

   *this = Rx * Ry * Rz;
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
   double cx = std::cos(angleRad.x());
   double sx = std::sin(angleRad.x());

   double cy = std::cos(angleRad.y());
   double sy = std::sin(angleRad.y());

   double cz = std::cos(angleRad.z());
   double sz = std::sin(angleRad.z());

   Matrix3 Rx(
      1.0, 0.0, 0.0,
      0.0, cx, -sx,
      0.0, sx, cx
   );

   Matrix3 Ry(
      cy, 0.0, sy,
      0.0, 1.0, 0.0,
      -sy, 0.0, cy
   );

   Matrix3 Rz(
      cz, -sz, 0.0,
      sz, cz, 0.0,
      0.0, 0.0, 1.0
   );

   *this = Rx * Rz * Ry;
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
   double cx = std::cos(angleRad.x());
   double sx = std::sin(angleRad.x());

   double cy = std::cos(angleRad.y());
   double sy = std::sin(angleRad.y());

   double cz = std::cos(angleRad.z());
   double sz = std::sin(angleRad.z());

   Matrix3 Rx(
      1.0, 0.0, 0.0,
      0.0, cx, -sx,
      0.0, sx, cx
   );

   Matrix3 Ry(
      cy, 0.0, sy,
      0.0, 1.0, 0.0,
      -sy, 0.0, cy
   );

   Matrix3 Rz(
      cz, -sz, 0.0,
      sz, cz, 0.0,
      0.0, 0.0, 1.0
   );

   *this = Ry * Rx * Rz;
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   double cx = std::cos(angleRad.x());
   double sx = std::sin(angleRad.x());

   double cy = std::cos(angleRad.y());
   double sy = std::sin(angleRad.y());

   double cz = std::cos(angleRad.z());
   double sz = std::sin(angleRad.z());

   Matrix3 Rx(
      1.0, 0.0, 0.0,
      0.0, cx, -sx,
      0.0, sx, cx
   );

   Matrix3 Ry(
      cy, 0.0, sy,
      0.0, 1.0, 0.0,
      -sy, 0.0, cy
   );

   Matrix3 Rz(
      cz, -sz, 0.0,
      sz, cz, 0.0,
      0.0, 0.0, 1.0
   );

   *this = Ry * Rz * Rx;
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   double cx = std::cos(angleRad.x());
   double sx = std::sin(angleRad.x());

   double cy = std::cos(angleRad.y());
   double sy = std::sin(angleRad.y());

   double cz = std::cos(angleRad.z());
   double sz = std::sin(angleRad.z());

   Matrix3 Rx(
      1.0, 0.0, 0.0,
      0.0, cx, -sx,
      0.0, sx, cx
   );

   Matrix3 Ry(
      cy, 0.0, sy,
      0.0, 1.0, 0.0,
      -sy, 0.0, cy
   );

   Matrix3 Rz(
      cz, -sz, 0.0,
      sz, cz, 0.0,
      0.0, 0.0, 1.0
   );

   *this = Rz * Rx * Ry;
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   double cx = std::cos(angleRad.x());
   double sx = std::sin(angleRad.x());

   double cy = std::cos(angleRad.y());
   double sy = std::sin(angleRad.y());

   double cz = std::cos(angleRad.z());
   double sz = std::sin(angleRad.z());

   Matrix3 Rx(
      1.0, 0.0, 0.0,
      0.0, cx, -sx,
      0.0, sx, cx
   );

   Matrix3 Ry(
      cy, 0.0, sy,
      0.0, 1.0, 0.0,
      -sy, 0.0, cy
   );

   Matrix3 Rz(
      cz, -sz, 0.0,
      sz, cz, 0.0,
      0.0, 0.0, 1.0
   );

   *this = Rz * Ry * Rx;
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   double trace = m11 + m22 + m33;
   double cosTheta = (trace - 1.0) / 2.0;

   //clamp cosTheta
   if (cosTheta > 1.0) cosTheta = 1.0;
   if (cosTheta < -1.0) cosTheta = -1.0;

   angleRad = std::acos(cosTheta);

   const double epsilon = 0.0001;

   if (angleRad < epsilon)
   {
      axis = Vector3(1.0, 0.0, 0.0);
   }
   else if (std::abs(angleRad - M_PI) < epsilon)
   {
      if (m11 > m22 && m11 > m33)
      {
         double x = std::sqrt(std::max(0.0, (m11 + 1.0) / 2.0));
         double y = m12 / (2.0 * x);
         double z = m13 / (2.0 * x);
         axis = Vector3(x, y, z);
      }
      else if (m22 > m33)
      {
         double y = std::sqrt(std::max(0.0, (m22 + 1.0) / 2.0));
         double x = m12 / (2.0 * y);
         double z = m23 / (2.0 * y);
         axis = Vector3(x, y, z);
      }
      axis.normalize();
   }
   else
   {
      double x = m32 - m23;
      double y = m13 - m31;
      double z = m21 - m12;

      axis = Vector3(x, y, z);
      axis.normalize();
   }
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   double c = std::cos(angleRad);
   double s = std::sin(angleRad);
   double t = 1.0 - c;
   
   // Calculate vector magnitude to ensure it is normalized
   double mag = std::sqrt(axis.x() * axis.x() + axis.y() * axis.y() + axis.z() * axis.z());
   
   if (mag < 0.0001) {
       *this = Identity;
       return;
   }

   double x = axis.x() / mag;
   double y = axis.y() / mag;
   double z = axis.z() / mag;

   // Assign to the matrix's internal variables
   m11 = t * x * x + c;
   m12 = t * x * y - z * s;
   m13 = t * x * z + y * s;

   m21 = t * x * y + z * s;
   m22 = t * y * y + c;
   m23 = t * y * z - x * s;

   m31 = t * x * z - y * s;
   m32 = t * y * z + x * s;
   m33 = t * z * z + c;
}
}