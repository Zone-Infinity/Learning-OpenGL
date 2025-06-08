#include "camera.h"

Camera::Camera(int width, int height, vec3 position, vec3 orientation) {
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
    Camera::orientation = orientation;
}

void Camera::updateMatrix(float fovDeg, float nearPlane, float farPlane) {
    mat4 view = mat4(1.0f);
    mat4 projection = mat4(1.0f);

    view = lookAt(position, position + orientation, up);
    projection = perspective(radians(fovDeg), (float) (width / height), nearPlane, farPlane);

    camMatrix = projection * view;
}

void Camera::matrix(Shader &shader, const char *uniform) {
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, value_ptr(camMatrix));
}


void Camera::handleInput(GLFWwindow *window) {
    // Handles key inputs
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        std::cout << "POS: " << position.x << " " << position.y << " " << position.z << std::endl;
        std::cout << "ORIENTATION: " << orientation.x << " " << orientation.y << " " << orientation.z << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += speed * orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position += speed * -normalize(cross(orientation, up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position += speed * -orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += speed * normalize(cross(orientation, up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += speed * up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position += speed * -up;
    }

    // Handles mouse inputs
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Hides mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Prevents camera from jumping on the first click
        if (firstClick) {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        // Stores the coordinates of the cursor
        double mouseX;
        double mouseY;
        // Fetches the coordinates of the cursor
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
        // and then "transforms" them into degrees
        float rotX = sensitivity * (float) (mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float) (mouseX - (width / 2)) / width;

        // Calculates upcoming vertical change in the orientation
        vec3 newOrientation = rotate(orientation, radians(-rotX), normalize(cross(orientation, up)));

        // Decides whether or not the next vertical orientation is legal or not
        if (abs(angle(newOrientation, up) - radians(90.0f)) <= radians(85.0f)) {
            orientation = newOrientation;
        }

        orientation = rotate(orientation, radians(-rotY), up);

        glfwSetCursorPos(window, (width / 2), (height / 2));
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
