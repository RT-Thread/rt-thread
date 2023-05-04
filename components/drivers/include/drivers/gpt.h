/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-05-05     linzhenxing     first version
 */
#ifndef __GPT_H
#define __GPT_H

#include <rtthread.h>
#include <stdint.h>

typedef struct
{
    uint8_t b[16]; /* GUID 16 bytes*/
} guid_t;

#define MSDOS_MBR_SIGNATURE 0xaa55
#define EFI_PMBR_OSTYPE_EFI 0xEF
#define EFI_PMBR_OSTYPE_EFI_GPT 0xEE

#define GPT_MBR_PROTECTIVE  1
#define GPT_MBR_HYBRID      2

#define GPT_HEADER_SIGNATURE 0x5452415020494645ULL
#define GPT_HEADER_REVISION_V1 0x00010000
#define GPT_PRIMARY_PARTITION_TABLE_LBA 1

typedef guid_t gpt_guid_t __attribute__ ((aligned (4)));
#define EFI_GUID(a, b, c, d...) (gpt_guid_t){ {                 \
    (a) & 0xff, ((a) >> 8) & 0xff, ((a) >> 16) & 0xff, ((a) >> 24) & 0xff,  \
    (b) & 0xff, ((b) >> 8) & 0xff,                      \
    (c) & 0xff, ((c) >> 8) & 0xff, d } }

#define NULL_GUID \
    EFI_GUID(0x00000000, 0x0000, 0x0000,\
             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
#define PARTITION_SYSTEM_GUID \
    EFI_GUID( 0xC12A7328, 0xF81F, 0x11d2, \
              0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B)
#define LEGACY_MBR_PARTITION_GUID \
    EFI_GUID( 0x024DEE41, 0x33E7, 0x11d3, \
              0x9D, 0x69, 0x00, 0x08, 0xC7, 0x81, 0xF3, 0x9F)
#define PARTITION_MSFT_RESERVED_GUID \
    EFI_GUID( 0xE3C9E316, 0x0B5C, 0x4DB8, \
              0x81, 0x7D, 0xF9, 0x2D, 0xF0, 0x02, 0x15, 0xAE)
#define PARTITION_BASIC_DATA_GUID \
    EFI_GUID( 0xEBD0A0A2, 0xB9E5, 0x4433, \
              0x87, 0xC0, 0x68, 0xB6, 0xB7, 0x26, 0x99, 0xC7)
#define PARTITION_LINUX_RAID_GUID \
    EFI_GUID( 0xa19d880f, 0x05fc, 0x4d3b, \
              0xa0, 0x06, 0x74, 0x3f, 0x0f, 0x84, 0x91, 0x1e)
#define PARTITION_LINUX_SWAP_GUID \
    EFI_GUID( 0x0657fd6d, 0xa4ab, 0x43c4, \
              0x84, 0xe5, 0x09, 0x33, 0xc8, 0x4b, 0x4f, 0x4f)
#define PARTITION_LINUX_LVM_GUID \
    EFI_GUID( 0xe6d6d379, 0xf507, 0x44c2, \
              0xa2, 0x3c, 0x23, 0x8f, 0x2a, 0x3d, 0xf9, 0x28)
#pragma pack(push, 1)
typedef struct _gpt_header
{
    uint64_t signature;
    uint32_t revision;
    uint32_t header_size;
    uint32_t header_crc32;
    uint32_t reserved1;
    uint64_t start_lba;     /*GPT head start sector*/
    uint64_t alternate_lba; /*GPT head alternate sector*/
    uint64_t first_usable_lba;
    uint64_t last_usable_lba;
    gpt_guid_t disk_guid;
    uint64_t partition_entry_lba;
    uint32_t num_partition_entries;
    uint32_t sizeof_partition_entry;
    uint32_t partition_entry_array_crc32;

    /* The rest of the logical block is reserved by UEFI and must be zero.
     * EFI standard handles this by:
     *
     * uint8_t      reserved2[ BlockSize - 92 ];
     */
} gpt_header;

typedef struct _gpt_entry_attributes
{
    uint64_t required_to_function:1;
    uint64_t reserved:47;
    uint64_t type_guid_specific:16;
} gpt_entry_attributes;

typedef struct _gpt_entry
{
    gpt_guid_t partition_type_guid;
    gpt_guid_t unique_partition_guid;
    uint64_t starting_lba;
    uint64_t ending_lba;
    gpt_entry_attributes attributes;
    uint16_t partition_name[72/sizeof(uint16_t)];
} gpt_entry;

typedef struct _gpt_mbr_record
{
    uint8_t boot_indicator; /* unused by EFI, set to 0x80 for bootable */
    uint8_t start_head;     /* unused by EFI, pt start in CHS */
    uint8_t start_sector;   /* unused by EFI, pt start in CHS */
    uint8_t start_track;
    uint8_t os_type;        /* EFI and legacy non-EFI OS types */
    uint8_t end_head;       /* unused by EFI, pt end in CHS */
    uint8_t end_sector;     /* unused by EFI, pt end in CHS */
    uint8_t end_track;      /* unused by EFI, pt end in CHS */
    uint32_t starting_lba;   /* used by EFI - start addr of the on disk pt */
    uint32_t size_in_lba;    /* used by EFI - size of pt in LBA */
} gpt_mbr_record;


typedef struct _legacy_mbr
{
    uint8_t boot_code[440];
    uint32_t unique_mbr_signature;
    uint16_t unknown;
    gpt_mbr_record partition_record[4];
    uint16_t signature;
} legacy_mbr;
#pragma pack(pop)

int check_gpt(struct rt_mmcsd_card *card);
int gpt_get_partition_param(struct rt_mmcsd_card *card, struct dfs_partition *part, uint32_t pindex);
void gpt_free(void);
#endif /*__GPT_H*/
