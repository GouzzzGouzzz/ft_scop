#pragma once

#include "matrix4.hpp"

class Matrix4;

class Quaternion {
	public:
		Quaternion();
		Quaternion(Vector3 axis, float angle);
		Quaternion operator*(const Quaternion& q) const;
		Matrix4 toMatrix() const;
		void normalize();
		void print();
		~Quaternion();
	private:
		float x, y, z, w;

};
