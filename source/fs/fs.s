.arm

#include <spmp/asminc.h>

BEGIN_ASM_FUNC SPMP_RecWrite
@ int SPMP_RecWrite(const char *path, void *buf, u8 flags, size_t offset, size_t size)
    OSCALL 0xEC, 0


BEGIN_ASM_FUNC SPMP_RecRead
@ int SPMP_RecRead(const char *path, void *buf, u8 flags, size_t offset, size_t size)
    OSCALL 0xF0, 0


BEGIN_ASM_FUNC SPMP_FileOpen
@ int SPMP_FileOpen(const char *filename, int flags, int *fd)
    OSCALL 0x138, 0


BEGIN_ASM_FUNC SPMP_FileRead
@ int SPMP_FileRead(int fd, void *buf, size_t count, int *res)
    OSCALL 0x13C, 0


BEGIN_ASM_FUNC SPMP_FileWrite
@ int SPMP_FileWrite(int fd, const void *buf, size_t count, int *res)
    OSCALL 0x140, 0


BEGIN_ASM_FUNC SPMP_FileClose
@ int SPMP_FileClose(int fd)
    OSCALL 0x144, 0


BEGIN_ASM_FUNC SPMP_FileSeek
@ void SPMP_FileSeek(int fd, int offset, int whence)
    OSCALL 0x148, 0
