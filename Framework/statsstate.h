// COMP710 GP 2D Framework 2020
#ifndef __STATSSTATE_H__
#define __STATSSTATE_H__

// Includes

// Local includes:
#include "gamestate.h"
#include "background.h"

// Forward Declarations:
class BackBuffer;
class InputHandler;


class StatsState : public GameState
{
	//Member Methods:
public:

	static StatsState* GetInstance();
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
	StatsState();

	//Member Data:
public:

protected:
	static StatsState* sm_pStatsStateInstance;

private:

};

#endif __STATSSTATE_H__
