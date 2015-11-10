#include "MantaRayControls.h"

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
		SetPosition(vector3(velocity, 0.0f, 0.0f));
}

// Move the ray vertically
void MantaRayControls::MoveVertical(float velocity)
{
		SetPosition(vector3(0.0f, velocity, 0.0f));
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
