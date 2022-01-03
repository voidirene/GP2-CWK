#include "Game.h"

//unsigned int indices[] = { 0, 1, 2 };

Game::Game()
{
	gameState = GameState::PLAYING; //set the game state to PLAYING
	gameDisplay = new ScreenDisplay(); //create a new display

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
	std::cout << text << '\n';
	std::cout << "Press any  key to exit the app.";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void Game::InitializeSystems()
{
	gameDisplay->InitializeDisplay(); //initializes the game display

	mesh1.LoadModel("..\\res\\monkey3.obj"); //loads a mesh from file
	mesh2.LoadModel("..\\res\\teapot.obj");
	mesh3.LoadModel("..\\res\\capsule.obj");
	shader.InitializeShader("..\\res\\shader"); //create a new shader
	//texture.InitializeTexture("..\\res\\bricks.jpg"); //load a texture
	//texture.InitializeTexture("..\\res\\water.jpg");
	//texture.InitializeTexture("..\\res\\grass.jpg");
	texture.InitializeAllTextures();

	camera.InitializeCamera(glm::vec3(0, 0, -5), 70.0f, (float) gameDisplay->GetWidth() / gameDisplay->GetHeight(), 0.01f, 1000.0f); //initializes the camera

	audio.AddNewSound("..\\res\\bang.wav");
	audio.AddNewBackgroundMusic("..\\res\\background.wav");
}

void Game::GameLoop()
{
	while (gameState == GameState::PLAYING)
	{
		audio.PlayBackgroundMusic();
		ProcessUserInputs();
		UpdateDisplay();

		DetectCollision(mesh1.boundingSphere.GetPosition(), mesh1.boundingSphere.GetRadius(), mesh2.boundingSphere.GetPosition(), mesh2.boundingSphere.GetRadius());
	}
}

void Game::ProcessUserInputs()
{
	glfwPollEvents(); //poll events

	//for quitting the game
	if (glfwGetKey(gameDisplay->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		gameState = GameState::QUITTING;
		return;
	}

	//for keyboard camera movement
	if (glfwGetKey(gameDisplay->window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera.MoveCameraVertically(1);
	}
	if (glfwGetKey(gameDisplay->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera.MoveCameraVertically(-1);
	}
	if (glfwGetKey(gameDisplay->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.MoveCameraHorizontally(1);
	}
	if (glfwGetKey(gameDisplay->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.MoveCameraHorizontally(-1);
	}
	if (glfwGetKey(gameDisplay->window, GLFW_KEY_EQUAL) == GLFW_PRESS)
	{
		camera.ZoomCamera(1);
	}
	if (glfwGetKey(gameDisplay->window, GLFW_KEY_MINUS) == GLFW_PRESS)
	{
		camera.ZoomCamera(-1);
	}

	//camera mouse input
	camera.MouseControls(gameDisplay);
}

//TODO: should this be in the ScreenDisplay class instead? setting the transform and such shouldn't be in in UpdateDisplay
void Game::UpdateDisplay()
{
	gameDisplay->ClearDisplay(0.0f, 0.0f, 0.0f, 1.0f); //clear the display

	//MESH1
	transform.SetPos(glm::vec3(-1.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(counter * 1, 0.0, 0.0));
	transform.SetScale(glm::vec3(1.0, 1.0, 1.0));

	shader.UseShader();
	shader.UpdateTransform(transform, camera);
	//texture.UseTexture(0);
	texture.UseSpecificTexture(0);

	mesh1.Display();
	mesh1.UpdateSphereData(*transform.GetPos(), 0.62f);

	//MESH2
	transform.SetPos(glm::vec3(0.0, sinf(counter) * 3, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(0.1, 0.1, 0.1));

	shader.UpdateTransform(transform, camera);
	//texture.UseTexture(1);
	texture.UseSpecificTexture(1);

	mesh2.Display();
	mesh2.UpdateSphereData(*transform.GetPos(), 0.62f);

	//MESH3
	transform.SetPos(glm::vec3(3.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 1, 0.0));
	transform.SetScale(glm::vec3(1.0, 1.0, 1.0));

	shader.UpdateTransform(transform, camera);
	//texture.UseTexture(2);
	texture.UseSpecificTexture(2);

	mesh3.Display();
	mesh3.UpdateSphereData(*transform.GetPos(), 0.62f);

	counter = counter + 0.01f;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	gameDisplay->ChangeBuffer(); //swap the buffers

	/*ideally this should look like
		clear display
		draw object1
		draw object2
		swap buffer*/
}

bool Game::DetectCollision(glm::vec3 position1, float radius1, glm::vec3 position2, float radius2)
{
	float distance = glm::sqrt((position2.x - position1.x) * (position2.x - position1.x) + (position2.y - position1.y) * (position2.y - position1.y) + (position2.z - position1.z) * (position2.z - position1.z)); //pythagoras

	if (distance < (radius1 + radius2))
	{
		cout << "collision! : " << distance << '\n';
		audio.PlaySound(0); //plays a sound if sound isn't already playing
		return true;
	}
	else
	{
		cout << "NO collision! : " << distance << '\n';
		return false;
	}
}