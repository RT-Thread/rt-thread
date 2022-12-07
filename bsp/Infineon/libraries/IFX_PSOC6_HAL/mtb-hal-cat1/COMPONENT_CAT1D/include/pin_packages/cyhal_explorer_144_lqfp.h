/***************************************************************************//**
* \file cyhal_explorer_144_lqfp.h
*
* \brief
* Explorer device GPIO HAL header for 144-LQFP package
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
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

#ifndef _CYHAL_EXPLORER_144_LQFP_H_
#define _CYHAL_EXPLORER_144_LQFP_H_

#include "cyhal_hw_resources.h"

/**
 * \addtogroup group_hal_impl_pin_package_explorer_144_lqfp Explorer 144-LQFP
 * \ingroup group_hal_impl_pin_package
 * \{
 * Pin definitions and connections specific to the Explorer 144-LQFP package.
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

/** Definitions for all of the pins that are bonded out on in the 144-LQFP package for the Explorer series. */
typedef enum {
    NC = 0xFF, //!< No Connect/Invalid Pin

    P0_2 = CYHAL_GET_GPIO(CYHAL_PORT_0, 2), //!< Port 0 Pin 2

    P1_0 = CYHAL_GET_GPIO(CYHAL_PORT_1, 0), //!< Port 1 Pin 0
    P1_1 = CYHAL_GET_GPIO(CYHAL_PORT_1, 1), //!< Port 1 Pin 1
    P1_2 = CYHAL_GET_GPIO(CYHAL_PORT_1, 2), //!< Port 1 Pin 2
    P1_3 = CYHAL_GET_GPIO(CYHAL_PORT_1, 3), //!< Port 1 Pin 3
    P1_4 = CYHAL_GET_GPIO(CYHAL_PORT_1, 4), //!< Port 1 Pin 4
    P1_5 = CYHAL_GET_GPIO(CYHAL_PORT_1, 5), //!< Port 1 Pin 5
    P1_6 = CYHAL_GET_GPIO(CYHAL_PORT_1, 6), //!< Port 1 Pin 6
    P1_7 = CYHAL_GET_GPIO(CYHAL_PORT_1, 7), //!< Port 1 Pin 7

    P2_0 = CYHAL_GET_GPIO(CYHAL_PORT_2, 0), //!< Port 2 Pin 0

    P3_0 = CYHAL_GET_GPIO(CYHAL_PORT_3, 0), //!< Port 3 Pin 0

    P4_0 = CYHAL_GET_GPIO(CYHAL_PORT_4, 0), //!< Port 4 Pin 0
    P4_1 = CYHAL_GET_GPIO(CYHAL_PORT_4, 1), //!< Port 4 Pin 1
    P4_2 = CYHAL_GET_GPIO(CYHAL_PORT_4, 2), //!< Port 4 Pin 2
    P4_3 = CYHAL_GET_GPIO(CYHAL_PORT_4, 3), //!< Port 4 Pin 3
    P4_4 = CYHAL_GET_GPIO(CYHAL_PORT_4, 4), //!< Port 4 Pin 4
    P4_5 = CYHAL_GET_GPIO(CYHAL_PORT_4, 5), //!< Port 4 Pin 5
    P4_6 = CYHAL_GET_GPIO(CYHAL_PORT_4, 6), //!< Port 4 Pin 6
    P4_7 = CYHAL_GET_GPIO(CYHAL_PORT_4, 7), //!< Port 4 Pin 7

    P5_0 = CYHAL_GET_GPIO(CYHAL_PORT_5, 0), //!< Port 5 Pin 0

    P6_0 = CYHAL_GET_GPIO(CYHAL_PORT_6, 0), //!< Port 6 Pin 0
    P6_1 = CYHAL_GET_GPIO(CYHAL_PORT_6, 1), //!< Port 6 Pin 1
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
    P7_4 = CYHAL_GET_GPIO(CYHAL_PORT_7, 4), //!< Port 7 Pin 4
    P7_5 = CYHAL_GET_GPIO(CYHAL_PORT_7, 5), //!< Port 7 Pin 5
    P7_6 = CYHAL_GET_GPIO(CYHAL_PORT_7, 6), //!< Port 7 Pin 6

    P8_0 = CYHAL_GET_GPIO(CYHAL_PORT_8, 0), //!< Port 8 Pin 0
    P8_1 = CYHAL_GET_GPIO(CYHAL_PORT_8, 1), //!< Port 8 Pin 1
    P8_2 = CYHAL_GET_GPIO(CYHAL_PORT_8, 2), //!< Port 8 Pin 2
    P8_3 = CYHAL_GET_GPIO(CYHAL_PORT_8, 3), //!< Port 8 Pin 3
    P8_4 = CYHAL_GET_GPIO(CYHAL_PORT_8, 4), //!< Port 8 Pin 4
    P8_5 = CYHAL_GET_GPIO(CYHAL_PORT_8, 5), //!< Port 8 Pin 5
    P8_6 = CYHAL_GET_GPIO(CYHAL_PORT_8, 6), //!< Port 8 Pin 6
    P8_7 = CYHAL_GET_GPIO(CYHAL_PORT_8, 7), //!< Port 8 Pin 7

    P9_1 = CYHAL_GET_GPIO(CYHAL_PORT_9, 1), //!< Port 9 Pin 1
    P9_2 = CYHAL_GET_GPIO(CYHAL_PORT_9, 2), //!< Port 9 Pin 2
    P9_3 = CYHAL_GET_GPIO(CYHAL_PORT_9, 3), //!< Port 9 Pin 3

    P10_2 = CYHAL_GET_GPIO(CYHAL_PORT_10, 2), //!< Port 10 Pin 2
    P10_3 = CYHAL_GET_GPIO(CYHAL_PORT_10, 3), //!< Port 10 Pin 3
    P10_4 = CYHAL_GET_GPIO(CYHAL_PORT_10, 4), //!< Port 10 Pin 4
    P10_5 = CYHAL_GET_GPIO(CYHAL_PORT_10, 5), //!< Port 10 Pin 5
    P10_6 = CYHAL_GET_GPIO(CYHAL_PORT_10, 6), //!< Port 10 Pin 6
    P10_7 = CYHAL_GET_GPIO(CYHAL_PORT_10, 7), //!< Port 10 Pin 7

    P11_0 = CYHAL_GET_GPIO(CYHAL_PORT_11, 0), //!< Port 11 Pin 0
    P11_1 = CYHAL_GET_GPIO(CYHAL_PORT_11, 1), //!< Port 11 Pin 1
    P11_2 = CYHAL_GET_GPIO(CYHAL_PORT_11, 2), //!< Port 11 Pin 2
    P11_3 = CYHAL_GET_GPIO(CYHAL_PORT_11, 3), //!< Port 11 Pin 3
    P11_4 = CYHAL_GET_GPIO(CYHAL_PORT_11, 4), //!< Port 11 Pin 4
    P11_5 = CYHAL_GET_GPIO(CYHAL_PORT_11, 5), //!< Port 11 Pin 5
    P11_6 = CYHAL_GET_GPIO(CYHAL_PORT_11, 6), //!< Port 11 Pin 6
    P11_7 = CYHAL_GET_GPIO(CYHAL_PORT_11, 7), //!< Port 11 Pin 7

    P12_0 = CYHAL_GET_GPIO(CYHAL_PORT_12, 0), //!< Port 12 Pin 0
    P12_1 = CYHAL_GET_GPIO(CYHAL_PORT_12, 1), //!< Port 12 Pin 1
    P12_2 = CYHAL_GET_GPIO(CYHAL_PORT_12, 2), //!< Port 12 Pin 2
    P12_3 = CYHAL_GET_GPIO(CYHAL_PORT_12, 3), //!< Port 12 Pin 3
    P12_4 = CYHAL_GET_GPIO(CYHAL_PORT_12, 4), //!< Port 12 Pin 4

    P13_0 = CYHAL_GET_GPIO(CYHAL_PORT_13, 0), //!< Port 13 Pin 0
    P13_1 = CYHAL_GET_GPIO(CYHAL_PORT_13, 1), //!< Port 13 Pin 1
    P13_2 = CYHAL_GET_GPIO(CYHAL_PORT_13, 2), //!< Port 13 Pin 2
    P13_3 = CYHAL_GET_GPIO(CYHAL_PORT_13, 3), //!< Port 13 Pin 3
    P13_4 = CYHAL_GET_GPIO(CYHAL_PORT_13, 4), //!< Port 13 Pin 4
    P13_5 = CYHAL_GET_GPIO(CYHAL_PORT_13, 5), //!< Port 13 Pin 5
    P13_6 = CYHAL_GET_GPIO(CYHAL_PORT_13, 6), //!< Port 13 Pin 6
    P13_7 = CYHAL_GET_GPIO(CYHAL_PORT_13, 7), //!< Port 13 Pin 7

    P15_1 = CYHAL_GET_GPIO(CYHAL_PORT_15, 1), //!< Port 15 Pin 1
    P15_2 = CYHAL_GET_GPIO(CYHAL_PORT_15, 2), //!< Port 15 Pin 2
    P15_3 = CYHAL_GET_GPIO(CYHAL_PORT_15, 3), //!< Port 15 Pin 3
    P15_4 = CYHAL_GET_GPIO(CYHAL_PORT_15, 4), //!< Port 15 Pin 4
    P15_5 = CYHAL_GET_GPIO(CYHAL_PORT_15, 5), //!< Port 15 Pin 5
    P15_6 = CYHAL_GET_GPIO(CYHAL_PORT_15, 6), //!< Port 15 Pin 6
    P15_7 = CYHAL_GET_GPIO(CYHAL_PORT_15, 7), //!< Port 15 Pin 7

    P16_0 = CYHAL_GET_GPIO(CYHAL_PORT_16, 0), //!< Port 16 Pin 0
    P16_1 = CYHAL_GET_GPIO(CYHAL_PORT_16, 1), //!< Port 16 Pin 1
    P16_2 = CYHAL_GET_GPIO(CYHAL_PORT_16, 2), //!< Port 16 Pin 2
    P16_3 = CYHAL_GET_GPIO(CYHAL_PORT_16, 3), //!< Port 16 Pin 3
    P16_4 = CYHAL_GET_GPIO(CYHAL_PORT_16, 4), //!< Port 16 Pin 4
    P16_5 = CYHAL_GET_GPIO(CYHAL_PORT_16, 5), //!< Port 16 Pin 5
    P16_6 = CYHAL_GET_GPIO(CYHAL_PORT_16, 6), //!< Port 16 Pin 6
    P16_7 = CYHAL_GET_GPIO(CYHAL_PORT_16, 7), //!< Port 16 Pin 7

    P17_0 = CYHAL_GET_GPIO(CYHAL_PORT_17, 0), //!< Port 17 Pin 0
    P17_1 = CYHAL_GET_GPIO(CYHAL_PORT_17, 1), //!< Port 17 Pin 1
    P17_2 = CYHAL_GET_GPIO(CYHAL_PORT_17, 2), //!< Port 17 Pin 2

    P18_0 = CYHAL_GET_GPIO(CYHAL_PORT_18, 0), //!< Port 18 Pin 0
    P18_1 = CYHAL_GET_GPIO(CYHAL_PORT_18, 1), //!< Port 18 Pin 1

    P19_0 = CYHAL_GET_GPIO(CYHAL_PORT_19, 0), //!< Port 19 Pin 0
    P19_1 = CYHAL_GET_GPIO(CYHAL_PORT_19, 1), //!< Port 19 Pin 1

    P20_0 = CYHAL_GET_GPIO(CYHAL_PORT_20, 0), //!< Port 20 Pin 0
    P20_1 = CYHAL_GET_GPIO(CYHAL_PORT_20, 1), //!< Port 20 Pin 1
    P20_2 = CYHAL_GET_GPIO(CYHAL_PORT_20, 2), //!< Port 20 Pin 2

    P23_0 = CYHAL_GET_GPIO(CYHAL_PORT_23, 0), //!< Port 23 Pin 0

    P24_0 = CYHAL_GET_GPIO(CYHAL_PORT_24, 0), //!< Port 24 Pin 0
} cyhal_gpio_explorer_144_lqfp_t;

/** Create generic name for the series/package specific type. */
typedef cyhal_gpio_explorer_144_lqfp_t cyhal_gpio_t;

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
#define CYHAL_PIN_MAP_DRIVE_MODE_CANFD_TTCAN_RX (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the canfd_ttcan_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_rx[2];
/** Indicates that a pin map exists for canfd_ttcan_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CANFD_TTCAN_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the canfd_ttcan_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_tx[2];
/** Indicates that a pin map exists for debug600_clk_swj_swclk_tclk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_DEBUG600_CLK_SWJ_SWCLK_TCLK (CY_GPIO_DM_PULLDOWN)
/** List of valid pin to peripheral connections for the debug600_clk_swj_swclk_tclk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_debug600_clk_swj_swclk_tclk[1];
/** Indicates that a pin map exists for debug600_rst_swj_trstn*/
#define CYHAL_PIN_MAP_DRIVE_MODE_DEBUG600_RST_SWJ_TRSTN (CY_GPIO_DM_PULLDOWN)
/** List of valid pin to peripheral connections for the debug600_rst_swj_trstn signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_debug600_rst_swj_trstn[1];
/** Indicates that a pin map exists for debug600_swj_swdio_tms*/
#define CYHAL_PIN_MAP_DRIVE_MODE_DEBUG600_SWJ_SWDIO_TMS (CY_GPIO_DM_PULLUP)
/** List of valid pin to peripheral connections for the debug600_swj_swdio_tms signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_debug600_swj_swdio_tms[1];
/** Indicates that a pin map exists for debug600_swj_swdoe_tdi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_DEBUG600_SWJ_SWDOE_TDI (CY_GPIO_DM_PULLUP)
/** List of valid pin to peripheral connections for the debug600_swj_swdoe_tdi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_debug600_swj_swdoe_tdi[1];
/** Indicates that a pin map exists for debug600_swj_swo_tdo*/
#define CYHAL_PIN_MAP_DRIVE_MODE_DEBUG600_SWJ_SWO_TDO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the debug600_swj_swo_tdo signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_debug600_swj_swo_tdo[1];
/** Indicates that a pin map exists for debug600_trace_clock*/
#define CYHAL_PIN_MAP_DRIVE_MODE_DEBUG600_TRACE_CLOCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the debug600_trace_clock signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_debug600_trace_clock[2];
/** Indicates that a pin map exists for debug600_trace_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_DEBUG600_TRACE_DATA (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the debug600_trace_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_debug600_trace_data[8];
/** Indicates that a pin map exists for eth_eth_tsu_timer_cmp_val*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_ETH_TSU_TIMER_CMP_VAL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the eth_eth_tsu_timer_cmp_val signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_eth_tsu_timer_cmp_val[1];
/** Indicates that a pin map exists for eth_mdc*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_MDC (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the eth_mdc signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_mdc[1];
/** Indicates that a pin map exists for eth_mdio*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_MDIO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the eth_mdio signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_mdio[1];
/** Indicates that a pin map exists for eth_ref_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_REF_CLK (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the eth_ref_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_ref_clk[1];
/** Indicates that a pin map exists for eth_rx_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_RX_CLK (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the eth_rx_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rx_clk[1];
/** Indicates that a pin map exists for eth_rx_ctl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_RX_CTL (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the eth_rx_ctl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rx_ctl[1];
/** Indicates that a pin map exists for eth_rx_er*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_RX_ER (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the eth_rx_er signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rx_er[1];
/** Indicates that a pin map exists for eth_rxd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_RXD (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the eth_rxd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rxd[2];
/** Indicates that a pin map exists for eth_tx_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_TX_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the eth_tx_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_tx_clk[1];
/** Indicates that a pin map exists for eth_tx_ctl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_TX_CTL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the eth_tx_ctl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_tx_ctl[1];
/** Indicates that a pin map exists for eth_txd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_TXD (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the eth_txd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_txd[4];
/** Indicates that a pin map exists for gfxss_dbi_csx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_GFXSS_DBI_CSX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the gfxss_dbi_csx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_gfxss_dbi_csx[1];
/** Indicates that a pin map exists for gfxss_dbi_d*/
#define CYHAL_PIN_MAP_DRIVE_MODE_GFXSS_DBI_D (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the gfxss_dbi_d signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_gfxss_dbi_d[8];
/** Indicates that a pin map exists for gfxss_dbi_dcx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_GFXSS_DBI_DCX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the gfxss_dbi_dcx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_gfxss_dbi_dcx[1];
/** Indicates that a pin map exists for gfxss_dbi_e*/
#define CYHAL_PIN_MAP_DRIVE_MODE_GFXSS_DBI_E (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the gfxss_dbi_e signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_gfxss_dbi_e[1];
/** Indicates that a pin map exists for gfxss_dbi_wrx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_GFXSS_DBI_WRX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the gfxss_dbi_wrx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_gfxss_dbi_wrx[1];
/** Indicates that a pin map exists for gfxss_spi_csx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_GFXSS_SPI_CSX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the gfxss_spi_csx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_gfxss_spi_csx[1];
/** Indicates that a pin map exists for gfxss_spi_dcx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_GFXSS_SPI_DCX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the gfxss_spi_dcx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_gfxss_spi_dcx[1];
/** Indicates that a pin map exists for gfxss_spi_dout*/
#define CYHAL_PIN_MAP_DRIVE_MODE_GFXSS_SPI_DOUT (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the gfxss_spi_dout signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_gfxss_spi_dout[1];
/** Indicates that a pin map exists for gfxss_spi_scl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_GFXSS_SPI_SCL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the gfxss_spi_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_gfxss_spi_scl[1];
/** Indicates that a pin map exists for i3c_i3c_scl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_I3C_I3C_SCL (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the i3c_i3c_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_i3c_i3c_scl[1];
/** Indicates that a pin map exists for i3c_i3c_sda*/
#define CYHAL_PIN_MAP_DRIVE_MODE_I3C_I3C_SDA (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the i3c_i3c_sda signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_i3c_i3c_sda[1];
/** Indicates that a pin map exists for lpcomp_inn_comp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LPCOMP_INN_COMP (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the lpcomp_inn_comp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inn_comp[2];
/** Indicates that a pin map exists for lpcomp_inp_comp*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LPCOMP_INP_COMP (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the lpcomp_inp_comp signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lpcomp_inp_comp[2];
/** Indicates that a pin map exists for m0seccpuss_clk_m0sec_swd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_M0SECCPUSS_CLK_M0SEC_SWD (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the m0seccpuss_clk_m0sec_swd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_m0seccpuss_clk_m0sec_swd[1];
/** Indicates that a pin map exists for m0seccpuss_m0sec_swd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_M0SECCPUSS_M0SEC_SWD (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the m0seccpuss_m0sec_swd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_m0seccpuss_m0sec_swd[1];
/** Indicates that a pin map exists for pass_sarmux_pads*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_SARMUX_PADS (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the pass_sarmux_pads signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sarmux_pads[7];
/** Indicates that a pin map exists for pdm_pdm_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PDM_PDM_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the pdm_pdm_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pdm_pdm_clk[5];
/** Indicates that a pin map exists for pdm_pdm_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PDM_PDM_DATA (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the pdm_pdm_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pdm_pdm_data[6];
/** Indicates that a pin map exists for peri_tr_io_input*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PERI_TR_IO_INPUT (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the peri_tr_io_input signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_input[8];
/** Indicates that a pin map exists for peri_tr_io_output*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PERI_TR_IO_OUTPUT (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the peri_tr_io_output signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_output[2];
/** Indicates that a pin map exists for scb_i2c_scl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SCL (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[8];
/** Indicates that a pin map exists for scb_i2c_sda*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SDA (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_sda signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[10];
/** Indicates that a pin map exists for scb_spi_m_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[8];
/** Indicates that a pin map exists for scb_spi_m_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MISO (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_m_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[11];
/** Indicates that a pin map exists for scb_spi_m_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MOSI (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[11];
/** Indicates that a pin map exists for scb_spi_m_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[10];
/** Indicates that a pin map exists for scb_spi_m_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select1[9];
/** Indicates that a pin map exists for scb_spi_s_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_CLK (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[8];
/** Indicates that a pin map exists for scb_spi_s_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MISO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_s_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[11];
/** Indicates that a pin map exists for scb_spi_s_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MOSI (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[11];
/** Indicates that a pin map exists for scb_spi_s_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0 (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[10];
/** Indicates that a pin map exists for scb_spi_s_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT1 (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select1[9];
/** Indicates that a pin map exists for scb_uart_cts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_CTS (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_cts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[10];
/** Indicates that a pin map exists for scb_uart_rts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RTS (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_rts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[9];
/** Indicates that a pin map exists for scb_uart_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RX (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[7];
/** Indicates that a pin map exists for scb_uart_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[9];
/** Indicates that a pin map exists for sdhc_card_cmd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_CMD (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the sdhc_card_cmd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_cmd[2];
/** Indicates that a pin map exists for sdhc_card_dat_3to0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_3TO0 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the sdhc_card_dat_3to0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_dat_3to0[8];
/** Indicates that a pin map exists for sdhc_card_dat_7to4*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_7TO4 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the sdhc_card_dat_7to4 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_dat_7to4[3];
/** Indicates that a pin map exists for sdhc_card_detect_n*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DETECT_N (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the sdhc_card_detect_n signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_detect_n[2];
/** Indicates that a pin map exists for sdhc_card_emmc_reset_n*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_EMMC_RESET_N (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the sdhc_card_emmc_reset_n signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_emmc_reset_n[1];
/** Indicates that a pin map exists for sdhc_card_if_pwr_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_IF_PWR_EN (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the sdhc_card_if_pwr_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_if_pwr_en[2];
/** Indicates that a pin map exists for sdhc_card_mech_write_prot*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_MECH_WRITE_PROT (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the sdhc_card_mech_write_prot signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_mech_write_prot[1];
/** Indicates that a pin map exists for sdhc_clk_card*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CLK_CARD (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the sdhc_clk_card signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_clk_card[2];
/** Indicates that a pin map exists for sdhc_io_volt_sel*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_IO_VOLT_SEL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the sdhc_io_volt_sel signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_io_volt_sel[2];
/** Indicates that a pin map exists for sdhc_led_ctrl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_LED_CTRL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the sdhc_led_ctrl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_led_ctrl[1];
/** Indicates that a pin map exists for smif_smif0_spi_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SMIF0_SPI_SELECT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_smif0_spi_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_smif0_spi_select0[1];
/** Indicates that a pin map exists for smif_smif0_spi_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SMIF0_SPI_SELECT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_smif0_spi_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_smif0_spi_select1[1];
/** Indicates that a pin map exists for smif_smif0_spi_select2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SMIF0_SPI_SELECT2 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_smif0_spi_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_smif0_spi_select2[1];
/** Indicates that a pin map exists for smif_smif0_spi_select3*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SMIF0_SPI_SELECT3 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_smif0_spi_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_smif0_spi_select3[1];
/** Indicates that a pin map exists for smif_smif1_spi_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SMIF1_SPI_SELECT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_smif1_spi_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_smif1_spi_select0[1];
/** Indicates that a pin map exists for smif_smif1_spi_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SMIF1_SPI_SELECT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_smif1_spi_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_smif1_spi_select1[1];
/** Indicates that a pin map exists for smif_smif1_spi_select2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SMIF1_SPI_SELECT2 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_smif1_spi_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_smif1_spi_select2[1];
/** Indicates that a pin map exists for smif_smif1_spi_select3*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SMIF1_SPI_SELECT3 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the smif_smif1_spi_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_smif1_spi_select3[1];
/** Indicates that a pin map exists for tcpwm_line*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_LINE (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_line signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[98];
/** Indicates that a pin map exists for tcpwm_line_compl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_LINE_COMPL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_line_compl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line_compl[94];
/** Indicates that a pin map exists for tdm_tdm_rx_fsync*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_FSYNC (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_rx_fsync signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_fsync[2];
/** Indicates that a pin map exists for tdm_tdm_rx_mck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_MCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_rx_mck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_mck[1];
/** Indicates that a pin map exists for tdm_tdm_rx_sck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_SCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_rx_sck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_sck[1];
/** Indicates that a pin map exists for tdm_tdm_rx_sd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_SD (CY_GPIO_EXT_DM_HIGHZ)
/** List of valid pin to peripheral connections for the tdm_tdm_rx_sd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_rx_sd[2];
/** Indicates that a pin map exists for tdm_tdm_tx_fsync*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_FSYNC (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_tx_fsync signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_fsync[2];
/** Indicates that a pin map exists for tdm_tdm_tx_mck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_MCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_tx_mck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_mck[2];
/** Indicates that a pin map exists for tdm_tdm_tx_sck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_SCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_tx_sck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_sck[2];
/** Indicates that a pin map exists for tdm_tdm_tx_sd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_SD (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tdm_tdm_tx_sd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tdm_tdm_tx_sd[2];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_pin_package */

#endif /* _CYHAL_EXPLORER_144_LQFP_H_ */


/* [] END OF FILE */
