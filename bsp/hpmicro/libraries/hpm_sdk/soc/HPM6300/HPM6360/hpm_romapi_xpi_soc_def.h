/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_ROMAPI_XPI_SOC_DEF_H
#define HPM_ROMAPI_XPI_SOC_DEF_H

#include "hpm_common.h"
#include "hpm_romapi_xpi_def.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

#define XPI_CLK_OUT_FREQ_OPTION_30MHz (1U)
#define XPI_CLK_OUT_FREQ_OPTION_50MHz (2U)
#define XPI_CLK_OUT_FREQ_OPTION_66MHz (3U)
#define XPI_CLK_OUT_FREQ_OPTION_80MHz (4U)
#define XPI_CLK_OUT_FREQ_OPTION_104MHz (5U)
#define XPI_CLK_OUT_FREQ_OPTION_120MHz (6U)
#define XPI_CLK_OUT_FREQ_OPTION_133MHz (7U)
#define XPI_CLK_OUT_FREQ_OPTION_166MHz (8U)
#define XPI_CLK_OUT_FREQ_OPTION_200MHz (9U)

typedef struct {
    struct {
        uint8_t priority;                   /* Offset: 0x00 */
        uint8_t master_idx;                 /* Offset: 0x01 */
        uint8_t buf_size_in_dword;          /* Offset: 0x02 */
        bool enable_prefetch;               /* Offset: 0x03 */
    } entry[8];
} xpi_ahb_buffer_cfg_t;

typedef struct {
    uint8_t data_pads;
    xpi_channel_t channel;
    xpi_io_group_t io_group;
    uint8_t drive_strength;
    bool enable_dqs;
    bool enable_diff_clk;
} xpi_io_config_t;

typedef enum {
    xpi_freq_type_typical,
    xpi_freq_type_mhz,
} clk_freq_type_t;

typedef enum {
    xpi_clk_src_auto,
    xpi_clk_src_osc,
    xpi_clk_src_pll0clk0,
    xpi_clk_src_pll1clk0,
    xpi_clk_src_pll1clk1,
    xpi_clk_src_pll2clk0,
    xpi_clk_src_pll2clk1,
    xpi_clk_src_pll3clk0,
    xpi_clk_src_pll4clk0,
} xpi_clk_src_t;


typedef union
{
    struct {
        uint8_t freq;
        bool enable_ddr;
        xpi_clk_src_t clk_src;
        clk_freq_type_t freq_type;
    };
    uint32_t freq_opt;
} xpi_clk_config_t;

typedef enum {
    xpi_clock_bus,
    xpi_clock_serial_root,
    xpi_clock_serial,
} xpi_clock_t;

#endif /* HPM_ROMAPI_XPI_SOC_DEF_H */
