#pragma once

#include "vector2.h"
#include "label.h"
#include "sprite.h"

class BackBuffer;

//TODO: Extend InterfaceComponent
class Button : public Label
{
public:
	Button();
	~Button();
	void Initialise(std::string buttonText, Vector2 center);
	void Initialise(std::string buttonText, Vector2 center, int buttonWidth, int buttonHeight);
	void Initialise(std::string buttonText, Vector2 center, int buttonWidth, int buttonHeight, Colour textColour, Colour buttonColour);
	
	void Draw(BackBuffer& backBuffer) override;
	void SetButtonSprite(Sprite* sprite);
	void SetButtonHoverSprite(Sprite* sprite);
	void SetButtonClickedSprite(Sprite* sprite);
	void UpdateButtonSprite();

	Vector2 GetButtonCenter();
	bool CheckClicked(int x, int y);


private:
	
protected:
	Vector2 m_center;
	Sprite* m_pCurrentSprite;
	Sprite* m_pButtonSprite;
	Sprite* m_pButtonHoverSprite;
	Sprite* m_pButtonClickedSprite;
	
public:
private:
protected:
};

