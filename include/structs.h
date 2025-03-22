#pragma once

typedef struct s_face {
	int v1;
	int v2;
	int v3;
	int v4;

	s_face() : v1(0), v2(0), v3(0), v4(0) {};
} t_face;

typedef struct Vector3{
	float x;
	float y;
	float z;

	Vector3(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val) {};
	Vector3(int x_val, int y_val, int z_val) : x((float)x_val), y((float)y_val), z((float)z_val) {};
	Vector3() : x(0), y(0), z(0) {};
} Vector3;

typedef struct t_uv {
	float u;
	float v;

	t_uv() : u(0), v(0) {};
	t_uv(float u_val, float v_val) : u(u_val), v(v_val) {};
} t_uv;
