#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "sprite.h"
#include <vector>

using namespace std;

class BackBuffer;
class Texture;
class Sprite;

class AnimatedSprite : public Sprite
{
	//Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	//Add initialise that takes in Y value
	bool Initialise(Texture& texture, int row);

	void AddFrame(int x);
	
	void Process(float deltaTime);
	void Draw(BackBuffer& buffer);

	void SetFrameSpeed(float f);
	void SetFrameWidth(int w);
	void SetFrameHeight(int w);
	void SetTotalFrames(int frames);

	int GetWidth() const;
	int GetHeight() const;

	int GetTotalFrames();
	int GetCurrentFrame();
	int GetFrameWidth();
	int GetFrameHeight();

	void Pause();
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

	//add a getter for y value
	int GetSpriteRow();

protected:
private:

	//Fields
public:

protected:
	vector<int> frameContainer;

	float m_frameSpeed;
	int m_frameWidth;
	int m_frameHeight;

	int m_TotalFrames;

	float m_timeElapsed;
	unsigned int m_currentFrame;

	bool m_paused;
	bool m_loop;
	bool m_animating;

	int m_row;
private:

};

#endif // ! __ANIMATEDSPRITE_H__
