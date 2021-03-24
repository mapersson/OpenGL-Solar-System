#include "Camera_Control.h"



Camera_Control::Camera_Control()
{
}

Camera_Control::Camera_Control(glm::vec3 initialPosition, glm::vec3 initialUp, GLfloat initialYaw, GLfloat initialPitch, GLfloat initialKeyboardMoveSpeed, GLfloat initialMouseMoveSpeed)
{
	curPos = initialPosition;
	referenceWorldUp = initialUp;
	yaw = initialYaw;
	pitch = initialPitch;
	goFront = glm::vec3(0.0f, 0.0f, -1.0f);

	keyboardMoveSpeed = initialKeyboardMoveSpeed;
	mouseMoveSpeeed = initialMouseMoveSpeed;
	updateAllPositions();
}

void Camera_Control::updateAllPositions()
{
	goFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	goFront.y = sin(glm::radians(pitch));
	goFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	goFront = glm::normalize(goFront);

	lookRight = glm::normalize(glm::cross(goFront, referenceWorldUp));
	lookUp = glm::normalize(glm::cross(lookRight, goFront));
}
void Camera_Control::keyboardControl(bool* kkeys, GLfloat deltaTime)
{
	GLfloat speed = keyboardMoveSpeed * deltaTime;

	if (kkeys[GLFW_KEY_UP])
	{
		curPos += goFront * keyboardMoveSpeed;
	}

	if (kkeys[GLFW_KEY_DOWN])
	{
		curPos -= goFront * keyboardMoveSpeed;
	}

	if (kkeys[GLFW_KEY_LEFT])
	{
		curPos -= lookRight * keyboardMoveSpeed;
	}

	if (kkeys[GLFW_KEY_RIGHT])
	{
		curPos += lookRight * keyboardMoveSpeed;
	}
}

void Camera_Control::mouseControl(GLfloat xChange, GLfloat yChange, GLfloat deltaTime)
{
	xChange *= mouseMoveSpeeed;//*deltaTime;
	yChange *= mouseMoveSpeeed;//*deltaTime;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	updateAllPositions();
}

glm::mat4 Camera_Control::calculateCameraViewMatrix()
{
	return glm::lookAt(curPos, curPos + goFront, lookUp);
}


Camera_Control::~Camera_Control()
{
}












