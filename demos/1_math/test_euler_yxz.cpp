#include "atkmath/constants.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"
#include "atkmath/test_utils.h"
#include <iostream>

using atkmath::Matrix3;
using atkmath::Vector3;
using atkmath::Deg2Rad;
#include "test_euler.h"

int main(int argc, char** argv)
{
    RUN_TEST(TestIdentity())
    RUN_TEST(TestEulerToMatrix_YXZ());

    return 0;
}
