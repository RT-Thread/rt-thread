/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BOOT_HEADER_H
#define HPM_BOOT_HEADER_H

#include "hpm_common.h"

#define HPM_BOOTHEADER_TAG (0xBFU)
#define HPM_BOOTHEADER_MAX_FW_COUNT (2U)

#ifndef HPM_BOOT_FW_COUNT
#define HPM_BOOT_FW_COUNT 1
#endif

#if HPM_BOOT_FW_COUNT < 1
#error "HPM_BOOT_FW_COUNT can't be less than 1"
#endif

typedef struct {
    uint32_t offset;            /* 0x0: offset to boot_header start */
    uint32_t size;              /* 0x4: size in bytes */
    uint32_t flags;             /* 0x8: [3:0] fw type: */
                                /*         0 - executable */
                                /*         1 - cmd container */
                                /*      [11:8] - hash type */
                                /*         0 - none */
                                /*         1 - sha256 */
                                /*         2 - sm3 */
    uint32_t reserved0;         /* 0xC */
    uint32_t load_addr;         /* 0x10: load address */
    uint32_t reserved1;         /* 0x14 */
    uint32_t entry_point;       /* 0x18: application entry */
    uint32_t reserved2;         /* 0x1C */
    uint8_t hash[64];           /* 0x20: hash value */
    uint8_t iv[32];             /* 0x60: initial vector */
} fw_info_table_t;

typedef struct {
    uint8_t tag;                /* 0x0: must be '0xbf' */
    uint8_t version;            /* 0x1: header version */
    uint16_t length;            /* 0x2: header length, max 8KB */
    uint32_t flags;             /* 0x4: [3:0] SRK set */
                                /*      [7:4] SRK index */
                                /*      [15:8] SRK_REVOKE_MASK */
                                /*      [19:16] Signature Type */
                                /*        1: ECDSA */
                                /*        2: SM2 */
    uint16_t sw_version;        /* 0x8: software version */
    uint8_t fuse_version;       /* 0xA: fuse version */
    uint8_t fw_count;           /* 0xB: number of fw */
    uint16_t dc_block_offset;   /* 0xC: device config block offset*/
    uint16_t sig_block_offset;  /* 0xE: signature block offset */
    /*
     * fw_info_table_t fw_info[HPM_BOOT_FW_COUNT]; [> 0x10: fw table <]
     * uint32_t dc_info[];         [> <]
     */
} boot_header_t;

#endif /* HPM_BOOT_HEADER_H */
