/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_ppi_drv.h"

void ppi_config_clk_pin(PPI_Type *ppi, ppi_clk_pin_config_t *config)
{
    uint32_t tmp;

    tmp = PPI_CLKPIN_CFG_CYCLE_SET(config->cycle_num)
        | PPI_CLKPIN_CFG_HIGH_SET(config->high_num)
        | PPI_CLKPIN_CFG_LOW_SET(config->low_num)
        | PPI_CLKPIN_CFG_INVERT_SET(config->revert)
        | PPI_CLKPIN_CFG_AON_SET(config->mode)
        | PPI_CLKPIN_CFG_EN_MASK;

    ppi->CLKPIN_CFG = tmp;
}

void ppi_config_cs_pin(PPI_Type *ppi, uint8_t index, ppi_cs_pin_config_t *config)
{
    uint32_t tmp;
    uint8_t shift;

    assert(index < 4);
    assert((config->addr_start_high_12bits >= 0xF80) && (config->addr_start_high_12bits <= 0xFFF));
    assert((config->addr_end_high_12bits >= 0xF80) && (config->addr_end_high_12bits <= 0xFFF));

    tmp = PPI_CS_CFG0_ADDR_START_SET(config->addr_start_high_12bits) | PPI_CS_CFG0_ADDR_END_SET(config->addr_end_high_12bits);
    ppi->CS[index].CFG0 = tmp;

    if (config->port_size == ppi_port_size_16bits) {
        shift = 1;
    } else if (config->port_size == ppi_port_size_32bits) {
        shift = 2;
    } else {
        shift = 0;
    }
    tmp = PPI_CS_CFG1_ADDR_MASK_SET(config->addr_mask) | PPI_CS_CFG1_ADDR_SHIFT_SET(shift);
    ppi->CS[index].CFG1 = tmp;

    tmp = PPI_CS_CFG3_RCMD_END1_SET(config->rcmd_end1)
        | PPI_CS_CFG3_RCMD_START1_SET(config->rcmd_start1)
        | PPI_CS_CFG3_RCMD_END0_SET(config->rcmd_end0)
        | PPI_CS_CFG3_RCMD_START0_SET(config->rcmd_start0);
    ppi->CS[index].CFG3 = tmp;

    tmp = PPI_CS_CFG4_WCMD_END1_SET(config->wcmd_end1)
        | PPI_CS_CFG4_WCMD_START1_SET(config->wcmd_start1)
        | PPI_CS_CFG4_WCMD_END0_SET(config->wcmd_end0)
        | PPI_CS_CFG4_WCMD_START0_SET(config->wcmd_start0);
    ppi->CS[index].CFG4 = tmp;

    tmp = PPI_CS_CFG2_CS_SYNC_EN_SET(config->sync_clk_en)
        | PPI_CS_CFG2_SYNC_CLK_SEL_SET(config->sync_clk_sel)
        | PPI_CS_CFG2_INTER_CMD_DLY_SET(config->interval_cycle)
#if defined(HPM_IP_FEATURE_PPI_DM_POLARITY_EACH_CS) && HPM_IP_FEATURE_PPI_DM_POLARITY_EACH_CS
        | PPI_CS_CFG2_DM_POLARITY_SET(config->dm_polarity)
#endif
        | PPI_CS_CFG2_PORT_SIZE_SET(config->port_size)
        | PPI_CS_CFG2_ENABLE_MASK;
    ppi->CS[index].CFG2 = tmp;
}

void ppi_config_cmd(PPI_Type *ppi, uint8_t index, ppi_cmd_config_t *config)
{
    uint32_t tmp;

    assert(index < 64);

    tmp = PPI_CMD_CMD_CFG_CS_VAL_SET(config->cs_pin_value)
        | PPI_CMD_CMD_CFG_CLK_GATE_SET(config->clk_output)
        | PPI_CMD_CMD_CFG_CYCLE_NUM_SET(config->cmd_cycle);
    ppi->CMD[index].CMD_CFG = tmp;

    tmp = PPI_CMD_AD_CFG_DIR3_SET(config->ad_pin_dir[3])
        | PPI_CMD_AD_CFG_AD_SEL3_SET(config->ad_func_sel[3])
        | PPI_CMD_AD_CFG_BYTE_SEL3_SET(config->byte_sel[3])
        | PPI_CMD_AD_CFG_DIR2_SET(config->ad_pin_dir[2])
        | PPI_CMD_AD_CFG_AD_SEL2_SET(config->ad_func_sel[2])
        | PPI_CMD_AD_CFG_BYTE_SEL2_SET(config->byte_sel[2])
        | PPI_CMD_AD_CFG_DIR1_SET(config->ad_pin_dir[1])
        | PPI_CMD_AD_CFG_AD_SEL1_SET(config->ad_func_sel[1])
        | PPI_CMD_AD_CFG_BYTE_SEL1_SET(config->byte_sel[1])
        | PPI_CMD_AD_CFG_DIR0_SET(config->ad_pin_dir[0])
        | PPI_CMD_AD_CFG_AD_SEL0_SET(config->ad_func_sel[0])
        | PPI_CMD_AD_CFG_BYTE_SEL0_SET(config->byte_sel[0]);
    ppi->CMD[index].AD_CFG = tmp;

    tmp = PPI_CMD_CTRL_CFG_IO_CFG7_SET(config->ctrl_pin_value[7])
        | PPI_CMD_CTRL_CFG_IO_CFG6_SET(config->ctrl_pin_value[6])
        | PPI_CMD_CTRL_CFG_IO_CFG5_SET(config->ctrl_pin_value[5])
        | PPI_CMD_CTRL_CFG_IO_CFG4_SET(config->ctrl_pin_value[4])
        | PPI_CMD_CTRL_CFG_IO_CFG3_SET(config->ctrl_pin_value[3])
        | PPI_CMD_CTRL_CFG_IO_CFG2_SET(config->ctrl_pin_value[2])
        | PPI_CMD_CTRL_CFG_IO_CFG1_SET(config->ctrl_pin_value[1])
        | PPI_CMD_CTRL_CFG_IO_CFG0_SET(config->ctrl_pin_value[0]);
    ppi->CMD[index].CTRL_CFG = tmp;
}
