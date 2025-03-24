#include "../include/scop.hpp"

void initWindow(GLFWwindow* window){
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetCursorPosCallback(window, mouse_motion_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, mouse_scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSwapInterval(1);
	LoadOpenGLFunctions();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
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
}
