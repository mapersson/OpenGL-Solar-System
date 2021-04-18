#pragma once
#include <GL\glew.h>
#include<string>
#include<fstream>
#include<iostream>

#include "ConstVar.h"
#include "DirectionalLight.h"
#include "PointLight.h"

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

	GLuint GetColour();
	GLuint GetAmbientIntensity();
	GLuint GetDiffuseIntensity();
	GLuint GetDirection();
	GLuint GetSpecularIntensity();
	GLuint GetShininess();
	GLuint GetEyePosition();
	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);


	~Shader();
private:
	GLuint shaderID;
	GLuint uniformModel, uniformProjection, uniformCamera;
	GLuint uniformSpecularIntensity, uniformShininess, uniformEyePosition;

	int pointLightCount;
	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;
	} uniformDirectionalLight;

	GLuint uniformPointLightCount;

	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];

	// Vertex Shader code based on GLSL version 3.30
	const char* vShader = "shaders/vShader.txt";
	// The Fragment Shader for version 3.30
	const char* fShader = "shaders/fShader.txt";
};

