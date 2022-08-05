#ifndef __PLAYSTATE_H__
#define __PLAYSTATE_H__

// Superclass include
#include "gamestate.h"

// Includes
#include <fmod.hpp>  
#include <cassert>
#include <SDL.h>
#include <list>

#include "background.h"
#include "label.h"
#include "rectangle.h"
#include "sectionmanager.h"
#include "togglebutton.h"

class Button;
class UserInterface;
// Forward Declarations:
class BackBuffer;
class InputHandler;
class Game;
class Sprite;
class Player;
class PickUps;
class GumbootPowerUp;
class HiVisPowerUp;
class LandPPowerUp;
class KiwiCoin;

class CrumblingPlatform;
class MovingPlatform;
class Platform;
class Section;
class GameState;
class ParallaxBackground;

class PlayState : public GameState
{
	//Member Methods:
public:
	static PlayState* GetInstance();
	static void DestroyInstance();
	~PlayState();

	bool Initialise(Game* game);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void HandleEvents();
	void HandleClick(int mouseX, int mouseY);

	void CreateInterfaceComponents();
	void CreateBackgrounds();

	void DeleteBackgrounds();

	//For debug purposes, draws rectangle on player feet hitbox
	void DrawPlayerFeetHitBox(BackBuffer& backBuffer);
	void ToggleDrawDebug();
	bool GetDrawDebug();

	Player* GetPlayer();
	void CheckPlayerEnemyCollision();

	void CleanUp();
	void Pause();
	void Resume();
	void TogglePause();

	//Level methods
	enum Level {
		FOREST,
		CITY,
		MOUNTAIN,
		CLOUD,
		SPACE
	};

	Level GetCurrentLevel();
	void UpgradeLevel(); //Method to switch from one level to the next

	void Quit();

	void Replay();

protected:

private:
	PlayState();

	//Member Data:
public:
	bool m_paused;
	bool m_gameOver;
	bool m_debugMode;
	Sprite* m_pGameGrid;
	SectionManager* m_pSectionManager;


protected:
	static PlayState* sm_pPlayStateInstance;
	int m_distanceTraveled;

	//Background
	ParallaxBackground* m_pCurrentGameBG;
	ParallaxBackground* m_pNextGameBG;

	ParallaxBackground* m_pForestBackground;
	ParallaxBackground* m_pCityBackground;
	ParallaxBackground* m_pMountainBackground;
	ParallaxBackground* m_pCloudsBackground;
	ParallaxBackground* m_pSpaceBackground;
	Background* m_pDefaultSpaceBackground;

	bool m_levelBGSwitched;

	//Entities
	Player* m_pPlayer;

	//Debugging
	bool m_drawDebug;
	bool m_showPlayerFeetHitBox;

	//Level
	Level m_currentLevel;

	//Game over
	Sprite* m_pGameOverSprite;
	float m_gameOverCountdown;

	//UI
	UserInterface* m_pGameInterface;
	Button* m_pPauseButton;
	Rectangle* m_pCoinCountIcon;
	Label* m_pCoinLabel;
	Label* m_pDistanceLabel;
	
	//Game Over UI
	UserInterface* m_pGameOverInterface;
	Label* m_pGameOverDistanceLabel;
	Label* m_pGameOverCoinsLabel;
	Button* m_pReplayButton;
	Button* m_pGameOverQuitButton;

	//Paused UI
	UserInterface* m_pPausedInterface;
	Label* m_pPausedLabel;
	Button* m_pPausedReplayButton;
	Button* m_pPausedQuitButton;
	Button* m_pPausedResumeButton;
	ToggleButton* m_pSoundToggleButton;



private:

};

#endif __PLAYSTATE_H__
