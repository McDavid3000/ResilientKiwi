#include "vector2.h"

#include <cmath>
#include <cassert>

Vector2::Vector2()
: x(0.0f)
, y(0.0f)
{
	
}

Vector2::~Vector2()
{
	
}

Vector2::Vector2(float x, float y)
: x(x)
, y(y)
{
	
}

void Vector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

int Vector2::GetXi()
{
	return (static_cast<int>(x));
}

int Vector2::GetYi()
{
	return (static_cast<int>(y));
}

float Vector2::LengthSquared() const
{
	return ((x * x) + (y * y));
}

float Vector2::Length() const
{
	return (sqrt(LengthSquared()));
}

void Vector2::Normalise()
{
	float length = Length();
	
	x = x / length;
	y = y / length;
}

float Vector2::DotProduct(const Vector2& vecA, const Vector2& vecB)
{
	return ((vecA.x * vecB.x) + (vecA.y * vecB.y));
}

Vector2 Vector2::Lerp(const Vector2& vecA, const Vector2& vecB, float time)
{
	return (Vector2(vecA + time * (vecB - vecA)));
}

Vector2 Vector2::Reflect(const Vector2& vec, const Vector2& normal)
{
	return (vec - 2.0f * DotProduct(vec, normal) * normal);
}

Vector2 Vector2::Difference(Vector2& vecA, Vector2& vecB)
{
	return Vector2(vecA.x-vecB.x,vecA.x-vecB.y);
}


bool Vector2::RunUnitTest()
{
	Vector2 testA;

	testA.Set(3.0f, 4.0f);
	float length = testA.Length();
	
	assert(length == 5.0f);

	//TODO: Add more unit tests to ensure correct implementation.

	return true;
}




