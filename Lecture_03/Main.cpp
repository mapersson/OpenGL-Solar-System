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

	RandomMode* rotateOffest = new RandomMode(0, 360.0f, 0.5f, true);
	RandomMode* transOffset = new RandomMode(0, 0.5f, 0.0005f);
	RandomMode* transOffsetZ = new RandomMode(0, 0.5f, 0.0001f);
	RandomMode* rotateYAxis = new RandomMode(0.0f, 0.5f, 0.01f);
 

	RandomMode* rotateOffest2 = new RandomMode(0, 360.0f, 0.03f, true);
	RandomMode* transOffset2 = new RandomMode(0, 2.0f, 0.001f);
	RandomMode* transOffsetZ2 = new RandomMode(0, 5.0f, 0.001f);


	Camera_Control myCamera = Camera_Control(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 0.002f, 0.05f);
	
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
		

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(transOffset->genCurrentValue(), 0.0f, transOffsetZ->genCurrentValue()));
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(1.0f, rotateYAxis->genCurrentValue(), 0.75f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

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

		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(transOffset->genCurrentValue(), 0.0f, transOffsetZ->genCurrentValue()));
		model = glm::rotate(model, glm::radians(rotateOffest->genCurrentValue()), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(myShader->getCameraViewLoc(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));
		glUniformMatrix4fv(myShader->getUnifromProjectionLoc(), 1, GL_FALSE, glm::value_ptr(projection));
		
		//wallTexture.applyTexture();
		//triangle->RenderMeshModel();


		model=glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(transOffset2->genCurrentValue(), 0.0f, -transOffsetZ2->genCurrentValue()));
		model = glm::rotate(model, glm::radians(rotateOffest2->genCurrentValue()), glm::vec3(1.0f, 1.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));


		glUniformMatrix4fv(myShader->getUnifromModelLoc(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(myShader->getCameraViewLoc(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));
		glUniformMatrix4fv(myShader->getUnifromProjectionLoc(), 1, GL_FALSE, glm::value_ptr(projection));

		
		//brickTexture.applyTexture();
		//cube->RenderMeshModel();
		
		glUseProgram(0);
		myWindow.swapBuffers(); //Swap buffers, OpenGL main tains two Buffers, One is displayed, one is getting prepared
	}
	return 0;
}