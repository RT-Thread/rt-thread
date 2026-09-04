/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <firmware-spacemit.h>

    .section ".rodata"
    SPACEMIT_FIRMWARE_DEFINE esos.elf

SPACEMIT_FIRMWARE_START
    SPACEMIT_FIRMWARE_REF esos.elf
SPACEMIT_FIRMWARE_END
