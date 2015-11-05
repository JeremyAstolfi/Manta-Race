#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Sandbox"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	m_pMeshMngr->LoadModel("Minecraft\\MC_Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper");
	bObjManager->AddBox("Steve",m_pMeshMngr->GetVertexList("Steve"));
	bObjManager->AddBox("Creeper",m_pMeshMngr->GetVertexList("Creeper"));
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

	//Call the arcball method
	ArcBall();




	m_pMeshMngr->SetModelMatrix(glm::translate(bObjManager->boundingObjects[0]->GetPosition()) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(bObjManager->boundingObjects[1]->GetPosition()), "Creeper");

	bObjManager->boundingObjects[0]->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Steve"));
	bObjManager->boundingObjects[1]->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Creeper"));

	bObjManager->boundingObjects[0]->SetVisibility(true);
	bObjManager->boundingObjects[1]->SetVisibility(true);
	//bObjManager->RenderBO(m_pMeshMngr);
	//Adds all loaded instance to the render list


	m_pMeshMngr->AddCubeToQueue(glm::translate(bObjManager->boundingObjects[0]->GetCenterGlobal()) * glm::scale(bObjManager->boundingObjects[0]->GetHalfWidthGlobal() * 2.0f), bObjManager->boundingObjects[0]->GetColor(), WIRE);
	m_pMeshMngr->AddCubeToQueue(glm::translate(bObjManager->boundingObjects[1]->GetCenterGlobal()) * glm::scale(bObjManager->boundingObjects[1]->GetHalfWidthGlobal() * 2.0f), bObjManager->boundingObjects[1]->GetColor(), WIRE);

	m_pMeshMngr->AddCubeToQueue(bObjManager->boundingObjects[0]->GetModelMatrix() * glm::translate(IDENTITY_M4, bObjManager->boundingObjects[0]->GetCenterLocal()) * glm::scale(bObjManager->boundingObjects[0]->GetHalfWidthLocal() * 2.0f), bObjManager->boundingObjects[0]->GetColor(), WIRE);
	m_pMeshMngr->AddCubeToQueue(bObjManager->boundingObjects[1]->GetModelMatrix() * glm::translate(IDENTITY_M4, bObjManager->boundingObjects[1]->GetCenterLocal()) * glm::scale(bObjManager->boundingObjects[1]->GetHalfWidthLocal() * 2.0f), bObjManager->boundingObjects[1]->GetColor(), WIRE);
	
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
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
	super::Release(); //release the memory of the inherited fields
}