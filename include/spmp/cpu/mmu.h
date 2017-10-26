#pragma once

#include <spmp/common.h>

u32 *MMU_GetTTBR(void);
void MMU_SetTTBR(u32 *tt);

u32  MMU_GetDACR(void);
void MMU_SetDACR(u32 dacr);

u32  MMU_GetFAR(void);
u32  MMU_GetIFSR(void);
u32  MMU_GetDFSR(void);

void MMU_InvTLB(void);
void MMU_InvTLBEntry(u32 mva_addr);
