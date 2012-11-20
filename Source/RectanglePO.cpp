#include "RectanglePO.h"

using namespace SPE;
using namespace glm;

RectanglePO::RectanglePO()
{
}

void RectanglePO::Update(float deltaTime)
{

}

bool RectanglePO::TestCollision(PhysicsObject *other)
{
	vec2 distanceVector = other->position - this->position;
	float distance = distanceVector.length();

	// broad phase
	if (other->radius + this->radius - distance >= 0)
	{
		vec2 collisionNormal = vec2(0,0);

		if (other->GetShape() == CIRCLE)
		{
			other->TestCollision(this);
		}
		//else if (other->GetShape() == RectanglePO)
		//{
		//	RectanglePO &o = static_cast<RectanglePO&>(*other);
		//	vec2 halfSize = size * 0.5f;
		//	vec2 oHalfSize = o.GetSize() * 0.5f;

		//	// upper
		//	if (position.y - halfSize.y <= o.position.y + oHalfSize.y &&
		//		position.y > o.position.y &&
		//		position.x + halfSize.x > o.position.x - oHalfSize.x &&
		//		position.x - halfSize.x < o.position.x + oHalfSize.x)
		//	{
		//		collisionNormal = vec2::up;
		//	}
		//	// lower
		//	else if (position.y + halfSize.y >= o.position.y - oHalfSize.y &&
		//		position.y < o.position.y &&
		//		position.x + halfSize.x > o.position.x - oHalfSize.x &&
		//		position.x - halfSize.x < o.position.x + oHalfSize.x)
		//	{
		//		collisionNormal = -vec2::up;
		//	}
		//	// right
		//	else if (position.x - halfSize.x <= o.position.x + oHalfSize.x &&
		//		position.x > o.position.x &&
		//		position.y - halfSize.y < o.position.y + oHalfSize.y &&
		//		position.y + halfSize.y > o.position.y - oHalfSize.y)
		//	{
		//		collisionNormal = vec2::right;
		//	}
		//	// left
		//	else if (position.x + halfSize.x >= o.position.x - oHalfSize.x &&
		//		position.x < o.position.x &&
		//		position.y - halfSize.y < o.position.y + oHalfSize.y &&
		//		position.y + halfSize.y > o.position.y - oHalfSize.y)
		//	{
		//		collisionNormal = -vec2::right;
		//	}
		//	else
		//	{
		//		return false;
		//	}
		//}
		else
		{
			return false;
		}

		Collide(other, collisionNormal);

		return true;
	}

	return false;
}

PhysicsObject::Shape RectanglePO::GetShape()
{
	return PhysicsObject::RECTANGLE;
}

void RectanglePO::SetSize(vec2 _size)
{
	size = _size;
	radius = size.length() * 0.5f;
}

vec2 RectanglePO::GetSize()
{
	return size;
}
