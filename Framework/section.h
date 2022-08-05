#pragma once
#include <list>

#include "platform.h"
class Enemy;
class GroundPassiveEnemy;
class GroundAggressiveEnemy;
class FlyingAggressiveEnemy;
class PickUps;
class Player;

class Section
{
public:
	Section();
	~Section();
	void Initialise(Vector2 position);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	
	/*Adds a single platform to the existing platforms*/
	void AddPlatform(Platform* platform);
	/*Replaces current platforms with a new list of platforms*/
	void AddPlatforms(std::list<Platform*> platforms);
	void AddPickUps(std::list<PickUps*> pickUps);

	void AddEnemies(std::list<Enemy*> enemies);
	void AddGPEnemies(std::list<GroundPassiveEnemy*> gpEnemies);
	void AddGAEnemies(std::list<GroundAggressiveEnemy*> gaEnemies);
	void AddFAEnemies(std::list<FlyingAggressiveEnemy*> faEnemies);
	
	Vector2 GetPosition();
	void SetPosition(Vector2 position);
	void UpdatePosition(Vector2 position);

	void CheckPickUpCollisions(Player* player);

	void RenewPickUps();
	void RenewEnemies();
	void RenewPlatforms();



	std::list<Platform*> GetPlatforms();
	std::list<Enemy*> GetEnemies();

protected:
private:

public:
protected:
	Vector2 m_position;
	std::list<Platform*> m_platforms;
	std::list<PickUps*> m_pickUps;

	std::list<Enemy*> m_enemies;
	std::list<GroundPassiveEnemy*> m_gpEnemies;
	std::list<GroundAggressiveEnemy*> m_gaEnemies;
	std::list<FlyingAggressiveEnemy*> m_faEnemies;

private:
};

