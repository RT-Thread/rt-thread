/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MMC_DRV_H
#define HPM_MMC_DRV_H

#include "hpm_common.h"
#include "hpm_mtg_regs.h"
/**
 * @brief MTG driver APIs
 * @defgroup mtg_interface MTG driver APIs
 * @ingroup motor_interfaces
 * @{
 */

/**
 * @brief define the struct of mtg lock values
 *
 */
typedef struct mtg_result {
    int32_t rev; /* revolution */
    uint32_t pos; /* postion */
    int32_t vel; /* velocity */
    int32_t acc; /* acceleration */
    uint32_t time_stamp; /* time stamp */
} mtg_lock_value_t;

/**
 * @brief define the enum of the postion of the observed object
 */
typedef enum mtg_evnet_object_postion {
    event_source_before_filter = 1 << 0, /* before filter, also treat as input of mtg */
    event_source_filter_output = 1 << 1, /* after filter, also treat as input of mtg's time compensation module */
    event_source_tra0_output = 1 << 2, /* output of mtg's trajectory predictor0 */
    event_source_tra1_output = 1 << 3, /* output of mtg's trajectory predictor1 */
} mtg_evnet_object_postion_t;

/**
 * @brief define the enum of the observed object
 */
typedef enum mtg_event_object {
    event_object_rev_pos = 1, /* location, revolution and position */
    event_object_vel = 2, /* velocity */
    event_object_acc = 4, /* acceleration */
    event_object_pos = 8, /* postion, ignore revolution */
} mtg_event_object_t;

/**
 * @brief define the enum of the event detection mode
 */
typedef enum mtg_event_mode {
    event_mode_across = 1, /* across mode, change from greater than to less than, or opposite */
    event_mode_hold = 2, /* hold mode, maintain within a range for a period of time */
    event_mode_over_protect = 4, /* over protect mode, greater than or less than */
    event_mode_time_match = 8, /* time match mode, when the synt's cnt value is equal to the preset */
} mtg_event_mode_t;

/**
 * @brief define the enum of the event detection direction
 */
typedef enum mtg_event_dir {
    event_dir_negative = 0,
    event_dir_positive = 1,
    event_dir_both = 2,
} mtg_event_dir_t;

/**
 * @brief define the enum of the event detection direction calculation mode
 */
typedef enum mtg_event_dir_mode {
    event_dir_mode_dy = 0, /* use first derivative of object */
    event_dir_mode_y1_y0 = 1, /* use difference of current and previous */
} mtg_event_dir_mode_t;

/**
 * @brief define the enum of the event detection over protect mode
 */
typedef enum mtg_event_over_mode_cmp {
    event_over_cmp_mode_smaller = 0,
    event_over_cmp_mode_bigger = 1,
} mtg_event_over_mode_cmp_t;

/**
 * @brief define the enum of the event trigger number
 */
typedef enum mtg_event_trig_num {
    event_trig_once = 0, /* event can only be triggered once */
    event_trig_repeat = 1, /* event can be triggered multiple times */
} mtg_event_trig_num_t;

/**
 * @brief define the struct of the event setup parameter
 */
typedef struct mtg_event_param {
    bool enable;
    bool irq_en; /* enable or disable the event irq */
    mtg_event_object_t obj;
    mtg_evnet_object_postion_t obj_postion;
    mtg_event_mode_t mode;
    mtg_event_dir_t dir;
    mtg_event_dir_mode_t dir_mode;
    mtg_event_over_mode_cmp_t cmp_mode;
    mtg_event_trig_num_t trig_num;

    /* union struct of event presets registers, different meaning when different event mode */
    union {
        struct {
            uint32_t cross_value_h; /* the high 32bit of cross_value, only need set when object is ${event_object_rev_pos} */
            uint32_t cross_value_l; /* the low 32bit of cross_value */
        } cross_param;
        struct {
            uint32_t hold_value_h; /* the high 32bit of hold_value, only need set when object is ${event_object_rev_pos} */
            uint32_t hold_value_l; /* the low 32bit of hold_value */
            uint32_t error_limit; /* the range is between ${hold value - error_limit} and ${hold value + error_limit} */
            uint32_t hold_clock_cnt; /* the event will be triggered when match the hold value and error_limit and last for &{hold_clock_cnt} clocks */
        } hold_param;
        struct {
            uint32_t limit_value_h; /* the high 32bit of limit_value */
            uint32_t limit_value_l; /* the low 32bit of limit_value */
        } over_protect_param;
        struct {
            uint32_t clock_count; /* the event will be triggered when synt clock match the value */
        } time_param;
        uint32_t preset[4];
    } preset;
} mtg_event_param_t;

/*
 * @brief define the struct of the trajectory predictor limit
 */
typedef struct mtg_tra_limit_param {
    bool vel_step_limit_en; /* velocity step limit enable, when enable, the velocity variation per clock will be limited by vel_step_max and vel_step_min */
    uint32_t vel_step_max; /* velocity step limit value max */
    uint32_t vel_step_min;  /* velocity step limit value min */
    bool pos_step_limit_en; /* postion step limit enable, when enable, the postion variation per clock will be limited by pos_step_max and pos_step_min */
    uint32_t pos_step_max; /* postion step limit value max */
    uint32_t pos_step_min; /* postion step limit value min */
} mtg_tra_limit_param_t;

/**
 * @brief define the enum of the software force one way mode
 */
typedef enum mtg_software_force_one_way_mode {
    sw_force_negative = 0,
    sw_force_positive = 1,
} mtg_software_force_one_way_mode_t;

/**
 * @brief define the enum of the hardware force one way mode
 */
typedef enum vel_one_way_mode {
    bigger_or_eq_zero = 0,
    smaller_or_eq_zero = 1,
} vel_one_way_mode_t;

/**
 * @brief define the struct of the hardware force one way mode
 */
typedef struct mtg_hardware_force_one_way_mode {
    uint32_t vel_limit_p;
    uint32_t vel_limit_n;
} mtg_hardware_force_one_way_mode_t;

/**
 * @brief define the enum of the filter initialization mode
 */
typedef enum mtg_filter_rev_init_mode {
    rev_init_mode_from_first_input_value = 0, /* the first input value will be used by the mtg filter to initialize the filter */
    rev_init_mode_from_register = 1, /* the value in the register will be used by the mtg filter to initialize the filter */
} mtg_filter_rev_init_mode_t;

/**
 * @brief define the enum of the filter judge mode
 * It affects the judgment conditions for changes in the number of revolution
 */
typedef enum mtg_filter_rev_judge_mode {
    mtg_rev_judge_mode_new_sub_old = 0,
    mtg_rev_judge_mode_encoder_lines = 1,
} mtg_filter_rev_judge_mode_t;

/**
 * @brief define the enum of the filter ff mode
 */
typedef enum mtg_filter_ff_mode {
    mtg_filter_ff_mode_from_register = 0,
    mtg_filter_ff_mode_from_input = 1,
} mtg_filter_ff_mode_t;

typedef struct mtg_filter_param {
    bool enable; /* filter enable */
    bool ff_en; /* filter feedforward enable */
    bool init_en; /* filter first value initialization enable */
    bool err_bypass_en; /* filter error bypass enable. when difference between filter input and output beyond the limit, filter output will be bypassed  */
    bool err_init; /* filter error reset enable. when difference between filter input and output beyond the limit, the filter will reset */
    bool timeout_en; /* filter timeout enable */
    bool err_bypass_i_f_en;
    bool err_bypass_f_i_en;
    bool multi_err_irq_en;
    bool acceleration_en; /* filter acceleration enable. when enable, the filter will output acceleration value */
    mtg_filter_rev_init_mode_t rev_ini_mode;
    mtg_filter_rev_judge_mode_t rev_judge_mode;
    mtg_filter_ff_mode_t ff_mode;
    int32_t rev_init_value; /* the initial value of revolution. only used when init_en == true */
    int32_t vel_init_value; /* the initial value of velocity. only used when init_en == true */
    int32_t acc_init_value; /* the initial value of acceleration. only used when init_en == true */
    uint32_t pos_init_value; /* the initial value of postion. only used when init_en == true */
    uint32_t filter_mot_sel;
    uint32_t filter_stage_sel;
    uint32_t filter_time_constant_tp;
    uint32_t filter_time_constant_tz;
    uint32_t filter_time_constant_tz_1;
    uint32_t filter_zero_tz_sel;
    uint32_t filter_gain;
    uint32_t filter_stage_shift[2];
    uint32_t filter_param_shift;
    uint32_t filter_time_shift;
    uint32_t filter_ff_shift;
    uint32_t filter_error_limit_l;
    uint32_t filter_error_limit_h;
} mtg_filter_param_t;

/**
 * @brief define the enum of the trajectory predictor time input source
 */
typedef enum mtg_time_input_source {
    mtg_time_input_from_filter = 1, /* the value in the filter will be used */
    mtg_time_input_from_input = 2, /* the value in the input will be used */
} mtg_time_input_source_t;

/**
 * @brief define the struct of the trajectory predictor time initialization
 */
typedef struct mtg_time_init_param {
    bool enable;
    uint32_t adjust_value; /* time compensation clocks */
    uint8_t index;
    mtg_time_input_source_t source;
} mtg_time_init_param_t;

/**
 * @brief define the struct of the trajectory predictor timeout
 */
typedef struct mtg_timeout_param {
    bool enable;
    uint32_t timeout_clock_count;
} mtg_timeout_param_t;

/**
 * @brief define the enum of the trajectory predictor link event
 * link the trigger source and the cmd object, it describes the
 * trigger source
 */
typedef enum mtg_link_cfg {
    link_event0 = 0,
    link_event1 = 1,
    link_event2 = 2,
    link_event3 = 3,
    link_hw_trigger = 4,
    link_sw_trigger = 5,
    link_event_timeout = 6,
} mtg_link_cfg_t;

/**
 * @brief define the enum of the trajectory predictor command object
 */
typedef enum {
    cmd_object_rev = 1 << 0,
    cmd_object_pos = 1 << 1,
    cmd_object_vel = 1 << 2,
    cmd_object_acc = 1 << 3,
    cmd_object_jer = 1 << 4,
} mtg_tra_cmd_object_t;

/**
 * @brief define the enum of the trajectory predictor command mode
 */
typedef enum {
    cmd_mode_new_value = 0, /* when cmd exec, the preset value will replace the old value */
    cmd_mode_old_delta = 1, /* when cmd exec, the preset value will be added to the old value */
} mtg_link_cmd_mode_t;

/**
 * @brief define the struct of the trajectory shift struct
 */
typedef struct mtg_tra_shift {
    uint8_t jerk_shift;
    uint8_t acc_shift;
    uint8_t vel_shift;
} mtg_tra_shift_t;

/**
 * @brief define the struct of the trajectory predictor command
 */
typedef struct mtg_tra_cmd_cfg {
    uint8_t index;
    uint32_t object; /* cmd object, see ${mtg_tra_cmd_object_t} */
    mtg_link_cmd_mode_t mode;
    uint32_t rev_preset;
    uint32_t pos_preset;
    uint32_t vel_preset;
    uint32_t acc_preset;
    uint32_t jer_preset;
} mtg_tra_cmd_cfg_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MTG get trajectory predictor control register value
 * @param [in] base - MTG base address
 * @param [in] tra_index - trajectory predictor index
 * @retval control register value
 */
static inline uint32_t mtg_get_tra_control_status(MTG_Type *base, uint8_t tra_index)
{
    assert(tra_index < 2);
    return base->TRA[tra_index].CONTROL;
}

/**
 * @brief MTG get trajectory predictor commond control register value
 * @param [in] base - MTG base address
 * @param [in] tra_index - trajectory predictor index
 * @param [in] cmd_index - trajectory predicotr command index
 * @retval control register value
 */
static inline uint32_t mtg_get_tra_cmd_control_status(MTG_Type *base, uint8_t tra_index, uint8_t cmd_index)
{
    assert((tra_index < 2) && (cmd_index < 4));
    return base->TRA[tra_index].CMD[cmd_index].CONTROL;
}

/**
 * @brief MTG trigger trajectory predictor lock current values
 * @param [in] base - MTG base address
 * @param [in] tra_index - trajectory predictor index
 */
static inline void mtg_trig_tra_lock(MTG_Type *base, uint8_t tra_index)
{
    assert(tra_index < 2);
    base->TRA[tra_index].CONTROL |= MTG_TRA_CONTROL_SW_LOCK_SET(1);
}

/**
 * @brief MTG clear trajectory predictor lock status
 * @param [in] base - MTG base address
 * @param [in] tra_index - trajectory predictor index
 */
static inline void mtg_clear_tra_lock(MTG_Type *base, uint8_t tra_index)
{
    assert(tra_index < 2);
    base->TRA[tra_index].CONTROL &= ~MTG_TRA_CONTROL_SW_LOCK_MASK;
}

/**
 * @brief MTG get trajectory predictor revolution lock value
 * @param [in] base - MTG base address
 * @param [in] tra_index - trajectory predictor index
 * @retval trajectory predictor revolution value
 */
static inline int32_t mtg_get_tra_rev_lock_value(MTG_Type *base, uint8_t tra_index)
{
    assert(tra_index < 2);
    return base->TRA[tra_index].LOCK_REV;
}

/**
 * @brief MTG get trajectory predictor postion lock value
 * @param [in] base - MTG base address
 * @param [in] tra_index - trajectory predictor index
 * @retval trajectory predictor postion value
 */
static inline uint32_t mtg_get_tra_pos_lock_value(MTG_Type *base, uint8_t tra_index)
{
    assert(tra_index < 2);
    return base->TRA[tra_index].LOCK_POS;
}

/**
 * @brief MTG get trajectory predictor velocity lock value
 * @param [in] base - MTG base address
 * @param [in] tra_index - trajectory predictor index
 * @retval trajectory predictor velocity value
 */
static inline int32_t mtg_get_tra_vel_lock_value(MTG_Type *base, uint8_t tra_index)
{
    assert(tra_index < 2);
    return base->TRA[tra_index].LOCK_VEL;
}

/**
 * @brief MTG get trajectory predictor acceleration lock value
 * @param [in] base - MTG base address
 * @param [in] tra_index - trajectory predictor index
 * @retval trajectory predictor acceleration value
 */
static inline int32_t mtg_get_tra_acc_lock_value(MTG_Type *base, uint8_t tra_index)
{
    assert(tra_index < 2);
    return base->TRA[tra_index].LOCK_ACC;
}

/**
 * @brief MTG setup filter error bypass limit
 * @param [in] base MTG base address
 * @param [in] limit - bypass limit
 */
static inline void mtg_filter_set_err_bypass_limit(MTG_Type *base, uint32_t limit)
{
    base->FILTER_ERROR_LIMIT_H = limit;
}

/**
 * @brief MTG setup hardware switch from bypass status to filter status's limit
 *        When the difference between input and filter's pos result is smaller than the limit,
 *        the filter will use the filter's result inside of the input.
 * @param [in] base MTG base address
 * @param [in] param - filter params
 */
static inline void mtg_filter_set_bypass_switch_filter_limit(MTG_Type *base, uint32_t limit)
{
    base->FILTER_ERROR_LIMIT_L = limit;
}

/**
 * @brief MTG enable filter error bypass
 *        When difference between input and filter's pos result is bigger than the limit,
 *        the filter output will be bypass and input will be output to the filter's port.
 * @param [in] base MTG base address
 * @param [in] limit - bypass limit
 */
static inline void mtg_filter_enable_bypass(MTG_Type *base)
{
    base->FILTER_CONTROL |= MTG_FILTER_CONTROL_ERR_BYPASS_F_I_EN_SET(1);
    base->FILTER_CONTROL |= MTG_FILTER_CONTROL_ERR_BYPASS_EN_SET(1);
}

/**
 * @brief MTG disable filter error bypass
 *        When difference between input and filter's pos result is bigger than the limit,
 *        the filter output will be bypass and input will be output to the filter's port.
 * @param [in] base MTG base address
 * @param [in] limit - bypass limit
 */
static inline void mtg_filter_disable_bypass(MTG_Type *base)
{
    base->FILTER_CONTROL &= ~MTG_FILTER_CONTROL_ERR_BYPASS_F_I_EN_MASK;
    base->FILTER_CONTROL &= ~MTG_FILTER_CONTROL_ERR_BYPASS_EN_MASK;
}

/**
 * @brief MTG reset filter enable error reset
 * @param [in] base MTG base address
 */
static inline void mtg_filter_enable_reset_init(MTG_Type *base)
{
    base->FILTER_CONTROL |= MTG_FILTER_CONTROL_ERR_INI_SET(1);
}

/**
 * @brief MTG reset filter disable error reset
 * @param [in] base MTG base address
 */
static inline void mtg_filter_disable_reset_init(MTG_Type *base)
{
    base->FILTER_CONTROL &= ~MTG_FILTER_CONTROL_ERR_INI_MASK;
}

/**
 * @brief MTG enable hardware switch from bypass status to filter status's limit
 *        When the difference between input and filter's pos result is smaller than the limit,
 *        the filter will use the filter's result inside of the input.
 *        The switch result can be defined by reading the switch status register.
 * @param [in] base MTG base address
 * @param [in] param - filter params
 */
static inline void mtg_filter_switch_filter_result(MTG_Type *base)
{
    base->FILTER_CONTROL |= MTG_FILTER_CONTROL_ERR_BYPASS_I_F_EN_SET(1);
}

/**
 * @brief MTG disable hardware switch from bypass status to filter status's limit
 *        When the difference between input and filter's pos result is smaller than the limit,
 *        the filter will use the filter's result inside of the input.
 *        The switch result can be defined by reading the switch status register.
 * @param [in] base MTG base address
 * @param [in] param - filter params
 */
static inline void mtg_filter_stop_auto_switch_filter_result(MTG_Type *base)
{
    base->FILTER_CONTROL &= ~MTG_FILTER_CONTROL_ERR_BYPASS_I_F_EN_MASK;
}

/**
 * @brief MTG setup hardware switch from bypass status to filter status's limit
 *        When the difference between input and filter's pos result is smaller than the limit,
 *        the filter will use the filter's result inside of the input.
 * @param [in] base - MTG base address
 * @retval bypass status
 */
static inline bool mtg_get_err_bypass_status(MTG_Type *base)
{
    return MTG_FILTER_CONTROL_ERR_BYPASS_STATUS_GET(base->FILTER_CONTROL) == 0 ? true : false;
}

/**
 * @brief MTG set time0 adjust value
 * @param [in] base - MTG base address
 * @param [in] value - adjust value
 */
static inline void mtg_set_time0_adjust_value(MTG_Type *base, uint32_t value)
{
    base->FILTER_TIME0_SW_ADJUST = value;
}

/**
 * @brief MTG set time1 adjust value
 * @param [in] base - MTG base address
 * @param [in] value - adjust value
 */
static inline void mtg_set_time1_adjust_value(MTG_Type *base, uint32_t value)
{
    base->FILTER_TIME1_SW_ADJUST = value;
}

/**
 * @brief MTG set time shift value
 * @param [in] base - MTG base address
 * @param [in] index - tra index
 * @param [in] jer_shift - jerk shift
 * @param [in] acc_shift - acceleration shift
 * @param [in] vel_shift - velocity shift
 */
static inline void mtg_tra_set_shift(MTG_Type *base, uint8_t index, uint8_t jer_shift, uint8_t acc_shift, uint8_t vel_shift)
{
    assert(index < 2);
    base->TRA[index].SHIFT = MTG_TRA_SHIFT_JER_SHIFT_SET(jer_shift) |
                             MTG_TRA_SHIFT_ACC_SHIFT_SET(acc_shift) |
                             MTG_TRA_SHIFT_VEL_SHIFT_SET(vel_shift);
}

/**
 * @brief MTG global reset
 * @param [in] base - MTG base address
 */
static inline void mtg_set_global_reset(MTG_Type *base)
{
    base->SW_GLB_RESET = 1;
}

/**
 * @brief MTG stop global reset
 */
static inline void mtg_stop_global_reset(MTG_Type *base)
{
    base->SW_GLB_RESET = 0;
}

/**
 * @brief MTG predictor get lock result
 * @param [in] base MTG base address
 * @param [in] tra_index - trajectory predictor index
 * @param [out] para mtg_lock_value_t
 */
void mtg_get_tra_lock_result(MTG_Type *base, uint8_t tra_index, mtg_lock_value_t *para);

/**
 * @brief MTG setup event params
 * @param [in] base MTG base address
 * @param [in] event_index - event index
 * @param [in] param - event params
 * @param [out] setup status
 */
hpm_stat_t mtg_setup_event(MTG_Type *base, uint8_t event_index, mtg_event_param_t *param);

/**
 * @brief MTG setup trajectory limit params
 * @param [in] base MTG base address
 * @param [in] tra_index - trajectory index
 * @param [in] param - trajectory limit params
 * @param [out] setup status
 */
hpm_stat_t mtg_setup_tra_limit(MTG_Type *base, uint8_t tra_index, mtg_tra_limit_param_t *param);

/**
 * @brief MTG setup trajectory software one_way mode
 * @param [in] base MTG base address
 * @param [in] tra_index - trajectory index
 * @param [in] param - 0:force + , 1:force -
 * @param [out] setup status
 */
void mtg_setup_tra_software_pos_one_way_mode(MTG_Type *base, uint8_t tra_index, mtg_software_force_one_way_mode_t param);

/**
 * @brief MTG setup trajectory hardware one_way mode
 * @param [in] base MTG base address
 * @param [in] tra_index - trajectory index
 * @param [in] param - 0:force + , 1:force -
 * @param [out] setup status
 */
void mtg_setup_tra_hardware_pos_one_way_mode(MTG_Type *base, uint8_t tra_index, mtg_hardware_force_one_way_mode_t *param);

/**
 * @brief MTG disable trajectory postion one_way mode
 * @param [in] base MTG base address
 * @param [in] tra_index - trajectory index
 */
void mtg_disable_tra_pos_one_way_mode(MTG_Type *base, uint8_t tra_index);

/**
 * @brief MTG setup trajectory velocity one_way mode
 * @param [in] base MTG base address
 * @param [in] tra_index - trajectory index
 * @param [in] mode - 0:bigger_or_eq_zero , 1:smaller_or_eq_zero
 */
void mtg_setup_tra_vel_one_way(MTG_Type *base, uint8_t tra_index, vel_one_way_mode_t mode, bool enable);

/**
 * @brief MTG setup filter
 * @param [in] base MTG base address
 * @param [in] param - filter params
 */
void mtg_filter_get_default_filter_stage_param(mtg_filter_param_t *param);

/**
 * @brief MTG setup time compensation module
 * @param [in] base MTG base address
 * @param [in] param - time compensation params
 */
void mtg_setup_time(MTG_Type *base, mtg_time_init_param_t *param);

/**
 * @brief MTG setup filter
 * @param [in] base MTG base address
 * @param [in] param - filter params
 */
void mtg_setup_filter(MTG_Type *base, mtg_filter_param_t *param);

/**
 * @brief MTG setup timeout
 * @param [in] base MTG base address
 * @param [in] param - timeout params
 */
void mtg_setup_timeout(MTG_Type *base, mtg_timeout_param_t *param);

/**
 * @brief MTG link trigger source and trajectory command
 * @param [in] base MTG base address
 * @param [in] tra_index - trajectory index
 * @param [in] link_cfg - link config
 * @param [in] cmd_cfg - command config
 */
void mtg_setup_link_cfg(MTG_Type *base, uint8_t tra_index, mtg_link_cfg_t link_cfg, mtg_tra_cmd_cfg_t *cmd_cfg);

/**
 * @brief MTG software trigger trajectory command
 * @param [in] base MTG base address
 */
void mtg_soft_event_trigger(MTG_Type *base);

/**
 * @brief Get default trajectory shift
 * @param [out] cfg pointer to the tra shift var
 */
void mtg_get_default_tra_shift(mtg_tra_shift_t *cfg);

/**
 * @brief Get the event irq status
 * @param [in] ptr the mtg base
 * @param [in] idx the event index
 */
static inline bool mtg_get_irq_status(MTG_Type *ptr, uint8_t idx)
{
    return ((MTG_EVENT_CONTROL_EVENT_IRQ_GET(ptr->EVENT[idx].CONTROL) != 0) ? true : false);
}

/**
 * @brief Clear the event irq status
 * @param [in] ptr the mtg base
 * @param [in] idx the event index
 */
static inline void mtg_clear_irq_status(MTG_Type *ptr, uint8_t idx)
{
    ptr->EVENT[idx].CONTROL |= MTG_EVENT_CONTROL_EVENT_IRQ_MASK;
}

/**
 * @brief calculate the vel preset
 * @param [in] base MTG base address
 * @param [in] clock MTG clock name
 * @param [in] tra_index - trajectory index
 * @param [in] speed - speed in r/s
 */
int32_t mtg_calc_vel_preset(MTG_Type *base, clock_name_t clock, uint8_t tra_index, float speed);

/**
 * @brief calculate the acc preset
 * @param [in] base MTG base address
 * @param [in] clock MTG clock name
 * @param [in] tra_index - trajectory index
 * @param [in] acc - acc in r/s2
 */
int32_t mtg_calc_acc_preset(MTG_Type *base, clock_name_t clock, uint8_t tra_index, float acc);

/**
 * @brief MTG link trigger source and trajectory command
 * @param [in] base MTG base address
 * @param [in] clock MTG clock name
 * @param [in] tra_index - trajectory index
 * @param [in] jer - jer in r/s3
 */
int32_t mtg_calc_jer_preset(MTG_Type *base, clock_name_t clock, uint8_t tra_index, float jer);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_MTG_DRV_H */
