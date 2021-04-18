#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include<cmath>

class RandomMode
{
public:
	RandomMode();
	RandomMode(GLfloat cv, GLfloat mv, GLfloat st, bool sp = false);
	GLfloat genCurrentValue();
	~RandomMode();

private:
	GLfloat curVal, maxValue, step;
	bool direction, spinn;

};

