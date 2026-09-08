/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __K1X_RPROC_H__
#define __K1X_RPROC_H__

#include <rtthread.h>

rt_err_t spacemit_k1x_rproc_boot(const char *fw_name);
void spacemit_k1x_rproc_dump_status(void);

#endif /* __K1X_RPROC_H__ */
