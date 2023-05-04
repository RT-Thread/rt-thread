/***************************************************************************//**
* \file cyhal_cyw20829_40_qfn.c
*
* \brief
* CYW20829 device GPIO HAL header for 40-QFN package
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

#if defined(_GPIO_CYW20829_40_QFN_H_)
#include "pin_packages/cyhal_cyw20829_40_qfn.h"

/* Pin connections */
/* Connections for: adcmic_clk_pdm */
const cyhal_resource_pin_mapping_t cyhal_pin_map_adcmic_clk_pdm[2] = {
    {0u, 0u, P3_2, P3_2_ADCMIC_CLK_PDM},
    {0u, 0u, P5_0, P5_0_ADCMIC_CLK_PDM},
};

/* Connections for: adcmic_gpio_adc_in */
/* The actual channel_num will always be 0 for the ADCMIC. However, the ADC driver does need to
   know the bit index on the analog_in signal. So store that in the channel_num field instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_adcmic_gpio_adc_in[3] = {
    {0u, 1u, P3_1, HSIOM_SEL_GPIO},
    {0u, 2u, P3_2, HSIOM_SEL_GPIO},
    {0u, 3u, P3_3, HSIOM_SEL_GPIO},
};

/* Connections for: adcmic_pdm_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_adcmic_pdm_data[2] = {
    {0u, 0u, P3_3, P3_3_ADCMIC_PDM_DATA},
    {0u, 0u, P5_1, P5_1_ADCMIC_PDM_DATA},
};

/* Connections for: canfd_ttcan_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_rx[1] = {
    {0u, 0u, P3_2, P3_2_CANFD0_TTCAN_RX0},
};

/* Connections for: canfd_ttcan_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_tx[1] = {
    {0u, 0u, P3_3, P3_3_CANFD0_TTCAN_TX0},
};

/* Connections for: cpuss_clk_swj_swclk_tclk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_clk_swj_swclk_tclk[1] = {
    {0u, 0u, P1_3, P1_3_CPUSS_CLK_SWJ_SWCLK_TCLK},
};

/* Connections for: cpuss_rst_swj_trstn */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_rst_swj_trstn[1] = {
    {0u, 0u, P3_1, P3_1_CPUSS_RST_SWJ_TRSTN},
};

/* Connections for: cpuss_swj_swdio_tms */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swdio_tms[1] = {
    {0u, 0u, P1_2, P1_2_CPUSS_SWJ_SWDIO_TMS},
};

/* Connections for: cpuss_swj_swdoe_tdi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swdoe_tdi[1] = {
    {0u, 0u, P1_1, P1_1_CPUSS_SWJ_SWDOE_TDI},
};

/* Connections for: cpuss_swj_swo_tdo */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swo_tdo[1] = {
    {0u, 0u, P1_0, P1_0_CPUSS_SWJ_SWO_TDO},
};

/* Connections for: cpuss_trace_clock */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_trace_clock[1] = {
    {0u, 0u, P1_2, P1_2_CPUSS_TRACE_CLOCK},
};

/* Connections for: cpuss_trace_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_trace_data[7] = {
    {0u, 3u, P0_4, P0_4_CPUSS_TRACE_DATA3},
    {0u, 2u, P0_5, P0_5_CPUSS_TRACE_DATA2},
    {0u, 1u, P1_0, P1_0_CPUSS_TRACE_DATA1},
    {0u, 0u, P1_1, P1_1_CPUSS_TRACE_DATA0},
    {0u, 2u, P3_1, P3_1_CPUSS_TRACE_DATA2},
    {0u, 1u, P3_2, P3_2_CPUSS_TRACE_DATA1},
    {0u, 0u, P3_3, P3_3_CPUSS_TRACE_DATA0},
};

/* Connections for: keyscan_ks_col */
/* The actual channel_num will always be 0 for the KeyScan. However, the driver does need to know
   the bit index on the row/column signal in order to check that the indices are contiguous and
   start at 0. Store that in the channel_num field instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_keyscan_ks_col[2] = {
    {0u, 0u, P5_0, P5_0_KEYSCAN_KS_COL0},
    {0u, 1u, P5_1, P5_1_KEYSCAN_KS_COL1},
};

/* Connections for: keyscan_ks_row */
/* The actual channel_num will always be 0 for the KeyScan. However, the driver does need to know
   the bit index on the row/column signal in order to check that the indices are contiguous and
   start at 0. Store that in the channel_num field instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_keyscan_ks_row[7] = {
    {0u, 0u, P0_4, P0_4_KEYSCAN_KS_ROW0},
    {0u, 1u, P0_5, P0_5_KEYSCAN_KS_ROW1},
    {0u, 5u, P1_0, P1_0_KEYSCAN_KS_ROW5},
    {0u, 6u, P1_1, P1_1_KEYSCAN_KS_ROW6},
    {0u, 4u, P3_1, P3_1_KEYSCAN_KS_ROW4},
    {0u, 2u, P4_0, P4_0_KEYSCAN_KS_ROW2},
    {0u, 3u, P4_1, P4_1_KEYSCAN_KS_ROW3},
};

/* Connections for: lin_lin_en */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_en[1] = {
    {0u, 0u, P3_1, P3_1_LIN0_LIN_EN0},
};

/* Connections for: lin_lin_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_rx[1] = {
    {0u, 0u, P3_2, P3_2_LIN0_LIN_RX0},
};

/* Connections for: lin_lin_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_tx[1] = {
    {0u, 0u, P3_3, P3_3_LIN0_LIN_TX0},
};

/* Connections for: pdm_pdm_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pdm_pdm_clk[2] = {
    {0u, 0u, P3_2, P3_2_PDM_PDM_CLK0},
    {0u, 0u, P5_0, P5_0_PDM_PDM_CLK0},
};

/* Connections for: pdm_pdm_data */
const cyhal_resource_pin_mapping_t cyhal_pin_map_pdm_pdm_data[2] = {
    {0u, 0u, P3_3, P3_3_PDM_PDM_DATA0},
    {0u, 0u, P5_1, P5_1_PDM_PDM_DATA0},
};

/* Connections for: peri_tr_io_input */
/* The actual channel_num has no value to how the connection works. However, the HAL driver needs
   to know the index of the input or output trigger line. Store that in the channel_num field
   instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_input[6] = {
    {0u, 0u, P0_4, P0_4_PERI_TR_IO_INPUT0},
    {0u, 1u, P0_5, P0_5_PERI_TR_IO_INPUT1},
    {0u, 2u, P1_2, P1_2_PERI_TR_IO_INPUT2},
    {0u, 3u, P1_3, P1_3_PERI_TR_IO_INPUT3},
    {0u, 6u, P3_2, P3_2_PERI_TR_IO_INPUT6},
    {0u, 7u, P3_3, P3_3_PERI_TR_IO_INPUT7},
};

/* Connections for: peri_tr_io_output */
/* The actual channel_num has no value to how the connection works. However, the HAL driver needs
   to know the index of the input or output trigger line. Store that in the channel_num field
   instead. */
const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_output[2] = {
    {0u, 0u, P1_0, P1_0_PERI_TR_IO_OUTPUT0},
    {0u, 1u, P1_1, P1_1_PERI_TR_IO_OUTPUT1},
};

/* Connections for: scb_i2c_scl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[3] = {
    {2u, 0u, P1_2, P1_2_SCB2_I2C_SCL},
    {2u, 0u, P3_2, P3_2_SCB2_I2C_SCL},
    {0u, 0u, P4_0, P4_0_SCB0_I2C_SCL},
};

/* Connections for: scb_i2c_sda */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[3] = {
    {2u, 0u, P1_3, P1_3_SCB2_I2C_SDA},
    {2u, 0u, P3_3, P3_3_SCB2_I2C_SDA},
    {0u, 0u, P4_1, P4_1_SCB0_I2C_SDA},
};

/* Connections for: scb_spi_m_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[3] = {
    {0u, 0u, P0_4, P0_4_SCB0_SPI_CLK},
    {1u, 0u, P1_1, P1_1_SCB1_SPI_CLK},
    {1u, 0u, P3_1, P3_1_SCB1_SPI_CLK},
};

/* Connections for: scb_spi_m_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[3] = {
    {1u, 0u, P1_3, P1_3_SCB1_SPI_MISO},
    {1u, 0u, P3_3, P3_3_SCB1_SPI_MISO},
    {0u, 0u, P4_1, P4_1_SCB0_SPI_MISO},
};

/* Connections for: scb_spi_m_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[3] = {
    {1u, 0u, P1_2, P1_2_SCB1_SPI_MOSI},
    {1u, 0u, P3_2, P3_2_SCB1_SPI_MOSI},
    {0u, 0u, P4_0, P4_0_SCB0_SPI_MOSI},
};

/* Connections for: scb_spi_m_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[3] = {
    {1u, 0u, P1_0, P1_0_SCB1_SPI_SELECT0},
    {1u, 0u, P5_0, P5_0_SCB1_SPI_SELECT0},
    {0u, 0u, P5_1, P5_1_SCB0_SPI_SELECT0},
};

/* Connections for: scb_spi_m_select1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select1[1] = {
    {1u, 0u, P0_5, P0_5_SCB1_SPI_SELECT1},
};

/* Connections for: scb_spi_m_select2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select2[1] = {
    {1u, 0u, P0_4, P0_4_SCB1_SPI_SELECT2},
};

/* Connections for: scb_spi_m_select3 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select3[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: scb_spi_s_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[3] = {
    {0u, 0u, P0_4, P0_4_SCB0_SPI_CLK},
    {1u, 0u, P1_1, P1_1_SCB1_SPI_CLK},
    {1u, 0u, P3_1, P3_1_SCB1_SPI_CLK},
};

/* Connections for: scb_spi_s_miso */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[3] = {
    {1u, 0u, P1_3, P1_3_SCB1_SPI_MISO},
    {1u, 0u, P3_3, P3_3_SCB1_SPI_MISO},
    {0u, 0u, P4_1, P4_1_SCB0_SPI_MISO},
};

/* Connections for: scb_spi_s_mosi */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[3] = {
    {1u, 0u, P1_2, P1_2_SCB1_SPI_MOSI},
    {1u, 0u, P3_2, P3_2_SCB1_SPI_MOSI},
    {0u, 0u, P4_0, P4_0_SCB0_SPI_MOSI},
};

/* Connections for: scb_spi_s_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[3] = {
    {1u, 0u, P1_0, P1_0_SCB1_SPI_SELECT0},
    {1u, 0u, P5_0, P5_0_SCB1_SPI_SELECT0},
    {0u, 0u, P5_1, P5_1_SCB0_SPI_SELECT0},
};

/* Connections for: scb_spi_s_select1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select1[1] = {
    {1u, 0u, P0_5, P0_5_SCB1_SPI_SELECT1},
};

/* Connections for: scb_spi_s_select2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select2[1] = {
    {1u, 0u, P0_4, P0_4_SCB1_SPI_SELECT2},
};

/* Connections for: scb_spi_s_select3 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select3[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: scb_uart_cts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[3] = {
    {1u, 0u, P1_0, P1_0_SCB1_UART_CTS},
    {2u, 0u, P4_0, P4_0_SCB2_UART_CTS},
    {2u, 0u, P5_0, P5_0_SCB2_UART_CTS},
};

/* Connections for: scb_uart_rts */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[2] = {
    {1u, 0u, P1_1, P1_1_SCB1_UART_RTS},
    {2u, 0u, P3_1, P3_1_SCB2_UART_RTS},
};

/* Connections for: scb_uart_rx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[2] = {
    {1u, 0u, P1_2, P1_2_SCB1_UART_RX},
    {2u, 0u, P3_2, P3_2_SCB2_UART_RX},
};

/* Connections for: scb_uart_tx */
const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[2] = {
    {1u, 0u, P1_3, P1_3_SCB1_UART_TX},
    {2u, 0u, P3_3, P3_3_SCB2_UART_TX},
};

/* Connections for: smif_spi_clk */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_clk[1] = {
    {0u, 0u, P2_5, P2_5_SMIF_SPIHB_CLK},
};

/* Connections for: smif_spi_data0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data0[1] = {
    {0u, 0u, P2_4, P2_4_SMIF_SPIHB_DATA0},
};

/* Connections for: smif_spi_data1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data1[1] = {
    {0u, 0u, P2_3, P2_3_SMIF_SPIHB_DATA1},
};

/* Connections for: smif_spi_data2 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data2[1] = {
    {0u, 0u, P2_2, P2_2_SMIF_SPIHB_DATA2},
};

/* Connections for: smif_spi_data3 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data3[1] = {
    {0u, 0u, P2_1, P2_1_SMIF_SPIHB_DATA3},
};

/* Connections for: smif_spi_select0 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_select0[1] = {
    {0u, 0u, P2_0, P2_0_SMIF_SPIHB_SELECT0},
};

/* Connections for: smif_spi_select1 */
const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_select1[1] = {
    {0u, 0u, P0_5, P0_5_SMIF_SPIHB_SELECT1},
};

/* Connections for: tcpwm_line */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[12] = {
    {0u, 1u, P0_5, P0_5_TCPWM0_LINE1},
    {1u, 2u, P0_5, P0_5_TCPWM0_LINE258},
    {0u, 0u, P1_1, P1_1_TCPWM0_LINE0},
    {1u, 3u, P1_1, P1_1_TCPWM0_LINE259},
    {0u, 1u, P1_3, P1_3_TCPWM0_LINE1},
    {1u, 4u, P1_3, P1_3_TCPWM0_LINE260},
    {0u, 1u, P3_2, P3_2_TCPWM0_LINE1},
    {1u, 1u, P3_2, P3_2_TCPWM0_LINE257},
    {0u, 0u, P4_1, P4_1_TCPWM0_LINE0},
    {1u, 6u, P4_1, P4_1_TCPWM0_LINE262},
    {0u, 0u, P5_0, P5_0_TCPWM0_LINE0},
    {1u, 4u, P5_0, P5_0_TCPWM0_LINE260},
};

/* Connections for: tcpwm_line_compl */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line_compl[14] = {
    {0u, 0u, P0_4, P0_4_TCPWM0_LINE_COMPL0},
    {1u, 1u, P0_4, P0_4_TCPWM0_LINE_COMPL257},
    {0u, 1u, P1_0, P1_0_TCPWM0_LINE_COMPL1},
    {1u, 2u, P1_0, P1_0_TCPWM0_LINE_COMPL258},
    {0u, 0u, P1_2, P1_2_TCPWM0_LINE_COMPL0},
    {1u, 3u, P1_2, P1_2_TCPWM0_LINE_COMPL259},
    {0u, 0u, P3_1, P3_1_TCPWM0_LINE_COMPL0},
    {1u, 0u, P3_1, P3_1_TCPWM0_LINE_COMPL256},
    {0u, 1u, P3_3, P3_3_TCPWM0_LINE_COMPL1},
    {1u, 1u, P3_3, P3_3_TCPWM0_LINE_COMPL257},
    {0u, 1u, P4_0, P4_0_TCPWM0_LINE_COMPL1},
    {1u, 5u, P4_0, P4_0_TCPWM0_LINE_COMPL261},
    {0u, 0u, P5_1, P5_1_TCPWM0_LINE_COMPL0},
    {1u, 4u, P5_1, P5_1_TCPWM0_LINE_COMPL260},
};

/* Connections for: tdm_tdm_rx_fsync */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_fsync[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: tdm_tdm_rx_mck */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_mck[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: tdm_tdm_rx_sck */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_sck[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: tdm_tdm_rx_sd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_sd[1] = {
    {0u, 0u, NC, HSIOM_SEL_GPIO},
};

/* Connections for: tdm_tdm_tx_fsync */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_fsync[1] = {
    {0u, 0u, P1_0, P1_0_TDM_TDM_TX_FSYNC0},
};

/* Connections for: tdm_tdm_tx_mck */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_mck[1] = {
    {0u, 0u, P0_4, P0_4_TDM_TDM_TX_MCK0},
};

/* Connections for: tdm_tdm_tx_sck */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_sck[1] = {
    {0u, 0u, P0_5, P0_5_TDM_TDM_TX_SCK0},
};

/* Connections for: tdm_tdm_tx_sd */
const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_sd[1] = {
    {0u, 0u, P1_1, P1_1_TDM_TDM_TX_SD0},
};

#endif
