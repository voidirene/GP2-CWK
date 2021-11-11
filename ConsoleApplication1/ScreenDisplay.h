#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>
#include <iostream>
using std::cout;

class ScreenDisplay
{
public:

	ScreenDisplay();
	~ScreenDisplay();

	void initializeDisplay(); //This function initializes the systems required for a new window screen
	void changeBuffer(); //This function swaps buffers (since we're using double buffering)

private:

	void checkForErrors(); //This function checks that all systems initialized in initializeDisplay() have initialized correctly

	SDL_Window* window; //Variable that holds a pointer to our game window
	SDL_GLContext sdlglContext; //Variable that holds the SDL GL Context
	GLenum glew;

	int displayWidth; //the game window's width
	int displayHeight; //the game window's height
};

