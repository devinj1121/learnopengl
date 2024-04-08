#include "../headers/texture.h"
#include "../headers/stb_image.h"   

    
    Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType, GLenum wrapType)
    {
        int widthImg, heightImg, numColCh;

        stbi_set_flip_vertically_on_load(true);
        this->texType = texType;
        this->slot = slot;
        unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
        
        // Generates an OpenGL texture object, binds to slot given
        glGenTextures(1, &ID);
        glActiveTexture(slot);
        glBindTexture(texType, ID);

        // Configures the type of algorithm that is used to make the image smaller or bigger
        glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Configures the way the texture repeats (if it does at all)
        glTexParameteri(texType, GL_TEXTURE_WRAP_S, wrapType);
        glTexParameteri(texType, GL_TEXTURE_WRAP_T, wrapType);

        if (wrapType == GL_CLAMP_TO_BORDER){
            float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
        }

        // Assigns the image to the OpenGL Texture object
        glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
       
        // Generates MipMaps
        glGenerateMipmap(texType);

        // Deletes the image data as it is already in the OpenGL Texture object
        stbi_image_free(bytes);

        // Unbinds the OpenGL Texture object so that it can't accidentally be modified
        glBindTexture(texType, 0);

    }
    
    Texture::~Texture(){
        glDeleteTextures(1, &ID);

    }

    void Texture::Bind(){
        glActiveTexture(slot);
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    void Texture::Unbind(){
        glBindTexture(GL_TEXTURE_2D, 0);
    }