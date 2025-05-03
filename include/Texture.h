#pragma once
#include <string>
#include <glad/glad.h>

class Texture {
private:
	GLuint ID;
public:
	// Load and generate a texture from file
	Texture(const std::string& path);
	~Texture();

	// Bind to a texture unit, which is 0 by default
	void bind(GLuint unit = 0) const;
};