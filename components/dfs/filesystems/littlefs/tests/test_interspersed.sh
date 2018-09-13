#!/bin/bash
set -eu

echo "=== Interspersed tests ==="
rm -rf blocks
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST

echo "--- Interspersed file test ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "a", LFS_O_WRONLY | LFS_O_CREAT) => 0;
    lfs_file_open(&lfs, &file[1], "b", LFS_O_WRONLY | LFS_O_CREAT) => 0;
    lfs_file_open(&lfs, &file[2], "c", LFS_O_WRONLY | LFS_O_CREAT) => 0;
    lfs_file_open(&lfs, &file[3], "d", LFS_O_WRONLY | LFS_O_CREAT) => 0;

    for (int i = 0; i < 10; i++) {
        lfs_file_write(&lfs, &file[0], (const void*)"a", 1) => 1;
        lfs_file_write(&lfs, &file[1], (const void*)"b", 1) => 1;
        lfs_file_write(&lfs, &file[2], (const void*)"c", 1) => 1;
        lfs_file_write(&lfs, &file[3], (const void*)"d", 1) => 1;
    }

    lfs_file_close(&lfs, &file[0]);
    lfs_file_close(&lfs, &file[1]);
    lfs_file_close(&lfs, &file[2]);
    lfs_file_close(&lfs, &file[3]);

    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "a") => 0;
    info.type => LFS_TYPE_REG;
    info.size => 10;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "b") => 0;
    info.type => LFS_TYPE_REG;
    info.size => 10;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "c") => 0;
    info.type => LFS_TYPE_REG;
    info.size => 10;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "d") => 0;
    info.type => LFS_TYPE_REG;
    info.size => 10;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;

    lfs_file_open(&lfs, &file[0], "a", LFS_O_RDONLY) => 0;
    lfs_file_open(&lfs, &file[1], "b", LFS_O_RDONLY) => 0;
    lfs_file_open(&lfs, &file[2], "c", LFS_O_RDONLY) => 0;
    lfs_file_open(&lfs, &file[3], "d", LFS_O_RDONLY) => 0;

    for (int i = 0; i < 10; i++) {
        lfs_file_read(&lfs, &file[0], buffer, 1) => 1;
        buffer[0] => 'a';
        lfs_file_read(&lfs, &file[1], buffer, 1) => 1;
        buffer[0] => 'b';
        lfs_file_read(&lfs, &file[2], buffer, 1) => 1;
        buffer[0] => 'c';
        lfs_file_read(&lfs, &file[3], buffer, 1) => 1;
        buffer[0] => 'd';
    }

    lfs_file_close(&lfs, &file[0]);
    lfs_file_close(&lfs, &file[1]);
    lfs_file_close(&lfs, &file[2]);
    lfs_file_close(&lfs, &file[3]);
    
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Interspersed remove file test ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "e", LFS_O_WRONLY | LFS_O_CREAT) => 0;

    for (int i = 0; i < 5; i++) {
        lfs_file_write(&lfs, &file[0], (const void*)"e", 1) => 1;
    }

    lfs_remove(&lfs, "a") => 0;
    lfs_remove(&lfs, "b") => 0;
    lfs_remove(&lfs, "c") => 0;
    lfs_remove(&lfs, "d") => 0;

    for (int i = 0; i < 5; i++) {
        lfs_file_write(&lfs, &file[0], (const void*)"e", 1) => 1;
    }

    lfs_file_close(&lfs, &file[0]);

    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "e") => 0;
    info.type => LFS_TYPE_REG;
    info.size => 10;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;

    lfs_file_open(&lfs, &file[0], "e", LFS_O_RDONLY) => 0;

    for (int i = 0; i < 10; i++) {
        lfs_file_read(&lfs, &file[0], buffer, 1) => 1;
        buffer[0] => 'e';
    }

    lfs_file_close(&lfs, &file[0]);
    
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Remove inconveniently test ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "e", LFS_O_WRONLY | LFS_O_TRUNC) => 0;
    lfs_file_open(&lfs, &file[1], "f", LFS_O_WRONLY | LFS_O_CREAT) => 0;
    lfs_file_open(&lfs, &file[2], "g", LFS_O_WRONLY | LFS_O_CREAT) => 0;

    for (int i = 0; i < 5; i++) {
        lfs_file_write(&lfs, &file[0], (const void*)"e", 1) => 1;
        lfs_file_write(&lfs, &file[1], (const void*)"f", 1) => 1;
        lfs_file_write(&lfs, &file[2], (const void*)"g", 1) => 1;
    }

    lfs_remove(&lfs, "f") => 0;

    for (int i = 0; i < 5; i++) {
        lfs_file_write(&lfs, &file[0], (const void*)"e", 1) => 1;
        lfs_file_write(&lfs, &file[1], (const void*)"f", 1) => 1;
        lfs_file_write(&lfs, &file[2], (const void*)"g", 1) => 1;
    }

    lfs_file_close(&lfs, &file[0]);
    lfs_file_close(&lfs, &file[1]);
    lfs_file_close(&lfs, &file[2]);

    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    info.type => LFS_TYPE_DIR;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "e") => 0;
    info.type => LFS_TYPE_REG;
    info.size => 10;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "g") => 0;
    info.type => LFS_TYPE_REG;
    info.size => 10;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;

    lfs_file_open(&lfs, &file[0], "e", LFS_O_RDONLY) => 0;
    lfs_file_open(&lfs, &file[1], "g", LFS_O_RDONLY) => 0;

    for (int i = 0; i < 10; i++) {
        lfs_file_read(&lfs, &file[0], buffer, 1) => 1;
        buffer[0] => 'e';
        lfs_file_read(&lfs, &file[1], buffer, 1) => 1;
        buffer[0] => 'g';
    }

    lfs_file_close(&lfs, &file[0]);
    lfs_file_close(&lfs, &file[1]);
    
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Results ---"
tests/stats.py
