#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include "obj_loader.h"
#include <string>

struct Vertex
{
public:

	Vertex(const glm::vec3& pos, const glm::vec2& texCoord) //TODO: why does this not take normal as a parameter?
	{
		this->position = pos;
		this->texCoordinates = texCoord;
		this->normal = normal;
	}
	//TODO: no destructor?

	glm::vec3* GetPosition() { return &position; }
	glm::vec2* GetTexCoordinates() { return &texCoordinates; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 position;
	glm::vec2 texCoordinates;
	glm::vec3 normal;
};

//TODO: make a new script for this?
struct BoundingSphere //for collision detection
{
public:

	BoundingSphere()
	{

	}

	void UpdateSphereData(glm::vec3 position, float radius) //TODO: overloads?
	{
		this->position = position;
		this->radius = radius;
	}

	glm::vec3 GetPosition() { return position; }
	float GetRadius() { return radius; }

private:

	float radius;
	glm::vec3 position;
};

class Mesh
{
public:

	Mesh();
	~Mesh();

	void Display();
	void LoadModel(const std::string& file); //for loading a model

	void UpdateSphereData(glm::vec3 position, float radius);

	unsigned int displayCount; //how many VAOs we want to display

	//TODO: make a getter for the position + radius?
	BoundingSphere boundingSphere;

private:

	void InitializeMesh(Vertex* vertices, unsigned int numberOfVertices, unsigned int* indices, unsigned int numberOfIndices);
	void InitializeModel(const IndexedModel& model); //for initializing the model

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint vao;
	GLuint vaBuffers[NUM_BUFFERS]; //creates an array of buffers
};

