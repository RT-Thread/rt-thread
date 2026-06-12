/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_CRC_H__
#define __DRV_CRC_H__

#include "rtdevice.h"

#define CRC_FLAG_REFIN    (0x1 << 0)
#define CRC_FLAG_REFOUT   (0x1 << 1)

rt_err_t nu_crc_init(void);

rt_uint32_t nu_crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length);

#endif /* __DRV_CRC_H__ */