#pragma once
#include <vector>
#include "../include/scop.hpp"
#include <math.h>

class Matrix4{
	public:
		Matrix4(float x, float y, float z, float w);
		//Identity matrix
		Matrix4(void);
		~Matrix4();
		Matrix4 operator*(const Matrix4& mat) const;
		std::vector<float> operator*(const std::vector<float>& vec) const;
		void Identity();
		void Translate(float x, float y, float z);
		void Scale(float x, float y, float z);
		void RotateX(float angle);
		void RotateY(float angle);
		void RotateZ(float angle);
		void setValue(const std::vector<float> vec);
		void print() const;
	private:
		float m[4][4];
};
