#!/bin/bash
set -eu

echo "=== Corrupt tests ==="

NAMEMULT=64
FILEMULT=1

lfs_mktree() {
tests/test.py ${1:-} << TEST
    lfs_format(&lfs, &cfg) => 0;

    lfs_mount(&lfs, &cfg) => 0;
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < $NAMEMULT; j++) {
            buffer[j] = '0'+i;
        }
        buffer[$NAMEMULT] = '\0';
        lfs_mkdir(&lfs, (char*)buffer) => 0;

        buffer[$NAMEMULT] = '/';
        for (int j = 0; j < $NAMEMULT; j++) {
            buffer[j+$NAMEMULT+1] = '0'+i;
        }
        buffer[2*$NAMEMULT+1] = '\0';
        lfs_file_open(&lfs, &file[0], (char*)buffer,
                LFS_O_WRONLY | LFS_O_CREAT) => 0;
        
        size = $NAMEMULT;
        for (int j = 0; j < i*$FILEMULT; j++) {
            lfs_file_write(&lfs, &file[0], buffer, size) => size;
        }

        lfs_file_close(&lfs, &file[0]) => 0;
    }
    lfs_unmount(&lfs) => 0;
TEST
}

lfs_chktree() {
tests/test.py ${1:-} << TEST
    lfs_mount(&lfs, &cfg) => 0;
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < $NAMEMULT; j++) {
            buffer[j] = '0'+i;
        }
        buffer[$NAMEMULT] = '\0';
        lfs_stat(&lfs, (char*)buffer, &info) => 0;
        info.type => LFS_TYPE_DIR;

        buffer[$NAMEMULT] = '/';
        for (int j = 0; j < $NAMEMULT; j++) {
            buffer[j+$NAMEMULT+1] = '0'+i;
        }
        buffer[2*$NAMEMULT+1] = '\0';
        lfs_file_open(&lfs, &file[0], (char*)buffer, LFS_O_RDONLY) => 0;
        
        size = $NAMEMULT;
        for (int j = 0; j < i*$FILEMULT; j++) {
            lfs_file_read(&lfs, &file[0], rbuffer, size) => size;
            memcmp(buffer, rbuffer, size) => 0;
        }

        lfs_file_close(&lfs, &file[0]) => 0;
    }
    lfs_unmount(&lfs) => 0;
TEST
}

echo "--- Sanity check ---"
rm -rf blocks
lfs_mktree
lfs_chktree

echo "--- Block corruption ---"
for i in {0..33}
do 
    rm -rf blocks
    mkdir blocks
    ln -s /dev/zero blocks/$(printf '%x' $i)
    lfs_mktree
    lfs_chktree
done

echo "--- Block persistance ---"
for i in {0..33}
do 
    rm -rf blocks
    mkdir blocks
    lfs_mktree
    chmod a-w blocks/$(printf '%x' $i)
    lfs_mktree
    lfs_chktree
done

echo "--- Big region corruption ---"
rm -rf blocks
mkdir blocks
for i in {2..255}
do
    ln -s /dev/zero blocks/$(printf '%x' $i)
done
lfs_mktree
lfs_chktree

echo "--- Alternating corruption ---"
rm -rf blocks
mkdir blocks
for i in {2..511..2}
do
    ln -s /dev/zero blocks/$(printf '%x' $i)
done
lfs_mktree
lfs_chktree

echo "--- Results ---"
tests/stats.py
