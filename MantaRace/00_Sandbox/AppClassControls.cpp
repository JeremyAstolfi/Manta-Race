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
	//if(bModifier)
		//fSpeed *= 10.0f;
	bool keyUp = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
<<<<<<< HEAD
		if (mantaRay->GetPosition().y < 2.5f)
			mantaRay->MoveVertical(fSpeed);
	}
=======
		mantaRay->MoveVertical(fSpeed);
>>>>>>> 74d3402e96aedb644ac6f0a88a0f5d335b612b1c
		//m_pCameraMngr->MoveForward(fSpeed);
		keyUp = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
<<<<<<< HEAD
		if (mantaRay->GetPosition().y>-2.5f)
=======
>>>>>>> 74d3402e96aedb644ac6f0a88a0f5d335b612b1c
		mantaRay->MoveVertical(-fSpeed);
	}
		//m_pCameraMngr->MoveForward(-fSpeed);
		keyUp = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
<<<<<<< HEAD
		if (mantaRay->GetPosition().x>-4.5f)
=======
>>>>>>> 74d3402e96aedb644ac6f0a88a0f5d335b612b1c
		mantaRay->MoveSideways(-fSpeed);
	}
		//m_pCameraMngr->MoveSideways(-fSpeed);
		keyUp = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
<<<<<<< HEAD
		if (mantaRay->GetPosition().x<4.5f)
=======
>>>>>>> 74d3402e96aedb644ac6f0a88a0f5d335b612b1c
		mantaRay->MoveSideways(fSpeed);
	}
		//m_pCameraMngr->MoveSideways(fSpeed);
		keyUp = false;
	}

	if (keyUp)
	{
		mantaRay->SetAcceleration(vector3(0.0f));
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCameraMngr->MoveVertical(fSpeed);*/
#pragma endregion
	
#pragma region Creeper Control
	/*
	if (bModifier)
		fSpeed *= 10.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		bObjManager->boundingObjects[0]->SetPosition(vector3(-0.1f, 0.0f, 0.0f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		bObjManager->boundingObjects[0]->SetPosition(vector3(0.1f, 0.0f, 0.0f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		bObjManager->boundingObjects[0]->SetPosition(vector3(0.0f, -0.1f, 0.0f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		bObjManager->boundingObjects[0]->SetPosition(vector3(0.0f, 0.1f, 0.0f));
		*/
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
