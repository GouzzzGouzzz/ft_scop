#include <GLFW/glfw3.h>
#include "glFunction.hpp"
#include "renderData.hpp"
#include "color.hpp"

class Controller {
	public:
		Controller(RenderData& render, uint verticesSize);
		~Controller();
		void setWindow(GLFWwindow* window);

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mouseMotionCallback(GLFWwindow* window, double xpos, double ypos);

	private:
		static RenderData* render;
		static double lastX, lastY;
		static bool isRightDrag;
		static uint verticesSize;
};
