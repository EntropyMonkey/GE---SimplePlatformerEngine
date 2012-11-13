#include "SDL.h"
#include "Game.h"

#ifdef _WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_image.lib")
#endif

#ifdef __cplusplus
extern "C"
#define main	SDL_main
#endif

int main (int argc, char* argv[])
{
	SPE::Game game = SPE::Game();

	return 0;
}
