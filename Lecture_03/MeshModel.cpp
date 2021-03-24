#include "MeshModel.h"



MeshModel::MeshModel()
{
	
	unsigned int indices[] = {
		0, 1, 2,   //front
		0, 2, 3,   //right 
		0, 3, 1,   //left
		3, 2, 1,	//bottom
	};

	GLfloat vertices[] = {
		//	x   y   z		u	  v
		0.5f, 1.0f, 0.5f, 0.5f, 1.0f,   //front right, point 0 //
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   //back right, point 1 //
		1.0f, 0.0f, 1.0f, 1.0f, 0.0f,   //front left, point 2
		0.5f, 0.0f, 0.0f, 0.5f, 0.0f	//back left, point 3
	};
	vCount = 20;
	iCount = 12;
	CreateObjectModel(vertices, indices, vCount, iCount);

}

MeshModel::MeshModel(int side)
{
	if (side == 0) {
		unsigned int indices[] = {
		0, 1, 2,   //front
		};

		GLfloat vertices[] = {
			//	x   y   z		u	  v
			0.5f, 1.0f, 0.5f, 0.5f, 1.0f,   //front right, point 0 //
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   //back right, point 1 //
			1.0f, 0.0f, 1.0f, 1.0f, 0.0f,   //front left, point 2
			0.5f, 0.0f, 0.0f, 0.5f, 0.0f	//back left, point 3
		};
		vCount = 20;
		iCount = 3;
		CreateObjectModel(vertices, indices, vCount, iCount);
	}
	else if (side == 1) {
		unsigned int indices[] = {
		0, 2, 3,   //right 
		};

		GLfloat vertices[] = {
			//	x   y   z		u	  v
			0.5f, 1.0f, 0.5f, 0.5f, 1.0f,   //front right, point 0 //
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   //back right, point 1 //
			1.0f, 0.0f, 1.0f, 1.0f, 0.0f,   //front left, point 2
			0.5f, 0.0f, 0.0f, 0.0f, 0.0f	//back left, point 3
		};
		vCount = 20;
		iCount = 3;
		CreateObjectModel(vertices, indices, vCount, iCount);
	}
	else if (side == 2) {
		unsigned int indices[] = {
		0, 3, 1,   //left
		};

		GLfloat vertices[] = {
			//	x   y   z		u	  v
			0.5f, 1.0f, 0.5f, 0.5f, 1.0f,   //front right, point 0 //
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   //back right, point 1 //
			1.0f, 0.0f, 1.0f, 1.0f, 0.0f,   //front left, point 2
			0.5f, 0.0f, 0.0f, 0.5f, 0.0f	//back left, point 3
		};
		vCount = 20;
		iCount = 3;
		CreateObjectModel(vertices, indices, vCount, iCount);
	}
	else {
		unsigned int indices[] = {

		3, 2, 1,	//bottom
		};

		GLfloat vertices[] = {
			//	x   y   z		u	  v
			0.5f, 1.0f, 0.5f, 0.5f, 1.0f,   //front right, point 0 //
			0.0f, 0.0f, 1.0f, 0.5f, 1.0f,   //back right, point 1 //
			1.0f, 0.0f, 1.0f, 1.0f, 0.0f,   //front left, point 2
			0.5f, 0.0f, 0.0f, 0.0f, 0.0f	//back left, point 3
		};
		vCount = 20;
		iCount = 3;
		CreateObjectModel(vertices, indices, vCount, iCount);
	}
	
}

MeshModel::MeshModel(string name)
{
	if (name == "SpaceFront") {
		unsigned int indices[] = {
		0, 1, 2, 0, 3, 2
		};

		GLfloat vertices[] = {
			//	x   y   z		u	  v
			-10.0f, -10.0f, -10.0f, 0.0f, 0.0f,   //front right, point 0 //
			10.0f, -10.0f, -10.0f, 2.0f, 0.0f,   //back right, point 1 //
			10.0f, 10.0f, -10.0f, 2.0f, 2.0f,   //front left, point 2
			-10.0f, 10.0f, -10.0f, 0.0f, 2.0f,	//back left, point 3
			
		};

		vCount = 4 * 5;
		iCount = 6;
		CreateObjectModel(vertices, indices, vCount, iCount);
	}
	else if (name == "SpaceRight") {
		unsigned int indices[] = {
		0, 1, 2, 0, 3, 2
		};

		GLfloat vertices[] = {
			//	x   y   z		u	  v
			10.0f, -10.0f, -10.0f, 0.0f, 0.0f,   //back right, point 1 //
			10.0f, 10.0f, -10.0f, 0.0f, 2.0f,   //front left, point 2
			10.0f, 10.0f, 10.0f, 2.0f, 2.0f,   //back right, point 5 //
			10.0f, -10.0f, 10.0f, 2.0f, 0.0f,   //front left, point 6
		};

		vCount = 4 * 5;
		iCount = 6;
		CreateObjectModel(vertices, indices, vCount, iCount);
	}
	else if (name == "SpaceLeft") {
		unsigned int indices[] = {
		0, 1, 2, 0, 3, 2
		};

		GLfloat vertices[] = {
			//	x   y   z		u	  v
			-10.0f, -10.0f, -10.0f, 0.0f, 0.0f,   //front right, point 0 //
			-10.0f, 10.0f, -10.0f, 0.0f, 2.0f,	//back left, point 3
			-10.0f, 10.0f, 10.0f, 2.0f, 2.0f,   //front right, point 4 //
			-10.0f, -10.0f, -10.0f, 2.0f, 0.0f	//back left, point 7
		};

		vCount = 4 * 5;
		iCount = 6;
		CreateObjectModel(vertices, indices, vCount, iCount);
	}
	else if (name == "SpaceTop") {
		unsigned int indices[] = {
		0, 1, 2, 0, 3, 2
		};

		GLfloat vertices[] = {
			//	x   y   z		u	  v
			10.0f, 10.0f, -10.0f, 2.0f, 2.0f,   //front left, point 2
			-10.0f, 10.0f, -10.0f, 0.0f, 2.0f,	//back left, point 3
			-10.0f, 10.0f, 10.0f, 0.0f, 0.0f,   //front right, point 4 //
			10.0f, 10.0f, 10.0f, 2.0f, 0.0f,   //back right, point 5 //
		};

		vCount = 4 * 5;
		iCount = 6;
		CreateObjectModel(vertices, indices, vCount, iCount);
	}
	else if (name == "SpaceBack") {
		unsigned int indices[] = {
		0, 1, 2, 0, 3, 2
		};

		GLfloat vertices[] = {
			//	x   y   z		u	  v
			-10.0f, 10.0f, 10.0f, 0.0f, 0.0f,   //front right, point 4 //
			10.0f, 10.0f, 10.0f, 2.0f, 0.0f,   //back right, point 5 //
			10.0f, -10.0f, 10.0f, 2.0f, 2.0f,   //front left, point 6
			-10.0f, -10.0f, -10.0f, 0.0f, 2.0f	//back left, point 7
		};

		vCount = 4 * 5;
		iCount = 6;
		CreateObjectModel(vertices, indices, vCount, iCount);
	}
	else {
		unsigned int indices[] = {
		0, 1, 2, 0, 3, 2
		};

		GLfloat vertices[] = {
			//	x   y   z		u	  v
			-10.0f, -10.0f, -10.0f, 0.0f, 0.0f,   //front right, point 0 //
			10.0f, -10.0f, -10.0f, 2.0f, 0.0f,   //back right, point 1 //
			10.0f, -10.0f, 10.0f, 2.0f, 2.0f,   //front left, point 6
			-10.0f, -10.0f, -10.0f, 0.0f, 2.0f	//back left, point 7
		};

		vCount = 4 * 5;
		iCount = 6;
		CreateObjectModel(vertices, indices, vCount, iCount);
	}

}

void MeshModel::CreateObjectModel(GLfloat* vertices, unsigned int* indices, unsigned int nVertices, unsigned int nIndices)
{

	if (nIndices != 0)
	{

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * nIndices, indices, GL_STATIC_DRAW);


		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * nVertices, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	else
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * nVertices, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

void MeshModel::RenderMeshModel()
{
	if (iCount != 0)
	{

		glBindVertexArray(VAO);
		/*
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 0, 12);
		*/
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
	else
	{
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 0, vCount);
		glBindVertexArray(0);
	}
	
}


MeshModel::~MeshModel()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

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
}
