#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {

    // Projection matrix
    glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 800.0f / 640.0f, 0.1f, 100.0f);
	std::cout << "GLM : Projection" << std::endl;
    float* m = glm::value_ptr(Projection);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout <<  m[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
    // View matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(2, 2, 2), // Camera position
        glm::vec3(0, 0, 0), // Target
        glm::vec3(0, 1, 0)  // Up vector
    );
	std::cout << "GLM : View" << std::endl;

    m = glm::value_ptr(View);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout <<  m[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
    // Model matrix (Identity)
    glm::mat4 Model = glm::mat4(1.0f);
	Model = glm::translate(Model, glm::vec3(1.0f, 0.0f, 0.0f));
	std::cout << "GLM : Model" << std::endl;
	m = glm::value_ptr(Model);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout <<  m[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
    // MVP Matrix
    glm::mat4 MVP = Projection * View * Model;

    // Print MVP matrix
	std::cout << "GLM : MVP" << std::endl;
    m = glm::value_ptr(MVP);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout <<  m[j * 4 + i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
