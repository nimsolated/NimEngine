#define STB_IMAGE_IMPLEMENTATION
#include "../include/Texture.h"
#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string& path) {
	int width;
	int height;
	int nrChannels;
	// Flip so that (0, 0) is bottom-left
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
	if (!data) {
		std::cerr << "[ERROR] Failed to load texture: " << path << '\n';
		return;
	}

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	// Fix row-alignment, makes sure rows are read tightly packed
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Wrapping/filtering defaults
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free the loaded image
	stbi_image_free(data);
}

Texture::~Texture() {
	glDeleteTextures(1, &ID);
}

void Texture::bind(GLuint unit) const {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}