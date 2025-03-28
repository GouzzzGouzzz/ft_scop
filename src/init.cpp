#include "../include/scop.hpp"

static void initTexture(GLuint programID, GLuint& textureID){
	textureID = TextureLoader::cycleTextureDir();
	glUniform1i(glGetUniformLocation(programID, "myTextureSampler"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

static void initVertex(GLuint* arrayID, GLuint* buffer, std::vector<GLfloat>& vertices){
	glGenVertexArrays(1, arrayID);
	glBindVertexArray(*arrayID);

	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
}

static void initColor( GLuint* colorbuffer, uint bufferSize){
	std::vector<GLfloat> buffer = Color::cycleColor(bufferSize);
	glGenBuffers(1, colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * buffer.size(), buffer.data(), GL_STATIC_DRAW);
}

static void initUv(GLuint* uvbuffer, std::vector<t_uv>& uv){
	glGenBuffers(1, uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (uv.size() * 2), uv.data(), GL_STATIC_DRAW);
}

void initAll(t_bufferID &bufferID)
{
	initVertex(&bufferID.vertexArrayID, &bufferID.vertexBuffer, *bufferID.vertices);
	initColor(&bufferID.colorBuffer, bufferID.vertices->size());
	initUv(&bufferID.uvBuffer, *bufferID.uv);
	initTexture(bufferID.programID, bufferID.textureID);
}
