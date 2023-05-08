/***************************************************************************//**
* \file cyhal_psoc6_03_68_qfn.h
*
* \brief
* PSoC6_03 device GPIO HAL header for 68-QFN package
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

#ifndef _CYHAL_PSOC6_03_68_QFN_H_
#define _CYHAL_PSOC6_03_68_QFN_H_

#include "cyhal_hw_resources.h"

/**
 * \addtogroup group_hal_impl_pin_package_psoc6_03_68_qfn PSoC6_03 68-QFN
 * \ingroup group_hal_impl_pin_package
 * \{
 * Pin definitions and connections specific to the PSoC6_03 68-QFN package.
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

/** Definitions for all of the pins that are bonded out on in the 68-QFN package for the PSoC6_03 series. */
typedef enum {
    NC = 0xFF, //!< No Connect/Invalid Pin

    P0_0 = CYHAL_GET_GPIO(CYHAL_PORT_0, 0), //!< Port 0 Pin 0
    P0_1 = CYHAL_GET_GPIO(CYHAL_PORT_0, 1), //!< Port 0 Pin 1
    P0_2 = CYHAL_GET_GPIO(CYHAL_PORT_0, 2), //!< Port 0 Pin 2
    P0_3 = CYHAL_GET_GPIO(CYHAL_PORT_0, 3), //!< Port 0 Pin 3
    P0_4 = CYHAL_GET_GPIO(CYHAL_PORT_0, 4), //!< Port 0 Pin 4
    P0_5 = CYHAL_GET_GPIO(CYHAL_PORT_0, 5), //!< Port 0 Pin 5

    P2_0 = CYHAL_GET_GPIO(CYHAL_PORT_2, 0), //!< Port 2 Pin 0
    P2_1 = CYHAL_GET_GPIO(CYHAL_PORT_2, 1), //!< Port 2 Pin 1
    P2_2 = CYHAL_GET_GPIO(CYHAL_PORT_2, 2), //!< Port 2 Pin 2
    P2_3 = CYHAL_GET_GPIO(CYHAL_PORT_2, 3), //!< Port 2 Pin 3
    P2_4 = CYHAL_GET_GPIO(CYHAL_PORT_2, 4), //!< Port 2 Pin 4
    P2_5 = CYHAL_GET_GPIO(CYHAL_PORT_2, 5), //!< Port 2 Pin 5
    P2_6 = CYHAL_GET_GPIO(CYHAL_PORT_2, 6), //!< Port 2 Pin 6
    P2_7 = CYHAL_GET_GPIO(CYHAL_PORT_2, 7), //!< Port 2 Pin 7

    P3_0 = CYHAL_GET_GPIO(CYHAL_PORT_3, 0), //!< Port 3 Pin 0
    P3_1 = CYHAL_GET_GPIO(CYHAL_PORT_3, 1), //!< Port 3 Pin 1

    P5_0 = CYHAL_GET_GPIO(CYHAL_PORT_5, 0), //!< Port 5 Pin 0
    P5_1 = CYHAL_GET_GPIO(CYHAL_PORT_5, 1), //!< Port 5 Pin 1
    P5_6 = CYHAL_GET_GPIO(CYHAL_PORT_5, 6), //!< Port 5 Pin 6
    P5_7 = CYHAL_GET_GPIO(CYHAL_PORT_5, 7), //!< Port 5 Pin 7

    P6_2 = CYHAL_GET_GPIO(CYHAL_PORT_6, 2), //!< Port 6 Pin 2
    P6_3 = CYHAL_GET_GPIO(CYHAL_PORT_6, 3), //!< Port 6 Pin 3
    P6_4 = CYHAL_GET_GPIO(CYHAL_PORT_6, 4), //!< Port 6 Pin 4
    P6_5 = CYHAL_GET_GPIO(CYHAL_PORT_6, 5), //!< Port 6 Pin 5
    P6_6 = CYHAL_GET_GPIO(CYHAL_PORT_6, 6), //!< Port 6 Pin 6
    P6_7 = CYHAL_GET_GPIO(CYHAL_PORT_6, 7), //!< Port 6 Pin 7

    P7_0 = CYHAL_GET_GPIO(CYHAL_PORT_7, 0), //!< Port 7 Pin 0
    P7_1 = CYHAL_GET_GPIO(CYHAL_PORT_7, 1), //!< Port 7 Pin 1
    P7_2 = CYHAL_GET_GPIO(CYHAL_PORT_7, 2), //!< Port 7 Pin 2
    P7_3 = CYHAL_GET_GPIO(CYHAL_PORT_7, 3), //!< Port 7 Pin 3
    P7_7 = CYHAL_GET_GPIO(CYHAL_PORT_7, 7), //!< Port 7 Pin 7

    P8_0 = CYHAL_GET_GPIO(CYHAL_PORT_8, 0), //!< Port 8 Pin 0
    P8_1 = CYHAL_GET_GPIO(CYHAL_PORT_8, 1), //!< Port 8 Pin 1

    P9_0 = CYHAL_GET_GPIO(CYHAL_PORT_9, 0), //!< Port 9 Pin 0
    P9_1 = CYHAL_GET_GPIO(CYHAL_PORT_9, 1), //!< Port 9 Pin 1
    P9_2 = CYHAL_GET_GPIO(CYHAL_PORT_9, 2), //!< Port 9 Pin 2
    P9_3 = CYHAL_GET_GPIO(CYHAL_PORT_9, 3), //!< Port 9 Pin 3

    P10_0 = CYHAL_GET_GPIO(CYHAL_PORT_10, 0), //!< Port 10 Pin 0
    P10_1 = CYHAL_GET_GPIO(CYHAL_PORT_10, 1), //!< Port 10 Pin 1
    P10_2 = CYHAL_GET_GPIO(CYHAL_PORT_10, 2), //!< Port 10 Pin 2
    P10_3 = CYHAL_GET_GPIO(CYHAL_PORT_10, 3), //!< Port 10 Pin 3
    P10_4 = CYHAL_GET_GPIO(CYHAL_PORT_10, 4), //!< Port 10 Pin 4
    P10_5 = CYHAL_GET_GPIO(CYHAL_PORT_10, 5), //!< Port 10 Pin 5

    P11_0 = CYHAL_GET_GPIO(CYHAL_PORT_11, 0), //!< Port 11 Pin 0
    P11_1 = CYHAL_GET_GPIO(CYHAL_PORT_11, 1), //!< Port 11 Pin 1
    P11_2 = CYHAL_GET_GPIO(CYHAL_PORT_11, 2), //!< Port 11 Pin 2
    P11_3 = CYHAL_GET_GPIO(CYHAL_PORT_11, 3), //!< Port 11 Pin 3
    P11_4 = CYHAL_GET_GPIO(CYHAL_PORT_11, 4), //!< Port 11 Pin 4
    P11_5 = CYHAL_GET_GPIO(CYHAL_PORT_11, 5), //!< Port 11 Pin 5
    P11_6 = CYHAL_GET_GPIO(CYHAL_PORT_11, 6), //!< Port 11 Pin 6
    P11_7 = CYHAL_GET_GPIO(CYHAL_PORT_11, 7), //!< Port 11 Pin 7

    P12_6 = CYHAL_GET_GPIO(CYHAL_PORT_12, 6), //!< Port 12 Pin 6
    P12_7 = CYHAL_GET_GPIO(CYHAL_PORT_12, 7), //!< Port 12 Pin 7

    USBDP = CYHAL_GET_GPIO(CYHAL_PORT_14, 0), //!< Port 14 Pin 0
    USBDM = CYHAL_GET_GPIO(CYHAL_PORT_14, 1), //!< Port 14 Pin 1
} cyhal_gpio_psoc6_03_68_qfn_t;

/** Create generic name for the series/package specific type. */
typedef cyhal_gpio_psoc6_03_68_qfn_t cyhal_gpio_t;

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
/** Indicates that a pin map exists for canfd_ttcan_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CANFD_TTCAN_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the canfd_ttcan_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_rx[1];
/** Indicates that a pin map exists for canfd_ttcan_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CANFD_TTCAN_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the canfd_ttcan_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_tx[1];
/** Indicates that a pin map exists for cpuss_clk_fm_pump*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_CLK_FM_PUMP (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_clk_fm_pump signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_clk_fm_pump[1];
/** Indicates that a pin map exists for cpuss_fault_out*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_FAULT_OUT (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_fault_out signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_fault_out[1];
/** Indicates that a pin map exists for cpuss_swj_swclk_tclk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_SWJ_SWCLK_TCLK (CY_GPIO_DM_PULLDOWN)
/** List of valid pin to peripheral connections for the cpuss_swj_swclk_tclk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_swclk_tclk[1];
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
/** Indicates that a pin map exists for cpuss_swj_trstn*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_SWJ_TRSTN (CY_GPIO_DM_PULLUP)
/** List of valid pin to peripheral connections for the cpuss_swj_trstn signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_swj_trstn[1];
/** Indicates that a pin map exists for cpuss_trace_clock*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_TRACE_CLOCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_trace_clock signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_trace_clock[1];
/** Indicates that a pin map exists for cpuss_trace_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_TRACE_DATA (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_trace_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_trace_data[9];
/** Indicates that a pin map exists for lpcomp_dsi_comp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LPCOMP_DSI_COMP (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the lpcomp_dsi_comp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_dsi_comp[1];
/** Indicates that a pin map exists for lpcomp_inn_comp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LPCOMP_INN_COMP (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the lpcomp_inn_comp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inn_comp[2];
/** Indicates that a pin map exists for lpcomp_inp_comp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LPCOMP_INP_COMP (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the lpcomp_inp_comp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inp_comp[2];
/** Indicates that a pin map exists for pass_sarmux_pads*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_SARMUX_PADS (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the pass_sarmux_pads signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sarmux_pads[6];
/** Indicates that a pin map exists for peri_tr_io_input*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PERI_TR_IO_INPUT (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the peri_tr_io_input signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_input[24];
/** Indicates that a pin map exists for peri_tr_io_output*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PERI_TR_IO_OUTPUT (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the peri_tr_io_output signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_output[6];
/** Indicates that a pin map exists for scb_i2c_scl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SCL (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[10];
/** Indicates that a pin map exists for scb_i2c_sda*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SDA (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_sda signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[10];
/** Indicates that a pin map exists for scb_spi_m_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[8];
/** Indicates that a pin map exists for scb_spi_m_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MISO (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_m_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[10];
/** Indicates that a pin map exists for scb_spi_m_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MOSI (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[10];
/** Indicates that a pin map exists for scb_spi_m_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[8];
/** Indicates that a pin map exists for scb_spi_m_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select1[4];
/** Indicates that a pin map exists for scb_spi_m_select2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT2 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select2[4];
/** Indicates that a pin map exists for scb_spi_m_select3*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT3 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select3[2];
/** Indicates that a pin map exists for scb_spi_s_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_CLK (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[8];
/** Indicates that a pin map exists for scb_spi_s_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MISO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_s_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[10];
/** Indicates that a pin map exists for scb_spi_s_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MOSI (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[10];
/** Indicates that a pin map exists for scb_spi_s_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[8];
/** Indicates that a pin map exists for scb_spi_s_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT1 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select1[4];
/** Indicates that a pin map exists for scb_spi_s_select2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT2 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select2[4];
/** Indicates that a pin map exists for scb_spi_s_select3*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT3 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select3[2];
/** Indicates that a pin map exists for scb_uart_cts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_CTS (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_cts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[7];
/** Indicates that a pin map exists for scb_uart_rts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RTS (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_rts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[7];
/** Indicates that a pin map exists for scb_uart_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[9];
/** Indicates that a pin map exists for scb_uart_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[9];
/** Indicates that a pin map exists for sdhc_card_cmd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_CMD (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the sdhc_card_cmd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_cmd[1];
/** Indicates that a pin map exists for sdhc_card_dat_3to0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_3TO0 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the sdhc_card_dat_3to0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_dat_3to0[4];
/** Indicates that a pin map exists for sdhc_card_detect_n*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DETECT_N (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the sdhc_card_detect_n signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_detect_n[1];
/** Indicates that a pin map exists for sdhc_card_if_pwr_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_IF_PWR_EN (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the sdhc_card_if_pwr_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_if_pwr_en[1];
/** Indicates that a pin map exists for sdhc_card_mech_write_prot*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_MECH_WRITE_PROT (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the sdhc_card_mech_write_prot signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_mech_write_prot[1];
/** Indicates that a pin map exists for sdhc_clk_card*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CLK_CARD (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the sdhc_clk_card signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_clk_card[1];
/** Indicates that a pin map exists for sdhc_io_volt_sel*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_IO_VOLT_SEL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the sdhc_io_volt_sel signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_io_volt_sel[1];
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
/** Indicates that a pin map exists for smif_spi_select2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_SELECT2 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_spi_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_select2[1];
/** Indicates that a pin map exists for tcpwm_line*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_LINE (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_line signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[52];
/** Indicates that a pin map exists for tcpwm_line_compl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_LINE_COMPL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_line_compl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line_compl[54];
/** Indicates that a pin map exists for usb_usb_dm_pad*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USB_USB_DM_PAD (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the usb_usb_dm_pad signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_usb_dm_pad[1];
/** Indicates that a pin map exists for usb_usb_dp_pad*/
#define CYHAL_PIN_MAP_DRIVE_MODE_USB_USB_DP_PAD (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the usb_usb_dp_pad signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_usb_usb_dp_pad[1];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_pin_package */

#endif /* _CYHAL_PSOC6_03_68_QFN_H_ */


/* [] END OF FILE */
