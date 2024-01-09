/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-12     CDT          first version
 */


#ifndef __DRV_PM_H__
#define __DRV_PM_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <drv_config.h>

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif
/*******************************************************************************
 *  @defgroup sleep_mode_map
 *  @brief The mapping of rtt pm sleep mode to hc32 low power mode
 * --------------------------------------------------
 * rtt pm sleep mode |  hc32 low power mode
 * ------------------|-------------------------------
 *    idle           |    sleep
 *    deep           |    stop
 *    standby        |    power down mode 1 or 2, selection @ref PM_SLEEP_STANDBY_CFG
 *    shutdown mode  |    power down mode 3 or 4, selection @ref PM_SLEEP_SHUTDOWN_CFG
 ******************************************************************************/

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
typedef void (* run_mode_init_func)(uint8_t run_mode);

/**
 * @brief  run mode config @ref PM_RUN_MODE_CFG
 */
struct pm_run_mode_config
{
    run_mode_init_func sys_clk_cfg;
};

/**
 * @brief  sleep idle config @ref PM_SLEEP_IDLE_CFG
 */
struct pm_sleep_mode_idle_config
{
    uint8_t pwc_sleep_type;              /*!< WFI/WFE selection and SEVONPEND configuration
                                            @ref PWC_Sleep_Type */
};


/**
 * @brief  sleep deep config @ref PM_SLEEP_DEEP_CFG
 */
struct pm_sleep_mode_deep_config
{
    stc_pwc_stop_mode_config_t cfg;
    uint8_t pwc_stop_type;              /*!< WFI/WFE selection and SEVONPEND configuration
                                            @ref PWC_Stop_Type */
};


/**
 * @brief  sleep standby config @ref PM_SLEEP_STANDBY_CFG
 */
struct pm_sleep_mode_standby_config
{
    stc_pwc_pd_mode_config_t cfg;       /*!< cfg.u8Mode could only be PWC_PD_MD1 or  PWC_PD_MD2,
                                            @ref PWC_PDMode_Sel, @ref  sleep_mode_map */
};

/**
 * @brief  sleep shutdown config @ref PM_SLEEP_SHUTDOWN_CFG
 */
struct pm_sleep_mode_shutdown_config
{
    stc_pwc_pd_mode_config_t cfg;       /*!< cfg.u8Mode could only be PWC_PD_MD3 or  PWC_PD_MD4,
                                              @ref PWC_PDMode_Sel, @ref sleep_mode_map */
};

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#if defined(HC32F4A0)
#define PM_CHECK_EFM()                  ((EFM_GetStatus(EFM_FLAG_RDY) == SET) && (EFM_GetStatus(EFM_FLAG_RDY1) == SET))
#elif defined(HC32F460)
#define PM_CHECK_EFM()                  ((EFM_GetStatus(EFM_FLAG_RDY) == SET))
#endif
#define PM_CHECK_XTAL()                 ((CM_CMU->XTALSTDCR & CLK_XTALSTD_ON) == 0)
#define PM_CHECK_DMA()                                              \
(                                       (DMA_GetTransStatus(CM_DMA1, DMA_STAT_TRANS_DMA) == RESET) && \
                                        (DMA_GetTransStatus(CM_DMA2, DMA_STAT_TRANS_DMA) == RESET))
#define PM_CHECK_SWDT()                                             \
(                                       ((CM_ICG->ICG0 & ICG_SWDT_RST_START) != ICG_SWDT_RST_START) || \
                                        ((CM_ICG->ICG0 & ICG_SWDT_LPM_CNT_STOP) == ICG_SWDT_LPM_CNT_STOP))
#define PM_CHECK_PVD()                                              \
(                                       ((CM_PWC->PVDCR1 & (PWC_PVDCR1_PVD1IRE | PWC_PVDCR1_PVD1IRS)) != (PWC_PVDCR1_PVD1IRE | PWC_PVDCR1_PVD1IRS)) && \
                                        ((CM_PWC->PVDCR1 & (PWC_PVDCR1_PVD2IRE | PWC_PVDCR1_PVD2IRS)) != (PWC_PVDCR1_PVD2IRE | PWC_PVDCR1_PVD2IRS)))
#define PM_SLEEP_SHUTDOWN_CHECK()                                   \
(                                       PM_CHECK_EFM() &&           \
                                        PM_CHECK_XTAL() &&          \
                                        PM_CHECK_SWDT() &&          \
                                        PM_CHECK_PVD())
#define PM_SLEEP_DEEP_CHECK()                                       \
(                                       PM_CHECK_EFM() &&           \
                                        PM_CHECK_XTAL() &&          \
                                        PM_CHECK_DMA())
/*
* please make sure the state of the peripherals meet the requirements of entering the specified sleep mode,
* otherwise system may not entering the right sleep mode or something unexpected may happen.
* PM_SLEEP_CHECK is a demo of requirements and may not be comprehensive,
* please refer user manual to know all the requirements in detail.
*/
#define PM_SLEEP_CHECK(mode)                                        \
(                                       (mode ==  PM_SLEEP_MODE_STANDBY && PM_SLEEP_SHUTDOWN_CHECK()) || \
(                                       (mode ==  PM_SLEEP_MODE_SHUTDOWN && PM_SLEEP_SHUTDOWN_CHECK()) || \
                                        (mode ==  PM_SLEEP_MODE_DEEP && PM_SLEEP_DEEP_CHECK())|| \
                                        (mode <=  PM_SLEEP_MODE_IDLE)))

/**
 * @defgroup PWC_Sleep_Type PWC sleep mode type.
 * @{
 */
#ifndef PWC_SLEEP_WFI
#define PWC_SLEEP_WFI                   (0x00U)                 /*!< Enter sleep mode by WFI, and wake-up by interrupt handle. */
#endif
#ifndef PWC_SLEEP_WFE_INT
#define PWC_SLEEP_WFE_INT               (0x01U)                 /*!< Enter sleep mode by WFE, and wake-up by interrupt request(SEVONPEND=1). */
#endif
#ifndef PWC_SLEEP_WFE_EVT
#define PWC_SLEEP_WFE_EVT               (0x02U)                 /*!< Enter sleep mode by WFE, and wake-up by event(SEVONPEND=0). */
#endif
/**
 * @}
 */

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/


#ifdef __cplusplus
}
#endif

#endif /* __DRV_PM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
