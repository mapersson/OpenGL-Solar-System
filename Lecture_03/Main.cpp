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

	MeshModel* triangle = new MeshModel();
	MeshModel* spaceFront = new MeshModel("SpaceFront");
	MeshModel* spaceRight = new MeshModel("SpaceRight");
	MeshModel* spaceLeft = new MeshModel("SpaceLeft");
	MeshModel* spaceTop = new MeshModel("SpaceTop");
	MeshModel* spaceBack = new MeshModel("SpaceBack");
	MeshModel* spaceBottom = new MeshModel("SpaceBottom");
	MeshModel* side0 = new MeshModel(0);
	MeshModel* side1 = new MeshModel(1);
	MeshModel* side2 = new MeshModel(2);
	MeshModel* side3 = new MeshModel(3);
	MeshModel* side99 = new MeshModel(99);

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
	RandomMode* transOffset = new RandomMode(0, 0.5f, 0.0005f);
	RandomMode* transOffsetZ = new RandomMode(0, 0.5f, 0.0001f);
	RandomMode* rotateYAxis = new RandomMode(0.0f, 0.5f, 0.01f);
 

	RandomMode* rotateOffest2 = new RandomMode(0, 360.0f, 0.03f, true);
	RandomMode* transOffset2 = new RandomMode(0, 2.0f, 0.001f);
	RandomMode* transOffsetZ2 = new RandomMode(0, 5.0f, 0.001f);

	// Camera is positioned on the xy plane @ z = -10. Looks towards the origin at 0,0,0 
	Camera_Control myCamera = Camera_Control(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 0.002f, 0.05f);

	DirectionalLight ambientDiffuseLight = DirectionalLight(1.0f, 1.0f, 1.0f, 0.75f, 1.0f, 0.0f, 0.0f, 0.0f); //color+ambient intensity
	PointLight pointLights[MAX_POINT_LIGHTS];
	unsigned int pointLightCount = 0;

	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
		2.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.3f, 0.3f, 0.3f);
	pointLightCount++;

	MaterialProperty shinyPyramid = MaterialProperty(1.0f, 32);
	MaterialProperty wallPyramid = MaterialProperty(0.2f, 2);
	
	deltaTime = prevTime = 0;

	//determine the projection matrix;
	glm::mat4 projection = glm::perspective((float)myWindow.getFoVChange(), (float)myWindow.getBufferWidth() / (float)myWindow.getBufferHeight(), 0.1f, 100.0f);


	TextureMapping brickTexture = TextureMapping((char*)"Textures/brick.png");
	brickTexture.LoadTextureRGBA();

	TextureMapping birdTexture = TextureMapping((char*)"Textures/bird.jpg");
	birdTexture.LoadTextureRGB();

	TextureMapping rockTexture = TextureMapping((char*)"Textures/Rock.jpg");
	rockTexture.LoadTextureRGB();

	TextureMapping woodTexture = TextureMapping((char*)"Textures/wood.jpg");
	woodTexture.LoadTextureRGB();

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

		
#pragma region Moon 1

		model = glm::mat4(1.0f);
		//Match Planet 1 rotation
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(0.0f, 0.0f, 1.0f));
		//Transate to the location of Plant 1
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		// Rotation around Planet 1
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(0.0f, 0.0f, -1.0f));
		// Translation to the location of the Moon around Plant 1. 
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		// Rotation of the Moon around its own access. 
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));

		
		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(myShader->getCameraViewLoc(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));
		glUniformMatrix4fv(myShader->getUnifromProjectionLoc(), 1, GL_FALSE, glm::value_ptr(projection));

		birdTexture.applyTexture();
		side0->RenderMeshModel();

		brickTexture.applyTexture();
		side1->RenderMeshModel();

		rockTexture.applyTexture();
		side2->RenderMeshModel();

		woodTexture.applyTexture();
		side3->RenderMeshModel();

#pragma endregion




		// Planet 1 
#pragma region Planet 1

		model = glm::mat4(1.0f);
		// Rotation around the Sun. 
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(0.0f, 0.0f, 1.0f));
		// Translate to the location of the orbit aorund the Sun
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		// Rotation of Planet 1 around its axis
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));

		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(myShader->getCameraViewLoc(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));
		glUniformMatrix4fv(myShader->getUnifromProjectionLoc(), 1, GL_FALSE, glm::value_ptr(projection));

		birdTexture.applyTexture();
		side0->RenderMeshModel();

		brickTexture.applyTexture();
		side1->RenderMeshModel();

		rockTexture.applyTexture();
		side2->RenderMeshModel();

		woodTexture.applyTexture();
		side3->RenderMeshModel();

#pragma endregion


#pragma region Sun
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		sun.RenderModel();

#pragma endregion

#pragma region Earth 
		model = glm::mat4(1.0f);
		//Copy to orbiting objects
			model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(0.4f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		earth.RenderModel();
#pragma endregion 

#pragma region Moon 
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(0.4f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(0.4f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		moon.RenderModel();
#pragma endregion 

#pragma region X-Wing
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(0.4f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()*2.0f), glm::vec3(0.4f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.4f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1400.0172f, -108.2528f, 1722.1118f));
		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		xwing.RenderModel();

#pragma endregion

		glUseProgram(0);
		myWindow.swapBuffers(); //Swap buffers, OpenGL main tains two Buffers, One is displayed, one is getting prepared
	}
	return 0;
}