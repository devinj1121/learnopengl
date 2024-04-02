#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../headers/Renderer.h"
#include "../headers/VertexBuffer.h"
#include "../headers/IndexBuffer.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static struct ShaderProgramSource ParseShader(const std::string& filepath)
{
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // Error handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader compile status: " << result << std::endl;
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout 
            << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << "shader"
            << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // create a shader program
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program));

    GLint program_linked;

    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &program_linked));
    std::cout << "Program link status: " << program_linked << std::endl;
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        GLCall(glGetProgramInfoLog(program, 1024, &log_length, message));
        std::cout << "Failed to link program" << std::endl;
        std::cout << message << std::endl;
    }

    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

int main(void)
{
    /////////////////////////////////////
    /// Setup Window
    ////////////////////////////////////
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
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	gladLoadGL(); // GLAD
	glViewport(0, 0, 800, 800);


    /////////////////////////////////////
    /// Meshes
    ////////////////////////////////////

    //// Mesh 1
    float vertices[] = {
        -0.5f, -0.5f, // 0
        0.5f, -0.5f, // 1
        0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // VAO (everything we do with VBOS and IBOs below will apply to this VAO until we unbind it.)
    // A VAO says "use this data/data layout", usually 1-1 with meshes.
    unsigned int VAO;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));

    // Make a vertex buffer, binds to current VAO above
    VertexBuffer vb(vertices, sizeof(vertices));

    // Layout of 0th attribute (the only attribute we have)
    // This attaches to bound VBO
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
    
    // Index Buffer, binds to current VAO
    IndexBuffer ib(indices, 6);

    // Unbind the VAO, VBO, IBO, and attribute arrays (clear the machine state)
    // We can rebind them later by using bind on the objects.
    GLCall(glBindVertexArray(0));
    GLCall(glDisableVertexAttribArray(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    /////////////////////////////////////
    /// Shader
    ////////////////////////////////////
    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader));
    GLCall(unsigned int u_Color = glGetUniformLocation(shader, "u_Color"));
    float red = 0.0f;
    float step = 0.05f;

    GLCall(glUseProgram(0));

    /////////////////////////////////////
    /// Main loop
    ////////////////////////////////////
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0){
        // Clear the screen
        GLCall(glClear(GL_COLOR_BUFFER_BIT);

        // set shader and set uniform color
        GLCall(glUseProgram(shader));
        GLCall(glUniform4f(u_Color, red, 0.3, 0.8, 1.0));

        // Instead of binding VBOs, attrib pointers, IBOs just bind VAO that we made
        // VAO includes all that info.
        GLCall(glBindVertexArray(VAO));

        // Draw
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)));

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        // increment red
        if (red < 0.0f || red > 1.0f)
            step *= -1.0;
        red += step;

    }

    // Cleanup
    GLCall(glDeleteVertexArrays(1, &VAO));
    GLCall(glDeleteProgram(shader));

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

