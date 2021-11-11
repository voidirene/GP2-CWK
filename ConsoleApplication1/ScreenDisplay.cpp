#include "ScreenDisplay.h"

ScreenDisplay::ScreenDisplay()
{
	window = nullptr;
	displayWidth = 1600;
	displayHeight = 900;
}

void ScreenDisplay::initializeDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initialize SDL

	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //set up double buffer

	window = SDL_CreateWindow("GP2 Coursework Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, displayWidth, displayHeight, SDL_WINDOW_OPENGL); //create game window

	sdlglContext = SDL_GL_CreateContext(window); //create a new SDL GL context to use with our OpenGL window
	glew = glewInit(); //initialize glew

	checkForErrors(); //check that everything has been initialized properly, else return an error message

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //set background color
}

void ScreenDisplay::changeBuffer()
{
	SDL_GL_SwapWindow(window);
}

//TODO: check for errors in more parts of the program? not just in screenDisplay?
//TODO: check for more errors here?
void ScreenDisplay::checkForErrors()
{
	if (window == nullptr)
	{
		std::cout << "Window is a null pointer. Press any key to exit the app.";
		int in;
		std::cin >> in;
		SDL_Quit();
	}
	if (sdlglContext == nullptr)
	{
		std::cout << "SDL GL Context is a null pointer. Press any key to exit the app.";
		int in;
		std::cin >> in;
		SDL_Quit();
	}
	if (glew != GLEW_OK)
	{
		std::cout << "Glew initialization failed. Press any key to exit the app.";
		int in;
		std::cin >> in;
		SDL_Quit();
	}
}