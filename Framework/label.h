#pragma once
#include "interfacecomponent.h"
#include <SDL_ttf.h>
#include <string>


#include "colour.h"

class Label : public InterfaceComponent
{
public:
	Label();
	~Label();

	void Initialise();
	void Initialise(std::string labelText, Vector2 position);
	void Initialise(std::string labelText, Vector2 position, Colour textColour);
	void Draw(BackBuffer& backBuffer);
	void DrawText(BackBuffer& backBuffer);
	void SetFont(char* fontFilePath, int fontSize);
	void SetLabelText(std::string text);
	std::string GetLabelText();
	Vector2 GetCenter();
	void AlignTextCenter(bool centerText);
	
protected:
private:
	

public:
protected:
	Vector2 m_center;
	int m_width;
	int m_height;
	
	//Font
	int m_fontSize;
	TTF_Font* m_pLabelFont;
	std::string m_pLabelText;

	
private:
	bool m_textCentered;
};

