#ifndef __BOUNDINGOBJECT_H_
#define __BOUNDINGOBJECT_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include <string.h>
class BoundingObject
{

	vector3 m_v3Position = vector3(0.0f);

	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the box Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the box Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the box Class

	vector3 m_v3CenterG = vector3(0.0f); //Will store the center point of the box Class
	vector3 m_v3MinG = vector3(0.0f); //Will store the minimum vector of the box Class
	vector3 m_v3MaxG = vector3(0.0f); //Will store the maximum vector of the box Class

	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
	vector3 m_v3HalfWidthG = vector3(0.0f);//Will store half the size of all sides
	vector3 color;
	bool visibilty = true;


public:
	BoundingObject();
	~BoundingObject();

	BoundingObject(std::vector<vector3> pts);
	String Model;
	void Init();
	void SetModelMatrix(matrix4 _m4ToWorld);
	vector3 GetPosition();
	void SetPosition(vector3 amount);
	vector3 GetRadiusV3();
	float GetRadiusF();
	matrix4 GetModelMatrix();
	vector3 GetCenterLocal();
	vector3 GetCenterGlobal();
	vector3 GetHalfWidthGlobal();
	vector3 GetHalfWidthLocal();
	vector3 GetColor();
	void SetColor(vector3 _v3Color);
	void SetVisibility(bool _visible);
	bool GetVisibility();
	
	bool IsBoxColliding(BoundingObject* other);
	bool IsSphereColliding(BoundingObject* other);

};
#endif //__MYBOUNDINGBOXCLASS_H__
