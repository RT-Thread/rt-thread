#!/bin/bash
set -eu

echo "=== Orphan tests ==="
rm -rf blocks
tests/test.py << TEST
    lfs_format(&lfs, &cfg) => 0;
TEST

echo "--- Orphan test ---"
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_mkdir(&lfs, "parent") => 0;
    lfs_mkdir(&lfs, "parent/orphan") => 0;
    lfs_mkdir(&lfs, "parent/child") => 0;
    lfs_remove(&lfs, "parent/orphan") => 0;
TEST
# remove most recent file, this should be the update to the previous
# linked-list entry and should orphan the child
rm -v blocks/8
tests/test.py << TEST
    lfs_mount(&lfs, &cfg) => 0;
    lfs_stat(&lfs, "parent/orphan", &info) => LFS_ERR_NOENT;
    unsigned before = 0;
    lfs_traverse(&lfs, test_count, &before) => 0;
    test_log("before", before);

    lfs_deorphan(&lfs) => 0;

    lfs_stat(&lfs, "parent/orphan", &info) => LFS_ERR_NOENT;
    unsigned after = 0;
    lfs_traverse(&lfs, test_count, &after) => 0;
    test_log("after", after);

    int diff = before - after;
    diff => 2;
    lfs_unmount(&lfs) => 0;
TEST

echo "--- Results ---"
tests/stats.py
