#pragma once
#include <GL\glew.h>
#include <string>

class Texturing
{
public:

	Texturing(const std::string& file);
	~Texturing();

	//TODO: functionality for using more than 32?
	void UseTexture(unsigned int number); //uses up to 32 textures

private:

	GLuint textureHandler;
};

