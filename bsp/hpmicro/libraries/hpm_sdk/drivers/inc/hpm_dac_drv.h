/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_DAC_DRV_H
#define HPM_DAC_DRV_H

#include "hpm_common.h"
#include "hpm_dac_regs.h"
#include "hpm_soc_feature.h"

/* The range of DAC output value setting is from 0.0 to 10000.0, which is mapped to 0 to 100 in percentage. */
#define DAC_OUTPUT(PERCENT) (PERCENT / 10000.0f * DAC_SOC_MAX_DATA)

#define DAC_AHB_ERROR_EVENT     DAC_IRQ_EN_AHB_ERROR_MASK
#define DAC_FIFO_EMPTY_EVENT    DAC_IRQ_EN_FIFO_EMPTY_MASK
#define DAC_BUF1_COMPLETE_EVENT DAC_IRQ_EN_BUF1_CMPT_MASK
#define DAC_BUF0_COMPLETE_EVENT DAC_IRQ_EN_BUF0_CMPT_MASK


typedef enum {
    dac_mode_direct = 0,
    dac_mode_step,
    dac_mode_buffer,
    dac_mode_trig
} dac_mode_t;

typedef enum {
    dac_ana_div_2 = 0,
    dac_ana_div_4,
    dac_ana_div_6,
    dac_ana_div_8
} dac_ana_div_t;

typedef struct {
    bool sync_mode;
    uint8_t dac_mode;
    uint8_t ana_div;
} dac_config_t;

typedef enum {
    dac_step_up = 0,
    dac_step_down
} dac_step_direction_t;

typedef enum {
    dac_round_mode_oneshot = 0,
    dac_round_mode_loop
} dac_round_mode_t;

typedef struct {
    uint16_t start_point;
    uint16_t end_point;
    uint8_t round_mode;
    uint8_t up_down;
    uint8_t step_num;
} dac_step_config_t;

typedef enum {
    dac_data_stru_2_point = 0,
    dac_data_stru_1_point
} dac_data_structure_t;

typedef enum {
    dac_burst_single = 0,
    dac_burst_incr4  = 3,
    dac_burst_incr8  = 5
} dac_burst_type_t;

typedef struct {
    uint32_t start_addr;
    uint8_t stop;
    uint16_t len;
} dac_buffer_t;

typedef struct {
    uint8_t buf_data_mode;
    uint8_t burst;
    dac_buffer_t buf0;
    dac_buffer_t buf1;
} dac_buffer_config_t;

#ifdef __cplusplus
extern "C" {
#endif

void dac_get_default_config(dac_config_t *config);
hpm_stat_t dac_init(DAC_Type *ptr, dac_config_t *config);
hpm_stat_t dac_set_direct_config(DAC_Type *ptr, uint16_t data);
hpm_stat_t dac_set_step_config(DAC_Type *ptr, uint8_t step_cfg_idx, dac_step_config_t *config);
hpm_stat_t dac_set_buffer_config(DAC_Type *ptr, dac_buffer_config_t *config);
hpm_stat_t dac_set_output_frequency(DAC_Type *ptr, uint32_t dac_input_freq, uint32_t dac_output_freq);
hpm_stat_t dac_set_step_sw_trigger(DAC_Type *ptr, uint8_t step_sw_trig_idx);
void dac_set_buffer_sw_trigger(DAC_Type *ptr);
void dac_set_hw_trigger_enable(DAC_Type *ptr, bool enable);
hpm_stat_t dac_external_dma_request_enable(DAC_Type *ptr, uint8_t buf_idx, bool enable);
void dac_set_buffer_dma_reset(DAC_Type *ptr);
void dac_enable_conversion(DAC_Type *ptr, bool enable);
void dac_enable_interrupts(DAC_Type *ptr, uint32_t mask);
uint32_t dac_get_status_flags(DAC_Type *ptr);
void dac_set_status_flags(DAC_Type *ptr, uint32_t mask);
uint8_t dac_get_current_buffer_index(DAC_Type *ptr);
uint16_t dac_get_current_buffer_offset(DAC_Type *ptr);

#ifdef __cplusplus
}
#endif

#endif
