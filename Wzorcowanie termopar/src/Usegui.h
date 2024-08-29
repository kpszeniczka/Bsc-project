#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "math.h"
#include "GLFW/glfw3.h"

class UseGui {
public:
	void Init(GLFWwindow* window);
	void NewFrame();
	virtual void MainGui(GLFWwindow* window);
	void Render();
	void Shutdown();
};