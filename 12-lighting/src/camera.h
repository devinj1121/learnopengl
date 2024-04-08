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

class Camera{
    public:
        glm::vec3 eye = glm::vec3(0.0f, 0.0f, 0.0f); //sits at origin
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f); // faces -z
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // up = pos y

        int width;
        int height;
        bool firstClick = true;

        Camera(int width, int height);

        void setMatrix(Shader& shader, glm::mat4 matrix, const char* uniform);
        void handleInput(GLFWwindow* window);
};