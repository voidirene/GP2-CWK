#pragma once
#include "Transform.h"
#include <GL\glew.h>
#include <string>

class Shading
{
public:

	Shading();
	~Shading();

	void InitializeShader(const std::string& file);
	void UseShader();
	void UpdateTransform(const Transform& transform, const Camera& camera);

private:

	GLuint CreateShader(const std::string& name, unsigned int type);
	std::string LoadShader(const std::string& fileName);
	void CheckForErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

	GLuint program; //holds the shader program

	static const unsigned int numberOfShaders = 2; //amount of shaders
	GLuint shaders[numberOfShaders]; //array of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};
	GLuint uniforms[NUM_UNIFORMS];
};

