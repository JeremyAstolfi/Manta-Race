
#ifndef __ENEMYOBJECT_H_
#define __ENEMYOBJECT_H_

#include "RE\ReEngAppClass.h"
#include "BoundingObjectManager.h"

class EnemyObject
{
	vector3 m_v3Position = vector3(); //Position of the Entity
	quaternion m_qOrientation = quaternion();//Orientation of the Entity
	vector3 m_v3Scale = vector3(); //Scale of the Entity

	vector3 m_v3Velocity = vector3(); //Velocity of the Entity
	vector3 m_v3Acceleration = vector3(); //Acceleration of the Entity

	float m_fMass = 1.0f;	//Mass of the Entity
	float m_fMaxAcc = 0.1f; //Limit of the acceleration of the entity

	String m_sName = ""; // Name index

	BoundingObjectManager* m_pColliderManager = nullptr; //Collider manager
	MeshManagerSingleton* m_pMeshManager = nullptr;//Mesh Manager

public:
	EnemyObject(String a_sName);

	EnemyObject(EnemyObject const& other);

	EnemyObject& operator=(EnemyObject const& other);

	~EnemyObject();

	void Update(void);

	void SetMaxAcc(float a_fMaxAcc);

	void SetMass(float a_fMass);

	void SetPosition(vector3 a_v3Position);

	void SetVelocity(vector3 a_v3Velocity);

	void SetAcceleration(vector3 a_v3Acceleration);

	vector3 GetAcceleration(void);

	vector3 GetPosition(void);
	vector3 GetVelocity(void);
	String GetName(void);

protected:

	void Init(void);

	void Swap(EnemyObject& other);

	void Release(void);
};
#endif //__ENEMYOBJECT_H_
