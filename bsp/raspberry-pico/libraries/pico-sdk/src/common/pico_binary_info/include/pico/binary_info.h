/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_BINARY_INFO_H
#define _PICO_BINARY_INFO_H

/**
 * Binary info is intended for embedding machine readable information with the binary in FLASH.
 *
 * Example uses include:
 *
 * - Program identification / information
 * - Pin layouts
 * - Included features
 * - Identifying flash regions used as block devices/storage
 */

#include "pico/binary_info/defs.h"
#include "pico/binary_info/structure.h"
#if PICO_ON_DEVICE
#include "pico/binary_info/code.h"
#endif


#endif