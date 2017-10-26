.arm

#include <spmp/asminc.h>

BEGIN_ASM_FUNC MMU_GetTTBR
@ u32 *MMU_GetTTBR(void)
    mrc p15, 0, r0, c2, c0, 0
    bx lr


BEGIN_ASM_FUNC MMU_SetTTBR
@ void MMU_SetTTBR(u32 *tt)
    mcr p15, 0, r0, c2, c0, 0
    bx lr


BEGIN_ASM_FUNC MMU_GetDACR
@ u32 MMU_GetDACR(void)
    mrc p15, 0, r0, c3, c0, 0
    bx lr


BEGIN_ASM_FUNC MMU_SetDACR
@ void MMU_SetDACR(u32 dacr)
    mcr p15, 0, r0, c3, c0, 0
    bx lr  


BEGIN_ASM_FUNC MMU_GetFAR
@ u32 MMU_GetFAR(void)
    mrc p15, 0, r0, c6, c0, 0
    bx lr


BEGIN_ASM_FUNC MMU_GetIFSR
@ u32 MMU_GetIFSR(void)
    mrc p15, 0, r0, c5, c0, 1
    bx lr


BEGIN_ASM_FUNC MMU_GetDFSR
@ u32 MMU_GetDFSR(void)
    mrc p15, 0, r0, c5, c0, 0
    bx lr


BEGIN_ASM_FUNC MMU_InvTLB
@ void MMU_InvTLB(void)
    mov r0, #0
    mcr p15, 0, r0, c8, c7, 0
    bx lr


BEGIN_ASM_FUNC MMU_InvTLBEntry
@ void MMU_InvTLBEntry(u32 mva)
    mcr p15, 0, r0, c8, c7, 0
    bx lr
