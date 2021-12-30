#include "Texturing.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texturing::Texturing()
{
	amountOfTextures = 0;
}

Texturing::~Texturing()
{
	for (unsigned int i = 0; i < amountOfTextures; i++)
	{
		glDeleteTextures(1, &textureHandler[i]); //number of and address of textures
	}
}

void Texturing::InitializeTexture(const std::string& file)
{
	int width;
	int height;
	int numberOfComponents;

	//load the image from file
	unsigned char* textureData = stbi_load((file).c_str(), &width, &height, &numberOfComponents, 4); //4 is the required components (not important to us)

	//TODO: move this to another function?
	//check if it loaded
	if (textureData == NULL)
	{
		std::cerr << "Failed to load texture" << file << std::endl;
	}

	//generate the buffer to store the texture in openGL
	glGenTextures(1, &textureHandler[amountOfTextures]); //number of and address of textures
	glBindTexture(GL_TEXTURE_2D, textureHandler[amountOfTextures]); //bind texture - define type & specify the texture it should work with

	//set the parameters to control texture wrapping and linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //wrap texture outside height
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear filtering for minification(texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //linear filtering for magnification(texture is larger)

	//send the texture to the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Texture Data

	stbi_image_free(textureData); //delete the data from CPU

	amountOfTextures += 1;
}

void Texturing::InitializeAllTextures() //TODO: fix InitializeTexture()
{
	int width;
	int height;
	int numberOfComponents;

	//load the image from file
	const std::string& file = "..\\res\\bricks.jpg";
	unsigned char* textureData = stbi_load((file).c_str(), &width, &height, &numberOfComponents, 4); //4 is the required components (not important to us)

	//TODO: move this to another function?
	//check if it loaded
	if (textureData == NULL)
	{
		std::cerr << "Failed to load texture" << "..\\res\\bricks.jpg" << std::endl;
	}

	//generate the buffer to store the texture in openGL
	glGenTextures(1, &texA); //number of and address of textures
	glBindTexture(GL_TEXTURE_2D, texA); //bind texture - define type & specify the texture it should work with

	//set the parameters to control texture wrapping and linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //wrap texture outside height
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear filtering for minification(texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //linear filtering for magnification(texture is larger)

	//send the texture to the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Texture Data

	stbi_image_free(textureData); //delete the data from CPU


	//load the image from file
	const std::string& file2 = "..\\res\\water.jpg";
	textureData = stbi_load((file2).c_str(), &width, &height, &numberOfComponents, 4); //4 is the required components (not important to us)

	//TODO: move this to another function?
	//check if it loaded
	if (textureData == NULL)
	{
		std::cerr << "Failed to load texture" << "..\\res\\bricks.jpg" << std::endl;
	}

	//generate the buffer to store the texture in openGL
	glGenTextures(1, &texB); //number of and address of textures
	glBindTexture(GL_TEXTURE_2D, texB); //bind texture - define type & specify the texture it should work with

	//set the parameters to control texture wrapping and linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //wrap texture outside height
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear filtering for minification(texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //linear filtering for magnification(texture is larger)

	//send the texture to the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Texture Data

	stbi_image_free(textureData); //delete the data from CPU


	//load the image from file
	const std::string& file3 = "..\\res\\grass.jpg";
	textureData = stbi_load((file3).c_str(), &width, &height, &numberOfComponents, 4); //4 is the required components (not important to us)

	//TODO: move this to another function?
	//check if it loaded
	if (textureData == NULL)
	{
		std::cerr << "Failed to load texture" << "..\\res\\bricks.jpg" << std::endl;
	}

	//generate the buffer to store the texture in openGL
	glGenTextures(1, &texC); //number of and address of textures
	glBindTexture(GL_TEXTURE_2D, texC); //bind texture - define type & specify the texture it should work with

	//set the parameters to control texture wrapping and linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //wrap texture outside height
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear filtering for minification(texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //linear filtering for magnification(texture is larger)

	//send the texture to the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Texture Data

	stbi_image_free(textureData); //delete the data from CPU
}

void Texturing::UseTexture(unsigned int number)
{
	assert(number >= 0 && number <= 31); //check that we are working with one of the 32 textures

	glActiveTexture(GL_TEXTURE0 + number); //set active texture unit
	glBindTexture(GL_TEXTURE_2D, textureHandler[number]); //type of and texture to bind to unit
}

void Texturing::UseSpecificTexture(unsigned int number) //TODO: fix UseTexture()
{
	if (number == 0)
	{
		glBindTexture(GL_TEXTURE_2D, texA); //type of and texture to bind to unit
	}
	else if (number == 1)
	{
		glBindTexture(GL_TEXTURE_2D, texB); //type of and texture to bind to unit
	}
	else if (number == 2)
	{
		glBindTexture(GL_TEXTURE_2D, texC); //type of and texture to bind to unit
	}
}