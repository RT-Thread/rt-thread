/***************************************************************************//**
* \file cyhal_cyw20829_40_qfn.h
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

#ifndef _CYHAL_CYW20829_40_QFN_H_
#define _CYHAL_CYW20829_40_QFN_H_

#include "cyhal_hw_resources.h"

/**
 * \addtogroup group_hal_impl_pin_package_cyw20829_40_qfn CYW20829 40-QFN
 * \ingroup group_hal_impl_pin_package
 * \{
 * Pin definitions and connections specific to the CYW20829 40-QFN package.
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** Gets a pin definition from the provided port and pin numbers */
#define CYHAL_GET_GPIO(port, pin)   ((((uint8_t)(port)) << 3U) + ((uint8_t)(pin)))

/** Macro that, given a gpio, will extract the pin number */
#define CYHAL_GET_PIN(pin)          ((uint8_t)(((uint8_t)pin) & 0x07U))
/** Macro that, given a gpio, will extract the port number */
#define CYHAL_GET_PORT(pin)         ((uint8_t)(((uint8_t)pin) >> 3U))

/** Definitions for all of the pins that are bonded out on in the 40-QFN package for the CYW20829 series. */
typedef enum {
    NC = 0xFF, //!< No Connect/Invalid Pin

    P0_4 = CYHAL_GET_GPIO(CYHAL_PORT_0, 4), //!< Port 0 Pin 4
    P0_5 = CYHAL_GET_GPIO(CYHAL_PORT_0, 5), //!< Port 0 Pin 5

    P1_0 = CYHAL_GET_GPIO(CYHAL_PORT_1, 0), //!< Port 1 Pin 0
    P1_1 = CYHAL_GET_GPIO(CYHAL_PORT_1, 1), //!< Port 1 Pin 1
    P1_2 = CYHAL_GET_GPIO(CYHAL_PORT_1, 2), //!< Port 1 Pin 2
    P1_3 = CYHAL_GET_GPIO(CYHAL_PORT_1, 3), //!< Port 1 Pin 3

    P2_0 = CYHAL_GET_GPIO(CYHAL_PORT_2, 0), //!< Port 2 Pin 0
    P2_1 = CYHAL_GET_GPIO(CYHAL_PORT_2, 1), //!< Port 2 Pin 1
    P2_2 = CYHAL_GET_GPIO(CYHAL_PORT_2, 2), //!< Port 2 Pin 2
    P2_3 = CYHAL_GET_GPIO(CYHAL_PORT_2, 3), //!< Port 2 Pin 3
    P2_4 = CYHAL_GET_GPIO(CYHAL_PORT_2, 4), //!< Port 2 Pin 4
    P2_5 = CYHAL_GET_GPIO(CYHAL_PORT_2, 5), //!< Port 2 Pin 5

    P3_1 = CYHAL_GET_GPIO(CYHAL_PORT_3, 1), //!< Port 3 Pin 1
    P3_2 = CYHAL_GET_GPIO(CYHAL_PORT_3, 2), //!< Port 3 Pin 2
    P3_3 = CYHAL_GET_GPIO(CYHAL_PORT_3, 3), //!< Port 3 Pin 3

    P4_0 = CYHAL_GET_GPIO(CYHAL_PORT_4, 0), //!< Port 4 Pin 0
    P4_1 = CYHAL_GET_GPIO(CYHAL_PORT_4, 1), //!< Port 4 Pin 1

    P5_0 = CYHAL_GET_GPIO(CYHAL_PORT_5, 0), //!< Port 5 Pin 0
    P5_1 = CYHAL_GET_GPIO(CYHAL_PORT_5, 1), //!< Port 5 Pin 1
} cyhal_gpio_cyw20829_40_qfn_t;

/** Create generic name for the series/package specific type. */
typedef cyhal_gpio_cyw20829_40_qfn_t cyhal_gpio_t;

/* Connection type definition */
/** Represents an association between a pin and a resource */
typedef struct
{
    uint8_t         block_num;   //!< The block number of the resource with this connection
    uint8_t         channel_num; //!< The channel number of the block with this connection
    cyhal_gpio_t    pin;         //!< The GPIO pin the connection is with
    en_hsiom_sel_t  hsiom;       //!< The HSIOM configuration value
} cyhal_resource_pin_mapping_t;

/* Pin connections */
/** Indicates that a pin map exists for adcmic_clk_pdm*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ADCMIC_CLK_PDM (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the adcmic_clk_pdm signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_adcmic_clk_pdm[2];
/** Indicates that a pin map exists for adcmic_gpio_adc_in*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ADCMIC_GPIO_ADC_IN (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the adcmic_gpio_adc_in signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_adcmic_gpio_adc_in[3];
/** Indicates that a pin map exists for adcmic_pdm_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ADCMIC_PDM_DATA (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the adcmic_pdm_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_adcmic_pdm_data[2];
/** Indicates that a pin map exists for canfd_ttcan_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CANFD_TTCAN_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the canfd_ttcan_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_rx[1];
/** Indicates that a pin map exists for canfd_ttcan_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CANFD_TTCAN_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the canfd_ttcan_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_tx[1];
/** Indicates that a pin map exists for cpuss_clk_swj_swclk_tclk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_CLK_SWJ_SWCLK_TCLK (CY_GPIO_DM_PULLDOWN)
/** List of valid pin to peripheral connections for the cpuss_clk_swj_swclk_tclk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_clk_swj_swclk_tclk[1];
/** Indicates that a pin map exists for cpuss_rst_swj_trstn*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_RST_SWJ_TRSTN (CY_GPIO_DM_PULLUP)
/** List of valid pin to peripheral connections for the cpuss_rst_swj_trstn signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_rst_swj_trstn[1];
/** Indicates that a pin map exists for cpuss_swj_swdio_tms*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_SWJ_SWDIO_TMS (CY_GPIO_DM_PULLUP)
/** List of valid pin to peripheral connections for the cpuss_swj_swdio_tms signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swdio_tms[1];
/** Indicates that a pin map exists for cpuss_swj_swdoe_tdi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_SWJ_SWDOE_TDI (CY_GPIO_DM_PULLUP)
/** List of valid pin to peripheral connections for the cpuss_swj_swdoe_tdi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swdoe_tdi[1];
/** Indicates that a pin map exists for cpuss_swj_swo_tdo*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_SWJ_SWO_TDO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_swj_swo_tdo signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swo_tdo[1];
/** Indicates that a pin map exists for cpuss_trace_clock*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_TRACE_CLOCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_trace_clock signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_trace_clock[1];
/** Indicates that a pin map exists for cpuss_trace_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_TRACE_DATA (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_trace_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_trace_data[7];
/** Indicates that a pin map exists for keyscan_ks_col*/
#define CYHAL_PIN_MAP_DRIVE_MODE_KEYSCAN_KS_COL (CY_GPIO_DM_PULLUP)
/** List of valid pin to peripheral connections for the keyscan_ks_col signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_keyscan_ks_col[2];
/** Indicates that a pin map exists for keyscan_ks_row*/
#define CYHAL_PIN_MAP_DRIVE_MODE_KEYSCAN_KS_ROW (CY_GPIO_DM_PULLUP)
/** List of valid pin to peripheral connections for the keyscan_ks_row signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_keyscan_ks_row[7];
/** Indicates that a pin map exists for lin_lin_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LIN_LIN_EN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the lin_lin_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_en[1];
/** Indicates that a pin map exists for lin_lin_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LIN_LIN_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the lin_lin_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_rx[1];
/** Indicates that a pin map exists for lin_lin_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LIN_LIN_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the lin_lin_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_tx[1];
/** Indicates that a pin map exists for pdm_pdm_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PDM_PDM_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the pdm_pdm_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pdm_pdm_clk[2];
/** Indicates that a pin map exists for pdm_pdm_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PDM_PDM_DATA (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the pdm_pdm_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pdm_pdm_data[2];
/** Indicates that a pin map exists for peri_tr_io_input*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PERI_TR_IO_INPUT (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the peri_tr_io_input signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_input[6];
/** Indicates that a pin map exists for peri_tr_io_output*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PERI_TR_IO_OUTPUT (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the peri_tr_io_output signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_output[2];
/** Indicates that a pin map exists for scb_i2c_scl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SCL (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[3];
/** Indicates that a pin map exists for scb_i2c_sda*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SDA (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_sda signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[3];
/** Indicates that a pin map exists for scb_spi_m_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[3];
/** Indicates that a pin map exists for scb_spi_m_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MISO (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_m_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[3];
/** Indicates that a pin map exists for scb_spi_m_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MOSI (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[3];
/** Indicates that a pin map exists for scb_spi_m_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[3];
/** Indicates that a pin map exists for scb_spi_m_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select1[1];
/** Indicates that a pin map exists for scb_spi_m_select2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT2 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select2[1];
/** Indicates that a pin map exists for scb_spi_m_select3*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT3 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select3[1];
/** Indicates that a pin map exists for scb_spi_s_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_CLK (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[3];
/** Indicates that a pin map exists for scb_spi_s_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MISO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_s_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[3];
/** Indicates that a pin map exists for scb_spi_s_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MOSI (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[3];
/** Indicates that a pin map exists for scb_spi_s_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[3];
/** Indicates that a pin map exists for scb_spi_s_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT1 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select1[1];
/** Indicates that a pin map exists for scb_spi_s_select2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT2 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select2[1];
/** Indicates that a pin map exists for scb_spi_s_select3*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT3 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select3[1];
/** Indicates that a pin map exists for scb_uart_cts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_CTS (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_cts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[3];
/** Indicates that a pin map exists for scb_uart_rts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RTS (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_rts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[2];
/** Indicates that a pin map exists for scb_uart_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[2];
/** Indicates that a pin map exists for scb_uart_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[2];
/** Indicates that a pin map exists for smif_spi_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_CLK (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the smif_spi_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_clk[1];
/** Indicates that a pin map exists for smif_spi_data0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_DATA0 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the smif_spi_data0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data0[1];
/** Indicates that a pin map exists for smif_spi_data1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_DATA1 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the smif_spi_data1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data1[1];
/** Indicates that a pin map exists for smif_spi_data2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_DATA2 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the smif_spi_data2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data2[1];
/** Indicates that a pin map exists for smif_spi_data3*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_DATA3 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the smif_spi_data3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data3[1];
/** Indicates that a pin map exists for smif_spi_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_SELECT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_spi_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_select0[1];
/** Indicates that a pin map exists for smif_spi_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_SELECT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_spi_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_select1[1];
/** Indicates that a pin map exists for tcpwm_line*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_LINE (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_line signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[12];
/** Indicates that a pin map exists for tcpwm_line_compl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_LINE_COMPL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_line_compl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line_compl[14];
/** Indicates that a pin map exists for tdm_tdm_rx_fsync*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_FSYNC (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_rx_fsync signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_fsync[1];
/** Indicates that a pin map exists for tdm_tdm_rx_mck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_MCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_rx_mck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_mck[1];
/** Indicates that a pin map exists for tdm_tdm_rx_sck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_SCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_rx_sck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_sck[1];
/** Indicates that a pin map exists for tdm_tdm_rx_sd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_SD (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the tdm_tdm_rx_sd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_sd[1];
/** Indicates that a pin map exists for tdm_tdm_tx_fsync*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_FSYNC (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_tx_fsync signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_fsync[1];
/** Indicates that a pin map exists for tdm_tdm_tx_mck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_MCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_tx_mck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_mck[1];
/** Indicates that a pin map exists for tdm_tdm_tx_sck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_SCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_tx_sck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_sck[1];
/** Indicates that a pin map exists for tdm_tdm_tx_sd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_SD (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_tx_sd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_sd[1];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_pin_package */

#endif /* _CYHAL_CYW20829_40_QFN_H_ */


/* [] END OF FILE */
