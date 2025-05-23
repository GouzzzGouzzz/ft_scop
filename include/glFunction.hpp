#pragma once

#include <GL/glx.h>

//Since we can't use GLAD and GLEW, i will manually load every function
//OpenGl VAOs functions
typedef void (*GL_GENBUFFERS)(GLsizei, GLuint*);
typedef void (*GL_BINDBUFFER)(GLenum, GLuint);
typedef void (*GL_BUFFERDATA)(GLenum, GLsizeiptr, const void*, GLenum);
typedef void (*GL_GENVERTEXARRAYS)(GLsizei, GLuint*);
typedef void (*GL_BINDVERTEXARRAY)(GLuint);
typedef void (*GL_VERTEXATTRIBPOINTER)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (*GL_ENABLEVERTEXATTRIBARRAY)(GLuint);
typedef void (*GL_DISABLEVERTEXATTRIBARRAY)(GLuint);

typedef void (*GL_DELETEPROGRAM)(GLuint);
typedef void (*GL_DELETEVERTEXARRAYS)(GLsizei, const GLuint*);
typedef void (*GL_DELETEVERTEXBUFFERS)(GLsizei, const GLuint*);

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

//Acces and modify uniforms
typedef GLuint (*GL_GETUNIFORMLOCATION)(GLuint, const GLchar*);
typedef void (*GL_UNIFORMMATRIX4FV)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (*GL_UNIFORM1I)(GLint, GLint);
typedef void (*GL_UNIFORM1F)(GLint, GLfloat);
typedef void (*GL_GETUNIFORMIV)(GLuint, GLint, GLint*);

//Var to VAOS functions
extern GL_GENBUFFERS glGenBuffers;
extern GL_BINDBUFFER glBindBuffer;
extern GL_BUFFERDATA glBufferData;
extern GL_GENVERTEXARRAYS glGenVertexArrays;
extern GL_BINDVERTEXARRAY glBindVertexArray;
extern GL_VERTEXATTRIBPOINTER glVertexAttribPointer;
extern GL_ENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray;
extern GL_DISABLEVERTEXATTRIBARRAY glDisableVertexAttribArray;

extern GL_DELETEPROGRAM glDeleteProgram;
extern GL_DELETEVERTEXARRAYS glDeleteVertexArrays;
extern GL_DELETEVERTEXBUFFERS glDeleteBuffers;

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

//Var to Acces and modify uniforms
extern GL_GETUNIFORMLOCATION glGetUniformLocation;
extern GL_UNIFORMMATRIX4FV glUniformMatrix4fv;
extern GL_UNIFORM1I glUniform1i;
extern GL_UNIFORM1F glUniform1f;
extern GL_GETUNIFORMIV glGetUniformiv;

void LoadOpenGLFunctions();
