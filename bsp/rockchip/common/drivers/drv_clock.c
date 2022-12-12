/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_clock.c
  * @version V0.1
  * @brief   cru clock interface
  *
  * Change Logs:
  * Date           Author          Notes
  * 2019-07-11     Elaine.Zhang      first implementation
  *
  ******************************************************************************
  */

/** @addtogroup RKBSP_Driver_Reference
*  @{
*/

/** @addtogroup Clock
 *  @{
 */

/** @defgroup Clock_How_To_Use How To Use
 *  @{

The Clock driver use to configure clock frequency, enable/disable clock output, clock reset, power on/off power domain,
 it can be used in the following three scenarios:

- **Configure clock frequency**:
    - The device set clock rate by clk_set_rate(eCLOCK_Name clk_id, uint32_t rate);
    - The device get clock rate by clk_get_rate(eCLOCK_Name clk_id);

- **Enable/disable clock output**:
    - The device get clock by get_clk_gate_from_id(int clk_id);
    - The device set clock enable/disable by clk_enable(struct clk_gate *gate) or clk_disable(struct clk_gate *gate);

- **Power on/off power domain**:
    - The device get pd by get_pd_from_id(int pd_id);
    - The device power on/off pd by pd_power(struct pd *power, int on);

 @} */

#include <rtdevice.h>
#include <rtthread.h>

#if defined(RT_USING_CRU)

#include "hal_base.h"
#include "drv_clock.h"

static const struct clk_init *g_clk_init = RT_NULL;

static rt_slist_t clk_gate_list;

static struct rt_mutex clk_lock;
static struct rt_mutex gate_lock;
#if defined(RT_USING_PMU)
static struct rt_mutex pd_lock;
static rt_slist_t pd_list;
#endif

/********************* Public Function Definition ****************************/

/** @defgroup CLOCK_Public_Functions Public Functions
 *  @{
 */

/**
 * @brief  clk set enable.
 * @param  gate: get_clk_gate_from_id.
 * @retval -RT_EINVAL: struct gate is invalid argument
 * @retval -RT_ERROR: clk enable failed.
 */
rt_err_t clk_enable(struct clk_gate *gate)
{
    rt_err_t error = RT_EOK;
    HAL_Status ret;

    if (!gate)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&gate_lock, RT_WAITING_FOREVER);

    if (gate->enable_count == 0)
    {
        ret = HAL_CRU_ClkEnable(gate->gate_id);
        if (ret != HAL_OK)
            error = -RT_ERROR;
    }
    gate->enable_count++;

    rt_mutex_release(&gate_lock);

    return error;
}

/**
 * @brief  clk set disable.
 * @param  gate: get_clk_gate_from_id.
 * @retval -RT_EINVAL: struct gate is invalid argument
 * @retval -RT_ERROR: clk disable failed.
 */
rt_err_t clk_disable(struct clk_gate *gate)
{
    rt_err_t error = RT_EOK;
    HAL_Status ret;

    if (!gate)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&gate_lock, RT_WAITING_FOREVER);

    if (gate->enable_count == 0)
    {
        rt_kprintf("It may be wrong to used, make enable first.(gate_id = %d)\n", __func__, gate->gate_id);
        goto out;
    }

    if (--gate->enable_count > 0)
    {
        goto out;
    }
    ret = HAL_CRU_ClkDisable(gate->gate_id);
    if (ret != HAL_OK)
        error = -RT_ERROR;

out:
    rt_mutex_release(&gate_lock);

    return error;
}

/**
 * @brief  clk is enabled.
 * @param gate: get_clk_gate_from_id.
 * @retval 0: clk is disabled
 * @retval 1: clk is enabled
 */
int clk_is_enabled(struct clk_gate *gate)
{
    if (!gate)
    {
        return 0;
    }

    return HAL_CRU_ClkIsEnabled(gate->gate_id);
}

/**
 * @brief  get clk gate by id.
 * @param gate_id: clk gate id.
 * @return struct of type clk_gate
 */
struct clk_gate *get_clk_gate_from_id(int gate_id)
{
    struct clk_gate *clk_gate;

    rt_mutex_take(&gate_lock, RT_WAITING_FOREVER);

    rt_slist_for_each_entry(clk_gate, &clk_gate_list, node)
    {
        if (clk_gate->gate_id == gate_id)
        {
            goto out;
        }
    }

    clk_gate = rt_calloc(1, sizeof(struct clk_gate));
    clk_gate->gate_id = gate_id;
    clk_gate->enable_count = 0;
    rt_slist_insert(&clk_gate_list, &clk_gate->node);

out:
    clk_gate->ref_count++;
    rt_mutex_release(&gate_lock);

    return clk_gate;
}

/**
 * @brief  put clk gate.
 * @param gate: get_clk_gate_from_id.
 */
void put_clk_gate(struct clk_gate *gate)
{
    if (!gate)
        return;

    rt_mutex_take(&gate_lock, RT_WAITING_FOREVER);

    if (--gate->ref_count > 0)
    {
        goto out;
    }
    rt_slist_remove(&clk_gate_list, &gate->node);
    rt_free(gate);

out:
    rt_mutex_release(&gate_lock);
}

/**
 * @brief  clk get rate.
 * @param clk_id: clk id.
 * @return the return value of HAL_CRU_ClkGetFreq, which returns the frequency value in unit hz.
 */
uint32_t clk_get_rate(eCLOCK_Name clk_id)
{
    uint32_t rate;

    rt_mutex_take(&clk_lock, RT_WAITING_FOREVER);

    rate = HAL_CRU_ClkGetFreq(clk_id);

    rt_mutex_release(&clk_lock);

    return rate;
}

/**
 * @brief  clk set rate.
 * @param clk_id: clk id.
 * @param rate: frequency value hz.
 * @retval RT_EOK: clk set successful
 * @retval HAL_OK: HAL_CRU_ClkSetFreq set frequency successfully
 * @retval HAL_ERROR: HAL_CRU_ClkSetFreq set frequency failed
 * @retval HAL_INVAL: HAL_CRU_ClkSetFreq set frequency unsupported
 */
rt_err_t clk_set_rate(eCLOCK_Name clk_id, uint32_t rate)
{
    rt_err_t error = RT_EOK;

    if (rate == clk_get_rate(clk_id))
        return error;

    rt_mutex_take(&clk_lock, RT_WAITING_FOREVER);

    error = HAL_CRU_ClkSetFreq(clk_id, rate);

    rt_mutex_release(&clk_lock);

    return error;
}

#if defined(RT_USING_PMU)

/**
 * @brief  pd power on.
 * @param power: get_pd_from_id.
 * @retval -RT_EINVAL: struct pd is invalid argument
 * @retval -RT_ERROR: pd power on failed.
 * @retval RT_EOK: pd power on success.
 */
rt_err_t pd_on(struct pd *power)
{
    rt_err_t error = RT_EOK;
    HAL_Status ret;

    if (!power)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&pd_lock, RT_WAITING_FOREVER);

    if (power->enable_count == 0)
    {
        ret = HAL_PD_On(power->pd_id);
        if (ret != HAL_OK)
            error = -RT_ERROR;
    }
    power->enable_count++;
    rt_mutex_release(&pd_lock);

    return error;
}

/**
 * @brief  pd power off.
 * @param power: get_pd_from_id.
 * @retval -RT_EINVAL: struct pd is invalid argument
 * @retval -RT_ERROR: pd power off failed.
 * @retval RT_EOK: pd power off success.
 */
rt_err_t pd_off(struct pd *power)
{
    rt_err_t error = RT_EOK;
    HAL_Status ret;

    if (!power)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&pd_lock, RT_WAITING_FOREVER);

    if (--power->enable_count > 0)
    {
        goto out;
    }
    ret = HAL_PD_Off(power->pd_id);
    if (ret != HAL_OK)
        error = -RT_ERROR;

out:
    rt_mutex_release(&pd_lock);

    return error;
}

/**
 * @brief  get pd by id.
 * @param pd_id: pd id.
 * @return struct of type pd
 */
struct pd *get_pd_from_id(ePD_Id pd_id)
{
    struct pd *pd;

    if (!pd_id)
        return NULL;

    rt_mutex_take(&pd_lock, RT_WAITING_FOREVER);

    rt_slist_for_each_entry(pd, &pd_list, node)
    {
        if (pd->pd_id == pd_id)
        {
            goto out;
        }
    }
    pd = rt_calloc(1, sizeof(struct pd));
    pd->pd_id = pd_id;
    pd->enable_count = 0;
    rt_slist_insert(&pd_list, &pd->node);

out:
    pd->ref_count++;
    rt_mutex_release(&pd_lock);

    return pd;
}

/**
 * @brief  put pd.
 * @param power: get_pd_from_id.
 */
void put_pd(struct pd *power)
{
    if (!power)
        return;

    rt_mutex_take(&pd_lock, RT_WAITING_FOREVER);

    if (--power->ref_count > 0)
    {
        goto out;
    }
    rt_slist_remove(&pd_list, &power->node);
    rt_free(power);

out:
    rt_mutex_release(&pd_lock);
}
#endif

/**
 * @brief  clock dev init.
 * @return RT_EOK
 */
int clock_dev_init(void)
{
    if (rt_mutex_init(&(clk_lock), "clkLock", RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        RT_ASSERT(0);
    }
    if (rt_mutex_init(&(gate_lock), "gateLock", RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        RT_ASSERT(0);
    }
    rt_slist_init(&clk_gate_list);
#if defined(RT_USING_PMU)
    if (rt_mutex_init(&(pd_lock), "pdLock", RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        RT_ASSERT(0);
    }
    rt_slist_init(&pd_list);
#endif

    return RT_EOK;
}
INIT_BOARD_EXPORT(clock_dev_init);

/**
 * @brief  clock init frequency.
 * @param clk_inits: some need init clks.
 * @param clk_dump: if need printf clk get freq after setting.
 */
void clk_init(const struct clk_init *clk_inits, bool clk_dump)
{
    const struct clk_init *clks = clk_inits;

    while (clks->name)
    {
        if (clks->init_rate)
        {
            HAL_CRU_ClkSetFreq(clks->clk_id, clks->init_rate);
        }
        if (clk_dump)
            rt_kprintf("%s: %s = %d\n", __func__, clks->name, HAL_CRU_ClkGetFreq(clks->clk_id));
        clks++;
    }
    g_clk_init = clk_inits;
}

/**
 * @brief  clock disable unused.
 * @param clks_unused: disable some not needed clks.
 */
void clk_disable_unused(const struct clk_unused *clks_unused)
{
    const struct clk_unused *clks = clks_unused;

    while (clks->gate_val)
    {
        if (clks->is_pmucru)
        {
#if defined(CRU_PMU_CLKGATE_CON0_OFFSET)
            CRU->PMU_CLKGATE_CON[clks->gate_con] = clks->gate_val;
#endif
        }
        else
        {
            CRU->CRU_CLKGATE_CON[clks->gate_con] = clks->gate_val;
        }
        clks++;
    }
}

#if defined(RT_USING_CRU_DUMP)

/**
 * @brief  clock dump frequency, dump cru registers, used for debug.
 */
static void clk_dump(void)
{
    const struct clk_init *clks = g_clk_init;
    int i;

    if (clks)
    {
        while (clks->name)
        {
            rt_kprintf("%s: %s[%x] = %d\n", __func__, clks->name, clks->clk_id,
                       HAL_CRU_ClkGetFreq(clks->clk_id));
            clks++;
        }
    }
    for (i = 0; i < HAL_ARRAY_SIZE(CRU->CRU_CLKSEL_CON); i++)
    {
        rt_kprintf("%s: cru_sel_con[%d] = %lx\n", __func__, i, CRU->CRU_CLKSEL_CON[i]);
    }
    for (i = 0; i < HAL_ARRAY_SIZE(CRU->CRU_CLKGATE_CON); i++)
    {
        rt_kprintf("%s: cru_gate_con[%d] = %lx\n", __func__, i, CRU->CRU_CLKGATE_CON[i]);
    }
    for (i = 0; i < HAL_ARRAY_SIZE(CRU->CRU_SOFTRST_CON); i++)
    {
        rt_kprintf("%s: cru_softreset_con[%d] = %lx\n", __func__, i, CRU->CRU_SOFTRST_CON[i]);
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
MSH_CMD_EXPORT(clk_dump, cru drive test. e.g: clk_dump);
#endif
#endif

/** @} */

#endif

/** @} */

/** @} */
