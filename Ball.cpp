#include "Ball.h"
#include "Player.h"

void Ball::Update(Vector2 _pos)
{
	if (dead)
		return; 

	if (!isAlive) {
		if (keys[SDL_SCANCODE_SPACE])
		{			
			//Get random horizontal direction (left/right)
			int r = RandNum(1);		
			int dirX = 0; 
			if (r == 0)
				dirX = 1;
			else
				dirX = -1; 

			dir = Vector2(dirX, -1); //Set dir to left/right and up

			//Set ball alive to start moving
			isAlive = true; 
		}	
		pos = _pos;
		collider.Update(Vector2(pos.x + 25 / 4.5f, pos.y + 25 / 4.5f));
		return; 
	}	

	if (pos.x + size.x > WIDTH && dir.x > 0) //Keeps the ball from going off screen to the right
		dir.x = -1; 
	if (pos.x < 0 && dir.x < 0) //Keeps the ball from going off screen to the left
		dir.x = 1; 
	if (pos.y < 0 && dir.y < 0) //Keeps the ball from going off screen at the top
		dir.y = 1; 

	dir.Normalize(); 
	//std::cout << dir << std::endl;
	pos += dir * speed * deltaTime; 

	collider.Update(Vector2(pos.x + 25 / 4.5f, pos.y + 25 / 4.5f));	
}

void Ball::Draw()
{
	SDL_Rect rect = { pos.x, pos.y, size.x, size.y };
	SDL_RenderCopy(renderer, texture, NULL, &rect);

	collider.Draw(); 
}

//Function that's called when ball collides with another object, comes with an impact direction that shows if impact was from below/above etc
void Ball::OnCollisionEnter(Vector2 impactDir, Vector2 _dir)
{	
	if (impactDir.y > 0 && dir.y < 0)
		dir = Vector2(dir.x, 1);
	else if (impactDir.y < 0 && dir.y > 0)
		dir = Vector2(dir.x, -1);
	else if (impactDir.x > 0 && dir.x < 0)
		dir = Vector2(1, dir.y);
	else if (impactDir.x < 0 && dir.x > 0)
		dir = Vector2(-1, dir.y);		

	//if ball is colliding with player and player is not standing still, will use the velocity direction of the player to change ball direction
	if (_dir == Vector2::Zero())
		return; 

	if (_dir.x > 0) //if paddle is going to the right, make ball bounce to the right
		dir.x = 1;
	else //else, make ball bounce to the left
		dir.x = -1; 
}

//Function for randomizing numbers
int Ball::RandNum(int range)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, range); // define the range

	return distr(gen);
}

Ball::Ball()
{
	//Texture
	SDL_Surface* tempSurface = IMG_Load("Assets/Ball/Ball.png");
	if (tempSurface == nullptr)
		std::cout << "Failed to load ball image: " << SDL_GetError() << std::endl; 

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface); 
	if (texture == nullptr)
		std::cout << "Failed to create ball texture from surface: " << SDL_GetError() << std::endl; 

	SDL_FreeSurface(tempSurface);

	//Size and positioning
	size = Vector2(35, 35);
	pos = Vector2(WIDTH / 2 - size.x / 2, HEIGHT * .75f);

	collider = BoxCollider(Vector2(pos.x + 25 / 4.5f, pos.y + 25 / 4.5f), Vector2(25, 25), false); 

	int r = RandNum(1); 
	dir.x = r == 1 ? 1 : -1; 
	dir.y = -1; 

	isAlive = true; 	
}

Ball::Ball(Vector2 _pos, Vector2 _size)
{
	//Texture
	SDL_Surface* tempSurface = IMG_Load("Assets/Ball/Ball.png");
	if (tempSurface == nullptr)
		std::cout << "Failed to load ball image: " << SDL_GetError() << std::endl;

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr)
		std::cout << "Failed to create ball texture from surface: " << SDL_GetError() << std::endl;

	SDL_FreeSurface(tempSurface);

	//Size and positioning
	size = _size; 
	pos = _pos;
	//hard coded collider size/pos. (Collider size is a bit janky with scaled png's)
	collider = BoxCollider(Vector2(pos.x + 25 / 4.5f, pos.y + 25 / 4.5f), Vector2(25, 25), false);
	//collider.draw = true; 			
}

Ball::~Ball()
{	
	texture = nullptr; 
}