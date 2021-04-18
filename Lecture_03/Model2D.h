#pragma once
#include <GL\glew.h>
#include <vector>
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

class Model2D
{
public:
	Model2D();
	Model2D(string fineName);
	void Render2DModel();
	~Model2D();


private:
	GLuint VAO, VBO;
	vector<GLfloat> vertices;
	vector<GLint> polys;
	int numpolys;

};

