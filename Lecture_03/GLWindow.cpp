#include "GLWindow.h"


GLWindow::GLWindow()
{
	width = 2400;
	height = 1600;
}

GLWindow::GLWindow(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}
int GLWindow::InitGLWindow()
{
	// Initialise GLFW
	if (!glfwInit())  //initializes OpenGL Window System
	{
		printf("GLFW initialisation failed!");
		glfwTerminate(); //terminate due to error
		return 1;
	}

	// Setup GLFW window properties and version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Major and minor version is 3.X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core Profile means No Backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 	// Allow Forward Compatbility

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Welcome to DESN3306!", NULL, NULL); // Create Main Window
	
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate(); //terminate due to error
		return 1;
	}
	// Get Buffer Size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight); //bufferwidth and bufferHeight is system dependent so, load them.
	glfwMakeContextCurrent(mainWindow); // Set mainWindow as context for GLEW
	glewExperimental = GL_TRUE; 	// Allow modern features

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);  //clear resources already allocated
		glfwTerminate();  //terminate due to error
		return 1;
	}

	glEnable(GL_DEPTH_TEST); 

	glViewport(0, 0, bufferWidth, bufferHeight); // Setup the Viewport dimension

	// Handle Keyboard and Mouse Inputs
	glfwSetKeyCallback(mainWindow, handleKeyboardKeys);

	glfwSetCursorPosCallback(mainWindow, handleMouseMovements);
	glfwSetScrollCallback(mainWindow, handleMouseScroll);
	
	//hide mouse cursor
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//add window input listener
	glfwSetWindowUserPointer(mainWindow, this);

	return 0;
}

void GLWindow::handleKeyboardKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	GLWindow* curWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 512)
	{
		if (action == GLFW_PRESS)
		{
			curWindow->kkeys[key] = true;
			cout << "Keyboard key: (" << key << ") is pressed" << endl;
		}
		else if (action == GLFW_RELEASE)
		{
			curWindow->kkeys[key] = false;
			cout << "Keyboard key: (" << key << ") is released" << endl;
		}

	}
}

void GLWindow::handleMouseMovements(GLFWwindow* window, double xPos, double yPos)
{
	GLWindow* curWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (curWindow->initMouse)
	{
		curWindow->prevX = xPos;
		curWindow->prevY = yPos;
		curWindow->initMouse = false;
	}

	curWindow->xChange = xPos - curWindow->prevX;
	curWindow->yChange = curWindow->prevY - yPos;

	curWindow->prevX = xPos;
	curWindow->prevY = yPos;

	cout << "Mouse Movement(" << curWindow->xChange << "," << curWindow->yChange << ")" << endl;
}

void GLWindow::handleMouseScroll(GLFWwindow* window, double xOffset, double yOffset)
{
	GLWindow* curWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (curWindow->initMouseScroll) {
		curWindow->mouseScroll = 0;
		curWindow->initMouseScroll = false;
	}

	if (yOffset < 0)
	{
		curWindow->mouseScroll--;

		if (curWindow->currentFoV > 1.0f) {
			curWindow->currentFoV = curWindow->currentFoV - 0.05;
		}
	}
	else
	{
		curWindow->mouseScroll++;

		if (curWindow->currentFoV < 45.0f)
		{
			curWindow->currentFoV = curWindow->currentFoV + 0.05;
		}
	}
	cout << "Mouse Scroll(" << curWindow->mouseScroll <<")" << endl;
}


GLfloat GLWindow::getXChange()
{
	GLfloat curChange = xChange;
	xChange = 0.0f;
	return curChange;
}

GLfloat GLWindow::getYChange()
{
	GLfloat curChange = yChange;
	yChange = 0.0f;
	return curChange;
}

GLfloat GLWindow::getFoVChange() {
	return currentFoV;
}

GLWindow::~GLWindow()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
