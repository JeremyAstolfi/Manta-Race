#include "MyBoundingBoxClass.h"
//  MyBoundingBoxClass
void MyBoundingBoxClass::Init(void)
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
void MyBoundingBoxClass::Swap(MyBoundingBoxClass& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3CenterG, other.m_v3CenterG);
	std::swap(m_v3MinG, other.m_v3MinG);
	std::swap(m_v3MaxG, other.m_v3MaxG);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
	std::swap(m_v3HalfWidthG, other.m_v3HalfWidthG);
}
void MyBoundingBoxClass::Release(void)
{

}
//The big 3
MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> a_lVectorList)
{
	//Init the default values
	Init();

	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth.x = glm::distance(vector3(m_v3Min.x, 0.0f, 0.0f), vector3(m_v3Max.x, 0.0f, 0.0f)) / 2.0f;
	m_v3HalfWidth.y = glm::distance(vector3(0.0f, m_v3Min.y, 0.0f), vector3(0.0f, m_v3Max.y, 0.0f)) / 2.0f;
	m_v3HalfWidth.z = glm::distance(vector3(0.0f, 0.0f, m_v3Min.z), vector3(0.0f, 0.0f, m_v3Max.z)) / 2.0f;
	
}
MyBoundingBoxClass::MyBoundingBoxClass(MyBoundingBoxClass const& other)
{
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterG = other.m_v3CenterG;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;
}
MyBoundingBoxClass& MyBoundingBoxClass::operator=(MyBoundingBoxClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBoundingBoxClass temp(other);
		Swap(temp);
	}
	return *this;
}
MyBoundingBoxClass::~MyBoundingBoxClass(){ Release(); };
//Accessors
void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	//If there are no changes in the Model Matrix there is no need
	//of doing further calculations
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	//Calculate the vertex that makes the box

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
	m_v3HalfWidthG.x = glm::distance(vector3(m_v3MinG.x, 0.0f, 0.0f), vector3(m_v3MaxG.x, 0.0f, 0.0f)) / 2.0f;
	m_v3HalfWidthG.y = glm::distance(vector3(0.0f, m_v3MinG.y, 0.0f), vector3(0.0f, m_v3MaxG.y, 0.0f)) / 2.0f;
	m_v3HalfWidthG.z = glm::distance(vector3(0.0f, 0.0f, m_v3MinG.z), vector3(0.0f, 0.0f, m_v3MaxG.z)) / 2.0f;

}
matrix4 MyBoundingBoxClass::GetModelMatrix(void){ return m_m4ToWorld; }
vector3 MyBoundingBoxClass::GetCenterLocal(void){ return m_v3Center; }
vector3 MyBoundingBoxClass::GetCenterGlobal(void){ return m_v3CenterG; }
vector3 MyBoundingBoxClass::GetHalfWidth(void){ return m_v3HalfWidth; }
vector3 MyBoundingBoxClass::GetHalfWidthG(void){ return m_v3HalfWidthG; }
//--- Non Standard Singleton Methods
bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* const a_pOther)
{
	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

	/*
	Are they colliding?
	For boxes we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	bool bColliding = true;
	
	//Check for X
	if (m_v3MaxG.x < a_pOther->m_v3MinG.x)
		bColliding = false;
	if (m_v3MinG.x > a_pOther->m_v3MaxG.x)
		bColliding = false;

	//Check for Y
	if (m_v3MaxG.y < a_pOther->m_v3MinG.y)
		bColliding = false;
	if (m_v3MinG.y > a_pOther->m_v3MaxG.y)
		bColliding = false;

	//Check for Z
	if (m_v3MaxG.z < a_pOther->m_v3MinG.z)
		bColliding = false;
	if (m_v3MinG.z > a_pOther->m_v3MaxG.z)
		bColliding = false;

	return bColliding;
}

bool MyBoundingBoxClass::SeperationAxisTest(MyBoundingBoxClass* const a_pOther)
{
	MyBoundingBoxClass* thisBox = this;
	MyBoundingBoxClass* otherBox = a_pOther;
	
	matrix4 thisModelMatrix = thisBox->GetModelMatrix();
	thisBox->localAxes[0] = vector3(thisModelMatrix[0][0], thisModelMatrix[0][1], thisModelMatrix[0][2]);
	thisBox->localAxes[1] = vector3(thisModelMatrix[1][0], thisModelMatrix[1][1], thisModelMatrix[1][2]);
	thisBox->localAxes[2] = vector3(thisModelMatrix[2][0], thisModelMatrix[2][1], thisModelMatrix[2][2]);

	matrix4 otherModelMatrix = otherBox->GetModelMatrix();
	otherBox->localAxes[0] = vector3(otherModelMatrix[0][0], otherModelMatrix[0][1], otherModelMatrix[0][2]);
	otherBox->localAxes[1] = vector3(otherModelMatrix[1][0], otherModelMatrix[1][1], otherModelMatrix[1][2]);
	otherBox->localAxes[2] = vector3(otherModelMatrix[2][0], otherModelMatrix[2][1], otherModelMatrix[2][2]);

	float ra, rb;
	matrix4 r, absr;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			r[i][j] = glm::dot(thisBox->localAxes[i], otherBox->localAxes[j]);
		}
	}
	
	vector3 t = otherBox->GetCenterGlobal() - thisBox->GetCenterGlobal();

	t = vector3(glm::dot(t, thisBox->localAxes[0]), glm::dot(t, thisBox->localAxes[1]), glm::dot(t, thisBox->localAxes[2]));
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			absr[i][j] = abs(r[i][j]) + std::numeric_limits<float>::epsilon();;

	float thisE[3];
	thisE[0] = thisBox->GetHalfWidth().x;
	thisE[1] = thisBox->GetHalfWidth().y;
	thisE[2] = thisBox->GetHalfWidth().z;

	float otherE[3];
	otherE[0] = otherBox->GetHalfWidth().x;
	otherE[1] = otherBox->GetHalfWidth().y;
	otherE[2] = otherBox->GetHalfWidth().z;

	for (int i = 0; i < 3; i++){
		ra = thisE[i];
		rb = otherE[0] * absr[i][0] + otherE[1] * absr[1][i] + otherE[2] * absr[i][2];
		if (abs(t[i]) > ra + rb)
			return true;
	}

	for (int i = 0; i < 3; i++)
	{

	}

	/*
	// Each element of this list contains a vector of two points that form an edge;
	std::vector<std::vector<vector3>> Edges;
	std::vector<std::vector<vector3>> oEdges;
	std::vector<vector3> Edge0;
	Edge0.push_back(v3Corner[0]);
	Edge0.push_back(v3Corner[1]);
	Edges.push_back(Edge0);
	Edge0.pop_back();
	Edge0.pop_back();
	std::vector<vector3> oEdge0;
	oEdge0.push_back(a_pOther->v3Corner[0]);
	oEdge0.push_back(a_pOther->v3Corner[1]);
	oEdges.push_back(Edge0);
	oEdge0.pop_back();
	oEdge0.pop_back();

	Edge0.push_back(v3Corner[0]);
	Edge0.push_back(v3Corner[2]);
	Edges.push_back(Edge0);
	Edge0.pop_back();
	Edge0.pop_back();

	oEdge0.push_back(a_pOther->v3Corner[0]);
	oEdge0.push_back(a_pOther->v3Corner[2]);
	oEdges.push_back(Edge0);
	oEdge0.pop_back();
	oEdge0.pop_back();


	Edge0.push_back(v3Corner[0]);
	Edge0.push_back(v3Corner[4]);
	Edges.push_back(Edge0);
	Edge0.pop_back();
	Edge0.pop_back();

	oEdge0.push_back(a_pOther->v3Corner[0]);
	oEdge0.push_back(a_pOther->v3Corner[4]);
	oEdges.push_back(Edge0);
	oEdge0.pop_back();
	oEdge0.pop_back();
	
	for (int i = 0; i < 3; i++)
	{
		//cross product of edge 1 and the other objects edge 1,
		// edge 1 is the vector produced from subtracting corner 0 from corner 1;
		vector3 m = glm::cross(Edges[0][1] - Edges[0][0], oEdges[0][1] - oEdges[0][0]);
		if (m != vector3(0.0f))
		{
			//potential seperating axis
			//taken from page 163 of orange book
			float r = (glm::distance(Edges[0][1] , Edges[0][0]) * abs(glm::dot(m, glm::normalize(Edges[0][1] - Edges[0][0]))))+
				(glm::distance(Edges[1][1], Edges[1][0]) * abs(glm::dot(m, glm::normalize(Edges[1][1] - Edges[1][0])))) +
				(glm::distance(Edges[2][1] , Edges[2][0]) * abs(glm::dot(m, glm::normalize(Edges[2][1] - Edges[2][0]))));
			float s = glm::distance(m, m_v3CenterG);
			if (abs(s) <= r)
			{
				return true;
			}
		}
		else
		{// page 159 of orange book
			vector3 n = glm::cross(Edges[i][1] - Edges[i][0], oEdges[i][0] - Edges[i][0]);
			m = glm::cross(Edges[i][1] - Edges[i][0], n);
			if (m != vector3(0.0f))
			{
				//potential seperating axis
				//taken from page 163 of orange book
				float r = (glm::distance(Edges[0][1], Edges[0][0]) * abs(glm::dot(m, glm::normalize(Edges[0][1] - Edges[0][0])))) +
					(glm::distance(Edges[1][1], Edges[1][0]) * abs(glm::dot(m, glm::normalize(Edges[1][1] - Edges[1][0])))) +
					(glm::distance(Edges[2][1], Edges[2][0]) * abs(glm::dot(m, glm::normalize(Edges[2][1] - Edges[2][0]))));
				float s = glm::distance(m, m_v3CenterG);
				if (abs(s) <= r)
				{
					return true;
				}
			}

		}
			
	}*/



	return false;
}