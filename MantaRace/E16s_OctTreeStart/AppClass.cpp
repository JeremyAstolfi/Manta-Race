#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("E16: Octree start"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(REAXISZ * 45.0f, REAXISY * 5.0f, REAXISY);

	m_pBOMngr = MyBOManager::GetInstance();
	
	m_pOctant = new MyOctant(vector3(0.0f), 20.0f);

	m_nInstances = 10;
	int nSquare = static_cast<int>(std::sqrt(m_nInstances));
	m_nInstances = nSquare * nSquare;
	for (int i = 0; i < nSquare; i++)
	{
		for (int j = 0; j < nSquare; j++)
		{
			String sInstance = "Cube_" + std::to_string(i) + "_" + std::to_string(j);
			matrix4 m4Positions = glm::translate(static_cast<float>(i - nSquare / 2.0f), static_cast<float>(j), 0.0f);
			m_pMeshMngr->LoadModel("Minecraft\\Cube.obj", sInstance, false, m4Positions);
			m_pBOMngr->AddObject(sInstance);
		}
	}
	m_pOctant->Subdivide();
	/*for (int q = 0; q < 2; q++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (q == 0)
			{
				m_pOctChildren[q][i] = m_pOctant->GetChild(i);
				m_pOctChildren[q][i]->Subdivide();
			}
			else
			{
				for (int w = 0; w < 8; w++)
				{
					m_pOctChildren[q][w] = m_pOctChildren[q - 1][i]->GetChild(w);
					m_pOctChildren[q][w]->Subdivide();
				}
			}
		}
	}*/
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();
	
	CheckForObjects(m_pOctant, 1);
	m_pMeshMngr->AddInstanceToRenderList("ALL");
	m_pOctant->DisplayBox(REBLUE);
	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
		
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	m_pBOMngr->ReleaseInstance();
	SafeDelete(m_pOctant);
	super::Release(); //release the memory of the inherited fields
}

void AppClass::CheckForObjects(MyOctant* currentNode, int _level)
{
	uint num = m_pBOMngr->GetPositions().size();
	for (int g = 0; g < 8; g++)
	{
		int withinIt = 0;
		for (int h = 0; h < num; h++)
		{
			if (m_pBOMngr->GetPositions()[h].x > (m_pOctant->GetChild(g)->GetCenter() - m_pOctant->GetChild(g)->GetSize()).x
				&&
				m_pBOMngr->GetPositions()[h].x < (m_pOctant->GetChild(g)->GetCenter() + m_pOctant->GetChild(g)->GetSize()).x
				&&
				m_pBOMngr->GetPositions()[h].y > (m_pOctant->GetChild(g)->GetCenter() - m_pOctant->GetChild(g)->GetSize()).y
				&&
				m_pBOMngr->GetPositions()[h].y < (m_pOctant->GetChild(g)->GetCenter() + m_pOctant->GetChild(g)->GetSize()).y
				&&
				m_pBOMngr->GetPositions()[h].z > (m_pOctant->GetChild(g)->GetCenter() - m_pOctant->GetChild(g)->GetSize()).z
				&&
				m_pBOMngr->GetPositions()[h].z < (m_pOctant->GetChild(g)->GetCenter() + m_pOctant->GetChild(g)->GetSize()).z
				)
			{
				withinIt++;
			}
			if (withinIt >= 3 && _level < 3)
			{
				currentNode->GetChild(g)->Subdivide();
				CheckForObjects(currentNode->GetChild(g), _level + 1);
			}
		}
	}
}