#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   return Vector3();
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