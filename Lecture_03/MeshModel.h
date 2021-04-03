#pragma once
#include <GL\glew.h>
#include <string>
using namespace std;

class MeshModel
{
public:
	MeshModel();
	MeshModel(int side);
	MeshModel(string name);
	void RenderMeshModel();
	void CreateObjectModel(GLfloat* vertices, unsigned int* indices, unsigned int nVertices, unsigned int nIndices);
	void CreateMeshModel(GLfloat* vertices, unsigned int* indices, unsigned int nVertices, unsigned int nIndices);
	~MeshModel();

private:
	GLuint VAO, VBO, IBO;
	int vCount;
	int iCount;
};

