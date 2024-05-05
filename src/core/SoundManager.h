#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

void SoundManager_Init();
void SoundManager_Load(const char *name, const char *filename);
void SoundManager_Play(const char *name, int volume, bool loop);
void SoundManager_StopAll();
void SoundManager_Clean();

#endif
