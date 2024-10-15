/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_VSC_DRV_H
#define HPM_VSC_DRV_H

#include "hpm_common.h"
#include "hpm_vsc_regs.h"

/**
 * @brief VSC driver APIs
 * @defgroup vsc_interface VSC driver APIs
 * @ingroup motor_interfaces
 * @{
 */

/**
 * @brief vsc phase mode
 *
 */
typedef enum vsc_phase_mode {
    vsc_abc_phase = 0,
    vsc_ab_phase = 1,
} vsc_phase_mode_t; /**< vsc_phase_mode_t */

/**
 * @brief vsc data operation mode
 *
 */
typedef enum vsc_data_opr_mode {
    vsc_data_opr_plus_mul_1 = 0,
    vsc_data_opr_plus_mul_2 = 1,
    vsc_data_opr_plus_div_2 = 5,
    vsc_data_opr_plus_div_3 = 6,
    vsc_data_opr_plus_div_4 = 7,
    vsc_data_opr_minus_mul_1 = 8,
    vsc_data_opr_minus_mul_2 = 9,
    vsc_data_opr_minus_div_2 = 13,
    vsc_data_opr_minus_div_3 = 14,
    vsc_data_opr_minus_div_4 = 15
} vsc_data_opr_mode_t; /**< vsc_data_opr_mode_t */

/**
 * @brief vsc select adc instance
 *
 */
typedef enum vsc_adc_sel {
    vsc_sel_adc0 = 1,
    vsc_sel_adc1 = 2,
    vsc_sel_adc2 = 3
} vsc_adc_sel_t; /**< vsc_adc_sel_t */

/**
 * @brief vsc position capture mode
 *
 */
typedef enum vsc_pos_cap_mode {
    vsc_pos_use_last_data_when_adc_sample_finish = 0,
    vsc_pos_use_first_data_after_adc_sample_start = 1,
    vsc_pos_use_last_data_before_adc_sample_start = 2
} vsc_pos_cap_mode_t; /**< vsc_pos_cap_mode_t */

/**
 * @brief vsc select adc timestamp
 *
 */
typedef enum vsc_timestamp_sel {
    vsc_timestamp_sel_value_a = 1,
    vsc_timestamp_sel_value_b = 2,
    vsc_timestamp_sel_value_c = 3
} vsc_timestamp_sel_t; /**< vsc_timestamp_sel_t */

/**
 * @brief vsc irq mask bit
 *
 */
typedef enum vsc_irq_mask {
    vsc_irq_convert_done = BIT0_MASK,
    vsc_irq_abc_over_tolerate = BIT1_MASK,
    vsc_irq_c_overflow = BIT2_MASK,
    vsc_irq_b_overflow = BIT3_MASK,
    vsc_irq_a_overflow = BIT4_MASK,
    vsc_irq_adc2_cap_not_enough = BIT5_MASK,
    vsc_irq_adc1_cap_not_enough = BIT6_MASK,
    vsc_irq_adc0_cap_not_enough = BIT7_MASK,
    vsc_irq_pos_timeout = BIT8_MASK,
    vsc_irq_adc2_timeout = BIT9_MASK,
    vsc_irq_adc1_timeout = BIT10_MASK,
    vsc_irq_adc0_timeout = BIT11_MASK,
    vsc_irq_convert_conflict = BIT12_MASK
} vsc_irq_mask_t;

/**
 * @brief adc config structure
 */
typedef struct {
    vsc_adc_sel_t adc_sel;
    uint8_t adc_chn;
    uint32_t adc_offset;
} vsc_adc_config_t;

/**
 * @brief vsc config structure
 */
typedef struct {
    vsc_data_opr_mode_t opr_0;
    vsc_data_opr_mode_t opr_1;
    vsc_data_opr_mode_t opr_2;
    vsc_data_opr_mode_t opr_3;
} vsc_data_opr_config_t;

/**
 * @brief vsc config structure
 */
typedef struct {
    vsc_phase_mode_t phase_mode;
    uint8_t a_data_cnt;
    uint8_t b_data_cnt;
    uint8_t c_data_cnt;
    vsc_data_opr_config_t a_data_opr_config;
    vsc_data_opr_config_t b_data_opr_config;
    vsc_data_opr_config_t c_data_opr_config;
    vsc_adc_config_t a_adc_config;
    vsc_adc_config_t b_adc_config;
    vsc_adc_config_t c_adc_config;
    vsc_pos_cap_mode_t pos_cap_mode;
    uint16_t pole_pairs;
} vsc_config_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief vsc enable or disable
 *
 * @param[in] vsc VSC base address
 * @param[in] enable true-enable, false-disable
 */
static inline void vsc_set_enable(VSC_Type *vsc, bool enable)
{
    if (enable) {
        vsc->ABC_MODE |= VSC_ABC_MODE_ENABLE_VSC_MASK;
    } else {
        vsc->ABC_MODE &= ~VSC_ABC_MODE_ENABLE_VSC_MASK;
    }
}

/**
 * @brief vsc config position capture mode
 *
 * @param[in] vsc VSC base address
 * @param[in] mode @ref vsc_pos_cap_mode_t
 */
static inline void vsc_config_pos_capture_mode(VSC_Type *vsc, vsc_pos_cap_mode_t mode)
{
    vsc->TIMELOCK = (vsc->TIMELOCK & ~(VSC_TIMELOCK_POSITION_CAPTURE_MODE_MASK))
                    | VSC_TIMELOCK_POSITION_CAPTURE_MODE_SET(mode);
}

/**
 * @brief vsc config adc timestamp
 *
 * @param[in] vsc VSC base address
 * @param[in] select timestamp select from value a/b/c. @ref vsc_timestamp_sel_t
 * @param[in] num timestamp use which number index of @ref vsc_timestamp_sel_t used.
 */
static inline void vsc_config_adc_timestamp(VSC_Type *vsc, vsc_timestamp_sel_t select, uint8_t num)
{
    vsc->TIMELOCK = (vsc->TIMELOCK & ~(VSC_TIMELOCK_ADC_TIMESTAMP_SEL_MASK | VSC_TIMELOCK_VALUE_COUNTER_SEL_MASK))
                    | VSC_TIMELOCK_ADC_TIMESTAMP_SEL_SET(select) | VSC_TIMELOCK_VALUE_COUNTER_SEL_SET(num);
}

/**
 * @brief vsc set irq enable or disable
 * @param [in] vsc CLC base address
 * @param [in] irq_mask irq mask, @ref vsc_irq_mask_t
 * @param [in] enable enable or disable
 *  @arg true enable
 *  @arg false disable
 */
static inline void vsc_set_irq_enable(VSC_Type *vsc, uint32_t irq_mask, bool enable)
{
    if (enable) {
        vsc->IRQ_ENABLE |= irq_mask;
    } else {
        vsc->IRQ_ENABLE &= ~irq_mask;
    }
}

/**
 * @brief vsc get irq status
 * @param [in] vsc CLC base address

 * @retval irq status.
 */
static inline uint32_t vsc_get_irq_status(VSC_Type *vsc)
{
    return vsc->IRQ_STATUS;
}

/**
 * @brief vsc clear irq status
 * @param [in] vsc CLC base address
 * @param [in] irq_mask irq mask, @ref vsc_irq_mask_t
 */
static inline void vsc_clear_irq_status(VSC_Type *vsc, uint32_t irq_mask)
{
    vsc->IRQ_STATUS = irq_mask;
}

/**
 * @brief vsc check irq request flag
 * @param [in] vsc CLC base address
 * @param [in] irq_mask irq mask, @ref vsc_irq_mask_t

 * @retval true-has irq req, false-no irq req.
 */
static inline bool vsc_get_irq_flag(VSC_Type *vsc, uint32_t irq_mask)
{
    return ((vsc->IRQ_STATUS & irq_mask) == irq_mask) ? true : false;
}

/**
 * @brief vsc set adc wait cycles
 * @param [in] vsc CLC base address
 * @param [in] wait_cycle adc wait cycle for exception
 */
static inline void vsc_set_adc_wait_cycle(VSC_Type *vsc, uint32_t wait_cycle)
{
    vsc->ADC_WAIT_CYCLE = VSC_ADC_WAIT_CYCLE_ADC_WAIT_CYCLE_SET(wait_cycle);
}

/**
 * @brief vsc set position wait cycles
 * @param [in] vsc CLC base address
 * @param [in] wait_cycle position wait cycle for exception
 */
static inline void vsc_set_pos_wait_cycle(VSC_Type *vsc, uint32_t wait_cycle)
{
    vsc->POS_WAIT_CYCLE = VSC_POS_WAIT_CYCLE_POS_WAIT_CYCLE_SET(wait_cycle);
}

/**
 * @brief vsc set abc phase value tolerate
 * @param [in] vsc CLC base address
 * @param [in] tolerate value a/b/c total value tolerate
 */
static inline void vsc_set_adc_tolerate(VSC_Type *vsc, uint32_t tolerate)
{
    vsc->ADC_PHASE_TOLERATE = VSC_ADC_PHASE_TOLERATE_ADC_PHASE_TOLERATE_SET(tolerate);
}

/**
 * @brief vsc set position pole pairs
 * @param [in] vsc CLC base address
 * @param [in] pole_pairs pole pairs number
 */
static inline void vsc_set_pos_pole_pairs(VSC_Type *vsc, uint32_t pole_pairs)
{
    vsc->POS_POLE = (vsc->POS_POLE & ~VSC_POS_POLE_POS_POLE_MASK) | VSC_POS_POLE_POS_POLE_SET(pole_pairs);
}

/**
 * @brief vsc set software trigger in
 * @param [in] vsc CLC base address
 */
static inline void vsc_set_sw_trig_in(VSC_Type *vsc)
{
    vsc->TRIGGER_SW = VSC_TRIGGER_SW_TRIGGER_SW_MASK;
}

/**
 * @brief vsc get d-axis value
 * @param [in] vsc CLC base address
 * @param [in] positive_seq true - positive order; false - reverse order
 * @retval d-axis value
 */
static inline int32_t vsc_get_d_axis_value(VSC_Type *vsc, bool positive_seq)
{
    if (positive_seq) {
        return (int32_t)vsc->ID_POSEDGE;
    } else {
        return (int32_t)vsc->ID_NEGEDGE;
    }
}

/**
 * @brief vsc get q-axis value
 * @param [in] vsc CLC base address
 * @param [in] positive_seq true - positive order; false - reverse order
 * @retval q-axis value
 */
static inline int32_t vsc_get_q_axis_value(VSC_Type *vsc, bool positive_seq)
{
    if (positive_seq) {
        return (int32_t)vsc->IQ_POSEDGE;
    } else {
        return (int32_t)vsc->IQ_NEGEDGE;
    }
}

/**
 * @brief vsc get alpha-axis value
 * @param [in] vsc CLC base address
 * @param [in] positive_seq true - positive order; false - reverse order
 * @retval alpha-axis value
 */
static inline int32_t vsc_get_alpha_axis_value(VSC_Type *vsc, bool positive_seq)
{
    if (positive_seq) {
        return (int32_t)vsc->ALPHA_POSEDGE;
    } else {
        return (int32_t)vsc->ALPHA_NEGEDGE;
    }
}

/**
 * @brief vsc get beta-axis value
 * @param [in] vsc CLC base address
 * @param [in] positive_seq true - positive order; false - reverse order
 * @retval beta-axis value
 */
static inline int32_t vsc_get_beta_axis_value(VSC_Type *vsc, bool positive_seq)
{
    if (positive_seq) {
        return (int32_t)vsc->BETA_POSEDGE;
    } else {
        if (vsc->BETA_NEGEDGE == 0x80000000) {
            return 0x7FFFFFFF;
        } else {
            return (int32_t)vsc->BETA_NEGEDGE;
        }
    }
}

/**
 * @brief vsc get adc timestamp value
 * @param [in] vsc CLC base address
 * @retval adc timestamp value
 */
static inline uint32_t vsc_get_adc_timestamp(VSC_Type *vsc)
{
    return vsc->TIMESTAMP_LOCKED;
}

/**
 * @brief vsc get default config
 *
 * @param[in] vsc VSC base address
 * @param[out] config vsc default config
 */
void vsc_get_default_config(VSC_Type *vsc, vsc_config_t *config);

/**
 * @brief vsc config initialization
 *
 * @param[in] vsc VSC base address
 * @param[in] config vsc config struct
 */
void vsc_config_init(VSC_Type *vsc, vsc_config_t *config);

/**
 * @brief vsc software inject phase a/b/c value
 *
 * @param[in] vsc VSC base address
 * @param[in] value_a phase a value
 * @param[in] value_b phase b value
 * @param[in] value_c phase c value
 */
void vsc_sw_inject_abc_value(VSC_Type *vsc, int32_t value_a, int32_t value_b, int32_t value_c);

/**
 * @brief vsc software inject position value
 *
 * @param[in] vsc VSC base address
 * @param[in] pos position value
 */
void vsc_sw_inject_pos_value(VSC_Type *vsc, uint32_t pos);


#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_VSC_DRV_H */
