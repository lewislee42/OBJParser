#pragma once

#include "glad/glad.h"
#include <string>
#include <stdexcept>
#include <Shader.hpp>

class ShaderProgram {
public:
	unsigned int shaderProgramId;

	ShaderProgram();
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	void useProgram();

	/* Exceptions */
	class ShaderProgramLinkingError: public std::runtime_error {
	public: 
		ShaderProgramLinkingError(const char* infoLog);
	};
};
