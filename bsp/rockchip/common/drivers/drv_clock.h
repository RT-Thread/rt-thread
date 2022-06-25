/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_clock.h
  * @version V0.1
  * @brief   clock interface
  *
  * Change Logs:
  * Date           Author          Notes
  * 2019-07-11     Elaine.Zhang      first implementation
  *
  ******************************************************************************
  */

#ifndef _DRV_CLOCK_H_
#define _DRV_CLOCK_H_

#include <hal_base.h>

#ifdef RT_CONSOLE_DEVICE_NAME
#define RT_CONSOLE_DEVICE_UART(ID) \
    ((strcmp(RT_CONSOLE_DEVICE_NAME, "uart"#ID)) ? 0:1)
#else
#define RT_CONSOLE_DEVICE_UART(ID) 0
#endif

#define INIT_CLK(NAME, ID, RATE)                     \
    { .name = NAME, .clk_id = ID, .init_rate = RATE, }

struct clk_gate
{
    uint32_t gate_id;
    int enable_count;
    int ref_count;
    rt_slist_t node;
};

struct clk_init
{
    const char *name;
    uint32_t clk_id;
    uint32_t init_rate;
};

struct clk_unused
{
    uint32_t is_pmucru : 1;
    uint32_t gate_con : 31;
    uint32_t gate_val;
};

struct pd
{
    uint32_t pd_id;
    int enable_count;
    int ref_count;
    rt_slist_t node;
};

/**
 * @brief  clk set enable by id.
 * @param  gate_id: gate id.
 * @retval RT_EOK: clk set enable success.
 * @retval -RT_ERROR: clk set enable failed.
 */
static inline rt_err_t clk_enable_by_id(int gate_id)
{
#ifdef HAL_CRU_MODULE_ENABLED
    return (HAL_CRU_ClkEnable(gate_id) == HAL_OK) ? RT_EOK : -RT_ERROR;
#else
    return RT_EOK;
#endif
}

/**
 * @brief  clk set disable by id.
 * @param  gate_id: gate id.
 * @retval RT_EOK: clk set disable success.
 * @retval -RT_ERROR: clk set disable failed.
 */
static inline rt_err_t clk_disable_by_id(int gate_id)
{
#ifdef HAL_CRU_MODULE_ENABLED
    return (HAL_CRU_ClkDisable(gate_id) == HAL_OK) ? RT_EOK : -RT_ERROR;
#else
    return RT_EOK;
#endif
}

struct clk_gate *get_clk_gate_from_id(int gate_id);
void put_clk_gate(struct clk_gate *gate);
rt_err_t clk_enable(struct clk_gate *gate);
rt_err_t clk_disable(struct clk_gate *gate);
int clk_is_enabled(struct clk_gate *gate);
uint32_t clk_get_rate(eCLOCK_Name clk_id);
rt_err_t clk_set_rate(eCLOCK_Name clk_id, uint32_t rate);
#if defined(RT_USING_PMU)
struct pd *get_pd_from_id(ePD_Id pd_id);
void put_pd(struct pd *power);
rt_err_t pd_on(struct pd *power);
rt_err_t pd_off(struct pd *power);
#endif
void clk_init(const struct clk_init *clk_inits, bool clk_dump);
void clk_disable_unused(const struct clk_unused *clks_unused);

#endif // _DRV_CLOCK_H_
