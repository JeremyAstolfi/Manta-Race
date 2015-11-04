#ifndef __BOUNDINGOBJECT_H_
#define __BOUNDINGOBJECT_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class BoundingObject
{
public:
	BoundingObject();
	~BoundingObject();

	BoundingObject(std::vector<vector3> pts);

	void Init();
	void SetModelMatrix(matrix4 _m4ToWorld);
	vector3 GetRadiusV3();
	vector3 maxDist;
	vector3 minDist;
	float GetRadiusF();

	bool IsBoxColliding(BoundingObject* other);
	bool IsSphereColliding(BoundingObject* other);

	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the box Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the box Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the box Class

	vector3 m_v3CenterG = vector3(0.0f); //Will store the center point of the box Class
	vector3 m_v3MinG = vector3(0.0f); //Will store the minimum vector of the box Class
	vector3 m_v3MaxG = vector3(0.0f); //Will store the maximum vector of the box Class

	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
	vector3 m_v3HalfWidthG = vector3(0.0f);//Will store half the size of all sides

};
#endif //__MYBOUNDINGBOXCLASS_H__
