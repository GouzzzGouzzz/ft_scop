#pragma once

//Glfw headers, used for the iwindow and the event handling
#include <GLFW/glfw3.h>

//My OpenGL headers to load the functions
#include "glFunction.hpp"

//My Custom headers
#include "matrix4.hpp"

//Standard includes
#include <fstream>
#include <iostream>
#include <vector>

typedef struct s_face {
	int v1;
	int v2;
	int v3;
	int v4;
} t_face;

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

