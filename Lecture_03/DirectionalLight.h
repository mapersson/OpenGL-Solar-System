#pragma once
#include "Light.h"

#include <GL\glew.h>
#include <glm\glm.hpp>

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir);

	void UseLight(GLfloat aColour, GLfloat aIntensity, GLfloat dIntensity, GLfloat dir);
	~DirectionalLight();


private:
	glm::vec3 direction;
};

