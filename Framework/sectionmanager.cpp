#include "sectionmanager.h"

#include <algorithm>
#include <ctime>

#include "crumblingplatform.h"
#include "movingplatform.h"

//enemy includes
#include "enemyfactory.h"
#include "enemy.h"

//Pickup includes
#include "pickupfactory.h"
#include "pickups.h"
#include "logmanager.h"



using namespace std;

SectionManager::SectionManager()
{
}

SectionManager::~SectionManager()
{
	for (auto section : m_loadedSections)
	{
		delete section;
		section = nullptr;
	}

	for (auto section : m_activeSections)
	{
		delete section;
		section = nullptr;
	}
}

//Don't need backbuffer for now.
// void SectionManager::Initialise(BackBuffer& backBuffer)
// {
// 	m_pBackBuffer = &backBuffer;
// }

bool SectionManager::LoadSections(char* sectionFileName)
{
	srand(unsigned int(time(0)));

	bool dataLoaded = m_sectionReader.LoadIniFile("assets//Sections.ini");

	//Platform Variables
	const int GRID_WIDTH = 30;
	const int GRID_HEIGHT = 30;
	const int SCREEN_WIDTH = 480;
	const char STATIC = '#';
	const char CRUMBLING = '~';
	const char MOVING_UP = '^';
	const char MOVING_DOWN = 'v';
	const char MOVING_LEFT = '<';
	const char MOVING_RIGHT = '>';
	const int MOVING_DISTANCE = 210; //Distance rising/lowering platforms move from their start.

	//Enemies
	const char GROUND_PASSIVE_ENEMY = 'G';
	const char GROUND_AGGRESSIVE_ENEMY = 'H';
	const char FLYING_AGGRESSIVE_ENEMY = 'F';

	//Pickups
	const char KIWICOIN = '$';
	const char GUMBOOTS_POWERUP = 'B';
	const char LANDP_POWERUP = 'L';
	const char HIVIS_POWERUP = 'J';
	const char RANDOM_PICKUP = 'P';

	if (dataLoaded)
	{
		for (auto m_section : m_sectionReader.GetLoadedSections())
		{
			//Get Section info
			string sectionName = m_sectionReader.GetValueAsString(m_section, "SectionName");
			string sectionFileLocation = m_sectionReader.GetValueAsString(m_section, "SectionFile");
			
			//Create empty list of platforms
			list<Platform*> platforms; 
			list<PickUps*> pickups;

			list<Enemy*> enemies;
			list<GroundPassiveEnemy*> gpEnemies;
			list<GroundAggressiveEnemy*> gaEnemies;
			list<FlyingAggressiveEnemy*> faEnemies;


			//Create file input stream for reading the section file.
			ifstream sectionFile;
			sectionFile.open(sectionFileLocation);

			if (sectionFile.is_open())
			{
				//Initialise file buffer and counters.
				char lineBuffer[128];
				int charCount = 0; //Determines what character in the line we are reading
				int lineCount = 0; //Determines what line in the file we are reading

				while (sectionFile.getline(lineBuffer, 128))
				{
					int currentPlatformWidth = 0;
					int platformHeight = GRID_HEIGHT;
					
					//While not at end of line
					while (lineBuffer[charCount] != '\0')
					{
						char readChar = lineBuffer[charCount];
						
						if (readChar == '0' || readChar == ' ')
						{
							//DO NOTHING
						}
						else if (readChar == STATIC )
						{
							if (lineBuffer[charCount - 2] != STATIC) //Previous char wasn't a static platform symbol
							{
								platforms.push_back(new Platform());
								platforms.back()->SetPosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * lineCount))); //Set start position
								currentPlatformWidth += GRID_WIDTH;
							}
							else //If platform already started
							{
								currentPlatformWidth += GRID_WIDTH; //Increase width of this platform
							}
							
							if (lineBuffer[charCount + 2] != STATIC) //if next char isn't a static platform
							{
								//Initialise platform
								platforms.back()->Initialise(platforms.back()->GetPosition(), currentPlatformWidth, platformHeight);
								currentPlatformWidth = 0; //Reset width counter
							}
							
						}
						else if (readChar == MOVING_UP)
						{
							//MOVING PLATFORM (UP)
							if (lineBuffer[charCount - 2] != MOVING_UP) //Previous char wasn't a moving platform symbol
							{
								platforms.push_back(new MovingPlatform());
								platforms.back()->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * lineCount))); //Set start position
								currentPlatformWidth += GRID_WIDTH;
							}
							else //If platform aready started
							{
								currentPlatformWidth += GRID_WIDTH; //Increase width of this platform
							}

							if (lineBuffer[charCount + 2] != MOVING_UP) //if next char isn't a moving platform
							{
								//Initialise platform
								Vector2 positionTwo(platforms.back()->GetPosition().x, (platforms.back()->GetPosition().y - MOVING_DISTANCE));
								dynamic_cast<MovingPlatform*>(platforms.back())->Initialise(platforms.back()->GetRelativePosition(), positionTwo, currentPlatformWidth, platformHeight);
								dynamic_cast<MovingPlatform*>(platforms.back())->SetDirection(MovingPlatform::UP);
								currentPlatformWidth = 0; //Reset width counter
							}
						}
						else if (readChar == MOVING_DOWN)
						{
							//MOVING PLATFORM PLATFORM (DOWN)
							if (lineBuffer[charCount - 2] != MOVING_DOWN) //Previous char wasn't a moving platform symbol
							{
								platforms.push_back(new MovingPlatform());
								platforms.back()->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * lineCount))); //Set start position
								currentPlatformWidth += GRID_WIDTH;
							}
							else //If platform aready started
							{
								currentPlatformWidth += GRID_WIDTH; //Increase width of this platform
							}

							if (lineBuffer[charCount + 2] != MOVING_DOWN) //If next char isn't a moving platform
							{
								Vector2 positionTwo(platforms.back()->GetPosition().x, (platforms.back()->GetPosition().y + MOVING_DISTANCE));

								dynamic_cast<MovingPlatform*>(platforms.back())->Initialise(positionTwo, platforms.back()->GetPosition(), currentPlatformWidth, platformHeight);
								dynamic_cast<MovingPlatform*>(platforms.back())->SetDirection(MovingPlatform::DOWN);
								currentPlatformWidth = 0; //Reset width counter
							}
						}
						else if (readChar == MOVING_LEFT)
						{
							//MOVING PLATFORM PLATFORM (LEFT)
							if (lineBuffer[charCount - 2] != MOVING_LEFT) //Previous char wasn't a moving platform symbol
							{
								platforms.push_back(new MovingPlatform());
								platforms.back()->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * lineCount))); //Set start position
								currentPlatformWidth += GRID_WIDTH;
							}
							else //If platform aready started
							{
								currentPlatformWidth += GRID_WIDTH; //Increase width of this platform
							}

							if (lineBuffer[charCount + 2] != MOVING_LEFT) //If next char isn't a moving platform
							{
								//Initialise platform
								Vector2 positionTwo(0, platforms.back()->GetPosition().y);
								dynamic_cast<MovingPlatform*>(platforms.back())->Initialise(positionTwo, platforms.back()->GetPosition(), currentPlatformWidth, platformHeight);
								dynamic_cast<MovingPlatform*>(platforms.back())->SetDirection(MovingPlatform::LEFT);
								currentPlatformWidth = 0; //Reset width counter
							}
						}
						else if (readChar == MOVING_RIGHT)
						{
							//MOVING PLATFORM PLATFORM (RIGHT)
							if (lineBuffer[charCount - 2] != MOVING_RIGHT) //Previous char wasn't a moving platform symbol
							{
								//Create initial platform
								platforms.push_back(new MovingPlatform());
								platforms.back()->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH)/2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * lineCount))); //Set start position
								currentPlatformWidth += GRID_WIDTH;
							}
							else //If platform aready started
							{
								currentPlatformWidth += GRID_WIDTH; //Increase width of this platform
							}

							if (lineBuffer[charCount + 2] != MOVING_RIGHT) //If next char isn't a moving platform
							{
								//Initialise platform
								Vector2 positionTwo(static_cast<float>(SCREEN_WIDTH - currentPlatformWidth), platforms.back()->GetPosition().y);
								dynamic_cast<MovingPlatform*>(platforms.back())->Initialise(platforms.back()->GetPosition(), positionTwo, currentPlatformWidth, platformHeight);
								dynamic_cast<MovingPlatform*>(platforms.back())->SetDirection(MovingPlatform::RIGHT);
								currentPlatformWidth = 0; //Reset width counter
							}
						}
						else if (readChar == CRUMBLING)
						{
							//CRUMBLING PLATFORM PLATFORM
							if (lineBuffer[charCount - 2] != CRUMBLING) //Previous char wasn't a crumbling platform symbol
							{
								platforms.push_back(new CrumblingPlatform());
								platforms.back()->SetPosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * lineCount))); //Set start position
								currentPlatformWidth += GRID_WIDTH;
							}
							else //If platform aready started
							{
								currentPlatformWidth += GRID_WIDTH; //Increase width of this platform
							}

							if (lineBuffer[charCount + 2] != CRUMBLING) //If next char isn't a crumbling platform
							{
								//Initialise platform
								float timeToBreak = 5;
								dynamic_cast<CrumblingPlatform*>(platforms.back())->Initialise(platforms.back()->GetPosition(), currentPlatformWidth, platformHeight, timeToBreak);
								currentPlatformWidth = 0; //Reset width counter
							}
						}
						else if (readChar == GROUND_PASSIVE_ENEMY)
						{
							//SPAWN GROUND PASSIVE ENEMY
							Enemy* newGroundPassiveEnemy = EnemyFactory::GetInstance().CreateGroundPassiveEnemy();
							newGroundPassiveEnemy->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * (lineCount - 1))));
							enemies.push_back(newGroundPassiveEnemy);
							gpEnemies.push_back((GroundPassiveEnemy*)newGroundPassiveEnemy);
						}
						else if (readChar == GROUND_AGGRESSIVE_ENEMY)
						{
							Enemy* newGroundAggressiveEnemy = EnemyFactory::GetInstance().CreateGroundAggressiveEnemy();
							newGroundAggressiveEnemy->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * (lineCount - 1))));
							enemies.push_back(newGroundAggressiveEnemy);
							gaEnemies.push_back((GroundAggressiveEnemy*)newGroundAggressiveEnemy);
						}
						else if (readChar == FLYING_AGGRESSIVE_ENEMY)
						{
							Enemy* newFlyingAggressiveEnemy = EnemyFactory::GetInstance().CreateFlyingAggressiveEnemy();
							newFlyingAggressiveEnemy->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * (lineCount - 1))));
							enemies.push_back(newFlyingAggressiveEnemy);
							faEnemies.push_back((FlyingAggressiveEnemy*)newFlyingAggressiveEnemy);
						}
						else if (readChar == KIWICOIN)
						{
							PickUps* newKiwiCoin = PickUpFactory::GetInstance().CreateKiwiCoin();
							newKiwiCoin->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * (lineCount - 1))));
							pickups.push_back(newKiwiCoin);
						}
						else if (readChar == GUMBOOTS_POWERUP)
						{
							PickUps* newGumboots = PickUpFactory::GetInstance().CreateGumbootsPowerUp();
							newGumboots->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * (lineCount - 1))));
							pickups.push_back(newGumboots);
						}
						else if (readChar == LANDP_POWERUP)
						{
							PickUps* newLandP = PickUpFactory::GetInstance().CreateLandPPowerUp();
							newLandP->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * (lineCount - 1))));
							pickups.push_back(newLandP);
						}
						else if (readChar == HIVIS_POWERUP)
						{
							PickUps* newHiVis = PickUpFactory::GetInstance().CreateHiVisPowerUp();
							newHiVis->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * (lineCount - 1))));
							pickups.push_back(newHiVis);
						}
						else if (readChar == RANDOM_PICKUP)
						{
							PickUps* newPickup = SpawnRandomPowerUp();
							newPickup->SetRelativePosition(Vector2((static_cast<float>(GRID_WIDTH) / 2) * static_cast<float>(charCount), static_cast<float>(GRID_HEIGHT * (lineCount - 1))));
							pickups.push_back(newPickup);
						}

						charCount++; //Move onto next char
					}
					//Loop exited (end of line)
					charCount = 0; //Reset char count
					lineCount++; //Increase line count
				}
				//After reached end of file,
				m_loadedSections.push_back(new Section()); //Create a new section
				m_loadedSections.back()->AddPlatforms(platforms); //Add platforms to the section
				m_loadedSections.back()->AddPickUps(pickups);

				m_loadedSections.back()->AddEnemies(enemies);
				m_loadedSections.back()->AddGPEnemies(gpEnemies);
				m_loadedSections.back()->AddGAEnemies(gaEnemies);
				m_loadedSections.back()->AddFAEnemies(faEnemies);


				//Give all enemies reference to the platforms in the section
				for (auto enemy : enemies)
				{
					enemy->SetSectionPlatforms(platforms);
				}

				for (auto pickup : pickups)
				{
					pickup->SetSectionPlatforms(platforms);
				}

			}
		}

		//Shuffle sections
		ShuffleSections();
		m_activeSections.push_back(m_loadedSections.back());
		m_loadedSections.pop_back();
		m_activeSections.back()->SetPosition(Vector2(0, 0));

		m_activeSections.push_back(m_loadedSections.back());
		m_loadedSections.pop_back();
		m_activeSections.back()->SetPosition(Vector2(0, -854));

		m_activeSections.push_back(m_loadedSections.back());
		m_loadedSections.pop_back();
		m_activeSections.back()->SetPosition(Vector2(0, -1708));
		
		
		// m_activeSections.push_back(m_loadedSections.at(rand() % m_loadedSections.size()));
		// m_activeSections.back()->SetPosition(Vector2(0, -854));
		// m_activeSections.push_back(m_loadedSections.at(rand() % m_loadedSections.size()));
		// m_activeSections.back()->SetPosition(Vector2(0, -1708));

		return true;
	}
	else
	{
		//Failed to load sections!
		return false;
	}
}

Section* SectionManager::DespawnSection()
{
	//m_activeSections.pop_front();
	m_loadedSections.push_front(m_activeSections.front());
	//m_activeSections.pop_front();
	
	m_activeSections.push_back(m_loadedSections.back());
  	m_loadedSections.pop_back();
 	m_activeSections.back()->SetPosition(Vector2(0, -1708));
	ShuffleSections();
	return m_activeSections.front();
}

void SectionManager::ShuffleSections()
{
	std::vector<Section*> sectionShuffler(m_loadedSections.begin(), m_loadedSections.end());
	std::random_shuffle(sectionShuffler.begin(), sectionShuffler.end());

	std::copy(sectionShuffler.begin(), sectionShuffler.end(), m_loadedSections.begin());
}

void SectionManager::ResetSections()
{
	for (auto section : m_activeSections)
	{
		m_loadedSections.push_front(section);
	}
	m_activeSections.clear();
	
	m_activeSections.push_back(m_loadedSections.back());
	m_loadedSections.pop_back();
	m_activeSections.back()->SetPosition(Vector2(0, 0));

	m_activeSections.push_back(m_loadedSections.back());
	m_loadedSections.pop_back();
	m_activeSections.back()->SetPosition(Vector2(0, -854));

	m_activeSections.push_back(m_loadedSections.back());
	m_loadedSections.pop_back();
	m_activeSections.back()->SetPosition(Vector2(0, -1708));
}

PickUps*
SectionManager::SpawnRandomPowerUp()
{
	int powerupOdds = (rand() % 100) + 1;

	//char buffer[64];
	//sprintf(buffer, "%d", powerupOdds);
	//LogManager::GetInstance().Log(buffer);

	PickUps* pickup = 0;

	if (powerupOdds <= 20)
	{
		pickup = PickUpFactory::GetInstance().CreateGumbootsPowerUp();
	}
	else if (powerupOdds > 20 && powerupOdds <= 40)
	{
		pickup = PickUpFactory::GetInstance().CreateHiVisPowerUp();

	}
	else if (powerupOdds > 40 && powerupOdds <= 50)
	{
		pickup = PickUpFactory::GetInstance().CreateLandPPowerUp();
	}
	else
	{
		pickup = PickUpFactory::GetInstance().CreateKiwiCoin();
	}
	
	return pickup;
}


