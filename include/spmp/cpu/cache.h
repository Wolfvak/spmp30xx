#pragma once

#include <spmp/common.h>

void CACHE_Inv(void);

void CACHE_InvIC(void);
void CACHE_InvICRange(u32 mva_start, u32 mva_end);

void CACHE_InvDC(void);
void CACHE_WbDC(void);
void CACHE_WbInvDC(void);
void CACHE_InvDCRange(u32 mva_start, u32 mva_end);
void CACHE_WbDCRange(u32 mva_start, u32 mva_end);
void CACHE_WbInvDCRange(u32 mva_start, u32 mva_end);

void CACHE_DrainWriteBuffer(void);
