#include "Vector2.h"
#include <cmath>
#include <iostream>

float Vector2::Dot(Vector2 &other)
{
	Vector2 normalizedVector = this->Normalized();
	float dot = (normalizedVector.x * other.x) + (normalizedVector.y * other.y);
	return dot; 
}

float Vector2::GetMagnitude() 
{
	float x2 = x * x;
	float y2 = y * y;
	float magnitude = std::sqrt(x2 + y2);

	return magnitude; 
}

void Vector2::Normalize()
{
	if (x == 0 && y == 0)
		return; 

	float magnitude = GetMagnitude();
	float newX = x / magnitude; 
	float newY = y / magnitude; 

	*this = Vector2(newX, newY);
}

Vector2 Vector2::Normalized()
{
	if (x == 0 && y == 0)
		return Vector2();

	float magnitude = GetMagnitude();
	float newX = x / magnitude;
	float newY = y / magnitude;

	return Vector2(newX, newY);
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::~Vector2()
{
	
}