#include "Player.h"

using namespace SPE;
using namespace glm;

Player::Player(Game* _game, Messenger *_messenger) :
	IMessageReceiver(_messenger),
	game(_game),
	spriteNum(7),
	spriteSize(64)
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

	// set physics stuff
	position = vec2(300, 0);
	radius = 2.0;

	// not doing this in the GameObject and PhysicsObject constructors
	// because of circular reference trouble
	game->Add((GameObject*)this);
	game->Add((PhysicsObject*)this);
}

Player::~Player()
{
	glDeleteTextures(1, &sprites);
}

void Player::Update(float deltaTime)
{
}

void Player::Render()
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, sprites);

	glPushMatrix();
	glTranslatef(position.x, position.y, 0);

	int i = 6 * 4;
	glBegin(GL_QUADS);
		// bottom left
		glTexCoord2f (spriteRects[i + X], spriteRects[i + Y]);
		glVertex3f (0.0, 0.0, 0.0);

		// bottom right
		glTexCoord2f (spriteRects[i + W], spriteRects[i + Y]);
		glVertex3f (64.0, 0.0, 0.0);

		// upper right
		glTexCoord2f (spriteRects[i + W], spriteRects[i + H]);
		glVertex3f (64.0, 64.0, 0.0);
		
		// upper left
		glTexCoord2f (spriteRects[i + X], spriteRects[i + H]);
		glVertex3f (0.0, 64.0, 0.0);
	glEnd();

	glPopMatrix();
}

void Player::Receive(Message *message)
{
	InputMessage *msg = dynamic_cast<InputMessage*>(message);
	if (msg)
		Receive(msg);
}

void Player::Receive(InputMessage *message)
{
	std::cout << (char)message->key << std::endl;
}

void Player::Receive(CollisionMessage *message)
{
	std::cout << "collision: " << message->colliderOne->id << " " << 
		message->colliderTwo->id << std::endl;
}