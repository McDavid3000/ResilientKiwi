// This include:
#include "spritemanager.h"

// Local includes:
#include "backbuffer.h"
#include "sprite.h"

// Library includes:
#include <vector>
#include <string>

#include "animatedspritemanager.h"

using std::string;

// Static members 
SpriteManager* SpriteManager::sm_pInstance = 0;


SpriteManager::SpriteManager()
{
	
}
SpriteManager::~SpriteManager()
{
	// Delete all sprites in master list
	for (Sprite* currentSprite : m_SpriteList)
	{
		delete currentSprite;
		currentSprite = 0;
	}

	delete m_pAnimatedSpriteManager;
	m_pAnimatedSpriteManager = nullptr;
}


SpriteManager&
SpriteManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new SpriteManager();
	}

	return *sm_pInstance;
}
void
SpriteManager::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}


// Method to feed BackBuffer into the manager
void	
SpriteManager::InitialiseManager(BackBuffer* backBuffer)
{
	sm_pInstance->m_pBackBuffer = backBuffer;
	sm_pInstance->m_pAnimatedSpriteManager = new AnimatedSpriteManager();
	sm_pInstance->m_pAnimatedSpriteManager->Initialise();
}

//Creates a sprite, returns it but also saves it into manager
Sprite*	
SpriteManager::CreateSprite(const char* pcFileName)
{
	// Create sprite using BackBuffer
	Sprite* newSprite = sm_pInstance->m_pBackBuffer->CreateSprite(pcFileName);

	// Save it in the master list
	sm_pInstance->m_SpriteList.push_back(newSprite);

	// Return newly created sprite
	return newSprite;
}

Sprite*
SpriteManager::CreateSpriteFromSheet(const char* pcFileName, int x, int y, int width, int height)
{
	// Create sprite using BackBuffer
	Sprite* newSprite = sm_pInstance->m_pBackBuffer->CreateSprite(pcFileName);
	newSprite->Initialise(*newSprite->GetTexture(), x, y, width, height);

	// Save it in the master list
	sm_pInstance->m_SpriteList.push_back(newSprite);

	// Return newly created sprite
	return newSprite;
}

//Get a sprite by giving the method the filename
Sprite*
SpriteManager::GetSprite(const char* pcFileName)
{
	string requestedFileString = pcFileName;

	//Search all sprites in list for one that could contain the parameter name
	for (Sprite* currentSprite : sm_pInstance->m_SpriteList)
	{
		string currentFileString = currentSprite->GetFileName();

		if (requestedFileString.compare(currentFileString) == 0) //TRUE if strings are equal
		{
			return currentSprite;
		}
	}

	//If no sprite has been returned, it does not exist in the manager
	return NULL;
}

AnimatedSpriteManager* SpriteManager::GetAnimatedSpriteManager()
{
	return sm_pInstance->m_pAnimatedSpriteManager;
}
