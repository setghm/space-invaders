#include "SoundManager.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <Config.h>

struct _MemorySound_ {
	char *name;
	int channel;
	Mix_Chunk *data;
	struct _MemorySound_ *next;
};

struct _LoadedSounds_ {
	int count;
	struct _MemorySound_ *first;
	struct _MemorySound_ *last;
} LoadedSounds;

void SoundManager_Init() {
	int init_formats = MIX_INIT_OGG;

	Mix_Init(init_formats);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512);
	Mix_AllocateChannels(32);

	LoadedSounds.count = 0;
}

void SoundManager_Load(const char *name, const char *filename) {
	// Prepend the filename with the assets directory
    char *fpath = (char *) malloc(strlen(filename) + strlen(ASSETS_DIRECTORY) + 1);
    sprintf(fpath, "%s%s\0", ASSETS_DIRECTORY, filename);

#ifdef DEBUG
    fprintf(stderr, "LOG: loading %s (%s)...", fpath, name);
#endif

	// Check if the file exists
    if (access(fpath, F_OK) != 0) {
#ifdef DEBUG
        fprintf(stderr, "\tERROR the file doesn't exists\n");
#endif
        return;
    }

    // Create new sound
    struct _MemorySound_ *sound = (struct _MemorySound_ *) malloc(sizeof(struct _MemorySound_));
    memset(sound, 0, sizeof(struct _MemorySound_));

    sound->name = strdup(name);
    sound->data = Mix_LoadWAV(fpath);

    // Add to the loaded sounds
    if (LoadedSounds.first == NULL) {
        LoadedSounds.first = sound;
    }

    if (LoadedSounds.last != NULL) {
        LoadedSounds.last->next = sound;
    }

    LoadedSounds.last = sound;
    LoadedSounds.count++;

#ifdef DEBUG
    fprintf(stderr, "\tLOADED! (name: \"%s\")\n", name);
#endif
}

// Private
struct _MemorySound_ *SoundManager_Get(const char *name) {
	struct _MemorySound_ *sound = LoadedSounds.first;

	while (sound) {
		if (strcmp(sound->name, name) == 0) {
			return sound;
		}
		sound = sound->next;
	}

	return NULL;
}

void SoundManager_Play(const char *name, int volume, bool loop) {
	struct _MemorySound_ *sound = SoundManager_Get(name);

	if (sound == NULL) {
#ifdef DEBUG
		fprintf(stderr, "ERROR: The sound with name %s was not loaded\n", name);
#endif
		return;
	}

	// Play the chunk in a separate channel
	sound->channel = Mix_PlayChannelTimed(-1, sound->data, loop ? -1 : 0, -1);

	if (sound->channel < 0) {
#ifdef DEBUG
		fprintf(stderr, "ERROR: Cannot reproduce that sound with name %s: %s\n", name, Mix_GetError());
#endif
		return;
	}

	// Convert the volume 0-100 to 0-128
	int sdl_volume = (volume * 128) / 100;

	// Set the volume of the channel
	Mix_Volume(sound->channel, sdl_volume);
}

void SoundManager_StopAll() {
	int channel_count = Mix_AllocateChannels(-1);

	for (int i=0; i<channel_count; i++) {
		Mix_HaltChannel(i);
	}
}

void SoundManager_Clean() {
	struct _MemorySound_ *curr = LoadedSounds.first;
	struct _MemorySound_ *next;

	SoundManager_StopAll();

	while (curr != NULL) {
		next = curr->next;

		Mix_FreeChunk(curr->data);
		free(curr->name);
		free(curr);

		curr = next;
	}

	LoadedSounds.count = 0;
	LoadedSounds.first = NULL;
	LoadedSounds.last = NULL;

	Mix_Quit();
}
