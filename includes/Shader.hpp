#pragma once

#include "glad/glad.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <Utils.hpp>


class Shader {
public:
	unsigned int shaderId;

	Shader(std::string filePath, GLenum shaderType);
	
	void deleteShader();
	
	
	/* Exceptions */
	class ShaderNotFoundException: public std::runtime_error {
	public:
		ShaderNotFoundException(const std::string& filePath);
	};

	class ShaderCouldNotCompileException: public std::runtime_error {
	public:
		ShaderCouldNotCompileException(const char* infoLog);
	};
};

