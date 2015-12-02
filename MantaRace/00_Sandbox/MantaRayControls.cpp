#include "MantaRayControls.h"

MantaRayControls* MantaRayControls::instance = nullptr;
MantaRayControls::MantaRayControls()
{
	boIndex = -1;
//	boIndex = BoundingObjectManager::GetInstance()->AddBox("MantaRay", MeshManagerSingleton::GetInstance()->GetVertexList("MantaRay"));
	boundary = vector3(3.5f, 2.0f, 4.0f);
}


MantaRayControls::~MantaRayControls()
{
}

void MantaRayControls::Update(void)
{
	if (boIndex == -1){
		boIndex = BoundingObjectManager::GetInstance()->AddBox("MantaRay", MeshManagerSingleton::GetInstance()->GetVertexList("MantaRay"));
	}

	vector3 v3Acceleration = rayAcceleration / rayMass;
	v3Acceleration = glm::clamp(v3Acceleration, -rayMaxAcceleration, rayMaxAcceleration);
	rayVelocity += v3Acceleration;
	rayPosition += rayVelocity;

	matrix4 m4ToWorld = glm::translate(rayPosition)*glm::scale(vector3(0.25,0.25,0.25));
	BoundingObjectManager::GetInstance()->boundingObjects[boIndex]->SetModelMatrix(m4ToWorld);

	if (rayVelocity != vector3(0.0f))
	{
		if (rayVelocity.x > 0.0f)
		{
			rayVelocity.x -= rayFriction;
		}
		if (rayVelocity.x < 0.0f)
		{
			rayVelocity.x += rayFriction;
		}
		if (rayVelocity.y > 0.0f)
		{
			rayVelocity.y -= rayFriction;
		}
		if (rayVelocity.y < 0.0f)
		{
			rayVelocity.y += rayFriction;
		}
		if (rayVelocity.z > 0.0f)
		{
			rayVelocity.z -= rayFriction;
		}
		if (rayVelocity.z < 0.0f)
		{
			rayVelocity.z += rayFriction;
		}
	}

	if (rayPosition.x > boundary.x)
	{
		SetPosition(vector3(boundary.x + rayAcceleration.x, rayPosition.y, rayPosition.z));
		SetAcceleration(vector3(0.0f, rayAcceleration.y, rayAcceleration.z));
		SetVelocity(vector3(0.0f, rayVelocity.y, rayVelocity.z));
	}
	else if (rayPosition.x < -boundary.x)
	{
		SetPosition(vector3(-boundary.x + rayAcceleration.x, rayPosition.y, rayPosition.z));
		SetAcceleration(vector3(0.0f));
		SetVelocity(vector3(0.0f));
	}

	if (rayPosition.y > boundary.y)
	{
		SetPosition(vector3(rayPosition.x, boundary.y + rayAcceleration.y, rayPosition.z));
		SetAcceleration(vector3(rayAcceleration.x, 0.0f, rayAcceleration.z));
		SetVelocity(vector3(rayVelocity.x, 0.0f, rayVelocity.z));
	}
	else if (rayPosition.y < -boundary.y)
	{
		SetPosition(vector3(rayPosition.x, -boundary.y + rayAcceleration.y, rayPosition.z));
		SetAcceleration(vector3(0.0f));
		SetVelocity(vector3(0.0f));
	}
}

//Moves the ray forward, NOTE: This is currently not implemented
void MantaRayControls::MoveForward(float acceleration)
{
	SetAcceleration(vector3(rayAcceleration.x, rayAcceleration.y, rayAcceleration.z + acceleration));
}

// Moves the ray sideways
void MantaRayControls::MoveSideways(float acceleration)
{
	SetAcceleration(vector3(rayAcceleration.x + acceleration, rayAcceleration.y, rayAcceleration.z));
}

// Move the ray vertically
void MantaRayControls::MoveVertical(float acceleration)
{
	SetAcceleration(vector3(rayAcceleration.x, rayAcceleration.y + acceleration, rayAcceleration.z));
}

// Sets the ray's position
void MantaRayControls::SetPosition(vector3 _position){ rayPosition = _position; }
// Returns the ray's position
vector3 MantaRayControls::GetPosition(void){ return rayPosition; }
// Sets the ray's velocity
void MantaRayControls::SetVelocity(vector3 _velocity){ rayVelocity = _velocity; }
// Returns the ray's velocity
vector3 MantaRayControls::GetVelocity(void){ return rayVelocity; }
// Sets the ray's acceleration
void MantaRayControls::SetAcceleration(vector3 _acceleration) { rayAcceleration = _acceleration; }
// Return the ray's acceleration
vector3 MantaRayControls::GetAcceleration(void) { return rayAcceleration; }
// Sets the ray's max acceleration
void MantaRayControls::SetMaxAcc(float _maxAcceleration) { rayMaxAcceleration = _maxAcceleration; }
// Sets the ray's mass
void MantaRayControls::SetMass(float _mass) { rayMass = _mass; }
// Sets the ray's friction
void MantaRayControls::SetFriction(float _friction) { rayFriction = _friction; }
// Sets the ray's health
void MantaRayControls::SetHealth(int _health) { health = _health; }
// Return the ray's health
int MantaRayControls::GetHealth(void) { return health; }

//Roates Ray
void MantaRayControls::Rotate(float speed) { theta += speed; }
