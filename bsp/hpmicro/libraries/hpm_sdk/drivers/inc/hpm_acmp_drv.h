/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_ACMP_DRV_H
#define HPM_ACMP_DRV_H

#include "hpm_common.h"
#include "hpm_acmp_regs.h"

/**
 * @brief ACMP driver APIs
 * @defgroup acmp_interface ACMP driver APIs
 * @ingroup io_interfaces
 * @{
 *
 */

/***********************************************************************************************************************
 *
 * Definitions
 *
 **********************************************************************************************************************/

/**
 * @brief ACMP hysteresis level
 */
#define ACMP_HYST_LEVEL_0 (0U)
#define ACMP_HYST_LEVEL_1 (1U)
#define ACMP_HYST_LEVEL_2 (2U)
#define ACMP_HYST_LEVEL_3 (3U)

/**
 * @brief ACMP input channel number
 */
#define ACMP_INPUT_DAC_OUT (0U)
#define ACMP_INPUT_ANALOG_1 (1U)
#define ACMP_INPUT_ANALOG_2 (2U)
#define ACMP_INPUT_ANALOG_3 (3U)
#define ACMP_INPUT_ANALOG_4 (4U)
#define ACMP_INPUT_ANALOG_5 (5U)
#define ACMP_INPUT_ANALOG_6 (6U)
#define ACMP_INPUT_ANALOG_7 (7U)

/**
 * @brief ACMP output digital filter mode
 */
#define ACMP_FILTER_MODE_BYPASS (0U)
#define ACMP_FILTER_MODE_CHANGE_IMMEDIATELY (4U)
#define ACMP_FILTER_MODE_CHANGE_AFTER_FILTER (5U)
#define ACMP_FILTER_MODE_STABLE_LOW (6U)
#define ACMP_FILTER_MODE_STABLE_HIGH (7U)

/**
 * @brief ACMP rising/falling flage mask
 */
#define ACMP_EVENT_RISING_EDGE  (1U)
#define ACMP_EVENT_FALLING_EDGE (2U)

/**
 * @brief ACMP channel config
 */

typedef struct acmp_channel_config {
    uint8_t plus_input;
    uint8_t minus_input;
    uint8_t filter_mode;
    uint8_t hyst_level;
    bool enable_cmp_output;
    bool enable_window_mode;
    bool invert_output;
    bool enable_clock_sync;
    bool bypass_filter;
    bool enable_dac;
    bool enable_hpmode;
    uint16_t filter_length; /* ACMP output digital filter length in ACMP clock cycle */
} acmp_channel_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ACMP channel config DAC output value
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] value DAC output value
 */
static inline void acmp_channel_config_dac(ACMP_Type *ptr, uint8_t ch, uint32_t value)
{
    ptr->CHANNEL[ch].DACCFG = ACMP_CHANNEL_DACCFG_DACCFG_SET(value);
}

/**
 * @brief ACMP channel clear status
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] mask :
 *  @arg ACMP_EVENT_RISING_EDGE: ACMP output rising flag
 *  @arg ACMP_EVENT_FALLING_EDGE: ACMP output fall flag
 */
static inline void acmp_channel_clear_status(ACMP_Type *ptr, uint8_t ch, uint32_t mask)
{
    ptr->CHANNEL[ch].SR = mask;
}

/**
 * @brief ACMP channel get status
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @retval ACMP channel's status
 */
static inline uint32_t acmp_channel_get_status(ACMP_Type *ptr, uint8_t ch)
{
    return ptr->CHANNEL[ch].SR;
}

/**
 * @brief ACMP channel enable DMA request
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] mask :
 *  @arg ACMP_EVENT_RISING_EDGE: ACMP output rising flag
 *  @arg ACMP_EVENT_FALLING_EDGE: ACMP output fall flag
 * @param [in] enable:
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void acmp_channel_dma_request_enable(ACMP_Type *ptr, uint8_t ch,
                                            uint32_t mask, bool enable)
{
    ptr->CHANNEL[ch].DMAEN = (ptr->CHANNEL[ch].DMAEN & ~mask)
                        | (enable ? mask : 0);
}

/**
 * @brief ACMP channel enable IRQ
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] mask :
 *  @arg ACMP_EVENT_RISING_EDGE: ACMP output rising flag
 *  @arg ACMP_EVENT_FALLING_EDGE: ACMP output fall flag
 * @param [in] enable:
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void acmp_channel_enable_irq(ACMP_Type *ptr, uint8_t ch,
                                            uint32_t mask, bool enable)
{
    ptr->CHANNEL[ch].IRQEN = (ptr->CHANNEL[ch].IRQEN & ~mask)
                        | (enable ? mask : 0);
}

/**
 * @brief ACMP channel enable DAC
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] enable:
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void acmp_channel_enable_dac(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_DACEN_MASK)
                        | ACMP_CHANNEL_CFG_DACEN_SET(enable);
}

/**
 * @brief ACMP channel enable high performance mode
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] enable:
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void acmp_channel_enable_hpmode(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_HPMODE_MASK)
                        | ACMP_CHANNEL_CFG_HPMODE_SET(enable);
}

/**
 * @brief ACMP channel enable hysteresis level
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] level: ACMP hysteresis level
 */
static inline void acmp_channel_set_hyst(ACMP_Type *ptr, uint8_t ch, uint8_t level)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_HYST_MASK)
                        | ACMP_CHANNEL_CFG_HYST_SET(level);
}

/**
 * @brief ACMP channel enable comparator
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] enable:
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void acmp_channel_enable_cmp(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_CMPEN_MASK)
                        | ACMP_CHANNEL_CFG_CMPEN_SET(enable);
}

/**
 * @brief ACMP channel enable comparator output
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] enable:
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void acmp_channel_enable_cmp_output(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_CMPOEN_MASK)
                        | ACMP_CHANNEL_CFG_CMPOEN_SET(enable);
}

/**
 * @brief ACMP channel bypass comparator output filter
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] enable:
 *  @arg true: bypass
 *  @arg false: not bypass
 */
static inline void acmp_channel_cmp_output_bypass_filter(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_FLTBYPS_MASK)
                        | ACMP_CHANNEL_CFG_FLTBYPS_SET(!enable);
}

/**
 * @brief ACMP channel enable comparator window mode
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] enable:
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void acmp_channel_enable_cmp_window_mode(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_WINEN_MASK)
                        | ACMP_CHANNEL_CFG_WINEN_SET(enable);
}

/**
 * @brief ACMP channel invert comparator output
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] enable:
 *  @arg true: invert
 *  @arg false: not invert
 */
static inline void acmp_channel_invert_output(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_OPOL_MASK)
                        | ACMP_CHANNEL_CFG_OPOL_SET(enable);
}

/**
 * @brief ACMP channel set comparator output filter mode
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] filter: ACMP output digital filter mode definition
 */
static inline void acmp_channel_set_filter_mode(ACMP_Type *ptr, uint8_t ch, uint8_t filter)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_FLTMODE_MASK)
                        | ACMP_CHANNEL_CFG_FLTMODE_SET(filter);
}

/**
 * @brief ACMP channel enable comparator output sync with clock
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] enable:
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void acmp_channel_enable_sync(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_SYNCEN_MASK)
                        | ACMP_CHANNEL_CFG_SYNCEN_SET(enable);
}

/**
 * @brief ACMP channel set comparator output filter length
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] filter_length: filter length in clock cycles
 */
static inline void acmp_channel_set_filter_length(ACMP_Type *ptr, uint8_t ch, uint16_t filter_length)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_FLTLEN_MASK)
                        | ACMP_CHANNEL_CFG_FLTLEN_SET(filter_length);
}

/**
 * @brief ADC channel config
 *
 * @param [in] ptr ACMP base address
 * @param [in] ch ACMP channel number
 * @param [in] config: acmp_channel_config_t
 * @param [in] enable:
 *  @arg true: enable comparator
 *  @arg false: disable comparator
 *
 * @retval hpm_stat_t
 */
hpm_stat_t acmp_channel_config(ACMP_Type *ptr, uint8_t ch, acmp_channel_config_t *config, bool enable);

/**
 * @brief ADC channel get default config setting
 *
 * @param [in] ptr ACMP base address
 * @param [out] config: acmp_channel_config_t
 */
void acmp_channel_get_default_config(ACMP_Type *ptr, acmp_channel_config_t *config);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_ACMP_DRV_H */
