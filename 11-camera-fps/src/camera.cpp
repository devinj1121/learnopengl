#include "../headers/camera.h"
#include <glm/gtx/string_cast.hpp>

Camera::Camera(int width, int height)
{
	Camera::width = width;
	Camera::height = height;
}

void Camera::setMatrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Defining a camera transform whose inverse is used to be the view matrix.
	// lookAt is just a convenience function to do all this for us.
	view = glm::lookAt(eye, direction, up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::linkInput(GLFWwindow* window){

	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		eye.z -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		eye.x -= 0.01f;
		direction.x -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		eye.z += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		eye.x += 0.01f;
		direction.x += 0.01f;
	}	

	double mouseX;
	double mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// Mouse coords are defined by window (top left = 0,0), positive y is downward on screen
	direction.x = (float)(mouseX - (width / 2)) / width;
	direction.y = -((float)(mouseY - (height / 2)) / height);
	
}