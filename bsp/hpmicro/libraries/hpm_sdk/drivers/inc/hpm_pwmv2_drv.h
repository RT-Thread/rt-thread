/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PWMV2_DRV_H
#define HPM_PWMV2_DRV_H

#include "hpm_common.h"
#include "hpm_pwmv2_regs.h"
#include "hpm_soc_feature.h"


/**
 * @brief PWM driver APIs
 * @defgroup pwmv2_interface PWMV2 driver APIs
 * @ingroup motor_interfaces
 * @{
 *
 */
#define PWM_UNLOCK_KEY (0xB0382607UL)
#define PWM_CMP_UNABLE_OUTPUT_INDEX (16)

/* IRQ enable bit mask */
#define PWM_IRQ_FAULT PWM_IRQEN_FAULTIRQE_MASK
#define PWM_IRQ_EX_RELOAD PWM_IRQEN_XRLDIRQE_MASK
#define PWM_IRQ_HALF_RELOAD PWM_IRQEN_HALFRLDIRQE_MASK
#define PWM_IRQ_RELOAD PWM_IRQEN_RLDIRQE_MASK
#define PWM_IRQ_CMP(x) PWM_IRQEN_CMPIRQEX_SET((1 << x))

/* PWM force output mask */
#define PWM_FORCE_OUTPUT(pwm_index, force_output) \
    (force_output << (pwm_index << 1))

#define PWM_DUTY_CYCLE_FP_MAX ((1U << 24) - 1)

#ifndef PWMV2_SOC_CAL_COUNT_MAX
    #define PWMV2_SOC_CAL_COUNT_MAX 8
#endif

#define PWMV2_SHADOW_INDEX(x)  PWMV2_SHADOW_VAL_##x
#define PWMV2_CMP_INDEX(x) PWMV2_CMP_VAL_WORK_##x
#define PWMV2_CALCULATE_INDEX(x) PWMV2_CAL_##x
#define PWMV2_CAL_SHADOW_OFFSET_ZERO    (31)

typedef enum {
    pwm_counter_0 = 0,
    pwm_counter_1 = 1,
    pwm_counter_2 = 2,
    pwm_counter_3 = 3,
} pwm_counter_t;

typedef enum {
    pwm_channel_0 = 0,
    pwm_channel_1 = 1,
    pwm_channel_2 = 2,
    pwm_channel_3 = 3,
    pwm_channel_4 = 4,
    pwm_channel_5 = 5,
    pwm_channel_6 = 6,
    pwm_channel_7 = 7,
} pwm_channel_t;


typedef enum {
    pwm_reload_update_on_shlk = 0,
    pwm_reload_update_on_compare_point = 1,
    pwm_reload_update_on_reload = 2,
    pwm_reload_update_on_trigger = 3,
} pwm_reload_update_time_t;


/**
 * @brief pwm output type
 *
 */
typedef enum {
    pwm_force_output_0 = 0, /**< output 0 */
    pwm_force_output_1 = 1, /**< output 1 */
    pwm_force_output_high_z = 2, /**< output */
    pwm_force_output_no_force = 3,
} pwm_force_mode_t;

typedef enum {
    pwm_fault_output_0 = 0, /**< output 0 */
    pwm_fault_output_1 = 1, /**< output 1 */
    pwm_fault_output_high_z = 2, /**< output */
} pwm_fault_mode_t;

typedef enum {
    pad_fault_active_low = 1,
    pad_fault_active_high = 0,
} pwm_fault_pad_polarity_t;

typedef enum {
    pwm_shadow_register_output_polarity_on_shlk = 0,
    pwm_shadow_register_output_polarity_on_reload = 1,
} pwm_shadow_register_output_polarity_t;

typedef enum {
    pwm_force_update_shadow_immediately = 0,  /**< after software set shlk bit of shlk register */
    pwm_force_update_shadow_at_cmp_point = 1,
    pwm_force_update_shadow_at_reload = 2,     /**< immediately after the register being modified */
    pwm_force_update_shadow_none = 3,         /**< after SHSYNCI assert */
} pwm_force_shadow_trigger_t;

typedef enum {
    pwm_force_immediately = 0,  /**< after software set shlk bit of shlk register */
    pwm_force_at_reload = 1,
    pwm_force_at_trigmux = 2,
    pwm_force_none = 3,         /**< after SHSYNCI assert */
} pwm_force_trigger_t;


typedef enum {
    pwm_logic_four_cmp_or = 0,
    pwm_logic_four_cmp_and = 1,
    pwm_logic_four_cmp_xor = 2,
    pwm_logic_four_cmp_cd = 3,
} pwm_logic_four_cmp_cfg_t;

/**
 * @brief  select when to recover PWM output after fault
 *
 */
typedef enum {
    pwm_fault_recovery_immediately = 0, /**< immediately*/
    pwm_fault_recovery_on_reload = 1,   /**<  after pwm timer counter reload time*/
    pwm_fault_recovery_on_hw_event = 2, /**< after hardware event assert*/
    pwm_fault_recovery_on_fault_clear = 3,  /**<  after software write faultclr bit in GCR register*/
} pwm_fault_recovery_trigger_t;

typedef enum {
    pwm_dac_channel_0 = 0,
    pwm_dac_channel_1 = 1,
    pwm_dac_channel_2 = 2,
    pwm_dac_channel_3 = 3,
} pwm_dac_channel_t;

typedef enum {
    pwm_capture_from_trigmux = 0,
    pwm_capture_from_gpio = 1
} pwm_capture_input_select_t;

typedef enum {
    pwm_dma_0 = 0,
    pwm_dma_1 = 1,
    pwm_dma_2 = 2,
    pwm_dma_3 = 3,
} pwm_dma_chn_t;

typedef enum {
    pwm_shadow_register_update_on_shlk = 0,     /**< after software set shlk bit of shlk register*/
    pwm_shadow_register_update_on_modify = 1,   /**<  immediately after the register being modified*/
    pwm_shadow_register_update_on_reload = 2,
    pwm_shadow_register_update_on_trigmux = 3,
    pwm_shadow_register_update_on_rld_cmp_select0 = 4,
    pwm_shadow_register_update_on_rld_cmp_select1 = 5,
    pwm_shadow_register_update_on_none = 6
} pwm_cmp_shadow_register_update_trigger_t;

typedef enum {
    cmp_value_from_shadow_val = 0,
    cmp_value_from_calculate = 0x20,
    cmp_value_from_capture_posedge = 0x30,
    cmp_value_from_counters = 0x38,
    cmp_value_fffff000 = 0x3e,
    cmp_value_ffffff00 = 0x3f
} pwm_cmp_source_t;

/**
 * @brief pwm compare config
 *
 */
typedef struct pwmv2_cmp_config {
    uint32_t cmp;         /**< compare value */
    bool enable_half_cmp;   /**< enable half compare value */
    bool enable_hrcmp;     /**< enable high precision pwm */
    pwm_cmp_source_t cmp_source;    /**< @ref pwm_cmp_source_t */
    pwm_counter_t cmp_use_counter;  /**< select one from 4 counters, only for CMP_N>=16 */
    uint8_t cmp_source_index;   /**< soure index */
    uint8_t mode;         /**< compare work mode: pwm_cmp_mode_output_compare or pwm_cmp_mode_input_capture */
    pwm_cmp_shadow_register_update_trigger_t update_trigger;  /**< compare configuration update trigger, need update trigger use pwm_shadow_register_update_on_trigmux */
    uint8_t update_trigger_index;   /**< select one trigger from 8, should set to pulse in trig_mux */
    uint8_t hrcmp;         /**< high precision pwm */
} pwmv2_cmp_config_t;

/**
 * @brief pwm fault source config
 *
 */
typedef struct pwmv2_async_fault_source_config {
    uint8_t async_signal_from_pad_index;     /**< select from 16bit async fault from pad*/
    pwm_fault_pad_polarity_t fault_async_pad_level;      /**< fault polarity for input fault from pad, 1-active low;  0-active high */
} pwmv2_async_fault_source_config_t;

/**
 * @brief pwm config data
 *
 */
typedef struct pwmv2_config {
    bool enable_output;                 /**< enable pwm output */
    bool enable_async_fault;            /**< enable the input async faults from pad directly */
    bool enable_sync_fault;             /**< enable the input faults from trig_mux */
    bool invert_output;                 /**< invert pwm output level */
    bool enable_four_cmp;                /**< Enable the four cmp functions */
    pwmv2_async_fault_source_config_t async_fault_source;
    pwm_shadow_register_output_polarity_t update_polarity_time;
    pwm_logic_four_cmp_cfg_t logic;     /**< valid only for pwm0/2/4/6 when trig_sel4 is set */
    uint8_t update_trigger;             /**< pwm config update trigger */
    uint8_t fault_mode;                 /**< fault mode */
    pwm_fault_recovery_trigger_t fault_recovery_trigger;     /**< fault recoverty trigger */
    uint8_t fault_recovery_trigmux_index;   /**< select one trigger from 8, should set to pulse in trig_mux */
    uint8_t force_shadow_trigmux_index;          /**< select one trigger from 8, should set to pulse in trig_mux */
    pwm_force_shadow_trigger_t force_shadow_trigger;         /**< will load shadow register(force)mode) to force_mode_work at this time */
    uint8_t force_trigmux_index;               /**< select one trigger from 8 as force signal */
    pwm_force_trigger_t force_trigger;          /**< @ref pwm_force_trigger_t */
    uint32_t dead_zone_in_half_cycle;   /**< dead zone in half cycle*/
} pwmv2_config_t;

/**
 * @brief pair pwm config
 *
 */
typedef struct pwmv2_pair_config {
    pwmv2_config_t pwm[2];    /**< pwm config data */
} pwmv2_pair_config_t;

typedef struct pwmv2_cmp_calculate_cfg {
    uint8_t counter_index;        /**< select one of 4 counter reload time */
    uint8_t in_index;       /**< 0~3 to select one of the dac input value; 4~7 to select one of the current counter value */
    uint8_t in_offset_index;    /**< from one of the shadow_val */
    int8_t t_param;    /**< period parameter */
    int8_t d_param;    /**< dac/counter value parameter */
    int8_t up_limit_param;
    uint8_t up_limit_offset_index;  /**< from one of the shadow_val */
    int8_t low_limit_param;
    uint8_t low_limit_offset_index; /**< from one of the shadow_val */
    bool enable_up_limit;
    bool enbale_low_limit;
} pwmv2_cmp_calculate_cfg_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief pwm deinitialize function
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 *
 */
void pwmv2_deinit(PWMV2_Type *pwm_x);

/**
 * @brief issue all shawdow register
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_issue_shadow_register_lock_event(PWMV2_Type *pwm_x)
{
    pwm_x->WORK_CTRL1 |= PWMV2_WORK_CTRL1_SHADOW_LOCK_MASK;
}

/**
 * @brief lock all shawdow register
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_shadow_register_lock(PWMV2_Type *pwm_x)
{
    pwm_x->WORK_CTRL1 |= PWMV2_WORK_CTRL1_SHADOW_LOCK_MASK;
}

/**
 * @brief select one trigger from 8, set to use input signal(selected by cnt_reload_trig) to reload timer
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param trig_index one trigger from 8
 */
static inline void pwmv2_set_counter_reload_trigmux_index(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t trig_index)
{
    pwm_x->CNT[counter].CFG2 = (pwm_x->CNT[counter].CFG2 & ~PWMV2_CNT_CFG2_CNT_RELOAD_TRIG_MASK) | PWMV2_CNT_CFG2_CNT_RELOAD_TRIG_SET(trig_index);
}

/**
 * @brief Multiple counters are enabled at the same time
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param mask bit0 - cnt0, bit1 - cnt1, bitn - cntn, n==3
 */
static inline void pwmv2_enable_multi_counter_sync(PWMV2_Type *pwm_x, uint8_t mask)
{
    pwm_x->CNT_GLBCFG &= ~(PWMV2_CNT_GLBCFG_TIMER_ENABLE_SET(mask));
    fencerw();
    pwm_x->CNT_GLBCFG |= PWMV2_CNT_GLBCFG_TIMER_ENABLE_SET(mask);
}

/**
 * @brief Multiple pwm out at the same time
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param mask bit0 - cnt0, bit1 - cnt1, bitn - cntn, n==3
 */
static inline void pwmv2_start_pwm_output_sync(PWMV2_Type *pwm_x, uint8_t mask)
{
    pwm_x->CNT_GLBCFG |= PWMV2_CNT_GLBCFG_CNT_SW_START_SET(mask);
}

/**
 * @brief unlock all shadow register
 *
 * @param[in] pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_shadow_register_unlock(PWMV2_Type *pwm_x)
{
    pwm_x->WORK_CTRL0 = PWM_UNLOCK_KEY;
}

/**
 * @brief The shadow registers can be updated only when related unlock_bit is set.
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param mask bit2 to bit 29 for value_shadow, bit30 for force_mode, bit31 for polarity.
 */
static inline void pwmv2_shadow_unlock_bit_mask(PWMV2_Type *pwm_x, uint32_t mask)
{
    pwm_x->UNLOCK = mask;
}

/**
 * @brief Set the value of the shadow register
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param index shadow index
 * @param value normal value (24bit)
 * @param high_resolution_tick High precision pwm values (0 -255)
 * @param enable_half_cycle half-cycle pwm
 */
static inline void pwmv2_set_shadow_val(PWMV2_Type *pwm_x, uint8_t index, uint32_t value, uint8_t high_resolution_tick, bool enable_half_cycle)
{
    pwm_x->SHADOW_VAL[index] = PWMV2_SHADOW_VAL_VALUE_SET(((value << 8) | (enable_half_cycle << 7) | (high_resolution_tick)));
}

/**
 * @brief force pwm output
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param mode @ref pwm_force_mode_t
 * @param invert 0 - low level, 1 - high level
 */
static inline void pwmv2_force_output(PWMV2_Type *pwm_x, pwm_channel_t chn, pwm_force_mode_t mode, bool invert)
{
    pwm_x->FORCE_MODE = (pwm_x->FORCE_MODE & ~(PWMV2_FORCE_MODE_POLARITY_SET((1 << (chn << 1))) | PWMV2_FORCE_MODE_FORCE_MODE_SET((3 << (chn << 1))))) |
                        PWMV2_FORCE_MODE_POLARITY_SET((invert << (chn << 1))) |
                        PWMV2_FORCE_MODE_FORCE_MODE_SET((mode << (chn << 1)));
}

/**
 * @brief enable four pwm outputs
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_enable_four_cmp(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG0 |= PWMV2_PWM_CFG0_TRIG_SEL4_MASK;
}

/**
 * @brief disable four pwm outputs
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_disable_four_cmp(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG0 &= ~PWMV2_PWM_CFG0_TRIG_SEL4_MASK;
}

/**
 * @brief Direct selection of the fail signal from the pin
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param pad_index motor pad
 */
static inline void pwmv2_fault_signal_select_from_pad(PWMV2_Type *pwm_x, pwm_channel_t chn, uint8_t pad_index)
{
    pwm_x->PWM[chn].CFG0 = (pwm_x->PWM[chn].CFG0 & ~PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_MASK) | PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_SET(pad_index);
}

/**
 * @brief Configure the polarity of the fail signal
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param polarity @ref pwm_fault_pad_polarity_t
 */
static inline void pwmv2_fault_signal_polarity(PWMV2_Type *pwm_x, pwm_channel_t chn, pwm_fault_pad_polarity_t polarity)
{
    pwm_x->PWM[chn].CFG0 = (pwm_x->PWM[chn].CFG0 & ~PWMV2_PWM_CFG0_FAULT_POL_ASYNC_MASK) | PWMV2_PWM_CFG0_FAULT_POL_ASYNC_SET(polarity);
}

/**
 * @brief Enable the fault signal from the pin
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_enable_fault_from_pad(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG0 |= PWMV2_PWM_CFG0_FAULT_EN_ASYNC_MASK;
}

/**
 * @brief Disable the fault signal from the pin
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_disable_fault_from_pad(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG0 &= ~PWMV2_PWM_CFG0_FAULT_EN_ASYNC_MASK;
}

/**
 * @brief Enable the fault signal from the trigmux
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_enable_fault_from_trigmux(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG0 |= PWMV2_PWM_CFG0_FAULT_EN_SYNC_MASK;
}

/**
 * @brief Disable the fault signal from the trigmux
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_disable_fault_from_trigmux(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG0 &= ~PWMV2_PWM_CFG0_FAULT_EN_SYNC_MASK;
}

/**
 * @brief Enable pwm output invert
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_enable_output_invert(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG0 |= PWMV2_PWM_CFG0_OUT_POLARITY_MASK;
}

/**
 * @brief Disable pwm output invert
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_disable_output_invert(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG0 &= ~PWMV2_PWM_CFG0_OUT_POLARITY_MASK;
}

/**
 * @brief Enable invert operations via shadow registers
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param update_select @ref pwm_shadow_register_output_polarity_t
 */
static inline void pwmv2_enable_invert_by_shadow(PWMV2_Type *pwm_x, pwm_channel_t chn, pwm_shadow_register_output_polarity_t update_select)
{
    pwm_x->PWM[chn].CFG0 |= PWMV2_PWM_CFG0_POLARITY_OPT0_MASK;
    pwm_x->PWM[chn].CFG0 = (pwm_x->PWM[chn].CFG0 & ~PWMV2_PWM_CFG0_POL_UPDATE_SEL_MASK) | PWMV2_PWM_CFG0_POL_UPDATE_SEL_SET(update_select);
}

/**
 * @brief Disable invert operations via shadow registers
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param update_select @ref pwm_shadow_register_output_polarity_t
 */
static inline void pwmv2_disable_invert_by_shadow(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG0 &= ~PWMV2_PWM_CFG0_POLARITY_OPT0_MASK;
}

/**
 * @brief Enable pwm output
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_channel_enable_output(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG1 |= PWMV2_PWM_CFG1_HIGHZ_EN_N_MASK;
}

/**
 * @brief Disable pwm output
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_channel_disable_output(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG1 &= ~PWMV2_PWM_CFG1_HIGHZ_EN_N_MASK;
}

/**
 * @brief Forces the output configuration to be updated from the time shadow hosting takes effect
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param update_time @ref pwm_force_shadow_trigger_t
 */
static inline void pwmv2_force_update_time_by_shadow(PWMV2_Type *pwm_x, pwm_channel_t chn, pwm_force_shadow_trigger_t update_time)
{
    pwm_x->PWM[chn].CFG1 = (pwm_x->PWM[chn].CFG1 & ~PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_MASK) | PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_SET(update_time);
}

/**
 * @brief set the fault mode
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param mode @ref pwm_fault_mode_t
 */
static inline void pwmv2_set_fault_mode(PWMV2_Type *pwm_x, pwm_channel_t chn, pwm_fault_mode_t mode)
{
    pwm_x->PWM[chn].CFG1 = (pwm_x->PWM[chn].CFG1 & ~PWMV2_PWM_CFG1_FAULT_MODE_MASK) | PWMV2_PWM_CFG1_FAULT_MODE_SET(mode);
}

/**
 * @brief Set the fault mode recovery time
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param trig @ref pwm_fault_recovery_trigger_t
 */
static inline void pwmv2_set_fault_recovery_time(PWMV2_Type *pwm_x, pwm_channel_t chn, pwm_fault_recovery_trigger_t trig)
{
    pwm_x->PWM[chn].CFG1 = (pwm_x->PWM[chn].CFG1 & ~PWMV2_PWM_CFG1_FAULT_REC_TIME_MASK) | PWMV2_PWM_CFG1_FAULT_REC_TIME_SET(trig);
}

/**
 * @brief Trigger forced mode by hardware signal
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_enable_force_by_hardware(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG1 &= ~PWMV2_PWM_CFG1_SW_FORCE_EN_MASK;
}

/**
 * @brief Enable force mode triggered by software
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_enable_force_by_software(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG1 |= PWMV2_PWM_CFG1_SW_FORCE_EN_MASK;
}

/**
 * @brief Disable force mode triggered by software
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_disable_force_by_software(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG1 &= ~PWMV2_PWM_CFG1_SW_FORCE_EN_MASK;
}

/**
 * @brief Enable pwm complementary mode
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_enable_pair_mode(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG1 |= PWMV2_PWM_CFG1_PAIR_MODE_MASK;
}

/**
 * @brief Disable pwm complementary mode
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_disable_pair_mode(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->PWM[chn].CFG1 &= ~PWMV2_PWM_CFG1_PAIR_MODE_MASK;
}

/**
 * @brief Configure the logic between the 4 cmp, valid only if the 4 cmp output is enabled
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param logic @ref pwm_logic_four_cmp_cfg_t
 */
static inline void pwmv2_set_four_cmp_logic(PWMV2_Type *pwm_x, pwm_channel_t chn, pwm_logic_four_cmp_cfg_t logic)
{
    pwm_x->PWM[chn].CFG1 = (pwm_x->PWM[chn].CFG1 & ~PWMV2_PWM_CFG1_PWM_LOGIC_MASK) | PWMV2_PWM_CFG1_PWM_LOGIC_SET(logic);
}

/**
 * @brief Setting the effective time of forced output
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param time @ref pwm_force_trigger_t
 */
static inline void pwmv2_set_force_update_time(PWMV2_Type *pwm_x, pwm_channel_t chn, pwm_force_trigger_t time)
{
    pwm_x->PWM[chn].CFG1 = (pwm_x->PWM[chn].CFG1 & ~PWMV2_PWM_CFG1_FORCE_TIME_MASK) | PWMV2_PWM_CFG1_FORCE_TIME_SET(time);
}

/**
 * @brief Selecting trigmux's signal as a forced mode trigger source
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param trigmux_index trigmux index
 */
static inline void pwmv2_trig_force_mode_select_trigmux_index(PWMV2_Type *pwm_x, pwm_channel_t chn, uint8_t trigmux_index)
{
    pwm_x->PWM[chn].CFG1 = (pwm_x->PWM[chn].CFG1 & ~PWMV2_PWM_CFG1_FORCE_TRIG_SEL_MASK) | PWMV2_PWM_CFG1_FORCE_TRIG_SEL_SET(trigmux_index);
}

/**
 * @brief Selection of trigger signals for software or hardware trigmux
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param trigmux_index select one trigger from 8
 */
static inline void pwmv2_trig_force_hardware_or_software_select_trigmux_index(PWMV2_Type *pwm_x, pwm_channel_t chn, uint8_t trigmux_index)
{
    pwm_x->PWM[chn].CFG1 = (pwm_x->PWM[chn].CFG1 & ~PWMV2_PWM_CFG1_FORCE_ACT_SEL_MASK) | PWMV2_PWM_CFG1_FORCE_ACT_SEL_SET(trigmux_index);
}

/**
 * @brief Select the trigger source that forces the output to take effect
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param trigmux_index select one trigger from 8
 */
static inline void pwmv2_select_force_trigmux_index(PWMV2_Type *pwm_x, pwm_channel_t chn, uint8_t trigmux_index)
{
    pwm_x->PWM[chn].CFG1 = (pwm_x->PWM[chn].CFG1 & ~PWMV2_PWM_CFG1_PWM_FORCE_SEL_MASK) | PWMV2_PWM_CFG1_PWM_FORCE_SEL_SET(trigmux_index);
}

/**
 * @brief Selection of trigger signal for fault recovery
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param trigmux_index select one trigger from 8
 */
static inline void pwmv2_select_recovery_fault_trigmux_index(PWMV2_Type *pwm_x, pwm_channel_t chn, uint8_t trigmux_index)
{
    pwm_x->PWM[chn].CFG1 = (pwm_x->PWM[chn].CFG1 & ~PWMV2_PWM_CFG1_FAULT_REC_SEL_MASK) | PWMV2_PWM_CFG1_FAULT_REC_SEL_SET(trigmux_index);
}

/**
 * @brief set pwm dead area
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param dead dead area time
 */
static inline void pwmv2_set_dead_area(PWMV2_Type *pwm_x, pwm_channel_t chn, uint32_t dead)
{
    pwm_x->PWM[chn].DEAD_AREA = PWMV2_PWM_DEAD_AREA_DEAD_AREA_SET((dead << 8));
}

/**
 * @brief Setting the comparator as an input to trigmux
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param trigmux_chn @ref pwm_channel_t
 * @param cmp_index cmp index
 */
static inline void pwmv2_set_trigout_cmp_index(PWMV2_Type *pwm_x, pwm_channel_t trigmux_chn, uint8_t cmp_index)
{
    pwm_x->TRIGGER_CFG[trigmux_chn] = (pwm_x->TRIGGER_CFG[trigmux_chn] & ~PWMV2_TRIGGER_CFG_TRIGGER_OUT_SEL_MASK) | PWMV2_TRIGGER_CFG_TRIGGER_OUT_SEL_SET(cmp_index);
}

/**
 * @brief Enable software forced output
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_enable_software_force(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->GLB_CTRL |= PWMV2_GLB_CTRL_SW_FORCE_SET((1 << chn));
}

/**
 * @brief Disable software forced output
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_disable_software_force(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->GLB_CTRL &= ~(PWMV2_GLB_CTRL_SW_FORCE_SET((1 << chn)));
}

#ifdef PWM_SOC_HRPWM_SUPPORT

/**
 * @brief Add a delay after deadband, 0-255ths of a clock cycle
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param delay_tick 0-255
 */
static inline void pwmv2_add_delay_tick_after_dead_area(PWMV2_Type *pwm_x, uint8_t delay_tick)
{
    pwm_x->GLB_CTRL = (pwm_x->GLB_CTRL & ~PWMV2_GLB_CTRL_OUTPUT_DELAY_MASK) | PWMV2_GLB_CTRL_OUTPUT_DELAY_SET(delay_tick);
}

/**
 * @brief Enable high precision pwm
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_enable_hrpwm(PWMV2_Type *pwm_x)
{
    pwm_x->GLB_CTRL |= PWMV2_GLB_CTRL_HR_PWM_EN_MASK;
}

/**
 * @brief Disable high precision pwm
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_disable_hrpwm(PWMV2_Type *pwm_x)
{
    pwm_x->GLB_CTRL &= ~PWMV2_GLB_CTRL_HR_PWM_EN_MASK;
}

#endif

/**
 * @brief Enable the software dac mode
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param dac_index @ref pwm_dac_channel_t
 */
static inline void pwmv2_enable_software_dac_mode(PWMV2_Type *pwm_x, pwm_dac_channel_t dac_index)
{
    pwm_x->GLB_CTRL2 |= PWMV2_GLB_CTRL2_DAC_SW_MODE_SET((1 << dac_index));
}

/**
 * @brief Disable the software dac mode
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param dac_index @ref pwm_dac_channel_t
 */
static inline void pwmv2_disable_software_dac_mode(PWMV2_Type *pwm_x, pwm_dac_channel_t dac_index)
{
    pwm_x->GLB_CTRL2 &= ~PWMV2_GLB_CTRL2_DAC_SW_MODE_SET((1 << dac_index));
}

/**
 * @brief Enable debug mode
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_enable_debug_mode(PWMV2_Type *pwm_x)
{
    pwm_x->GLB_CTRL2 |= PWMV2_GLB_CTRL2_DEBUG_IN_EN_MASK;
}


/**
 * @brief Disable debug mode
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_disable_debug_mode(PWMV2_Type *pwm_x)
{
    pwm_x->GLB_CTRL2 &= ~PWMV2_GLB_CTRL2_DEBUG_IN_EN_MASK;
}

/**
 * @brief Clear fault event
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 */
static inline void pwmv2_clear_fault_event(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    pwm_x->GLB_CTRL2 = (pwm_x->GLB_CTRL2 & ~(PWMV2_GLB_CTRL2_FAULT_CLEAR_MASK)) | PWMV2_GLB_CTRL2_FAULT_CLEAR_SET((1 << chn));
}

/**
 * @brief Using the Shadow Register Function
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_enable_shadow_lock_feature(PWMV2_Type *pwm_x)
{
    pwm_x->GLB_CTRL2 |= PWMV2_GLB_CTRL2_SHADOW_LOCK_EN_MASK;
}

/**
 * @brief Do not use the shadow register function
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_disable_shadow_lock_feature(PWMV2_Type *pwm_x)
{
    pwm_x->GLB_CTRL2 &= ~PWMV2_GLB_CTRL2_SHADOW_LOCK_EN_MASK;
}

/**
 * @brief Get counter work status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter_index @ref pwm_counter_t
 * @return uint32_t status mask
 */
static inline uint32_t pwmv2_get_counter_working_status(PWMV2_Type *pwm_x, pwm_counter_t counter_index)
{
    return PWMV2_CNT_RELOAD_WORK_VALUE_GET(pwm_x->CNT_RELOAD_WORK[counter_index]);
}

/**
 * @brief Get cmp work status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cmp_index cmp index
 * @return uint32_t status mask
 */
static inline uint32_t pwmv2_get_cmp_working_status(PWMV2_Type *pwm_x, uint8_t cmp_index)
{
    return PWMV2_CMP_VAL_WORK_VALUE_GET(pwm_x->CMP_VAL_WORK[cmp_index]);
}

/**
 * @brief Get force mode work status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @return uint32_t status mask
 */
static inline uint32_t pwmv2_get_force_working_status(PWMV2_Type *pwm_x)
{
    return PWMV2_FORCE_WORK_FORCE_MODE_GET(pwm_x->FORCE_WORK);
}

/**
 * @brief Get the status of the output polarity
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @return uint32_t polarity
 */
static inline uint32_t pwmv2_get_force_work_out_polarity_status(PWMV2_Type *pwm_x)
{
    return PWMV2_FORCE_WORK_OUT_POLARITY_GET(pwm_x->FORCE_WORK);
}

/**
 * @brief Getting the value of a counter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter_index @ref pwm_counter_t
 * @return uint32_t counter value
 */
static inline uint32_t pwmv2_get_counter_value(PWMV2_Type *pwm_x, pwm_counter_t counter_index)
{
    return PWMV2_CNT_VAL_VALUE_GET(pwm_x->CNT_VAL[counter_index]);
}

/**
 * @brief set dac value
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param dac_index @ref pwm_dac_channel_t
 * @param value dac value
 */
static inline void pwmv2_set_dac_value(PWMV2_Type *pwm_x, pwm_dac_channel_t dac_index, uint32_t value)
{
    pwm_x->DAC_VALUE_SV[dac_index] = PWMV2_DAC_VALUE_SV_VALUE_SET(value);
}

/**
 * @brief get capture posedge value
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @return uint32_t posedge value
 */
static inline uint32_t pwmv2_get_capture_posedge_value(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    return PWMV2_CAPTURE_POS_CAPTURE_POS_GET(pwm_x->CAPTURE_POS[chn]);
}

/**
 * @brief Select the input source for the captured signal
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param select @ref pwm_capture_input_select_t
 */
static inline void pwmv2_capture_selection_input_source(PWMV2_Type *pwm_x, pwm_channel_t chn, pwm_capture_input_select_t select)
{
    pwm_x->CAPTURE_POS[chn] = (pwm_x->CAPTURE_POS[chn] & ~PWMV2_CAPTURE_POS_CAPTURE_SELGPIO_MASK) |
                                                        PWMV2_CAPTURE_POS_CAPTURE_SELGPIO_SET(select);
}

/**
 * @brief Set the counter to be used for the capture channel
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param counter_index counter index
 */
static inline void pwmv2_set_capture_counter_index(PWMV2_Type *pwm_x, pwm_channel_t chn, uint8_t counter_index)
{
    pwm_x->CAPTURE_POS[chn] = (pwm_x->CAPTURE_POS[chn] & ~PWMV2_CAPTURE_POS_CNT_INDEX_MASK) |
                                                        PWMV2_CAPTURE_POS_CNT_INDEX_SET(counter_index);
}

/**
 * @brief get capture negedge value
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @return uint32_t posedge value
 */
static inline uint32_t pwmv2_get_capture_negedge_value(PWMV2_Type *pwm_x, pwm_channel_t chn)
{
    return PWMV2_CAPTURE_NEG_CAPTURE_NEG_GET(pwm_x->CAPTURE_NEG[chn]);
}

/**
 * @brief Get all interrupt status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @return uint32_t irq status mask
 */
static inline uint32_t pwmv2_get_irq_status_all(PWMV2_Type *pwm_x)
{
    return pwm_x->IRQ_STS;
}

/**
 * @brief clear calculate overflow irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_clear_calculate_overflow_irq_status(PWMV2_Type *pwm_x)
{
    pwm_x->IRQ_STS &= PWMV2_IRQ_STS_IRQ_CAL_OVERFLOW_MASK;
}

/**
 * @brief enable calculate overflow irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_enable_calculate_overflow_irq(PWMV2_Type *pwm_x)
{
    pwm_x->IRQ_EN |= PWMV2_IRQ_EN_IRQ_EN_OVERFLOW_MASK;
}

/**
 * @brief Disable calculate overflow irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 */
static inline void pwmv2_disable_calculate_overflow_irq(PWMV2_Type *pwm_x)
{
    pwm_x->IRQ_EN &= ~PWMV2_IRQ_EN_IRQ_EN_OVERFLOW_MASK;
}

/**
 * @brief Get cmp irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @return uint32_t irq status
 */
static inline uint32_t pwmv2_get_cmp_irq_status(PWMV2_Type *pwm_x)
{
    return PWMV2_IRQ_STS_CMP_IRQ_STS_CMP_GET(pwm_x->IRQ_STS_CMP);
}

/**
 * @brief Clear cmp irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param mask uint32_t irq status
 */
static inline void pwmv2_clear_cmp_irq_status(PWMV2_Type *pwm_x, uint32_t mask)
{
    pwm_x->IRQ_STS_CMP = PWMV2_IRQ_STS_CMP_IRQ_STS_CMP_SET(mask);
}

/**
 * @brief Get reload irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @return uint32_t reload irq status
 */
static inline uint32_t pwmv2_get_reload_irq_status(PWMV2_Type *pwm_x)
{
    return PWMV2_IRQ_STS_RELOAD_IRQ_STS_RELOAD_GET(pwm_x->IRQ_STS_RELOAD);
}

/**
 * @brief Clear reload irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param mask irq status mask
 */
static inline void pwmv2_clear_reload_irq_status(PWMV2_Type *pwm_x, uint32_t mask)
{
    pwm_x->IRQ_STS_RELOAD = PWMV2_IRQ_STS_RELOAD_IRQ_STS_RELOAD_SET(mask);
}

/**
 * @brief Get capture posedge irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @return uint32_t irq status
 */
static inline uint32_t pwmv2_get_capture_posedge_irq_status(PWMV2_Type *pwm_x)
{
    return PWMV2_IRQ_STS_CAP_POS_IRQ_STS_CAP_POS_GET(pwm_x->IRQ_STS_CAP_POS);
}

/**
 * @brief Clear capture posedge irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param mask capture posedge irq mask
 */
static inline void pwmv2_clear_capture_posedge_irq_status(PWMV2_Type *pwm_x, uint32_t mask)
{
    pwm_x->IRQ_STS_CAP_POS = PWMV2_IRQ_STS_CAP_POS_IRQ_STS_CAP_POS_SET(mask);
}

/**
 * @brief Get capture negedge irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @return uint32_t irq status
 */
static inline uint32_t pwmv2_get_capture_negedge_irq_status(PWMV2_Type *pwm_x)
{
    return PWMV2_IRQ_STS_CAP_NEG_IRQ_STS_CAP_NEG_GET(pwm_x->IRQ_STS_CAP_NEG);
}

/**
 * @brief Clear capture negedge irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param mask capture posedge irq mask
 */
static inline void pwmv2_clear_capture_negedge_irq_status(PWMV2_Type *pwm_x, uint32_t mask)
{
    pwm_x->IRQ_STS_CAP_NEG = PWMV2_IRQ_STS_CAP_NEG_IRQ_STS_CAP_NEG_SET(mask);
}

/**
 * @brief Get fault irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @return uint32_t irq status
 */
static inline uint32_t pwmv2_get_fault_irq_status(PWMV2_Type *pwm_x)
{
    return PWMV2_IRQ_STS_FAULT_IRQ_STS_FAULT_GET(pwm_x->IRQ_STS_FAULT);
}

/**
 * @brief Clear fault irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @return uint32_t irq status
 */
static inline void pwmv2_clear_fault_irq_status(PWMV2_Type *pwm_x, uint32_t mask)
{
    pwm_x->IRQ_STS_FAULT = PWMV2_IRQ_STS_FAULT_IRQ_STS_FAULT_SET(mask);
}

/**
 * @brief Get burstend irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @return uint32_t irq status
 */
static inline uint32_t pwmv2_get_burstend_irq_status(PWMV2_Type *pwm_x)
{
    return PWMV2_IRQ_STS_BURSTEND_IRQ_STS_BURSTEND_GET(pwm_x->IRQ_STS_BURSTEND);
}

/**
 * @brief Clear burstend irq status
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param mask mask status
 */
static inline void pwmv2_clear_burstend__irq_status(PWMV2_Type *pwm_x, uint32_t mask)
{
    pwm_x->IRQ_STS_BURSTEND = PWMV2_IRQ_STS_BURSTEND_IRQ_STS_BURSTEND_SET(mask);
}

/**
 * @brief enable cmp irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cmp_index cmp index
 */
static inline void pwmv2_enable_cmp_irq(PWMV2_Type *pwm_x, uint8_t cmp_index)
{
    pwm_x->IRQ_EN_CMP |= PWMV2_IRQ_EN_CMP_IRQ_EN_CMP_SET(1 << cmp_index);
}

/**
 * @brief disable cmp irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cmp_index cmp index
 */
static inline void pwmv2_disable_cmp_irq(PWMV2_Type *pwm_x, uint8_t cmp_index)
{
    pwm_x->IRQ_EN_CMP &= ~PWMV2_IRQ_EN_CMP_IRQ_EN_CMP_SET(1 << cmp_index);
}

/**
 * @brief enable reload irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter_index @ref pwm_counter_t
 */
static inline void pwmv2_enable_reload_irq(PWMV2_Type *pwm_x, pwm_counter_t counter_index)
{
    pwm_x->IRQ_EN_RELOAD |= PWMV2_IRQ_EN_RELOAD_IRQ_EN_RELOAD_SET(1 << counter_index);
}

/**
 * @brief disable reload irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter_index @ref pwm_counter_t
 */
static inline void pwmv2_disable_reload_irq(PWMV2_Type *pwm_x, pwm_counter_t counter_index)
{
    pwm_x->IRQ_EN_RELOAD &= ~PWMV2_IRQ_EN_RELOAD_IRQ_EN_RELOAD_SET(1 << counter_index);
}

/**
 * @brief enable capture posedge irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param channel_index @ref pwm_counter_t
 */
static inline void pwmv2_enable_capture_posedge_irq(PWMV2_Type *pwm_x, pwm_channel_t channel_index)
{
    pwm_x->IRQ_EN_CAP_POS |= PWMV2_IRQ_EN_CAP_POS_IRQ_EN_CAP_POS_SET(1 << channel_index);
}

/**
 * @brief disable capture posedge irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param channel_index @ref pwm_counter_t
 */
static inline void pwmv2_disable_capture_posedge_irq(PWMV2_Type *pwm_x, pwm_channel_t channel_index)
{
    pwm_x->IRQ_EN_CAP_POS &= ~PWMV2_IRQ_EN_CAP_POS_IRQ_EN_CAP_POS_SET(1 << channel_index);
}

/**
 * @brief enable capture nedege irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param channel_index @ref pwm_channel_t
 */
static inline void pwmv2_enable_capture_nededge_irq(PWMV2_Type *pwm_x, pwm_channel_t channel_index)
{
    pwm_x->IRQ_EN_CAP_NEG |= PWMV2_IRQ_EN_CAP_NEG_IRQ_EN_CAP_NEG_SET(1 << channel_index);
}

/**
 * @brief disable capture nedege irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param channel_index @ref pwm_channel_t
 */
static inline void pwmv2_disable_capture_nededge_irq(PWMV2_Type *pwm_x, pwm_channel_t channel_index)
{
    pwm_x->IRQ_EN_CAP_NEG &= ~PWMV2_IRQ_EN_CAP_NEG_IRQ_EN_CAP_NEG_SET(1 << channel_index);
}

/**
 * @brief enable fault irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param channel_index @ref pwm_channel_t
 */
static inline void pwmv2_enable_fault_irq(PWMV2_Type *pwm_x, pwm_channel_t channel_index)
{
    pwm_x->IRQ_EN_FAULT |= PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_SET(1 << channel_index);
}

/**
 * @brief disable fault irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param channel_index @ref pwm_channel_t
 */
static inline void pwmv2_disable_fault_irq(PWMV2_Type *pwm_x, pwm_channel_t channel_index)
{
    pwm_x->IRQ_EN_FAULT &= ~PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_SET(1 << channel_index);
}

/**
 * @brief enable burstend irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter_index @ref pwm_counter_t
 */
static inline void pwmv2_enable_burstend_irq(PWMV2_Type *pwm_x, pwm_counter_t counter_index)
{
    pwm_x->IRQ_EN_BURSTEND |= PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_SET(1 << counter_index);
}

/**
 * @brief disable burstend irq
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter_index @ref pwm_counter_t
 */
static inline void pwmv2_disable_burstend_irq(PWMV2_Type *pwm_x, pwm_counter_t counter_index)
{
    pwm_x->IRQ_EN_BURSTEND &= ~PWMV2_IRQ_EN_FAULT_IRQ_EN_FAULT_SET(1 << counter_index);
}

/**
 * @brief enable dma at compare point
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param dma_channel @ref pwm_dma_chn_t
 * @param cmp_index cmp index
 */
static inline void pwmv2_enable_dma_at_compare_point(PWMV2_Type *pwm_x, pwm_dma_chn_t dma_channel, uint8_t cmp_index)
{
    pwm_x->DMA_EN = (pwm_x->DMA_EN & ~((PWMV2_DMA_EN_DMA0_SEL_MASK | PWMV2_DMA_EN_DMA0_EN_MASK) << (PWMV2_DMA_EN_DMA1_SEL_SHIFT * dma_channel))) |
    ((PWMV2_DMA_EN_DMA0_SEL_SET(cmp_index) | PWMV2_DMA_EN_DMA0_EN_MASK) << (PWMV2_DMA_EN_DMA1_SEL_SHIFT * dma_channel));
}

/**
 * @brief disable dma at compare point
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param dma_channel @ref pwm_dma_chn_t
 */
static inline void pwmv2_disable_dma_at_compare_point(PWMV2_Type *pwm_x, pwm_dma_chn_t dma_channel)
{
    pwm_x->DMA_EN &= ~((PWMV2_DMA_EN_DMA0_SEL_MASK | PWMV2_DMA_EN_DMA0_EN_MASK) << (PWMV2_DMA_EN_DMA1_SEL_SHIFT * dma_channel));
}

/**
 * @brief enable dma at reload point
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param dma_channel @ref pwm_dma_chn_t
 * @param reload_index @ref pwm_counter_t
 */
static inline void pwmv2_enable_dma_at_reload_point(PWMV2_Type *pwm_x, pwm_dma_chn_t dma_channel, pwm_counter_t reload_index)
{
    pwm_x->DMA_EN = (pwm_x->DMA_EN & ~((PWMV2_DMA_EN_DMA0_SEL_MASK | PWMV2_DMA_EN_DMA0_EN_MASK) << (PWMV2_DMA_EN_DMA1_SEL_SHIFT * dma_channel))) |
    ((PWMV2_DMA_EN_DMA0_SEL_SET(reload_index + 24) | PWMV2_DMA_EN_DMA0_EN_MASK) << (PWMV2_DMA_EN_DMA1_SEL_SHIFT * dma_channel));
}

/**
 * @brief disable dma at reload point
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param dma_channel @ref pwm_dma_chn_t
 */
static inline void pwmv2_disable_dma_at_reload_point(PWMV2_Type *pwm_x, pwm_dma_chn_t dma_channel)
{
    pwm_x->DMA_EN &= ~((PWMV2_DMA_EN_DMA0_SEL_MASK | PWMV2_DMA_EN_DMA0_EN_MASK) << (PWMV2_DMA_EN_DMA1_SEL_SHIFT * dma_channel));
}

/**
 * @brief select compare point 0 index
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param cmp_index cmp index
 */
static inline void pwmv2_reload_select_compare_point0_index(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t cmp_index)
{
    pwm_x->CNT[counter].CFG0 = (pwm_x->CNT[counter].CFG0 & ~(PWMV2_CNT_CFG0_RLD_CMP_SEL0_MASK)) | PWMV2_CNT_CFG0_RLD_CMP_SEL0_SET(cmp_index);
}

/**
 * @brief select compare point 1 index
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param cmp_index cmp index
 */
static inline void pwmv2_reload_select_compare_point1_index(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t cmp_index)
{
    pwm_x->CNT[counter].CFG0 = (pwm_x->CNT[counter].CFG0 & ~(PWMV2_CNT_CFG0_RLD_CMP_SEL1_MASK)) | PWMV2_CNT_CFG0_RLD_CMP_SEL1_SET(cmp_index);
}

/**
 * @brief Select the input trigger source for the reload point
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param trig_index trig index
 */
static inline void pwmv2_reload_select_input_trigger(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t trig_index)
{
    pwm_x->CNT[counter].CFG0 = (pwm_x->CNT[counter].CFG0 & ~(PWMV2_CNT_CFG0_RLD_TRIG_SEL_MASK)) | PWMV2_CNT_CFG0_RLD_TRIG_SEL_SET(trig_index);
}

/**
 * @brief Set reload update time
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param update @ref pwm_reload_update_time_t
 */
static inline void pwmv2_set_reload_update_time(PWMV2_Type *pwm_x, pwm_counter_t counter, pwm_reload_update_time_t update)
{
    pwm_x->CNT[counter].CFG0 = (pwm_x->CNT[counter].CFG0 & ~(PWMV2_CNT_CFG0_RLD_UPDATE_TIME_MASK)) | PWMV2_CNT_CFG0_RLD_UPDATE_TIME_SET(update);
}

/**
 * @brief Set dac data parameter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param dac_parameter dac parameter
 */
static inline void pwmv2_counter_set_dac_data_parameter(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t dac_parameter)
{
    pwm_x->CNT[counter].CFG0 = (pwm_x->CNT[counter].CFG0 & ~PWMV2_CNT_CFG0_CNT_D_PARAM_MASK) | PWMV2_CNT_CFG0_CNT_D_PARAM_SET(dac_parameter);
}

/**
 * @brief Select dac index
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param dac_index @ref pwm_dac_channel_t
 */
static inline void pwmv2_conuter_select_dac_index(PWMV2_Type *pwm_x, pwm_counter_t counter, pwm_dac_channel_t dac_index)
{
    pwm_x->CNT[counter].CFG1 = (pwm_x->CNT[counter].CFG1 & ~PWMV2_CNT_CFG1_CNT_DAC_INDEX_MASK) | PWMV2_CNT_CFG1_CNT_DAC_INDEX_SET(dac_index);
}

/**
 * @brief Enable the upper limit of the calculation unit
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_up_limit_enable(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG1 |= PWMV2_CNT_CFG1_CNT_LU_EN_MASK;
}

/**
 * @brief Disable the upper limit of the calculation unit
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_up_limit_disable(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG1 &= ~PWMV2_CNT_CFG1_CNT_LU_EN_MASK;
}

/**
 * @brief Select the upper limit from the shadow register
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param index shadow index
 */
static inline void pwmv2_counter_select_up_limit_from_shadow_value(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t index)
{
    pwm_x->CNT[counter].CFG1 = (pwm_x->CNT[counter].CFG1 & ~PWMV2_CNT_CFG1_CNT_LIM_UP_MASK) | PWMV2_CNT_CFG1_CNT_LIM_UP_SET(index);
}

/**
 * @brief Enable the lower limit of the calculation unit
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_low_limit_enable(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG1 |= PWMV2_CNT_CFG1_CNT_LL_EN_MASK;
}


/**
 * @brief Disable the lower limit of the calculation unit
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_low_limit_disable(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG1 &= ~PWMV2_CNT_CFG1_CNT_LL_EN_MASK;
}

/**
 * @brief Select the lower limit from the shadow register
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param index shadow index
 */
static inline void pwmv2_counter_select_low_limit_from_shadow_value(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t index)
{
    pwm_x->CNT[counter].CFG1 = (pwm_x->CNT[counter].CFG1 & ~PWMV2_CNT_CFG1_CNT_LIM_LO_MASK) | PWMV2_CNT_CFG1_CNT_LIM_LO_SET(index);
}

/**
 * @brief Select data offset from shadow register
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param index shadow index
 */
static inline void pwmv2_counter_select_data_offset_from_shadow_value(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t index)
{
    pwm_x->CNT[counter].CFG1 = (pwm_x->CNT[counter].CFG1 & ~PWMV2_CNT_CFG1_CNT_IN_OFF_MASK) | PWMV2_CNT_CFG1_CNT_IN_OFF_SET(index);
}

/**
 * @brief enable counter reload by trigmux
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_enable_reload_by_trig(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG2 |= PWMV2_CNT_CFG2_CNT_RELOAD_EN_MASK;
}

/**
 * @brief disable counter reload by trigmux
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_disable_reload_by_trig(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG2 &= ~PWMV2_CNT_CFG2_CNT_RELOAD_EN_MASK;
}

/**
 * @brief Select counter update by trigmux1
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param trig_index trigmux index
 */
static inline void pwmv2_counter_update_trig1(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t trig_index)
{
    pwm_x->CNT[counter].CFG2 = (pwm_x->CNT[counter].CFG2 & ~PWMV2_CNT_CFG2_CNT_UPDATE_TRIG1_MASK) | PWMV2_CNT_CFG2_CNT_UPDATE_TRIG1_SET(trig_index);
}

/**
 * @brief Enable counter update by trigmux1
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_enable_update_trig1(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG2 |= PWMV2_CNT_CFG2_CNT_UPDATE_EN1_MASK;
}

/**
 * @brief Disable counter update by trigmux1
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_disable_update_trig1(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG2 &= ~PWMV2_CNT_CFG2_CNT_UPDATE_EN1_MASK;
}

/**
 * @brief Enable change counter value to one of the calculation cell output when cnt_update_triger1 issued
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param cal_index cal index
 */
static inline void pwmv2_counter_set_trig1_calculate_cell_index(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t cal_index)
{
    pwm_x->CNT[counter].CFG2 = (pwm_x->CNT[counter].CFG2 & ~PWMV2_CNT_CFG2_CNT_TRIG1_MASK) | PWMV2_CNT_CFG2_CNT_TRIG1_SET(cal_index);
}

/**
 * @brief Select counter update by trigmux0
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param trig_index trigmux index
 */
static inline void pwmv2_counter_update_trig0(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t trig_index)
{
    pwm_x->CNT[counter].CFG2 = (pwm_x->CNT[counter].CFG2 & ~PWMV2_CNT_CFG2_CNT_UPDATE_TRIG0_MASK) | PWMV2_CNT_CFG2_CNT_UPDATE_TRIG0_SET(trig_index);
}

/**
 * @brief Enable counter update by trigmux0
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_enable_update_trig0(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG2 |= PWMV2_CNT_CFG2_CNT_UPDATE_EN0_MASK;
}

/**
 * @brief Disable counter update by trigmux0
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_disable_update_trig0(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG2 &= ~PWMV2_CNT_CFG2_CNT_UPDATE_EN0_MASK;
}

/**
 * @brief Enable change counter value to one of the calculation cell output when cnt_update_triger0 issued
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param cal_index cal index
 */
static inline void pwmv2_counter_set_trig0_calculate_cell_index(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t cal_index)
{
    pwm_x->CNT[counter].CFG2 = (pwm_x->CNT[counter].CFG2 & ~PWMV2_CNT_CFG2_CNT_TRIG0_MASK) | PWMV2_CNT_CFG2_CNT_TRIG0_SET(cal_index);
}

/**
 * @brief Set trigmux index to start counter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param trig_index trig index
 */
static inline void pwmv2_counter_start_select_trigger_index(PWMV2_Type *pwm_x, pwm_counter_t counter, uint8_t trig_index)
{
    pwm_x->CNT[counter].CFG3 = (pwm_x->CNT[counter].CFG3 & ~PWMV2_CNT_CFG3_CNT_START_SEL_MASK) | PWMV2_CNT_CFG3_CNT_START_SEL_SET(trig_index);
}

/**
 * @brief Enable trigmux to trigger counter initiation
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_start_trigger_enable(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG3 |= PWMV2_CNT_CFG3_CNT_HW_START_EN_MASK;
}

/**
 * @brief Disable trigmux to trigger counter initiation
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_start_trigger_disable(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG3 &= ~PWMV2_CNT_CFG3_CNT_HW_START_EN_MASK;
}

/**
 * @brief Set counter burst value
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 * @param burst burst value
 */
static inline void pwmv2_set_counter_burst(PWMV2_Type *pwm_x, pwm_counter_t counter, uint16_t burst)
{
    pwm_x->CNT[counter].CFG3 |= PWMV2_CNT_CFG3_CNT_BURST_SET(burst);
}

/**
 * @brief Disable counter burst function
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_counter_burst_disable(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT[counter].CFG3 |= PWMV2_CNT_CFG3_CNT_BURST_MASK;
}

/**
 * @brief start pwm output
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_start_pwm_output(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT_GLBCFG |= PWMV2_CNT_GLBCFG_CNT_SW_START_SET((1 << counter));
}

/**
 * @brief Reset pwm counter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_reset_counter(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT_GLBCFG |= PWMV2_CNT_GLBCFG_TIMER_RESET_SET((1 << counter));
}

/**
 * @brief Enable pwm counter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_enable_counter(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT_GLBCFG |= PWMV2_CNT_GLBCFG_TIMER_ENABLE_SET((1 << counter));
}

/**
 * @brief Disable pwm counter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param counter @ref pwm_counter_t
 */
static inline void pwmv2_disable_counter(PWMV2_Type *pwm_x, pwm_counter_t counter)
{
    pwm_x->CNT_GLBCFG &= ~PWMV2_CNT_GLBCFG_TIMER_ENABLE_SET((1 << counter));
}

/**
 * @brief Set calculate up limit parameter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 * @param value parameter
 */
static inline void pwmv2_calculate_set_up_limit_parameter(PWMV2_Type *pwm_x, uint8_t cal_index, uint8_t value)
{
    pwm_x->CAL[cal_index].CFG0 = (pwm_x->CAL[cal_index].CFG0 & ~PWMV2_CAL_CFG0_CAL_LU_PARAM_MASK) | PWMV2_CAL_CFG0_CAL_LU_PARAM_SET(value);
}

/**
 * @brief Set calculate low limit parameter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 * @param value parameter
 */
static inline void pwmv2_calculate_set_low_limit_parameter(PWMV2_Type *pwm_x, uint8_t cal_index, uint8_t value)
{
    pwm_x->CAL[cal_index].CFG0 = (pwm_x->CAL[cal_index].CFG0 & ~PWMV2_CAL_CFG0_CAL_LL_PARAM_MASK) | PWMV2_CAL_CFG0_CAL_LL_PARAM_SET(value);
}

/**
 * @brief Set calculate period parameter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 * @param value parameter
 */
static inline void pwmv2_calculate_set_period_parameter(PWMV2_Type *pwm_x, uint8_t cal_index, uint8_t value)
{
    pwm_x->CAL[cal_index].CFG0 = (pwm_x->CAL[cal_index].CFG0 & ~PWMV2_CAL_CFG0_CAL_T_PARAM_MASK) | PWMV2_CAL_CFG0_CAL_T_PARAM_SET(value);
}

/**
 * @brief Set calculate dac value parameter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 * @param value parameter
 */
static inline void pwmv2_calculate_set_dac_value_parameter(PWMV2_Type *pwm_x, uint8_t cal_index, uint8_t value)
{
    pwm_x->CAL[cal_index].CFG0 = (pwm_x->CAL[cal_index].CFG0 & ~PWMV2_CAL_CFG0_CAL_D_PARAM_MASK) | PWMV2_CAL_CFG0_CAL_D_PARAM_SET(value);
}

/**
 * @brief Select calculate index to counter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 * @param counter_calculate counter index
 */
static inline void pwmv2_calculate_select_counter_calculate_index(PWMV2_Type *pwm_x, uint8_t cal_index, uint8_t counter_calculate)
{
    pwm_x->CAL[cal_index].CFG1 = (pwm_x->CAL[cal_index].CFG1 & ~PWMV2_CAL_CFG1_CAL_T_INDEX_MASK) | PWMV2_CAL_CFG1_CAL_T_INDEX_SET(counter_calculate);
}

/**
 * @brief Select calculate input value
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 * @param index shadow index
 */
static inline void pwmv2_calculate_select_in_value(PWMV2_Type *pwm_x, uint8_t cal_index, uint8_t index)
{
    pwm_x->CAL[cal_index].CFG1 = (pwm_x->CAL[cal_index].CFG1 & ~PWMV2_CAL_CFG1_CAL_IN_INDEX_MASK) | PWMV2_CAL_CFG1_CAL_IN_INDEX_SET(index);
}

/**
 * @brief enable calculate up limit
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 */
static inline void pwmv2_calculate_enable_up_limit(PWMV2_Type *pwm_x, uint8_t cal_index)
{
    pwm_x->CAL[cal_index].CFG1 |= PWMV2_CAL_CFG1_CAL_LU_EN_MASK;
}

/**
 * @brief disable calculate up limit
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 */
static inline void pwmv2_calculate_disable_up_limit(PWMV2_Type *pwm_x, uint8_t cal_index)
{
    pwm_x->CAL[cal_index].CFG1 &= ~PWMV2_CAL_CFG1_CAL_LU_EN_MASK;
}

/**
 * @brief Select up limit offset from shadow index
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 * @param shadow_index shadow index
 */
static inline void pwmv2_calculate_select_up_limit_offset(PWMV2_Type *pwm_x, uint8_t cal_index, uint8_t shadow_index)
{
    pwm_x->CAL[cal_index].CFG1 = (pwm_x->CAL[cal_index].CFG1 & ~PWMV2_CAL_CFG1_CAL_LIM_UP_MASK) | PWMV2_CAL_CFG1_CAL_LIM_UP_SET(shadow_index);
}

/**
 * @brief Select low limit offset from shadow index
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 * @param shadow_index shadow index
 */
static inline void pwmv2_calculate_select_low_limit_offset(PWMV2_Type *pwm_x, uint8_t cal_index, uint8_t shadow_index)
{
    pwm_x->CAL[cal_index].CFG1 = (pwm_x->CAL[cal_index].CFG1 & ~PWMV2_CAL_CFG1_CAL_LIM_LO_MASK) | PWMV2_CAL_CFG1_CAL_LIM_LO_SET(shadow_index);
}

/**
 * @brief Select offset from shadow index
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 * @param shadow_index shadow index
 */
static inline void pwmv2_calculate_select_in_offset(PWMV2_Type *pwm_x, uint8_t cal_index, uint8_t shadow_index)
{
    pwm_x->CAL[cal_index].CFG1 = (pwm_x->CAL[cal_index].CFG1 & ~PWMV2_CAL_CFG1_CAL_IN_OFF_MASK) | PWMV2_CAL_CFG1_CAL_IN_OFF_SET(shadow_index);
}

/**
 * @brief enable low limit
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 */
static inline void pwmv2_calculate_enable_low_limit(PWMV2_Type *pwm_x, uint8_t cal_index)
{
    pwm_x->CAL[cal_index].CFG1 |= PWMV2_CAL_CFG1_CAL_LL_EN_MASK;
}

/**
 * @brief disable low limit
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 */
static inline void pwmv2_calculate_disable_low_limit(PWMV2_Type *pwm_x, uint8_t cal_index)
{
    pwm_x->CAL[cal_index].CFG1 &= ~PWMV2_CAL_CFG1_CAL_LL_EN_MASK;
}

/**
 * @brief Select cmp trigmux index
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cmp_index cmp index
 * @param trig_index trigmux index
 */
static inline void pwmv2_select_cmp_trigmux(PWMV2_Type *pwm_x, uint8_t cmp_index, uint8_t trig_index)
{
    pwm_x->CMP[cmp_index].CFG = (pwm_x->CMP[cmp_index].CFG & ~PWMV2_CMP_CFG_CMP_TRIG_SEL_MASK) | PWMV2_CMP_CFG_CMP_TRIG_SEL_SET(trig_index);
}

/**
 * @brief Select cmp update trigmux time
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cmp_index cmp index
 * @param trig_time @ref pwm_cmp_shadow_register_update_trigger_t
 */
static inline void pwmv2_cmp_update_trig_time(PWMV2_Type *pwm_x, uint8_t cmp_index, pwm_cmp_shadow_register_update_trigger_t trig_time)
{
    pwm_x->CMP[cmp_index].CFG = (pwm_x->CMP[cmp_index].CFG & ~PWMV2_CMP_CFG_CMP_UPDATE_TIME_MASK) | PWMV2_CMP_CFG_CMP_UPDATE_TIME_SET(trig_time);
}

/**
 * @brief Select cmp source
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cmp_index cmp index
 * @param cmp_sel @ref pwm_cmp_source_t
 * @param index source index
 */
static inline void pwmv2_select_cmp_source(PWMV2_Type *pwm_x, uint8_t cmp_index, pwm_cmp_source_t cmp_sel, uint8_t index)
{
    pwm_x->CMP[cmp_index].CFG = (pwm_x->CMP[cmp_index].CFG & ~PWMV2_CMP_CFG_CMP_IN_SEL_MASK) | PWMV2_CMP_CFG_CMP_IN_SEL_SET((cmp_sel + index));
}

/**
 * @brief Select cmp use counter
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cmp_index cmp index
 * @param counter_index @ref pwm_counter_t
 */
static inline void pwmv2_cmp_select_counter(PWMV2_Type *pwm_x, uint8_t cmp_index, pwm_counter_t counter_index)
{
    if (cmp_index >= 16) {
        pwm_x->CMP[cmp_index].CFG = (pwm_x->CMP[cmp_index].CFG & ~PWMV2_CMP_CFG_CMP_CNT_MASK) | PWMV2_CMP_CFG_CMP_CNT_SET((counter_index));
    }
}

/**
 * @brief config pwm cmp
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param index cmp index
 * @param config @ref pwmv2_cmp_config_t
 */
void pwmv2_config_cmp(PWMV2_Type *pwm_x, uint8_t index, pwmv2_cmp_config_t *config);

/**
 * @brief config async fault source
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param index cmp index
 * @param config @ref pwmv2_async_fault_source_config_t
 */
void pwmv2_config_async_fault_source(PWMV2_Type *pwm_x, pwm_channel_t index, pwmv2_async_fault_source_config_t *config);

/**
 * @brief config pwm
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param index @ref pwm_channel_t
 * @param config @ref pwmv2_config_t
 * @param enable_pair_mode bool
 */
void pwmv2_config_pwm(PWMV2_Type *pwm_x, pwm_channel_t index, pwmv2_config_t *config, bool enable_pair_mode);

/**
 * @brief Set pwm waveform
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param pwm_config @ref pwmv2_config_t
 * @param cmp_start_index cmp start index
 * @param cmp @ref pwmv2_cmp_config_t
 * @param cmp_num cmp number
 * @return hpm_stat_t @ref hpm_stat_t
 */
hpm_stat_t pwmv2_setup_waveform(PWMV2_Type *pwm_x,
                        pwm_channel_t chn, pwmv2_config_t *pwm_config,
                        uint8_t cmp_start_index, pwmv2_cmp_config_t *cmp, uint8_t cmp_num);

/**
 * @brief set the pwm waveform complementary mode
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param chn @ref pwm_channel_t
 * @param pwm_pair_config @ref pwmv2_pair_config_t
 * @param cmp_start_index cmp start index
 * @param cmp @ref pwmv2_cmp_config_t
 * @param cmp_num cmp number
 * @return hpm_stat_t @ref hpm_stat_t
 */
hpm_stat_t pwmv2_setup_waveform_in_pair(PWMV2_Type *pwm_x, pwm_channel_t chn,
                        pwmv2_pair_config_t *pwm_pair_config, uint8_t cmp_start_index,
                        pwmv2_cmp_config_t *cmp, uint8_t cmp_num);

/**
 * @brief Configure the cmp calculate unit
 *
 * @param pwm_x PWM base address, HPM_PWMx(x=0..n)
 * @param cal_index calculate index
 * @param cal @ref pwmv2_cmp_calculate_cfg_t
 */
void pwmv2_setup_cmp_calculate(PWMV2_Type *pwm_x, uint8_t cal_index, pwmv2_cmp_calculate_cfg_t *cal);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_PWMV2_DRV_H */
