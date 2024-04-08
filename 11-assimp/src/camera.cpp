#include "camera.h"

Camera::Camera(int width, int height)
{
	Camera::width = width;
	Camera::height = height;
}

void Camera::setView(Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(eye, direction, up);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(view));
	
}

void Camera::setProjection(Shader& shader, const char* uniform, float fov, float near, float far)
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(fov), (float)width / height, near, far);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection));
	
}


void Camera::handleInput(GLFWwindow* window){

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
			exit(0);
	}

	double mouseX;
	double mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// Mouse coords are defined by window (top left = 0,0), positive y is downward on screen
	direction.x = (float)(mouseX - (width / 2)) / width;
	direction.y = -((float)(mouseY - (height / 2)) / height);
	
}