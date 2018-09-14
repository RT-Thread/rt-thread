#!/bin/bash
set -eu

SMALLSIZE=4
MEDIUMSIZE=128
LARGESIZE=132

echo "=== Seek tests ==="
rm -rf blocks
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "hello") => 0;
    for (int i = 0; i < $LARGESIZE; i++) {
        sprintf((char*)buffer, "hello/kitty%d", i);
        lfs_file_open(&lfs, &file[0], (char*)buffer,
                LFS_O_WRONLY | LFS_O_CREAT | LFS_O_APPEND) => 0;

        size = strlen("kittycatcat");
        memcpy(buffer, "kittycatcat", size);
        for (int j = 0; j < $LARGESIZE; j++) {
            lfs_file_write(&lfs, &file[0], buffer, size);
        }

        lfs_file_close(&lfs, &file[0]) => 0;
    }
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Simple dir seek ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "hello") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;

    lfs_soff_t pos;
    int i;
    for (i = 0; i < $SMALLSIZE; i++) {
        sprintf((char*)buffer, "kitty%d", i);
        lfs_dir_read(&lfs, &dir[0], &info) => 1;
        strcmp(info.name, (char*)buffer) => 0;
        pos = lfs_dir_tell(&lfs, &dir[0]);
    }
    pos >= 0 => 1;

    lfs_dir_seek(&lfs, &dir[0], pos) => 0;
    sprintf((char*)buffer, "kitty%d", i);
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, (char*)buffer) => 0;

    lfs_dir_rewind(&lfs, &dir[0]) => 0;
    sprintf((char*)buffer, "kitty%d", 0);
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, (char*)buffer) => 0;

    lfs_dir_seek(&lfs, &dir[0], pos) => 0;
    sprintf((char*)buffer, "kitty%d", i);
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, (char*)buffer) => 0;

    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Large dir seek ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "hello") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;

    lfs_soff_t pos;
    int i;
    for (i = 0; i < $MEDIUMSIZE; i++) {
        sprintf((char*)buffer, "kitty%d", i);
        lfs_dir_read(&lfs, &dir[0], &info) => 1;
        strcmp(info.name, (char*)buffer) => 0;
        pos = lfs_dir_tell(&lfs, &dir[0]);
    }
    pos >= 0 => 1;

    lfs_dir_seek(&lfs, &dir[0], pos) => 0;
    sprintf((char*)buffer, "kitty%d", i);
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, (char*)buffer) => 0;

    lfs_dir_rewind(&lfs, &dir[0]) => 0;
    sprintf((char*)buffer, "kitty%d", 0);
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, (char*)buffer) => 0;

    lfs_dir_seek(&lfs, &dir[0], pos) => 0;
    sprintf((char*)buffer, "kitty%d", i);
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, (char*)buffer) => 0;

    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Simple file seek ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "hello/kitty42", LFS_O_RDONLY) => 0;

    lfs_soff_t pos;
    size = strlen("kittycatcat");
    for (int i = 0; i < $SMALLSIZE; i++) {
        lfs_file_read(&lfs, &file[0], buffer, size) => size;
        memcmp(buffer, "kittycatcat", size) => 0;
        pos = lfs_file_tell(&lfs, &file[0]);
    }
    pos >= 0 => 1;

    lfs_file_seek(&lfs, &file[0], pos, LFS_SEEK_SET) => pos;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_rewind(&lfs, &file[0]) => 0;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], 0, LFS_SEEK_CUR) => size;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], size, LFS_SEEK_CUR) => 3*size;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], pos, LFS_SEEK_SET) => pos;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], -size, LFS_SEEK_CUR) => pos;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], -size, LFS_SEEK_END) >= 0 => 1;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    size = lfs_file_size(&lfs, &file[0]);
    lfs_file_seek(&lfs, &file[0], 0, LFS_SEEK_CUR) => size;

    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Large file seek ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "hello/kitty42", LFS_O_RDONLY) => 0;

    lfs_soff_t pos;
    size = strlen("kittycatcat");
    for (int i = 0; i < $MEDIUMSIZE; i++) {
        lfs_file_read(&lfs, &file[0], buffer, size) => size;
        memcmp(buffer, "kittycatcat", size) => 0;
        pos = lfs_file_tell(&lfs, &file[0]);
    }
    pos >= 0 => 1;

    lfs_file_seek(&lfs, &file[0], pos, LFS_SEEK_SET) => pos;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_rewind(&lfs, &file[0]) => 0;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], 0, LFS_SEEK_CUR) => size;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], size, LFS_SEEK_CUR) => 3*size;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], pos, LFS_SEEK_SET) => pos;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], -size, LFS_SEEK_CUR) => pos;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], -size, LFS_SEEK_END) >= 0 => 1;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    size = lfs_file_size(&lfs, &file[0]);
    lfs_file_seek(&lfs, &file[0], 0, LFS_SEEK_CUR) => size;

    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Simple file seek and write ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "hello/kitty42", LFS_O_RDWR) => 0;

    lfs_soff_t pos;
    size = strlen("kittycatcat");
    for (int i = 0; i < $SMALLSIZE; i++) {
        lfs_file_read(&lfs, &file[0], buffer, size) => size;
        memcmp(buffer, "kittycatcat", size) => 0;
        pos = lfs_file_tell(&lfs, &file[0]);
    }
    pos >= 0 => 1;

    memcpy(buffer, "doggodogdog", size);
    lfs_file_seek(&lfs, &file[0], pos, LFS_SEEK_SET) => pos;
    lfs_file_write(&lfs, &file[0], buffer, size) => size;

    lfs_file_seek(&lfs, &file[0], pos, LFS_SEEK_SET) => pos;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "doggodogdog", size) => 0;

    lfs_file_rewind(&lfs, &file[0]) => 0;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], pos, LFS_SEEK_SET) => pos;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "doggodogdog", size) => 0;

    lfs_file_seek(&lfs, &file[0], -size, LFS_SEEK_END) >= 0 => 1;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    size = lfs_file_size(&lfs, &file[0]);
    lfs_file_seek(&lfs, &file[0], 0, LFS_SEEK_CUR) => size;

    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Large file seek and write ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "hello/kitty42", LFS_O_RDWR) => 0;

    lfs_soff_t pos;
    size = strlen("kittycatcat");
    for (int i = 0; i < $MEDIUMSIZE; i++) {
        lfs_file_read(&lfs, &file[0], buffer, size) => size;
        if (i != $SMALLSIZE) {
            memcmp(buffer, "kittycatcat", size) => 0;
        }
        pos = lfs_file_tell(&lfs, &file[0]);
    }
    pos >= 0 => 1;

    memcpy(buffer, "doggodogdog", size);
    lfs_file_seek(&lfs, &file[0], pos, LFS_SEEK_SET) => pos;
    lfs_file_write(&lfs, &file[0], buffer, size) => size;

    lfs_file_seek(&lfs, &file[0], pos, LFS_SEEK_SET) => pos;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "doggodogdog", size) => 0;

    lfs_file_rewind(&lfs, &file[0]) => 0;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    lfs_file_seek(&lfs, &file[0], pos, LFS_SEEK_SET) => pos;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "doggodogdog", size) => 0;

    lfs_file_seek(&lfs, &file[0], -size, LFS_SEEK_END) >= 0 => 1;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "kittycatcat", size) => 0;

    size = lfs_file_size(&lfs, &file[0]);
    lfs_file_seek(&lfs, &file[0], 0, LFS_SEEK_CUR) => size;

    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Boundary seek and write ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "hello/kitty42", LFS_O_RDWR) => 0;

    size = strlen("hedgehoghog");
    const lfs_soff_t offsets[] = {512, 1020, 513, 1021, 511, 1019};

    for (int i = 0; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        lfs_soff_t off = offsets[i];
        memcpy(buffer, "hedgehoghog", size);
        lfs_file_seek(&lfs, &file[0], off, LFS_SEEK_SET) => off;
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
        lfs_file_seek(&lfs, &file[0], off, LFS_SEEK_SET) => off;
        lfs_file_read(&lfs, &file[0], buffer, size) => size;
        memcmp(buffer, "hedgehoghog", size) => 0;

        lfs_file_seek(&lfs, &file[0], 0, LFS_SEEK_SET) => 0;
        lfs_file_read(&lfs, &file[0], buffer, size) => size;
        memcmp(buffer, "kittycatcat", size) => 0;

        lfs_file_sync(&lfs, &file[0]) => 0;
    }

    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Out-of-bounds seek ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "hello/kitty42", LFS_O_RDWR) => 0;

    size = strlen("kittycatcat");
    lfs_file_size(&lfs, &file[0]) => $LARGESIZE*size;
    lfs_file_seek(&lfs, &file[0], ($LARGESIZE+$SMALLSIZE)*size,
            LFS_SEEK_SET) => ($LARGESIZE+$SMALLSIZE)*size;
    lfs_file_read(&lfs, &file[0], buffer, size) => 0;

    memcpy(buffer, "porcupineee", size);
    lfs_file_write(&lfs, &file[0], buffer, size) => size;

    lfs_file_seek(&lfs, &file[0], ($LARGESIZE+$SMALLSIZE)*size,
            LFS_SEEK_SET) => ($LARGESIZE+$SMALLSIZE)*size;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "porcupineee", size) => 0;

    lfs_file_seek(&lfs, &file[0], $LARGESIZE*size,
            LFS_SEEK_SET) => $LARGESIZE*size;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "\0\0\0\0\0\0\0\0\0\0\0", size) => 0;

    lfs_file_seek(&lfs, &file[0], -(($LARGESIZE+$SMALLSIZE)*size),
            LFS_SEEK_CUR) => LFS_ERR_INVAL;
    lfs_file_tell(&lfs, &file[0]) => ($LARGESIZE+1)*size;

    lfs_file_seek(&lfs, &file[0], -(($LARGESIZE+2*$SMALLSIZE)*size),
            LFS_SEEK_END) => LFS_ERR_INVAL;
    lfs_file_tell(&lfs, &file[0]) => ($LARGESIZE+1)*size;

    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Results ---"
tests/stats.py
