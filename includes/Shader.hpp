#pragma once

#include "glad/glad.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <Utils.hpp>


class Shader {
public:
	// Shader Program ID
	unsigned int id;

	Shader(std::string vertexPath, std::string fragmentPath);

	void use();
	
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	
	/* Exceptions */
	class ShaderCouldNotReadFile: public std::runtime_error {
	public:
		ShaderCouldNotReadFile(const char* errmsg);
	};

	class ShaderCouldNotCompileException: public std::runtime_error {
	public:
		ShaderCouldNotCompileException(const char* infoLog);
	};

	class ShaderProgramLinkingError: public std::runtime_error {
	public: 
		ShaderProgramLinkingError(const char* infoLog);
	};
};

