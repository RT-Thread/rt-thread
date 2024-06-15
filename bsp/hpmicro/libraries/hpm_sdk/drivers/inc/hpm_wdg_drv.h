/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_WDG_DRV_H
#define HPM_WDG_DRV_H

/**
 * @brief WDG APIs
 * @defgroup wdg_interface WDG driver APIs
 * @ingroup wdg_interfaces
 * @{
 */


#include "hpm_common.h"
#include "hpm_wdg_regs.h"

/**
 * @brief WDG Reset Interval definitions
 */
typedef enum reset_interval_enum {
    reset_interval_clock_period_mult_128    = 0,
    reset_interval_clock_period_mult_256    = 1,
    reset_interval_clock_period_mult_512    = 2,
    reset_interval_clock_period_mult_1k     = 3,
    reset_interval_clock_period_mult_2k     = 4,
    reset_interval_clock_period_mult_4k     = 5,
    reset_interval_clock_period_mult_8k     = 6,
    reset_interval_clock_period_mult_16k    = 7,
    reset_interval_max = reset_interval_clock_period_mult_16k,
    reset_interval_out_of_range,
} reset_interval_t;

/**
 * @brief WDG Interrupt interval definitions
 */
typedef enum interrupt_interval_enum {
    interrupt_interval_clock_period_multi_64     = 0,
    interrupt_interval_clock_period_multi_256    = 1,
    interrupt_interval_clock_period_multi_1k     = 2,
    interrupt_interval_clock_period_multi_2k     = 3,
    interrupt_interval_clock_period_multi_4k     = 4,
    interrupt_interval_clock_period_multi_8k     = 5,
    interrupt_interval_clock_period_multi_16k    = 6,
    interrupt_interval_clock_period_multi_32k    = 7,
    interrupt_interval_clock_period_multi_128k   = 8,
    interrupt_interval_clock_period_multi_512k   = 9,
    interrupt_interval_clock_period_multi_2m     = 10,
    interrupt_interval_clock_period_multi_8m     = 11,
    interrupt_interval_clock_period_multi_32m     = 12,
    interrupt_interval_clock_period_multi_128m    = 13,
    interrupt_interval_clock_period_multi_512m   = 14,
    interrupt_interval_clock_period_multi_2g   = 15,
    interrupt_interval_max = interrupt_interval_clock_period_multi_2g,
    interrupt_interval_out_of_range,
} interrupt_interval_t;

/**
 * @brief WDG clock source definitions
 */
typedef enum wdg_clksrc_enum {
    wdg_clksrc_extclk,                  /**< WDG clock source: external clock */
    wdg_clksrc_pclk,                    /**< WDG clock source: Peripheral clock */
    wdg_clksrc_max = wdg_clksrc_pclk
} wdg_clksrc_t;

/**
 * @brief WDG Control configuration structure
 * @note WDG reset time = reset_interval + interrupt interval
 */
typedef struct wdg_control_struct {
    reset_interval_t reset_interval;            /**< WDG reset interval */
    interrupt_interval_t interrupt_interval;    /**< WDG interrupt interval */
    bool reset_enable;                          /**< WDG reset enable */
    bool interrupt_enable;                      /**< WDG interrupt enable */
    wdg_clksrc_t clksrc;                        /**< WDG clock source */
    bool wdg_enable;                            /**< WDG enable */
} wdg_control_t;

#define WDG_WRITE_ENABLE_MAGIC_NUM (0x5AA5UL)   /**< WDG enable magic number */
#define WDG_RESTART_MAGIC_NUM (0xCAFEUL)        /**< WDG restart magic number */

#define WDG_EXT_CLK_FREQ (32768UL) /**< WDG External CLock frequency: 32768 Hz */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief WDG write enable function
 *
 * @param [in] base WDG base address
 */
static inline void wdg_write_enable(WDG_Type *base)
{
    base->WREN = WDG_WRITE_ENABLE_MAGIC_NUM;
}

/**
 * @brief WDG Enable function
 *
 * @param [in] base  WDG base address
 */
static inline void wdg_enable(WDG_Type *base)
{
    wdg_write_enable(base);
    base->CTRL |= WDG_CTRL_EN_MASK;
}

/**
 * @brief WDG Disable function
 *
 * @param [in] base  WDG base address
 */
static inline void wdg_disable(WDG_Type *base)
{
    wdg_write_enable(base);
    base->CTRL &= ~WDG_CTRL_EN_MASK;
}

/**
 * @brief WDG reset enable function
 *
 * @param [in] base WDG base address
 */
static inline void wdg_reset_enable(WDG_Type *base)
{
    wdg_write_enable(base);
    base->CTRL |= WDG_CTRL_RSTEN_MASK;
}

/**
 * @brief WDG reset disable function
 *
 * @param [in] base WDG base address
 */
static inline void wdg_reset_disable(WDG_Type *base)
{
    wdg_write_enable(base);
    base->CTRL &= ~WDG_CTRL_RSTEN_MASK;
}


/**
 * @brief WDG interrupt enable function
 *
 * @param [in] base WDG base address
 */
static inline void wdg_interrupt_enable(WDG_Type *base)
{
    wdg_write_enable(base);
    base->CTRL |= WDG_CTRL_INTEN_MASK;
}

/**
 * @brief WDG interrupt disable function
 *
 * @param [in] base WDG base address
 */
static inline void wdg_interrupt_disable(WDG_Type *base)
{
    wdg_write_enable(base);
    base->CTRL &= ~WDG_CTRL_INTEN_MASK;
}

/**
 * @brief WDG Clock Source selection function
 *
 * @param [in] base WDG base address
 * @param [in] clksrc WDG clock source
 *   @arg wdg_clksrc_extclk     External clock
 *   @arg wdg_clksrc_pclk       Peripheral clock
 */
static inline void wdg_clksrc_select(WDG_Type *base, wdg_clksrc_t clksrc)
{
    if (clksrc == wdg_clksrc_extclk) {
        base->CTRL &= ~WDG_CTRL_CLKSEL_MASK;
    } else {
        base->CTRL |= WDG_CTRL_CLKSEL_MASK;
    }
}

/**
 * @brief WDG restart function
 *
 * @param [in] base WDG base address
 */
static inline void wdg_restart(WDG_Type *base)
{
    wdg_write_enable(base);
    base->RESTART = WDG_RESTART_MAGIC_NUM;
}

/**
 * @brief WDG Get Status function
 *
 * @param [in] base WDG base address
 * @retval WDG status register value
 */
static inline uint32_t wdg_get_status(WDG_Type *base)
{
    return base->ST;
}

/**
 * @brief WDG clear status function
 *
 * @param [in] base WDG base address
 * @param [in] status_mask WDG status mask value
 */
static inline void wdg_clear_status(WDG_Type *base, uint32_t status_mask)
{
    base->ST = status_mask;
}

/**
 * @brief WDG initialization function
 *
 * @param [in] base WDG base address
 * @param [in] wdg_ctrl WDG control structure
 * @retval API execution status
 */
hpm_stat_t wdg_init(WDG_Type *base, wdg_control_t *wdg_ctrl);

/**
 * @brief Convert the Reset interval value based on the WDG source clock frequency and the expected reset interval
 *        in terms of microseconds
 *
 * @param [in] src_freq WDG source clock frequency
 * @param [in] reset_us Expected Reset interval in terms of microseconds
 * @retval Converted WDG reset interval
 */
reset_interval_t wdg_convert_reset_interval_from_us(const uint32_t src_freq, const uint32_t reset_us);

/**
 * @brief Convert the interrupt interval value based on the WDG source clock frequency and the expected interrupt interval
 *        in terms of microseconds
 *
 * @param [in] src_freq WDG source clock frequency
 * @param [in] interval Expected Interrupt interval
 * @retval Converted WDG interrupt interval in us
 */
 uint64_t wdg_convert_interrupt_interval_to_us(const uint32_t src_freq, interrupt_interval_t interval);

/**
 * @brief Convert the Reset interval value based on the WDG source clock frequency and the expected reset interval
 *        in terms of microseconds
 *
 * @param [in] src_freq WDG source clock frequency
 * @param [in] interval Expected Reset interval
 * @retval Converted WDG reset interval in us
 */
uint32_t wdg_convert_reset_interval_to_us(const uint32_t src_freq, reset_interval_t interval);

/**
 * @brief Convert the interrupt interval value based on the WDG source clock frequency and the expected interrupt interval
 *        in terms of microseconds
 *
 * @param [in] src_freq WDG source clock frequency
 * @param [in] interval_us Expected Interrupt interval in terms of microseconds
 * @retval Converted WDG interrupt interval
 */
interrupt_interval_t wdg_convert_interrupt_interval_from_us(const uint32_t src_freq, uint32_t interval_us);

/**
 * @brief Get Actual WDG Interrupt Interval in terms of microseconds
 *
 * @param [in] base WDG base address
 * @param [in] src_freq WDG source clock frequency
 * @return Converted WDG interrupt interval in terms of microseconds
 */
uint64_t wdg_get_interrupt_interval_in_us(WDG_Type *base, const uint32_t src_freq);

/**
 * @brief Get Actual WDG Reset Interval in terms of microseconds
 *
 * @param [in] base WDG base address
 * @param [in] src_freq WDG source clock frequency
 * @return Converted WDG total reset interval in terms of microseconds
 */
uint64_t wdg_get_total_reset_interval_in_us(WDG_Type *base, const uint32_t src_freq);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* HPM_WDG_DRV_H */
