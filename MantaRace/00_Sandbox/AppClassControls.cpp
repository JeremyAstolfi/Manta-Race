#include "AppClass.h"


void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.001f;


#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false, bLastF = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Camera Positioning
	bool xKeyUp = true;
	bool yKeyUp = true;
	int xValue = 0;
	int yValue = 0;
	vector3 rayAcc = mantaRay->GetAcceleration();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (tempY < 0)
		{
			mantaRay->SetAcceleration(vector3(rayAcc.x, 0.0f, rayAcc.z));
		}
		yValue += 1;
		yKeyUp = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (tempY > 0)
		{
			mantaRay->SetAcceleration(vector3(rayAcc.x, 0.0f, rayAcc.z));
		}
		yValue -= 1;
		yKeyUp = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (tempX > 0)
		{
			mantaRay->SetAcceleration(vector3(0.0f, rayAcc.y, rayAcc.z));
			mantaRay->Rotate(25.0f);
		}
		xValue -= 1;
		xKeyUp = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (tempX < 0)
		{
			mantaRay->SetAcceleration(vector3(0.0f, rayAcc.y, rayAcc.z));
			mantaRay->Rotate(-25.0f);
		}
		xValue += 1;
		xKeyUp = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		mantaRay->Rotate(-fSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		mantaRay->Rotate(fSpeed);
	}


	if (yKeyUp && !xKeyUp)
	{
		mantaRay->SetAcceleration(vector3(rayAcc.x, 0.0f, rayAcc.z));
	}
	if (xKeyUp && !yKeyUp)
	{
		mantaRay->SetAcceleration(vector3(0.0f, rayAcc.y, rayAcc.z));
	}
	if (xKeyUp && yKeyUp)
	{
		mantaRay->SetAcceleration(vector3(0.0f));
	}
	
	tempX = xValue;
	tempY = yValue;
	mantaRay->MoveVertical(fSpeed * yValue);
	mantaRay->MoveSideways(fSpeed * xValue);

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCameraMngr->MoveVertical(fSpeed);*/
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	ON_KEY_PRESS_RELEASE(F1, NULL, m_pCameraMngr->SetCameraMode(CAMPERSP));
	ON_KEY_PRESS_RELEASE(F2, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOZ));
	ON_KEY_PRESS_RELEASE(F3, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOY));
	ON_KEY_PRESS_RELEASE(F4, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOX));
	static bool bFPSControll = false;
	ON_KEY_PRESS_RELEASE(F, bFPSControll = !bFPSControll, m_pCameraMngr->SetFPS(bFPSControll))
		;
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
			for (int i = 0; i < 8; i++)
		{
			m_pMeshMngr->AddLineToRenderList(vector3(mantaRay->GetPosition().x, mantaRay->GetPosition().y, mantaRay->GetPosition().z-1.0f), vector3(GetMousePosition().x + (i*0.01f), GetMousePosition().y + (i*0.01f), -1.0f), vector3(0.0f), vector3(255.0f));
		}
		}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;

	
	AppClass::mousePos = sf::Mouse::getPosition();

}
