#include "Mesh.h"
#include <vector>

//Mesh::Mesh(Vertex* vertex, unsigned int numberOfVertices)
//{
//	displayCount = numberOfVertices;
//
//	glGenVertexArrays(1, &vao); //makes a vertex array
//	glBindVertexArray(vao); //binds it so we can use it
//
//	std::vector<glm::vec3> positions; //holds the position data
//	std::vector<glm::vec2> texCoords; //holds the texture coordinates data
//	//reserve all the space needed to hold our data
//	positions.reserve(numberOfVertices);
//	texCoords.reserve(numberOfVertices);
//
//	//TODO: changed int i to size_t i to avoid an error. is this the best solution? look into this
//	for (size_t i = 0; i < numberOfVertices; i++) //for loop for running the number of vertices and storing data in the lists
//	{
//		positions.push_back(vertex[i].position);
//		texCoords.push_back(vertex[i].texCoordinates);
//	}
//
//	glGenBuffers(NUM_BUFFERS, vaBuffers); //generate buffers based on the array of data/buffers (vaBuffers) - GLuint vertexArrayBuffers[NUM_BUFFERS];
//	glBindBuffer(GL_ARRAY_BUFFER, vaBuffers[POSITION_VERTEXBUFFER]); //bind the buffer and specify the type (in this case array) of buffer data and pass the data so we can work on the buffer in our specified position
//	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW); //move the data to the GPU and specify the type, size, starting address (pointer) of the data, as well as where to store it on the GPU
//
//	glEnableVertexAttribArray(0); //specify to openGL how many attributes there are in the object
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //specify to openGL how to read the above array/s - which array are we working with (0 - from above), how many pieces of data there are (3 - vertex), type of data, whether to normalize or not, how much data we need to skip, and how far from the beginning to find the first attribute
//
//	glBindBuffer(GL_ARRAY_BUFFER, vaBuffers[TEXCOORD_VB]); //tell openGL what type of data the buffer is(GL_ARRAY_BUFFER), and pass the data
//	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer)of data, where do we store the data on the GPU
//	
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindVertexArray(0); //unbinds the vertex array
//}

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao); //delete the vertex array
}

void Mesh::LoadModel(const std::string& file)
{
	IndexedModel model = OBJModel(file).ToIndexedModel(); //loads a model from file
	InitializeModel(model); //initialize the model
}

void Mesh::InitializeMesh(Vertex* vertices, unsigned int numberOfVertices, unsigned int* indices, unsigned int numberOfIndices) //TODO: redo comments
{
	IndexedModel model;

	for (unsigned int i = 0; i < numberOfVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPosition());
		model.texCoords.push_back(*vertices[i].GetTexCoordinates());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numberOfIndices; i++)
		model.indices.push_back(indices[i]);

	InitializeModel(model);
}

void Mesh::InitializeModel(const IndexedModel& model) //TODO: redo comments
{
	displayCount = model.indices.size();

	glGenVertexArrays(1, &vao); //generate a vertex array and store it in the VAO
	glBindVertexArray(vao); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	glGenBuffers(NUM_BUFFERS, vaBuffers); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];

	glBindBuffer(GL_ARRAY_BUFFER, vaBuffers[POSITION_VERTEXBUFFER]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vaBuffers[TEXCOORD_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vaBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vaBuffers[INDEX_VB]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glBindVertexArray(0); // unbind our VAO
}

void Mesh::Display()
{
	glBindVertexArray(vao); //bind the vertex array
	glDrawElements(GL_TRIANGLES, displayCount, GL_UNSIGNED_INT, 0); //display; mode, number of objects, type, const void *indices
	glBindVertexArray(0); //unbind
}

void Mesh::UpdateSphereData(glm::vec3 position, float radius)
{
	boundingSphere.UpdateSphereData(position, radius);
}