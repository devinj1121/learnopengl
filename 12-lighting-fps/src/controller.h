#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include<glm/gtx/string_cast.hpp>

#include "shader.h"

// template <typename T> how do i get the generic working?

class Controller{
     private:
        glm::mat4 view;
        glm::mat4 projection;
        glm::vec3 eye = glm::vec3(0,0,5); 
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f); // faces -z
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // up = pos y

        Shader shader;

        float horizontalAngle = 3.14f;
        float verticalAngle = 0.0f;
        float fov = 45.0f;
        float speed = 3.0f;
        float mouseSpeed = 0.005f;

    public:
        Controller();
        void setUniform(T value, const char* uniform);
        void Poll(GLFWwindow* window);
       
};