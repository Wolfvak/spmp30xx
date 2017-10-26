#pragma once

#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define asm      __asm volatile
#define NORETURN __attribute__((noreturn))
#define UNUSED   __attribute__((unused))
#define PACKED   __attribute__((packed))

#define ARM_FUNC __attribute__((target("arm")))
#define TMB_FUNC __attribute__((target("thumb")))

#define BIT(x)       (1<<(x))
#define ALIGN(x,y)   ((x)+(BIT((y)))-((x)&(BIT((y))-1)))
#define MAX(x,y)     ((x)>=(y)?(x):(y))
#define MIN(x,y)     ((x)<=(y)?(x):(y))
#define CLAMP(x,y,z) ((x)<(y)?(y):((x)>(z)?(z):(x)))
#define RANGE(x,y,z) ((x)>=(y)&&(x)<=(z))
#define BREAK(x)     asm("bkpt " #x " \n\t")

#undef assert
#ifndef NDEBUG
#define assert(x) do{if(!(x)){BREAK(0x1F);__builtin_unreachable();}}while(0)
#else
#define assert(x) ((void) 0)
#endif

typedef int8_t    s8;
typedef int16_t   s16;
typedef int32_t   s32;
typedef int64_t   s64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef volatile s8  vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef volatile u8  vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

extern void *fake_heap_start, *fake_heap_end;
