#include "Engine.h"

#include "../Global.h"
#include "../Game.h"

#include <time.h>

#ifdef __linux__
#include <unistd.h>
#else
#include <io.h>
#endif

struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	bool quit;
	uint64_t last_time;
} Engine;

void Engine_Halt(const char *message) {
	fputs(message, stderr);
	exit(0);
}

bool Engine_Init() {
	Engine.quit = false;

	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		return false;
	}

#ifdef DEBUG
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		fprintf(stderr, "LOG: current working directory \"%s\"\n", cwd);
	}
#endif

	Engine.window = SDL_CreateWindow(
		GAME_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (!Engine.window) {
		return false;
	}

	Engine.renderer = SDL_CreateRenderer(Engine.window, -1, 0);

	if (!Engine.renderer) {
		SDL_DestroyWindow(Engine.window);
		return false;
	}

	SDL_SetRenderDrawBlendMode(Engine.renderer, SDL_BLENDMODE_BLEND);

	if (AssetsPath_Init() != 0) {
		return false;
	}

	SoundManager_Init();
	TextureManager_Init(Engine.renderer);

	Game_Preload();

	return true;
}

void Engine_Close() {
	Game_Release();

	AssetsPath_Clean();
	TextureManager_Clean();
	SoundManager_Clean();

	SDL_DestroyRenderer(Engine.renderer);
	SDL_DestroyWindow(Engine.window);

	SDL_Quit();
}

void Engine_MainLoop() {
	Engine.last_time = SDL_GetTicks();

	Game_Create();

	atexit(Engine_Close);

	while (!Engine.quit) {
		uint64_t current_time = SDL_GetTicks64();
		float delta_time = (current_time - Engine.last_time) / 1000.0f;
		Engine.last_time = current_time;

		while (SDL_PollEvent(&Engine.event)) {
			if (Engine.event.type == SDL_QUIT ||
				(Engine.event.type == SDL_KEYUP &&
				 Engine.event.key.keysym.sym == SDLK_ESCAPE))
			{
				Engine.quit = true;
			} else {
				Game_Input(&Engine.event);
			}
		}

		SDL_RenderClear(Engine.renderer);
		Game_Update(Engine.renderer, delta_time);
		SDL_RenderPresent(Engine.renderer);
	}
}

// Private
int Engine_Start() {
	if (Engine_Init() == false) {
		Engine_Halt("We can't start the game D:");
	}
	Engine_MainLoop();
	return 0;
}
