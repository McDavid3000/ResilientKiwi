// COMP710 GP 2D Framework 2020
#ifndef __INPUTHANDER_H__
#define __INPUTHANDER_H__

// Library includes:
#include <SDL.h>

// Forward Declarations:
class Game;
class PlayState;
class MainMenuState;
class GameOverState;

class InputHandler
{
	//Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise();


	//Game state input handlers
	void ProcessPlayInput(PlayState& playState);
	void ProcessMainMenuInput(MainMenuState& mainMenuState);
	void ProcessGameOverInput(GameOverState& gameOverState);
	void ProcessGameOverInput(PlayState & playState);
	void ProcessPauseInput(PlayState & playState);

	bool HasGameController();


protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	//Member Data:
public:

protected:
	SDL_GameController* m_pGameController;
	bool m_pControllerConnected;

private:

};

#endif // __INPUTHANDER_H__
