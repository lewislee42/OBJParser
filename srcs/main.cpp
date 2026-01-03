#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <exception>
#include <iostream>
#include <string>

// resizes the viewport to the new window width & height
void framebuffer_resize_callback(GLFWwindow* window, int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
}

int main(void) {
	
	std::cout << "Program Successfully Started..." << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);


	// Creates GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OBJ Parser", NULL, NULL);
	if (!window) {
		std::cerr << "Error: Could not create GLFW window." << std::endl;
		glfwTerminate();
		return (1);
	}
	glfwMakeContextCurrent(window);


	// Loads OpenGL functions for us to use later
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Error: Could not load GL functions using GLAD." << std::endl;
		return (1);
	}

	
	// Sets the callback function when the screen resizes
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);


	std::string temp("test.obj");
	{
		auto dotPos = temp.find_last_of('.');
		if (temp.substr(dotPos) != ".obj")
			
	}

	
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();

	}


	glfwTerminate();
	std::cout << "Program Successfully Finished." << std::endl;
	return (0);
}
