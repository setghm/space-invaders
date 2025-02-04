#include "AssetsPath.h"
#include "Config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __linux__

#include <unistd.h>

#else

#include <io.h>
#define access _access
#define F_OK 0

#endif

static char* assets_path = NULL;

int AssetsPath_Init(void) {
#ifdef BUILD_APPIMAGE
    const char* appdir = getenv("APPDIR");

    if (appdir == NULL) {
        puts("[ERROR] APPDIR value not set");
        return -1;
    }

    int len = strlen(appdir) + strlen("/"ASSETS_DIRECTORY) + 1;

    assets_path = (char*) malloc(len);
    memset(assets_path, 0, len);
    sprintf(assets_path, "%s/%s", appdir, ASSETS_DIRECTORY);
#else
    assets_path = ASSETS_DIRECTORY;
#endif

#ifdef DEBUG
    printf("[DEBUG] Using assets path directory: %s\n", assets_path);
#endif

    return 0; // No errors
}

char* AssetsPath_Resolve(const char* file_name) {
    int len = strlen(assets_path) + strlen(file_name) + 2;
    char* asset_path = (char*) malloc(len);
    memset(asset_path, 0, len);

    sprintf(asset_path, "%s/%s", assets_path, file_name);

#ifdef DEBUG
    fprintf(stderr, "[DEBUG] Checking if file \"%s\" exists... ", asset_path);
#endif

    // Check if the file exists.
    if (access(asset_path, F_OK) != 0) {
#ifdef DEBUG
        fputs("NOT FOUND\n", stderr);
#endif
        free(asset_path);
        return NULL;
    }

#ifdef DEBUG
    fputs("DONE\n", stderr);
#endif

    return asset_path;
}

void AssetsPath_Clean(void) {
#ifdef BUILD_APPIMAGE
    free(assets_path);
#endif
}
