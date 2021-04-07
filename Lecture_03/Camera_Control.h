#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include <iostream>

class Camera_Control
{
public:
	Camera_Control();
	Camera_Control(glm::vec3 initialPosition, glm::vec3 initialUp, GLfloat initialYaw, GLfloat initialPitch, GLfloat initialKeyboardMoveSpeed, GLfloat initialMouseMoveSpeed);
	void keyboardControl(bool* kkeys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange, GLfloat deltaTime);

	glm::mat4 calculateCameraViewMatrix();
	~Camera_Control();

private:
	glm::vec3 curPos;
	glm::vec3 goFront;
	glm::vec3 lookUp;
	glm::vec3 lookRight;
	glm::vec3 referenceWorldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat keyboardMoveSpeed;
	GLfloat mouseMoveSpeeed;
	bool cameraTabbed = false;
	GLuint currentView = 0;

	void updateAllPositions();
};