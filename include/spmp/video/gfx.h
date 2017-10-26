#pragma once

#define SPMP_GFXWIDTH  (320)
#define SPMP_GFXHEIGHT (240)

#define SPMP_ROPPEN (0xF0)
#define SPMP_ROPSRC (0xCC)
#define SPMP_ROPDST (0xAA)
#define SPMP_ROPWHI (0xFF)
#define SPMP_ROPBLK (0x00)

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} PACKED SPMP_GFXRect;

typedef struct {
    u16 x;
    u16 y;
} PACKED SPMP_GFXCoords;

#define SPMP_MAKERECT(x, y, w, h) ((SPMP_GFXRect){(x), (y), (w), (h)})
#define SPMP_MAKECOORD(x, y)      ((SPMP_GFXCoords){(x), (y)})

void SPMP_GFXFlush(void);
void SPMP_GFXPaint(void);
void SPMP_GFXInit(void);
void SPMP_GFXSetROPMode(u8 rop);
u8   SPMP_GFXGetROPMode(void);
void SPMP_GFXSetFGColor(const u8 *rgb);
void SPMP_GFXGetFGColor(u8 *rgb);
void SPMP_GFXFillRect(const SPMP_GFXRect *rect);
void SPMP_GFXSetDisplayScreen(void);
void SPMP_GFXSetCameraMode(int mode);
void SPMP_GFXClear(int width, int height);
void SPMP_GFXDefaultInit(void);
