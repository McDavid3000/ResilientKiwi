// Local includes:
#include "game.h"
#include "gameoverstate.h"
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "mainmenustate.h"
#include "spritemanager.h"

// Library Includes
#include <assert.h>

// Forward Declarations:


// Static Members:

GameOverState* GameOverState::sm_pGameOverStateInstance = 0;

GameOverState*
GameOverState::GetInstance()
{
	if (sm_pGameOverStateInstance == 0)
	{
		sm_pGameOverStateInstance = new GameOverState();
	}

	assert(sm_pGameOverStateInstance);

	return (sm_pGameOverStateInstance);
}

GameOverState::GameOverState()
{
}

void
GameOverState::DestroyInstance()
{
	delete sm_pGameOverStateInstance;
	sm_pGameOverStateInstance = 0;
}

bool
GameOverState::Initialise(Game* game)
{
	m_pGameEngine = game;

	return true;
}

void
GameOverState::Process(float deltaTime)
{
	
}

void
GameOverState::Draw(BackBuffer & backBuffer)
{
	
}

void
GameOverState::CleanUp()
{
	DestroyInstance();
}

void
GameOverState::HandleEvents()
{
	m_pGameEngine->GetInputHandler()->ProcessGameOverInput(*this);
}

void
GameOverState::Pause()
{
}

void
GameOverState::Resume()
{
}

void
GameOverState::Quit()
{
	m_pGameEngine->ChangeState(MainMenuState::GetInstance());
}