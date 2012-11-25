#include "Player.h"

using namespace SPE;
using namespace glm;

Player::Player(Game* _game, Messenger *_messenger) :
	IMessageReceiver(_messenger),
	game(_game),
	spriteNum(7),
	spriteSize(64),
	flyTime(2)
{
	// load textures
	SpriteHelper::LoadTexture("Images/sprites/bomb.png", sprites);

	// set texture coords
	spriteRects = new float[spriteNum * 4]();

	float pixSize = 256.0f;
	int spritesPerRow = 3;
	vec2 size = vec2((float)spriteSize / pixSize, (float)spriteSize / pixSize);

	int x = 0; int y = 0;
	for (int i = 0; i < 7; i++)
	{
		spriteRects[i * 4 + X] = x * size.x;
		spriteRects[i * 4 + Y] = y * size.y;
		spriteRects[i * 4 + W] = spriteRects[i * 4 + X] + size.x;
		spriteRects[i * 4 + H] = spriteRects[i * 4 + Y] + size.y;

		x++;
		if (x >= spritesPerRow)
		{
			x = 0;
			y++;
		}
	}

	currentSprite = 0;

	// set physics stuff
	position = vec2(0, 0);
	radius = 20.0f;
	mass = 1;

	// fly state
	startFlying = false;
	flySpeed = 100;
	flyDirection = vec2(0, 0);
	flyStartTimer = 0;
	maxVelocity = 200;

	// weight change
	getBigger = false;
	getBiggerAntiBoost = 0.2f;
	getSmaller = false;
	getSmallerBoost = 0.3f;
	weightChange = 10;
	minWeight = 0.1f;
	maxWeight = 50;
	minSize = 32;
	maxSize = 50;

	// not doing this in the GameObject and PhysicsObject constructors
	// because of circular reference trouble
	game->Add((GameObject*)this);
	game->Add((PhysicsObject*)this);
}

Player::~Player()
{
	game->Remove((GameObject*)this);
	game->Remove((PhysicsObject*)this);

	glDeleteTextures(1, &sprites);
}

void Player::Active(bool _update, bool _render)
{
	physicsActive = _update;
	update = _update;
	render = _render;
}

void Player::Update(float deltaTime)
{
	//printf("%f %f\n", position.x, position.y);
	if (startFlying)
	{
		// give the bomb a push for some time in the beginning
		flyStartTimer -= deltaTime;
		if (flyStartTimer > 0)
		{
			AddForce(flyDirection * flySpeed);
		
			float velSqrMagnitude = velocity.x * velocity.x + velocity.y * velocity.y;
			if (velSqrMagnitude > maxVelocity * maxVelocity)
			{
				velocity /= sqrt(velSqrMagnitude);
				velocity *= maxVelocity;
			}
		}
		else
		{
			startFlying = false;
		}
	}

	if (!game->aiming)
	{
		// make the bomb bigger and smaller
		if (getBigger && mass < maxWeight)
		{
			AddForce(vec2(-1, 0) * getBiggerAntiBoost);
			velocity -= velocity * getBiggerAntiBoost * deltaTime;

			mass += weightChange * deltaTime;
			printf("%f\n", radius);
			radius += weightChange * deltaTime;
		}
		else if (getSmaller && mass - minWeight > 0.2f)
		{
			AddForce(vec2(1, 0) * getSmallerBoost);
			velocity += velocity * getSmallerBoost * deltaTime;

			mass -= weightChange * deltaTime;
			printf("%f\n", radius);
			radius -= weightChange * deltaTime;
		}
	}
}

void Player::Render()
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, sprites);

	{
		ScopedMatrix m = ScopedMatrix();

		float s = radius + 0.6f * radius; // draw it bigger to make up for
		// the image's border

		glTranslatef(position.x, position.y, 0);

		int i = 3 * 4;
		
		glBegin(GL_QUADS);
			// bottom left
			glTexCoord2f (spriteRects[i + X], spriteRects[i + Y]);
			glVertex3f (-s, -s, 0.0);

			// bottom right
			glTexCoord2f (spriteRects[i + W], spriteRects[i + Y]);
			glVertex3f (s, -s, 0.0);

			// upper right
			glTexCoord2f (spriteRects[i + W], spriteRects[i + H]);
			glVertex3f (s, s, 0.0);
		
			// upper left
			glTexCoord2f (spriteRects[i + X], spriteRects[i + H]);
			glVertex3f (-s, s, 0.0);
		glEnd();
	
		// disable texturing
		/*glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINE_LOOP);
 
			glColor3f(1, 1, 0);
			for (int i=0; i < 360; i++)
			{
				float degInRad = i*DEG2RAD;
				glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
			}
 
		glEnd();

		// enable texturing again
		glEnable(GL_TEXTURE_2D);*/

			// reset color
		glColor3f(1,1,1);

	}

	glDisable(GL_BLEND);
}

void Player::Shoot(glm::vec2 direction)
{
	// normalize direction just in case
	flyDirection = normalize(direction);

	flyStartTimer = flyTime;
	startFlying = true;
}

void Player::OnCollision(PhysicsObject *o1, PhysicsObject *o2)
{
	messenger->SendMessage(CollisionMessage(o1, o2));
}

void Player::Receive(Message *message)
{
	{
		InputMessage *msg = dynamic_cast<InputMessage*>(message);
		if (msg)
			Receive(msg);
	}

	{
		CollisionMessage *msg = dynamic_cast<CollisionMessage*>(message);
		if (msg)
			Receive(msg);
	}
}

void Player::Receive(InputMessage *message)
{
	if (!game->aiming)
	{
		if (message->action == InputMessage::KEY_DOWN)
		{
			if (message->key == SDLKey::SDLK_UP)
			{
				getBigger = true;
				printf("getBigger\n");
			}
			else if (message->key == SDLKey::SDLK_DOWN)
			{
				getSmaller = true;
				printf("getSmaller\n");
			}
		}
		else if (message->action == InputMessage::KEY_UP)
		{
			if (message->key == SDLKey::SDLK_UP)
			{
				getBigger = false;
			}
			else if (message->key == SDLKey::SDLK_DOWN)
			{
				getSmaller = false;
			}
		}
	}
}

void Player::Receive(CollisionMessage *message)
{
	/*std::cout << "collision: " << message->colliderOne->id << " " << 
		message->colliderTwo->id << std::endl;*/
}