/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "BoundingObjectManager.h"
#include "MantaRayControls.h"
#include "EnemyObjectManager.h"
using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
public:
	typedef ReEngAppClass super;
	
	sf::Vector2i mousePos;
	vector3 v3MousePos;
	EnemyObjectManager* m_pEOManage = EnemyObjectManager::GetInstance();
	int enemies = 500;

	float yCeiling = 3.0f;
	float yFloor = -3.0f;
	float xCeiling = 5.0f;
	float xFloor = -5.0f;
	float yRange = yCeiling - yFloor;
	float xRange = xCeiling - xFloor;
	float zCeiling = -1450.0f;
	float zFloor = -375.0f;
	float zRange = zCeiling - zFloor;

	int tempX = 0;
	int tempY = 0;

	/* Constructor */
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}
	BoundingObjectManager* bObjManager = BoundingObjectManager::GetInstance();
	MantaRayControls* mantaRay = MantaRayControls::GetInstance();
	vector4 GetMousePosition(void);
	/*
	ReadConfig
	Reads the configuration of the application to a file
	*/
	virtual void ReadConfig(void) final {}

	/*
	WriteConfig
	Writes the configuration of the application to a file
	*/
	virtual void WriteConfig(void) final {}

	/*
	InitWindow
	Initialize ReEng variables necessary to create the window
	*/
	virtual void InitWindow(String a_sWindowName) final;

	/*
	InitVariables
	Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	*/
	virtual void InitVariables(void) final;

	/*
	Update
	Updates the scene
	*/
	virtual void Update(void) final;

	/*
	Display
	Displays the scene
	*/
	virtual void Display(void) final;

	/*
	ProcessKeyboard
	Manage the response of key presses
	*/
	virtual void ProcessKeyboard(void) final;

	/*
	ProcessMouse
	Manage the response of key presses and mouse position
	*/
	virtual void ProcessMouse(void) final;

	/*
	Release
	Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	*/
	virtual void Release(void) final;
};

#endif //__APPLICATION_H_
