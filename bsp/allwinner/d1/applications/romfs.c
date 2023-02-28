#include <dfs_romfs.h>

static const struct romfs_dirent _romfs_root[] = {
    {ROMFS_DIRENT_DIR, "etc", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "mnt", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "boot", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "boot-resource", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "bin", RT_NULL, 0}
};

const struct romfs_dirent romfs_root = {
    ROMFS_DIRENT_DIR, "/", (rt_uint8_t *)_romfs_root, sizeof(_romfs_root) / sizeof(_romfs_root[0])};

