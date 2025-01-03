#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>
#include <limits.h>

#ifdef __linux__
#include <unistd.h>
#endif

#include "Config.h"

#include <TextureManager.h>
#include <SoundManager.h>
#include <GameObjects.h>

#define RAND_RANGE(min, max)	((rand() % (max - min + 1)) + min)

#endif
