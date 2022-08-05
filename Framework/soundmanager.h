// Created by Papaya Game Studio

#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

// Forward Declarations
#include "fmod.hpp"

class SoundManager
{
	//Member methods
public:
	static SoundManager& GetInstance();
	static void DestroyInstance();

	void Initialise();

	//Play sound methods
	//void PlayBGMusic();

	void PlayJumpSFX();
	void PlayKiwiCoinSFX();
	void PlayPowerUpSFX();
	void PlayShootSFX();
	void PlayDeadSFX();
	void PlayEnemyDeadSFX();
	void PlayGameOverSFX();
	void PlayCrumblePlatformSFX();

	void ToggleSound();
	bool IsSoundEnabled();

	FMOD::System* GetFMODSystem();

protected:
private:
	SoundManager();
	~SoundManager();

	//Member data
public:
protected:
	static SoundManager* sm_pInstance;
private:
	//Sounds
	FMOD::System *m_pFMODSystem;
	FMOD::SoundGroup* m_pSFXGroup;

	//FMOD::Sound* m_pBgMusic;
	FMOD::Sound* m_pKiwiCoinSFX;
	FMOD::Sound* m_pJumpSFX;
	FMOD::Sound* m_pPowerUpSFX;
	FMOD::Sound* m_pShootSFX;
	FMOD::Sound* m_pDeadSFX;
	FMOD::Sound* m_pEnemyDeadSFX;
	FMOD::Sound* m_pGameOverSFX;
	FMOD::Sound* m_pCrumblingPlatformSFX;

	bool m_soundOn;
};

#endif // __SOUNDMANAGER_H__