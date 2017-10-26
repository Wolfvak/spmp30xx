#pragma once

#include <spmp/common.h>

u32  ARM_GetIDCode(void);

u32  ARM_GetCPSR(void);
void ARM_SetCPSR(u32 cpsr);

void ARM_DisableIRQ(void);
void ARM_EnableIRQ(void);

u32  ARM_EnterCritical(void);
void ARM_LeaveCritical(u32 stat);

u32  ARM_GetCR(void);
void ARM_SetCR(u32 cr);

void ARM_WaitForInterrupt(void);
