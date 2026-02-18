#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <stdexcept>
#include <string>
#include <vector>

#include <ShaderProgram.hpp>
#include <Utils.hpp>

class MainScene {
private:
	GLFWwindow* 				window;
	ShaderProgram* 				shaderProgram;
	std::vector<float>			vertices;
	std::vector<unsigned int>	indices;
	bool						qPressed = false;
	bool						isWireframe = false;

	void processInput();

public:

	MainScene();
	~MainScene();

	void loadModel(const char* modelPath);
	void run();


	/* Exceptions */
	class CouldNotCreateGLFWWindowException: public std::runtime_error {
	public:
		CouldNotCreateGLFWWindowException();
	};

	class CouldNotLoadGLFunctionsException: public std::runtime_error {
	public:
		CouldNotLoadGLFunctionsException();
	};
	
	class ModelFileNotCorrectFormatException: public std::runtime_error {
	public:
		ModelFileNotCorrectFormatException();
	};
};
