#include "Player.h"

void Player::Update()
{
	dir.x = keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT] ? 1 : 0;
	dir.x = keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT] ? -1 : dir.x; 

	if (pos.x + size.x >= WIDTH && dir.x > 0 || pos.x <= 0 && dir.x < 0)
		return; 	

	pos += dir * speed * deltaTime; 
	collider.Update(Vector2(pos.x, pos.y + size.y / 4));

	for (size_t i = 0; i < *ballCount + 1; i++)
	{
		if (collider.CheckCollision(ball[i].collider) && !collider.hasCollided)
		{
			ball[i].OnCollisionEnter(collider.lastImpactDirection, dir);
			collider.hasCollided = true;
		}
		else if (!collider.CheckCollision(ball[i].collider))
			collider.hasCollided = false;
	}	
}

void Player::Draw()
{
	SDL_Rect rect = { pos.x, pos.y, size.x, size.y };
	SDL_RenderCopy(renderer, texture, NULL, &rect);

	collider.Draw(); 
}

void Player::GetBallReference(Ball* _ball, int *_ballCount)
{
	ball = _ball; 
	ballCount = _ballCount;
}

Player::Player()
{
	//Player texture
	SDL_Surface* tempSurface = IMG_Load("Assets/Player/Player.png");
	if (tempSurface == nullptr)
		std::cout << "Failed to load player texture: " << SDL_GetError() << std::endl; 
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface); 
	if(texture == nullptr)
		std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
	SDL_FreeSurface(tempSurface); //Cleanup

	//Size and start positioning
	size = Vector2(100, 50);
	pos = Vector2(WIDTH / 2 - size.x / 2, HEIGHT * .85f - size.y / 2);

	// feedback: you don't have to call a constructor of the BoxCollider explicitly here, since the instance is already created as a class member. You can just set the values of
	// the needed memebers of collider like you did with collider.hasCollided
	collider = BoxCollider(Vector2(pos.x, pos.y + size.y / 4), Vector2(size.x, size.y / 2), false);
	//collider.draw = true; 
	collider.hasCollided = true; 
}

Player::~Player()
{
	ball = nullptr; 
	texture = nullptr;
	ballCount = nullptr; 
}