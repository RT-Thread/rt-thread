/***************************************************************************//**
* \file cyhal_xmc7100_144_teqfp.h
*
* \brief
* XMC7100 device GPIO HAL header for 144-TEQFP package
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

#ifndef _CYHAL_XMC7100_144_TEQFP_H_
#define _CYHAL_XMC7100_144_TEQFP_H_

#include "cyhal_hw_resources.h"

/**
 * \addtogroup group_hal_impl_pin_package_xmc7100_144_teqfp XMC7100 144-TEQFP
 * \ingroup group_hal_impl_pin_package
 * \{
 * Pin definitions and connections specific to the XMC7100 144-TEQFP package.
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

/** Definitions for all of the pins that are bonded out on in the 144-TEQFP package for the XMC7100 series. */
typedef enum {
    NC = 0xFF, //!< No Connect/Invalid Pin

    P0_0 = CYHAL_GET_GPIO(CYHAL_PORT_0, 0), //!< Port 0 Pin 0
    P0_1 = CYHAL_GET_GPIO(CYHAL_PORT_0, 1), //!< Port 0 Pin 1
    P0_2 = CYHAL_GET_GPIO(CYHAL_PORT_0, 2), //!< Port 0 Pin 2
    P0_3 = CYHAL_GET_GPIO(CYHAL_PORT_0, 3), //!< Port 0 Pin 3

    P1_0 = CYHAL_GET_GPIO(CYHAL_PORT_1, 0), //!< Port 1 Pin 0
    P1_1 = CYHAL_GET_GPIO(CYHAL_PORT_1, 1), //!< Port 1 Pin 1

    P2_0 = CYHAL_GET_GPIO(CYHAL_PORT_2, 0), //!< Port 2 Pin 0
    P2_1 = CYHAL_GET_GPIO(CYHAL_PORT_2, 1), //!< Port 2 Pin 1
    P2_2 = CYHAL_GET_GPIO(CYHAL_PORT_2, 2), //!< Port 2 Pin 2
    P2_3 = CYHAL_GET_GPIO(CYHAL_PORT_2, 3), //!< Port 2 Pin 3
    P2_4 = CYHAL_GET_GPIO(CYHAL_PORT_2, 4), //!< Port 2 Pin 4

    P3_0 = CYHAL_GET_GPIO(CYHAL_PORT_3, 0), //!< Port 3 Pin 0
    P3_1 = CYHAL_GET_GPIO(CYHAL_PORT_3, 1), //!< Port 3 Pin 1
    P3_2 = CYHAL_GET_GPIO(CYHAL_PORT_3, 2), //!< Port 3 Pin 2
    P3_3 = CYHAL_GET_GPIO(CYHAL_PORT_3, 3), //!< Port 3 Pin 3
    P3_4 = CYHAL_GET_GPIO(CYHAL_PORT_3, 4), //!< Port 3 Pin 4

    P4_0 = CYHAL_GET_GPIO(CYHAL_PORT_4, 0), //!< Port 4 Pin 0
    P4_1 = CYHAL_GET_GPIO(CYHAL_PORT_4, 1), //!< Port 4 Pin 1

    P5_0 = CYHAL_GET_GPIO(CYHAL_PORT_5, 0), //!< Port 5 Pin 0
    P5_1 = CYHAL_GET_GPIO(CYHAL_PORT_5, 1), //!< Port 5 Pin 1
    P5_2 = CYHAL_GET_GPIO(CYHAL_PORT_5, 2), //!< Port 5 Pin 2
    P5_3 = CYHAL_GET_GPIO(CYHAL_PORT_5, 3), //!< Port 5 Pin 3
    P5_4 = CYHAL_GET_GPIO(CYHAL_PORT_5, 4), //!< Port 5 Pin 4

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
    P7_7 = CYHAL_GET_GPIO(CYHAL_PORT_7, 7), //!< Port 7 Pin 7

    P8_0 = CYHAL_GET_GPIO(CYHAL_PORT_8, 0), //!< Port 8 Pin 0
    P8_1 = CYHAL_GET_GPIO(CYHAL_PORT_8, 1), //!< Port 8 Pin 1
    P8_2 = CYHAL_GET_GPIO(CYHAL_PORT_8, 2), //!< Port 8 Pin 2
    P8_3 = CYHAL_GET_GPIO(CYHAL_PORT_8, 3), //!< Port 8 Pin 3

    P9_0 = CYHAL_GET_GPIO(CYHAL_PORT_9, 0), //!< Port 9 Pin 0
    P9_1 = CYHAL_GET_GPIO(CYHAL_PORT_9, 1), //!< Port 9 Pin 1

    P10_0 = CYHAL_GET_GPIO(CYHAL_PORT_10, 0), //!< Port 10 Pin 0
    P10_1 = CYHAL_GET_GPIO(CYHAL_PORT_10, 1), //!< Port 10 Pin 1
    P10_2 = CYHAL_GET_GPIO(CYHAL_PORT_10, 2), //!< Port 10 Pin 2
    P10_3 = CYHAL_GET_GPIO(CYHAL_PORT_10, 3), //!< Port 10 Pin 3
    P10_4 = CYHAL_GET_GPIO(CYHAL_PORT_10, 4), //!< Port 10 Pin 4

    P11_0 = CYHAL_GET_GPIO(CYHAL_PORT_11, 0), //!< Port 11 Pin 0
    P11_1 = CYHAL_GET_GPIO(CYHAL_PORT_11, 1), //!< Port 11 Pin 1
    P11_2 = CYHAL_GET_GPIO(CYHAL_PORT_11, 2), //!< Port 11 Pin 2

    P12_0 = CYHAL_GET_GPIO(CYHAL_PORT_12, 0), //!< Port 12 Pin 0
    P12_1 = CYHAL_GET_GPIO(CYHAL_PORT_12, 1), //!< Port 12 Pin 1
    P12_2 = CYHAL_GET_GPIO(CYHAL_PORT_12, 2), //!< Port 12 Pin 2
    P12_3 = CYHAL_GET_GPIO(CYHAL_PORT_12, 3), //!< Port 12 Pin 3
    P12_4 = CYHAL_GET_GPIO(CYHAL_PORT_12, 4), //!< Port 12 Pin 4
    P12_5 = CYHAL_GET_GPIO(CYHAL_PORT_12, 5), //!< Port 12 Pin 5

    P13_0 = CYHAL_GET_GPIO(CYHAL_PORT_13, 0), //!< Port 13 Pin 0
    P13_1 = CYHAL_GET_GPIO(CYHAL_PORT_13, 1), //!< Port 13 Pin 1
    P13_2 = CYHAL_GET_GPIO(CYHAL_PORT_13, 2), //!< Port 13 Pin 2
    P13_3 = CYHAL_GET_GPIO(CYHAL_PORT_13, 3), //!< Port 13 Pin 3
    P13_4 = CYHAL_GET_GPIO(CYHAL_PORT_13, 4), //!< Port 13 Pin 4
    P13_5 = CYHAL_GET_GPIO(CYHAL_PORT_13, 5), //!< Port 13 Pin 5
    P13_6 = CYHAL_GET_GPIO(CYHAL_PORT_13, 6), //!< Port 13 Pin 6
    P13_7 = CYHAL_GET_GPIO(CYHAL_PORT_13, 7), //!< Port 13 Pin 7

    P14_0 = CYHAL_GET_GPIO(CYHAL_PORT_14, 0), //!< Port 14 Pin 0
    P14_1 = CYHAL_GET_GPIO(CYHAL_PORT_14, 1), //!< Port 14 Pin 1
    P14_4 = CYHAL_GET_GPIO(CYHAL_PORT_14, 4), //!< Port 14 Pin 4
    P14_5 = CYHAL_GET_GPIO(CYHAL_PORT_14, 5), //!< Port 14 Pin 5

    P15_0 = CYHAL_GET_GPIO(CYHAL_PORT_15, 0), //!< Port 15 Pin 0
    P15_1 = CYHAL_GET_GPIO(CYHAL_PORT_15, 1), //!< Port 15 Pin 1
    P15_2 = CYHAL_GET_GPIO(CYHAL_PORT_15, 2), //!< Port 15 Pin 2
    P15_3 = CYHAL_GET_GPIO(CYHAL_PORT_15, 3), //!< Port 15 Pin 3

    P17_0 = CYHAL_GET_GPIO(CYHAL_PORT_17, 0), //!< Port 17 Pin 0
    P17_1 = CYHAL_GET_GPIO(CYHAL_PORT_17, 1), //!< Port 17 Pin 1
    P17_2 = CYHAL_GET_GPIO(CYHAL_PORT_17, 2), //!< Port 17 Pin 2
    P17_3 = CYHAL_GET_GPIO(CYHAL_PORT_17, 3), //!< Port 17 Pin 3
    P17_4 = CYHAL_GET_GPIO(CYHAL_PORT_17, 4), //!< Port 17 Pin 4

    P18_0 = CYHAL_GET_GPIO(CYHAL_PORT_18, 0), //!< Port 18 Pin 0
    P18_1 = CYHAL_GET_GPIO(CYHAL_PORT_18, 1), //!< Port 18 Pin 1
    P18_2 = CYHAL_GET_GPIO(CYHAL_PORT_18, 2), //!< Port 18 Pin 2
    P18_3 = CYHAL_GET_GPIO(CYHAL_PORT_18, 3), //!< Port 18 Pin 3
    P18_4 = CYHAL_GET_GPIO(CYHAL_PORT_18, 4), //!< Port 18 Pin 4
    P18_5 = CYHAL_GET_GPIO(CYHAL_PORT_18, 5), //!< Port 18 Pin 5
    P18_6 = CYHAL_GET_GPIO(CYHAL_PORT_18, 6), //!< Port 18 Pin 6
    P18_7 = CYHAL_GET_GPIO(CYHAL_PORT_18, 7), //!< Port 18 Pin 7

    P19_0 = CYHAL_GET_GPIO(CYHAL_PORT_19, 0), //!< Port 19 Pin 0
    P19_1 = CYHAL_GET_GPIO(CYHAL_PORT_19, 1), //!< Port 19 Pin 1
    P19_2 = CYHAL_GET_GPIO(CYHAL_PORT_19, 2), //!< Port 19 Pin 2
    P19_3 = CYHAL_GET_GPIO(CYHAL_PORT_19, 3), //!< Port 19 Pin 3
    P19_4 = CYHAL_GET_GPIO(CYHAL_PORT_19, 4), //!< Port 19 Pin 4

    P20_0 = CYHAL_GET_GPIO(CYHAL_PORT_20, 0), //!< Port 20 Pin 0
    P20_1 = CYHAL_GET_GPIO(CYHAL_PORT_20, 1), //!< Port 20 Pin 1
    P20_2 = CYHAL_GET_GPIO(CYHAL_PORT_20, 2), //!< Port 20 Pin 2
    P20_3 = CYHAL_GET_GPIO(CYHAL_PORT_20, 3), //!< Port 20 Pin 3

    P21_0 = CYHAL_GET_GPIO(CYHAL_PORT_21, 0), //!< Port 21 Pin 0
    P21_1 = CYHAL_GET_GPIO(CYHAL_PORT_21, 1), //!< Port 21 Pin 1
    P21_2 = CYHAL_GET_GPIO(CYHAL_PORT_21, 2), //!< Port 21 Pin 2
    P21_3 = CYHAL_GET_GPIO(CYHAL_PORT_21, 3), //!< Port 21 Pin 3
    P21_5 = CYHAL_GET_GPIO(CYHAL_PORT_21, 5), //!< Port 21 Pin 5
    P21_6 = CYHAL_GET_GPIO(CYHAL_PORT_21, 6), //!< Port 21 Pin 6

    P22_1 = CYHAL_GET_GPIO(CYHAL_PORT_22, 1), //!< Port 22 Pin 1
    P22_2 = CYHAL_GET_GPIO(CYHAL_PORT_22, 2), //!< Port 22 Pin 2
    P22_3 = CYHAL_GET_GPIO(CYHAL_PORT_22, 3), //!< Port 22 Pin 3
    P22_4 = CYHAL_GET_GPIO(CYHAL_PORT_22, 4), //!< Port 22 Pin 4
    P22_5 = CYHAL_GET_GPIO(CYHAL_PORT_22, 5), //!< Port 22 Pin 5
    P22_6 = CYHAL_GET_GPIO(CYHAL_PORT_22, 6), //!< Port 22 Pin 6

    P23_0 = CYHAL_GET_GPIO(CYHAL_PORT_23, 0), //!< Port 23 Pin 0
    P23_1 = CYHAL_GET_GPIO(CYHAL_PORT_23, 1), //!< Port 23 Pin 1
    P23_3 = CYHAL_GET_GPIO(CYHAL_PORT_23, 3), //!< Port 23 Pin 3
    P23_4 = CYHAL_GET_GPIO(CYHAL_PORT_23, 4), //!< Port 23 Pin 4
    P23_5 = CYHAL_GET_GPIO(CYHAL_PORT_23, 5), //!< Port 23 Pin 5
    P23_6 = CYHAL_GET_GPIO(CYHAL_PORT_23, 6), //!< Port 23 Pin 6
    P23_7 = CYHAL_GET_GPIO(CYHAL_PORT_23, 7), //!< Port 23 Pin 7
} cyhal_gpio_xmc7100_144_teqfp_t;

/** Create generic name for the series/package specific type. */
typedef cyhal_gpio_xmc7100_144_teqfp_t cyhal_gpio_t;

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
/** Indicates that a pin map exists for audioss_clk_i2s_if*/
#define CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_CLK_I2S_IF (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the audioss_clk_i2s_if signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_clk_i2s_if[3];
/** Indicates that a pin map exists for audioss_mclk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_MCLK (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the audioss_mclk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_mclk[3];
/** Indicates that a pin map exists for audioss_rx_sck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_RX_SCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the audioss_rx_sck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_rx_sck[3];
/** Indicates that a pin map exists for audioss_rx_sdi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_RX_SDI (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the audioss_rx_sdi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_rx_sdi[3];
/** Indicates that a pin map exists for audioss_rx_ws*/
#define CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_RX_WS (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the audioss_rx_ws signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_rx_ws[3];
/** Indicates that a pin map exists for audioss_tx_sck*/
#define CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_TX_SCK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the audioss_tx_sck signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_tx_sck[3];
/** Indicates that a pin map exists for audioss_tx_sdo*/
#define CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_TX_SDO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the audioss_tx_sdo signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_tx_sdo[3];
/** Indicates that a pin map exists for audioss_tx_ws*/
#define CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_TX_WS (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the audioss_tx_ws signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_audioss_tx_ws[3];
/** Indicates that a pin map exists for canfd_ttcan_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CANFD_TTCAN_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the canfd_ttcan_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_rx[14];
/** Indicates that a pin map exists for canfd_ttcan_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CANFD_TTCAN_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the canfd_ttcan_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_canfd_ttcan_tx[15];
/** Indicates that a pin map exists for cpuss_cal_sup_nz*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_CAL_SUP_NZ (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_cal_sup_nz signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_cal_sup_nz[2];
/** Indicates that a pin map exists for cpuss_clk_fm_pump*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_CLK_FM_PUMP (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_clk_fm_pump signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_clk_fm_pump[1];
/** Indicates that a pin map exists for cpuss_fault_out*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_FAULT_OUT (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_fault_out signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_fault_out[7];
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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_trace_clock[2];
/** Indicates that a pin map exists for cpuss_trace_data*/
#define CYHAL_PIN_MAP_DRIVE_MODE_CPUSS_TRACE_DATA (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the cpuss_trace_data signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_cpuss_trace_data[8];
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
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_REF_CLK (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the eth_ref_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_ref_clk[1];
/** Indicates that a pin map exists for eth_rx_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_RX_CLK (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the eth_rx_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rx_clk[1];
/** Indicates that a pin map exists for eth_rx_ctl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_RX_CTL (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the eth_rx_ctl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rx_ctl[1];
/** Indicates that a pin map exists for eth_rx_er*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_RX_ER (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the eth_rx_er signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rx_er[1];
/** Indicates that a pin map exists for eth_rxd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_RXD (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the eth_rxd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_rxd[4];
/** Indicates that a pin map exists for eth_tx_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_TX_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the eth_tx_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_tx_clk[1];
/** Indicates that a pin map exists for eth_tx_ctl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_TX_CTL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the eth_tx_ctl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_tx_ctl[1];
/** Indicates that a pin map exists for eth_tx_er*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_TX_ER (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the eth_tx_er signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_tx_er[1];
/** Indicates that a pin map exists for eth_txd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_ETH_TXD (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the eth_txd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_eth_txd[4];
/** Indicates that a pin map exists for lin_lin_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LIN_LIN_EN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the lin_lin_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_en[17];
/** Indicates that a pin map exists for lin_lin_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LIN_LIN_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the lin_lin_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_rx[28];
/** Indicates that a pin map exists for lin_lin_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_LIN_LIN_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the lin_lin_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_lin_lin_tx[27];
/** Indicates that a pin map exists for pass_sar_ext_mux_en*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_SAR_EXT_MUX_EN (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the pass_sar_ext_mux_en signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_mux_en[2];
/** Indicates that a pin map exists for pass_sar_ext_mux_sel*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_SAR_EXT_MUX_SEL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the pass_sar_ext_mux_sel signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sar_ext_mux_sel[8];
/** Indicates that a pin map exists for pass_sarmux_pads*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PASS_SARMUX_PADS (CY_GPIO_DM_ANALOG)
/** List of valid pin to peripheral connections for the pass_sarmux_pads signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_pass_sarmux_pads[52];
/** Indicates that a pin map exists for peri_tr_io_input*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PERI_TR_IO_INPUT (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the peri_tr_io_input signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_input[25];
/** Indicates that a pin map exists for peri_tr_io_output*/
#define CYHAL_PIN_MAP_DRIVE_MODE_PERI_TR_IO_OUTPUT (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the peri_tr_io_output signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_peri_tr_io_output[5];
/** Indicates that a pin map exists for scb_i2c_scl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SCL (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_scl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_scl[15];
/** Indicates that a pin map exists for scb_i2c_sda*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SDA (CY_GPIO_DM_OD_DRIVESLOW)
/** List of valid pin to peripheral connections for the scb_i2c_sda signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_i2c_sda[18];
/** Indicates that a pin map exists for scb_spi_m_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_CLK (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_clk[16];
/** Indicates that a pin map exists for scb_spi_m_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MISO (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_m_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_miso[19];
/** Indicates that a pin map exists for scb_spi_m_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MOSI (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_mosi[19];
/** Indicates that a pin map exists for scb_spi_m_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT0 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select0[17];
/** Indicates that a pin map exists for scb_spi_m_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT1 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select1[13];
/** Indicates that a pin map exists for scb_spi_m_select2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT2 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select2[11];
/** Indicates that a pin map exists for scb_spi_m_select3*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_SELECT3 (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_m_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_m_select3[5];
/** Indicates that a pin map exists for scb_spi_s_clk*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_CLK (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_clk signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_clk[16];
/** Indicates that a pin map exists for scb_spi_s_miso*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MISO (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_spi_s_miso signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_miso[19];
/** Indicates that a pin map exists for scb_spi_s_mosi*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MOSI (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_mosi signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_mosi[19];
/** Indicates that a pin map exists for scb_spi_s_select0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select0[17];
/** Indicates that a pin map exists for scb_spi_s_select1*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT1 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select1 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select1[13];
/** Indicates that a pin map exists for scb_spi_s_select2*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT2 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select2 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select2[11];
/** Indicates that a pin map exists for scb_spi_s_select3*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT3 (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_spi_s_select3 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_spi_s_select3[5];
/** Indicates that a pin map exists for scb_uart_cts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_CTS (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_cts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_cts[14];
/** Indicates that a pin map exists for scb_uart_rts*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RTS (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_rts signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rts[13];
/** Indicates that a pin map exists for scb_uart_rx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_RX (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the scb_uart_rx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_rx[16];
/** Indicates that a pin map exists for scb_uart_tx*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SCB_UART_TX (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the scb_uart_tx signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_scb_uart_tx[16];
/** Indicates that a pin map exists for sdhc_card_cmd*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_CMD (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the sdhc_card_cmd signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_cmd[1];
/** Indicates that a pin map exists for sdhc_card_dat_3to0*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_3TO0 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the sdhc_card_dat_3to0 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_dat_3to0[4];
/** Indicates that a pin map exists for sdhc_card_dat_7to4*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_7TO4 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the sdhc_card_dat_7to4 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_sdhc_card_dat_7to4[4];
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
/** Indicates that a pin map exists for smif_spi_data4*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_DATA4 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the smif_spi_data4 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data4[1];
/** Indicates that a pin map exists for smif_spi_data5*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_DATA5 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the smif_spi_data5 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data5[1];
/** Indicates that a pin map exists for smif_spi_data6*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_DATA6 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the smif_spi_data6 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data6[1];
/** Indicates that a pin map exists for smif_spi_data7*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_DATA7 (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the smif_spi_data7 signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_data7[1];
/** Indicates that a pin map exists for smif_spi_rwds*/
#define CYHAL_PIN_MAP_DRIVE_MODE_SMIF_SPI_RWDS (CY_GPIO_DM_STRONG)
/** List of valid pin to peripheral connections for the smif_spi_rwds signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_smif_spi_rwds[1];
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
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line[127];
/** Indicates that a pin map exists for tcpwm_line_compl*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_LINE_COMPL (CY_GPIO_DM_STRONG_IN_OFF)
/** List of valid pin to peripheral connections for the tcpwm_line_compl signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_line_compl[128];
/** Indicates that a pin map exists for tcpwm_tr_one_cnt_in*/
#define CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_ONE_CNT_IN (CY_GPIO_DM_HIGHZ)
/** List of valid pin to peripheral connections for the tcpwm_tr_one_cnt_in signal. */
extern const cyhal_resource_pin_mapping_t cyhal_pin_map_tcpwm_tr_one_cnt_in[255];

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_pin_package */

#endif /* _CYHAL_XMC7100_144_TEQFP_H_ */


/* [] END OF FILE */
