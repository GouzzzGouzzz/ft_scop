#include <GLFW/glfw3.h>
#include "glFunction.hpp"
#include "renderData.hpp"
#include "color.hpp"
#include "textureLoader.hpp"

class Controller {
	public:
		Controller(RenderData& render, uint verticesSize, t_bufferID& bufferID);
		~Controller();
		void setWindow(GLFWwindow* window);

		static void toggleTexture();
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mouseMotionCallback(GLFWwindow* window, double xpos, double ypos);
		static bool isTextureEnabled();
		static bool isTransitioning();
		static void setTransitioning(bool state);

	private:
		static RenderData* render;
		static t_bufferID* bufferID;
		static double lastX, lastY;
		static bool isRightDrag;
		static uint verticesSize;
		static bool textureEnabled;
		static bool transitioning;
	};
