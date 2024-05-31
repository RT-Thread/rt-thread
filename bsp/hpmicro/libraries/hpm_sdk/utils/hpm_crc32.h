/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_CRC32_H
#define _HPM_CRC32_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */

uint32_t crc32(const uint8_t *buf, uint32_t len);

#ifdef __cplusplus
}
#endif /* __cplusplus  */
#endif