#pragma once
#include <GL\glew.h>
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

class Shader
{
public:
	Shader();
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void CompileShaderFromString(const char* vertexCode, const char* fragmentCode);
	string ReadFile(const char* fileDir);
	void CreateShaderProgramFromFiles(const char* vertexPath, const char* fragmentPath);
	void UseShader();
	GLuint getUnifromModelLoc() { return uniformModel; }
	GLuint getUnifromProjectionLoc() { return uniformProjection; }
	GLuint getCameraViewLoc() { return uniformCamera; }

	~Shader();
private:
	GLuint shaderID;
	GLuint uniformModel, uniformProjection, uniformCamera;
	// Vertex Shader code based on GLSL version 3.30
	const char* vShader = "shaders/vShader.txt";
	// The Fragment Shader for version 3.30
	const char* fShader = "shaders/fShader.txt";
};

