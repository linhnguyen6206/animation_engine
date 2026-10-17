#include "atkmath/constants.h"
#include "atkmath/quaternion.h"
#include "atkmath/vector3.h"
#include "atkmath/test_utils.h"
#include <iostream>

using atkmath::Vector3;
using atkmath::Matrix3;
using atkmath::Quaternion;
using atkmath::Deg2Rad;
using atkmath::Rad2Deg;

void TestAxisAngle(const Quaternion& inputq, const Vector3& inputv, double inputRad)
{
    Quaternion q;
    Vector3 v; double angle;

    q.fromAxisAngle(inputv, inputRad);
    EXPECT_FLOAT_EQ(q.x(), inputq.x());
    EXPECT_FLOAT_EQ(q.y(), inputq.y());
    EXPECT_FLOAT_EQ(q.z(), inputq.z());
    EXPECT_FLOAT_EQ(q.w(), inputq.w());

    q.toAxisAngle(v, angle);
    EXPECT_EQ(v, inputv);
    EXPECT_FLOAT_EQ(angle, inputRad);
}

int main(int argc, char** argv)
{
    Quaternion q, q0, q1;
    Vector3 v; double angle = 0.0;
    Matrix3 m;

    std::cout << "45 Z " << std::endl;
    TestAxisAngle(Quaternion(0, 0, 0.382683, 0.92388), Vector3(0,0,1), M_PI/4);

    std::cout << "45 Y " << std::endl;
    TestAxisAngle(Quaternion(0, 0.382683, 0, 0.92388), Vector3(0,1,0), M_PI/4);

    std::cout << "45 X " << std::endl;
    TestAxisAngle(Quaternion(0.382683, 0, 0, 0.92388), Vector3(1,0,0), M_PI/4);

    std::cout << "identity " << std::endl;
    q = Quaternion(0,0,0,1);
    q.toAxisAngle(v, angle);
    if (v != Vector3(1,0,0) && v != Vector3(0,1,0) && v != Vector3(0,0,1))
    {
      assert("TEST FAIL: Invalid axis");
    }
    EXPECT_FLOAT_EQ(angle, 0.0);

    q0 = Quaternion(Vector3(0,0,1), -120 * Deg2Rad);
    q1 = Quaternion(Vector3(0,0,1), 120 * Deg2Rad);
    //std::cout << "q0 " << q0 << std::endl;
    //std::cout << "q1 " << q1 << std::endl;

    std::cout << "slerp #1 " << std::endl;
    q = Quaternion::Slerp(q0, q1, 0);
    EXPECT_EQ(q, q0);

    std::cout << "slerp #2 " << std::endl;
    q = Quaternion::Slerp(q0, q1, 0.5);
    EXPECT_EQ(q, Quaternion(0,0,-1,0));

    std::cout << "slerp #3 " << std::endl;
    q = Quaternion::Slerp(q0, q1, 1.0);
    EXPECT_EQ(q, q1);

    std::cout << "slerp #4 " << std::endl;
    q0 = Quaternion(Vector3(0,0,1), 0 * Deg2Rad);
    q1 = Quaternion(Vector3(0,0,1), 180 * Deg2Rad);
    q = Quaternion::Slerp(q0, q1, 0.5);
    EXPECT_EQ(q, Quaternion(0, 0, 0.707107, 0.707107));

    std::cout << "slerp #5 " << std::endl;
    q0 = Quaternion(Vector3(0,0,1), 0 * Deg2Rad);
    q1 = Quaternion(Vector3(0,0,1), 0 * Deg2Rad);
    q = Quaternion::Slerp(q0, q1, 0.5);
    EXPECT_EQ(q, Quaternion(0, 0, 0, 1));

    std::cout << "45 Z Matrix" << std::endl;
    m.fromEulerAnglesYXZ(Vector3(0,0,M_PI/4));
    q.fromMatrix(m);
    EXPECT_EQ(Quaternion(0, 0, 0.382683, 0.92388), q);
    m = q.toMatrix();
    std::cout << m << std::endl;
    EXPECT_EQ(Matrix3(0.707107, -0.707107, 0,
                      0.707107, 0.707107, 0,
                      0, 0, 1), m);

    std::cout << "45 Y Matrix" << std::endl;
    m.fromEulerAnglesYXZ(Vector3(0,M_PI/4,0));
    q.fromMatrix(m);
    EXPECT_EQ(Quaternion(0, 0.382683, 0, 0.92388), q);
    m = q.toMatrix();
    std::cout << m << std::endl;
    EXPECT_EQ(Matrix3(0.707107, 0, 0.707107,
                      0, 1, 0,
                     -0.707107, 0, 0.707107), m);

    std::cout << "45 X Matrix" << std::endl;
    m.fromEulerAnglesYXZ(Vector3(M_PI/4,0,0));
    q.fromMatrix(m);
    EXPECT_EQ(Quaternion(0.382683, 0, 0, 0.92388), q);
    m = q.toMatrix();
    std::cout << m << std::endl;
    EXPECT_EQ(Matrix3(1, 0, 0,
                      0, 0.707107, -0.707107,
                      0, 0.707107, 0.707107), m);

    return 0;
}
