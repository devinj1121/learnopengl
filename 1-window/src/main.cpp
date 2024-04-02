#include<iostream>

// This points to actual GPU driver functions (like GLEW)
#include<glad/glad.h> 

// This library sets up window for OpenGL
// This is the more modern option for the old "GLUT"
#include<GLFW/glfw3.h> 


/// @brief Resizes the window
/// @param window Pointer to window
/// @param width Width of window in pixels
/// @param height Height of window in pixels
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

/// @brief Handle the input keys
/// @param window 
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void initialize(){
    
}

int main(){

    // Initializing GLFW
    
    // Init glfw
    glfwInit();
    
    // Version of glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Core profile ~ "Modern"
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   

   // Creating the window
   GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Make the window our main context


    // Initializing GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 

    glViewport(0, 0, 800, 600); // {lower left x}{lower left y}{width}{height}
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // Window resize callback

    // Render loop
    while(!glfwWindowShouldClose(window)){
        
        // input
        processInput(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Check and call events and swap buffers
        glfwPollEvents();    
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
    
}