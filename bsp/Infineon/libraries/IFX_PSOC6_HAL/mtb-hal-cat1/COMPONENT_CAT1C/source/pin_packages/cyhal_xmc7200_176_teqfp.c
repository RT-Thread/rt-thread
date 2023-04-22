/***************************************************************************//**
* \file cyhal_xmc7200_176_teqfp.c
*
* \brief
* XMC7200 device GPIO HAL header for 176-TEQFP package
*
********************************************************************************
* \copyright
* (c) (2016-2023), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device_headers.h"
#include "cyhal_hw_types.h"

#if defined(_GPIO_XMC7200_176_TEQFP_H_)
#include "pin_packages/cyhal_xmc7200_176_teqfp.h"

/* Pin connections */
/* Connections for: audioss_clk_i2s_if */
const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_clk_i2s_if[3] = {
    {0u, 0u, P12_1, P12_1_AUDIOSS0_CLK_I2S_IF},
    {1u, 0u, P13_4, P13_4_AUDIOSS1_CLK_I2S_IF},
    {2u, 0u, P15_0, P15_0_AUDIOSS2_CLK_I2S_IF},
};

/* Connections for: audioss_mclk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_mclk[3] = {
    {0u, 0u, P11_0, P11_0_AUDIOSS0_MCLK},
    {1u, 0u, P13_0, P13_0_AUDIOSS1_MCLK},
    {2u, 0u, P14_0, P14_0_AUDIOSS2_MCLK},
};

/* Connections for: audioss_rx_sck */
const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_rx_sck[3] = {
    {0u, 0u, P12_2, P12_2_AUDIOSS0_RX_SCK},
    {1u, 0u, P13_5, P13_5_AUDIOSS1_RX_SCK},
    {2u, 0u, P15_1, P15_1_AUDIOSS2_RX_SCK},
};

/* Connections for: audioss_rx_sdi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_rx_sdi[3] = {
    {0u, 0u, P12_4, P12_4_AUDIOSS0_RX_SDI},
    {1u, 0u, P13_7, P13_7_AUDIOSS1_RX_SDI},
    {2u, 0u, P15_3, P15_3_AUDIOSS2_RX_SDI},
};

/* Connections for: audioss_rx_ws */
const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_rx_ws[3] = {
    {0u, 0u, P12_3, P12_3_AUDIOSS0_RX_WS},
    {1u, 0u, P13_6, P13_6_AUDIOSS1_RX_WS},
    {2u, 0u, P15_2, P15_2_AUDIOSS2_RX_WS},
};

/* Connections for: audioss_tx_sck */
const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_tx_sck[3] = {
    {0u, 0u, P11_1, P11_1_AUDIOSS0_TX_SCK},
    {1u, 0u, P13_1, P13_1_AUDIOSS1_TX_SCK},
    {2u, 0u, P14_1, P14_1_AUDIOSS2_TX_SCK},
};

/* Connections for: audioss_tx_sdo */
const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_tx_sdo[3] = {
    {0u, 0u, P12_0, P12_0_AUDIOSS0_TX_SDO},
    {1u, 0u, P13_3, P13_3_AUDIOSS1_TX_SDO},
    {2u, 0u, P14_5, P14_5_AUDIOSS2_TX_SDO},
};

/* Connections for: audioss_tx_ws */
const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_tx_ws[3] = {
    {0u, 0u, P11_2, P11_2_AUDIOSS0_TX_WS},
    {1u, 0u, P13_2, P13_2_AUDIOSS1_TX_WS},
    {2u, 0u, P14_4, P14_4_AUDIOSS2_TX_WS},
};

/* Connections for: canfd_ttcan_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_rx[18] = {
    {0u, 1u, P0_3, P0_3_CANFD0_TTCAN_RX1},
    {0u, 0u, P2_1, P2_1_CANFD0_TTCAN_RX0},
    {0u, 3u, P3_1, P3_1_CANFD0_TTCAN_RX3},
    {0u, 1u, P4_4, P4_4_CANFD0_TTCAN_RX1},
    {0u, 2u, P6_3, P6_3_CANFD0_TTCAN_RX2},
    {0u, 4u, P7_4, P7_4_CANFD0_TTCAN_RX4},
    {0u, 0u, P8_1, P8_1_CANFD0_TTCAN_RX0},
    {0u, 2u, P12_1, P12_1_CANFD0_TTCAN_RX2},
    {1u, 1u, P12_5, P12_5_CANFD1_TTCAN_RX1},
    {1u, 0u, P14_1, P14_1_CANFD1_TTCAN_RX0},
    {1u, 3u, P15_1, P15_1_CANFD1_TTCAN_RX3},
    {1u, 1u, P17_1, P17_1_CANFD1_TTCAN_RX1},
    {1u, 2u, P18_7, P18_7_CANFD1_TTCAN_RX2},
    {1u, 3u, P19_1, P19_1_CANFD1_TTCAN_RX3},
    {1u, 2u, P20_4, P20_4_CANFD1_TTCAN_RX2},
    {1u, 4u, P20_7, P20_7_CANFD1_TTCAN_RX4},
    {1u, 1u, P22_1, P22_1_CANFD1_TTCAN_RX1},
    {1u, 0u, P23_1, P23_1_CANFD1_TTCAN_RX0},
};

/* Connections for: canfd_ttcan_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_tx[18] = {
    {0u, 1u, P0_2, P0_2_CANFD0_TTCAN_TX1},
    {0u, 0u, P2_0, P2_0_CANFD0_TTCAN_TX0},
    {0u, 3u, P3_0, P3_0_CANFD0_TTCAN_TX3},
    {0u, 1u, P4_3, P4_3_CANFD0_TTCAN_TX1},
    {0u, 2u, P6_2, P6_2_CANFD0_TTCAN_TX2},
    {0u, 4u, P7_3, P7_3_CANFD0_TTCAN_TX4},
    {0u, 0u, P8_0, P8_0_CANFD0_TTCAN_TX0},
    {0u, 2u, P12_0, P12_0_CANFD0_TTCAN_TX2},
    {1u, 1u, P12_4, P12_4_CANFD1_TTCAN_TX1},
    {1u, 0u, P14_0, P14_0_CANFD1_TTCAN_TX0},
    {1u, 3u, P15_0, P15_0_CANFD1_TTCAN_TX3},
    {1u, 1u, P17_0, P17_0_CANFD1_TTCAN_TX1},
    {1u, 2u, P18_6, P18_6_CANFD1_TTCAN_TX2},
    {1u, 3u, P19_0, P19_0_CANFD1_TTCAN_TX3},
    {1u, 2u, P20_3, P20_3_CANFD1_TTCAN_TX2},
    {1u, 4u, P20_6, P20_6_CANFD1_TTCAN_TX4},
    {1u, 1u, P21_5, P21_5_CANFD1_TTCAN_TX1},
    {1u, 0u, P23_0, P23_0_CANFD1_TTCAN_TX0},
};

/* Connections for: cpuss_cal_sup_nz */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_cal_sup_nz[3] = {
    {0u, 0u, P6_3, P6_3_CPUSS_CAL_SUP_NZ},
    {0u, 0u, P21_7, P21_7_CPUSS_CAL_SUP_NZ},
    {0u, 0u, P23_7, P23_7_CPUSS_CAL_SUP_NZ},
};

/* Connections for: cpuss_clk_fm_pump */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_clk_fm_pump[1] = {
    {0u, 0u, P21_6, P21_6_CPUSS_CLK_FM_PUMP},
};

/* Connections for: cpuss_fault_out */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_fault_out[8] = {
    {0u, 0u, P18_0, P18_0_CPUSS_FAULT_OUT0},
    {0u, 1u, P18_1, P18_1_CPUSS_FAULT_OUT1},
    {0u, 2u, P19_0, P19_0_CPUSS_FAULT_OUT2},
    {0u, 3u, P19_1, P19_1_CPUSS_FAULT_OUT3},
    {0u, 0u, P23_0, P23_0_CPUSS_FAULT_OUT0},
    {0u, 1u, P23_1, P23_1_CPUSS_FAULT_OUT1},
    {0u, 2u, P23_2, P23_2_CPUSS_FAULT_OUT2},
    {0u, 3u, P23_3, P23_3_CPUSS_FAULT_OUT3},
};

/* Connections for: cpuss_swj_swclk_tclk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swclk_tclk[1] = {
    {0u, 0u, P23_5, P23_5_CPUSS_SWJ_SWCLK_TCLK},
};

/* Connections for: cpuss_swj_swdio_tms */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swdio_tms[1] = {
    {0u, 0u, P23_6, P23_6_CPUSS_SWJ_SWDIO_TMS},
};

/* Connections for: cpuss_swj_swdoe_tdi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swdoe_tdi[1] = {
    {0u, 0u, P23_7, P23_7_CPUSS_SWJ_SWDOE_TDI},
};

/* Connections for: cpuss_swj_swo_tdo */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swo_tdo[1] = {
    {0u, 0u, P23_4, P23_4_CPUSS_SWJ_SWO_TDO},
};

/* Connections for: cpuss_swj_trstn */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_trstn[1] = {
    {0u, 0u, P2_0, P2_0_CPUSS_SWJ_TRSTN},
};

/* Connections for: cpuss_trace_clock */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_trace_clock[2] = {
    {0u, 0u, P18_3, P18_3_CPUSS_TRACE_CLOCK},
    {0u, 0u, P22_4, P22_4_CPUSS_TRACE_CLOCK},
};

/* Connections for: cpuss_trace_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_trace_data[8] = {
    {0u, 0u, P18_4, P18_4_CPUSS_TRACE_DATA0},
    {0u, 1u, P18_5, P18_5_CPUSS_TRACE_DATA1},
    {0u, 2u, P18_6, P18_6_CPUSS_TRACE_DATA2},
    {0u, 3u, P18_7, P18_7_CPUSS_TRACE_DATA3},
    {0u, 0u, P21_5, P21_5_CPUSS_TRACE_DATA0},
    {0u, 1u, P22_1, P22_1_CPUSS_TRACE_DATA1},
    {0u, 2u, P22_2, P22_2_CPUSS_TRACE_DATA2},
    {0u, 3u, P22_3, P22_3_CPUSS_TRACE_DATA3},
};

/* Connections for: eth_eth_tsu_timer_cmp_val */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_eth_tsu_timer_cmp_val[1] = {
    {0u, 0u, P2_3, P2_3_ETH0_ETH_TSU_TIMER_CMP_VAL},
};

/* Connections for: eth_mdc */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_mdc[1] = {
    {0u, 0u, P3_1, P3_1_ETH0_MDC},
};

/* Connections for: eth_mdio */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_mdio[1] = {
    {0u, 0u, P3_0, P3_0_ETH0_MDIO},
};

/* Connections for: eth_ref_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_ref_clk[1] = {
    {0u, 0u, P18_0, P18_0_ETH0_REF_CLK},
};

/* Connections for: eth_rx_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rx_clk[1] = {
    {0u, 0u, P23_3, P23_3_ETH0_RX_CLK},
};

/* Connections for: eth_rx_ctl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rx_ctl[1] = {
    {0u, 0u, P21_5, P21_5_ETH0_RX_CTL},
};

/* Connections for: eth_rx_er */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rx_er[1] = {
    {0u, 0u, P2_2, P2_2_ETH0_RX_ER},
};

/* Connections for: eth_rxd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rxd[4] = {
    {0u, 0u, P19_0, P19_0_ETH0_RXD0},
    {0u, 1u, P19_1, P19_1_ETH0_RXD1},
    {0u, 2u, P19_2, P19_2_ETH0_RXD2},
    {0u, 3u, P19_3, P19_3_ETH0_RXD3},
};

/* Connections for: eth_tx_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_tx_clk[1] = {
    {0u, 0u, P18_3, P18_3_ETH0_TX_CLK},
};

/* Connections for: eth_tx_ctl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_tx_ctl[1] = {
    {0u, 0u, P18_1, P18_1_ETH0_TX_CTL},
};

/* Connections for: eth_tx_er */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_tx_er[1] = {
    {0u, 0u, P18_2, P18_2_ETH0_TX_ER},
};

/* Connections for: eth_txd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_txd[4] = {
    {0u, 0u, P18_4, P18_4_ETH0_TXD0},
    {0u, 1u, P18_5, P18_5_ETH0_TXD1},
    {0u, 2u, P18_6, P18_6_ETH0_TXD2},
    {0u, 3u, P18_7, P18_7_ETH0_TXD3},
};

/* Connections for: flexray_rxda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_flexray_rxda[1] = {
    {0u, 0u, P10_2, P10_2_FLEXRAY0_RXDA},
};

/* Connections for: flexray_rxdb */
const cyhal_resource_pin_mapping_t cyhal_pin_map_flexray_rxdb[1] = {
    {0u, 0u, P10_5, P10_5_FLEXRAY0_RXDB},
};

/* Connections for: flexray_txda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_flexray_txda[1] = {
    {0u, 0u, P10_3, P10_3_FLEXRAY0_TXDA},
};

/* Connections for: flexray_txdb */
const cyhal_resource_pin_mapping_t cyhal_pin_map_flexray_txdb[1] = {
    {0u, 0u, P10_6, P10_6_FLEXRAY0_TXDB},
};

/* Connections for: flexray_txena_n */
const cyhal_resource_pin_mapping_t cyhal_pin_map_flexray_txena_n[1] = {
    {0u, 0u, P10_4, P10_4_FLEXRAY0_TXENA_N},
};

/* Connections for: flexray_txenb_n */
const cyhal_resource_pin_mapping_t cyhal_pin_map_flexray_txenb_n[1] = {
    {0u, 0u, P10_7, P10_7_FLEXRAY0_TXENB_N},
};

/* Connections for: lin_lin_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_en[27] = {
    {0u, 1u, P0_2, P0_2_LIN0_LIN_EN1},
    {0u, 0u, P2_2, P2_2_LIN0_LIN_EN0},
    {0u, 5u, P2_5, P2_5_LIN0_LIN_EN5},
    {0u, 1u, P4_2, P4_2_LIN0_LIN_EN1},
    {0u, 7u, P5_2, P5_2_LIN0_LIN_EN7},
    {0u, 2u, P5_5, P5_5_LIN0_LIN_EN2},
    {0u, 9u, P6_0, P6_0_LIN0_LIN_EN9},
    {0u, 3u, P6_2, P6_2_LIN0_LIN_EN3},
    {0u, 4u, P6_5, P6_5_LIN0_LIN_EN4},
    {0u, 4u, P7_2, P7_2_LIN0_LIN_EN4},
    {0u, 10u, P7_7, P7_7_LIN0_LIN_EN10},
    {0u, 2u, P8_2, P8_2_LIN0_LIN_EN2},
    {0u, 16u, P9_0, P9_0_LIN0_LIN_EN16},
    {0u, 12u, P9_3, P9_3_LIN0_LIN_EN12},
    {0u, 8u, P10_4, P10_4_LIN0_LIN_EN8},
    {0u, 13u, P10_7, P10_7_LIN0_LIN_EN13},
    {0u, 6u, P12_1, P12_1_LIN0_LIN_EN6},
    {0u, 3u, P13_2, P13_2_LIN0_LIN_EN3},
    {0u, 8u, P13_6, P13_6_LIN0_LIN_EN8},
    {0u, 6u, P14_4, P14_4_LIN0_LIN_EN6},
    {0u, 14u, P14_7, P14_7_LIN0_LIN_EN14},
    {0u, 11u, P17_2, P17_2_LIN0_LIN_EN11},
    {0u, 15u, P17_7, P17_7_LIN0_LIN_EN15},
    {0u, 5u, P20_2, P20_2_LIN0_LIN_EN5},
    {0u, 0u, P21_7, P21_7_LIN0_LIN_EN0},
    {0u, 7u, P22_7, P22_7_LIN0_LIN_EN7},
    {0u, 9u, P23_7, P23_7_LIN0_LIN_EN9},
};

/* Connections for: lin_lin_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_rx[37] = {
    {0u, 1u, P0_0, P0_0_LIN0_LIN_RX1},
    {0u, 0u, P1_2, P1_2_LIN0_LIN_RX0},
    {0u, 0u, P2_0, P2_0_LIN0_LIN_RX0},
    {0u, 5u, P2_3, P2_3_LIN0_LIN_RX5},
    {0u, 1u, P3_4, P3_4_LIN0_LIN_RX1},
    {0u, 1u, P4_0, P4_0_LIN0_LIN_RX1},
    {0u, 15u, P4_4, P4_4_LIN0_LIN_RX15},
    {0u, 7u, P5_0, P5_0_LIN0_LIN_RX7},
    {0u, 10u, P5_2, P5_2_LIN0_LIN_RX10},
    {0u, 2u, P5_3, P5_3_LIN0_LIN_RX2},
    {0u, 9u, P5_4, P5_4_LIN0_LIN_RX9},
    {0u, 3u, P6_0, P6_0_LIN0_LIN_RX3},
    {0u, 4u, P6_3, P6_3_LIN0_LIN_RX4},
    {0u, 4u, P7_0, P7_0_LIN0_LIN_RX4},
    {0u, 10u, P7_5, P7_5_LIN0_LIN_RX10},
    {0u, 2u, P8_0, P8_0_LIN0_LIN_RX2},
    {0u, 16u, P8_3, P8_3_LIN0_LIN_RX16},
    {0u, 12u, P9_1, P9_1_LIN0_LIN_RX12},
    {0u, 7u, P10_0, P10_0_LIN0_LIN_RX7},
    {0u, 8u, P10_2, P10_2_LIN0_LIN_RX8},
    {0u, 13u, P10_5, P10_5_LIN0_LIN_RX13},
    {0u, 6u, P12_2, P12_2_LIN0_LIN_RX6},
    {0u, 3u, P13_0, P13_0_LIN0_LIN_RX3},
    {0u, 2u, P13_3, P13_3_LIN0_LIN_RX2},
    {0u, 8u, P13_4, P13_4_LIN0_LIN_RX8},
    {0u, 6u, P14_2, P14_2_LIN0_LIN_RX6},
    {0u, 14u, P14_5, P14_5_LIN0_LIN_RX14},
    {0u, 11u, P17_0, P17_0_LIN0_LIN_RX11},
    {0u, 15u, P17_5, P17_5_LIN0_LIN_RX15},
    {0u, 12u, P17_7, P17_7_LIN0_LIN_RX12},
    {0u, 5u, P20_0, P20_0_LIN0_LIN_RX5},
    {0u, 0u, P21_5, P21_5_LIN0_LIN_RX0},
    {0u, 13u, P21_6, P21_6_LIN0_LIN_RX13},
    {0u, 7u, P22_5, P22_5_LIN0_LIN_RX7},
    {0u, 14u, P22_7, P22_7_LIN0_LIN_RX14},
    {0u, 6u, P23_2, P23_2_LIN0_LIN_RX6},
    {0u, 9u, P23_5, P23_5_LIN0_LIN_RX9},
};

/* Connections for: lin_lin_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_tx[37] = {
    {0u, 1u, P0_1, P0_1_LIN0_LIN_TX1},
    {0u, 0u, P1_3, P1_3_LIN0_LIN_TX0},
    {0u, 0u, P2_1, P2_1_LIN0_LIN_TX0},
    {0u, 5u, P2_4, P2_4_LIN0_LIN_TX5},
    {0u, 1u, P3_5, P3_5_LIN0_LIN_TX1},
    {0u, 1u, P4_1, P4_1_LIN0_LIN_TX1},
    {0u, 15u, P5_0, P5_0_LIN0_LIN_TX15},
    {0u, 7u, P5_1, P5_1_LIN0_LIN_TX7},
    {0u, 10u, P5_3, P5_3_LIN0_LIN_TX10},
    {0u, 2u, P5_4, P5_4_LIN0_LIN_TX2},
    {0u, 9u, P5_5, P5_5_LIN0_LIN_TX9},
    {0u, 3u, P6_1, P6_1_LIN0_LIN_TX3},
    {0u, 4u, P6_4, P6_4_LIN0_LIN_TX4},
    {0u, 4u, P7_1, P7_1_LIN0_LIN_TX4},
    {0u, 10u, P7_6, P7_6_LIN0_LIN_TX10},
    {0u, 2u, P8_1, P8_1_LIN0_LIN_TX2},
    {0u, 16u, P8_4, P8_4_LIN0_LIN_TX16},
    {0u, 12u, P9_2, P9_2_LIN0_LIN_TX12},
    {0u, 7u, P10_1, P10_1_LIN0_LIN_TX7},
    {0u, 8u, P10_3, P10_3_LIN0_LIN_TX8},
    {0u, 13u, P10_6, P10_6_LIN0_LIN_TX13},
    {0u, 6u, P12_3, P12_3_LIN0_LIN_TX6},
    {0u, 3u, P13_1, P13_1_LIN0_LIN_TX3},
    {0u, 2u, P13_4, P13_4_LIN0_LIN_TX2},
    {0u, 8u, P13_5, P13_5_LIN0_LIN_TX8},
    {0u, 6u, P14_3, P14_3_LIN0_LIN_TX6},
    {0u, 14u, P14_6, P14_6_LIN0_LIN_TX14},
    {0u, 11u, P17_1, P17_1_LIN0_LIN_TX11},
    {0u, 15u, P17_6, P17_6_LIN0_LIN_TX15},
    {0u, 12u, P18_0, P18_0_LIN0_LIN_TX12},
    {0u, 5u, P20_1, P20_1_LIN0_LIN_TX5},
    {0u, 0u, P21_6, P21_6_LIN0_LIN_TX0},
    {0u, 13u, P21_7, P21_7_LIN0_LIN_TX13},
    {0u, 7u, P22_6, P22_6_LIN0_LIN_TX7},
    {0u, 14u, P23_0, P23_0_LIN0_LIN_TX14},
    {0u, 6u, P23_3, P23_3_LIN0_LIN_TX6},
    {0u, 9u, P23_6, P23_6_LIN0_LIN_TX9},
};

/* Connections for: pass_sar_ext_mux_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_mux_en[3] = {
    {0u, 0u, P4_3, P4_3_PASS0_SAR_EXT_MUX_EN0},
    {0u, 1u, P12_2, P12_2_PASS0_SAR_EXT_MUX_EN1},
    {0u, 2u, P13_3, P13_3_PASS0_SAR_EXT_MUX_EN2},
};

/* Connections for: pass_sar_ext_mux_sel */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_mux_sel[9] = {
    {0u, 0u, P4_0, P4_0_PASS0_SAR_EXT_MUX_SEL0},
    {0u, 1u, P4_1, P4_1_PASS0_SAR_EXT_MUX_SEL1},
    {0u, 2u, P4_2, P4_2_PASS0_SAR_EXT_MUX_SEL2},
    {0u, 3u, P12_3, P12_3_PASS0_SAR_EXT_MUX_SEL3},
    {0u, 4u, P12_4, P12_4_PASS0_SAR_EXT_MUX_SEL4},
    {0u, 5u, P12_5, P12_5_PASS0_SAR_EXT_MUX_SEL5},
    {0u, 6u, P13_0, P13_0_PASS0_SAR_EXT_MUX_SEL6},
    {0u, 7u, P13_1, P13_1_PASS0_SAR_EXT_MUX_SEL7},
    {0u, 8u, P13_2, P13_2_PASS0_SAR_EXT_MUX_SEL8},
};

/* Connections for: pass_sarmux_pads */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sarmux_pads[81] = {
    {0u, 0u, P6_0, HSIOM_SEL_GPIO},
    {0u, 1u, P6_1, HSIOM_SEL_GPIO},
    {0u, 2u, P6_2, HSIOM_SEL_GPIO},
    {0u, 3u, P6_3, HSIOM_SEL_GPIO},
    {0u, 4u, P6_4, HSIOM_SEL_GPIO},
    {0u, 5u, P6_5, HSIOM_SEL_GPIO},
    {0u, 6u, P6_6, HSIOM_SEL_GPIO},
    {0u, 7u, P6_7, HSIOM_SEL_GPIO},
    {0u, 16u, P7_0, HSIOM_SEL_GPIO},
    {0u, 17u, P7_1, HSIOM_SEL_GPIO},
    {0u, 18u, P7_2, HSIOM_SEL_GPIO},
    {0u, 19u, P7_3, HSIOM_SEL_GPIO},
    {0u, 20u, P7_4, HSIOM_SEL_GPIO},
    {0u, 21u, P7_5, HSIOM_SEL_GPIO},
    {0u, 22u, P7_6, HSIOM_SEL_GPIO},
    {0u, 23u, P7_7, HSIOM_SEL_GPIO},
    {0u, 24u, P8_1, HSIOM_SEL_GPIO},
    {0u, 25u, P8_2, HSIOM_SEL_GPIO},
    {0u, 26u, P8_3, HSIOM_SEL_GPIO},
    {0u, 27u, P8_4, HSIOM_SEL_GPIO},
    {0u, 28u, P9_0, HSIOM_SEL_GPIO},
    {0u, 29u, P9_1, HSIOM_SEL_GPIO},
    {0u, 30u, P9_2, HSIOM_SEL_GPIO},
    {0u, 31u, P9_3, HSIOM_SEL_GPIO},
    {1u, 0u, P10_4, HSIOM_SEL_GPIO},
    {1u, 1u, P10_5, HSIOM_SEL_GPIO},
    {1u, 2u, P10_6, HSIOM_SEL_GPIO},
    {1u, 3u, P10_7, HSIOM_SEL_GPIO},
    {1u, 4u, P12_0, HSIOM_SEL_GPIO},
    {1u, 5u, P12_1, HSIOM_SEL_GPIO},
    {1u, 6u, P12_2, HSIOM_SEL_GPIO},
    {1u, 7u, P12_3, HSIOM_SEL_GPIO},
    {1u, 8u, P12_4, HSIOM_SEL_GPIO},
    {1u, 9u, P12_5, HSIOM_SEL_GPIO},
    {1u, 10u, P12_6, HSIOM_SEL_GPIO},
    {1u, 11u, P12_7, HSIOM_SEL_GPIO},
    {1u, 12u, P13_0, HSIOM_SEL_GPIO},
    {1u, 13u, P13_1, HSIOM_SEL_GPIO},
    {1u, 14u, P13_2, HSIOM_SEL_GPIO},
    {1u, 15u, P13_3, HSIOM_SEL_GPIO},
    {1u, 16u, P13_4, HSIOM_SEL_GPIO},
    {1u, 17u, P13_5, HSIOM_SEL_GPIO},
    {1u, 18u, P13_6, HSIOM_SEL_GPIO},
    {1u, 19u, P13_7, HSIOM_SEL_GPIO},
    {1u, 20u, P14_0, HSIOM_SEL_GPIO},
    {1u, 21u, P14_1, HSIOM_SEL_GPIO},
    {1u, 22u, P14_2, HSIOM_SEL_GPIO},
    {1u, 23u, P14_3, HSIOM_SEL_GPIO},
    {1u, 24u, P14_4, HSIOM_SEL_GPIO},
    {1u, 25u, P14_5, HSIOM_SEL_GPIO},
    {1u, 26u, P14_6, HSIOM_SEL_GPIO},
    {1u, 27u, P14_7, HSIOM_SEL_GPIO},
    {1u, 28u, P15_0, HSIOM_SEL_GPIO},
    {1u, 29u, P15_1, HSIOM_SEL_GPIO},
    {1u, 30u, P15_2, HSIOM_SEL_GPIO},
    {1u, 31u, P15_3, HSIOM_SEL_GPIO},
    {2u, 3u, P16_3, HSIOM_SEL_GPIO},
    {2u, 8u, P17_0, HSIOM_SEL_GPIO},
    {2u, 9u, P17_1, HSIOM_SEL_GPIO},
    {2u, 10u, P17_2, HSIOM_SEL_GPIO},
    {2u, 11u, P17_3, HSIOM_SEL_GPIO},
    {2u, 12u, P17_4, HSIOM_SEL_GPIO},
    {2u, 13u, P17_5, HSIOM_SEL_GPIO},
    {2u, 14u, P17_6, HSIOM_SEL_GPIO},
    {2u, 15u, P17_7, HSIOM_SEL_GPIO},
    {2u, 16u, P18_0, HSIOM_SEL_GPIO},
    {2u, 17u, P18_1, HSIOM_SEL_GPIO},
    {2u, 18u, P18_2, HSIOM_SEL_GPIO},
    {2u, 19u, P18_3, HSIOM_SEL_GPIO},
    {2u, 20u, P18_4, HSIOM_SEL_GPIO},
    {2u, 21u, P18_5, HSIOM_SEL_GPIO},
    {2u, 22u, P18_6, HSIOM_SEL_GPIO},
    {2u, 23u, P18_7, HSIOM_SEL_GPIO},
    {2u, 24u, P19_0, HSIOM_SEL_GPIO},
    {2u, 25u, P19_1, HSIOM_SEL_GPIO},
    {2u, 26u, P19_2, HSIOM_SEL_GPIO},
    {2u, 27u, P19_3, HSIOM_SEL_GPIO},
    {2u, 28u, P19_4, HSIOM_SEL_GPIO},
    {2u, 29u, P20_0, HSIOM_SEL_GPIO},
    {2u, 30u, P20_1, HSIOM_SEL_GPIO},
    {2u, 31u, P20_2, HSIOM_SEL_GPIO},
};

/* Connections for: peri_tr_io_input */
/* The actual channel_num has no value to how the connection works. However, the HAL driver needs
   to know the index of the input or output trigger line. Store that in the channel_num field
   instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_input[34] = {
    {0u, 0u, P1_2, P1_2_PERI_TR_IO_INPUT0},
    {0u, 1u, P1_3, P1_3_PERI_TR_IO_INPUT1},
    {0u, 2u, P2_0, P2_0_PERI_TR_IO_INPUT2},
    {0u, 3u, P2_1, P2_1_PERI_TR_IO_INPUT3},
    {0u, 4u, P2_2, P2_2_PERI_TR_IO_INPUT4},
    {0u, 5u, P2_3, P2_3_PERI_TR_IO_INPUT5},
    {0u, 6u, P2_4, P2_4_PERI_TR_IO_INPUT6},
    {0u, 7u, P2_5, P2_5_PERI_TR_IO_INPUT7},
    {0u, 10u, P4_0, P4_0_PERI_TR_IO_INPUT10},
    {0u, 11u, P4_1, P4_1_PERI_TR_IO_INPUT11},
    {0u, 12u, P4_2, P4_2_PERI_TR_IO_INPUT12},
    {0u, 13u, P4_3, P4_3_PERI_TR_IO_INPUT13},
    {0u, 38u, P5_0, P5_0_PERI_TR_IO_INPUT38},
    {0u, 39u, P5_1, P5_1_PERI_TR_IO_INPUT39},
    {0u, 8u, P6_6, P6_6_PERI_TR_IO_INPUT8},
    {0u, 9u, P6_7, P6_7_PERI_TR_IO_INPUT9},
    {0u, 16u, P7_6, P7_6_PERI_TR_IO_INPUT16},
    {0u, 17u, P7_7, P7_7_PERI_TR_IO_INPUT17},
    {0u, 14u, P8_1, P8_1_PERI_TR_IO_INPUT14},
    {0u, 15u, P8_2, P8_2_PERI_TR_IO_INPUT15},
    {0u, 18u, P10_0, P10_0_PERI_TR_IO_INPUT18},
    {0u, 19u, P10_1, P10_1_PERI_TR_IO_INPUT19},
    {0u, 20u, P12_0, P12_0_PERI_TR_IO_INPUT20},
    {0u, 21u, P12_1, P12_1_PERI_TR_IO_INPUT21},
    {0u, 22u, P13_6, P13_6_PERI_TR_IO_INPUT22},
    {0u, 23u, P13_7, P13_7_PERI_TR_IO_INPUT23},
    {0u, 24u, P14_6, P14_6_PERI_TR_IO_INPUT24},
    {0u, 25u, P14_7, P14_7_PERI_TR_IO_INPUT25},
    {0u, 26u, P17_3, P17_3_PERI_TR_IO_INPUT26},
    {0u, 27u, P17_4, P17_4_PERI_TR_IO_INPUT27},
    {0u, 28u, P19_2, P19_2_PERI_TR_IO_INPUT28},
    {0u, 29u, P19_3, P19_3_PERI_TR_IO_INPUT29},
    {0u, 30u, P23_3, P23_3_PERI_TR_IO_INPUT30},
    {0u, 31u, P23_4, P23_4_PERI_TR_IO_INPUT31},
};

/* Connections for: peri_tr_io_output */
/* The actual channel_num has no value to how the connection works. However, the HAL driver needs
   to know the index of the input or output trigger line. Store that in the channel_num field
   instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_output[6] = {
    {0u, 0u, P3_0, P3_0_PERI_TR_IO_OUTPUT0},
    {0u, 1u, P3_1, P3_1_PERI_TR_IO_OUTPUT1},
    {0u, 0u, P8_3, P8_3_PERI_TR_IO_OUTPUT0},
    {0u, 1u, P8_4, P8_4_PERI_TR_IO_OUTPUT1},
    {0u, 1u, P21_2, P21_2_PERI_TR_IO_OUTPUT1},
    {0u, 0u, P23_4, P23_4_PERI_TR_IO_OUTPUT0},
};

/* Connections for: scb_i2c_scl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[19] = {
    {7u, 0u, P0_1, P0_1_SCB7_I2C_SCL},
    {0u, 0u, P0_2, P0_2_SCB0_I2C_SCL},
    {0u, 0u, P1_0, P1_0_SCB0_I2C_SCL},
    {7u, 0u, P2_2, P2_2_SCB7_I2C_SCL},
    {6u, 0u, P3_2, P3_2_SCB6_I2C_SCL},
    {5u, 0u, P4_2, P4_2_SCB5_I2C_SCL},
    {4u, 0u, P6_2, P6_2_SCB4_I2C_SCL},
    {5u, 0u, P7_2, P7_2_SCB5_I2C_SCL},
    {4u, 0u, P10_2, P10_2_SCB4_I2C_SCL},
    {8u, 0u, P12_2, P12_2_SCB8_I2C_SCL},
    {3u, 0u, P13_2, P13_2_SCB3_I2C_SCL},
    {2u, 0u, P14_2, P14_2_SCB2_I2C_SCL},
    {9u, 0u, P15_2, P15_2_SCB9_I2C_SCL},
    {3u, 0u, P17_3, P17_3_SCB3_I2C_SCL},
    {1u, 0u, P18_2, P18_2_SCB1_I2C_SCL},
    {2u, 0u, P19_2, P19_2_SCB2_I2C_SCL},
    {1u, 0u, P20_5, P20_5_SCB1_I2C_SCL},
    {6u, 0u, P22_2, P22_2_SCB6_I2C_SCL},
    {7u, 0u, P23_2, P23_2_SCB7_I2C_SCL},
};

/* Connections for: scb_i2c_sda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[19] = {
    {7u, 0u, P0_0, P0_0_SCB7_I2C_SDA},
    {0u, 0u, P0_3, P0_3_SCB0_I2C_SDA},
    {0u, 0u, P1_1, P1_1_SCB0_I2C_SDA},
    {7u, 0u, P2_1, P2_1_SCB7_I2C_SDA},
    {6u, 0u, P3_1, P3_1_SCB6_I2C_SDA},
    {5u, 0u, P4_1, P4_1_SCB5_I2C_SDA},
    {4u, 0u, P6_1, P6_1_SCB4_I2C_SDA},
    {5u, 0u, P7_1, P7_1_SCB5_I2C_SDA},
    {4u, 0u, P10_1, P10_1_SCB4_I2C_SDA},
    {8u, 0u, P12_1, P12_1_SCB8_I2C_SDA},
    {3u, 0u, P13_1, P13_1_SCB3_I2C_SDA},
    {2u, 0u, P14_1, P14_1_SCB2_I2C_SDA},
    {9u, 0u, P15_1, P15_1_SCB9_I2C_SDA},
    {3u, 0u, P17_2, P17_2_SCB3_I2C_SDA},
    {1u, 0u, P18_1, P18_1_SCB1_I2C_SDA},
    {2u, 0u, P19_1, P19_1_SCB2_I2C_SDA},
    {1u, 0u, P20_4, P20_4_SCB1_I2C_SDA},
    {6u, 0u, P22_1, P22_1_SCB6_I2C_SDA},
    {7u, 0u, P23_1, P23_1_SCB7_I2C_SDA},
};

/* Connections for: scb_spi_m_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[21] = {
    {0u, 0u, P0_2, P0_2_SCB0_SPI_CLK},
    {4u, 0u, P1_0, P1_0_SCB4_SPI_CLK},
    {0u, 0u, P1_2, P1_2_SCB0_SPI_CLK},
    {7u, 0u, P2_2, P2_2_SCB7_SPI_CLK},
    {6u, 0u, P3_2, P3_2_SCB6_SPI_CLK},
    {5u, 0u, P4_2, P4_2_SCB5_SPI_CLK},
    {4u, 0u, P6_2, P6_2_SCB4_SPI_CLK},
    {5u, 0u, P7_2, P7_2_SCB5_SPI_CLK},
    {4u, 0u, P10_2, P10_2_SCB4_SPI_CLK},
    {8u, 0u, P12_2, P12_2_SCB8_SPI_CLK},
    {3u, 0u, P13_2, P13_2_SCB3_SPI_CLK},
    {2u, 0u, P14_2, P14_2_SCB2_SPI_CLK},
    {9u, 0u, P15_2, P15_2_SCB9_SPI_CLK},
    {3u, 0u, P17_3, P17_3_SCB3_SPI_CLK},
    {1u, 0u, P18_2, P18_2_SCB1_SPI_CLK},
    {3u, 0u, P18_3, P18_3_SCB3_SPI_CLK},
    {2u, 0u, P19_2, P19_2_SCB2_SPI_CLK},
    {1u, 0u, P20_5, P20_5_SCB1_SPI_CLK},
    {6u, 0u, P22_2, P22_2_SCB6_SPI_CLK},
    {7u, 0u, P23_2, P23_2_SCB7_SPI_CLK},
    {2u, 0u, P23_6, P23_6_SCB2_SPI_CLK},
};

/* Connections for: scb_spi_m_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[20] = {
    {0u, 0u, P0_0, P0_0_SCB0_SPI_MISO},
    {4u, 0u, P0_2, P0_2_SCB4_SPI_MISO},
    {0u, 0u, P1_0, P1_0_SCB0_SPI_MISO},
    {7u, 0u, P2_0, P2_0_SCB7_SPI_MISO},
    {6u, 0u, P3_0, P3_0_SCB6_SPI_MISO},
    {5u, 0u, P4_0, P4_0_SCB5_SPI_MISO},
    {4u, 0u, P6_0, P6_0_SCB4_SPI_MISO},
    {5u, 0u, P7_0, P7_0_SCB5_SPI_MISO},
    {4u, 0u, P10_0, P10_0_SCB4_SPI_MISO},
    {8u, 0u, P12_0, P12_0_SCB8_SPI_MISO},
    {3u, 0u, P13_0, P13_0_SCB3_SPI_MISO},
    {2u, 0u, P14_0, P14_0_SCB2_SPI_MISO},
    {9u, 0u, P15_0, P15_0_SCB9_SPI_MISO},
    {1u, 0u, P18_0, P18_0_SCB1_SPI_MISO},
    {3u, 0u, P18_1, P18_1_SCB3_SPI_MISO},
    {2u, 0u, P19_0, P19_0_SCB2_SPI_MISO},
    {1u, 0u, P20_3, P20_3_SCB1_SPI_MISO},
    {6u, 0u, P21_7, P21_7_SCB6_SPI_MISO},
    {7u, 0u, P23_0, P23_0_SCB7_SPI_MISO},
    {2u, 0u, P23_4, P23_4_SCB2_SPI_MISO},
};

/* Connections for: scb_spi_m_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[20] = {
    {0u, 0u, P0_1, P0_1_SCB0_SPI_MOSI},
    {4u, 0u, P0_3, P0_3_SCB4_SPI_MOSI},
    {0u, 0u, P1_1, P1_1_SCB0_SPI_MOSI},
    {7u, 0u, P2_1, P2_1_SCB7_SPI_MOSI},
    {6u, 0u, P3_1, P3_1_SCB6_SPI_MOSI},
    {5u, 0u, P4_1, P4_1_SCB5_SPI_MOSI},
    {4u, 0u, P6_1, P6_1_SCB4_SPI_MOSI},
    {5u, 0u, P7_1, P7_1_SCB5_SPI_MOSI},
    {4u, 0u, P10_1, P10_1_SCB4_SPI_MOSI},
    {8u, 0u, P12_1, P12_1_SCB8_SPI_MOSI},
    {3u, 0u, P13_1, P13_1_SCB3_SPI_MOSI},
    {2u, 0u, P14_1, P14_1_SCB2_SPI_MOSI},
    {9u, 0u, P15_1, P15_1_SCB9_SPI_MOSI},
    {1u, 0u, P18_1, P18_1_SCB1_SPI_MOSI},
    {3u, 0u, P18_2, P18_2_SCB3_SPI_MOSI},
    {2u, 0u, P19_1, P19_1_SCB2_SPI_MOSI},
    {1u, 0u, P20_4, P20_4_SCB1_SPI_MOSI},
    {6u, 0u, P22_1, P22_1_SCB6_SPI_MOSI},
    {7u, 0u, P23_1, P23_1_SCB7_SPI_MOSI},
    {2u, 0u, P23_5, P23_5_SCB2_SPI_MOSI},
};

/* Connections for: scb_spi_m_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[21] = {
    {0u, 0u, P0_3, P0_3_SCB0_SPI_SELECT0},
    {4u, 0u, P1_1, P1_1_SCB4_SPI_SELECT0},
    {0u, 0u, P1_3, P1_3_SCB0_SPI_SELECT0},
    {7u, 0u, P2_3, P2_3_SCB7_SPI_SELECT0},
    {6u, 0u, P3_3, P3_3_SCB6_SPI_SELECT0},
    {5u, 0u, P4_3, P4_3_SCB5_SPI_SELECT0},
    {4u, 0u, P6_3, P6_3_SCB4_SPI_SELECT0},
    {5u, 0u, P7_3, P7_3_SCB5_SPI_SELECT0},
    {4u, 0u, P10_3, P10_3_SCB4_SPI_SELECT0},
    {8u, 0u, P12_3, P12_3_SCB8_SPI_SELECT0},
    {3u, 0u, P13_3, P13_3_SCB3_SPI_SELECT0},
    {2u, 0u, P14_3, P14_3_SCB2_SPI_SELECT0},
    {9u, 0u, P15_3, P15_3_SCB9_SPI_SELECT0},
    {3u, 0u, P17_4, P17_4_SCB3_SPI_SELECT0},
    {1u, 0u, P18_3, P18_3_SCB1_SPI_SELECT0},
    {3u, 0u, P18_4, P18_4_SCB3_SPI_SELECT0},
    {2u, 0u, P19_3, P19_3_SCB2_SPI_SELECT0},
    {1u, 0u, P20_6, P20_6_SCB1_SPI_SELECT0},
    {6u, 0u, P22_3, P22_3_SCB6_SPI_SELECT0},
    {7u, 0u, P23_3, P23_3_SCB7_SPI_SELECT0},
    {2u, 0u, P23_7, P23_7_SCB2_SPI_SELECT0},
};

/* Connections for: scb_spi_m_select1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select1[16] = {
    {0u, 0u, P2_0, P2_0_SCB0_SPI_SELECT1},
    {7u, 0u, P2_4, P2_4_SCB7_SPI_SELECT1},
    {6u, 0u, P3_4, P3_4_SCB6_SPI_SELECT1},
    {5u, 0u, P4_4, P4_4_SCB5_SPI_SELECT1},
    {4u, 0u, P6_4, P6_4_SCB4_SPI_SELECT1},
    {5u, 0u, P7_4, P7_4_SCB5_SPI_SELECT1},
    {4u, 0u, P10_4, P10_4_SCB4_SPI_SELECT1},
    {8u, 0u, P12_4, P12_4_SCB8_SPI_SELECT1},
    {3u, 0u, P13_4, P13_4_SCB3_SPI_SELECT1},
    {2u, 0u, P14_4, P14_4_SCB2_SPI_SELECT1},
    {3u, 0u, P17_5, P17_5_SCB3_SPI_SELECT1},
    {1u, 0u, P18_4, P18_4_SCB1_SPI_SELECT1},
    {2u, 0u, P19_4, P19_4_SCB2_SPI_SELECT1},
    {1u, 0u, P20_7, P20_7_SCB1_SPI_SELECT1},
    {6u, 0u, P22_4, P22_4_SCB6_SPI_SELECT1},
    {7u, 0u, P23_4, P23_4_SCB7_SPI_SELECT1},
};

/* Connections for: scb_spi_m_select2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select2[15] = {
    {0u, 0u, P2_1, P2_1_SCB0_SPI_SELECT2},
    {7u, 0u, P2_5, P2_5_SCB7_SPI_SELECT2},
    {6u, 0u, P3_5, P3_5_SCB6_SPI_SELECT2},
    {5u, 0u, P5_0, P5_0_SCB5_SPI_SELECT2},
    {4u, 0u, P6_5, P6_5_SCB4_SPI_SELECT2},
    {5u, 0u, P7_5, P7_5_SCB5_SPI_SELECT2},
    {4u, 0u, P10_5, P10_5_SCB4_SPI_SELECT2},
    {3u, 0u, P13_5, P13_5_SCB3_SPI_SELECT2},
    {2u, 0u, P14_5, P14_5_SCB2_SPI_SELECT2},
    {3u, 0u, P17_6, P17_6_SCB3_SPI_SELECT2},
    {1u, 0u, P18_5, P18_5_SCB1_SPI_SELECT2},
    {2u, 0u, P20_0, P20_0_SCB2_SPI_SELECT2},
    {1u, 0u, P21_0, P21_0_SCB1_SPI_SELECT2},
    {6u, 0u, P22_5, P22_5_SCB6_SPI_SELECT2},
    {7u, 0u, P23_5, P23_5_SCB7_SPI_SELECT2},
};

/* Connections for: scb_spi_m_select3 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select3[5] = {
    {0u, 0u, P2_2, P2_2_SCB0_SPI_SELECT3},
    {9u, 0u, P5_1, P5_1_SCB9_SPI_SELECT3},
    {4u, 0u, P6_6, P6_6_SCB4_SPI_SELECT3},
    {3u, 0u, P13_6, P13_6_SCB3_SPI_SELECT3},
    {1u, 0u, P18_6, P18_6_SCB1_SPI_SELECT3},
};

/* Connections for: scb_spi_s_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[21] = {
    {0u, 0u, P0_2, P0_2_SCB0_SPI_CLK},
    {4u, 0u, P1_0, P1_0_SCB4_SPI_CLK},
    {0u, 0u, P1_2, P1_2_SCB0_SPI_CLK},
    {7u, 0u, P2_2, P2_2_SCB7_SPI_CLK},
    {6u, 0u, P3_2, P3_2_SCB6_SPI_CLK},
    {5u, 0u, P4_2, P4_2_SCB5_SPI_CLK},
    {4u, 0u, P6_2, P6_2_SCB4_SPI_CLK},
    {5u, 0u, P7_2, P7_2_SCB5_SPI_CLK},
    {4u, 0u, P10_2, P10_2_SCB4_SPI_CLK},
    {8u, 0u, P12_2, P12_2_SCB8_SPI_CLK},
    {3u, 0u, P13_2, P13_2_SCB3_SPI_CLK},
    {2u, 0u, P14_2, P14_2_SCB2_SPI_CLK},
    {9u, 0u, P15_2, P15_2_SCB9_SPI_CLK},
    {3u, 0u, P17_3, P17_3_SCB3_SPI_CLK},
    {1u, 0u, P18_2, P18_2_SCB1_SPI_CLK},
    {3u, 0u, P18_3, P18_3_SCB3_SPI_CLK},
    {2u, 0u, P19_2, P19_2_SCB2_SPI_CLK},
    {1u, 0u, P20_5, P20_5_SCB1_SPI_CLK},
    {6u, 0u, P22_2, P22_2_SCB6_SPI_CLK},
    {7u, 0u, P23_2, P23_2_SCB7_SPI_CLK},
    {2u, 0u, P23_6, P23_6_SCB2_SPI_CLK},
};

/* Connections for: scb_spi_s_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[20] = {
    {0u, 0u, P0_0, P0_0_SCB0_SPI_MISO},
    {4u, 0u, P0_2, P0_2_SCB4_SPI_MISO},
    {0u, 0u, P1_0, P1_0_SCB0_SPI_MISO},
    {7u, 0u, P2_0, P2_0_SCB7_SPI_MISO},
    {6u, 0u, P3_0, P3_0_SCB6_SPI_MISO},
    {5u, 0u, P4_0, P4_0_SCB5_SPI_MISO},
    {4u, 0u, P6_0, P6_0_SCB4_SPI_MISO},
    {5u, 0u, P7_0, P7_0_SCB5_SPI_MISO},
    {4u, 0u, P10_0, P10_0_SCB4_SPI_MISO},
    {8u, 0u, P12_0, P12_0_SCB8_SPI_MISO},
    {3u, 0u, P13_0, P13_0_SCB3_SPI_MISO},
    {2u, 0u, P14_0, P14_0_SCB2_SPI_MISO},
    {9u, 0u, P15_0, P15_0_SCB9_SPI_MISO},
    {1u, 0u, P18_0, P18_0_SCB1_SPI_MISO},
    {3u, 0u, P18_1, P18_1_SCB3_SPI_MISO},
    {2u, 0u, P19_0, P19_0_SCB2_SPI_MISO},
    {1u, 0u, P20_3, P20_3_SCB1_SPI_MISO},
    {6u, 0u, P21_7, P21_7_SCB6_SPI_MISO},
    {7u, 0u, P23_0, P23_0_SCB7_SPI_MISO},
    {2u, 0u, P23_4, P23_4_SCB2_SPI_MISO},
};

/* Connections for: scb_spi_s_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[20] = {
    {0u, 0u, P0_1, P0_1_SCB0_SPI_MOSI},
    {4u, 0u, P0_3, P0_3_SCB4_SPI_MOSI},
    {0u, 0u, P1_1, P1_1_SCB0_SPI_MOSI},
    {7u, 0u, P2_1, P2_1_SCB7_SPI_MOSI},
    {6u, 0u, P3_1, P3_1_SCB6_SPI_MOSI},
    {5u, 0u, P4_1, P4_1_SCB5_SPI_MOSI},
    {4u, 0u, P6_1, P6_1_SCB4_SPI_MOSI},
    {5u, 0u, P7_1, P7_1_SCB5_SPI_MOSI},
    {4u, 0u, P10_1, P10_1_SCB4_SPI_MOSI},
    {8u, 0u, P12_1, P12_1_SCB8_SPI_MOSI},
    {3u, 0u, P13_1, P13_1_SCB3_SPI_MOSI},
    {2u, 0u, P14_1, P14_1_SCB2_SPI_MOSI},
    {9u, 0u, P15_1, P15_1_SCB9_SPI_MOSI},
    {1u, 0u, P18_1, P18_1_SCB1_SPI_MOSI},
    {3u, 0u, P18_2, P18_2_SCB3_SPI_MOSI},
    {2u, 0u, P19_1, P19_1_SCB2_SPI_MOSI},
    {1u, 0u, P20_4, P20_4_SCB1_SPI_MOSI},
    {6u, 0u, P22_1, P22_1_SCB6_SPI_MOSI},
    {7u, 0u, P23_1, P23_1_SCB7_SPI_MOSI},
    {2u, 0u, P23_5, P23_5_SCB2_SPI_MOSI},
};

/* Connections for: scb_spi_s_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[21] = {
    {0u, 0u, P0_3, P0_3_SCB0_SPI_SELECT0},
    {4u, 0u, P1_1, P1_1_SCB4_SPI_SELECT0},
    {0u, 0u, P1_3, P1_3_SCB0_SPI_SELECT0},
    {7u, 0u, P2_3, P2_3_SCB7_SPI_SELECT0},
    {6u, 0u, P3_3, P3_3_SCB6_SPI_SELECT0},
    {5u, 0u, P4_3, P4_3_SCB5_SPI_SELECT0},
    {4u, 0u, P6_3, P6_3_SCB4_SPI_SELECT0},
    {5u, 0u, P7_3, P7_3_SCB5_SPI_SELECT0},
    {4u, 0u, P10_3, P10_3_SCB4_SPI_SELECT0},
    {8u, 0u, P12_3, P12_3_SCB8_SPI_SELECT0},
    {3u, 0u, P13_3, P13_3_SCB3_SPI_SELECT0},
    {2u, 0u, P14_3, P14_3_SCB2_SPI_SELECT0},
    {9u, 0u, P15_3, P15_3_SCB9_SPI_SELECT0},
    {3u, 0u, P17_4, P17_4_SCB3_SPI_SELECT0},
    {1u, 0u, P18_3, P18_3_SCB1_SPI_SELECT0},
    {3u, 0u, P18_4, P18_4_SCB3_SPI_SELECT0},
    {2u, 0u, P19_3, P19_3_SCB2_SPI_SELECT0},
    {1u, 0u, P20_6, P20_6_SCB1_SPI_SELECT0},
    {6u, 0u, P22_3, P22_3_SCB6_SPI_SELECT0},
    {7u, 0u, P23_3, P23_3_SCB7_SPI_SELECT0},
    {2u, 0u, P23_7, P23_7_SCB2_SPI_SELECT0},
};

/* Connections for: scb_spi_s_select1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select1[16] = {
    {0u, 0u, P2_0, P2_0_SCB0_SPI_SELECT1},
    {7u, 0u, P2_4, P2_4_SCB7_SPI_SELECT1},
    {6u, 0u, P3_4, P3_4_SCB6_SPI_SELECT1},
    {5u, 0u, P4_4, P4_4_SCB5_SPI_SELECT1},
    {4u, 0u, P6_4, P6_4_SCB4_SPI_SELECT1},
    {5u, 0u, P7_4, P7_4_SCB5_SPI_SELECT1},
    {4u, 0u, P10_4, P10_4_SCB4_SPI_SELECT1},
    {8u, 0u, P12_4, P12_4_SCB8_SPI_SELECT1},
    {3u, 0u, P13_4, P13_4_SCB3_SPI_SELECT1},
    {2u, 0u, P14_4, P14_4_SCB2_SPI_SELECT1},
    {3u, 0u, P17_5, P17_5_SCB3_SPI_SELECT1},
    {1u, 0u, P18_4, P18_4_SCB1_SPI_SELECT1},
    {2u, 0u, P19_4, P19_4_SCB2_SPI_SELECT1},
    {1u, 0u, P20_7, P20_7_SCB1_SPI_SELECT1},
    {6u, 0u, P22_4, P22_4_SCB6_SPI_SELECT1},
    {7u, 0u, P23_4, P23_4_SCB7_SPI_SELECT1},
};

/* Connections for: scb_spi_s_select2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select2[15] = {
    {0u, 0u, P2_1, P2_1_SCB0_SPI_SELECT2},
    {7u, 0u, P2_5, P2_5_SCB7_SPI_SELECT2},
    {6u, 0u, P3_5, P3_5_SCB6_SPI_SELECT2},
    {5u, 0u, P5_0, P5_0_SCB5_SPI_SELECT2},
    {4u, 0u, P6_5, P6_5_SCB4_SPI_SELECT2},
    {5u, 0u, P7_5, P7_5_SCB5_SPI_SELECT2},
    {4u, 0u, P10_5, P10_5_SCB4_SPI_SELECT2},
    {3u, 0u, P13_5, P13_5_SCB3_SPI_SELECT2},
    {2u, 0u, P14_5, P14_5_SCB2_SPI_SELECT2},
    {3u, 0u, P17_6, P17_6_SCB3_SPI_SELECT2},
    {1u, 0u, P18_5, P18_5_SCB1_SPI_SELECT2},
    {2u, 0u, P20_0, P20_0_SCB2_SPI_SELECT2},
    {1u, 0u, P21_0, P21_0_SCB1_SPI_SELECT2},
    {6u, 0u, P22_5, P22_5_SCB6_SPI_SELECT2},
    {7u, 0u, P23_5, P23_5_SCB7_SPI_SELECT2},
};

/* Connections for: scb_spi_s_select3 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select3[5] = {
    {0u, 0u, P2_2, P2_2_SCB0_SPI_SELECT3},
    {9u, 0u, P5_1, P5_1_SCB9_SPI_SELECT3},
    {4u, 0u, P6_6, P6_6_SCB4_SPI_SELECT3},
    {3u, 0u, P13_6, P13_6_SCB3_SPI_SELECT3},
    {1u, 0u, P18_6, P18_6_SCB1_SPI_SELECT3},
};

/* Connections for: scb_uart_cts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[17] = {
    {0u, 0u, P0_3, P0_3_SCB0_UART_CTS},
    {7u, 0u, P2_3, P2_3_SCB7_UART_CTS},
    {6u, 0u, P3_3, P3_3_SCB6_UART_CTS},
    {5u, 0u, P4_3, P4_3_SCB5_UART_CTS},
    {4u, 0u, P6_3, P6_3_SCB4_UART_CTS},
    {5u, 0u, P7_3, P7_3_SCB5_UART_CTS},
    {4u, 0u, P10_3, P10_3_SCB4_UART_CTS},
    {8u, 0u, P12_3, P12_3_SCB8_UART_CTS},
    {3u, 0u, P13_3, P13_3_SCB3_UART_CTS},
    {2u, 0u, P14_3, P14_3_SCB2_UART_CTS},
    {9u, 0u, P15_3, P15_3_SCB9_UART_CTS},
    {3u, 0u, P17_4, P17_4_SCB3_UART_CTS},
    {1u, 0u, P18_3, P18_3_SCB1_UART_CTS},
    {2u, 0u, P19_3, P19_3_SCB2_UART_CTS},
    {1u, 0u, P20_6, P20_6_SCB1_UART_CTS},
    {6u, 0u, P22_3, P22_3_SCB6_UART_CTS},
    {7u, 0u, P23_3, P23_3_SCB7_UART_CTS},
};

/* Connections for: scb_uart_rts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[17] = {
    {0u, 0u, P0_2, P0_2_SCB0_UART_RTS},
    {7u, 0u, P2_2, P2_2_SCB7_UART_RTS},
    {6u, 0u, P3_2, P3_2_SCB6_UART_RTS},
    {5u, 0u, P4_2, P4_2_SCB5_UART_RTS},
    {4u, 0u, P6_2, P6_2_SCB4_UART_RTS},
    {5u, 0u, P7_2, P7_2_SCB5_UART_RTS},
    {4u, 0u, P10_2, P10_2_SCB4_UART_RTS},
    {8u, 0u, P12_2, P12_2_SCB8_UART_RTS},
    {3u, 0u, P13_2, P13_2_SCB3_UART_RTS},
    {2u, 0u, P14_2, P14_2_SCB2_UART_RTS},
    {9u, 0u, P15_2, P15_2_SCB9_UART_RTS},
    {3u, 0u, P17_3, P17_3_SCB3_UART_RTS},
    {1u, 0u, P18_2, P18_2_SCB1_UART_RTS},
    {2u, 0u, P19_2, P19_2_SCB2_UART_RTS},
    {1u, 0u, P20_5, P20_5_SCB1_UART_RTS},
    {6u, 0u, P22_2, P22_2_SCB6_UART_RTS},
    {7u, 0u, P23_2, P23_2_SCB7_UART_RTS},
};

/* Connections for: scb_uart_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[17] = {
    {0u, 0u, P0_0, P0_0_SCB0_UART_RX},
    {7u, 0u, P2_0, P2_0_SCB7_UART_RX},
    {6u, 0u, P3_0, P3_0_SCB6_UART_RX},
    {5u, 0u, P4_0, P4_0_SCB5_UART_RX},
    {4u, 0u, P6_0, P6_0_SCB4_UART_RX},
    {5u, 0u, P7_0, P7_0_SCB5_UART_RX},
    {4u, 0u, P10_0, P10_0_SCB4_UART_RX},
    {8u, 0u, P12_0, P12_0_SCB8_UART_RX},
    {3u, 0u, P13_0, P13_0_SCB3_UART_RX},
    {2u, 0u, P14_0, P14_0_SCB2_UART_RX},
    {9u, 0u, P15_0, P15_0_SCB9_UART_RX},
    {3u, 0u, P17_1, P17_1_SCB3_UART_RX},
    {1u, 0u, P18_0, P18_0_SCB1_UART_RX},
    {2u, 0u, P19_0, P19_0_SCB2_UART_RX},
    {1u, 0u, P20_3, P20_3_SCB1_UART_RX},
    {6u, 0u, P21_7, P21_7_SCB6_UART_RX},
    {7u, 0u, P23_0, P23_0_SCB7_UART_RX},
};

/* Connections for: scb_uart_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[17] = {
    {0u, 0u, P0_1, P0_1_SCB0_UART_TX},
    {7u, 0u, P2_1, P2_1_SCB7_UART_TX},
    {6u, 0u, P3_1, P3_1_SCB6_UART_TX},
    {5u, 0u, P4_1, P4_1_SCB5_UART_TX},
    {4u, 0u, P6_1, P6_1_SCB4_UART_TX},
    {5u, 0u, P7_1, P7_1_SCB5_UART_TX},
    {4u, 0u, P10_1, P10_1_SCB4_UART_TX},
    {8u, 0u, P12_1, P12_1_SCB8_UART_TX},
    {3u, 0u, P13_1, P13_1_SCB3_UART_TX},
    {2u, 0u, P14_1, P14_1_SCB2_UART_TX},
    {9u, 0u, P15_1, P15_1_SCB9_UART_TX},
    {3u, 0u, P17_2, P17_2_SCB3_UART_TX},
    {1u, 0u, P18_1, P18_1_SCB1_UART_TX},
    {2u, 0u, P19_1, P19_1_SCB2_UART_TX},
    {1u, 0u, P20_4, P20_4_SCB1_UART_TX},
    {6u, 0u, P22_1, P22_1_SCB6_UART_TX},
    {7u, 0u, P23_1, P23_1_SCB7_UART_TX},
};

/* Connections for: sdhc_card_cmd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_cmd[1] = {
    {0u, 0u, P6_3, P6_3_SDHC0_CARD_CMD},
};

/* Connections for: sdhc_card_dat_3to0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_dat_3to0[4] = {
    {0u, 0u, P7_1, P7_1_SDHC0_CARD_DAT_3TO00},
    {0u, 1u, P7_2, P7_2_SDHC0_CARD_DAT_3TO01},
    {0u, 2u, P7_3, P7_3_SDHC0_CARD_DAT_3TO02},
    {0u, 3u, P7_4, P7_4_SDHC0_CARD_DAT_3TO03},
};

/* Connections for: sdhc_card_dat_7to4 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_dat_7to4[4] = {
    {0u, 0u, P7_5, P7_5_SDHC0_CARD_DAT_7TO40},
    {0u, 1u, P8_0, P8_0_SDHC0_CARD_DAT_7TO41},
    {0u, 2u, P8_1, P8_1_SDHC0_CARD_DAT_7TO42},
    {0u, 3u, P8_2, P8_2_SDHC0_CARD_DAT_7TO43},
};

/* Connections for: sdhc_card_detect_n */
const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_detect_n[1] = {
    {0u, 0u, P6_5, P6_5_SDHC0_CARD_DETECT_N},
};

/* Connections for: sdhc_card_if_pwr_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_if_pwr_en[1] = {
    {0u, 0u, P7_0, P7_0_SDHC0_CARD_IF_PWR_EN},
};

/* Connections for: sdhc_card_mech_write_prot */
const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_mech_write_prot[1] = {
    {0u, 0u, P6_2, P6_2_SDHC0_CARD_MECH_WRITE_PROT},
};

/* Connections for: sdhc_clk_card */
const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_clk_card[1] = {
    {0u, 0u, P6_4, P6_4_SDHC0_CLK_CARD},
};

/* Connections for: smif_spi_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_clk[1] = {
    {0u, 0u, P6_3, P6_3_SMIF0_SPIHB_CLK},
};

/* Connections for: smif_spi_data0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data0[1] = {
    {0u, 0u, P7_1, P7_1_SMIF0_SPIHB_DATA0},
};

/* Connections for: smif_spi_data1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data1[1] = {
    {0u, 0u, P7_2, P7_2_SMIF0_SPIHB_DATA1},
};

/* Connections for: smif_spi_data2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data2[1] = {
    {0u, 0u, P7_3, P7_3_SMIF0_SPIHB_DATA2},
};

/* Connections for: smif_spi_data3 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data3[1] = {
    {0u, 0u, P7_4, P7_4_SMIF0_SPIHB_DATA3},
};

/* Connections for: smif_spi_data4 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data4[1] = {
    {0u, 0u, P7_5, P7_5_SMIF0_SPIHB_DATA4},
};

/* Connections for: smif_spi_data5 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data5[1] = {
    {0u, 0u, P8_0, P8_0_SMIF0_SPIHB_DATA5},
};

/* Connections for: smif_spi_data6 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data6[1] = {
    {0u, 0u, P8_1, P8_1_SMIF0_SPIHB_DATA6},
};

/* Connections for: smif_spi_data7 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data7[1] = {
    {0u, 0u, P8_2, P8_2_SMIF0_SPIHB_DATA7},
};

/* Connections for: smif_spi_rwds */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_rwds[1] = {
    {0u, 0u, P6_4, P6_4_SMIF0_SPIHB_RWDS},
};

/* Connections for: smif_spi_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_select0[1] = {
    {0u, 0u, P6_5, P6_5_SMIF0_SPIHB_SELECT0},
};

/* Connections for: smif_spi_select1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_select1[1] = {
    {0u, 0u, P7_0, P7_0_SMIF0_SPIHB_SELECT1},
};

/* Connections for: tcpwm_line */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[181] = {
    {2u, 0u, P0_0, P0_0_TCPWM0_LINE512},
    {4u, 18u, P0_0, P0_0_TCPWM1_LINE18},
    {4u, 17u, P0_1, P0_1_TCPWM1_LINE17},
    {4u, 14u, P0_2, P0_2_TCPWM1_LINE14},
    {4u, 13u, P0_3, P0_3_TCPWM1_LINE13},
    {4u, 12u, P1_0, P1_0_TCPWM1_LINE12},
    {6u, 4u, P1_0, P1_0_TCPWM1_LINE516},
    {4u, 11u, P1_1, P1_1_TCPWM1_LINE11},
    {6u, 5u, P1_1, P1_1_TCPWM1_LINE517},
    {4u, 10u, P1_2, P1_2_TCPWM1_LINE10},
    {6u, 6u, P1_2, P1_2_TCPWM1_LINE518},
    {4u, 8u, P1_3, P1_3_TCPWM1_LINE8},
    {6u, 7u, P1_3, P1_3_TCPWM1_LINE519},
    {4u, 7u, P2_0, P2_0_TCPWM1_LINE7},
    {4u, 6u, P2_1, P2_1_TCPWM1_LINE6},
    {4u, 5u, P2_2, P2_2_TCPWM1_LINE5},
    {4u, 4u, P2_3, P2_3_TCPWM1_LINE4},
    {4u, 3u, P2_4, P2_4_TCPWM1_LINE3},
    {4u, 2u, P2_5, P2_5_TCPWM1_LINE2},
    {4u, 1u, P3_0, P3_0_TCPWM1_LINE1},
    {4u, 0u, P3_1, P3_1_TCPWM1_LINE0},
    {5u, 3u, P3_2, P3_2_TCPWM1_LINE259},
    {5u, 2u, P3_3, P3_3_TCPWM1_LINE258},
    {5u, 1u, P3_4, P3_4_TCPWM1_LINE257},
    {5u, 0u, P3_5, P3_5_TCPWM1_LINE256},
    {4u, 4u, P4_0, P4_0_TCPWM1_LINE4},
    {4u, 5u, P4_1, P4_1_TCPWM1_LINE5},
    {4u, 6u, P4_2, P4_2_TCPWM1_LINE6},
    {4u, 7u, P4_3, P4_3_TCPWM1_LINE7},
    {4u, 8u, P4_4, P4_4_TCPWM1_LINE8},
    {1u, 0u, P5_0, P5_0_TCPWM0_LINE256},
    {4u, 9u, P5_0, P5_0_TCPWM1_LINE9},
    {6u, 10u, P5_0, P5_0_TCPWM1_LINE522},
    {4u, 10u, P5_1, P5_1_TCPWM1_LINE10},
    {4u, 11u, P5_2, P5_2_TCPWM1_LINE11},
    {4u, 12u, P5_3, P5_3_TCPWM1_LINE12},
    {4u, 13u, P5_4, P5_4_TCPWM1_LINE13},
    {6u, 11u, P5_4, P5_4_TCPWM1_LINE523},
    {4u, 14u, P5_5, P5_5_TCPWM1_LINE14},
    {0u, 0u, P6_0, P6_0_TCPWM0_LINE0},
    {5u, 0u, P6_0, P6_0_TCPWM1_LINE256},
    {4u, 0u, P6_1, P6_1_TCPWM1_LINE0},
    {5u, 1u, P6_2, P6_2_TCPWM1_LINE257},
    {6u, 12u, P6_2, P6_2_TCPWM1_LINE524},
    {4u, 1u, P6_3, P6_3_TCPWM1_LINE1},
    {5u, 2u, P6_4, P6_4_TCPWM1_LINE258},
    {4u, 2u, P6_5, P6_5_TCPWM1_LINE2},
    {5u, 3u, P6_6, P6_6_TCPWM1_LINE259},
    {4u, 3u, P6_7, P6_7_TCPWM1_LINE3},
    {0u, 1u, P7_0, P7_0_TCPWM0_LINE1},
    {5u, 4u, P7_0, P7_0_TCPWM1_LINE260},
    {4u, 15u, P7_1, P7_1_TCPWM1_LINE15},
    {5u, 5u, P7_2, P7_2_TCPWM1_LINE261},
    {4u, 16u, P7_3, P7_3_TCPWM1_LINE16},
    {5u, 6u, P7_4, P7_4_TCPWM1_LINE262},
    {2u, 2u, P7_5, P7_5_TCPWM0_LINE514},
    {4u, 17u, P7_5, P7_5_TCPWM1_LINE17},
    {5u, 7u, P7_6, P7_6_TCPWM1_LINE263},
    {4u, 18u, P7_7, P7_7_TCPWM1_LINE18},
    {4u, 19u, P8_0, P8_0_TCPWM1_LINE19},
    {6u, 8u, P8_0, P8_0_TCPWM1_LINE520},
    {4u, 20u, P8_1, P8_1_TCPWM1_LINE20},
    {4u, 21u, P8_2, P8_2_TCPWM1_LINE21},
    {4u, 22u, P8_3, P8_3_TCPWM1_LINE22},
    {4u, 23u, P8_4, P8_4_TCPWM1_LINE23},
    {4u, 24u, P9_0, P9_0_TCPWM1_LINE24},
    {6u, 9u, P9_0, P9_0_TCPWM1_LINE521},
    {4u, 25u, P9_1, P9_1_TCPWM1_LINE25},
    {4u, 26u, P9_2, P9_2_TCPWM1_LINE26},
    {4u, 27u, P9_3, P9_3_TCPWM1_LINE27},
    {4u, 28u, P10_0, P10_0_TCPWM1_LINE28},
    {6u, 10u, P10_0, P10_0_TCPWM1_LINE522},
    {4u, 29u, P10_1, P10_1_TCPWM1_LINE29},
    {4u, 30u, P10_2, P10_2_TCPWM1_LINE30},
    {4u, 31u, P10_3, P10_3_TCPWM1_LINE31},
    {4u, 32u, P10_4, P10_4_TCPWM1_LINE32},
    {6u, 11u, P10_4, P10_4_TCPWM1_LINE523},
    {4u, 33u, P10_5, P10_5_TCPWM1_LINE33},
    {4u, 34u, P10_6, P10_6_TCPWM1_LINE34},
    {4u, 35u, P10_7, P10_7_TCPWM1_LINE35},
    {4u, 61u, P11_0, P11_0_TCPWM1_LINE61},
    {4u, 60u, P11_1, P11_1_TCPWM1_LINE60},
    {4u, 59u, P11_2, P11_2_TCPWM1_LINE59},
    {2u, 1u, P12_0, P12_0_TCPWM0_LINE513},
    {4u, 36u, P12_0, P12_0_TCPWM1_LINE36},
    {4u, 37u, P12_1, P12_1_TCPWM1_LINE37},
    {4u, 38u, P12_2, P12_2_TCPWM1_LINE38},
    {4u, 39u, P12_3, P12_3_TCPWM1_LINE39},
    {4u, 40u, P12_4, P12_4_TCPWM1_LINE40},
    {4u, 41u, P12_5, P12_5_TCPWM1_LINE41},
    {4u, 42u, P12_6, P12_6_TCPWM1_LINE42},
    {4u, 43u, P12_7, P12_7_TCPWM1_LINE43},
    {5u, 8u, P13_0, P13_0_TCPWM1_LINE264},
    {4u, 44u, P13_1, P13_1_TCPWM1_LINE44},
    {0u, 2u, P13_2, P13_2_TCPWM0_LINE2},
    {5u, 9u, P13_2, P13_2_TCPWM1_LINE265},
    {4u, 45u, P13_3, P13_3_TCPWM1_LINE45},
    {5u, 10u, P13_4, P13_4_TCPWM1_LINE266},
    {6u, 4u, P13_4, P13_4_TCPWM1_LINE516},
    {4u, 46u, P13_5, P13_5_TCPWM1_LINE46},
    {5u, 11u, P13_6, P13_6_TCPWM1_LINE267},
    {6u, 5u, P13_6, P13_6_TCPWM1_LINE517},
    {4u, 47u, P13_7, P13_7_TCPWM1_LINE47},
    {1u, 1u, P14_0, P14_0_TCPWM0_LINE257},
    {4u, 48u, P14_0, P14_0_TCPWM1_LINE48},
    {6u, 6u, P14_0, P14_0_TCPWM1_LINE518},
    {4u, 49u, P14_1, P14_1_TCPWM1_LINE49},
    {4u, 50u, P14_2, P14_2_TCPWM1_LINE50},
    {6u, 7u, P14_2, P14_2_TCPWM1_LINE519},
    {4u, 51u, P14_3, P14_3_TCPWM1_LINE51},
    {4u, 52u, P14_4, P14_4_TCPWM1_LINE52},
    {4u, 53u, P14_5, P14_5_TCPWM1_LINE53},
    {4u, 54u, P14_6, P14_6_TCPWM1_LINE54},
    {4u, 55u, P14_7, P14_7_TCPWM1_LINE55},
    {4u, 56u, P15_0, P15_0_TCPWM1_LINE56},
    {4u, 57u, P15_1, P15_1_TCPWM1_LINE57},
    {4u, 58u, P15_2, P15_2_TCPWM1_LINE58},
    {4u, 59u, P15_3, P15_3_TCPWM1_LINE59},
    {4u, 62u, P16_3, P16_3_TCPWM1_LINE62},
    {4u, 61u, P17_0, P17_0_TCPWM1_LINE61},
    {4u, 60u, P17_1, P17_1_TCPWM1_LINE60},
    {4u, 59u, P17_2, P17_2_TCPWM1_LINE59},
    {4u, 58u, P17_3, P17_3_TCPWM1_LINE58},
    {6u, 3u, P17_3, P17_3_TCPWM1_LINE515},
    {4u, 57u, P17_4, P17_4_TCPWM1_LINE57},
    {4u, 56u, P17_5, P17_5_TCPWM1_LINE56},
    {6u, 2u, P17_5, P17_5_TCPWM1_LINE514},
    {5u, 4u, P17_6, P17_6_TCPWM1_LINE260},
    {5u, 5u, P17_7, P17_7_TCPWM1_LINE261},
    {5u, 6u, P18_0, P18_0_TCPWM1_LINE262},
    {6u, 0u, P18_0, P18_0_TCPWM1_LINE512},
    {5u, 7u, P18_1, P18_1_TCPWM1_LINE263},
    {4u, 55u, P18_2, P18_2_TCPWM1_LINE55},
    {6u, 1u, P18_2, P18_2_TCPWM1_LINE513},
    {4u, 54u, P18_3, P18_3_TCPWM1_LINE54},
    {1u, 2u, P18_4, P18_4_TCPWM0_LINE258},
    {4u, 53u, P18_4, P18_4_TCPWM1_LINE53},
    {6u, 2u, P18_4, P18_4_TCPWM1_LINE514},
    {4u, 52u, P18_5, P18_5_TCPWM1_LINE52},
    {4u, 51u, P18_6, P18_6_TCPWM1_LINE51},
    {6u, 3u, P18_6, P18_6_TCPWM1_LINE515},
    {4u, 50u, P18_7, P18_7_TCPWM1_LINE50},
    {5u, 3u, P19_0, P19_0_TCPWM1_LINE259},
    {4u, 26u, P19_1, P19_1_TCPWM1_LINE26},
    {4u, 27u, P19_2, P19_2_TCPWM1_LINE27},
    {4u, 28u, P19_3, P19_3_TCPWM1_LINE28},
    {4u, 29u, P19_4, P19_4_TCPWM1_LINE29},
    {4u, 30u, P20_0, P20_0_TCPWM1_LINE30},
    {4u, 49u, P20_1, P20_1_TCPWM1_LINE49},
    {4u, 48u, P20_2, P20_2_TCPWM1_LINE48},
    {4u, 47u, P20_3, P20_3_TCPWM1_LINE47},
    {4u, 46u, P20_4, P20_4_TCPWM1_LINE46},
    {4u, 45u, P20_5, P20_5_TCPWM1_LINE45},
    {4u, 44u, P20_6, P20_6_TCPWM1_LINE44},
    {4u, 43u, P20_7, P20_7_TCPWM1_LINE43},
    {4u, 42u, P21_0, P21_0_TCPWM1_LINE42},
    {4u, 41u, P21_1, P21_1_TCPWM1_LINE41},
    {4u, 40u, P21_2, P21_2_TCPWM1_LINE40},
    {4u, 39u, P21_3, P21_3_TCPWM1_LINE39},
    {4u, 38u, P21_4, P21_4_TCPWM1_LINE38},
    {4u, 34u, P21_5, P21_5_TCPWM1_LINE34},
    {4u, 37u, P21_5, P21_5_TCPWM1_LINE37},
    {4u, 36u, P21_6, P21_6_TCPWM1_LINE36},
    {4u, 35u, P21_7, P21_7_TCPWM1_LINE35},
    {4u, 33u, P22_1, P22_1_TCPWM1_LINE33},
    {4u, 32u, P22_2, P22_2_TCPWM1_LINE32},
    {4u, 31u, P22_3, P22_3_TCPWM1_LINE31},
    {4u, 30u, P22_4, P22_4_TCPWM1_LINE30},
    {4u, 29u, P22_5, P22_5_TCPWM1_LINE29},
    {6u, 8u, P22_5, P22_5_TCPWM1_LINE520},
    {4u, 28u, P22_6, P22_6_TCPWM1_LINE28},
    {4u, 27u, P22_7, P22_7_TCPWM1_LINE27},
    {5u, 8u, P23_0, P23_0_TCPWM1_LINE264},
    {5u, 9u, P23_1, P23_1_TCPWM1_LINE265},
    {5u, 10u, P23_2, P23_2_TCPWM1_LINE266},
    {5u, 11u, P23_3, P23_3_TCPWM1_LINE267},
    {4u, 25u, P23_4, P23_4_TCPWM1_LINE25},
    {6u, 9u, P23_4, P23_4_TCPWM1_LINE521},
    {4u, 24u, P23_5, P23_5_TCPWM1_LINE24},
    {4u, 23u, P23_6, P23_6_TCPWM1_LINE23},
    {4u, 22u, P23_7, P23_7_TCPWM1_LINE22},
};

/* Connections for: tcpwm_line_compl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line_compl[182] = {
    {4u, 22u, P0_0, P0_0_TCPWM1_LINE_COMPL22},
    {2u, 0u, P0_1, P0_1_TCPWM0_LINE_COMPL512},
    {4u, 18u, P0_1, P0_1_TCPWM1_LINE_COMPL18},
    {4u, 17u, P0_2, P0_2_TCPWM1_LINE_COMPL17},
    {4u, 14u, P0_3, P0_3_TCPWM1_LINE_COMPL14},
    {4u, 13u, P1_0, P1_0_TCPWM1_LINE_COMPL13},
    {4u, 12u, P1_1, P1_1_TCPWM1_LINE_COMPL12},
    {4u, 11u, P1_2, P1_2_TCPWM1_LINE_COMPL11},
    {4u, 10u, P1_3, P1_3_TCPWM1_LINE_COMPL10},
    {4u, 8u, P2_0, P2_0_TCPWM1_LINE_COMPL8},
    {4u, 7u, P2_1, P2_1_TCPWM1_LINE_COMPL7},
    {4u, 6u, P2_2, P2_2_TCPWM1_LINE_COMPL6},
    {4u, 5u, P2_3, P2_3_TCPWM1_LINE_COMPL5},
    {4u, 4u, P2_4, P2_4_TCPWM1_LINE_COMPL4},
    {6u, 4u, P2_4, P2_4_TCPWM1_LINE_COMPL516},
    {4u, 3u, P2_5, P2_5_TCPWM1_LINE_COMPL3},
    {6u, 5u, P2_5, P2_5_TCPWM1_LINE_COMPL517},
    {4u, 2u, P3_0, P3_0_TCPWM1_LINE_COMPL2},
    {6u, 6u, P3_0, P3_0_TCPWM1_LINE_COMPL518},
    {4u, 1u, P3_1, P3_1_TCPWM1_LINE_COMPL1},
    {6u, 7u, P3_1, P3_1_TCPWM1_LINE_COMPL519},
    {4u, 0u, P3_2, P3_2_TCPWM1_LINE_COMPL0},
    {5u, 3u, P3_3, P3_3_TCPWM1_LINE_COMPL259},
    {5u, 2u, P3_4, P3_4_TCPWM1_LINE_COMPL258},
    {5u, 1u, P3_5, P3_5_TCPWM1_LINE_COMPL257},
    {5u, 0u, P4_0, P4_0_TCPWM1_LINE_COMPL256},
    {4u, 4u, P4_1, P4_1_TCPWM1_LINE_COMPL4},
    {4u, 5u, P4_2, P4_2_TCPWM1_LINE_COMPL5},
    {4u, 6u, P4_3, P4_3_TCPWM1_LINE_COMPL6},
    {4u, 7u, P4_4, P4_4_TCPWM1_LINE_COMPL7},
    {4u, 8u, P5_0, P5_0_TCPWM1_LINE_COMPL8},
    {1u, 0u, P5_1, P5_1_TCPWM0_LINE_COMPL256},
    {4u, 9u, P5_1, P5_1_TCPWM1_LINE_COMPL9},
    {6u, 10u, P5_1, P5_1_TCPWM1_LINE_COMPL522},
    {4u, 10u, P5_2, P5_2_TCPWM1_LINE_COMPL10},
    {4u, 11u, P5_3, P5_3_TCPWM1_LINE_COMPL11},
    {4u, 12u, P5_4, P5_4_TCPWM1_LINE_COMPL12},
    {4u, 13u, P5_5, P5_5_TCPWM1_LINE_COMPL13},
    {6u, 11u, P5_5, P5_5_TCPWM1_LINE_COMPL523},
    {4u, 14u, P6_0, P6_0_TCPWM1_LINE_COMPL14},
    {5u, 0u, P6_1, P6_1_TCPWM1_LINE_COMPL256},
    {0u, 0u, P6_2, P6_2_TCPWM0_LINE_COMPL0},
    {4u, 0u, P6_2, P6_2_TCPWM1_LINE_COMPL0},
    {5u, 1u, P6_3, P6_3_TCPWM1_LINE_COMPL257},
    {6u, 12u, P6_3, P6_3_TCPWM1_LINE_COMPL524},
    {4u, 1u, P6_4, P6_4_TCPWM1_LINE_COMPL1},
    {5u, 2u, P6_5, P6_5_TCPWM1_LINE_COMPL258},
    {4u, 2u, P6_6, P6_6_TCPWM1_LINE_COMPL2},
    {5u, 3u, P6_7, P6_7_TCPWM1_LINE_COMPL259},
    {4u, 3u, P7_0, P7_0_TCPWM1_LINE_COMPL3},
    {5u, 4u, P7_1, P7_1_TCPWM1_LINE_COMPL260},
    {0u, 1u, P7_2, P7_2_TCPWM0_LINE_COMPL1},
    {4u, 15u, P7_2, P7_2_TCPWM1_LINE_COMPL15},
    {5u, 5u, P7_3, P7_3_TCPWM1_LINE_COMPL261},
    {4u, 16u, P7_4, P7_4_TCPWM1_LINE_COMPL16},
    {5u, 6u, P7_5, P7_5_TCPWM1_LINE_COMPL262},
    {4u, 17u, P7_6, P7_6_TCPWM1_LINE_COMPL17},
    {5u, 7u, P7_7, P7_7_TCPWM1_LINE_COMPL263},
    {2u, 2u, P8_0, P8_0_TCPWM0_LINE_COMPL514},
    {4u, 18u, P8_0, P8_0_TCPWM1_LINE_COMPL18},
    {4u, 19u, P8_1, P8_1_TCPWM1_LINE_COMPL19},
    {6u, 8u, P8_1, P8_1_TCPWM1_LINE_COMPL520},
    {4u, 20u, P8_2, P8_2_TCPWM1_LINE_COMPL20},
    {4u, 21u, P8_3, P8_3_TCPWM1_LINE_COMPL21},
    {4u, 22u, P8_4, P8_4_TCPWM1_LINE_COMPL22},
    {4u, 23u, P9_0, P9_0_TCPWM1_LINE_COMPL23},
    {4u, 24u, P9_1, P9_1_TCPWM1_LINE_COMPL24},
    {6u, 9u, P9_1, P9_1_TCPWM1_LINE_COMPL521},
    {4u, 25u, P9_2, P9_2_TCPWM1_LINE_COMPL25},
    {4u, 26u, P9_3, P9_3_TCPWM1_LINE_COMPL26},
    {4u, 27u, P10_0, P10_0_TCPWM1_LINE_COMPL27},
    {4u, 28u, P10_1, P10_1_TCPWM1_LINE_COMPL28},
    {6u, 10u, P10_1, P10_1_TCPWM1_LINE_COMPL522},
    {4u, 29u, P10_2, P10_2_TCPWM1_LINE_COMPL29},
    {4u, 30u, P10_3, P10_3_TCPWM1_LINE_COMPL30},
    {4u, 31u, P10_4, P10_4_TCPWM1_LINE_COMPL31},
    {4u, 32u, P10_5, P10_5_TCPWM1_LINE_COMPL32},
    {6u, 11u, P10_5, P10_5_TCPWM1_LINE_COMPL523},
    {4u, 33u, P10_6, P10_6_TCPWM1_LINE_COMPL33},
    {4u, 34u, P10_7, P10_7_TCPWM1_LINE_COMPL34},
    {4u, 62u, P11_0, P11_0_TCPWM1_LINE_COMPL62},
    {4u, 61u, P11_1, P11_1_TCPWM1_LINE_COMPL61},
    {4u, 60u, P11_2, P11_2_TCPWM1_LINE_COMPL60},
    {4u, 35u, P12_0, P12_0_TCPWM1_LINE_COMPL35},
    {2u, 1u, P12_1, P12_1_TCPWM0_LINE_COMPL513},
    {4u, 36u, P12_1, P12_1_TCPWM1_LINE_COMPL36},
    {4u, 37u, P12_2, P12_2_TCPWM1_LINE_COMPL37},
    {4u, 38u, P12_3, P12_3_TCPWM1_LINE_COMPL38},
    {4u, 39u, P12_4, P12_4_TCPWM1_LINE_COMPL39},
    {4u, 40u, P12_5, P12_5_TCPWM1_LINE_COMPL40},
    {4u, 41u, P12_6, P12_6_TCPWM1_LINE_COMPL41},
    {4u, 42u, P12_7, P12_7_TCPWM1_LINE_COMPL42},
    {4u, 43u, P13_0, P13_0_TCPWM1_LINE_COMPL43},
    {0u, 2u, P13_1, P13_1_TCPWM0_LINE_COMPL2},
    {5u, 8u, P13_1, P13_1_TCPWM1_LINE_COMPL264},
    {4u, 44u, P13_2, P13_2_TCPWM1_LINE_COMPL44},
    {5u, 9u, P13_3, P13_3_TCPWM1_LINE_COMPL265},
    {4u, 45u, P13_4, P13_4_TCPWM1_LINE_COMPL45},
    {5u, 10u, P13_5, P13_5_TCPWM1_LINE_COMPL266},
    {6u, 4u, P13_5, P13_5_TCPWM1_LINE_COMPL516},
    {4u, 46u, P13_6, P13_6_TCPWM1_LINE_COMPL46},
    {5u, 11u, P13_7, P13_7_TCPWM1_LINE_COMPL267},
    {6u, 5u, P13_7, P13_7_TCPWM1_LINE_COMPL517},
    {4u, 47u, P14_0, P14_0_TCPWM1_LINE_COMPL47},
    {1u, 1u, P14_1, P14_1_TCPWM0_LINE_COMPL257},
    {4u, 48u, P14_1, P14_1_TCPWM1_LINE_COMPL48},
    {6u, 6u, P14_1, P14_1_TCPWM1_LINE_COMPL518},
    {4u, 49u, P14_2, P14_2_TCPWM1_LINE_COMPL49},
    {4u, 50u, P14_3, P14_3_TCPWM1_LINE_COMPL50},
    {6u, 7u, P14_3, P14_3_TCPWM1_LINE_COMPL519},
    {4u, 51u, P14_4, P14_4_TCPWM1_LINE_COMPL51},
    {4u, 52u, P14_5, P14_5_TCPWM1_LINE_COMPL52},
    {4u, 53u, P14_6, P14_6_TCPWM1_LINE_COMPL53},
    {4u, 54u, P14_7, P14_7_TCPWM1_LINE_COMPL54},
    {4u, 55u, P15_0, P15_0_TCPWM1_LINE_COMPL55},
    {4u, 56u, P15_1, P15_1_TCPWM1_LINE_COMPL56},
    {4u, 57u, P15_2, P15_2_TCPWM1_LINE_COMPL57},
    {4u, 58u, P15_3, P15_3_TCPWM1_LINE_COMPL58},
    {4u, 62u, P16_3, P16_3_TCPWM1_LINE_COMPL62},
    {6u, 1u, P16_3, P16_3_TCPWM1_LINE_COMPL513},
    {4u, 62u, P17_0, P17_0_TCPWM1_LINE_COMPL62},
    {4u, 61u, P17_1, P17_1_TCPWM1_LINE_COMPL61},
    {4u, 60u, P17_2, P17_2_TCPWM1_LINE_COMPL60},
    {4u, 59u, P17_3, P17_3_TCPWM1_LINE_COMPL59},
    {4u, 58u, P17_4, P17_4_TCPWM1_LINE_COMPL58},
    {6u, 3u, P17_4, P17_4_TCPWM1_LINE_COMPL515},
    {4u, 57u, P17_5, P17_5_TCPWM1_LINE_COMPL57},
    {4u, 56u, P17_6, P17_6_TCPWM1_LINE_COMPL56},
    {6u, 2u, P17_6, P17_6_TCPWM1_LINE_COMPL514},
    {5u, 4u, P17_7, P17_7_TCPWM1_LINE_COMPL260},
    {5u, 5u, P18_0, P18_0_TCPWM1_LINE_COMPL261},
    {5u, 6u, P18_1, P18_1_TCPWM1_LINE_COMPL262},
    {6u, 0u, P18_1, P18_1_TCPWM1_LINE_COMPL512},
    {5u, 7u, P18_2, P18_2_TCPWM1_LINE_COMPL263},
    {4u, 55u, P18_3, P18_3_TCPWM1_LINE_COMPL55},
    {6u, 1u, P18_3, P18_3_TCPWM1_LINE_COMPL513},
    {4u, 54u, P18_4, P18_4_TCPWM1_LINE_COMPL54},
    {1u, 2u, P18_5, P18_5_TCPWM0_LINE_COMPL258},
    {4u, 53u, P18_5, P18_5_TCPWM1_LINE_COMPL53},
    {6u, 2u, P18_5, P18_5_TCPWM1_LINE_COMPL514},
    {4u, 52u, P18_6, P18_6_TCPWM1_LINE_COMPL52},
    {4u, 51u, P18_7, P18_7_TCPWM1_LINE_COMPL51},
    {6u, 3u, P18_7, P18_7_TCPWM1_LINE_COMPL515},
    {4u, 50u, P19_0, P19_0_TCPWM1_LINE_COMPL50},
    {5u, 3u, P19_1, P19_1_TCPWM1_LINE_COMPL259},
    {4u, 26u, P19_2, P19_2_TCPWM1_LINE_COMPL26},
    {4u, 27u, P19_3, P19_3_TCPWM1_LINE_COMPL27},
    {4u, 28u, P19_4, P19_4_TCPWM1_LINE_COMPL28},
    {4u, 29u, P20_0, P20_0_TCPWM1_LINE_COMPL29},
    {4u, 30u, P20_1, P20_1_TCPWM1_LINE_COMPL30},
    {4u, 49u, P20_2, P20_2_TCPWM1_LINE_COMPL49},
    {4u, 48u, P20_3, P20_3_TCPWM1_LINE_COMPL48},
    {4u, 47u, P20_4, P20_4_TCPWM1_LINE_COMPL47},
    {4u, 46u, P20_5, P20_5_TCPWM1_LINE_COMPL46},
    {4u, 45u, P20_6, P20_6_TCPWM1_LINE_COMPL45},
    {4u, 44u, P20_7, P20_7_TCPWM1_LINE_COMPL44},
    {4u, 43u, P21_0, P21_0_TCPWM1_LINE_COMPL43},
    {4u, 42u, P21_1, P21_1_TCPWM1_LINE_COMPL42},
    {4u, 41u, P21_2, P21_2_TCPWM1_LINE_COMPL41},
    {4u, 40u, P21_3, P21_3_TCPWM1_LINE_COMPL40},
    {4u, 39u, P21_4, P21_4_TCPWM1_LINE_COMPL39},
    {4u, 35u, P21_5, P21_5_TCPWM1_LINE_COMPL35},
    {4u, 38u, P21_5, P21_5_TCPWM1_LINE_COMPL38},
    {4u, 37u, P21_6, P21_6_TCPWM1_LINE_COMPL37},
    {4u, 36u, P21_7, P21_7_TCPWM1_LINE_COMPL36},
    {4u, 34u, P22_1, P22_1_TCPWM1_LINE_COMPL34},
    {4u, 33u, P22_2, P22_2_TCPWM1_LINE_COMPL33},
    {4u, 32u, P22_3, P22_3_TCPWM1_LINE_COMPL32},
    {4u, 31u, P22_4, P22_4_TCPWM1_LINE_COMPL31},
    {4u, 30u, P22_5, P22_5_TCPWM1_LINE_COMPL30},
    {4u, 29u, P22_6, P22_6_TCPWM1_LINE_COMPL29},
    {6u, 8u, P22_6, P22_6_TCPWM1_LINE_COMPL520},
    {4u, 28u, P22_7, P22_7_TCPWM1_LINE_COMPL28},
    {4u, 27u, P23_0, P23_0_TCPWM1_LINE_COMPL27},
    {5u, 8u, P23_1, P23_1_TCPWM1_LINE_COMPL264},
    {5u, 9u, P23_2, P23_2_TCPWM1_LINE_COMPL265},
    {5u, 10u, P23_3, P23_3_TCPWM1_LINE_COMPL266},
    {5u, 11u, P23_4, P23_4_TCPWM1_LINE_COMPL267},
    {4u, 25u, P23_5, P23_5_TCPWM1_LINE_COMPL25},
    {6u, 9u, P23_5, P23_5_TCPWM1_LINE_COMPL521},
    {4u, 24u, P23_6, P23_6_TCPWM1_LINE_COMPL24},
    {4u, 23u, P23_7, P23_7_TCPWM1_LINE_COMPL23},
};

/* Connections for: tcpwm_tr_one_cnt_in */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_one_cnt_in[358] = {
    {4u, 54u, P0_0, P0_0_TCPWM1_TR_ONE_CNT_IN54},
    {4u, 67u, P0_0, P0_0_TCPWM1_TR_ONE_CNT_IN67},
    {4u, 51u, P0_1, P0_1_TCPWM1_TR_ONE_CNT_IN51},
    {4u, 55u, P0_1, P0_1_TCPWM1_TR_ONE_CNT_IN55},
    {4u, 42u, P0_2, P0_2_TCPWM1_TR_ONE_CNT_IN42},
    {4u, 52u, P0_2, P0_2_TCPWM1_TR_ONE_CNT_IN52},
    {6u, 0u, P0_2, P0_2_TCPWM0_TR_ONE_CNT_IN1536},
    {4u, 39u, P0_3, P0_3_TCPWM1_TR_ONE_CNT_IN39},
    {4u, 43u, P0_3, P0_3_TCPWM1_TR_ONE_CNT_IN43},
    {6u, 1u, P0_3, P0_3_TCPWM0_TR_ONE_CNT_IN1537},
    {4u, 36u, P1_0, P1_0_TCPWM1_TR_ONE_CNT_IN36},
    {4u, 40u, P1_0, P1_0_TCPWM1_TR_ONE_CNT_IN40},
    {4u, 33u, P1_1, P1_1_TCPWM1_TR_ONE_CNT_IN33},
    {4u, 37u, P1_1, P1_1_TCPWM1_TR_ONE_CNT_IN37},
    {4u, 30u, P1_2, P1_2_TCPWM1_TR_ONE_CNT_IN30},
    {4u, 34u, P1_2, P1_2_TCPWM1_TR_ONE_CNT_IN34},
    {4u, 24u, P1_3, P1_3_TCPWM1_TR_ONE_CNT_IN24},
    {4u, 31u, P1_3, P1_3_TCPWM1_TR_ONE_CNT_IN31},
    {4u, 21u, P2_0, P2_0_TCPWM1_TR_ONE_CNT_IN21},
    {4u, 25u, P2_0, P2_0_TCPWM1_TR_ONE_CNT_IN25},
    {10u, 12u, P2_0, P2_0_TCPWM1_TR_ONE_CNT_IN1548},
    {4u, 18u, P2_1, P2_1_TCPWM1_TR_ONE_CNT_IN18},
    {4u, 22u, P2_1, P2_1_TCPWM1_TR_ONE_CNT_IN22},
    {10u, 15u, P2_1, P2_1_TCPWM1_TR_ONE_CNT_IN1551},
    {4u, 15u, P2_2, P2_2_TCPWM1_TR_ONE_CNT_IN15},
    {4u, 19u, P2_2, P2_2_TCPWM1_TR_ONE_CNT_IN19},
    {10u, 18u, P2_2, P2_2_TCPWM1_TR_ONE_CNT_IN1554},
    {4u, 12u, P2_3, P2_3_TCPWM1_TR_ONE_CNT_IN12},
    {4u, 16u, P2_3, P2_3_TCPWM1_TR_ONE_CNT_IN16},
    {10u, 21u, P2_3, P2_3_TCPWM1_TR_ONE_CNT_IN1557},
    {4u, 9u, P2_4, P2_4_TCPWM1_TR_ONE_CNT_IN9},
    {4u, 13u, P2_4, P2_4_TCPWM1_TR_ONE_CNT_IN13},
    {4u, 6u, P2_5, P2_5_TCPWM1_TR_ONE_CNT_IN6},
    {4u, 10u, P2_5, P2_5_TCPWM1_TR_ONE_CNT_IN10},
    {4u, 3u, P3_0, P3_0_TCPWM1_TR_ONE_CNT_IN3},
    {4u, 7u, P3_0, P3_0_TCPWM1_TR_ONE_CNT_IN7},
    {4u, 0u, P3_1, P3_1_TCPWM1_TR_ONE_CNT_IN0},
    {4u, 4u, P3_1, P3_1_TCPWM1_TR_ONE_CNT_IN4},
    {4u, 1u, P3_2, P3_2_TCPWM1_TR_ONE_CNT_IN1},
    {7u, 9u, P3_2, P3_2_TCPWM1_TR_ONE_CNT_IN777},
    {10u, 13u, P3_2, P3_2_TCPWM1_TR_ONE_CNT_IN1549},
    {7u, 6u, P3_3, P3_3_TCPWM1_TR_ONE_CNT_IN774},
    {7u, 10u, P3_3, P3_3_TCPWM1_TR_ONE_CNT_IN778},
    {10u, 16u, P3_3, P3_3_TCPWM1_TR_ONE_CNT_IN1552},
    {7u, 3u, P3_4, P3_4_TCPWM1_TR_ONE_CNT_IN771},
    {7u, 7u, P3_4, P3_4_TCPWM1_TR_ONE_CNT_IN775},
    {10u, 19u, P3_4, P3_4_TCPWM1_TR_ONE_CNT_IN1555},
    {7u, 0u, P3_5, P3_5_TCPWM1_TR_ONE_CNT_IN768},
    {7u, 4u, P3_5, P3_5_TCPWM1_TR_ONE_CNT_IN772},
    {10u, 22u, P3_5, P3_5_TCPWM1_TR_ONE_CNT_IN1558},
    {4u, 12u, P4_0, P4_0_TCPWM1_TR_ONE_CNT_IN12},
    {7u, 1u, P4_0, P4_0_TCPWM1_TR_ONE_CNT_IN769},
    {4u, 13u, P4_1, P4_1_TCPWM1_TR_ONE_CNT_IN13},
    {4u, 15u, P4_1, P4_1_TCPWM1_TR_ONE_CNT_IN15},
    {4u, 16u, P4_2, P4_2_TCPWM1_TR_ONE_CNT_IN16},
    {4u, 18u, P4_2, P4_2_TCPWM1_TR_ONE_CNT_IN18},
    {4u, 19u, P4_3, P4_3_TCPWM1_TR_ONE_CNT_IN19},
    {4u, 21u, P4_3, P4_3_TCPWM1_TR_ONE_CNT_IN21},
    {4u, 22u, P4_4, P4_4_TCPWM1_TR_ONE_CNT_IN22},
    {4u, 24u, P4_4, P4_4_TCPWM1_TR_ONE_CNT_IN24},
    {4u, 25u, P5_0, P5_0_TCPWM1_TR_ONE_CNT_IN25},
    {4u, 27u, P5_0, P5_0_TCPWM1_TR_ONE_CNT_IN27},
    {4u, 28u, P5_1, P5_1_TCPWM1_TR_ONE_CNT_IN28},
    {4u, 30u, P5_1, P5_1_TCPWM1_TR_ONE_CNT_IN30},
    {3u, 0u, P5_2, P5_2_TCPWM0_TR_ONE_CNT_IN768},
    {4u, 31u, P5_2, P5_2_TCPWM1_TR_ONE_CNT_IN31},
    {4u, 33u, P5_2, P5_2_TCPWM1_TR_ONE_CNT_IN33},
    {10u, 30u, P5_2, P5_2_TCPWM1_TR_ONE_CNT_IN1566},
    {3u, 1u, P5_3, P5_3_TCPWM0_TR_ONE_CNT_IN769},
    {4u, 34u, P5_3, P5_3_TCPWM1_TR_ONE_CNT_IN34},
    {4u, 36u, P5_3, P5_3_TCPWM1_TR_ONE_CNT_IN36},
    {10u, 31u, P5_3, P5_3_TCPWM1_TR_ONE_CNT_IN1567},
    {4u, 37u, P5_4, P5_4_TCPWM1_TR_ONE_CNT_IN37},
    {4u, 39u, P5_4, P5_4_TCPWM1_TR_ONE_CNT_IN39},
    {4u, 40u, P5_5, P5_5_TCPWM1_TR_ONE_CNT_IN40},
    {4u, 42u, P5_5, P5_5_TCPWM1_TR_ONE_CNT_IN42},
    {4u, 43u, P6_0, P6_0_TCPWM1_TR_ONE_CNT_IN43},
    {7u, 0u, P6_0, P6_0_TCPWM1_TR_ONE_CNT_IN768},
    {10u, 33u, P6_0, P6_0_TCPWM1_TR_ONE_CNT_IN1569},
    {4u, 0u, P6_1, P6_1_TCPWM1_TR_ONE_CNT_IN0},
    {7u, 1u, P6_1, P6_1_TCPWM1_TR_ONE_CNT_IN769},
    {10u, 34u, P6_1, P6_1_TCPWM1_TR_ONE_CNT_IN1570},
    {4u, 1u, P6_2, P6_2_TCPWM1_TR_ONE_CNT_IN1},
    {7u, 3u, P6_2, P6_2_TCPWM1_TR_ONE_CNT_IN771},
    {4u, 3u, P6_3, P6_3_TCPWM1_TR_ONE_CNT_IN3},
    {7u, 4u, P6_3, P6_3_TCPWM1_TR_ONE_CNT_IN772},
    {0u, 0u, P6_4, P6_4_TCPWM0_TR_ONE_CNT_IN0},
    {4u, 4u, P6_4, P6_4_TCPWM1_TR_ONE_CNT_IN4},
    {7u, 6u, P6_4, P6_4_TCPWM1_TR_ONE_CNT_IN774},
    {10u, 36u, P6_4, P6_4_TCPWM1_TR_ONE_CNT_IN1572},
    {0u, 1u, P6_5, P6_5_TCPWM0_TR_ONE_CNT_IN1},
    {4u, 6u, P6_5, P6_5_TCPWM1_TR_ONE_CNT_IN6},
    {7u, 7u, P6_5, P6_5_TCPWM1_TR_ONE_CNT_IN775},
    {10u, 37u, P6_5, P6_5_TCPWM1_TR_ONE_CNT_IN1573},
    {4u, 7u, P6_6, P6_6_TCPWM1_TR_ONE_CNT_IN7},
    {7u, 9u, P6_6, P6_6_TCPWM1_TR_ONE_CNT_IN777},
    {4u, 9u, P6_7, P6_7_TCPWM1_TR_ONE_CNT_IN9},
    {7u, 10u, P6_7, P6_7_TCPWM1_TR_ONE_CNT_IN778},
    {4u, 10u, P7_0, P7_0_TCPWM1_TR_ONE_CNT_IN10},
    {7u, 12u, P7_0, P7_0_TCPWM1_TR_ONE_CNT_IN780},
    {4u, 45u, P7_1, P7_1_TCPWM1_TR_ONE_CNT_IN45},
    {7u, 13u, P7_1, P7_1_TCPWM1_TR_ONE_CNT_IN781},
    {4u, 46u, P7_2, P7_2_TCPWM1_TR_ONE_CNT_IN46},
    {7u, 15u, P7_2, P7_2_TCPWM1_TR_ONE_CNT_IN783},
    {0u, 3u, P7_3, P7_3_TCPWM0_TR_ONE_CNT_IN3},
    {4u, 48u, P7_3, P7_3_TCPWM1_TR_ONE_CNT_IN48},
    {7u, 16u, P7_3, P7_3_TCPWM1_TR_ONE_CNT_IN784},
    {0u, 4u, P7_4, P7_4_TCPWM0_TR_ONE_CNT_IN4},
    {4u, 49u, P7_4, P7_4_TCPWM1_TR_ONE_CNT_IN49},
    {7u, 18u, P7_4, P7_4_TCPWM1_TR_ONE_CNT_IN786},
    {4u, 51u, P7_5, P7_5_TCPWM1_TR_ONE_CNT_IN51},
    {7u, 19u, P7_5, P7_5_TCPWM1_TR_ONE_CNT_IN787},
    {4u, 52u, P7_6, P7_6_TCPWM1_TR_ONE_CNT_IN52},
    {7u, 21u, P7_6, P7_6_TCPWM1_TR_ONE_CNT_IN789},
    {4u, 54u, P7_7, P7_7_TCPWM1_TR_ONE_CNT_IN54},
    {7u, 22u, P7_7, P7_7_TCPWM1_TR_ONE_CNT_IN790},
    {4u, 55u, P8_0, P8_0_TCPWM1_TR_ONE_CNT_IN55},
    {4u, 57u, P8_0, P8_0_TCPWM1_TR_ONE_CNT_IN57},
    {4u, 58u, P8_1, P8_1_TCPWM1_TR_ONE_CNT_IN58},
    {4u, 60u, P8_1, P8_1_TCPWM1_TR_ONE_CNT_IN60},
    {6u, 6u, P8_1, P8_1_TCPWM0_TR_ONE_CNT_IN1542},
    {4u, 61u, P8_2, P8_2_TCPWM1_TR_ONE_CNT_IN61},
    {4u, 63u, P8_2, P8_2_TCPWM1_TR_ONE_CNT_IN63},
    {6u, 7u, P8_2, P8_2_TCPWM0_TR_ONE_CNT_IN1543},
    {10u, 24u, P8_2, P8_2_TCPWM1_TR_ONE_CNT_IN1560},
    {4u, 64u, P8_3, P8_3_TCPWM1_TR_ONE_CNT_IN64},
    {4u, 66u, P8_3, P8_3_TCPWM1_TR_ONE_CNT_IN66},
    {10u, 25u, P8_3, P8_3_TCPWM1_TR_ONE_CNT_IN1561},
    {4u, 67u, P8_4, P8_4_TCPWM1_TR_ONE_CNT_IN67},
    {4u, 69u, P8_4, P8_4_TCPWM1_TR_ONE_CNT_IN69},
    {4u, 70u, P9_0, P9_0_TCPWM1_TR_ONE_CNT_IN70},
    {4u, 72u, P9_0, P9_0_TCPWM1_TR_ONE_CNT_IN72},
    {4u, 73u, P9_1, P9_1_TCPWM1_TR_ONE_CNT_IN73},
    {4u, 75u, P9_1, P9_1_TCPWM1_TR_ONE_CNT_IN75},
    {4u, 76u, P9_2, P9_2_TCPWM1_TR_ONE_CNT_IN76},
    {4u, 78u, P9_2, P9_2_TCPWM1_TR_ONE_CNT_IN78},
    {10u, 27u, P9_2, P9_2_TCPWM1_TR_ONE_CNT_IN1563},
    {4u, 79u, P9_3, P9_3_TCPWM1_TR_ONE_CNT_IN79},
    {4u, 81u, P9_3, P9_3_TCPWM1_TR_ONE_CNT_IN81},
    {10u, 28u, P9_3, P9_3_TCPWM1_TR_ONE_CNT_IN1564},
    {4u, 82u, P10_0, P10_0_TCPWM1_TR_ONE_CNT_IN82},
    {4u, 84u, P10_0, P10_0_TCPWM1_TR_ONE_CNT_IN84},
    {4u, 85u, P10_1, P10_1_TCPWM1_TR_ONE_CNT_IN85},
    {4u, 87u, P10_1, P10_1_TCPWM1_TR_ONE_CNT_IN87},
    {4u, 88u, P10_2, P10_2_TCPWM1_TR_ONE_CNT_IN88},
    {4u, 90u, P10_2, P10_2_TCPWM1_TR_ONE_CNT_IN90},
    {10u, 30u, P10_2, P10_2_TCPWM1_TR_ONE_CNT_IN1566},
    {4u, 91u, P10_3, P10_3_TCPWM1_TR_ONE_CNT_IN91},
    {4u, 93u, P10_3, P10_3_TCPWM1_TR_ONE_CNT_IN93},
    {10u, 31u, P10_3, P10_3_TCPWM1_TR_ONE_CNT_IN1567},
    {4u, 94u, P10_4, P10_4_TCPWM1_TR_ONE_CNT_IN94},
    {4u, 96u, P10_4, P10_4_TCPWM1_TR_ONE_CNT_IN96},
    {4u, 97u, P10_5, P10_5_TCPWM1_TR_ONE_CNT_IN97},
    {4u, 99u, P10_5, P10_5_TCPWM1_TR_ONE_CNT_IN99},
    {4u, 100u, P10_6, P10_6_TCPWM1_TR_ONE_CNT_IN100},
    {4u, 102u, P10_6, P10_6_TCPWM1_TR_ONE_CNT_IN102},
    {10u, 33u, P10_6, P10_6_TCPWM1_TR_ONE_CNT_IN1569},
    {4u, 103u, P10_7, P10_7_TCPWM1_TR_ONE_CNT_IN103},
    {4u, 105u, P10_7, P10_7_TCPWM1_TR_ONE_CNT_IN105},
    {10u, 34u, P10_7, P10_7_TCPWM1_TR_ONE_CNT_IN1570},
    {4u, 183u, P11_0, P11_0_TCPWM1_TR_ONE_CNT_IN183},
    {4u, 187u, P11_0, P11_0_TCPWM1_TR_ONE_CNT_IN187},
    {4u, 180u, P11_1, P11_1_TCPWM1_TR_ONE_CNT_IN180},
    {4u, 184u, P11_1, P11_1_TCPWM1_TR_ONE_CNT_IN184},
    {4u, 177u, P11_2, P11_2_TCPWM1_TR_ONE_CNT_IN177},
    {4u, 181u, P11_2, P11_2_TCPWM1_TR_ONE_CNT_IN181},
    {4u, 106u, P12_0, P12_0_TCPWM1_TR_ONE_CNT_IN106},
    {4u, 108u, P12_0, P12_0_TCPWM1_TR_ONE_CNT_IN108},
    {4u, 109u, P12_1, P12_1_TCPWM1_TR_ONE_CNT_IN109},
    {4u, 111u, P12_1, P12_1_TCPWM1_TR_ONE_CNT_IN111},
    {4u, 112u, P12_2, P12_2_TCPWM1_TR_ONE_CNT_IN112},
    {4u, 114u, P12_2, P12_2_TCPWM1_TR_ONE_CNT_IN114},
    {6u, 3u, P12_2, P12_2_TCPWM0_TR_ONE_CNT_IN1539},
    {4u, 115u, P12_3, P12_3_TCPWM1_TR_ONE_CNT_IN115},
    {4u, 117u, P12_3, P12_3_TCPWM1_TR_ONE_CNT_IN117},
    {6u, 4u, P12_3, P12_3_TCPWM0_TR_ONE_CNT_IN1540},
    {0u, 7u, P12_4, P12_4_TCPWM0_TR_ONE_CNT_IN7},
    {4u, 118u, P12_4, P12_4_TCPWM1_TR_ONE_CNT_IN118},
    {4u, 120u, P12_4, P12_4_TCPWM1_TR_ONE_CNT_IN120},
    {4u, 121u, P12_5, P12_5_TCPWM1_TR_ONE_CNT_IN121},
    {4u, 123u, P12_5, P12_5_TCPWM1_TR_ONE_CNT_IN123},
    {4u, 124u, P12_6, P12_6_TCPWM1_TR_ONE_CNT_IN124},
    {4u, 126u, P12_6, P12_6_TCPWM1_TR_ONE_CNT_IN126},
    {4u, 127u, P12_7, P12_7_TCPWM1_TR_ONE_CNT_IN127},
    {4u, 129u, P12_7, P12_7_TCPWM1_TR_ONE_CNT_IN129},
    {0u, 6u, P13_0, P13_0_TCPWM0_TR_ONE_CNT_IN6},
    {4u, 130u, P13_0, P13_0_TCPWM1_TR_ONE_CNT_IN130},
    {7u, 24u, P13_0, P13_0_TCPWM1_TR_ONE_CNT_IN792},
    {4u, 132u, P13_1, P13_1_TCPWM1_TR_ONE_CNT_IN132},
    {7u, 25u, P13_1, P13_1_TCPWM1_TR_ONE_CNT_IN793},
    {4u, 133u, P13_2, P13_2_TCPWM1_TR_ONE_CNT_IN133},
    {7u, 27u, P13_2, P13_2_TCPWM1_TR_ONE_CNT_IN795},
    {4u, 135u, P13_3, P13_3_TCPWM1_TR_ONE_CNT_IN135},
    {7u, 28u, P13_3, P13_3_TCPWM1_TR_ONE_CNT_IN796},
    {4u, 136u, P13_4, P13_4_TCPWM1_TR_ONE_CNT_IN136},
    {7u, 30u, P13_4, P13_4_TCPWM1_TR_ONE_CNT_IN798},
    {4u, 138u, P13_5, P13_5_TCPWM1_TR_ONE_CNT_IN138},
    {7u, 31u, P13_5, P13_5_TCPWM1_TR_ONE_CNT_IN799},
    {4u, 139u, P13_6, P13_6_TCPWM1_TR_ONE_CNT_IN139},
    {7u, 33u, P13_6, P13_6_TCPWM1_TR_ONE_CNT_IN801},
    {4u, 141u, P13_7, P13_7_TCPWM1_TR_ONE_CNT_IN141},
    {7u, 34u, P13_7, P13_7_TCPWM1_TR_ONE_CNT_IN802},
    {4u, 142u, P14_0, P14_0_TCPWM1_TR_ONE_CNT_IN142},
    {4u, 144u, P14_0, P14_0_TCPWM1_TR_ONE_CNT_IN144},
    {4u, 145u, P14_1, P14_1_TCPWM1_TR_ONE_CNT_IN145},
    {4u, 147u, P14_1, P14_1_TCPWM1_TR_ONE_CNT_IN147},
    {3u, 3u, P14_2, P14_2_TCPWM0_TR_ONE_CNT_IN771},
    {4u, 148u, P14_2, P14_2_TCPWM1_TR_ONE_CNT_IN148},
    {4u, 150u, P14_2, P14_2_TCPWM1_TR_ONE_CNT_IN150},
    {3u, 4u, P14_3, P14_3_TCPWM0_TR_ONE_CNT_IN772},
    {4u, 151u, P14_3, P14_3_TCPWM1_TR_ONE_CNT_IN151},
    {4u, 153u, P14_3, P14_3_TCPWM1_TR_ONE_CNT_IN153},
    {4u, 154u, P14_4, P14_4_TCPWM1_TR_ONE_CNT_IN154},
    {4u, 156u, P14_4, P14_4_TCPWM1_TR_ONE_CNT_IN156},
    {10u, 12u, P14_4, P14_4_TCPWM1_TR_ONE_CNT_IN1548},
    {4u, 157u, P14_5, P14_5_TCPWM1_TR_ONE_CNT_IN157},
    {4u, 159u, P14_5, P14_5_TCPWM1_TR_ONE_CNT_IN159},
    {10u, 13u, P14_5, P14_5_TCPWM1_TR_ONE_CNT_IN1549},
    {4u, 160u, P14_6, P14_6_TCPWM1_TR_ONE_CNT_IN160},
    {4u, 162u, P14_6, P14_6_TCPWM1_TR_ONE_CNT_IN162},
    {10u, 15u, P14_6, P14_6_TCPWM1_TR_ONE_CNT_IN1551},
    {4u, 163u, P14_7, P14_7_TCPWM1_TR_ONE_CNT_IN163},
    {4u, 165u, P14_7, P14_7_TCPWM1_TR_ONE_CNT_IN165},
    {10u, 16u, P14_7, P14_7_TCPWM1_TR_ONE_CNT_IN1552},
    {4u, 166u, P15_0, P15_0_TCPWM1_TR_ONE_CNT_IN166},
    {4u, 168u, P15_0, P15_0_TCPWM1_TR_ONE_CNT_IN168},
    {10u, 18u, P15_0, P15_0_TCPWM1_TR_ONE_CNT_IN1554},
    {4u, 169u, P15_1, P15_1_TCPWM1_TR_ONE_CNT_IN169},
    {4u, 171u, P15_1, P15_1_TCPWM1_TR_ONE_CNT_IN171},
    {10u, 19u, P15_1, P15_1_TCPWM1_TR_ONE_CNT_IN1555},
    {4u, 172u, P15_2, P15_2_TCPWM1_TR_ONE_CNT_IN172},
    {4u, 174u, P15_2, P15_2_TCPWM1_TR_ONE_CNT_IN174},
    {10u, 21u, P15_2, P15_2_TCPWM1_TR_ONE_CNT_IN1557},
    {4u, 175u, P15_3, P15_3_TCPWM1_TR_ONE_CNT_IN175},
    {4u, 177u, P15_3, P15_3_TCPWM1_TR_ONE_CNT_IN177},
    {10u, 22u, P15_3, P15_3_TCPWM1_TR_ONE_CNT_IN1558},
    {4u, 186u, P16_3, P16_3_TCPWM1_TR_ONE_CNT_IN186},
    {4u, 187u, P16_3, P16_3_TCPWM1_TR_ONE_CNT_IN187},
    {4u, 183u, P17_0, P17_0_TCPWM1_TR_ONE_CNT_IN183},
    {4u, 187u, P17_0, P17_0_TCPWM1_TR_ONE_CNT_IN187},
    {4u, 180u, P17_1, P17_1_TCPWM1_TR_ONE_CNT_IN180},
    {4u, 184u, P17_1, P17_1_TCPWM1_TR_ONE_CNT_IN184},
    {4u, 177u, P17_2, P17_2_TCPWM1_TR_ONE_CNT_IN177},
    {4u, 181u, P17_2, P17_2_TCPWM1_TR_ONE_CNT_IN181},
    {4u, 174u, P17_3, P17_3_TCPWM1_TR_ONE_CNT_IN174},
    {4u, 178u, P17_3, P17_3_TCPWM1_TR_ONE_CNT_IN178},
    {4u, 171u, P17_4, P17_4_TCPWM1_TR_ONE_CNT_IN171},
    {4u, 175u, P17_4, P17_4_TCPWM1_TR_ONE_CNT_IN175},
    {4u, 168u, P17_5, P17_5_TCPWM1_TR_ONE_CNT_IN168},
    {4u, 172u, P17_5, P17_5_TCPWM1_TR_ONE_CNT_IN172},
    {4u, 169u, P17_6, P17_6_TCPWM1_TR_ONE_CNT_IN169},
    {7u, 12u, P17_6, P17_6_TCPWM1_TR_ONE_CNT_IN780},
    {7u, 13u, P17_7, P17_7_TCPWM1_TR_ONE_CNT_IN781},
    {7u, 15u, P17_7, P17_7_TCPWM1_TR_ONE_CNT_IN783},
    {7u, 16u, P18_0, P18_0_TCPWM1_TR_ONE_CNT_IN784},
    {7u, 18u, P18_0, P18_0_TCPWM1_TR_ONE_CNT_IN786},
    {7u, 19u, P18_1, P18_1_TCPWM1_TR_ONE_CNT_IN787},
    {7u, 21u, P18_1, P18_1_TCPWM1_TR_ONE_CNT_IN789},
    {4u, 165u, P18_2, P18_2_TCPWM1_TR_ONE_CNT_IN165},
    {7u, 22u, P18_2, P18_2_TCPWM1_TR_ONE_CNT_IN790},
    {4u, 162u, P18_3, P18_3_TCPWM1_TR_ONE_CNT_IN162},
    {4u, 166u, P18_3, P18_3_TCPWM1_TR_ONE_CNT_IN166},
    {4u, 159u, P18_4, P18_4_TCPWM1_TR_ONE_CNT_IN159},
    {4u, 163u, P18_4, P18_4_TCPWM1_TR_ONE_CNT_IN163},
    {4u, 156u, P18_5, P18_5_TCPWM1_TR_ONE_CNT_IN156},
    {4u, 160u, P18_5, P18_5_TCPWM1_TR_ONE_CNT_IN160},
    {3u, 6u, P18_6, P18_6_TCPWM0_TR_ONE_CNT_IN774},
    {4u, 153u, P18_6, P18_6_TCPWM1_TR_ONE_CNT_IN153},
    {4u, 157u, P18_6, P18_6_TCPWM1_TR_ONE_CNT_IN157},
    {3u, 7u, P18_7, P18_7_TCPWM0_TR_ONE_CNT_IN775},
    {4u, 150u, P18_7, P18_7_TCPWM1_TR_ONE_CNT_IN150},
    {4u, 154u, P18_7, P18_7_TCPWM1_TR_ONE_CNT_IN154},
    {4u, 151u, P19_0, P19_0_TCPWM1_TR_ONE_CNT_IN151},
    {7u, 9u, P19_0, P19_0_TCPWM1_TR_ONE_CNT_IN777},
    {10u, 0u, P19_0, P19_0_TCPWM1_TR_ONE_CNT_IN1536},
    {4u, 78u, P19_1, P19_1_TCPWM1_TR_ONE_CNT_IN78},
    {7u, 10u, P19_1, P19_1_TCPWM1_TR_ONE_CNT_IN778},
    {10u, 1u, P19_1, P19_1_TCPWM1_TR_ONE_CNT_IN1537},
    {4u, 79u, P19_2, P19_2_TCPWM1_TR_ONE_CNT_IN79},
    {4u, 81u, P19_2, P19_2_TCPWM1_TR_ONE_CNT_IN81},
    {10u, 3u, P19_2, P19_2_TCPWM1_TR_ONE_CNT_IN1539},
    {4u, 82u, P19_3, P19_3_TCPWM1_TR_ONE_CNT_IN82},
    {4u, 84u, P19_3, P19_3_TCPWM1_TR_ONE_CNT_IN84},
    {10u, 4u, P19_3, P19_3_TCPWM1_TR_ONE_CNT_IN1540},
    {4u, 85u, P19_4, P19_4_TCPWM1_TR_ONE_CNT_IN85},
    {4u, 87u, P19_4, P19_4_TCPWM1_TR_ONE_CNT_IN87},
    {10u, 6u, P19_4, P19_4_TCPWM1_TR_ONE_CNT_IN1542},
    {4u, 88u, P20_0, P20_0_TCPWM1_TR_ONE_CNT_IN88},
    {4u, 90u, P20_0, P20_0_TCPWM1_TR_ONE_CNT_IN90},
    {10u, 7u, P20_0, P20_0_TCPWM1_TR_ONE_CNT_IN1543},
    {4u, 91u, P20_1, P20_1_TCPWM1_TR_ONE_CNT_IN91},
    {4u, 147u, P20_1, P20_1_TCPWM1_TR_ONE_CNT_IN147},
    {10u, 9u, P20_1, P20_1_TCPWM1_TR_ONE_CNT_IN1545},
    {4u, 144u, P20_2, P20_2_TCPWM1_TR_ONE_CNT_IN144},
    {4u, 148u, P20_2, P20_2_TCPWM1_TR_ONE_CNT_IN148},
    {10u, 10u, P20_2, P20_2_TCPWM1_TR_ONE_CNT_IN1546},
    {4u, 141u, P20_3, P20_3_TCPWM1_TR_ONE_CNT_IN141},
    {4u, 145u, P20_3, P20_3_TCPWM1_TR_ONE_CNT_IN145},
    {4u, 138u, P20_4, P20_4_TCPWM1_TR_ONE_CNT_IN138},
    {4u, 142u, P20_4, P20_4_TCPWM1_TR_ONE_CNT_IN142},
    {4u, 135u, P20_5, P20_5_TCPWM1_TR_ONE_CNT_IN135},
    {4u, 139u, P20_5, P20_5_TCPWM1_TR_ONE_CNT_IN139},
    {4u, 132u, P20_6, P20_6_TCPWM1_TR_ONE_CNT_IN132},
    {4u, 136u, P20_6, P20_6_TCPWM1_TR_ONE_CNT_IN136},
    {4u, 129u, P20_7, P20_7_TCPWM1_TR_ONE_CNT_IN129},
    {4u, 133u, P20_7, P20_7_TCPWM1_TR_ONE_CNT_IN133},
    {4u, 126u, P21_0, P21_0_TCPWM1_TR_ONE_CNT_IN126},
    {4u, 130u, P21_0, P21_0_TCPWM1_TR_ONE_CNT_IN130},
    {4u, 123u, P21_1, P21_1_TCPWM1_TR_ONE_CNT_IN123},
    {4u, 127u, P21_1, P21_1_TCPWM1_TR_ONE_CNT_IN127},
    {4u, 120u, P21_2, P21_2_TCPWM1_TR_ONE_CNT_IN120},
    {4u, 124u, P21_2, P21_2_TCPWM1_TR_ONE_CNT_IN124},
    {4u, 117u, P21_3, P21_3_TCPWM1_TR_ONE_CNT_IN117},
    {4u, 121u, P21_3, P21_3_TCPWM1_TR_ONE_CNT_IN121},
    {4u, 114u, P21_4, P21_4_TCPWM1_TR_ONE_CNT_IN114},
    {4u, 118u, P21_4, P21_4_TCPWM1_TR_ONE_CNT_IN118},
    {4u, 102u, P21_5, P21_5_TCPWM1_TR_ONE_CNT_IN102},
    {4u, 106u, P21_5, P21_5_TCPWM1_TR_ONE_CNT_IN106},
    {4u, 111u, P21_5, P21_5_TCPWM1_TR_ONE_CNT_IN111},
    {4u, 115u, P21_5, P21_5_TCPWM1_TR_ONE_CNT_IN115},
    {4u, 108u, P21_6, P21_6_TCPWM1_TR_ONE_CNT_IN108},
    {4u, 112u, P21_6, P21_6_TCPWM1_TR_ONE_CNT_IN112},
    {4u, 105u, P21_7, P21_7_TCPWM1_TR_ONE_CNT_IN105},
    {4u, 109u, P21_7, P21_7_TCPWM1_TR_ONE_CNT_IN109},
    {4u, 99u, P22_1, P22_1_TCPWM1_TR_ONE_CNT_IN99},
    {4u, 103u, P22_1, P22_1_TCPWM1_TR_ONE_CNT_IN103},
    {4u, 96u, P22_2, P22_2_TCPWM1_TR_ONE_CNT_IN96},
    {4u, 100u, P22_2, P22_2_TCPWM1_TR_ONE_CNT_IN100},
    {4u, 93u, P22_3, P22_3_TCPWM1_TR_ONE_CNT_IN93},
    {4u, 97u, P22_3, P22_3_TCPWM1_TR_ONE_CNT_IN97},
    {4u, 90u, P22_4, P22_4_TCPWM1_TR_ONE_CNT_IN90},
    {4u, 94u, P22_4, P22_4_TCPWM1_TR_ONE_CNT_IN94},
    {4u, 87u, P22_5, P22_5_TCPWM1_TR_ONE_CNT_IN87},
    {4u, 91u, P22_5, P22_5_TCPWM1_TR_ONE_CNT_IN91},
    {4u, 84u, P22_6, P22_6_TCPWM1_TR_ONE_CNT_IN84},
    {4u, 88u, P22_6, P22_6_TCPWM1_TR_ONE_CNT_IN88},
    {4u, 81u, P22_7, P22_7_TCPWM1_TR_ONE_CNT_IN81},
    {4u, 85u, P22_7, P22_7_TCPWM1_TR_ONE_CNT_IN85},
    {10u, 24u, P22_7, P22_7_TCPWM1_TR_ONE_CNT_IN1560},
    {4u, 82u, P23_0, P23_0_TCPWM1_TR_ONE_CNT_IN82},
    {7u, 24u, P23_0, P23_0_TCPWM1_TR_ONE_CNT_IN792},
    {10u, 25u, P23_0, P23_0_TCPWM1_TR_ONE_CNT_IN1561},
    {7u, 25u, P23_1, P23_1_TCPWM1_TR_ONE_CNT_IN793},
    {7u, 27u, P23_1, P23_1_TCPWM1_TR_ONE_CNT_IN795},
    {7u, 28u, P23_2, P23_2_TCPWM1_TR_ONE_CNT_IN796},
    {7u, 30u, P23_2, P23_2_TCPWM1_TR_ONE_CNT_IN798},
    {7u, 31u, P23_3, P23_3_TCPWM1_TR_ONE_CNT_IN799},
    {7u, 33u, P23_3, P23_3_TCPWM1_TR_ONE_CNT_IN801},
    {4u, 75u, P23_4, P23_4_TCPWM1_TR_ONE_CNT_IN75},
    {7u, 34u, P23_4, P23_4_TCPWM1_TR_ONE_CNT_IN802},
    {4u, 72u, P23_5, P23_5_TCPWM1_TR_ONE_CNT_IN72},
    {4u, 76u, P23_5, P23_5_TCPWM1_TR_ONE_CNT_IN76},
    {4u, 69u, P23_6, P23_6_TCPWM1_TR_ONE_CNT_IN69},
    {4u, 73u, P23_6, P23_6_TCPWM1_TR_ONE_CNT_IN73},
    {10u, 27u, P23_6, P23_6_TCPWM1_TR_ONE_CNT_IN1563},
    {4u, 66u, P23_7, P23_7_TCPWM1_TR_ONE_CNT_IN66},
    {4u, 70u, P23_7, P23_7_TCPWM1_TR_ONE_CNT_IN70},
    {10u, 28u, P23_7, P23_7_TCPWM1_TR_ONE_CNT_IN1564},
};

#endif
