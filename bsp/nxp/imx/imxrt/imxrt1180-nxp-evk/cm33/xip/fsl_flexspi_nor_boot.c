/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexspi_nor_boot.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.xip_device"
#endif

/* clang-format off */
#if defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1) && \
    defined(XIP_BOOT_HEADER_ENABLE) && (XIP_BOOT_HEADER_ENABLE == 1)
/* clang-format on */

#if defined(__CC_ARM) || defined(__ARMCC_VERSION) || defined(__GNUC__)
__attribute__((section(".boot_hdr.container"), used))
#elif defined(__ICCARM__)
#pragma location = ".boot_hdr.container"
#endif

/* clang-format off */
const container container_data =
{
    {
        CNT_VERSION,
        CNT_SIZE,
        CNT_TAG_HEADER,
        CNT_FLAGS,
        CNT_SW_VER,
        CNT_FUSE_VER,
        CNT_NUM_IMG,
        sizeof(cnt_hdr) + CNT_NUM_IMG * sizeof(image_entry),
        0
    },
    {{
        IMAGE_OFFSET,
        IMAGE_SIZE,
        IMAGE_LOAD_ADDRESS,
        0x00000000,
        IMAGE_ENTRY_ADDRESS,
        0x00000000,
        IMG_FLAGS,
        0x0,
        {0},
        {0}
    }},
    {
        SGNBK_VERSION,
        SGNBK_SIZE,
        SGNBK_TAG,
        0x0,
        0x0,
        0x0,
        0x0
    }
};
/* clang-format on */

#endif