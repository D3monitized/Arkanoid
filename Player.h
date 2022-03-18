#pragma once
#include "Engine.h"
#include "Ball.h"


class Player {
public:
	SDL_Texture* texture; 
	BoxCollider collider;
	Ball* ball; 
	int* ballCount; 

	Vector2 pos;
	Vector2 size; 
	Vector2 dir; 

	float speed = 400; 

	void GetBallReference(Ball* ball, int *ballCount); 

	void Draw();
	void Update();

	Player(); 
	~Player();
};