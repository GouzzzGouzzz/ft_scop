#pragma once

//Glfw headers, used for the iwindow and the event handling
#include <GLFW/glfw3.h>

//Standard includes
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>

//My OpenGL headers to load the functions
#include "glFunction.hpp"

//My Custom headers
#include "structs.h"
#include "moreMath.hpp"
#include "matrix4.hpp"

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

