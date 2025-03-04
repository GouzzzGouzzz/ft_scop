#pragma once
#include "../include/moreMath.hpp"

class Matrix4{
	public:
		Matrix4(float x, float y, float z, float w);
		//Identity matrix
		Matrix4(void);
		~Matrix4();
		Matrix4 operator*(const Matrix4& mat) const;
		std::vector<float> operator*(const std::vector<float>& vec) const;
		void identity();
		void translate(float x, float y, float z);
		void scale(float x, float y, float z);
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);
		void view(Vector3 eye, Vector3 center, Vector3 up);
		void projection();
		void setValue(const std::array<float, 16> vec);
		void print() const;
	private:
		float m[4][4];
};
