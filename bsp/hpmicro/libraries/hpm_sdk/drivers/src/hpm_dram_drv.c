/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_dram_drv.h"

#ifndef HPM_DRAM_DRV_DEFAULT_PRESCALER
#define HPM_DRAM_DRV_DEFAULT_PRESCALER (0x3UL)
#endif

#ifndef HPM_DRAM_DRV_RETRY_COUNT
#define HPM_DRAM_DRV_RETRY_COUNT (5000U)
#endif

#define DRAM_PRESCALER_MAX (256UL)

static void dram_config_delay_cell(DRAM_Type *ptr, uint32_t delay_cell_value)
{
    ptr->DLYCFG &= ~DRAM_DLYCFG_OE_MASK;
    ptr->DLYCFG = DRAM_DLYCFG_DLYSEL_SET(delay_cell_value) | DRAM_DLYCFG_DLYEN_MASK;
    ptr->DLYCFG |= DRAM_DLYCFG_OE_MASK;
}

static hpm_stat_t dram_ip_cmd_done(DRAM_Type *ptr)
{
    uint32_t intr_status = 0;
    uint32_t retry = 0;
    do {
        if (retry > HPM_DRAM_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
        intr_status = ptr->INTR
            & (uint32_t)(DRAM_INTR_IPCMDDONE_MASK | DRAM_INTR_IPCMDERR_MASK);
    } while (intr_status == 0);

    if (retry > HPM_DRAM_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    ptr->INTR |= DRAM_INTR_IPCMDDONE_MASK | DRAM_INTR_IPCMDERR_MASK;
    if (intr_status & DRAM_INTR_IPCMDERR_MASK) {
        return status_dram_cmd_err;
    }
    return status_success;
}

static uint32_t dram_make_cmd(uint32_t opcode)
{
    return (opcode & ~DRAM_CMD_WRITE_FLAG) | DRAM_CMD_KEY;
}

static bool dram_is_write_cmd(uint32_t opcode)
{
    return ((opcode & DRAM_CMD_WRITE_FLAG) == DRAM_CMD_WRITE_FLAG);
}

uint32_t dram_issue_ip_cmd(DRAM_Type *ptr, uint32_t base_address, dram_cmd_t *cmd)
{
    bool read_data = !dram_is_write_cmd(cmd->opcode);
    ptr->SADDR = base_address;
    if (!read_data) {
        ptr->IPTX = cmd->data;
    }
    ptr->IPCMD = dram_make_cmd(cmd->opcode);

    if (dram_ip_cmd_done(ptr) < 0) {
        return status_dram_cmd_err;
    }

    if (read_data) {
        cmd->data = ptr->IPRX;
    }
    return status_success;
}

void dram_default_config(DRAM_Type *ptr, dram_config_t *config)
{
    dram_axi_q_weight_t *q;
    config->dqs = DRAM_DQS_FROM_PAD;
    config->cmd_timeout = 0;
    config->bus_timeout = 0x10;
    q = &config->axi_q_weight[DRAM_AXI_Q_A];
    q->enable = true;
    q->qos = 4;
    q->age = 2;
    q->slave_hit = 0x5;
    q->slave_hit_wo_rw = 0x3;

    q = &config->axi_q_weight[DRAM_AXI_Q_B];
    q->enable = true;
    q->qos = 4;
    q->age = 2;
    q->page_hit = 0x5;
    q->slave_hit_wo_rw = 0x3;
    q->bank_rotation = 0x6;
}

void dram_get_typical_sdram_config(DRAM_Type *ptr, dram_sdram_config_t *config)
{
    config->col_addr_bits = DRAM_SDRAM_COLUMN_ADDR_9_BITS;
    config->cas_latency = DRAM_SDRAM_CAS_LATENCY_3;
    config->bank_num = DRAM_SDRAM_BANK_NUM_4;
    config->prescaler = HPM_DRAM_DRV_DEFAULT_PRESCALER;
    config->burst_len_in_byte = 8;
    config->auto_refresh_count_in_one_burst = 1;
    config->precharge_to_act_in_ns = 20;
    config->act_to_rw_in_ns = 20;
    config->refresh_recover_in_ns = 70;
    config->write_recover_in_ns = 12;
    config->cke_off_in_ns = 42;
    config->act_to_precharge_in_ns = 42;

    config->self_refresh_recover_in_ns = 70;
    config->refresh_to_refresh_in_ns = 60;
    config->act_to_act_in_ns = 12;
    config->idle_timeout_in_ns = 6;
    config->cs_mux_pin = DRAM_IO_MUX_NOT_USED;
}

void dram_init(DRAM_Type *ptr, dram_config_t *config)
{
    uint32_t i;
    dram_axi_q_weight_t *q;
    for (i = 0; i < DRAM_BR_COUNT; i++) {
        ptr->BR[i] = 0;
    }

    dram_sw_reset(ptr);
    dram_disable(ptr);
    ptr->CTRL |= DRAM_CTRL_BTO_SET(config->bus_timeout)
        | DRAM_CTRL_CTO_SET(config->cmd_timeout)
        | DRAM_CTRL_DQS_SET(config->dqs);

    q = &config->axi_q_weight[DRAM_AXI_Q_A];
    if (q->enable) {
        ptr->BMW0 = DRAM_BMW0_QOS_SET(q->qos)
            | DRAM_BMW0_AGE_SET(q->age)
            | DRAM_BMW0_SH_SET(q->slave_hit)
            | DRAM_BMW0_RWS_SET(q->slave_hit_wo_rw);
    } else {
        ptr->BMW0 = 0;
    }

    q = &config->axi_q_weight[DRAM_AXI_Q_B];
    if (q->enable) {
        ptr->BMW1 = DRAM_BMW1_QOS_SET(q->qos)
            | DRAM_BMW1_AGE_SET(q->age)
            | DRAM_BMW1_PH_SET(q->page_hit)
            | DRAM_BMW1_BR_SET(q->bank_rotation)
            | DRAM_BMW1_RWS_SET(q->slave_hit_wo_rw);
    } else {
        ptr->BMW1 = 0;
    }

    dram_enable(ptr);
}

static uint8_t dram_convert_actual_size_to_memory_size(uint32_t size_in_kb)
{
    uint8_t size = 0;
    if (size_in_kb == 4) {
        return 0;
    }

    if (size_in_kb > 2 * 1 << 20) {
        return 0x1F;
    }

    size = 1;
    size_in_kb >>= 3;
    while (size_in_kb > 1) {
        size_in_kb >>= 1;
        size++;
    }
    return size;
}

static uint8_t dram_convert_burst_len(uint8_t burst_len_in_byte)
{
    if ((burst_len_in_byte == 0)
            || (burst_len_in_byte > DRAM_SDRAM_MAX_BURST_LENGTH_IN_BYTE)) {
        return DRAM_SDRAM_MAX_BURST_LENGTH_IN_BYTE + 1;
    }

    switch (burst_len_in_byte) {
        case 1:
        case 2:
        case 4:
            return burst_len_in_byte >> 1;
        case 8:
            return (burst_len_in_byte - 1) >> 1;
        default:
            return DRAM_SDRAM_MAX_BURST_LENGTH_IN_BYTE + 1;
    }
}

static uint32_t ns2cycle(uint32_t freq_in_hz, uint32_t ns)
{
    uint32_t ns_per_cycle;
    ns_per_cycle = 1000000000 / freq_in_hz ;
    if (ns < ns_per_cycle) {
        return 1;
    }
    return ns / ns_per_cycle;
}

hpm_stat_t dram_config_sdram(DRAM_Type *ptr, uint32_t clk_in_hz, dram_sdram_config_t *config)
{
    hpm_stat_t err;
    uint32_t prescaler;
    uint32_t refresh_cycle;
    uint32_t clk_in_khz = clk_in_hz / 1000;
    dram_cmd_t cmd = {0};
    uint8_t size = dram_convert_actual_size_to_memory_size(config->size_in_byte >> 10);
    uint8_t burst_len = dram_convert_burst_len(config->burst_len_in_byte);

    prescaler = ((config->prescaler == 0) ? DRAM_PRESCALER_MAX : config->prescaler);
    refresh_cycle = clk_in_khz * config->refresh_in_ms / config->refresh_count / (prescaler << 4);

    if ((prescaler == 0) || (prescaler > DRAM_PRESCALER_MAX)
            || (refresh_cycle == 0) || (refresh_cycle > DRAM_PRESCALER_MAX)) {
        return status_invalid_argument;
    }

    if (prescaler == DRAM_PRESCALER_MAX) {
        prescaler = 0;
    }

    if (refresh_cycle == DRAM_PRESCALER_MAX) {
        refresh_cycle = 0;
    }

    ptr->BR[config->cs] = DRAM_BR_BASE_SET(config->base_address >> DRAM_BR_BASE_SHIFT)
             | DRAM_BR_SIZE_SET(size) | DRAM_BR_VLD_MASK;

    ptr->SDRCTRL0 = DRAM_SDRCTRL0_PORTSZ_SET(config->port_size)
                  | DRAM_SDRCTRL0_BURSTLEN_SET(burst_len)
                  | DRAM_SDRCTRL0_COL_SET(config->col_addr_bits)
                  | DRAM_SDRCTRL0_COL8_SET(config->col_addr_bits == DRAM_SDRAM_COLUMN_ADDR_8_BITS)
                  | DRAM_SDRCTRL0_CAS_SET(config->cas_latency)
                  | DRAM_SDRCTRL0_BANK2_SET(config->bank_num);

    ptr->SDRCTRL1 = DRAM_SDRCTRL1_PRE2ACT_SET(ns2cycle(clk_in_hz, config->precharge_to_act_in_ns))
                  | DRAM_SDRCTRL1_ACT2RW_SET(ns2cycle(clk_in_hz, config->act_to_rw_in_ns))
                  | DRAM_SDRCTRL1_RFRC_SET(ns2cycle(clk_in_hz, config->refresh_recover_in_ns))
                  | DRAM_SDRCTRL1_WRC_SET(ns2cycle(clk_in_hz, config->write_recover_in_ns))
                  | DRAM_SDRCTRL1_CKEOFF_SET(ns2cycle(clk_in_hz, config->cke_off_in_ns))
                  | DRAM_SDRCTRL1_ACT2PRE_SET(ns2cycle(clk_in_hz, config->act_to_precharge_in_ns));

    ptr->SDRCTRL2 = DRAM_SDRCTRL2_SRRC_SET(ns2cycle(clk_in_hz, config->self_refresh_recover_in_ns))
                  | DRAM_SDRCTRL2_REF2REF_SET(ns2cycle(clk_in_hz, config->refresh_to_refresh_in_ns))
                  | DRAM_SDRCTRL2_ACT2ACT_SET(ns2cycle(clk_in_hz, config->act_to_act_in_ns))
                  | DRAM_SDRCTRL2_ITO_SET(ns2cycle(clk_in_hz, config->idle_timeout_in_ns));

    ptr->SDRCTRL3 = DRAM_SDRCTRL3_PRESCALE_SET(prescaler)
                  | DRAM_SDRCTRL3_RT_SET(refresh_cycle)
                  | DRAM_SDRCTRL3_UT_SET(refresh_cycle)
                  | DRAM_SDRCTRL3_REBL_SET(config->auto_refresh_count_in_one_burst - 1);
    /*
     *
     * DATSZ[2:0]: Data size in byte
     *     0b - 4
     *     1b - 1
     *     2b - 2
     *     3b - 3
     *   > 3b - 4
     */
    ptr->DATSZ = DRAM_DATSZ_DATSZ_SET((config->data_width_in_byte & (0x3UL)));
    ptr->BYTEMSK = 0;

    cmd.opcode = DRAM_CMD_SDRAM_PRECHARGE_ALL;
    cmd.data = 0;
    err = dram_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }

    cmd.opcode = DRAM_CMD_SDRAM_AUTO_REFRESH;
    err = dram_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }
    err = dram_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }

    /*
     *
     * DATSZ[2:0]: Data size in byte
     *     0b - 4
     *     1b - 1
     *     2b - 2
     *     3b - 3
     *   > 3b - 4
     */
    ptr->DATSZ = DRAM_DATSZ_DATSZ_SET((config->data_width_in_byte & (0x3UL)));
    ptr->BYTEMSK = 0;

    /*
     * config delay cell
     */
    dram_config_delay_cell(ptr, config->delay_cell_value);

    cmd.opcode = DRAM_CMD_SDRAM_PRECHARGE_ALL;
    cmd.data = 0;
    err = dram_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }

    cmd.opcode = DRAM_CMD_SDRAM_AUTO_REFRESH;
    err = dram_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }
    err = dram_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }

    cmd.opcode = DRAM_CMD_SDRAM_MODE_SET;
    /* FIXME: the mode register layout definition better to be passed in? */
    cmd.data = (uint32_t)(burst_len | config->cas_latency << 4);
    err = dram_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }
    ptr->SDRCTRL3 |= DRAM_SDRCTRL3_REN_MASK;

    return status_success;
}

