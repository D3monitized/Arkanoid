#include "Block.h"


void Block::Update()
{
	if (!isAlive)
		return; 

	for (size_t i = 0; i < *ballCount + 1; i++)
	{
		if (collider.CheckCollision(ball[i].collider) && !collider.hasCollided)
		{
			collider.hasCollided = true; //Makes sure that collision is only registered once and reset after ball-collider has exited this collider
			ball[i].OnCollisionEnter(collider.lastImpactDirection);
			TakeDamage();
		}
		else if (!collider.CheckCollision(ball[i].collider))
			collider.hasCollided = false;
	}		 
}

void Block::Draw()
{
	if (!isAlive)
		return; 

	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_Rect rect = { pos.x, pos.y, size.x, size.y };
	SDL_RenderCopy(renderer, texture, NULL, &rect);

	collider.Draw(); 
}

void Block::GetBallReference(Ball *_ball, int *_ballCount)
{
	ball = _ball; 
	ballCount = _ballCount; 
}

void Block::TakeDamage() // feedback: seems like this function does a little bit more than it looks like from its name(I'm thinking about playing sound here).
						// This is also the only reason why Block class needs to have pointer to the Engine instance. If playing of the sound was implemented elsewhere
						// you could remove Engine reference from this class compeletely as well as make sure this function does only what its named for :)
{
	health--; 
	//std::cout << health << std::endl; 
	if (health <= 0) {
		isAlive = false;
		//std::cout << "Block Destroyed" << std::endl; 
	}
	
	//Plays audio on block collision
	engine->PlayAudio("Assets/Ball/OnBallCollision.wav");
}

Block::Block()
{
	//Texture
	SDL_Surface* tempSurface = IMG_Load("Assets/Block/Block.png");
	if (tempSurface == nullptr)
		std::cout << "Failed to load block image: " << SDL_GetError() << std::endl; 

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr)
		std::cout << "Failed to create block texture from surface: " << SDL_GetError() << std::endl; 

	SDL_FreeSurface(tempSurface);

	pos = Vector2(100, 100);
	size = Vector2(50, 50);
}

Block::Block(Vector2 _pos, Vector2 _size)
{
	//Texture
	SDL_Surface* tempSurface = IMG_Load("Assets/Block/Block.png");
	if (tempSurface == nullptr)
		std::cout << "Failed to load block image: " << SDL_GetError() << std::endl;

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr)
		std::cout << "Failed to create block texture from surface: " << SDL_GetError() << std::endl;

	SDL_FreeSurface(tempSurface);

	pos = _pos;
	size = _size;
}

Block::Block(Engine *_engine, Vector2 _pos, Vector2 _size, int _health)
{
	//Texture
	SDL_Surface* tempSurface = IMG_Load("Assets/Block/Block.png");
	if (tempSurface == nullptr)
		std::cout << "Failed to load block image: " << SDL_GetError() << std::endl;

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr)
		std::cout << "Failed to create block texture from surface: " << SDL_GetError() << std::endl;

	SDL_FreeSurface(tempSurface);

	pos = _pos;
	size = _size;

	collider = BoxCollider(Vector2(pos.x, pos.y + size.y / 4), Vector2(size.x, size.y / 2), true); 	
	health = _health; 
	//std::cout << health << std::endl; 

	engine = _engine; 
}

Block::~Block()
{
	ball = nullptr; 
	texture = nullptr; 
	textTexture = nullptr; 
	ballCount = nullptr; 
	engine = nullptr; 
}