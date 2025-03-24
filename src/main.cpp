#include "../include/scop.hpp"

double lastX = 0.0;
double lastY = 0.0;
bool isRightDrag = false;

RenderData render;

//problem des callback
//faire systeme texture changement
//faire systeme de rotation (controller class pour input tout simplement)

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		render.axeX(1);
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		render.axeX(-1);
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
		render.axeY(1);
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
		render.axeY(-1);
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
		render.axeZ(-1);
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
		render.axeZ(1);
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	else if (key == GLFW_KEY_T && action == GLFW_PRESS){
		std::vector<GLfloat> buffer = Color::cycleColor();
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * buffer.size(), buffer.data(), GL_STATIC_DRAW);
	}
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset > 0) {
		render.zoomIn(1);
	}
	else {
		render.zoomOut(1);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			glfwGetCursorPos(window, &lastX, &lastY);
			isRightDrag = true;
		}
		else if (action == GLFW_RELEASE)
		{
			isRightDrag = false;
		}
	}
}

void mouse_motion_callback(GLFWwindow* window, double xpos, double ypos){
	if (isRightDrag)
	{
		double deltaX = xpos - lastX;
		double deltaY = ypos - lastY;
		lastX = xpos;
		lastY = ypos;
		if (deltaX < 0){
			render.rotateX(45);
		}
		else if (deltaX > 0){
			render.rotateX(0);
		}
		if (deltaY < 0){
			render.rotateY(0);
		}
		else if (deltaY > 0){
			render.rotateY(0);
		}
		render.applyRotation();
	}
}

void renderingLoop(GLFWwindow* window, Parser* parser){
	t_bufferID bufferID;
	bufferID.vertices = &(*parser).getVertices();
	bufferID.faces = &(*parser).getFaces();
	bufferID.uv = &(*parser).getUv();


	render.init(*bufferID.vertices);
	initAll(bufferID);

	bufferID.programID = LoadShaders( "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl" );
	glUseProgram(bufferID.programID);

	//texture
	GLuint texture = loadBMP("textures/wood128.bmp");
	glUniform1i(glGetUniformLocation(bufferID.programID, "myTextureSampler"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(bufferID.programID, "useTexture"), GL_TRUE);
	//end of texture

	bufferID.MatrixID = glGetUniformLocation(bufferID.programID, "MVP");
	render.lookAtObj();
	while (glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawAll(bufferID, render);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteTextures(1, &texture);
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
	initWindow(window);
	renderingLoop(window, &parser);
}
