#pragma once
#include <vector>
#include "../include/scop.hpp"

class Matrix4{
	public:
		Matrix4(float x, float y, float z, float w);
		//Identity matrix
		Matrix4(void);
		~Matrix4();
		std::vector<float> operator*(const std::vector<float>& vec) const;
		void Translate(float x, float y, float z);
		void Scale(float x, float y, float z);
		// void Rotate()
		void setValue(const std::vector<float> vec);
		void print() const;
	private:
		float m[4][4];
};
