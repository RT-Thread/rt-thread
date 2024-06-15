/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-12     CDT          first version
 */

#ifndef __PM_CONFIG_H__
#define __PM_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_PM
extern void rt_hw_board_pm_sysclk_cfg(uint8_t run_mode);

#ifndef PM_TICKLESS_TIMER_ENABLE_MASK
#define PM_TICKLESS_TIMER_ENABLE_MASK                                          \
(   (1UL << PM_SLEEP_MODE_IDLE)  |                                             \
    (1UL << PM_SLEEP_MODE_DEEP))
#endif

/**
 * @brief  run mode config @ref pm_run_mode_config structure
 */
#ifndef PM_RUN_MODE_CFG
#define PM_RUN_MODE_CFG                                                        \
    {                                                                          \
       .sys_clk_cfg = rt_hw_board_pm_sysclk_cfg                                \
    }
#endif /* PM_RUN_MODE_CFG */

/**
 * @brief  sleep idle config @ref pm_sleep_mode_idle_config structure
 */
#ifndef PM_SLEEP_IDLE_CFG
#define PM_SLEEP_IDLE_CFG                                                      \
{                                                                              \
    .pwc_sleep_type = PWC_SLEEP_WFE_INT,                                       \
}
#endif /*PM_SLEEP_IDLE_CFG*/

/**
 * @brief  sleep deep config @ref pm_sleep_mode_deep_config structure
 */
#ifndef PM_SLEEP_DEEP_CFG
#define PM_SLEEP_DEEP_CFG                                                      \
{                                                                              \
    {                                                                          \
        .u16Clock = PWC_STOP_CLK_KEEP,                                         \
        .u8StopDrv = PWC_STOP_DRV_HIGH,                                        \
        .u16ExBusHold = PWC_STOP_EXBUS_HIZ,                                    \
        .u16FlashWait = PWC_STOP_FLASH_WAIT_ON,                                \
    },                                                                         \
    .pwc_stop_type = PWC_STOP_WFE_INT,                                         \
}
#endif /*PM_SLEEP_DEEP_CFG*/

/**
 * @brief  sleep standby config @ref pm_sleep_mode_standby_config structure
 */
#ifndef PM_SLEEP_STANDBY_CFG
#define PM_SLEEP_STANDBY_CFG                                                   \
{                                                                              \
    {                                                                          \
        .u8Mode = PWC_PD_MD1,                                                  \
        .u8IOState = PWC_PD_IO_KEEP1,                                          \
        .u8VcapCtrl = PWC_PD_VCAP_0P047UF,                                     \
    },                                                                         \
}
#endif /*PM_SLEEP_STANDBY_CFG*/

/**
 * @brief  sleep shutdown config @ref pm_sleep_mode_shutdown_config structure
 */
#ifndef PM_SLEEP_SHUTDOWN_CFG
#define PM_SLEEP_SHUTDOWN_CFG                                                  \
{                                                                              \
    {                                                                          \
        .u8Mode = PWC_PD_MD3,                                                  \
        .u8IOState = PWC_PD_IO_KEEP1,                                          \
        .u8VcapCtrl = PWC_PD_VCAP_0P047UF,                                     \
    },                                                                         \
}
#endif /*PM_SLEEP_SHUTDOWN_CFG*/

#endif /* BSP_USING_PM */

#ifdef __cplusplus
}
#endif

#endif /* __PM_CONFIG_H__ */
