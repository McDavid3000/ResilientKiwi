#ifndef __VECTOR2_H_
#define __VECTOR2_H_
#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	void Set(float x, float y);
	/*Get X position as int, makes code look less ugly with static casts*/
	int GetXi();
	/*Get Y position as int, makes code look less ugly with static casts*/
	int GetYi();
	float LengthSquared() const;
	float Length() const;

	void Normalise();

	friend Vector2 operator+(const Vector2& vecA, const Vector2 vecB)
	{
		return (Vector2(vecA.x + vecB.x, vecA.y + vecB.y));
	}

	friend Vector2 operator-(const Vector2& vecA, const Vector2 vecB)
	{
		return (Vector2(vecA.x - vecB.x, vecA.y - vecB.y));
	}

	friend Vector2 operator*(float scalar, const Vector2 vec)
	{
		return (Vector2(vec.x * scalar, vec.y * scalar));
	}

	friend Vector2 operator*(const Vector2 vec, float scalar)
	{
		return (Vector2(vec.x * scalar, vec.y * scalar));
	}

	Vector2& operator*=(float scalar)
	{
		x = x * scalar;
		y = y * scalar;

		return (*this);
	}

	Vector2& operator+=(const Vector2& vecRight)
	{
		x = x + vecRight.x;
		y = y + vecRight.y;

		return (*this);
	}

	Vector2& operator-=(const Vector2& vecRight)
	{
		x = x - vecRight.x;
		y = y - vecRight.y;

		return (*this);
	}

	static float DotProduct(const Vector2& vecA, const Vector2& vecB);
	static Vector2 Lerp(const Vector2& vecA, const Vector2& vecB, float time);
	static Vector2 Reflect(const Vector2& vec, const Vector2& normal);
	static Vector2 Difference(Vector2& vecA, Vector2& vecB);

	//Unit Tests
	static bool RunUnitTest();


protected:
private:

public:
	float x;
	float y;

protected:
private:
	
};
#endif

