#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

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

	void MoveCameraHorizontally(int direction)
	{
		cameraPosition.x += 1 * direction;
	}

	void MoveCameraVertically(int direction)
	{
		cameraPosition.y += 1 * direction;
	}

private:

	glm::vec3 cameraPosition;
	glm::mat4 projectionMatrix;
	glm::vec3 forwardVector;
	glm::vec3 upVector;
};
