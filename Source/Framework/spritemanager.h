#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

class AnimatedSpriteManager;
// Forward Declarations:
class BackBuffer;
class Sprite;

#include <vector>

//Singleton class to manage sprites and access them
class SpriteManager
{
	// --- Member methods ---
public:
	static SpriteManager& GetInstance();
	static void DestroyInstance();

	static void InitialiseManager(BackBuffer* backBuffer);
	
	static Sprite* CreateSprite(const char* pcFileName);
	static Sprite* CreateSpriteFromSheet(const char* pcFileName, int x, int y, int width, int height);
	static Sprite* GetSprite(const char* pcFileName);
	static AnimatedSpriteManager* GetAnimatedSpriteManager();

protected:

private:
	SpriteManager();	
	~SpriteManager();	//Must delete all sprites


	// --- Member data ---
public:

protected:
	static SpriteManager* sm_pInstance;

private:
	BackBuffer* m_pBackBuffer;
	std::vector<Sprite*> m_SpriteList;
	AnimatedSpriteManager* m_pAnimatedSpriteManager;

};

#endif //__SPRITEMANAGER_H__