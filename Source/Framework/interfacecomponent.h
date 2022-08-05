#pragma once
#include "colour.h"
#include "interfacecomponent.h"
#include "vector2.h"

class BackBuffer;

class InterfaceComponent
{
public:
	virtual ~InterfaceComponent();
	virtual void Initialise();
	virtual void SetEnabled(bool enabled);
	virtual void ToggleEnabled();
	virtual void SetVisibility(bool visible);
	virtual void ToggleVisibility();
	virtual bool CheckClicked(int x, int y);
	Colour GetPrimaryColour();
	void SetPrimaryColour(Colour colour);
	Colour GetPrimaryColourDisabled();
	void SetPrimaryColourDisabled(Colour colour);
	Colour GetSecondaryColour();
	void SetSecondaryColour(Colour colour);
	Colour GetSecondaryColourDisabled();
	void SetSecondaryColourDisabled(Colour colour);
	virtual void Draw(BackBuffer& backBuffer);
	Vector2 GetPosition();
	
private:
	
protected:
	Vector2 m_position;
	Colour m_primaryColour;
	Colour m_secondaryColour;
	Colour m_primaryColourDisabled;
	Colour m_secondaryColourDisabled;

	
	bool m_visible;
	bool m_enabled;
};
