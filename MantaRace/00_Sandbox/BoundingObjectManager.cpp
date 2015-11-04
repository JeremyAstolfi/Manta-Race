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
int BoundingObjectManager::GetBONum(BoundingObject* checker){
	return 0;
}

void BoundingObjectManager::SetBOColor(BoundingObject* checker, vector3 colorChoice){
	checker->SetColor(colorChoice);
}

void BoundingObjectManager::SetBOVisible(BoundingObject* checker){
	checker->SetVisibility(true);
}

//various methods

void BoundingObjectManager::AddBox(){
	BoundingObject* adder = new BoundingObject();
	boundingObjects.push_back(adder);
}

void BoundingObjectManager::SwitchVisible(BoundingObject* checker){
	if (checker->GetVisibility() == true){
		checker->SetVisibility(false);
	}
	else{
		checker->SetVisibility(true);
	}
}

void BoundingObjectManager::RenderBOs(){

}

void BoundingObjectManager::CheckCollisions(){

}

void BoundingObjectManager::Collide(){

}