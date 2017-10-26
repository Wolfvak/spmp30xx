#include <spmp/common.h>
#include <spmp/video/gfx.h>
#include <spmp/video/sprite.h>

void ARM_FUNC SPMP_DrawRect(const SPMP_GFXRect *rect, const u8 *rgb) {
    u8 rop, fgcol[3];

    rop = SPMP_GFXGetROPMode();
    SPMP_GFXGetFGColor(fgcol);

    SPMP_GFXSetROPMode(SPMP_ROPPEN);
    SPMP_GFXSetFGColor(rgb);

    SPMP_GFXFillRect(rect);

    SPMP_GFXSetFGColor(fgcol);
    SPMP_GFXSetROPMode(rop);
    return;
}

void SPMP_ClearScreen(const u8 *rgb) {
    SPMP_DrawRect(&SPMP_MAKERECT(0, 0, SPMP_GFXWIDTH, SPMP_GFXHEIGHT), rgb);
    return;
}

// TODO: Perhaps some Sprite abstraction?
