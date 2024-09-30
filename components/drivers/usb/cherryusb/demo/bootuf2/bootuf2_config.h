/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef BOOTUF2_CONFIG_H
#define BOOTUF2_CONFIG_H

#define CONFIG_PRODUCT            "CherryUSB"
#define CONFIG_BOARD              "CherryUSB BOARD"
#define CONFIG_BOOTUF2_INDEX_URL "https://github.com/cherry-embedded"
#define CONFIG_BOOTUF2_JOIN_URL  "http://qm.qq.com/cgi-bin/qm/qr?_wv=1027&k=GyH2M5XfWTHQzmZis4ClpgvfdObPrvtk&authKey=LmcLhfno%2BiW51wmgVC%2F8WoYwUXqiclzWDHMU1Jy1d6S8cECJ4Q7bfJ%2FTe67RLakI&noverify=0&group_code=642693751"

#define CONFIG_BOOTUF2_CACHE_SIZE         4096
#define CONFIG_BOOTUF2_SECTOR_SIZE        512
#define CONFIG_BOOTUF2_SECTOR_PER_CLUSTER 2
#define CONFIG_BOOTUF2_SECTOR_RESERVED    1
#define CONFIG_BOOTUF2_NUM_OF_FAT         2
#define CONFIG_BOOTUF2_ROOT_ENTRIES       64

#define CONFIG_BOOTUF2_FAMILYID      0xFFFFFFFF
#define CONFIG_BOOTUF2_FLASHMAX      0x800000
#define CONFIG_BOOTUF2_PAGE_COUNTMAX 1024

#endif