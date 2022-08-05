#include "colour.h"

Colour::Colour()
{
	m_red = 255;
	m_green = 255;
	m_blue = 255;
	m_alpha = 255;
}


Colour::Colour(unsigned char red, unsigned char green, unsigned char blue)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
	m_alpha = 255;
}

Colour::Colour(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
	m_alpha = alpha;
}

Colour::~Colour()
{
	
}
