#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <stdexcept>
#include <string>
#include <vector>

#include <Shader.hpp>
#include <Image.hpp>
#include <Utils.hpp>

class MainScene {
private:
	GLFWwindow* 				window;
	Shader* 					shaderProgram;
	std::vector<float>			vertices;
	std::vector<unsigned int>	indices;
	bool						qPressed = false;
	bool						isWireframe = false;
	std::vector<Image>			images;	

	void processInput();
	void loadSquareModel();
	void loadTriangleModel();

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
