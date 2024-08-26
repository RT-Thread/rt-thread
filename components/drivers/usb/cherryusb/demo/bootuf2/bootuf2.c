/*
 * Copyright (c) 2024, sakumisu
 * Copyright (c) 2024, Egahp
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "bootuf2.h"
#include "usbd_core.h"

char file_INFO[] = {
    "CherryUSB UF2 BOOT\r\n"
    "Model: " CONFIG_PRODUCT "\r\n"
    "Board-ID: " CONFIG_BOARD "\r\n"
};

const char file_IDEX[] = {
    "<!doctype html>\n"
    "<html>"
    "<body>"
    "<script>\n"
    "location.replace(\"" CONFIG_BOOTUF2_INDEX_URL "\");\n"
    "</script>"
    "</body>"
    "</html>\n"
};

const char file_JOIN[] = {
    "<!doctype html>\n"
    "<html>"
    "<body>"
    "<script>\n"
    "location.replace(\"" CONFIG_BOOTUF2_JOIN_URL "\");\n"
    "</script>"
    "</body>"
    "</html>\n"
};

const char file_ID__[12] = BOOTUF2_FAMILYID_ARRAY;

static struct bootuf2_FILE files[] = {
    [0] = { .Name = file_ID__, .Content = NULL, .FileSize = 0 },
    [1] = { .Name = "INFO_UF2TXT", .Content = file_INFO, .FileSize = sizeof(file_INFO) - 1 },
    [2] = { .Name = "INDEX   HTM", .Content = file_IDEX, .FileSize = sizeof(file_IDEX) - 1 },
    [3] = { .Name = "JOIN    HTM", .Content = file_JOIN, .FileSize = sizeof(file_JOIN) - 1 },
};

struct bootuf2_data {
    const struct bootuf2_DBR *const DBR;
    struct bootuf2_STATE *const STATE;
    uint8_t *const fbuff;
    uint8_t *const erase;
    size_t page_count;
    uint8_t *const cache;
    const size_t cache_size;
    uint32_t cached_address;
    size_t cached_bytes;
};

/*!< define DBRs */
static const struct bootuf2_DBR bootuf2_DBR = {
    .JMPInstruction = { 0xEB, 0x3C, 0x90 },
    .OEM = "UF2 UF2 ",
    .BPB = {
        .BytesPerSector = CONFIG_BOOTUF2_SECTOR_SIZE,
        .SectorsPerCluster = CONFIG_BOOTUF2_SECTOR_PER_CLUSTER,
        .ReservedSectors = CONFIG_BOOTUF2_SECTOR_RESERVED,
        .NumberOfFAT = CONFIG_BOOTUF2_NUM_OF_FAT,
        .RootEntries = CONFIG_BOOTUF2_ROOT_ENTRIES,
        .Sectors = (BOOTUF2_SECTORS(0) > 0xFFFF) ? 0 : BOOTUF2_SECTORS(0),
        .MediaDescriptor = 0xF8,
        .SectorsPerFAT = BOOTUF2_SECTORS_PER_FAT(0),
        .SectorsPerTrack = 1,
        .Heads = 1,
        .HiddenSectors = 0,
        .SectorsOver32MB = (BOOTUF2_SECTORS(0) > 0xFFFF) ? BOOTUF2_SECTORS(0) : 0,
        .BIOSDrive = 0x80,
        .Reserved = 0,
        .ExtendBootSignature = 0x29,
        .VolumeSerialNumber = 0x00420042,
        .VolumeLabel = "CHERRYUF2",
        .FileSystem = "FAT16   ",
    },
};

/*!< define mask */
static uint8_t __attribute__((aligned(4))) bootuf2_mask[BOOTUF2_BLOCKSMAX / 8 + 1] = { 0 };

/*!< define state */
static struct bootuf2_STATE bootuf2_STATE = {
    .NumberOfBlock = 0,
    .NumberOfWritten = 0,
    .Mask = bootuf2_mask,
    .Enable = 1,
};

/*!< define flash cache */
static uint8_t __attribute__((aligned(4))) bootuf2_disk_cache[CONFIG_BOOTUF2_CACHE_SIZE];

/*!< define flash buff */
static uint8_t __attribute__((aligned(4))) bootuf2_disk_fbuff[256];

/*!< define erase flag buff */
static uint8_t __attribute__((aligned(4))) bootuf2_disk_erase[BOOTUF2_DIVCEIL(CONFIG_BOOTUF2_PAGE_COUNTMAX, 8)];

/*!< define disk */
static struct bootuf2_data bootuf2_disk = {
    .DBR = &bootuf2_DBR,
    .STATE = &bootuf2_STATE,
    .fbuff = bootuf2_disk_fbuff,
    .erase = bootuf2_disk_erase,
    .cache = bootuf2_disk_cache,
    .cache_size = sizeof(bootuf2_disk_cache),
};

static void fname_copy(char *dst, char const *src, uint16_t len)
{
    for (size_t i = 0; i < len; ++i) {
        if (*src)
            *dst++ = *src++;
        else
            *dst++ = ' ';
    }
}

static void fcalculate_cluster(struct bootuf2_data *ctx)
{
    /*!< init files cluster */
    uint16_t cluster_beg = 2;
    for (int i = 0; i < ARRAY_SIZE(files); i++) {
        files[i].ClusterBeg = cluster_beg;
        files[i].ClusterEnd = -1 + cluster_beg +
                              BOOTUF2_DIVCEIL(files[i].FileSize,
                                              ctx->DBR->BPB.BytesPerSector *
                                                  ctx->DBR->BPB.SectorsPerCluster);
        cluster_beg = files[i].ClusterEnd + 1;
    }
}

static int ffind_by_cluster(uint32_t cluster)
{
    if (cluster >= 0xFFF0) {
        return -1;
    }

    for (uint32_t i = 0; i < ARRAY_SIZE(files); i++) {
        if ((files[i].ClusterBeg <= cluster) &&
            (cluster <= files[i].ClusterEnd)) {
            return i;
        }
    }

    return -1;
}

static bool bootuf2block_check_writable(struct bootuf2_STATE *STATE,
                                        struct bootuf2_BLOCK *uf2, uint32_t block_max)
{
    if (uf2->NumberOfBlock) {
        if (uf2->BlockIndex < block_max) {
            uint8_t mask = 1 << (uf2->BlockIndex % 8);
            uint32_t pos = uf2->BlockIndex / 8;

            if ((STATE->Mask[pos] & mask) == 0) {
                return true;
            }
        }
    }

    return false;
}

static void bootuf2block_state_update(struct bootuf2_STATE *STATE,
                                      struct bootuf2_BLOCK *uf2, uint32_t block_max)
{
    if (uf2->NumberOfBlock) {
        if (STATE->NumberOfBlock != uf2->NumberOfBlock) {
            if ((uf2->NumberOfBlock >= BOOTUF2_BLOCKSMAX) ||
                STATE->NumberOfBlock) {
                /*!< uf2 block only can be update once */
                /*!< this will cause never auto reboot */
                STATE->NumberOfBlock = 0xffffffff;
            } else {
                STATE->NumberOfBlock = uf2->NumberOfBlock;
            }
        }

        if (uf2->BlockIndex < block_max) {
            uint8_t mask = 1 << (uf2->BlockIndex % 8);
            uint32_t pos = uf2->BlockIndex / 8;

            if ((STATE->Mask[pos] & mask) == 0) {
                STATE->Mask[pos] |= mask;
                STATE->NumberOfWritten++;
            }
        }
    }

    USB_LOG_DBG("UF2 block total %d written %d index %d\r\n",
                uf2->NumberOfBlock, STATE->NumberOfWritten, uf2->BlockIndex);
}

static bool bootuf2block_state_check(struct bootuf2_STATE *STATE)
{
    return (STATE->NumberOfWritten >= STATE->NumberOfBlock) &&
           STATE->NumberOfBlock;
}

static int bootuf2_flash_flush(struct bootuf2_data *ctx)
{
    int err;

    if (ctx->cached_bytes == 0) {
        return 0;
    }

    err = bootuf2_flash_write(ctx->cached_address, ctx->cache, ctx->cached_bytes);

    if (err) {
        USB_LOG_ERR("UF2 slot flash write error %d at offset %08lx len %d\r\n",
                    err, ctx->cached_address, ctx->cached_bytes);
        return -1;
    }

    ctx->cached_bytes = 0;

    return 0;
}

int bootuf2_flash_write_internal(struct bootuf2_data *ctx, struct bootuf2_BLOCK *uf2)
{
    /*!< 1.cache not empty and address not continue */
    /*!< 2.cache full */
    if ((ctx->cached_bytes && ((ctx->cached_address + ctx->cached_bytes) != uf2->TargetAddress)) ||
        (ctx->cached_bytes == ctx->cache_size)) {
        int err = bootuf2_flash_flush(ctx);
        if (err)
            return err;
    }

    /*!< write len always is 256, cache_size always is a multiple of 256 */
    memcpy(ctx->cache + ctx->cached_bytes, uf2->Data, uf2->PayloadSize);

    ctx->cached_address = uf2->TargetAddress - ctx->cached_bytes;
    ctx->cached_bytes += uf2->PayloadSize;

    return 0;
}

void bootuf2_init(void)
{
    struct bootuf2_data *ctx;

    ctx = &bootuf2_disk;

    fcalculate_cluster(ctx);

    ctx->cached_bytes = 0;
    ctx->cached_address = 0;
}

int boot2uf2_read_sector(uint32_t start_sector, uint8_t *buff, uint32_t sector_count)
{
    struct bootuf2_data *ctx;

    ctx = &bootuf2_disk;

    while (sector_count) {
        memset(buff, 0, ctx->DBR->BPB.BytesPerSector);

        uint32_t sector_relative = start_sector;

        /*!< DBR sector */
        if (start_sector == BOOTUF2_SECTOR_DBR_END) {
            memcpy(buff, ctx->DBR, sizeof(struct bootuf2_DBR));
            buff[510] = 0x55;
            buff[511] = 0xaa;
        }
        /*!< FAT sector */
        else if (start_sector < BOOTUF2_SECTOR_FAT_END(ctx->DBR)) {
            uint16_t *buff16 = (uint16_t *)buff;

            sector_relative -= BOOTUF2_SECTOR_RSVD_END(ctx->DBR);

            /*!< Perform the same operation on all FAT tables */
            while (sector_relative >= ctx->DBR->BPB.SectorsPerFAT) {
                sector_relative -= ctx->DBR->BPB.SectorsPerFAT;
            }

            uint16_t cluster_unused = files[ARRAY_SIZE(files) - 1].ClusterEnd + 1;
            uint16_t cluster_absolute_first = sector_relative *
                                              BOOTUF2_FAT16_PER_SECTOR(ctx->DBR);

            /*!< cluster used link to chain, or unsed */
            for (uint16_t i = 0, cluster_absolute = cluster_absolute_first;
                 i < BOOTUF2_FAT16_PER_SECTOR(ctx->DBR);
                 i++, cluster_absolute++) {
                if (cluster_absolute >= cluster_unused)
                    buff16[i] = 0;
                else
                    buff16[i] = cluster_absolute + 1;
            }

            /*!< cluster 0 and 1 */
            if (sector_relative == 0) {
                buff[0] = ctx->DBR->BPB.MediaDescriptor;
                buff[1] = 0xff;
                buff16[1] = 0xffff;
            }

            /*!< cluster end of file */
            for (uint32_t i = 0; i < ARRAY_SIZE(files); i++) {
                uint16_t cluster_file_last = files[i].ClusterEnd;

                if (cluster_file_last >= cluster_absolute_first) {
                    uint16_t idx = cluster_file_last - cluster_absolute_first;
                    if (idx < BOOTUF2_FAT16_PER_SECTOR(ctx->DBR)) {
                        buff16[idx] = 0xffff;
                    }
                }
            }
        }
        /*!< root entries */
        else if (start_sector < BOOTUF2_SECTOR_ROOT_END(ctx->DBR)) {
            sector_relative -= BOOTUF2_SECTOR_FAT_END(ctx->DBR);

            struct bootuf2_ENTRY *ent = (void *)buff;
            int remain_entries = BOOTUF2_ENTRY_PER_SECTOR(ctx->DBR);

            uint32_t file_index_first;

            /*!< volume label entry */
            if (sector_relative == 0) {
                fname_copy(ent->Name, (char const *)ctx->DBR->BPB.VolumeLabel, 11);
                ent->Attribute = 0x28;
                ent++;
                remain_entries--;
                file_index_first = 0;
            } else {
                /*!< -1 to account for volume label in first sector */
                file_index_first = sector_relative * BOOTUF2_ENTRY_PER_SECTOR(ctx->DBR) - 1;
            }

            for (uint32_t idx = file_index_first;
                 (remain_entries > 0) && (idx < ARRAY_SIZE(files));
                 idx++, ent++) {
                const uint32_t cluster_beg = files[idx].ClusterBeg;

                const struct bootuf2_FILE *f = &files[idx];

                if ((0 == f->FileSize) &&
                    (0 != idx)) {
                    continue;
                }

                fname_copy(ent->Name, f->Name, 11);
                ent->Attribute = 0x05;
                ent->CreateTimeTeenth = BOOTUF2_SECONDS_INT % 2 * 100;
                ent->CreateTime = BOOTUF2_DOS_TIME;
                ent->CreateDate = BOOTUF2_DOS_DATE;
                ent->LastAccessDate = BOOTUF2_DOS_DATE;
                ent->FirstClustH16 = cluster_beg >> 16;
                ent->UpdateTime = BOOTUF2_DOS_TIME;
                ent->UpdateDate = BOOTUF2_DOS_DATE;
                ent->FirstClustL16 = cluster_beg & 0xffff;
                ent->FileSize = f->FileSize;
            }
        }
        /*!< data */
        else if (start_sector < BOOTUF2_SECTOR_DATA_END(ctx->DBR)) {
            sector_relative -= BOOTUF2_SECTOR_ROOT_END(ctx->DBR);

            int fid = ffind_by_cluster(2 + sector_relative / ctx->DBR->BPB.SectorsPerCluster);

            if (fid >= 0) {
                const struct bootuf2_FILE *f = &files[fid];

                uint32_t sector_relative_file =
                    sector_relative -
                    (files[fid].ClusterBeg - 2) * ctx->DBR->BPB.SectorsPerCluster;

                size_t fcontent_offset = sector_relative_file * ctx->DBR->BPB.BytesPerSector;
                size_t fcontent_length = f->FileSize;

                if (fcontent_length > fcontent_offset) {
                    const void *src = (void *)((uint8_t *)(f->Content) + fcontent_offset);
                    size_t copy_size = fcontent_length - fcontent_offset;

                    if (copy_size > ctx->DBR->BPB.BytesPerSector) {
                        copy_size = ctx->DBR->BPB.BytesPerSector;
                    }

                    memcpy(buff, src, copy_size);
                }
            }
        }
        /*!< unknown sector, ignore */

        start_sector++;
        sector_count--;
        buff += ctx->DBR->BPB.BytesPerSector;
    }

    return 0;
}

int bootuf2_write_sector(uint32_t start_sector, const uint8_t *buff, uint32_t sector_count)
{
    struct bootuf2_data *ctx;

    ctx = &bootuf2_disk;

    while (sector_count) {
        struct bootuf2_BLOCK *uf2 = (void *)buff;

        if (!((uf2->MagicStart0 == BOOTUF2_MAGIC_START0) &&
              (uf2->MagicStart1 == BOOTUF2_MAGIC_START1) &&
              (uf2->MagicEnd == BOOTUF2_MAGIC_END) &&
              (uf2->Flags & BOOTUF2_FLAG_FAMILID_PRESENT) &&
              !(uf2->Flags & BOOTUF2_FLAG_NOT_MAIN_FLASH))) {
            goto next;
        }

        if (uf2->FamilyID == CONFIG_BOOTUF2_FAMILYID) {
            if (bootuf2block_check_writable(ctx->STATE, uf2, CONFIG_BOOTUF2_FLASHMAX)) {
                bootuf2_flash_write_internal(ctx, uf2);
                bootuf2block_state_update(ctx->STATE, uf2, CONFIG_BOOTUF2_FLASHMAX);
            } else {
                USB_LOG_DBG("UF2 block %d already written\r\n",
                            uf2->BlockIndex);
            }
        } else {
            USB_LOG_DBG("UF2 block illegal id %08x\r\n", uf2->FamilyID);
        }

    next:
        start_sector++;
        sector_count--;
        buff += ctx->DBR->BPB.BytesPerSector;
    }

    return 0;
}

uint16_t bootuf2_get_sector_size(void)
{
    return bootuf2_disk.DBR->BPB.BytesPerSector;
}

uint32_t bootuf2_get_sector_count(void)
{
    return bootuf2_disk.DBR->BPB.SectorsOver32MB + bootuf2_disk.DBR->BPB.Sectors;
}

bool bootuf2_is_write_done(void)
{
    if (bootuf2block_state_check(bootuf2_disk.STATE)) {
        bootuf2_flash_flush(&bootuf2_disk);
        USB_LOG_DBG("UF2 update ok\r\n");
        return true;
    } else {
        return false;
    }
}