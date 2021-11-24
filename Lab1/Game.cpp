#include "Game.h"
#include "Mesh.h"
#include "Shading.h"
#include "Texturing.h"

unsigned int indices[] = { 0, 1, 2 };
Transform transform;

//for displaying triangles
//Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0),glm::vec2(0.0, 0.0)), Vertex(glm::vec3(0, 0.5, 0),glm::vec2(0.5, 1.0)), Vertex(glm::vec3(0.5, -0.5, 0),glm::vec2(1.0, 0.0)) }; //making an array of vertices
//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0])); //make a mesh; size calculated by number of bytes of an array / no bytes of one element

Game::Game()
{
	gameState = GameState::PLAYING; //set the game state to PLAYING
	ScreenDisplay* gameDisplay = new ScreenDisplay(); //create a new display

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

void Game::InitializeSystems()
{
	gameDisplay.InitializeDisplay(); //initializes the game display

	mesh1.LoadModel("..\\res\\monkey3.obj"); //loads a mesh from file
	mesh2.LoadModel("..\\res\\monkey3.obj");
	shader.InitializeShader("..\\res\\shader"); //create a new shader
	texture.InitializeTexture("..\\res\\bricks.jpg"); //load a texture

	camera.InitializeCamera(glm::vec3(0, 0, -5), 70.0f, (float) gameDisplay.GetWidth() / gameDisplay.GetHeight(), 0.01f, 1000.0f); //initializes the camera
}

void Game::GameLoop()
{
	while (gameState == GameState::PLAYING)
	{
		ProcessUserInputs();
		UpdateDisplay();

		DetectCollision(); //TODO:
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
	gameDisplay.ClearDisplay(0.0f, 0.0f, 0.0f, 1.0f); //clear the display

	transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 2, 0.0));
	transform.SetScale(glm::vec3(1.0, 1.0, 1.0));

	shader.UseShader();
	shader.UpdateTransform(transform, camera);
	texture.UseTexture(0);

	mesh1.Display();
	mesh1.UpdateSphereData(*transform.GetPos(), 0.62f);

	mesh2.Display();
	mesh2.UpdateSphereData(*transform.GetPos(), 0.62f);

	counter = counter + 0.01f;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameDisplay.ChangeBuffer(); //swap the buffers
}

//TODO: rename
bool Game::DetectCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x) * (m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z) * (m2Pos.z - m1Pos.z)); //pythagoras

	if (distance < (m1Rad + m2Rad)) //TODO: check what happens if you remove the sqrt and multiply this distance by itself
	{
		cout << distance << '\n';
		return true;
	}
	else
	{
		return false;
	}
}