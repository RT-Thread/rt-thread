/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#ifndef __PDM_H_
#define __PDM_H_

#include <rtthread.h>

/**
 * @brief External function definitions
 *
 */
int rt_pdm_init(void);
rt_uint8_t am_pdm_data_get(rt_uint8_t *buff, rt_uint16_t size);
void am_pdm_start(void);
void am_pdm_stop(void);

#endif // __PDM_H_
