#include "statemanager.h"
#include "standingstate.h"
#include "jumpingstate.h"
#include "walkingstate.h"
#include "fallingstate.h"
#include "landpstate.h"

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
	delete m_pStandingState;
	m_pStandingState = 0;

	delete m_pJumpingState;
	m_pJumpingState = 0;

	delete m_pWalkingState;
	m_pWalkingState = 0;

	delete m_pFallingState;
	m_pFallingState = 0;

	delete m_pLandPState;
	m_pLandPState = 0;
}

void 
StateManager::Initialise(Player* player)
{
	//init statnding state
	m_pStandingState = new StandingState();
	m_pStandingState->Initialise(player);

	//init jumping state
	m_pJumpingState = new JumpingState();
	m_pJumpingState->Initialise(player);

	//init wlaking state
	m_pWalkingState = new WalkingState();
	m_pWalkingState->Initialise(player);
	
	m_pFallingState = new FallingState();
	m_pFallingState->Initialise(player);

	m_pLandPState = new LandPState();
	m_pLandPState->Initialise(player);
}

StandingState * 
StateManager::GetStandingState()
{
	return m_pStandingState;
}

JumpingState * 
StateManager::GetJumpingState()
{
	return m_pJumpingState;
}

WalkingState * 
StateManager::GetWalkingState()
{
	return m_pWalkingState;
}

FallingState *
StateManager::GetFallingState()
{
	return m_pFallingState;
}

LandPState *
StateManager::GetLandPState()
{
	return m_pLandPState;
}
