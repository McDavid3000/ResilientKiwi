#pragma once
class Colour
{
public:
	Colour();
	Colour(unsigned char red, unsigned char green, unsigned char blue);
	Colour(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	~Colour();

	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;
	unsigned char m_alpha;
	
private:
protected:
};

