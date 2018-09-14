#!/bin/bash
set -eu

echo "=== Formatting tests ==="
rm -rf blocks

echo "--- Basic formatting ---"
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST

echo "--- Invalid superblocks ---"
ln -f -s /dev/zero blocks/0
ln -f -s /dev/zero blocks/1
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => LFS_ERR_CORRUPT;
TEST
rm blocks/0 blocks/1

echo "--- Basic mounting ---"
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Invalid mount ---"
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST
rm blocks/0 blocks/1
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => LFS_ERR_CORRUPT;
TEST

echo "--- Valid corrupt mount ---"
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST
rm blocks/0
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Results ---"
tests/stats.py
