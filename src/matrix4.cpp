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

Matrix4 Matrix4::operator*(const Matrix4& mat) const
{
	Matrix4 res;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			res.m[i][j] = 0;
			for(int k = 0; k < 4; k++){
				res.m[i][j] += m[i][k] * mat.m[k][j];
			}
		}
	}

	return res;
}

void Matrix4::translate(float x, float y, float z) {
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
}

void Matrix4::scale(float x, float y, float z) {
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
}

//Use degree as input
void Matrix4::rotateX(float angle){
	angle = angle * M_PI / 180;
	m[0][0] = 1;
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
	m[3][3] = 1;
}

//Use degree as input
void Matrix4::rotateY(float angle){
	angle = angle * M_PI / 180;
	m[0][0] = cos(angle);
	m[0][2] = sin(angle);
	m[1][1] = 1;
	m[2][0] = -sin(angle);
	m[2][2] = cos(angle);
	m[3][3] = 1;

}

//Use degree as input
void Matrix4::rotateZ(float angle){
	angle = angle * M_PI / 180;
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
	m[2][2] = 1;
	m[3][3] = 1;
}

//Set the matrix to identity (1,1,1,1)
void Matrix4::identity(){
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

//Exaclty the same as glm::LookAt
//Used to calculate the view matrix
//https://stackoverflow.com/questions/19740463/lookat-function-im-going-crazy/19740748
void Matrix4::view(Vector3 eye, Vector3 center, Vector3 up){
	Vector3 lookDirection;
	Vector3 right;
	Vector3 pre_f;
	pre_f.x = center.x - eye.x;
	pre_f.y = center.y - eye.y;
	pre_f.z = center.z - eye.z;

	lookDirection  = normalize(pre_f);
	up = normalize(up);
	right = normalize(cross(lookDirection, up));
	up = cross(right, lookDirection);

	m[0][0] = right.x;
	m[1][0] = right.y;
	m[2][0] = right.z;
	m[0][1] = up.x;
	m[1][1] = up.y;
	m[2][1] = up.z;
	m[0][2] =-lookDirection.x;
	m[1][2] =-lookDirection.y;
	m[2][2] =-lookDirection.z;
	m[3][0] =-dot(right, eye);
	m[3][1] =-dot(up, eye);
	m[3][2] = dot(lookDirection, eye);
}

//Set the matrix value with a vector of size 16
void Matrix4::setValue(const std::array<float, 16> vec) {
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
