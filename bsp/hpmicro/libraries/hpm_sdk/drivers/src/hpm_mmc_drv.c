/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_mmc_drv.h"

void mmc_track_config_pos_mode(MMC_Type *base, mmc_track_pos_mode_t *mode)
{
    if (mode->discrete_pos_mode) {
        base->CR |= MMC_CR_DISCRETETRC_MASK;
        base->DISCRETECFG0 = MMC_DISCRETECFG0_POSMAX_SET(mode->discrete_line);
        uint32_t inv_line = (uint32_t)(100000000UL / mode->discrete_line);
        base->DISCRETECFG1 = MMC_DISCRETECFG1_INV_POSMAX_SET(inv_line);
    } else {
        base->CR &= ~MMC_CR_DISCRETETRC_MASK;
        base->DISCRETECFG1 = MMC_DISCRETECFG1_INV_POSMAX_SET(mode->continuous_step_thr);
        base->CONTCFG0 = MMC_CONTCFG0_HALF_CIRC_THETA_SET(mode->continuous_circ_thr);
    }

    base->OOSYNC_THETA_THR = MMC_OOSYNC_THETA_THR_VAL_SET(mode->oosync_theta_thr);
}

void mmc_track_get_default_mode_config(MMC_Type *base, mmc_track_mode_t *config)
{
    (void) base;
    config->force_accel_to_zero = false;
    config->en_ms_coef = false;
    config->open_loop_mode = false;
    config->pos_16bit_type = false;
    config->sync_new_pos = false;

    config->pos_mode.discrete_pos_mode = false;
    config->pos_mode.discrete_line = 0x10000;
    config->pos_mode.continuous_step_thr = 0x1000000;
    config->pos_mode.continuous_circ_thr = 0x1000000;
    config->pos_mode.oosync_theta_thr = 0x1000000;
}

void mmc_track_config_mode(MMC_Type *base, mmc_track_mode_t *config)
{
    base->CR &= ~(MMC_CR_FRCACCELZERO_MASK
                | MMC_CR_MS_COEF_EN_MASK
                | MMC_CR_OPEN_LOOP_MODE_MASK
                | MMC_CR_POS_TYPE_MASK
                | MMC_CR_ADJOP_MASK);

    base->CR |= MMC_CR_FRCACCELZERO_SET(config->force_accel_to_zero)
            | MMC_CR_MS_COEF_EN_SET(config->en_ms_coef)
            | MMC_CR_OPEN_LOOP_MODE_SET(config->open_loop_mode)
            | MMC_CR_POS_TYPE_SET(config->pos_16bit_type)
            | MMC_CR_ADJOP_SET(config->sync_new_pos);

    mmc_track_config_pos_mode(base, &config->pos_mode);
}

void mmc_get_default_pos_or_delta_pos_para(MMC_Type *base, mmc_pos_or_delta_pos_input_t *para)
{
    (void) base;
    para->pos_time = 0;
    para->position = 0;
    para->revolution = 0;
    para->speed = 0;
    para->accel = 0;
    para->cmd_mask = mmc_pos_update_all;
    para->trigger = mmc_pos_update_by_timestamp;
}

void mmc_track_config_pos_para(MMC_Type *base, mmc_pos_or_delta_pos_input_t *para)
{
    /* speed and accel has 19bit decimal */
    int32_t speed = (int32_t)(para->speed * (1 << 19U));
    int32_t accel = (int32_t)(para->accel * (1 << 19U));

    base->INI_SPEED = speed;
    base->INI_ACCEL = accel;
    base->INI_POS = para->position;
    base->INI_REV = para->revolution;
    base->INI_POS_TIME = para->pos_time;

    base->CR &= ~(MMC_CR_INI_POS_TRG_TYPE_MASK | MMC_CR_INI_POS_CMD_MSK_MASK | MMC_CR_INI_POS_REQ_MASK);
    base->CR |= MMC_CR_INI_POS_TRG_TYPE_SET((para->trigger))
                | MMC_CR_INI_POS_CMD_MSK_SET(para->cmd_mask)
                | MMC_CR_INI_POS_REQ_MASK;
}

void mmc_track_config_delta_para(MMC_Type *base, mmc_pos_or_delta_pos_input_t *para)
{
    int32_t speed = (int32_t)(para->speed * (1 << 19U));
    int32_t accel = (int32_t)(para->accel * (1 << 19U));

    base->INI_DELTA_SPEED = speed;
    base->INI_DELTA_ACCEL = accel;
    base->INI_DELTA_POS = para->position;
    base->INI_DELTA_REV = para->revolution;
    base->INI_DELTA_POS_TIME = para->pos_time;

    base->CR &= ~(MMC_CR_INI_DELTA_POS_TRG_TYPE_MASK | MMC_CR_INI_DELTA_POS_CMD_MSK_MASK | MMC_CR_INI_DELTA_POS_REQ_MASK);
    base->CR |= MMC_CR_INI_DELTA_POS_TRG_TYPE_SET((para->trigger))
                | MMC_CR_INI_DELTA_POS_CMD_MSK_SET(para->cmd_mask)
                | MMC_CR_INI_DELTA_POS_REQ_MASK;
}

void mmc_track_config_coef_para(MMC_Type *base, mmc_coef_input_t *para)
{
    int32_t coef_p = (int32_t)(para->coef_p * (1 << 15U));
    int32_t coef_i = (int32_t)(para->coef_i * (1 << 21U));
    int32_t coef_a = (int32_t)(para->coef_a * (1 << 19U));

    base->INI_PCOEF = coef_p;
    base->INI_ICOEF = coef_i;
    base->INI_ACOEF = coef_a;
    base->INI_COEF_TIME = para->coef_time;

    base->CR &= ~(MMC_CR_INI_COEFS_CMD_MSK_MASK | MMC_CR_INI_COEFS_CMD_MASK);
    base->CR |= MMC_CR_INI_COEFS_CMD_MSK_SET(para->cmd_mask)
                | MMC_CR_INI_COEFS_CMD_MASK;
}

void mmc_track_config_coef_trig(MMC_Type *base, uint8_t index, mmc_coef_trig_config_t *config)
{
    int32_t coef_p = (int32_t)(config->coef_p * (1 << 15U));
    int32_t coef_i = (int32_t)(config->coef_i * (1 << 21U));
    int32_t coef_a = (int32_t)(config->coef_a * (1 << 19U));

    base->COEF_TRG_CFG[index].P = coef_p;
    base->COEF_TRG_CFG[index].I = coef_i;
    base->COEF_TRG_CFG[index].A = coef_a;
    base->COEF_TRG_CFG[index].TIME = config->hold_time;
    base->COEF_TRG_CFG[index].ERR_THR = config->err_thr;
}

void mmc_track_get_result(MMC_Type *base, mmc_pos_out_t *pos_out, mmc_coef_out_t *coef_out)
{
    /* mmc_track_enable_shadow_read(base); */

    base->CR |= MMC_CR_SHADOW_RD_REQ_MASK;
    while ((base->CR & MMC_CR_SHADOW_RD_REQ_MASK) == MMC_CR_SHADOW_RD_REQ_MASK) {
    }

    if (pos_out != NULL) {
        pos_out->time = base->ESTM_TIM;
        pos_out->position = base->ESTM_POS;
        pos_out->revolution = (int32_t)base->ESTM_REV;

        int32_t speed = base->ESTM_SPEED;
        int32_t accel = base->ESTM_ACCEL;

        pos_out->speed = (double)speed / (1 << 19U);
        pos_out->accel = (double)accel / (1 << 19U);
    }

    if (coef_out != NULL) {
        int32_t coef_p = base->CUR_PCOEF;
        int32_t coef_i = base->CUR_ICOEF;
        int32_t coef_a = base->CUR_ACOEF;

        coef_out->coef_p = (double)coef_p / (1 << 15U);
        coef_out->coef_i = (double)coef_i / (1 << 21U);
        coef_out->coef_a = (double)coef_a / (1 << 19U);
    }
}


void mmc_pred_get_default_mode_config(MMC_Type *base, mmc_pred_mode_t *config)
{
    (void) base;
    config->speed_trig_int = false;
    config->position_trig_int = false;
    config->delta_pos_done_trig_int = false;


    config->open_loop_mode = false;
    config->pred_mode = 0;
    config->not_first_pred_trig_type = 0;
    config->first_pred_trig_type = 0;
}

void mmc_pred_config_mode(MMC_Type *base, uint8_t index, mmc_pred_mode_t *config)
{
    base->BR[index].BR_CTRL &= ~(MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_MASK
                            | MMC_BR_BR_CTRL_POS_TRG_VALID_IE_MASK
                            | MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_MASK
                            | MMC_BR_BR_CTRL_OPEN_LOOP_MODE_MASK
                            | MMC_BR_BR_CTRL_PRED_MODE_MASK
                            | MMC_BR_BR_CTRL_NF_TRG_TYPE_MASK
                            | MMC_BR_BR_CTRL_F_TRG_TYPE_MASK);

    base->BR[index].BR_CTRL |= MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_SET(config->speed_trig_int)
                            | MMC_BR_BR_CTRL_POS_TRG_VALID_IE_SET(config->position_trig_int)
                            | MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_SET(config->delta_pos_done_trig_int)
                            | MMC_BR_BR_CTRL_OPEN_LOOP_MODE_SET(config->open_loop_mode)
                            | MMC_BR_BR_CTRL_PRED_MODE_SET(config->pred_mode)
                            | MMC_BR_BR_CTRL_NF_TRG_TYPE_SET(config->not_first_pred_trig_type)
                            | MMC_BR_BR_CTRL_F_TRG_TYPE_SET(config->first_pred_trig_type);
}

void mmc_pred_config_pos_para(MMC_Type *base, uint8_t index, mmc_pos_or_delta_pos_input_t *para, bool req_reload)
{
    /* speed and accel has 19bit decimal */
    int32_t speed = (int32_t)(para->speed * (1 << 19U));
    int32_t accel = (int32_t)(para->accel * (1 << 19U));

    base->BR[index].BR_INI_SPEED = speed;
    base->BR[index].BR_INI_ACCEL = accel;
    base->BR[index].BR_INI_POS = para->position;
    base->BR[index].BR_INI_REV = para->revolution;
    base->BR[index].BR_INI_POS_TIME = para->pos_time;

    base->BR[index].BR_CTRL &= ~(MMC_BR_BR_CTRL_INI_POS_TRG_TYPE_MASK | MMC_BR_BR_CTRL_INI_POS_CMD_MSK_MASK);
    base->BR[index].BR_CTRL |= MMC_BR_BR_CTRL_INI_POS_TRG_TYPE_SET((para->trigger))
                            | MMC_BR_BR_CTRL_INI_POS_CMD_MSK_SET(para->cmd_mask);

    if (req_reload) {
        base->CR |= (1U << (MMC_CR_INI_BR0_POS_REQ_SHIFT - index));
    }
}

void mmc_pred_config_delta_para(MMC_Type *base, uint8_t index, mmc_pos_or_delta_pos_input_t *para)
{
    int32_t speed = (int32_t)(para->speed * (1 << 19U));
    int32_t accel = (int32_t)(para->accel * (1 << 19U));

    base->BR[index].BR_INI_DELTA_SPEED = speed;
    base->BR[index].BR_INI_DELTA_ACCEL = accel;
    base->BR[index].BR_INI_DELTA_POS = para->position;
    base->BR[index].BR_INI_DELTA_REV = para->revolution;
    base->BR[index].BR_INI_DELTA_POS_TIME = para->pos_time;

    base->BR[index].BR_CTRL &= ~(MMC_BR_BR_CTRL_INI_DELTA_POS_TRG_TYPE_MASK
                                | MMC_BR_BR_CTRL_INI_DELTA_POS_CMD_MSK_MASK
                                | MMC_BR_BR_CTRL_INI_DELTA_POS_REQ_MASK);

    base->BR[index].BR_CTRL |= MMC_BR_BR_CTRL_INI_DELTA_POS_TRG_TYPE_SET(para->trigger)
                            | MMC_BR_BR_CTRL_INI_DELTA_POS_CMD_MSK_SET(para->cmd_mask)
                            | MMC_BR_BR_CTRL_INI_DELTA_POS_REQ_MASK;
}

/* 不需要shadow吗 */
void mmc_pred_get_result(MMC_Type *base, uint8_t index, mmc_pos_out_t *pos_out)
{
        pos_out->time = base->BR[index].BR_CUR_POS_TIME;
        pos_out->position = base->BR[index].BR_CUR_POS;
        pos_out->revolution = (int32_t)base->BR[index].BR_CUR_REV;

        int32_t speed = base->BR[index].BR_CUR_SPEED;
        int32_t accel = base->BR[index].BR_CUR_ACCEL;

        pos_out->speed = (double)speed / (1 << 19U);
        pos_out->accel = (double)accel / (1 << 19U);
}

void mmc_pred_config_period_time(MMC_Type *base, uint8_t index, mmc_pred_period_time_t *time)
{
    base->BR[index].BR_TIMEOFF = time->offset_time;
    base->BR[index].BR_TRG_PERIOD = time->period_time;
    base->BR[index].BR_TRG_F_TIME = time->first_time;
}

void mmc_pred_config_position_trig(MMC_Type *base, uint8_t index, mmc_pos_trig_t *trig)
{
    base->BR[index].BR_TRG_POS_THR = trig->position_thr;
    base->BR[index].BR_TRG_REV_THR = trig->revolution_thr;

    base->BR[index].BR_TRG_POS_CFG = MMC_BR_BR_TRG_POS_CFG_EDGE_SET(trig->less_than)
                                    | MMC_BR_BR_TRG_POS_CFG_EN_SET(trig->enable);
}

void mmc_pred_config_speed_trig(MMC_Type *base, uint8_t index, mmc_speed_trig_t *trig)
{
    /* speed has 19bit decimal */
    int32_t speed = (int32_t)(trig->speed_thr * (1 << 19U));

    base->BR[index].BR_TRG_SPEED_THR = speed;
    base->BR[index].BR_TRG_SPEED_CFG = MMC_BR_BR_TRG_SPEED_CFG_COMP_TYPE_SET(trig->absolute_compare)
                                    | MMC_BR_BR_TRG_SPEED_CFG_EDGE_SEL_SET(trig->less_than)
                                    | MMC_BR_BR_TRG_SPEED_CFG_EN_SET(trig->enable);
}

void mmc_track_config_position_trig(MMC_Type *base, mmc_pos_trig_t *trig)
{
    base->POS_TRG_POS_THR = trig->position_thr;
    base->POS_TRG_REV_THR = trig->revolution_thr;

    base->POS_TRG_CFG = MMC_POS_TRG_CFG_EDGE_SET(trig->less_than)
                        | MMC_POS_TRG_CFG_EN_SET(trig->enable);
}

void mmc_track_config_speed_trig(MMC_Type *base, mmc_speed_trig_t *trig)
{
    /* speed has 19bit decimal */
    int32_t speed = (int32_t)(trig->speed_thr * (1 << 19U));
    base->SPEED_TRG_THR = speed;
    base->SPEED_TRG_CFG = MMC_SPEED_TRG_CFG_COMP_TYPE_SET(trig->absolute_compare)
                        | MMC_SPEED_TRG_CFG_EDGE_SET(trig->less_than)
                        | MMC_SPEED_TRG_CFG_EN_SET(trig->enable);
}