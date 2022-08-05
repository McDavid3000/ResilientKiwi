// Local includes:
#include "game.h"
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "mainmenustate.h"
#include "spritemanager.h"
#include "statsstate.h"

// Library Includes
#include <assert.h>

// Forward Declarations:


// Static Members:

StatsState* StatsState::sm_pStatsStateInstance = 0;

StatsState*
StatsState::GetInstance()
{
	if (sm_pStatsStateInstance == 0)
	{
		sm_pStatsStateInstance = new StatsState();
	}

	assert(sm_pStatsStateInstance);

	return (sm_pStatsStateInstance);
}

StatsState::StatsState()
{
}

void
StatsState::DestroyInstance()
{
	delete sm_pStatsStateInstance;
	sm_pStatsStateInstance = 0;
}

bool
StatsState::Initialise(Game* game)
{
	m_pGameEngine = game;

	game->GetBackBuffer()->SetClearColour(0, 0, 0);

	return true;
}

void
StatsState::Process(float deltaTime)
{
	m_pGameEngine->ChangeState(MainMenuState::GetInstance());
}

void
StatsState::Draw(BackBuffer & backBuffer)
{
}

void
StatsState::CleanUp()
{
}

void
StatsState::HandleEvents()
{
	//m_pGameEngine->GetInputHandler()->ProcessIntroInput(*this);
}

void
StatsState::Pause()
{
}

void
StatsState::Resume()
{
}

void
StatsState::Quit()
{
}





