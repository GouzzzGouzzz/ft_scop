
#include "../include/scop.hpp"
#include "../include/parser.hpp"


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	static bool lbutton_down = false;
	// if (button == GLFW_MOUSE_BUTTON_RIGHT)
	// {
	// 	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	// }
	// if (button == GLFW_MOUSE_BUTTON_LEFT)
	// {
	// 	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	// }
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if(GLFW_PRESS == action)
			lbutton_down = true;
		else if(GLFW_RELEASE == action)
			lbutton_down = false;
	}

	if(lbutton_down) {
		// glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
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

	Parser parser(filename);
	std::vector<t_vertex> vertices = parser.getVertices();
	std::vector<t_face> faces = parser.getFaces();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "ft_scop", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//CHATGPT
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	// Set up the perspective projection matrix using glFrustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0); // Perspective without GLU

	// Switch back to ModelView for the camera setup
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move the camera to a position where it can see three faces of the cube
	// This will place the camera at (2, 2, 2), looking at the origin (0, 0, 0)
	glTranslatef(-2.0f, -2.0f, -5.0f);  // Move the camera back and slightly down and left

	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);  // Rotate on the X-axis
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);  // Rotate on the Y-axis

	glDisable(GL_LIGHTING);
	//END CHATGPT

	//Disable Cursor to be able to use raw mouse motion
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		for (std::vector<t_face>::iterator it = faces.begin(); it != faces.end(); it++) {
			glVertex3f(vertices[it->v2 - 1].x, vertices[it->v2 - 1].y, vertices[it->v2 - 1].z);
			glVertex3f(vertices[it->v1 - 1].x, vertices[it->v1 - 1].y, vertices[it->v1 - 1].z);
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
