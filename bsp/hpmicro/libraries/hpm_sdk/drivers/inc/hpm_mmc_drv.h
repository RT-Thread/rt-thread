/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MMC_DRV_H
#define HPM_MMC_DRV_H

#include "hpm_common.h"
#include "hpm_mmc_regs.h"
/**
 * @brief MMC driver APIs
 * @defgroup mmc_interface MMC driver APIs
 * @ingroup mmc_interfaces
 * @{
 */

/* trigger source to update position parameter */
typedef enum {
    mmc_pos_update_by_timestamp = 0,
    mmc_pos_update_by_intrgr0_rise_edge = 1,
    mmc_pos_update_by_intrgr1_rise_edge = 2,
    mmc_pos_update_by_outtrgr0_rise_edge = 3,
    mmc_pos_update_by_outtrgr1_rise_edge = 4,
    mmc_pos_update_by_self_pos_thr = 5,
    mmc_pos_update_by_self_speed_thr = 6,
} mmc_pos_update_trigger_t;


/* cmd mask to update position parameter */
typedef enum {
    mmc_pos_update_none = 0,
    mmc_pos_update_position = 1 << 0,
    mmc_pos_update_revolution = 1 << 1,
    mmc_pos_update_speed = 1 << 2,
    mmc_pos_update_accel = 1 << 3,
    mmc_pos_update_all = 0b1111,
} mmc_pos_update_cmd_mask_t;

typedef enum {
    mmc_coef_not_update = 0,
    mmc_coef_p_update = 1 << 0,
    mmc_coef_i_update = 1 << 1,
    mmc_coef_a_update = 1 << 2,
    mmc_coef_update_all = 0b111,
} mmc_coef_update_cmd_mask_t;

typedef struct {
    bool discrete_pos_mode;
    uint32_t discrete_line;
    uint32_t continuous_step_thr;
    uint32_t continuous_circ_thr;
    uint32_t oosync_theta_thr;
} mmc_track_pos_mode_t;

typedef struct {
    bool force_accel_to_zero;
    bool en_ms_coef;
    bool open_loop_mode;
    bool pos_16bit_type;      /* true for output 16bit position, false for output 32bit position */
    bool sync_new_pos;        /* predictor base new track position data */
    mmc_track_pos_mode_t pos_mode;
} mmc_track_mode_t;

typedef struct {
    uint32_t pos_time;
    uint32_t position;
    int32_t revolution;
    double speed;
    double accel;
    uint32_t cmd_mask; /*!< cmd to to select which parameters to update */
    uint32_t trigger;  /*!< trigger source for when to update parameters */
} mmc_pos_or_delta_pos_input_t;

typedef struct {
    uint32_t coef_time;
    double coef_p;
    double coef_i;
    double coef_a;
    uint32_t cmd_mask; /* cmd to select change which parameter */
} mmc_coef_input_t;

typedef struct {
    uint32_t err_thr;
    uint32_t hold_time;
    double coef_p;
    double coef_i;
    double coef_a;
} mmc_coef_trig_config_t;

typedef struct {
    uint32_t time;
    uint32_t position;
    int32_t revolution;
    double speed;
    double accel;
} mmc_pos_out_t;

typedef struct {
    double coef_p;
    double coef_i;
    double coef_a;
} mmc_coef_out_t;

/* track event, definition align with interrupt mask and status mask */
typedef enum {
    mmc_track_shadow_read_done = 1 << 0,
    mmc_track_init_coefs_done = 1 << 1,
    mmc_track_init_pos_done = 1 << 2,
    mmc_track_oosync = 1 << 4,
    mmc_track_idle = 1 << 5, /*!< no corresponding interrupt */
    mmc_pred1_init_pos_done = 1 << 6,
    mmc_pred0_init_pos_done = 1 << 7,
    mmc_track_init_delta_pos_done = 1 << 8,
    mmc_track_pos_trig_valid = 1 << 9,
    mmc_track_speed_trig_valid = 1 << 10,
} mmc_track_event_t;

typedef enum {
    mmc_pred_idle = MMC_BR_BR_ST_IDLE_MASK,
    mmc_pred_init_delta_pos_done = MMC_BR_BR_ST_INI_DELTA_POS_DONE_MASK,
    mmc_pred_pos_trig_valid = MMC_BR_BR_ST_POS_TRG_VLD_MASK,
    mmc_pred_speed_trig_valid = MMC_BR_BR_ST_SPEED_TRG_VLD_MASK,
    mmc_pred_open_loop = MMC_BR_BR_ST_OPEN_LOOP_ST_MASK,
} mmc_pred_event_t;

typedef enum {
    mmc_pred_pos_trig_valid_int = MMC_BR_BR_CTRL_POS_TRG_VALID_IE_MASK,
    mmc_pred_speed_trig_valid_int = MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_MASK,
    mmc_pred_init_delta_pos_done_int = MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_MASK
} mmc_pred_int_t;

typedef struct {
    bool speed_trig_int;
    bool position_trig_int;
    bool delta_pos_done_trig_int;
    bool open_loop_mode;
    uint8_t pred_mode;
    uint8_t not_first_pred_trig_type;
    uint8_t first_pred_trig_type;
} mmc_pred_mode_t;

typedef enum {
    mmc_pred_not_reload_pos_cmd = 0,
    mmc_pred_0_reload_pos_cmd = 2,
    mmc_pred_1_reload_pos_cmd = 1,
    mmc_pred_both_reload_pos_cmd = 3,
} mmc_pred_reload_pos_cmd_t;

typedef enum {
    mmc_pred_by_period = 0,
    mmc_pred_continuously_repeat = 1,
    mmc_pred_only_once = 2,
} mmc_pred_time_t;

/* using for mmc_pred_by_period mode */
typedef struct {
    uint32_t offset_time;
    uint32_t period_time;
    uint32_t first_time;
} mmc_pred_period_time_t;

typedef struct {
    bool less_than;         /*!< true for less than, false for greater than */
    bool enable;
    uint32_t position_thr;  /*!< position in a cycle */
    int32_t revolution_thr; /*!< cycle */
} mmc_pos_trig_t;

typedef struct {
    bool absolute_compare; /*!< true for absolute value compare, false for signed value compare */
    bool less_than;        /*!< true for less than, false for greater than */
    bool enable;
    int32_t speed_thr;
} mmc_speed_trig_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MMC set frequency
 * @param [in] base MMC base address
 * @param [in] freq the moto system freq
 */
static inline void mmc_set_sysclk_freq(MMC_Type *base, uint32_t freq)
{
    uint32_t period;
    base->SYSCLK_FREQ = freq;
    /* 1/freq *(2^24)*(2^20) */
    period = (uint32_t)((double)(1 << 20) * (1 << 24) / freq);
    base->SYSCLK_PERIOD = period;
}

/**
 * @brief MMC software reset
 * @param [in] base MMC base address
 */
static inline void mmc_software_reset(MMC_Type *base)
{
    base->CR |= MMC_CR_SFTRST_MASK;
    base->CR &= ~MMC_CR_SFTRST_MASK;
}

/**
 * @brief MMC module enable
 * @param [in] base MMC base address
 */
static inline void mmc_enable_module(MMC_Type *base)
{
    base->CR |= MMC_CR_MOD_EN_MASK;
}

/**
 * @brief MMC module disable
 * @param [in] base MMC base address
 */
static inline void mmc_disable_module(MMC_Type *base)
{
    base->CR &= ~MMC_CR_MOD_EN_MASK;
}

/**
 * @brief MMC track set loop mode
 * @param [in] base MMC base address
 * @param [in] open_loop true for open loop, false for close loop
 */
static inline void mmc_track_set_open_loop_mode(MMC_Type *base, bool open_loop)
{
    if (open_loop) {
        base->CR |= MMC_CR_OPEN_LOOP_MODE_MASK;
    } else {
        base->CR &= ~MMC_CR_OPEN_LOOP_MODE_MASK;
    }
}

/**
 * @brief MMC track set adjop mode
 * @param [in] base MMC base address
 * @param [in] adjop true for adjop mode, false for normal mode
 */
static inline void mmc_track_set_adjop_mode(MMC_Type *base, bool adjop)
{
    if (adjop) {
        base->CR |= MMC_CR_ADJOP_MASK;
    } else {
        base->CR &= ~MMC_CR_ADJOP_MASK;
    }
}

/**
 * @brief MMC track request shadow read
 * @param [in] base MMC base address
 *
 * @note request shadow before read mmc track resoult register
 */
static inline void mmc_track_enable_shadow_read(MMC_Type *base)
{
    base->CR |= MMC_CR_SHADOW_RD_REQ_MASK;
    /* SHADOW_RD_REQ clear indicates that the shadow is complete */
    while ((base->CR & MMC_CR_SHADOW_RD_REQ_MASK) == MMC_CR_SHADOW_RD_REQ_MASK) {
    }
}

/**
 * @brief MMC track enable interrupt
 * @param [in] base MMC base address
 * @param [in] int_mask interrupt_mask @ref mmc_track_event_t
 */
static inline void mmc_track_enable_interrupt(MMC_Type *base, uint32_t int_mask)
{
    base->INT_EN = int_mask;
}

/**
 * @brief MMC track disable interrupt
 * @param [in] base MMC base address
 * @param [in] int_mask interrupt_mask @ref mmc_track_event_t
 */
static inline void mmc_track_disable_interrupt(MMC_Type *base, uint32_t int_mask)
{
    base->INT_EN &= ~int_mask;
}

/**
 * @brief MMC track get status register value
 * @param [in] base MMC base address
 * @retval status register value
 */
static inline uint32_t mmc_track_get_status(MMC_Type *base)
{
    return base->STA;
}

/**
 * @brief MMC track clear status flag in status register
 * @param [in] base MMC base address
 * @param [in] clr_mask  @ref mmc_track_event_t
 */
static inline void mmc_track_clear_status(MMC_Type *base, uint32_t clr_mask)
{
    base->STA = clr_mask; /* W1C */
}

/**
 * @brief MMC track set the threshold of theta for out-of-sync
 * @param [in] base MMC base address
 * @param [in] threshold threshold value
 */
static inline void mmc_track_set_oosync_theta_threshold(MMC_Type *base, uint32_t threshold)
{
    base->OOSYNC_THETA_THR = MMC_OOSYNC_THETA_THR_VAL_SET(threshold);
}

/**
 * @brief MMC track config position mode
 * @param [in] base MMC base address
 * @param [in] mode mmc_track_pos_mode_t
 */
void mmc_track_config_pos_mode(MMC_Type *base, mmc_track_pos_mode_t *mode);

/**
 * @brief MMC track get default mode config
 * @param [in] base MMC base address
 * @param [in] config mmc_track_mode_t
 */
void mmc_track_get_default_mode_config(MMC_Type *base, mmc_track_mode_t *config);

/**
 * @brief MMC track config mode
 * @param [in] base MMC base address
 * @param [in] config mmc_track_mode_t
 */
void mmc_track_config_mode(MMC_Type *base, mmc_track_mode_t *config);

/**
 * @brief MMC track config position parameter
 * @param [in] base MMC base address
 * @param [in] para mmc_pos_or_delta_pos_input_t
 */
void mmc_track_config_pos_para(MMC_Type *base, mmc_pos_or_delta_pos_input_t *para);

/**
 * @brief MMC track config delta parameter
 * @param [in] base MMC base address
 * @param [in] para mmc_pos_or_delta_pos_input_t
 */
void mmc_track_config_delta_para(MMC_Type *base, mmc_pos_or_delta_pos_input_t *para);

/**
 * @brief MMC track config coef parameter
 * @param [in] base MMC base address
 * @param [in] para mmc_coef_input_t
 */
void mmc_track_config_coef_para(MMC_Type *base, mmc_coef_input_t *para);

/**
 * @brief MMC track config position trigger
 * @param [in] base MMC base address
 * @param [in] trig mmc_pos_trig_t
 */
void mmc_track_config_position_trig(MMC_Type *base, mmc_pos_trig_t *trig);

/**
 * @brief MMC track config speed trigger
 * @param [in] base MMC base address
 * @param [in] trig mmc_speed_trig_t
 */
void mmc_track_config_speed_trig(MMC_Type *base, mmc_speed_trig_t *trig);

/**
 * @brief MMC track disable position trigger
 * @param [in] base MMC base address
 */
static inline void mmc_track_disable_position_trig(MMC_Type *base)
{
    base->POS_TRG_CFG &= ~MMC_POS_TRG_CFG_EN_MASK;
}

/**
 * @brief MMC track disable speed trigger
 * @param [in] base MMC base address
 */
static inline void mmc_track_disable_speed_trig(MMC_Type *base)
{
    base->SPEED_TRG_CFG &= ~MMC_SPEED_TRG_CFG_EN_MASK;
}

/**
 * @brief MMC track config multiple coef trigger
 * @param [in] base MMC base address
 * @param [in] index coef trigger index(0/1/2)
 * @param [in] config mmc_coef_trig_config_t
 */
void mmc_track_config_coef_trig(MMC_Type *base, uint8_t index, mmc_coef_trig_config_t *config);

/**
 * @brief MMC track get result
 * @param [in] base MMC base address
 * @param [out] pos_out mmc_pos_out_t
 * @param [out] coef_out mmc_coef_out_t
 */
void mmc_track_get_result(MMC_Type *base, mmc_pos_out_t *pos_out, mmc_coef_out_t *coef_out);

/* predictor */
/**
 * @brief MMC enable predictor
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 */
static inline void mmc_enable_pred(MMC_Type *base, uint8_t index)
{
    base->BR[index].BR_CTRL |= MMC_BR_BR_CTRL_BR_EN_MASK;
}

/**
 * @brief MMC disable predictor
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 */
static inline void mmc_disable_pred(MMC_Type *base, uint8_t index)
{
    base->BR[index].BR_CTRL &= ~MMC_BR_BR_CTRL_BR_EN_MASK;
}

/**
 * @brief MMC predictor set loop mode
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] open_loop true for open loop, false for close loop
 */
static inline void mmc_pred_set_open_loop_mode(MMC_Type *base, uint8_t index, bool open_loop)
{
    if (open_loop) {
        base->BR[index].BR_CTRL |= MMC_BR_BR_CTRL_OPEN_LOOP_MODE_MASK;
    } else {
        base->BR[index].BR_CTRL &= ~MMC_BR_BR_CTRL_OPEN_LOOP_MODE_MASK;
    }
}

/**
 * @brief MMC predictor set pred time
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] time mmc_pred_time_t
 */
static inline void mmc_pred_set_pred_time(MMC_Type *base, uint8_t index, mmc_pred_time_t time)
{
    base->BR[index].BR_CTRL &= ~MMC_BR_BR_CTRL_PRED_MODE_MASK;
    base->BR[index].BR_CTRL |= MMC_BR_BR_CTRL_PRED_MODE_SET(time);
}

/**
 * @brief MMC pred enable interrupt
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] int_mask interrupt_mask @ref mmc_pred_int_t
 */
static inline void mmc_pred_enable_interrupt(MMC_Type *base, uint8_t index, uint32_t int_mask)
{
    base->BR[index].BR_CTRL |= int_mask;
}

/**
 * @brief MMC pred disable interrupt
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] int_mask interrupt_mask @ref mmc_pred_int_t
 */
static inline void mmc_pred_disable_interrupt(MMC_Type *base, uint8_t index, uint32_t int_mask)
{
    base->BR[index].BR_CTRL &= ~int_mask;
}

/**
 * @brief MMC predictor get status register value
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @retval predictor status register value
 */
static inline uint32_t mmc_pred_get_status(MMC_Type *base, uint8_t index)
{
    return base->BR[index].BR_ST;
}

/**
 * @brief MMC predictor clear status bit in reigster
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] clr_mask bit mask @ref mmc_pred_event_t
 */
static inline void mmc_pred_clear_status(MMC_Type *base, uint8_t index, uint32_t clr_mask)
{
    base->BR[index].BR_ST = clr_mask; /*!< W1C */
}

/**
 * @brief MMC predictor get default mode config
 * @param [in] base MMC base address
 * @param [in] config mmc_pred_mode_t
 */
void mmc_pred_get_default_mode_config(MMC_Type *base, mmc_pred_mode_t *config);

/**
 * @brief MMC predictor config mode
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] config mmc_pred_mode_t
 */
void mmc_pred_config_mode(MMC_Type *base, uint8_t index, mmc_pred_mode_t *config);

/**
 * @brief MMC predictor config position parameter
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] para mmc_pos_or_delta_pos_input_t
 * @param [in] req_reload request to update parameter cmd
 *
 * @note 2 predictors can be set simultaneously by call mmc_pred_reload_pos_cmd()
 */
void mmc_pred_config_pos_para(MMC_Type *base, uint8_t index, mmc_pos_or_delta_pos_input_t *para, bool req_reload);

/**
 * @brief MMC predictor reload position parameter cmd
 * @param [in] base MMC base address
 * @param [in] cmd mmc_pred_reload_pos_cmd_t
 */
static inline void mmc_pred_reload_pos_cmd(MMC_Type *base, mmc_pred_reload_pos_cmd_t cmd)
{
    base->CR &= ~(MMC_CR_INI_BR0_POS_REQ_MASK | MMC_CR_INI_BR0_POS_REQ_MASK);
    base->CR |= cmd << MMC_CR_INI_BR1_POS_REQ_SHIFT;
}

/**
 * @brief MMC predictor update delta parameter
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] para mmc_pos_or_delta_pos_input_t
 */
void mmc_pred_config_delta_para(MMC_Type *base, uint8_t index, mmc_pos_or_delta_pos_input_t *para);

/**
 * @brief MMC predictor config period time
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] time mmc_pred_period_time_t
 */
void mmc_pred_config_period_time(MMC_Type *base, uint8_t index, mmc_pred_period_time_t *time);

/**
 * @brief MMC predictor config position trigger
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] trig mmc_pos_trig_t
 */
void mmc_pred_config_position_trig(MMC_Type *base, uint8_t index, mmc_pos_trig_t *trig);

/**
 * @brief MMC predictor config speed trigger
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [in] trig mmc_speed_trig_t
 */
void mmc_pred_config_speed_trig(MMC_Type *base, uint8_t index, mmc_speed_trig_t *trig);

/**
 * @brief MMC predictor disable position trigger
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 */
static inline void mmc_pred_disable_position_trig(MMC_Type *base, uint8_t index)
{
    base->BR[index].BR_TRG_POS_CFG &= ~MMC_BR_BR_TRG_POS_CFG_EN_MASK;
}

/**
 * @brief MMC predictor disable speed trigger
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 */
static inline void mmc_pred_disable_speed_trig(MMC_Type *base, uint8_t index)
{
    base->BR[index].BR_TRG_SPEED_CFG &= ~MMC_BR_BR_TRG_SPEED_CFG_EN_MASK;
}

/**
 * @brief MMC predictor get result
 * @param [in] base MMC base address
 * @param [in] index predictor index(0/1)
 * @param [out] pos_out mmc_pos_out_t
 */
void mmc_pred_get_result(MMC_Type *base, uint8_t index, mmc_pos_out_t *pos_out);

/**
 * @brief MMC predictor get result
 * @param [in] base MMC base address
 * @param [out] para mmc_pos_or_delta_pos_input_t
 */
void mmc_get_default_pos_or_delta_pos_para(MMC_Type *base, mmc_pos_or_delta_pos_input_t *para);


#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_MMC_DRV_H */
