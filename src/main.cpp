
#include "../include/scop.hpp"
#include "../include/parser.hpp"

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

	for (std::vector<t_vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
		std::cout << "x: " << it->x << " y: " << it->y << " z: " << it->z << std::endl;
	}

	// if (!glfwInit()) {
	// 	std::cerr << "Failed to initialize GLFW" << std::endl;
	// 	return -1;
	// }

	// GLFWwindow* window = glfwCreateWindow(640, 480, "ft_scop", NULL, NULL);
	// if (!window) {
	// 	std::cerr << "Failed to create window" << std::endl;
	// 	glfwTerminate();
	// 	return -1;
	// }

	// glfwMakeContextCurrent(window);
	// glfwSwapInterval(1);
	// while (!glfwWindowShouldClose(window)) {

	// 	glfwSwapBuffers(window);
	// 	glfwPollEvents();
	// }

	// glfwDestroyWindow(window);
	// glfwTerminate();
	// return 0;
}
