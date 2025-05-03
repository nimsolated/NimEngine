#pragma once
#include <string>
#include <glad/glad.h>

class Shader {
private:
	GLuint ID;

	std::string readFile(const std::string& path);
	void checkCompileErrors(GLuint shader, const std::string& type);
public:
	// paths are relative to working directory
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use() const { glUseProgram(ID); }
	GLuint getID() const { return ID; }
};