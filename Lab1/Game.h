#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
//#include "Camera.h"
#include "ScreenDisplay.h"
#include "Mesh.h"
#include "Shading.h"
#include "Texturing.h"
#include "Transform.h"
#include <string>
#include <iostream>
using std::cout; //TODO: maybe remove Exit() as well as these?

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
	void ProcessUserInputs(); //This function takes in and processes the user's inputs
	void GameLoop(); //This function runs the game loop; no game loop means the game ends
	void UpdateDisplay(); //This function updates the game's display

	bool DetectCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);

	GameState gameState; //Variable holding a reference to the current game state
	ScreenDisplay gameDisplay; //Variable holding a pointer to the game's screen display

	Mesh mesh1;
	Mesh mesh2;
	Camera camera;

	Texturing texture;
	Shading shader;

	float counter;
};

