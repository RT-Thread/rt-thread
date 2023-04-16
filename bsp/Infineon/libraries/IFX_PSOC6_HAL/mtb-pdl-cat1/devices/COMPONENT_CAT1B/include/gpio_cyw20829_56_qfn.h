/***************************************************************************//**
* \file gpio_cyw20829_56_qfn.h
*
* \brief
* CYW20829 device GPIO header for 56-QFN package
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

#ifndef _GPIO_CYW20829_56_QFN_H_
#define _GPIO_CYW20829_56_QFN_H_

/* Package type */
enum
{
    CY_GPIO_PACKAGE_QFN,
    CY_GPIO_PACKAGE_BGA,
    CY_GPIO_PACKAGE_CSP,
    CY_GPIO_PACKAGE_WLCSP,
    CY_GPIO_PACKAGE_LQFP,
    CY_GPIO_PACKAGE_TQFP,
    CY_GPIO_PACKAGE_SMT,
};

#define CY_GPIO_PACKAGE_TYPE            CY_GPIO_PACKAGE_QFN
#define CY_GPIO_PIN_COUNT               56u

/* AMUXBUS Segments */
enum
{
    AMUXBUS_MAIN,
    AMUXBUS_TEST,
    AMUXBUS_VDDD,
};

/* AMUX Splitter Controls */
typedef enum
{
    AMUX_SPLIT_CTL_0                = 0x0000u   /* Left = AMUXBUS_TEST; Right = AMUXBUS_VDDD */
} cy_en_amux_split_t;

/* Port List */
/* PORT 0 (SLEW_EXT, DRIVE_EXT, SLEW_WIDTH, DRIVE_WIDTH) */
#define P0_0_PORT                       GPIO_PRT0
#define P0_0_PIN                        0u
#define P0_0_NUM                        0u
#define P0_1_PORT                       GPIO_PRT0
#define P0_1_PIN                        1u
#define P0_1_NUM                        1u
#define P0_2_PORT                       GPIO_PRT0
#define P0_2_PIN                        2u
#define P0_2_NUM                        2u
#define P0_3_PORT                       GPIO_PRT0
#define P0_3_PIN                        3u
#define P0_3_NUM                        3u
#define P0_4_PORT                       GPIO_PRT0
#define P0_4_PIN                        4u
#define P0_4_NUM                        4u
#define P0_5_PORT                       GPIO_PRT0
#define P0_5_PIN                        5u
#define P0_5_NUM                        5u

/* PORT 1 (SLEW_EXT, DRIVE_EXT, SLEW_WIDTH, DRIVE_WIDTH) */
#define P1_0_PORT                       GPIO_PRT1
#define P1_0_PIN                        0u
#define P1_0_NUM                        0u
#define P1_1_PORT                       GPIO_PRT1
#define P1_1_PIN                        1u
#define P1_1_NUM                        1u
#define P1_2_PORT                       GPIO_PRT1
#define P1_2_PIN                        2u
#define P1_2_NUM                        2u
#define P1_3_PORT                       GPIO_PRT1
#define P1_3_PIN                        3u
#define P1_3_NUM                        3u
#define P1_4_PORT                       GPIO_PRT1
#define P1_4_PIN                        4u
#define P1_4_NUM                        4u
#define P1_5_PORT                       GPIO_PRT1
#define P1_5_PIN                        5u
#define P1_5_NUM                        5u
#define P1_6_PORT                       GPIO_PRT1
#define P1_6_PIN                        6u
#define P1_6_NUM                        6u

/* PORT 2 (HSIO, SLEW_EXT, DRIVE_EXT, SLEW_WIDTH, DRIVE_WIDTH) */
#define P2_0_PORT                       GPIO_PRT2
#define P2_0_PIN                        0u
#define P2_0_NUM                        0u
#define P2_1_PORT                       GPIO_PRT2
#define P2_1_PIN                        1u
#define P2_1_NUM                        1u
#define P2_2_PORT                       GPIO_PRT2
#define P2_2_PIN                        2u
#define P2_2_NUM                        2u
#define P2_3_PORT                       GPIO_PRT2
#define P2_3_PIN                        3u
#define P2_3_NUM                        3u
#define P2_4_PORT                       GPIO_PRT2
#define P2_4_PIN                        4u
#define P2_4_NUM                        4u
#define P2_5_PORT                       GPIO_PRT2
#define P2_5_PIN                        5u
#define P2_5_NUM                        5u

/* PORT 3 (SLEW_EXT, DRIVE_EXT, SLEW_WIDTH, DRIVE_WIDTH) */
#define P3_0_PORT                       GPIO_PRT3
#define P3_0_PIN                        0u
#define P3_0_NUM                        0u
#define P3_1_PORT                       GPIO_PRT3
#define P3_1_PIN                        1u
#define P3_1_NUM                        1u
#define P3_2_PORT                       GPIO_PRT3
#define P3_2_PIN                        2u
#define P3_2_NUM                        2u
#define P3_3_PORT                       GPIO_PRT3
#define P3_3_PIN                        3u
#define P3_3_NUM                        3u
#define P3_4_PORT                       GPIO_PRT3
#define P3_4_PIN                        4u
#define P3_4_NUM                        4u
#define P3_5_PORT                       GPIO_PRT3
#define P3_5_PIN                        5u
#define P3_5_NUM                        5u
#define P3_6_PORT                       GPIO_PRT3
#define P3_6_PIN                        6u
#define P3_6_NUM                        6u
#define P3_7_PORT                       GPIO_PRT3
#define P3_7_PIN                        7u
#define P3_7_NUM                        7u

/* PORT 4 (GPIO_OVT, SLEW_EXT, DRIVE_EXT, SLEW_WIDTH, DRIVE_WIDTH) */
#define P4_0_PORT                       GPIO_PRT4
#define P4_0_PIN                        0u
#define P4_0_NUM                        0u
#define P4_0_AMUXSEGMENT                AMUXBUS_MAIN
#define P4_1_PORT                       GPIO_PRT4
#define P4_1_PIN                        1u
#define P4_1_NUM                        1u
#define P4_1_AMUXSEGMENT                AMUXBUS_MAIN

/* PORT 5 (SLEW_EXT, DRIVE_EXT, SLEW_WIDTH, DRIVE_WIDTH) */
#define P5_0_PORT                       GPIO_PRT5
#define P5_0_PIN                        0u
#define P5_0_NUM                        0u
#define P5_1_PORT                       GPIO_PRT5
#define P5_1_PIN                        1u
#define P5_1_NUM                        1u
#define P5_2_PORT                       GPIO_PRT5
#define P5_2_PIN                        2u
#define P5_2_NUM                        2u

/* Analog Connections */
#define ADCMIC_GPIO_ADC_IN0_PORT        3u
#define ADCMIC_GPIO_ADC_IN0_PIN         0u
#define ADCMIC_GPIO_ADC_IN1_PORT        3u
#define ADCMIC_GPIO_ADC_IN1_PIN         1u
#define ADCMIC_GPIO_ADC_IN2_PORT        3u
#define ADCMIC_GPIO_ADC_IN2_PIN         2u
#define ADCMIC_GPIO_ADC_IN3_PORT        3u
#define ADCMIC_GPIO_ADC_IN3_PIN         3u
#define ADCMIC_GPIO_ADC_IN4_PORT        3u
#define ADCMIC_GPIO_ADC_IN4_PIN         4u
#define ADCMIC_GPIO_ADC_IN5_PORT        3u
#define ADCMIC_GPIO_ADC_IN5_PIN         5u
#define ADCMIC_GPIO_ADC_IN6_PORT        3u
#define ADCMIC_GPIO_ADC_IN6_PIN         6u
#define ADCMIC_GPIO_ADC_IN7_PORT        3u
#define ADCMIC_GPIO_ADC_IN7_PIN         7u
#define IOSS_ADFT0_NET0_PORT            4u
#define IOSS_ADFT0_NET0_PIN             0u
#define IOSS_ADFT1_NET0_PORT            4u
#define IOSS_ADFT1_NET0_PIN             1u
#define SRSS_WCO_IN_PORT                5u
#define SRSS_WCO_IN_PIN                 0u
#define SRSS_WCO_OUT_PORT               5u
#define SRSS_WCO_OUT_PIN                1u

/* HSIOM Connections */
typedef enum
{
    /* Generic HSIOM connections */
    HSIOM_SEL_GPIO                  =  0,       /* GPIO controls 'out' */
    HSIOM_SEL_GPIO_DSI              =  1,       /* GPIO controls 'out', DSI controls 'output enable' */
    HSIOM_SEL_DSI_DSI               =  2,       /* DSI controls 'out' and 'output enable' */
    HSIOM_SEL_DSI_GPIO              =  3,       /* DSI controls 'out', GPIO controls 'output enable' */
    HSIOM_SEL_AMUXA                 =  4,       /* Analog mux bus A */
    HSIOM_SEL_AMUXB                 =  5,       /* Analog mux bus B */
    HSIOM_SEL_AMUXA_DSI             =  6,       /* Analog mux bus A, DSI control */
    HSIOM_SEL_AMUXB_DSI             =  7,       /* Analog mux bus B, DSI control */
    HSIOM_SEL_ACT_0                 =  8,       /* Active functionality 0 */
    HSIOM_SEL_ACT_1                 =  9,       /* Active functionality 1 */
    HSIOM_SEL_ACT_2                 = 10,       /* Active functionality 2 */
    HSIOM_SEL_ACT_3                 = 11,       /* Active functionality 3 */
    HSIOM_SEL_DS_0                  = 12,       /* DeepSleep functionality 0 */
    HSIOM_SEL_DS_1                  = 13,       /* DeepSleep functionality 1 */
    HSIOM_SEL_DS_2                  = 14,       /* DeepSleep functionality 2 */
    HSIOM_SEL_DS_3                  = 15,       /* DeepSleep functionality 3 */
    HSIOM_SEL_ACT_4                 = 16,       /* Active functionality 4 */
    HSIOM_SEL_ACT_5                 = 17,       /* Active functionality 5 */
    HSIOM_SEL_ACT_6                 = 18,       /* Active functionality 6 */
    HSIOM_SEL_ACT_7                 = 19,       /* Active functionality 7 */
    HSIOM_SEL_ACT_8                 = 20,       /* Active functionality 8 */
    HSIOM_SEL_ACT_9                 = 21,       /* Active functionality 9 */
    HSIOM_SEL_ACT_10                = 22,       /* Active functionality 10 */
    HSIOM_SEL_ACT_11                = 23,       /* Active functionality 11 */
    HSIOM_SEL_ACT_12                = 24,       /* Active functionality 12 */
    HSIOM_SEL_ACT_13                = 25,       /* Active functionality 13 */
    HSIOM_SEL_ACT_14                = 26,       /* Active functionality 14 */
    HSIOM_SEL_ACT_15                = 27,       /* Active functionality 15 */
    HSIOM_SEL_DS_4                  = 28,       /* DeepSleep functionality 4 */
    HSIOM_SEL_DS_5                  = 29,       /* DeepSleep functionality 5 */
    HSIOM_SEL_DS_6                  = 30,       /* DeepSleep functionality 6 */
    HSIOM_SEL_DS_7                  = 31,       /* DeepSleep functionality 7 */

    /* P0.0 */
    P0_0_GPIO                       =  0,       /* GPIO controls 'out' */
    P0_0_TCPWM0_LINE_COMPL0         =  8,       /* Digital Active - tcpwm[0].line_compl[0]:3 */
    P0_0_TCPWM0_LINE_COMPL262       =  9,       /* Digital Active - tcpwm[0].line_compl[262]:0 */
    P0_0_KEYSCAN_KS_COL3            = 14,       /* Digital Deep Sleep - keyscan.ks_col[3] */
    P0_0_PDM_PDM_CLK1               = 21,       /* Digital Active - pdm.pdm_clk[1]:0 */
    P0_0_TDM_TDM_RX_MCK0            = 24,       /* Digital Active - tdm.tdm_rx_mck[0]:0 */
    P0_0_BTSS_DEBUG12               = 26,       /* Digital Active - btss.debug[12] */
    P0_0_SCB0_SPI_SELECT1           = 30,       /* Digital Deep Sleep - scb[0].spi_select1:0 */

    /* P0.1 */
    P0_1_GPIO                       =  0,       /* GPIO controls 'out' */
    P0_1_TCPWM0_LINE1               =  8,       /* Digital Active - tcpwm[0].line[1]:3 */
    P0_1_TCPWM0_LINE256             =  9,       /* Digital Active - tcpwm[0].line[256]:1 */
    P0_1_KEYSCAN_KS_COL4            = 14,       /* Digital Deep Sleep - keyscan.ks_col[4] */
    P0_1_PDM_PDM_DATA1              = 21,       /* Digital Active - pdm.pdm_data[1]:0 */
    P0_1_TDM_TDM_RX_SCK0            = 24,       /* Digital Active - tdm.tdm_rx_sck[0]:0 */
    P0_1_BTSS_DEBUG13               = 26,       /* Digital Active - btss.debug[13] */
    P0_1_SCB0_SPI_SELECT2           = 30,       /* Digital Deep Sleep - scb[0].spi_select2:0 */

    /* P0.2 */
    P0_2_GPIO                       =  0,       /* GPIO controls 'out' */
    P0_2_TCPWM0_LINE_COMPL1         =  8,       /* Digital Active - tcpwm[0].line_compl[1]:3 */
    P0_2_TCPWM0_LINE_COMPL256       =  9,       /* Digital Active - tcpwm[0].line_compl[256]:1 */
    P0_2_KEYSCAN_KS_COL11           = 14,       /* Digital Deep Sleep - keyscan.ks_col[11] */
    P0_2_SCB0_I2C_SCL               = 15,       /* Digital Deep Sleep - scb[0].i2c_scl:0 */
    P0_2_PERI_TR_IO_INPUT4          = 22,       /* Digital Active - peri.tr_io_input[4]:0 */
    P0_2_TDM_TDM_RX_FSYNC0          = 24,       /* Digital Active - tdm.tdm_rx_fsync[0]:0 */
    P0_2_BTSS_DEBUG14               = 26,       /* Digital Active - btss.debug[14] */
    P0_2_SCB0_SPI_MOSI              = 30,       /* Digital Deep Sleep - scb[0].spi_mosi:0 */

    /* P0.3 */
    P0_3_GPIO                       =  0,       /* GPIO controls 'out' */
    P0_3_TCPWM0_LINE0               =  8,       /* Digital Active - tcpwm[0].line[0]:4 */
    P0_3_TCPWM0_LINE257             =  9,       /* Digital Active - tcpwm[0].line[257]:1 */
    P0_3_KEYSCAN_KS_COL12           = 14,       /* Digital Deep Sleep - keyscan.ks_col[12] */
    P0_3_SCB0_I2C_SDA               = 15,       /* Digital Deep Sleep - scb[0].i2c_sda:0 */
    P0_3_SCB1_SPI_SELECT3           = 20,       /* Digital Active - scb[1].spi_select3:0 */
    P0_3_PERI_TR_IO_INPUT5          = 22,       /* Digital Active - peri.tr_io_input[5]:0 */
    P0_3_TDM_TDM_RX_SD0             = 24,       /* Digital Active - tdm.tdm_rx_sd[0]:0 */
    P0_3_BTSS_DEBUG15               = 26,       /* Digital Active - btss.debug[15] */
    P0_3_SCB0_SPI_MISO              = 30,       /* Digital Deep Sleep - scb[0].spi_miso:0 */

    /* P0.4 */
    P0_4_GPIO                       =  0,       /* GPIO controls 'out' */
    P0_4_TCPWM0_LINE_COMPL0         =  8,       /* Digital Active - tcpwm[0].line_compl[0]:4 */
    P0_4_TCPWM0_LINE_COMPL257       =  9,       /* Digital Active - tcpwm[0].line_compl[257]:1 */
    P0_4_BTSS_GPIO5                 = 10,       /* Digital Active - btss.gpio[5]:0 */
    P0_4_BTSS_TXD_PYLD_MOD_TEST1    = 11,       /* Digital Active - btss.txd_pyld_mod_test[1] */
    P0_4_KEYSCAN_KS_ROW0            = 14,       /* Digital Deep Sleep - keyscan.ks_row[0] */
    P0_4_SRSS_EXT_CLK               = 16,       /* Digital Active - srss.ext_clk:0 */
    P0_4_CPUSS_TRACE_DATA3          = 17,       /* Digital Active - cpuss.trace_data[3]:1 */
    P0_4_SCB1_SPI_SELECT2           = 20,       /* Digital Active - scb[1].spi_select2:0 */
    P0_4_PERI_TR_IO_INPUT0          = 22,       /* Digital Active - peri.tr_io_input[0]:0 */
    P0_4_TDM_TDM_TX_MCK0            = 24,       /* Digital Active - tdm.tdm_tx_mck[0]:0 */
    P0_4_BTSS_DEBUG3                = 26,       /* Digital Active - btss.debug[3]:0 */
    P0_4_BTSS_SPI_CLK               = 27,       /* Digital Active - btss.spi_clk:0 */
    P0_4_SCB0_SPI_CLK               = 30,       /* Digital Deep Sleep - scb[0].spi_clk:0 */
    P0_4_IOSS_DDFT_PIN1             = 31,       /* Digital Deep Sleep - ioss.ddft_pin[1]:0 */

    /* P0.5 */
    P0_5_GPIO                       =  0,       /* GPIO controls 'out' */
    P0_5_TCPWM0_LINE1               =  8,       /* Digital Active - tcpwm[0].line[1]:4 */
    P0_5_TCPWM0_LINE258             =  9,       /* Digital Active - tcpwm[0].line[258]:1 */
    P0_5_BTSS_ANTENNA_SWITCH_CTRL0  = 10,       /* Digital Active - btss.antenna_switch_ctrl[0] */
    P0_5_BTSS_TX_ST_TEST            = 11,       /* Digital Active - btss.tx_st_test */
    P0_5_KEYSCAN_KS_ROW1            = 14,       /* Digital Deep Sleep - keyscan.ks_row[1] */
    P0_5_CPUSS_TRACE_DATA2          = 17,       /* Digital Active - cpuss.trace_data[2]:1 */
    P0_5_SCB1_SPI_SELECT1           = 20,       /* Digital Active - scb[1].spi_select1:0 */
    P0_5_PERI_TR_IO_INPUT1          = 22,       /* Digital Active - peri.tr_io_input[1]:0 */
    P0_5_TDM_TDM_TX_SCK0            = 24,       /* Digital Active - tdm.tdm_tx_sck[0]:0 */
    P0_5_BTSS_GCI_GPIO0             = 25,       /* Digital Active - btss.gci_gpio[0] */
    P0_5_BTSS_DEBUG4                = 26,       /* Digital Active - btss.debug[4] */
    P0_5_SMIF_SPIHB_SELECT1         = 27,       /* Digital Active - smif.spihb_select1 */

    /* P1.0 */
    P1_0_GPIO                       =  0,       /* GPIO controls 'out' */
    P1_0_TCPWM0_LINE_COMPL1         =  8,       /* Digital Active - tcpwm[0].line_compl[1]:4 */
    P1_0_TCPWM0_LINE_COMPL258       =  9,       /* Digital Active - tcpwm[0].line_compl[258]:1 */
    P1_0_BTSS_ANTENNA_SWITCH_CTRL1  = 10,       /* Digital Active - btss.antenna_switch_ctrl[1] */
    P1_0_BTSS_RPU_TDO               = 11,       /* Digital Active - btss.rpu_tdo */
    P1_0_KEYSCAN_KS_ROW5            = 14,       /* Digital Deep Sleep - keyscan.ks_row[5] */
    P1_0_CPUSS_TRACE_DATA1          = 17,       /* Digital Active - cpuss.trace_data[1]:1 */
    P1_0_SCB1_UART_CTS              = 18,       /* Digital Active - scb[1].uart_cts:0 */
    P1_0_SCB1_SPI_SELECT0           = 20,       /* Digital Active - scb[1].spi_select0:0 */
    P1_0_PERI_TR_IO_OUTPUT0         = 23,       /* Digital Active - peri.tr_io_output[0]:0 */
    P1_0_TDM_TDM_TX_FSYNC0          = 24,       /* Digital Active - tdm.tdm_tx_fsync[0]:0 */
    P1_0_BTSS_GCI_GPIO1             = 25,       /* Digital Active - btss.gci_gpio[1] */
    P1_0_BTSS_DEBUG5                = 26,       /* Digital Active - btss.debug[5] */
    P1_0_CPUSS_SWJ_SWO_TDO          = 29,       /* Digital Deep Sleep - cpuss.swj_swo_tdo */

    /* P1.1 */
    P1_1_GPIO                       =  0,       /* GPIO controls 'out' */
    P1_1_TCPWM0_LINE0               =  8,       /* Digital Active - tcpwm[0].line[0]:5 */
    P1_1_TCPWM0_LINE259             =  9,       /* Digital Active - tcpwm[0].line[259]:1 */
    P1_1_BTSS_ANTENNA_SWITCH_CTRL2  = 10,       /* Digital Active - btss.antenna_switch_ctrl[2] */
    P1_1_BTSS_RPU_TDI               = 11,       /* Digital Active - btss.rpu_tdi */
    P1_1_KEYSCAN_KS_ROW6            = 14,       /* Digital Deep Sleep - keyscan.ks_row[6] */
    P1_1_CPUSS_TRACE_DATA0          = 17,       /* Digital Active - cpuss.trace_data[0]:1 */
    P1_1_SCB1_UART_RTS              = 18,       /* Digital Active - scb[1].uart_rts:0 */
    P1_1_SCB1_SPI_CLK               = 20,       /* Digital Active - scb[1].spi_clk:0 */
    P1_1_PERI_TR_IO_OUTPUT1         = 23,       /* Digital Active - peri.tr_io_output[1]:0 */
    P1_1_TDM_TDM_TX_SD0             = 24,       /* Digital Active - tdm.tdm_tx_sd[0]:0 */
    P1_1_BTSS_GCI_GPIO2             = 25,       /* Digital Active - btss.gci_gpio[2]:0 */
    P1_1_BTSS_DEBUG6                = 26,       /* Digital Active - btss.debug[6] */
    P1_1_BTSS_UART_TXD              = 27,       /* Digital Active - btss.uart_txd:2 */
    P1_1_CPUSS_SWJ_SWDOE_TDI        = 29,       /* Digital Deep Sleep - cpuss.swj_swdoe_tdi */
    P1_1_IOSS_DDFT_PIN0             = 31,       /* Digital Deep Sleep - ioss.ddft_pin[0]:0 */

    /* P1.2 */
    P1_2_GPIO                       =  0,       /* GPIO controls 'out' */
    P1_2_TCPWM0_LINE_COMPL0         =  8,       /* Digital Active - tcpwm[0].line_compl[0]:5 */
    P1_2_TCPWM0_LINE_COMPL259       =  9,       /* Digital Active - tcpwm[0].line_compl[259]:1 */
    P1_2_BTSS_GPIO0                 = 10,       /* Digital Active - btss.gpio[0]:0 */
    P1_2_BTSS_RPU_SWD               = 11,       /* Digital Active - btss.rpu_swd */
    P1_2_KEYSCAN_KS_COL17           = 15,       /* Digital Deep Sleep - keyscan.ks_col[17]:0 */
    P1_2_CPUSS_TRACE_CLOCK          = 17,       /* Digital Active - cpuss.trace_clock:1 */
    P1_2_SCB1_UART_RX               = 18,       /* Digital Active - scb[1].uart_rx:0 */
    P1_2_SCB2_I2C_SCL               = 19,       /* Digital Active - scb[2].i2c_scl:1 */
    P1_2_SCB1_SPI_MOSI              = 20,       /* Digital Active - scb[1].spi_mosi:0 */
    P1_2_PERI_TR_IO_INPUT2          = 22,       /* Digital Active - peri.tr_io_input[2]:0 */
    P1_2_BTSS_GCI_GPIO3             = 25,       /* Digital Active - btss.gci_gpio[3] */
    P1_2_BTSS_DEBUG7                = 26,       /* Digital Active - btss.debug[7]:0 */
    P1_2_BTSS_SPI_MOSI              = 27,       /* Digital Active - btss.spi_mosi:1 */
    P1_2_CPUSS_SWJ_SWDIO_TMS        = 29,       /* Digital Deep Sleep - cpuss.swj_swdio_tms */

    /* P1.3 */
    P1_3_GPIO                       =  0,       /* GPIO controls 'out' */
    P1_3_TCPWM0_LINE1               =  8,       /* Digital Active - tcpwm[0].line[1]:5 */
    P1_3_TCPWM0_LINE260             =  9,       /* Digital Active - tcpwm[0].line[260]:1 */
    P1_3_BTSS_GPIO1                 = 10,       /* Digital Active - btss.gpio[1]:0 */
    P1_3_BTSS_RPU_TCK               = 11,       /* Digital Active - btss.rpu_tck */
    P1_3_KEYSCAN_KS_COL16           = 15,       /* Digital Deep Sleep - keyscan.ks_col[16]:0 */
    P1_3_SRSS_EXT_CLK               = 16,       /* Digital Active - srss.ext_clk:1 */
    P1_3_SCB1_UART_TX               = 18,       /* Digital Active - scb[1].uart_tx:0 */
    P1_3_SCB2_I2C_SDA               = 19,       /* Digital Active - scb[2].i2c_sda:1 */
    P1_3_SCB1_SPI_MISO              = 20,       /* Digital Active - scb[1].spi_miso:0 */
    P1_3_PERI_TR_IO_INPUT3          = 22,       /* Digital Active - peri.tr_io_input[3]:0 */
    P1_3_BTSS_GCI_GPIO4             = 25,       /* Digital Active - btss.gci_gpio[4] */
    P1_3_BTSS_DEBUG8                = 26,       /* Digital Active - btss.debug[8]:0 */
    P1_3_BTSS_SPI_CLK               = 27,       /* Digital Active - btss.spi_clk:1 */
    P1_3_CPUSS_CLK_SWJ_SWCLK_TCLK   = 29,       /* Digital Deep Sleep - cpuss.clk_swj_swclk_tclk */

    /* P1.4 */
    P1_4_GPIO                       =  0,       /* GPIO controls 'out' */
    P1_4_TCPWM0_LINE_COMPL1         =  8,       /* Digital Active - tcpwm[0].line_compl[1]:5 */
    P1_4_TCPWM0_LINE_COMPL260       =  9,       /* Digital Active - tcpwm[0].line_compl[260]:1 */
    P1_4_BTSS_GPIO5                 = 10,       /* Digital Active - btss.gpio[5]:1 */
    P1_4_KEYSCAN_KS_COL15           = 14,       /* Digital Deep Sleep - keyscan.ks_col[15] */
    P1_4_KEYSCAN_KS_COL16           = 15,       /* Digital Deep Sleep - keyscan.ks_col[16]:1 */
    P1_4_LIN0_LIN_EN1               = 23,       /* Digital Active - lin[0].lin_en[1]:0 */
    P1_4_BTSS_GCI_GPIO2             = 25,       /* Digital Active - btss.gci_gpio[2]:1 */
    P1_4_BTSS_DEBUG9                = 26,       /* Digital Active - btss.debug[9] */

    /* P1.5 */
    P1_5_GPIO                       =  0,       /* GPIO controls 'out' */
    P1_5_TCPWM0_LINE0               =  8,       /* Digital Active - tcpwm[0].line[0]:6 */
    P1_5_TCPWM0_LINE261             =  9,       /* Digital Active - tcpwm[0].line[261]:1 */
    P1_5_BTSS_GPIO6                 = 10,       /* Digital Active - btss.gpio[6] */
    P1_5_KEYSCAN_KS_COL5            = 14,       /* Digital Deep Sleep - keyscan.ks_col[5] */
    P1_5_LIN0_LIN_RX1               = 23,       /* Digital Active - lin[0].lin_rx[1]:0 */
    P1_5_BTSS_DEBUG10               = 26,       /* Digital Active - btss.debug[10] */

    /* P1.6 */
    P1_6_GPIO                       =  0,       /* GPIO controls 'out' */
    P1_6_TCPWM0_LINE_COMPL0         =  8,       /* Digital Active - tcpwm[0].line_compl[0]:6 */
    P1_6_TCPWM0_LINE_COMPL261       =  9,       /* Digital Active - tcpwm[0].line_compl[261]:1 */
    P1_6_BTSS_GPIO7                 = 10,       /* Digital Active - btss.gpio[7] */
    P1_6_KEYSCAN_KS_COL6            = 14,       /* Digital Deep Sleep - keyscan.ks_col[6] */
    P1_6_SRSS_CAL_WAVE              = 15,       /* Digital Deep Sleep - srss.cal_wave */
    P1_6_LIN0_LIN_TX1               = 23,       /* Digital Active - lin[0].lin_tx[1]:0 */
    P1_6_BTSS_DEBUG11               = 26,       /* Digital Active - btss.debug[11] */

    /* P2.0 */
    P2_0_GPIO                       =  0,       /* GPIO controls 'out' */
    P2_0_SMIF_SPIHB_SELECT0         = 27,       /* Digital Active - smif.spihb_select0 */

    /* P2.1 */
    P2_1_GPIO                       =  0,       /* GPIO controls 'out' */
    P2_1_SMIF_SPIHB_DATA3           = 27,       /* Digital Active - smif.spihb_data3 */

    /* P2.2 */
    P2_2_GPIO                       =  0,       /* GPIO controls 'out' */
    P2_2_SMIF_SPIHB_DATA2           = 27,       /* Digital Active - smif.spihb_data2 */

    /* P2.3 */
    P2_3_GPIO                       =  0,       /* GPIO controls 'out' */
    P2_3_SMIF_SPIHB_DATA1           = 27,       /* Digital Active - smif.spihb_data1 */

    /* P2.4 */
    P2_4_GPIO                       =  0,       /* GPIO controls 'out' */
    P2_4_SMIF_SPIHB_DATA0           = 27,       /* Digital Active - smif.spihb_data0 */

    /* P2.5 */
    P2_5_GPIO                       =  0,       /* GPIO controls 'out' */
    P2_5_SMIF_SPIHB_CLK             = 27,       /* Digital Active - smif.spihb_clk */

    /* P3.0 */
    P3_0_GPIO                       =  0,       /* GPIO controls 'out' */
    P3_0_TCPWM0_LINE0               =  8,       /* Digital Active - tcpwm[0].line[0]:0 */
    P3_0_TCPWM0_LINE256             =  9,       /* Digital Active - tcpwm[0].line[256]:0 */
    P3_0_KEYSCAN_KS_ROW7            = 14,       /* Digital Deep Sleep - keyscan.ks_row[7] */
    P3_0_CPUSS_TRACE_DATA3          = 17,       /* Digital Active - cpuss.trace_data[3]:0 */
    P3_0_SCB2_UART_CTS              = 18,       /* Digital Active - scb[2].uart_cts:0 */
    P3_0_SCB1_SPI_SELECT0           = 20,       /* Digital Active - scb[1].spi_select0:1 */
    P3_0_BTSS_UART_CTS              = 26,       /* Digital Active - btss.uart_cts:0 */

    /* P3.1 */
    P3_1_GPIO                       =  0,       /* GPIO controls 'out' */
    P3_1_TCPWM0_LINE_COMPL0         =  8,       /* Digital Active - tcpwm[0].line_compl[0]:0 */
    P3_1_TCPWM0_LINE_COMPL256       =  9,       /* Digital Active - tcpwm[0].line_compl[256]:0 */
    P3_1_BTSS_RPU_NTRST             = 11,       /* Digital Active - btss.rpu_ntrst */
    P3_1_KEYSCAN_KS_ROW4            = 14,       /* Digital Deep Sleep - keyscan.ks_row[4] */
    P3_1_CPUSS_TRACE_DATA2          = 17,       /* Digital Active - cpuss.trace_data[2]:0 */
    P3_1_SCB2_UART_RTS              = 18,       /* Digital Active - scb[2].uart_rts:0 */
    P3_1_SCB1_SPI_CLK               = 20,       /* Digital Active - scb[1].spi_clk:1 */
    P3_1_LIN0_LIN_EN0               = 23,       /* Digital Active - lin[0].lin_en[0]:0 */
    P3_1_BTSS_UART_RTS              = 26,       /* Digital Active - btss.uart_rts:0 */
    P3_1_BTSS_SYSCLK_RF             = 27,       /* Digital Active - btss.sysclk_rf */
    P3_1_CPUSS_RST_SWJ_TRSTN        = 29,       /* Digital Deep Sleep - cpuss.rst_swj_trstn */

    /* P3.2 */
    P3_2_GPIO                       =  0,       /* GPIO controls 'out' */
    P3_2_TCPWM0_LINE1               =  8,       /* Digital Active - tcpwm[0].line[1]:0 */
    P3_2_TCPWM0_LINE257             =  9,       /* Digital Active - tcpwm[0].line[257]:0 */
    P3_2_BTSS_TXD_SYMB_DATA_TEST0   = 11,       /* Digital Active - btss.txd_symb_data_test[0] */
    P3_2_KEYSCAN_KS_COL13           = 14,       /* Digital Deep Sleep - keyscan.ks_col[13] */
    P3_2_CPUSS_TRACE_DATA1          = 17,       /* Digital Active - cpuss.trace_data[1]:0 */
    P3_2_SCB2_UART_RX               = 18,       /* Digital Active - scb[2].uart_rx:0 */
    P3_2_SCB2_I2C_SCL               = 19,       /* Digital Active - scb[2].i2c_scl:0 */
    P3_2_SCB1_SPI_MOSI              = 20,       /* Digital Active - scb[1].spi_mosi:1 */
    P3_2_PDM_PDM_CLK0               = 21,       /* Digital Active - pdm.pdm_clk[0]:0 */
    P3_2_PERI_TR_IO_INPUT6          = 22,       /* Digital Active - peri.tr_io_input[6]:0 */
    P3_2_LIN0_LIN_RX0               = 23,       /* Digital Active - lin[0].lin_rx[0]:0 */
    P3_2_CANFD0_TTCAN_RX0           = 24,       /* Digital Active - canfd[0].ttcan_rx[0] */
    P3_2_ADCMIC_CLK_PDM             = 25,       /* Digital Active - adcmic.clk_pdm:0 */
    P3_2_BTSS_UART_RXD              = 27,       /* Digital Active - btss.uart_rxd:0 */
    P3_2_IOSS_DDFT_PIN1             = 31,       /* Digital Deep Sleep - ioss.ddft_pin[1]:1 */

    /* P3.3 */
    P3_3_GPIO                       =  0,       /* GPIO controls 'out' */
    P3_3_TCPWM0_LINE_COMPL1         =  8,       /* Digital Active - tcpwm[0].line_compl[1]:0 */
    P3_3_TCPWM0_LINE_COMPL257       =  9,       /* Digital Active - tcpwm[0].line_compl[257]:0 */
    P3_3_BTSS_TXD_SYMB_DATA_TEST1   = 11,       /* Digital Active - btss.txd_symb_data_test[1] */
    P3_3_KEYSCAN_KS_COL14           = 14,       /* Digital Deep Sleep - keyscan.ks_col[14] */
    P3_3_KEYSCAN_KS_COL17           = 15,       /* Digital Deep Sleep - keyscan.ks_col[17]:1 */
    P3_3_CPUSS_TRACE_DATA0          = 17,       /* Digital Active - cpuss.trace_data[0]:0 */
    P3_3_SCB2_UART_TX               = 18,       /* Digital Active - scb[2].uart_tx:0 */
    P3_3_SCB2_I2C_SDA               = 19,       /* Digital Active - scb[2].i2c_sda:0 */
    P3_3_SCB1_SPI_MISO              = 20,       /* Digital Active - scb[1].spi_miso:1 */
    P3_3_PDM_PDM_DATA0              = 21,       /* Digital Active - pdm.pdm_data[0]:0 */
    P3_3_PERI_TR_IO_INPUT7          = 22,       /* Digital Active - peri.tr_io_input[7]:0 */
    P3_3_LIN0_LIN_TX0               = 23,       /* Digital Active - lin[0].lin_tx[0]:0 */
    P3_3_CANFD0_TTCAN_TX0           = 24,       /* Digital Active - canfd[0].ttcan_tx[0] */
    P3_3_ADCMIC_PDM_DATA            = 25,       /* Digital Active - adcmic.pdm_data:0 */
    P3_3_BTSS_UART_TXD              = 27,       /* Digital Active - btss.uart_txd:0 */
    P3_3_IOSS_DDFT_PIN0             = 31,       /* Digital Deep Sleep - ioss.ddft_pin[0]:1 */

    /* P3.4 */
    P3_4_GPIO                       =  0,       /* GPIO controls 'out' */
    P3_4_TCPWM0_LINE0               =  8,       /* Digital Active - tcpwm[0].line[0]:1 */
    P3_4_TCPWM0_LINE258             =  9,       /* Digital Active - tcpwm[0].line[258]:0 */
    P3_4_BTSS_GPIO0                 = 10,       /* Digital Active - btss.gpio[0]:1 */
    P3_4_KEYSCAN_KS_COL7            = 14,       /* Digital Deep Sleep - keyscan.ks_col[7] */
    P3_4_CPUSS_TRACE_CLOCK          = 17,       /* Digital Active - cpuss.trace_clock:0 */
    P3_4_SCB1_SPI_SELECT3           = 20,       /* Digital Active - scb[1].spi_select3:1 */
    P3_4_BTSS_DEBUG3                = 26,       /* Digital Active - btss.debug[3]:1 */

    /* P3.5 */
    P3_5_GPIO                       =  0,       /* GPIO controls 'out' */
    P3_5_TCPWM0_LINE_COMPL0         =  8,       /* Digital Active - tcpwm[0].line_compl[0]:1 */
    P3_5_TCPWM0_LINE_COMPL258       =  9,       /* Digital Active - tcpwm[0].line_compl[258]:0 */
    P3_5_BTSS_GPIO1                 = 10,       /* Digital Active - btss.gpio[1]:1 */
    P3_5_KEYSCAN_KS_COL8            = 14,       /* Digital Deep Sleep - keyscan.ks_col[8] */
    P3_5_SCB1_SPI_SELECT2           = 20,       /* Digital Active - scb[1].spi_select2:1 */
    P3_5_BTSS_DEBUG1                = 26,       /* Digital Active - btss.debug[1]:1 */

    /* P3.6 */
    P3_6_GPIO                       =  0,       /* GPIO controls 'out' */
    P3_6_TCPWM0_LINE1               =  8,       /* Digital Active - tcpwm[0].line[1]:1 */
    P3_6_TCPWM0_LINE259             =  9,       /* Digital Active - tcpwm[0].line[259]:0 */
    P3_6_KEYSCAN_KS_COL9            = 14,       /* Digital Deep Sleep - keyscan.ks_col[9] */
    P3_6_SCB1_SPI_SELECT1           = 20,       /* Digital Active - scb[1].spi_select1:1 */
    P3_6_BTSS_DEBUG2                = 26,       /* Digital Active - btss.debug[2]:1 */

    /* P3.7 */
    P3_7_GPIO                       =  0,       /* GPIO controls 'out' */
    P3_7_TCPWM0_LINE_COMPL1         =  8,       /* Digital Active - tcpwm[0].line_compl[1]:1 */
    P3_7_TCPWM0_LINE_COMPL259       =  9,       /* Digital Active - tcpwm[0].line_compl[259]:0 */
    P3_7_BTSS_ANTENNA_SWITCH_CTRL3  = 10,       /* Digital Active - btss.antenna_switch_ctrl[3] */
    P3_7_KEYSCAN_KS_COL10           = 14,       /* Digital Deep Sleep - keyscan.ks_col[10] */
    P3_7_BTSS_DEBUG7                = 26,       /* Digital Active - btss.debug[7]:1 */

    /* P4.0 */
    P4_0_GPIO                       =  0,       /* GPIO controls 'out' */
    P4_0_TCPWM0_LINE_COMPL1         =  8,       /* Digital Active - tcpwm[0].line_compl[1]:2 */
    P4_0_TCPWM0_LINE_COMPL261       =  9,       /* Digital Active - tcpwm[0].line_compl[261]:0 */
    P4_0_BTSS_GPIO2                 = 10,       /* Digital Active - btss.gpio[2] */
    P4_0_BTSS_TXD_SYMB_STRB_TEST    = 11,       /* Digital Active - btss.txd_symb_strb_test */
    P4_0_KEYSCAN_KS_ROW2            = 14,       /* Digital Deep Sleep - keyscan.ks_row[2] */
    P4_0_SCB0_I2C_SCL               = 15,       /* Digital Deep Sleep - scb[0].i2c_scl:1 */
    P4_0_SCB2_UART_CTS              = 18,       /* Digital Active - scb[2].uart_cts:2 */
    P4_0_BTSS_DEBUG1                = 26,       /* Digital Active - btss.debug[1]:0 */
    P4_0_BTSS_UART_TXD              = 27,       /* Digital Active - btss.uart_txd:1 */
    P4_0_SCB0_SPI_MOSI              = 30,       /* Digital Deep Sleep - scb[0].spi_mosi:1 */

    /* P4.1 */
    P4_1_GPIO                       =  0,       /* GPIO controls 'out' */
    P4_1_TCPWM0_LINE0               =  8,       /* Digital Active - tcpwm[0].line[0]:3 */
    P4_1_TCPWM0_LINE262             =  9,       /* Digital Active - tcpwm[0].line[262]:0 */
    P4_1_BTSS_GPIO4                 = 10,       /* Digital Active - btss.gpio[4]:1 */
    P4_1_BTSS_TXD_PYLD_MOD_TEST0    = 11,       /* Digital Active - btss.txd_pyld_mod_test[0] */
    P4_1_KEYSCAN_KS_ROW3            = 14,       /* Digital Deep Sleep - keyscan.ks_row[3] */
    P4_1_SCB0_I2C_SDA               = 15,       /* Digital Deep Sleep - scb[0].i2c_sda:1 */
    P4_1_BTSS_DEBUG2                = 26,       /* Digital Active - btss.debug[2]:0 */
    P4_1_BTSS_SPI_MOSI              = 27,       /* Digital Active - btss.spi_mosi:0 */
    P4_1_SCB0_SPI_MISO              = 30,       /* Digital Deep Sleep - scb[0].spi_miso:1 */

    /* P5.0 */
    P5_0_GPIO                       =  0,       /* GPIO controls 'out' */
    P5_0_TCPWM0_LINE0               =  8,       /* Digital Active - tcpwm[0].line[0]:2 */
    P5_0_TCPWM0_LINE260             =  9,       /* Digital Active - tcpwm[0].line[260]:0 */
    P5_0_BTSS_TXD_SYMB_DATA_TEST2   = 11,       /* Digital Active - btss.txd_symb_data_test[2] */
    P5_0_KEYSCAN_KS_COL0            = 14,       /* Digital Deep Sleep - keyscan.ks_col[0] */
    P5_0_SCB2_UART_CTS              = 18,       /* Digital Active - scb[2].uart_cts:1 */
    P5_0_SCB1_SPI_SELECT0           = 20,       /* Digital Active - scb[1].spi_select0:2 */
    P5_0_PDM_PDM_CLK0               = 21,       /* Digital Active - pdm.pdm_clk[0]:1 */
    P5_0_ADCMIC_CLK_PDM             = 25,       /* Digital Active - adcmic.clk_pdm:1 */
    P5_0_BTSS_UART_CTS              = 26,       /* Digital Active - btss.uart_cts:1 */

    /* P5.1 */
    P5_1_GPIO                       =  0,       /* GPIO controls 'out' */
    P5_1_TCPWM0_LINE_COMPL0         =  8,       /* Digital Active - tcpwm[0].line_compl[0]:2 */
    P5_1_TCPWM0_LINE_COMPL260       =  9,       /* Digital Active - tcpwm[0].line_compl[260]:0 */
    P5_1_BTSS_GPIO3                 = 10,       /* Digital Active - btss.gpio[3] */
    P5_1_BTSS_TXD_SYMB_DATA_TEST3   = 11,       /* Digital Active - btss.txd_symb_data_test[3] */
    P5_1_KEYSCAN_KS_COL1            = 14,       /* Digital Deep Sleep - keyscan.ks_col[1] */
    P5_1_PDM_PDM_DATA0              = 21,       /* Digital Active - pdm.pdm_data[0]:1 */
    P5_1_ADCMIC_PDM_DATA            = 25,       /* Digital Active - adcmic.pdm_data:1 */
    P5_1_BTSS_DEBUG0                = 26,       /* Digital Active - btss.debug[0] */
    P5_1_BTSS_UART_RXD              = 27,       /* Digital Active - btss.uart_rxd:1 */
    P5_1_SCB0_SPI_SELECT0           = 30,       /* Digital Deep Sleep - scb[0].spi_select0:0 */

    /* P5.2 */
    P5_2_GPIO                       =  0,       /* GPIO controls 'out' */
    P5_2_TCPWM0_LINE1               =  8,       /* Digital Active - tcpwm[0].line[1]:2 */
    P5_2_TCPWM0_LINE261             =  9,       /* Digital Active - tcpwm[0].line[261]:0 */
    P5_2_BTSS_GPIO4                 = 10,       /* Digital Active - btss.gpio[4]:0 */
    P5_2_KEYSCAN_KS_COL2            = 14,       /* Digital Deep Sleep - keyscan.ks_col[2] */
    P5_2_BTSS_DEBUG8                = 26        /* Digital Active - btss.debug[8]:1 */
} en_hsiom_sel_t;

#endif /* _GPIO_CYW20829_56_QFN_H_ */


/* [] END OF FILE */
