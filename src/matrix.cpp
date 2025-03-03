#include "../include/matrix4.hpp"

Matrix4::Matrix4(float x, float y, float z, float w) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = 0;
		}
	}
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	m[3][3] = w;
}

Matrix4::Matrix4(void){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = 0;
		}
	}
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;
}

Matrix4::~Matrix4() {}

std::vector<float> Matrix4::operator*(const std::vector<float>& vec) const
{
	if (vec.size() != 4){
		std::cerr << "Matrix * : vector size must be 4" << std::endl;
		return vec;
	}
	std::vector<float> res(4, 0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res[i] += m[i][j] * vec[j];
		}
	}
	return res;
}

void Matrix4::Translate(float x, float y, float z) {
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
}

void Matrix4::Scale(float x, float y, float z) {
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
}



void Matrix4::setValue(const std::vector<float> vec) {
	if (vec.size() != 16) {
		std::cerr << "Matrix setValue : vector size must be 16" << std::endl;
		return;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = vec[i * 4 + j];
		}
	}
}

void Matrix4::print() const {
	for (int i = 0; i < 4; i++) {
		std::cout << "[ ";
		for (int j = 0; j < 4; j++) {
			std::cout << m[i][j] << " ";
		}
		std::cout <<" ]" << std::endl;
	}
}
