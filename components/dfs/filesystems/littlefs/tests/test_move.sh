#!/bin/bash
set -eu

echo "=== Move tests ==="
rm -rf blocks
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;

    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "a") => 0;
    lfs_mkdir(&lfs, "b") => 0;
    lfs_mkdir(&lfs, "c") => 0;
    lfs_mkdir(&lfs, "d") => 0;

    lfs_mkdir(&lfs, "a/hi") => 0;
    lfs_mkdir(&lfs, "a/hi/hola") => 0;
    lfs_mkdir(&lfs, "a/hi/bonjour") => 0;
    lfs_mkdir(&lfs, "a/hi/ohayo") => 0;

    lfs_file_open(&lfs, &file[0], "a/hello", LFS_O_CREAT | LFS_O_WRONLY) => 0;
    lfs_file_write(&lfs, &file[0], "hola\n", 5) => 5;
    lfs_file_write(&lfs, &file[0], "bonjour\n", 8) => 8;
    lfs_file_write(&lfs, &file[0], "ohayo\n", 6) => 6;
    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Move file ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_rename(&lfs, "a/hello", "b/hello") => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "a") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hi") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_dir_open(&lfs, &dir[0], "b") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hello") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Move file corrupt source ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_rename(&lfs, "b/hello", "c/hello") => 0;
    lfs_unmount(&lfs) => 0;
TEST
rm -v blocks/7
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "b") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_dir_open(&lfs, &dir[0], "c") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hello") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Move file corrupt source and dest ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_rename(&lfs, "c/hello", "d/hello") => 0;
    lfs_unmount(&lfs) => 0;
TEST
rm -v blocks/8
rm -v blocks/a
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "c") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hello") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_dir_open(&lfs, &dir[0], "d") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Move dir ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_rename(&lfs, "a/hi", "b/hi") => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "a") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_dir_open(&lfs, &dir[0], "b") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hi") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Move dir corrupt source ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_rename(&lfs, "b/hi", "c/hi") => 0;
    lfs_unmount(&lfs) => 0;
TEST
rm -v blocks/7
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "b") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_dir_open(&lfs, &dir[0], "c") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hello") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hi") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Move dir corrupt source and dest ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_rename(&lfs, "c/hi", "d/hi") => 0;
    lfs_unmount(&lfs) => 0;
TEST
rm -v blocks/9
rm -v blocks/a
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "c") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hello") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hi") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_dir_open(&lfs, &dir[0], "d") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Move check ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;

    lfs_dir_open(&lfs, &dir[0], "a/hi") => LFS_ERR_NOENT;
    lfs_dir_open(&lfs, &dir[0], "b/hi") => LFS_ERR_NOENT;
    lfs_dir_open(&lfs, &dir[0], "d/hi") => LFS_ERR_NOENT;

    lfs_dir_open(&lfs, &dir[0], "c/hi") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, ".") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "..") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hola") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "bonjour") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "ohayo") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;

    lfs_dir_open(&lfs, &dir[0], "a/hello") => LFS_ERR_NOENT;
    lfs_dir_open(&lfs, &dir[0], "b/hello") => LFS_ERR_NOENT;
    lfs_dir_open(&lfs, &dir[0], "d/hello") => LFS_ERR_NOENT;

    lfs_file_open(&lfs, &file[0], "c/hello", LFS_O_RDONLY) => 0;
    lfs_file_read(&lfs, &file[0], buffer, 5) => 5;
    memcmp(buffer, "hola\n", 5) => 0;
    lfs_file_read(&lfs, &file[0], buffer, 8) => 8;
    memcmp(buffer, "bonjour\n", 8) => 0;
    lfs_file_read(&lfs, &file[0], buffer, 6) => 6;
    memcmp(buffer, "ohayo\n", 6) => 0;
    lfs_file_close(&lfs, &file[0]) => 0;

    lfs_unmount(&lfs) => 0;
TEST


echo "--- Results ---"
tests/stats.py
