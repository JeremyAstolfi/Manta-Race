#include "MyOctant.h"
//  MyOctant
void MyOctant::Init(void)
{
	m_v3Center = vector3(0.0f);

	m_fsize = 0.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	parent = nullptr;
	for (int i = 0; i < 8; i++)
	{
		child[i] = nullptr;
	}
}
void MyOctant::Swap(MyOctant& other)
{
	std::swap(parent, other.parent);
	for (int i = 0; i < 8; i++)
	{
		std::swap(child[i], other.child[i]);
	}
	std::swap(m_v3Center, other.m_v3Center);

	std::swap(m_fsize, other.m_fsize);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);

	std::swap(childrenAmount, other.childrenAmount);
}
void MyOctant::Release(void) { if (parent == nullptr){ ClearTree(); } }
//The big 3
MyOctant::MyOctant(vector3 v3_center, float size)
{
	//Init the default values
	Init();
	m_v3Center = v3_center;
	m_fsize = size;
}
MyOctant::MyOctant(MyOctant const& other)
{
	m_v3Center = other.m_v3Center;
	m_fsize = other.m_fsize;
	for (int i = 0; i < 8; i++)
	{
		child[i] = other.child[i];
	}
	parent = other.parent;
	m_pMeshMngr = other.m_pMeshMngr;
}
MyOctant& MyOctant::operator=(MyOctant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
MyOctant::~MyOctant() { Release(); };
//Accessors
float MyOctant::GetSize(void) { return m_fsize; }
vector3 MyOctant::GetCenter(void) { return m_v3Center; }
void MyOctant::DisplayBox(vector3 a_v3Color)
{ 
	for (uint g = 0; g < 8; g++)
	{
		if (child[g] != nullptr)
		child[g]->DisplayBox();
	}
	m_pMeshMngr->AddCubeToQueue(glm::translate(IDENTITY_M4, m_v3Center) *
		glm::scale(vector3(m_fsize) * 2.0f), a_v3Color, WIRE);
}

void MyOctant::Subdivide(void)
{
	for (uint q = 0; q < 8; q++)
	{
		child[q] = new MyOctant(SetChildCenter(GetCenter(), q), m_fsize / 2.0f);
		child[q]->parent = this;
		childrenAmount++;
	}
}

void MyOctant::ClearTree(void)
{
	for (uint n = 0; n < childrenAmount; n++)
	{
		child[n]->ClearTree();
	}
	if (child != nullptr)
	{
		delete[] child;
	}
}

MyOctant* MyOctant::GetChild(uint nChild)
{
	if (nChild >= 8)
	{
		return nullptr;
	}
	return child[nChild];
}

vector3 MyOctant::SetChildCenter(vector3 parentCenter, int childIndex)
{
	float nSize = m_fsize / 2.0f;
	switch (childIndex)
	{
	case 0:
		return parentCenter + vector3(nSize, nSize, nSize);
		break;
	case 1:
		return parentCenter + vector3(-nSize, nSize, nSize);
		break;
	case 2:
		return parentCenter + vector3(-nSize, -nSize, nSize);
		break;
	case 3:
		return parentCenter + vector3(nSize, -nSize, nSize);
		break;
	case 4:
		return parentCenter + vector3(nSize, nSize, -nSize);
		break;
	case 5:
		return parentCenter + vector3(-nSize, nSize, -nSize);
		break;
	case 6:
		return parentCenter + vector3(-nSize, -nSize, -nSize);
		break;
	case 7:
		return parentCenter + vector3(nSize, -nSize, -nSize);
		break;
	default:
		return parentCenter;
		break;
	}
}
