#pragma once

#include <spmp/common.h>
#include <spmp/libs/qrcodegen.h>

bool SPMP_QREncodeString(const char *str, void *qr);
void SPMP_QRDraw(const void *qr, int scale);
