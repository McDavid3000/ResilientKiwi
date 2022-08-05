#include "interfacecomponent.h"

InterfaceComponent::~InterfaceComponent()
{
	
}


void InterfaceComponent::Initialise()
{
	
}

void InterfaceComponent::SetEnabled(bool enabled)
{
	m_enabled = enabled;
}

void InterfaceComponent::ToggleEnabled()
{
	m_enabled = !m_enabled;
}

void InterfaceComponent::SetVisibility(bool visible)
{
	m_visible = visible;
}

void InterfaceComponent::ToggleVisibility()
{
	m_visible = !m_visible;
}

Vector2 InterfaceComponent::GetPosition()
{
	return m_position;
}


void InterfaceComponent::Draw(BackBuffer& backBuffer)
{
	
}

bool InterfaceComponent::CheckClicked(int x, int y)
{
	return false;
}

Colour InterfaceComponent::GetPrimaryColour()
{
	return m_primaryColour;
}

void InterfaceComponent::SetPrimaryColour(Colour colour)
{
	m_primaryColour = colour;
}

Colour InterfaceComponent::GetPrimaryColourDisabled()
{
	return m_primaryColourDisabled;
}

void InterfaceComponent::SetPrimaryColourDisabled(Colour colour)
{
	m_primaryColourDisabled = colour;
}

Colour InterfaceComponent::GetSecondaryColour()
{
	return m_secondaryColour;
}

void InterfaceComponent::SetSecondaryColour(Colour colour)
{
	m_secondaryColour = colour;
}

Colour InterfaceComponent::GetSecondaryColourDisabled()
{
	return m_secondaryColourDisabled;
}

void InterfaceComponent::SetSecondaryColourDisabled(Colour colour)
{
	m_secondaryColourDisabled = colour;
}



