#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"../headers/stb_image.h"
#include"../headers/shader.h"
#include"../headers/vao.h"
#include"../headers/vbo.h"
#include"../headers/ebo.h"
#include"../headers/texture.h"
#include"../headers/camera.h"
#include <cmath>

const char* vertex_shader_path = "res/shaders/default.vert";
const char* fragment_shader_path = "res/shaders/default.frag";

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "learnopengl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), 0.05f);
	
	// Generates Vertex Array Object and binds it
	VAO VAO1; 
	VAO1.Bind();

	// Add VBO, EBO, and attributes to current VAO
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram(vertex_shader_path, fragment_shader_path);

	// Load textures
	Texture t0("res/textures/container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE, GL_REPEAT);
	Texture t1("res/textures/happy.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE, GL_REPEAT);

	// Get uniforms from shader file into this program
	int tex0uid = glGetUniformLocation(shaderProgram.ID, "tex0");
	int tex1uid = glGetUniformLocation(shaderProgram.ID, "tex1");
	int mixtureuid = glGetUniformLocation(shaderProgram.ID, "mixtureFactor");
	
	// Sets the values of the uniforms (shader must be bound first)
	shaderProgram.Bind();
	glUniform1i(tex0uid, 0);
	glUniform1i(tex1uid, 1);
	glUniform1f(mixtureuid, 0.5f);

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	shaderProgram.Delete();	

	glEnable(GL_DEPTH_TEST);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Link the current object to draw + textures + shader
		shaderProgram.Bind();
		t0.Bind();
		t1.Bind();
		VAO1.Bind();

		// Link inputs to cam
		camera.linkInput(window);

		// Updates and links the camera matrix to the vertex shader
		camera.setMatrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}