#include "AppClass.h"

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Sandbox"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.2f, 0.3f, 0.65f, 0.0f);
}

void AppClass::InitVariables(void)
{

	m_pWindow->SetFullscreen(true);
	m_pMeshMngr->LoadModel("MantaRace\\crosshair.obj", "crosshair");
	
	m_pMeshMngr->LoadModel("MantaRace\\newManta.obj", "MantaRay");
	mousePos = sf::Vector2i(m_pWindow->GetWidth() / 2, m_pWindow->GetHeight() / 2);
	v3MousePos = vector3(0.0f);
	sf::Mouse::setPosition(sf::Vector2i(m_pWindow->GetWidth() / 2, m_pWindow->GetHeight() / 2));
	for (int i = 0; i < enemies; i++)
	{
		m_pEOManage->AddEntity("Enemy" + i);	
		float xRand = static_cast <float> (xFloor + (xRange * rand() / (RAND_MAX + 1.0f)));
		float yRand = static_cast <float> (yFloor + (yRange * rand() / (RAND_MAX + 1.0f)));
		float zRand = static_cast <float> (zFloor + (zRange * rand() / (RAND_MAX + 1.0f)));
		EnemyObject* temp = m_pEOManage->GetEntity(i);
		temp->SetPosition(vector3(xRand, yRand, zRand));
		temp->SetVelocity(vector3(0.0f, 0.0f, .5f));
		temp->SetScale(vector3(0.33f));
		temp->SetVisibility(true);
		m_pMeshMngr->LoadModel("MantaRace\\Mine.obj", "Mine" + i);
		temp->~EnemyObject();
	}

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

	mantaRay->Update();

	v3MousePos = vector3(GetMousePosition().x, GetMousePosition().y, GetMousePosition().z);

	//enemies
	for (int i = 0; i < m_pEOManage->GetEntityCount(); i++)
	{
		EnemyObject* temp = m_pEOManage->GetEntity(i);
		if (temp->GetPosition().z > 15.0f)
		{
			float xRand = static_cast <float> (xFloor + (xRange * rand() / (RAND_MAX + 1.0f)));
			float yRand = static_cast <float> (yFloor + (yRange * rand() / (RAND_MAX + 1.0f)));
			float zRand = static_cast <float> (zFloor + (zRange * rand() / (RAND_MAX + 1.0f)));

			temp->SetPosition(vector3(xRand,yRand,zRand));
		}
	//	m_pMeshMngr->SetModelMatrix(glm::translate(temp->GetPosition()) * glm::scale(vector3(0.25f)), "Mine");
	}
	m_pEOManage->Update();
	
	//Updates the crosshairs
	m_pMeshMngr->SetModelMatrix(glm::translate(v3MousePos) * glm::scale(vector3(0.5f)), "crosshair");

	//Updates the manta ray
	m_pMeshMngr->SetModelMatrix(glm::translate(mantaRay->GetPosition()) * glm::scale(vector3(.33f, .33f, -.33f)), "MantaRay");

	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//this line renders all bounding objects that are tagged as visible (default)
	//bObjManager->RenderBO(m_pMeshMngr);

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	//m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	//m_pMeshMngr->Print("FPS:");
	//m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}

vector4 AppClass::GetMousePosition(void)
{
	matrix4 projection = m_pCameraMngr->GetViewMatrix() * m_pCameraMngr->GetProjectionMatrix();
	matrix4 projInverse = glm::inverse(projection);

	float in[4];
	float winZ = 1.0f;

	in[0] = (2.0f*((float)(mousePos.x - 0) / (float)m_pWindow->GetWidth())) - 1.0f;
	in[1] = 1.0f - (2.0f*((float)mousePos.y - 0) / ((float)m_pWindow->GetHeight()));
	in[2] = 2.0f * winZ - 1.0f;
	in[3] = 1.0f;


	in[1] = MapValue(in[1], 0.0f, 1.0f, 0.0f, 9.0f);
	in[0] = MapValue(in[0], 0.0f, 1.0f, 0.0f, 11.0f);
	vector4 tempMousePos = vector4(in[0], in[1], in[2], in[3]);
	vector4 mouseGetPosition = projInverse * tempMousePos;
	return mouseGetPosition;
}