#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

class Texture
{
  public:
    unsigned int ID;
    Texture(const char *filePath)
    {
        load(filePath);
    }
    void activate(unsigned int textureIndex)
    {
        glActiveTexture(GL_TEXTURE0 + textureIndex);
        glBindTexture(GL_TEXTURE_2D, ID);
    }

  private:
    void load(const char *filePath)
    {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannel;
        unsigned char *data = stbi_load(filePath, &width, &height, &nrChannel, 0);
        if (data)
        {
            switch (nrChannel)
            {
            case 1:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_R8, GL_UNSIGNED_BYTE, data);
                break;
            case 2:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
                break;
            case 3:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                break;
            case 4:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                break;
            default:
                std::cout << "Unknown channel numbers!" << std::endl;
            }
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Unable to load Image texture" << std::endl;
        }
        stbi_image_free(data);
    }
};
#endif