#pragma once
#include "GLCommon.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

//Class responsible to control  and  hold all camera  information
class cCameraControl
{
private:
	int left;
	int right;
	int forward;
	int backward;
	int upward;
	int downward;
	int reset;
	int showWireFrame;
	int showFill;

	float cameraSpeed;

	glm::vec3 cameraEye;
	glm::vec3 originalCameraEye;
	glm::vec3 cameraTarget;
	glm::vec3 upVector;

	//Toggle that holds state of wire frame/fill option
	bool toggleWireFrame;
	//show camera eye positions 
	bool debug;
	//load preferences
	void InitPreferences();
	//adjust eye to the left
	void LookLeft();
	//adjust eye to the right
	void LookRight();
	//adjust eye forward
	void LookForward();
	//adjust eye backwards
	void LookBackward();
	//adjust eye downwards 
	void LookDownward();
	//adjust eye upward
	void LookUpward();

public:
	//constructor
	cCameraControl();
	//destructor
	~cCameraControl();
	//Resets camera position
	void ResetCameraEye();
	//Return Camera Eye vector
	glm::vec3 GetEye();
	//process camera user inputKey
	void CameraComand(int  inputKey);
	//adjust the camera matrix
	glm::mat4 RepositionCamera();
	//Should Reset Camera
	bool IsResetCommand(int key);
	//Should show 
	bool IsShowWireFrame();
};