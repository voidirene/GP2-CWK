#include "Game.h"

Game::Game()
{
	gameState = GameState::PLAYING;
	gameDisplay = new ScreenDisplay();
}
Game::~Game()
{

}

void Game::StartGame()
{
	InitializeSystems();
	GameLoop();
}

//TODO: check if this is okay to have in the game/is necessary
void Game::Exit(std::string text)
{
	std::cout << text << std::endl;
	std::cout << "Press any  key to exit the app.";
	int in;
	std::cin >> in;
	SDL_Quit();
}

//TODO: maybe this can moved to StartGame() altogether? since its just one line
void Game::InitializeSystems()
{
	gameDisplay->initializeDisplay();
}

void Game::GameLoop()
{
	while (gameState == GameState::PLAYING)
	{
		ProcessUserInputs();
		UpdateDisplay();
	}
}

void Game::ProcessUserInputs()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) //get and process events
	{
		switch (event.type) //TODO: add more event types, such as for moving camera (or maybe even moving the objects on the screen?)
		{
		case SDL_QUIT:
			gameState = GameState::QUITTING;
			break;
		}
	}
}

//TODO: should this be in the ScreenDisplay class instead?
void Game::UpdateDisplay()
{
	//TODO: these two lines should probably be in their own function in screendisplay
	glClearDepth(1.0); //sets the clear depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears color and depth buffer //set colour to colour defined in glClearColor

	//TODO: remove this bit
	// old code for testing only 
	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0, 0);
	glVertex2f(0, 500);
	glVertex2f(500, 500);
	glEnd();

	gameDisplay->changeBuffer(); //swap the buffers
}