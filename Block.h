#pragma once
#include <iostream>

#include "Engine.h"
#include "Vector2.h"
#include "Ball.h"



class Block {
public:	
	SDL_Texture* texture; 
	SDL_Texture* textTexture; 
	Ball* ball; 
	int* ballCount; 
	Engine* engine; 

	SDL_Color color; 
	BoxCollider collider; 
	
	Vector2 pos; 
	Vector2 size; 
	
	bool isAlive = false; 
	int health = 1; //each healthpoint represents number of hits needed to break

	void GetBallReference(Ball* ball, int *ballCount);
	void TakeDamage();

	void Update(); 
	void Draw(); 

	Block();
	Block(Engine *engine, Vector2 pos, Vector2 size, int _health);
	Block(Vector2 pos, Vector2 size);
	~Block(); 
};