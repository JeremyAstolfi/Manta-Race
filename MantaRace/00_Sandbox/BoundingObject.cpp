#include "BoundingObject.h"


BoundingObject::BoundingObject()
{
}

BoundingObject::BoundingObject(std::vector<vector3> pts)
{
	Init();
	//pts = points
	int ptsCount = pts.size();
	
	if (ptsCount == 0)
		return;

	m_v3Max = m_v3Min = pts[0];
	for (uint i = 1; i < ptsCount; i++)
	{
		if (m_v3Min.x > pts[i].x) //If min is larger than current
			m_v3Min.x = pts[i].x;
		else if (m_v3Max.x < pts[i].x)//if max is smaller than current
			m_v3Max.x = pts[i].x;

		if (m_v3Min.y > pts[i].y) //If min is larger than current
			m_v3Min.y = pts[i].y;
		else if (m_v3Max.y < pts[i].y)//if max is smaller than current
			m_v3Max.y = pts[i].y;

		if (m_v3Min.z > pts[i].z) //If min is larger than current
			m_v3Min.z = pts[i].z;
		else if (m_v3Max.z < pts[i].z)//if max is smaller than current
			m_v3Max.z = pts[i].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth.x = glm::distance(vector3(m_v3Min.x, 0.0f, 0.0f), vector3(m_v3Max.x, 0.0f, 0.0f)) / 2.0f;
	m_v3HalfWidth.y = glm::distance(vector3(0.0f, m_v3Min.y, 0.0f), vector3(0.0f, m_v3Max.y, 0.0f)) / 2.0f;
	m_v3HalfWidth.z = glm::distance(vector3(0.0f, 0.0f, m_v3Min.z), vector3(0.0f, 0.0f, m_v3Max.z)) / 2.0f;

}


BoundingObject::~BoundingObject()
{
}

void BoundingObject::Init()
{
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_v3CenterG = vector3(0.0f);
	m_v3MinG = vector3(0.0f);
	m_v3MaxG = vector3(0.0f);

	m_v3HalfWidth = vector3(0.0f);
	m_v3HalfWidthG = vector3(0.0f);
}

matrix4 BoundingObject::GetModelMatrix(void){ return m_m4ToWorld; }
vector3 BoundingObject::GetCenterLocal(void){ return m_v3Center; }
vector3 BoundingObject::GetCenterGlobal(void){ return m_v3CenterG; }
vector3 BoundingObject::GetHalfWidthLocal(void){ return m_v3HalfWidth; }
vector3 BoundingObject::GetHalfWidthGlobal(void){ return m_v3HalfWidthG; }

vector3 BoundingObject::GetRadiusV3()
{
	//this emthod finds the point ont the axis fruthest from the center in both the minimum and maximum dirwection
	//and it gets the furthest from the center of those two, and then returns a vector with the largest distance stored in all values
	vector3 maxDist = vector3(0.0f); //m_v3MaxG * vector3((m_v3MaxG.x - m_v3MinG.x) / 2.0f, (m_v3MaxG.y - m_v3MinG.y) / 2.0f, (m_v3MaxG.z - m_v3MinG.z) / 2.0f);
	vector3 minDist = vector3(0.0f);

	//find the axis that is furthest out in maximum direction
	if (glm::distance(vector3(m_v3MaxG.x), m_v3CenterG) > glm::distance(maxDist, m_v3CenterG))
		maxDist = vector3(m_v3MaxG.x);
	if (glm::distance(vector3(m_v3MaxG.y), m_v3CenterG) > glm::distance(maxDist, m_v3CenterG))
		maxDist = vector3(m_v3MaxG.y);
	if (glm::distance(vector3(m_v3MaxG.z), m_v3CenterG) > glm::distance(maxDist, m_v3CenterG))
		maxDist = vector3(m_v3MaxG.z);
	
	//find the axis furthest out in minimum direction
	if (glm::distance(vector3(m_v3MinG.x), m_v3CenterG) < glm::distance(minDist, m_v3CenterG))
		minDist = vector3(m_v3MinG.x);
	if (glm::distance(vector3(m_v3MinG.y), m_v3CenterG) < glm::distance(maxDist, m_v3CenterG))
		minDist = vector3(m_v3MinG.y);
	if (glm::distance(vector3(m_v3MinG.z), m_v3CenterG) < glm::distance(maxDist, m_v3CenterG))
		minDist = vector3(m_v3MinG.z);

	//get them in radius form from center
	float maxDistFloat = glm::distance(maxDist, m_v3CenterG);
	float minDistFloat = glm::distance(minDist, m_v3CenterG);
	vector3 returnVec = vector3(0.0f);

	//find which one is bigger then return a vector populated with said distance
	if (minDistFloat > maxDistFloat)
		returnVec = vector3(minDistFloat);
	else
		returnVec = vector3(maxDistFloat);

	return returnVec;
}

float BoundingObject::GetRadiusF()
{
	vector3 rad = this->GetRadiusV3();
	return rad.x;
}

void BoundingObject::SetModelMatrix(matrix4 _m4ToWorld)
{
	//If there are no changes in the Model Matrix there is no need
	//of doing further calculations
	if (m_m4ToWorld == _m4ToWorld)
		return;

	m_m4ToWorld = _m4ToWorld;
	//Calculate the vertex that makes the box
	vector3 v3Corner[8];
	v3Corner[0] = vector3(m_v3Min.x, m_v3Min.y, m_v3Min.z);
	v3Corner[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	v3Corner[2] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	v3Corner[3] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);

	v3Corner[4] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	v3Corner[5] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	v3Corner[6] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	v3Corner[7] = vector3(m_v3Max.x, m_v3Max.y, m_v3Max.z);
	//Get vectors in global space
	for (uint nVertex = 0; nVertex < 8; nVertex++)
	{
		v3Corner[nVertex] = vector3(m_m4ToWorld * vector4(v3Corner[nVertex], 1.0f));
	}

	//Get the max and min out of the list
	m_v3MaxG = m_v3MinG = v3Corner[0];
	for (uint nVertex = 1; nVertex < 8; nVertex++)
	{
		if (m_v3MinG.x > v3Corner[nVertex].x) //If min is larger than current
			m_v3MinG.x = v3Corner[nVertex].x;
		else if (m_v3MaxG.x < v3Corner[nVertex].x)//if max is smaller than current
			m_v3MaxG.x = v3Corner[nVertex].x;

		if (m_v3MinG.y > v3Corner[nVertex].y) //If min is larger than current
			m_v3MinG.y = v3Corner[nVertex].y;
		else if (m_v3MaxG.y < v3Corner[nVertex].y)//if max is smaller than current
			m_v3MaxG.y = v3Corner[nVertex].y;

		if (m_v3MinG.z > v3Corner[nVertex].z) //If min is larger than current
			m_v3MinG.z = v3Corner[nVertex].z;
		else if (m_v3MaxG.z < v3Corner[nVertex].z)//if max is smaller than current
			m_v3MaxG.z = v3Corner[nVertex].z;
	}
	m_v3CenterG = (m_v3MinG + m_v3MaxG) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidthG.x = m_v3MaxG.x - m_v3MinG.x / 2.0f;
	m_v3HalfWidthG.y = m_v3MaxG.y - m_v3MinG.y / 2.0f;
	m_v3HalfWidthG.z = m_v3MaxG.z - m_v3MinG.z / 2.0f;
}

bool BoundingObject::IsBoxColliding(BoundingObject* other)
{
	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(other->m_m4ToWorld * vector4(other->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(other->m_m4ToWorld * vector4(other->m_v3Max, 1.0f));

	/*
	Are they colliding?
	For boxes we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	bool bColliding = true;

	//Check for X
	if (m_v3MaxG.x < other->m_v3MinG.x)
		bColliding = false;
	if (m_v3MinG.x > other->m_v3MaxG.x)
		bColliding = false;

	//Check for Y
	if (m_v3MaxG.y < other->m_v3MinG.y)
		bColliding = false;
	if (m_v3MinG.y > other->m_v3MaxG.y)
		bColliding = false;

	//Check for Z
	if (m_v3MaxG.z < other->m_v3MinG.z)
		bColliding = false;
	if (m_v3MinG.z > other->m_v3MaxG.z)
		bColliding = false;

	return bColliding;
}

bool BoundingObject::IsSphereColliding(BoundingObject* other)
{
	bool bColliding = true;

	float otherTheta = other->GetRadiusF();
	float thisTheta = this->GetRadiusF();

	//CHECK X
	if (this->m_v3CenterG.x + thisTheta > other->m_v3CenterG.x - otherTheta)
		bColliding = false;
	if (this->m_v3CenterG.x - thisTheta > other->m_v3CenterG.x + otherTheta)
		bColliding = false;
	
	//CHECK Y
	if (this->m_v3CenterG.y + thisTheta > other->m_v3CenterG.y - otherTheta)
		bColliding = false;
	if (this->m_v3CenterG.y - thisTheta > other->m_v3CenterG.y + otherTheta)
		bColliding = false;

	//CHECK Z
	if (this->m_v3CenterG.z + thisTheta > other->m_v3CenterG.z - otherTheta)
		bColliding = false;
	if (this->m_v3CenterG.z - thisTheta > other->m_v3CenterG.z + otherTheta)
		bColliding = false;

	return bColliding;
}

vector3 BoundingObject::GetColor(){ return this->color; }

void BoundingObject::SetColor(vector3 _v3Color)
{
	this->color = _v3Color;
}

bool BoundingObject::GetVisibility(){ return this->visibilty; }

void BoundingObject::SetVisibility(bool _visible)
{
	this->visibilty = _visible;
}
