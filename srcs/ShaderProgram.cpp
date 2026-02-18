#include <ShaderProgram.hpp>

ShaderProgram::ShaderProgram():
	ShaderProgram("./shaders/basic.vert", "./shaders/basic.frag") {
}

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	std::cout << "testing in shaderprogram" << std::endl;
	Shader vertexShader(vertexShaderPath, GL_VERTEX_SHADER);
	Shader fragmentShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	shaderProgramId = glCreateProgram();
	glAttachShader(shaderProgramId, vertexShader.shaderId);
	glAttachShader(shaderProgramId, fragmentShader.shaderId);
	glLinkProgram(shaderProgramId);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
		throw ShaderProgramLinkingError(infoLog);
	}

	vertexShader.deleteShader();
	fragmentShader.deleteShader();
}

void ShaderProgram::useProgram() {
	glUseProgram(shaderProgramId);
}


/* ---------- EXCEPTIONS ---------- */

/* ShaderProgramLinkingError */
ShaderProgram::ShaderProgramLinkingError::ShaderProgramLinkingError(const char* infoLog):
	std::runtime_error("Shader Program failed to link shaders\n" + std::string(infoLog)){
}
