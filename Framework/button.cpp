#include "button.h"

#include "backbuffer.h"
#include "logmanager.h"
#include <stdio.h>
#include <string>

Button::Button()
{
	//Set default values
	m_primaryColour = Colour(255, 255, 255);
	m_secondaryColour = Colour(0, 120, 255);
	m_primaryColourDisabled = Colour(100,100,100);
	m_secondaryColourDisabled = Colour(155, 155, 155);
	m_pCurrentSprite = nullptr;
	m_pButtonSprite = nullptr;
	m_pButtonHoverSprite = nullptr;
	m_pButtonClickedSprite = nullptr;
	m_pLabelFont = TTF_OpenFont("assets//arial.ttf", m_fontSize);
	m_width = 100;
	m_height = 40;
}

Button::~Button()
{
	
}

void Button::Initialise(std::string buttonText, Vector2 center)
{
	m_center = center;
	m_position = Vector2(center.x - (static_cast<float>(m_width) / 2), center.y - (static_cast<float>(m_height) / 2));
	m_pLabelText = buttonText;
}

void Button::Initialise(std::string buttonText, Vector2 center, int buttonWidth, int buttonHeight)
{
	m_center = center;
	m_position = Vector2(center.x - (static_cast<float>(buttonWidth) / 2), center.y - (static_cast<float>(buttonHeight) / 2));
	m_width = buttonWidth;
	m_height = buttonHeight;
	m_pLabelText = buttonText;
}

void Button::Initialise(std::string buttonText, Vector2 center, int buttonWidth, int buttonHeight, Colour textColour, Colour buttonColour)
{
	m_center = center;
	m_position = Vector2(center.x - static_cast<float>(buttonWidth) / 2, center.y - static_cast<float>(buttonHeight) / 2);
	m_width = buttonWidth;
	m_height = buttonHeight;
	m_pLabelText = buttonText;
	m_primaryColour = textColour;
	m_secondaryColour = buttonColour;
}


Vector2 Button::GetButtonCenter()
{
	return m_center;
}

bool Button::CheckClicked(int x, int y)
{
	if (m_enabled)
	{
		if (x >= m_position.GetXi() && y >= m_position.GetYi() && x <= m_position.GetXi() + m_width && y <= m_position.GetYi() + m_height)
		{
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Button::Draw(BackBuffer& backBuffer)
{	
	if (m_visible)
	{
		UpdateButtonSprite();
		
		if (m_enabled)
		{
			backBuffer.SetDrawColour(m_secondaryColour);
			backBuffer.SetTextColour(m_primaryColour);
		}
		else
		{
			backBuffer.SetDrawColour(m_secondaryColourDisabled);
			backBuffer.SetTextColour(m_primaryColourDisabled);
		}
		
		//Text rectangle sizes for centering
		int textWidth = 0;
		int textHeight = 0;

		TTF_SizeText(m_pLabelFont, m_pLabelText.c_str(), &textWidth, &textHeight); //Get text rectangle size

		if (m_pCurrentSprite != nullptr)
		{
			backBuffer.DrawFromSpriteSheet(*m_pCurrentSprite, m_position.GetXi(), m_position.GetYi());
			backBuffer.DrawText((m_center.GetXi() - (textWidth / 2)), (m_center.GetYi() - (textHeight / 2)), m_pLabelFont, m_pLabelText.c_str());
		}
		else
		{
			backBuffer.DrawRectangle(m_position.GetXi(), m_position.GetYi(), m_position.GetXi() + m_width, m_position.GetYi() + m_height);
			backBuffer.DrawText((m_center.GetXi() - (textWidth / 2)), (m_center.GetYi() - (textHeight / 2)), m_pLabelFont, m_pLabelText.c_str());
		}
	}
	
}

void Button::SetButtonSprite(Sprite* sprite)
{
	m_pButtonSprite = sprite;
	m_width = sprite->GetWidth();
	m_height = sprite->GetHeight();
}

void Button::SetButtonHoverSprite(Sprite* sprite)
{
	m_pButtonHoverSprite = sprite;
}

void Button::SetButtonClickedSprite(Sprite* sprite)
{
	m_pButtonClickedSprite = sprite;
}

void Button::UpdateButtonSprite()
{
	if (m_pButtonSprite != nullptr)
	{
		int mouseX = 0;
		int mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);

		//if hovered
		if (CheckClicked(mouseX, mouseY))
		{
			m_pCurrentSprite = m_pButtonHoverSprite;
		}
		//else if pressed
		else
			m_pCurrentSprite = m_pButtonSprite;
		
	}
}

