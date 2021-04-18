#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() :Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red, green, blue, aIntensity, dIntensity)
{

	direction = glm::vec3(xDir, yDir, zDir);
}

void DirectionalLight::UseLight(GLfloat aColour, GLfloat aIntensity, GLfloat dIntensity, GLfloat dir)
{
	glUniform3f(aColour, colour.x, colour.y, colour.z);
	glUniform1f(aIntensity, ambientIntensity);
	glUniform1f(dIntensity, diffuseIntensity);
	glUniform3f(dir, direction.x, direction.y, direction.z);

}

DirectionalLight::~DirectionalLight()
{

}
