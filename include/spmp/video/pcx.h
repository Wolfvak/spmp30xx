#pragma once

#include <spmp/common.h>
#include <spmp/video/sprite.h>

typedef struct {
    u8  manufacturer;
    u8  version;
    u8  encoding;
    u8  bitsppxl;
    u16 minx;
    u16 miny;
    u16 maxx;
    u16 maxy;
    u16 hres;
    u16 vres;
    u8  egapalette[48];
    u8  reserved;
    u8  clrplanes;
    u16 bytesperline;
    u16 palettetype;
    u8  resv_[58];
} PACKED PCXHeader;

int PCX_Sprite(Sprite *out, const u8 *pcx, size_t pcx_size);

static inline int PCX_Width(const void *hdr) {
    return (((PCXHeader*)hdr)->maxx + 1);
}

static inline int PCX_Height(const void *hdr) {
    return (((PCXHeader*)hdr)->maxy + 1);
}

static inline int PCX_BitsPerPixel(const void *hdr) {
    return (((PCXHeader*)hdr)->bitsppxl);
}

static inline size_t PCX_BitmapSize(const void *hdr) {
    return (PCX_Width(hdr) * PCX_Height(hdr) * (PCX_BitsPerPixel(hdr)/8));
}

static inline int PCX_GetMaxColors(const void *hdr) {
    return (1<<PCX_BitsPerPixel(hdr));
}

static inline u8 *PCX_GetPaletteData(const void *hdr, size_t pcx_len) {
    if (PCX_BitsPerPixel(hdr) == 4) {
        return (((PCXHeader*)hdr)->egapalette);
    } else {
        return ((u8*)hdr + pcx_len - 768);
    }
}

static inline u8 PCX_Planes(const void *hdr) {
    return (((PCXHeader*)hdr)->clrplanes);
}

static inline u8 PCX_Encoding(const void *hdr) {
    return (((PCXHeader*)hdr)->encoding);
}

static inline bool PCX_Validate(const void *hdr) {
    return (hdr != NULL &&
            ((PCXHeader*)hdr)->manufacturer == 10 &&
            PCX_Encoding(hdr) == 1 &&
            PCX_Planes(hdr) == 1 &&
            (PCX_BitsPerPixel(hdr) == 4 || PCX_BitsPerPixel(hdr) == 8));
}

void PCX_Free(Sprite *tex);
