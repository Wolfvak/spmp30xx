#pragma once

#include <spmp/common.h>

/*
 Input
*/

typedef enum {
    KEY_UP    = BIT(0),
    KEY_DOWN  = BIT(1),
    KEY_LEFT  = BIT(2),
    KEY_RIGHT = BIT(3),
    KEY_SPEC1 = BIT(13),
    KEY_SPEC2 = BIT(15),
    KEY_A     = BIT(16),
    KEY_B     = BIT(17)
} ButtonKeys;
int SPMP_ReadKeys(void);
int SPMP_ScanKeys(int *keys);

/*
 Serial
*/

void SPMP_SerialPrint(const char *fmt, ...);


/*
 System
*/

u32  SPMP_TimeElapsed(void);
