#include "../include/scop.hpp"

double lastX = 0.0;
double lastY = 0.0;
bool isRightDrag = false;

RenderData render;

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
			render.decreaseAngleX(1);
		}
		else if (deltaX > 0){
			render.increaseAngleX(1);
		}
		if (deltaY < 0){
			render.decreaseAngleY(1);
		}
		else if (deltaY > 0){
			render.increaseAngleY(1);
		}
		render.applyRotation();
	}
}

void init(GLFWwindow* window){
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetCursorPosCallback(window, mouse_motion_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSwapInterval(1);
	LoadOpenGLFunctions();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void initVertex(GLuint* arrayID, GLuint* buffer, const std::vector<GLfloat>& vertices){
	glGenVertexArrays(1, arrayID);
	glBindVertexArray(*arrayID);

	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
}

void renderingLoop(GLFWwindow* window, const Parser* parser){
	GLuint VertexArrayID, vertexbuffer;
	const std::vector<GLfloat>& vertices = (*parser).getVertices();
	const std::vector<t_face>& faces = (*parser).getFaces();
	initVertex(&VertexArrayID, &vertexbuffer, vertices);
	GLuint programID, MatrixID;

	programID = LoadShaders( "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl" );
	MatrixID = glGetUniformLocation(programID, "MVP");
	while (glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		//GL_FALSE or GL_TRUE depending if row major ot column major
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &render.getMVP()[0][0]);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		glDisableVertexAttribArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
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
	init(window);
	renderingLoop(window, &parser);
}
