// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"
#include "sprite.h"
#include "logmanager.h"
#include <vector>
#include <iterator>

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.0f)
	, m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
	, m_row(0)
{
}

AnimatedSprite::~AnimatedSprite()
{
	frameContainer.clear();
}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	for (int i = 0; i < GetTotalFrames(); i++)
	{
		AddFrame(m_frameWidth*i);

		//Frame container debug stub
		/*char buffer[100];
		sprintf_s(buffer, "Frame container at position %d has Frame Coordinate %d: Sprite Frame width is: %d", i, m_frameWidth*i, texture.GetWidth());
		LogManager::GetInstance().Log(buffer);*/
	}

	m_loop = true;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

bool AnimatedSprite::Initialise(Texture & texture, int row)
{
	//Set this->row to m_row
	//Points to what row to print
	m_row = row;

	for (int i = 0; i < GetTotalFrames(); i++)
	{
		AddFrame(m_frameWidth*i);

		//Frame container debug stub
		/*char buffer[100];
		sprintf_s(buffer, "Frame container at position %d has Frame Coordinate %d: Sprite Frame width is: %d", i, m_frameWidth*i, texture.GetWidth());
		LogManager::GetInstance().Log(buffer);*/
	}

	m_loop = true;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void
AnimatedSprite::AddFrame(int x)
{
	frameContainer.push_back(x);
}

void
AnimatedSprite::Process(float deltaTime)
{
	if (!this->IsPaused())
	{
		if (IsAnimating() == true)
		{
			m_timeElapsed += deltaTime;
			if (m_timeElapsed > m_frameSpeed)
			{
				m_currentFrame++;
				m_timeElapsed = 0;
			}
		}
	}
	else
	{
		m_animating = false;
	}

	//Stop the animation if it is not looping...
	if (IsLooping() == false)
	{
		if (m_currentFrame >= frameContainer.size())
		{
			m_animating = false;
			m_currentFrame = 0;
			//Debug stub
			/*char buffer[64];
			sprintf(buffer, "Pause: %d", IsPaused());
			LogManager::GetInstance().Log(buffer);*/
		}
	}

	if (m_currentFrame >= frameContainer.size())
	{
		m_currentFrame = 0;
	}
}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	backbuffer.DrawAnimatedSprite(*this, frameContainer.at(m_currentFrame));
}

void
AnimatedSprite::SetTotalFrames(int frames)
{
	m_TotalFrames = frames;
}

int AnimatedSprite::GetWidth() const
{
	return m_frameWidth;
}

int AnimatedSprite::GetHeight() const
{
	return m_frameHeight;
}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void
AnimatedSprite::SetFrameHeight(int w)
{
	m_frameHeight = w;
}

int
AnimatedSprite::GetCurrentFrame()
{
	return (m_currentFrame);
}

int AnimatedSprite::GetFrameWidth()
{
	return m_frameWidth;
}

int AnimatedSprite::GetFrameHeight()
{
	return m_frameHeight;
}

int
AnimatedSprite::GetTotalFrames()
{
	return (m_TotalFrames);
}

void
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

int
AnimatedSprite::GetSpriteRow()
{
	return (m_row);
}