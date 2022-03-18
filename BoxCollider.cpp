#include "BoxCollider.h"

void BoxCollider::Update(Vector2 pos)
{
	if (isStatic)
		return; 

		collider.x = pos.x;
		collider.y = pos.y;
	
}

void BoxCollider::Draw()
{
	if (!draw)
		return;
	
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &collider);
}

bool BoxCollider::CheckCollision(BoxCollider& other)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = collider.x;
	rightA = collider.x + collider.w;
	topA = collider.y;
	bottomA = collider.y + collider.h;

	leftB = other.collider.x;
	rightB = other.collider.x + other.collider.w;
	topB = other.collider.y;
	bottomB = other.collider.y + other.collider.h;

	float bottomCollision = bottomA - topB;
	float topCollision = bottomB - topA;
	float leftCollision = rightB - leftA;
	float rightCollision = rightA - leftB;

	if (bottomA <= topB)
		return false;
	if (topA >= bottomB)
		return false;
	if (rightA <= leftB)
		return false;
	if (leftA >= rightB)
		return false;

	if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision)
	{
		//Top collision
		//std::cout << "Top collision" << std::endl;
		lastImpactDirection = Vector2(0, -1);
	}
	if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision)
	{
		//Bottom collision
		//std::cout << "Bottom collision" << std::endl;
		lastImpactDirection = Vector2(0, 1);
	}
	if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision)
	{
		//Left collision
		//std::cout << "Left collision" << std::endl;
		lastImpactDirection = Vector2(-1, 0);
	}
	if (rightCollision < leftCollision && rightCollision < topCollision && rightCollision < bottomCollision)
	{
		//Right collision
		//std::cout << "Right collision" << std::endl;
		lastImpactDirection = Vector2(1, 0);
	}

	return true;
}

BoxCollider::BoxCollider()
{
	SDL_Rect tempRect = { 0, 0, 0, 0 };
	collider = tempRect;
}

BoxCollider::BoxCollider(Vector2 pos, Vector2 size, bool _isStatic)
{
	SDL_Rect tempRect = { pos.x, pos.y, size.x, size.y };
	collider = tempRect;
	isStatic = _isStatic; 
}

BoxCollider::~BoxCollider()
{

}