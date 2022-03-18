#pragma once
#include <sstream>

class Vector2 {
public:
	float x; 
	float y; 

	float GetMagnitude();
	void Normalize(); 
	Vector2 Normalized(); 
	float Dot(Vector2 &other);

	//Static Funcitons
	static Vector2 Zero() {
		return Vector2(0, 0);
	}
	
	//Operators 

	friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
	{
		stream << "(" << vector.x << ", " << vector.y << ")";
		return stream; 
	}

	Vector2& operator+=(const Vector2 &other) {
		this->x += other.x; 
		this->y += other.y; 
		return *this;
	}

	Vector2& operator-=(const Vector2& other)
	{
		this->x -= other.x; 
		this->y -= other.y; 
		return *this; 
	}

	Vector2& operator=(const Vector2& other)
	{
		this->x = other.x; 
		this->y = other.y; 

		return *this; 
	}

	bool operator!=(const Vector2& other)
	{
		if (this->x != other.x || this->y != other.y)
			return true; 

		return false; 
	}

	bool operator==(const Vector2& other)
	{
		if (this->x == other.x && this->y == other.y)
			return true; 

		return false; 
	}

	Vector2& operator-(const Vector2& other)
	{
		Vector2 temp = *this; 
		temp.x -= other.x; 
		temp.y -= other.y; 
		return temp; 
	}

	Vector2& operator*(const float& other) {
		this->x *= other; 
		this->y *= other; 
		return *this; 
	}

	//Constructors/Destructors
	Vector2(float x, float y);
	Vector2(); 
	~Vector2();
};