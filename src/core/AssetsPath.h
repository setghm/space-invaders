#ifndef __ASSETS_PATH__
#define __ASSETS_PATH__

int AssetsPath_Init(void);
char* AssetsPath_Resolve(const char* file_name);
void AssetsPath_Clean(void);

#endif
