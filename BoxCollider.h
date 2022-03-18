#pragma once
#include <iostream>

#include "Engine.h"
#include "Vector2.h"

class BoxCollider {
public:
	SDL_Rect collider;

	Vector2 lastImpactDirection;

	bool draw = false; //if draw is active, will draw a green box around the object, representing the collider
	bool isStatic = true; //if isStatic, will not update position
	bool hasCollided = false;

	bool CheckCollision(BoxCollider& other);
	void Update(Vector2 pos);
	void Draw();	

	BoxCollider();
	BoxCollider(Vector2 pos, Vector2 size, bool isStatic);
	~BoxCollider();
};