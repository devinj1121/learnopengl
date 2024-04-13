#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include "../include/stb/stb_image.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "camera.h"
#include "model.h"

const unsigned int width = 800;
const unsigned int height = 800;


int main()
{

	// Initialize
    // ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 800, "learnopengl", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	stbi_set_flip_vertically_on_load(true);
	
	// Camera, shader, model
    // ------------------------------
	Camera camera(width,height);
	Shader defaultShader("res/shaders/default.vert", "res/shaders/default.frag");
	Model m1("res/objects/backpack/backpack.obj", false);
	Model m2("res/objects/male/male.obj", false);


	// Main loop (think of in order of dependencies)
    // ------------------------------
	while (!glfwWindowShouldClose(window))
	{
		// Depend on nothing
		camera.handleInput(window);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		defaultShader.Activate();

		glm::mat4 view, projection = glm::mat4(1.0f);
		view = glm::lookAt(camera.eye, camera.direction, camera.up);
		projection = glm::perspective(glm::radians(45.0f), (float)(camera.width / camera.height), 0.1f, 100.0f);
		camera.setMatrix(defaultShader, view, "view");
		camera.setMatrix(defaultShader, projection, "projection");
		
		// Draw model2 (depend on user input)
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01f, 0.01f, 0.01f));
		// std::cout << glm::to_string(modelMatrix) << std::endl;
		m2.setMatrix(defaultShader, modelMatrix, "model");
		m2.Draw(defaultShader); // Draw all the meshes (VAOs) of this model using the shader, while applying the model matrix

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}