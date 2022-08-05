#include "gamestate.h"
#include "game.h"

void GameState::ChangeState(GameState * state)
{
	m_pGameEngine->ChangeState(state);
}

GameState::GameState()
{
}

GameState::~GameState()
{
}