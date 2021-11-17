#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertex, unsigned int numberOfVertices)
{
	displayCount = numberOfVertices;

	glGenVertexArrays(1, &vao); //makes a vertex array
	glBindVertexArray(vao); //binds it so we can use it

	std::vector<glm::vec3> positions; //holds the position data
	std::vector<glm::vec2> textCoords; //holds the texture coordinates data
	//reserve all the space needed to hold our data
	positions.reserve(numberOfVertices);
	textCoords.reserve(numberOfVertices);

	for (int i = 0; i < numberOfVertices; i++) //for loop for running the number of vertices and storing data in the lists
	{
		positions.push_back(vertex[i].position);
		textCoords.push_back(vertex[i].texCoordinates);
	}

	glGenBuffers(NUM_BUFFERS, vaBuffers); //generate buffers based on the array of data/buffers (vaBuffers) - GLuint vertexArrayBuffers[NUM_BUFFERS];
	glBindBuffer(GL_ARRAY_BUFFER, vaBuffers[POSITION_VERTEXBUFFER]); //bind the buffer and specify the type (in this case array) of buffer data and pass the data so we can work on the buffer in our specified position
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW); //move the data to the GPU and specify the type, size, starting address (pointer) of the data, as well as where to store it on the GPU

	glEnableVertexAttribArray(0); //specify to openGL how many attributes there are in the object
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //specify to openGL how to read the above array/s - which array are we working with (0 - from above), how many pieces of data there are (3 - vertex), type of data, whether to normalize or not, how much data we need to skip, and how far from the beginning to find the first attribute

	glBindBuffer(GL_ARRAY_BUFFER, vaBuffers[TEXCOORD_VB]); //tell openGL what type of data the buffer is(GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(textCoords[0]), &textCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer)of data, where do we store the data on the GPU
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0); //unbinds the vertex array
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao); //delete the vertex array
}

void Mesh::Display()
{
	glBindVertexArray(vao); //bind the vertex array
	glDrawArrays(GL_TRIANGLES, 0, displayCount); //display; mode, starting position, where we want to stop
	glBindVertexArray(0); //unbind
}