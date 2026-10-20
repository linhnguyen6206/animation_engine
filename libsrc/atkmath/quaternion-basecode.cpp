#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	double dot = q0.w() * q1.w() + q0.x() * q1.x() + q0.y() * q1.y() + q0.z() * q1.z();

	Quaternion q1_adj = q1;
	if (dot < 0.0) {
		q1_adj = Quaternion(-q1.x(), -q1.y(), -q1.z(), -q1.w());
		dot = -dot;
	}

	const double DOT_THRESHOLD = 0.995;
	if (dot > DOT_THRESHOLD) {
		double w = q0.w() + t * (q1_adj.w() - q0.w());
		double x = q0.x() + t * (q1_adj.x() - q0.x());
		double y = q0.y() + t * (q1_adj.y() - q0.y());
		double z = q0.z() + t * (q1_adj.z() - q0.z());

		double mag = std::sqrt(w*w + x*x + y*y + z*z);
		return Quaternion(x/mag, y/mag, z/mag, w/mag);
	}
	double theta_0 = std::acos(dot);
	double theta = theta_0 * t;

	double sin_theta_0 = std::sin(theta_0);
	double sin_theta = std::sin(theta);

	double s0 = std::cos(theta) - dot * sin_theta / sin_theta_0;
	double s1 = sin_theta / sin_theta_0;

	return Quaternion(
		s0 * q0.x() + s1 * q1_adj.x(),
		s0 * q0.y() + s1 * q1_adj.y(),
		s0 * q0.z() + s1 * q1_adj.z(),
		s0 * q0.w() + s1 * q1_adj.w()
	);
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	// Clamp w to [-1.0, 1.0]
	double w_clamped = w();
	if (w_clamped > 1.0) w_clamped = 1.0;
	else if (w_clamped < -1.0) w_clamped = -1.0;

	// Calculate the rotation angle
	angleRad = 2.0 * std::acos(w_clamped);

	//Calculate the divisor for the axis components
	//Since q = (cos(theta/2), axis * sin(theta/2)) s is sin(theta/2)
	double s = std::sqrt(1.0 - w_clamped * w_clamped);

	if (s < 0.0001) {
		// if s is close to zero, there is no rotation so an arbitrary unit vector is set to avoid division
		// by zero
		axis = Vector3(1.0, 0.0, 0.0);
	} else {
		axis = Vector3(x() / s, y() / s, z() / s);
	}
}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	double halfAngle = angleRad * 0.5;

	double s = std::sin(halfAngle);
	double c = std::cos(halfAngle);
	// Ensure the axis vector is normalized
	double mag = std::sqrt(axis.x() * axis.x() + axis.y() * axis.y() + axis.z() * axis.z());

	// Assign the components
	if (mag > 0.0001) {
		mX = (axis.x() / mag) * s;
		mY = (axis.y() / mag) * s;
		mZ = (axis.z() / mag) * s;
		mW = c;
	}
	else {
		mX = 0.0;
		mY= 0.0;
		mZ = 0.0;
		mW = c;
	}
}

Matrix3 Quaternion::toMatrix () const
{
	double xx = x() * x();
	double yy = y() * y();
	double zz = z() * z();

	double xy = x() * y();
	double yz = y() * z();
	double xz = x() * z();

	double wx = w() * x();
	double wy = w() * y();
	double wz = w() * z();


	return Matrix3(
		1.0 - 2.0 * (yy + zz), 2.0 * (xy - wz),       2.0 * (xz + wy),
		2.0 * (xy + wz),       1.0 - 2.0 * (xx + zz), 2.0 * (yz - wx),
		2.0 * (xz - wy),       2.0 * (yz + wx),       1.0 - 2.0 * (xx + yy)
	);
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	double m00 = rot[0][0];
	double m01 = rot[0][1];
	double m02 = rot[0][2];
	double m10 = rot[1][0];
	double m11 = rot[1][1];
	double m12 = rot[1][2];
	double m20 = rot[2][0];
	double m21 = rot[2][1];
	double m22 = rot[2][2];

	double qw, qx, qy, qz;
	double trace = m00 + m11 + m22;
	if (trace > 0.0) {
		double S = 2.0 * std::sqrt(trace + 1.0);
		qw = 0.25 * S;
		qx = (m21 - m12) / S;
		qy = (m02 - m20) / S;
		qz = (m10 - m01) / S;
	}
	else {
		if (m00 > m11 && m00 > m22) {
			double S = 2.0 * std::sqrt(1.0 + m00 - m11 - m22);
			qw = (m21 - m12) / S;
			qx = 0.25 * S;
			qy = (m01 + m10) / S;
			qz = (m02 + m20) / S;
		}
		else if (m11 > m22) {
			double S = 2.0 * std::sqrt(1.0 + m11 - m00 - m22);
			qw = (m02 - m20) / S;
			qx = (m01 + m10) / S;
			qy = 0.25 * S;
			qz = (m12 + m21) / S;
		}
		else {
			double S = 2.0 * std::sqrt(1.0 + m22 - m00 - m11);
			qw = (m10 - m01) / S;
			qx = (m02 + m20) / S;
			qy = (m12 + m21) / S;
			qz = 0.25 * S;
		}
	}
	mX = qx;
	mY = qy;
	mZ = qz;
	mW = qw;
}
}