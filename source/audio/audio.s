.arm

#include <spmp/asminc.h>

BEGIN_ASM_FUNC SPMP_AudioSetup
@ void SPMP_AudioInit(const AudioFile **file)
    mov r1, r0
    mov r0, #3
    OSCALL 0xD4, 0


BEGIN_ASM_FUNC SPMP_AudioInfo
@ int SPMP_AudioInfo(const AudioFile *file, AudioInfo *info)
    OSCALL 0xD8, 0


BEGIN_ASM_FUNC SPMP_AudioPlay
@ void SPMP_AudioPlay(int type, u8 loops, AudioInfo *info)
    OSCALL 0xDC, 0


BEGIN_ASM_FUNC SPMP_AudioStop
@ void SPMP_AudioStop(int type)
    OSCALL 0xE0, 0
