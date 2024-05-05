#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef struct _Point_ Point;
typedef struct _Vec2_ Vec2;
typedef struct _Box2_ Box2;
typedef struct _Color_ Color;

struct _Box2_ {
    float x;
    float y;
    float w;
    float h;
};

struct _Vec2_ {
    float x;
    float y;
};

struct _Point_ {
    float x;
    float y;
};

struct _Color_ {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

#endif
