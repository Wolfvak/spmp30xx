.arm

#include <spmp/asminc.h>

BEGIN_ASM_FUNC SPMP_SerialPrint
@ void SPMP_SerialPrint(const char *fmt, ...)
    OSCALL 0x04, 0


BEGIN_ASM_FUNC SPMP_ReadKeys
@ int SPMP_ReadKeys(void)
    push {lr}
    sub sp, sp, #12
    mov r0, sp
    OSCALL 0x100
    cmp r0, #0
    ldrne r0, [sp, #4]
    add sp, sp, #12
    pop {lr}
    bx lr


BEGIN_ASM_FUNC SPMP_ScanKeys
@ int SPMP_ScanKeys(int *keys)
    OSCALL 0xFC, 0


BEGIN_ASM_FUNC SPMP_TimeElapsed
@ u32 SPMP_TimeElapsed(void)
    OSCALL 0x124, 0
