#include "atkmath/vector3.h"
#include <algorithm>
#include <cmath>

namespace atkmath {
const Vector3 Vector3::AxisX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::AxisY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::AxisZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);

using namespace std;

Vector3::Vector3() 
{
    mX = 0; mY = 0; mZ = 0; 
}

Vector3::Vector3(double x, double y, double z)
{ 
    mX = x;
    mY = y;
    mZ = z;
}

Vector3::Vector3(const Vector3& v)
{ 
    mX = v.mX;
    mY = v.mY;
    mZ = v.mZ;
}

// ASSIGNMENT OPERATORS

Vector3& Vector3::operator = (const Vector3& v)
{ 
    if (this != &v)
    {
        mX = v.mX;
        mY = v.mY;
        mZ = v.mZ;
    }
    return *this; 
}

Vector3& Vector3::operator += ( const Vector3& v )
{ 
    mX += v.mX;
    mY += v.mY;
    mZ += v.mZ;
    return *this; 
}

Vector3& Vector3::operator -= ( const Vector3& v )
{ 
    mX -= v.mX;
    mY -= v.mY;
    mZ -= v.mZ;
    return *this; 
}

Vector3& Vector3::operator *= ( double d )
{ 
    mX *= d;
    mY *= d;
    mZ *= d;
    return *this; 
}

Vector3& Vector3::operator /= ( double d )
{ 
    mX /= d;
    mY /= d;
    mZ /= d;
    return *this; 
}

double& Vector3::operator [] ( int i) {
    assert(! (i < VX || i > VZ));
    return mV[i]; 
}

double Vector3::operator [] ( int i) const {
    assert(! (i < VX || i > VZ));
    return mV[i];  
}

double Vector3::x() const
{
	return mX;
}

double Vector3::y() const
{
	return mY;
}

double Vector3::z() const
{
	return mZ;
}

// SPECIAL FUNCTIONS
double Vector3::length() const
{  
    return std::sqrt(mX * mX + mY * mY + mZ * mZ);
}

double Vector3::sqrLength() const
{  
    return (mX * mX + mY * mY + mZ * mZ);
}

Vector3 Vector3::normalized() const 
{
    double len = length();
    if (len > 0.0)
    {
        return Vector3(mX / len, mY / len, mZ / len);
    }
    return Vector3(0.0, 0.0, 0.0);
}

void Vector3::normalize() 
{ 
    double len = length();
    if (len > 0.0)
    {
        mX /= len;
        mY /= len;
        mZ /= len;
    }
}

Vector3 Vector3::Cross(const Vector3 &left, const Vector3& right)
{
    return Vector3(
        left.mY * right.mZ - left.mZ * right.mY,
        left.mZ * right.mX - left.mX * right.mZ,
        left.mX * right.mY - left.mY * right.mX
    );
}

// FRIENDS
Vector3 operator - (const Vector3& a)
{  
    return Vector3(-a.x(), -a.y(), -a.z()); 
}                       

Vector3 operator + (const Vector3& a, const Vector3& b)
{ 
    return Vector3(a.x()+ b.x(), a.y() + b.y(), a.z() + b.z()); 
}

Vector3 operator - (const Vector3& a, const Vector3& b)
{ 
    return Vector3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z()); 
}

Vector3 operator * (const Vector3& a, double d)
{ 
    return Vector3(a.x() * d, a.y() * d, a.z() * d); 
}

Vector3 operator * (double d, const Vector3& a)
{
    return a * d; 
}

double operator * (const Vector3& a, const Vector3& b)
{ 
    return (a.x() * b.x()) + (a.y() * b.y()) + (a.z() * b.z());
}

Vector3 operator / (const Vector3& a, double d)
{ 
    return Vector3(a.x() / d, + a.y() / d, a.z() / d); 
}


int operator == (const Vector3& a, const Vector3& b)
{ 
    float eps = 0.001f; // low precision equality

    return (std::abs(a.x() - b.x()) < eps) &&
            (std::abs(a.y() - b.y()) < eps) &&
            (std::abs(a.z() - b.z()) < eps);
}

int operator != (const Vector3& a, const Vector3& b)
{ 
    return !(a == b);
}

double Vector3::Dot(const Vector3& a, const Vector3& b)
{
    return (a.x() * b.x() + a.y() * b.y() + a.z() * b.z());
}

std::istream& operator>>(std::istream& s, Vector3& v)
{
    double x, y, z;
    s >> x >> y >> z;
    v = Vector3(x, y, z);
    return s; 
}

std::ostream& operator<<(std::ostream& s, const Vector3& v)
{
    s << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
    return s;
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
    return Vector3(
        a.x() + (b.x() - a.x()) * t,
        a.y() + (b.y() - a.y()) * t,
        a.z() + (b.z() - a.z()) * t
    ); 
}

double Vector3::DistanceSqr(const Vector3& a, const Vector3& b)
{
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    double dz = a.z() - b.z();
    return (dx * dx) + (dy * dy) + (dz * dz);
}

double Vector3::Distance(const Vector3& a, const Vector3& b)
{
    return std::sqrt(DistanceSqr(a, b));
}
}
