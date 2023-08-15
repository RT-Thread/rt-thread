/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_soc_feature.h"
#include "hpm_ptpc_drv.h"

#define PTPC_SS_INCR_UINT_AT_BIN_MODE_IN_PS (446U)

void ptpc_get_default_config(PTPC_Type *ptr, ptpc_config_t *config)
{
    config->capture_trigger = ptpc_capture_trigger_none;
    config->ns_rollover_mode = ptpc_ns_counter_rollover_digital;
    config->capture_keep = true;
    config->coarse_increment = false;
    config->src_frequency = 0;
}

hpm_stat_t ptpc_init(PTPC_Type *ptr, uint8_t index, ptpc_config_t *config)
{
    uint8_t ss_incr;
    if (!config || (index > PTPC_SOC_TIMER_MAX_COUNT) || !config->src_frequency) {
        return status_invalid_argument;
    }

    if (config->ns_rollover_mode == ptpc_ns_counter_rollover_digital) {
        ss_incr = 1000000000 / config->src_frequency;
    } else {
        ss_incr = 1000000000 / config->src_frequency * 1000 / PTPC_SS_INCR_UINT_AT_BIN_MODE_IN_PS;
    }
    if (!ss_incr) {
        return status_invalid_argument;
    }
    ptpc_disable_timer(ptr, index);
    ptr->PTPC[index].CTRL0 = PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_SET(config->ns_rollover_mode)
                    | PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_SET(config->capture_keep)
                    | PTPC_PTPC_CTRL0_FINE_COARSE_SEL_SET(config->coarse_increment)
                    | (config->capture_trigger &
                        ((PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_MASK
                          | PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_MASK) >> PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_SHIFT)
                        << PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_SHIFT);
    ptpc_set_ns_counter_step(ptr, index, ss_incr);
    ptpc_enable_timer(ptr, index);
    return status_success;
}

hpm_stat_t ptpc_set_timer_output(PTPC_Type *ptr, uint8_t can_index, bool use_ptpc1)
{
    if (can_index > CAN_SOC_MAX_COUNT) {
        return status_invalid_argument;
    }
    ptr->TIME_SEL = (ptr->TIME_SEL & ~(1 << can_index)) | (use_ptpc1 ? (1 << can_index) : 0);
    return status_success;
}

hpm_stat_t ptpc_set_ns_update(PTPC_Type *ptr, uint8_t index, uint32_t ns, ptpc_counting_mode mode)
{
    if ((PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_GET(ptr->PTPC[index].CTRL0) == ptpc_ns_counter_rollover_digital)
            && (ns > PTPC_MAX_NS_COUNTER)) {
        return status_invalid_argument;
    }
    ptr->PTPC[index].TS_UPDTL = PTPC_PTPC_TS_UPDTL_NS_UPDATE_SET(ns) | PTPC_PTPC_TS_UPDTL_ADD_SUB_SET(mode);
    return status_success;
}

hpm_stat_t ptpc_update_timer(PTPC_Type *ptr, uint8_t index, uint32_t sec, uint32_t ns, ptpc_counting_mode mode)
{
    if (status_success != ptpc_set_ns_update(ptr, index, ns, mode)) {
        return status_invalid_argument;
    }
    ptpc_set_second_update(ptr, index, sec);
    ptr->PTPC[index].CTRL0 |= PTPC_PTPC_CTRL0_UPDATE_TIMER_MASK;
    return status_success;
}

void ptpc_init_timer(PTPC_Type *ptr, uint8_t index)
{
    ptpc_set_second_update(ptr, index, 0);
    ptpc_set_ns_update(ptr, index, 0, ptpc_counting_increment);
    ptr->PTPC[index].CTRL0 |= PTPC_PTPC_CTRL0_INIT_TIMER_MASK;
}

hpm_stat_t ptpc_init_timer_with_initial(PTPC_Type *ptr, uint8_t index, uint32_t sec, uint32_t ns, ptpc_counting_mode mode)
{
    if (status_success != ptpc_set_ns_update(ptr, index, ns, mode)) {
        return status_invalid_argument;
    }
    ptpc_set_second_update(ptr, index, sec);
    ptr->PTPC[index].CTRL0 |= PTPC_PTPC_CTRL0_INIT_TIMER_MASK;
    return status_success;
}

hpm_stat_t ptpc_set_pps(PTPC_Type *ptr, uint8_t index, uint8_t p)
{
    if (p > 15) {
        return status_invalid_argument;
    } else if (p > 0) {
        if (PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_GET(ptr->PTPC[index].CTRL0) == ptpc_ns_counter_rollover_digital) {
            if (p == 15) {
                /* At digital mode, it can only generate interrupt at 16.384 KHz maximum */
                return status_invalid_argument;
            }
        } else {
            if (p == 1) {
                /* At binary mode, it can only generate interrupt at 2 Hz minimum, when p > 0 */
                return status_invalid_argument;
            }
            p--;
        }
    }
    ptr->PTPC[index].PPS_CTRL = PTPC_PTPC_PPS_CTRL_PPS_CTRL_SET(p);
    return status_success;
}


