#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include<iostream>

using namespace std;

class GLWindow
{
public:
	GLWindow();
	GLWindow(GLint windowWidth, GLint windowHeight);
	int InitGLWindow();
	GLint getBufferWidth() { return width; }
	GLint getBufferHeight() { return height; }
	bool getShouldClose()  { return glfwWindowShouldClose(mainWindow); }
	void swapBuffers() { glfwSwapBuffers(mainWindow); }
	static void handleKeyboardKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouseMovements(GLFWwindow* window, double xPos, double yPos);
	static void handleMouseScroll(GLFWwindow* window, double xOffset, double yOffset);
	bool* getsKeybordKeys() { return kkeys; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getFoVChange();

	~GLWindow();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	bool kkeys[512];
	
	bool initMouse = true;
	bool initMouseScroll = true;
	GLfloat prevX;
	GLfloat prevY;
	GLfloat xChange;
	GLfloat yChange;
	GLint mouseScroll;
	GLfloat currentFoV = 45.0f;
};

