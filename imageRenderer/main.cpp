#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.h"
#include <cmath>
#include "texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

int window_width = 800;
int window_height = 600;
void framebuffer_callback(GLFWwindow *window, int x, int y);
void input_callback(GLFWwindow *window);
void mousebutton_callback(GLFWwindow *window, int x, int y, int z);
void scroll_callback(GLFWwindow *window, double x, double y);
void cursorPos_callback(GLFWwindow *window, double x, double y);
float val = 0;
int idx = 0;
float alpha = 0.0;
int nrPictures = 3;
float scale = 1.0;
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, "window", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Window is not open!!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_callback);
    glfwSetMouseButtonCallback(window, mousebutton_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursorPos_callback);
    if ((!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize glad!!" << std::endl;
        return -1;
    }
    Shader shader("shader/vertexShader.vert", "shader/fragShader.frag");
    shader.use();
    Texture texture1("/home/chen1180/Documents/renderer/pictures/Witcher3.jpg");
    Texture texture2("/home/chen1180/Documents/renderer/pictures/frog.png");
    Texture texture3("/home/chen1180/Documents/renderer/pictures/wall.jpg");
    float points[] = {
        -1.0, -1.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0,
        1.0, -1.0, 0.0, 0.0, 0.0, 0.5, 1.0, 0.0,
        1.0, 1.0, 0.0, 0.5, 0.0, 0.0, 1.0, 1.0,
        -1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    shader.use();
    shader.setInt(0, "texture1");
    shader.setInt(1, "texture2");
    shader.setInt(2, "texture3");

    while (!glfwWindowShouldClose(window))
    {
        input_callback(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        switch (idx)
        {
        case 0:
            glBindTexture(GL_TEXTURE_2D, 0);
            texture1.use(0);
            break;
        case 1:
            glBindTexture(GL_TEXTURE_2D, 0);
            texture2.use(1);
            break;
        case 2:
            glBindTexture(GL_TEXTURE_2D, 0);
            texture3.use(2);
            break;
        default:
            glBindTexture(GL_TEXTURE_2D, 0);
            texture3.use(2);
        }
        shader.setFloat(val, "val");
        shader.setFloat(alpha, "alpha");
        glm::mat4 trans;
        //trans = glm::rotate(trans, (float)(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(scale));
        shader.setMat4(trans, "trans");
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
void framebuffer_callback(GLFWwindow *window, int x, int y)
{
    glViewport(0, 0, x, y);
}
void input_callback(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (alpha <= 1.0)
            alpha += 0.01;
        else
            alpha = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (alpha >= 0.0)
            alpha -= 0.01;
        else
            alpha = 0.0;
    }
}
void mousebutton_callback(GLFWwindow *window, int x, int y, int z)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        if (idx < nrPictures)
            idx++;
        else
            idx = nrPictures;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        if (idx > 0)
            idx--;
        else
            idx = 0;
}
void scroll_callback(GLFWwindow *window, double x, double y)
{
    if (y > 0)
        scale += 0.01;
    if (y < 0)
        scale -= 0.01;
}
void cursorPos_callback(GLFWwindow *window, double x, double y)
{
    //glfwGetCursorPos(window,&x,&y);
    std::cout << '(' << x << ',' << y << ')' << std::endl;
}