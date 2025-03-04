#include "../include/scop.hpp"

float dot(Vector3 a, Vector3 b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross(Vector3 a, Vector3 b){
	Vector3 res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return res;
}

Vector3 normalize(Vector3 a){
	float lenght = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);

	Vector3 res;

	res.x = a.x / lenght;
	res.y = a.y / lenght;
	res.z = a.z / lenght;
	return res;
}
