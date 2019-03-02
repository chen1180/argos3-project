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
#include "camera.h"

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
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastXpos = window_width / 2.0;
float lastYpos = window_height / 2.0;
bool firstMouse = true;

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
    Shader light("shader/light.vert", "shader/light.frag");
    Texture marble_diffuse("/home/chen1180/Documents/renderer/pictures/Marble062/1K/Marble062_COL_1K.jpg");
    Texture marble_specular("/home/chen1180/Documents/renderer/pictures/Marble062/1K/Marble062_REFL_1K.jpg");
    float points[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};
    glm::vec3 lightPosition[] = {
        glm::vec3(2.0f, 3.0f, 5.0f),
        glm::vec3(5.0f, 6.0f, -15.0f),
        glm::vec3(1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, 2.0f, -12.3f)};
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVBO, lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glBindVertexArray(lightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //Anti aliasing activation
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);
    while (!glfwWindowShouldClose(window))
    {
        //window title text
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        input_callback(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 lightPos(5.0 * cos(glfwGetTime()), 0.0, 5.0 * sin(glfwGetTime()));
        shader.use();
        //material textures binding
        shader.setInt(0, "material.diffuse");
        shader.setInt(1, "material.specular");
        shader.setFloat(64.0, "material.shininess");
        marble_diffuse.activate(0);
        marble_specular.activate(1);
        //directional light
        shader.setVec3(glm::vec3(0.0, -1.0, 0.0), "directionLight.direction");
        shader.setVec3(glm::vec3(0.1, 0.1, 0.1), "directionLight.ambient");
        shader.setVec3(glm::vec3(0.8, 0.8, 0.8), "directionLight.diffuse");
        shader.setVec3(glm::vec3(1.0, 1.0, 1.0), "directionLight.specular");
        //point light
        for (int i = 0; i < 4; i++)
        {
            std::string num = std::to_string(i);
            shader.setVec3(lightPosition[i], ("pointLight[" + num + "].position").c_str());
            shader.setVec3(glm::vec3(0.2, 0.2, 0.2), ("pointLight[" + num + "].ambient").c_str());
            shader.setVec3(glm::vec3(0.8, 0.8, 0.8), ("pointLight[" + num + "].diffuse").c_str());
            shader.setVec3(glm::vec3(1.0, 1.0, 1.0), ("pointLight[" + num + "].specular").c_str());
            shader.setFloat(1.0, ("pointLight[" + num + "].constant").c_str());
            shader.setFloat(0.09, ("pointLight[" + num + "].linear").c_str());
            shader.setFloat(0.032, ("pointLight[" + num + "].quadratic").c_str());
        }
        //flash light
        shader.setVec3(camera.Pos, "flashLight.position");
        shader.setVec3(camera.Front, "flashLight.direction");
        shader.setVec3(glm::vec3(0.1, 0.1, 0.1), "flashLight.ambient");
        shader.setVec3(glm::vec3(0.5, 0.5, 0.5), "flashLight.diffuse");
        shader.setVec3(glm::vec3(0.8, 0.8, 0.8), "flashLight.specular");
        shader.setFloat(1.0, "flashLight.constant");
        shader.setFloat(0.09, "flashLight.linear");
        shader.setFloat(0.032, "flashLight.quadratic");
        shader.setFloat(glm::cos(glm::radians(15.0)), "flashLight.cutoff");
        shader.setFloat(glm::cos(glm::radians(20.0)), "flashLight.outerCutoff");
        //model view and projection
        glm::mat4 view;
        view = camera.getViewMatrix();
        glm::mat4 projection;
        projection = glm::perspective(camera.Zoom, (float)window_width / window_height, 0.1f, 100.0f);
        shader.setMat4(view, "view");
        shader.setMat4(projection, "projection");
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            shader.setMat4(model, "model");
            glDrawArrays(GL_TRIANGLES, 0, sizeof(points));
        }

        //draw light
        light.use();
        light.setMat4(view, "view");
        light.setMat4(projection, "projection");
        for (int i = 0; i < 4; i++)
        {
            glm::mat4 model;
            model = glm::translate(model, lightPosition[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            light.setMat4(model, "model");
            glBindVertexArray(lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, sizeof(points));
        }

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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
void mousebutton_callback(GLFWwindow *window, int x, int y, int z)
{
}
void scroll_callback(GLFWwindow *window, double x, double y)
{
    camera.ProcessMouseScroll(y);
}
void cursorPos_callback(GLFWwindow *window, double x, double y)
{
    if (firstMouse)
    {
        lastXpos = x;
        lastYpos = y;
        firstMouse = false;
    }
    float xoffset = x - lastXpos;
    float yoffset = lastYpos - y;
    lastXpos = x;
    lastYpos = y;
    camera.ProcessMouseMovement(xoffset, yoffset, true);
}