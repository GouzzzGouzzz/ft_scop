#include "../include/scop.hpp"

static void draw_color(GLuint colorbuffer)
{
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	//GL_FALSE or GL_TRUE depending if row major ot column major
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

static void draw_texture(GLuint uvbuffer)
{
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

static void draw_vertices(GLuint MatrixID, RenderData &render, GLuint vertexbuffer, std::vector<GLfloat> &vertices)
{
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &render.getMVP()[0][0]);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
	glDisableVertexAttribArray(0);
}

void drawAll(t_bufferID &bufferID, RenderData &render)
{
	draw_vertices(bufferID.MatrixID, render, bufferID.vertexBuffer, *bufferID.vertices);
	draw_color(bufferID.colorBuffer);
	draw_texture(bufferID.uvBuffer);
}
