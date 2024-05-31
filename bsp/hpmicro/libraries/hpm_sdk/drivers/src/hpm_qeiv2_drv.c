/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_qeiv2_drv.h"
#include "hpm_enc_pos_drv.h"

hpm_stat_t qeiv2_config_phcnt_cmp_match_condition(QEIV2_Type *qeiv2_x, qeiv2_phcnt_cmp_match_config_t *config)
{
    if (qeiv2_check_spd_tmr_as_pos_angle(qeiv2_x)) {
        return status_fail;
    }
    qeiv2_set_phcnt_cmp_value(qeiv2_x, config->phcnt_cmp_value);
    qeiv2_set_spd_pos_cmp_value(qeiv2_x, 0);
    qeiv2_set_z_cmp_value(qeiv2_x, config->zcmp_value);
    qeiv2_set_cmp_match_option(qeiv2_x, config->ignore_zcmp, false, false, config->ignore_rotate_dir, config->rotate_dir, true, qeiv2_pos_dir_decrease);
    return status_success;
}

hpm_stat_t qeiv2_config_position_cmp_match_condition(QEIV2_Type *qeiv2_x, qeiv2_pos_cmp_match_config_t *config)
{
    if (!qeiv2_check_spd_tmr_as_pos_angle(qeiv2_x)) {
        return status_fail;
    }
    qeiv2_set_spd_pos_cmp_value(qeiv2_x, config->pos_cmp_value);
    qeiv2_set_cmp_match_option(qeiv2_x, true, true, false, true, qeiv2_rotate_dir_forward, config->ignore_pos_dir, config->pos_dir);
    return status_success;
}

hpm_stat_t qeiv2_config_phcnt_cmp2_match_condition(QEIV2_Type *qeiv2_x, qeiv2_phcnt_cmp_match_config_t *config)
{
    if (qeiv2_check_spd_tmr_as_pos_angle(qeiv2_x)) {
        return status_fail;
    }
    qeiv2_set_phcnt_cmp2_value(qeiv2_x, config->phcnt_cmp_value);
    qeiv2_set_spd_pos_cmp2_value(qeiv2_x, 0);
    qeiv2_set_z_cmp2_value(qeiv2_x, config->zcmp_value);
    qeiv2_set_cmp2_match_option(qeiv2_x, config->ignore_zcmp, false, false, config->ignore_rotate_dir, config->rotate_dir, true, qeiv2_pos_dir_decrease);
    return status_success;
}

hpm_stat_t qeiv2_config_position_cmp2_match_condition(QEIV2_Type *qeiv2_x, qeiv2_pos_cmp_match_config_t *config)
{
    if (!qeiv2_check_spd_tmr_as_pos_angle(qeiv2_x)) {
        return status_fail;
    }
    qeiv2_set_spd_pos_cmp2_value(qeiv2_x, config->pos_cmp_value);
    qeiv2_set_cmp2_match_option(qeiv2_x, true, true, false, true, qeiv2_rotate_dir_forward, config->ignore_pos_dir, config->pos_dir);
    return status_success;
}

void qeiv2_get_uvw_position_defconfig(qeiv2_uvw_config_t *config)
{
    config->pos_opt = qeiv2_uvw_pos_opt_current;

    config->u_pos_sel[0] = qeiv2_uvw_pos_sel_high;
    config->v_pos_sel[0] = qeiv2_uvw_pos_sel_low;
    config->w_pos_sel[0] = qeiv2_uvw_pos_sel_high;

    config->u_pos_sel[1] = qeiv2_uvw_pos_sel_high;
    config->v_pos_sel[1] = qeiv2_uvw_pos_sel_low;
    config->w_pos_sel[1] = qeiv2_uvw_pos_sel_low;

    config->u_pos_sel[2] = qeiv2_uvw_pos_sel_high;
    config->v_pos_sel[2] = qeiv2_uvw_pos_sel_high;
    config->w_pos_sel[2] = qeiv2_uvw_pos_sel_low;

    config->u_pos_sel[3] = qeiv2_uvw_pos_sel_low;
    config->v_pos_sel[3] = qeiv2_uvw_pos_sel_high;
    config->w_pos_sel[3] = qeiv2_uvw_pos_sel_low;

    config->u_pos_sel[4] = qeiv2_uvw_pos_sel_low;
    config->v_pos_sel[4] = qeiv2_uvw_pos_sel_high;
    config->w_pos_sel[4] = qeiv2_uvw_pos_sel_high;

    config->u_pos_sel[5] = qeiv2_uvw_pos_sel_low;
    config->v_pos_sel[5] = qeiv2_uvw_pos_sel_low;
    config->w_pos_sel[5] = qeiv2_uvw_pos_sel_high;

    config->pos_cfg[0] = encoder_deg_to_position(30);
    config->pos_cfg[1] = encoder_deg_to_position(90);
    config->pos_cfg[2] = encoder_deg_to_position(150);
    config->pos_cfg[3] = encoder_deg_to_position(210);
    config->pos_cfg[4] = encoder_deg_to_position(270);
    config->pos_cfg[5] = encoder_deg_to_position(330);
}

hpm_stat_t qeiv2_config_uvw_position(QEIV2_Type *qeiv2_x, qeiv2_uvw_config_t *config)
{
    qeiv2_set_uvw_position_opt(qeiv2_x, config->pos_opt);
    for (uint8_t i = 0; i < 6; i++) {
        if (config->pos_opt == qeiv2_uvw_pos_opt_next) {
            if ((config->u_pos_sel[i] == qeiv2_uvw_pos_sel_edge)
             || (config->v_pos_sel[i] == qeiv2_uvw_pos_sel_edge)
             || (config->w_pos_sel[i] == qeiv2_uvw_pos_sel_edge)) {
                return status_invalid_argument;
            }
        }
    }

    for (uint8_t i = 0; i < 6; i++) {
        if (config->pos_opt == qeiv2_uvw_pos_opt_next) {
            qeiv2_set_uvw_position_sel(qeiv2_x, i,
                    (config->u_pos_sel[i] == qeiv2_uvw_pos_sel_high) ? QEIV2_UVW_POS_OPT_NEX_SEL_HIGH : QEIV2_UVW_POS_OPT_NEX_SEL_LOW,
                    (config->v_pos_sel[i] == qeiv2_uvw_pos_sel_high) ? QEIV2_UVW_POS_OPT_NEX_SEL_HIGH : QEIV2_UVW_POS_OPT_NEX_SEL_LOW,
                    (config->w_pos_sel[i] == qeiv2_uvw_pos_sel_high) ? QEIV2_UVW_POS_OPT_NEX_SEL_HIGH : QEIV2_UVW_POS_OPT_NEX_SEL_LOW,
                    true);
        } else {
            qeiv2_set_uvw_position_sel(qeiv2_x, i, config->u_pos_sel[i], config->v_pos_sel[i], config->w_pos_sel[i], true);
        }
        qeiv2_set_uvw_position(qeiv2_x, i, config->pos_cfg[i]);
    }

    return status_success;
}

void qeiv2_config_filter(QEIV2_Type *qeiv2_x, qeiv2_filter_phase_t phase, bool outinv, qeiv2_filter_mode_t mode, bool sync, uint32_t filtlen)
{
    uint32_t len = filtlen;
    uint8_t shift;
    for (shift = 0; shift <= 7u; shift++) {
        if (shift > 0) {
            len >>= 1u;
        }
        if (len <= 0x1FFu) {
            break;
        }
    }
    if (len > 0x1FFu) {
        len = 0x1FFu;
        shift = 7u;
    }

    qeiv2_x->FILT_CFG[phase] =
        QEIV2_FILT_CFG_OUTINV_SET(outinv) | QEIV2_FILT_CFG_MODE_SET(mode) | QEIV2_FILT_CFG_SYNCEN_SET(sync) | QEIV2_FILT_CFG_FILTLEN_SET(((shift << 9u) | len));
}
