#include <glm/gtc/matrix_transform.hpp> 
#include <iostream>

#include "cCameraControl.h"
#include "JsonUtils.h"

cCameraControl::cCameraControl()
{
	InitPreferences();
}

cCameraControl::~cCameraControl()
{
}

void cCameraControl::InitPreferences()
{
	Document  config = ReadFromJson("cameraConfig.json");
	//load keyboard controls
	this->left = config["left"].GetInt();
	this->right = config["right"].GetInt();
	this->backward = config["backward"].GetInt();
	this->forward = config["forward"].GetInt();
	this->upward = config["upward"].GetInt();
	this->downward = config["downward"].GetInt();
	this->reset = config["reset"].GetInt();
	this->showFill = config["showFill"].GetInt();
	this->showWireFrame = config["showWireFrame"].GetInt();

	//camera preferences and positions
	this->cameraSpeed = config["speed"].GetFloat();
	this->cameraEye = glm::vec3(config["cameraEye_x"].GetFloat(),config["cameraEye_y"].GetFloat(), config["cameraEye_z"].GetFloat());
	this->originalCameraEye = glm::vec3(config["cameraEye_x"].GetFloat(), config["cameraEye_y"].GetFloat(), config["cameraEye_z"].GetFloat());
	this->cameraTarget = glm::vec3(config["cameraTarget_x"].GetFloat(), config["cameraTarget_y"].GetFloat(), config["cameraTarget_z"].GetFloat());
	this->upVector = glm::vec3(config["upVector_x"].GetFloat(), config["upVector_y"].GetFloat(), config["upVector_z"].GetFloat());
	this->debug  = config["debug"].GetBool();
	this->toggleWireFrame = false;
}

void cCameraControl::LookLeft() {
	this->cameraEye.x -= cameraSpeed;
}

void cCameraControl::LookRight() {
	this->cameraEye.x += cameraSpeed;
}

void cCameraControl::LookForward() 
{
	this->cameraEye.z += cameraSpeed;
}

void cCameraControl::LookBackward() 
{
	this->cameraEye.z -= cameraSpeed;
}

void cCameraControl::LookUpward()
{
	this->cameraEye.y += cameraSpeed;
}

void cCameraControl::LookDownward() 
{
	this->cameraEye.y -= cameraSpeed;
}

void cCameraControl::CameraComand(int inputKey)
{
	if (inputKey == left) 
	{
		LookLeft();
	}
	else if (inputKey == right) 
	{
		LookRight();
	}
	else if (inputKey == forward) 
	{
		LookForward();
	}
	else if (inputKey == backward)
	{
		LookBackward();
	}
	else if (inputKey == upward)
	{
		LookUpward();
	}
	else if (inputKey == downward)
	{
		LookDownward();
	}
	else if (inputKey == showFill)
	{
		this->toggleWireFrame = false;
	}
	else if (inputKey == showWireFrame)
	{
		this->toggleWireFrame = true;
	}

	if (debug) 
	{
		std::cout << "Camera: "
			<< GetEye().x << ", "
			<< GetEye().y << ", "
			<< GetEye().z << std::endl;
	}
	
}

glm::mat4 cCameraControl::RepositionCamera()
{
	return glm::lookAt(cameraEye,cameraTarget, upVector);
}

bool cCameraControl::IsResetCommand(int key)
{
	return key == reset;
}

bool cCameraControl::IsShowWireFrame()
{
	return this->toggleWireFrame;
}

glm::vec3 cCameraControl::GetEye()
{
	return this->cameraEye;
}

void cCameraControl::ResetCameraEye() 
{
	this->cameraEye.x = this->originalCameraEye.x;
	this->cameraEye.y = this->originalCameraEye.y;
	this->cameraEye.z = this->originalCameraEye.z;
}