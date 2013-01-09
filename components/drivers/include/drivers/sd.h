#ifndef __SD_H__
#define __SD_H__
/*
 * File      : sd.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2011-07-25     weety		first version
 */

#include <rtthread.h>
#include <drivers/mmcsd_host.h>

#ifdef __cplusplus
extern "C" {
#endif

rt_err_t mmcsd_send_if_cond(struct rt_mmcsd_host *host, rt_uint32_t ocr);
rt_err_t mmcsd_send_app_op_cond(struct rt_mmcsd_host *host, rt_uint32_t ocr, rt_uint32_t *rocr);
rt_int32_t init_sd(struct rt_mmcsd_host *host, rt_uint32_t ocr);

#ifdef __cplusplus
}
#endif

#endif
