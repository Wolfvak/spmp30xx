#pragma once

#ifdef __ASSEMBLER__
.macro BEGIN_ASM_FUNC func
    .section .text.\func, "ax", %progbits

    .global \func
    .type \func, %function
    .align 2
\func:
.endm

.macro OSCALL oscall_n=4, ret=1
    ldr r12, =0x24000000
    .if \ret
    mov lr, pc
    .endif
    ldr pc, [r12, #(0xC00 + (\oscall_n))]
.endm
#endif


/* Status Register */
#define SR_USR_MODE   (0x10)
#define SR_FIQ_MODE   (0x11)
#define SR_IRQ_MODE   (0x12)
#define SR_SVC_MODE   (0x13)
#define SR_ABT_MODE   (0x17)
#define SR_UND_MODE   (0x1B)
#define SR_SYS_MODE   (0x1F)
#define SR_PMODE_MASK (0x0F)

#define SR_THUMB      (1<<5)
#define SR_FIQ        (1<<6)
#define SR_IRQ        (1<<7)


/* Control Register */
#define CR_MMU     (1<<0)
#define CR_AFAULT  (1<<1)
#define CR_DCACHE  (1<<2)
#define CR_ENDIAN  (1<<7)
#define CR_SYSPROT (1<<8)
#define CR_ROMPROT (1<<9)
#define CR_ICACHE  (1<<12)
#define CR_ALTXRQV (1<<13)
#define CR_CRROBIN (1<<14)
#define CR_OLDTMBB (1<<15)


/* MMU Section/Page */
#define MMU_AP_NA_NA     (0)
#define MMU_AP_RW_NA     (1)
#define MMU_AP_RW_RO     (2)
#define MMU_AP_RW_RW     (3)

#define MMU_CACHE_NA     (0)
#define MMU_CACHE_NA_BUF (1)
#define MMU_CACHE_WT_BUF (2)
#define MMU_CACHE_WB_BUF (3)

#define MMU_FAULT        (0)

#define MMU_COARSE       (1)
#define MMU_SECTION      (2)
#define MMU_FINEPAGE     (3)

#define MMU_LARGEPAGE    (1)
#define MMU_SMALLPAGE    (2)
#define MMU_TINYPAGE     (3)


/* Exception types */
#define XRQ_RESET (0)
#define XRQ_UNDEF (1)
#define XRQ_SWI   (2)
#define XRQ_PABT  (3)
#define XRQ_DABT  (4)
#define XRQ_RESV  (5)
#define XRQ_IRQ   (6)
#define XRQ_FIQ   (7)
