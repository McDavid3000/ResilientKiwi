// COMP710 GP 2D Framework 2020

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "gamestate.h"
#include "spritemanager.h"
#include "playstate.h"
#include "introstate.h"
#include "player.h"
#include "enemyfactory.h"
#include "pickupfactory.h"
#include "soundmanager.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>

#include "mainmenustate.h"

// Static Members:
Game* Game::sm_pInstance = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
, m_windowWidth(0)
, m_windowHeight(0)
, m_drawDebugInfo(false)
{
	//Declare window sizing (in pixels)
	m_windowHeight = 854;
	m_windowWidth = 480;
}

Game::~Game()
{
	delete m_pInputHandler;
	m_pInputHandler = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	PlayState::DestroyInstance();
	IntroState::DestroyInstance();
	MainMenuState::DestroyInstance();
	SpriteManager::DestroyInstance();
	EnemyFactory::DestroyInstance();
	PickUpFactory::DestroyInstance();
	SoundManager::DestroyInstance();

	delete m_pSectionManager;
	m_pSectionManager = nullptr;
}

bool 
Game::Initialise()
{
	srand(0);
	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight)))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	//Initialising Sprite Manager
	SpriteManager::GetInstance().InitialiseManager(m_pBackBuffer);

	//Initialising Sound Manager
	SoundManager::GetInstance().Initialise();

	//Create Section Manager
	m_pSectionManager = new SectionManager();
	m_pSectionManager->LoadSections("assets//Sections.ini");
	
	m_lastTime = SDL_GetPerformanceCounter();
	m_lag = 0.0f;

	CreateBackgrounds();

	m_pBackBuffer->SetClearColour(0xCC, 0xCC, 0xCC);

	return (true);
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);

	m_vecGameStates.back()->HandleEvents();

	if (m_looping)
	{
		Uint64 current = SDL_GetPerformanceCounter();

		float deltaTime = (current - m_lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
		
		m_lastTime = current;

		m_executionTime += deltaTime;

		Process(deltaTime);
	
		m_lag += deltaTime;

		int innerLag = 0;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
			++innerLag;
		}

		// DEBUG STUB:
//		char buffer[64];
//		sprintf(buffer, "%f", deltaTime);
//		LogManager::GetInstance().Log(buffer);

		Draw(*m_pBackBuffer);
	}

	return (m_looping);
}

void 
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	// Update the game world simulation:
	m_vecGameStates.back()->Process(deltaTime);

	SoundManager::GetInstance().GetFMODSystem()->update();
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	m_vecGameStates.back()->Draw(backBuffer);

	//Draw debug info
	DrawDebug(backBuffer);
	
	backBuffer.Present();
}

void 
Game::DrawDebug(BackBuffer& backBuffer)
{
	if (m_drawDebugInfo)
	{
		//Draw FPS
		backBuffer.SetTextColour(Colour(0, 255, 0));
		char FPSbuffer[32];
		sprintf(FPSbuffer, "%s", "FPS: ");
		sprintf(FPSbuffer + strlen(FPSbuffer), "%d", m_FPS);
		backBuffer.DrawText(400, 0, FPSbuffer);
	}
}

void 
Game::Quit()
{
	m_looping = false;
}

float
Game::GetWindowWidth()
{
	return m_windowWidth;
}

float
Game::GetWindowHeight()
{
	return m_windowHeight;
}


void 
Game::ChangeState(GameState * state)
{
	if (!m_vecGameStates.empty())
	{
		m_vecGameStates.back()->CleanUp();
		m_vecGameStates.pop_back();
	}

	// store and init the new state
	m_vecGameStates.push_back(state);
	m_vecGameStates.back()->Initialise(this);
}

void 
Game::PushState(GameState * state)
{
	if (!m_vecGameStates.empty())
	{
		m_vecGameStates.back()->Pause();
	}

	m_vecGameStates.push_back(state);
	m_vecGameStates.back()->Initialise(this);
}

void 
Game::PopState()
{
	// cleanup the current state
	if (!m_vecGameStates.empty())
	{
		m_vecGameStates.back()->CleanUp();
		m_vecGameStates.pop_back();
	}

	// resume previous state
	if (!m_vecGameStates.empty())
	{
		m_vecGameStates.back()->Resume();
	}
}

BackBuffer * Game::GetBackBuffer()
{
	return m_pBackBuffer;
}

InputHandler * Game::GetInputHandler()
{
	return m_pInputHandler;
}

SectionManager* Game::GetSectionManager()
{
	return m_pSectionManager;
}

bool Game::GetDrawDebug()
{
	return m_drawDebugInfo;
}

void Game::SetDrawDebug(bool debug)
{
	m_drawDebugInfo = debug;
}

void
Game::CreateBackgrounds()
{
	SpriteManager::GetInstance().CreateSprite("assets\\Backgrounds\\ForestBackground.png");
	SpriteManager::GetInstance().CreateSprite("assets\\Backgrounds\\CityBackground.png");
	SpriteManager::GetInstance().CreateSprite("assets\\Backgrounds\\MountainBackground.png");
	SpriteManager::GetInstance().CreateSprite("assets\\Backgrounds\\CloudsBackground.png");
	SpriteManager::GetInstance().CreateSprite("assets\\Backgrounds\\SpaceBackground.png");
	SpriteManager::GetInstance().CreateSprite("assets\\Backgrounds\\DefaultSpaceBackground.png");
}