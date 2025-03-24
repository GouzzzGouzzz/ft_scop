#include "../include/controller.hpp"

RenderData* Controller::render = nullptr;
double Controller::lastX = 0.0;
double Controller::lastY = 0.0;
bool Controller::isRightDrag = false;
uint Controller::verticesSize = 0;

Controller::Controller(RenderData& render,uint verticesSize){
	this->render = &render;
	this->verticesSize = verticesSize;
}

Controller::~Controller() { };

void Controller::setWindow(GLFWwindow* window){
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetCursorPosCallback(window, mouseMotionCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSwapInterval(1);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void Controller::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		render->axeX(1);
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		render->axeX(-1);
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
		render->axeY(1);
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
		render->axeY(-1);
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
		render->axeZ(-1);
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
		render->axeZ(1);
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	else if (key == GLFW_KEY_T && action == GLFW_PRESS){
		std::vector<GLfloat> buffer = Color::cycleColor(verticesSize);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * buffer.size(), buffer.data(), GL_STATIC_DRAW);
	}//test
	else if (key == GLFW_KEY_J && GLFW_PRESS){
		render->rotateY(1);
		render->applyRotation();
	}
	else if (key == GLFW_KEY_L && GLFW_PRESS){
		render->rotateY(-1);
		render->applyRotation();
	}
	else if (key == GLFW_KEY_I && GLFW_PRESS){
		render->rotateX(1);
		render->applyRotation();
	}
	else if (key == GLFW_KEY_K && GLFW_PRESS){
		render->rotateX(-1);
		render->applyRotation();
	}
	else if (key == GLFW_KEY_U && GLFW_PRESS){
		render->rotateZ(1);
		render->applyRotation();
	}
	else if (key == GLFW_KEY_O && GLFW_PRESS){
		render->rotateZ(-1);
		render->applyRotation();
	}
}

void Controller::scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
	if (yoffset > 0) {
		render->zoomIn(1);
	}
	else {
		render->zoomOut(1);
	}
}

void Controller::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
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

void Controller::mouseMotionCallback(GLFWwindow* window, double xpos, double ypos){
	if (isRightDrag)
	{
		double deltaX = xpos - lastX;
		double deltaY = ypos - lastY;
		lastX = xpos;
		lastY = ypos;
		float angleX = deltaX * 0.2;
		float angleY = deltaY * 0.2;

		// std::cout << "angleX: " << angleX << " angleY: " << angleY << std::endl;
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
			render->rotateX(angleX);
		} else {
			render->rotateY(-angleX);
			render->rotateZ(-angleY);
		}
		render->applyRotation();
	}
}
