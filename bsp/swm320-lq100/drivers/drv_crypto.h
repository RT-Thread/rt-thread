/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-10     lik          first version
 */

#ifndef __DRV_CRYPTO_H__
#define __DRV_CRYPTO_H__

#include "board.h"

/* swm config class */
struct swm_crc_cfg
{
    CRC_TypeDef *CRCx;
    uint32_t inival;
    uint8_t crc_inbits;
    uint8_t crc_1632;
    uint8_t crc_out_not;
    uint8_t crc_out_rev;
};

#ifdef BSP_USING_CRC

#define DEFAULT_CRC (CRC)
#define DEFAULT_INIVAL (0x00000000)
#define DEFAULT_INBITS (2)
#define DEFAULT_CRC1632 (0)
#define DEFAULT_OUT_NOT (0)
#define DEFAULT_OUT_REV (0)

#endif /* BSP_USING_CRC */

int rt_hw_crypto_init(void);

#endif /* __DRV_CRYPTO_H__ */
