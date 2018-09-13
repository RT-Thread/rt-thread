#!/bin/bash
set -eu

SMALLSIZE=32
MEDIUMSIZE=8192
LARGESIZE=262144

echo "=== File tests ==="
rm -rf blocks
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST

echo "--- Simple file test ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "hello", LFS_O_WRONLY | LFS_O_CREAT) => 0;
    size = strlen("Hello World!\n");
    memcpy(wbuffer, "Hello World!\n", size);
    lfs_file_write(&lfs, &file[0], wbuffer, size) => size;
    lfs_file_close(&lfs, &file[0]) => 0;

    lfs_file_open(&lfs, &file[0], "hello", LFS_O_RDONLY) => 0;
    size = strlen("Hello World!\n");
    lfs_file_read(&lfs, &file[0], rbuffer, size) => size;
    memcmp(rbuffer, wbuffer, size) => 0;
    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

w_test() {
tests/test.py << TEST
    size = $1;
    lfs_size_t chunk = 31;
    srand(0);
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "$2",
        ${3:-LFS_O_WRONLY | LFS_O_CREAT | LFS_O_TRUNC}) => 0;
    for (lfs_size_t i = 0; i < size; i += chunk) {
        chunk = (chunk < size - i) ? chunk : size - i;
        for (lfs_size_t b = 0; b < chunk; b++) {
            buffer[b] = rand() & 0xff;
        }
        lfs_file_write(&lfs, &file[0], buffer, chunk) => chunk;
    }
    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST
}

r_test() {
tests/test.py << TEST
    size = $1;
    lfs_size_t chunk = 29;
    srand(0);
    lfs_mount(&lfs, &cfg) => 0;
    lfs_stat(&lfs, "$2", &info) => 0;
    info.type => LFS_TYPE_REG;
    info.size => size;
    lfs_file_open(&lfs, &file[0], "$2", ${3:-LFS_O_RDONLY}) => 0;
    for (lfs_size_t i = 0; i < size; i += chunk) {
        chunk = (chunk < size - i) ? chunk : size - i;
        lfs_file_read(&lfs, &file[0], buffer, chunk) => chunk;
        for (lfs_size_t b = 0; b < chunk && i+b < size; b++) {
            buffer[b] => rand() & 0xff;
        }
    }
    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST
}

echo "--- Small file test ---"
w_test $SMALLSIZE smallavacado
r_test $SMALLSIZE smallavacado

echo "--- Medium file test ---"
w_test $MEDIUMSIZE mediumavacado
r_test $MEDIUMSIZE mediumavacado

echo "--- Large file test ---"
w_test $LARGESIZE largeavacado
r_test $LARGESIZE largeavacado

echo "--- Zero file test ---"
w_test 0 noavacado
r_test 0 noavacado

echo "--- Truncate small test ---"
w_test $SMALLSIZE mediumavacado
r_test $SMALLSIZE mediumavacado
w_test $MEDIUMSIZE mediumavacado
r_test $MEDIUMSIZE mediumavacado

echo "--- Truncate zero test ---"
w_test $SMALLSIZE noavacado
r_test $SMALLSIZE noavacado
w_test 0 noavacado
r_test 0 noavacado

echo "--- Non-overlap check ---"
r_test $SMALLSIZE smallavacado
r_test $MEDIUMSIZE mediumavacado
r_test $LARGESIZE largeavacado
r_test 0 noavacado

echo "--- Dir check ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_dir_open(&lfs, &dir[0], "/") => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "hello") => 0;
    info.type => LFS_TYPE_REG;
    info.size => strlen("Hello World!\n");
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "smallavacado") => 0;
    info.type => LFS_TYPE_REG;
    info.size => $SMALLSIZE;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "mediumavacado") => 0;
    info.type => LFS_TYPE_REG;
    info.size => $MEDIUMSIZE;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "largeavacado") => 0;
    info.type => LFS_TYPE_REG;
    info.size => $LARGESIZE;
    lfs_dir_read(&lfs, &dir[0], &info) => 1;
    strcmp(info.name, "noavacado") => 0;
    info.type => LFS_TYPE_REG;
    info.size => 0;
    lfs_dir_read(&lfs, &dir[0], &info) => 0;
    lfs_dir_close(&lfs, &dir[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Many file test ---"
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST
tests/test.py << TEST
    // Create 300 files of 6 bytes
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "directory") => 0;
    for (unsigned i = 0; i < 300; i++) {
        snprintf((char*)buffer, sizeof(buffer), "file_%03d", i);
        lfs_file_open(&lfs, &file[0], (char*)buffer, LFS_O_WRONLY | LFS_O_CREAT) => 0;
        size = 6;
        memcpy(wbuffer, "Hello", size);
        lfs_file_write(&lfs, &file[0], wbuffer, size) => size;
        lfs_file_close(&lfs, &file[0]) => 0;
    }
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Results ---"
tests/stats.py
