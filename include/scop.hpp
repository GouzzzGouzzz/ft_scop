#pragma once

//Glfw headers, used for the iwindow and the event handling
#include <GLFW/glfw3.h>

//Standard includes
#include "standard.hpp"

//My OpenGL headers to load the functions (like GLEW)
#include "glFunction.hpp"

//Include defines
#include "defines.hpp"

//My Custom headers
#include "structs.h"
#include "moreMath.hpp"
#include "matrix4.hpp"
#include "quaternion.hpp"
#include "renderData.hpp"
#include "parser.hpp"
#include "color.hpp"
#include "controller.hpp"
#include "textureLoader.hpp"

void drawAll(t_bufferID &bufferID, RenderData &render);
void initAll(t_bufferID &bufferID);

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

