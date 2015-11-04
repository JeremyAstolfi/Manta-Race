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
	int GetBONum();
	void SetBOColor(BoundingObject* checker, vector3 colorChoice);
	void SetBOVisibility(BoundingObject* checker, bool visible);
	void SwitchVisibility(BoundingObject* checker);

	//Various methods
	void AddBox();
	void RenderBOs();
	void CheckCollisions();
	void CollisionResponse(BoundingObject* object1, BoundingObject* object2);
};

