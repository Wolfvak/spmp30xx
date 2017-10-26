#pragma once

#include <spmp/common.h>
#include <spmp/video/gfx.h>

typedef enum {
    Sprite_8BPP = 1,
    Sprite_4BPP = 2
} SpriteType;

typedef struct {
    u8  *data;
    u16 width;
    u16 height;
    u32 type;
    u16 *palette;
    u16 palette_count;
    u32 unknown_;
} PACKED Sprite;

int  SPMP_SpriteLoad(const Sprite *spr);
int  SPMP_SpriteQueryInfo(int handle, u8 info);
void SPMP_SpriteBlit(int handle, const SPMP_GFXRect *src, const SPMP_GFXCoords *dst);
void SPMP_SpriteFree(int handle);

static inline void SPMP_SpriteBlitSimple(int handle, u16 x, u16 y) {
    SPMP_SpriteBlit(handle,
        &SPMP_MAKERECT(0, 0,
            SPMP_SpriteQueryInfo(handle, 1),
            SPMP_SpriteQueryInfo(handle, 2)),
        &SPMP_MAKECOORD(x ,y));
    return;
}
