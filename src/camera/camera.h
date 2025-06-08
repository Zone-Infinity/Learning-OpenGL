#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "../shader/shader.h"

using namespace glm;

class Camera {
public:
    vec3 position{};
    vec3 orientation = vec3(0, 0, -1);
    vec3 up = vec3(0, 1, 0);
    mat4 camMatrix = mat4(1.0f);

    bool firstClick = true;

    int width;
    int height;

    float speed = 0.03f;
    float sensitivity = 100.0f;

    Camera(int width, int height, vec3 position, vec3 orientation);

    void updateMatrix(float fovDeg, float nearPlane, float farPlane);

    void matrix(Shader &shader, const char *uniform);

    void handleInput(GLFWwindow *window);
};

#endif
