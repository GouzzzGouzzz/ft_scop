#pragma once

#include "structs.h"
#include "standard.hpp"
#include "moreMath.hpp"


//Use row-major matrix
class Matrix4{
	public:
		Matrix4(float x, float y, float z, float w);
		Matrix4(void);
		~Matrix4();
		void convertToColumnMajor();
		Matrix4 operator*(const Matrix4& mat) const;
		std::vector<float> operator*(const std::vector<float>& vec) const;
		void identity();
		void translate(float x, float y, float z);
		void scale(float x, float y, float z);
		void view(Vector3 eye, Vector3 center, Vector3 up);
		void perspective(const float fovy, const float aspect, const float zNear, const float zFar);
		std::array<std::array<float, 4>, 4> getMatrix() const;
		void setMatrix(const std::array<std::array<float, 4>, 4> mat);
		void print() const;
	private:
		std::array<std::array<float, 4>, 4> m;
};
