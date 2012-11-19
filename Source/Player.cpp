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
	// first row
	spriteRects[0 * 4 + X] = 0;
	spriteRects[0 * 4 + Y] = 0;
	spriteRects[0 * 4 + W] = 0.25;
	spriteRects[0 * 4 + H] = 0.25;

	spriteRects[1 * 4 + X] = 0.25;
	spriteRects[1 * 4 + Y] = 0;
	spriteRects[1 * 4 + W] = 0.5;
	spriteRects[1 * 4 + H] = 0.25;

	spriteRects[2 * 4 + X] = 0.5;
	spriteRects[2 * 4 + Y] = 0;
	spriteRects[2 * 4 + W] = 0.75;
	spriteRects[2 * 4 + H] = 0.25;
	
	// second row
	spriteRects[3 * 4 + X] = 0;
	spriteRects[3 * 4 + Y] = 0.25;
	spriteRects[3 * 4 + W] = 0.25;
	spriteRects[3 * 4 + H] = 0.5;
	
	spriteRects[4 * 4 + X] = 0.25;
	spriteRects[4 * 4 + Y] = 0.25;
	spriteRects[4 * 4 + W] = 0.5;
	spriteRects[4 * 4 + H] = 0.5;
	
	spriteRects[5 * 4 + X] = 0.5;
	spriteRects[5 * 4 + Y] = 0.25;
	spriteRects[5 * 4 + W] = 0.75;
	spriteRects[5 * 4 + H] = 0.5;

	// third row
	spriteRects[6 * 4 + X] = 0;
	spriteRects[6 * 4 + Y] = 0.5;
	spriteRects[6 * 4 + W] = 0.25;
	spriteRects[6 * 4 + H] = 0.75;

	position = vec2(300, 0);

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
	AddForce(vec2(0, 9.81f));
}

void Player::Render()
{
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
	std::cout << message->key << std::endl;
}

void Player::Receive(CollisionMessage *message)
{
	std::cout << "collision: " << message->colliderOne->id << " " << 
		message->colliderTwo->id << std::endl;
}