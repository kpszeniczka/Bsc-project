#include "glad/glad.h"
#include "Usegui.h"
#include <iostream>

bool dragging = false;
double lastX, lastY;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        if (action == GLFW_PRESS) {
            dragging = true;
            glfwGetCursorPos(window, &lastX, &lastY);
        }
        else if (action == GLFW_RELEASE) {
            dragging = false;
        }
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (dragging) {
        int windowX, windowY;
        glfwGetWindowPos(window, &windowX, &windowY);
        int deltaX = static_cast<int>(xpos - lastX);
        int deltaY = static_cast<int>(ypos - lastY);
        glfwSetWindowPos(window, windowX + deltaX, windowY + deltaY);
    }
}

void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Proste Okno ImGui", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    UseGui mygui;
    mygui.Init(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        mygui.NewFrame();
        mygui.MainGui(window);
        mygui.Render();
        glfwSwapBuffers(window);
    }
    
    mygui.Shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
