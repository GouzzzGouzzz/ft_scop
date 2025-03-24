#include "../include/quaternion.hpp"

Quaternion::Quaternion() {
	x = 0;
	y = 0;
	z = 0;
	w = 1;
};

Quaternion::Quaternion(float x, float y, float z, float w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::Quaternion(Vector3 axis, float angle) {
	angle = angle * M_PI / 180;
	x = axis.x * sin(angle / 2);
	y = axis.y * sin(angle / 2);
	z = axis.z * sin(angle / 2);
	w = cos(angle / 2);
};

Quaternion Quaternion::operator*(const Quaternion& q) const {
	return Quaternion(
		w * q.w - x * q.x - y * q.y - z * q.z,
		w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x,
		w * q.z + x * q.y - y * q.x + z * q.w);
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

//https://www.opengl-tutorial.org/assets/faq_quaternions/index.html#Q54
Matrix4 Quaternion::toMatrix() const{
	std::array<std::array<float, 4>, 4> matrix = {};
	Matrix4 matrix4;

	float xx = x * x;
	float xy = x * y;
	float xz = x * z;
	float xw = x * w;
	float yy = y * y;
	float yz = y * z;
	float yw = y * w;
	float zz = z * z;
	float zw = z * w;

	matrix[0][0] = 1 - 2 * (yy + zz);
	matrix[1][0] = 2 * (xy - zw);
	matrix[2][0] = 2 * (xz + yw);

	matrix[0][1] = 2 * (xy + zw);
	matrix[1][1] = 1 - 2 * (xx + zz);
	matrix[2][1] = 2 * (yz - xw);

	matrix[0][2] = 2 * (xz - yw);
	matrix[1][2] = 2 * (yz + xw);
	matrix[2][2] = 1 - 2 * (xx + yy);

	matrix[3][3] = 1;

	matrix4.setMatrix(matrix);
	return matrix4;
}

Quaternion::~Quaternion() {};

void Quaternion::print() {
	std::cout << "x: " << x << " y: " << y << " z: " << z << " w: " << w << std::endl;
}
