#pragma once
#include "button.h"

class ToggleButton : public Button
{
public:
	ToggleButton();
	~ToggleButton();

	void Initialise(std::string buttonText, Vector2 center);
	void Initialise(std::string buttonText, Vector2 center, int buttonWidth, int buttonHeight);
	void Initialise(Vector2 center, int buttonWidth, int buttonHeight, std::string buttonText, Colour textColour, Colour buttonColour);
	void Draw(BackBuffer& backBuffer) override;
	bool CheckClicked(int x, int y);
	bool CheckHovered(int x, int y);
	bool IsSelected();
	void UpdateButtonSprite();
	void SetSelected(bool selected);
	void SetSelectedTextColour(Colour colour);
	void SetSelectedButtonColour(Colour colour);
	void SetSelectedSprite(Sprite* sprite);
	void SetSelectedHoverSprite(Sprite* sprite);
	void SetSelectedClickedSprite(Sprite* sprite);

protected:
	Colour m_textSelectedColour;
	Colour m_buttonSelectedColour;
	Sprite* m_pSelectedSprite;
	Sprite* m_pSelectedHoverSprite;
	Sprite* m_pSelectedClickedSprite;
	bool m_selected;
private:
	
};

