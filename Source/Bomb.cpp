#include "Bomb.h"

using namespace SPE;
using namespace glm;

Bomb::Bomb(Game *game, Messenger *messenger, char* texturePath) :
	IMessageReceiver(messenger),
	spriteNum(7),
	spriteSize(64)
{
	this->game = game;
	game->Add((GameObject*)this);
	game->Add((PhysicsObject*)this);

	// load textures
	SpriteHelper::LoadTexture(texturePath, sprites);

	// set texture coords
	spriteRects = new float[spriteNum * 4]();

	float pixSize = 256.0f;
	int spritesPerRow = 3;
	vec2 size = vec2((float)spriteSize / pixSize, (float)spriteSize / pixSize);

	int x = 0; int y = 0;
	for (int i = 0; i < spriteNum; i++)
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

	// physics stuff
	mass = 10;
	radius = 20;
	useGravity = true;

	liveTime = 20;

	enteredScreen = false;
}

Bomb::~Bomb()
{
	glDeleteTextures(1, &sprites);
	game->Remove((GameObject*)this);
	game->Remove((PhysicsObject*)this);
}

void Bomb::Update(float deltaTime)
{
	liveTime -= deltaTime;
	if (liveTime < 0.0f)
		this->~Bomb();
}

void Bomb::Render()
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, sprites);

	{
		ScopedMatrix m = ScopedMatrix();

		float s = radius + 0.6f * radius; // draw it bigger to make up for
		// the image's border

		glTranslatef(position.x, position.y, 0);

		int i = currentSprite * 4;
		
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

void Bomb::Receive(Message *message)
{
	CollisionMessage *msg = dynamic_cast<CollisionMessage*>(message);
	if (msg)
		Receive(msg);
}

void Bomb::Receive(CollisionMessage *message)
{
}

void Bomb::OnCollision(PhysicsObject *o1, PhysicsObject *o2)
{
	messenger->SendMessage(CollisionMessage(o1, o2));
}

void Bomb::ChangeSpriteFrame()
{
	currentSprite = rand() % spriteNum;
}