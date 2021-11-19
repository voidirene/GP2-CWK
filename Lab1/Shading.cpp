#include "Shading.h"
#include <fstream>
#include <iostream>

Shading::Shading(const std::string& filename)
{
	program = glCreateProgram(); //create the program

	shaders[0] = CreateShader(LoadShader("..\\res\\shader.vert"), GL_VERTEX_SHADER); //create the shaders from file
	shaders[1] = CreateShader(LoadShader("..\\res\\shader.frag"), GL_FRAGMENT_SHADER);
	
	for (int i = 0; i < numberOfShaders; i++) //for loop for attaching shaders to the program
	{
		glAttachShader(program, shaders[i]);
	}

	glBindAttribLocation(program, 0, "position"); //bind the attribute locations
	glBindAttribLocation(program, 1, "texCoord");
	
	glLinkProgram(program); //create executables that will run on the GPU shaders
	CheckForErrors(program, GL_LINK_STATUS, true, "Error: Shader program linking failed"); //check if it has linked

	glValidateProgram(program); //check the entire program is valid
	CheckForErrors(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform"); //sets up the uniform with the shader program
}

Shading::~Shading()
{
	for (int i = 0; i < numberOfShaders; i++) 
	{
		glDetachShader(program, shaders[i]); //dettach shaders from program
		glDeleteShader(shaders[i]); //delete the shaders
	}
	glDeleteProgram(program); //delete the program
}

void Shading::UseShader()
{
	glUseProgram(program); //use the shader program
}

//TODO: check this and change names/optimize?
GLuint Shading::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckForErrors(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

//TODO: check this and change names/optimize?
std::string Shading::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());
	std::string output;
	std::string line;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}
	return output;
}

void Shading::UpdateTransform(const Transform& transform)
{
	glm::mat4 model = transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &model[0][0]);
}

//TODO: check this and change names/optimize?
void Shading::CheckForErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };
	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);
	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}