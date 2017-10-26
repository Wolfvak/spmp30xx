#include <spmp/common.h>
#include <spmp/system/os.h>
#include <spmp/video/pcx.h>

void PCX_ConvertPalette(u16 *out_pal, const u8 *pcx_pal, int palcount) {
    if (pcx_pal == NULL || out_pal == NULL) {
        return;
    }

    for (int i=0; i<palcount; i++) {
        u8 r, g, b;
        r = pcx_pal[i*3 + 0] >> 3;
        g = pcx_pal[i*3 + 1] >> 2;
        b = pcx_pal[i*3 + 2] >> 3;
        out_pal[i] = ((r<<11) | (g<<5) | (b));
    }
    return;
}

void PCX_Decode(u8 *rld, const u8 *pcx, size_t rlelen, size_t rldlen) {
    size_t i=0;
    const u8 *pcx_end = &pcx[rlelen];
    while (i < rldlen && pcx < pcx_end) {

        /*
         Run Length Marker
         If both bit 7 and 6 are set, it marks an RLE pair
         RLM - 0xC0 is the amount of times
         the byte gets repeated (0x00-0x3F)
        */
        u8 rlm = *(pcx++);

        if (rlm >= 0xC0) {
            rlm -= 0xC0;
            for (int j=0; j<rlm && (i+j)<rldlen; j++) {
                rld[i+j] = *pcx;
            }
            pcx++;
            i+=rlm;
        } else {
            rld[i++] = rlm;
        }
    }
    return;
}

int PCX_Sprite(Sprite *out, const u8 *pcx, size_t pcx_size) {
    u8  *buf, *palbuf;
    const u8 *pcxpal;
    int pcxpalc, bufsize;

    if (pcx == NULL || pcx_size <= sizeof(PCXHeader) ||
        PCX_Validate(pcx) == false) {
        return -1;
    }

    pcxpalc = PCX_GetMaxColors(pcx);
    pcxpal  = PCX_GetPaletteData(pcx, pcx_size);
    bufsize = PCX_BitmapSize(pcx);

    buf = malloc(bufsize);
    palbuf = malloc(pcxpalc * sizeof(u16));

    if (buf == NULL || palbuf == NULL)
        return -3;

    PCX_Decode(buf, &pcx[sizeof(PCXHeader)], pcx_size - sizeof(PCXHeader), bufsize);
    PCX_ConvertPalette((u16*)palbuf, pcxpal, pcxpalc);

    out->data = buf;
    out->width = PCX_Width(pcx);
    out->height = PCX_Height(pcx);
    if (PCX_BitsPerPixel(pcx) == 4) {
        out->type = Sprite_4BPP;
    } else {
        out->type = Sprite_8BPP;
    }
    out->palette = (u16*)palbuf;
    out->palette_count = pcxpalc;

    return 0;
}

void PCX_Free(Sprite *tex) {
    free(tex->data);
    free(tex->palette);
}
