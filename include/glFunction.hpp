#pragma once

#include <GL/glx.h>

//Since we can't use GLAD and GLEW, i will manually load every function
//OpenGl VAOs and VBOs functions
typedef void (*GL_GENBUFFERS)(GLsizei, GLuint*);
typedef void (*GL_BINDBUFFER)(GLenum, GLuint);
typedef void (*GL_BUFFERDATA)(GLenum, GLsizeiptr, const void*, GLenum);
typedef void (*GL_GENVERTEXARRAYS)(GLsizei, GLuint*);
typedef void (*GL_BINDVERTEXARRAY)(GLuint);
typedef void (*GL_VERTEXATTRIBPOINTER)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (*GL_ENABLEVERTEXATTRIBARRAY)(GLuint);
typedef void (*GL_DISABLEVERTEXATTRIBARRAY)(GLuint);

//Shaders functions
typedef GLuint (*GL_CREATESHADER)(GLenum);
typedef void (*GL_SHADERSOURCE)(GLuint, GLsizei, const GLchar**, const GLint*);
typedef void (*GL_COMPILESHADER)(GLuint);
typedef void (*GL_GETSHADERIV)(GLuint, GLenum, GLint*);
typedef void (*GL_GETSHADERINFOLOG)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef GLuint (*GL_CREATEPROGRAM)(void);
typedef void (*GL_ATTACHSHADER)(GLuint, GLuint);
typedef void (*GL_LINKPROGRAM)(GLuint);
typedef void (*GL_GETPROGRAMIV)(GLuint, GLenum, GLint*);
typedef void (*GL_GETPROGRAMINFOLOG)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (*GL_USEPROGRAM)(GLuint);
typedef void (*GL_DETACHSHADER)(GLuint, GLuint);
typedef void (*GL_DELETESHADER)(GLuint);

//Var to VAOS and VBOs functions
extern GL_GENBUFFERS glGenBuffers;
extern GL_BINDBUFFER glBindBuffer;
extern GL_BUFFERDATA glBufferData;
extern GL_GENVERTEXARRAYS glGenVertexArrays;
extern GL_BINDVERTEXARRAY glBindVertexArray;
extern GL_VERTEXATTRIBPOINTER glVertexAttribPointer;
extern GL_ENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray;
extern GL_DISABLEVERTEXATTRIBARRAY glDisableVertexAttribArray;

//Var to Shader Functions
extern GL_CREATESHADER glCreateShader;
extern GL_SHADERSOURCE glShaderSource;
extern GL_COMPILESHADER glCompileShader;
extern GL_GETSHADERIV glGetShaderiv;
extern GL_GETSHADERINFOLOG glGetShaderInfoLog;
extern GL_CREATEPROGRAM glCreateProgram;
extern GL_ATTACHSHADER glAttachShader;
extern GL_LINKPROGRAM glLinkProgram;
extern GL_GETPROGRAMIV glGetProgramiv;
extern GL_GETPROGRAMINFOLOG glGetProgramInfoLog;
extern GL_USEPROGRAM glUseProgram;
extern GL_DETACHSHADER glDetachShader;
extern GL_DELETESHADER glDeleteShader;

void LoadOpenGLFunctions();
