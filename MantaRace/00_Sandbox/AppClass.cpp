#include "AppClass.h"
MantaRayControls* MantaRayControls::instance = nullptr;
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


	//m_pMeshMngr->LoadModel("MantaRay\\Ray_HighPoly.obj", "Manta");
	m_pMeshMngr->LoadModel("MantaRace\\crosshair.obj", "crosshair");

	
	

	
	mousePos = sf::Vector2i(m_pWindow->GetWidth() / 2, m_pWindow->GetHeight() / 2);
	v3MousePos = vector3(0.0f);
	sf::Mouse::setPosition(sf::Vector2i(m_pWindow->GetWidth() / 2, m_pWindow->GetHeight() / 2));

}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//First person camera movement
	if (m_bFPC == true)
	//	CameraRotation(); 

	ProcessMouse();
	
	//Call the arcball method
	ArcBall();




	//m_pMeshMngr->AddCylinderToQueue(IDENTITY_M4*glm::scale(0.25f,10.0f,0.25f), vector3(255.0f,0.0f,255.0f), SOLID);
	//m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "Manta");


	matrix4 projection = m_pCameraMngr->GetViewMatrix() * m_pCameraMngr->GetProjectionMatrix();
	matrix4 projInverse = glm::inverse(projection);

	float in[4];
	float winZ = 1.0f;

	in[0] = (2.0f*((float)(mousePos.x - 0) / (float)m_pWindow->GetWidth())) - 1.0f;
	in[1] = 1.0f -(2.0f*((float)mousePos.y - 0) / ((float)m_pWindow->GetHeight()));
	in[2] = 2.0 * winZ - 1.0f;
	in[3] = 1.0f;

	vector4 tempMousePos = vector4(in[0], in[1], in[2], in[3]);
	vector4 mouseGetPosition = projInverse * tempMousePos;
	//mouseGetPosition.w = 1.0f * mouseGetPosition.w;
	//mouseGetPosition.x *= mouseGetPosition.w;
	//mouseGetPosition.y *= mouseGetPosition.w;
	//mouseGetPosition.z *= mouseGetPosition.w;
	v3MousePos = vector3(mouseGetPosition.x, mouseGetPosition.y, mouseGetPosition.z);
	

	



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