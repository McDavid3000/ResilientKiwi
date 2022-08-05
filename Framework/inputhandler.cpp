// COMP710 GP 2D Framework 2020

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "logmanager.h"
#include "playstate.h"
#include "player.h"
#include "mainmenustate.h"
#include "gameoverstate.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
: m_pGameController(0)
, m_pControllerConnected(true)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_GameControllerClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{
	int numController = SDL_NumJoysticks();

	m_pGameController = SDL_GameControllerOpen(0);

	if (!m_pGameController)
	{
		m_pControllerConnected = false;
		LogManager::GetInstance().Log("No controller detected!");
	}

	return (true);
}

bool InputHandler::HasGameController()
{
	return m_pControllerConnected;
}


void
InputHandler::ProcessGameOverInput(PlayState& playState)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			playState.Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				playState.Quit();
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//Get mouse position
			int mouseX = 0;
			int mouseY = 0;
			SDL_GetMouseState(&mouseX, &mouseY);
			//Handle click behaviour in menu state
			playState.HandleClick(mouseX, mouseY);
		}
		//game controller input handling
		if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				//replay
				playState.Replay();
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				//quit
				playState.Quit();
			}
		}
	}
}

void
InputHandler::ProcessPauseInput(PlayState& playState)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			playState.Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				playState.TogglePause();
			}
			if (event.key.keysym.sym == SDLK_p)
			{
				playState.TogglePause();
			}
		}
		//game controller input handling
		if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
			{
				playState.TogglePause();
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				playState.Quit();
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
			{
				playState.Replay();
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//Get mouse position
			int mouseX = 0;
			int mouseY = 0;
			SDL_GetMouseState(&mouseX, &mouseY);
			//Handle click behaviour in menu state
			playState.HandleClick(mouseX, mouseY);
		}
	}
}

void 
InputHandler::ProcessPlayInput(PlayState& playState)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			playState.Quit();
		}
		else
		{
			if (event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
				{
					playState.TogglePause();
				}
				else
				{
					playState.GetPlayer()->HandleInput(event.cbutton.button);
				}
			}

			if (event.type == SDL_CONTROLLERBUTTONUP)
			{
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
				{
					//Stop player movement
					playState.GetPlayer()->SetHorizontalVelocity(0);
				}
			}

			//Player movement keyboard input handling
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					playState.TogglePause();
				}
				else if (event.key.keysym.sym == SDLK_p)
				{
					playState.TogglePause();
				}
				else
				{
					playState.GetPlayer()->HandleInput(event.key.keysym.sym);
				}
			}

			if (event.type == SDL_KEYUP)
			{
				//Move LEFT
				if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d)
				{
					//Stop player movement
					playState.GetPlayer()->SetHorizontalVelocity(0);
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				//Get mouse position
				int mouseX = 0;
				int mouseY = 0;
				SDL_GetMouseState(&mouseX, &mouseY);
				//Handle click behaviour in menu state
				playState.HandleClick(mouseX, mouseY);
			}
		}
	}
}


//main menu input methods 
void 
InputHandler::ProcessMainMenuInput(MainMenuState& mainMenuState)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			mainMenuState.Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				mainMenuState.Quit();
			}
		}
		else if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				mainMenuState.Play();
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				mainMenuState.Quit();
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//Get mouse position
			int mouseX = 0;
			int mouseY = 0;
			SDL_GetMouseState(&mouseX, &mouseY);
			//Handle click behaviour in menu state
			mainMenuState.HandleClick(mouseX, mouseY);			
		}
	}
}

void
InputHandler::ProcessGameOverInput(GameOverState& gameOverState)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			gameOverState.Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				gameOverState.Quit();
			}
		}
	}
}