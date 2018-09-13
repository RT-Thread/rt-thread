#!/bin/bash
set -eu

LARGESIZE=128

echo "=== Directory tests ==="
rm -rf blocks
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST

echo "--- Root directory ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Directory creation ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "potato") => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- File creation ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "burito", LFS_O_CREAT | LFS_O_WRONLY) => 0;
    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Directory iteration ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "potato") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "burito") => 0;
    info.type => LFS_TYPE_REG;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Directory failures ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "potato") => LFS_ERR_EXIST;
    lfs_dir_open(&lfs, &dir[0], "tomato") => LFS_ERR_NOENT;
    lfs_dir_open(&lfs, &dir[0], "burito") => LFS_ERR_NOTDIR;
    lfs_file_open(&lfs, &file[0], "tomato", LFS_O_RDONLY) => LFS_ERR_NOENT;
    lfs_file_open(&lfs, &file[0], "potato", LFS_O_RDONLY) => LFS_ERR_ISDIR;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Nested directories ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "potato/baked") => 0;
    lfs_mkdir(&lfs, "potato/sweet") => 0;
    lfs_mkdir(&lfs, "potato/fried") => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "potato") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "baked") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "sweet") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "fried") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Multi-block directory ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "cactus") => 0;
    for (int i = 0; i < $LARGESIZE; i++) {
        sprintf((char*)buffer, "cactus/test%d", i);
        lfs_mkdir(&lfs, (char*)buffer) => 0;
    }
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "cactus") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    for (int i = 0; i < $LARGESIZE; i++) {
        sprintf((char*)buffer, "test%d", i);
        lfs_dir_read(&lfs, &dir[0], &info) => 1;
        strcmp(info.name, (char*)buffer) => 0;
        info.type => LFS_TYPE_DIR;
    }
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Directory remove ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_remove(&lfs, "potato") => LFS_ERR_NOTEMPTY;
    lfs_remove(&lfs, "potato/sweet") => 0;
    lfs_remove(&lfs, "potato/baked") => 0;
    lfs_remove(&lfs, "potato/fried") => 0;

    lfs_dir_open(&lfs, &dir[0], "potato") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;

    lfs_remove(&lfs, "potato") => 0;

    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "burito") => 0;
    info.type => LFS_TYPE_REG;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "cactus") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "burito") => 0;
    info.type => LFS_TYPE_REG;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "cactus") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Directory rename ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "coldpotato") => 0;
    lfs_mkdir(&lfs, "coldpotato/baked") => 0;
    lfs_mkdir(&lfs, "coldpotato/sweet") => 0;
    lfs_mkdir(&lfs, "coldpotato/fried") => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_rename(&lfs, "coldpotato", "hotpotato") => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "hotpotato") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "baked") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "sweet") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "fried") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "warmpotato") => 0;
    lfs_mkdir(&lfs, "warmpotato/mushy") => 0;
    lfs_rename(&lfs, "hotpotato", "warmpotato") => LFS_ERR_NOTEMPTY;

    lfs_remove(&lfs, "warmpotato/mushy") => 0;
    lfs_rename(&lfs, "hotpotato", "warmpotato") => 0;

    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "warmpotato") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "baked") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "sweet") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "fried") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "coldpotato") => 0;
    lfs_rename(&lfs, "warmpotato/baked", "coldpotato/baked") => 0;
    lfs_rename(&lfs, "warmpotato/sweet", "coldpotato/sweet") => 0;
    lfs_rename(&lfs, "warmpotato/fried", "coldpotato/fried") => 0;
    lfs_remove(&lfs, "coldpotato") => LFS_ERR_NOTEMPTY;
    lfs_remove(&lfs, "warmpotato") => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "coldpotato") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "baked") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "sweet") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "fried") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Recursive remove ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_remove(&lfs, "coldpotato") => LFS_ERR_NOTEMPTY;

    lfs_dir_open(&lfs, &dir[0], "coldpotato") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;

    while (true) {
        int err = lfs_dir_read(&lfs, &dir[0], &info);
        err >= 0 => 1;
        if (err == 0) {
            break;
        }

        strcpy((char*)buffer, "coldpotato/");
        strcat((char*)buffer, info.name);
        lfs_remove(&lfs, (char*)buffer) => 0;
    }

    lfs_remove(&lfs, "coldpotato") => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "burito") => 0;
    info.type => LFS_TYPE_REG;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "cactus") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Multi-block remove ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_remove(&lfs, "cactus") => LFS_ERR_NOTEMPTY;

    for (int i = 0; i < $LARGESIZE; i++) {
        sprintf((char*)buffer, "cactus/test%d", i);
        lfs_remove(&lfs, (char*)buffer) => 0;
    }

    lfs_remove(&lfs, "cactus") => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "burito") => 0;
    info.type => LFS_TYPE_REG;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Multi-block directory with files ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "prickly-pear") => 0;
    for (int i = 0; i < $LARGESIZE; i++) {
        sprintf((char*)buffer, "prickly-pear/test%d", i);
        lfs_file_open(&lfs, &file[0], (char*)buffer,
                LFS_O_WRONLY | LFS_O_CREAT) => 0;
        size = 6;
        memcpy(wbuffer, "Hello", size);
        lfs_file_write(&lfs, &file[0], wbuffer, size) => size;
        lfs_file_close(&lfs, &file[0]) => 0;
    }
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "prickly-pear") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    for (int i = 0; i < $LARGESIZE; i++) {
        sprintf((char*)buffer, "test%d", i);
        lfs_dir_read(&lfs, &dir[0], &info) => 1;
        strcmp(info.name, (char*)buffer) => 0;
        info.type => LFS_TYPE_REG;
        info.size => 6;
    }
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Multi-block remove with files ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_remove(&lfs, "prickly-pear") => LFS_ERR_NOTEMPTY;

    for (int i = 0; i < $LARGESIZE; i++) {
        sprintf((char*)buffer, "prickly-pear/test%d", i);
        lfs_remove(&lfs, (char*)buffer) => 0;
    }

    lfs_remove(&lfs, "prickly-pear") => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "burito") => 0;
    info.type => LFS_TYPE_REG;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Results ---"
tests/stats.py
