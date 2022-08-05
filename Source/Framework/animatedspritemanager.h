//Local include
#ifndef __ANIMATEDSPRITEMANAGER_H__
#define __ANIMATEDSPRITEMANAGER_H__

// Forward Declarations:
class AnimatedSprite;
class Player;

class AnimatedSpriteManager
{
	// --- Member methods ---
public:
	AnimatedSpriteManager();
	~AnimatedSpriteManager();

	void Initialise();

	//Get Sprites
	AnimatedSprite* GetStandingRight();
	AnimatedSprite* GetStandingLeft();

	AnimatedSprite* GetRunningRight();
	AnimatedSprite* GetRunningLeft();

	AnimatedSprite* GetJumpingRight();
	AnimatedSprite* GetJumpingLeft();

protected:

private:

	// --- Member data ---
public:

protected:
	//Standing 
	AnimatedSprite* m_pStandingLeftSprite;
	AnimatedSprite* m_pStandingRightSprite;
	//Jumping
	AnimatedSprite* m_pJumpingLeftSprite;
	AnimatedSprite* m_pJumpingRightSprite;
	//Running
	AnimatedSprite* m_pRunningLeftSprite;
	AnimatedSprite* m_pRunningRightSprite;
private:
};

#endif //__ANIMATEDSPRITEMANAGER_H__