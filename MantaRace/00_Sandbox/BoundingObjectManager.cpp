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
//Get the index of a BO?
int BoundingObjectManager::GetBONum(BoundingObject* checker){
	return 0;
}

//Set the color of a Bounding Object
void BoundingObjectManager::SetBOColor(BoundingObject* checker, vector3 colorChoice){
	checker->SetColor(colorChoice);
}

//Set the visibility of a Bounding Object
void BoundingObjectManager::SetBOVisibility(BoundingObject* checker, bool visible){
	checker->SetVisibility(visible);
}

//various methods

//Add a new Bounding Object to the list
void BoundingObjectManager::AddBox(){
	BoundingObject* adder = new BoundingObject();
	boundingObjects.push_back(adder);
}

//Switch the visibility of a Bounding Object
void BoundingObjectManager::SwitchVisibility(BoundingObject* checker){
	if (checker->GetVisibility() == true){
		checker->SetVisibility(false);
	}
	else{
		checker->SetVisibility(true);
	}
}

//Create a list of visible Bounding Objects and add them to a render list
void BoundingObjectManager::RenderBOs(){
	for (int i = 0; i < boundingObjects.size(); i++){
		if (boundingObjects[i]->GetVisibility == true){
			visibleForRender.push_back(boundingObjects[i]);
		}
	}

	//TODO:: actually render the visibleForRender list
}

void BoundingObjectManager::CheckCollisions(){

}




void BoundingObjectManager::CollisionResponse(BoundingObject* object1, BoundingObject* object2)
{
	/*
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
		*/
}


