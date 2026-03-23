#include <Shader.hpp>

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile; 
	std::ifstream fragmentFile; 

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		std::stringstream vertexShaderStream, fragmentShaderStream;

		vertexShaderStream << vertexFile.rdbuf();
		fragmentShaderStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	} catch (std::ifstream::failure e) {
		throw ShaderCouldNotReadFile(e.what());
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();
	
	unsigned int vertexId, fragmentId;
	int success;
	char infoLog[512];

	// Vertex Shader Compilation 
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexId);

	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
		throw ShaderCouldNotCompileException(infoLog);
	}

	// Fragment Shader Compilation 
	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentId);

	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentId, 512, NULL, infoLog);
		throw ShaderCouldNotCompileException(infoLog);
	}

	id = glCreateProgram();
	glAttachShader(id, vertexId);
	glAttachShader(id, fragmentId);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		throw ShaderProgramLinkingError(infoLog);
	}

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void Shader::use() {
	glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}


/* ----------- EXCEPTIONS ------------ */

/* ShaderNotFoundException */
Shader::ShaderCouldNotReadFile::ShaderCouldNotReadFile(const char* errmsg):
	std::runtime_error("Could not read shader file with exception: " + std::string(errmsg)) {
}

/* ShaderCouldNotCompileException */
Shader::ShaderCouldNotCompileException::ShaderCouldNotCompileException(const char* infoLog): 
	std::runtime_error("Shader compilation failed.\n" + std::string(infoLog)) {
}

/* ShaderProgramLinkingError */
Shader::ShaderProgramLinkingError::ShaderProgramLinkingError(const char* infoLog):
	std::runtime_error("Shader Program failed to link shaders\n" + std::string(infoLog)){
}
