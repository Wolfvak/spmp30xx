.arm

#include <spmp/asminc.h>

BEGIN_ASM_FUNC SPMP_SpriteLoad
@ int SPMP_SpriteLoad(const Sprite *tex)
    push {lr}
    sub sp, sp, #4
    mov r1, sp
    OSCALL 0x14
    cmp r0, #0
    pop {r0,lr}
    andeq r0, r0, #0xFF
    movne r0, #0xFFFFFFFF
    bx lr


BEGIN_ASM_FUNC SPMP_SpriteFree
@ void SPMP_SpriteFree(int hndl)
    OSCALL 0x18, 0


BEGIN_ASM_FUNC SPMP_SpriteQueryInfo
@ int SPMP_SpriteQueryInfo(int hndl, u8 info)
@ info = 1 => width
@ info = 2 => height
@ info = 3 => type?
@ info = 4 => palette count?
    push {lr}
    sub sp, sp, #4
    mov r2, sp
    OSCALL 0xA4
    cmp r0, #0
    pop {r0,lr}
    movne r0, #0xFFFFFFFF
    lsleq r0, #16
    lsreq r0, #16
    bx lr


BEGIN_ASM_FUNC SPMP_SpriteBlit
@ void SPMP_SpriteBlit(int handle, SPMP_GFXRect *src, SPMP_GFXCoords *dst)
    ldr r3, =colorkey
    OSCALL 0xB8, 0

.section .rodata.colorkey
colorkey:
    .byte 0xF8, 0x00, 0xF8, \
          0xF8, 0x00, 0xF8, \
          0xF8, 0x00, 0xF8, \
          0xF8, 0x00, 0xF8, \
          0x0A, 0x00, 0x00, \
          0x00, 0x00, 0x00, \
          0x40, 0x01, 0xF0, \
          0x00, 0x00, 0x00
