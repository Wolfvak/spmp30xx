.arm

#include <spmp/asminc.h>

BEGIN_ASM_FUNC vectors
    ldr pc, =_init      @ Reset application
    ldr pc, =xrq_undef  @ Undefined instruction
    ldr pc, =xrq_svc    @ SVC / Software Interrupt
    ldr pc, =xrq_pabt   @ Prefetch abort (Instruction Fetch)
    ldr pc, =xrq_dabt   @ Data abort (Data Fetch)
    ldr pc, =0x00000014 @ Reserved
    ldr pc, =0x00000018 @ IRQ
    ldr pc, =0x0000001C @ FIQ

.macro XRQ_FATAL n
    ldr sp, =abt_stack_top
    sub sp, sp, #(0x80)

    stmia sp, {r0-r12}
    add r4, sp, #(13*4)
    mov r11, #(\n)

    mrs r9, spsr
    mrs r10, cpsr

    orr r0, r9, #(SR_IRQ | SR_FIQ)
    bic r0, r0, #(SR_THUMB)
    tst r9, #(SR_PMODE_MASK)
    orreq r0, r0, #(SR_SYS_MODE)

    msr cpsr_c, r0
    mov r1, sp
    mov r2, lr
    msr cpsr_c, r10
    mov r3, lr

    stmia r4!, {r1,r2,r3,r9,r10}

    bl MMU_GetTTBR
    mov r5, r0
    bl MMU_GetFAR
    mov r6, r0
    bl MMU_GetIFSR
    mov r7, r0
    bl MMU_GetDFSR
    mov r8, r0

    stmia r4!, {r5,r6,r7,r8}

    mov r0, sp
    mov r1, r11
    bl XRQ_MainHandler

    ldr lr, =ARM_WaitForInterrupt
    bx lr
.endm

xrq_undef:
    XRQ_FATAL XRQ_UNDEF

xrq_svc:
    bkpt

xrq_pabt:
    XRQ_FATAL XRQ_PABT

xrq_dabt:
    XRQ_FATAL XRQ_DABT

.section .bss.abt_stack
.align 3
abt_stack_bot:
    .space (24*1024)
abt_stack_top:
