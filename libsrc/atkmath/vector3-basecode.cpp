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
    // todo
}

Vector3::Vector3(const Vector3& v)
{ 
    // todo
}

// ASSIGNMENT OPERATORS

Vector3& Vector3::operator = (const Vector3& v)
{ 
    // todo
    return *this; 
}

Vector3& Vector3::operator += ( const Vector3& v )
{ 
    // todo
    return *this; 
}

Vector3& Vector3::operator -= ( const Vector3& v )
{ 
    // todo
    return *this; 
}

Vector3& Vector3::operator *= ( double d )
{ 
    // todo
    return *this; 
}

Vector3& Vector3::operator /= ( double d )
{ 
    // todo
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
    // todo
    return 0.0; 
}

double Vector3::sqrLength() const
{  
    // todo
    return 0.0; 
}

Vector3 Vector3::normalized() const 
{
    // todo
    return Vector3();
}

void Vector3::normalize() 
{ 
    // todo
    
}

Vector3 Vector3::Cross(const Vector3 &left, const Vector3& right)
{
    // todo
    return Vector3();
}

// FRIENDS
Vector3 operator - (const Vector3& a)
{  
    // todo
    return Vector3(); 
}

Vector3 operator + (const Vector3& a, const Vector3& b)
{ 
    // todo
    return Vector3(); 
}

Vector3 operator - (const Vector3& a, const Vector3& b)
{ 
    // todo
    return Vector3(); 
}

Vector3 operator * (const Vector3& a, double d)
{ 
    // todo
    return Vector3(); 
}

Vector3 operator * (double d, const Vector3& a)
{ 
    // todo
    return a; 
}

Vector3 operator / (const Vector3& a, double d)
{ 
    // todo
    return Vector3(); // todo
}


int operator == (const Vector3& a, const Vector3& b)
{ 
    //float eps = 0.001f; // low precision equality
    return 0;  // todo
}

int operator != (const Vector3& a, const Vector3& b)
{ 
    return false; //todo
}

double Vector3::Dot(const Vector3& a, const Vector3& b)
{
    return 0; //todo
}

std::istream& operator>>(std::istream& s, Vector3& v)
{
    return s; // todo
}

std::ostream& operator<<(std::ostream& s, const Vector3& v)
{
    // todo
    return s;
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
    return Vector3(); // todo (next assignment)
}

double Vector3::Distance(const Vector3& a, const Vector3& b)
{
    return 0; // todo 
}

double Vector3::DistanceSqr(const Vector3& a, const Vector3& b)
{
    return 0; // todo
}
}
