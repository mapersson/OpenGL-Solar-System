#include "randomMode.h"

RandomMode::RandomMode()
{
	curVal = rand()/32767;
	maxValue = 1.0f;
	step = 0.0001f;
	direction = true;
}

RandomMode::RandomMode(GLfloat cv, GLfloat mv, GLfloat st, bool sp):RandomMode()
{
	curVal = cv;
	maxValue = mv;
	step = st;
	spinn = sp;
}

GLfloat RandomMode::genCurrentValue()
{
	if (direction)
	{
		curVal += step;
	}
	else {
		curVal -= step;
	}

	if (abs(curVal) >= maxValue)
	{
		if (spinn)
		{
			curVal = 0;
		}
		else
		{
			direction = !direction;
		}
	}

	return curVal;
}


RandomMode::~RandomMode()
{
}
