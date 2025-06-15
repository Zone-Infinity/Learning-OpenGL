#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader/shader.h"
#include "object/EBO.h"
#include "object/VBO.h"
#include "object/VAO.h"
#include "texture/texture.h"
#include "camera/camera.h"

using namespace glm;

const unsigned int width = 800;
const unsigned int height = 800;

// // Vertices coordinates
// GLfloat vertices[] =
// { //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
// 	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
// 	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
// 	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
// 	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
//
// 	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
// 	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
// 	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side
//
// 	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
// 	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
// 	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
//
// 	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
// 	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
// 	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side
//
// 	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
// 	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
// 	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
// };
//
// // Indices for vertices order
// GLuint indices[] =
// {
// 	0, 1, 2, // Bottom side
// 	0, 2, 3, // Bottom side
// 	4, 6, 5, // Left side
// 	7, 9, 8, // Non-facing side
// 	10, 12, 11, // Right side
// 	13, 15, 14 // Facing side
// };

// Vertices coordinates
GLfloat vertices[] =
{
    //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
    -3.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -3.0f, 0.0f, -3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    3.0f, 0.0f, -3.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    3.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3
};

GLfloat lightVertices[] =
{
    //     COORDINATES     //
    -0.1f, -0.1f, 0.1f,
    -0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, 0.1f,
    -0.1f, 0.1f, 0.1f,
    -0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, 0.1f
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // Initialize GLFW
    glfwInit();

    // GLFW Version 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Using Core Profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac OS Shi

    GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Introduce the window as current context
    gladLoadGL(); // Load glad to configure OpenGL
    glViewport(0, 0, width, height);

    /////////////////////////
    Shader pyramidShader("resource/shaders/default.vert", "resource/shaders/default.frag");
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void *) 0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void *) (3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void *) (6 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 3, 2, GL_FLOAT, 11 * sizeof(float), (void *) (8 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    /////////////////////////

    ////////////////////////
    // Light Source
    Shader lightShader("resource/shaders/light.vert", "resource/shaders/light.frag");
    VAO lightVAO;
    lightVAO.Bind();

    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *) 0);

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();
    ////////////////////////

    // Coloring
    vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    ////////////////////////
    // Positioning
    vec3 camPos = vec3(0, 1, 1);

    vec3 lightPos = vec3(0, 0.75f, 0);
    mat4 lightModel = mat4(1.0f);

    lightModel = translate(lightModel, lightPos);

    vec3 pyramidPos = vec3(0.0f, 0.0f, 0.0f);
    mat4 pyramidModel = mat4(1.0f);

    pyramidModel = translate(pyramidModel, pyramidPos);
    ////////////////////////

    ////////////////////////
    // Uniforms
    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
                lightColor.w);

    pyramidShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(pyramidShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(pyramidShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
                lightColor.w);
    glUniform3f(glGetUniformLocation(pyramidShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    /////////////////////////

    // Texture
    Texture planks("./resource/textures/planks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    planks.texUnit(pyramidShader, "tex0", 0);
    Texture planksSpec("./resource/textures/planksSpec.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RED, GL_UNSIGNED_BYTE);
    planksSpec.texUnit(pyramidShader, "tex1", 1);

    // float rotation = 0.1f;
    // double previousTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    Camera camera = Camera(width, height, camPos, vec3(0, 0, -1));

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the back buffers and give background color to it

        // Camera
        camera.handleInput(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // Drawing Pyramid
        pyramidShader.Activate();
        glUniform3f(glGetUniformLocation(pyramidShader.ID, "camPos"), camera.position.x, camera.position.y,
                    camera.position.z);

        camera.matrix(pyramidShader, "camMatrix");
        planks.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        // Drawing Light Source
        lightShader.Activate();
        camera.matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window); // Swap the front and back buffer
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    planks.Delete();
    planksSpec.Delete();
    pyramidShader.Delete();
    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    lightShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
