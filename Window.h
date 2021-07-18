#pragma once

#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	~Window();

	int Initialize();
	GLfloat GetBufferWidth() { return bufferWidth; }
	GLfloat GetBufferHeight() { return bufferHeight; }
	bool GetShouldClose() { return glfwWindowShouldClose(mainWindow); }
	void SwapBuffers() { glfwSwapBuffers(mainWindow); }
	bool* getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	

private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;
	bool keys[1024];//range of ASCII characters
	// Last mouse coordinates
	GLfloat lastX = 0.0f;
	GLfloat lastY = 0.0f;
	// Change in the mouse position subtracting the current coordinates by the previous coordinates
	GLfloat xChange = 0.0f;
	GLfloat yChange = 0.0f;
	// Mouse first movement
	bool mouseInitialMovement = true;

	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	void createCallbacks();
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

