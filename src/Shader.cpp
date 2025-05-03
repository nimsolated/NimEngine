#include "../include/Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vPath, const std::string& fPath) {
	// read and source the vertex and fragment files
	std::string vertCode = readFile(vPath);
	std::string fragCode = readFile(fPath);
	const char* vSrc = vertCode.c_str();
	const char* fSrc = fragCode.c_str();
	// create vertex shader
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vSrc, nullptr);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// create fragment shader
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fSrc, nullptr);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// attach shaders and link program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	// delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader() {
	glDeleteProgram(ID);
}

std::string Shader::readFile(const std::string& path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "[ERROR] Could not open file: " << path << '\n';
	}
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

void Shader::checkCompileErrors(GLuint obj, const std::string& type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(obj, 1024, nullptr, infoLog);
			std::cerr << "[ERROR] SHADER_COMPILATION_ERROR of type: " << type << '\n' << infoLog << '\n';
		}
	}
	else {
		glGetProgramiv(obj, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(obj, 1024, nullptr, infoLog);
			std::cerr << "[ERROR] PROGRAM_LINKING_ERROR of type: " << type << '\n' << infoLog << '\n';
		}
	}
}