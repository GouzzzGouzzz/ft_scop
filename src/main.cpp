#include "../include/scop.hpp"

void textureTransition(float& mixFactor, t_bufferID& bufferID, double& lastTime) {
	if (Controller::isTransitioning()) {
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		if (Controller::isTextureEnabled()) {
			mixFactor += 0.65f * deltaTime;
			if (mixFactor >= 1.0f) {
				mixFactor = 1.0f;
				Controller::setTransitioning(false);
			}
		}
		else {
			mixFactor -= 0.65f * deltaTime;
			if (mixFactor <= 0.0f) {
				mixFactor = 0.0f;
				Controller::setTransitioning(false);
			}
		}
	}
	glUniform1f(glGetUniformLocation(bufferID.programID, "mixFactor"), mixFactor);
}

void renderingLoop(GLFWwindow* window, Parser& parser, RenderData& render, t_bufferID& bufferID) {
	bufferID.vertices = &parser.getVertices();
	bufferID.faces = &parser.getFaces();
	bufferID.uv = &parser.getUv();

	initAll(bufferID);
	bufferID.programID = LoadShaders( "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl" );
	glUseProgram(bufferID.programID);
	bufferID.MatrixID = glGetUniformLocation(bufferID.programID, "MVP");
	render.lookAtObj();
	render.applyRotation();
	float mixFactor = 0.0f;
	double lastTime = glfwGetTime();
	while (glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		textureTransition(mixFactor, bufferID, lastTime);
		drawAll(bufferID, render);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteTextures(1, &bufferID.textureID);
	glDeleteProgram(bufferID.programID);
	glDeleteVertexArrays(1, &bufferID.vertexArrayID);
	glDeleteBuffers(1, &bufferID.vertexBuffer);
	glDeleteBuffers(1, &bufferID.colorBuffer);
	glDeleteBuffers(1, &bufferID.uvBuffer);

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
		std::cerr << "Usage: " << av[0] << " <filename>.obj" << std::endl;
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
