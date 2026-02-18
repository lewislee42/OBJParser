#include <Shader.hpp>

Shader::Shader(std::string filePath, GLenum shaderType) {
	std::string shaderSource = readFileIntoString(filePath);

	const char* shaderSourceCChar = shaderSource.c_str();
	// creates a vertex shader specifying the shader type and then saving the id
	shaderId = glCreateShader(shaderType);
	// attaches shader code to the shader object and compiles it
	glShaderSource(shaderId, 1, &shaderSourceCChar, NULL);
	glCompileShader(shaderId);

	// maybe find out a way to do a loading page for compiling the shader
	// how should we not compile the shader every time and only need to compile once like games?
	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		throw ShaderCouldNotCompileException(infoLog);
	}
}

void Shader::deleteShader() {
	glDeleteShader(shaderId);
}

/* ----------- EXCEPTIONS ------------ */

/* ShaderNotFoundException */
Shader::ShaderNotFoundException::ShaderNotFoundException(const std::string& filePath):
	std::runtime_error("Shader \"" + filePath + "\" could not be found") {
}

/* ShaderCouldNotCompileException */
Shader::ShaderCouldNotCompileException::ShaderCouldNotCompileException(const char* infoLog): 
	std::runtime_error("Shader compilation failed.\n" + std::string(infoLog)) {
}
