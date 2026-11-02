/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_PD_RA6W1_H
#define BSP_PD_RA6W1_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "bsp_rtc.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**
 * Number of Power Domain IDs defined for this device
 */
#define BSP_PD_ID_COUNT           (3)

/* For retention memory bank*/
#define RETENTION_MEM_NONE        0x00
#define RETENTION_MEM_BANK0       0x01 // 0x00180000 ~ 0x00181fff
#define RETENTION_MEM_BANK1       0x02 // 0x00182000 ~ 0x00184000
#define RETENTION_MEM_BANK2       0x04 // 0x00184000 ~
#define RETENTION_MEM_BANK_ALL    0x07 // All

/* Alias name of BSP_WAKEUP_RESET_WITH_RETENTION */
#define BSP_WAKEUP_RETENTION      (BSP_WAKEUP_RESET_WITH_RETENTION)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Hardware power domains.*/
typedef enum e_bsp_power_domain
{
    BSP_PD_AON = 0,                    ///< Always on power domain
    BSP_PD_PHY = 1,                    ///< PHY power domain
    BSP_PD_MAC = 2,                    ///< MAC power domain
} bsp_power_domain_t;

/* Wakeup edge for individual pins */
typedef enum e_bsp_wakeup_edge
{
    BSP_WAKEUP_EDGE_LOW = 0,           ///< Low
    BSP_WAKEUP_EDGE_HIGH               ///< High
} bsp_io_wakeup_edge_t;

/* Wakeup pins */
typedef enum e_bsp_wakeup_pin
{
    BSP_WAKEUP_GPIO_P0_00 = (0x01 << 0),
    BSP_WAKEUP_GPIO_P0_08 = (0x01 << 1),
    BSP_WAKEUP_GPIO_P0_09 = (0x01 << 2),
    BSP_WAKEUP_GPIO_P0_10 = (0x01 << 3),
    BSP_WAKEUP_GPIO_P0_11 = (0x01 << 4),
    BSP_WAKEUP_GPIO_P0_12 = (0x01 << 5),
    BSP_WAKEUP_GPIO_P0_13 = (0x01 << 6),
    BSP_WAKEUP_GPIO_P1_10 = (0x01 << 7),
    BSP_WAKEUP_GPIO_P1_11 = (0x01 << 8),
    BSP_WAKEUP_GPIO_P1_12 = (0x01 << 9),
    BSP_WAKEUP_GPIO_P1_13 = (0x01 << 10),
} bsp_io_wakeup_pin_t;

// TIN-TODO: This enum was located in bsp_common and guarded with the same features as the RTC function.
// Consider moving this under a header file of the power manager.

/*
 * The value below consists of a bit mask and the rest is a combination of the corresponding values.
 * These values are based on RTC->WAKEUP_SRC_CLR_SIG_REG
 * BSP_WAKEUP_RESET                     0x00
 * BSP_WAKEUP_SOURCE_GPIO               0x01
 * BSP_WAKEUP_SOURCE_WAKEUP_COUNTER     0x02
 * BSP_WAKEUP_SOURCE_POR                0x04
 * BSP_WAKEUP_SOURCE_WATCHDOG           0x08
 * BSP_WAKEUP_SENSOR                    0x10
 * BSP_WAKEUP_PULSE                     0x20
 * BSP_WAKEUP_TIMER                     0x40  - Only in sleep 4/5
 *
 * This value is based on RTC->RTM_INFO, written by software
 * BSP_WAKEUP_RESET_WITH_RETENTION      0x80
 */
typedef enum e_bsp_wakeup_source_mask
{
    BSP_WAKEUP_RESET                 = 0x00,                ///< Internal reset
    BSP_WAKEUP_SOURCE_GPIO           = 0x01,                ///< Boot from GPIO wake up signal
    BSP_WAKEUP_SOURCE_WAKEUP_COUNTER = 0x02,                ///< Boot from wake up counter
    BSP_WAKEUP_GPIO_WAKEUP_COUNTER   = 0x03,                ///< Boot from wake up counter or GPIO wakeup
    BSP_WAKEUP_SOURCE_POR            = 0x04,                ///< Boot from power on reset
    BSP_WAKEUP_SOURCE_POR_GPIO       = 0x05,                ///< FPGA only
    BSP_WAKEUP_SOURCE_WATCHDOG       = 0x08,                ///< Boot from RTC_watch dog (not cpu watchdog)
    BSP_WAKEUP_WATCHDOG_GPIO         = 0x09,                ///< Boot from watch dog or GPIO wakeup
    BSP_WAKEUP_SOURCE_SENSOR         = 0x10,                ///< Boot from sensor (ADC)
    BSP_WAKEUP_SOURCE_PULSE          = 0x20,                ///< Boot from pulse sensor

    BSP_WAKEUP_SENSOR_GPIO                          = 0x11, ///< Boot from sensor or GPIO wakeup
    BSP_WAKEUP_SENSOR_WAKEUP_COUNTER                = 0x12, ///< Boot from sensor or wakeup counter
    BSP_WAKEUP_SENSOR_GPIO_COUNTER                  = 0x13, ///< Boot from sensor or external or wakeup counter
    BSP_WAKEUP_SENSOR_WATCHDOG                      = 0x18, ///< Boot from sensor or RTC watch dog
    BSP_WAKEUP_SENSOR_GPIO_WATCHDOG                 = 0x19, ///< Boot from sensor or GPIO or watch dog
    BSP_WAKEUP_RESET_WITH_RETENTION                 = 0x80, ///< Boot from internal reset and have retention info
    BSP_WAKEUP_GPIO_WITH_RETENTION                  = 0x81, ///< Boot from GPIO and have retention info
    BSP_WAKEUP_COUNTER_WITH_RETENTION               = 0x82, ///< Boot from counter and have retention info (most common)
    BSP_WAKEUP_GPIO_WAKEUP_COUNTER_WITH_RETENTION   = 0x83, ///< Boot from GPIO or wakeup counter with retention
    BSP_WAKEUP_WATCHDOG_WITH_RETENTION              = 0x88, ///< Boot from RTC watch dog with retention
    BSP_WAKEUP_WATCHDOG_GPIO_WITH_RETENTION         = 0x89, ///< Boot from watch dog or GPIO
    BSP_WAKEUP_SENSOR_WITH_RETENTION                = 0x90, ///< Boot from sensor with retention
    BSP_WAKEUP_SENSOR_GPIO_WITH_RETENTION           = 0x91, ///< Boot from sensor or GPIO with retention
    BSP_WAKEUP_SENSOR_WAKEUP_COUNTER_WITH_RETENTION = 0x92, ///< Boot from sensor or wakeup counter with retention
    BSP_WAKEUP_SENSOR_GPIO_COUNTER_WITH_RETENTION   = 0x93, ///< Boot from sensor or GPIO or wakeup counter with retention
    BSP_WAKEUP_SENSOR_WATCHDOG_WITH_RETENTION       = 0x98, ///< Boot from sensor or watchdog with retention
    BSP_WAKEUP_SENSOR_GPIO_WATCHDOG_WITH_RETENTION  = 0x99, ///< Boot from sensor or GPIO or watchdog with retention

    BSP_WAKEUP_ALLTIMER_WITH_RETENTION = 0xC2,              ///< Boot from rtc, hw & mac-timer and have retention info (most common)
    BSP_WAKEUP_HWTIMER_WITH_RETENTION  = 0xC0,              ///< Boot from hw & mac-timer and have retention info (most common)

    BSP_WAKEUP_SOURCE_UNKNOWN = 0xff,
} bsp_wakeup_source_mask_t;

typedef uint32_t bsp_wakeup_source_t;

typedef void (* BSP_RTC_BOD_CALLBACK_TYPE)(void);

typedef struct
{
    void (* func)(void *);
    void * param;
} BSP_RTC_TIME_EXP_CALLBACK_TYPE;

/* Wakeup edge for individual pins */

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/* Used internaly by bsp_pd.c */
void bsp_prv_pd_masks_get(bsp_power_domain_t power_domain, uint32_t * sleep_mask, uint32_t * is_up_mask);

/**
 * @brief Enable a power domain by clearing its sleep status bit
 *
 * @param [in] sleep_mask   mask for the power domain's SLEEP status bit
 * @param [in] is_aon       whether the power domain is part of the AON domain group
 *
 * @note    Multiple power domains may be enabled if more than one bits are set in \p sleep_mask
 */
__STATIC_INLINE void bsp_prv_pd_enable (uint32_t sleep_mask, bool is_aon)
{
    FSP_PARAMETER_NOT_USED(is_aon);

    CRG_TOP->PMU_CTRL_REG &= ~sleep_mask;
}

/**
 * @brief Disable a power domain by setting its sleep status bit
 *
 * @param [in] sleep_mask   mask for the power domain's SLEEP status bit
 * @param [in] is_aon       whether the power domain is part of the AON domain group
 *
 * @note    Multiple power domains may be disabled if more than one bits are set in \p sleep_mask
 */
__STATIC_INLINE void bsp_prv_pd_disable (uint32_t sleep_mask, bool is_aon)
{
    FSP_PARAMETER_NOT_USED(is_aon);
    CRG_TOP->PMU_CTRL_REG |= sleep_mask;
}

/**
 * @brief Check if a power domain by checking its is-up status bit
 *
 * @param [in] is_up_mask   mask for the power domain's IS_UP status bit
 *
 * @return  True iff the power domains corresponding to the set bits in \p is_up_mask are up.
 *
 * @note    Multiple power domains may be checked if more than one bits are set in \p is_up_mask
 */
__STATIC_INLINE bool bsp_prv_pd_is_up_check (uint32_t is_up_mask)
{
    return (CRG_TOP->SYS_STATUS_REG & is_up_mask) == is_up_mask;
}

bsp_wakeup_source_mask_t R_BSP_WakeupSourceGet(void);

void SystemWakeupSourceUpdate(void);
void R_BSP_WakeupSourceClear(bool clear);

bsp_io_wakeup_pin_t bsp_prv_port_pin_to_wakeup_gpio(bsp_io_port_pin_t port_pin);
bsp_io_port_pin_t   bsp_prv_wakeup_pin_to_port_pin(bsp_io_wakeup_pin_t wakeup_gpio);
bsp_io_wakeup_pin_t R_BSP_WakeupSourcePinGet(void);
void                R_BSP_WakeupSourcePinClear(void);
void                R_BSP_WakeupSourcePinSet(bsp_io_wakeup_pin_t pin, bsp_io_wakeup_edge_t edge);
void                R_BSP_WakeupSourcePinSetRetained(bsp_io_wakeup_pin_t pin, bsp_io_wakeup_edge_t edge);
void                R_BSP_WakeupSourcePinUnSet(bsp_io_wakeup_pin_t pin);

void     R_BSP_RetainedMemFlagSet(void);
void     R_BSP_RetainedMemFlagClear(void);
uint32_t R_BSP_RetainedMemFlagGet(void);

void     bsp_prv_pd_wakeup_counter_set(uint32_t sleep_id, uint64_t wakeup_time);
uint64_t bsp_prv_pd_wakeup_counter_get(void);
uint32_t bsp_prv_pd_sleep_id_get(void);

void bsp_rtc_enable_bod(BSP_RTC_BOD_CALLBACK_TYPE brown_callback, BSP_RTC_BOD_CALLBACK_TYPE black_callback);
void bsp_rtc_disable_bod(void);
int  bsp_rtc_get_brown_out_status(void);

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
