#include "../include/scop.hpp"

float dot(Vector3 a, Vector3 b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross(Vector3 a, Vector3 b){
	Vector3 res;

	res.x = a.y * b.z - b.y * a.z;
	res.y = a.z * b.x - b.z * a.x;
	res.z = a.x * b.y - b.x * a.y;
	return res;
}

Vector3 normalize(Vector3 a){
	float lenght = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);

	if (lenght < 0)
		return Vector3(1,0,0);
	Vector3 res;

	res.x = a.x / lenght;
	res.y = a.y / lenght;
	res.z = a.z / lenght;
	return res;
}
