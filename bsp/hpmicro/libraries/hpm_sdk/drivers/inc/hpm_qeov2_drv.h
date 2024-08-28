/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_QEOV2_DRV_H
#define HPM_QEOV2_DRV_H

#include "hpm_common.h"
#include "hpm_qeov2_regs.h"
/**
 * @brief QEOV2 driver APIs
 * @defgroup qeov2_interface QEOV2 driver APIs
 * @ingroup qeov2_interfaces
 * @{
 */

typedef enum {
    qeo_wave_cosine = 0,
    qeo_wave_saddle = 1,
    qeo_wave_abs_cosine = 2,
    qeo_wave_saw = 3,
} qeo_wave_type_t;

typedef enum {
    qeo_saddle_standard = 0,
    qeo_saddle_triple
} qeo_saddle_type_t;

typedef enum {
    qeo_wave_above_max_limit_max_val = 0,
    qeo_wave_above_max_limit_zero = 1,
    qeo_wave_above_max_limit_max_level0_val = 2,

    qeo_wave_high_area_limit_max_val = 0,
    qeo_wave_high_area_limit_max_level0_val = 1,

    qeo_wave_low_area_limit_zero = 0,
    qeo_wave_low_area_limit_min_level1_val = 1,

    qeo_wave_below_min_limit_zero = 0,
    qeo_wave_below_min_limit_max_val = 1,
    qeo_wave_below_min_limit_min_level1_val = 2,
} qeo_wave_limit_t;

typedef struct {
    qeo_wave_limit_t above_max_limit;
    qeo_wave_limit_t high_area0_limit;
    qeo_wave_limit_t high_area1_limit;
    qeo_wave_limit_t low_area0_limit;
    qeo_wave_limit_t low_area1_limit;
    qeo_wave_limit_t below_min_limit;
} qeo_wave_limit_config_t;

typedef struct {
    qeo_wave_limit_config_t wave0;
    qeo_wave_limit_config_t wave1;
    qeo_wave_limit_config_t wave2;
    bool dq_valid_trig_enable; /*!< DQ valid trigger calculate */
    bool pos_valid_trig_enable; /*!< Position valid trigger calculate */
    bool vd_vq_inject_enable;
    bool vd_vq_from_sw; /*!< true: DQ from register; false: DQ from CLC module */
    qeo_wave_type_t wave_type;
    qeo_saddle_type_t saddle_type;
} qeo_wave_mode_t;

typedef enum {
    qeo_abz_output_abz = 0, /*!< A and B are orthogonal signals, Z is zero pulse */
    qeo_abz_output_pulse_revise = 1, /*!< A is speed pulse, B is directional pulse, Z not used */
    qeo_abz_output_up_down = 2, /*!< A is forward pulse, B is reverse pusle, Z not used */
    qeo_abz_output_three_phase = 3, /*!< A/B/Z are 3-phase orthogonal pulse */
} qeo_abz_type_t;

typedef enum {
    qeo_z_as_zero_signal_mode0 = 0,
    qeo_z_as_zero_signal_mode1 = 1,
    qeo_z_as_no_output_signal = 2,
    qeo_z_as_third_phase_signal = 3,
} qeo_z_pulse_type_t;

typedef struct {
    bool z_inv_pol;
    bool b_inv_pol;
    bool a_inv_pol;
    bool enable_wdog;
    bool sync_step_position;
    bool reverse_align_clk_falling_edge;
    qeo_abz_type_t output_type; /*!< @ref qeo_abz_type_t */
} qeo_abz_mode_t;

/*!< zero pusle legth mode */
typedef struct {
    uint8_t type;
    uint32_t start_line;
    uint32_t end_line;
    uint8_t  start_step;
    uint8_t  end_step;
    uint32_t width;
} qeo_z_output_mode_t;

typedef enum {
    qeo_pwm_output_force_0 = 2,
    qeo_pwm_output_force_1 = 3,
    qeo_pwm_output_not_force = 0,
} qeo_pwm_force_output_t;

typedef enum {
    qeo_pwm_safety_output_0 = 0,
    qeo_pwm_safety_output_1 = 1,
    qeo_pwm_safety_output_highz = 2,
} qeo_pwm_safety_output_t;

typedef struct {
    qeo_pwm_force_output_t pwm0_output; /*!< @ref qeo_pwm_force_output_t */
    qeo_pwm_force_output_t pwm1_output;
    qeo_pwm_force_output_t pwm2_output;
    qeo_pwm_force_output_t pwm3_output;
    qeo_pwm_force_output_t pwm4_output;
    qeo_pwm_force_output_t pwm5_output;
    qeo_pwm_force_output_t pwm6_output;
    qeo_pwm_force_output_t pwm7_output;
} qeo_pwm_phase_output_table_t;

typedef struct {
    qeo_pwm_safety_output_t pwm0_output; /*!< @ref qeo_pwm_safety_output_t */
    qeo_pwm_safety_output_t pwm1_output;
    qeo_pwm_safety_output_t pwm2_output;
    qeo_pwm_safety_output_t pwm3_output;
    qeo_pwm_safety_output_t pwm4_output;
    qeo_pwm_safety_output_t pwm5_output;
    qeo_pwm_safety_output_t pwm6_output;
    qeo_pwm_safety_output_t pwm7_output;
} qeo_pwm_safety_output_table_t;

typedef struct {
    uint8_t phase_num;
    bool shield_hardware_trig_safety;
    bool revise_pairs_output;
} qeo_pwm_mode_t;

#ifdef __cplusplus
extern "C" {
#endif

/* WAVE API */
/**
 * @brief QEO set resolution lines for wave mode
 * @param [in] base QEO base address
 * @param [in] lines resolution lines
 */
static inline void qeo_wave_set_resolution_lines(QEOV2_Type *base, uint32_t lines)
{
    base->WAVE.RESOLUTION = QEOV2_WAVE_RESOLUTION_LINES_SET(lines);
}

/**
 * @brief QEO set output type for wave mode
 * @param [in] base QEO base address
 * @param [in] type qeo_wave_type_t
 */
static inline void qeo_wave_set_output_type(QEOV2_Type *base, qeo_wave_type_t type)
{
    base->WAVE.MODE = (base->WAVE.MODE & ~QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_MASK) | QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_SET(type);
}

/**
 * @brief QEO set saddle type for wave mode
 * @param [in] base QEO base address
 * @param [in] standard true for standard saddle, false for triangular wave stacking
 */
static inline void qeo_wave_set_saddle_type(QEOV2_Type *base, bool standard)
{
    if (standard) {
        base->WAVE.MODE &= ~QEOV2_WAVE_MODE_SADDLE_TYPE_MASK;
    } else {
        base->WAVE.MODE |= QEOV2_WAVE_MODE_SADDLE_TYPE_MASK;
    }
}

/**
 * @brief QEO set phase shift for wave mode
 * @param [in] base QEO base address
 * @param [in] index wave index(0/1/2)
 * @param [in] angle left shift angle
 */
static inline void qeo_wave_set_phase_shift(QEOV2_Type *base, uint8_t index, double angle)
{
    assert((angle >= 0) && (angle <= 360));
    uint32_t val = (uint32_t)(angle * 0x100000000UL / 360);
    base->WAVE.PHASE_SHIFT[index] = QEOV2_WAVE_PHASE_SHIFT_VAL_SET(val);
}

/**
 * @brief QEO enable vd vq inject and select vq vq source for wave mode
 * @param [in] base QEO base address
 * @param [in] from_sw false for vd vq data from clc module, true for vd vq from software inject register
 */
static inline void qeo_wave_enable_vd_vq_inject(QEOV2_Type *base, bool from_sw)
{
    if (from_sw) {
        base->WAVE.MODE |= QEOV2_WAVE_MODE_VD_VQ_SEL_MASK;
    } else {
        base->WAVE.MODE &= ~QEOV2_WAVE_MODE_VD_VQ_SEL_MASK;
    }
    base->WAVE.MODE |= QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_MASK;
}

/**
 * @brief QEO disable vd vq inject for wave mode
 * @param [in] base QEO base address
 */
static inline void qeo_wave_disable_vd_vq_inject(QEOV2_Type *base)
{
    base->WAVE.MODE &= ~QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_MASK;
}

/**
 * @brief QEO config vd vq value when vd vq from register
 * @param [in] base QEO base address
 * @param [in] vd_val vd value
 * @param [in] vq_val vq value
 */
static inline void qeo_wave_config_vd_vq_value(QEOV2_Type *base, int32_t vd_val, int32_t vq_val)
{
    base->WAVE.VD_INJECT = QEOV2_WAVE_VD_INJECT_VD_VAL_SET(vd_val);
    base->WAVE.VQ_INJECT = QEOV2_WAVE_VQ_INJECT_VQ_VAL_SET(vq_val);
}

/**
 * @brief QEO load vd vq inject value when vd vq from register
 * @param [in] base QEO base address
 */
static inline void qeo_wave_load_vd_vq(QEOV2_Type *base)
{
    base->WAVE.VD_VQ_LOAD = QEOV2_WAVE_VD_VQ_LOAD_LOAD_MASK;
}

/**
 * @brief QEO enable amplitude for wave mode
 * @param [in] base QEO base address
 * @param [in] index wave index(0/1/2)
 * @param [in] amp amplitude value
 */
static inline void qeo_wave_enable_amplitude(QEOV2_Type *base, uint8_t index, double amp)
{
    assert(amp > 0);
    uint32_t val = (uint32_t)(amp * (1U << 12U));
    base->WAVE.AMPLITUDE[index] = QEOV2_WAVE_AMPLITUDE_EN_SCAL_MASK | QEOV2_WAVE_AMPLITUDE_AMP_VAL_SET(val);
}

/**
 * @brief QEO disable amplitude for wave mode
 * @param [in] base QEO base address
 * @param [in] index wave index(0/1/2)
 */
static inline void qeo_wave_disable_amplitude(QEOV2_Type *base, uint8_t index)
{
    base->WAVE.AMPLITUDE[index] &= ~QEOV2_WAVE_AMPLITUDE_EN_SCAL_MASK;
}

/**
 * @brief QEO set mid point shift for wave mode
 * @param [in] base QEO base address
 * @param [in] index wave index(0/1/2)
 * @param [in] shift mid point shift value
 */
static inline void qeo_wave_set_mid_point_shift(QEOV2_Type *base, uint8_t index, double shift)
{
    int32_t val = (int32_t)(shift * (1U << 27U));
    base->WAVE.MID_POINT[index] = QEOV2_WAVE_MID_POINT_VAL_SET(val);
}

/**
 * @brief QEO set max limmit for wave mode
 * @param [in] base QEO base address
 * @param [in] index wave index(0/1/2)
 * @param [in] limit0 limit0 value
 * @param [in] limit1 limit1 value
 */
static inline void qeo_wave_set_max_limit(QEOV2_Type *base, uint8_t index, uint32_t limit0, uint32_t limit1)
{
    base->WAVE.LIMIT0[index].MAX_LEVEL0 = QEOV2_WAVE_LIMIT0_MAX_LEVEL0_LIMIT_LEVEL0_SET(limit0);
    base->WAVE.LIMIT1[index].MAX_LEVEL1 = QEOV2_WAVE_LIMIT1_MAX_LEVEL1_LIMIT_LEVEL1_SET(limit1);
}

/**
 * @brief QEO set min limmit for wave mode
 * @param [in] base QEO base address
 * @param [in] index wave index(0/1/2)
 * @param [in] limit0 limit0 value
 * @param [in] limit1 limit1 value
 */
static inline void qeo_wave_set_min_limit(QEOV2_Type *base, uint8_t index, uint32_t limit0, uint32_t limit1)
{
    base->WAVE.LIMIT0[index].MIN_LEVEL0 = QEOV2_WAVE_LIMIT0_MIN_LEVEL0_LIMIT_LEVEL0_SET(limit0);
    base->WAVE.LIMIT1[index].MIN_LEVEL1 = QEOV2_WAVE_LIMIT1_MIN_LEVEL1_LIMIT_LEVEL1_SET(limit1);
}

/**
 * @brief QEO set deadzone shift for wave mode
 * @param [in] base QEO base address
 * @param [in] index wave index(0/1/2)
 * @param [in] shift deadzone shift value
 */
static inline void qeo_wave_set_deadzone_shift(QEOV2_Type *base, uint8_t index, int32_t shift)
{
    base->WAVE.DEADZONE_SHIFT[index] = QEOV2_WAVE_DEADZONE_SHIFT_VAL_SET(shift);
}

/**
 * @brief QEO wave set pwm cycle
 *
 * @note when cycle is 0, output value is 0 - 0xFFFFFFFF, others, output value is 0 - cycle
 *
 * @param [in] base QEO base address
 * @param [in] cycle pwm period cycle
 */
static inline void qeo_wave_set_pwm_cycle(QEOV2_Type *base, uint32_t cycle)
{
    base->WAVE.PWM_CYCLE = QEOV2_WAVE_PWM_CYCLE_VAL_SET(cycle);
}

/**
 * @brief QEO get wave output value
 * @param [in] base QEO base address
 * @param [in] index wave index(0/1/2)
 * @retval wave output value
 */
static inline uint32_t qeo_get_wave_output_val(QEOV2_Type *base, uint8_t index)
{
    if (index == 0) {
        return QEOV2_DEBUG0_VALUE_DAC0_GET(base->DEBUG0);
    } else if (index == 1) {
        return QEOV2_DEBUG4_VALUE_DAC1_GET(base->DEBUG4);
    } else if (index  == 2) {
        return QEOV2_DEBUG5_VALUE_DAC2_GET(base->DEBUG5);
    }
    return 0;
}

/**
 * @brief QEO wave get defalut mode config
 * @param [in] base QEO base address
 * @param [in] config qeo_wave_mode_t
 */
void qeo_wave_get_default_mode_config(QEOV2_Type *base, qeo_wave_mode_t *config);

/**
 * @brief QEO wave config mode
 * @param [in] base QEO base address
 * @param [in] config qeo_wave_mode_t
 */
void qeo_wave_config_mode(QEOV2_Type *base, qeo_wave_mode_t *config);

/* ABZ API */
/**
 * @brief QEO set resolution lines for ABZ mode
 * @param [in] base QEO base address
 * @param [in] lines resolution lines
 */
static inline void qeo_abz_set_resolution_lines(QEOV2_Type *base, uint32_t lines)
{
    base->ABZ.RESOLUTION = QEOV2_ABZ_RESOLUTION_LINES_SET(lines);
}

/**
 * @brief QEO set phase shift for three phase output mode
 * @param [in] base QEO base address
 * @param [in] index ABZ index(0/1/2)
 * @param [in] angle left shift angle
 */
static inline void qeo_abz_set_phase_shift(QEOV2_Type *base, uint8_t index, double angle)
{
    assert((angle >= 0) && (angle <= 360));
    uint32_t val = (uint32_t)(angle * 0x100000000U / 360);
    base->ABZ.PHASE_SHIFT[index] = QEOV2_ABZ_PHASE_SHIFT_VAL_SET(val);
}

/**
 * @brief QEO set offset for output signal in ABZ mode
 * @param [in] base QEO base address
 * @param [in] physical_angle physical angle
 */
static inline void qeo_abz_set_offset(QEOV2_Type *base, double physical_angle)
{
    assert((physical_angle >= 0) && (physical_angle <= 360));
    uint32_t val = (uint32_t)(physical_angle * 0x100000000U / 360);
    base->ABZ.OVERALL_OFFSET = QEOV2_ABZ_OVERALL_OFFSET_VAL_SET(val);
}

/**
 * @brief QEO set max frequency for ABZ mode
 * @param [in] base QEO base address
 * @param [in] src_freq QEO(MOTO system) frequency
 * @param [in] freq abz signal frequency (A pulse frequency)
 * @retval status_success or status_invalid_argument
 */
hpm_stat_t qeo_abz_set_max_frequency(QEOV2_Type *base, uint32_t src_freq, uint32_t freq);

/**
 * @brief QEO set wdog frequency for ABZ mode
 * @param [in] base QEO base address
 * @param [in] src_freq QEO(MOTO system) frequency
 * @param [in] freq wdog frequency
 * @retval status_success or status_invalid_argument
 */
hpm_stat_t qeo_abz_set_wdog_frequency(QEOV2_Type *base, uint32_t src_freq, uint32_t freq);

/**
 * @brief QEO disable wdog for ABZ mode
 * @param [in] base QEO base address
 */
static inline void qeo_abz_disable_wdog(QEOV2_Type *base)
{
    base->ABZ.MODE &= ~QEOV2_ABZ_MODE_EN_WDOG_MASK;
}

/**
 * @brief QEO config reverse edge for ABZ mode
 * @param [in] base QEO base address
 * @param [in] speed_pulse_negedge true for reverse edge point speed pulse's negedge
 * false for reverse edge point between speed pulse's posedge and negedge, min period dedicated by the num line_width
 *
 * @note take effect when ABZ work on qeo_abz_output_pulse_revise mode
 */
static inline void qeo_abz_config_reverse_edge(QEOV2_Type *base, bool speed_pulse_negedge)
{
    if (speed_pulse_negedge) {
        base->ABZ.MODE |= QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_MASK;
    } else {
        base->ABZ.MODE &= ~QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_MASK;
    }
}

/**
 * @brief QEO ABZ get default mode config
 * @param [in] base QEO base address
 * @param [in] config qeo_abz_mode_t
 */
void qeo_abz_get_default_mode_config(QEOV2_Type *base, qeo_abz_mode_t *config);

/**
 * @brief QEO ABZ config mode
 * @param [in] base QEO base address
 * @param [in] config qeo_abz_mode_t
 */
void qeo_abz_config_mode(QEOV2_Type *base, qeo_abz_mode_t *config);

/**
 * @brief QEO ABZ mode enable output
 * @param [in] base QEO base address
 */
static inline void qeo_abz_enable_output(QEOV2_Type *base)
{
    base->ABZ.MODE |= QEOV2_ABZ_MODE_ABZ_OUTPUT_ENABLE_MASK;
}

/**
 * @brief QEO ABZ mode disable output
 * @param [in] base QEO base address
 */
static inline void qeo_abz_disable_output(QEOV2_Type *base)
{
    base->ABZ.MODE &= ~QEOV2_ABZ_MODE_ABZ_OUTPUT_ENABLE_MASK;
}

/**
 * @brief QEO ABZ mode enable and configure position sync mode
 * @param [in] base QEO base address
 * @param [in] sync_identical_pos true: sync identical posistion; false: sync step of position
 */
static inline void qeo_abz_enable_position_sync(QEOV2_Type *base, bool sync_identical_pos)
{
    if (sync_identical_pos) {
        base->ABZ.MODE |= QEOV2_ABZ_MODE_POSITION_SYNC_MODE_MASK;
    } else {
        base->ABZ.MODE &= ~QEOV2_ABZ_MODE_POSITION_SYNC_MODE_MASK;
    }

    base->ABZ.POSTION_SYNC = QEOV2_ABZ_POSTION_SYNC_POSTION_MASK;
}

/**
 * @brief QEO ABZ mode get default zero pulse output mode
 * @param [in] base QEO base address
 * @param [out] mode qeo_z_output_mode_t
 */
void qeo_abz_get_default_z_output_mode(QEOV2_Type *base, qeo_z_output_mode_t *mode);

/**
 * @brief QEO ABZ mode configure zero pulse output mode
 * @param [in] base QEO base address
 * @param [in] mode qeo_z_output_mode_t
 */
void qeo_abz_config_z_output_mode(QEOV2_Type *base, qeo_z_output_mode_t *mode);

/* PWM API */
/**
 * @brief QEO set resolution lines for PWM mode
 * @param [in] base QEO base address
 * @param [in] lines resolution lines
 */
static inline void qeo_pwm_set_resolution_lines(QEOV2_Type *base, uint32_t lines)
{
    base->PWM.RESOLUTION = QEOV2_PWM_RESOLUTION_LINES_SET(lines);
}

/**
 * @brief QEO set phase shift for PWM mode
 * @param [in] base QEO base address
 * @param [in] index PWM index(0/1/2/3)
 * @param [in] angle left shift angle
 */
static inline void qeo_pwm_set_phase_shift(QEOV2_Type *base, uint8_t index, double angle)
{
    assert((angle >= 0) && (angle <= 360));
    uint32_t val = (uint32_t)(angle * 0x1000010000U / 360);
    base->PWM.PHASE_SHIFT[index] = QEOV2_PWM_PHASE_SHIFT_VAL_SET(val);
}

/**
 * @brief QEO PWM mode enable output
 * @param [in] base QEO base address
 */
static inline void qeo_pwm_enable_output(QEOV2_Type *base)
{
    base->PWM.MODE |= QEOV2_PWM_MODE_ENABLE_PWM_MASK;
}

/**
 * @brief QEO PWM mode disable output
 * @param [in] base QEO base address
 */
static inline void qeo_pwm_disable_output(QEOV2_Type *base)
{
    base->PWM.MODE &= ~QEOV2_PWM_MODE_ENABLE_PWM_MASK;
}

/**
 * @brief QEO PWM check if it is triggered by hardware to enter safety mode
 *
 * @note This bit is only valid if the hardware trigger source has not been cleared
 *
 * @param [in] base QEO base address
 * @retval true or false
 */
static inline bool qeo_pwm_check_hardware_trig_safety(QEOV2_Type *base)
{
    return ((base->STATUS & QEOV2_STATUS_PWM_SAFETY_MASK) != 0) ? true : false;
}

/**
 * @brief QEO PWM select phase table
 * @param [in] base QEO base address
 * @param [in] positive true for using positive phase table, false for using negative phase table
 */
static inline void qeo_pwm_select_phase_table(QEOV2_Type *base, bool positive)
{
    if (positive) {
        base->PWM.MODE &= ~QEOV2_PWM_MODE_REVISE_UP_DN_MASK;
    } else {
        base->PWM.MODE |= QEOV2_PWM_MODE_REVISE_UP_DN_MASK;
    }
}

/**
 * @brief QEO PWM enter safety mode by software
 *
 * @note call qeo_pwm_software_exit_safety to exit safety mode
 *
 * @param [in] base QEO base address
 */
static inline void qeo_pwm_software_enter_safety(QEOV2_Type *base)
{
    base->PWM.MODE |= QEOV2_PWM_MODE_PWM_ENTER_SAFETY_MODE_MASK;
}

/**
 * @brief QEO PWM exit safety mode by software
 * @param [in] base QEO base address
 */
static inline void qeo_pwm_software_exit_safety(QEOV2_Type *base)
{
    base->PWM.MODE &= ~QEOV2_PWM_MODE_PWM_ENTER_SAFETY_MODE_MASK;
}

/**
 * @brief QEO PWM get default mode config
 * @param [in] base QEO base address
 * @param [in] config qeo_pwm_mode_t
 */
void qeo_pwm_get_default_mode_config(QEOV2_Type *base, qeo_pwm_mode_t *config);

/**
 * @brief QEO PWM config mode
 * @param [in] base QEO base address
 * @param [in] config qeo_pwm_mode_t
 */
void qeo_pwm_config_mode(QEOV2_Type *base, qeo_pwm_mode_t *config);

/**
 * @brief QEO PWM get default safety table
 * @param [in] base QEO base address
 * @param [in] table qeo_pwm_safety_output_table_t
 */
void qeo_pwm_get_default_safety_table_config(QEOV2_Type *base, qeo_pwm_safety_output_table_t *table);

/**
 * @brief QEO PWM get default phase table
 * @param [in] base QEO base address
 * @param [in] table qeo_pwm_phase_output_table_t
 */
void qeo_pwm_get_default_phase_table_config(QEOV2_Type *base, qeo_pwm_phase_output_table_t *table);

/**
 * @brief QEO PWM config safety table
 * @param [in] base QEO base address
 * @param [in] table qeo_pwm_safety_output_table_t
 */
void qeo_pwm_config_safety_table(QEOV2_Type *base, qeo_pwm_safety_output_table_t *table);

/**
 * @brief QEO PWM onfig phase table
 * @param [in] base QEO base address
 * @param [in] index phase table index
 * @param [in] table qeo_pwm_phase_output_table_t
 */
void qeo_pwm_config_phase_table(QEOV2_Type *base, uint8_t index, qeo_pwm_phase_output_table_t *table);

/**
 * @brief QEO enable software position inject
 * @param [in] base QEO base address
 */
static inline void qeo_enable_software_position_inject(QEOV2_Type *base)
{
    base->POSTION_SEL |= QEOV2_POSTION_SEL_POSTION_SEL_MASK;
}

/**
 * @brief QEO software inject position
 * @param [in] base QEO base address
 * @param [in] position position value
 */
static inline void qeo_software_position_inject(QEOV2_Type *base, uint32_t position)
{
    base->POSTION_SOFTWARE = QEOV2_POSTION_SOFTWARE_POSTION_SOFTWAVE_SET(position);
}

/**
 * @brief QEO disable software position inject, QEO will using position from hardware
 * @param [in] base QEO base address
 */
static inline void qeo_disable_software_position_inject(QEOV2_Type *base)
{
    base->POSTION_SEL &= ~QEOV2_POSTION_SEL_POSTION_SEL_MASK;
}

/**
 * @brief QEO check calculate finish status
 * @param [in] base QEO base address
 * @retval true or false
 */
static inline bool qeo_check_calculate_finish(QEOV2_Type *base)
{
    return (QEOV2_DEBUG1_QEO_FINISH_GET(base->DEBUG1) != 0) ? true : false;
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_QEOV2_DRV_H */
