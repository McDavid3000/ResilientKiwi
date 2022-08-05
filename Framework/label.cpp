#include "label.h"

#include "backbuffer.h"

Label::Label()
{
	//Set default values
	m_fontSize = 24;
	m_primaryColour = Colour(255, 255, 255);
	m_secondaryColour = Colour(0, 0, 0, 0);
	
	m_visible = true;
	m_enabled = true;
	m_textCentered = false;
}

Label::~Label()
{
	
}

void Label::Initialise()
{
	
}

void Label::Initialise(std::string labelText, Vector2 position)
{
	Initialise(labelText, position, Colour(255, 255, 255, 255));
}

void Label::Initialise(std::string labelText, Vector2 position, Colour textColour)
{
	m_position = position;
	m_pLabelText = labelText;
	m_pLabelFont = TTF_OpenFont("assets//arial.ttf", m_fontSize);
	m_primaryColour = textColour;
}

void Label::Draw(BackBuffer& backBuffer)
{
	if (m_visible)
	{
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

		if (m_textCentered)
		{
			m_center.x = m_position.x - (textWidth /2);
			m_center.y = m_position.y - (textHeight /2);
			backBuffer.DrawRectangle(m_center.GetXi(), m_center.GetYi(), m_center.GetXi() + textWidth, m_center.GetYi() + textHeight);
			backBuffer.DrawText(m_center.GetXi(), m_center.GetYi(), m_pLabelFont, m_pLabelText.c_str());
		}
		else
		{
			backBuffer.DrawRectangle(m_position.GetXi(), m_position.GetYi(), m_position.GetXi() + textWidth, m_position.GetYi() + textHeight);
			backBuffer.DrawText(m_position.GetXi(), m_position.GetYi(), m_pLabelFont, m_pLabelText.c_str());
		}
	}
}

void Label::DrawText(BackBuffer& backBuffer)
{
	backBuffer.DrawText(m_position.GetXi(), m_position.GetYi(), m_pLabelFont, m_pLabelText.c_str());
}

Vector2 Label::GetCenter()
{
	//TODO
	return Vector2(0,0);
}

void Label::SetFont(char* fontFilePath, int fontSize)
{
	m_fontSize = fontSize;
	m_pLabelFont = TTF_OpenFont(fontFilePath, m_fontSize);
}


void Label::SetLabelText(std::string text)
{
	m_pLabelText = text;
}

std::string Label::GetLabelText()
{
	return m_pLabelText;
}


void Label::AlignTextCenter(bool centerText)
{
	m_textCentered = centerText;
}
