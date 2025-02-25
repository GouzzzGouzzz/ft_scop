
#include "../include/scop.hpp"
#include "../include/parser.hpp"

double lastX = 0.0;
double lastY = 0.0;
bool isRightDrag = false;

GL_GENBUFFERS glGenBuffers = nullptr;
GL_BINDBUFFER glBindBuffer = nullptr;
GL_BUFFERDATA glBufferData = nullptr;
GL_GENVERTEXARRAYS glGenVertexArrays = nullptr;
GL_BINDVERTEXARRAY glBindVertexArray = nullptr;
GL_VERTEXATTRIBPOINTER glVertexAttribPointer = nullptr;
GL_ENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray = nullptr;
GL_DISABLEVERTEXATTRIBARRAY glDisableVertexAttribArray = nullptr;


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

void LoadOpenGLFunctions() {
	glGenBuffers = (GL_GENBUFFERS)glXGetProcAddress((const GLubyte*)"glGenBuffers");
	glBindBuffer = (GL_BINDBUFFER)glXGetProcAddress((const GLubyte*)"glBindBuffer");
	glBufferData = (GL_BUFFERDATA)glXGetProcAddress((const GLubyte*)"glBufferData");
	glGenVertexArrays = (GL_GENVERTEXARRAYS)glXGetProcAddress((const GLubyte*)"glGenVertexArrays");
	glBindVertexArray = (GL_BINDVERTEXARRAY)glXGetProcAddress((const GLubyte*)"glBindVertexArray");
	glVertexAttribPointer = (GL_VERTEXATTRIBPOINTER)glXGetProcAddress((const GLubyte*)"glVertexAttribPointer");
	glEnableVertexAttribArray = (GL_ENABLEVERTEXATTRIBARRAY)glXGetProcAddress((const GLubyte*)"glEnableVertexAttribArray");
	glDisableVertexAttribArray = (GL_DISABLEVERTEXATTRIBARRAY)glXGetProcAddress((const GLubyte*)"glDisableVertexAttribArray");

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
	int i = 0;
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
	std::vector<GLfloat> vertices = parser.getVertices();
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
	init(window);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//triangle
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	std::cout << vertices.size() / 3 << std::endl;
	while (glfwWindowShouldClose(window) == 0)
	{
		glClear( GL_COLOR_BUFFER_BIT );
		glColor3f(1.0f, 0.0f, 0.0f);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}




















	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
