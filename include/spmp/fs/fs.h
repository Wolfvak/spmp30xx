#pragma once

typedef enum {
    FS_RDONLY = BIT(0),
    FS_WRONLY = BIT(1),
    FS_RDWR   = (FS_RDONLY | FS_WRONLY),
    FS_CREAT  = BIT(3),
    FS_EXCL   = BIT(4),
    FS_NOCTTY = BIT(5),
    FS_TRUNC  = BIT(6),
    FS_APPEND = BIT(7),
    FS_DSYNC  = BIT(8),
    FS_NBLOCK = BIT(9),
    FS_RSYNC  = BIT(10),
    FS_SYNC   = BIT(11)
} SPMP_FileOpenMode;

typedef enum {
    FS_SEEK_SET = 0,
    FS_SEEK_CUR = 1,
    FS_SEEK_END = 2
} SPMP_FileSeekMode;

int SPMP_FileOpen(const char *path, int flags, int *fd);
int SPMP_FileRead(int fd, const void *buf, size_t count, int *result);
int SPMP_FileWrite(int fd, const void *buf, size_t count, int *result);
int SPMP_FileClose(int fd);
void SPMP_FileSeek(int fd, int offset, int whence);

int SPMP_RecWrite(const char *path, void *buf, u8 flags, size_t offset, size_t size);
int SPMP_RecRead(const char *path, void *buf, u8 flags, size_t offset, size_t size);
