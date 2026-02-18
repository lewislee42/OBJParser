#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <exception>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ios>


std::string readFileIntoString(const std::string& filePath);
std::vector<std::string> readFileIntoVector(const std::string& filePath);
void framebufferResizeCallback(GLFWwindow* window, int newWidth, int newHeight);

/* Exceptions */
class FileNotOpened : public std::exception {
	const char *what() const throw();
};
