.arm

#include <spmp/asminc.h>

BEGIN_ASM_FUNC ARM_GetIDCode
@ u32 ARM_GetIDCode(void)
    mrc p15, 0, r0, c0, c0, 0
    bx lr


BEGIN_ASM_FUNC ARM_GetCPSR
@ u32 ARM_GetCPSR(void)
    mrs r0, cpsr
    bx lr


BEGIN_ASM_FUNC ARM_SetCPSR
@ void ARM_SetCPSR(u32 cpsr)
    msr cpsr_c, r0
    bx lr


BEGIN_ASM_FUNC ARM_DisableIRQ
@ void ARM_DisableIRQ(void)
    mrs r0, cpsr
    orr r0, r0, #(SR_IRQ | SR_FIQ)
    msr cpsr_c, r0
    bx lr


BEGIN_ASM_FUNC ARM_EnableIRQ
@ void ARM_EnableIRQ(void)
    mrs r0, cpsr
    bic r0, r0, #(SR_IRQ | SR_FIQ)
    msr cpsr_c, r0
    bx lr


BEGIN_ASM_FUNC ARM_EnterCritical
@ u32 ARM_EnterCritical(void)
    mrs r0, cpsr
    orr r1, r0, #(SR_IRQ | SR_FIQ)
    msr cpsr_c, r1
    bx lr


BEGIN_ASM_FUNC ARM_LeaveCritical
@ void ARM_LeaveCritical(u32 stat)
    msr cpsr_c, r0
    bx lr


BEGIN_ASM_FUNC ARM_GetCR
@ u32 ARM_GetCR(void)
    mrc p15, 0, r0, c1, c0, 0
    bx lr


BEGIN_ASM_FUNC ARM_SetCR
@ void ARM_SetCR(u32 cr)
    mcr p15, 0, r0, c1, c0, 0
    bx lr


BEGIN_ASM_FUNC ARM_WaitForInterrupt
@ void ARM_WaitForInterrupt
    mov r0, #0
    mcr p15, 0, r0, c7, c0, 4
    bx lr

