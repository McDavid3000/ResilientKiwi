#pragma once
#include <list>
#include "interfacecomponent.h"

class ToggleButton;

class ButtonGroup : public InterfaceComponent
{
public:
	ButtonGroup();
	~ButtonGroup();
	void Draw(BackBuffer& backBuffer) override;
	bool CheckClicked(int x, int y) override;
	ToggleButton* ClickedButton();

	void AddButton(ToggleButton* button);
	ToggleButton* GetSelected();
	void SetSelected(ToggleButton* button);

protected:
	std::list<ToggleButton*> m_buttons;
	
	ToggleButton* m_currentlySelected;
private:

};

