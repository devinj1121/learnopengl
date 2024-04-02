#include<iostream>
#include <cmath>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
using namespace std;


string vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec4 position;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = position;\n"
    "}\0";
    
string fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "   color = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
    "}\n\0";


GLfloat vertices[] = {
    -0.5f, -0.5f, //v1, a1=(-0.5f,-0.5f) (could have more attributes, but just one)
    0.5f, 0.5f, // v2
    0.5f, -0.5f //v3
};

static unsigned int CompileShader(unsigned int type, const string& source){
     unsigned int id = glCreateShader(type);
     const char* src = source.c_str();
     glShaderSource(id, 1, &src, nullptr);
     glCompileShader(id);

    // TODO: Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE){
        int length;
        cout << "Shader didn't compile" << endl;
        glDeleteShader(id);
        return 0;
    }

     return(id);
}

static unsigned int CreateShaderProgram(const string& vertexShaderSource, const string& fragmentShaderSource){
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // Linked to program, so can delete
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{

    /* 
        Initalize window
    */
	glfwInit();   // GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Modern funcs only

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL(); // GLAD
	glViewport(0, 0, 800, 800);
    

    // Have to make a VAO too, but we'll do more later.
    unsigned int VAO; 
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);

    /* 
        Make/choose my current buffer (object)
    */
    // Buffer details
    unsigned int VBO; // This will hold the IDs of the buffer objects (just 1 in this case)
    glGenBuffers(1, &VBO); // Generates 1 ID, stores in array at &VBO (i.e., size 1)
    
    // Give an array buffer to VRAM, ID=VBO
    // This is current buffer until deselecting!
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 

    // Copy vertices data onto current buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    // Tell the GPU the layout of the data for the current buffer
    // Give this attribute index of 0
    // Attribute has 2 components of type float, normalized already
    // Attributes per vertex are spaced by 2 floats
    // Pointer = Offset to get to that attribute within that vertex
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);
    glEnableVertexAttribArray(0);





    unsigned int shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shaderProgram);


	// Main loop
	while (!glfwWindowShouldClose(window))
	{
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3); // Current buffer has 3 vertices

        glfwSwapBuffers(window);

		glfwPollEvents();
	}

    glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}