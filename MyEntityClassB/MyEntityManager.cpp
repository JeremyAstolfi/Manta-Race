#include "MyEntityManager.h"
//  MyEntityManager
MyEntityManager* MyEntityManager::m_pInstance = nullptr;
void MyEntityManager::Init(void)
{
	m_nEntityCount = 0;
	m_pColliderManager = MyBOManager::GetInstance();
}
void MyEntityManager::Release(void)
{
	m_lEntity.clear();
}
MyEntityManager* MyEntityManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}
void MyEntityManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
MyEntityManager::MyEntityManager(){Init();}
MyEntityManager::MyEntityManager(MyEntityManager const& other){ }
MyEntityManager& MyEntityManager::operator=(MyEntityManager const& other) { return *this; }
MyEntityManager::~MyEntityManager(){Release();};
//Accessors
int MyEntityManager::GetEntityCount(void){ return m_nEntityCount; }
void MyEntityManager::AddEntity(String a_sEntity)
{
	MyEntityClass* pEntity = new MyEntityClass(a_sEntity);
	AddEntity(pEntity);
}
void MyEntityManager::AddEntity(MyEntityClass* a_nEntity)
{
	if (a_nEntity == nullptr)
		return;
	m_lEntity.push_back(a_nEntity);
	m_map[a_nEntity->GetName()] = m_nEntityCount;
	m_nEntityCount++;
}
MyEntityClass* MyEntityManager::GetEntity(String a_sIndex)
{
	int nIndex = GetIndex(a_sIndex); //Identify the entry by name
	return GetEntity(nIndex); //return the entry if found
}
MyEntityClass* MyEntityManager::GetEntity(int a_nIndex)
{
	uint nIndex = static_cast<int>(m_lEntity.size());//check if the index is in bounds
	//assert(a_nIndex >= 0 && a_nIndex < nIndex); // Assert there is an entry
	if (nIndex == -1)//If the index was not found
		return nullptr; //return a nullptr
	return m_lEntity[a_nIndex];//return the entry
}
//--- Non Standard Singleton Methods
int MyEntityManager::GetIndex(String a_sIndex)
{
	//Find the related index
	auto var = m_map.find(a_sIndex);
	//If not found return -1
	if (var == m_map.end())
		return -1;
	return var->second;//Get the index
}
void MyEntityManager::Update(void)
{
	m_pColliderManager->Update();
	for (uint nEntity = 0; nEntity < m_nEntityCount; nEntity++)
	{
		std::vector<int> list = m_pColliderManager->GetCollidingVector(nEntity);
		if (m_lEntity[nEntity]->GetPosition().x > 15.0f && m_lEntity[nEntity]->GetVelocity().x > 0.0f)
		{
			m_lEntity[nEntity]->SetVelocity(vector3(0.0f));
			m_lEntity[nEntity]->SetAcceleration(-m_lEntity[nEntity]->GetAcceleration());
		}
		if (m_lEntity[nEntity]->GetPosition().x < -15.0f && m_lEntity[nEntity]->GetVelocity().x < 0.0f)
		{
			m_lEntity[nEntity]->SetVelocity(vector3(0.0f));
			m_lEntity[nEntity]->SetAcceleration(-m_lEntity[nEntity]->GetAcceleration());
		}
		m_lEntity[nEntity]->Update();
	}
}

void MyEntityManager::SetValues(vector3 a_v3Acceleration, float a_fMass, float a_fMaxAcc, String a_sName)
{
	int nIndex = GetIndex(a_sName);
	if (nIndex >= 0)
	{
		m_lEntity[nIndex]->SetAcceleration(a_v3Acceleration);
		m_lEntity[nIndex]->SetMass(a_fMass);
		m_lEntity[nIndex]->SetMaxAcc(a_fMaxAcc);
	}
}

void MyEntityManager::SetPosition(vector3 a_v3Position, String a_sName)
{
	int nIndex = GetIndex(a_sName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetPosition(a_v3Position);
}
void MyEntityManager::SetVelocity(vector3 a_v3Velocity, String a_sName)
{
	int nIndex = GetIndex(a_sName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetVelocity(a_v3Velocity);
}
void MyEntityManager::SetAcceleration(vector3 a_v3Acceleration, String a_sName)
{
	int nIndex = GetIndex(a_sName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetAcceleration(a_v3Acceleration);
}
void MyEntityManager::SetMass(float a_fMass, String a_sName) 
{
	int nIndex = GetIndex(a_sName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetMass(a_fMass);
}
void MyEntityManager::SetMaxAcc(float a_fMaxAcc, String a_sName) 
{ 
	int nIndex = GetIndex(a_sName);
	if (nIndex >= 0)
		m_lEntity[nIndex]->SetMaxAcc(a_fMaxAcc);
}