/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_femc_drv.h"

#ifndef HPM_FEMC_DRV_DEFAULT_PRESCALER
#define HPM_FEMC_DRV_DEFAULT_PRESCALER (0x3UL)
#endif

#ifndef HPM_FEMC_DRV_RETRY_COUNT
#define HPM_FEMC_DRV_RETRY_COUNT (5000U)
#endif

#define FEMC_PRESCALER_MAX (256UL)

static void femc_config_delay_cell(FEMC_Type *ptr, bool delay_cell_en, uint32_t delay_cell_value)
{
    ptr->DLYCFG &= ~FEMC_DLYCFG_OE_MASK;
    ptr->DLYCFG = FEMC_DLYCFG_DLYSEL_SET(delay_cell_value) | FEMC_DLYCFG_DLYEN_SET(delay_cell_en);
    ptr->DLYCFG |= FEMC_DLYCFG_OE_MASK;
}

static hpm_stat_t femc_ip_cmd_done(FEMC_Type *ptr)
{
    uint32_t intr_status = 0;
    uint32_t retry = 0;
    do {
        if (retry > HPM_FEMC_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
        intr_status = ptr->INTR
            & (uint32_t)(FEMC_INTR_IPCMDDONE_MASK | FEMC_INTR_IPCMDERR_MASK);
    } while (intr_status == 0);

    if (retry > HPM_FEMC_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    ptr->INTR |= FEMC_INTR_IPCMDDONE_MASK | FEMC_INTR_IPCMDERR_MASK;
    if (intr_status & FEMC_INTR_IPCMDERR_MASK) {
        return status_femc_cmd_err;
    }
    return status_success;
}

static uint32_t femc_make_cmd(uint32_t opcode)
{
    return (opcode & ~FEMC_CMD_WRITE_FLAG) | FEMC_CMD_KEY;
}

static bool femc_is_write_cmd(uint32_t opcode)
{
    return ((opcode & FEMC_CMD_WRITE_FLAG) == FEMC_CMD_WRITE_FLAG);
}

uint32_t femc_issue_ip_cmd(FEMC_Type *ptr, uint32_t base_address, femc_cmd_t *cmd)
{
    bool read_data = !femc_is_write_cmd(cmd->opcode);
    ptr->SADDR = base_address;
    if (!read_data) {
        ptr->IPTX = cmd->data;
    }
    ptr->IPCMD = femc_make_cmd(cmd->opcode);

    if (femc_ip_cmd_done(ptr) != status_success) {
        return status_femc_cmd_err;
    }

    if (read_data) {
        cmd->data = ptr->IPRX;
    }
    return status_success;
}

void femc_default_config(FEMC_Type *ptr, femc_config_t *config)
{
    (void) ptr;
    femc_axi_q_weight_t *q;
    config->dqs = FEMC_DQS_FROM_PAD;
    config->cmd_timeout = 0;
    config->bus_timeout = 0x10;
    q = &config->axi_q_weight[FEMC_AXI_Q_A];
    q->enable = true;
    q->qos = 4;
    q->age = 2;
    q->slave_hit = 0x5;
    q->slave_hit_wo_rw = 0x3;

    q = &config->axi_q_weight[FEMC_AXI_Q_B];
    q->enable = true;
    q->qos = 4;
    q->age = 2;
    q->page_hit = 0x5;
    q->slave_hit_wo_rw = 0x3;
    q->bank_rotation = 0x6;
}

void femc_get_typical_sdram_config(FEMC_Type *ptr, femc_sdram_config_t *config)
{
    (void) ptr;
    config->col_addr_bits = FEMC_SDRAM_COLUMN_ADDR_9_BITS;
    config->cas_latency = FEMC_SDRAM_CAS_LATENCY_3;
    config->bank_num = FEMC_SDRAM_BANK_NUM_4;
    config->prescaler = HPM_FEMC_DRV_DEFAULT_PRESCALER;
    config->burst_len_in_byte = 8;
    config->auto_refresh_count_in_one_burst = 1;
    config->precharge_to_act_in_ns = 18;
    config->act_to_rw_in_ns = 18;
    config->refresh_recover_in_ns = 60;
    config->write_recover_in_ns = 12;
    config->cke_off_in_ns = 42;
    config->act_to_precharge_in_ns = 42;

    config->self_refresh_recover_in_ns = 72;
    config->refresh_to_refresh_in_ns = 60;
    config->act_to_act_in_ns = 12;
    config->idle_timeout_in_ns = 6;
    config->cs_mux_pin = FEMC_IO_MUX_NOT_USED;

    config->cmd_data_width = 4;
}

void femc_init(FEMC_Type *ptr, femc_config_t *config)
{
    uint32_t i;
    femc_axi_q_weight_t *q;
    for (i = 0; i < FEMC_BR_COUNT; i++) {
        ptr->BR[i] = 0;
    }

    femc_sw_reset(ptr);
    femc_disable(ptr);
    ptr->CTRL |= FEMC_CTRL_BTO_SET(config->bus_timeout)
        | FEMC_CTRL_CTO_SET(config->cmd_timeout)
        | FEMC_CTRL_DQS_SET(config->dqs);

    q = &config->axi_q_weight[FEMC_AXI_Q_A];
    if (q->enable) {
        ptr->BMW0 = FEMC_BMW0_QOS_SET(q->qos)
            | FEMC_BMW0_AGE_SET(q->age)
            | FEMC_BMW0_SH_SET(q->slave_hit)
            | FEMC_BMW0_RWS_SET(q->slave_hit_wo_rw);
    } else {
        ptr->BMW0 = 0;
    }

    q = &config->axi_q_weight[FEMC_AXI_Q_B];
    if (q->enable) {
        ptr->BMW1 = FEMC_BMW1_QOS_SET(q->qos)
            | FEMC_BMW1_AGE_SET(q->age)
            | FEMC_BMW1_PH_SET(q->page_hit)
            | FEMC_BMW1_BR_SET(q->bank_rotation)
            | FEMC_BMW1_RWS_SET(q->slave_hit_wo_rw);
    } else {
        ptr->BMW1 = 0;
    }

    femc_enable(ptr);
}

static uint8_t femc_convert_actual_size_to_memory_size(uint32_t size_in_kb)
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

static uint8_t femc_convert_burst_len(uint8_t burst_len_in_byte)
{
    if ((burst_len_in_byte == 0)
            || (burst_len_in_byte > FEMC_SDRAM_MAX_BURST_LENGTH_IN_BYTE)) {
        return FEMC_SDRAM_MAX_BURST_LENGTH_IN_BYTE + 1;
    }

    switch (burst_len_in_byte) {
    case 1:
    case 2:
    case 4:
        return burst_len_in_byte >> 1;
    case 8:
        return (burst_len_in_byte - 1) >> 1;
    default:
        return FEMC_SDRAM_MAX_BURST_LENGTH_IN_BYTE + 1;
    }
}

static uint32_t ns2cycle(uint32_t freq_in_hz, uint32_t ns, uint32_t max_cycle)
{
    uint32_t ns_per_cycle;
    uint32_t cycle;

    ns_per_cycle = 1000000000 / freq_in_hz;
    cycle = ns / ns_per_cycle;
    if (cycle > max_cycle) {
        cycle = max_cycle;
    }
    return cycle;
}

hpm_stat_t femc_config_sdram(FEMC_Type *ptr, uint32_t clk_in_hz, femc_sdram_config_t *config)
{
    hpm_stat_t err;
    uint32_t prescaler;
    uint32_t refresh_cycle;
    uint32_t clk_in_khz = clk_in_hz / 1000;
    femc_cmd_t cmd = {0};
    uint8_t size = femc_convert_actual_size_to_memory_size(config->size_in_byte >> 10);
    uint8_t burst_len = femc_convert_burst_len(config->burst_len_in_byte);

    prescaler = ((config->prescaler == 0) ? FEMC_PRESCALER_MAX : config->prescaler);
    refresh_cycle = clk_in_khz * config->refresh_in_ms / config->refresh_count / (prescaler << 4);

    if ((prescaler == 0) || (prescaler > FEMC_PRESCALER_MAX)
            || (refresh_cycle == 0) || (refresh_cycle > FEMC_PRESCALER_MAX)) {
        return status_invalid_argument;
    }

    if (prescaler == FEMC_PRESCALER_MAX) {
        prescaler = 0;
    }

    if (refresh_cycle == FEMC_PRESCALER_MAX) {
        refresh_cycle = 0;
    }

    ptr->BR[config->cs] = FEMC_BR_BASE_SET(config->base_address >> FEMC_BR_BASE_SHIFT)
                        | FEMC_BR_SIZE_SET(size) | FEMC_BR_VLD_MASK;

    ptr->SDRCTRL0 = FEMC_SDRCTRL0_PORTSZ_SET(config->port_size)
                  | FEMC_SDRCTRL0_BURSTLEN_SET(burst_len)
                  | FEMC_SDRCTRL0_COL_SET(config->col_addr_bits)
                  | FEMC_SDRCTRL0_COL8_SET(config->col_addr_bits == FEMC_SDRAM_COLUMN_ADDR_8_BITS)
                  | FEMC_SDRCTRL0_CAS_SET(config->cas_latency)
                  | FEMC_SDRCTRL0_BANK2_SET(config->bank_num);

    ptr->SDRCTRL1 = FEMC_SDRCTRL1_PRE2ACT_SET(ns2cycle(clk_in_hz, config->precharge_to_act_in_ns, FEMC_SDRCTRL1_PRE2ACT_MASK >> FEMC_SDRCTRL1_PRE2ACT_SHIFT))
                  | FEMC_SDRCTRL1_ACT2RW_SET(ns2cycle(clk_in_hz, config->act_to_rw_in_ns, FEMC_SDRCTRL1_ACT2RW_MASK >> FEMC_SDRCTRL1_ACT2RW_SHIFT))
                  | FEMC_SDRCTRL1_RFRC_SET(ns2cycle(clk_in_hz, config->refresh_recover_in_ns, FEMC_SDRCTRL1_RFRC_MASK >> FEMC_SDRCTRL1_RFRC_SHIFT))
                  | FEMC_SDRCTRL1_WRC_SET(ns2cycle(clk_in_hz, config->write_recover_in_ns, FEMC_SDRCTRL1_WRC_MASK >> FEMC_SDRCTRL1_WRC_SHIFT))
                  | FEMC_SDRCTRL1_CKEOFF_SET(ns2cycle(clk_in_hz, config->cke_off_in_ns, FEMC_SDRCTRL1_CKEOFF_MASK >> FEMC_SDRCTRL1_CKEOFF_SHIFT))
                  | FEMC_SDRCTRL1_ACT2PRE_SET(ns2cycle(clk_in_hz, config->act_to_precharge_in_ns, FEMC_SDRCTRL1_ACT2PRE_MASK >> FEMC_SDRCTRL1_ACT2PRE_SHIFT));

    ptr->SDRCTRL2 = FEMC_SDRCTRL2_SRRC_SET(ns2cycle(clk_in_hz, config->self_refresh_recover_in_ns, FEMC_SDRCTRL2_SRRC_MASK >> FEMC_SDRCTRL2_SRRC_SHIFT))
                  | FEMC_SDRCTRL2_REF2REF_SET(ns2cycle(clk_in_hz, config->refresh_to_refresh_in_ns, FEMC_SDRCTRL2_REF2REF_MASK >> FEMC_SDRCTRL2_REF2REF_SHIFT))
                  | FEMC_SDRCTRL2_ACT2ACT_SET(ns2cycle(clk_in_hz, config->act_to_act_in_ns, FEMC_SDRCTRL2_ACT2ACT_MASK >> FEMC_SDRCTRL2_ACT2ACT_SHIFT))
                  | FEMC_SDRCTRL2_ITO_SET(ns2cycle(clk_in_hz, config->idle_timeout_in_ns, FEMC_SDRCTRL2_ITO_MASK >> FEMC_SDRCTRL2_ITO_SHIFT));

    ptr->SDRCTRL3 = FEMC_SDRCTRL3_PRESCALE_SET(prescaler)
                  | FEMC_SDRCTRL3_RT_SET(refresh_cycle)
                  | FEMC_SDRCTRL3_UT_SET(refresh_cycle)
                  | FEMC_SDRCTRL3_REBL_SET(config->auto_refresh_count_in_one_burst - 1);

    /*
     * config delay cell
     */
    femc_config_delay_cell(ptr, !config->delay_cell_disable, config->delay_cell_value);

    /*
     *
     * DATSZ[2:0]: Data size in byte
     *     0b - 4
     *     1b - 1
     *     2b - 2
     *     3b - 3
     *   > 3b - 4
     */
    ptr->DATSZ = FEMC_DATSZ_DATSZ_SET((config->cmd_data_width & (0x3UL)));
    ptr->BYTEMSK = 0;

    cmd.opcode = FEMC_CMD_SDRAM_PRECHARGE_ALL;
    cmd.data = 0;
    err = femc_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }

    cmd.opcode = FEMC_CMD_SDRAM_AUTO_REFRESH;
    err = femc_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }
    err = femc_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }

    cmd.opcode = FEMC_CMD_SDRAM_MODE_SET;
    /* FIXME: the mode register layout definition better to be passed in? */
    cmd.data = (uint32_t)(burst_len | config->cas_latency << 4);
    err = femc_issue_ip_cmd(ptr, config->base_address, &cmd);
    if (status_success != err) {
        return err;
    }
    ptr->SDRCTRL3 |= FEMC_SDRCTRL3_REN_MASK;

    return status_success;
}

void femc_get_typical_sram_config(FEMC_Type *ptr, femc_sram_config_t *config)
{
    (void) ptr;
    config->base_address = 0x48000000;
    config->size_in_byte = 4096;
    config->address_mode = FEMC_SRAM_AD_NONMUX_MODE;
    config->port_size = FEMC_SRAM_PORT_SIZE_8_BITS;
    config->adv_hold_state = FEMC_SRAM_ADV_HOLD_LOW;
    config->adv_polarity = FEMC_SRAM_ADV_ACTIVE_HIGH;
    config->oeh_in_ns = 0;
    config->oel_in_ns = 50;
    config->weh_in_ns = 0;
    config->wel_in_ns = 50;
    config->ah_in_ns = 50;
    config->as_in_ns = 0;
    config->ceh_in_ns = 0;
    config->ces_in_ns = 0;
}

hpm_stat_t femc_config_sram(FEMC_Type *ptr, uint32_t clk_in_hz, femc_sram_config_t *config)
{
    uint8_t size = femc_convert_actual_size_to_memory_size(config->size_in_byte >> 10);

    ptr->IOCTRL = FEMC_IOCTRL_IO_CSX_SET(FEMC_IO_CSX_SRAM_CE);

    ptr->BR[FEMC_BR_BASE6] = FEMC_BR_BASE_SET(config->base_address >> FEMC_BR_BASE_SHIFT)
                           | FEMC_BR_SIZE_SET(size)
                           | FEMC_BR_VLD_MASK;

    ptr->SRCTRL0 = FEMC_SRCTRL0_ADVH_SET(config->adv_hold_state)
                 | FEMC_SRCTRL0_ADVP_SET(config->adv_polarity)
                 | FEMC_SRCTRL0_ADM_SET(config->address_mode)
                 | FEMC_SRCTRL0_PORTSZ_SET(config->port_size);

    ptr->SRCTRL1 = FEMC_SRCTRL1_OEH_SET(ns2cycle(clk_in_hz, config->oeh_in_ns, FEMC_SRCTRL1_OEH_MASK >> FEMC_SRCTRL1_OEH_SHIFT))
                 | FEMC_SRCTRL1_OEL_SET(ns2cycle(clk_in_hz, config->oel_in_ns, FEMC_SRCTRL1_OEL_MASK >> FEMC_SRCTRL1_OEL_SHIFT))
                 | FEMC_SRCTRL1_WEH_SET(ns2cycle(clk_in_hz, config->weh_in_ns, FEMC_SRCTRL1_WEH_MASK >> FEMC_SRCTRL1_WEH_SHIFT))
                 | FEMC_SRCTRL1_WEL_SET(ns2cycle(clk_in_hz, config->wel_in_ns, FEMC_SRCTRL1_WEL_MASK >> FEMC_SRCTRL1_WEL_SHIFT))
                 | FEMC_SRCTRL1_AH_SET(ns2cycle(clk_in_hz, config->ah_in_ns, FEMC_SRCTRL1_AH_MASK >> FEMC_SRCTRL1_AH_SHIFT))
                 | FEMC_SRCTRL1_AS_SET(ns2cycle(clk_in_hz, config->as_in_ns, FEMC_SRCTRL1_AS_MASK >> FEMC_SRCTRL1_AS_SHIFT))
                 | FEMC_SRCTRL1_CEH_SET(ns2cycle(clk_in_hz, config->ceh_in_ns, FEMC_SRCTRL1_CEH_MASK >> FEMC_SRCTRL1_CEH_SHIFT))
                 | FEMC_SRCTRL1_CES_SET(ns2cycle(clk_in_hz, config->ces_in_ns, FEMC_SRCTRL1_CES_MASK >> FEMC_SRCTRL1_CES_SHIFT));

    return status_success;
}
