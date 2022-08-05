// COMP710 GP 2D Framework 2020
#ifndef __INTROSTATE_H__
#define __INTROSTATE_H__

// Includes

// Local includes:
#include "gamestate.h"
#include "background.h"

// Forward Declarations:
class BackBuffer;
class InputHandler;


class IntroState : public GameState
{
	//Member Methods:
public:

	static IntroState* GetInstance();
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
	IntroState();

	//Member Data:
public:

protected:
	static IntroState* sm_pIntroStateInstance;

private:

	//Middleware logo images
	Background m_FMODLogo;
	Background m_AUTLogo;
	Background m_SDLLogo;
	Background m_RKMDLogo;
};

#endif __INTROSTATE_H__
