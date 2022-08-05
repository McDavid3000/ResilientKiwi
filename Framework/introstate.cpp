// Local includes:
#include "introstate.h"
#include "game.h"
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "mainmenustate.h"
#include "spritemanager.h"

// Library Includes
#include <assert.h>

// Forward Declarations:


// Static Members:
IntroState* IntroState::sm_pIntroStateInstance = 0;

IntroState*
IntroState::GetInstance()
{
	if (sm_pIntroStateInstance == 0)
	{
		sm_pIntroStateInstance = new IntroState();
	}

	assert(sm_pIntroStateInstance);

	return (sm_pIntroStateInstance);
}

IntroState::IntroState()
{
}

void 
IntroState::DestroyInstance()
{
	delete sm_pIntroStateInstance;
	sm_pIntroStateInstance = 0;
}

bool 
IntroState::Initialise(Game* game)
{
	m_pGameEngine = game;

	game->GetBackBuffer()->SetClearColour(0, 0, 0);

	if (!m_AUTLogo.Initialise(SpriteManager::CreateSprite("assets\\resizedlogos\\autlogo.png")))
	{
		LogManager::GetInstance().Log("AUT logo Init Fail!");
		return (false);
	}
	m_AUTLogo.SetPosition(Vector2(0, 0));
	
	if (!m_FMODLogo.Initialise(SpriteManager::CreateSprite("assets\\resizedlogos\\fmodlogowhite.png")))
	{
		LogManager::GetInstance().Log("FMOD logo Init Fail!");
		return (false);
	}
	m_FMODLogo.SetPosition(Vector2(0, 0));

	if (!m_SDLLogo.Initialise(SpriteManager::CreateSprite("assets\\resizedlogos\\sdllogo.png")))
	{
		LogManager::GetInstance().Log("SDL logo Init Fail!");
		return (false);
	}
	m_SDLLogo.SetPosition(Vector2(0, 0));

	if (!m_RKMDLogo.Initialise(SpriteManager::CreateSprite("assets\\resizedlogos\\rkmdLogo.png")))
	{
		LogManager::GetInstance().Log("RKMD logo Init Fail!");
		return (false);
	}
	m_RKMDLogo.SetPosition(Vector2(0, 0));

	return true;
}

void 
IntroState::Process(float deltaTime)
{
	
	if (m_AUTLogo.GetAlpha() > 0)
	{
		m_AUTLogo.SetAlpha(m_AUTLogo.GetAlpha() - 1);
	}
	else if (m_SDLLogo.GetAlpha() > 0)
	{
		m_SDLLogo.SetAlpha(m_SDLLogo.GetAlpha() - 1);
	}
	else if (m_FMODLogo.GetAlpha() > 0)
	{
		m_FMODLogo.SetAlpha(m_FMODLogo.GetAlpha() - 1);
	}
	else if (m_RKMDLogo.GetAlpha() > 0)
	{
		m_RKMDLogo.SetAlpha(m_RKMDLogo.GetAlpha() - 1);
	}
	else 
	{
		m_pGameEngine->ChangeState(MainMenuState::GetInstance());
	}	
}

void 
IntroState::Draw(BackBuffer & backBuffer)
{
	if (m_AUTLogo.GetAlpha() > 0)
	{
		m_AUTLogo.Draw(backBuffer);
	}
	else if (m_SDLLogo.GetAlpha() > 0)
	{
		m_SDLLogo.Draw(backBuffer);
	}
	else if (m_FMODLogo.GetAlpha() > 0)
	{
		m_FMODLogo.Draw(backBuffer);
	}
	else if (m_RKMDLogo.GetAlpha() > 0)
	{
		m_RKMDLogo.Draw(backBuffer);
	}
}

void 
IntroState::CleanUp()
{
}

void 
IntroState::HandleEvents()
{
	//m_pGameEngine->GetInputHandler()->ProcessIntroInput(*this);
}

void 
IntroState::Pause()
{
}

void 
IntroState::Resume()
{
}

void 
IntroState::Quit()
{
}





