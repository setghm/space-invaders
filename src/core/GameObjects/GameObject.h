#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#define GAME_OBJECT(o)	((GameObject *) o)

typedef struct _GameObject_ GameObject;

struct _GameObject_ {
    float width;
    float height;
};

void GameObject_SetSize(GameObject *object, float width, float height);
float GameObject_GetWidth(GameObject *object);
float GameObject_GetHeight(GameObject *object);

#endif
