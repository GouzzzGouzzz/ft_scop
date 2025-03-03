
#include "../include/scop.hpp"
#include "../include/parser.hpp"

double lastX = 0.0;
double lastY = 0.0;
bool isRightDrag = false;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
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

void mouse_motion_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (isRightDrag)
	{
		double deltaX = xpos - lastX;
		double deltaY = ypos - lastY;
		lastX = xpos;
		lastY = ypos;
		glRotatef(-deltaX * 0.2f, 0.0f, 1.0f, 0.0f);
		glRotatef(-deltaY * 0.2f, 1.0f, 0.0f, 0.0f);
	}
}

void init(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetCursorPosCallback(window, mouse_motion_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSwapInterval(1);
	LoadOpenGLFunctions();
}

std::vector<GLuint> loadEBO(std::vector<t_face> faces) {
	std::vector<GLuint> indices;
	for (std::vector<t_face>::iterator it = faces.begin(); it != faces.end(); it++) {
		indices.push_back(it->v1 - 1);
		indices.push_back(it->v2 - 1);
		indices.push_back(it->v3 - 1);
		if (it->v4 != 0) {
			indices.push_back(it->v1 - 1);
			indices.push_back(it->v3 - 1);
			indices.push_back(it->v4 - 1);
		}
	}
	return indices;
}


//Maybe put every vertices in the correct order directly before sending them into the vertex buffer data

int main(int ac, char **av) {

	if (ac != 2) {
		std::cerr << "Usage: " << av[0] << " <filename>.obj" << std::endl;
		return -1;
	}
	std::string filename = av[1];
	if (filename.find(".obj") == std::string::npos || filename.rfind(".") != filename.find(".") || filename.find(".obj") + 4 != filename.length()) {
		// std::cout << filename.find(".obj") << "==" << std::string::npos << std::endl;
		// std::cout << filename.rfind(".") << "!=" << filename.find(".") << std::endl;
		// std::cout << filename.find(".obj") + 4 << "!=" << filename.length() << std::endl;

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
	const std::vector<GLfloat>& vertices = parser.getVertices();
	const std::vector<t_face>& faces = parser.getFaces();









	Matrix4 m(1.0f, 1.0f, 1.0f, 1.0f);
	m.Translate(10.0f, 0.0f, 0.0f);
	std::vector<float> vec = {10.0f, 10.0f, 10.0f, 1.0f};
	std::vector<float> res = m * vec;
	for (std::vector<float>::iterator it = res.begin(); it != res.end(); it++) {
		std::cout << *it << " ";
	}



	return 1;




	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW or OpenGl Functions" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(900, 900, "ft_scop", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	init(window);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 0.5, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	//Shader implemtation
	GLuint programID = LoadShaders( "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl" );
	while (glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
		0,
		3,			// size
		GL_FLOAT,	// type
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)0	// array buffer offset
		);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}
