#include "GameObject.h"

void GameObject_SetSize(GameObject *object, float width, float height) {
    object->width = width;
    object->height = height;
}

inline float GameObject_GetWidth(GameObject *object) {
    return object->width;
}

inline float GameObject_GetHeight(GameObject *object) {
    return object->height;
}
