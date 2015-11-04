#include "BoundingObjectManager.h"

BoundingObjectManager* BoundingObjectManager::instance = nullptr;

BoundingObjectManager::BoundingObjectManager()
{
}


BoundingObjectManager::~BoundingObjectManager()
{
}

BoundingObjectManager* BoundingObjectManager::GetInstance()
{
	if (BoundingObjectManager::instance == nullptr)
	{
		BoundingObjectManager::instance = new BoundingObjectManager();
	}
	return BoundingObjectManager::instance;
}

void BoundingObjectManager::ReleaseInstance()
{
	if (BoundingObjectManager::instance != nullptr)
	{
		delete BoundingObjectManager::instance;
		BoundingObjectManager::instance = nullptr;
	}
}

//get - sets
int BoundingObjectManager::GetBONum(BoundingObject checker){
	return 0;
}

vector3 BoundingObjectManager::SetBOColor(BoundingObject checker){
	return vector3(0, 0, 0);
}

void BoundingObjectManager::CollisionResponse(BoundingObject* object1, BoundingObject* object2)
{
	vector3 m_v3MinG = vector3(object1->GetModelMatrix() * vector4(m_v3Min, 1.0f));
	vector3 m_v3MaxG = vector3(object1->GetModelMatrix() * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(object2->GetModelMatrix() * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(object2->GetModelMatrix() * vector4(a_pOther->m_v3Max, 1.0f));

	if (m_v3MaxG.x < a_pOther->m_v3MinG.x)
		bColliding = false;
	if (m_v3MinG.x > a_pOther->m_v3MaxG.x)
		bColliding = false;

	//Check for Y
	if (m_v3MaxG.y < a_pOther->m_v3MinG.y)
		bColliding = false;
	if (m_v3MinG.y > a_pOther->m_v3MaxG.y)
		bColliding = false;

	//Check for Z
	if (m_v3MaxG.z < a_pOther->m_v3MinG.z)
		bColliding = false;
	if (m_v3MinG.z > a_pOther->m_v3MaxG.z)
		bColliding = false;
}

//various methods


