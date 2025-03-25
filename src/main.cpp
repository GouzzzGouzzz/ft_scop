#include "../include/scop.hpp"

//faire systeme texture changement

void renderingLoop(GLFWwindow* window, Parser& parser, RenderData& render, t_bufferID& bufferID) {
	bufferID.vertices = &parser.getVertices();
	bufferID.faces = &parser.getFaces();
	bufferID.uv = &parser.getUv();

	initAll(bufferID);
	bufferID.programID = LoadShaders( "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl" );
	glUseProgram(bufferID.programID);
	bufferID.MatrixID = glGetUniformLocation(bufferID.programID, "MVP");
	render.lookAtObj();
	while (glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawAll(bufferID, render);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// glDeleteTextures(1, &texture);
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Usage: " << av[0] << " <filename>.obj" << std::endl;
		return -1;
	}
	std::string filename = av[1];
	if (filename.find(".obj") == std::string::npos || filename.rfind(".") != filename.find(".") || filename.find(".obj") + 4 != filename.length()) {
		std::cerr << "Invalid file format" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	Parser parser(filename);

	if (parser.failed) {
		std::cerr << "Failed to parse file" << std::endl;
		return -1;
	}

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW or OpenGl Functions" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "ft_scop", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	RenderData render(parser.getVertices());
	t_bufferID bufferID;
	Controller controller(render, parser.getVertices().size(), bufferID);
	controller.setWindow(window);
	LoadOpenGLFunctions();
	renderingLoop(window, parser, render, bufferID);
}
