// This include:
#include "playstate.h"

// Local includes:
#include <chrono>

#include "game.h"
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"

#include "player.h"
#include "enemy.h"
#include "section.h"
#include "gumbootpowerup.h"
#include "background.h"
#include "button.h"
#include "parallaxbackground.h"

#include "gameoverstate.h"
#include "mainmenustate.h"
#include "rectangle.h"

#include "sectionmanager.h"
#include "spritemanager.h"
#include "soundmanager.h"
#include "togglebutton.h"
#include "userinterface.h"

//Library includes

// Static Members:
PlayState* PlayState::sm_pPlayStateInstance = 0;

PlayState*
PlayState::GetInstance()
{
	if (sm_pPlayStateInstance == 0)
	{
		sm_pPlayStateInstance = new PlayState();
	}

	assert(sm_pPlayStateInstance);

	return (sm_pPlayStateInstance);
}

void 
PlayState::DestroyInstance()
{
	delete sm_pPlayStateInstance;
	sm_pPlayStateInstance = 0;
}

PlayState::PlayState()
:	m_paused(false)
,	m_currentLevel(PlayState::Level::FOREST)
,	m_gameOverCountdown(3) //3 seconds
,	m_distanceTraveled(0)
{
}

PlayState::~PlayState()
{	
}

bool 
PlayState::Initialise(Game* game)
{
	m_pGameEngine = game;
	m_pGameEngine->GetBackBuffer()->SetDrawColour(255, 0, 0);

	//Log game load time to output.
	auto t1 = std::chrono::high_resolution_clock::now();	//Start time

	CreateInterfaceComponents();
	CreateBackgrounds();

	auto t2 = std::chrono::high_resolution_clock::now(); //End time
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count(); //Get difference

	//Create Grid for debugging
	m_pGameGrid = SpriteManager::CreateSprite("assets\\GameGrid.png");

	//Log to output
	char buffer[64];
	sprintf(buffer, "Create BG Loading Time: %lld", duration);
	LogManager::GetInstance().Log(buffer);

	m_pNextGameBG = 0;
	m_pCurrentGameBG = m_pForestBackground;
	m_pCurrentGameBG->SetPositionX(m_pGameEngine->GetWindowHeight() - m_pCurrentGameBG->GetHeight());

	m_currentLevel = PlayState::Level::FOREST;
	m_pNextGameBG = 0;
	m_levelBGSwitched = false;
	
	//Get Section Manager
	m_pSectionManager = game->GetSectionManager();

	m_pPlayer = new Player();

	//Reset game over/pause states
	m_drawDebug = false;
	m_paused = false;
	m_gameOver = false;
	m_gameOverCountdown = 3; //3 seconds

	m_distanceTraveled = 0;

	return true;
}

void 
PlayState::Process(float deltaTime)
{
	if (!m_paused)
	{
		//Only process player if not dead
		if (!m_pPlayer->IsDead())
		{
			m_pPlayer->Process(deltaTime);
			
			//Check if player is colliding with an enemy
			CheckPlayerEnemyCollision();
			
			//Check if player is still on screen
			if (m_pPlayer->CheckOnScreen())
			{
				SoundManager::GetInstance().PlayGameOverSFX();
				m_pPlayer->SetDead(true);
				m_gameOver = true;
			}
		}

		//Check if the player is over halfway
		Vector2 distOverHalf(0, 0); //Set distance to 0
		if (m_pPlayer->GetPosition().y < m_pGameEngine->GetWindowHeight() / 2) //If player is above halfway
		{
			//Get distance over halfway
			distOverHalf.y = std::abs(m_pPlayer->GetPosition().y - (m_pGameEngine->GetWindowHeight() / 2));
			m_pPlayer->SetPositionY(m_pPlayer->GetPosition().y + distOverHalf.y); //move player back under halfway
			m_distanceTraveled += (int)distOverHalf.y;
		}

		Section* toRemove;
		for (auto m_section : m_pSectionManager->m_activeSections)
		{
			m_section->UpdatePosition(distOverHalf); //Adjust platforms if player is above halfway
			m_section->Process(deltaTime);

			//Move background(s)
			int parallaxSpeed = 5;
			m_pCurrentGameBG->ShiftPortionDown(distOverHalf.y / parallaxSpeed); //Move parallax background
			if (m_pNextGameBG != 0)
			{
				m_pNextGameBG->ShiftPortionDown(distOverHalf.y / parallaxSpeed); //Move next parallax background if loaded
			}
			
			if (m_section->GetPosition().y > m_pGameEngine->GetWindowHeight())
			{
				//Despawn section
 				toRemove = m_pSectionManager->DespawnSection();
				toRemove->RenewPickUps();
				toRemove->RenewEnemies();
				toRemove->RenewPlatforms();
			}

			m_section->CheckPickUpCollisions(m_pPlayer);

		}
		m_pSectionManager->m_activeSections.remove(toRemove);

		//Check if new level/background needs to be spawned
		if (m_pCurrentGameBG->GetCurrentPortionY() <= m_pGameEngine->GetWindowHeight() + 20)
		{
			if (m_levelBGSwitched == false)
			{
				UpgradeLevel();
				m_levelBGSwitched = true;
			}
		}
		//Check if next background needs to be switched to current background
		if (m_pNextGameBG != 0)
		{
			if (m_pCurrentGameBG->GetCurrentPortionY() <= 0)
			{
				m_pCurrentGameBG = m_pNextGameBG;
				//Reset background data
				m_pNextGameBG = 0;
				m_levelBGSwitched = false;
			}
		}
		
		//Update Coin Label
		char distBuffer[64];
		sprintf(distBuffer, "%dm", m_distanceTraveled/10);
		m_pDistanceLabel->SetLabelText(distBuffer);
		
		//Update Coin Label
		char buffer[64];
		sprintf(buffer, "%d", m_pPlayer->GetCoins());
		m_pCoinLabel->SetLabelText(buffer);
	}
}

void 
PlayState::Draw(BackBuffer & backBuffer)
{
	//Draw Space background
	m_pDefaultSpaceBackground->Draw(backBuffer);

	//Draw background
	m_pCurrentGameBG->Draw(backBuffer);
	if (m_pNextGameBG != 0) //Draw next background if exists
	{
		m_pNextGameBG->Draw(backBuffer);
	}

	//Draw debug
	if (GetDrawDebug())
	{
		m_pGameGrid->Draw(backBuffer);
	}
	
	//TODO: Stack sections
	for (auto m_section : m_pSectionManager->m_activeSections)
	{
		m_section->Draw(backBuffer);
	}
	
	//Draw player
	m_pPlayer->Draw(backBuffer);
	//Debug Method for player feet hitbox
	DrawPlayerFeetHitBox(backBuffer);
	
	if (m_pPlayer->IsDead())
	{
		m_pGameOverCoinsLabel->SetLabelText(std::to_string(m_pPlayer->GetCoins()));
		m_pGameOverDistanceLabel->SetLabelText(std::to_string(m_distanceTraveled/10)+"m");
		m_pGameOverInterface->DrawInterface(backBuffer);
	}

	//Draw paused label if paused
	if (m_paused)
	{
		m_pPausedInterface->DrawInterface(backBuffer);
	}

	m_pGameInterface->DrawInterface(backBuffer);
}

void 
PlayState::HandleEvents()
{
	if (m_gameOver)
	{
		m_pGameEngine->GetInputHandler()->ProcessGameOverInput(*this);
	}
	else if (m_paused)
	{
		m_pGameEngine->GetInputHandler()->ProcessPauseInput(*this);
	}
	else
	{
		m_pGameEngine->GetInputHandler()->ProcessPlayInput(*this);
	}
}

void
PlayState::HandleClick(int mouseX, int mouseY)
{
	if (!m_gameOver)
	{
		//Check what component was clicked.
		InterfaceComponent* clickedComponent = nullptr;
		
		if (m_paused)
			clickedComponent = m_pPausedInterface->HandleClick(mouseX, mouseY);
		if (clickedComponent == nullptr)
			clickedComponent = m_pGameInterface->HandleClick(mouseX, mouseY);

		//If play button clicked
		if (clickedComponent == m_pPauseButton)
		{
			//Play game!
			TogglePause();
		}
		else if (clickedComponent == m_pPausedQuitButton)
		{
			Quit();
		}
		else if (clickedComponent == m_pPausedReplayButton)
		{
			Replay();
		}
		else if (clickedComponent == m_pPausedResumeButton)
		{
			TogglePause();
		}
		else if (clickedComponent == m_pSoundToggleButton)
		{
			m_pSoundToggleButton->SetSelected(SoundManager::GetInstance().IsSoundEnabled());
			SoundManager::GetInstance().ToggleSound();
		}
	}
	else {
		InterfaceComponent* clickedComponent = m_pGameOverInterface->HandleClick(mouseX, mouseY);

		if (clickedComponent == m_pGameOverQuitButton)
		{
			//Quit game
			Quit();
		}
		else if (clickedComponent == m_pReplayButton)
		{
			//Replay game
			Replay();
		}
	}
}

void 
PlayState::CleanUp()
{
	delete m_pPlayer;
	m_pPlayer = 0;

	//Delete backgrounds
	DeleteBackgrounds();

	delete m_pGameInterface;
	m_pGameInterface = nullptr;

	delete m_pGameOverInterface;
	m_pGameOverInterface = nullptr;

	delete m_pPausedInterface;
	m_pPausedInterface = nullptr;
	
	m_pSectionManager->ResetSections();
}

void 
PlayState::Pause()
{
	m_paused = true;
}

void 
PlayState::Resume()
{
	m_paused = false;
}

void
PlayState::TogglePause()
{
	m_paused = !m_paused;
}

void 
PlayState::Quit()
{
	for (auto m_section : m_pSectionManager->m_activeSections)
	{
		m_section->RenewPickUps();
		m_section->RenewEnemies();
		m_section->RenewPlatforms();
	}
	m_pGameEngine->ChangeState(MainMenuState::GetInstance());
}

void
PlayState::Replay()
{
	for (auto m_section : m_pSectionManager->m_activeSections)
	{
		m_section->RenewPickUps();
		m_section->RenewEnemies();
		m_section->RenewPlatforms();
	}

	m_pGameEngine->ChangeState(PlayState::GetInstance());
}

Player* 
PlayState::GetPlayer()
{
	return m_pPlayer;
}

void 
PlayState::ToggleDrawDebug()
{
	m_pGameEngine->SetDrawDebug(!m_pGameEngine->GetDrawDebug());
}

bool 
PlayState::GetDrawDebug()
{
	return m_pGameEngine->GetDrawDebug();
}

void 
PlayState::DrawPlayerFeetHitBox(BackBuffer& backBuffer)
{
	if (GetDrawDebug())
	{
		int feetOffset = 30;
		int feetX = m_pPlayer->GetPosition().GetXi() + feetOffset;
		int feetY = m_pPlayer->GetPosition().GetYi() + ((m_pPlayer->GetHeight() / 8) * 7); //Bottom 1/8th of the sprite
		int feetW = m_pPlayer->GetWidth() - (feetOffset * 2);
		int feetH = m_pPlayer->GetHeight() - ((m_pPlayer->GetHeight() / 8) * 7);
		backBuffer.SetDrawColour(255, 0, 0);
		backBuffer.DrawRectangle(feetX, feetY, feetW + feetX, feetH + feetY);
		backBuffer.SetDrawColour(0, 0, 0);
	}
}

PlayState::Level 
PlayState::GetCurrentLevel()
{
	return m_currentLevel;
}

void
PlayState::UpgradeLevel()
{
	switch (m_currentLevel)
	{
	case PlayState::Level::FOREST:
		m_currentLevel = PlayState::Level::CITY;
		m_pNextGameBG = m_pCityBackground;
		m_pNextGameBG->ShiftPortionDown(-m_pGameEngine->GetWindowHeight()); //Shifts portion up
		break;
	case PlayState::Level::CITY:
		m_currentLevel = PlayState::Level::MOUNTAIN;
		m_pNextGameBG = m_pMountainBackground;
		m_pNextGameBG->ShiftPortionDown(-m_pGameEngine->GetWindowHeight()); //Shifts portion up
		break;
	case PlayState::Level::MOUNTAIN:
		m_currentLevel = PlayState::Level::CLOUD;
		m_pNextGameBG = m_pCloudsBackground;
		m_pNextGameBG->ShiftPortionDown(-m_pGameEngine->GetWindowHeight()); //Shifts portion up
		break;
	case PlayState::Level::CLOUD:
		m_currentLevel = PlayState::Level::SPACE;
		m_pNextGameBG = m_pSpaceBackground;
		m_pNextGameBG->ShiftPortionDown(-m_pGameEngine->GetWindowHeight()); //Shifts portion up
		break;
	}
}

void 
PlayState::CheckPlayerEnemyCollision()
{
	//Loop over every enemy in the section
	//for (auto enemy : m_pSectionManager->bottomSection->GetEnemies())
	for (auto sections : m_pSectionManager->m_activeSections)
	{
		for (auto enemy : sections->GetEnemies())
		{
			//Only check if not on a power up
			if (!(m_pPlayer->hasHiVis() || m_pPlayer->hasLandP()))
			{
				//If player collides with any enemy
				if (enemy->IsCollidingWith(*m_pPlayer))
				{
					//Game over, switch to game over state
					m_pPlayer->SetDead(true);
					m_gameOver = true;
					SoundManager::GetInstance().PlayDeadSFX();
					SoundManager::GetInstance().PlayGameOverSFX();
				}
			}
			else if (m_pPlayer->hasHiVis())
			{
				//If player collides with any enemy while wearing the hi vis vest
				if (enemy->IsCircleCollidingWith(*m_pPlayer))
				{
					enemy->SetDead(true);
					SoundManager::GetInstance().PlayEnemyDeadSFX();
				}
			}
		}
	}
}


void 
PlayState::CreateInterfaceComponents()
{
	
	//Create Game Interface
	m_pGameInterface = new UserInterface();
	m_pPauseButton = new Button();
	m_pPauseButton->Initialise("||", Vector2(30, 30), 50, 45);
	m_pPauseButton->SetButtonSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 0, 50, 50, 50));
	m_pPauseButton->SetButtonHoverSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 50, 50, 50, 50));
	m_pPauseButton->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pGameInterface->AddComponent(m_pPauseButton);

	m_pCoinCountIcon = new Rectangle();
	m_pCoinCountIcon->Initialise(Vector2(m_pGameEngine->GetWindowWidth() - 100, 25), 50, 50);
	m_pCoinCountIcon->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 0, 550, 50, 50));
	m_pGameInterface->AddComponent(m_pCoinCountIcon);

	m_pCoinLabel = new Label();
	m_pCoinLabel->Initialise("0", Vector2(m_pCoinCountIcon->GetPosition().x + 45, m_pCoinCountIcon->GetPosition().y + 5));
	m_pCoinLabel->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pGameInterface->AddComponent(m_pCoinLabel);

	m_pDistanceLabel = new Label();
	m_pDistanceLabel->Initialise("0m", Vector2(m_pGameEngine->GetWindowWidth() / 2, 40));
	m_pDistanceLabel->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pDistanceLabel->AlignTextCenter(true);
	m_pGameInterface->AddComponent(m_pDistanceLabel);

	//Game over interface
	m_pGameOverInterface = new UserInterface();
	Rectangle* pGameOverContainer = new Rectangle();
	pGameOverContainer->Initialise(Vector2(m_pGameEngine->GetWindowWidth() / 2, m_pGameEngine->GetWindowHeight() / 2), 400, 200);
	pGameOverContainer->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 0, 100, 350, 200));
	pGameOverContainer->DrawFromCenter(true);
	m_pGameOverInterface->AddComponent(pGameOverContainer);

	Label* pGameOverTitle = new Label();
	pGameOverTitle->Initialise("Game Over", Vector2(pGameOverContainer->GetCenter().x, pGameOverContainer->GetPosition().y + 20));
	pGameOverTitle->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	pGameOverTitle->AlignTextCenter(true);
	m_pGameOverInterface->AddComponent(pGameOverTitle);

	m_pGameOverDistanceLabel = new Label();
	m_pGameOverDistanceLabel->Initialise("0m", Vector2(pGameOverContainer->GetCenter().x, pGameOverContainer->GetCenter().y - 25));
	m_pGameOverDistanceLabel->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pGameOverDistanceLabel->AlignTextCenter(true);
	m_pGameOverDistanceLabel->SetPrimaryColour(Colour(0, 0, 0));
	m_pGameOverInterface->AddComponent(m_pGameOverDistanceLabel);

	m_pGameOverCoinsLabel = new Label();
	m_pGameOverCoinsLabel->Initialise("0", Vector2(pGameOverContainer->GetCenter().x, pGameOverContainer->GetCenter().y + 20));
	m_pGameOverCoinsLabel->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pGameOverCoinsLabel->AlignTextCenter(true);
	m_pGameOverCoinsLabel->SetPrimaryColour(Colour(0, 0, 0));
	m_pGameOverInterface->AddComponent(m_pGameOverCoinsLabel);

	Rectangle* pCoinGraphic = new Rectangle();
	pCoinGraphic->Initialise(Vector2(m_pGameOverCoinsLabel->GetPosition().x - 80, m_pGameOverCoinsLabel->GetPosition().y - 25), 50, 50);
	pCoinGraphic->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 0, 550, 50, 50));
	m_pGameOverInterface->AddComponent(pCoinGraphic);

	m_pReplayButton = new Button();
	m_pReplayButton->Initialise("", Vector2(pGameOverContainer->GetCenter().x + 30, pGameOverContainer->GetCenter().y + 90), 50, 45);
	m_pReplayButton->SetButtonSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 300, 50, 50, 50));
	m_pReplayButton->SetButtonHoverSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 350, 50, 50, 50));
	m_pReplayButton->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pGameOverInterface->AddComponent(m_pReplayButton);

	m_pGameOverQuitButton = new Button();
	m_pGameOverQuitButton->Initialise("", Vector2(pGameOverContainer->GetCenter().x-30, pGameOverContainer->GetCenter().y + 90), 50, 45);
	m_pGameOverQuitButton->SetButtonSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 150, 50, 50, 50));
	m_pGameOverQuitButton->SetButtonHoverSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 200, 50, 50, 50));
	m_pGameOverQuitButton->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pGameOverInterface->AddComponent(m_pGameOverQuitButton);

	//Paused interface
	m_pPausedInterface = new UserInterface();
	Rectangle* pPausedContainer = new Rectangle();
	pPausedContainer->Initialise(Vector2(m_pGameEngine->GetWindowWidth() / 2, m_pGameEngine->GetWindowHeight() / 2), 400, 200);
	pPausedContainer->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 0, 100, 350, 200));
	pPausedContainer->DrawFromCenter(true);
	m_pPausedInterface->AddComponent(pPausedContainer);

	Label* m_pPausedLabel = new Label();
	m_pPausedLabel->Initialise("Paused", Vector2(pPausedContainer->GetCenter().x, pPausedContainer->GetPosition().y + 20));
	m_pPausedLabel->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pPausedLabel->AlignTextCenter(true);
	m_pPausedInterface->AddComponent(m_pPausedLabel);

	m_pPausedReplayButton = new Button();
	m_pPausedReplayButton->Initialise("", Vector2(pGameOverContainer->GetCenter().x, pGameOverContainer->GetCenter().y + 90), 50, 45);
	m_pPausedReplayButton->SetButtonSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 300, 50, 50, 50));
	m_pPausedReplayButton->SetButtonHoverSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 350, 50, 50, 50));
	m_pPausedReplayButton->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pPausedInterface->AddComponent(m_pPausedReplayButton);

	m_pPausedResumeButton = new Button();
	m_pPausedResumeButton->Initialise("", Vector2(pGameOverContainer->GetCenter().x +60, pGameOverContainer->GetCenter().y + 90), 50, 45);
	m_pPausedResumeButton->SetButtonSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 450, 50, 50, 50));
	m_pPausedResumeButton->SetButtonHoverSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 500, 50, 50, 50));
	m_pPausedResumeButton->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pPausedInterface->AddComponent(m_pPausedResumeButton);
	
	m_pPausedQuitButton = new Button();
	m_pPausedQuitButton->Initialise("", Vector2(pGameOverContainer->GetCenter().x - 60, pGameOverContainer->GetCenter().y + 90), 50, 45);
	m_pPausedQuitButton->SetButtonSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 150, 50, 50, 50));
	m_pPausedQuitButton->SetButtonHoverSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 200, 50, 50, 50));
	m_pPausedQuitButton->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pPausedInterface->AddComponent(m_pPausedQuitButton);

	m_pSoundToggleButton = new ToggleButton();
	m_pSoundToggleButton->Initialise("", pPausedContainer->GetCenter(), 50, 45);
	m_pSoundToggleButton->SetButtonSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 450, 100, 50, 50));
	m_pSoundToggleButton->SetButtonHoverSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 500, 100, 50, 50));
	m_pSoundToggleButton->SetButtonClickedSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 550, 100, 50, 50));
	m_pSoundToggleButton->SetSelectedSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 450, 150, 50, 50));
	m_pSoundToggleButton->SetSelectedHoverSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 500, 150, 50, 50));
	m_pSoundToggleButton->SetSelectedClickedSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 550, 150, 50, 50));
	m_pSoundToggleButton->SetSelectedSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 450, 150, 50, 50));
	m_pSoundToggleButton->SetFont("assets//Tasty_Birds_Bold.otf", 34);
	m_pPausedInterface->AddComponent(m_pSoundToggleButton);

	//Only draw xbox buttons if controller detected
	if( m_pGameEngine->GetInputHandler()->HasGameController())
	{
		Rectangle* pPausedXboxBButton = new Rectangle();
		pPausedXboxBButton->Initialise(Vector2(m_pPausedQuitButton->GetPosition().x, m_pPausedQuitButton->GetPosition().y + 25), 50, 50);
		pPausedXboxBButton->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 100, 550, 50, 50));
		m_pPausedInterface->AddComponent(pPausedXboxBButton);

		Rectangle* pPausedXboxStartButton = new Rectangle();
		pPausedXboxStartButton->Initialise(Vector2(m_pPausedResumeButton->GetPosition().x, m_pPausedResumeButton->GetPosition().y + 25), 50, 50);
		pPausedXboxStartButton->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 250, 550, 50, 50));
		m_pPausedInterface->AddComponent(pPausedXboxStartButton);

		Rectangle* pPausedXboxXButton = new Rectangle();
		pPausedXboxXButton->Initialise(Vector2(m_pPausedReplayButton->GetPosition().x, m_pPausedReplayButton->GetPosition().y + 25), 50, 50);
		pPausedXboxXButton->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 150, 550, 50, 50));
		m_pPausedInterface->AddComponent(pPausedXboxXButton);
		
		Rectangle* gameOverXboxBButton = new Rectangle();
		gameOverXboxBButton->Initialise(Vector2(m_pGameOverQuitButton->GetPosition().x, m_pGameOverQuitButton->GetPosition().y + 25), 50, 50);
		gameOverXboxBButton->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 100, 550, 50, 50));
		m_pGameOverInterface->AddComponent(gameOverXboxBButton);

		Rectangle* gameOverXboxAButton = new Rectangle();
		gameOverXboxAButton->Initialise(Vector2(m_pReplayButton->GetPosition().x, m_pReplayButton->GetPosition().y + 25), 50, 50);
		gameOverXboxAButton->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 50, 550, 50, 50));
		m_pGameOverInterface->AddComponent(gameOverXboxAButton);

		Rectangle* xboxStartButton = new Rectangle();
		xboxStartButton->Initialise(Vector2(m_pPauseButton->GetPosition().x, m_pPauseButton->GetPosition().y + 25), 50, 50);
		xboxStartButton->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 250, 550, 50, 50));
		m_pGameInterface->AddComponent(xboxStartButton);
	}
}

void 
PlayState::CreateBackgrounds()
{
	//Create backgrounds
	m_pForestBackground = new ParallaxBackground;
	m_pCityBackground = new ParallaxBackground;
	m_pMountainBackground = new ParallaxBackground;
	m_pCloudsBackground = new ParallaxBackground;
	m_pSpaceBackground = new ParallaxBackground;
	m_pDefaultSpaceBackground = new Background;

	m_pForestBackground->Initialise(SpriteManager::GetInstance().GetSprite("assets\\Backgrounds\\ForestBackground.png"));
	m_pCityBackground->Initialise(SpriteManager::GetInstance().GetSprite("assets\\Backgrounds\\CityBackground.png"));
	m_pMountainBackground->Initialise(SpriteManager::GetInstance().GetSprite("assets\\Backgrounds\\MountainBackground.png"));
	m_pCloudsBackground->Initialise(SpriteManager::GetInstance().GetSprite("assets\\Backgrounds\\CloudsBackground.png"));
	m_pSpaceBackground->Initialise(SpriteManager::GetInstance().GetSprite("assets\\Backgrounds\\SpaceBackground.png"));
	m_pDefaultSpaceBackground->Initialise(SpriteManager::GetInstance().GetSprite("assets\\Backgrounds\\DefaultSpaceBackground.png"));
}

void
PlayState::DeleteBackgrounds()
{
	delete m_pForestBackground;
	m_pForestBackground = 0;
	delete m_pCityBackground;
	m_pCityBackground = 0;
	delete m_pMountainBackground;
	m_pMountainBackground = 0;
	delete m_pCloudsBackground;
	m_pCloudsBackground = 0;
	delete m_pSpaceBackground;
	m_pSpaceBackground = 0;
	delete m_pDefaultSpaceBackground;
	m_pDefaultSpaceBackground = 0;
}