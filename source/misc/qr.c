#include <spmp/common.h>
#include <spmp/misc/draw.h>
#include <spmp/libs/qrcodegen.h>

#define QR_MAX_SCALE    (8)
#define QR_INNER_BORDER (4)
#define QR_OUTER_BORDER (32)

bool SPMP_QREncodeString(const char *str, void *qr) {
    u8 qrtmpbuf[qrcodegen_BUFFER_LEN_MAX];
    return qrcodegen_encodeText(str, qrtmpbuf, qr, qrcodegen_Ecc_LOW, 
           qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
}

void ARM_FUNC SPMP_QRDraw(const void *qr, int scale) {
    int qr_dim,    // QR code height/width in px
        qr_margin, // QR code exterior border
        x_base,    // QR code X pos
        y_base;    // QR code Y pos

    if (qr == NULL) return;
    qr_dim = qrcodegen_getSize(qr);
    if (qr_dim == 0 || qr_dim > (SPMP_GFXHEIGHT - QR_OUTER_BORDER)) { // Huh?
        return;
    }

    // If scale is negative it's calculated on runtime
    if (scale < 0) {
        scale = (SPMP_GFXHEIGHT-QR_OUTER_BORDER)/qr_dim;
    }

    // Set up all coordinates
    scale = CLAMP(scale, 1, QR_MAX_SCALE);
    qr_margin = (qr_dim + QR_INNER_BORDER)*scale;
    x_base = (SPMP_GFXWIDTH - (qr_dim*scale))/2;
    y_base = (SPMP_GFXHEIGHT - (qr_dim*scale))/2;

    // Clear the screen to black
    SPMP_ClearScreen((u8[]){0x00, 0x00, 0x00});

    // Draw a white rectangle on the middle
    SPMP_DrawRect(&SPMP_MAKERECT(
        (SPMP_GFXWIDTH - qr_margin)/2,
        (SPMP_GFXHEIGHT - qr_margin)/2,
        qr_margin, qr_margin), (u8[]){0xFF, 0xFF, 0xFF});

    // Draw the QR code out of rectangles
    for (int y=0; y<qr_dim; y++) {
        int x=0, i;
        while (x < qr_dim) {
            // Draw an entire line of modules
            for (i=0; qrcodegen_getModule(qr, x + i, y); i++);
            SPMP_DrawRect(&SPMP_MAKERECT(
                x_base + (x * scale), y_base + (y * scale),
                i*scale, scale), (u8[]){0x00, 0x00, 0x00});
            x += i+1;
        }
    }
    SPMP_GFXPaint();
    return;
}
