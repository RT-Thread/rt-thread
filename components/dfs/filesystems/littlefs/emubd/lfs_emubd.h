/*
 * Block device emulated on standard files
 *
 * Copyright (c) 2017, Arm Limited. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef LFS_EMUBD_H
#define LFS_EMUBD_H

#include "lfs.h"
#include "lfs_util.h"

#ifdef __cplusplus
extern "C"
{
#endif


// Config options
#ifndef LFS_EMUBD_READ_SIZE
#define LFS_EMUBD_READ_SIZE 1
#endif

#ifndef LFS_EMUBD_PROG_SIZE
#define LFS_EMUBD_PROG_SIZE 1
#endif

#ifndef LFS_EMUBD_ERASE_SIZE
#define LFS_EMUBD_ERASE_SIZE 512
#endif

#ifndef LFS_EMUBD_TOTAL_SIZE
#define LFS_EMUBD_TOTAL_SIZE 524288
#endif


// The emu bd state
typedef struct lfs_emubd {
    char *path;
    char *child;

    struct {
        uint64_t read_count;
        uint64_t prog_count;
        uint64_t erase_count;
    } stats;

    struct {
        uint32_t read_size;
        uint32_t prog_size;
        uint32_t block_size;
        uint32_t block_count;
    } cfg;
} lfs_emubd_t;


// Create a block device using path for the directory to store blocks
int lfs_emubd_create(const struct lfs_config *cfg, const char *path);

// Clean up memory associated with emu block device
void lfs_emubd_destroy(const struct lfs_config *cfg);

// Read a block
int lfs_emubd_read(const struct lfs_config *cfg, lfs_block_t block,
        lfs_off_t off, void *buffer, lfs_size_t size);

// Program a block
//
// The block must have previously been erased.
int lfs_emubd_prog(const struct lfs_config *cfg, lfs_block_t block,
        lfs_off_t off, const void *buffer, lfs_size_t size);

// Erase a block
//
// A block must be erased before being programmed. The
// state of an erased block is undefined.
int lfs_emubd_erase(const struct lfs_config *cfg, lfs_block_t block);

// Sync the block device
int lfs_emubd_sync(const struct lfs_config *cfg);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
