#pragma once


#include <GL\glew.h>

class MaterialProperty
{
public:
	MaterialProperty();
	MaterialProperty(GLfloat sIntensity, GLfloat shine);
	void UseMaterialProperty(GLuint sIntensity, GLuint shine);

	~MaterialProperty();

private:
	GLfloat specularIntensity;
	GLfloat shininess;

};

