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
}

//https://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/

//return a texture ID to use with opegGL
//load a BMP file using our custom loader
GLuint loadBMP(const char* imagepath){
	char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
	std::ifstream file(imagepath);
	if (!file.is_open()) {
		std::cerr << "Failed to open texutre file" << std::endl;
		return 0;
	}
	file.read(header, 54);
	if (file.gcount() != 54){
		std::cerr << "Failed to read file header" << std::endl;
		return 0;
	}
	if ( header[0] != 'B' || header[1] != 'M' ){
		std::cerr << "Invalid BMP file" << std::endl;
		return 0;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if (imageSize == 0)
		imageSize = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;
	data = new unsigned char[imageSize];
	file.read((char*)data, imageSize);
	file.close();

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	//filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return textureID;
}
