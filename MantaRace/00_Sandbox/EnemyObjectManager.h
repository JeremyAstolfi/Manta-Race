#ifndef __EnemyObjectMANAGER_H_
#define __EnemyObjectMANAGER_H_

#include "RE\ReEngAppClass.h"
#include "EnemyObject.h"

//System Class
class EnemyObjectManager
{
	uint m_nEntityCount = 0; //number of elements in the list
	static EnemyObjectManager* m_pInstance; // Singleton pointer
	std::vector<EnemyObject*> m_lEntity; //list of elements
	std::map<String, uint> m_map;//Map relating the mesh and the index
	BoundingObjectManager* m_pColliderManager = nullptr; //Collider manager
public:

	static EnemyObjectManager* GetInstance();

	static void ReleaseInstance(void);

	int GetEntityCount(void);

	void AddEntity(EnemyObject* a_nEntity);

	void AddEntity(String a_sEntity);

	void SetValues(vector3 a_v3Acceleration, float a_fMass, float a_fMaxAcc, String a_sEntity);

	EnemyObject* GetEntity(int a_nIndex);

	EnemyObject* GetEntity(String a_sEntity);

	int GetIndex(String a_sEntity);

	void Update(void);

	void SetMaxAcc(float a_fMaxAcc, String a_sEntity);

	void SetMass(float a_fMass, String a_sEntity);

	void SetPosition(vector3 a_v3Position, String a_sEntity);

	void SetVelocity(vector3 a_v3Velocity, String a_sEntity);

	void SetAcceleration(vector3 a_v3Acceleration, String a_sEntity);

private:

	EnemyObjectManager(void);

	EnemyObjectManager(EnemyObjectManager const& other);

	EnemyObjectManager& operator=(EnemyObjectManager const& other);

	~EnemyObjectManager(void);

	void Release(void);

	void Init(void);
};

#endif //__EnemyObjectMANAGER_H_
