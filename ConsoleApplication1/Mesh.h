#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex
{
public:

	Vertex(const glm::vec3& pos)
	{
		this->position = pos;
	}
	//TODO: no destructor?

private:
	glm::vec3 position;
};

class Mesh
{
public:

	//TODO: look into unsigned ints
	Mesh(Vertex* vertex, unsigned int numberOfVertices);
	~Mesh();

	void Display();

private:

	enum
	{
		POSITION_VERTEXBUFFER,
		NUM_BUFFERS
	};

	GLuint vao;
	GLuint vaBuffers[NUM_BUFFERS]; //creates an array of buffers
	unsigned int displayCount; //how many VAOs we want to display
};

