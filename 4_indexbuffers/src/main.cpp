#include<iostream>
#include <cmath>
#include<fstream>
#include<string>
#include<sstream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
using namespace std;

unsigned int shaderProgram;
const int NumObjects = 1;
unsigned int vBufferIds[NumObjects]; 
unsigned int vArrayIds[NumObjects];
unsigned int iBufferIds[NumObjects];


struct ShaderProgramSource{
    string VertexSource;
    string FragmentSource;
};

static ShaderProgramSource parseShadersSources(const string& fpath){
    ifstream stream(fpath);

    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream,line)){
        // If you see shader hash heading
        if (line.find("#shader") != string::npos){
            if (line.find("vertex") != string::npos){
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != string::npos){
                type = ShaderType::FRAGMENT;
            }
        }
        else{
            ss[(int)type] << line << endl;
        }
    }
    return {ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const string& source){
     unsigned int id = glCreateShader(type);
     const char* src = source.c_str();
     glShaderSource(id, 1, &src, nullptr);
     glCompileShader(id);

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

void setupShaders(){
    ShaderProgramSource s = parseShadersSources("res/shaders/basic.shader");
    shaderProgram = CreateShaderProgram(s.VertexSource, s.FragmentSource);
}

void setupGeometries(){
    
    // Object zero, generate ID for 0th index
    glGenVertexArrays(NumObjects, &vArrayIds[0]);
    glGenBuffers(NumObjects, &vBufferIds[0]);
    glGenBuffers(NumObjects, &iBufferIds[0]);


    // OBJECT 1 (a square)
    GLfloat vertices[] = {
        -0.5f, -0.5f, //0
        0.5f, -0.5f, // 1
        0.5f, 0.5f, // 2
        -0.5f, 0.5f, //3
    };

    // This allows us to reuse vertices instead of reduplicating
    // BTW: Must be unsigned (positive only)
    unsigned int indices[] = {
        0, 1, 2,        // triangle 1 (face 1)
        2, 3, 0,        // triangle 2 (face 2)
    };

    // 0th vertex array
    glBindVertexArray(vArrayIds[0]); 

    // 0th vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vBufferIds[0]); // Current vBufferIds index working in is 0th
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Make the buffer

    // 0th index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferIds[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ATTRIBUTES OF OBJ 1's VERTICES, binds to vertex array
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

}

void renderScene() {

	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);

    glBindVertexArray(vArrayIds[0]); // Triangles object at vArrayIds index 0

    // MODE, #INDICES
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    // glDrawArrays(GL_TRIANGLES, 0, 6); We are using index buffer so dont use this
    
    glBindVertexArray(0);       // Unbind not necessary, but a good idea
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


    setupGeometries();
    setupShaders();
    

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
        renderScene();

        glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}