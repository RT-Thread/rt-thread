/*
 * Copyright (c) 2024, sakumisu
 * Copyright (c) 2024, Egahp
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef BOOTUF2_H
#define BOOTUF2_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <bootuf2_config.h>

#ifndef __PACKED
#define __PACKED __attribute__((packed))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) \
    ((int)((sizeof(array) / sizeof((array)[0]))))
#endif

struct bootuf2_BLOCK
{
    // 32 byte header
    uint32_t MagicStart0;
    uint32_t MagicStart1;
    uint32_t Flags;
    uint32_t TargetAddress;
    uint32_t PayloadSize;
    uint32_t BlockIndex;
    uint32_t NumberOfBlock;
    uint32_t FamilyID; // or file_size
    uint8_t Data[476];
    uint32_t MagicEnd;
} __PACKED;
//BUILD_ASSERT(sizeof(struct bootuf2_BLOCK) == 512, "bootuf2_BLOCK not sector sized");

struct bootuf2_STATE
{
    uint32_t NumberOfBlock;
    uint32_t NumberOfWritten;
    uint8_t *const Mask;
    uint8_t Enable;
};

struct bootuf2_DBR
{
    /*!< offset 0   */
    uint8_t JMPInstruction[3];
    /*!< offset 3   */
    uint8_t OEM[8];
    /*!< offset 11  */
    struct
    {
        uint16_t BytesPerSector;
        uint8_t SectorsPerCluster;
        uint16_t ReservedSectors;
        uint8_t NumberOfFAT;
        uint16_t RootEntries;
        uint16_t Sectors;
        uint8_t MediaDescriptor;
        uint16_t SectorsPerFAT;
        uint16_t SectorsPerTrack;
        uint16_t Heads;
        uint32_t HiddenSectors;
        uint32_t SectorsOver32MB;
        uint8_t BIOSDrive;
        uint8_t Reserved;
        uint8_t ExtendBootSignature;
        uint32_t VolumeSerialNumber;
        uint8_t VolumeLabel[11];
        uint8_t FileSystem[8];
    } __PACKED BPB;
    /*!< offset 62  */
    /*!< BootLoader */
    /*!< offset 511 */
    /*!< 0x55 0xAA  */
} __PACKED;
//BUILD_ASSERT(sizeof(struct bootuf2_DBR) == 62, "bootuf2_DBR size must be 62 byte");

struct bootuf2_ENTRY
{
    char Name[11];
    uint8_t Attribute;
    uint8_t NTReserved;
    uint8_t CreateTimeTeenth;
    uint16_t CreateTime;
    uint16_t CreateDate;
    uint16_t LastAccessDate;
    uint16_t FirstClustH16;
    uint16_t UpdateTime;
    uint16_t UpdateDate;
    uint16_t FirstClustL16;
    uint32_t FileSize;
} __PACKED;
//BUILD_ASSERT(sizeof(struct bootuf2_ENTRY) == 32, "bootuf2_ENTRY size must be 32 byte");

struct bootuf2_FILE
{
    const char *const Name;
    const void *const Content;
    uint32_t FileSize;
    uint16_t ClusterBeg;
    uint16_t ClusterEnd;
};

#define BOOTUF2_DIVCEIL(_v, _d) (((_v) / (_d)) + ((_v) % (_d) ? 1 : 0))

#define BOOTUF2_MAGIC_START0 0x0A324655u
#define BOOTUF2_MAGIC_START1 0x9E5D5157u
#define BOOTUF2_MAGIC_SERIAL 0x251B18BDu
#define BOOTUF2_MAGIC_END 0x0AB16F30u

#define BOOTUF2_FLAG_NOT_MAIN_FLASH 0x00000001u
#define BOOTUF2_FLAG_FILE_CONTAINER 0x00001000u
#define BOOTUF2_FLAG_FAMILID_PRESENT 0x00002000u
#define BOOTUF2_FLAG_MD5_PRESENT 0x00004000u

#define BOOTUF2_CMD_READ 0
#define BOOTUF2_CMD_SYNC 1

#define BOOTUF2_BLOCKSMAX (((CONFIG_BOOTUF2_FLASHMAX) / 256) + (((CONFIG_BOOTUF2_FLASHMAX) % 256) ? 1 : 0))

#define BOOTUF2_FAMILYID_POSNUM(n) (((CONFIG_BOOTUF2_FAMILYID) / (0x10000000 >> ((n) * 4))) % 0x10)
#define BOOTUF2_FAMILYID_ARRAY                                                                                           \
    {                                                                                                                    \
        ((BOOTUF2_FAMILYID_POSNUM(0) >= 10) ? BOOTUF2_FAMILYID_POSNUM(0) - 10 + 'A' : BOOTUF2_FAMILYID_POSNUM(0) + '0'), \
        ((BOOTUF2_FAMILYID_POSNUM(1) >= 10) ? BOOTUF2_FAMILYID_POSNUM(1) - 10 + 'A' : BOOTUF2_FAMILYID_POSNUM(1) + '0'), \
        ((BOOTUF2_FAMILYID_POSNUM(2) >= 10) ? BOOTUF2_FAMILYID_POSNUM(2) - 10 + 'A' : BOOTUF2_FAMILYID_POSNUM(2) + '0'), \
        ((BOOTUF2_FAMILYID_POSNUM(3) >= 10) ? BOOTUF2_FAMILYID_POSNUM(3) - 10 + 'A' : BOOTUF2_FAMILYID_POSNUM(3) + '0'), \
        ((BOOTUF2_FAMILYID_POSNUM(4) >= 10) ? BOOTUF2_FAMILYID_POSNUM(4) - 10 + 'A' : BOOTUF2_FAMILYID_POSNUM(4) + '0'), \
        ((BOOTUF2_FAMILYID_POSNUM(5) >= 10) ? BOOTUF2_FAMILYID_POSNUM(5) - 10 + 'A' : BOOTUF2_FAMILYID_POSNUM(5) + '0'), \
        ((BOOTUF2_FAMILYID_POSNUM(6) >= 10) ? BOOTUF2_FAMILYID_POSNUM(6) - 10 + 'A' : BOOTUF2_FAMILYID_POSNUM(6) + '0'), \
        ((BOOTUF2_FAMILYID_POSNUM(7) >= 10) ? BOOTUF2_FAMILYID_POSNUM(7) - 10 + 'A' : BOOTUF2_FAMILYID_POSNUM(7) + '0'), \
        ('I'),                                                                                                           \
        ('D'),                                                                                                           \
        (' '),                                                                                                           \
        ('\0'),                                                                                                          \
    };

#define BOOTUF2_FAT16_PER_SECTOR(pDBR) (pDBR->BPB.BytesPerSector / 2)
#define BOOTUF2_ENTRY_PER_SECTOR(pDBR) (pDBR->BPB.BytesPerSector / sizeof(struct bootuf2_ENTRY))
#define BOOTUF2_CLUSTERSMAX (0xFFF0 - 2)
#define BOOTUF2_SECTOR_DBR_END (0)
#define BOOTUF2_SECTOR_RSVD_END(pDBR) BOOTUF2_SECTOR_DBR_END + (pDBR->BPB.ReservedSectors)
#define BOOTUF2_SECTOR_FAT_END(pDBR) BOOTUF2_SECTOR_RSVD_END(pDBR) + (pDBR->BPB.SectorsPerFAT * pDBR->BPB.NumberOfFAT)
#define BOOTUF2_SECTOR_ROOT_END(pDBR) BOOTUF2_SECTOR_FAT_END(pDBR) + (pDBR->BPB.RootEntries / (pDBR->BPB.BytesPerSector / sizeof(struct bootuf2_ENTRY)))
#define BOOTUF2_SECTOR_DATA_END(pDBR) (pDBR->BPB.Sectors + pDBR->BPB.SectorsOver32MB)

#define BOOTUF2_SECTORS_PER_FAT(n) \
    BOOTUF2_DIVCEIL(BOOTUF2_CLUSTERSMAX, (CONFIG_BOOTUF2_SECTOR_SIZE / 2))
#define BOOTUF2_SECTORS_FOR_ENTRIES(n) \
    (CONFIG_BOOTUF2_ROOT_ENTRIES / (CONFIG_BOOTUF2_SECTOR_SIZE / sizeof(struct bootuf2_ENTRY)))
#define BOOTUF2_SECTORS(n)                                \
    (CONFIG_BOOTUF2_SECTOR_RESERVED +                         \
     CONFIG_BOOTUF2_NUM_OF_FAT * BOOTUF2_SECTORS_PER_FAT(n) + \
     BOOTUF2_SECTORS_FOR_ENTRIES(n) +                     \
     BOOTUF2_CLUSTERSMAX * CONFIG_BOOTUF2_SECTOR_PER_CLUSTER)

#define BOOTUF2_YEAR_INT (         \
    (__DATE__[7u] - '0') * 1000u + \
    (__DATE__[8u] - '0') * 100u +  \
    (__DATE__[9u] - '0') * 10u +   \
    (__DATE__[10u] - '0') * 1u)

#define BOOTUF2_MONTH_INT (                                      \
    (__DATE__[2u] == 'n' && __DATE__[1u] == 'a')   ? 1u  /*Jan*/ \
    : (__DATE__[2u] == 'b')                        ? 2u  /*Feb*/ \
    : (__DATE__[2u] == 'r' && __DATE__[1u] == 'a') ? 3u  /*Mar*/ \
    : (__DATE__[2u] == 'r')                        ? 4u  /*Apr*/ \
    : (__DATE__[2u] == 'y')                        ? 5u  /*May*/ \
    : (__DATE__[2u] == 'n')                        ? 6u  /*Jun*/ \
    : (__DATE__[2u] == 'l')                        ? 7u  /*Jul*/ \
    : (__DATE__[2u] == 'g')                        ? 8u  /*Aug*/ \
    : (__DATE__[2u] == 'p')                        ? 9u  /*Sep*/ \
    : (__DATE__[2u] == 't')                        ? 10u /*Oct*/ \
    : (__DATE__[2u] == 'v')                        ? 11u /*Nov*/ \
                                                   : 12u /*Dec*/)

#define BOOTUF2_DAY_INT (                                  \
    (__DATE__[4u] == ' ' ? 0 : __DATE__[4u] - '0') * 10u + \
    (__DATE__[5u] - '0'))

#define BOOTUF2_HOUR_INT ( \
    (__TIME__[0u] == '?' ? 0 : __TIME__[0u] - '0') * 10u + (__TIME__[1u] == '?' ? 0 : __TIME__[1u] - '0'))

#define BOOTUF2_MINUTE_INT ( \
    (__TIME__[3u] == '?' ? 0 : __TIME__[3u] - '0') * 10u + (__TIME__[4u] == '?' ? 0 : __TIME__[4u] - '0'))

#define BOOTUF2_SECONDS_INT ( \
    (__TIME__[6u] == '?' ? 0 : __TIME__[6u] - '0') * 10u + (__TIME__[7u] == '?' ? 0 : __TIME__[7u] - '0'))

#define BOOTUF2_DOS_DATE (               \
    ((BOOTUF2_YEAR_INT - 1980u) << 9u) | \
    (BOOTUF2_MONTH_INT << 5u) |          \
    (BOOTUF2_DAY_INT << 0u))

#define BOOTUF2_DOS_TIME (       \
    (BOOTUF2_HOUR_INT << 11u) |  \
    (BOOTUF2_MINUTE_INT << 5u) | \
    (BOOTUF2_SECONDS_INT << 0u))

void bootuf2_init(void);
int boot2uf2_read_sector(uint32_t start_sector, uint8_t *buff, uint32_t sector_count);
int bootuf2_write_sector(uint32_t start_sector, const uint8_t *buff, uint32_t sector_count);
uint16_t bootuf2_get_sector_size(void);
uint32_t bootuf2_get_sector_count(void);

bool bootuf2_is_write_done(void);

void boot2uf2_flash_init(void);
int bootuf2_flash_write(uint32_t address, const uint8_t *data, size_t size);

#endif /*  BOOTUF2_H */
