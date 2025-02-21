#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <fstream>

typedef struct s_vertex {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} t_vertex;

typedef struct s_face {
	int v1;
	int v2;
	int v3;
	int v4;
} t_face;
