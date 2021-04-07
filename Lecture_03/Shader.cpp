#include "Shader.h"



Shader::Shader()
{
	shaderID = 0;
	CreateShaderProgramFromFiles(vShader, fShader);
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();
	if (!shaderID)
	{
		printf("Failed to create shader\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformCamera= glGetUniformLocation(shaderID, "camera");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

	uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		
		string s = "pointLights[" + to_string(i) + "].base.colour";
		uniformPointLight[i].uniformColour = glGetUniformLocation(shaderID, &s[0]);

		s = "pointLights[" + to_string(i) + "].base.ambientIntensity";
		uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, &s[0]);

		s = "pointLights[" + to_string(i) + "].base.diffuseIntensity";
		uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, &s[0]);

		s = "pointLights[" + to_string(i) + "].position";
		uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, &s[0]);

		s = "pointLights[" + to_string(i) + "].constant";
		uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, &s[0]);

		s = "pointLights[" + to_string(i) + "].linear";
		uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, &s[0]);

		s = "pointLights[" + to_string(i) + "].exponent";
		uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, &s[0]);

	}

}

void Shader::CompileShaderFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

string Shader::ReadFile(const char* fileDir)
{
	string content;
	ifstream fileStream(fileDir, ios::in);

	if (!fileStream.is_open()) {
		cout << "Failed to read " << fileDir << "! File doesn't exist.";
		return "";
	}

	string lineCode = "";
	while (!fileStream.eof())
	{
		getline(fileStream, lineCode);
		content.append(lineCode + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::CreateShaderProgramFromFiles(const char* vertexPath, const char* fragmentPath)
{
	string vString = ReadFile(vertexPath);
	string fString = ReadFile(fragmentPath);
	const char* vertexCode = vString.c_str();
	const char* fragmentCode = fString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

void Shader::UseShader()
{
	glUseProgram(shaderID);
}

GLuint Shader::GetSpecularIntensity()
{
	return uniformSpecularIntensity;
}
GLuint Shader::GetShininess()
{
	return uniformShininess;
}

GLuint Shader::GetEyePosition()
{
	return uniformEyePosition;
}


GLuint Shader::GetColour()
{
	return uniformDirectionalLight.uniformColour;
}
GLuint Shader::GetAmbientIntensity()
{
	return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetDiffuseIntensity()
{
	return uniformDirectionalLight.uniformDiffuseIntensity;
}
GLuint Shader::GetDirection()
{
	return uniformDirectionalLight.uniformDirection;
}


void Shader::SetDirectionalLight(DirectionalLight* dLight)
{
	dLight->UseLight(uniformDirectionalLight.uniformColour, uniformDirectionalLight.uniformAmbientIntensity,
		uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLights(PointLight* pLight, unsigned int lightCount)
{
	if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

	glUniform1i(uniformPointLightCount, lightCount);

	for (int i = 0; i < lightCount; i++)
	{
		pLight[i].UseLight(uniformPointLight[i].uniformColour, uniformPointLight[i].uniformAmbientIntensity,
			uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition,
			uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
	}
}


Shader::~Shader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
}
