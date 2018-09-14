/*
 * The little filesystem
 *
 * Copyright (c) 2017, Arm Limited. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "lfs.h"
#include "lfs_util.h"

#include <inttypes.h>


/// Caching block device operations ///
static int lfs_cache_read(lfs_t *lfs, lfs_cache_t *rcache,
        const lfs_cache_t *pcache, lfs_block_t block,
        lfs_off_t off, void *buffer, lfs_size_t size) {
    uint8_t *data = buffer;
    LFS_ASSERT(block < lfs->cfg->block_count);

    while (size > 0) {
        if (pcache && block == pcache->block && off >= pcache->off &&
                off < pcache->off + lfs->cfg->prog_size) {
            // is already in pcache?
            lfs_size_t diff = lfs_min(size,
                    lfs->cfg->prog_size - (off-pcache->off));
            memcpy(data, &pcache->buffer[off-pcache->off], diff);

            data += diff;
            off += diff;
            size -= diff;
            continue;
        }

        if (block == rcache->block && off >= rcache->off &&
                off < rcache->off + lfs->cfg->read_size) {
            // is already in rcache?
            lfs_size_t diff = lfs_min(size,
                    lfs->cfg->read_size - (off-rcache->off));
            memcpy(data, &rcache->buffer[off-rcache->off], diff);

            data += diff;
            off += diff;
            size -= diff;
            continue;
        }

        if (off % lfs->cfg->read_size == 0 && size >= lfs->cfg->read_size) {
            // bypass cache?
            lfs_size_t diff = size - (size % lfs->cfg->read_size);
            int err = lfs->cfg->read(lfs->cfg, block, off, data, diff);
            if (err) {
                return err;
            }

            data += diff;
            off += diff;
            size -= diff;
            continue;
        }

        // load to cache, first condition can no longer fail
        rcache->block = block;
        rcache->off = off - (off % lfs->cfg->read_size);
        int err = lfs->cfg->read(lfs->cfg, rcache->block,
                rcache->off, rcache->buffer, lfs->cfg->read_size);
        if (err) {
            return err;
        }
    }

    return 0;
}

static int lfs_cache_cmp(lfs_t *lfs, lfs_cache_t *rcache,
        const lfs_cache_t *pcache, lfs_block_t block,
        lfs_off_t off, const void *buffer, lfs_size_t size) {
    const uint8_t *data = buffer;

    for (lfs_off_t i = 0; i < size; i++) {
        uint8_t c;
        int err = lfs_cache_read(lfs, rcache, pcache,
                block, off+i, &c, 1);
        if (err) {
            return err;
        }

        if (c != data[i]) {
            return false;
        }
    }

    return true;
}

static int lfs_cache_crc(lfs_t *lfs, lfs_cache_t *rcache,
        const lfs_cache_t *pcache, lfs_block_t block,
        lfs_off_t off, lfs_size_t size, uint32_t *crc) {
    for (lfs_off_t i = 0; i < size; i++) {
        uint8_t c;
        int err = lfs_cache_read(lfs, rcache, pcache,
                block, off+i, &c, 1);
        if (err) {
            return err;
        }

        lfs_crc(crc, &c, 1);
    }

    return 0;
}

static inline void lfs_cache_drop(lfs_t *lfs, lfs_cache_t *rcache) {
    // do not zero, cheaper if cache is readonly or only going to be
    // written with identical data (during relocates)
    (void)lfs;
    rcache->block = 0xffffffff;
}

static inline void lfs_cache_zero(lfs_t *lfs, lfs_cache_t *pcache) {
    // zero to avoid information leak
    memset(pcache->buffer, 0xff, lfs->cfg->prog_size);
    pcache->block = 0xffffffff;
}

static int lfs_cache_flush(lfs_t *lfs,
        lfs_cache_t *pcache, lfs_cache_t *rcache) {
    if (pcache->block != 0xffffffff) {
        int err = lfs->cfg->prog(lfs->cfg, pcache->block,
                pcache->off, pcache->buffer, lfs->cfg->prog_size);
        if (err) {
            return err;
        }

        if (rcache) {
            int res = lfs_cache_cmp(lfs, rcache, NULL, pcache->block,
                    pcache->off, pcache->buffer, lfs->cfg->prog_size);
            if (res < 0) {
                return res;
            }

            if (!res) {
                return LFS_ERR_CORRUPT;
            }
        }

        lfs_cache_zero(lfs, pcache);
    }

    return 0;
}

static int lfs_cache_prog(lfs_t *lfs, lfs_cache_t *pcache,
        lfs_cache_t *rcache, lfs_block_t block,
        lfs_off_t off, const void *buffer, lfs_size_t size) {
    const uint8_t *data = buffer;
    LFS_ASSERT(block < lfs->cfg->block_count);

    while (size > 0) {
        if (block == pcache->block && off >= pcache->off &&
                off < pcache->off + lfs->cfg->prog_size) {
            // is already in pcache?
            lfs_size_t diff = lfs_min(size,
                    lfs->cfg->prog_size - (off-pcache->off));
            memcpy(&pcache->buffer[off-pcache->off], data, diff);

            data += diff;
            off += diff;
            size -= diff;

            if (off % lfs->cfg->prog_size == 0) {
                // eagerly flush out pcache if we fill up
                int err = lfs_cache_flush(lfs, pcache, rcache);
                if (err) {
                    return err;
                }
            }

            continue;
        }

        // pcache must have been flushed, either by programming and
        // entire block or manually flushing the pcache
        LFS_ASSERT(pcache->block == 0xffffffff);

        if (off % lfs->cfg->prog_size == 0 &&
                size >= lfs->cfg->prog_size) {
            // bypass pcache?
            lfs_size_t diff = size - (size % lfs->cfg->prog_size);
            int err = lfs->cfg->prog(lfs->cfg, block, off, data, diff);
            if (err) {
                return err;
            }

            if (rcache) {
                int res = lfs_cache_cmp(lfs, rcache, NULL,
                        block, off, data, diff);
                if (res < 0) {
                    return res;
                }

                if (!res) {
                    return LFS_ERR_CORRUPT;
                }
            }

            data += diff;
            off += diff;
            size -= diff;
            continue;
        }

        // prepare pcache, first condition can no longer fail
        pcache->block = block;
        pcache->off = off - (off % lfs->cfg->prog_size);
    }

    return 0;
}


/// General lfs block device operations ///
static int lfs_bd_read(lfs_t *lfs, lfs_block_t block,
        lfs_off_t off, void *buffer, lfs_size_t size) {
    // if we ever do more than writes to alternating pairs,
    // this may need to consider pcache
    return lfs_cache_read(lfs, &lfs->rcache, NULL,
            block, off, buffer, size);
}

static int lfs_bd_prog(lfs_t *lfs, lfs_block_t block,
        lfs_off_t off, const void *buffer, lfs_size_t size) {
    return lfs_cache_prog(lfs, &lfs->pcache, NULL,
            block, off, buffer, size);
}

static int lfs_bd_cmp(lfs_t *lfs, lfs_block_t block,
        lfs_off_t off, const void *buffer, lfs_size_t size) {
    return lfs_cache_cmp(lfs, &lfs->rcache, NULL, block, off, buffer, size);
}

static int lfs_bd_crc(lfs_t *lfs, lfs_block_t block,
        lfs_off_t off, lfs_size_t size, uint32_t *crc) {
    return lfs_cache_crc(lfs, &lfs->rcache, NULL, block, off, size, crc);
}

static int lfs_bd_erase(lfs_t *lfs, lfs_block_t block) {
    return lfs->cfg->erase(lfs->cfg, block);
}

static int lfs_bd_sync(lfs_t *lfs) {
    lfs_cache_drop(lfs, &lfs->rcache);

    int err = lfs_cache_flush(lfs, &lfs->pcache, NULL);
    if (err) {
        return err;
    }

    return lfs->cfg->sync(lfs->cfg);
}


/// Internal operations predeclared here ///
int lfs_traverse(lfs_t *lfs, int (*cb)(void*, lfs_block_t), void *data);
static int lfs_pred(lfs_t *lfs, const lfs_block_t dir[2], lfs_dir_t *pdir);
static int lfs_parent(lfs_t *lfs, const lfs_block_t dir[2],
        lfs_dir_t *parent, lfs_entry_t *entry);
static int lfs_moved(lfs_t *lfs, const void *e);
static int lfs_relocate(lfs_t *lfs,
        const lfs_block_t oldpair[2], const lfs_block_t newpair[2]);
int lfs_deorphan(lfs_t *lfs);


/// Block allocator ///
static int lfs_alloc_lookahead(void *p, lfs_block_t block) {
    lfs_t *lfs = p;

    lfs_block_t off = ((block - lfs->free.off)
            + lfs->cfg->block_count) % lfs->cfg->block_count;

    if (off < lfs->free.size) {
        lfs->free.buffer[off / 32] |= 1U << (off % 32);
    }

    return 0;
}

static int lfs_alloc(lfs_t *lfs, lfs_block_t *block) {
    while (true) {
        while (lfs->free.i != lfs->free.size) {
            lfs_block_t off = lfs->free.i;
            lfs->free.i += 1;
            lfs->free.ack -= 1;

            if (!(lfs->free.buffer[off / 32] & (1U << (off % 32)))) {
                // found a free block
                *block = (lfs->free.off + off) % lfs->cfg->block_count;

                // eagerly find next off so an alloc ack can
                // discredit old lookahead blocks
                while (lfs->free.i != lfs->free.size &&
                        (lfs->free.buffer[lfs->free.i / 32]
                            & (1U << (lfs->free.i % 32)))) {
                    lfs->free.i += 1;
                    lfs->free.ack -= 1;
                }

                return 0;
            }
        }

        // check if we have looked at all blocks since last ack
        if (lfs->free.ack == 0) {
            LFS_WARN("No more free space %" PRIu32,
                    lfs->free.i + lfs->free.off);
            return LFS_ERR_NOSPC;
        }

        lfs->free.off = (lfs->free.off + lfs->free.size)
                % lfs->cfg->block_count;
        lfs->free.size = lfs_min(lfs->cfg->lookahead, lfs->free.ack);
        lfs->free.i = 0;

        // find mask of free blocks from tree
        memset(lfs->free.buffer, 0, lfs->cfg->lookahead/8);
        int err = lfs_traverse(lfs, lfs_alloc_lookahead, lfs);
        if (err) {
            return err;
        }
    }
}

static void lfs_alloc_ack(lfs_t *lfs) {
    lfs->free.ack = lfs->cfg->block_count;
}


/// Endian swapping functions ///
static void lfs_dir_fromle32(struct lfs_disk_dir *d) {
    d->rev     = lfs_fromle32(d->rev);
    d->size    = lfs_fromle32(d->size);
    d->tail[0] = lfs_fromle32(d->tail[0]);
    d->tail[1] = lfs_fromle32(d->tail[1]);
}

static void lfs_dir_tole32(struct lfs_disk_dir *d) {
    d->rev     = lfs_tole32(d->rev);
    d->size    = lfs_tole32(d->size);
    d->tail[0] = lfs_tole32(d->tail[0]);
    d->tail[1] = lfs_tole32(d->tail[1]);
}

static void lfs_entry_fromle32(struct lfs_disk_entry *d) {
    d->u.dir[0] = lfs_fromle32(d->u.dir[0]);
    d->u.dir[1] = lfs_fromle32(d->u.dir[1]);
}

static void lfs_entry_tole32(struct lfs_disk_entry *d) {
    d->u.dir[0] = lfs_tole32(d->u.dir[0]);
    d->u.dir[1] = lfs_tole32(d->u.dir[1]);
}

static void lfs_superblock_fromle32(struct lfs_disk_superblock *d) {
    d->root[0]     = lfs_fromle32(d->root[0]);
    d->root[1]     = lfs_fromle32(d->root[1]);
    d->block_size  = lfs_fromle32(d->block_size);
    d->block_count = lfs_fromle32(d->block_count);
    d->version     = lfs_fromle32(d->version);
}

static void lfs_superblock_tole32(struct lfs_disk_superblock *d) {
    d->root[0]     = lfs_tole32(d->root[0]);
    d->root[1]     = lfs_tole32(d->root[1]);
    d->block_size  = lfs_tole32(d->block_size);
    d->block_count = lfs_tole32(d->block_count);
    d->version     = lfs_tole32(d->version);
}


/// Metadata pair and directory operations ///
static inline void lfs_pairswap(lfs_block_t pair[2]) {
    lfs_block_t t = pair[0];
    pair[0] = pair[1];
    pair[1] = t;
}

static inline bool lfs_pairisnull(const lfs_block_t pair[2]) {
    return pair[0] == 0xffffffff || pair[1] == 0xffffffff;
}

static inline int lfs_paircmp(
        const lfs_block_t paira[2],
        const lfs_block_t pairb[2]) {
    return !(paira[0] == pairb[0] || paira[1] == pairb[1] ||
             paira[0] == pairb[1] || paira[1] == pairb[0]);
}

static inline bool lfs_pairsync(
        const lfs_block_t paira[2],
        const lfs_block_t pairb[2]) {
    return (paira[0] == pairb[0] && paira[1] == pairb[1]) ||
           (paira[0] == pairb[1] && paira[1] == pairb[0]);
}

static inline lfs_size_t lfs_entry_size(const lfs_entry_t *entry) {
    return 4 + entry->d.elen + entry->d.alen + entry->d.nlen;
}

static int lfs_dir_alloc(lfs_t *lfs, lfs_dir_t *dir) {
    // allocate pair of dir blocks
    for (int i = 0; i < 2; i++) {
        int err = lfs_alloc(lfs, &dir->pair[i]);
        if (err) {
            return err;
        }
    }

    // rather than clobbering one of the blocks we just pretend
    // the revision may be valid
    int err = lfs_bd_read(lfs, dir->pair[0], 0, &dir->d.rev, 4);
    if (err && err != LFS_ERR_CORRUPT) {
        return err;
    }

    if (err != LFS_ERR_CORRUPT) {
        dir->d.rev = lfs_fromle32(dir->d.rev);
    }

    // set defaults
    dir->d.rev += 1;
    dir->d.size = sizeof(dir->d)+4;
    dir->d.tail[0] = 0xffffffff;
    dir->d.tail[1] = 0xffffffff;
    dir->off = sizeof(dir->d);

    // don't write out yet, let caller take care of that
    return 0;
}

static int lfs_dir_fetch(lfs_t *lfs,
        lfs_dir_t *dir, const lfs_block_t pair[2]) {
    // copy out pair, otherwise may be aliasing dir
    const lfs_block_t tpair[2] = {pair[0], pair[1]};
    bool valid = false;

    // check both blocks for the most recent revision
    for (int i = 0; i < 2; i++) {
        struct lfs_disk_dir test;
        int err = lfs_bd_read(lfs, tpair[i], 0, &test, sizeof(test));
        lfs_dir_fromle32(&test);
        if (err) {
            if (err == LFS_ERR_CORRUPT) {
                continue;
            }
            return err;
        }

        if (valid && lfs_scmp(test.rev, dir->d.rev) < 0) {
            continue;
        }

        if ((0x7fffffff & test.size) < sizeof(test)+4 ||
            (0x7fffffff & test.size) > lfs->cfg->block_size) {
            continue;
        }

        uint32_t crc = 0xffffffff;
        lfs_dir_tole32(&test);
        lfs_crc(&crc, &test, sizeof(test));
        lfs_dir_fromle32(&test);
        err = lfs_bd_crc(lfs, tpair[i], sizeof(test),
                (0x7fffffff & test.size) - sizeof(test), &crc);
        if (err) {
            if (err == LFS_ERR_CORRUPT) {
                continue;
            }
            return err;
        }

        if (crc != 0) {
            continue;
        }

        valid = true;

        // setup dir in case it's valid
        dir->pair[0] = tpair[(i+0) % 2];
        dir->pair[1] = tpair[(i+1) % 2];
        dir->off = sizeof(dir->d);
        dir->d = test;
    }

    if (!valid) {
        LFS_ERROR("Corrupted dir pair at %" PRIu32 " %" PRIu32 ,
                tpair[0], tpair[1]);
        return LFS_ERR_CORRUPT;
    }

    return 0;
}

struct lfs_region {
    lfs_off_t oldoff;
    lfs_size_t oldlen;
    const void *newdata;
    lfs_size_t newlen;
};

static int lfs_dir_commit(lfs_t *lfs, lfs_dir_t *dir,
        const struct lfs_region *regions, int count) {
    // increment revision count
    dir->d.rev += 1;

    // keep pairs in order such that pair[0] is most recent
    lfs_pairswap(dir->pair);
    for (int i = 0; i < count; i++) {
        dir->d.size += regions[i].newlen - regions[i].oldlen;
    }

    const lfs_block_t oldpair[2] = {dir->pair[0], dir->pair[1]};
    bool relocated = false;

    while (true) {
        if (true) {
            int err = lfs_bd_erase(lfs, dir->pair[0]);
            if (err) {
                if (err == LFS_ERR_CORRUPT) {
                    goto relocate;
                }
                return err;
            }

            uint32_t crc = 0xffffffff;
            lfs_dir_tole32(&dir->d);
            lfs_crc(&crc, &dir->d, sizeof(dir->d));
            err = lfs_bd_prog(lfs, dir->pair[0], 0, &dir->d, sizeof(dir->d));
            lfs_dir_fromle32(&dir->d);
            if (err) {
                if (err == LFS_ERR_CORRUPT) {
                    goto relocate;
                }
                return err;
            }

            int i = 0;
            lfs_off_t oldoff = sizeof(dir->d);
            lfs_off_t newoff = sizeof(dir->d);
            while (newoff < (0x7fffffff & dir->d.size)-4) {
                if (i < count && regions[i].oldoff == oldoff) {
                    lfs_crc(&crc, regions[i].newdata, regions[i].newlen);
                    err = lfs_bd_prog(lfs, dir->pair[0],
                            newoff, regions[i].newdata, regions[i].newlen);
                    if (err) {
                        if (err == LFS_ERR_CORRUPT) {
                            goto relocate;
                        }
                        return err;
                    }

                    oldoff += regions[i].oldlen;
                    newoff += regions[i].newlen;
                    i += 1;
                } else {
                    uint8_t data;
                    err = lfs_bd_read(lfs, oldpair[1], oldoff, &data, 1);
                    if (err) {
                        return err;
                    }

                    lfs_crc(&crc, &data, 1);
                    err = lfs_bd_prog(lfs, dir->pair[0], newoff, &data, 1);
                    if (err) {
                        if (err == LFS_ERR_CORRUPT) {
                            goto relocate;
                        }
                        return err;
                    }

                    oldoff += 1;
                    newoff += 1;
                }
            }

            crc = lfs_tole32(crc);
            err = lfs_bd_prog(lfs, dir->pair[0], newoff, &crc, 4);
            crc = lfs_fromle32(crc);
            if (err) {
                if (err == LFS_ERR_CORRUPT) {
                    goto relocate;
                }
                return err;
            }

            err = lfs_bd_sync(lfs);
            if (err) {
                if (err == LFS_ERR_CORRUPT) {
                    goto relocate;
                }
                return err;
            }

            // successful commit, check checksum to make sure
            uint32_t ncrc = 0xffffffff;
            err = lfs_bd_crc(lfs, dir->pair[0], 0,
                    (0x7fffffff & dir->d.size)-4, &ncrc);
            if (err) {
                return err;
            }

            if (ncrc != crc) {
                goto relocate;
            }
        }

        break;
relocate:
        //commit was corrupted
        LFS_DEBUG("Bad block at %" PRIu32, dir->pair[0]);

        // drop caches and prepare to relocate block
        relocated = true;
        lfs_cache_drop(lfs, &lfs->pcache);

        // can't relocate superblock, filesystem is now frozen
        if (lfs_paircmp(oldpair, (const lfs_block_t[2]){0, 1}) == 0) {
            LFS_WARN("Superblock %" PRIu32 " has become unwritable",
                    oldpair[0]);
            return LFS_ERR_CORRUPT;
        }

        // relocate half of pair
        int err = lfs_alloc(lfs, &dir->pair[0]);
        if (err) {
            return err;
        }
    }

    if (relocated) {
        // update references if we relocated
        LFS_DEBUG("Relocating %" PRIu32 " %" PRIu32 " to %" PRIu32 " %" PRIu32,
                oldpair[0], oldpair[1], dir->pair[0], dir->pair[1]);
        int err = lfs_relocate(lfs, oldpair, dir->pair);
        if (err) {
            return err;
        }
    }

    // shift over any directories that are affected
    for (lfs_dir_t *d = lfs->dirs; d; d = d->next) {
        if (lfs_paircmp(d->pair, dir->pair) == 0) {
            d->pair[0] = dir->pair[0];
            d->pair[1] = dir->pair[1];
        }
    }

    return 0;
}

static int lfs_dir_update(lfs_t *lfs, lfs_dir_t *dir,
        lfs_entry_t *entry, const void *data) {
    lfs_entry_tole32(&entry->d);
    int err = lfs_dir_commit(lfs, dir, (struct lfs_region[]){
            {entry->off, sizeof(entry->d), &entry->d, sizeof(entry->d)},
            {entry->off+sizeof(entry->d), entry->d.nlen, data, entry->d.nlen}
        }, data ? 2 : 1);
    lfs_entry_fromle32(&entry->d);
    return err;
}

static int lfs_dir_append(lfs_t *lfs, lfs_dir_t *dir,
        lfs_entry_t *entry, const void *data) {
    // check if we fit, if top bit is set we do not and move on
    while (true) {
        if (dir->d.size + lfs_entry_size(entry) <= lfs->cfg->block_size) {
            entry->off = dir->d.size - 4;

            lfs_entry_tole32(&entry->d);
            int err = lfs_dir_commit(lfs, dir, (struct lfs_region[]){
                    {entry->off, 0, &entry->d, sizeof(entry->d)},
                    {entry->off, 0, data, entry->d.nlen}
                }, 2);
            lfs_entry_fromle32(&entry->d);
            return err;
        }

        // we need to allocate a new dir block
        if (!(0x80000000 & dir->d.size)) {
            lfs_dir_t olddir = *dir;
            int err = lfs_dir_alloc(lfs, dir);
            if (err) {
                return err;
            }

            dir->d.tail[0] = olddir.d.tail[0];
            dir->d.tail[1] = olddir.d.tail[1];
            entry->off = dir->d.size - 4;
            lfs_entry_tole32(&entry->d);
            err = lfs_dir_commit(lfs, dir, (struct lfs_region[]){
                    {entry->off, 0, &entry->d, sizeof(entry->d)},
                    {entry->off, 0, data, entry->d.nlen}
                }, 2);
            lfs_entry_fromle32(&entry->d);
            if (err) {
                return err;
            }

            olddir.d.size |= 0x80000000;
            olddir.d.tail[0] = dir->pair[0];
            olddir.d.tail[1] = dir->pair[1];
            return lfs_dir_commit(lfs, &olddir, NULL, 0);
        }

        int err = lfs_dir_fetch(lfs, dir, dir->d.tail);
        if (err) {
            return err;
        }
    }
}

static int lfs_dir_remove(lfs_t *lfs, lfs_dir_t *dir, lfs_entry_t *entry) {
    // check if we should just drop the directory block
    if ((dir->d.size & 0x7fffffff) == sizeof(dir->d)+4
            + lfs_entry_size(entry)) {
        lfs_dir_t pdir;
        int res = lfs_pred(lfs, dir->pair, &pdir);
        if (res < 0) {
            return res;
        }

        if (pdir.d.size & 0x80000000) {
            pdir.d.size &= dir->d.size | 0x7fffffff;
            pdir.d.tail[0] = dir->d.tail[0];
            pdir.d.tail[1] = dir->d.tail[1];
            return lfs_dir_commit(lfs, &pdir, NULL, 0);
        }
    }

    // shift out the entry
    int err = lfs_dir_commit(lfs, dir, (struct lfs_region[]){
            {entry->off, lfs_entry_size(entry), NULL, 0},
        }, 1);
    if (err) {
        return err;
    }

    // shift over any files/directories that are affected
    for (lfs_file_t *f = lfs->files; f; f = f->next) {
        if (lfs_paircmp(f->pair, dir->pair) == 0) {
            if (f->poff == entry->off) {
                f->pair[0] = 0xffffffff;
                f->pair[1] = 0xffffffff;
            } else if (f->poff > entry->off) {
                f->poff -= lfs_entry_size(entry);
            }
        }
    }

    for (lfs_dir_t *d = lfs->dirs; d; d = d->next) {
        if (lfs_paircmp(d->pair, dir->pair) == 0) {
            if (d->off > entry->off) {
                d->off -= lfs_entry_size(entry);
                d->pos -= lfs_entry_size(entry);
            }
        }
    }

    return 0;
}

static int lfs_dir_next(lfs_t *lfs, lfs_dir_t *dir, lfs_entry_t *entry) {
    while (dir->off + sizeof(entry->d) > (0x7fffffff & dir->d.size)-4) {
        if (!(0x80000000 & dir->d.size)) {
            entry->off = dir->off;
            return LFS_ERR_NOENT;
        }

        int err = lfs_dir_fetch(lfs, dir, dir->d.tail);
        if (err) {
            return err;
        }

        dir->off = sizeof(dir->d);
        dir->pos += sizeof(dir->d) + 4;
    }

    int err = lfs_bd_read(lfs, dir->pair[0], dir->off,
            &entry->d, sizeof(entry->d));
    lfs_entry_fromle32(&entry->d);
    if (err) {
        return err;
    }

    entry->off = dir->off;
    dir->off += lfs_entry_size(entry);
    dir->pos += lfs_entry_size(entry);
    return 0;
}

static int lfs_dir_find(lfs_t *lfs, lfs_dir_t *dir,
        lfs_entry_t *entry, const char **path) {
    const char *pathname = *path;
    size_t pathlen;
    entry->d.type = LFS_TYPE_DIR;
    entry->d.elen = sizeof(entry->d) - 4;
    entry->d.alen = 0;
    entry->d.nlen = 0;
    entry->d.u.dir[0] = lfs->root[0];
    entry->d.u.dir[1] = lfs->root[1];

    while (true) {
nextname:
        // skip slashes
        pathname += strspn(pathname, "/");
        pathlen = strcspn(pathname, "/");

        // skip '.' and root '..'
        if ((pathlen == 1 && memcmp(pathname, ".", 1) == 0) ||
            (pathlen == 2 && memcmp(pathname, "..", 2) == 0)) {
            pathname += pathlen;
            goto nextname;
        }

        // skip if matched by '..' in name
        const char *suffix = pathname + pathlen;
        size_t sufflen;
        int depth = 1;
        while (true) {
            suffix += strspn(suffix, "/");
            sufflen = strcspn(suffix, "/");
            if (sufflen == 0) {
                break;
            }

            if (sufflen == 2 && memcmp(suffix, "..", 2) == 0) {
                depth -= 1;
                if (depth == 0) {
                    pathname = suffix + sufflen;
                    goto nextname;
                }
            } else {
                depth += 1;
            }

            suffix += sufflen;
        }

        // found path
        if (pathname[0] == '\0') {
            return 0;
        }

        // update what we've found
        *path = pathname;

        // continue on if we hit a directory
        if (entry->d.type != LFS_TYPE_DIR) {
            return LFS_ERR_NOTDIR;
        }

        int err = lfs_dir_fetch(lfs, dir, entry->d.u.dir);
        if (err) {
            return err;
        }

        // find entry matching name
        while (true) {
            err = lfs_dir_next(lfs, dir, entry);
            if (err) {
                return err;
            }

            if (((0x7f & entry->d.type) != LFS_TYPE_REG &&
                 (0x7f & entry->d.type) != LFS_TYPE_DIR) ||
                entry->d.nlen != pathlen) {
                continue;
            }

            int res = lfs_bd_cmp(lfs, dir->pair[0],
                    entry->off + 4+entry->d.elen+entry->d.alen,
                    pathname, pathlen);
            if (res < 0) {
                return res;
            }

            // found match
            if (res) {
                break;
            }
        }

        // check that entry has not been moved
        if (entry->d.type & 0x80) {
            int moved = lfs_moved(lfs, &entry->d.u);
            if (moved < 0 || moved) {
                return (moved < 0) ? moved : LFS_ERR_NOENT;
            }

            entry->d.type &= ~0x80;
        }

        // to next name
        pathname += pathlen;
    }
}


/// Top level directory operations ///
int lfs_mkdir(lfs_t *lfs, const char *path) {
    // deorphan if we haven't yet, needed at most once after poweron
    if (!lfs->deorphaned) {
        int err = lfs_deorphan(lfs);
        if (err) {
            return err;
        }
    }

    // fetch parent directory
    lfs_dir_t cwd;
    lfs_entry_t entry;
    int err = lfs_dir_find(lfs, &cwd, &entry, &path);
    if (err != LFS_ERR_NOENT || strchr(path, '/') != NULL) {
        return err ? err : LFS_ERR_EXIST;
    }

    // build up new directory
    lfs_alloc_ack(lfs);

    lfs_dir_t dir;
    err = lfs_dir_alloc(lfs, &dir);
    if (err) {
        return err;
    }
    dir.d.tail[0] = cwd.d.tail[0];
    dir.d.tail[1] = cwd.d.tail[1];

    err = lfs_dir_commit(lfs, &dir, NULL, 0);
    if (err) {
        return err;
    }

    entry.d.type = LFS_TYPE_DIR;
    entry.d.elen = sizeof(entry.d) - 4;
    entry.d.alen = 0;
    entry.d.nlen = strlen(path);
    entry.d.u.dir[0] = dir.pair[0];
    entry.d.u.dir[1] = dir.pair[1];

    cwd.d.tail[0] = dir.pair[0];
    cwd.d.tail[1] = dir.pair[1];

    err = lfs_dir_append(lfs, &cwd, &entry, path);
    if (err) {
        return err;
    }

    lfs_alloc_ack(lfs);
    return 0;
}

int lfs_dir_open(lfs_t *lfs, lfs_dir_t *dir, const char *path) {
    dir->pair[0] = lfs->root[0];
    dir->pair[1] = lfs->root[1];

    lfs_entry_t entry;
    int err = lfs_dir_find(lfs, dir, &entry, &path);
    if (err) {
        return err;
    } else if (entry.d.type != LFS_TYPE_DIR) {
        return LFS_ERR_NOTDIR;
    }

    err = lfs_dir_fetch(lfs, dir, entry.d.u.dir);
    if (err) {
        return err;
    }

    // setup head dir
    // special offset for '.' and '..'
    dir->head[0] = dir->pair[0];
    dir->head[1] = dir->pair[1];
    dir->pos = sizeof(dir->d) - 2;
    dir->off = sizeof(dir->d);

    // add to list of directories
    dir->next = lfs->dirs;
    lfs->dirs = dir;

    return 0;
}

int lfs_dir_close(lfs_t *lfs, lfs_dir_t *dir) {
    // remove from list of directories
    for (lfs_dir_t **p = &lfs->dirs; *p; p = &(*p)->next) {
        if (*p == dir) {
            *p = dir->next;
            break;
        }
    }

    return 0;
}

int lfs_dir_read(lfs_t *lfs, lfs_dir_t *dir, struct lfs_info *info) {
    memset(info, 0, sizeof(*info));

    // special offset for '.' and '..'
    if (dir->pos == sizeof(dir->d) - 2) {
        info->type = LFS_TYPE_DIR;
        strcpy(info->name, ".");
        dir->pos += 1;
        return 1;
    } else if (dir->pos == sizeof(dir->d) - 1) {
        info->type = LFS_TYPE_DIR;
        strcpy(info->name, "..");
        dir->pos += 1;
        return 1;
    }

    lfs_entry_t entry;
    while (true) {
        int err = lfs_dir_next(lfs, dir, &entry);
        if (err) {
            return (err == LFS_ERR_NOENT) ? 0 : err;
        }

        if ((0x7f & entry.d.type) != LFS_TYPE_REG &&
            (0x7f & entry.d.type) != LFS_TYPE_DIR) {
            continue;
        }

        // check that entry has not been moved
        if (entry.d.type & 0x80) {
            int moved = lfs_moved(lfs, &entry.d.u);
            if (moved < 0) {
                return moved;
            }

            if (moved) {
                continue;
            }

            entry.d.type &= ~0x80;
        }

        break;
    }

    info->type = entry.d.type;
    if (info->type == LFS_TYPE_REG) {
        info->size = entry.d.u.file.size;
    }

    int err = lfs_bd_read(lfs, dir->pair[0],
            entry.off + 4+entry.d.elen+entry.d.alen,
            info->name, entry.d.nlen);
    if (err) {
        return err;
    }

    return 1;
}

int lfs_dir_seek(lfs_t *lfs, lfs_dir_t *dir, lfs_off_t off) {
    // simply walk from head dir
    int err = lfs_dir_rewind(lfs, dir);
    if (err) {
        return err;
    }
    dir->pos = off;

    while (off > (0x7fffffff & dir->d.size)) {
        off -= 0x7fffffff & dir->d.size;
        if (!(0x80000000 & dir->d.size)) {
            return LFS_ERR_INVAL;
        }

        err = lfs_dir_fetch(lfs, dir, dir->d.tail);
        if (err) {
            return err;
        }
    }

    dir->off = off;
    return 0;
}

lfs_soff_t lfs_dir_tell(lfs_t *lfs, lfs_dir_t *dir) {
    (void)lfs;
    return dir->pos;
}

int lfs_dir_rewind(lfs_t *lfs, lfs_dir_t *dir) {
    // reload the head dir
    int err = lfs_dir_fetch(lfs, dir, dir->head);
    if (err) {
        return err;
    }

    dir->pair[0] = dir->head[0];
    dir->pair[1] = dir->head[1];
    dir->pos = sizeof(dir->d) - 2;
    dir->off = sizeof(dir->d);
    return 0;
}


/// File index list operations ///
static int lfs_ctz_index(lfs_t *lfs, lfs_off_t *off) {
    lfs_off_t size = *off;
    lfs_off_t b = lfs->cfg->block_size - 2*4;
    lfs_off_t i = size / b;
    if (i == 0) {
        return 0;
    }

    i = (size - 4*(lfs_popc(i-1)+2)) / b;
    *off = size - b*i - 4*lfs_popc(i);
    return i;
}

static int lfs_ctz_find(lfs_t *lfs,
        lfs_cache_t *rcache, const lfs_cache_t *pcache,
        lfs_block_t head, lfs_size_t size,
        lfs_size_t pos, lfs_block_t *block, lfs_off_t *off) {
    if (size == 0) {
        *block = 0xffffffff;
        *off = 0;
        return 0;
    }

    lfs_off_t current = lfs_ctz_index(lfs, &(lfs_off_t){size-1});
    lfs_off_t target = lfs_ctz_index(lfs, &pos);

    while (current > target) {
        lfs_size_t skip = lfs_min(
                lfs_npw2(current-target+1) - 1,
                lfs_ctz(current));

        int err = lfs_cache_read(lfs, rcache, pcache, head, 4*skip, &head, 4);
        head = lfs_fromle32(head);
        if (err) {
            return err;
        }

        LFS_ASSERT(head >= 2 && head <= lfs->cfg->block_count);
        current -= 1 << skip;
    }

    *block = head;
    *off = pos;
    return 0;
}

static int lfs_ctz_extend(lfs_t *lfs,
        lfs_cache_t *rcache, lfs_cache_t *pcache,
        lfs_block_t head, lfs_size_t size,
        lfs_block_t *block, lfs_off_t *off) {
    while (true) {
        // go ahead and grab a block
        lfs_block_t nblock;
        int err = lfs_alloc(lfs, &nblock);
        if (err) {
            return err;
        }
        LFS_ASSERT(nblock >= 2 && nblock <= lfs->cfg->block_count);

        if (true) {
            err = lfs_bd_erase(lfs, nblock);
            if (err) {
                if (err == LFS_ERR_CORRUPT) {
                    goto relocate;
                }
                return err;
            }

            if (size == 0) {
                *block = nblock;
                *off = 0;
                return 0;
            }

            size -= 1;
            lfs_off_t index = lfs_ctz_index(lfs, &size);
            size += 1;

            // just copy out the last block if it is incomplete
            if (size != lfs->cfg->block_size) {
                for (lfs_off_t i = 0; i < size; i++) {
                    uint8_t data;
                    err = lfs_cache_read(lfs, rcache, NULL,
                            head, i, &data, 1);
                    if (err) {
                        return err;
                    }

                    err = lfs_cache_prog(lfs, pcache, rcache,
                            nblock, i, &data, 1);
                    if (err) {
                        if (err == LFS_ERR_CORRUPT) {
                            goto relocate;
                        }
                        return err;
                    }
                }

                *block = nblock;
                *off = size;
                return 0;
            }

            // append block
            index += 1;
            lfs_size_t skips = lfs_ctz(index) + 1;

            for (lfs_off_t i = 0; i < skips; i++) {
                head = lfs_tole32(head);
                err = lfs_cache_prog(lfs, pcache, rcache,
                        nblock, 4*i, &head, 4);
                head = lfs_fromle32(head);
                if (err) {
                    if (err == LFS_ERR_CORRUPT) {
                        goto relocate;
                    }
                    return err;
                }

                if (i != skips-1) {
                    err = lfs_cache_read(lfs, rcache, NULL,
                            head, 4*i, &head, 4);
                    head = lfs_fromle32(head);
                    if (err) {
                        return err;
                    }
                }

                LFS_ASSERT(head >= 2 && head <= lfs->cfg->block_count);
            }

            *block = nblock;
            *off = 4*skips;
            return 0;
        }

relocate:
        LFS_DEBUG("Bad block at %" PRIu32, nblock);

        // just clear cache and try a new block
        lfs_cache_drop(lfs, &lfs->pcache);
    }
}

static int lfs_ctz_traverse(lfs_t *lfs,
        lfs_cache_t *rcache, const lfs_cache_t *pcache,
        lfs_block_t head, lfs_size_t size,
        int (*cb)(void*, lfs_block_t), void *data) {
    if (size == 0) {
        return 0;
    }

    lfs_off_t index = lfs_ctz_index(lfs, &(lfs_off_t){size-1});

    while (true) {
        int err = cb(data, head);
        if (err) {
            return err;
        }

        if (index == 0) {
            return 0;
        }

        lfs_block_t heads[2];
        int count = 2 - (index & 1);
        err = lfs_cache_read(lfs, rcache, pcache, head, 0, &heads, count*4);
        heads[0] = lfs_fromle32(heads[0]);
        heads[1] = lfs_fromle32(heads[1]);
        if (err) {
            return err;
        }

        for (int i = 0; i < count-1; i++) {
            err = cb(data, heads[i]);
            if (err) {
                return err;
            }
        }

        head = heads[count-1];
        index -= count;
    }
}


/// Top level file operations ///
int lfs_file_opencfg(lfs_t *lfs, lfs_file_t *file,
        const char *path, int flags,
        const struct lfs_file_config *cfg) {
    // deorphan if we haven't yet, needed at most once after poweron
    if ((flags & 3) != LFS_O_RDONLY && !lfs->deorphaned) {
        int err = lfs_deorphan(lfs);
        if (err) {
            return err;
        }
    }

    // allocate entry for file if it doesn't exist
    lfs_dir_t cwd;
    lfs_entry_t entry;
    int err = lfs_dir_find(lfs, &cwd, &entry, &path);
    if (err && (err != LFS_ERR_NOENT || strchr(path, '/') != NULL)) {
        return err;
    }

    if (err == LFS_ERR_NOENT) {
        if (!(flags & LFS_O_CREAT)) {
            return LFS_ERR_NOENT;
        }

        // create entry to remember name
        entry.d.type = LFS_TYPE_REG;
        entry.d.elen = sizeof(entry.d) - 4;
        entry.d.alen = 0;
        entry.d.nlen = strlen(path);
        entry.d.u.file.head = 0xffffffff;
        entry.d.u.file.size = 0;
        err = lfs_dir_append(lfs, &cwd, &entry, path);
        if (err) {
            return err;
        }
    } else if (entry.d.type == LFS_TYPE_DIR) {
        return LFS_ERR_ISDIR;
    } else if (flags & LFS_O_EXCL) {
        return LFS_ERR_EXIST;
    }

    // setup file struct
    file->cfg = cfg;
    file->pair[0] = cwd.pair[0];
    file->pair[1] = cwd.pair[1];
    file->poff = entry.off;
    file->head = entry.d.u.file.head;
    file->size = entry.d.u.file.size;
    file->flags = flags;
    file->pos = 0;

    if (flags & LFS_O_TRUNC) {
        if (file->size != 0) {
            file->flags |= LFS_F_DIRTY;
        }
        file->head = 0xffffffff;
        file->size = 0;
    }

    // allocate buffer if needed
    file->cache.block = 0xffffffff;
    if (file->cfg && file->cfg->buffer) {
        file->cache.buffer = file->cfg->buffer;
    } else if (lfs->cfg->file_buffer) {
        if (lfs->files) {
            // already in use
            return LFS_ERR_NOMEM;
        }
        file->cache.buffer = lfs->cfg->file_buffer;
    } else if ((file->flags & 3) == LFS_O_RDONLY) {
        file->cache.buffer = lfs_malloc(lfs->cfg->read_size);
        if (!file->cache.buffer) {
            return LFS_ERR_NOMEM;
        }
    } else {
        file->cache.buffer = lfs_malloc(lfs->cfg->prog_size);
        if (!file->cache.buffer) {
            return LFS_ERR_NOMEM;
        }
    }

    // zero to avoid information leak
    lfs_cache_zero(lfs, &file->cache);

    // add to list of files
    file->next = lfs->files;
    lfs->files = file;

    return 0;
}

int lfs_file_open(lfs_t *lfs, lfs_file_t *file,
        const char *path, int flags) {
    return lfs_file_opencfg(lfs, file, path, flags, NULL);
}

int lfs_file_close(lfs_t *lfs, lfs_file_t *file) {
    int err = lfs_file_sync(lfs, file);

    // remove from list of files
    for (lfs_file_t **p = &lfs->files; *p; p = &(*p)->next) {
        if (*p == file) {
            *p = file->next;
            break;
        }
    }

    // clean up memory
    if (!(file->cfg && file->cfg->buffer) && !lfs->cfg->file_buffer) {
        lfs_free(file->cache.buffer);
    }

    return err;
}

static int lfs_file_relocate(lfs_t *lfs, lfs_file_t *file) {
relocate:
    LFS_DEBUG("Bad block at %" PRIu32, file->block);

    // just relocate what exists into new block
    lfs_block_t nblock;
    int err = lfs_alloc(lfs, &nblock);
    if (err) {
        return err;
    }

    err = lfs_bd_erase(lfs, nblock);
    if (err) {
        if (err == LFS_ERR_CORRUPT) {
            goto relocate;
        }
        return err;
    }

    // either read from dirty cache or disk
    for (lfs_off_t i = 0; i < file->off; i++) {
        uint8_t data;
        err = lfs_cache_read(lfs, &lfs->rcache, &file->cache,
                file->block, i, &data, 1);
        if (err) {
            return err;
        }

        err = lfs_cache_prog(lfs, &lfs->pcache, &lfs->rcache,
                nblock, i, &data, 1);
        if (err) {
            if (err == LFS_ERR_CORRUPT) {
                goto relocate;
            }
            return err;
        }
    }

    // copy over new state of file
    memcpy(file->cache.buffer, lfs->pcache.buffer, lfs->cfg->prog_size);
    file->cache.block = lfs->pcache.block;
    file->cache.off = lfs->pcache.off;
    lfs_cache_zero(lfs, &lfs->pcache);

    file->block = nblock;
    return 0;
}

static int lfs_file_flush(lfs_t *lfs, lfs_file_t *file) {
    if (file->flags & LFS_F_READING) {
        // just drop read cache
        lfs_cache_drop(lfs, &file->cache);
        file->flags &= ~LFS_F_READING;
    }

    if (file->flags & LFS_F_WRITING) {
        lfs_off_t pos = file->pos;

        // copy over anything after current branch
        lfs_file_t orig = {
            .head = file->head,
            .size = file->size,
            .flags = LFS_O_RDONLY,
            .pos = file->pos,
            .cache = lfs->rcache,
        };
        lfs_cache_drop(lfs, &lfs->rcache);

        while (file->pos < file->size) {
            // copy over a byte at a time, leave it up to caching
            // to make this efficient
            uint8_t data;
            lfs_ssize_t res = lfs_file_read(lfs, &orig, &data, 1);
            if (res < 0) {
                return res;
            }

            res = lfs_file_write(lfs, file, &data, 1);
            if (res < 0) {
                return res;
            }

            // keep our reference to the rcache in sync
            if (lfs->rcache.block != 0xffffffff) {
                lfs_cache_drop(lfs, &orig.cache);
                lfs_cache_drop(lfs, &lfs->rcache);
            }
        }

        // write out what we have
        while (true) {
            int err = lfs_cache_flush(lfs, &file->cache, &lfs->rcache);
            if (err) {
                if (err == LFS_ERR_CORRUPT) {
                    goto relocate;
                }
                return err;
            }

            break;
relocate:
            err = lfs_file_relocate(lfs, file);
            if (err) {
                return err;
            }
        }

        // actual file updates
        file->head = file->block;
        file->size = file->pos;
        file->flags &= ~LFS_F_WRITING;
        file->flags |= LFS_F_DIRTY;

        file->pos = pos;
    }

    return 0;
}

int lfs_file_sync(lfs_t *lfs, lfs_file_t *file) {
    int err = lfs_file_flush(lfs, file);
    if (err) {
        return err;
    }

    if ((file->flags & LFS_F_DIRTY) &&
            !(file->flags & LFS_F_ERRED) &&
            !lfs_pairisnull(file->pair)) {
        // update dir entry
        lfs_dir_t cwd;
        err = lfs_dir_fetch(lfs, &cwd, file->pair);
        if (err) {
            return err;
        }

        lfs_entry_t entry = {.off = file->poff};
        err = lfs_bd_read(lfs, cwd.pair[0], entry.off,
                &entry.d, sizeof(entry.d));
        lfs_entry_fromle32(&entry.d);
        if (err) {
            return err;
        }

        LFS_ASSERT(entry.d.type == LFS_TYPE_REG);
        entry.d.u.file.head = file->head;
        entry.d.u.file.size = file->size;

        err = lfs_dir_update(lfs, &cwd, &entry, NULL);
        if (err) {
            return err;
        }

        file->flags &= ~LFS_F_DIRTY;
    }

    return 0;
}

lfs_ssize_t lfs_file_read(lfs_t *lfs, lfs_file_t *file,
        void *buffer, lfs_size_t size) {
    uint8_t *data = buffer;
    lfs_size_t nsize = size;

    if ((file->flags & 3) == LFS_O_WRONLY) {
        return LFS_ERR_BADF;
    }

    if (file->flags & LFS_F_WRITING) {
        // flush out any writes
        int err = lfs_file_flush(lfs, file);
        if (err) {
            return err;
        }
    }

    if (file->pos >= file->size) {
        // eof if past end
        return 0;
    }

    size = lfs_min(size, file->size - file->pos);
    nsize = size;

    while (nsize > 0) {
        // check if we need a new block
        if (!(file->flags & LFS_F_READING) ||
                file->off == lfs->cfg->block_size) {
            int err = lfs_ctz_find(lfs, &file->cache, NULL,
                    file->head, file->size,
                    file->pos, &file->block, &file->off);
            if (err) {
                return err;
            }

            file->flags |= LFS_F_READING;
        }

        // read as much as we can in current block
        lfs_size_t diff = lfs_min(nsize, lfs->cfg->block_size - file->off);
        int err = lfs_cache_read(lfs, &file->cache, NULL,
                file->block, file->off, data, diff);
        if (err) {
            return err;
        }

        file->pos += diff;
        file->off += diff;
        data += diff;
        nsize -= diff;
    }

    return size;
}

lfs_ssize_t lfs_file_write(lfs_t *lfs, lfs_file_t *file,
        const void *buffer, lfs_size_t size) {
    const uint8_t *data = buffer;
    lfs_size_t nsize = size;

    if ((file->flags & 3) == LFS_O_RDONLY) {
        return LFS_ERR_BADF;
    }

    if (file->flags & LFS_F_READING) {
        // drop any reads
        int err = lfs_file_flush(lfs, file);
        if (err) {
            return err;
        }
    }

    if ((file->flags & LFS_O_APPEND) && file->pos < file->size) {
        file->pos = file->size;
    }

    if (!(file->flags & LFS_F_WRITING) && file->pos > file->size) {
        // fill with zeros
        lfs_off_t pos = file->pos;
        file->pos = file->size;

        while (file->pos < pos) {
            lfs_ssize_t res = lfs_file_write(lfs, file, &(uint8_t){0}, 1);
            if (res < 0) {
                return res;
            }
        }
    }

    while (nsize > 0) {
        // check if we need a new block
        if (!(file->flags & LFS_F_WRITING) ||
                file->off == lfs->cfg->block_size) {
            if (!(file->flags & LFS_F_WRITING) && file->pos > 0) {
                // find out which block we're extending from
                int err = lfs_ctz_find(lfs, &file->cache, NULL,
                        file->head, file->size,
                        file->pos-1, &file->block, &file->off);
                if (err) {
                    file->flags |= LFS_F_ERRED;
                    return err;
                }

                // mark cache as dirty since we may have read data into it
                lfs_cache_zero(lfs, &file->cache);
            }

            // extend file with new blocks
            lfs_alloc_ack(lfs);
            int err = lfs_ctz_extend(lfs, &lfs->rcache, &file->cache,
                    file->block, file->pos,
                    &file->block, &file->off);
            if (err) {
                file->flags |= LFS_F_ERRED;
                return err;
            }

            file->flags |= LFS_F_WRITING;
        }

        // program as much as we can in current block
        lfs_size_t diff = lfs_min(nsize, lfs->cfg->block_size - file->off);
        while (true) {
            int err = lfs_cache_prog(lfs, &file->cache, &lfs->rcache,
                    file->block, file->off, data, diff);
            if (err) {
                if (err == LFS_ERR_CORRUPT) {
                    goto relocate;
                }
                file->flags |= LFS_F_ERRED;
                return err;
            }

            break;
relocate:
            err = lfs_file_relocate(lfs, file);
            if (err) {
                file->flags |= LFS_F_ERRED;
                return err;
            }
        }

        file->pos += diff;
        file->off += diff;
        data += diff;
        nsize -= diff;

        lfs_alloc_ack(lfs);
    }

    file->flags &= ~LFS_F_ERRED;
    return size;
}

lfs_soff_t lfs_file_seek(lfs_t *lfs, lfs_file_t *file,
        lfs_soff_t off, int whence) {
    // write out everything beforehand, may be noop if rdonly
    int err = lfs_file_flush(lfs, file);
    if (err) {
        return err;
    }

    // update pos
    if (whence == LFS_SEEK_SET) {
        file->pos = off;
    } else if (whence == LFS_SEEK_CUR) {
        if (off < 0 && (lfs_off_t)-off > file->pos) {
            return LFS_ERR_INVAL;
        }

        file->pos = file->pos + off;
    } else if (whence == LFS_SEEK_END) {
        if (off < 0 && (lfs_off_t)-off > file->size) {
            return LFS_ERR_INVAL;
        }

        file->pos = file->size + off;
    }

    return file->pos;
}

int lfs_file_truncate(lfs_t *lfs, lfs_file_t *file, lfs_off_t size) {
    if ((file->flags & 3) == LFS_O_RDONLY) {
        return LFS_ERR_BADF;
    }

    lfs_off_t oldsize = lfs_file_size(lfs, file);
    if (size < oldsize) {
        // need to flush since directly changing metadata
        int err = lfs_file_flush(lfs, file);
        if (err) {
            return err;
        }

        // lookup new head in ctz skip list
        err = lfs_ctz_find(lfs, &file->cache, NULL,
                file->head, file->size,
                size, &file->head, &(lfs_off_t){0});
        if (err) {
            return err;
        }

        file->size = size;
        file->flags |= LFS_F_DIRTY;
    } else if (size > oldsize) {
        lfs_off_t pos = file->pos;

        // flush+seek if not already at end
        if (file->pos != oldsize) {
            int err = lfs_file_seek(lfs, file, 0, LFS_SEEK_END);
            if (err < 0) {
                return err;
            }
        }

        // fill with zeros
        while (file->pos < size) {
            lfs_ssize_t res = lfs_file_write(lfs, file, &(uint8_t){0}, 1);
            if (res < 0) {
                return res;
            }
        }

        // restore pos
        int err = lfs_file_seek(lfs, file, pos, LFS_SEEK_SET);
        if (err < 0) {
            return err;
        }
    }

    return 0;
}

lfs_soff_t lfs_file_tell(lfs_t *lfs, lfs_file_t *file) {
    (void)lfs;
    return file->pos;
}

int lfs_file_rewind(lfs_t *lfs, lfs_file_t *file) {
    lfs_soff_t res = lfs_file_seek(lfs, file, 0, LFS_SEEK_SET);
    if (res < 0) {
        return res;
    }

    return 0;
}

lfs_soff_t lfs_file_size(lfs_t *lfs, lfs_file_t *file) {
    (void)lfs;
    if (file->flags & LFS_F_WRITING) {
        return lfs_max(file->pos, file->size);
    } else {
        return file->size;
    }
}


/// General fs operations ///
int lfs_stat(lfs_t *lfs, const char *path, struct lfs_info *info) {
    lfs_dir_t cwd;
    lfs_entry_t entry;
    int err = lfs_dir_find(lfs, &cwd, &entry, &path);
    if (err) {
        return err;
    }

    memset(info, 0, sizeof(*info));
    info->type = entry.d.type;
    if (info->type == LFS_TYPE_REG) {
        info->size = entry.d.u.file.size;
    }

    if (lfs_paircmp(entry.d.u.dir, lfs->root) == 0) {
        strcpy(info->name, "/");
    } else {
        err = lfs_bd_read(lfs, cwd.pair[0],
                entry.off + 4+entry.d.elen+entry.d.alen,
                info->name, entry.d.nlen);
        if (err) {
            return err;
        }
    }

    return 0;
}

int lfs_remove(lfs_t *lfs, const char *path) {
    // deorphan if we haven't yet, needed at most once after poweron
    if (!lfs->deorphaned) {
        int err = lfs_deorphan(lfs);
        if (err) {
            return err;
        }
    }

    lfs_dir_t cwd;
    lfs_entry_t entry;
    int err = lfs_dir_find(lfs, &cwd, &entry, &path);
    if (err) {
        return err;
    }

    lfs_dir_t dir;
    if (entry.d.type == LFS_TYPE_DIR) {
        // must be empty before removal, checking size
        // without masking top bit checks for any case where
        // dir is not empty
        err = lfs_dir_fetch(lfs, &dir, entry.d.u.dir);
        if (err) {
            return err;
        } else if (dir.d.size != sizeof(dir.d)+4) {
            return LFS_ERR_NOTEMPTY;
        }
    }

    // remove the entry
    err = lfs_dir_remove(lfs, &cwd, &entry);
    if (err) {
        return err;
    }

    // if we were a directory, find pred, replace tail
    if (entry.d.type == LFS_TYPE_DIR) {
        int res = lfs_pred(lfs, dir.pair, &cwd);
        if (res < 0) {
            return res;
        }

        LFS_ASSERT(res); // must have pred
        cwd.d.tail[0] = dir.d.tail[0];
        cwd.d.tail[1] = dir.d.tail[1];

        err = lfs_dir_commit(lfs, &cwd, NULL, 0);
        if (err) {
            return err;
        }
    }

    return 0;
}

int lfs_rename(lfs_t *lfs, const char *oldpath, const char *newpath) {
    // deorphan if we haven't yet, needed at most once after poweron
    if (!lfs->deorphaned) {
        int err = lfs_deorphan(lfs);
        if (err) {
            return err;
        }
    }

    // find old entry
    lfs_dir_t oldcwd;
    lfs_entry_t oldentry;
    int err = lfs_dir_find(lfs, &oldcwd, &oldentry, &oldpath);
    if (err) {
        return err;
    }

    // allocate new entry
    lfs_dir_t newcwd;
    lfs_entry_t preventry;
    err = lfs_dir_find(lfs, &newcwd, &preventry, &newpath);
    if (err && (err != LFS_ERR_NOENT || strchr(newpath, '/') != NULL)) {
        return err;
    }

    bool prevexists = (err != LFS_ERR_NOENT);
    bool samepair = (lfs_paircmp(oldcwd.pair, newcwd.pair) == 0);

    // must have same type
    if (prevexists && preventry.d.type != oldentry.d.type) {
        return LFS_ERR_ISDIR;
    }

    lfs_dir_t dir;
    if (prevexists && preventry.d.type == LFS_TYPE_DIR) {
        // must be empty before removal, checking size
        // without masking top bit checks for any case where
        // dir is not empty
        err = lfs_dir_fetch(lfs, &dir, preventry.d.u.dir);
        if (err) {
            return err;
        } else if (dir.d.size != sizeof(dir.d)+4) {
            return LFS_ERR_NOTEMPTY;
        }
    }

    // mark as moving
    oldentry.d.type |= 0x80;
    err = lfs_dir_update(lfs, &oldcwd, &oldentry, NULL);
    if (err) {
        return err;
    }

    // update pair if newcwd == oldcwd
    if (samepair) {
        newcwd = oldcwd;
    }

    // move to new location
    lfs_entry_t newentry = preventry;
    newentry.d = oldentry.d;
    newentry.d.type &= ~0x80;
    newentry.d.nlen = strlen(newpath);

    if (prevexists) {
        err = lfs_dir_update(lfs, &newcwd, &newentry, newpath);
        if (err) {
            return err;
        }
    } else {
        err = lfs_dir_append(lfs, &newcwd, &newentry, newpath);
        if (err) {
            return err;
        }
    }

    // update pair if newcwd == oldcwd
    if (samepair) {
        oldcwd = newcwd;
    }

    // remove old entry
    err = lfs_dir_remove(lfs, &oldcwd, &oldentry);
    if (err) {
        return err;
    }

    // if we were a directory, find pred, replace tail
    if (prevexists && preventry.d.type == LFS_TYPE_DIR) {
        int res = lfs_pred(lfs, dir.pair, &newcwd);
        if (res < 0) {
            return res;
        }

        LFS_ASSERT(res); // must have pred
        newcwd.d.tail[0] = dir.d.tail[0];
        newcwd.d.tail[1] = dir.d.tail[1];

        err = lfs_dir_commit(lfs, &newcwd, NULL, 0);
        if (err) {
            return err;
        }
    }

    return 0;
}


/// Filesystem operations ///
static void lfs_deinit(lfs_t *lfs) {
    // free allocated memory
    if (!lfs->cfg->read_buffer) {
        lfs_free(lfs->rcache.buffer);
    }

    if (!lfs->cfg->prog_buffer) {
        lfs_free(lfs->pcache.buffer);
    }

    if (!lfs->cfg->lookahead_buffer) {
        lfs_free(lfs->free.buffer);
    }
}

static int lfs_init(lfs_t *lfs, const struct lfs_config *cfg) {
    lfs->cfg = cfg;

    // setup read cache
    if (lfs->cfg->read_buffer) {
        lfs->rcache.buffer = lfs->cfg->read_buffer;
    } else {
        lfs->rcache.buffer = lfs_malloc(lfs->cfg->read_size);
        if (!lfs->rcache.buffer) {
            goto cleanup;
        }
    }

    // setup program cache
    if (lfs->cfg->prog_buffer) {
        lfs->pcache.buffer = lfs->cfg->prog_buffer;
    } else {
        lfs->pcache.buffer = lfs_malloc(lfs->cfg->prog_size);
        if (!lfs->pcache.buffer) {
            goto cleanup;
        }
    }

    // zero to avoid information leaks
    lfs_cache_zero(lfs, &lfs->rcache);
    lfs_cache_zero(lfs, &lfs->pcache);

    // setup lookahead, round down to nearest 32-bits
    LFS_ASSERT(lfs->cfg->lookahead % 32 == 0);
    LFS_ASSERT(lfs->cfg->lookahead > 0);
    if (lfs->cfg->lookahead_buffer) {
        lfs->free.buffer = lfs->cfg->lookahead_buffer;
    } else {
        lfs->free.buffer = lfs_malloc(lfs->cfg->lookahead/8);
        if (!lfs->free.buffer) {
            goto cleanup;
        }
    }

    // check that program and read sizes are multiples of the block size
    LFS_ASSERT(lfs->cfg->prog_size % lfs->cfg->read_size == 0);
    LFS_ASSERT(lfs->cfg->block_size % lfs->cfg->prog_size == 0);

    // check that the block size is large enough to fit ctz pointers
    LFS_ASSERT(4*lfs_npw2(0xffffffff / (lfs->cfg->block_size-2*4))
            <= lfs->cfg->block_size);

    // setup default state
    lfs->root[0] = 0xffffffff;
    lfs->root[1] = 0xffffffff;
    lfs->files = NULL;
    lfs->dirs = NULL;
    lfs->deorphaned = false;

    return 0;

cleanup:
    lfs_deinit(lfs);
    return LFS_ERR_NOMEM;
}

int lfs_format(lfs_t *lfs, const struct lfs_config *cfg) {
    int err = lfs_init(lfs, cfg);
    if (err) {
        return err;
    }

    // create free lookahead
    memset(lfs->free.buffer, 0, lfs->cfg->lookahead/8);
    lfs->free.off = 0;
    lfs->free.size = lfs_min(lfs->cfg->lookahead, lfs->cfg->block_count);
    lfs->free.i = 0;
    lfs_alloc_ack(lfs);

    // create superblock dir
    lfs_dir_t superdir;
    err = lfs_dir_alloc(lfs, &superdir);
    if (err) {
        goto cleanup;
    }

    // write root directory
    lfs_dir_t root;
    err = lfs_dir_alloc(lfs, &root);
    if (err) {
        goto cleanup;
    }

    err = lfs_dir_commit(lfs, &root, NULL, 0);
    if (err) {
        goto cleanup;
    }

    lfs->root[0] = root.pair[0];
    lfs->root[1] = root.pair[1];

    // write superblocks
    lfs_superblock_t superblock = {
        .off = sizeof(superdir.d),
        .d.type = LFS_TYPE_SUPERBLOCK,
        .d.elen = sizeof(superblock.d) - sizeof(superblock.d.magic) - 4,
        .d.nlen = sizeof(superblock.d.magic),
        .d.version = LFS_DISK_VERSION,
        .d.magic = {"littlefs"},
        .d.block_size  = lfs->cfg->block_size,
        .d.block_count = lfs->cfg->block_count,
        .d.root = {lfs->root[0], lfs->root[1]},
    };
    superdir.d.tail[0] = root.pair[0];
    superdir.d.tail[1] = root.pair[1];
    superdir.d.size = sizeof(superdir.d) + sizeof(superblock.d) + 4;

    // write both pairs to be safe
    lfs_superblock_tole32(&superblock.d);
    bool valid = false;
    for (int i = 0; i < 2; i++) {
        err = lfs_dir_commit(lfs, &superdir, (struct lfs_region[]){
                {sizeof(superdir.d), sizeof(superblock.d),
                 &superblock.d, sizeof(superblock.d)}
            }, 1);
        if (err && err != LFS_ERR_CORRUPT) {
            goto cleanup;
        }

        valid = valid || !err;
    }

    if (!valid) {
        err = LFS_ERR_CORRUPT;
        goto cleanup;
    }

    // sanity check that fetch works
    err = lfs_dir_fetch(lfs, &superdir, (const lfs_block_t[2]){0, 1});
    if (err) {
        goto cleanup;
    }

    lfs_alloc_ack(lfs);

cleanup:
    lfs_deinit(lfs);
    return err;
}

int lfs_mount(lfs_t *lfs, const struct lfs_config *cfg) {
    int err = lfs_init(lfs, cfg);
    if (err) {
        return err;
    }

    // setup free lookahead
    lfs->free.off = 0;
    lfs->free.size = 0;
    lfs->free.i = 0;
    lfs_alloc_ack(lfs);

    // load superblock
    lfs_dir_t dir;
    lfs_superblock_t superblock;
    err = lfs_dir_fetch(lfs, &dir, (const lfs_block_t[2]){0, 1});
    if (err && err != LFS_ERR_CORRUPT) {
        goto cleanup;
    }

    if (!err) {
        err = lfs_bd_read(lfs, dir.pair[0], sizeof(dir.d),
                &superblock.d, sizeof(superblock.d));
        lfs_superblock_fromle32(&superblock.d);
        if (err) {
            goto cleanup;
        }

        lfs->root[0] = superblock.d.root[0];
        lfs->root[1] = superblock.d.root[1];
    }

    if (err || memcmp(superblock.d.magic, "littlefs", 8) != 0) {
        LFS_ERROR("Invalid superblock at %d %d", 0, 1);
        err = LFS_ERR_CORRUPT;
        goto cleanup;
    }

    uint16_t major_version = (0xffff & (superblock.d.version >> 16));
    uint16_t minor_version = (0xffff & (superblock.d.version >>  0));
    if ((major_version != LFS_DISK_VERSION_MAJOR ||
         minor_version > LFS_DISK_VERSION_MINOR)) {
        LFS_ERROR("Invalid version %d.%d", major_version, minor_version);
        err = LFS_ERR_INVAL;
        goto cleanup;
    }

    return 0;

cleanup:

    lfs_deinit(lfs);
    return err;
}

int lfs_unmount(lfs_t *lfs) {
    lfs_deinit(lfs);
    return 0;
}


/// Littlefs specific operations ///
int lfs_traverse(lfs_t *lfs, int (*cb)(void*, lfs_block_t), void *data) {
    if (lfs_pairisnull(lfs->root)) {
        return 0;
    }

    // iterate over metadata pairs
    lfs_dir_t dir;
    lfs_entry_t entry;
    lfs_block_t cwd[2] = {0, 1};

    while (true) {
        for (int i = 0; i < 2; i++) {
            int err = cb(data, cwd[i]);
            if (err) {
                return err;
            }
        }

        int err = lfs_dir_fetch(lfs, &dir, cwd);
        if (err) {
            return err;
        }

        // iterate over contents
        while (dir.off + sizeof(entry.d) <= (0x7fffffff & dir.d.size)-4) {
            err = lfs_bd_read(lfs, dir.pair[0], dir.off,
                    &entry.d, sizeof(entry.d));
            lfs_entry_fromle32(&entry.d);
            if (err) {
                return err;
            }

            dir.off += lfs_entry_size(&entry);
            if ((0x70 & entry.d.type) == (0x70 & LFS_TYPE_REG)) {
                err = lfs_ctz_traverse(lfs, &lfs->rcache, NULL,
                        entry.d.u.file.head, entry.d.u.file.size, cb, data);
                if (err) {
                    return err;
                }
            }
        }

        cwd[0] = dir.d.tail[0];
        cwd[1] = dir.d.tail[1];

        if (lfs_pairisnull(cwd)) {
            break;
        }
    }

    // iterate over any open files
    for (lfs_file_t *f = lfs->files; f; f = f->next) {
        if (f->flags & LFS_F_DIRTY) {
            int err = lfs_ctz_traverse(lfs, &lfs->rcache, &f->cache,
                    f->head, f->size, cb, data);
            if (err) {
                return err;
            }
        }

        if (f->flags & LFS_F_WRITING) {
            int err = lfs_ctz_traverse(lfs, &lfs->rcache, &f->cache,
                    f->block, f->pos, cb, data);
            if (err) {
                return err;
            }
        }
    }

    return 0;
}

static int lfs_pred(lfs_t *lfs, const lfs_block_t dir[2], lfs_dir_t *pdir) {
    if (lfs_pairisnull(lfs->root)) {
        return 0;
    }

    // iterate over all directory directory entries
    int err = lfs_dir_fetch(lfs, pdir, (const lfs_block_t[2]){0, 1});
    if (err) {
        return err;
    }

    while (!lfs_pairisnull(pdir->d.tail)) {
        if (lfs_paircmp(pdir->d.tail, dir) == 0) {
            return true;
        }

        err = lfs_dir_fetch(lfs, pdir, pdir->d.tail);
        if (err) {
            return err;
        }
    }

    return false;
}

static int lfs_parent(lfs_t *lfs, const lfs_block_t dir[2],
        lfs_dir_t *parent, lfs_entry_t *entry) {
    if (lfs_pairisnull(lfs->root)) {
        return 0;
    }

    parent->d.tail[0] = 0;
    parent->d.tail[1] = 1;

    // iterate over all directory directory entries
    while (!lfs_pairisnull(parent->d.tail)) {
        int err = lfs_dir_fetch(lfs, parent, parent->d.tail);
        if (err) {
            return err;
        }

        while (true) {
            err = lfs_dir_next(lfs, parent, entry);
            if (err && err != LFS_ERR_NOENT) {
                return err;
            }

            if (err == LFS_ERR_NOENT) {
                break;
            }

            if (((0x70 & entry->d.type) == (0x70 & LFS_TYPE_DIR)) &&
                 lfs_paircmp(entry->d.u.dir, dir) == 0) {
                return true;
            }
        }
    }

    return false;
}

static int lfs_moved(lfs_t *lfs, const void *e) {
    if (lfs_pairisnull(lfs->root)) {
        return 0;
    }

    // skip superblock
    lfs_dir_t cwd;
    int err = lfs_dir_fetch(lfs, &cwd, (const lfs_block_t[2]){0, 1});
    if (err) {
        return err;
    }

    // iterate over all directory directory entries
    lfs_entry_t entry;
    while (!lfs_pairisnull(cwd.d.tail)) {
        err = lfs_dir_fetch(lfs, &cwd, cwd.d.tail);
        if (err) {
            return err;
        }

        while (true) {
            err = lfs_dir_next(lfs, &cwd, &entry);
            if (err && err != LFS_ERR_NOENT) {
                return err;
            }

            if (err == LFS_ERR_NOENT) {
                break;
            }

            if (!(0x80 & entry.d.type) &&
                 memcmp(&entry.d.u, e, sizeof(entry.d.u)) == 0) {
                return true;
            }
        }
    }

    return false;
}

static int lfs_relocate(lfs_t *lfs,
        const lfs_block_t oldpair[2], const lfs_block_t newpair[2]) {
    // find parent
    lfs_dir_t parent;
    lfs_entry_t entry;
    int res = lfs_parent(lfs, oldpair, &parent, &entry);
    if (res < 0) {
        return res;
    }

    if (res) {
        // update disk, this creates a desync
        entry.d.u.dir[0] = newpair[0];
        entry.d.u.dir[1] = newpair[1];

        int err = lfs_dir_update(lfs, &parent, &entry, NULL);
        if (err) {
            return err;
        }

        // update internal root
        if (lfs_paircmp(oldpair, lfs->root) == 0) {
            LFS_DEBUG("Relocating root %" PRIu32 " %" PRIu32,
                    newpair[0], newpair[1]);
            lfs->root[0] = newpair[0];
            lfs->root[1] = newpair[1];
        }

        // clean up bad block, which should now be a desync
        return lfs_deorphan(lfs);
    }

    // find pred
    res = lfs_pred(lfs, oldpair, &parent);
    if (res < 0) {
        return res;
    }

    if (res) {
        // just replace bad pair, no desync can occur
        parent.d.tail[0] = newpair[0];
        parent.d.tail[1] = newpair[1];

        return lfs_dir_commit(lfs, &parent, NULL, 0);
    }

    // couldn't find dir, must be new
    return 0;
}

int lfs_deorphan(lfs_t *lfs) {
    lfs->deorphaned = true;

    if (lfs_pairisnull(lfs->root)) {
        return 0;
    }

    lfs_dir_t pdir = {.d.size = 0x80000000};
    lfs_dir_t cwd = {.d.tail[0] = 0, .d.tail[1] = 1};

    // iterate over all directory directory entries
    while (!lfs_pairisnull(cwd.d.tail)) {
        int err = lfs_dir_fetch(lfs, &cwd, cwd.d.tail);
        if (err) {
            return err;
        }

        // check head blocks for orphans
        if (!(0x80000000 & pdir.d.size)) {
            // check if we have a parent
            lfs_dir_t parent;
            lfs_entry_t entry;
            int res = lfs_parent(lfs, pdir.d.tail, &parent, &entry);
            if (res < 0) {
                return res;
            }

            if (!res) {
                // we are an orphan
                LFS_DEBUG("Found orphan %" PRIu32 " %" PRIu32,
                        pdir.d.tail[0], pdir.d.tail[1]);

                pdir.d.tail[0] = cwd.d.tail[0];
                pdir.d.tail[1] = cwd.d.tail[1];

                err = lfs_dir_commit(lfs, &pdir, NULL, 0);
                if (err) {
                    return err;
                }

                break;
            }

            if (!lfs_pairsync(entry.d.u.dir, pdir.d.tail)) {
                // we have desynced
                LFS_DEBUG("Found desync %" PRIu32 " %" PRIu32,
                        entry.d.u.dir[0], entry.d.u.dir[1]);

                pdir.d.tail[0] = entry.d.u.dir[0];
                pdir.d.tail[1] = entry.d.u.dir[1];

                err = lfs_dir_commit(lfs, &pdir, NULL, 0);
                if (err) {
                    return err;
                }

                break;
            }
        }

        // check entries for moves
        lfs_entry_t entry;
        while (true) {
            err = lfs_dir_next(lfs, &cwd, &entry);
            if (err && err != LFS_ERR_NOENT) {
                return err;
            }

            if (err == LFS_ERR_NOENT) {
                break;
            }

            // found moved entry
            if (entry.d.type & 0x80) {
                int moved = lfs_moved(lfs, &entry.d.u);
                if (moved < 0) {
                    return moved;
                }

                if (moved) {
                    LFS_DEBUG("Found move %" PRIu32 " %" PRIu32,
                            entry.d.u.dir[0], entry.d.u.dir[1]);
                    err = lfs_dir_remove(lfs, &cwd, &entry);
                    if (err) {
                        return err;
                    }
                } else {
                    LFS_DEBUG("Found partial move %" PRIu32 " %" PRIu32,
                            entry.d.u.dir[0], entry.d.u.dir[1]);
                    entry.d.type &= ~0x80;
                    err = lfs_dir_update(lfs, &cwd, &entry, NULL);
                    if (err) {
                        return err;
                    }
                }
            }
        }

        memcpy(&pdir, &cwd, sizeof(pdir));
    }

    return 0;
}
