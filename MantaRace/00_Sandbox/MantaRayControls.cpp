#include "MantaRayControls.h"
#include <math.h>

MantaRayControls* MantaRayControls::instance = nullptr;
MantaRayControls::MantaRayControls()
{
}


MantaRayControls::~MantaRayControls()
{
}

//Moves the ray forward, NOTE: This is currently not implemented
void MantaRayControls::MoveForward(float velocity)
{
	SetPosition(vector3(0.0f, 0.0f, velocity));
}

// Moves the ray sideways
void MantaRayControls::MoveSideways(float velocity)
{
	if (abs(rayPosition.x) <= 2.0f)
	{
		SetPosition(vector3(velocity, 0.0f, 0.0f));
	}
	else
	{
		SetPosition(vector3(-velocity, 0.0f, 0.0f));
	}
}

// Move the ray vertically
void MantaRayControls::MoveVertical(float velocity)
{
	if (abs(rayPosition.y) <= 1.0f)
	{
		SetPosition(vector3(0.0f, velocity, 0.0f));
	}
	else
	{
		SetPosition(vector3(0.0f, -velocity, 0.0f));
	}
}

void MantaRayControls::FireRay(vector2 mousePos)
{
	float length = glm::distance(vector3(mousePos, 0), rayPosition);
	meshManager->AddCylinderToQueue(IDENTITY_M4 * glm::scale(0.0f, length, 0.0f), vector3(255.0f), SOLID);
}

// Sets the ray's position
void MantaRayControls::SetPosition(vector3 changeInPosition)
{
	rayPosition += changeInPosition;
}

// Returns the ray's position
vector3 MantaRayControls::GetPosition(void)
{
	return rayPosition;
	//return m_v3Position;
}
