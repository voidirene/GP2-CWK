#include "ScreenDisplay.h"

ScreenDisplay::ScreenDisplay()
{
	window = nullptr;
	displayWidth = 1600;
	displayHeight = 900;
}

ScreenDisplay::~ScreenDisplay()
{
	SDL_GL_DeleteContext(sdlglContext); //delete the context
	SDL_DestroyWindow(window); //delete the window
	SDL_Quit();
}

void ScreenDisplay::InitializeDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initialize SDL

	//TODO: figure out if we're keeping these
	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //set up double buffer

	window = SDL_CreateWindow("GP2 Coursework Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, displayWidth, displayHeight, SDL_WINDOW_OPENGL); //create game window

	sdlglContext = SDL_GL_CreateContext(window); //create a new SDL GL context to use with our OpenGL window
	glew = glewInit(); //initialize glew

	CheckForErrors(); //check that everything has been initialized properly, else return an error message

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //set background color
}

void ScreenDisplay::ChangeBuffer()
{
	SDL_GL_SwapWindow(window);
}

void ScreenDisplay::ClearDisplay()
{
	glClearDepth(1.0); //sets the clear depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears color and depth buffer //set colour to colour defined in glClearColor
}

//TODO: check for errors in more parts of the program? not just in screenDisplay?
//TODO: check for more errors here?
void ScreenDisplay::CheckForErrors()
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