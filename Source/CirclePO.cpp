#include "CirclePO.h"

using namespace SPE;
using namespace glm;


bool CirclePO::TestCollision(PhysicsObject* other)
{
	vec2 collisionNormal = vec2(0,0);
	vec2 distanceVector = other->position - position;
	float distance = sqrt(distanceVector.x * distanceVector.x + 
		distanceVector.y * distanceVector.y);

	if (other->radius + this->radius - distance >= 0)
	{
		if (other->GetShape() == CIRCLE)
		{
			collisionNormal = -normalize(distanceVector);
		}
		else if (other->GetShape() == RECTANGLE)
		{
			RectanglePO &o = static_cast<RectanglePO&>(*other);

			// left side
			if (position.x + radius >= o.position.x - o.GetSize().x * 0.5f &&
				position.x < o.position.x &&
				position.y < o.position.y + o.GetSize().y * 0.5f &&
				position.y > o.position.y - o.GetSize().y * 0.5f)
			{
				collisionNormal = vec2(-1, 0);
			}
			// right side
			else if (position.x - radius <= o.position.x + o.GetSize().x * 0.5f &&
				position.x > o.position.x &&
				position.y < o.position.y + o.GetSize().y * 0.5f &&
				position.y > o.position.y - o.GetSize().y * 0.5f)
			{
				collisionNormal = vec2(1, 0);
			}
			// upper edge
			else if (position.y - radius <= o.position.y + o.GetSize().y * 0.5f &&
				position.y > o.position.y &&
				position.x > o.position.x - o.GetSize().x * 0.5f &&
				position.x < o.position.x + o.GetSize().x * 0.5f)
			{
				collisionNormal = vec2(0, 1);
			}
			// lower edge
			else if (position.y + radius >= o.position.y - o.GetSize().y * 0.5f &&
				position.y < o.position.y &&
				position.x > o.position.x - o.GetSize().x * 0.5f &&
				position.x < o.position.x + o.GetSize().x * 0.5f)
			{
				collisionNormal = vec2(0, -1);
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		Collide(other, collisionNormal);

		return true;
	}
	return false;
}

PhysicsObject::Shape CirclePO::GetShape()
{
	return PhysicsObject::CIRCLE;
}
