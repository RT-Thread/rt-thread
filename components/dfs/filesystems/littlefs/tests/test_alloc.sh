#!/bin/bash
set -eu

echo "=== Allocator tests ==="
rm -rf blocks
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST

SIZE=15000

lfs_mkdir() {
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "$1") => 0;
    lfs_unmount(&lfs) => 0;
TEST
}

lfs_remove() {
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_remove(&lfs, "$1/eggs") => 0;
    lfs_remove(&lfs, "$1/bacon") => 0;
    lfs_remove(&lfs, "$1/pancakes") => 0;
    lfs_remove(&lfs, "$1") => 0;
    lfs_unmount(&lfs) => 0;
TEST
}

lfs_alloc_singleproc() {
tests/test.py << TEST
    const char *names[] = {"bacon", "eggs", "pancakes"};
    lfs_mount(&lfs, &cfg) => 0;
    for (int n = 0; n < sizeof(names)/sizeof(names[0]); n++) {
        sprintf((char*)buffer, "$1/%s", names[n]);
        lfs_file_open(&lfs, &file[n], (char*)buffer,
                LFS_O_WRONLY | LFS_O_CREAT | LFS_O_APPEND) => 0;
    }
    for (int n = 0; n < sizeof(names)/sizeof(names[0]); n++) {
        size = strlen(names[n]);
        for (int i = 0; i < $SIZE; i++) {
            lfs_file_write(&lfs, &file[n], names[n], size) => size;
        }
    }
    for (int n = 0; n < sizeof(names)/sizeof(names[0]); n++) {
        lfs_file_close(&lfs, &file[n]) => 0;
    }
    lfs_unmount(&lfs) => 0;
TEST
}

lfs_alloc_multiproc() {
for name in bacon eggs pancakes
do
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "$1/$name",
            LFS_O_WRONLY | LFS_O_CREAT | LFS_O_APPEND) => 0;
    size = strlen("$name");
    memcpy(buffer, "$name", size);
    for (int i = 0; i < $SIZE; i++) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST
done
}

lfs_verify() {
for name in bacon eggs pancakes
do
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "$1/$name", LFS_O_RDONLY) => 0;
    size = strlen("$name");
    for (int i = 0; i < $SIZE; i++) {
        lfs_file_read(&lfs, &file[0], buffer, size) => size;
        memcmp(buffer, "$name", size) => 0;
    }
    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST
done
}

echo "--- Single-process allocation test ---"
lfs_mkdir singleproc
lfs_alloc_singleproc singleproc
lfs_verify singleproc

echo "--- Multi-process allocation test ---"
lfs_mkdir multiproc
lfs_alloc_multiproc multiproc
lfs_verify multiproc
lfs_verify singleproc

echo "--- Single-process reuse test ---"
lfs_remove singleproc
lfs_mkdir singleprocreuse
lfs_alloc_singleproc singleprocreuse
lfs_verify singleprocreuse
lfs_verify multiproc

echo "--- Multi-process reuse test ---"
lfs_remove multiproc
lfs_mkdir multiprocreuse
lfs_alloc_singleproc multiprocreuse
lfs_verify multiprocreuse
lfs_verify singleprocreuse

echo "--- Cleanup ---"
lfs_remove multiprocreuse
lfs_remove singleprocreuse

echo "--- Exhaustion test ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "exhaustion", LFS_O_WRONLY | LFS_O_CREAT);
    size = strlen("exhaustion");
    memcpy(buffer, "exhaustion", size);
    lfs_file_write(&lfs, &file[0], buffer, size) => size;
    lfs_file_sync(&lfs, &file[0]) => 0;

    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    lfs_ssize_t res;
    while (true) {
        res = lfs_file_write(&lfs, &file[0], buffer, size);
        if (res < 0) {
            break;
        }

        res => size;
    }
    res => LFS_ERR_NOSPC;

    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "exhaustion", LFS_O_RDONLY);
    size = strlen("exhaustion");
    lfs_file_size(&lfs, &file[0]) => size;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "exhaustion", size) => 0;
    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Exhaustion wraparound test ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_remove(&lfs, "exhaustion") => 0;

    lfs_file_open(&lfs, &file[0], "padding", LFS_O_WRONLY | LFS_O_CREAT);
    size = strlen("buffering");
    memcpy(buffer, "buffering", size);
    for (int i = 0; i < $SIZE; i++) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_remove(&lfs, "padding") => 0;

    lfs_file_open(&lfs, &file[0], "exhaustion", LFS_O_WRONLY | LFS_O_CREAT);
    size = strlen("exhaustion");
    memcpy(buffer, "exhaustion", size);
    lfs_file_write(&lfs, &file[0], buffer, size) => size;
    lfs_file_sync(&lfs, &file[0]) => 0;

    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    lfs_ssize_t res;
    while (true) {
        res = lfs_file_write(&lfs, &file[0], buffer, size);
        if (res < 0) {
            break;
        }

        res => size;
    }
    res => LFS_ERR_NOSPC;

    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_file_open(&lfs, &file[0], "exhaustion", LFS_O_RDONLY);
    size = strlen("exhaustion");
    lfs_file_size(&lfs, &file[0]) => size;
    lfs_file_read(&lfs, &file[0], buffer, size) => size;
    memcmp(buffer, "exhaustion", size) => 0;
    lfs_file_close(&lfs, &file[0]) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Dir exhaustion test ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_remove(&lfs, "exhaustion") => 0;

    lfs_file_open(&lfs, &file[0], "exhaustion", LFS_O_WRONLY | LFS_O_CREAT);
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < (cfg.block_count-6)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    lfs_mkdir(&lfs, "exhaustiondir") => 0;
    lfs_remove(&lfs, "exhaustiondir") => 0;

    lfs_file_open(&lfs, &file[0], "exhaustion", LFS_O_WRONLY | LFS_O_APPEND);
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < (cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    lfs_mkdir(&lfs, "exhaustiondir") => LFS_ERR_NOSPC;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Chained dir exhaustion test ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_remove(&lfs, "exhaustion") => 0;

    lfs_file_open(&lfs, &file[0], "exhaustion", LFS_O_WRONLY | LFS_O_CREAT);
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < (cfg.block_count-24)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    for (int i = 0; i < 9; i++) {
        sprintf((char*)buffer, "dirwithanexhaustivelylongnameforpadding%d", i);
        lfs_mkdir(&lfs, (char*)buffer) => 0;
    }

    lfs_mkdir(&lfs, "exhaustiondir") => LFS_ERR_NOSPC;

    lfs_remove(&lfs, "exhaustion") => 0;
    lfs_file_open(&lfs, &file[0], "exhaustion", LFS_O_WRONLY | LFS_O_CREAT);
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < (cfg.block_count-26)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    lfs_mkdir(&lfs, "exhaustiondir") => 0;
    lfs_mkdir(&lfs, "exhaustiondir2") => LFS_ERR_NOSPC;
TEST

echo "--- Split dir test ---"
rm -rf blocks
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;

    // create one block whole for half a directory
    lfs_file_open(&lfs, &file[0], "bump", LFS_O_WRONLY | LFS_O_CREAT) => 0;
    lfs_file_write(&lfs, &file[0], (void*)"hi", 2) => 2;
    lfs_file_close(&lfs, &file[0]) => 0;

    lfs_file_open(&lfs, &file[0], "exhaustion", LFS_O_WRONLY | LFS_O_CREAT);
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < (cfg.block_count-6)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    // open hole
    lfs_remove(&lfs, "bump") => 0;

    lfs_mkdir(&lfs, "splitdir") => 0;
    lfs_file_open(&lfs, &file[0], "splitdir/bump",
            LFS_O_WRONLY | LFS_O_CREAT) => 0;
    lfs_file_write(&lfs, &file[0], buffer, size) => LFS_ERR_NOSPC;
    lfs_file_close(&lfs, &file[0]) => 0;

    lfs_unmount(&lfs) => 0;
TEST

echo "--- Outdated lookahead test ---"
rm -rf blocks
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;

    lfs_mount(&lfs, &cfg) => 0;

    // fill completely with two files
    lfs_file_open(&lfs, &file[0], "exhaustion1",
            LFS_O_WRONLY | LFS_O_CREAT) => 0;
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < ((cfg.block_count-4)/2)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    lfs_file_open(&lfs, &file[0], "exhaustion2",
            LFS_O_WRONLY | LFS_O_CREAT) => 0;
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < ((cfg.block_count-4+1)/2)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    // remount to force reset of lookahead
    lfs_unmount(&lfs) => 0;

    lfs_mount(&lfs, &cfg) => 0;

    // rewrite one file
    lfs_file_open(&lfs, &file[0], "exhaustion1",
            LFS_O_WRONLY | LFS_O_TRUNC) => 0;
    lfs_file_sync(&lfs, &file[0]) => 0;
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < ((cfg.block_count-4)/2)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    // rewrite second file, this requires lookahead does not
    // use old population
    lfs_file_open(&lfs, &file[0], "exhaustion2",
            LFS_O_WRONLY | LFS_O_TRUNC) => 0;
    lfs_file_sync(&lfs, &file[0]) => 0;
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < ((cfg.block_count-4+1)/2)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;
TEST

echo "--- Outdated lookahead and split dir test ---"
rm -rf blocks
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;

    lfs_mount(&lfs, &cfg) => 0;

    // fill completely with two files
    lfs_file_open(&lfs, &file[0], "exhaustion1",
            LFS_O_WRONLY | LFS_O_CREAT) => 0;
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < ((cfg.block_count-4)/2)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    lfs_file_open(&lfs, &file[0], "exhaustion2",
            LFS_O_WRONLY | LFS_O_CREAT) => 0;
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < ((cfg.block_count-4+1)/2)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    // remount to force reset of lookahead
    lfs_unmount(&lfs) => 0;

    lfs_mount(&lfs, &cfg) => 0;

    // rewrite one file with a hole of one block
    lfs_file_open(&lfs, &file[0], "exhaustion1",
            LFS_O_WRONLY | LFS_O_TRUNC) => 0;
    lfs_file_sync(&lfs, &file[0]) => 0;
    size = strlen("blahblahblahblah");
    memcpy(buffer, "blahblahblahblah", size);
    for (lfs_size_t i = 0;
            i < ((cfg.block_count-4)/2 - 1)*(cfg.block_size-8);
            i += size) {
        lfs_file_write(&lfs, &file[0], buffer, size) => size;
    }
    lfs_file_close(&lfs, &file[0]) => 0;

    // try to allocate a directory, should fail!
    lfs_mkdir(&lfs, "split") => LFS_ERR_NOSPC;

    // file should not fail
    lfs_file_open(&lfs, &file[0], "notasplit",
            LFS_O_WRONLY | LFS_O_CREAT) => 0;
    lfs_file_write(&lfs, &file[0], "hi", 2) => 2;
    lfs_file_close(&lfs, &file[0]) => 0;

    lfs_unmount(&lfs) => 0;
TEST

echo "--- Results ---"
tests/stats.py
