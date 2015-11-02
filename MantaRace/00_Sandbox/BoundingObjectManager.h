#pragma once
class BoundingObjectManager
{
public:
	BoundingObjectManager();
	~BoundingObjectManager();
	static BoundingObjectManager* instance;
	static BoundingObjectManager* GetInstance();
	static void ReleaseInstance();
};

