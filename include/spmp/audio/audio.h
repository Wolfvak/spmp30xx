#pragma once

#include <spmp/common.h>

typedef enum {
    AUDIO_PCM  = 1,
    AUDIO_MIDI = 2
} AudioType;

typedef struct {
    const char name[16];
    const u8 *data;
} PACKED AudioFile;

typedef struct {
    u8 *data;
    u32 size;
    int unk[2];
} PACKED AudioInfo;

void SPMP_AudioInit(const AudioFile **file);
int  SPMP_AudioInfo(const AudioFile *file, AudioInfo *info);
void SPMP_AudioPlay(u8 type, u8 loops, AudioInfo *info);
void SPMP_AudioStop(int type);
