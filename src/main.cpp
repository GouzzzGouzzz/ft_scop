
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
		std::cout << "deltaX: " << deltaX << " deltaY: " << deltaY << std::endl;
		glRotatef(-deltaX * 0.2f, 0.0f, 1.0f, 0.0f);
		glRotatef(-deltaY * 0.2f, 1.0f, 0.0f, 0.0f);
	}
}

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
	std::vector<t_vertex> vertices = parser.getVertices();
	std::vector<t_face> faces = parser.getFaces();
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(900, 900, "ft_scop", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetCursorPosCallback(window, mouse_motion_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		for (std::vector<t_face>::iterator it = faces.begin(); it != faces.end(); it++) {
			glVertex3f(vertices[it->v1 - 1].x, vertices[it->v1 - 1].y, vertices[it->v1 - 1].z);
			glVertex3f(vertices[it->v2 - 1].x, vertices[it->v2 - 1].y, vertices[it->v2 - 1].z);
			glVertex3f(vertices[it->v3 - 1].x, vertices[it->v3 - 1].y, vertices[it->v3 - 1].z);
			if (it->v4 != 0) {
				glVertex3f(vertices[it->v1 - 1].x, vertices[it->v1 - 1].y, vertices[it->v1 - 1].z);
				glVertex3f(vertices[it->v3 - 1].x, vertices[it->v3 - 1].y, vertices[it->v3 - 1].z);
				glVertex3f(vertices[it->v4 - 1].x, vertices[it->v4 - 1].y, vertices[it->v4 - 1].z);
			}
		}
		glEnd();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
