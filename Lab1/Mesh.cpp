#include "Mesh.h"

Mesh::Mesh(Vertex* vertex, unsigned int numberOfVertices)
{
	displayCount = numberOfVertices;

	glGenVertexArrays(1, &vao); //makes a vertex array
	glBindVertexArray(vao); //binds it so we can use it

	glGenBuffers(NUM_BUFFERS, vaBuffers); //generate buffers based on the array of data (vaBuffers)
	glBindBuffer(GL_ARRAY_BUFFER, vaBuffers[POSITION_VERTEXBUFFER]); //bind the buffer and specify the type (in this case array) of data and pass the data so we can work on the buffer in our specified position
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(vertex[0]), vertex, GL_STATIC_DRAW); //move the data to the GPU and specify the type, size, starting address (pointer) of the data, as well as where to store it on the GPU

	glEnableVertexAttribArray(0); //specify to openGL how many attributes there are in the object
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //specify to openGL how to read the above array/s - which array are we working with (0 - from above), how many pieces of data there are (3 - vertex), type of data, whether to normalize or not, how much data we need to skip, and how far from the beginning to find the first attribute

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