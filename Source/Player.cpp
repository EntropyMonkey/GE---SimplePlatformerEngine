#include "Player.h"

using namespace SPE;

Player::Player(Game* _game) : 
	game(_game)
{
	image = SDL_LoadBMP("Images/hello.bmp");
	if (!image)
		printf("didnt load image");
}

Player::~Player()
{
	SDL_FreeSurface(image);
}

void Player::Update(float deltaTime)
{

}

void Player::Render()
{
	SDL_BlitSurface(image, NULL, game->screen, NULL);
}
