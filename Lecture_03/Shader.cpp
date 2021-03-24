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


Shader::~Shader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
}
