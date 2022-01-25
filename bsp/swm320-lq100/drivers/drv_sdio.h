/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-10     lik          first version
 */

#ifndef __DRV_SDIO_H__
#define __DRV_SDIO_H__

#include "board.h"

#define SDIO_BUFF_SIZE 4096
#define SDIO_ALIGN_LEN 4

#ifndef SDIO_MAX_FREQ
#define SDIO_MAX_FREQ (30000000)
#endif

struct sdio_pkg
{
    struct rt_mmcsd_cmd *cmd;
    void *buff;
    rt_uint32_t flag;
};

typedef rt_err_t (*sdio_txconfig)(struct sdio_pkg *pkg, rt_uint32_t *buff, int size);
typedef rt_err_t (*sdio_rxconfig)(struct sdio_pkg *pkg, rt_uint32_t *buff, int size);
typedef rt_uint32_t (*sdio_clk_get)(SDIO_TypeDef *hw_sdio);

struct swm_sdio_des
{
    SDIO_TypeDef *hw_sdio;
    sdio_txconfig txconfig;
    sdio_rxconfig rxconfig;
    sdio_clk_get clk_get;
};

#endif /* __DRV_SDIO_H__ */
