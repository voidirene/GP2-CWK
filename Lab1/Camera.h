#pragma once
#include "ScreenDisplay.h"
#include <glfw3.h>
#include "glm/ext.hpp" //TODO: remove this
#include <iostream> //TODO: remove this
#include <glm/gtx/vector_angle.hpp>

struct Camera
{
public:

	Camera()
	{

	}
	//TODO: destructor?

	void InitializeCamera(const glm::vec3& position, float fov, float aspectRatio, float nearClip, float farClip)
	{
		this->cameraPosition = position;
		this->forwardVector = glm::vec3(0.0f, 0.0f, 1.0f);
		this->upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projectionMatrix = glm::perspective(fov, aspectRatio, nearClip, farClip);
	}

	inline glm::mat4 GetViewProjection() const //creates projection matrix
	{
		return projectionMatrix * glm::lookAt(cameraPosition, cameraPosition + forwardVector, upVector);
	}

	void MouseControls(ScreenDisplay* display)
	{
		glfwSetInputMode(display->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		std::cout << glm::to_string(GetForward());
		if (glfwGetMouseButton(display->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glfwSetInputMode(display->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); //hide cursor

			// Prevents camera from jumping on the first click
			if (firstClick)
			{
				glfwSetCursorPos(display->window, (display->GetWidth() / 2), (display->GetHeight() / 2));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double x;
			double y;
			// Fetches the coordinates of the cursor
			glfwGetCursorPos(display->window, &x, &y);

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "transforms" them into degrees 
			float rotX = 10 * (float)(y - (display->GetHeight() / 2)) / display->GetHeight();
			float rotY = 10 * (float)(x - (display->GetWidth() / 2)) / display->GetWidth();

			// Calculates upcoming vertical change in the Orientation
			glm::vec3 forwardNew = glm::rotate(forwardVector, glm::radians(-rotX), glm::normalize(glm::cross(forwardVector, upVector)));

			// Decides whether or not the next vertical Orientation is legal or not
			if (abs(glm::angle(forwardNew, upVector) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				forwardVector = forwardNew;
			}

			// Rotates the Orientation left and right
			forwardVector = glm::rotate(forwardVector, glm::radians(-rotY), upVector);

			// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			glfwSetCursorPos(display->window, (display->GetWidth() / 2), (display->GetHeight() / 2));
		}
		else if (glfwGetMouseButton(display->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(display->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			firstClick = true;
		}
	}


	void MoveCameraHorizontally(int direction)
	{
		cameraPosition.x += 1 * direction;
	}

	void MoveCameraVertically(int direction)
	{
		cameraPosition.y += 1 * direction;
	}

	glm::vec3 GetPosition() { return cameraPosition; }
	glm::vec3 GetForward() { return forwardVector; }
	glm::vec3 GetUp() { return upVector; }
	bool firstClick = true;

private:

	glm::vec3 cameraPosition;
	glm::mat4 projectionMatrix;
	glm::vec3 forwardVector;
	glm::vec3 upVector;
};
