// COMP710 GP 2D Framework 2020
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "sectionmanager.h"

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class GameState;
class Player; //Temporary

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();
	float GetWindowWidth();
	float GetWindowHeight();
	SectionManager* GetSectionManager();

	bool GetDrawDebug();
	void SetDrawDebug(bool debug);

	//State managment methods
	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	//FMOD::System* GetFMODSystem();
	BackBuffer* GetBackBuffer();
	InputHandler* GetInputHandler();

	void CreateBackgrounds();

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void DrawDebug(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;
	float m_windowWidth;
	float m_windowHeight;
	
	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	__int64 m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// State vector
	std::vector<GameState*> m_vecGameStates;
	SectionManager* m_pSectionManager;

private:

};

#endif // __GAME_H__
