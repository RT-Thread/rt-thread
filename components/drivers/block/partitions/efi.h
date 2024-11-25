/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-05-05     linzhenxing   first version
 * 2023-02-25     GuEe-GUI      make blk interface
 */

#ifndef __PARTITIONS_EFI_H__
#define __PARTITIONS_EFI_H__

#include "../blk_partition.h"
#include <drivers/misc.h>
#include <drivers/byteorder.h>

#define MSDOS_MBR_SIGNATURE     0xaa55
#define EFI_PMBR_OSTYPE_EFI     0xef
#define EFI_PMBR_OSTYPE_EFI_GPT 0xee

#define GPT_MBR_PROTECTIVE      1
#define GPT_MBR_HYBRID          2

#define GPT_HEADER_SIGNATURE    0x5452415020494645ULL
#define GPT_HEADER_REVISION_V1  0x00010000
#define GPT_PRIMARY_PARTITION_TABLE_LBA 1

#ifndef __UUID_H__
#define UUID_SIZE 16

typedef struct
{
    rt_uint8_t b[UUID_SIZE];
} guid_t;
#endif /* __UUID_H__ */

#ifndef __EFI_H__
typedef guid_t efi_guid_t rt_align(4);

#define EFI_GUID(a, b, c, d...) (efi_guid_t)                                \
{{                                                                          \
    (a) & 0xff, ((a) >> 8) & 0xff, ((a) >> 16) & 0xff, ((a) >> 24) & 0xff,  \
    (b) & 0xff, ((b) >> 8) & 0xff,                                          \
    (c) & 0xff, ((c) >> 8) & 0xff,                                          \
    d                                                                       \
}}

#define NULL_GUID \
    EFI_GUID(0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

rt_inline int efi_guidcmp(efi_guid_t left, efi_guid_t right)
{
    return rt_memcmp(&left, &right, sizeof (efi_guid_t));
}
#endif /* __EFI_H__ */

#define PARTITION_SYSTEM_GUID \
    EFI_GUID(0xc12a7328, 0xf81f, 0x11d2, 0xba, 0x4b, 0x00, 0xa0, 0xc9, 0x3e, 0xc9, 0x3b)

#define LEGACY_MBR_PARTITION_GUID \
    EFI_GUID(0x024dee41, 0x33e7, 0x11d3, 0x9d, 0x69, 0x00, 0x08, 0xc7, 0x81, 0xf3, 0x9f)

#define PARTITION_MSFT_RESERVED_GUID \
    EFI_GUID(0xe3c9e316, 0x0b5c, 0x4db8, 0x81, 0x7d, 0xf9, 0x2d, 0xf0, 0x02, 0x15, 0xae)

#define PARTITION_BASIC_DATA_GUID \
    EFI_GUID(0xebd0a0a2, 0xb9e5, 0x4433, 0x87, 0xc0, 0x68, 0xb6, 0xb7, 0x26, 0x99, 0xc7)

rt_packed(struct _gpt_header
{
    rt_le64_t signature;
    rt_le32_t revision;
    rt_le32_t header_size;
    rt_le32_t header_crc32;
    rt_le32_t reserved1;
    rt_le64_t start_lba;
    rt_le64_t alternate_lba;
    rt_le64_t first_usable_lba;
    rt_le64_t last_usable_lba;
    efi_guid_t disk_guid;
    rt_le64_t partition_entry_lba;
    rt_le32_t num_partition_entries;
    rt_le32_t sizeof_partition_entry;
    rt_le32_t partition_entry_array_crc32;

    /*
     * The rest of the logical block is reserved by UEFI and must be zero.
     * EFI standard handles this by:
     *
     * uint8_t reserved2[BlockSize - 92];
     */
});
typedef struct _gpt_header gpt_header;

rt_packed(struct _gpt_entry_attributes
{
    rt_uint64_t required_to_function:1;
    rt_uint64_t reserved:47;
    rt_uint64_t type_guid_specific:16;
});
typedef struct _gpt_entry_attributes gpt_entry_attributes;

rt_packed(struct _gpt_entry
{
    efi_guid_t partition_type_guid;
    efi_guid_t unique_partition_guid;
    rt_le64_t starting_lba;
    rt_le64_t ending_lba;
    gpt_entry_attributes attributes;
    rt_le16_t partition_name[72/sizeof(rt_le16_t)];
});
typedef struct _gpt_entry gpt_entry;

rt_packed(struct _gpt_mbr_record
{
    rt_uint8_t boot_indicator;  /* unused by EFI, set to 0x80 for bootable */
    rt_uint8_t start_head;      /* unused by EFI, pt start in CHS */
    rt_uint8_t start_sector;    /* unused by EFI, pt start in CHS */
    rt_uint8_t start_track;
    rt_uint8_t os_type;         /* EFI and legacy non-EFI OS types */
    rt_uint8_t end_head;        /* unused by EFI, pt end in CHS */
    rt_uint8_t end_sector;      /* unused by EFI, pt end in CHS */
    rt_uint8_t end_track;       /* unused by EFI, pt end in CHS */
    rt_le32_t starting_lba;     /* used by EFI - start addr of the on disk pt */
    rt_le32_t size_in_lba;      /* used by EFI - size of pt in LBA */
});
typedef struct _gpt_mbr_record gpt_mbr_record;

rt_packed(struct _legacy_mbr
{
    rt_uint8_t boot_code[440];
    rt_le32_t unique_mbr_signature;
    rt_le16_t unknown;
    gpt_mbr_record partition_record[4];
    rt_le16_t signature;
});
typedef struct _legacy_mbr legacy_mbr;

#endif /* __PARTITIONS_EFI_H__ */
