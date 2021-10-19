/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2021-10-13   AisinoChip    first add to bsp
 */

#include "board.h"
#include <rtdevice.h>

#if defined(RT_USING_HWCRYPTO) && defined(RT_HWCRYPTO_USING_CRC) && defined(BSP_USING_CRC)

#define CRC_MUTEX_NAME      "crc_mutex"

static CRC_HandleTypeDef hcrc = {0};
static struct rt_mutex crc_mutex;

rt_err_t rt_hw_crc_init(void)
{
    return rt_mutex_init(&crc_mutex, CRC_MUTEX_NAME, RT_IPC_FLAG_PRIO);
}

rt_uint32_t rt_hw_crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    rt_uint32_t crc_val = 0;
    rt_memset(&hcrc, 0, sizeof(hcrc));

    rt_mutex_take(&crc_mutex, RT_WAITING_FOREVER);

    switch (ctx->crc_cfg.width)
    {
    case 8:
        hcrc.Init.PolyLen = CRC_POLTY_LEN_8;
        break;
    case 16:
        hcrc.Init.PolyLen = CRC_POLTY_LEN_16;
        break;
    case 32:
        hcrc.Init.PolyLen = CRC_POLTY_LEN_32;
        break;
    default:
        rt_mutex_release(&crc_mutex);
        return RT_EINVAL;
    }

    hcrc.Init.PolyRev = CRC_POLY_REV_EN;
    hcrc.Init.InitRev = CRC_INIT_REV_EN;
    if (!(ctx->crc_cfg.flags & CRC_FLAG_REFIN))
    {
        hcrc.Init.DataRev = CRC_DATA_REV_BY_BYTE;
    }

    if (!(ctx->crc_cfg.flags & CRC_FLAG_REFOUT))
    {
        hcrc.Init.RsltRev = CRC_RSLT_REV_EN;
    }
    hcrc.Init.OutxorRev = CRC_OUTXOR_REV_EN;

    hcrc.Init.InitData = ctx->crc_cfg.last_val;
    hcrc.Init.OutXorData = ctx->crc_cfg.xorout;

    hcrc.Instance = CRC;
    hcrc.Init.PolyData = ctx->crc_cfg.poly;

    hcrc.Init.DataLen = CRC_DATA_LEN_1B;

    System_Module_Enable(EN_CRC);
    hcrc.Instance->CTRL = hcrc.Init.PolyRev | hcrc.Init.OutxorRev | hcrc.Init.InitRev | hcrc.Init.RsltRev |
        hcrc.Init.DataRev | hcrc.Init.PolyLen   | hcrc.Init.DataLen;

    hcrc.Instance->INIT = hcrc.Init.InitData;
    hcrc.Instance->OUTXOR = hcrc.Init.OutXorData;
    hcrc.Instance->POLY = hcrc.Init.PolyData;

    while (length--)
    {
        hcrc.Instance->DATA = *in++;
    }
    crc_val = hcrc.Instance->DATA;

    System_Module_Disable(EN_CRC);

    rt_mutex_release(&crc_mutex);

    return crc_val;
}

#endif /* defined(RT_USING_HWCRYPTO) && defined(RT_HWCRYPTO_USING_CRC) && defined(BSP_USING_CRC) */

