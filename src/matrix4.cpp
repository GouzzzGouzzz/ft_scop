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
				res.m[i][j] += m[k][j] * mat.m[i][k];
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

//use degree as input in vector3(x,y,z)
void Matrix4::rotate(Vector3 angles)
{
	float angleX = angles.x * M_PI / 180;
	float angleY = angles.y * M_PI / 180;
	float angleZ = angles.z * M_PI / 180;

	Matrix4 rotX, rotY, rotZ;

	//rota x
	rotX.m[0][0] = 1;
	rotX.m[1][1] = cos(angleX);
	rotX.m[1][2] = -sin(angleX);
	rotX.m[2][1] = sin(angleX);
	rotX.m[2][2] = cos(angleX);
	rotX.m[3][3] = 1;
	//rota y
	rotY.m[0][0] = cos(angleY);
	rotY.m[0][2] = sin(angleY);
	rotY.m[1][1] = 1;
	rotY.m[2][0] = -sin(angleY);
	rotY.m[2][2] = cos(angleY);
	rotY.m[3][3] = 1;

	//rota z
	rotZ.m[0][0] = cos(angleZ);
	rotZ.m[0][1] = -sin(angleZ);
	rotZ.m[1][0] = sin(angleZ);
	rotZ.m[1][1] = cos(angleZ);
	rotZ.m[2][2] = 1;
	rotZ.m[3][3] = 1;

	*this = rotX * rotY * rotZ;
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
	Vector3 centerMinusEye(center.x - eye.x, center.y - eye.y, center.z - eye.z);
	const Vector3 f(normalize(centerMinusEye));
	const Vector3 s(normalize(cross(f, up)));
	const Vector3 u(cross(s, f));

	m[0][0] = s.x;
	m[1][0] = s.y;
	m[2][0] = s.z;
	m[0][1] = u.x;
	m[1][1] = u.y;
	m[2][1] = u.z;
	m[0][2] =-f.x;
	m[1][2] =-f.y;
	m[2][2] =-f.z;
	m[3][0] =-dot(s, eye);
	m[3][1] =-dot(u, eye);
	m[3][2] = dot(f, eye);
	m[3][3] = 1;
}


// https://github.com/g-truc/glm/blob/0.9.5/glm/gtc/matrix_transform.inl#L207-L229
//Use degree as input for fovy
void Matrix4::perspective(const float fovy, const float aspect, const float zNear, const float zFar)
{
	if (aspect == 0 || zFar == zNear)
		return ;
	const float rad = fovy * M_PI / 180;
	const float tanHalfFovy = tan(rad / 2);

	m[0][0] = 1 / (aspect * tanHalfFovy);
	m[1][1] = 1 / (tanHalfFovy);
	m[2][2] = - (zFar + zNear) / (zFar - zNear);
	m[2][3] = - 1;
	m[3][2] = - (2 * zFar * zNear) / (zFar - zNear);
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

//!!!!!!!!!!
//ALWAYS CALL THIS FUNCTION BEFORE GIVING IT TO OPENGL
//!!!!!!!!!!
void Matrix4::convertToColumnMajor()
{
	std::array<std::array<float, 4>, 4> res;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++){
			res[j][i] = m[i][j];
		}
	}
	m = res;
}

std::array<std::array<float, 4>, 4> Matrix4::getMatrix() const{
	return m;
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
