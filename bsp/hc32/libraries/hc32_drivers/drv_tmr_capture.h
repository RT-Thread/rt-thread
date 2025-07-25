/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-10    CDT          first version
 */

#ifndef __DRV_TMR_CAPTURE_H__
#define __DRV_TMR_CAPTURE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <board.h>
#include <rtdevice.h>
#include <rtthread.h>


struct tmr_capture_dev_init_params
{
    char *name;
    uint32_t ch;
    uint8_t clk_div;
    uint32_t first_edge;
    IRQn_Type irq_num_cap;
    uint32_t  irq_prio_cap;
    IRQn_Type irq_num_ovf;
    uint32_t  irq_prio_ovf;
};

extern rt_err_t rt_hw_board_input_capture_init(uint32_t *tmr_instance);
int tmr_capture_device_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_TMR_CAPTURE_H__ */

/************************** end of file ******************/
