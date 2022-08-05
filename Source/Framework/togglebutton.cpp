#include "togglebutton.h"

#include "backbuffer.h"

ToggleButton::ToggleButton()
: m_selected(false)
, m_buttonSelectedColour(75, 160, 255)
, m_textSelectedColour(255, 255, 255)
{
	m_pButtonSprite = nullptr;
	m_pSelectedHoverSprite = nullptr;
	m_pSelectedClickedSprite = nullptr;
	m_pCurrentSprite = nullptr;
	m_pSelectedHoverSprite = nullptr;
	m_pSelectedClickedSprite = nullptr;
	m_pSelectedSprite = nullptr;
}

ToggleButton::~ToggleButton()
{
	
}

void ToggleButton::Initialise(std::string buttonText, Vector2 center)
{
	Button::Initialise(buttonText, center);
}

void ToggleButton::Initialise(std::string buttonText, Vector2 center, int buttonWidth, int buttonHeight)
{
	Button::Initialise(buttonText, center, buttonWidth, buttonHeight);
}

void ToggleButton::Initialise(Vector2 center, int buttonWidth, int buttonHeight, std::string buttonText, Colour textColour, Colour buttonColour)
{
	Button::Initialise(buttonText, center, buttonWidth, buttonHeight, textColour, buttonColour);
}

void ToggleButton::Draw(BackBuffer& backBuffer)
{
	if (m_visible)
	{
		UpdateButtonSprite();
		if (m_enabled)
		{
			if (m_selected)
			{
				backBuffer.SetDrawColour(m_buttonSelectedColour);
				backBuffer.SetTextColour(m_textSelectedColour);
			}
			else
			{
				backBuffer.SetDrawColour(m_secondaryColour);
				backBuffer.SetTextColour(m_primaryColour);
			}
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
		}
		else {
			backBuffer.DrawRectangle(m_position.GetXi(), m_position.GetYi(), m_position.GetXi() + m_width, m_position.GetYi() + m_height);
		}
		backBuffer.DrawText((m_center.GetXi() - textWidth / 2), (m_center.GetYi() - textHeight / 2), m_pLabelFont, m_pLabelText.c_str());
	}
}

bool ToggleButton::CheckClicked(int x, int y)
{
	if (Button::CheckClicked(x, y))
	{
		SetSelected(!m_selected);
		return true;
	}
	return false;
}

bool ToggleButton::CheckHovered(int x, int y)
{
	return Button::CheckClicked(x, y);
}

bool ToggleButton::IsSelected()
{
	return m_selected;
}

void ToggleButton::SetSelected(bool selected)
{
	m_selected = selected;

	UpdateButtonSprite();
}

void ToggleButton::SetSelectedButtonColour(Colour colour)
{
	m_buttonSelectedColour = colour;
}

void ToggleButton::SetSelectedTextColour(Colour colour)
{
	m_textSelectedColour = colour;
}

void ToggleButton::SetSelectedSprite(Sprite* sprite)
{
	m_pSelectedSprite = sprite;
	m_width = sprite->GetWidth();
	m_height = sprite->GetHeight();
}

void ToggleButton::SetSelectedHoverSprite(Sprite* sprite)
{
	m_pSelectedHoverSprite = sprite;
}

void ToggleButton::SetSelectedClickedSprite(Sprite* sprite)
{
	m_pSelectedClickedSprite = sprite;
}


void ToggleButton::UpdateButtonSprite()
{
	if (m_pButtonSprite != nullptr)
	{
		int mouseX = 0;
		int mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);
		
		if (m_selected == true)
		{
			
			//if hovered
			if (CheckHovered(mouseX, mouseY))
			{
				m_pCurrentSprite = m_pSelectedHoverSprite;
			}
			else
				m_pCurrentSprite = m_pSelectedSprite;
		}
		else
		{
			//if hovered
			if (CheckHovered(mouseX, mouseY))
			{
				m_pCurrentSprite = m_pButtonHoverSprite;
			}
			else
				m_pCurrentSprite = m_pButtonSprite;
		}
	}
}

