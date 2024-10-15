/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_CLC_DRV_H
#define HPM_CLC_DRV_H

#include "hpm_common.h"
#include "hpm_clc_regs.h"

/**
 * @brief CLC driver APIs
 * @defgroup clc_interface CLC driver APIs
 * @ingroup motor_interfaces
 * @{
 */

/**
 * @brief clc channel
 */
typedef enum {
    clc_vd_chn = CLC_VDVQ_CHAN_VD,
    clc_vq_chn = CLC_VDVQ_CHAN_VQ,
} clc_chn_t; /**< clc_chn_t */

/**
 * @brief clc coefficient zone
 */
typedef enum {
    clc_coeff_zone_0 = CLC_COEFF_0,
    clc_coeff_zone_1 = CLC_COEFF_1,
    clc_coeff_zone_2 = CLC_COEFF_2,
} clc_coeff_zone_t; /**< clc_coeff_zone_t */

/**
 * @brief clc irq mask bit
 */
typedef enum {
    clc_irq_calc_done = BIT0_MASK,
    clc_irq_eadc_setting_err = BIT1_MASK,
    clc_irq_2p2z_clamp_setting_err = BIT2_MASK,
    clc_irq_2p2z_over_hi = BIT3_MASK,
    clc_irq_2p2z_over_lo = BIT4_MASK,
    clc_irq_2p2z_over_sf = BIT5_MASK,
    clc_irq_3p3z_clamp_setting_err = BIT6_MASK,
    clc_irq_3p3z_over_hi = BIT7_MASK,
    clc_irq_3p3z_over_lo = BIT8_MASK,
    clc_irq_forb_setting_err = BIT9_MASK,
    clc_irq_data_in_forbid = BIT10_MASK
} clc_irq_mask_t;

/**
 * @brief clc parameter configuration
 */
typedef struct {
    int32_t eadc_lowth;
    int32_t eadc_mid_lowth;
    int32_t eadc_mid_highth;
    int32_t eadc_highth;
    int32_t _2p2z_clamp_lowth;
    int32_t _2p2z_clamp_highth;
    int32_t _3p3z_clamp_lowth;
    int32_t _3p3z_clamp_highth;
    int32_t output_forbid_lowth;
    int32_t output_forbid_mid;
    int32_t output_forbid_highth;
} clc_param_config_t;   /**< clc_param_config_t */

/**
 * @brief clc coefficient configuration
 */
typedef struct {
    float b0;
    float b1;
    float b2;
    float b3;
    float a0;
    float a1;
    float a2;
} clc_coeff_config_t;   /**< clc_coeff_config_t */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CLC enable or disable
 *
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] enable true-enable, false-disable
 */
static inline void clc_set_enable(CLC_Type *clc, clc_chn_t chn, bool enable)
{
    if (enable) {
        clc->VDVQ_CHAN[chn].MODE |= CLC_VDVQ_CHAN_MODE_ENABLE_CLC_MASK;
    } else {
        clc->VDVQ_CHAN[chn].MODE &= ~CLC_VDVQ_CHAN_MODE_ENABLE_CLC_MASK;
    }
}

/**
 * @brief CLC keep working even if bad irq status ocurred
 *
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] enable true-enable, false-disable
 */
static inline void clc_set_mask_mode_enable(CLC_Type *clc, clc_chn_t chn, bool enable)
{
    if (enable) {
        clc->VDVQ_CHAN[chn].MODE |= CLC_VDVQ_CHAN_MODE_MASK_MODE_MASK;
    } else {
        clc->VDVQ_CHAN[chn].MODE &= ~CLC_VDVQ_CHAN_MODE_MASK_MODE_MASK;
    }
}

/**
 * @brief CLC set software inject dq work mode
 *
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] enable true-if the ADC value comes from software injection and the VD/VQ channel is required for joint use.
 */
static inline void clc_set_sw_inject_dq_mode_enable(CLC_Type *clc, clc_chn_t chn, bool enable)
{
    if (enable) {
        clc->VDVQ_CHAN[chn].MODE |= CLC_VDVQ_CHAN_MODE_DQ_MODE_MASK;
    } else {
        clc->VDVQ_CHAN[chn].MODE &= ~CLC_VDVQ_CHAN_MODE_DQ_MODE_MASK;
    }
}

/**
 * @brief CLC set irq enable or disable
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] irq_mask irq mask, @ref clc_irq_mask_t
 * @param[in] enable enable or disable
 *  @arg true enable
 *  @arg false disable
 */
static inline void clc_set_irq_enable(CLC_Type *clc, clc_chn_t chn, uint32_t irq_mask, bool enable)
{
    if (enable) {
        clc->VDVQ_CHAN[chn].MODE |= CLC_VDVQ_CHAN_MODE_ENABLE_IRQ_SET(irq_mask);
    } else {
        clc->VDVQ_CHAN[chn].MODE &= ~CLC_VDVQ_CHAN_MODE_ENABLE_IRQ_SET(irq_mask);
    }
}

/**
 * @brief CLC get irq status
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t

 * @retval irq status.
 */
static inline uint32_t clc_get_irq_status(CLC_Type *clc, clc_chn_t chn)
{
    return CLC_VDVQ_CHAN_STATUS_STATUS_GET(clc->VDVQ_CHAN[chn].STATUS);
}

/**
 * @brief CLC clear irq status
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] irq_mask irq mask, @ref clc_irq_mask_t
 */
static inline void clc_clear_irq_status(CLC_Type *clc, clc_chn_t chn, uint32_t irq_mask)
{
    clc->VDVQ_CHAN[chn].STATUS = CLC_VDVQ_CHAN_STATUS_STATUS_SET(irq_mask);
}

/**
 * @brief CLC check irq request flag
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] irq_mask irq mask, @ref clc_irq_mask_t

 * @retval true-has irq req, false-no irq req.
 */
static inline bool clc_get_irq_flag(CLC_Type *clc, clc_chn_t chn, uint32_t irq_mask)
{
    return ((clc->VDVQ_CHAN[chn].STATUS & irq_mask) == irq_mask) ? true : false;
}

/**
 * @brief CLC set adc channel
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] adc_chn adc channel for ADC0~3 or SDM_ADC0~7, adc from VSC must be set to 0.
 * @param[in] adc_offset adc offset for ADC0~3 or SDM_ADC0~7, adc from VSC must be set to 0.
 */
static inline void clc_set_adc_chn_offset(CLC_Type *clc, clc_chn_t chn, uint32_t adc_chn, uint32_t adc_offset)
{
    clc->VDVQ_CHAN[chn].ADC_CHAN = adc_chn;
    clc->VDVQ_CHAN[chn].ADC_OFFSET = adc_offset;
}

/**
 * @brief CLC set pwm period
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] pwm_period 0-clc dac output pwm duty ratio, else-clc dac output pwm period, number of clock cycles.
 */
static inline void clc_set_pwm_period(CLC_Type *clc, clc_chn_t chn, uint32_t pwm_period)
{
    clc->VDVQ_CHAN[chn].PWM_PERIOD = pwm_period;
}

/**
 * @brief CLC set pwm period
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @retval pwm period
 */
static inline uint32_t clc_get_pwm_period(CLC_Type *clc, clc_chn_t chn)
{
    return clc->VDVQ_CHAN[chn].PWM_PERIOD;
}

/**
 * @brief CLC get output caculated value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @retval CLC output caculated value
 */
static inline uint32_t clc_get_output_value(CLC_Type *clc, clc_chn_t chn)
{
    return clc->VDVQ_CHAN[chn].OUTPUT_VALUE;
}

/**
 * @brief CLC get timestamp
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @retval CLC adc timestamp
 */
static inline uint32_t clc_get_timestamp(CLC_Type *clc, clc_chn_t chn)
{
    return clc->VDVQ_CHAN[chn].TIMESTAMP;
}

/**
 * @brief CLC get error adc latest value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @retval CLC error adc latest value
 */
static inline int32_t clc_get_eadc_current_value(CLC_Type *clc, clc_chn_t chn)
{
    return (int32_t)clc->VDVQ_CHAN[chn].EADC_CURR;
}

/**
 * @brief CLC get error adc previous0 value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @retval CLC error adc previous0 value
 */
static inline int32_t clc_get_eadc_previous0_value(CLC_Type *clc, clc_chn_t chn)
{
    return (int32_t)clc->VDVQ_CHAN[chn].EADC_PRE0;
}

/**
 * @brief CLC software inject error adc previous0 value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] value CLC error adc previous0 value
 */
static inline void clc_sw_inject_eadc_previous0_value(CLC_Type *clc, clc_chn_t chn, int32_t value)
{
    clc->VDVQ_CHAN[chn].EADC_PRE0 = (uint32_t)value;
}

/**
 * @brief CLC get error adc previous1 value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @retval CLC error adc previous1 value
 */
static inline int32_t clc_get_eadc_previous1_value(CLC_Type *clc, clc_chn_t chn)
{
    return (int32_t)clc->VDVQ_CHAN[chn].EADC_PRE1;
}

/**
 * @brief CLC software inject error adc previous1 value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] value CLC error adc previous1 value
 */
static inline void clc_sw_inject_eadc_previous1_value(CLC_Type *clc, clc_chn_t chn, int32_t value)
{
    clc->VDVQ_CHAN[chn].EADC_PRE1 = (uint32_t)value;
}

/**
 * @brief CLC get 2p2z last value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @retval CLC 2p2z last value
 */
static inline int32_t clc_get_2p2z_current_value(CLC_Type *clc, clc_chn_t chn)
{
    return (int32_t)clc->VDVQ_CHAN[chn].P2Z2_CURR;
}

/**
 * @brief CLC software inject 2p2z last value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] value CLC 2p2z last value
 */
static inline void clc_sw_inject_2p2z_current_value(CLC_Type *clc, clc_chn_t chn, int32_t value)
{
    clc->VDVQ_CHAN[chn].P2Z2_CURR = (uint32_t)value;
}

/**
 * @brief CLC get 2p2z previous0 value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @retval CLC 2p2z previous0 value
 */
static inline int32_t clc_get_2p2z_previous0_value(CLC_Type *clc, clc_chn_t chn)
{
    return (int32_t)clc->VDVQ_CHAN[chn].P2Z2_PRE0;
}

/**
 * @brief CLC software inject 2p2z previous0 value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] value CLC 2p2z previous0 value
 */
static inline void clc_sw_inject_2p2z_previous0_value(CLC_Type *clc, clc_chn_t chn, int32_t value)
{
    clc->VDVQ_CHAN[chn].P2Z2_PRE0 = (uint32_t)value;
}

/**
 * @brief CLC get 3p3z last value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @retval CLC 3p3z last value
 */
static inline int32_t clc_get_3p3z_current_value(CLC_Type *clc, clc_chn_t chn)
{
    return (int32_t)clc->VDVQ_CHAN[chn].P3Z3_CURR;
}

/**
 * @brief CLC software inject 3p3z last value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] value CLC 3p3z last value
 */
static inline void clc_sw_inject_3p3z_current_value(CLC_Type *clc, clc_chn_t chn, int32_t value)
{
    clc->VDVQ_CHAN[chn].P3Z3_CURR = (uint32_t)value;
}

/**
 * @brief CLC set expected adc value
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] expect expected adc value
 */
static inline void clc_set_expect_adc_value(CLC_Type *clc, clc_chn_t chn, int32_t expect)
{
    clc->VDVQ_CHAN[chn].ADC_EXPECT = (uint32_t)expect;
}

/**
 * @brief CLC software inject adc value. If it's not dq mode, this will trig clc calculation.
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] value CLC adc value
 */
static inline void clc_sw_inject_adc_value(CLC_Type *clc, clc_chn_t chn, uint32_t value)
{
    clc->VDVQ_CHAN[chn].ADC_SW = value;
}

/**
 * @brief CLC set software inject dq adc value ready, this will trig clc calculation.
 * @param[in] clc CLC base address
 */
static inline void clc_set_sw_inject_dq_adc_value_ready(CLC_Type *clc)
{
    clc->DQ_ADC_SW_READY = CLC_DQ_ADC_SW_READY_DQ_ADC_SW_READY_MASK;
}

/**
 * @brief CLC parameter configuration
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] param @ref clc_param_config_t.
 */
void clc_config_param(CLC_Type *clc, clc_chn_t chn, clc_param_config_t *param);

/**
 * @brief CLC coefficient configuration
 * @param[in] clc CLC base address
 * @param[in] chn CLC channel, @ref clc_chn_t
 * @param[in] zone CLC coefficient zone, @ref clc_coeff_zone_t
 * @param[in] coeff @ref clc_param_config_t.
 *
 * @retval status_invalid_argument some parameters are invalid
 * @retval status_success operation is successful
 */
hpm_stat_t clc_config_coeff(CLC_Type *clc, clc_chn_t chn, clc_coeff_zone_t zone, clc_coeff_config_t *coeff);

/**
 * @brief CLC software inject dq adc value
 * @param[in] clc CLC base address
 * @param[in] d_value CLC d adc value
 * @param[in] q_value CLC q adc value
 */
void clc_sw_inject_dq_adc_value(CLC_Type *clc, uint32_t d_value, uint32_t q_value);


#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_CLC_DRV_H */
