#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "ScreenDisplay.h"
#include <string>
#include <iostream>
using std::cout;

enum class GameState { PLAYING, QUITTING };

class Game
{
public:
	Game();
	~Game();

	void StartGame(); //This function boots up the game
	void Exit(std::string text); //This function lets the user exit the app by pressing any key

private:

	void InitializeSystems(); //This function initializes the game's systems
	void GameLoop(); //This function runs the game loop; no game loop means the game ends
	void ProcessUserInputs(); //This function takes in and processes the user's inputs
	void UpdateDisplay(); //This function updates the game's display

	GameState gameState; //Variable holding a reference to the current game state
	ScreenDisplay* gameDisplay; //Variable holding a pointer to the game's screen display

	float counter;
};

