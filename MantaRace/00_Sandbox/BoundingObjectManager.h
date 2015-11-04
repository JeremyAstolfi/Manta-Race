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
	std::vector<BoundingObject*> visibleForRender;

	//Get-Sets
	int GetBONum(BoundingObject* checker);
	void SetBOColor(BoundingObject* checker, vector3 colorChoice);
	void SetBOVisibility(BoundingObject* checker, bool visible);

	//Various methods
	void AddBox();
	void SwitchVisible(BoundingObject* checker);
	void RenderBOs();
	void CheckCollisions();
	void CollisionResponse(BoundingObject* object1, BoundingObject* object2);
};

