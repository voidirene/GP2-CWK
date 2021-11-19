#include "Game.h"
#include "Mesh.h"
#include "Shading.h"
#include "Texturing.h"

Game::Game()
{
	gameState = GameState::PLAYING;
	gameDisplay = new ScreenDisplay();

	counter = 0;
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
	gameDisplay->InitializeDisplay();
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
	gameDisplay->ClearDisplay(); //clear the display

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0),glm::vec2(0.0, 0.0)), Vertex(glm::vec3(0, 0.5, 0),glm::vec2(0.5, 1.0)), Vertex(glm::vec3(0.5, -0.5, 0),glm::vec2(1.0, 0.0)) }; //making an array of vertices
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0])); //make a mesh; size calculated by number of bytes of an array / no bytes of one element
	Shading shader("..\\res\\shader"); //create a new shader
	Texturing texture("..\\res\\bricks.jpg"); //load a texture
	Transform transform;
	transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));

	shader.UseShader();
	shader.UpdateTransform(transform);
	texture.UseTexture(0);
	mesh.Display();

	counter = counter + 0.01f;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameDisplay->ChangeBuffer(); //swap the buffers
}