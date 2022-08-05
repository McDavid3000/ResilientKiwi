// COMP710 GP 2D Framework 2020
#ifndef __GAMEOVERSTATE_H__
#define __GAMEOVERSTATE_H__

// Includes

// Local includes:
#include "gamestate.h"

// Forward Declarations:
class BackBuffer;
class InputHandler;

class GameOverState : public GameState
{
	//Member Methods:
public:

	static GameOverState* GetInstance();
	static void DestroyInstance();

	bool Initialise(Game* game);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void HandleEvents();

	void CleanUp();
	void Pause();
	void Resume();

	// Gameplay methods:

	void Quit();

protected:

private:
	GameOverState();

	//Member Data:
public:

protected:
	static GameOverState* sm_pGameOverStateInstance;

private:


};

#endif __GAMEOVERSTATE_H__
