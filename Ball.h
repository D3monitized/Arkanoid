#pragma once
#include <random>

#include "Engine.h"

class Ball {
public:
	SDL_Texture* texture; 
	BoxCollider collider;			

	Vector2 pos; 
	Vector2 size; 
	Vector2 dir; 	

	float speed = 200; 	
	bool isAlive = false; //Bool used to see if ball has started bouncing around yet.
	bool dead = false;  //Bool for checking if it's dead
	
	//dir has default value as the blocks won't be returning a velocity direction
	void OnCollisionEnter(Vector2 impactDir, Vector2 dir = Vector2()); 
	int RandNum(int range); 

	void Update(Vector2 _pos);
	void Draw();

	// feedback: format: constructors and destructors are usually placed first in the class declaration
	Ball(); 
	Ball(Vector2 pos, Vector2 size);
	~Ball(); 
};