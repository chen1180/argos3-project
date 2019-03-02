#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Shader
{
  public:
    unsigned int ID;
    Shader(const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath)
    {
        std::string vertexShader, fragmentShader;
        std::ifstream vertexShaderFile, fragmentShaderFile;
        vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vertexShaderFile.open(vertexShaderPath);
            fragmentShaderFile.open(fragmentShaderPath);
            std::stringstream vShader, fShader;
            vShader << vertexShaderFile.rdbuf();
            fShader << fragmentShaderFile.rdbuf();
            vertexShaderFile.close();
            fragmentShaderFile.close();

            vertexShader = vShader.str();
            fragmentShader = fShader.str();
        }
        catch (std::fstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READED!!!" << std::endl;
        }
        const char *vShaderCode = vertexShader.c_str();
        const char *fShaderCode = fragmentShader.c_str();
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    void use()
    {
        glUseProgram(ID);
    }
    void setFloat(float val, const char *uniformName)
    {
        glUniform1f(glGetUniformLocation(ID, uniformName), val);
    }
    void setInt(int val, const char *uniformName)
    {
        glUniform1i(glGetUniformLocation(ID, uniformName), val);
    }
    void setMat4(glm::mat4 val, const char *uniformName)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, uniformName),1,GL_FALSE,glm::value_ptr(val));
    }
};
#endif