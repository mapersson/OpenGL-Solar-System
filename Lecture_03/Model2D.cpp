#include "Model2D.h"



Model2D::Model2D()
{
	VAO = 0;
	VBO = 0;
}


Model2D::Model2D(string fileName) :Model2D()
{
	fstream inStream;
	inStream.open(fileName, ios::in);


	if (inStream.fail())
	{
		cout << "file does not exists!";
		return;
	}

	GLint numLines;
	GLfloat xPos, yPos;
	inStream >> numpolys;     // read the number of polylines
	GLfloat maxValue = 0;

	for (int j = 0; j < numpolys; j++)  // read each polyline
	{
		inStream >> numLines;
		polys.push_back(numLines);


		for (int i = 0; i < numLines; i++)
		{
			inStream >> xPos;        // read the next x, y pair
			inStream >> yPos;        // read the next x, y pair

			maxValue = maxValue < xPos ? xPos : maxValue;

			vertices.push_back(xPos);
			vertices.push_back(yPos);
			vertices.push_back(0.0f);

			/*
			vertices.push_back((rand() % (int)maxValue));
			vertices.push_back((rand() % (int)maxValue));
			vertices.push_back((rand() % (int)maxValue));
			*/

		}
	}

	/*
	cout << numpolys << endl;
	for (int i = 0; i < vertices.size(); i++)
		cout << vertices[i] << " ";
	cout << endl;
	cout << sizeof(vertices[0]) * vertices.size();
	*/

	inStream.close();

	if (maxValue > 1.0)
	{
		for (unsigned int i = 0; i < vertices.size(); i++)
			vertices[i] = vertices[i] / maxValue;
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	/*
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	*/



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);






}
void Model2D::Render2DModel()
{
	glBindVertexArray(VAO);
	for (int cVal = 0, i = 0; i < numpolys; i++)
	{
		int nVal = polys[i];
		glDrawArrays(GL_LINE_STRIP, cVal, nVal);
		cVal += polys[i];
	}

	glBindVertexArray(0);
}

Model2D::~Model2D()
{
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	vertices.clear();
}
