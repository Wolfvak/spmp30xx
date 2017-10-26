.arm

#include <spmp/asminc.h>

BEGIN_ASM_FUNC _init
    push {r0-r6,lr}

    @ Clear BSS
    mov r4, #0
    ldr r5, =__bss_s
    ldr r6, =__bss_e
    .LClearBSS:
        cmp r5, r6
        strlo r0, [r5], #4
        blo .LClearBSS

    @ Setup heap
    ldr r4, =fake_heap_start
    ldr r5, =__heap_start
    str r5, [r4]    

    ldr r4, =fake_heap_end
    ldr r5, =__heap_end
    str r5, [r4]

    @ Map high exception vectors
    @ [0xFFFF0000, 0xFFFF1000] -> [vectors, vectors+0x1000]
    @ R4 = TTBR
    @ R5 = High exception vector coarse page table
    ldr r5, =__highxrqv_tt
    bl MMU_GetTTBR
    mov r4, r0

    @ Build the 4K page descriptor and 
    @ store it @ 0xF0 in the coarse page table
    ldr r0, =vectors
    ldr r1, =MMU_AP_RW_RW
    ldr r2, =MMU_CACHE_WB_BUF
    bl __build_mmupage_small
    str r0, [r5, #(0xF0 << 2)]

    @ Get domain of section 0 (bootROM) and
    @ make page 0xFFF of the TT point to the
    @ exception vector coarse page table
    ldr r1, [r4]
    mov r0, r5
    lsr r1, r1, #5
    and r1, r1, #0xF
    bl __build_mmudesc_coarse

    mov r1, #0x00FF
    orr r1, r1, #0x0F00
    str r0, [r4, r1, lsl #2]

    @ Writeback and invalidate caches and TLB
    @ TODO: Controlled cache invalidations
    bl CACHE_WbDC
    bl CACHE_DrainWriteBuffer
    bl CACHE_InvIC
    bl MMU_InvTLB

    ldr r1, =(CR_AFAULT | CR_ALTXRQV | CR_CRROBIN)
    bl ARM_GetCR
    mov r4, r0
    orr r0, r0, r1
    bl ARM_SetCR

    @ Branch to C code
    ldr r0, =main
    mov lr, pc
    bx r0

    @ Restore previous CR1 status
    mov r0, r4
    bl ARM_SetCR

    pop {r0-r6,lr}
    bx lr

.section .bss.highxrqv_tt
.align 10
__highxrqv_tt: .space (256*4)
