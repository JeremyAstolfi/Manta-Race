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