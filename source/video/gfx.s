.arm

#include <spmp/asminc.h>

BEGIN_ASM_FUNC SPMP_GFXFlush
@ void SPMP_GFXFlush(void)
    OSCALL 0x0C, 0


BEGIN_ASM_FUNC SPMP_GFXPaint
@ void SPMP_GFXPaint(void)
    OSCALL 0x10, 0


BEGIN_ASM_FUNC SPMP_GFXInit
@ void SPMP_GFXInit(void)
    push {r4,lr}
    sub sp, sp, #8
    mov r0, sp
    ldr r1, =(320*240*2)
    OSCALL 0x38
    add sp, sp, #8
    pop {r4,lr}
    bx lr


BEGIN_ASM_FUNC SPMP_GFXSetROPMode
@ void SPMP_GFXSetROPMode(u8 rop)
    OSCALL 0x3C, 0


BEGIN_ASM_FUNC SPMP_GFXGetROPMode
@ u8 SPMP_GFXGetROPMode(void)
    push {r0,lr}
    mov r0, sp
    OSCALL 0x40
    pop {r0,lr}
    and r0, r0, #0xFF
    bx lr


BEGIN_ASM_FUNC SPMP_GFXSetFGColor
@ void SPMP_GFXSetFGColor(u8 *rgb)
    OSCALL 0x44, 0


BEGIN_ASM_FUNC SPMP_GFXGetFGColor
@ void SPMP_GFXGetFGColor(u8 *rgb)
    OSCALL 0x48, 0


BEGIN_ASM_FUNC SPMP_GFXSetDisplayScreen
@ void SPMP_GFXSetDisplayScreen(void)
@ don't even ask...
    push {r4,lr}
    sub sp, sp, #8
    mov r1, #0
    mov r2, #320
    mov r3, #240
    str r1, [sp, #0]
    strh r2, [sp, #4]
    strh r3, [sp, #6]
    mov r0, sp
    OSCALL 0x54
    add sp, sp, #8
    pop {r4,lr}
    bx lr


BEGIN_ASM_FUNC SPMP_GFXSetCameraMode
@ void SPMP_GFXSetCameraMode(int mode)
    OSCALL 0x8C, 0


BEGIN_ASM_FUNC SPMP_GFXClear
@ void SPMP_GFXClear(int width, int height)
    OSCALL 0x90, 0


BEGIN_ASM_FUNC SPMP_GFXFillRect
@ void SPMP_GFXFillRect(const SPMP_GFXRect *rect)
    OSCALL 0xC4, 0


BEGIN_ASM_FUNC SPMP_GFXDefaultInit
@ void SPMP_GFXDefaultInit(void)
    push {r4,lr}
    bl SPMP_GFXInit
    mov r0, #320
    mov r1, #240
    bl SPMP_GFXClear
    bl SPMP_GFXSetDisplayScreen
    mov r0, #0x20
    bl SPMP_GFXSetCameraMode
    pop {r4,lr}
    bx lr
