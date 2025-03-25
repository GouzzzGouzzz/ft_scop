#include "../include/scop.hpp"

//Function pointers to the OpenGL functions
GL_GENBUFFERS glGenBuffers = nullptr;
GL_BINDBUFFER glBindBuffer = nullptr;
GL_BUFFERDATA glBufferData = nullptr;
GL_GENVERTEXARRAYS glGenVertexArrays = nullptr;
GL_BINDVERTEXARRAY glBindVertexArray = nullptr;
GL_VERTEXATTRIBPOINTER glVertexAttribPointer = nullptr;
GL_ENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray = nullptr;
GL_DISABLEVERTEXATTRIBARRAY glDisableVertexAttribArray = nullptr;
//Shader functions
GL_CREATESHADER glCreateShader = nullptr;
GL_SHADERSOURCE glShaderSource = nullptr;
GL_COMPILESHADER glCompileShader = nullptr;
GL_GETSHADERIV glGetShaderiv = nullptr;
GL_GETSHADERINFOLOG glGetShaderInfoLog = nullptr;
GL_CREATEPROGRAM glCreateProgram = nullptr;
GL_ATTACHSHADER glAttachShader = nullptr;
GL_LINKPROGRAM glLinkProgram = nullptr;
GL_GETPROGRAMIV glGetProgramiv = nullptr;
GL_GETPROGRAMINFOLOG glGetProgramInfoLog = nullptr;
GL_USEPROGRAM glUseProgram = nullptr;
GL_DETACHSHADER glDetachShader = nullptr;
GL_DELETESHADER glDeleteShader = nullptr;
//Idk
GL_GETUNIFORMLOCATION glGetUniformLocation = nullptr;
GL_UNIFORMMATRIX4FV glUniformMatrix4fv = nullptr;
GL_UNIFORM1I glUniform1i = nullptr;
GL_GETUNIFORMIV glGetUniformiv = nullptr;

void LoadOpenGLFunctions() {
	// Load OpenGL functions
	glGenBuffers = (GL_GENBUFFERS)glXGetProcAddress((const GLubyte*)"glGenBuffers");
	glBindBuffer = (GL_BINDBUFFER)glXGetProcAddress((const GLubyte*)"glBindBuffer");
	glBufferData = (GL_BUFFERDATA)glXGetProcAddress((const GLubyte*)"glBufferData");
	glGenVertexArrays = (GL_GENVERTEXARRAYS)glXGetProcAddress((const GLubyte*)"glGenVertexArrays");
	glBindVertexArray = (GL_BINDVERTEXARRAY)glXGetProcAddress((const GLubyte*)"glBindVertexArray");
	glVertexAttribPointer = (GL_VERTEXATTRIBPOINTER)glXGetProcAddress((const GLubyte*)"glVertexAttribPointer");
	glEnableVertexAttribArray = (GL_ENABLEVERTEXATTRIBARRAY)glXGetProcAddress((const GLubyte*)"glEnableVertexAttribArray");
	glDisableVertexAttribArray = (GL_DISABLEVERTEXATTRIBARRAY)glXGetProcAddress((const GLubyte*)"glDisableVertexAttribArray");
	//Shader functions
	glCreateShader = (GL_CREATESHADER)glXGetProcAddress((const GLubyte*)"glCreateShader");
	glShaderSource = (GL_SHADERSOURCE)glXGetProcAddress((const GLubyte*)"glShaderSource");
	glCompileShader = (GL_COMPILESHADER)glXGetProcAddress((const GLubyte*)"glCompileShader");
	glGetShaderiv = (GL_GETSHADERIV)glXGetProcAddress((const GLubyte*)"glGetShaderiv");
	glGetShaderInfoLog = (GL_GETSHADERINFOLOG)glXGetProcAddress((const GLubyte*)"glGetShaderInfoLog");
	glCreateProgram = (GL_CREATEPROGRAM)glXGetProcAddress((const GLubyte*)"glCreateProgram");
	glAttachShader = (GL_ATTACHSHADER)glXGetProcAddress((const GLubyte*)"glAttachShader");
	glLinkProgram = (GL_LINKPROGRAM)glXGetProcAddress((const GLubyte*)"glLinkProgram");
	glGetProgramiv = (GL_GETPROGRAMIV)glXGetProcAddress((const GLubyte*)"glGetProgramiv");
	glGetProgramInfoLog = (GL_GETPROGRAMINFOLOG)glXGetProcAddress((const GLubyte*)"glGetProgramInfoLog");
	glUseProgram = (GL_USEPROGRAM)glXGetProcAddress((const GLubyte*)"glUseProgram");
	glDetachShader = (GL_DETACHSHADER)glXGetProcAddress((const GLubyte*)"glDetachShader");
	glDeleteShader = (GL_DELETESHADER)glXGetProcAddress((const GLubyte*)"glDeleteShader");
	//Idk
	glGetUniformLocation = (GL_GETUNIFORMLOCATION)glXGetProcAddress((const GLubyte*)"glGetUniformLocation");
	glUniformMatrix4fv = (GL_UNIFORMMATRIX4FV)glXGetProcAddress((const GLubyte*)"glUniformMatrix4fv");
	glUniform1i = (GL_UNIFORM1I)glXGetProcAddress((const GLubyte*)"glUniform1i");
	glGetUniformiv = (GL_GETUNIFORMIV)glXGetProcAddress((const GLubyte*)"glGetUniformiv");
}
