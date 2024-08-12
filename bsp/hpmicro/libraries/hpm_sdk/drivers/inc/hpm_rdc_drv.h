/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_RDC_DRV_H
#define HPM_RDC_DRV_H

#include "hpm_common.h"
#include "hpm_rdc_regs.h"
#include "hpm_soc_feature.h"

/**
 * @brief RDC driver APIs
 * @defgroup rdc_interface RDC driver APIs
 * @ingroup rdc_interfaces
 * @{
 */


#ifdef __cplusplus
extern "C" {
#endif
/**
 * @name Initialization and Deinitialization
 * @{
 */


/**
 * @brief Rdc output precision, use n points to form an excitation signal period.
 *
 */
typedef enum rdc_output_precision {
    rdc_output_precision_4_point = 0,
    rdc_output_precision_8_point = 1,
    rdc_output_precision_16_point = 2,
    rdc_output_precision_32_point = 3,
    rdc_output_precision_64_point = 4,
    rdc_output_precision_128_point = 5,
    rdc_output_precision_256_point = 6,
    rdc_output_precision_512_point = 7,
    rdc_output_precision_1024_point = 8,
} rdc_output_precision_t;

/**
 * @brief Pwm output period in samples
 *
 */
typedef enum rdc_output_pwm_period {
    rdc_output_pwm_period_1_sample = 0,
    rdc_output_pwm_period_2_sample,
    rdc_output_pwm_period_3_sample,
    rdc_output_pwm_period_4_sample,
    rdc_output_pwm_period_5_sample,
    rdc_output_pwm_period_6_sample,
    rdc_output_pwm_period_7_sample,
    rdc_output_pwm_period_8_sample,
    rdc_output_pwm_period_9_sample,
    rdc_output_pwm_period_10_sample,
    rdc_output_pwm_period_11_sample,
    rdc_output_pwm_period_12_sample,
    rdc_output_pwm_period_13_sample,
    rdc_output_pwm_period_14_sample,
    rdc_output_pwm_period_15_sample,
    rdc_output_pwm_period_16_sample,
} rdc_output_pwm_period_t;



/**
 * @brief Rdc output mode
 *
 */
typedef enum rdc_output_mode {
    rdc_output_dac,
    rdc_output_pwm
} rdc_output_mode_t;

/**
 * @brief Synchronize output trig adc position
 *
 */
typedef enum rdc_sync_out_src {
    rdc_sync_out_exc_0_ph = RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_SET(0),
    rdc_sync_out_exc_90_ph = RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_SET(1),
    rdc_sync_out_exc_180_ph = RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_SET(2),
    rdc_sync_out_exc_270_ph = RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_SET(3),
    rdc_sync_out_max = RDC_SYNC_OUT_CTRL_MAX2TRIG_EN_MASK,
    rdc_sync_out_min = RDC_SYNC_OUT_CTRL_MIN2TRIG_EN_MASK,
} rdc_sync_out_src_t;

/**
 * @brief Select reference point of rectify signal
 *
 */
typedef enum rdc_rectify_signal {
    rdc_rectify_signal_exc_0_ph = 0,
    rdc_rectify_signal_exc_90_ph = 1,
    rdc_rectify_signal_exc_180_ph = 2,
    rdc_rectify_signal_exc_270_ph = 3,
    rdc_rectify_signal_external = 4,
    rdc_rectify_signal_external_invert = 5,
} rdc_rectify_signal_t;

/**
 * @brief Time stamp selection for accumulation
 *
 */
typedef enum rdc_acc_stamp_time {
    rdc_acc_stamp_end_of_acc = 0,   /**< End of accumulation */
    rdc_acc_stamp_start_of_acc = 1, /**< Start of accumulation  */
    rdc_acc_stamp_center_of_acc = 2,    /**< Center of accumulation */
} rdc_acc_stamp_time_t;

/**
 * @brief Rdc trigger out channel 0 or channel 1
 *
 */
typedef enum rdc_output_trig_chn {
    trigger_out_0 = 0,
    trigger_out_1 = 1
} rdc_output_trig_chn_t;


/**
 * @brief Rdc input channel
 *
 */
typedef enum rdc_input_acc_chn {
    rdc_acc_chn_i = 0,
    rdc_acc_chn_q = 1
} rdc_input_acc_chn_t;

typedef enum rdc_input_max_min_value_source {
    rdc_value_at_adc = 0,
    rdc_value_at_iir = 1
} rdc_input_max_min_value_source_t;

/**
 * @brief Rdc status flags
 *
 */
typedef enum rdc_interrupt_stat {
    acc_vld_i_stat = RDC_INT_EN_ACC_VLD_I_EN_MASK,
    acc_vld_q_stat = RDC_INT_EN_ACC_VLD_Q_EN_MASK,
    rising_delay_i_stat = RDC_INT_EN_RISING_DELAY_I_EN_MASK,
    falling_delay_i_stat = RDC_INT_EN_FALLING_DELAY_I_EN_MASK,
    rising_delay_q_stat = RDC_INT_EN_RISING_DELAY_Q_EN_MASK,
    falling_delay_q_stat = RDC_INT_EN_FALLING_DELAY_Q_EN_MASK,
    sample_rising_i_stat = RDC_INT_EN_SAMPLE_RISING_I_EN_MASK,
    sample_falling_i_stat = RDC_INT_EN_SAMPLE_FALLING_I_EN_MASK,
    sample_rising_q_stat = RDC_INT_EN_SAMPLE_RISING_Q_EN_MASK,
    sample_falling_q_stat = RDC_INT_EN_SAMPLE_FALLING_Q_EN_MASK,
    acc_vld_i_ovh_stat = RDC_INT_EN_ACC_VLD_I_OVH_EN_MASK,
    acc_vld_q_ovh_stat = RDC_INT_EN_ACC_VLD_Q_OVH_EN_MASK,
    acc_vld_i_ovl_stat = RDC_INT_EN_ACC_VLD_I_OVL_EN_MASK,
    acc_vld_q_ovl_stat = RDC_INT_EN_ACC_VLD_Q_OVL_EN_MASK,
    acc_amp_ovh_stat = RDC_INT_EN_ACC_AMP_OVH_EN_MASK,
    acc_amp_ovl_stat = RDC_INT_EN_ACC_AMP_OVL_EN_MASK,
} rdc_interrupt_stat_t;

/**
 * @brief Rdc output configuration
 *
 */
typedef struct rdc_output_cfg {
    rdc_output_mode_t mode; /**< pwm or dac */
    uint32_t excitation_period_cycle;   /**< The period of the excitation signal, in cycles */
    rdc_output_precision_t excitation_precision;    /**< Excitation signal precision */
    rdc_output_pwm_period_t pwm_period; /**< Pwm period in samples */
    bool output_swap;   /**< Swap output of PWM and DAC */
    int32_t amp_offset; /**< Offset for excitation, signed value*/
    uint16_t amp_man;   /**< Amplitude scaling for excitation,  amplitude = [table value] x man / 2^exp */
    uint16_t amp_exp;   /**< Amplitude scaling for excitation,  amplitude = [table value] x man / 2^exp */
    bool pwm_dither_enable; /**< Enable dither of pwm */
    bool pwm_exc_p_low_active;  /**< Polarity of exc_p signal */
    bool pwm_exc_n_low_active;  /**< Polarity of exc_n signal */
    bool trig_by_hw;    /**< Hardware triggered excitation signal generation. Software triggering is required after shutdown */
    uint32_t hw_trig_delay; /**< Trigger in delay timming in bus cycle from rising edge of trigger signal */
    uint8_t dac_chn_i_sel;  /**< Output channel selection for i_channel */
    uint8_t dac_chn_q_sel;  /**< Output channel selection for q_channel */
    uint8_t pwm_deadzone_p; /**< Exc_p dead zone  in clock cycle before swap */
    uint8_t pwm_deadzone_n; /**< Exc_n dead zone  in clock cycle before swap */
} rdc_output_cfg_t;


/**
 * @brief Rdc input configuration
 *
 */
typedef struct rdc_input_cfg {
    rdc_rectify_signal_t rectify_signal_sel;    /**< Select reference point of rectify signal */
#if defined(HPM_IP_FEATURE_RDC_IIR) && (HPM_IP_FEATURE_RDC_IIR)
    bool acc_fast;          /**< every adc value can be as one accumulate value,  */
    rdc_input_max_min_value_source_t max_min_value_position;    /**< max min value position */
#endif
    uint8_t acc_cycle_len;  /**< Accumulate time, support on the fly change, Only acc_fast is zero, this bit is available */
    rdc_acc_stamp_time_t acc_stamp; /**< Time stamp selection for accumulation */
    uint32_t acc_input_chn_i;   /**< Input channel selection for i_channel */
    uint32_t acc_input_port_i;  /**< Input port selection for i_channel */
    uint32_t acc_input_chn_q;   /**< Input channel selection for q_channel */
    uint32_t acc_input_port_q;  /**< Input port selection for q_channel */
} rdc_input_cfg_t;

/**
 * @brief Accumulated configuration information
 *
 */
typedef struct rdc_acc_cfg {
    struct {
        uint16_t continue_edge_num: 3;  /**< Filtering val: 1 - 8 */
        uint16_t edge_distance: 6;  /**< Minimum distance between two edges 0-63 */
    };
#if defined(HPM_IP_FEATURE_RDC_IIR) && (HPM_IP_FEATURE_RDC_IIR)
    bool enable_i_thrs_data_for_acc;  /**< enable thrs data for accumulate */
    bool enable_q_thrs_data_for_acc;  /**< enable thrs data for accumulate */
#endif
    uint8_t right_shift_without_sign;   /**< Right shift without sign bit */
    bool error_data_remove; /**< Toxic accumulation data be removed */
    uint32_t exc_carrier_period;    /**< The num in clock cycle for period of excitation 0-NULL others-cycles */
    uint32_t sync_delay_i;  /**< Delay in clock cycle for synchronous signal, the value should less than half of exc_period.exc_period. */
    uint32_t sync_delay_q;  /**< Delay in clock cycle for synchronous signal, the value should less than half of exc_period.exc_period. */
    uint32_t amp_max;   /**< The maximum of acc amplitude */
    uint32_t amp_min;   /**< The minimum of acc amplitude */
} rdc_acc_cfg_t;

#if defined(HPM_IP_FEATURE_RDC_IIR) && (HPM_IP_FEATURE_RDC_IIR)
/**
 * @brief IIR Filter Configuration
 *
 */
typedef struct rdc_iir_cfg {
    float b;    /**< IIR parameter for b branch */
    float a1;   /**< IIR parameter a1 for a1 branch*/
    float a2;   /**< IIR parameter a1 for a2 branch*/
    bool enable_lowpass;    /**< IIR in lowpass mode */
} rdc_iir_cfg_t;
#endif

/** @} */

/**
 * @name RDC Control
 * @{
 */

/**
 * @brief Rdc output configuration, can be configured pwm output or dac output
 *
 * @param ptr @ref RDC_Type base
 * @param cfg @ref rdc_output_cfg_t
 */
void rdc_output_config(RDC_Type *ptr, rdc_output_cfg_t *cfg);

/**
 * @brief Rdc input configuration, configuration of adc signal source and calculation parameters
 *
 * @param ptr @ref RDC_Type base
 * @param cfg @ref rdc_input_cfg_t
 */
void rdc_input_config(RDC_Type *ptr, rdc_input_cfg_t *cfg);

/**
 * @brief Configuration accumulate time, support on the fly change
 *
 * @param ptr @ref RDC_Type base
 * @param len accumulate time 0-255
 */
static inline void rdc_set_acc_len(RDC_Type *ptr, uint8_t len)
{
    ptr->RDC_CTL = (ptr->RDC_CTL & (~RDC_RDC_CTL_ACC_LEN_MASK))
                    | RDC_RDC_CTL_ACC_LEN_SET(len);
}

/**
 * @brief Enable accumulate calculation function
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_acc_enable(RDC_Type *ptr)
{
    ptr->RDC_CTL |= RDC_RDC_CTL_ACC_EN_MASK;
}

/**
 * @brief Disable accumulate calculation function
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_acc_disable(RDC_Type *ptr)
{
    ptr->RDC_CTL &= ~RDC_RDC_CTL_ACC_EN_MASK;
}

#if defined(HPM_IP_FEATURE_RDC_IIR) && (HPM_IP_FEATURE_RDC_IIR)
/**
 * @brief Enable IIR for adc input
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_irr_enable(RDC_Type *ptr)
{
    ptr->RDC_CTL |= RDC_RDC_CTL_IIR_EN_MASK;
}

/**
 * @brief Disable IIR for adc input
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_irr_disable(RDC_Type *ptr)
{
    ptr->RDC_CTL &= ~RDC_RDC_CTL_IIR_EN_MASK;
}

/**
 * @brief enable i thrs data for accumulate
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_enable_i_channel_thrs_data_for_acc(RDC_Type *ptr)
{
    ptr->THRS_I |= RDC_THRS_I_THRS4ACC_MASK;
}

/**
 * @brief disable i thrs data for accumulate
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_disable_i_channel_thrs_data_for_acc(RDC_Type *ptr)
{
    ptr->THRS_I &= ~RDC_THRS_I_THRS4ACC_MASK;
}

/**
 * @brief enable q thrs data for accumulate
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_enable_q_channel_thrs_data_for_acc(RDC_Type *ptr)
{
    ptr->THRS_Q |= RDC_THRS_Q_THRS4ACC_MASK;
}

/**
 * @brief disable q thrs data for accumulate
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_disable_q_channel_thrs_data_for_acc(RDC_Type *ptr)
{
    ptr->THRS_Q &= ~RDC_THRS_Q_THRS4ACC_MASK;
}

#endif

/**
 * @brief Get the accumulate value
 *
 * @param ptr @ref RDC_Type base
 * @param chn @ref rdc_input_acc_chn_t
 * @return uint32_t accumulate value
 */
uint32_t rdc_get_acc_avl(RDC_Type *ptr, rdc_input_acc_chn_t chn);

/**
 * @brief Output trigger configuration
 * Lead time for trigger out0 or out1 from center of low level , this is a signed value
 * @param ptr @ref RDC_Type base
 * @param chn @ref rdc_output_trig_chn_t
 * @param offset lead_time
 */
void rdc_output_trig_offset_config(RDC_Type *ptr, rdc_output_trig_chn_t chn, int32_t offset);

/**
 * @brief Enable output trigger configuration
 *
 * @param ptr @ref RDC_Type base
 * @param chn @ref rdc_output_trig_chn_t
 */
void rdc_output_trig_enable(RDC_Type *ptr, rdc_output_trig_chn_t chn);

/**
 * @brief Disable rdc output trigger configuration
 *
 * @param ptr @ref RDC_Type base
 * @param chn @ref rdc_output_trig_chn_t
 */
void rdc_output_trig_disable(RDC_Type *ptr, rdc_output_trig_chn_t chn);

/**
 * @brief Select output synchornize signal
 *
 * @param ptr @ref RDC_Type base
 * @param sel @ref rdc_sync_out_src_t
 */
static inline void rdc_sync_output_trig_adc_cfg(RDC_Type *ptr, rdc_sync_out_src_t sel)
{
    ptr->SYNC_OUT_CTRL = sel;
}

/**
 * @brief Enable rdc excite signal
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_exc_enable(RDC_Type *ptr)
{
    ptr->RDC_CTL |= RDC_RDC_CTL_EXC_EN_MASK;
}

/**
 * @brief Disable rdc excite signal
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_exc_disable(RDC_Type *ptr)
{
    ptr->RDC_CTL &= ~RDC_RDC_CTL_EXC_EN_MASK;
}

/**
 * @brief Software triggered excitation signal output
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_output_trig_sw(RDC_Type *ptr)
{
    ptr->RDC_CTL |= RDC_RDC_CTL_EXC_START_MASK;
}

/**
 * @brief Get I-phase maximum
 *
 * @param ptr @ref RDC_Type base
 * @retval - other max value
 *         - -1 illegal data
 */
int32_t rdc_get_i_maxval(RDC_Type *ptr);

/**
 * @brief Clear Maximum
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_clear_i_maxval(RDC_Type *ptr)
{
    ptr->MAX_I = 0;
}

/**
 * @brief Get I-phase minimum
 *
 * @param ptr @ref RDC_Type base
 * @retval - other max value
 *         - -1 illegal data
 */
int32_t rdc_get_i_minval(RDC_Type *ptr);

/**
 * @brief Clear I-phase minimum
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_clear_i_minval(RDC_Type *ptr)
{
    ptr->MIN_I = 0;
}

/**
 * @brief Set Acc sync delay
 *
 * @param ptr @ref RDC_Type base
 * @param chn @ref rdc_input_acc_chn_t
 * @param delay delay tick
 */
void rdc_set_acc_sync_delay(RDC_Type *ptr, rdc_input_acc_chn_t chn, uint32_t delay);

/**
 * @brief Delay bettween the delyed trigger and
 *  the first pwm pulse in clock cycle
 *
 * @param ptr @ref RDC_Type base
 * @retval delay tick
 */
static inline uint32_t rdc_get_sync_output_delay(RDC_Type *ptr)
{
    return RDC_SYNC_OUT_CTRL_PWM_OUT_DLY_GET(ptr->SYNC_OUT_CTRL);
}

/**
 * @brief Get Q-phase maximum
 *
 * @param ptr @ref RDC_Type base
 * @retval - other max value
 *         - -1 illegal data
 */
int32_t rdc_get_q_maxval(RDC_Type *ptr);

/**
 * @brief Clear Q-phase maxval
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_clear_q_maxval(RDC_Type *ptr)
{
    ptr->MAX_Q = 0;
}

/**
 * @brief Get Q-phase Minval
 *
 * @param ptr @ref RDC_Type base
 * @retval - other max value
 *         - -1 illegal data
 */
int32_t rdc_get_q_minval(RDC_Type *ptr);

/**
 * @brief Clear Q-phase Minval
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_clear_q_minval(RDC_Type *ptr)
{
    ptr->MIN_Q = 0;
}

/**
 * @brief The offset setting for edge detection of the i_channel or q_channel
 *
 * @param ptr @ref RDC_Type base
 * @param chn @ref rdc_input_acc_chn_t
 * @param offset offset value
 */
void rdc_set_edge_detection_offset(RDC_Type *ptr, rdc_input_acc_chn_t chn, int32_t offset);

/**
 * @brief RDC set accumulate configuration
 *
 * @param ptr @ref RDC_Type base
 * @param cfg @ref rdc_acc_cfg_t
 */
void rdc_set_acc_config(RDC_Type *ptr, rdc_acc_cfg_t *cfg);

/**
 * @brief Get delay in clock cycle between excitation synchrnous signal and rising edge of i_channel data
 *
 * @param ptr @ref RDC_Type base
 * @retval clock cycle
 */
static inline uint32_t rdc_get_rise_delay_i(RDC_Type *ptr)
{
    return RDC_RISE_DELAY_I_RISE_DELAY_GET(ptr->RISE_DELAY_I);
}

/**
 * @brief Get delay in clock cycle between excitation synchrnous signal and fall edge of i_channel data
 *
 * @param ptr @ref RDC_Type base
 * @retval clock cycle
 */
static inline uint32_t rdc_get_fall_delay_i(RDC_Type *ptr)
{
    return RDC_FALL_DELAY_I_FALL_DELAY_GET(ptr->FALL_DELAY_I);
}

/**
 * @brief Get sample value on rising edge of rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval clock cycle
 */
static inline uint32_t rdc_get_sample_rise_i(RDC_Type *ptr)
{
    return RDC_SAMPLE_RISE_I_VALUE_GET(ptr->SAMPLE_RISE_I);
}

/**
 * @brief Get sample value on falling edge of rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval clock cycle
 */
static inline uint32_t rdc_get_sample_fall_i(RDC_Type *ptr)
{
    return RDC_SAMPLE_FALL_I_VALUE_GET(ptr->SAMPLE_FALL_I);
}

/**
 * @brief Get sample number during the positive of rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval counter
 */
static inline uint32_t rdc_get_acc_cnt_positive_i(RDC_Type *ptr)
{
    return RDC_ACC_CNT_I_CNT_POS_GET(ptr->ACC_CNT_I);
}

/**
 * @brief Get sample number during the negtive of rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval counter
 */
static inline uint32_t rdc_get_acc_cnt_negative_i(RDC_Type *ptr)
{
    return RDC_ACC_CNT_I_CNT_POS_GET(ptr->ACC_CNT_I);
}

/**
 * @brief Get Negative sample counter during positive rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval counter
 */
static inline uint32_t rdc_get_sign_cnt_poitive_i(RDC_Type *ptr)
{
    return RDC_SIGN_CNT_I_CNT_POS_GET(ptr->SIGN_CNT_I);
}

/**
 * @brief Get Positive sample counter during negative rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval counter
 */
static inline uint32_t rdc_get_sign_cnt_negative_i(RDC_Type *ptr)
{
    return RDC_SIGN_CNT_I_CNT_NEG_GET(ptr->SIGN_CNT_I);
}

/**
 * @brief Get delay in clock cycle between excitation synchrnous signal and rising edge of q_channel data
 *
 * @param ptr @ref RDC_Type base
 * @retval cycles
 */
static inline uint32_t rdc_get_rise_delay_q(RDC_Type *ptr)
{
    return RDC_RISE_DELAY_Q_RISE_DELAY_GET(ptr->RISE_DELAY_Q);
}

/**
 * @brief Get delay in clock cycle between excitation synchrnous signal and falling edge of q_channel data
 *
 * @param ptr @ref RDC_Type base
 * @retval cycles
 */
static inline uint32_t rdc_get_fall_delay_q(RDC_Type *ptr)
{
    return RDC_FALL_DELAY_Q_FALL_DELAY_GET(ptr->FALL_DELAY_Q);
}

/**
 * @brief Get q channel sample value on rising edge of rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval cycles
 */
static inline uint32_t rdc_get_sample_rise_q(RDC_Type *ptr)
{
    return RDC_SAMPLE_RISE_Q_VALUE_GET(ptr->SAMPLE_RISE_Q);
}

/**
 * @brief Get q channel sample value on falling edge of rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval cycles
 */
static inline uint32_t rdc_get_sample_fall_q(RDC_Type *ptr)
{
    return RDC_SAMPLE_FALL_Q_VALUE_GET(ptr->SAMPLE_FALL_Q);
}

/**
 * @brief Get q channel sample number during the positive of rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval number
 */
static inline uint32_t rdc_get_acc_cnt_positive_q(RDC_Type *ptr)
{
    return RDC_ACC_CNT_Q_CNT_POS_GET(ptr->ACC_CNT_Q);
}

/**
 * @brief Get q channel sample number during the negtive of rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval number
 */
static inline uint32_t rdc_get_acc_cnt_negative_q(RDC_Type *ptr)
{
    return RDC_ACC_CNT_Q_CNT_POS_GET(ptr->ACC_CNT_Q);
}

/**
 * @brief Get q channel negative sample counter during positive rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval counter
 */
static inline uint32_t rdc_get_sign_cnt_poitive_q(RDC_Type *ptr)
{
    return RDC_SIGN_CNT_Q_CNT_POS_GET(ptr->SIGN_CNT_Q);
}

/**
 * @brief Get q channel sample number during the negtive of rectify signal
 *
 * @param ptr @ref RDC_Type base
 * @retval counter
 */
static inline uint32_t rdc_get_sign_cnt_negative_q(RDC_Type *ptr)
{
    return RDC_SIGN_CNT_Q_CNT_NEG_GET(ptr->SIGN_CNT_Q);
}

/**
 * @brief Enables configured interrupts
 *
 * @param ptr @ref RDC_Type base
 * @param status @ref rdc_interrupt_stat_t
 */
static inline void rdc_interrupt_config(RDC_Type *ptr, uint32_t status)
{
    ptr->INT_EN |= status;
}

/**
 * @brief Clear interrupts configured
 *
 * @param ptr @ref RDC_Type base
 * @param status @ref rdc_interrupt_stat_t
 */
static inline void rdc_interrupt_reset_config(RDC_Type *ptr, uint32_t status)
{
    ptr->INT_EN &= ~status;
}

/**
 * @brief Enable rdc interrupt
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_interrupt_enable(RDC_Type *ptr)
{
    ptr->INT_EN |= RDC_INT_EN_INT_EN_MASK;
}

/**
 * @brief Disable rdc interrupt
 *
 * @param ptr @ref RDC_Type base
 */
static inline void rdc_interrupt_disable(RDC_Type *ptr)
{
    ptr->INT_EN &= ~RDC_INT_EN_INT_EN_MASK;
}

/**
 * @brief Clear interrupt flag bits
 *
 * @param ptr @ref RDC_Type base
 * @param mask @ref rdc_interrupt_stat_t
 */
static inline void rdc_interrupt_clear_flag_bits(RDC_Type *ptr, uint32_t mask)
{
    ptr->ADC_INT_STATE &= mask;
}

/**
 * @brief Get the interrupt status object
 *
 * @param ptr @ref RDC_Type base
 * @return @ref rdc_interrupt_stat_t
 */
static inline uint32_t get_interrupt_status(RDC_Type *ptr)
{
    return ptr->ADC_INT_STATE;
}

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* HPM_ADC12_DRV_H */
