#pragma once
#include "../include/moreMath.hpp"

//Use row-major matrix for calculations, should call convertToColumnMajor before giving it to OpenGL
class Matrix4{
	public:
		Matrix4(float x, float y, float z, float w);
		Matrix4(void);
		~Matrix4();
		//MOST IMPORTANT FUNCTION
		void convertToColumnMajor();
		Matrix4 operator*(const Matrix4& mat) const;
		std::vector<float> operator*(const std::vector<float>& vec) const;
		void identity();
		void translate(float x, float y, float z);
		void scale(float x, float y, float z);
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);
		void view(Vector3 eye, Vector3 center, Vector3 up);
		void perspective(const float fovy, const float aspect, const float zNear, const float zFar);
		void setValue(const std::array<float, 16> vec);
		std::array<std::array<float, 4>, 4> getMatrix() const;
		void print() const;
	private:
		std::array<std::array<float, 4>, 4> m;
};
