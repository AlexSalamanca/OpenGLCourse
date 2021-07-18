#include "Window.h"


Window::Window() {
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = false;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight) {
	width = windowWidth;
	height = windowHeight;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = false;
	}
}

Window::~Window() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

int Window::Initialize() {
	// Inititalize GLFW
	if (!glfwInit()) {
		std::cout << "GLFW initialization failed" << std::endl;
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No backward compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow) {
		std::cout << "Window creation failed" << std::endl;
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Handle key + mouse input
	createCallbacks();
	// Make the cursor invisible
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern externsions features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialization failed" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* window_reference = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) window_reference->keys[key] = true;
		else if (action == GLFW_RELEASE) window_reference->keys[key] = false;
	}
}

void Window::createCallbacks() {
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {
	Window* window_reference = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (window_reference->mouseInitialMovement) {
		window_reference->lastX = xPos;
		window_reference->lastY = yPos;
		window_reference->mouseInitialMovement = false;
	}

	window_reference->xChange = xPos - window_reference->lastX;
	window_reference->yChange = window_reference->lastY - yPos; // different order to prevent inverted movement

	window_reference->lastX = xPos;
	window_reference->lastY = yPos;
}

GLfloat Window::getXChange() {
	GLfloat change = xChange;
	xChange = 0.0f;
	return change;
}

GLfloat Window::getYChange() {
	GLfloat change = yChange;
	yChange = 0.0f;
	return change;
}