/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-07-25     weety         first version
 */

#ifndef __SD_H__
#define __SD_H__

#include <rtthread.h>
#include <drivers/mmcsd_host.h>

#ifdef __cplusplus
extern "C" {
#endif

rt_err_t mmcsd_send_if_cond(struct rt_mmcsd_host *host, rt_uint32_t ocr);
rt_err_t mmcsd_send_app_op_cond(struct rt_mmcsd_host *host, rt_uint32_t ocr, rt_uint32_t *rocr);

rt_err_t mmcsd_get_card_addr(struct rt_mmcsd_host *host, rt_uint32_t *rca);
rt_int32_t mmcsd_get_scr(struct rt_mmcsd_card *card, rt_uint32_t *scr);

rt_int32_t init_sd(struct rt_mmcsd_host *host, rt_uint32_t ocr);

#ifdef __cplusplus
}
#endif

#endif
