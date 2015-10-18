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
	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper");
	m_v3Rotation = vector3(10.0f, 12.0f, 21.0f);
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

	static int nProgress = 0;

	float fPercentage = MapValue(static_cast<float>(nProgress), 0.0f, 360.0f, 0.0f, 1.0f);

	vector3 v3StartX = vector3(0.0f, 0.0f, 0.0f);
	vector3 v3EndX = vector3(360.0f, 0.0f, 0.0f);

	m_v3Rotation = glm::lerp(v3StartX, v3EndX, fPercentage);

	matrix4 rotX = glm::rotate(matrix4(IDENTITY), m_v3Rotation.x, REAXISX);
	matrix4 rotY = glm::rotate(matrix4(IDENTITY), m_v3Rotation.y, REAXISY);
	matrix4 rotZ = glm::rotate(matrix4(IDENTITY), m_v3Rotation.z, REAXISZ);

	m_pMeshMngr->SetModelMatrix(rotX * rotY * rotZ, "Creeper");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	m_pGrid->Render(); //renders the XY grid with a 100% scale

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}
