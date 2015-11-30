#pragma once

#include "RE\ReEngAppClass.h"
#include <math.h>
class MantaRayControls
{

public:
	static MantaRayControls* instance;	//Singleton of the Controls
	MeshManagerSingleton* meshManager;

	vector3 rayPosition = vector3(0.0f, 0.0f, 3.0f); //Manta Position
	vector3 rayVelocity = vector3(0.0f, 0.0f, 0.0f); //Manta Velocity
	vector3 rayAcceleration = vector3(0.0f, 0.0f, 0.0f); //Manta Acceleration
	float rayMass = 1.0f;
	float rayMaxAcceleration = 0.005f;
	float rayFriction = 0.0005f;
	float theta = 0.0f;
	vector3 m_v3Forward; //Manta view vector
	vector3 m_v3Up; //Manta up vector

	///<summary> Constructs the singleton pointer </summary>
	static MantaRayControls* GetInstance(){
		if (instance == nullptr)
			instance = new MantaRayControls();
		return instance;
	}

	///<summary> Releases the singleton pointer </summary>
	static void ReleaseInstance(){
		if (instance != nullptr){
			delete instance;
			instance = nullptr;
		}
	}

	///<summary> Updates physics and any other events that occur within the Manta Ray Controls
	void Update(void);

	///<summary> Moves the ray forward, NOTE: This is currently not implemented </summary>
	void MoveForward(float velocity);

	///<summary> Moves the ray sideways </summary>
	void MoveSideways(float velocity);

	///<summary> Move the ray vertically </summary>
	void MoveVertical(float velocity);

	///<summary> Rotrate manta ray </summary>
	void Rotate(float speed);

	///<summary> Sets the ray's position through addition</summary>
	void SetPosition(vector3 _position);

	///<summary> Sets the ray's velocity through addition</summary>
	void SetVelocity(vector3 _velocity);

	///<summary> Sets the ray's acceleration through addition</summary>
	void SetAcceleration(vector3 _acceleration);

	///<summary> Draws a cylinder to display the laser </summary>
	void FireRay(vector2);

	///<summary> Returns the ray's position </summary>
	vector3 GetPosition(void);

	///<summary> Returns the ray's velocity </summary>
	vector3 GetVelocity(void);

	///<summary> Returns the ray's acceleration </summary>
	vector3 GetAcceleration(void);

	///<summary> Set the max value the ray can accelerate </summary>
	void SetMaxAcc(float _maxAcceleration);

	///<summary> Set mass for the ray </summary>
	void SetMass(float _mass);

	///<summary> Set friction to oppose the ray's acceleration </summary>
	void SetFriction(float _friction);

private:
	//Boundaries within the manta must be contained
	vector3 boundary = vector3(0.0f);

	///<summary> Constructor </summary>
	MantaRayControls(void);

	///<summary> Copy Constructor </summary>
	MantaRayControls(MantaRayControls const& other);

	///<summary> Copy Assignment Constructor </summary>
	MantaRayControls& operator=(MantaRayControls const& other);

	///<summary> Destructor </summary>
	~MantaRayControls(void);
};


