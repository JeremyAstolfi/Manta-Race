#include "MantaRayControls.h"

MantaRayControls* MantaRayControls::instance = nullptr;
MantaRayControls::MantaRayControls()
{
	boundary = vector3(3.5f, 2.0f, 4.0f);
}


MantaRayControls::~MantaRayControls()
{
}

//Moves the ray forward, NOTE: This is currently not implemented
void MantaRayControls::MoveForward(float velocity)
{
	SetPosition(vector3(rayPosition.x, rayPosition.y, rayPosition.z + velocity));
}

// Moves the ray sideways
void MantaRayControls::MoveSideways(float velocity)
{
	if (rayPosition.x > boundary.x)
	{
		SetPosition(vector3(boundary.x, rayPosition.y, rayPosition.z));
	}
	else if (rayPosition.x < -boundary.x)
	{
		SetPosition(vector3(-boundary.x + velocity, rayPosition.y, rayPosition.z));
	}
	else
	{
		SetPosition(vector3(rayPosition.x + velocity, rayPosition.y, rayPosition.z));
	}
}

// Move the ray vertically
void MantaRayControls::MoveVertical(float velocity)
{
	if (rayPosition.y > boundary.y)
	{
		SetPosition(vector3(rayPosition.x, boundary.y, rayPosition.z));
	}
	else if (rayPosition.y < -boundary.y)
	{
		SetPosition(vector3(rayPosition.x, -boundary.y + velocity, rayPosition.z));
	}
	else
	{
		SetPosition(vector3(rayPosition.x, rayPosition.y + velocity, rayPosition.z));
	}
}

// Sets the ray's position
void MantaRayControls::SetPosition(vector3 changeInPosition){ rayPosition = changeInPosition; }
// Returns the ray's position
vector3 MantaRayControls::GetPosition(void){ return rayPosition; }
// Sets the ray's velocity
void MantaRayControls::SetVelocity(vector3 changeInVelocity){ rayVelocity = changeInVelocity; }
// Returns the ray's velocity
vector3 MantaRayControls::GetVelocity(void){ return rayVelocity; }
// Sets the ray's acceleration
void MantaRayControls::SetAcceleration(vector3 changeInAcceleration) { rayAcceleration = changeInAcceleration; }
// Return the ray's acceleration
vector3 MantaRayControls::GetAcceleration(void) { return rayAcceleration; }
