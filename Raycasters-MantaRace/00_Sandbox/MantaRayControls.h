#pragma once

#include "RE\ReEngAppClass.h"
class MantaRayControls
{
public:
		static MantaRayControls* instance;	//Singleton of the Controls

		//vector3 m_v3Position = vector3(0.0f); //Manta Position
		vector3 rayPosition = vector3(0.0f, 0.0f, -5.0f);
		vector3 m_v3Forward; //Manta view vector
		vector3 m_v3Up; //Manta up vector

		//matrix4 m_m4Projection; //Projection
		//matrix4 m_m4View; //View
		//matrix4 m_m4MVP; //MVP

		//matrix4 m_m4ViewInverse; //Inverse of the view
		//matrix4 m_m4VPInverse; // Inverse of the View-Projection matrix

	public:

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


