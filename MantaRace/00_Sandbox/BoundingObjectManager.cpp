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
uint BoundingObjectManager::AddBox(String model,std::vector<vector3> vertLists){
	BoundingObject* adder = new BoundingObject(vertLists);
	adder->Model = model;
	
	boundingObjects.push_back(adder);
	//boundingObjects[boundingObjects.size() - 1]->SetPosition(vector3(2.5f * (boundingObjects.size() - 1), 0.0f, 0.0f));
	return boundingObjects.size() - 1;
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
//0 = all
void BoundingObjectManager::RenderBO(MeshManagerSingleton* meshManager){
	for (int i = 0; i < boundingObjects.size(); i++){
		if (boundingObjects[i]->GetVisibility() == true){
			visibleForRender.push_back(boundingObjects[i]);
		}
	}

	//TODO:: actually render the visibleForRender list
	for (int i = 0; i < visibleForRender.size(); i++)
	{
		meshManager->AddCubeToQueue(visibleForRender[i]->GetModelMatrix() * glm::scale(visibleForRender[i]->GetHalfWidthLocal() *2.0f), vector3(255.0f, 0.0f, 0.0f), WIRE);
	}
	visibleForRender.clear();
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
					
						CollisionResponse(visibleForRender[i], visibleForRender[e]);

					}//end box
				}// end sphere
			}//end i !=e
		}//end for e
	}// end for i
}




void BoundingObjectManager::CollisionResponse(BoundingObject* object1, BoundingObject* object2)
{
	object1->SetColor(vector3(1.0f, 0.0f, 0.0f));
	object2->SetColor(vector3(1.0f, 0.0f, 0.0f));
	vector3 o1WidthX = vector3(object1->GetHalfWidthGlobal().x - object1->GetCenterGlobal().x, 0.0f, 0.0f); //>>
	vector3 o2WidthX = vector3(object2->GetHalfWidthGlobal().x + object2->GetCenterGlobal().x, 0.0f, 0.0f); //<<
	vector3 o1WidthY = vector3(0.0f, object1->GetHalfWidthGlobal().y - object1->GetCenterGlobal().y, 0.0f);
	vector3 o2WidthY = vector3(0.0f, object2->GetHalfWidthGlobal().y + object2->GetCenterGlobal().y, 0.0f);
	vector3 o1WidthZ = vector3(0.0f, 0.0f, object1->GetHalfWidthGlobal().z - object1->GetCenterGlobal().z);
	vector3 o2WidthZ = vector3(0.0f, 0.0f, object2->GetHalfWidthGlobal().z + object2->GetCenterGlobal().z);

	if (glm::distance(o1WidthX, o2WidthX) <= 0.0f)
	{
		object1->SetPosition(vector3(glm::distance(o1WidthX, o2WidthX) / 2.0f - 0.1f, 0.0f, 0.0f));
		object2->SetPosition(vector3(-glm::distance(o1WidthX, o2WidthX) / 2.0f + 0.1f, 0.0f, 0.0f));
	}

	if (glm::distance(o1WidthY, o2WidthY) <= 0.0f)
	{
		object1->SetPosition(vector3(glm::distance(o1WidthY, o2WidthY) / 2.0f - 0.1f, 0.0f, 0.0f));
		object2->SetPosition(vector3(-glm::distance(o1WidthY, o2WidthY) / 2.0f + 0.1f, 0.0f, 0.0f));
	}
	if (glm::distance(o1WidthZ, o2WidthZ) <= 0.0f)
	{
		object1->SetPosition(vector3(glm::distance(o1WidthZ, o2WidthZ) / 2.0f - 0.1f, 0.0f, 0.0f));
		object2->SetPosition(vector3(-glm::distance(o1WidthZ, o2WidthZ) / 2.0f + 0.1f, 0.0f, 0.0f));
	}

	o1WidthX = vector3(object1->GetHalfWidthGlobal().x + object1->GetCenterGlobal().x, 0.0f, 0.0f); //<<
	o2WidthX = vector3(object2->GetHalfWidthGlobal().x - object2->GetCenterGlobal().x, 0.0f, 0.0f); //>>
	o1WidthY = vector3(0.0f, object1->GetHalfWidthGlobal().y + object1->GetCenterGlobal().y, 0.0f);
	o2WidthY = vector3(0.0f, object2->GetHalfWidthGlobal().y - object2->GetCenterGlobal().y, 0.0f);
	o1WidthZ = vector3(0.0f, 0.0f, object1->GetHalfWidthGlobal().z + object1->GetCenterGlobal().z);
	o2WidthZ = vector3(0.0f, 0.0f, object2->GetHalfWidthGlobal().z - object2->GetCenterGlobal().z);

	if (glm::distance(o1WidthX, o2WidthX) <= 0.0f)
	{
		object1->SetPosition(vector3(glm::distance(o1WidthX, o2WidthX) / 2.0f + 0.1f, 0.0f, 0.0f));
		object2->SetPosition(vector3(-glm::distance(o1WidthX, o2WidthX) / 2.0f - 0.1f, 0.0f, 0.0f));
	}

	if (glm::distance(o1WidthY, o2WidthY) <= 0.0f)
	{
		object1->SetPosition(vector3(glm::distance(o1WidthY, o2WidthY) / 2.0f + 0.1f, 0.0f, 0.0f));
		object2->SetPosition(vector3(-glm::distance(o1WidthY, o2WidthY) / 2.0f - 0.1f, 0.0f, 0.0f));
	}
	if (glm::distance(o1WidthZ, o2WidthZ) <= 0.0f)
	{
		object1->SetPosition(vector3(glm::distance(o1WidthZ, o2WidthZ) / 2.0f + 0.1f, 0.0f, 0.0f));
		object2->SetPosition(vector3(-glm::distance(o1WidthZ, o2WidthZ) / 2.0f - 0.1f, 0.0f, 0.0f));
	}
		
}


