/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/11
----------------------------------------------*/
#ifndef __MyOctant_H_
#define __MyOctant_H_

#include "RE\ReEng.h"

//System Class
class MyOctant
{
	float m_fsize = 0.0f; //Radius of the Bounding Object

	MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager Singleton

	MyOctant* parent;
	MyOctant* child[8];

	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Object Class
	int childrenAmount = 0;
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyOctant(vector3 v3_center, float size);
	/*
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	MyOctant(MyOctant const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	MyOctant& operator=(MyOctant const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyOctant(void);
	/*
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	- MyOctant& other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(MyOctant& other);
	float GetSize(void);
	vector3 GetCenter(void);
	void DisplayBox(vector3 a_v3Color = REDEFAULT);
	void Subdivide(void);
	void ClearTree(void);
	MyOctant* GetChild(uint nChild);
	vector3 SetChildCenter(vector3 parentCenter, int childIndex);


private:
	/*
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

#endif //__MyOctant_H__
