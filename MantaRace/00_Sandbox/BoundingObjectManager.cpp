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
int BoundingObjectManager::GetBONum(){
	return boundingObjects.size();
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
		if (boundingObjects[i]->GetVisibility() == true){
			visibleForRender.push_back(boundingObjects[i]);
		}
	}

	//TODO:: actually render the visibleForRender list
}


void BoundingObjectManager::CheckCollisions()
{
	/* //for when the visibleForRender vector is removed above
	for (int i = 0; i < boundingObjects.size(); i++){
		if (boundingObjects[i]->GetVisibility == true){
			visibleForRender.push_back(boundingObjects[i]);
		}
	}
	*/

	for (int i = 0; i < visibleForRender.size(); i++){
		for (int e = i; e < visibleForRender.size(); e++){

			if (i != e){
				if (visibleForRender[i]->IsSphereColliding(visibleForRender[e])){
					if (visibleForRender[i]->IsBoxColliding(visibleForRender[e])){
					
						//CollisionResponse(visibleForRender[i], visibleForRender[e]);

					}//end box
				}// end sphere
			}//end i !=e
		}//end for e
	}// end for i
}



/*
void BoundingObjectManager::CollisionResponse(BoundingObject* object1, BoundingObject* object2)
{
	vector3 o1WidthX = vector3(object1->GetHalfWidthGlobal().x - object1->GetCenterGlobal().x, 0.0f, 0.0f);
	vector3 o2WidthX = vector3(object2->GetHalfWidthGlobal().x + object2->GetCenterGlobal().x, 0.0f, 0.0f);
	vector3 o1WidthY = vector3(0.0f, object1->GetHalfWidthGlobal().x - object1->GetCenterGlobal().x, 0.0f);
	vector3 o2WidthY = vector3(0.0f, object2->GetHalfWidthGlobal().x + object2->GetCenterGlobal().x, 0.0f);
	vector3 o1WidthZ = vector3(0.0f, 0.0f, object1->GetHalfWidthGlobal().x - object1->GetCenterGlobal().x);
	vector3 o2WidthZ = vector3(0.0f, 0.0f, object2->GetHalfWidthGlobal().x + object2->GetCenterGlobal().x);

	if (glm::distance(o1WidthX, o2WidthX) <= 0.0f)
	{

	}
		
}*/


