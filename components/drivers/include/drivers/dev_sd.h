/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-07-25     weety         first version
 * 2024-05-26     HPMicro       Add UHS-I support
 */

#ifndef __DEV_SD_H__
#define __DEV_SD_H__

#include <rtthread.h>
#include <drivers/mmcsd_host.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 *  SWITCH_FUNC timing
 */
#define SD_SWITCH_FUNC_TIMING_DEFAULT 0
#define SD_SWITCH_FUNC_TIMING_HS      1
#define SD_SWITCH_FUNC_TIMING_SDR50   2
#define SD_SWITCH_FUNC_TIMING_SDR104  3
#define SD_SWITCH_FUNC_TIMING_DDR50   4


rt_err_t mmcsd_send_if_cond(struct rt_mmcsd_host *host, rt_uint32_t ocr);
rt_err_t mmcsd_send_app_op_cond(struct rt_mmcsd_host *host, rt_uint32_t ocr, rt_uint32_t *rocr);

rt_err_t mmcsd_get_card_addr(struct rt_mmcsd_host *host, rt_uint32_t *rca);
rt_int32_t mmcsd_get_scr(struct rt_mmcsd_card *card, rt_uint32_t *scr);

rt_int32_t init_sd(struct rt_mmcsd_host *host, rt_uint32_t ocr);

#ifdef __cplusplus
}
#endif

#endif
