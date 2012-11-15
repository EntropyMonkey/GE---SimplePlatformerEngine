#include "Player.h"

using namespace SPE;

Player::Player(Game* _game, Messenger *_messenger) : 
	IMessageReceiver(_messenger),
	game(_game),
	spriteNum(7)
{
	sprites = IMG_Load("Images/sprites/bomb.png");
	if (!sprites)
		printf("didnt load image");

	spriteRects = new SDL_Rect[spriteNum];
	SpriteHelper::GetRects(spriteRects, spriteNum, 64, 3);
}

Player::~Player()
{
	SDL_FreeSurface(sprites);
}

void Player::Update(float deltaTime)
{

}

void Player::Render()
{
	SDL_BlitSurface(sprites, &spriteRects[6], game->screen, NULL);
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
