#pragma once
#include "platform.h"
class CrumblingPlatform : public Platform
{
public:
	CrumblingPlatform();
	~CrumblingPlatform();

	bool Initialise(Vector2 m_position, int width, int height, float timeToBreak);
	bool Initialise(Sprite* sprite) override;
	void Process(float deltaTime) override;
	void Draw(BackBuffer& backBuffer) override;
	bool IsCollidingWith(Entity& e) override;
	bool IsCollidingWith(int x, int y, int w, int h) override;

	bool IsCrumbling();
	void SetCrumbling(bool crumble);
	void ResetPosition(Vector2 sectionPosition);

	void ResetPlatform() override;
	void SetDead(bool dead);

protected:
private:

public:
protected:
	bool m_crumble;
	float m_timeToBreak;
	float m_respawnCountdown;

	bool m_soundEffectPlayed;
private:
};

