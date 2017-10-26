.arm

#include <spmp/asminc.h>

BEGIN_ASM_FUNC CACHE_Inv
@ void CACHE_Inv(void)
    mov r0, #0
    mcr p15, 0, r0, c7, c7, 0
    bx lr


BEGIN_ASM_FUNC CACHE_InvIC
@ void CACHE_InvIC(void)
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0
    bx lr


BEGIN_ASM_FUNC CACHE_InvICRange
@ void CACHE_InvICRange(u32 mva_start, u32 mva_end)
    bic r0, #0x1F
    .LInvICR:
        cmp r0, r1
        mcrlo p15, 0, r0, c7, c5, 1
        addlo r0, #0x20
        blo .LInvICR
    bx lr


BEGIN_ASM_FUNC CACHE_InvDC
@ void CACHE_InvDC(void)
    mov r0, #0
    mcr p15, 0, r0, c7, c6, 0
    bx lr

BEGIN_ASM_FUNC CACHE_InvDCRange
@ void CACHE_InvDCRange(u32 mva_start, u32 mva_end)
    bic r0, #0x1F
    .LInvDCR:
        cmp r0, r1
        mcrlo p15, 0, r0, c7, c6, 1
        addlo r0, #0x20
        blo .LInvDCR
    bx lr


BEGIN_ASM_FUNC CACHE_WbDC
@ void CACHE_WbDC(void)
    mrc p15, 0, r15, c7, c10, 3
    bne CACHE_WbDC
    bx lr


BEGIN_ASM_FUNC CACHE_WbDCRange
@ void CACHE_WbDCRange(u32 mva_start, u32 mva_end)
    bic r0, #0x1F
    mov r2, #0
    .LWbDCR:
        cmp r0, r1
        mcrlo p15, 0, r0, c7, c10, 1
        mcrlo p15, 0, r2, c7, c10, 4
        addlo r0, #0x20
        blo .LWbDCR
    bx lr


BEGIN_ASM_FUNC CACHE_WbInvDC
@ void CACHE_WbInvDC(void)
    mrc p15, 0, r15, c7, c14, 3
    bne CACHE_WbInvDC
    bx lr


BEGIN_ASM_FUNC CACHE_WbInvDCRange
@ void CACHE_WbInvDCRange(u32 mva_start, u32 mva_end)
    bic r0, #0x1F
    mov r2, #0
    .WbInvDCR:
        cmp r0, r1
        mcrlo p15, 0, r0, c7, c10, 1
        mcrlo p15, 0, r2, c7, c10, 4
        mcrlo p15, 0, r0, c7, c14, 1
        addlo r0, #0x20
        blo .WbInvDCR
    bx lr


BEGIN_ASM_FUNC CACHE_DrainWriteBuffer
@ void CACHE_DrainWriteBuffer(void)
    mov r0, #0
    mcr p15, 0, r0, c7, c10, 4
    bx lr
