/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-09     CDT          first version
 */

#include <board.h>
#include <drv_wktm.h>

#if defined(RT_USING_PM)

#if defined(BSP_USING_PM)

// #define DRV_DEBUG
#define LOG_TAG                     "drv_wktm"
#include <drv_log.h>

#define CMPVAL_MAX                  (0xFFFUL)

#if defined(BSP_USING_WKTM_XTAL32)
    #define PWC_WKT_CLK_SRC             (PWC_WKT_CLK_SRC_XTAL32)
    #define PWC_WKT_COUNT_FRQ           (32768UL)
#elif defined(BSP_USING_WKTM_64HZ)
    #define PWC_WKT_CLK_SRC             (PWC_WKT_CLK_SRC_64HZ)
    #define PWC_WKT_COUNT_FRQ           (64U)
#else
    #if defined(HC32F4A0)
        #define PWC_WKT_CLK_SRC             (PWC_WKT_CLK_SRC_RTCLRC)
    #elif defined(HC32F460) || defined(HC32F448)
        #define PWC_WKT_CLK_SRC             (PWC_WKT_CLK_SRC_LRC)
    #endif
    #define PWC_WKT_COUNT_FRQ           (32768UL)
#endif

static rt_uint32_t cmpval = CMPVAL_MAX;

/**
 * This function get current count value of WKTM
 * @param  None
 * @return the count value
 */
rt_uint32_t hc32_wktm_get_current_tick(void)
{
    return (CMPVAL_MAX);
}

/**
 * This function get the max value that WKTM can count
 * @param  None
 * @return the max count
 */
rt_uint32_t hc32_wktm_get_tick_max(void)
{
    return (CMPVAL_MAX);
}

/**
 * This function start WKTM with reload value
 * @param reload The value that Comparison value of the Counter
 * @return RT_EOK
 */
rt_err_t hc32_wktm_start(rt_uint32_t reload)
{
    /* 64HZ must use XTAL32 and run RTC */
#if defined(BSP_USING_WKTM_64HZ)
#if defined(BSP_RTC_USING_XTAL32)
    if (DISABLE == RTC_GetCounterState())
    {
        /* #error "Please start the RTC!" */
        RT_ASSERT(0);
    }
#else
#error "Please enable XTAL32 and start the RTC!"
#endif
#endif
    if (reload > CMPVAL_MAX || !reload)
    {
        return -RT_ERROR;
    }
    cmpval = reload;
    PWC_WKT_SetCompareValue(cmpval);
    PWC_WKT_Cmd(ENABLE);

    return RT_EOK;
}

/**
 * @brief  This function stop WKTM
 * @param  None
 * @retval None
 */
void hc32_wktm_stop(void)
{
    PWC_WKT_Cmd(DISABLE);
}

/**
 * This function get the count clock of WKTM
 * @param  None
 * @return the count clock frequency in Hz
 */
rt_uint32_t hc32_wktm_get_countfreq(void)
{
    return PWC_WKT_COUNT_FRQ;
}

/**
 * @brief  This function initialize the wktm
 * @param  None
 * @retval type code
 */
int rt_hw_wktm_init(void)
{
    rt_err_t ret = RT_EOK;

    /* Disable WKTM in advance */
    PWC_WKT_Cmd(DISABLE);
    /* WKTM init */
    PWC_WKT_Config(PWC_WKT_CLK_SRC, CMPVAL_MAX);

#if defined(HC32F4A0)
    /* F4A0 if select RTCLRC clock need open the LRCEN by RTC->CR3 register */
#if (PWC_WKT_CLK_SRC == PWC_WKT_CLK_SRC_RTCLRC)
    MODIFY_REG8(CM_RTC->CR3, RTC_CR3_LRCEN, 0x01U << RTC_CR3_LRCEN_POS);
#endif
#endif

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_wktm_init);

#endif

#endif  /* RT_USING_PM */
