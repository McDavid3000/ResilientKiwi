// COMP710 GP 2D Framework 2020
#ifndef __SPRITE_H__
#define __SPRITE_H__

// Forward Declarations:
class BackBuffer;
class Texture;

class Sprite
{
	//Member Methods:
public:
	Sprite();
	~Sprite();

	bool Initialise(Texture& texture);
	bool Initialise(Texture& texture, int x, int y, int width, int height);

	virtual void Process(float deltaTime);
	virtual void Draw(BackBuffer& backbuffer);

	void SetX(int x);
	void SetY(int y);

	int GetX() const;
	int GetY() const;

	void SetAngle(float angle);
	float GetAngle() const;

	void SetCenter(int x, int y);
	void SetHandleCenter();

	virtual int GetWidth() const;
	virtual int GetHeight() const;
		
	unsigned char GetAlpha();
	void SetAlpha(unsigned char alpha);
	Sprite* GetFromSheet(int x, int y, int width, int height);

	Texture* GetTexture();

	const char* GetFileName();

protected:

private:
	Sprite(const Sprite& sprite);
	Sprite& operator=(const Sprite& sprite);

	//Member Data:
public:

protected:
	Texture* m_pTexture;
	int m_x;
	int m_y;

	float m_angle;
	int m_centerX;
	int m_centerY;

	int m_width;
	int m_height;

	unsigned char m_ucAlpha;

private:
	const char* m_pFileName;

};

#endif // __SPRITE_H__
