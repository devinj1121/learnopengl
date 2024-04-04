#pragma once

#include <glad/glad.h>

class Texture{

    public:
        GLuint ID;
        GLenum texType;
        unsigned int slot;
        int width, height, BPP;

        Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType,GLenum wrapType);
        ~Texture();

        void Bind();
        void Unbind();
};