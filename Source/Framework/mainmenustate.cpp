// Local includes:
#include "mainmenustate.h"

#include <chrono>


#include "animatedsprite.h"
#include "game.h"
#include "backbuffer.h"
#include "button.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "playstate.h"
#include "spritemanager.h"
#include "userinterface.h"
#include "soundmanager.h"

#include <chrono>
#include <cassert>

// Forward Declarations:


// Static Members:
MainMenuState* MainMenuState::sm_pMainMenuStateInstance = 0;

MainMenuState*
MainMenuState::GetInstance()
{
	if (sm_pMainMenuStateInstance == 0)
	{
		sm_pMainMenuStateInstance = new MainMenuState();
	}

	assert(sm_pMainMenuStateInstance);

	return (sm_pMainMenuStateInstance);
}

MainMenuState::MainMenuState()
{
}

void
MainMenuState::DestroyInstance()
{
	delete sm_pMainMenuStateInstance;
	sm_pMainMenuStateInstance = 0;
}

bool
MainMenuState::Initialise(Game* game)
{
	m_pGameEngine = game;

	if (!m_menuBackground.Initialise(SpriteManager::CreateSprite("assets\\MenuBackground.png")))
	{
		LogManager::GetInstance().Log("Menu background logo Init Fail!");
		return (false);
	}
	m_menuBackground.SetPosition(Vector2(0, 0));

	//Create Interface
	m_pMenuInterface = new UserInterface();
	
	InitialiseButtons();
	
	return true;
}

void
MainMenuState::Process(float deltaTime)
{
}

void
MainMenuState::Draw(BackBuffer & backBuffer)
{
	m_menuBackground.Draw(backBuffer);
	m_pMenuInterface->DrawInterface(backBuffer); //Draw all components in the interface
}

void
MainMenuState::CleanUp()
{
	//Delete interface and all components inside it.
	delete m_pMenuInterface;
	m_pMenuInterface = nullptr;
}

void
MainMenuState::HandleEvents()
{
	m_pGameEngine->GetInputHandler()->ProcessMainMenuInput(*this);
}

void MainMenuState::HandleClick(int mouseX, int mouseY)
{
	//Check what component was clicked.
	InterfaceComponent* clickedComponent = m_pMenuInterface->HandleClick(mouseX, mouseY);
	//If play button clicked
	if (clickedComponent == m_pInfoBackButton)
	{
		m_pInfoSprite->ToggleVisibility();
		m_pInfoBackButton->ToggleVisibility();
	}
	else if (clickedComponent == m_pPlayButton)
	{
		//Play game!
		Play();
	}
	else if (clickedComponent == m_pSettingsButton)
	{
		//Show settings
	}
	else if (clickedComponent == m_pShopButton)
	{
		//Show shop
	}
	else if (clickedComponent == m_pStatsButton)
	{
		//Show stats
	}
	else if (clickedComponent == m_pAboutButton)
	{
		m_pInfoSprite->ToggleVisibility();
		m_pInfoBackButton->ToggleVisibility();
	}
	else if (clickedComponent == m_pQuitButton)
	{
		Quit();
	}
}


void
MainMenuState::Pause()
{
}

void
MainMenuState::Resume()
{
}

void
MainMenuState::Quit()
{
	CleanUp();
	m_pGameEngine->Quit();
}

void
MainMenuState::Play()
{
	SoundManager::GetInstance().PlayKiwiCoinSFX();

	//Log game load time to output.
	auto t1 = std::chrono::high_resolution_clock::now();	//Start time
	
	m_pGameEngine->ChangeState(PlayState::GetInstance());
	
	auto t2 = std::chrono::high_resolution_clock::now(); //End time
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count(); //Get difference

	//Log to output
	char buffer[64];
	sprintf(buffer, "Play Loading Time: %lld", duration);
	LogManager::GetInstance().Log(buffer);
	
}

void 
MainMenuState::InitialiseButtons()
{
	Sprite* buttonSprite = SpriteManager::CreateSpriteFromSheet("assets//UISpriteSheet.png", 0, 0, 200, 50);
	//TODO: Further modify button class to use these
	Sprite* hoverSprite = SpriteManager::CreateSpriteFromSheet("assets//UISpriteSheet.png", 200, 0, 200, 50);
	Sprite* pressedSprite = SpriteManager::CreateSpriteFromSheet("assets//UISpriteSheet.png", 400, 0, 200, 50);
	Sprite* smallButtonSprite = SpriteManager::CreateSpriteFromSheet("assets//UISpriteSheet.png", 0, 50, 50, 50);
	Sprite* smallButtonHoverSprite = SpriteManager::CreateSpriteFromSheet("assets//UISpriteSheet.png", 50, 50, 50, 50);
	Sprite* exitButtonSprite = SpriteManager::CreateSpriteFromSheet("assets//UISpriteSheet.png", 150, 50, 50, 50);
	Sprite* exitButtonHoverSprite = SpriteManager::CreateSpriteFromSheet("assets//UISpriteSheet.png", 200, 50, 50, 50);

	int fontSize = 34;
	char* fontFile = "assets//Tasty_Birds_Bold.otf";
	
	//Create play button
	m_pPlayButton = new Button();
	m_pPlayButton->Initialise("Play", Vector2((m_pGameEngine->GetWindowWidth() / 2), (m_pGameEngine->GetWindowHeight() / 3) + 150), 200, 45);
	m_pPlayButton->SetButtonSprite(buttonSprite);
	m_pPlayButton->SetButtonHoverSprite(hoverSprite);
	m_pPlayButton->SetFont(fontFile, fontSize);
	m_pMenuInterface->AddComponent(m_pPlayButton); //Add play button to interface

	//Create shop button
	m_pShopButton = new Button();
	m_pShopButton->Initialise("Shop", Vector2((m_pGameEngine->GetWindowWidth() / 2), (m_pGameEngine->GetWindowHeight() / 3) + 210), 200, 45);
	m_pShopButton->SetButtonSprite(buttonSprite);
	m_pShopButton->SetButtonHoverSprite(hoverSprite);
	m_pShopButton->SetFont(fontFile, fontSize);
	m_pMenuInterface->AddComponent(m_pShopButton); //Add shop button to interface

	//Create Settings button
	m_pSettingsButton = new Button();
	m_pSettingsButton->Initialise("Settings", Vector2((m_pGameEngine->GetWindowWidth() / 2), (m_pGameEngine->GetWindowHeight() / 3) + 270), 200, 45);
	m_pSettingsButton->SetButtonSprite(buttonSprite);
	m_pSettingsButton->SetButtonHoverSprite(hoverSprite);
	m_pSettingsButton->SetFont(fontFile, fontSize);
	m_pMenuInterface->AddComponent(m_pSettingsButton); //Add settings button to interface

	//Create Stats button
	m_pStatsButton = new Button();
	m_pStatsButton->Initialise("Stats", Vector2((m_pGameEngine->GetWindowWidth() / 2), (m_pGameEngine->GetWindowHeight() / 3) + 330), 200, 45);
	m_pStatsButton->SetButtonSprite(buttonSprite);
	m_pStatsButton->SetButtonHoverSprite(hoverSprite);
	m_pStatsButton->SetFont(fontFile, fontSize);
	m_pMenuInterface->AddComponent(m_pStatsButton); //Add stats button to interface

	//Create Quit button
	m_pQuitButton = new Button();
	m_pQuitButton->Initialise("", Vector2(30, m_pGameEngine->GetWindowHeight() - 30), 50, 50);
	m_pQuitButton->SetButtonSprite(exitButtonSprite);
	m_pQuitButton->SetButtonHoverSprite(exitButtonHoverSprite);
	m_pMenuInterface->AddComponent(m_pQuitButton); //Add quit button to interface

	//Create About button
	m_pAboutButton = new Button();
	m_pAboutButton->Initialise("?", Vector2(m_pQuitButton->GetPosition().x + 80, m_pGameEngine->GetWindowHeight() - 32), 50, 45);
	m_pAboutButton->SetButtonSprite(smallButtonSprite);
	m_pAboutButton->SetButtonHoverSprite(smallButtonHoverSprite);
	m_pAboutButton->SetFont(fontFile, 40);
	m_pMenuInterface->AddComponent(m_pAboutButton); //Add about button to interface

	//Create Info Interface
	m_pInfoSprite = new Rectangle();
	m_pInfoSprite->Initialise(Vector2(m_pGameEngine->GetWindowWidth() / 2, m_pGameEngine->GetWindowHeight() / 2), 350, 456);
	m_pInfoSprite->SetBackgroundSprite(SpriteManager::GetInstance().CreateSprite("assets//InfoScreenSprite.png"));
	m_pInfoSprite->DrawFromCenter(true);
	m_pInfoSprite->SetVisibility(false);
	m_pMenuInterface->AddComponent(m_pInfoSprite);

	m_pInfoBackButton = new Button();
	m_pInfoBackButton->Initialise("Back", Vector2((m_pGameEngine->GetWindowWidth() / 2), (m_pGameEngine->GetWindowHeight() / 2)+230), 200, 45);
	m_pInfoBackButton->SetButtonSprite(buttonSprite);
	m_pInfoBackButton->SetButtonHoverSprite(hoverSprite);
	m_pInfoBackButton->SetFont(fontFile, fontSize);
	m_pInfoBackButton->SetVisibility(false);
	m_pMenuInterface->AddComponent(m_pInfoBackButton);

	//Only draw xbox buttons if controller detected
	if (m_pGameEngine->GetInputHandler()->HasGameController())
	{
		Rectangle* pXboxAButton = new Rectangle();
		pXboxAButton->Initialise(Vector2(m_pPlayButton->GetButtonCenter().x - 70, m_pPlayButton->GetPosition().y - 2), 50, 50);
		pXboxAButton->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 50, 550, 50, 50));
		m_pMenuInterface->AddComponent(pXboxAButton);

		Rectangle* pXboxBButton = new Rectangle();
		pXboxBButton->Initialise(Vector2(m_pQuitButton->GetPosition().x, m_pQuitButton->GetPosition().y - 40), 50, 50);
		pXboxBButton->SetBackgroundSprite(SpriteManager::GetInstance().CreateSpriteFromSheet("assets//UISpriteSheet.png", 100, 550, 50, 50));
		m_pMenuInterface->AddComponent(pXboxBButton);
	}
}