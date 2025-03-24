#include "../include/quaternion.hpp"

Quaternion::Quaternion() {
	x = 0;
	y = 0;
	z = 0;
	w = 1;
};

Quaternion::Quaternion(Vector3 axis, float angle) {
	angle = angle * M_PI / 180;
	x = axis.x * sin(angle / 2);
	y = axis.y * sin(angle / 2);
	z = axis.z * sin(angle / 2);
	w = cos(angle / 2);
};

Quaternion Quaternion::operator*(const Quaternion& q) const {
	return Quaternion(Vector3(
		w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x,
		w * q.z + x * q.y - y * q.x + z * q.w
	), w * q.w - x * q.x - y * q.y - z * q.z);
};

void Quaternion::normalize() {
	float magnitude = sqrt(x * x + y * y + z * z + w * w);
	if (magnitude > 0.0f) {
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
	}
}

Matrix4 Quaternion::toMatrix() const{
	std::array<std::array<float, 4>, 4> matrix = {};
	Matrix4 matrix4;
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	matrix[0][0] = 1.0f - 2.0f * (yy + zz);
	matrix[0][1] = 2.0f * (xy - wz);
	matrix[0][2] = 2.0f * (xz + wy);

	matrix[1][0] = 2.0f * (xy + wz);
	matrix[1][1] = 1.0f - 2.0f * (xx + zz);
	matrix[1][2] = 2.0f * (yz - wx);

	matrix[2][0] = 2.0f * (xz - wy);
	matrix[2][1] = 2.0f * (yz + wx);
	matrix[2][2] = 1.0f - 2.0f * (xx + yy);

	matrix[3][3] = 1.0f;
	matrix4.setMatrix(matrix);
	return matrix4;
}

Quaternion::~Quaternion() {};

void Quaternion::print() {
	std::cout << "x: " << x << " y: " << y << " z: " << z << " w: " << w << std::endl;
}
