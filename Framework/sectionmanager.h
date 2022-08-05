#pragma once
#include <vector>

#include "inireader.h"
#include "section.h"
class BackBuffer;

class SectionManager
{
public:
	SectionManager();
	~SectionManager();

	void ResetSections();
	//generate a random pickup
	PickUps * SpawnRandomPowerUp();

	//void Initialise(BackBuffer& backBuffer); //Don't need backbuffer for now.
	bool LoadSections(char* sectionFileName);
	Section* DespawnSection();
	void ShuffleSections();

	
protected:
private:

public:
	INIReader m_sectionReader;
	list<Section*> m_loadedSections;
	list<Section*> m_activeSections; //Sections currently in play
	Section* topSection;
	Section* bottomSection;
	BackBuffer* m_pBackBuffer;
protected:
private:
};

