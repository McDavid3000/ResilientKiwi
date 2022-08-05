// COMP710 GP 2D Framework 2020
#ifndef __MAINMENUSTATE_H__
#define __MAINMENUSTATE_H__

// Includes

// Local includes:
#include "gamestate.h"
#include "background.h"
#include "rectangle.h"

class Button;
class UserInterface;
// Forward Declarations:
class BackBuffer;
class InputHandler;

class MainMenuState : public GameState
{
	//Member Methods:
public:

	static MainMenuState* GetInstance();
	static void DestroyInstance();

	bool Initialise(Game* game);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void HandleEvents();

	void CleanUp();
	void Pause();
	void Resume();

	//UI Creation
	void InitialiseButtons();

	// Menu methods
	void Play();
	void Quit();
	void HandleClick(int mouseX, int mouseY);


protected:

private:
	MainMenuState();

	//Member Data:
public:

protected:
	static MainMenuState* sm_pMainMenuStateInstance;

private:

	//Middleware logo images
	Background m_menuBackground;
	UserInterface* m_pMenuInterface;

	//Buttons
	Button* m_pPlayButton;
	Button* m_pShopButton;
	Button* m_pSettingsButton;
	Button* m_pStatsButton;

	Button* m_pQuitButton;
	Button* m_pAboutButton;
	Button* m_pInfoBackButton;
	Rectangle* m_pInfoSprite;
};

#endif //__MAINMENUSTATE_H__
