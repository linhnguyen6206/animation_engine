#include "atkmath/constants.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"
#include "atkmath/test_utils.h"
#include <math.h>
#include <iostream>
#include <sstream>

using atkmath::Vector3;
using atkmath::Deg2Rad;

int main(int argc, char** argv)
{
    double d;

    std::cout << "test Vector3(double, double, double)\n";
    Vector3 v(1.0, 2.0, 3.0);
    EXPECT_EQ(v.x(), 1.0);
    EXPECT_EQ(v.y(), 2.0);
    EXPECT_EQ(v.z(), 3.0);

    std::cout << "test Vector3(const Vector3&)\n";
    Vector3 a = v;
    EXPECT_EQ(a.x(), 1.0);
    EXPECT_EQ(a.y(), 2.0);
    EXPECT_EQ(a.z(), 3.0);

    std::cout << "test Vector3()\n";
    Vector3 b;
    EXPECT_EQ(b.x(), 0.0);
    EXPECT_EQ(b.y(), 0.0);
    EXPECT_EQ(b.z(), 0.0);

    std::cout << "test operator=(const Vector3&)\n";
    b = a;
    EXPECT_EQ(b.x(), 1.0);
    EXPECT_EQ(b.y(), 2.0);
    EXPECT_EQ(b.z(), 3.0);

    std::cout << "test operator+=(const Vector3&)\n";
    b += Vector3(1.0, 1.0, 1.0);
    EXPECT_EQ(b.x(), 2.0);
    EXPECT_EQ(b.y(), 3.0);
    EXPECT_EQ(b.z(), 4.0);

    std::cout << "test operator-=(const Vector3&)\n";
    b -= Vector3(1.0, 1.0, 1.0);
    EXPECT_EQ(b.x(), 1.0);
    EXPECT_EQ(b.y(), 2.0);
    EXPECT_EQ(b.z(), 3.0);

    std::cout << "test operator*=(double)\n";
    b *= 2.0;
    EXPECT_EQ(b.x(), 2.0);
    EXPECT_EQ(b.y(), 4.0);
    EXPECT_EQ(b.z(), 6.0);

    std::cout << "test operator/=(double)\n";
    b /= 2.0;
    EXPECT_EQ(b.x(), 1.0);
    EXPECT_EQ(b.y(), 2.0);
    EXPECT_EQ(b.z(), 3.0);

    std::cout << "test sqrLength\n";
    d = b.sqrLength();
    EXPECT_EQ(d, 14.0);

    std::cout << "test length\n";
    d = b.length();
    EXPECT_EQ(d, sqrt(14.0));

    std::cout << "test normalize zero\n";
    Vector3 zero(0,0,0);
    zero.normalize();
    EXPECT_EQ(zero.x(), 0.0);
    EXPECT_EQ(zero.y(), 0.0);
    EXPECT_EQ(zero.z(), 0.0);

    std::cout << "test normalized zero\n";
    Vector3 test = zero.normalized();
    EXPECT_EQ(test.x(), 0.0);
    EXPECT_EQ(test.y(), 0.0);
    EXPECT_EQ(test.z(), 0.0);

    std::cout << "test normalized non-zero\n";
    Vector3 c = b.normalized();
    EXPECT_EQ(c.x(), 1.0/sqrt(14));
    EXPECT_EQ(c.y(), 2.0/sqrt(14));
    EXPECT_EQ(c.z(), 3.0/sqrt(14));

    std::cout << "test normalize non-zero\n";
    b.normalize();
    EXPECT_EQ(b.x(), 1.0/sqrt(14));
    EXPECT_EQ(b.y(), 2.0/sqrt(14));
    EXPECT_EQ(b.z(), 3.0/sqrt(14));

    std::cout << "test cross\n";
    Vector3 x(1,0,0);
    Vector3 y(0,1,0);
    Vector3 z = Vector3::Cross(x, y);
    EXPECT_EQ(z.x(), 0.0);
    EXPECT_EQ(z.y(), 0.0);
    EXPECT_EQ(z.z(), 1.0);

    z = Vector3::Cross(y, x);
    EXPECT_EQ(z.x(), 0.0);
    EXPECT_EQ(z.y(), 0.0);
    EXPECT_EQ(z.z(), -1.0);

    std::cout << "test -v\n";
    b = -Vector3(2, 2, 2);
    EXPECT_EQ(b.x(), -2.0);
    EXPECT_EQ(b.y(), -2.0);
    EXPECT_EQ(b.z(), -2.0);

    std::cout << "test a-b\n";
    b = Vector3(2, 2, 2) - Vector3(1, 2, 3);
    EXPECT_EQ(b.x(), 1.0);
    EXPECT_EQ(b.y(), 0.0);
    EXPECT_EQ(b.z(), -1.0);

    std::cout << "test a+b\n";
    b = Vector3(2, 2, 2) + Vector3(1, 2, 3);
    EXPECT_EQ(b.x(), 3.0);
    EXPECT_EQ(b.y(), 4.0);
    EXPECT_EQ(b.z(), 5.0);

    std::cout << "test a*d\n";
    b = Vector3(2, 2, 2)*2.0;
    EXPECT_EQ(b.x(), 4.0);
    EXPECT_EQ(b.y(), 4.0);
    EXPECT_EQ(b.z(), 4.0);

    std::cout << "test d*a\n";
    b = 2.0*Vector3(2, 2, 2);
    EXPECT_EQ(b.x(), 4.0);
    EXPECT_EQ(b.y(), 4.0);
    EXPECT_EQ(b.z(), 4.0);

    std::cout << "test a/2\n";
    b = Vector3(2, 2, 2)/2.0;
    EXPECT_EQ(b.x(), 1.0);
    EXPECT_EQ(b.y(), 1.0);
    EXPECT_EQ(b.z(), 1.0);
    
    std::cout << "test a == b\n";
    bool eq = (b == b);
    assert(eq == true);

    std::cout << "test a != b\n";
    eq = (b == a);
    assert(eq == false);

    std::cout << "test Dot\n";
    double dot = Vector3::Dot(x, y);
    assert(dot == 0);
    
    std::cout << "test output stream - " << b << std::endl;

    std::cout << "test input stream - " << b << std::endl;
    std::stringstream ss("10.0 5.0 -5.0");
    ss >> b;
    EXPECT_EQ(b.x(), 10.0);
    EXPECT_EQ(b.y(), 5.0);
    EXPECT_EQ(b.z(), -5.0);

    std::cout << "test lerp\n";
    b = Vector3::Lerp(Vector3(0,0,0), Vector3(1,1,1), 0.5);
    EXPECT_EQ(b.x(), 0.5);
    EXPECT_EQ(b.y(), 0.5);
    EXPECT_EQ(b.z(), 0.5);

    std::cout << "test distance\n";
    d = Vector3::Distance(Vector3(0,0,0), Vector3(1,1,1));
    EXPECT_EQ(d, sqrt(3));

    d = Vector3::DistanceSqr(Vector3(0,0,0), Vector3(1,1,1));
    EXPECT_EQ(d, 3.0);
    return 0;
}
