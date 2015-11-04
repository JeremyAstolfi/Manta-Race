#pragma once

#include "RE\ReEngAppClass.h"
#include "BoundingObject.h"
#include <SFML\Graphics.hpp>

class BoundingObjectManager
{
public:
	BoundingObjectManager();
	~BoundingObjectManager();
	static BoundingObjectManager* instance;
	static BoundingObjectManager* GetInstance();
	static void ReleaseInstance();

	//fields
	std::vector<BoundingObject*> boundingObjects;


	//Get-Sets
	int GetBONum(BoundingObject checker);
	vector3 SetBOColor(BoundingObject checker);
	bool SetBOVisible();

	//Various methods
	void AddBox();
	void SwitchVisible();

	void CheckCollisions();
	void Collide();
};

