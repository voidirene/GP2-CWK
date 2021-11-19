#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>

class Vertex
{
public:

	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->position = pos;
		this->texCoordinates = texCoord;
	}
	//TODO: no destructor?

	glm::vec3 position;
	glm::vec2 texCoordinates; //position on texture to map to vertex
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
		TEXCOORD_VB,

		NUM_BUFFERS
	};

	GLuint vao;
	GLuint vaBuffers[NUM_BUFFERS]; //creates an array of buffers
	unsigned int displayCount; //how many VAOs we want to display
};

