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
	m_pOctant = new MyOctant(vector3(0.0f), 5.0f);
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
		temp->SetVelocity(vector3(0.0f, 0.0f, .33f));
		temp->SetScale(vector3(0.33f));
		temp->SetVisibility(true);
		//m_pMeshMngr->LoadModel("MantaRace\\Mine.obj", "Mine" + i);
		m_pMeshMngr->LoadModel("MantaRace\\Shark.obj", "Enemy"+i);
		temp->isShark = true;
		temp->~EnemyObject();
	}
	m_pOctant->Subdivide();
}

void AppClass::Update(void)
{
	if (mantaRay->GetHealth() <= 0)
	{
		score = 0;
		mantaRay->SetHealth(10);
		m_pMeshMngr->Print("YOU DIED", vector3(255.0f, 0.0f, 0.0f)); m_pMeshMngr->Print("YOU DIED", vector3(255.0f, 0.0f, 0.0f));
		m_pMeshMngr->Print("YOU DIED", vector3(255.0f, 0.0f, 0.0f)); m_pMeshMngr->Print("YOU DIED", vector3(255.0f, 0.0f, 0.0f));
	}
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
		vector3 attackVec = vector3(0.0f);
		EnemyObject* temp = m_pEOManage->GetEntity(i);
		if (!temp->isDead){
			if (temp->GetPosition().z > 15.0f)
			{
				temp-> isDead = true;
			}

			if (temp->isShark && glm::distance(temp->GetPosition(), mantaRay->GetPosition()) < 10.0f)
			{
				attackVec = temp->GetPosition() - mantaRay->GetPosition();
				attackVec = glm::normalize(attackVec);
				attackVec *= 0.125f;
				attackVec.z = 0.0f;

				temp->SetPosition(temp->GetPosition() - attackVec);

				//implement collision detection here
				if (temp->GetBoundingObject()->IsBoxColliding(bObjManager->boundingObjects[mantaRay->boIndex])){
					mantaRay->SetHealth(mantaRay->health - 1);
					score -= 500;
					std::cout << "HIT";
					temp->isDead = true;
					//temp->~EnemyObject();
				}
			}
		}
		else{
			float xRand = static_cast <float> (xFloor + (xRange * rand() / (RAND_MAX + 1.0f)));
			float yRand = static_cast <float> (yFloor + (yRange * rand() / (RAND_MAX + 1.0f)));
			float zRand = static_cast <float> (zFloor + (zRange * rand() / (RAND_MAX + 1.0f)));

			temp->SetPosition(vector3(xRand, yRand, zRand));
			temp->isDead = false;
			//temp->~EnemyObject();
		}
	//	m_pMeshMngr->SetModelMatrix(glm::translate(temp->GetPosition()) * glm::scale(vector3(0.25f)), "Mine");
	}
	m_pEOManage->Update();
	
	//Updates the crosshairs
	m_pMeshMngr->SetModelMatrix(glm::translate(v3MousePos) * glm::scale(vector3(0.5f)), "crosshair");

	//Updates the manta ray
	m_pMeshMngr->SetModelMatrix(glm::translate(mantaRay->GetPosition()) * glm::scale(vector3(.33f, .33f, -.33f)), "MantaRay");

	//m_pMeshMngr->AddInstanceToRenderList("ALL");
	m_pMeshMngr->AddInstanceToRenderList("crosshair");
	m_pMeshMngr->AddInstanceToRenderList("MantaRay");

	m_pMeshMngr->AddPlaneToQueue(glm::rotate(glm::translate(vector3(0, -6, -250)) * glm::scale(vector3(500.0f, 500.0f, 500.0f)),-90.0f,vector3(1,0,0)), vector3(0.0, 0.3, 0.3));
	//m_pMeshMngr->AddPlaneToQueue(glm::translate(vector3(2, 1, 0)) * glm::scale(vector3(1.0f, 1.0f, 1.0f)), vector3(1, 1, 1));
	//m_pMeshMngr->AddPlaneToQueue(glm::translate(glm::rotate(vector3(0, 0, 0), 90.0f, vector3(0, 0, 0))) * glm::scale(vector3(1.0f, 1.0f, 1.0f)), vector3(1, 1, 1));

	//this line renders all bounding objects that are tagged as visible (default)
	//bObjManager->RenderBO(m_pMeshMngr);
	if (OctTree){
	
		CheckForObjects(m_pOctant, 1);
		m_pOctant->DisplayBox(REBLUE);
	}
	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	int timeTick = (clock() - previousTime) / CLOCKS_PER_SEC;
	int currentTime = timeTick;
	m_pMeshMngr->Print("Score: ", REWHITE);
	m_pMeshMngr->PrintLine(std::to_string(score + currentTime * 100), RERED);
	if (currentTime < 0)
	{
		previousTime = clock();
	}
	m_pMeshMngr->Print("Health: ", REWHITE);
	m_pMeshMngr->Print(std::to_string(mantaRay->GetHealth()), RERED);
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
	SafeDelete(m_pOctant);
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
void AppClass::CheckForObjects(MyOctant* currentNode, int _level)
{
	uint num = bObjManager->GetPositions().size();
	for (int g = 0; g < 8; g++)
	{
		int withinIt = 0;
		for (int h = 0; h < num; h++)
		{
			if (currentNode->GetChild(g) != nullptr){
				BoundingObject* test = bObjManager->GetBoundingObject(h);
				if (bObjManager->GetPositions()[h].x + test->GetHalfWidthLocal().x >(currentNode->GetChild(g)->GetCenter().x - currentNode->GetChild(g)->GetSize())
					&&
					bObjManager->GetPositions()[h].x - test->GetHalfWidthLocal().x < (currentNode->GetChild(g)->GetCenter().x + currentNode->GetChild(g)->GetSize())
					&&
					bObjManager->GetPositions()[h].y + test->GetHalfWidthLocal().y >(currentNode->GetChild(g)->GetCenter().y - currentNode->GetChild(g)->GetSize())
					&&
					bObjManager->GetPositions()[h].y - test->GetHalfWidthLocal().y < (currentNode->GetChild(g)->GetCenter().y + currentNode->GetChild(g)->GetSize())
					&&
					bObjManager->GetPositions()[h].z + test->GetHalfWidthLocal().z >(currentNode->GetChild(g)->GetCenter().z - currentNode->GetChild(g)->GetSize())
					&&
					bObjManager->GetPositions()[h].z - test->GetHalfWidthLocal().z < (currentNode->GetChild(g)->GetCenter().z + currentNode->GetChild(g)->GetSize())
					)
				{
					withinIt++;
				}
		
				if (withinIt >= 2 && _level < 3)
				{
					currentNode->GetChild(g)->Subdivide();
					CheckForObjects(currentNode->GetChild(g), _level + 1);
				}
				
			}

		}
	}
}