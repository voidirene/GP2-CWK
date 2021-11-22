#include "Game.h"
#include <SDL\SDL.h>
#undef main

//The function that starts the entire program
int main(int argc, char** argv) //arguments used to call SDL main
{
	Game game;
	game.StartGame();

	return 0;
}