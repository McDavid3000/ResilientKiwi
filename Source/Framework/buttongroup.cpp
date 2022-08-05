#include "buttongroup.h"

#include "button.h"
#include "togglebutton.h"

ButtonGroup::ButtonGroup()
: m_currentlySelected(nullptr)
{
}

ButtonGroup::~ButtonGroup()
{
	for (auto button : m_buttons)
	{
		delete button;
		button = nullptr;
	}
}

void ButtonGroup::Draw(BackBuffer& backBuffer)
{
	for (auto button : m_buttons)
	{
		button->Draw(backBuffer);
	}
}

bool ButtonGroup::CheckClicked(int x, int y)
{
	for (auto button : m_buttons)
	{
		if(button->CheckClicked(x, y))
		{
			if (button == m_currentlySelected)
			{
				button->SetSelected(true);
			}
			else if (m_currentlySelected != nullptr)
			{
				m_currentlySelected->SetSelected(false);
			}
			m_currentlySelected = button;
			return true;
		}
	}
	return false;
}

ToggleButton* ButtonGroup::ClickedButton()
{
	return m_currentlySelected != nullptr ? m_currentlySelected : nullptr;
}


void ButtonGroup::AddButton(ToggleButton* button)
{
	m_buttons.push_back(button);
}

ToggleButton* ButtonGroup::GetSelected()
{
	return m_currentlySelected;
}

void ButtonGroup::SetSelected(ToggleButton* button)
{
	if (m_currentlySelected != nullptr)
	{
		m_currentlySelected->SetSelected(false);
	}
	button->SetSelected(true);
	m_currentlySelected = button;
}
