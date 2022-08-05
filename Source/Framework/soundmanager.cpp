// Created by Papaya Game Studio

// This includes:
#include "soundmanager.h"

// Local includes:


// Library includes:
#include "fmod.hpp"
#include "fmod_errors.h"
#include <SDL.h>
#include <cstdio>

//Static members:
SoundManager* SoundManager::sm_pInstance = 0;

SoundManager::SoundManager()
	: m_soundOn(true)
{

}

SoundManager::~SoundManager()
{
	//Release and close sound
	//m_pBgMusic->release();

	m_pSFXGroup->release();
	m_pFMODSystem->release();
	m_pFMODSystem->close();
}

SoundManager&
SoundManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new SoundManager();
	}

	return *sm_pInstance;
}

void
SoundManager::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

void
SoundManager::Initialise()
{
	//Initialise FMOD Core API - /doc/FMOD API User Manual/white-papers-getting-started.html
	FMOD_RESULT result;
	m_pFMODSystem = 0;
	result = FMOD::System_Create(&m_pFMODSystem);      // Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
	result = m_pFMODSystem->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	//Initialise sounds EXAMPLE
	m_pFMODSystem->createSoundGroup("Group", &m_pSFXGroup);
	//system->createStream("assets\\Sounds\\KorobeinikiPappyRemix.mp3", FMOD_LOOP_NORMAL | FMOD_2D, 0, &m_pBgMusic);	m_pBgMusic->setSoundGroup(m_pSFXGroup);
	
	m_pFMODSystem->createSound("assets\\Sounds\\kiwicoinsound.wav", FMOD_DEFAULT, 0, &m_pKiwiCoinSFX);						m_pKiwiCoinSFX->setSoundGroup(m_pSFXGroup);
	m_pFMODSystem->createSound("assets\\Sounds\\powerupsound.wav", FMOD_DEFAULT, 0, &m_pPowerUpSFX);					m_pPowerUpSFX->setSoundGroup(m_pSFXGroup);
	m_pFMODSystem->createSound("assets\\Sounds\\jumpsound.wav", FMOD_DEFAULT, 0, &m_pJumpSFX);						m_pJumpSFX->setSoundGroup(m_pSFXGroup);
	m_pFMODSystem->createSound("assets\\Sounds\\lasersound.wav", FMOD_DEFAULT, 0, &m_pShootSFX);					m_pShootSFX->setSoundGroup(m_pSFXGroup);
	m_pFMODSystem->createSound("assets\\Sounds\\deadsound.wav", FMOD_DEFAULT, 0, &m_pDeadSFX);					m_pDeadSFX->setSoundGroup(m_pSFXGroup);
	m_pFMODSystem->createSound("assets\\Sounds\\enemydead.wav", FMOD_DEFAULT, 0, &m_pEnemyDeadSFX);					m_pEnemyDeadSFX->setSoundGroup(m_pSFXGroup);
	m_pFMODSystem->createSound("assets\\Sounds\\gameover.wav", FMOD_DEFAULT, 0, &m_pGameOverSFX);					m_pGameOverSFX->setSoundGroup(m_pSFXGroup);
	m_pFMODSystem->createSound("assets\\Sounds\\crumblingplatform.wav", FMOD_DEFAULT, 0, &m_pCrumblingPlatformSFX);		m_pCrumblingPlatformSFX->setSoundGroup(m_pSFXGroup);

	//Start playing background music
	//PlayBGMusic();
}

FMOD::System*
SoundManager::GetFMODSystem()
{
	return m_pFMODSystem;
}

/*
void
SoundManager::PlayBGMusic()
{
	//Start playing BG music
	if (m_soundOn) {
		m_pFMODSystem->playSound(m_pBgMusic, 0, false, 0);
	}
}
*/

void SoundManager::PlayJumpSFX()
{
	if (m_soundOn)
	{
		m_pFMODSystem->playSound(m_pJumpSFX, 0, false, 0);
	}
}

void SoundManager::PlayKiwiCoinSFX()
{
	if (m_soundOn) 
	{
		m_pFMODSystem->playSound(m_pKiwiCoinSFX, 0, false, 0);
	}
}

void SoundManager::PlayPowerUpSFX()
{
	if (m_soundOn)
	{
		m_pFMODSystem->playSound(m_pPowerUpSFX, 0, false, 0);
	}
}

void SoundManager::PlayShootSFX()
{
	if (m_soundOn)
	{
		m_pFMODSystem->playSound(m_pShootSFX, 0, false, 0);
	}
}

void SoundManager::PlayDeadSFX()
{
	if (m_soundOn)
	{
		m_pFMODSystem->playSound(m_pDeadSFX, 0, false, 0);
	}
}

void SoundManager::PlayEnemyDeadSFX()
{
	if (m_soundOn)
	{
		m_pFMODSystem->playSound(m_pEnemyDeadSFX, 0, false, 0);
	}
}

void SoundManager::PlayGameOverSFX()
{
	if (m_soundOn)
	{
		m_pFMODSystem->playSound(m_pGameOverSFX, 0, false, 0);
	}
}

void SoundManager::PlayCrumblePlatformSFX()
{
	if (m_soundOn)
	{
		m_pFMODSystem->playSound(m_pCrumblingPlatformSFX, 0, false, 0);
	}
}

void
SoundManager::ToggleSound()
{
	m_soundOn = !m_soundOn;

	if (m_soundOn)
	{
		m_pSFXGroup->setVolume(1.0f);
	}
	else
	{
		m_pSFXGroup->setVolume(0.0f);
	}
}

bool SoundManager::IsSoundEnabled()
{
	return m_soundOn;
}