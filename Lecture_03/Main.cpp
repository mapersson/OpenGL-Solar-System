// Term Project : This file contains the 'main' function. Program execution begins and ends there.

#define STB_IMAGE_IMPLEMENTATION
#include "TextureMapping.h"

#include <iostream> //controls input/output streams
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Model2D.h"
#include"MeshModel.h"
#include"Shader.h"
#include"GLWindow.h"
#include"RandomMode.h"
#include "Camera_Control.h"
#include "ImportedModel.h"
#include "Light.h"
#include "MaterialProperty.h"

using namespace std;


GLfloat deltaTime, prevTime;

int main()
{

	GLWindow myWindow = GLWindow(2400, 1600);
	myWindow.InitGLWindow();
	Shader *myShader = new Shader();

	MeshModel* spaceFront = new MeshModel("SpaceFront");
	MeshModel* spaceRight = new MeshModel("SpaceRight");
	MeshModel* spaceLeft = new MeshModel("SpaceLeft");
	MeshModel* spaceTop = new MeshModel("SpaceTop");
	MeshModel* spaceBack = new MeshModel("SpaceBack");
	MeshModel* spaceBottom = new MeshModel("SpaceBottom");

	//External 3D Models 
	ImportedModel earth = ImportedModel();
	earth.LoadModel("3DModels/Earth2K.obj");

	ImportedModel moon = ImportedModel();
	moon.LoadModel("3DModels/moon.obj");

	ImportedModel sun = ImportedModel();
	sun.LoadModel("3DModels/sun-v2.obj");

	ImportedModel xwing = ImportedModel();
	xwing.LoadModel("3DModels/x-wing.obj");


	RandomMode* rotateOffest = new RandomMode(0, 360.0f, 0.5f, true);
	
	RandomMode* rotateOffest2 = new RandomMode(0, 360.0f, 0.03f, true);
	
	// Camera is positioned on the xy plane @ z = -10. Looks towards the origin at 0,0,0 
	Camera_Control myCamera = Camera_Control(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 0.02f, 0.05f);

	DirectionalLight ambientDiffuseLight = DirectionalLight(1.0f, 1.0f, 1.0f, 0.75f, 1.0f, 0.0f, 0.0f, 0.0f); //color+ambient intensity
	PointLight pointLights[MAX_POINT_LIGHTS];
	unsigned int pointLightCount = 0;

	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
		2.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.3f, 0.3f, 0.3f);
	pointLightCount++;
	
	deltaTime = prevTime = 0;

	//determine the projection matrix;
	glm::mat4 projection = glm::perspective((float)myWindow.getFoVChange(), (float)myWindow.getBufferWidth() / (float)myWindow.getBufferHeight(), 0.1f, 100.0f);

	TextureMapping spaceTexture = TextureMapping((char*)"Textures/space.png");
	spaceTexture.LoadTextureRGB();


	while (!myWindow.getShouldClose()) 	// Loop until main window is closed
	{

		//Adjusted Hardware Speed
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - prevTime;
		prevTime = currentTime;

		glfwPollEvents(); 		// Get/set/control user input events
		myCamera.keyboardControl(myWindow.getsKeybordKeys(), deltaTime);
		myCamera.mouseControl(myWindow.getXChange(), myWindow.getYChange(), deltaTime);

		glm::mat4 projection = glm::perspective((float)myWindow.getFoVChange(), (float)myWindow.getBufferWidth() / (float)myWindow.getBufferHeight(), 0.1f, 100.0f);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear window, here clear color is Blue
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myShader->UseShader();
		myShader->SetDirectionalLight(&ambientDiffuseLight);
		myShader->SetPointLights(pointLights, pointLightCount);

		glm::mat4 model = glm::mat4(1.0f);
		
		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(myShader->getCameraViewLoc(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));
		glUniformMatrix4fv(myShader->getUnifromProjectionLoc(), 1, GL_FALSE, glm::value_ptr(projection));

		spaceTexture.applyTexture();
		spaceFront->RenderMeshModel();
		spaceRight->RenderMeshModel();
		spaceLeft->RenderMeshModel();
		spaceTop->RenderMeshModel();
		spaceBack->RenderMeshModel();
		spaceBottom->RenderMeshModel();
		
		

#pragma region Sun
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f)); //Scaling the model to fit scene. 
		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		sun.RenderModel();

#pragma endregion

#pragma region Earth 
		model = glm::mat4(1.0f);
		//Copy to orbiting objects
			model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(0.4f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)); //Scaling the model to fit scene. 
		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		earth.RenderModel();
#pragma endregion 

#pragma region Moon 
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(0.4f, 1.0f, 0.0f)); //Copied from Earth
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f)); //Copied from Earth
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(0.4f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f)); //Scaling the model to fit scene. 
		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		moon.RenderModel();
#pragma endregion 

#pragma region X-Wing
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(0.4f, 1.0f, 0.0f)); //Copied from Earth
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f)); //Copied from Earth
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()*2.0f ), glm::vec3(0.4f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f)); //
		model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f)); //Scaling the model to fit scene. 
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.4f, 1.0f, 0.0f)); //Rotate X-wing to the correct direction so it points the way it flys. 
		model = glm::translate(model, glm::vec3(-1400.0172f, -108.2528f, 1722.1118f)); //Move origin of 3D model from corner point to center of object
		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		xwing.RenderModel();

#pragma endregion

		glUseProgram(0);
		myWindow.swapBuffers(); //Swap buffers, OpenGL main tains two Buffers, One is displayed, one is getting prepared
	}
	return 0;
}