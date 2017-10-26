#include <spmp/common.h>
#include <spmp/asminc.h>

#include <spmp/system/os.h>
#include <spmp/misc/qr.h>

#include <stdio.h>

#define MMU_AFAULT "Alignment fault"
#define MMU_EATRAN "External abort on translation"
#define MMU_TRAN   "Translation fault"
#define MMU_DOM    "Domain fault"
#define MMU_AP     "Permission fault"
#define MMU_EABT   "External abort"
#define MMU_UNKFLT "Unknown"

const char *xrqtype[] = {
    "Reset", "Undefined instruction", "Software interrupt",
    "Prefetch abort", "Data abort", "Reserved",
    "Hardware interrupt", "Fast hardware interrupt"
};

const char *pmodes[] = {
    "User", "FIQ", "IRQ", "Supervisor",
    "Abort", "Undefined", "System"
};

const char *fsrtype[] = {
    MMU_UNKFLT, MMU_AFAULT, MMU_UNKFLT, MMU_AFAULT,
    MMU_UNKFLT, MMU_TRAN, MMU_UNKFLT, MMU_TRAN,
    MMU_EABT, MMU_DOM, MMU_EABT, MMU_DOM,
    MMU_EATRAN, MMU_AP, MMU_EABT, MMU_AP
};

void XRQ_MainHandler(u32 *regs, u32 xrq_type) {
    char str[2048], *str_ = str;
    u8 qr[qrcodegen_BUFFER_LEN_MAX];

    str_ += sprintf(str_, "Abort! (%s)\n", xrqtype[xrq_type]);
    for (int i=0; i<16; i++) {
        str_ += sprintf(str_, "R%02d = %08X\n", i, regs[i]);
    }

    str_ += sprintf(str_, "CPSR = %08X (%s, interrupts %s)\n",
        regs[16], pmodes[regs[16]&0xF], (regs[16]&SR_IRQ) ? "off" : "on");

    str_ += sprintf(str_, "XPSR = %08X\n", regs[17]);
    str_ += sprintf(str_, "TTBR = %08X\n", regs[18]);

    if (xrq_type == XRQ_DABT) {
        str_ += sprintf(str_, "FAR  = %08X\n", regs[19]);
        str_ += sprintf(str_, "DFSR = %08X\n", regs[21]);
        str_ += sprintf(str_, "MMU fault: %s\n", fsrtype[regs[21] & 0xF]);
    }

    SPMP_SerialPrint(str);
    if (SPMP_QREncodeString(str, qr)) {
        SPMP_QRDraw(qr, -1);
    }
    return;
}
