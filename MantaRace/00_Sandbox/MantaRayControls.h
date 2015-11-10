#pragma once

#include "RE\ReEngAppClass.h"
#include <math.h>
class MantaRayControls
{

public:
		static MantaRayControls* instance;	//Singleton of the Controls
		MeshManagerSingleton* meshManager;
		//vector3 m_v3Position = vector3(0.0f); //Manta Position
	
	vector3 rayPosition = vector3(0.0f, 0.0f, 3.0f);
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

	///<summary> Moves the ray forward, NOTE: This is currently not implemented </summary>
	void MoveForward(float velocity);

	///<summary> Moves the ray sideways </summary>
	void MoveSideways(float velocity);

	///<summary> Move the ray vertically </summary>
	void MoveVertical(float velocity);


	///<summary> Sets the ray's position </summary>
	void SetPosition(vector3 changeInPosition);


		///<summary> Draws a cylinder to display the laser </summary>
		void FireRay(vector2);

	///<summary> Returns the ray's position </summary>
	vector3 GetPosition(void);


private:
	///<summary> Constructor </summary>
	MantaRayControls(void);

	///<summary> Copy Constructor </summary>
	MantaRayControls(MantaRayControls const& other);

	///<summary> Copy Assignment Constructor </summary>
	MantaRayControls& operator=(MantaRayControls const& other);

	///<summary> Destructor </summary>
	~MantaRayControls(void);
};


