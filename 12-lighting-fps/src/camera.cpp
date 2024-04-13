#include "camera.h"

Camera::Camera(int width, int height)
{
	Camera::width = width;
	Camera::height = height;
}


void Camera::setMatrix(Shader& shader, glm::mat4 matrix, const char* uniform){
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
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
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		eye.y += 0.01f;
		direction.y += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		eye.y -= 0.01f;
		direction.y -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
			exit(0);
	}
}