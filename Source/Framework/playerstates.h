#ifndef __PLAYERSTATES_H_
#define __PLAYERSTATES_H_

#include <SDL.h>

//Forward declarations
class BackBuffer;
class Player;
class Sprite;
class AnimatedSprite;
class AnimatedSpriteManager;

class PlayerStates
{
public:
	//Player state methods

	PlayerStates();
	~PlayerStates();

	virtual void Initialise(Player* player) = 0;
	virtual void Process(float deltaTime);
	virtual void Draw(BackBuffer& backBuffer);
	virtual void HandleInput(SDL_Keycode key);

	//player wrap screen method
	void PerformBoundChecking();
	void CheckPlayerPlatformCollision();

	void ChangePlayerState(PlayerStates* state);

protected:
private:

public:
	Player* m_pPlayer;

	AnimatedSpriteManager* m_pAnimatedSpriteManager;
	AnimatedSprite* m_pLeftSprite;
	AnimatedSprite* m_pRightSprite;
protected:

private:

};
#endif __PLAYERSTATES_H_

