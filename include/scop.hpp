#pragma once

//Glfw headers, used for the iwindow and the event handling
#include <GLFW/glfw3.h>

//OpenGL linux headers used to load the OpenGL functions manually
#include <GL/glx.h>

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

//Since we can't use GLAD and GLEW, i will manually load every function
typedef void (*GL_GENBUFFERS)(GLsizei, GLuint*);
typedef void (*GL_BINDBUFFER)(GLenum, GLuint);
typedef void (*GL_BUFFERDATA)(GLenum, GLsizeiptr, const void*, GLenum);
typedef void (*GL_GENVERTEXARRAYS)(GLsizei, GLuint*);
typedef void (*GL_BINDVERTEXARRAY)(GLuint);
typedef void (*GL_VERTEXATTRIBPOINTER)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (*GL_ENABLEVERTEXATTRIBARRAY)(GLuint);
typedef void (*GL_DISABLEVERTEXATTRIBARRAY)(GLuint);
