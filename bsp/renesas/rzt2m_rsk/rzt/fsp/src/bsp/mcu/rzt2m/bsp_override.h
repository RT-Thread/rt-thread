/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RZT2M
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RZT2M) */

#ifndef BSP_OVERRIDE_H
#define BSP_OVERRIDE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/* BSP Common Includes. */
#include "../../src/bsp/mcu/all/bsp_common.h"

/* BSP MPU Specific Includes. */
#include "../../src/bsp/mcu/all/bsp_register_protection.h"
#include "../../src/bsp/mcu/all/bsp_irq.h"
#include "../../src/bsp/mcu/all/bsp_io.h"
#include "../../src/bsp/mcu/all/bsp_clocks.h"
#include "../../src/bsp/mcu/all/bsp_module_stop.h"
#include "../../src/bsp/mcu/all/bsp_semaphore.h"
#include "../../src/bsp/mcu/all/bsp_reset.h"
#include "../../src/bsp/mcu/all/bsp_cache.h"

/* Factory MPU information. */
#include "../../inc/fsp_features.h"

/* BSP Common Includes (Other than bsp_common.h) */
#include "../../src/bsp/mcu/all/bsp_delay.h"
#include "../../src/bsp/mcu/all/bsp_mcu_api.h"

/* BSP TFU Includes. */
#if BSP_FEATURE_TFU_SUPPORTED
 #include "../../src/bsp/mcu/all/bsp_tfu.h"
#endif

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Define overrides required for this MPU. */
#define BSP_OVERRIDE_ADC_MODE_T
#define BSP_OVERRIDE_ADC_CHANNEL_T
#define BSP_OVERRIDE_CGC_CLOCK_T
#define BSP_OVERRIDE_CGC_PLL_CFG_T
#define BSP_OVERRIDE_CGC_DIVIDER_CFG_T
#define BSP_OVERRIDE_CGC_CLOCK_CHANGE_T
#define BSP_OVERRIDE_CGC_CLOCKS_CFG_T
#define BSP_OVERRIDE_ELC_PERIPHERAL_T
#define BSP_OVERRIDE_ETHER_EVENT_T
#define BSP_OVERRIDE_ETHER_CALLBACK_ARGS_T
#define BSP_OVERRIDE_ETHER_PHY_LSI_TYPE_T
#define BSP_OVERRIDE_ETHER_SWITCH_CALLBACK_ARGS_T
#define BSP_OVERRIDE_POE3_STATE_T
#define BSP_OVERRIDE_POEG_STATE_T
#define BSP_OVERRIDE_POEG_TRIGGER_T
#define BSP_OVERRIDE_TRANSFER_MODE_T
#define BSP_OVERRIDE_TRANSFER_SIZE_T
#define BSP_OVERRIDE_TRANSFER_ADDR_MODE_T
#define BSP_OVERRIDE_TRANSFER_CALLBACK_ARGS_T
#define BSP_OVERRIDE_TRANSFER_INFO_T

/* Override definitions. */

#define ELC_PERIPHERAL_NUM     (55U)

/* Private definition to set enumeration values. */
#define IOPORT_P_OFFSET        (0U)
#define IOPORT_PM_OFFSET       (1U)
#define IOPORT_PMC_OFFSET      (3U)
#define IOPORT_PFC_OFFSET      (4U)
#define IOPORT_DRCTL_OFFSET    (8U)
#define IOPORT_RSELP_OFFSET    (14U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/*==============================================
 * ADC API Overrides
 *==============================================*/

/** ADC operation mode definitions  */
typedef enum e_adc_mode
{
    ADC_MODE_SINGLE_SCAN      = 0,     ///< Single scan - one or more channels
    ADC_MODE_GROUP_SCAN       = 1,     ///< Two trigger sources to trigger scan for two groups which contain one or more channels
    ADC_MODE_CONTINUOUS_SCAN  = 2,     ///< Continuous scan - one or more channels
    ADC_MODE_SYNCHRONIZE_SCAN = 3,     ///< Channel synchronization control mode
    ADC_MODE_INDIVIDUAL_SCAN  = 4,     ///< Channel individual control mode
} adc_mode_t;

/** ADC channels */
typedef enum e_adc_channel
{
    ADC_CHANNEL_0                 = 0,     ///< ADC channel 0
    ADC_CHANNEL_1                 = 1,     ///< ADC channel 1
    ADC_CHANNEL_2                 = 2,     ///< ADC channel 2
    ADC_CHANNEL_3                 = 3,     ///< ADC channel 3
    ADC_CHANNEL_4                 = 4,     ///< ADC channel 4
    ADC_CHANNEL_5                 = 5,     ///< ADC channel 5
    ADC_CHANNEL_6                 = 6,     ///< ADC channel 6
    ADC_CHANNEL_7                 = 7,     ///< ADC channel 7
    ADC_CHANNEL_8                 = 8,     ///< ADC channel 8
    ADC_CHANNEL_9                 = 9,     ///< ADC channel 9
    ADC_CHANNEL_10                = 10,    ///< ADC channel 10
    ADC_CHANNEL_11                = 11,    ///< ADC channel 11
    ADC_CHANNEL_12                = 12,    ///< ADC channel 12
    ADC_CHANNEL_13                = 13,    ///< ADC channel 13
    ADC_CHANNEL_14                = 14,    ///< ADC channel 14
    ADC_CHANNEL_15                = 15,    ///< ADC channel 15
    ADC_CHANNEL_16                = 16,    ///< ADC channel 16
    ADC_CHANNEL_17                = 17,    ///< ADC channel 17
    ADC_CHANNEL_18                = 18,    ///< ADC channel 18
    ADC_CHANNEL_19                = 19,    ///< ADC channel 19
    ADC_CHANNEL_20                = 20,    ///< ADC channel 20
    ADC_CHANNEL_21                = 21,    ///< ADC channel 21
    ADC_CHANNEL_22                = 22,    ///< ADC channel 22
    ADC_CHANNEL_23                = 23,    ///< ADC channel 23
    ADC_CHANNEL_24                = 24,    ///< ADC channel 24
    ADC_CHANNEL_25                = 25,    ///< ADC channel 25
    ADC_CHANNEL_26                = 26,    ///< ADC channel 26
    ADC_CHANNEL_27                = 27,    ///< ADC channel 27
    ADC_CHANNEL_28                = 28,    ///< ADC channel 28
    ADC_CHANNEL_DUPLEX_A          = 50,    ///< Data duplexing register A
    ADC_CHANNEL_DUPLEX_B          = 51,    ///< Data duplexing register B
    ADC_CHANNEL_DUPLEX            = -4,    ///< Data duplexing register
    ADC_CHANNEL_TEMPERATURE       = -3,    ///< Temperature sensor output
    ADC_CHANNEL_VOLT              = -2,    ///< Internal reference voltage
    ADC_CHANNEL_0_DSMIF_CAPTURE_A = 0x100, ///< ADC channel 0 Capture Current Data Register A
    ADC_CHANNEL_0_DSMIF_CAPTURE_B = 0x200, ///< ADC channel 0 Capture Current Data Register B
    ADC_CHANNEL_1_DSMIF_CAPTURE_A = 0x101, ///< ADC channel 1 Capture Current Data Register A
    ADC_CHANNEL_1_DSMIF_CAPTURE_B = 0x201, ///< ADC channel 1 Capture Current Data Register B
    ADC_CHANNEL_2_DSMIF_CAPTURE_A = 0x102, ///< ADC channel 2 Capture Current Data Register A
    ADC_CHANNEL_2_DSMIF_CAPTURE_B = 0x202, ///< ADC channel 2 Capture Current Data Register B
} adc_channel_t;

/*==============================================
 * CGC API Overrides
 *==============================================*/

/** Divider values of clock provided to xSPI */
typedef enum e_cgc_fsel_xspi_clock_div
{
    CGC_FSEL_XSPI_CLOCK_DIV_6  = 0x02, ///< XSPI_CLKn 133.3MHz (XSPI base clock divided by 3)
    CGC_FSEL_XSPI_CLOCK_DIV_8  = 0x03, ///< XSPI_CLKn 100.0MHz / 75.0MHz (XSPI base clock divided by 3 / divided by 4)
    CGC_FSEL_XSPI_CLOCK_DIV_16 = 0x04, ///< XSPI_CLKn 50.0MHz / 37.5MHz (XSPI base clock divided by 3 / divided by 4)
    CGC_FSEL_XSPI_CLOCK_DIV_32 = 0x05, ///< XSPI_CLKn 25.0MHz (XSPI base clock divided by 3)
    CGC_FSEL_XSPI_CLOCK_DIV_64 = 0x06, ///< XSPI_CLKn 12.5MHz (XSPI base clock divided by 3)
} cgc_fsel_xspi_clock_div_t;

/** Divider values of base clock generated for xSPI */
typedef enum e_cgc_divsel_xspi_clock_div
{
    CGC_DIVSEL_XSPI_CLOCK_DIV_3 = 0x00, ///< XSPI base clock divided by 3
    CGC_DIVSEL_XSPI_CLOCK_DIV_4 = 0x01, ///< XSPI base clock divided by 4
} cgc_divsel_xspi_clock_div_t;

/** Clock output divider values */
typedef enum e_cgc_clock_out_clock_div
{
    CGC_CLOCK_OUT_CLOCK_DIV_2 = 0,     ///< CKIO 100.0MHz / 75.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_3 = 1,     ///< CKIO 66.7MHz / 50.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_4 = 2,     ///< CKIO 50.0MHz / 37.5MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_5 = 3,     ///< CKIO 40.0MHz / 30.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_6 = 4,     ///< CKIO 33.3MHz / 25.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_7 = 5,     ///< CKIO 28.6MHz / 21.4MHz (Base clock divided by 3 / divided by 4)
    CGC_CLOCK_OUT_CLOCK_DIV_8 = 6,     ///< CKIO 25.0MHz / 18.75MHz (Base clock divided by 3 / divided by 4)
} cgc_clock_out_clock_div_t;

/** CANFD clock divider values */
typedef enum e_cgc_canfd_clock_div
{
    CGC_CANFD_CLOCK_DIV_10 = 0,        ///< CANFD clock 80.0MHz
    CGC_CANFD_CLOCK_DIV_20 = 1,        ///< CANFD clock 40.0MHz
} cgc_canfd_clock_div_t;

/** PHY clock source identifiers */
typedef enum e_cgc_phy_clock
{
    CGC_PHY_CLOCK_PLL1     = 0,        ///< PLL1 divider clock
    CGC_PHY_CLOCK_MAIN_OSC = 1,        ///< Main clock oscillator
} cgc_phy_clock_t;

/** SPI asynchronous serial clock frequency */
typedef enum e_cgc_spi_async_clock
{
    CGC_SPI_ASYNC_CLOCK_75MHZ = 0,     ///< SPI asynchronous serial clock 75MHz
    CGC_SPI_ASYNC_CLOCK_96MHZ = 1,     ///< SPI asynchronous serial clock 96MHz
} cgc_spi_async_clock_t;

/** SCI asynchronous serial clock frequency */
typedef enum e_cgc_sci_async_clock
{
    CGC_SCI_ASYNC_CLOCK_75MHZ = 0,     ///< SCI asynchronous serial clock 75MHz
    CGC_SCI_ASYNC_CLOCK_96MHZ = 1,     ///< SCI asynchronous serial clock 96MHz
} cgc_sci_async_clock_t;

/** CPU clock divider values */
typedef enum e_cgc_cpu_clock_div
{
    CGC_CPU_CLOCK_DIV_1 = 0,           ///< CPU 800.0MHz / 600.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CPU_CLOCK_DIV_2 = 1,           ///< CPU 400.0MHz / 300.0MHz (Base clock divided by 3 / divided by 4)
    CGC_CPU_CLOCK_DIV_4 = 2,           ///< CPU 200.0MHz / 150.0MHz (Base clock divided by 3 / divided by 4)
} cgc_cpu_clock_div_t;

/** Base clock divider values */
typedef enum e_cgc_baseclock_div
{
    CGC_BASECLOCK_DIV_3 = 0,           ///< Base clock divided by 3 (ICLK=200.0MHz etc.)
    CGC_BASECLOCK_DIV_4 = 1,           ///< Base clock divided by 4 (ICLK=150.0MHz etc.)
} cgc_baseclock_div_t;

/** System clock source identifiers */
typedef enum e_cgc_clock
{
    CGC_CLOCK_LOCO = 0,                ///< The low speed on chip oscillator
    CGC_CLOCK_PLL0 = 1,                ///< The PLL0 oscillator
    CGC_CLOCK_PLL1 = 2,                ///< The PLL1 oscillator
} cgc_clock_t;

/** Clock configuration structure - Dummy definition because it is not used in this MPU.
 * Set NULL as an input parameter to the @ref cgc_api_t::clockStart function for the PLL clock. */
typedef struct st_cgc_pll_cfg
{
    uint32_t dummy;                    /* Dummy. */
} cgc_pll_cfg_t;

/** Clock configuration structure */
typedef struct st_cgc_divider_cfg
{
    union
    {
        uint32_t sckcr_w;                                ///< System Clock Control Register

        struct
        {
            cgc_fsel_xspi_clock_div_t fselxspi0     : 3; ///< Divider value for XSPI_CLK0
            uint32_t                                : 3;
            cgc_divsel_xspi_clock_div_t divselxspi0 : 1; ///< Divider base value for XSPI_CLK0
            uint32_t                                : 1;
            cgc_fsel_xspi_clock_div_t fselxspi1     : 3; ///< Divider value for XSPI_CLK1
            uint32_t                                : 3;
            cgc_divsel_xspi_clock_div_t divselxspi1 : 1; ///< Divider base value for XSPI_CLK1
            uint32_t                                : 1;
            cgc_clock_out_clock_div_t ckio_div      : 3; ///< Divider value for CKIO
            uint32_t                                : 1;
            cgc_canfd_clock_div_t fselcanfd_div     : 1; ///< Divider value for CANFD clock
            cgc_phy_clock_t       phy_sel           : 1; ///< Ethernet PHY reference clock output
            uint32_t                                : 2;
            cgc_spi_async_clock_t spi0_async_sel    : 1; ///< SPI0 asynchronous serial clock
            cgc_spi_async_clock_t spi1_async_sel    : 1; ///< SPI1 asynchronous serial clock
            cgc_spi_async_clock_t spi2_async_sel    : 1; ///< SPI2 asynchronous serial clock
            cgc_sci_async_clock_t sci0_async_sel    : 1; ///< SCI0 asynchronous serial clock
            cgc_sci_async_clock_t sci1_async_sel    : 1; ///< SCI1 asynchronous serial clock
            cgc_sci_async_clock_t sci2_async_sel    : 1; ///< SCI2 asynchronous serial clock
            cgc_sci_async_clock_t sci3_async_sel    : 1; ///< SCI3 asynchronous serial clock
            cgc_sci_async_clock_t sci4_async_sel    : 1; ///< SCI4 asynchronous serial clock
        } sckcr_b;
    };

    union
    {
        uint32_t sckcr2_w;                            ///< System Clock Control Register 2

        struct
        {
            cgc_cpu_clock_div_t fsel0cr52        : 2; ///< Divider value for Cortex-R52 CPU0
            cgc_cpu_clock_div_t fsel1cr52        : 2; ///< Divider value for Cortex-R52 CPU1
            uint32_t                             : 1;
            cgc_baseclock_div_t div_sub_sel      : 1; ///< Divider value for base clock
            uint32_t                             : 18;
            cgc_spi_async_clock_t spi3_async_sel : 1; ///< SPI3 asynchronous serial clock
            cgc_sci_async_clock_t sci5_async_sel : 1; ///< SCI5 asynchronous serial clock
            uint32_t                             : 6;
        } sckcr2_b;
    };
} cgc_divider_cfg_t;

/** Clock options */
typedef enum e_cgc_clock_change
{
    CGC_CLOCK_CHANGE_START = 0,        ///< Start the clock
    CGC_CLOCK_CHANGE_STOP  = 1,        ///< Stop the clock
    CGC_CLOCK_CHANGE_NONE  = 2,        ///< No change to the clock
} cgc_clock_change_t;

/** Clock configuration */
typedef struct st_cgc_clocks_cfg
{
    cgc_divider_cfg_t  divider_cfg;    ///< Clock dividers structure
    cgc_clock_change_t loco_state;     ///< State of LOCO
    cgc_clock_change_t pll1_state;     ///< State of PLL1
} cgc_clocks_cfg_t;

/*==============================================
 * ELC API Overrides
 *==============================================*/

/** Possible peripherals to be linked to event signals (not all available on all MPUs) */
typedef enum e_elc_peripheral
{
    ELC_PERIPHERAL_MTU0          = (0),
    ELC_PERIPHERAL_MTU3          = (1),
    ELC_PERIPHERAL_MTU4          = (2),
    ELC_PERIPHERAL_LLPPGPT_A     = (3),
    ELC_PERIPHERAL_LLPPGPT_B     = (4),
    ELC_PERIPHERAL_LLPPGPT_C     = (5),
    ELC_PERIPHERAL_LLPPGPT_D     = (6),
    ELC_PERIPHERAL_LLPPGPT_E     = (7),
    ELC_PERIPHERAL_LLPPGPT_F     = (8),
    ELC_PERIPHERAL_LLPPGPT_G     = (9),
    ELC_PERIPHERAL_LLPPGPT_H     = (10),
    ELC_PERIPHERAL_NONSAFTYGPT_A = (11),
    ELC_PERIPHERAL_NONSAFTYGPT_B = (12),
    ELC_PERIPHERAL_NONSAFTYGPT_C = (13),
    ELC_PERIPHERAL_NONSAFTYGPT_D = (14),
    ELC_PERIPHERAL_NONSAFTYGPT_E = (15),
    ELC_PERIPHERAL_NONSAFTYGPT_F = (16),
    ELC_PERIPHERAL_NONSAFTYGPT_G = (17),
    ELC_PERIPHERAL_NONSAFTYGPT_H = (18),
    ELC_PERIPHERAL_ADC0_A        = (19),
    ELC_PERIPHERAL_ADC0_B        = (20),
    ELC_PERIPHERAL_ADC1_A        = (21),
    ELC_PERIPHERAL_ADC1_B        = (22),
    ELC_PERIPHERAL_DSMIF0_CAP0   = (23),
    ELC_PERIPHERAL_DSMIF0_CAP1   = (24),
    ELC_PERIPHERAL_DSMIF0_CAP2   = (25),
    ELC_PERIPHERAL_DSMIF0_CAP3   = (26),
    ELC_PERIPHERAL_DSMIF0_CAP4   = (27),
    ELC_PERIPHERAL_DSMIF0_CAP5   = (28),
    ELC_PERIPHERAL_DSMIF0_CDCNT0 = (29),
    ELC_PERIPHERAL_DSMIF0_CDCNT1 = (30),
    ELC_PERIPHERAL_DSMIF0_CDCNT2 = (31),
    ELC_PERIPHERAL_DSMIF1_CAP0   = (32),
    ELC_PERIPHERAL_DSMIF1_CAP1   = (33),
    ELC_PERIPHERAL_DSMIF1_CAP2   = (34),
    ELC_PERIPHERAL_DSMIF1_CAP3   = (35),
    ELC_PERIPHERAL_DSMIF1_CAP4   = (36),
    ELC_PERIPHERAL_DSMIF1_CAP5   = (37),
    ELC_PERIPHERAL_DSMIF1_CDCNT0 = (38),
    ELC_PERIPHERAL_DSMIF1_CDCNT1 = (39),
    ELC_PERIPHERAL_DSMIF1_CDCNT2 = (40),
    ELC_PERIPHERAL_ENCIF_TRG0    = (41),
    ELC_PERIPHERAL_ENCIF_TRG1    = (42),
    ELC_PERIPHERAL_ESC0          = (43),
    ELC_PERIPHERAL_ESC1          = (44),
    ELC_PERIPHERAL_GMA0          = (45),
    ELC_PERIPHERAL_GMA1          = (46),
    ELC_PERIPHERAL_OUTPORTGR1    = (47),
    ELC_PERIPHERAL_OUTPORTGR2    = (48),
    ELC_PERIPHERAL_INPORTGR1     = (49),
    ELC_PERIPHERAL_INPORTGR2     = (50),
    ELC_PERIPHERAL_SINGLEPORT0   = (51),
    ELC_PERIPHERAL_SINGLEPORT1   = (52),
    ELC_PERIPHERAL_SINGLEPORT2   = (53),
    ELC_PERIPHERAL_SINGLEPORT3   = (54),
} elc_peripheral_t;

/*==============================================
 * ETHER API Overrides
 *==============================================*/

/** Event code of callback function */
typedef enum e_ether_event
{
    ETHER_EVENT_WAKEON_LAN,            ///< Magic packet detection event
    ETHER_EVENT_LINK_ON,               ///< Link up detection event
    ETHER_EVENT_LINK_OFF,              ///< Link down detection event
    ETHER_EVENT_SBD_INTERRUPT,         ///< SBD Interrupt event
    ETHER_EVENT_PMT_INTERRUPT          ///< PMT Interrupt event
} ether_event_t;

/** Ether Callback function parameter data */
typedef struct st_ether_callback_args
{
    uint32_t      channel;             ///< Device channel number
    ether_event_t event;               ///< Event code

    uint32_t status_ether;             ///< Interrupt status of SDB or PMT
    uint32_t status_link;              ///< Link status

    void const * p_context;            ///< Placeholder for user data.
} ether_callback_args_t;

/*==============================================
 * ETHER PHY API Overrides
 *==============================================*/

/** Phy LSI */
typedef enum e_ether_phy_lsi_type
{
    ETHER_PHY_LSI_TYPE_DEFAULT = 0,     ///< Select default configuration. This type dose not change Phy LSI default setting by strapping option.
    ETHER_PHY_LSI_TYPE_VSC8541 = 1,     ///< Select configuration forVSC8541
    ETHER_PHY_LSI_TYPE_KSZ9131 = 2,     ///< Select configuration forKSZ9131
    ETHER_PHY_LSI_TYPE_KSZ9031 = 3,     ///< Select configuration forKSZ9031
    ETHER_PHY_LSI_TYPE_KSZ8081 = 4,     ///< Select configuration forKSZ8081
    ETHER_PHY_LSI_TYPE_KSZ8041 = 5,     ///< Select configuration forKSZ8041
    ETHER_PHY_LSI_TYPE_CUSTOM  = 0xFFU, ///< Select configuration for User custom.
} ether_phy_lsi_type_t;

/*==============================================
 * ETHER SWITCH API Overrides
 *==============================================*/

/** Ether Switch Event code of callback function */
typedef enum e_ether_switch_event
{
    ETHER_SWITCH_EVENT_LINK_CHANGE     ///< Change Link status
} ether_switch_event_t;

/** Ether Switch Callback function parameter data */
typedef struct st_ether_switch_callback_args
{
    uint32_t             channel;      ///< Device channel number
    ether_switch_event_t event;        ///< Event code

    uint32_t status_link;              ///< Link status bit0:port0. bit1:port1. bit2:port2, bit3:port3

    void const * p_context;            ///< Placeholder for user data.
} ether_switch_callback_args_t;

/*==============================================
 * IOPORT API Overrides
 *==============================================*/

/** Superset of all peripheral functions.  */
typedef enum e_ioport_pin_pfc
{
    IOPORT_PIN_P000_PFC_00_ETH2_RXD3       = (0x00U << IOPORT_PFC_OFFSET), ///< P00_0 / ETHER_ETHn / ETH2_RXD3
    IOPORT_PIN_P000_PFC_01_D26             = (0x01U << IOPORT_PFC_OFFSET), ///< P00_0 / BSC / D26
    IOPORT_PIN_P000_PFC_02_D15             = (0x02U << IOPORT_PFC_OFFSET), ///< P00_0 / BSC / D15
    IOPORT_PIN_P000_PFC_03_SCK2            = (0x03U << IOPORT_PFC_OFFSET), ///< P00_0 / SCIn / SCK2
    IOPORT_PIN_P001_PFC_00_IRQ0            = (0x00U << IOPORT_PFC_OFFSET), ///< P00_1 / IRQ / IRQ0
    IOPORT_PIN_P001_PFC_01_ETH2_RXDV       = (0x01U << IOPORT_PFC_OFFSET), ///< P00_1 / ETHER_ETHn / ETH2_RXDV
    IOPORT_PIN_P001_PFC_02_D27             = (0x02U << IOPORT_PFC_OFFSET), ///< P00_1 / BSC / D27
    IOPORT_PIN_P001_PFC_03_A13             = (0x03U << IOPORT_PFC_OFFSET), ///< P00_1 / BSC / A13
    IOPORT_PIN_P001_PFC_04_MTIC5U          = (0x04U << IOPORT_PFC_OFFSET), ///< P00_1 / MTU3n / MTIC5U
    IOPORT_PIN_P001_PFC_05_RXD2_SCL2_MISO2 = (0x05U << IOPORT_PFC_OFFSET), ///< P00_1 / SCIn / RXD2_SCL2_MISO2
    IOPORT_PIN_P002_PFC_00_ETH2_TXEN       = (0x00U << IOPORT_PFC_OFFSET), ///< P00_2 / ETHER_ETHn / ETH2_TXEN
    IOPORT_PIN_P002_PFC_01_D28             = (0x01U << IOPORT_PFC_OFFSET), ///< P00_2 / BSC / D28
    IOPORT_PIN_P002_PFC_02_RD              = (0x02U << IOPORT_PFC_OFFSET), ///< P00_2 / BSC / RD
    IOPORT_PIN_P002_PFC_03_MTIC5V          = (0x03U << IOPORT_PFC_OFFSET), ///< P00_2 / MTU3n / MTIC5V
    IOPORT_PIN_P002_PFC_04_TXD2_SDA2_MOSI2 = (0x04U << IOPORT_PFC_OFFSET), ///< P00_2 / SCIn / TXD2_SDA2_MOSI2
    IOPORT_PIN_P002_PFC_05_USB_OVRCUR      = (0x05U << IOPORT_PFC_OFFSET), ///< P00_2 / USB_HS / USB_OVRCUR
    IOPORT_PIN_P003_PFC_00_IRQ1            = (0x00U << IOPORT_PFC_OFFSET), ///< P00_3 / IRQ / IRQ1
    IOPORT_PIN_P003_PFC_01_ETH2_REFCLK     = (0x01U << IOPORT_PFC_OFFSET), ///< P00_3 / ETHER_ETHn / ETH2_REFCLK
    IOPORT_PIN_P003_PFC_02_RMII2_REFCLK    = (0x02U << IOPORT_PFC_OFFSET), ///< P00_3 / ETHER_ETHn / RMII2_REFCLK
    IOPORT_PIN_P003_PFC_03_D29             = (0x03U << IOPORT_PFC_OFFSET), ///< P00_3 / BSC / D29
    IOPORT_PIN_P003_PFC_04_RD_WR           = (0x04U << IOPORT_PFC_OFFSET), ///< P00_3 / BSC / RD_WR
    IOPORT_PIN_P003_PFC_05_MTIC5W          = (0x05U << IOPORT_PFC_OFFSET), ///< P00_3 / MTU3n / MTIC5W
    IOPORT_PIN_P003_PFC_06_SS2_CTS2_RTS2   = (0x06U << IOPORT_PFC_OFFSET), ///< P00_3 / SCIn / SS2_CTS2_RTS2
    IOPORT_PIN_P004_PFC_00_IRQ13           = (0x00U << IOPORT_PFC_OFFSET), ///< P00_4 / IRQ / IRQ13
    IOPORT_PIN_P004_PFC_01_ETH2_RXER       = (0x01U << IOPORT_PFC_OFFSET), ///< P00_4 / ETHER_ETHn / ETH2_RXER
    IOPORT_PIN_P004_PFC_02_D30             = (0x02U << IOPORT_PFC_OFFSET), ///< P00_4 / BSC / D30
    IOPORT_PIN_P004_PFC_03_WAIT            = (0x03U << IOPORT_PFC_OFFSET), ///< P00_4 / BSC / WAIT
    IOPORT_PIN_P004_PFC_04_MTIOC3A         = (0x04U << IOPORT_PFC_OFFSET), ///< P00_4 / MTU3n / MTIOC3A
    IOPORT_PIN_P004_PFC_05_GTIOC0A         = (0x05U << IOPORT_PFC_OFFSET), ///< P00_4 / GPTn / GTIOC0A
    IOPORT_PIN_P004_PFC_06_MCLK0           = (0x06U << IOPORT_PFC_OFFSET), ///< P00_4 / DSMIFn / MCLK0
    IOPORT_PIN_P005_PFC_00_ETHSW_PHYLINK2  = (0x00U << IOPORT_PFC_OFFSET), ///< P00_5 / ETHER_ETHSW / ETHSW_PHYLINK2
    IOPORT_PIN_P005_PFC_01_D31             = (0x01U << IOPORT_PFC_OFFSET), ///< P00_5 / BSC / D31
    IOPORT_PIN_P005_PFC_02_CS0             = (0x02U << IOPORT_PFC_OFFSET), ///< P00_5 / BSC / CS0
    IOPORT_PIN_P005_PFC_03_ESC_PHYLINK2    = (0x03U << IOPORT_PFC_OFFSET), ///< P00_5 / ETHER_ESC / ESC_PHYLINK2
    IOPORT_PIN_P005_PFC_04_MTIOC3C         = (0x04U << IOPORT_PFC_OFFSET), ///< P00_5 / MTU3n / MTIOC3C
    IOPORT_PIN_P005_PFC_05_GTIOC0B         = (0x05U << IOPORT_PFC_OFFSET), ///< P00_5 / GPTn / GTIOC0B
    IOPORT_PIN_P005_PFC_06_MDAT0           = (0x06U << IOPORT_PFC_OFFSET), ///< P00_5 / DSMIFn / MDAT0
    IOPORT_PIN_P006_PFC_00_ETH2_TXCLK      = (0x00U << IOPORT_PFC_OFFSET), ///< P00_6 / ETHER_ETHn / ETH2_TXCLK
    IOPORT_PIN_P006_PFC_01_CS5             = (0x01U << IOPORT_PFC_OFFSET), ///< P00_6 / BSC / CS5
    IOPORT_PIN_P006_PFC_02_MTIOC3B         = (0x02U << IOPORT_PFC_OFFSET), ///< P00_6 / MTU3n / MTIOC3B
    IOPORT_PIN_P006_PFC_03_GTIOC1A         = (0x03U << IOPORT_PFC_OFFSET), ///< P00_6 / GPTn / GTIOC1A
    IOPORT_PIN_P007_PFC_00_IRQ13           = (0x00U << IOPORT_PFC_OFFSET), ///< P00_7 / IRQ / IRQ13
    IOPORT_PIN_P007_PFC_01_RAS             = (0x01U << IOPORT_PFC_OFFSET), ///< P00_7 / BSC / RAS
    IOPORT_PIN_P007_PFC_02_MTIOC4A         = (0x02U << IOPORT_PFC_OFFSET), ///< P00_7 / MTU3n / MTIOC4A
    IOPORT_PIN_P007_PFC_03_GTIOC2A         = (0x03U << IOPORT_PFC_OFFSET), ///< P00_7 / GPTn / GTIOC2A
    IOPORT_PIN_P010_PFC_00_GMAC_MDIO       = (0x00U << IOPORT_PFC_OFFSET), ///< P01_0 / ETHER_GMAC / GMAC_MDIO
    IOPORT_PIN_P010_PFC_01_ETHSW_MDIO      = (0x01U << IOPORT_PFC_OFFSET), ///< P01_0 / ETHER_ETHSW / ETHSW_MDIO
    IOPORT_PIN_P010_PFC_02_CAS             = (0x02U << IOPORT_PFC_OFFSET), ///< P01_0 / BSC / CAS
    IOPORT_PIN_P010_PFC_03_ESC_MDIO        = (0x03U << IOPORT_PFC_OFFSET), ///< P01_0 / ETHER_ESC / ESC_MDIO
    IOPORT_PIN_P010_PFC_04_MTIOC4C         = (0x04U << IOPORT_PFC_OFFSET), ///< P01_0 / MTU3n / MTIOC4C
    IOPORT_PIN_P010_PFC_05_GTIOC3A         = (0x05U << IOPORT_PFC_OFFSET), ///< P01_0 / GPTn / GTIOC3A
    IOPORT_PIN_P010_PFC_06_CTS2            = (0x06U << IOPORT_PFC_OFFSET), ///< P01_0 / SCIn / CTS2
    IOPORT_PIN_P010_PFC_07_MCLK1           = (0x07U << IOPORT_PFC_OFFSET), ///< P01_0 / DSMIFn / MCLK1
    IOPORT_PIN_P011_PFC_00_GMAC_MDC        = (0x00U << IOPORT_PFC_OFFSET), ///< P01_1 / ETHER_GMAC / GMAC_MDC
    IOPORT_PIN_P011_PFC_01_ETHSW_MDC       = (0x01U << IOPORT_PFC_OFFSET), ///< P01_1 / ETHER_ETHSW / ETHSW_MDC
    IOPORT_PIN_P011_PFC_02_CKE             = (0x02U << IOPORT_PFC_OFFSET), ///< P01_1 / BSC / CKE
    IOPORT_PIN_P011_PFC_03_ESC_MDC         = (0x03U << IOPORT_PFC_OFFSET), ///< P01_1 / ETHER_ESC / ESC_MDC
    IOPORT_PIN_P011_PFC_04_MTIOC3D         = (0x04U << IOPORT_PFC_OFFSET), ///< P01_1 / MTU3n / MTIOC3D
    IOPORT_PIN_P011_PFC_05_GTIOC1B         = (0x05U << IOPORT_PFC_OFFSET), ///< P01_1 / GPTn / GTIOC1B
    IOPORT_PIN_P011_PFC_06_DE2             = (0x06U << IOPORT_PFC_OFFSET), ///< P01_1 / SCIn / DE2
    IOPORT_PIN_P011_PFC_07_MDAT1           = (0x07U << IOPORT_PFC_OFFSET), ///< P01_1 / DSMIFn / MDAT1
    IOPORT_PIN_P012_PFC_00_IRQ2            = (0x00U << IOPORT_PFC_OFFSET), ///< P01_2 / IRQ / IRQ2
    IOPORT_PIN_P012_PFC_01_ETH2_TXD3       = (0x01U << IOPORT_PFC_OFFSET), ///< P01_2 / ETHER_ETHn / ETH2_TXD3
    IOPORT_PIN_P012_PFC_02_CS2             = (0x02U << IOPORT_PFC_OFFSET), ///< P01_2 / BSC / CS2
    IOPORT_PIN_P012_PFC_03_MTIOC4B         = (0x03U << IOPORT_PFC_OFFSET), ///< P01_2 / MTU3n / MTIOC4B
    IOPORT_PIN_P012_PFC_04_GTIOC2B         = (0x04U << IOPORT_PFC_OFFSET), ///< P01_2 / GPTn / GTIOC2B
    IOPORT_PIN_P013_PFC_00_ETH2_TXD2       = (0x00U << IOPORT_PFC_OFFSET), ///< P01_3 / ETHER_ETHn / ETH2_TXD2
    IOPORT_PIN_P013_PFC_01_WE3_DQMUU_AH    = (0x01U << IOPORT_PFC_OFFSET), ///< P01_3 / BSC / WE3_DQMUU_AH
    IOPORT_PIN_P013_PFC_02_MTIOC4D         = (0x02U << IOPORT_PFC_OFFSET), ///< P01_3 / MTU3n / MTIOC4D
    IOPORT_PIN_P013_PFC_03_GTIOC3B         = (0x03U << IOPORT_PFC_OFFSET), ///< P01_3 / GPTn / GTIOC3B
    IOPORT_PIN_P014_PFC_00_IRQ3            = (0x00U << IOPORT_PFC_OFFSET), ///< P01_4 / IRQ / IRQ3
    IOPORT_PIN_P014_PFC_01_ETH2_TXD1       = (0x01U << IOPORT_PFC_OFFSET), ///< P01_4 / ETHER_ETHn / ETH2_TXD1
    IOPORT_PIN_P014_PFC_02_WE1_DQMLU       = (0x02U << IOPORT_PFC_OFFSET), ///< P01_4 / BSC / WE1_DQMLU
    IOPORT_PIN_P014_PFC_03_POE0            = (0x03U << IOPORT_PFC_OFFSET), ///< P01_4 / MTU_POE3 / POE0
    IOPORT_PIN_P015_PFC_00_ETH2_TXD0       = (0x00U << IOPORT_PFC_OFFSET), ///< P01_5 / ETHER_ETHn / ETH2_TXD0
    IOPORT_PIN_P015_PFC_01_WE0_DQMLL       = (0x01U << IOPORT_PFC_OFFSET), ///< P01_5 / BSC / WE0_DQMLL
    IOPORT_PIN_P016_PFC_00_GMAC_PTPTRG1    = (0x00U << IOPORT_PFC_OFFSET), ///< P01_6 / ETHER_GMAC / GMAC_PTPTRG1
    IOPORT_PIN_P016_PFC_01_TRACEDATA0      = (0x01U << IOPORT_PFC_OFFSET), ///< P01_6 / TRACE / TRACEDATA0
    IOPORT_PIN_P016_PFC_02_A20             = (0x02U << IOPORT_PFC_OFFSET), ///< P01_6 / BSC / A20
    IOPORT_PIN_P016_PFC_03_ESC_LATCH1      = (0x03U << IOPORT_PFC_OFFSET), ///< P01_6 / ETHER_ESC / ESC_LATCH1
    IOPORT_PIN_P016_PFC_04_ESC_LATCH0      = (0x04U << IOPORT_PFC_OFFSET), ///< P01_6 / ETHER_ESC / ESC_LATCH0
    IOPORT_PIN_P016_PFC_05_MTIOC1A         = (0x05U << IOPORT_PFC_OFFSET), ///< P01_6 / MTU3n / MTIOC1A
    IOPORT_PIN_P016_PFC_06_GTIOC9A         = (0x06U << IOPORT_PFC_OFFSET), ///< P01_6 / GPTn / GTIOC9A
    IOPORT_PIN_P016_PFC_07_CTS1            = (0x07U << IOPORT_PFC_OFFSET), ///< P01_6 / SCIn / CTS1
    IOPORT_PIN_P016_PFC_08_CANTXDP1        = (0x08U << IOPORT_PFC_OFFSET), ///< P01_6 / CANFDn / CANTXDP1
    IOPORT_PIN_P016_PFC_09_ENCIF0          = (0x09U << IOPORT_PFC_OFFSET), ///< P01_6 / ENCIF / ENCIF0
    IOPORT_PIN_P017_PFC_00_ETHSW_LPI1      = (0x00U << IOPORT_PFC_OFFSET), ///< P01_7 / ETHER_ETHSW / ETHSW_LPI1
    IOPORT_PIN_P017_PFC_01_TRACEDATA1      = (0x01U << IOPORT_PFC_OFFSET), ///< P01_7 / TRACE / TRACEDATA1
    IOPORT_PIN_P017_PFC_02_A19             = (0x02U << IOPORT_PFC_OFFSET), ///< P01_7 / BSC / A19
    IOPORT_PIN_P017_PFC_03_MTIOC1B         = (0x03U << IOPORT_PFC_OFFSET), ///< P01_7 / MTU3n / MTIOC1B
    IOPORT_PIN_P017_PFC_04_GTIOC9B         = (0x04U << IOPORT_PFC_OFFSET), ///< P01_7 / GPTn / GTIOC9B
    IOPORT_PIN_P017_PFC_05_ADTRG0          = (0x05U << IOPORT_PFC_OFFSET), ///< P01_7 / ADCn / ADTRG0
    IOPORT_PIN_P017_PFC_06_SCK1            = (0x06U << IOPORT_PFC_OFFSET), ///< P01_7 / SCIn / SCK1
    IOPORT_PIN_P017_PFC_07_SPI_RSPCK3      = (0x07U << IOPORT_PFC_OFFSET), ///< P01_7 / SPIn / SPI_RSPCK3
    IOPORT_PIN_P017_PFC_08_CANRX0          = (0x08U << IOPORT_PFC_OFFSET), ///< P01_7 / CANFDn / CANRX0
    IOPORT_PIN_P017_PFC_09_ENCIF1          = (0x09U << IOPORT_PFC_OFFSET), ///< P01_7 / ENCIF / ENCIF1
    IOPORT_PIN_P020_PFC_00_IRQ4            = (0x00U << IOPORT_PFC_OFFSET), ///< P02_0 / IRQ / IRQ4
    IOPORT_PIN_P020_PFC_01_ETHSW_LPI2      = (0x01U << IOPORT_PFC_OFFSET), ///< P02_0 / ETHER_ETHSW / ETHSW_LPI2
    IOPORT_PIN_P020_PFC_02_TRACEDATA2      = (0x02U << IOPORT_PFC_OFFSET), ///< P02_0 / TRACE / TRACEDATA2
    IOPORT_PIN_P020_PFC_03_A18             = (0x03U << IOPORT_PFC_OFFSET), ///< P02_0 / BSC / A18
    IOPORT_PIN_P020_PFC_04_GTADSML0        = (0x04U << IOPORT_PFC_OFFSET), ///< P02_0 / GPT / GTADSML0
    IOPORT_PIN_P020_PFC_05_RXD1_SCL1_MISO1 = (0x05U << IOPORT_PFC_OFFSET), ///< P02_0 / SCIn / RXD1_SCL1_MISO1
    IOPORT_PIN_P020_PFC_06_SPI_MISO3       = (0x06U << IOPORT_PFC_OFFSET), ///< P02_0 / SPIn / SPI_MISO3
    IOPORT_PIN_P020_PFC_07_CANTX1          = (0x07U << IOPORT_PFC_OFFSET), ///< P02_0 / CANFDn / CANTX1
    IOPORT_PIN_P020_PFC_08_USB_OTGID       = (0x08U << IOPORT_PFC_OFFSET), ///< P02_0 / USB_HS / USB_OTGID
    IOPORT_PIN_P020_PFC_09_ENCIF2          = (0x09U << IOPORT_PFC_OFFSET), ///< P02_0 / ENCIF / ENCIF2
    IOPORT_PIN_P021_PFC_00_ETHSW_PTPOUT1   = (0x00U << IOPORT_PFC_OFFSET), ///< P02_1 / ETHER_ETHSW / ETHSW_PTPOUT1
    IOPORT_PIN_P021_PFC_01_A17             = (0x01U << IOPORT_PFC_OFFSET), ///< P02_1 / BSC / A17
    IOPORT_PIN_P021_PFC_02_ESC_SYNC1       = (0x02U << IOPORT_PFC_OFFSET), ///< P02_1 / ETHER_ESC / ESC_SYNC1
    IOPORT_PIN_P021_PFC_03_ESC_SYNC0       = (0x03U << IOPORT_PFC_OFFSET), ///< P02_1 / ETHER_ESC / ESC_SYNC0
    IOPORT_PIN_P022_PFC_00_IRQ14           = (0x00U << IOPORT_PFC_OFFSET), ///< P02_2 / IRQ / IRQ14
    IOPORT_PIN_P022_PFC_01_ETHSW_TDMAOUT0  = (0x01U << IOPORT_PFC_OFFSET), ///< P02_2 / ETHER_ETHSW / ETHSW_TDMAOUT0
    IOPORT_PIN_P022_PFC_02_A16             = (0x02U << IOPORT_PFC_OFFSET), ///< P02_2 / BSC / A16
    IOPORT_PIN_P022_PFC_03_MTIOC2A         = (0x03U << IOPORT_PFC_OFFSET), ///< P02_2 / MTU3n / MTIOC2A
    IOPORT_PIN_P022_PFC_04_GTIOC10A        = (0x04U << IOPORT_PFC_OFFSET), ///< P02_2 / GPTn / GTIOC10A
    IOPORT_PIN_P022_PFC_05_POE10           = (0x05U << IOPORT_PFC_OFFSET), ///< P02_2 / MTU_POE3 / POE10
    IOPORT_PIN_P022_PFC_06_TXD1_SDA1_MOSI1 = (0x06U << IOPORT_PFC_OFFSET), ///< P02_2 / SCIn / TXD1_SDA1_MOSI1
    IOPORT_PIN_P022_PFC_07_SPI_MOSI3       = (0x07U << IOPORT_PFC_OFFSET), ///< P02_2 / SPIn / SPI_MOSI3
    IOPORT_PIN_P022_PFC_08_CANTX0          = (0x08U << IOPORT_PFC_OFFSET), ///< P02_2 / CANFDn / CANTX0
    IOPORT_PIN_P022_PFC_09_ENCIF3          = (0x09U << IOPORT_PFC_OFFSET), ///< P02_2 / ENCIF / ENCIF3
    IOPORT_PIN_P022_PFC_0A_RTCAT1HZ        = (0x0AU << IOPORT_PFC_OFFSET), ///< P02_2 / RTC / RTCAT1HZ
    IOPORT_PIN_P023_PFC_00_IRQ15           = (0x00U << IOPORT_PFC_OFFSET), ///< P02_3 / IRQ / IRQ15
    IOPORT_PIN_P023_PFC_01_ETHSW_TDMAOUT1  = (0x01U << IOPORT_PFC_OFFSET), ///< P02_3 / ETHER_ETHSW / ETHSW_TDMAOUT1
    IOPORT_PIN_P023_PFC_02_A15             = (0x02U << IOPORT_PFC_OFFSET), ///< P02_3 / BSC / A15
    IOPORT_PIN_P023_PFC_03_WE3_DQMUU_AH    = (0x03U << IOPORT_PFC_OFFSET), ///< P02_3 / BSC / WE3_DQMUU_AH
    IOPORT_PIN_P023_PFC_04_MTIOC2B         = (0x04U << IOPORT_PFC_OFFSET), ///< P02_3 / MTU3n / MTIOC2B
    IOPORT_PIN_P023_PFC_05_GTIOC10B        = (0x05U << IOPORT_PFC_OFFSET), ///< P02_3 / GPTn / GTIOC10B
    IOPORT_PIN_P023_PFC_06_POE11           = (0x06U << IOPORT_PFC_OFFSET), ///< P02_3 / MTU_POE3 / POE11
    IOPORT_PIN_P023_PFC_07_SS1_CTS1_RTS1   = (0x07U << IOPORT_PFC_OFFSET), ///< P02_3 / SCIn / SS1_CTS1_RTS1
    IOPORT_PIN_P023_PFC_08_SPI_SSL30       = (0x08U << IOPORT_PFC_OFFSET), ///< P02_3 / SPIn / SPI_SSL30
    IOPORT_PIN_P023_PFC_09_CANRX1          = (0x09U << IOPORT_PFC_OFFSET), ///< P02_3 / CANFDn / CANRX1
    IOPORT_PIN_P023_PFC_0A_ENCIF4          = (0x0AU << IOPORT_PFC_OFFSET), ///< P02_3 / ENCIF / ENCIF4
    IOPORT_PIN_P024_PFC_00_TDO             = (0x00U << IOPORT_PFC_OFFSET), ///< P02_4 / JTAG/SWD / TDO
    IOPORT_PIN_P024_PFC_01_WE0_DQMLL       = (0x01U << IOPORT_PFC_OFFSET), ///< P02_4 / BSC / WE0_DQMLL
    IOPORT_PIN_P024_PFC_02_DE1             = (0x02U << IOPORT_PFC_OFFSET), ///< P02_4 / SCIn / DE1
    IOPORT_PIN_P024_PFC_03_SPI_SSL33       = (0x03U << IOPORT_PFC_OFFSET), ///< P02_4 / SPIn / SPI_SSL33
    IOPORT_PIN_P025_PFC_00_ETHSW_TDMAOUT3  = (0x00U << IOPORT_PFC_OFFSET), ///< P02_5 / ETHER_ETHSW / ETHSW_TDMAOUT3
    IOPORT_PIN_P025_PFC_01_TDI             = (0x01U << IOPORT_PFC_OFFSET), ///< P02_5 / JTAG/SWD / TDI
    IOPORT_PIN_P025_PFC_02_WE1_DQMLU       = (0x02U << IOPORT_PFC_OFFSET), ///< P02_5 / BSC / WE1_DQMLU
    IOPORT_PIN_P025_PFC_03_SCK5            = (0x03U << IOPORT_PFC_OFFSET), ///< P02_5 / SCIn / SCK5
    IOPORT_PIN_P025_PFC_04_SPI_SSL31       = (0x04U << IOPORT_PFC_OFFSET), ///< P02_5 / SPIn / SPI_SSL31
    IOPORT_PIN_P025_PFC_05_ENCIF5          = (0x05U << IOPORT_PFC_OFFSET), ///< P02_5 / ENCIF / ENCIF5
    IOPORT_PIN_P026_PFC_00_TMS_SWDIO       = (0x00U << IOPORT_PFC_OFFSET), ///< P02_6 / JTAG/SWD / TMS_SWDIO
    IOPORT_PIN_P026_PFC_01_RXD5_SCL5_MISO5 = (0x01U << IOPORT_PFC_OFFSET), ///< P02_6 / SCIn / RXD5_SCL5_MISO5
    IOPORT_PIN_P026_PFC_02_ENCIF6          = (0x02U << IOPORT_PFC_OFFSET), ///< P02_6 / ENCIF / ENCIF6
    IOPORT_PIN_P027_PFC_00_TCK_SWCLK       = (0x00U << IOPORT_PFC_OFFSET), ///< P02_7 / JTAG/SWD / TCK_SWCLK
    IOPORT_PIN_P027_PFC_01_TXD5_SDA5_MOSI5 = (0x01U << IOPORT_PFC_OFFSET), ///< P02_7 / SCIn / TXD5_SDA5_MOSI5
    IOPORT_PIN_P027_PFC_02_ENCIF7          = (0x02U << IOPORT_PFC_OFFSET), ///< P02_7 / ENCIF / ENCIF7
    IOPORT_PIN_P030_PFC_00_IRQ14           = (0x00U << IOPORT_PFC_OFFSET), ///< P03_0 / IRQ / IRQ14
    IOPORT_PIN_P030_PFC_01_TRACEDATA3      = (0x01U << IOPORT_PFC_OFFSET), ///< P03_0 / TRACE / TRACEDATA3
    IOPORT_PIN_P030_PFC_02_A14             = (0x02U << IOPORT_PFC_OFFSET), ///< P03_0 / BSC / A14
    IOPORT_PIN_P030_PFC_03_CS5             = (0x03U << IOPORT_PFC_OFFSET), ///< P03_0 / BSC / CS5
    IOPORT_PIN_P030_PFC_04_GTADSML1        = (0x04U << IOPORT_PFC_OFFSET), ///< P03_0 / GPT / GTADSML1
    IOPORT_PIN_P030_PFC_05_SCK2            = (0x05U << IOPORT_PFC_OFFSET), ///< P03_0 / SCIn / SCK2
    IOPORT_PIN_P030_PFC_06_SPI_SSL32       = (0x06U << IOPORT_PFC_OFFSET), ///< P03_0 / SPIn / SPI_SSL32
    IOPORT_PIN_P030_PFC_07_CANTXDP1        = (0x07U << IOPORT_PFC_OFFSET), ///< P03_0 / CANFDn / CANTXDP1
    IOPORT_PIN_P030_PFC_08_ENCIF8          = (0x08U << IOPORT_PFC_OFFSET), ///< P03_0 / ENCIF / ENCIF8
    IOPORT_PIN_P032_PFC_00_NMI             = (0x00U << IOPORT_PFC_OFFSET), ///< P03_2 / IRQ / NMI
    IOPORT_PIN_P032_PFC_01_ETHSW_TDMAOUT2  = (0x01U << IOPORT_PFC_OFFSET), ///< P03_2 / ETHER_ETHSW / ETHSW_TDMAOUT2
    IOPORT_PIN_P032_PFC_02_A13             = (0x02U << IOPORT_PFC_OFFSET), ///< P03_2 / BSC / A13
    IOPORT_PIN_P032_PFC_03_CTS2            = (0x03U << IOPORT_PFC_OFFSET), ///< P03_2 / SCIn / CTS2
    IOPORT_PIN_P032_PFC_04_CANRXDP0        = (0x04U << IOPORT_PFC_OFFSET), ///< P03_2 / CANFDn / CANRXDP0
    IOPORT_PIN_P033_PFC_00_IRQ11           = (0x00U << IOPORT_PFC_OFFSET), ///< P03_3 / IRQ / IRQ11
    IOPORT_PIN_P033_PFC_01_WAIT            = (0x01U << IOPORT_PFC_OFFSET), ///< P03_3 / BSC / WAIT
    IOPORT_PIN_P033_PFC_02_DE2             = (0x02U << IOPORT_PFC_OFFSET), ///< P03_3 / SCIn / DE2
    IOPORT_PIN_P033_PFC_03_TEND            = (0x03U << IOPORT_PFC_OFFSET), ///< P03_3 / DMAC / TEND
    IOPORT_PIN_P033_PFC_04_USB_OTGID       = (0x04U << IOPORT_PFC_OFFSET), ///< P03_3 / USB_HS / USB_OTGID
    IOPORT_PIN_P033_PFC_05_ENCIF9          = (0x05U << IOPORT_PFC_OFFSET), ///< P03_3 / ENCIF / ENCIF9
    IOPORT_PIN_P034_PFC_00_IRQ7            = (0x00U << IOPORT_PFC_OFFSET), ///< P03_4 / IRQ / IRQ7
    IOPORT_PIN_P034_PFC_01_RD_WR           = (0x01U << IOPORT_PFC_OFFSET), ///< P03_4 / BSC / RD_WR
    IOPORT_PIN_P034_PFC_02_SS2_CTS2_RTS2   = (0x02U << IOPORT_PFC_OFFSET), ///< P03_4 / SCIn / SS2_CTS2_RTS2
    IOPORT_PIN_P034_PFC_03_SPI_SSL03       = (0x03U << IOPORT_PFC_OFFSET), ///< P03_4 / SPIn / SPI_SSL03
    IOPORT_PIN_P035_PFC_00_IRQ5            = (0x00U << IOPORT_PFC_OFFSET), ///< P03_5 / IRQ / IRQ5
    IOPORT_PIN_P035_PFC_01_ETH2_CRS        = (0x01U << IOPORT_PFC_OFFSET), ///< P03_5 / ETHER_ETHn / ETH2_CRS
    IOPORT_PIN_P035_PFC_02_A12             = (0x02U << IOPORT_PFC_OFFSET), ///< P03_5 / BSC / A12
    IOPORT_PIN_P035_PFC_03_MTIOC3A         = (0x03U << IOPORT_PFC_OFFSET), ///< P03_5 / MTU3n / MTIOC3A
    IOPORT_PIN_P035_PFC_04_GTIOC4A         = (0x04U << IOPORT_PFC_OFFSET), ///< P03_5 / GPTn / GTIOC4A
    IOPORT_PIN_P035_PFC_05_RXD2_SCL2_MISO2 = (0x05U << IOPORT_PFC_OFFSET), ///< P03_5 / SCIn / RXD2_SCL2_MISO2
    IOPORT_PIN_P035_PFC_06_MCLK2           = (0x06U << IOPORT_PFC_OFFSET), ///< P03_5 / DSMIFn / MCLK2
    IOPORT_PIN_P036_PFC_00_IRQ8            = (0x00U << IOPORT_PFC_OFFSET), ///< P03_6 / IRQ / IRQ8
    IOPORT_PIN_P036_PFC_01_ETH2_COL        = (0x01U << IOPORT_PFC_OFFSET), ///< P03_6 / ETHER_ETHn / ETH2_COL
    IOPORT_PIN_P036_PFC_02_TRACEDATA4      = (0x02U << IOPORT_PFC_OFFSET), ///< P03_6 / TRACE / TRACEDATA4
    IOPORT_PIN_P036_PFC_03_A11             = (0x03U << IOPORT_PFC_OFFSET), ///< P03_6 / BSC / A11
    IOPORT_PIN_P036_PFC_04_MTIOC3B         = (0x04U << IOPORT_PFC_OFFSET), ///< P03_6 / MTU3n / MTIOC3B
    IOPORT_PIN_P036_PFC_05_GTIOC4B         = (0x05U << IOPORT_PFC_OFFSET), ///< P03_6 / GPTn / GTIOC4B
    IOPORT_PIN_P036_PFC_06_TXD2_SDA2_MOSI2 = (0x06U << IOPORT_PFC_OFFSET), ///< P03_6 / SCIn / TXD2_SDA2_MOSI2
    IOPORT_PIN_P036_PFC_07_SPI_SSL13       = (0x07U << IOPORT_PFC_OFFSET), ///< P03_6 / SPIn / SPI_SSL13
    IOPORT_PIN_P036_PFC_08_MDAT2           = (0x08U << IOPORT_PFC_OFFSET), ///< P03_6 / DSMIFn / MDAT2
    IOPORT_PIN_P037_PFC_00_IRQ9            = (0x00U << IOPORT_PFC_OFFSET), ///< P03_7 / IRQ / IRQ9
    IOPORT_PIN_P037_PFC_01_ETH2_TXER       = (0x01U << IOPORT_PFC_OFFSET), ///< P03_7 / ETHER_ETHn / ETH2_TXER
    IOPORT_PIN_P037_PFC_02_TRACEDATA5      = (0x02U << IOPORT_PFC_OFFSET), ///< P03_7 / TRACE / TRACEDATA5
    IOPORT_PIN_P037_PFC_03_A10             = (0x03U << IOPORT_PFC_OFFSET), ///< P03_7 / BSC / A10
    IOPORT_PIN_P037_PFC_04_MTIOC3C         = (0x04U << IOPORT_PFC_OFFSET), ///< P03_7 / MTU3n / MTIOC3C
    IOPORT_PIN_P037_PFC_05_GTIOC5A         = (0x05U << IOPORT_PFC_OFFSET), ///< P03_7 / GPTn / GTIOC5A
    IOPORT_PIN_P037_PFC_06_SCK3            = (0x06U << IOPORT_PFC_OFFSET), ///< P03_7 / SCIn / SCK3
    IOPORT_PIN_P040_PFC_00_TRACEDATA6      = (0x00U << IOPORT_PFC_OFFSET), ///< P04_0 / TRACE / TRACEDATA6
    IOPORT_PIN_P040_PFC_01_A9              = (0x01U << IOPORT_PFC_OFFSET), ///< P04_0 / BSC / A9
    IOPORT_PIN_P040_PFC_02_MTIOC3D         = (0x02U << IOPORT_PFC_OFFSET), ///< P04_0 / MTU3n / MTIOC3D
    IOPORT_PIN_P040_PFC_03_GTIOC5B         = (0x03U << IOPORT_PFC_OFFSET), ///< P04_0 / GPTn / GTIOC5B
    IOPORT_PIN_P040_PFC_04_RXD3_SCL3_MISO3 = (0x04U << IOPORT_PFC_OFFSET), ///< P04_0 / SCIn / RXD3_SCL3_MISO3
    IOPORT_PIN_P041_PFC_00_CKIO            = (0x00U << IOPORT_PFC_OFFSET), ///< P04_1 / BSC / CKIO
    IOPORT_PIN_P041_PFC_01_TXD3_SDA3_MOSI3 = (0x01U << IOPORT_PFC_OFFSET), ///< P04_1 / SCIn / TXD3_SDA3_MOSI3
    IOPORT_PIN_P041_PFC_02_SPI_MOSI0       = (0x02U << IOPORT_PFC_OFFSET), ///< P04_1 / SPIn / SPI_MOSI0
    IOPORT_PIN_P041_PFC_03_IIC_SDA2        = (0x03U << IOPORT_PFC_OFFSET), ///< P04_1 / IICn / IIC_SDA2
    IOPORT_PIN_P042_PFC_00_CS0             = (0x00U << IOPORT_PFC_OFFSET), ///< P04_2 / BSC / CS0
    IOPORT_PIN_P043_PFC_00_RD              = (0x00U << IOPORT_PFC_OFFSET), ///< P04_3 / BSC / RD
    IOPORT_PIN_P043_PFC_01_SS3_CTS3_RTS3   = (0x01U << IOPORT_PFC_OFFSET), ///< P04_3 / SCIn / SS3_CTS3_RTS3
    IOPORT_PIN_P043_PFC_02_SPI_RSPCK0      = (0x02U << IOPORT_PFC_OFFSET), ///< P04_3 / SPIn / SPI_RSPCK0
    IOPORT_PIN_P043_PFC_03_IIC_SCL2        = (0x03U << IOPORT_PFC_OFFSET), ///< P04_3 / IICn / IIC_SCL2
    IOPORT_PIN_P043_PFC_04_USB_OVRCUR      = (0x04U << IOPORT_PFC_OFFSET), ///< P04_3 / USB_HS / USB_OVRCUR
    IOPORT_PIN_P044_PFC_00_IRQ10           = (0x00U << IOPORT_PFC_OFFSET), ///< P04_4 / IRQ / IRQ10
    IOPORT_PIN_P044_PFC_01_TRACEDATA7      = (0x01U << IOPORT_PFC_OFFSET), ///< P04_4 / TRACE / TRACEDATA7
    IOPORT_PIN_P044_PFC_02_A8              = (0x02U << IOPORT_PFC_OFFSET), ///< P04_4 / BSC / A8
    IOPORT_PIN_P044_PFC_03_GTADSMP0        = (0x03U << IOPORT_PFC_OFFSET), ///< P04_4 / GPT / GTADSMP0
    IOPORT_PIN_P044_PFC_04_POE10           = (0x04U << IOPORT_PFC_OFFSET), ///< P04_4 / MTU_POE3 / POE10
    IOPORT_PIN_P044_PFC_05_CTS3            = (0x05U << IOPORT_PFC_OFFSET), ///< P04_4 / SCIn / CTS3
    IOPORT_PIN_P044_PFC_06_SPI_RSPCK1      = (0x06U << IOPORT_PFC_OFFSET), ///< P04_4 / SPIn / SPI_RSPCK1
    IOPORT_PIN_P044_PFC_07_ENCIF10         = (0x07U << IOPORT_PFC_OFFSET), ///< P04_4 / ENCIF / ENCIF10
    IOPORT_PIN_P045_PFC_00_A7              = (0x00U << IOPORT_PFC_OFFSET), ///< P04_5 / BSC / A7
    IOPORT_PIN_P045_PFC_01_DE3             = (0x01U << IOPORT_PFC_OFFSET), ///< P04_5 / SCIn / DE3
    IOPORT_PIN_P046_PFC_00_ETH1_TXER       = (0x00U << IOPORT_PFC_OFFSET), ///< P04_6 / ETHER_ETHn / ETH1_TXER
    IOPORT_PIN_P046_PFC_01_A6              = (0x01U << IOPORT_PFC_OFFSET), ///< P04_6 / BSC / A6
    IOPORT_PIN_P046_PFC_02_DACK            = (0x02U << IOPORT_PFC_OFFSET), ///< P04_6 / DMAC / DACK
    IOPORT_PIN_P046_PFC_03_RTCAT1HZ        = (0x03U << IOPORT_PFC_OFFSET), ///< P04_6 / RTC / RTCAT1HZ
    IOPORT_PIN_P047_PFC_00_ETH0_TXER       = (0x00U << IOPORT_PFC_OFFSET), ///< P04_7 / ETHER_ETHn / ETH0_TXER
    IOPORT_PIN_P047_PFC_01_A5              = (0x01U << IOPORT_PFC_OFFSET), ///< P04_7 / BSC / A5
    IOPORT_PIN_P047_PFC_02_SPI_SSL21       = (0x02U << IOPORT_PFC_OFFSET), ///< P04_7 / SPIn / SPI_SSL21
    IOPORT_PIN_P050_PFC_00_IRQ12           = (0x00U << IOPORT_PFC_OFFSET), ///< P05_0 / IRQ / IRQ12
    IOPORT_PIN_P050_PFC_01_ETH1_CRS        = (0x01U << IOPORT_PFC_OFFSET), ///< P05_0 / ETHER_ETHn / ETH1_CRS
    IOPORT_PIN_P050_PFC_02_A4              = (0x02U << IOPORT_PFC_OFFSET), ///< P05_0 / BSC / A4
    IOPORT_PIN_P050_PFC_03_MTIOC4A         = (0x03U << IOPORT_PFC_OFFSET), ///< P05_0 / MTU3n / MTIOC4A
    IOPORT_PIN_P050_PFC_04_GTIOC6A         = (0x04U << IOPORT_PFC_OFFSET), ///< P05_0 / GPTn / GTIOC6A
    IOPORT_PIN_P050_PFC_05_CMTW0_TOC0      = (0x05U << IOPORT_PFC_OFFSET), ///< P05_0 / CMTWn / CMTW0_TOC0
    IOPORT_PIN_P050_PFC_06_SS5_CTS5_RTS5   = (0x06U << IOPORT_PFC_OFFSET), ///< P05_0 / SCIn / SS5_CTS5_RTS5
    IOPORT_PIN_P050_PFC_07_CANTXDP0        = (0x07U << IOPORT_PFC_OFFSET), ///< P05_0 / CANFDn / CANTXDP0
    IOPORT_PIN_P050_PFC_08_USB_VBUSEN      = (0x08U << IOPORT_PFC_OFFSET), ///< P05_0 / USB_HS / USB_VBUSEN
    IOPORT_PIN_P050_PFC_09_MCLK3           = (0x09U << IOPORT_PFC_OFFSET), ///< P05_0 / DSMIFn / MCLK3
    IOPORT_PIN_P050_PFC_0A_ENCIF11         = (0x0AU << IOPORT_PFC_OFFSET), ///< P05_0 / ENCIF / ENCIF11
    IOPORT_PIN_P051_PFC_00_IRQ13           = (0x00U << IOPORT_PFC_OFFSET), ///< P05_1 / IRQ / IRQ13
    IOPORT_PIN_P051_PFC_01_ETH1_COL        = (0x01U << IOPORT_PFC_OFFSET), ///< P05_1 / ETHER_ETHn / ETH1_COL
    IOPORT_PIN_P051_PFC_02_A3              = (0x02U << IOPORT_PFC_OFFSET), ///< P05_1 / BSC / A3
    IOPORT_PIN_P051_PFC_03_MTIOC4B         = (0x03U << IOPORT_PFC_OFFSET), ///< P05_1 / MTU3n / MTIOC4B
    IOPORT_PIN_P051_PFC_04_GTIOC6B         = (0x04U << IOPORT_PFC_OFFSET), ///< P05_1 / GPTn / GTIOC6B
    IOPORT_PIN_P051_PFC_05_CMTW0_TIC1      = (0x05U << IOPORT_PFC_OFFSET), ///< P05_1 / CMTWn / CMTW0_TIC1
    IOPORT_PIN_P051_PFC_06_CTS5            = (0x06U << IOPORT_PFC_OFFSET), ///< P05_1 / SCIn / CTS5
    IOPORT_PIN_P051_PFC_07_CANRXDP0        = (0x07U << IOPORT_PFC_OFFSET), ///< P05_1 / CANFDn / CANRXDP0
    IOPORT_PIN_P051_PFC_08_USB_EXICEN      = (0x08U << IOPORT_PFC_OFFSET), ///< P05_1 / USB_HS / USB_EXICEN
    IOPORT_PIN_P051_PFC_09_MDAT3           = (0x09U << IOPORT_PFC_OFFSET), ///< P05_1 / DSMIFn / MDAT3
    IOPORT_PIN_P051_PFC_0A_ENCIF12         = (0x0AU << IOPORT_PFC_OFFSET), ///< P05_1 / ENCIF / ENCIF12
    IOPORT_PIN_P052_PFC_00_IRQ14           = (0x00U << IOPORT_PFC_OFFSET), ///< P05_2 / IRQ / IRQ14
    IOPORT_PIN_P052_PFC_01_ETH0_CRS        = (0x01U << IOPORT_PFC_OFFSET), ///< P05_2 / ETHER_ETHn / ETH0_CRS
    IOPORT_PIN_P052_PFC_02_A2              = (0x02U << IOPORT_PFC_OFFSET), ///< P05_2 / BSC / A2
    IOPORT_PIN_P052_PFC_03_MTIOC4C         = (0x03U << IOPORT_PFC_OFFSET), ///< P05_2 / MTU3n / MTIOC4C
    IOPORT_PIN_P052_PFC_04_GTETRGSA        = (0x04U << IOPORT_PFC_OFFSET), ///< P05_2 / GPT_POEG / GTETRGSA
    IOPORT_PIN_P052_PFC_05_GTIOC7A         = (0x05U << IOPORT_PFC_OFFSET), ///< P05_2 / GPTn / GTIOC7A
    IOPORT_PIN_P052_PFC_06_CMTW0_TOC0      = (0x06U << IOPORT_PFC_OFFSET), ///< P05_2 / CMTWn / CMTW0_TOC0
    IOPORT_PIN_P052_PFC_07_DE5             = (0x07U << IOPORT_PFC_OFFSET), ///< P05_2 / SCIn / DE5
    IOPORT_PIN_P052_PFC_08_IIC_SCL1        = (0x08U << IOPORT_PFC_OFFSET), ///< P05_2 / IICn / IIC_SCL1
    IOPORT_PIN_P052_PFC_09_CANRX0          = (0x09U << IOPORT_PFC_OFFSET), ///< P05_2 / CANFDn / CANRX0
    IOPORT_PIN_P052_PFC_0A_DREQ            = (0x0AU << IOPORT_PFC_OFFSET), ///< P05_2 / DMAC / DREQ
    IOPORT_PIN_P052_PFC_0B_USB_VBUSEN      = (0x0BU << IOPORT_PFC_OFFSET), ///< P05_2 / USB_HS / USB_VBUSEN
    IOPORT_PIN_P052_PFC_0C_ENCIF13         = (0x0CU << IOPORT_PFC_OFFSET), ///< P05_2 / ENCIF / ENCIF13
    IOPORT_PIN_P053_PFC_00_IRQ15           = (0x00U << IOPORT_PFC_OFFSET), ///< P05_3 / IRQ / IRQ15
    IOPORT_PIN_P053_PFC_01_ETH0_COL        = (0x01U << IOPORT_PFC_OFFSET), ///< P05_3 / ETHER_ETHn / ETH0_COL
    IOPORT_PIN_P053_PFC_02_A1              = (0x02U << IOPORT_PFC_OFFSET), ///< P05_3 / BSC / A1
    IOPORT_PIN_P053_PFC_03_MTIOC4D         = (0x03U << IOPORT_PFC_OFFSET), ///< P05_3 / MTU3n / MTIOC4D
    IOPORT_PIN_P053_PFC_04_GTETRGSB        = (0x04U << IOPORT_PFC_OFFSET), ///< P05_3 / GPT_POEG / GTETRGSB
    IOPORT_PIN_P053_PFC_05_GTIOC7B         = (0x05U << IOPORT_PFC_OFFSET), ///< P05_3 / GPTn / GTIOC7B
    IOPORT_PIN_P053_PFC_06_POE11           = (0x06U << IOPORT_PFC_OFFSET), ///< P05_3 / MTU_POE3 / POE11
    IOPORT_PIN_P053_PFC_07_CMTW0_TIC0      = (0x07U << IOPORT_PFC_OFFSET), ///< P05_3 / CMTWn / CMTW0_TIC0
    IOPORT_PIN_P053_PFC_08_SCK4            = (0x08U << IOPORT_PFC_OFFSET), ///< P05_3 / SCIn / SCK4
    IOPORT_PIN_P053_PFC_09_IIC_SDA1        = (0x09U << IOPORT_PFC_OFFSET), ///< P05_3 / IICn / IIC_SDA1
    IOPORT_PIN_P053_PFC_0A_CANTX0          = (0x0AU << IOPORT_PFC_OFFSET), ///< P05_3 / CANFDn / CANTX0
    IOPORT_PIN_P053_PFC_0B_USB_EXICEN      = (0x0BU << IOPORT_PFC_OFFSET), ///< P05_3 / USB_HS / USB_EXICEN
    IOPORT_PIN_P053_PFC_0C_ENCIF14         = (0x0CU << IOPORT_PFC_OFFSET), ///< P05_3 / ENCIF / ENCIF14
    IOPORT_PIN_P054_PFC_00_IRQ12           = (0x00U << IOPORT_PFC_OFFSET), ///< P05_4 / IRQ / IRQ12
    IOPORT_PIN_P054_PFC_01_ETHSW_LPI0      = (0x01U << IOPORT_PFC_OFFSET), ///< P05_4 / ETHER_ETHSW / ETHSW_LPI0
    IOPORT_PIN_P054_PFC_02_A0              = (0x02U << IOPORT_PFC_OFFSET), ///< P05_4 / BSC / A0
    IOPORT_PIN_P054_PFC_03_GTIOC14A        = (0x03U << IOPORT_PFC_OFFSET), ///< P05_4 / GPTn / GTIOC14A
    IOPORT_PIN_P054_PFC_04_RXD4_SCL4_MISO4 = (0x04U << IOPORT_PFC_OFFSET), ///< P05_4 / SCIn / RXD4_SCL4_MISO4
    IOPORT_PIN_P054_PFC_05_SPI_SSL00       = (0x05U << IOPORT_PFC_OFFSET), ///< P05_4 / SPIn / SPI_SSL00
    IOPORT_PIN_P054_PFC_06_CANTXDP0        = (0x06U << IOPORT_PFC_OFFSET), ///< P05_4 / CANFDn / CANTXDP0
    IOPORT_PIN_P054_PFC_07_DACK            = (0x07U << IOPORT_PFC_OFFSET), ///< P05_4 / DMAC / DACK
    IOPORT_PIN_P054_PFC_08_USB_OVRCUR      = (0x08U << IOPORT_PFC_OFFSET), ///< P05_4 / USB_HS / USB_OVRCUR
    IOPORT_PIN_P054_PFC_09_ENCIF15         = (0x09U << IOPORT_PFC_OFFSET), ///< P05_4 / ENCIF / ENCIF15
    IOPORT_PIN_P055_PFC_00_ETHSW_PHYLINK1  = (0x00U << IOPORT_PFC_OFFSET), ///< P05_5 / ETHER_ETHSW / ETHSW_PHYLINK1
    IOPORT_PIN_P055_PFC_01_D16             = (0x01U << IOPORT_PFC_OFFSET), ///< P05_5 / BSC / D16
    IOPORT_PIN_P055_PFC_02_ESC_PHYLINK1    = (0x02U << IOPORT_PFC_OFFSET), ///< P05_5 / ETHER_ESC / ESC_PHYLINK1
    IOPORT_PIN_P055_PFC_03_GTIOC14B        = (0x03U << IOPORT_PFC_OFFSET), ///< P05_5 / GPTn / GTIOC14B
    IOPORT_PIN_P055_PFC_04_CMTW0_TOC1      = (0x04U << IOPORT_PFC_OFFSET), ///< P05_5 / CMTWn / CMTW0_TOC1
    IOPORT_PIN_P055_PFC_05_SPI_RSPCK2      = (0x05U << IOPORT_PFC_OFFSET), ///< P05_5 / SPIn / SPI_RSPCK2
    IOPORT_PIN_P056_PFC_00_IRQ12           = (0x00U << IOPORT_PFC_OFFSET), ///< P05_6 / IRQ / IRQ12
    IOPORT_PIN_P056_PFC_01_ETH1_RXER       = (0x01U << IOPORT_PFC_OFFSET), ///< P05_6 / ETHER_ETHn / ETH1_RXER
    IOPORT_PIN_P056_PFC_02_D17             = (0x02U << IOPORT_PFC_OFFSET), ///< P05_6 / BSC / D17
    IOPORT_PIN_P056_PFC_03_GTIOC15A        = (0x03U << IOPORT_PFC_OFFSET), ///< P05_6 / GPTn / GTIOC15A
    IOPORT_PIN_P056_PFC_04_CMTW1_TIC0      = (0x04U << IOPORT_PFC_OFFSET), ///< P05_6 / CMTWn / CMTW1_TIC0
    IOPORT_PIN_P056_PFC_05_SPI_SSL22       = (0x05U << IOPORT_PFC_OFFSET), ///< P05_6 / SPIn / SPI_SSL22
    IOPORT_PIN_P057_PFC_00_ETH1_TXD2       = (0x00U << IOPORT_PFC_OFFSET), ///< P05_7 / ETHER_ETHn / ETH1_TXD2
    IOPORT_PIN_P057_PFC_01_D18             = (0x01U << IOPORT_PFC_OFFSET), ///< P05_7 / BSC / D18
    IOPORT_PIN_P057_PFC_02_GTIOC15B        = (0x02U << IOPORT_PFC_OFFSET), ///< P05_7 / GPTn / GTIOC15B
    IOPORT_PIN_P057_PFC_03_CMTW1_TOC1      = (0x03U << IOPORT_PFC_OFFSET), ///< P05_7 / CMTWn / CMTW1_TOC1
    IOPORT_PIN_P057_PFC_04_TXD4_SDA4_MOSI4 = (0x04U << IOPORT_PFC_OFFSET), ///< P05_7 / SCIn / TXD4_SDA4_MOSI4
    IOPORT_PIN_P057_PFC_05_SPI_SSL23       = (0x05U << IOPORT_PFC_OFFSET), ///< P05_7 / SPIn / SPI_SSL23
    IOPORT_PIN_P060_PFC_00_ETH1_TXD3       = (0x00U << IOPORT_PFC_OFFSET), ///< P06_0 / ETHER_ETHn / ETH1_TXD3
    IOPORT_PIN_P060_PFC_01_D19             = (0x01U << IOPORT_PFC_OFFSET), ///< P06_0 / BSC / D19
    IOPORT_PIN_P060_PFC_02_GTIOC16A        = (0x02U << IOPORT_PFC_OFFSET), ///< P06_0 / GPTn / GTIOC16A
    IOPORT_PIN_P060_PFC_03_CMTW1_TOC0      = (0x03U << IOPORT_PFC_OFFSET), ///< P06_0 / CMTWn / CMTW1_TOC0
    IOPORT_PIN_P060_PFC_04_SS4_CTS4_RTS4   = (0x04U << IOPORT_PFC_OFFSET), ///< P06_0 / SCIn / SS4_CTS4_RTS4
    IOPORT_PIN_P060_PFC_05_SPI_SSL23       = (0x05U << IOPORT_PFC_OFFSET), ///< P06_0 / SPIn / SPI_SSL23
    IOPORT_PIN_P060_PFC_06_CANRX1          = (0x06U << IOPORT_PFC_OFFSET), ///< P06_0 / CANFDn / CANRX1
    IOPORT_PIN_P061_PFC_00_ETH1_REFCLK     = (0x00U << IOPORT_PFC_OFFSET), ///< P06_1 / ETHER_ETHn / ETH1_REFCLK
    IOPORT_PIN_P061_PFC_01_RMII1_REFCLK    = (0x01U << IOPORT_PFC_OFFSET), ///< P06_1 / ETHER_ETHn / RMII1_REFCLK
    IOPORT_PIN_P061_PFC_02_D22             = (0x02U << IOPORT_PFC_OFFSET), ///< P06_1 / BSC / D22
    IOPORT_PIN_P061_PFC_03_GTIOC16B        = (0x03U << IOPORT_PFC_OFFSET), ///< P06_1 / GPTn / GTIOC16B
    IOPORT_PIN_P061_PFC_04_CTS4            = (0x04U << IOPORT_PFC_OFFSET), ///< P06_1 / SCIn / CTS4
    IOPORT_PIN_P061_PFC_05_SPI_SSL22       = (0x05U << IOPORT_PFC_OFFSET), ///< P06_1 / SPIn / SPI_SSL22
    IOPORT_PIN_P061_PFC_06_CANTX1          = (0x06U << IOPORT_PFC_OFFSET), ///< P06_1 / CANFDn / CANTX1
    IOPORT_PIN_P062_PFC_00_ETH1_TXD1       = (0x00U << IOPORT_PFC_OFFSET), ///< P06_2 / ETHER_ETHn / ETH1_TXD1
    IOPORT_PIN_P062_PFC_01_D20             = (0x01U << IOPORT_PFC_OFFSET), ///< P06_2 / BSC / D20
    IOPORT_PIN_P062_PFC_02_GTIOC17A        = (0x02U << IOPORT_PFC_OFFSET), ///< P06_2 / GPTn / GTIOC17A
    IOPORT_PIN_P062_PFC_03_CANRXDP1        = (0x03U << IOPORT_PFC_OFFSET), ///< P06_2 / CANFDn / CANRXDP1
    IOPORT_PIN_P063_PFC_00_ETH1_TXD0       = (0x00U << IOPORT_PFC_OFFSET), ///< P06_3 / ETHER_ETHn / ETH1_TXD0
    IOPORT_PIN_P063_PFC_01_D23             = (0x01U << IOPORT_PFC_OFFSET), ///< P06_3 / BSC / D23
    IOPORT_PIN_P063_PFC_02_GTIOC17B        = (0x02U << IOPORT_PFC_OFFSET), ///< P06_3 / GPTn / GTIOC17B
    IOPORT_PIN_P063_PFC_03_CMTW1_TIC1      = (0x03U << IOPORT_PFC_OFFSET), ///< P06_3 / CMTWn / CMTW1_TIC1
    IOPORT_PIN_P063_PFC_04_DE4             = (0x04U << IOPORT_PFC_OFFSET), ///< P06_3 / SCIn / DE4
    IOPORT_PIN_P063_PFC_05_SPI_MISO1       = (0x05U << IOPORT_PFC_OFFSET), ///< P06_3 / SPIn / SPI_MISO1
    IOPORT_PIN_P063_PFC_06_CANTXDP1        = (0x06U << IOPORT_PFC_OFFSET), ///< P06_3 / CANFDn / CANTXDP1
    IOPORT_PIN_P064_PFC_00_ETH1_TXCLK      = (0x00U << IOPORT_PFC_OFFSET), ///< P06_4 / ETHER_ETHn / ETH1_TXCLK
    IOPORT_PIN_P064_PFC_01_D24             = (0x01U << IOPORT_PFC_OFFSET), ///< P06_4 / BSC / D24
    IOPORT_PIN_P064_PFC_02_GTIOC11A        = (0x02U << IOPORT_PFC_OFFSET), ///< P06_4 / GPTn / GTIOC11A
    IOPORT_PIN_P064_PFC_03_SPI_MOSI1       = (0x03U << IOPORT_PFC_OFFSET), ///< P06_4 / SPIn / SPI_MOSI1
    IOPORT_PIN_P065_PFC_00_ETH1_TXEN       = (0x00U << IOPORT_PFC_OFFSET), ///< P06_5 / ETHER_ETHn / ETH1_TXEN
    IOPORT_PIN_P065_PFC_01_D25             = (0x01U << IOPORT_PFC_OFFSET), ///< P06_5 / BSC / D25
    IOPORT_PIN_P065_PFC_02_GTIOC11B        = (0x02U << IOPORT_PFC_OFFSET), ///< P06_5 / GPTn / GTIOC11B
    IOPORT_PIN_P066_PFC_00_ETH1_RXD0       = (0x00U << IOPORT_PFC_OFFSET), ///< P06_6 / ETHER_ETHn / ETH1_RXD0
    IOPORT_PIN_P066_PFC_01_D21             = (0x01U << IOPORT_PFC_OFFSET), ///< P06_6 / BSC / D21
    IOPORT_PIN_P066_PFC_02_GTIOC12A        = (0x02U << IOPORT_PFC_OFFSET), ///< P06_6 / GPTn / GTIOC12A
    IOPORT_PIN_P066_PFC_03_SPI_SSL10       = (0x03U << IOPORT_PFC_OFFSET), ///< P06_6 / SPIn / SPI_SSL10
    IOPORT_PIN_P067_PFC_00_ETH1_RXD1       = (0x00U << IOPORT_PFC_OFFSET), ///< P06_7 / ETHER_ETHn / ETH1_RXD1
    IOPORT_PIN_P067_PFC_01_D26             = (0x01U << IOPORT_PFC_OFFSET), ///< P06_7 / BSC / D26
    IOPORT_PIN_P067_PFC_02_GTIOC12B        = (0x02U << IOPORT_PFC_OFFSET), ///< P06_7 / GPTn / GTIOC12B
    IOPORT_PIN_P067_PFC_03_SPI_SSL11       = (0x03U << IOPORT_PFC_OFFSET), ///< P06_7 / SPIn / SPI_SSL11
    IOPORT_PIN_P070_PFC_00_ETH1_RXD2       = (0x00U << IOPORT_PFC_OFFSET), ///< P07_0 / ETHER_ETHn / ETH1_RXD2
    IOPORT_PIN_P070_PFC_01_D27             = (0x01U << IOPORT_PFC_OFFSET), ///< P07_0 / BSC / D27
    IOPORT_PIN_P070_PFC_02_GTIOC13A        = (0x02U << IOPORT_PFC_OFFSET), ///< P07_0 / GPTn / GTIOC13A
    IOPORT_PIN_P071_PFC_00_ETH1_RXD3       = (0x00U << IOPORT_PFC_OFFSET), ///< P07_1 / ETHER_ETHn / ETH1_RXD3
    IOPORT_PIN_P071_PFC_01_D28             = (0x01U << IOPORT_PFC_OFFSET), ///< P07_1 / BSC / D28
    IOPORT_PIN_P071_PFC_02_GTIOC13B        = (0x02U << IOPORT_PFC_OFFSET), ///< P07_1 / GPTn / GTIOC13B
    IOPORT_PIN_P072_PFC_00_ETH1_RXDV       = (0x00U << IOPORT_PFC_OFFSET), ///< P07_2 / ETHER_ETHn / ETH1_RXDV
    IOPORT_PIN_P072_PFC_01_D29             = (0x01U << IOPORT_PFC_OFFSET), ///< P07_2 / BSC / D29
    IOPORT_PIN_P073_PFC_00_ETH1_RXCLK      = (0x00U << IOPORT_PFC_OFFSET), ///< P07_3 / ETHER_ETHn / ETH1_RXCLK
    IOPORT_PIN_P073_PFC_01_D30             = (0x01U << IOPORT_PFC_OFFSET), ///< P07_3 / BSC / D30
    IOPORT_PIN_P074_PFC_00_IRQ1            = (0x00U << IOPORT_PFC_OFFSET), ///< P07_4 / IRQ / IRQ1
    IOPORT_PIN_P074_PFC_01_ADTRG0          = (0x01U << IOPORT_PFC_OFFSET), ///< P07_4 / ADCn / ADTRG0
    IOPORT_PIN_P074_PFC_02_USB_VBUSIN      = (0x02U << IOPORT_PFC_OFFSET), ///< P07_4 / USB_HS / USB_VBUSIN
    IOPORT_PIN_P075_PFC_00_A21             = (0x00U << IOPORT_PFC_OFFSET), ///< P07_5 / BSC / A21
    IOPORT_PIN_P075_PFC_01_D22             = (0x01U << IOPORT_PFC_OFFSET), ///< P07_5 / BSC / D22
    IOPORT_PIN_P076_PFC_00_A22             = (0x00U << IOPORT_PFC_OFFSET), ///< P07_6 / BSC / A22
    IOPORT_PIN_P076_PFC_01_D23             = (0x01U << IOPORT_PFC_OFFSET), ///< P07_6 / BSC / D23
    IOPORT_PIN_P076_PFC_02_SPI_SSL21       = (0x02U << IOPORT_PFC_OFFSET), ///< P07_6 / SPIn / SPI_SSL21
    IOPORT_PIN_P077_PFC_00_ETHSW_LPI1      = (0x00U << IOPORT_PFC_OFFSET), ///< P07_7 / ETHER_ETHSW / ETHSW_LPI1
    IOPORT_PIN_P077_PFC_01_A23             = (0x01U << IOPORT_PFC_OFFSET), ///< P07_7 / BSC / A23
    IOPORT_PIN_P077_PFC_02_D24             = (0x02U << IOPORT_PFC_OFFSET), ///< P07_7 / BSC / D24
    IOPORT_PIN_P080_PFC_00_ETHSW_LPI0      = (0x00U << IOPORT_PFC_OFFSET), ///< P08_0 / ETHER_ETHSW / ETHSW_LPI0
    IOPORT_PIN_P080_PFC_01_A24             = (0x01U << IOPORT_PFC_OFFSET), ///< P08_0 / BSC / A24
    IOPORT_PIN_P080_PFC_02_D25             = (0x02U << IOPORT_PFC_OFFSET), ///< P08_0 / BSC / D25
    IOPORT_PIN_P081_PFC_00_ETHSW_LPI2      = (0x00U << IOPORT_PFC_OFFSET), ///< P08_1 / ETHER_ETHSW / ETHSW_LPI2
    IOPORT_PIN_P081_PFC_01_A25             = (0x01U << IOPORT_PFC_OFFSET), ///< P08_1 / BSC / A25
    IOPORT_PIN_P081_PFC_02_D26             = (0x02U << IOPORT_PFC_OFFSET), ///< P08_1 / BSC / D26
    IOPORT_PIN_P081_PFC_03_USB_VBUSEN      = (0x03U << IOPORT_PFC_OFFSET), ///< P08_1 / USB_HS / USB_VBUSEN
    IOPORT_PIN_P082_PFC_00_GMAC_PTPTRG0    = (0x00U << IOPORT_PFC_OFFSET), ///< P08_2 / ETHER_GMAC / GMAC_PTPTRG0
    IOPORT_PIN_P082_PFC_01_D27             = (0x01U << IOPORT_PFC_OFFSET), ///< P08_2 / BSC / D27
    IOPORT_PIN_P082_PFC_02_ESC_LATCH0      = (0x02U << IOPORT_PFC_OFFSET), ///< P08_2 / ETHER_ESC / ESC_LATCH0
    IOPORT_PIN_P082_PFC_03_ESC_LATCH1      = (0x03U << IOPORT_PFC_OFFSET), ///< P08_2 / ETHER_ESC / ESC_LATCH1
    IOPORT_PIN_P083_PFC_00_ETHSW_PTPOUT0   = (0x00U << IOPORT_PFC_OFFSET), ///< P08_3 / ETHER_ETHSW / ETHSW_PTPOUT0
    IOPORT_PIN_P083_PFC_01_D28             = (0x01U << IOPORT_PFC_OFFSET), ///< P08_3 / BSC / D28
    IOPORT_PIN_P083_PFC_02_ESC_SYNC0       = (0x02U << IOPORT_PFC_OFFSET), ///< P08_3 / ETHER_ESC / ESC_SYNC0
    IOPORT_PIN_P083_PFC_03_ESC_SYNC1       = (0x03U << IOPORT_PFC_OFFSET), ///< P08_3 / ETHER_ESC / ESC_SYNC1
    IOPORT_PIN_P084_PFC_00_ETH0_RXD3       = (0x00U << IOPORT_PFC_OFFSET), ///< P08_4 / ETHER_ETHn / ETH0_RXD3
    IOPORT_PIN_P084_PFC_01_D31             = (0x01U << IOPORT_PFC_OFFSET), ///< P08_4 / BSC / D31
    IOPORT_PIN_P084_PFC_02_MTIOC6A         = (0x02U << IOPORT_PFC_OFFSET), ///< P08_4 / MTU3n / MTIOC6A
    IOPORT_PIN_P085_PFC_00_ETH0_RXDV       = (0x00U << IOPORT_PFC_OFFSET), ///< P08_5 / ETHER_ETHn / ETH0_RXDV
    IOPORT_PIN_P085_PFC_01_MTIOC6B         = (0x01U << IOPORT_PFC_OFFSET), ///< P08_5 / MTU3n / MTIOC6B
    IOPORT_PIN_P086_PFC_00_ETH0_RXCLK      = (0x00U << IOPORT_PFC_OFFSET), ///< P08_6 / ETHER_ETHn / ETH0_RXCLK
    IOPORT_PIN_P086_PFC_01_MTIOC6C         = (0x01U << IOPORT_PFC_OFFSET), ///< P08_6 / MTU3n / MTIOC6C
    IOPORT_PIN_P087_PFC_00_GMAC_MDC        = (0x00U << IOPORT_PFC_OFFSET), ///< P08_7 / ETHER_GMAC / GMAC_MDC
    IOPORT_PIN_P087_PFC_01_ETHSW_MDC       = (0x01U << IOPORT_PFC_OFFSET), ///< P08_7 / ETHER_ETHSW / ETHSW_MDC
    IOPORT_PIN_P087_PFC_02_D29             = (0x02U << IOPORT_PFC_OFFSET), ///< P08_7 / BSC / D29
    IOPORT_PIN_P087_PFC_03_ESC_MDC         = (0x03U << IOPORT_PFC_OFFSET), ///< P08_7 / ETHER_ESC / ESC_MDC
    IOPORT_PIN_P087_PFC_04_MTIOC6D         = (0x04U << IOPORT_PFC_OFFSET), ///< P08_7 / MTU3n / MTIOC6D
    IOPORT_PIN_P090_PFC_00_GMAC_MDIO       = (0x00U << IOPORT_PFC_OFFSET), ///< P09_0 / ETHER_GMAC / GMAC_MDIO
    IOPORT_PIN_P090_PFC_01_ETHSW_MDIO      = (0x01U << IOPORT_PFC_OFFSET), ///< P09_0 / ETHER_ETHSW / ETHSW_MDIO
    IOPORT_PIN_P090_PFC_02_D30             = (0x02U << IOPORT_PFC_OFFSET), ///< P09_0 / BSC / D30
    IOPORT_PIN_P090_PFC_03_ESC_MDIO        = (0x03U << IOPORT_PFC_OFFSET), ///< P09_0 / ETHER_ESC / ESC_MDIO
    IOPORT_PIN_P090_PFC_04_MTIOC7A         = (0x04U << IOPORT_PFC_OFFSET), ///< P09_0 / MTU3n / MTIOC7A
    IOPORT_PIN_P091_PFC_00_ETH0_REFCLK     = (0x00U << IOPORT_PFC_OFFSET), ///< P09_1 / ETHER_ETHn / ETH0_REFCLK
    IOPORT_PIN_P091_PFC_01_RMII0_REFCLK    = (0x01U << IOPORT_PFC_OFFSET), ///< P09_1 / ETHER_ETHn / RMII0_REFCLK
    IOPORT_PIN_P091_PFC_02_MTIOC7B         = (0x02U << IOPORT_PFC_OFFSET), ///< P09_1 / MTU3n / MTIOC7B
    IOPORT_PIN_P092_PFC_00_IRQ0            = (0x00U << IOPORT_PFC_OFFSET), ///< P09_2 / IRQ / IRQ0
    IOPORT_PIN_P092_PFC_01_ETH0_RXER       = (0x01U << IOPORT_PFC_OFFSET), ///< P09_2 / ETHER_ETHn / ETH0_RXER
    IOPORT_PIN_P092_PFC_02_D31             = (0x02U << IOPORT_PFC_OFFSET), ///< P09_2 / BSC / D31
    IOPORT_PIN_P092_PFC_03_MTIOC7C         = (0x03U << IOPORT_PFC_OFFSET), ///< P09_2 / MTU3n / MTIOC7C
    IOPORT_PIN_P093_PFC_00_ETH0_TXD3       = (0x00U << IOPORT_PFC_OFFSET), ///< P09_3 / ETHER_ETHn / ETH0_TXD3
    IOPORT_PIN_P093_PFC_01_MTIOC7D         = (0x01U << IOPORT_PFC_OFFSET), ///< P09_3 / MTU3n / MTIOC7D
    IOPORT_PIN_P094_PFC_00_ETH0_TXD2       = (0x00U << IOPORT_PFC_OFFSET), ///< P09_4 / ETHER_ETHn / ETH0_TXD2
    IOPORT_PIN_P095_PFC_00_ETH0_TXD1       = (0x00U << IOPORT_PFC_OFFSET), ///< P09_5 / ETHER_ETHn / ETH0_TXD1
    IOPORT_PIN_P096_PFC_00_ETH0_TXD0       = (0x00U << IOPORT_PFC_OFFSET), ///< P09_6 / ETHER_ETHn / ETH0_TXD0
    IOPORT_PIN_P097_PFC_00_ETH0_TXCLK      = (0x00U << IOPORT_PFC_OFFSET), ///< P09_7 / ETHER_ETHn / ETH0_TXCLK
    IOPORT_PIN_P100_PFC_00_ETH0_TXEN       = (0x00U << IOPORT_PFC_OFFSET), ///< P10_0 / ETHER_ETHn / ETH0_TXEN
    IOPORT_PIN_P101_PFC_00_ETH0_RXD0       = (0x00U << IOPORT_PFC_OFFSET), ///< P10_1 / ETHER_ETHn / ETH0_RXD0
    IOPORT_PIN_P102_PFC_00_ETH0_RXD1       = (0x00U << IOPORT_PFC_OFFSET), ///< P10_2 / ETHER_ETHn / ETH0_RXD1
    IOPORT_PIN_P103_PFC_00_ETH0_RXD2       = (0x00U << IOPORT_PFC_OFFSET), ///< P10_3 / ETHER_ETHn / ETH0_RXD2
    IOPORT_PIN_P103_PFC_01_RTCAT1HZ        = (0x01U << IOPORT_PFC_OFFSET), ///< P10_3 / RTC / RTCAT1HZ
    IOPORT_PIN_P104_PFC_00_IRQ11           = (0x00U << IOPORT_PFC_OFFSET), ///< P10_4 / IRQ / IRQ11
    IOPORT_PIN_P104_PFC_01_ETHSW_PHYLINK0  = (0x01U << IOPORT_PFC_OFFSET), ///< P10_4 / ETHER_ETHSW / ETHSW_PHYLINK0
    IOPORT_PIN_P104_PFC_02_WE2_DQMUL       = (0x02U << IOPORT_PFC_OFFSET), ///< P10_4 / BSC / WE2_DQMUL
    IOPORT_PIN_P104_PFC_03_ESC_PHYLINK0    = (0x03U << IOPORT_PFC_OFFSET), ///< P10_4 / ETHER_ESC / ESC_PHYLINK0
    IOPORT_PIN_P105_PFC_00_IRQ2            = (0x00U << IOPORT_PFC_OFFSET), ///< P10_5 / IRQ / IRQ2
    IOPORT_PIN_P105_PFC_01_ETH2_CRS        = (0x01U << IOPORT_PFC_OFFSET), ///< P10_5 / ETHER_ETHn / ETH2_CRS
    IOPORT_PIN_P106_PFC_00_XSPI1_INT1      = (0x00U << IOPORT_PFC_OFFSET), ///< P10_6 / XSPIn / XSPI1_INT1
    IOPORT_PIN_P106_PFC_01_ETH2_COL        = (0x01U << IOPORT_PFC_OFFSET), ///< P10_6 / ETHER_ETHn / ETH2_COL
    IOPORT_PIN_P107_PFC_00_XSPI1_INT0      = (0x00U << IOPORT_PFC_OFFSET), ///< P10_7 / XSPIn / XSPI1_INT0
    IOPORT_PIN_P107_PFC_01_ETH2_TXER       = (0x01U << IOPORT_PFC_OFFSET), ///< P10_7 / ETHER_ETHn / ETH2_TXER
    IOPORT_PIN_P110_PFC_00_XSPI1_ECS1      = (0x00U << IOPORT_PFC_OFFSET), ///< P11_0 / XSPIn / XSPI1_ECS1
    IOPORT_PIN_P110_PFC_01_ETH1_CRS        = (0x01U << IOPORT_PFC_OFFSET), ///< P11_0 / ETHER_ETHn / ETH1_CRS
    IOPORT_PIN_P111_PFC_00_XSPI1_WP1       = (0x00U << IOPORT_PFC_OFFSET), ///< P11_1 / XSPIn / XSPI1_WP1
    IOPORT_PIN_P111_PFC_01_ETH1_COL        = (0x01U << IOPORT_PFC_OFFSET), ///< P11_1 / ETHER_ETHn / ETH1_COL
    IOPORT_PIN_P111_PFC_02_MTIOC1A         = (0x02U << IOPORT_PFC_OFFSET), ///< P11_1 / MTU3n / MTIOC1A
    IOPORT_PIN_P111_PFC_03_GTIOC11A        = (0x03U << IOPORT_PFC_OFFSET), ///< P11_1 / GPTn / GTIOC11A
    IOPORT_PIN_P112_PFC_00_XSPI1_WP0       = (0x00U << IOPORT_PFC_OFFSET), ///< P11_2 / XSPIn / XSPI1_WP0
    IOPORT_PIN_P112_PFC_01_ETH1_TXER       = (0x01U << IOPORT_PFC_OFFSET), ///< P11_2 / ETHER_ETHn / ETH1_TXER
    IOPORT_PIN_P112_PFC_02_MTIOC1B         = (0x02U << IOPORT_PFC_OFFSET), ///< P11_2 / MTU3n / MTIOC1B
    IOPORT_PIN_P112_PFC_03_GTIOC11B        = (0x03U << IOPORT_PFC_OFFSET), ///< P11_2 / GPTn / GTIOC11B
    IOPORT_PIN_P113_PFC_00_XSPI1_ECS0      = (0x00U << IOPORT_PFC_OFFSET), ///< P11_3 / XSPIn / XSPI1_ECS0
    IOPORT_PIN_P113_PFC_01_ETH0_TXER       = (0x01U << IOPORT_PFC_OFFSET), ///< P11_3 / ETHER_ETHn / ETH0_TXER
    IOPORT_PIN_P113_PFC_02_MTIOC2A         = (0x02U << IOPORT_PFC_OFFSET), ///< P11_3 / MTU3n / MTIOC2A
    IOPORT_PIN_P113_PFC_03_GTIOC12A        = (0x03U << IOPORT_PFC_OFFSET), ///< P11_3 / GPTn / GTIOC12A
    IOPORT_PIN_P114_PFC_00_XSPI1_RSTO1     = (0x00U << IOPORT_PFC_OFFSET), ///< P11_4 / XSPIn / XSPI1_RSTO1
    IOPORT_PIN_P114_PFC_01_ETH0_CRS        = (0x01U << IOPORT_PFC_OFFSET), ///< P11_4 / ETHER_ETHn / ETH0_CRS
    IOPORT_PIN_P114_PFC_02_MTIOC2B         = (0x02U << IOPORT_PFC_OFFSET), ///< P11_4 / MTU3n / MTIOC2B
    IOPORT_PIN_P114_PFC_03_GTIOC12B        = (0x03U << IOPORT_PFC_OFFSET), ///< P11_4 / GPTn / GTIOC12B
    IOPORT_PIN_P115_PFC_00_XSPI1_RSTO0     = (0x00U << IOPORT_PFC_OFFSET), ///< P11_5 / XSPIn / XSPI1_RSTO0
    IOPORT_PIN_P115_PFC_01_MTIOC0B         = (0x01U << IOPORT_PFC_OFFSET), ///< P11_5 / MTU3n / MTIOC0B
    IOPORT_PIN_P115_PFC_02_ENCIF0          = (0x02U << IOPORT_PFC_OFFSET), ///< P11_5 / ENCIF / ENCIF0
    IOPORT_PIN_P116_PFC_00_XSPI1_RESET1    = (0x00U << IOPORT_PFC_OFFSET), ///< P11_6 / XSPIn / XSPI1_RESET1
    IOPORT_PIN_P116_PFC_01_ETH0_COL        = (0x01U << IOPORT_PFC_OFFSET), ///< P11_6 / ETHER_ETHn / ETH0_COL
    IOPORT_PIN_P116_PFC_02_MTIOC8C         = (0x02U << IOPORT_PFC_OFFSET), ///< P11_6 / MTU3n / MTIOC8C
    IOPORT_PIN_P116_PFC_03_ENCIF1          = (0x03U << IOPORT_PFC_OFFSET), ///< P11_6 / ENCIF / ENCIF1
    IOPORT_PIN_P117_PFC_00_XSPI1_DS        = (0x00U << IOPORT_PFC_OFFSET), ///< P11_7 / XSPIn / XSPI1_DS
    IOPORT_PIN_P117_PFC_01_MTIOC8D         = (0x01U << IOPORT_PFC_OFFSET), ///< P11_7 / MTU3n / MTIOC8D
    IOPORT_PIN_P117_PFC_02_USB_OVRCUR      = (0x02U << IOPORT_PFC_OFFSET), ///< P11_7 / USB_HS / USB_OVRCUR
    IOPORT_PIN_P117_PFC_03_ENCIF2          = (0x03U << IOPORT_PFC_OFFSET), ///< P11_7 / ENCIF / ENCIF2
    IOPORT_PIN_P120_PFC_00_XSPI1_IO7       = (0x00U << IOPORT_PFC_OFFSET), ///< P12_0 / XSPIn / XSPI1_IO7
    IOPORT_PIN_P120_PFC_01_GTADSMP1        = (0x01U << IOPORT_PFC_OFFSET), ///< P12_0 / GPT / GTADSMP1
    IOPORT_PIN_P120_PFC_02_ENCIF3          = (0x02U << IOPORT_PFC_OFFSET), ///< P12_0 / ENCIF / ENCIF3
    IOPORT_PIN_P121_PFC_00_XSPI1_IO6       = (0x00U << IOPORT_PFC_OFFSET), ///< P12_1 / XSPIn / XSPI1_IO6
    IOPORT_PIN_P121_PFC_01_GTADSML0        = (0x01U << IOPORT_PFC_OFFSET), ///< P12_1 / GPT / GTADSML0
    IOPORT_PIN_P121_PFC_02_ENCIF4          = (0x02U << IOPORT_PFC_OFFSET), ///< P12_1 / ENCIF / ENCIF4
    IOPORT_PIN_P122_PFC_00_XSPI1_IO5       = (0x00U << IOPORT_PFC_OFFSET), ///< P12_2 / XSPIn / XSPI1_IO5
    IOPORT_PIN_P122_PFC_01_GTADSML1        = (0x01U << IOPORT_PFC_OFFSET), ///< P12_2 / GPT / GTADSML1
    IOPORT_PIN_P122_PFC_02_ENCIF5          = (0x02U << IOPORT_PFC_OFFSET), ///< P12_2 / ENCIF / ENCIF5
    IOPORT_PIN_P123_PFC_00_XSPI1_IO4       = (0x00U << IOPORT_PFC_OFFSET), ///< P12_3 / XSPIn / XSPI1_IO4
    IOPORT_PIN_P123_PFC_01_GTADSMP0        = (0x01U << IOPORT_PFC_OFFSET), ///< P12_3 / GPT / GTADSMP0
    IOPORT_PIN_P123_PFC_02_ENCIF6          = (0x02U << IOPORT_PFC_OFFSET), ///< P12_3 / ENCIF / ENCIF6
    IOPORT_PIN_P124_PFC_00_XSPI1_RESET0    = (0x00U << IOPORT_PFC_OFFSET), ///< P12_4 / XSPIn / XSPI1_RESET0
    IOPORT_PIN_P124_PFC_01_ETH1_CRS        = (0x01U << IOPORT_PFC_OFFSET), ///< P12_4 / ETHER_ETHn / ETH1_CRS
    IOPORT_PIN_P124_PFC_02_TRACEDATA0      = (0x02U << IOPORT_PFC_OFFSET), ///< P12_4 / TRACE / TRACEDATA0
    IOPORT_PIN_P124_PFC_03_D15             = (0x03U << IOPORT_PFC_OFFSET), ///< P12_4 / BSC / D15
    IOPORT_PIN_P124_PFC_04_MTIOC8B         = (0x04U << IOPORT_PFC_OFFSET), ///< P12_4 / MTU3n / MTIOC8B
    IOPORT_PIN_P124_PFC_05_GTIOC8B         = (0x05U << IOPORT_PFC_OFFSET), ///< P12_4 / GPTn / GTIOC8B
    IOPORT_PIN_P124_PFC_06_SPI_SSL01       = (0x06U << IOPORT_PFC_OFFSET), ///< P12_4 / SPIn / SPI_SSL01
    IOPORT_PIN_P124_PFC_07_ENCIF7          = (0x07U << IOPORT_PFC_OFFSET), ///< P12_4 / ENCIF / ENCIF7
    IOPORT_PIN_P125_PFC_00_XSPI1_IO3       = (0x00U << IOPORT_PFC_OFFSET), ///< P12_5 / XSPIn / XSPI1_IO3
    IOPORT_PIN_P125_PFC_01_TRACEDATA1      = (0x01U << IOPORT_PFC_OFFSET), ///< P12_5 / TRACE / TRACEDATA1
    IOPORT_PIN_P125_PFC_02_D14             = (0x02U << IOPORT_PFC_OFFSET), ///< P12_5 / BSC / D14
    IOPORT_PIN_P125_PFC_03_MTIOC8A         = (0x03U << IOPORT_PFC_OFFSET), ///< P12_5 / MTU3n / MTIOC8A
    IOPORT_PIN_P125_PFC_04_GTIOC8A         = (0x04U << IOPORT_PFC_OFFSET), ///< P12_5 / GPTn / GTIOC8A
    IOPORT_PIN_P125_PFC_05_SPI_SSL03       = (0x05U << IOPORT_PFC_OFFSET), ///< P12_5 / SPIn / SPI_SSL03
    IOPORT_PIN_P125_PFC_06_DACK            = (0x06U << IOPORT_PFC_OFFSET), ///< P12_5 / DMAC / DACK
    IOPORT_PIN_P125_PFC_07_ENCIF0          = (0x07U << IOPORT_PFC_OFFSET), ///< P12_5 / ENCIF / ENCIF0
    IOPORT_PIN_P126_PFC_00_IRQ3            = (0x00U << IOPORT_PFC_OFFSET), ///< P12_6 / IRQ / IRQ3
    IOPORT_PIN_P126_PFC_01_XSPI1_IO2       = (0x01U << IOPORT_PFC_OFFSET), ///< P12_6 / XSPIn / XSPI1_IO2
    IOPORT_PIN_P126_PFC_02_TRACEDATA2      = (0x02U << IOPORT_PFC_OFFSET), ///< P12_6 / TRACE / TRACEDATA2
    IOPORT_PIN_P126_PFC_03_D13             = (0x03U << IOPORT_PFC_OFFSET), ///< P12_6 / BSC / D13
    IOPORT_PIN_P126_PFC_04_MTCLKA          = (0x04U << IOPORT_PFC_OFFSET), ///< P12_6 / MTU3 / MTCLKA
    IOPORT_PIN_P126_PFC_05_DE1             = (0x05U << IOPORT_PFC_OFFSET), ///< P12_6 / SCIn / DE1
    IOPORT_PIN_P126_PFC_06_SPI_SSL02       = (0x06U << IOPORT_PFC_OFFSET), ///< P12_6 / SPIn / SPI_SSL02
    IOPORT_PIN_P126_PFC_07_MCLK5           = (0x07U << IOPORT_PFC_OFFSET), ///< P12_6 / DSMIFn / MCLK5
    IOPORT_PIN_P126_PFC_08_ENCIF1          = (0x08U << IOPORT_PFC_OFFSET), ///< P12_6 / ENCIF / ENCIF1
    IOPORT_PIN_P127_PFC_00_IRQ4            = (0x00U << IOPORT_PFC_OFFSET), ///< P12_7 / IRQ / IRQ4
    IOPORT_PIN_P127_PFC_01_XSPI1_IO1       = (0x01U << IOPORT_PFC_OFFSET), ///< P12_7 / XSPIn / XSPI1_IO1
    IOPORT_PIN_P127_PFC_02_TRACEDATA3      = (0x02U << IOPORT_PFC_OFFSET), ///< P12_7 / TRACE / TRACEDATA3
    IOPORT_PIN_P127_PFC_03_D12             = (0x03U << IOPORT_PFC_OFFSET), ///< P12_7 / BSC / D12
    IOPORT_PIN_P127_PFC_04_MTCLKB          = (0x04U << IOPORT_PFC_OFFSET), ///< P12_7 / MTU3 / MTCLKB
    IOPORT_PIN_P127_PFC_05_MTCLKC          = (0x05U << IOPORT_PFC_OFFSET), ///< P12_7 / MTU3 / MTCLKC
    IOPORT_PIN_P127_PFC_06_SCK1            = (0x06U << IOPORT_PFC_OFFSET), ///< P12_7 / SCIn / SCK1
    IOPORT_PIN_P127_PFC_07_SPI_SSL01       = (0x07U << IOPORT_PFC_OFFSET), ///< P12_7 / SPIn / SPI_SSL01
    IOPORT_PIN_P127_PFC_08_MDAT5           = (0x08U << IOPORT_PFC_OFFSET), ///< P12_7 / DSMIFn / MDAT5
    IOPORT_PIN_P127_PFC_09_ENCIF2          = (0x09U << IOPORT_PFC_OFFSET), ///< P12_7 / ENCIF / ENCIF2
    IOPORT_PIN_P130_PFC_00_XSPI1_IO0       = (0x00U << IOPORT_PFC_OFFSET), ///< P13_0 / XSPIn / XSPI1_IO0
    IOPORT_PIN_P130_PFC_01_TRACEDATA4      = (0x01U << IOPORT_PFC_OFFSET), ///< P13_0 / TRACE / TRACEDATA4
    IOPORT_PIN_P130_PFC_02_D11             = (0x02U << IOPORT_PFC_OFFSET), ///< P13_0 / BSC / D11
    IOPORT_PIN_P130_PFC_03_MTCLKC          = (0x03U << IOPORT_PFC_OFFSET), ///< P13_0 / MTU3 / MTCLKC
    IOPORT_PIN_P130_PFC_04_MTCLKB          = (0x04U << IOPORT_PFC_OFFSET), ///< P13_0 / MTU3 / MTCLKB
    IOPORT_PIN_P130_PFC_05_GTIOC9A         = (0x05U << IOPORT_PFC_OFFSET), ///< P13_0 / GPTn / GTIOC9A
    IOPORT_PIN_P130_PFC_06_RXD1_SCL1_MISO1 = (0x06U << IOPORT_PFC_OFFSET), ///< P13_0 / SCIn / RXD1_SCL1_MISO1
    IOPORT_PIN_P130_PFC_07_SPI_SSL00       = (0x07U << IOPORT_PFC_OFFSET), ///< P13_0 / SPIn / SPI_SSL00
    IOPORT_PIN_P130_PFC_08_MCLK0           = (0x08U << IOPORT_PFC_OFFSET), ///< P13_0 / DSMIFn / MCLK0
    IOPORT_PIN_P130_PFC_09_ENCIF3          = (0x09U << IOPORT_PFC_OFFSET), ///< P13_0 / ENCIF / ENCIF3
    IOPORT_PIN_P131_PFC_00_XSPI1_CS0       = (0x00U << IOPORT_PFC_OFFSET), ///< P13_1 / XSPIn / XSPI1_CS0
    IOPORT_PIN_P131_PFC_01_TRACEDATA5      = (0x01U << IOPORT_PFC_OFFSET), ///< P13_1 / TRACE / TRACEDATA5
    IOPORT_PIN_P131_PFC_02_D10             = (0x02U << IOPORT_PFC_OFFSET), ///< P13_1 / BSC / D10
    IOPORT_PIN_P131_PFC_03_MTCLKD          = (0x03U << IOPORT_PFC_OFFSET), ///< P13_1 / MTU3 / MTCLKD
    IOPORT_PIN_P131_PFC_04_GTIOC9B         = (0x04U << IOPORT_PFC_OFFSET), ///< P13_1 / GPTn / GTIOC9B
    IOPORT_PIN_P131_PFC_05_TXD1_SDA1_MOSI1 = (0x05U << IOPORT_PFC_OFFSET), ///< P13_1 / SCIn / TXD1_SDA1_MOSI1
    IOPORT_PIN_P131_PFC_06_SPI_MOSI0       = (0x06U << IOPORT_PFC_OFFSET), ///< P13_1 / SPIn / SPI_MOSI0
    IOPORT_PIN_P131_PFC_07_MDAT0           = (0x07U << IOPORT_PFC_OFFSET), ///< P13_1 / DSMIFn / MDAT0
    IOPORT_PIN_P131_PFC_08_ENCIF4          = (0x08U << IOPORT_PFC_OFFSET), ///< P13_1 / ENCIF / ENCIF4
    IOPORT_PIN_P132_PFC_00_IRQ5            = (0x00U << IOPORT_PFC_OFFSET), ///< P13_2 / IRQ / IRQ5
    IOPORT_PIN_P132_PFC_01_XSPI1_CS1       = (0x01U << IOPORT_PFC_OFFSET), ///< P13_2 / XSPIn / XSPI1_CS1
    IOPORT_PIN_P132_PFC_02_ETHSW_PTPOUT2   = (0x02U << IOPORT_PFC_OFFSET), ///< P13_2 / ETHER_ETHSW / ETHSW_PTPOUT2
    IOPORT_PIN_P132_PFC_03_TRACEDATA6      = (0x03U << IOPORT_PFC_OFFSET), ///< P13_2 / TRACE / TRACEDATA6
    IOPORT_PIN_P132_PFC_04_D9              = (0x04U << IOPORT_PFC_OFFSET), ///< P13_2 / BSC / D9
    IOPORT_PIN_P132_PFC_05_ESC_I2CCLK      = (0x05U << IOPORT_PFC_OFFSET), ///< P13_2 / ETHER_ESC / ESC_I2CCLK
    IOPORT_PIN_P132_PFC_06_MTIOC0A         = (0x06U << IOPORT_PFC_OFFSET), ///< P13_2 / MTU3n / MTIOC0A
    IOPORT_PIN_P132_PFC_07_GTIOC10A        = (0x07U << IOPORT_PFC_OFFSET), ///< P13_2 / GPTn / GTIOC10A
    IOPORT_PIN_P132_PFC_08_POE8            = (0x08U << IOPORT_PFC_OFFSET), ///< P13_2 / MTU_POE3 / POE8
    IOPORT_PIN_P132_PFC_09_SS1_CTS1_RTS1   = (0x09U << IOPORT_PFC_OFFSET), ///< P13_2 / SCIn / SS1_CTS1_RTS1
    IOPORT_PIN_P132_PFC_0A_SPI_MISO0       = (0x0AU << IOPORT_PFC_OFFSET), ///< P13_2 / SPIn / SPI_MISO0
    IOPORT_PIN_P132_PFC_0B_IIC_SCL0        = (0x0BU << IOPORT_PFC_OFFSET), ///< P13_2 / IICn / IIC_SCL0
    IOPORT_PIN_P132_PFC_0C_MCLK4           = (0x0CU << IOPORT_PFC_OFFSET), ///< P13_2 / DSMIFn / MCLK4
    IOPORT_PIN_P132_PFC_0D_ENCIF8          = (0x0DU << IOPORT_PFC_OFFSET), ///< P13_2 / ENCIF / ENCIF8
    IOPORT_PIN_P133_PFC_00_XSPI1_CKP       = (0x00U << IOPORT_PFC_OFFSET), ///< P13_3 / XSPIn / XSPI1_CKP
    IOPORT_PIN_P133_PFC_01_ETHSW_PTPOUT3   = (0x01U << IOPORT_PFC_OFFSET), ///< P13_3 / ETHER_ETHSW / ETHSW_PTPOUT3
    IOPORT_PIN_P133_PFC_02_TRACEDATA7      = (0x02U << IOPORT_PFC_OFFSET), ///< P13_3 / TRACE / TRACEDATA7
    IOPORT_PIN_P133_PFC_03_D8              = (0x03U << IOPORT_PFC_OFFSET), ///< P13_3 / BSC / D8
    IOPORT_PIN_P133_PFC_04_ESC_I2CDATA     = (0x04U << IOPORT_PFC_OFFSET), ///< P13_3 / ETHER_ESC / ESC_I2CDATA
    IOPORT_PIN_P133_PFC_05_MTIOC0C         = (0x05U << IOPORT_PFC_OFFSET), ///< P13_3 / MTU3n / MTIOC0C
    IOPORT_PIN_P133_PFC_06_MTIOC0B         = (0x06U << IOPORT_PFC_OFFSET), ///< P13_3 / MTU3n / MTIOC0B
    IOPORT_PIN_P133_PFC_07_GTIOC10B        = (0x07U << IOPORT_PFC_OFFSET), ///< P13_3 / GPTn / GTIOC10B
    IOPORT_PIN_P133_PFC_08_CMTW1_TOC0      = (0x08U << IOPORT_PFC_OFFSET), ///< P13_3 / CMTWn / CMTW1_TOC0
    IOPORT_PIN_P133_PFC_09_CTS1            = (0x09U << IOPORT_PFC_OFFSET), ///< P13_3 / SCIn / CTS1
    IOPORT_PIN_P133_PFC_0A_SPI_RSPCK0      = (0x0AU << IOPORT_PFC_OFFSET), ///< P13_3 / SPIn / SPI_RSPCK0
    IOPORT_PIN_P133_PFC_0B_IIC_SDA0        = (0x0BU << IOPORT_PFC_OFFSET), ///< P13_3 / IICn / IIC_SDA0
    IOPORT_PIN_P133_PFC_0C_MDAT4           = (0x0CU << IOPORT_PFC_OFFSET), ///< P13_3 / DSMIFn / MDAT4
    IOPORT_PIN_P133_PFC_0D_ENCIF9          = (0x0DU << IOPORT_PFC_OFFSET), ///< P13_3 / ENCIF / ENCIF9
    IOPORT_PIN_P134_PFC_00_XSPI1_CKN       = (0x00U << IOPORT_PFC_OFFSET), ///< P13_4 / XSPIn / XSPI1_CKN
    IOPORT_PIN_P134_PFC_01_ESC_RESETOUT    = (0x01U << IOPORT_PFC_OFFSET), ///< P13_4 / ETHER_ESC / ESC_RESETOUT
    IOPORT_PIN_P134_PFC_02_MTIOC0D         = (0x02U << IOPORT_PFC_OFFSET), ///< P13_4 / MTU3n / MTIOC0D
    IOPORT_PIN_P134_PFC_03_GTIOC8B         = (0x03U << IOPORT_PFC_OFFSET), ///< P13_4 / GPTn / GTIOC8B
    IOPORT_PIN_P134_PFC_04_ENCIF10         = (0x04U << IOPORT_PFC_OFFSET), ///< P13_4 / ENCIF / ENCIF10
    IOPORT_PIN_P135_PFC_00_XSPI0_WP1       = (0x00U << IOPORT_PFC_OFFSET), ///< P13_5 / XSPIn / XSPI0_WP1
    IOPORT_PIN_P135_PFC_01_GMAC_PTPTRG0    = (0x01U << IOPORT_PFC_OFFSET), ///< P13_5 / ETHER_GMAC / GMAC_PTPTRG0
    IOPORT_PIN_P135_PFC_02_ESC_LATCH0      = (0x02U << IOPORT_PFC_OFFSET), ///< P13_5 / ETHER_ESC / ESC_LATCH0
    IOPORT_PIN_P135_PFC_03_ESC_LATCH1      = (0x03U << IOPORT_PFC_OFFSET), ///< P13_5 / ETHER_ESC / ESC_LATCH1
    IOPORT_PIN_P135_PFC_04_MTCLKA          = (0x04U << IOPORT_PFC_OFFSET), ///< P13_5 / MTU3 / MTCLKA
    IOPORT_PIN_P135_PFC_05_SPI_RSPCK1      = (0x05U << IOPORT_PFC_OFFSET), ///< P13_5 / SPIn / SPI_RSPCK1
    IOPORT_PIN_P136_PFC_00_XSPI0_WP0       = (0x00U << IOPORT_PFC_OFFSET), ///< P13_6 / XSPIn / XSPI0_WP0
    IOPORT_PIN_P136_PFC_01_ETHSW_PTPOUT0   = (0x01U << IOPORT_PFC_OFFSET), ///< P13_6 / ETHER_ETHSW / ETHSW_PTPOUT0
    IOPORT_PIN_P136_PFC_02_ESC_SYNC0       = (0x02U << IOPORT_PFC_OFFSET), ///< P13_6 / ETHER_ESC / ESC_SYNC0
    IOPORT_PIN_P136_PFC_03_ESC_SYNC1       = (0x03U << IOPORT_PFC_OFFSET), ///< P13_6 / ETHER_ESC / ESC_SYNC1
    IOPORT_PIN_P136_PFC_04_MTCLKB          = (0x04U << IOPORT_PFC_OFFSET), ///< P13_6 / MTU3 / MTCLKB
    IOPORT_PIN_P137_PFC_00_XSPI0_ECS1      = (0x00U << IOPORT_PFC_OFFSET), ///< P13_7 / XSPIn / XSPI0_ECS1
    IOPORT_PIN_P137_PFC_01_GMAC_PTPTRG1    = (0x01U << IOPORT_PFC_OFFSET), ///< P13_7 / ETHER_GMAC / GMAC_PTPTRG1
    IOPORT_PIN_P137_PFC_02_ESC_LATCH1      = (0x02U << IOPORT_PFC_OFFSET), ///< P13_7 / ETHER_ESC / ESC_LATCH1
    IOPORT_PIN_P137_PFC_03_ESC_LATCH0      = (0x03U << IOPORT_PFC_OFFSET), ///< P13_7 / ETHER_ESC / ESC_LATCH0
    IOPORT_PIN_P137_PFC_04_MTCLKC          = (0x04U << IOPORT_PFC_OFFSET), ///< P13_7 / MTU3 / MTCLKC
    IOPORT_PIN_P140_PFC_00_XSPI0_INT0      = (0x00U << IOPORT_PFC_OFFSET), ///< P14_0 / XSPIn / XSPI0_INT0
    IOPORT_PIN_P140_PFC_01_ETHSW_PTPOUT1   = (0x01U << IOPORT_PFC_OFFSET), ///< P14_0 / ETHER_ETHSW / ETHSW_PTPOUT1
    IOPORT_PIN_P140_PFC_02_ESC_SYNC1       = (0x02U << IOPORT_PFC_OFFSET), ///< P14_0 / ETHER_ESC / ESC_SYNC1
    IOPORT_PIN_P140_PFC_03_ESC_SYNC0       = (0x03U << IOPORT_PFC_OFFSET), ///< P14_0 / ETHER_ESC / ESC_SYNC0
    IOPORT_PIN_P140_PFC_04_MTCLKD          = (0x04U << IOPORT_PFC_OFFSET), ///< P14_0 / MTU3 / MTCLKD
    IOPORT_PIN_P141_PFC_00_XSPI0_INT1      = (0x00U << IOPORT_PFC_OFFSET), ///< P14_1 / XSPIn / XSPI0_INT1
    IOPORT_PIN_P141_PFC_01_ETH1_COL        = (0x01U << IOPORT_PFC_OFFSET), ///< P14_1 / ETHER_ETHn / ETH1_COL
    IOPORT_PIN_P141_PFC_03_MTIOC8A         = (0x03U << IOPORT_PFC_OFFSET), ///< P14_1 / MTU3n / MTIOC8A
    IOPORT_PIN_P141_PFC_04_GTIOC8A         = (0x04U << IOPORT_PFC_OFFSET), ///< P14_1 / GPTn / GTIOC8A
    IOPORT_PIN_P141_PFC_05_ENCIF11         = (0x05U << IOPORT_PFC_OFFSET), ///< P14_1 / ENCIF / ENCIF11
    IOPORT_PIN_P142_PFC_00_IRQ6            = (0x00U << IOPORT_PFC_OFFSET), ///< P14_2 / IRQ / IRQ6
    IOPORT_PIN_P142_PFC_01_XSPI0_ECS0      = (0x01U << IOPORT_PFC_OFFSET), ///< P14_2 / XSPIn / XSPI0_ECS0
    IOPORT_PIN_P142_PFC_02_ETH0_CRS        = (0x02U << IOPORT_PFC_OFFSET), ///< P14_2 / ETHER_ETHn / ETH0_CRS
    IOPORT_PIN_P142_PFC_04_MTIOC8B         = (0x04U << IOPORT_PFC_OFFSET), ///< P14_2 / MTU3n / MTIOC8B
    IOPORT_PIN_P142_PFC_05_GTIOC8B         = (0x05U << IOPORT_PFC_OFFSET), ///< P14_2 / GPTn / GTIOC8B
    IOPORT_PIN_P142_PFC_06_ENCIF12         = (0x06U << IOPORT_PFC_OFFSET), ///< P14_2 / ENCIF / ENCIF12
    IOPORT_PIN_P143_PFC_00_XSPI0_RSTO1     = (0x00U << IOPORT_PFC_OFFSET), ///< P14_3 / XSPIn / XSPI0_RSTO1
    IOPORT_PIN_P143_PFC_01_ETH0_COL        = (0x01U << IOPORT_PFC_OFFSET), ///< P14_3 / ETHER_ETHn / ETH0_COL
    IOPORT_PIN_P143_PFC_04_MTIOC0A         = (0x04U << IOPORT_PFC_OFFSET), ///< P14_3 / MTU3n / MTIOC0A
    IOPORT_PIN_P143_PFC_05_ENCIF13         = (0x05U << IOPORT_PFC_OFFSET), ///< P14_3 / ENCIF / ENCIF13
    IOPORT_PIN_P144_PFC_00_XSPI0_DS        = (0x00U << IOPORT_PFC_OFFSET), ///< P14_4 / XSPIn / XSPI0_DS
    IOPORT_PIN_P144_PFC_01_BS              = (0x01U << IOPORT_PFC_OFFSET), ///< P14_4 / BSC / BS
    IOPORT_PIN_P144_PFC_02_ESC_IRQ         = (0x02U << IOPORT_PFC_OFFSET), ///< P14_4 / ETHER_ESC / ESC_IRQ
    IOPORT_PIN_P144_PFC_03_MTIOC0B         = (0x03U << IOPORT_PFC_OFFSET), ///< P14_4 / MTU3n / MTIOC0B
    IOPORT_PIN_P145_PFC_00_XSPI0_CKN       = (0x00U << IOPORT_PFC_OFFSET), ///< P14_5 / XSPIn / XSPI0_CKN
    IOPORT_PIN_P145_PFC_01_CS3             = (0x01U << IOPORT_PFC_OFFSET), ///< P14_5 / BSC / CS3
    IOPORT_PIN_P145_PFC_02_POE8            = (0x02U << IOPORT_PFC_OFFSET), ///< P14_5 / MTU_POE3 / POE8
    IOPORT_PIN_P146_PFC_00_XSPI0_CKP       = (0x00U << IOPORT_PFC_OFFSET), ///< P14_6 / XSPIn / XSPI0_CKP
    IOPORT_PIN_P146_PFC_01_A21             = (0x01U << IOPORT_PFC_OFFSET), ///< P14_6 / BSC / A21
    IOPORT_PIN_P147_PFC_00_XSPI0_IO0       = (0x00U << IOPORT_PFC_OFFSET), ///< P14_7 / XSPIn / XSPI0_IO0
    IOPORT_PIN_P147_PFC_01_A22             = (0x01U << IOPORT_PFC_OFFSET), ///< P14_7 / BSC / A22
    IOPORT_PIN_P147_PFC_02_SCK5            = (0x02U << IOPORT_PFC_OFFSET), ///< P14_7 / SCIn / SCK5
    IOPORT_PIN_P147_PFC_03_SPI_MISO1       = (0x03U << IOPORT_PFC_OFFSET), ///< P14_7 / SPIn / SPI_MISO1
    IOPORT_PIN_P150_PFC_00_XSPI0_IO1       = (0x00U << IOPORT_PFC_OFFSET), ///< P15_0 / XSPIn / XSPI0_IO1
    IOPORT_PIN_P150_PFC_01_A23             = (0x01U << IOPORT_PFC_OFFSET), ///< P15_0 / BSC / A23
    IOPORT_PIN_P150_PFC_02_RXD5_SCL5_MISO5 = (0x02U << IOPORT_PFC_OFFSET), ///< P15_0 / SCIn / RXD5_SCL5_MISO5
    IOPORT_PIN_P150_PFC_03_SPI_MOSI1       = (0x03U << IOPORT_PFC_OFFSET), ///< P15_0 / SPIn / SPI_MOSI1
    IOPORT_PIN_P151_PFC_00_XSPI0_IO2       = (0x00U << IOPORT_PFC_OFFSET), ///< P15_1 / XSPIn / XSPI0_IO2
    IOPORT_PIN_P151_PFC_01_A24             = (0x01U << IOPORT_PFC_OFFSET), ///< P15_1 / BSC / A24
    IOPORT_PIN_P151_PFC_02_MTIOC0C         = (0x02U << IOPORT_PFC_OFFSET), ///< P15_1 / MTU3n / MTIOC0C
    IOPORT_PIN_P151_PFC_03_TXD5_SDA5_MOSI5 = (0x03U << IOPORT_PFC_OFFSET), ///< P15_1 / SCIn / TXD5_SDA5_MOSI5
    IOPORT_PIN_P151_PFC_04_SPI_SSL10       = (0x04U << IOPORT_PFC_OFFSET), ///< P15_1 / SPIn / SPI_SSL10
    IOPORT_PIN_P152_PFC_00_XSPI0_IO3       = (0x00U << IOPORT_PFC_OFFSET), ///< P15_2 / XSPIn / XSPI0_IO3
    IOPORT_PIN_P152_PFC_01_A25             = (0x01U << IOPORT_PFC_OFFSET), ///< P15_2 / BSC / A25
    IOPORT_PIN_P152_PFC_02_MTIOC0D         = (0x02U << IOPORT_PFC_OFFSET), ///< P15_2 / MTU3n / MTIOC0D
    IOPORT_PIN_P152_PFC_03_SS5_CTS5_RTS5   = (0x03U << IOPORT_PFC_OFFSET), ///< P15_2 / SCIn / SS5_CTS5_RTS5
    IOPORT_PIN_P152_PFC_04_SPI_SSL11       = (0x04U << IOPORT_PFC_OFFSET), ///< P15_2 / SPIn / SPI_SSL11
    IOPORT_PIN_P153_PFC_00_XSPI0_IO4       = (0x00U << IOPORT_PFC_OFFSET), ///< P15_3 / XSPIn / XSPI0_IO4
    IOPORT_PIN_P153_PFC_01_MTIOC8C         = (0x01U << IOPORT_PFC_OFFSET), ///< P15_3 / MTU3n / MTIOC8C
    IOPORT_PIN_P153_PFC_02_MCLK1           = (0x02U << IOPORT_PFC_OFFSET), ///< P15_3 / DSMIFn / MCLK1
    IOPORT_PIN_P154_PFC_00_XSPI0_IO5       = (0x00U << IOPORT_PFC_OFFSET), ///< P15_4 / XSPIn / XSPI0_IO5
    IOPORT_PIN_P154_PFC_01_MTIOC8D         = (0x01U << IOPORT_PFC_OFFSET), ///< P15_4 / MTU3n / MTIOC8D
    IOPORT_PIN_P154_PFC_02_MDAT1           = (0x02U << IOPORT_PFC_OFFSET), ///< P15_4 / DSMIFn / MDAT1
    IOPORT_PIN_P155_PFC_00_XSPI0_IO6       = (0x00U << IOPORT_PFC_OFFSET), ///< P15_5 / XSPIn / XSPI0_IO6
    IOPORT_PIN_P155_PFC_01_MCLK2           = (0x01U << IOPORT_PFC_OFFSET), ///< P15_5 / DSMIFn / MCLK2
    IOPORT_PIN_P156_PFC_00_XSPI0_IO7       = (0x00U << IOPORT_PFC_OFFSET), ///< P15_6 / XSPIn / XSPI0_IO7
    IOPORT_PIN_P156_PFC_01_SPI_SSL12       = (0x01U << IOPORT_PFC_OFFSET), ///< P15_6 / SPIn / SPI_SSL12
    IOPORT_PIN_P156_PFC_02_MDAT2           = (0x02U << IOPORT_PFC_OFFSET), ///< P15_6 / DSMIFn / MDAT2
    IOPORT_PIN_P157_PFC_00_XSPI0_CS0       = (0x00U << IOPORT_PFC_OFFSET), ///< P15_7 / XSPIn / XSPI0_CS0
    IOPORT_PIN_P157_PFC_01_CTS5            = (0x01U << IOPORT_PFC_OFFSET), ///< P15_7 / SCIn / CTS5
    IOPORT_PIN_P157_PFC_02_SPI_SSL13       = (0x02U << IOPORT_PFC_OFFSET), ///< P15_7 / SPIn / SPI_SSL13
    IOPORT_PIN_P157_PFC_03_TEND            = (0x03U << IOPORT_PFC_OFFSET), ///< P15_7 / DMAC / TEND
    IOPORT_PIN_P157_PFC_04_ENCIF1          = (0x04U << IOPORT_PFC_OFFSET), ///< P15_7 / ENCIF / ENCIF1
    IOPORT_PIN_P160_PFC_00_XSPI0_CS1       = (0x00U << IOPORT_PFC_OFFSET), ///< P16_0 / XSPIn / XSPI0_CS1
    IOPORT_PIN_P160_PFC_01_ETH0_TXER       = (0x01U << IOPORT_PFC_OFFSET), ///< P16_0 / ETHER_ETHn / ETH0_TXER
    IOPORT_PIN_P160_PFC_02_TXD0_SDA0_MOSI0 = (0x02U << IOPORT_PFC_OFFSET), ///< P16_0 / SCIn / TXD0_SDA0_MOSI0
    IOPORT_PIN_P160_PFC_03_SPI_MOSI3       = (0x03U << IOPORT_PFC_OFFSET), ///< P16_0 / SPIn / SPI_MOSI3
    IOPORT_PIN_P160_PFC_04_MCLK3           = (0x04U << IOPORT_PFC_OFFSET), ///< P16_0 / DSMIFn / MCLK3
    IOPORT_PIN_P160_PFC_05_ENCIF0          = (0x05U << IOPORT_PFC_OFFSET), ///< P16_0 / ENCIF / ENCIF0
    IOPORT_PIN_P161_PFC_00_XSPI0_RESET0    = (0x00U << IOPORT_PFC_OFFSET), ///< P16_1 / XSPIn / XSPI0_RESET0
    IOPORT_PIN_P161_PFC_01_CMTW0_TOC1      = (0x01U << IOPORT_PFC_OFFSET), ///< P16_1 / CMTWn / CMTW0_TOC1
    IOPORT_PIN_P161_PFC_02_ADTRG0          = (0x02U << IOPORT_PFC_OFFSET), ///< P16_1 / ADCn / ADTRG0
    IOPORT_PIN_P161_PFC_03_RXD0_SCL0_MISO0 = (0x03U << IOPORT_PFC_OFFSET), ///< P16_1 / SCIn / RXD0_SCL0_MISO0
    IOPORT_PIN_P161_PFC_04_SPI_MISO3       = (0x04U << IOPORT_PFC_OFFSET), ///< P16_1 / SPIn / SPI_MISO3
    IOPORT_PIN_P161_PFC_05_MDAT3           = (0x05U << IOPORT_PFC_OFFSET), ///< P16_1 / DSMIFn / MDAT3
    IOPORT_PIN_P161_PFC_06_ENCIF2          = (0x06U << IOPORT_PFC_OFFSET), ///< P16_1 / ENCIF / ENCIF2
    IOPORT_PIN_P162_PFC_00_NMI             = (0x00U << IOPORT_PFC_OFFSET), ///< P16_2 / IRQ / NMI
    IOPORT_PIN_P162_PFC_01_XSPI0_RESET1    = (0x01U << IOPORT_PFC_OFFSET), ///< P16_2 / XSPIn / XSPI0_RESET1
    IOPORT_PIN_P162_PFC_02_CTS0            = (0x02U << IOPORT_PFC_OFFSET), ///< P16_2 / SCIn / CTS0
    IOPORT_PIN_P162_PFC_03_SPI_RSPCK3      = (0x03U << IOPORT_PFC_OFFSET), ///< P16_2 / SPIn / SPI_RSPCK3
    IOPORT_PIN_P162_PFC_04_USB_EXICEN      = (0x04U << IOPORT_PFC_OFFSET), ///< P16_2 / USB_HS / USB_EXICEN
    IOPORT_PIN_P162_PFC_05_ENCIF3          = (0x05U << IOPORT_PFC_OFFSET), ///< P16_2 / ENCIF / ENCIF3
    IOPORT_PIN_P163_PFC_00_IRQ7            = (0x00U << IOPORT_PFC_OFFSET), ///< P16_3 / IRQ / IRQ7
    IOPORT_PIN_P163_PFC_01_XSPI0_RSTO0     = (0x01U << IOPORT_PFC_OFFSET), ///< P16_3 / XSPIn / XSPI0_RSTO0
    IOPORT_PIN_P163_PFC_02_ETH1_TXER       = (0x02U << IOPORT_PFC_OFFSET), ///< P16_3 / ETHER_ETHn / ETH1_TXER
    IOPORT_PIN_P163_PFC_03_GTADSMP1        = (0x03U << IOPORT_PFC_OFFSET), ///< P16_3 / GPT / GTADSMP1
    IOPORT_PIN_P163_PFC_04_SCK0            = (0x04U << IOPORT_PFC_OFFSET), ///< P16_3 / SCIn / SCK0
    IOPORT_PIN_P163_PFC_05_SPI_SSL30       = (0x05U << IOPORT_PFC_OFFSET), ///< P16_3 / SPIn / SPI_SSL30
    IOPORT_PIN_P163_PFC_06_ENCIF4          = (0x06U << IOPORT_PFC_OFFSET), ///< P16_3 / ENCIF / ENCIF4
    IOPORT_PIN_P165_PFC_00_MTIC5U          = (0x00U << IOPORT_PFC_OFFSET), ///< P16_5 / MTU3n / MTIC5U
    IOPORT_PIN_P165_PFC_01_TXD0_SDA0_MOSI0 = (0x01U << IOPORT_PFC_OFFSET), ///< P16_5 / SCIn / TXD0_SDA0_MOSI0
    IOPORT_PIN_P166_PFC_00_IRQ8            = (0x00U << IOPORT_PFC_OFFSET), ///< P16_6 / IRQ / IRQ8
    IOPORT_PIN_P166_PFC_01_MTIC5V          = (0x01U << IOPORT_PFC_OFFSET), ///< P16_6 / MTU3n / MTIC5V
    IOPORT_PIN_P166_PFC_02_RXD0_SCL0_MISO0 = (0x02U << IOPORT_PFC_OFFSET), ///< P16_6 / SCIn / RXD0_SCL0_MISO0
    IOPORT_PIN_P167_PFC_00_MTIC5W          = (0x00U << IOPORT_PFC_OFFSET), ///< P16_7 / MTU3n / MTIC5W
    IOPORT_PIN_P167_PFC_01_SCK0            = (0x01U << IOPORT_PFC_OFFSET), ///< P16_7 / SCIn / SCK0
    IOPORT_PIN_P170_PFC_00_ESC_IRQ         = (0x00U << IOPORT_PFC_OFFSET), ///< P17_0 / ETHER_ESC / ESC_IRQ
    IOPORT_PIN_P170_PFC_01_SS0_CTS0_RTS0   = (0x01U << IOPORT_PFC_OFFSET), ///< P17_0 / SCIn / SS0_CTS0_RTS0
    IOPORT_PIN_P171_PFC_00_DE0             = (0x00U << IOPORT_PFC_OFFSET), ///< P17_1 / SCIn / DE0
    IOPORT_PIN_P172_PFC_00_IRQ9            = (0x00U << IOPORT_PFC_OFFSET), ///< P17_2 / IRQ / IRQ9
    IOPORT_PIN_P172_PFC_01_CMTW1_TIC0      = (0x01U << IOPORT_PFC_OFFSET), ///< P17_2 / CMTWn / CMTW1_TIC0
    IOPORT_PIN_P173_PFC_00_TRACECTL        = (0x00U << IOPORT_PFC_OFFSET), ///< P17_3 / TRACE / TRACECTL
    IOPORT_PIN_P173_PFC_01_GTETRGA         = (0x01U << IOPORT_PFC_OFFSET), ///< P17_3 / GPT_POEG / GTETRGA
    IOPORT_PIN_P173_PFC_02_POE0            = (0x02U << IOPORT_PFC_OFFSET), ///< P17_3 / MTU_POE3 / POE0
    IOPORT_PIN_P173_PFC_03_ADTRG1          = (0x03U << IOPORT_PFC_OFFSET), ///< P17_3 / ADCn / ADTRG1
    IOPORT_PIN_P173_PFC_04_SPI_SSL31       = (0x04U << IOPORT_PFC_OFFSET), ///< P17_3 / SPIn / SPI_SSL31
    IOPORT_PIN_P173_PFC_05_DREQ            = (0x05U << IOPORT_PFC_OFFSET), ///< P17_3 / DMAC / DREQ
    IOPORT_PIN_P173_PFC_06_ENCIF5          = (0x06U << IOPORT_PFC_OFFSET), ///< P17_3 / ENCIF / ENCIF5
    IOPORT_PIN_P174_PFC_00_TRACECLK        = (0x00U << IOPORT_PFC_OFFSET), ///< P17_4 / TRACE / TRACECLK
    IOPORT_PIN_P174_PFC_01_MTIOC3C         = (0x01U << IOPORT_PFC_OFFSET), ///< P17_4 / MTU3n / MTIOC3C
    IOPORT_PIN_P174_PFC_02_GTETRGB         = (0x02U << IOPORT_PFC_OFFSET), ///< P17_4 / GPT_POEG / GTETRGB
    IOPORT_PIN_P174_PFC_03_GTIOC0A         = (0x03U << IOPORT_PFC_OFFSET), ///< P17_4 / GPTn / GTIOC0A
    IOPORT_PIN_P174_PFC_04_CTS3            = (0x04U << IOPORT_PFC_OFFSET), ///< P17_4 / SCIn / CTS3
    IOPORT_PIN_P174_PFC_05_SPI_SSL32       = (0x05U << IOPORT_PFC_OFFSET), ///< P17_4 / SPIn / SPI_SSL32
    IOPORT_PIN_P174_PFC_06_ENCIF6          = (0x06U << IOPORT_PFC_OFFSET), ///< P17_4 / ENCIF / ENCIF6
    IOPORT_PIN_P175_PFC_01_MTIOC3A         = (0x01U << IOPORT_PFC_OFFSET), ///< P17_5 / MTU3n / MTIOC3A
    IOPORT_PIN_P175_PFC_02_GTETRGC         = (0x02U << IOPORT_PFC_OFFSET), ///< P17_5 / GPT_POEG / GTETRGC
    IOPORT_PIN_P175_PFC_03_GTIOC0B         = (0x03U << IOPORT_PFC_OFFSET), ///< P17_5 / GPTn / GTIOC0B
    IOPORT_PIN_P175_PFC_04_TEND            = (0x04U << IOPORT_PFC_OFFSET), ///< P17_5 / DMAC / TEND
    IOPORT_PIN_P175_PFC_05_USB_OVRCUR      = (0x05U << IOPORT_PFC_OFFSET), ///< P17_5 / USB_HS / USB_OVRCUR
    IOPORT_PIN_P175_PFC_06_ENCIF7          = (0x06U << IOPORT_PFC_OFFSET), ///< P17_5 / ENCIF / ENCIF7
    IOPORT_PIN_P176_PFC_00_MTIOC3B         = (0x00U << IOPORT_PFC_OFFSET), ///< P17_6 / MTU3n / MTIOC3B
    IOPORT_PIN_P176_PFC_01_GTIOC1A         = (0x01U << IOPORT_PFC_OFFSET), ///< P17_6 / GPTn / GTIOC1A
    IOPORT_PIN_P176_PFC_02_SCK3            = (0x02U << IOPORT_PFC_OFFSET), ///< P17_6 / SCIn / SCK3
    IOPORT_PIN_P176_PFC_03_ENCIF8          = (0x03U << IOPORT_PFC_OFFSET), ///< P17_6 / ENCIF / ENCIF8
    IOPORT_PIN_P177_PFC_00_MTIOC4A         = (0x00U << IOPORT_PFC_OFFSET), ///< P17_7 / MTU3n / MTIOC4A
    IOPORT_PIN_P177_PFC_01_MTIOC4C         = (0x01U << IOPORT_PFC_OFFSET), ///< P17_7 / MTU3n / MTIOC4C
    IOPORT_PIN_P177_PFC_02_GTIOC2A         = (0x02U << IOPORT_PFC_OFFSET), ///< P17_7 / GPTn / GTIOC2A
    IOPORT_PIN_P177_PFC_03_GTIOC3A         = (0x03U << IOPORT_PFC_OFFSET), ///< P17_7 / GPTn / GTIOC3A
    IOPORT_PIN_P177_PFC_04_RXD3_SCL3_MISO3 = (0x04U << IOPORT_PFC_OFFSET), ///< P17_7 / SCIn / RXD3_SCL3_MISO3
    IOPORT_PIN_P177_PFC_05_DACK            = (0x05U << IOPORT_PFC_OFFSET), ///< P17_7 / DMAC / DACK
    IOPORT_PIN_P177_PFC_06_ENCIF9          = (0x06U << IOPORT_PFC_OFFSET), ///< P17_7 / ENCIF / ENCIF9
    IOPORT_PIN_P180_PFC_00_MTIOC4C         = (0x00U << IOPORT_PFC_OFFSET), ///< P18_0 / MTU3n / MTIOC4C
    IOPORT_PIN_P180_PFC_01_MTIOC4A         = (0x01U << IOPORT_PFC_OFFSET), ///< P18_0 / MTU3n / MTIOC4A
    IOPORT_PIN_P180_PFC_02_GTIOC3A         = (0x02U << IOPORT_PFC_OFFSET), ///< P18_0 / GPTn / GTIOC3A
    IOPORT_PIN_P180_PFC_03_GTIOC2A         = (0x03U << IOPORT_PFC_OFFSET), ///< P18_0 / GPTn / GTIOC2A
    IOPORT_PIN_P180_PFC_04_TXD3_SDA3_MOSI3 = (0x04U << IOPORT_PFC_OFFSET), ///< P18_0 / SCIn / TXD3_SDA3_MOSI3
    IOPORT_PIN_P181_PFC_00_IRQ10           = (0x00U << IOPORT_PFC_OFFSET), ///< P18_1 / IRQ / IRQ10
    IOPORT_PIN_P181_PFC_01_MTIOC3D         = (0x01U << IOPORT_PFC_OFFSET), ///< P18_1 / MTU3n / MTIOC3D
    IOPORT_PIN_P181_PFC_02_GTIOC1B         = (0x02U << IOPORT_PFC_OFFSET), ///< P18_1 / GPTn / GTIOC1B
    IOPORT_PIN_P181_PFC_03_ADTRG1          = (0x03U << IOPORT_PFC_OFFSET), ///< P18_1 / ADCn / ADTRG1
    IOPORT_PIN_P181_PFC_04_SS3_CTS3_RTS3   = (0x04U << IOPORT_PFC_OFFSET), ///< P18_1 / SCIn / SS3_CTS3_RTS3
    IOPORT_PIN_P181_PFC_05_ENCIF10         = (0x05U << IOPORT_PFC_OFFSET), ///< P18_1 / ENCIF / ENCIF10
    IOPORT_PIN_P182_PFC_00_MTIOC4B         = (0x00U << IOPORT_PFC_OFFSET), ///< P18_2 / MTU3n / MTIOC4B
    IOPORT_PIN_P182_PFC_01_MTIOC4D         = (0x01U << IOPORT_PFC_OFFSET), ///< P18_2 / MTU3n / MTIOC4D
    IOPORT_PIN_P182_PFC_02_GTIOC2B         = (0x02U << IOPORT_PFC_OFFSET), ///< P18_2 / GPTn / GTIOC2B
    IOPORT_PIN_P182_PFC_03_GTIOC3B         = (0x03U << IOPORT_PFC_OFFSET), ///< P18_2 / GPTn / GTIOC3B
    IOPORT_PIN_P182_PFC_04_ENCIF11         = (0x04U << IOPORT_PFC_OFFSET), ///< P18_2 / ENCIF / ENCIF11
    IOPORT_PIN_P183_PFC_00_IRQ0            = (0x00U << IOPORT_PFC_OFFSET), ///< P18_3 / IRQ / IRQ0
    IOPORT_PIN_P183_PFC_01_MTIOC4D         = (0x01U << IOPORT_PFC_OFFSET), ///< P18_3 / MTU3n / MTIOC4D
    IOPORT_PIN_P183_PFC_02_MTIOC4B         = (0x02U << IOPORT_PFC_OFFSET), ///< P18_3 / MTU3n / MTIOC4B
    IOPORT_PIN_P183_PFC_03_GTIOC3B         = (0x03U << IOPORT_PFC_OFFSET), ///< P18_3 / GPTn / GTIOC3B
    IOPORT_PIN_P183_PFC_04_GTIOC2B         = (0x04U << IOPORT_PFC_OFFSET), ///< P18_3 / GPTn / GTIOC2B
    IOPORT_PIN_P183_PFC_05_CMTW1_TIC1      = (0x05U << IOPORT_PFC_OFFSET), ///< P18_3 / CMTWn / CMTW1_TIC1
    IOPORT_PIN_P183_PFC_06_CANRXDP1        = (0x06U << IOPORT_PFC_OFFSET), ///< P18_3 / CANFDn / CANRXDP1
    IOPORT_PIN_P183_PFC_07_ENCIF12         = (0x07U << IOPORT_PFC_OFFSET), ///< P18_3 / ENCIF / ENCIF12
    IOPORT_PIN_P184_PFC_00_IRQ1            = (0x00U << IOPORT_PFC_OFFSET), ///< P18_4 / IRQ / IRQ1
    IOPORT_PIN_P184_PFC_01_MTIC5U          = (0x01U << IOPORT_PFC_OFFSET), ///< P18_4 / MTU3n / MTIC5U
    IOPORT_PIN_P184_PFC_02_TXD4_SDA4_MOSI4 = (0x02U << IOPORT_PFC_OFFSET), ///< P18_4 / SCIn / TXD4_SDA4_MOSI4
    IOPORT_PIN_P184_PFC_03_SPI_RSPCK2      = (0x03U << IOPORT_PFC_OFFSET), ///< P18_4 / SPIn / SPI_RSPCK2
    IOPORT_PIN_P184_PFC_04_ENCIF13         = (0x04U << IOPORT_PFC_OFFSET), ///< P18_4 / ENCIF / ENCIF13
    IOPORT_PIN_P185_PFC_00_TRACECTL        = (0x00U << IOPORT_PFC_OFFSET), ///< P18_5 / TRACE / TRACECTL
    IOPORT_PIN_P185_PFC_01_MTIC5V          = (0x01U << IOPORT_PFC_OFFSET), ///< P18_5 / MTU3n / MTIC5V
    IOPORT_PIN_P185_PFC_02_RXD4_SCL4_MISO4 = (0x02U << IOPORT_PFC_OFFSET), ///< P18_5 / SCIn / RXD4_SCL4_MISO4
    IOPORT_PIN_P185_PFC_03_SPI_MOSI2       = (0x03U << IOPORT_PFC_OFFSET), ///< P18_5 / SPIn / SPI_MOSI2
    IOPORT_PIN_P185_PFC_04_ENCIF14         = (0x04U << IOPORT_PFC_OFFSET), ///< P18_5 / ENCIF / ENCIF14
    IOPORT_PIN_P186_PFC_00_IRQ11           = (0x00U << IOPORT_PFC_OFFSET), ///< P18_6 / IRQ / IRQ11
    IOPORT_PIN_P186_PFC_01_TRACECLK        = (0x01U << IOPORT_PFC_OFFSET), ///< P18_6 / TRACE / TRACECLK
    IOPORT_PIN_P186_PFC_02_MTIC5W          = (0x02U << IOPORT_PFC_OFFSET), ///< P18_6 / MTU3n / MTIC5W
    IOPORT_PIN_P186_PFC_03_ADTRG0          = (0x03U << IOPORT_PFC_OFFSET), ///< P18_6 / ADCn / ADTRG0
    IOPORT_PIN_P186_PFC_04_SCK4            = (0x04U << IOPORT_PFC_OFFSET), ///< P18_6 / SCIn / SCK4
    IOPORT_PIN_P186_PFC_05_SPI_MISO2       = (0x05U << IOPORT_PFC_OFFSET), ///< P18_6 / SPIn / SPI_MISO2
    IOPORT_PIN_P186_PFC_06_IIC_SCL2        = (0x06U << IOPORT_PFC_OFFSET), ///< P18_6 / IICn / IIC_SCL2
    IOPORT_PIN_P186_PFC_07_ENCIF15         = (0x07U << IOPORT_PFC_OFFSET), ///< P18_6 / ENCIF / ENCIF15
    IOPORT_PIN_P187_PFC_00_IRQ2            = (0x00U << IOPORT_PFC_OFFSET), ///< P18_7 / IRQ / IRQ2
    IOPORT_PIN_P187_PFC_01_GTETRGD         = (0x01U << IOPORT_PFC_OFFSET), ///< P18_7 / GPT_POEG / GTETRGD
    IOPORT_PIN_P187_PFC_02_POE4            = (0x02U << IOPORT_PFC_OFFSET), ///< P18_7 / MTU_POE3 / POE4
    IOPORT_PIN_P187_PFC_03_SPI_SSL20       = (0x03U << IOPORT_PFC_OFFSET), ///< P18_7 / SPIn / SPI_SSL20
    IOPORT_PIN_P187_PFC_04_IIC_SDA2        = (0x04U << IOPORT_PFC_OFFSET), ///< P18_7 / IICn / IIC_SDA2
    IOPORT_PIN_P187_PFC_05_USB_VBUSEN      = (0x05U << IOPORT_PFC_OFFSET), ///< P18_7 / USB_HS / USB_VBUSEN
    IOPORT_PIN_P190_PFC_00_USB_VBUSEN      = (0x00U << IOPORT_PFC_OFFSET), ///< P19_0 / USB_HS / USB_VBUSEN
    IOPORT_PIN_P191_PFC_00_MTIOC6A         = (0x00U << IOPORT_PFC_OFFSET), ///< P19_1 / MTU3n / MTIOC6A
    IOPORT_PIN_P191_PFC_01_GTIOC4A         = (0x01U << IOPORT_PFC_OFFSET), ///< P19_1 / GPTn / GTIOC4A
    IOPORT_PIN_P192_PFC_00_IRQ3            = (0x00U << IOPORT_PFC_OFFSET), ///< P19_2 / IRQ / IRQ3
    IOPORT_PIN_P192_PFC_01_MTIOC6C         = (0x01U << IOPORT_PFC_OFFSET), ///< P19_2 / MTU3n / MTIOC6C
    IOPORT_PIN_P192_PFC_02_GTIOC4B         = (0x02U << IOPORT_PFC_OFFSET), ///< P19_2 / GPTn / GTIOC4B
    IOPORT_PIN_P193_PFC_00_MTIOC6B         = (0x00U << IOPORT_PFC_OFFSET), ///< P19_3 / MTU3n / MTIOC6B
    IOPORT_PIN_P193_PFC_01_GTIOC5A         = (0x01U << IOPORT_PFC_OFFSET), ///< P19_3 / GPTn / GTIOC5A
    IOPORT_PIN_P194_PFC_00_MTIOC7A         = (0x00U << IOPORT_PFC_OFFSET), ///< P19_4 / MTU3n / MTIOC7A
    IOPORT_PIN_P194_PFC_01_GTIOC6A         = (0x01U << IOPORT_PFC_OFFSET), ///< P19_4 / GPTn / GTIOC6A
    IOPORT_PIN_P195_PFC_00_MTIOC7C         = (0x00U << IOPORT_PFC_OFFSET), ///< P19_5 / MTU3n / MTIOC7C
    IOPORT_PIN_P195_PFC_01_GTIOC7A         = (0x01U << IOPORT_PFC_OFFSET), ///< P19_5 / GPTn / GTIOC7A
    IOPORT_PIN_P196_PFC_00_MTIOC6D         = (0x00U << IOPORT_PFC_OFFSET), ///< P19_6 / MTU3n / MTIOC6D
    IOPORT_PIN_P196_PFC_01_GTIOC5B         = (0x01U << IOPORT_PFC_OFFSET), ///< P19_6 / GPTn / GTIOC5B
    IOPORT_PIN_P197_PFC_00_MTIOC7B         = (0x00U << IOPORT_PFC_OFFSET), ///< P19_7 / MTU3n / MTIOC7B
    IOPORT_PIN_P197_PFC_01_GTIOC6B         = (0x01U << IOPORT_PFC_OFFSET), ///< P19_7 / GPTn / GTIOC6B
    IOPORT_PIN_P200_PFC_00_MTIOC7D         = (0x00U << IOPORT_PFC_OFFSET), ///< P20_0 / MTU3n / MTIOC7D
    IOPORT_PIN_P200_PFC_01_GTIOC7B         = (0x01U << IOPORT_PFC_OFFSET), ///< P20_0 / GPTn / GTIOC7B
    IOPORT_PIN_P201_PFC_00_ETHSW_TDMAOUT0  = (0x00U << IOPORT_PFC_OFFSET), ///< P20_1 / ETHER_ETHSW / ETHSW_TDMAOUT0
    IOPORT_PIN_P201_PFC_01_ESC_LINKACT0    = (0x01U << IOPORT_PFC_OFFSET), ///< P20_1 / ETHER_ESC / ESC_LINKACT0
    IOPORT_PIN_P202_PFC_00_ETHSW_TDMAOUT1  = (0x00U << IOPORT_PFC_OFFSET), ///< P20_2 / ETHER_ETHSW / ETHSW_TDMAOUT1
    IOPORT_PIN_P202_PFC_01_ESC_LEDRUN      = (0x01U << IOPORT_PFC_OFFSET), ///< P20_2 / ETHER_ESC / ESC_LEDRUN
    IOPORT_PIN_P202_PFC_02_ESC_LEDSTER     = (0x02U << IOPORT_PFC_OFFSET), ///< P20_2 / ETHER_ESC / ESC_LEDSTER
    IOPORT_PIN_P202_PFC_03_DE3             = (0x03U << IOPORT_PFC_OFFSET), ///< P20_2 / SCIn / DE3
    IOPORT_PIN_P203_PFC_00_ETHSW_TDMAOUT2  = (0x00U << IOPORT_PFC_OFFSET), ///< P20_3 / ETHER_ETHSW / ETHSW_TDMAOUT2
    IOPORT_PIN_P203_PFC_01_ESC_LEDERR      = (0x01U << IOPORT_PFC_OFFSET), ///< P20_3 / ETHER_ESC / ESC_LEDERR
    IOPORT_PIN_P204_PFC_00_ETHSW_TDMAOUT3  = (0x00U << IOPORT_PFC_OFFSET), ///< P20_4 / ETHER_ETHSW / ETHSW_TDMAOUT3
    IOPORT_PIN_P204_PFC_01_ESC_LINKACT1    = (0x01U << IOPORT_PFC_OFFSET), ///< P20_4 / ETHER_ESC / ESC_LINKACT1
    IOPORT_PIN_P205_PFC_00_ESC_I2CCLK      = (0x00U << IOPORT_PFC_OFFSET), ///< P20_5 / ETHER_ESC / ESC_I2CCLK
    IOPORT_PIN_P205_PFC_01_MTIOC1A         = (0x01U << IOPORT_PFC_OFFSET), ///< P20_5 / MTU3n / MTIOC1A
    IOPORT_PIN_P205_PFC_02_IIC_SCL0        = (0x02U << IOPORT_PFC_OFFSET), ///< P20_5 / IICn / IIC_SCL0
    IOPORT_PIN_P205_PFC_03_MCLK4           = (0x03U << IOPORT_PFC_OFFSET), ///< P20_5 / DSMIFn / MCLK4
    IOPORT_PIN_P206_PFC_00_ESC_I2CDATA     = (0x00U << IOPORT_PFC_OFFSET), ///< P20_6 / ETHER_ESC / ESC_I2CDATA
    IOPORT_PIN_P206_PFC_01_MTIOC1B         = (0x01U << IOPORT_PFC_OFFSET), ///< P20_6 / MTU3n / MTIOC1B
    IOPORT_PIN_P206_PFC_02_IIC_SDA0        = (0x02U << IOPORT_PFC_OFFSET), ///< P20_6 / IICn / IIC_SDA0
    IOPORT_PIN_P206_PFC_03_MDAT4           = (0x03U << IOPORT_PFC_OFFSET), ///< P20_6 / DSMIFn / MDAT4
    IOPORT_PIN_P207_PFC_00_ETHSW_PTPOUT2   = (0x00U << IOPORT_PFC_OFFSET), ///< P20_7 / ETHER_ETHSW / ETHSW_PTPOUT2
    IOPORT_PIN_P207_PFC_01_ESC_RESETOUT    = (0x01U << IOPORT_PFC_OFFSET), ///< P20_7 / ETHER_ESC / ESC_RESETOUT
    IOPORT_PIN_P207_PFC_02_MTIOC2A         = (0x02U << IOPORT_PFC_OFFSET), ///< P20_7 / MTU3n / MTIOC2A
    IOPORT_PIN_P207_PFC_03_GTIOC13A        = (0x03U << IOPORT_PFC_OFFSET), ///< P20_7 / GPTn / GTIOC13A
    IOPORT_PIN_P207_PFC_04_MCLK5           = (0x04U << IOPORT_PFC_OFFSET), ///< P20_7 / DSMIFn / MCLK5
    IOPORT_PIN_P210_PFC_00_ETHSW_PTPOUT3   = (0x00U << IOPORT_PFC_OFFSET), ///< P21_0 / ETHER_ETHSW / ETHSW_PTPOUT3
    IOPORT_PIN_P210_PFC_01_WE2_DQMUL       = (0x01U << IOPORT_PFC_OFFSET), ///< P21_0 / BSC / WE2_DQMUL
    IOPORT_PIN_P210_PFC_02_ESC_LINKACT2    = (0x02U << IOPORT_PFC_OFFSET), ///< P21_0 / ETHER_ESC / ESC_LINKACT2
    IOPORT_PIN_P210_PFC_03_MTIOC2B         = (0x03U << IOPORT_PFC_OFFSET), ///< P21_0 / MTU3n / MTIOC2B
    IOPORT_PIN_P210_PFC_04_GTIOC13B        = (0x04U << IOPORT_PFC_OFFSET), ///< P21_0 / GPTn / GTIOC13B
    IOPORT_PIN_P210_PFC_05_MDAT5           = (0x05U << IOPORT_PFC_OFFSET), ///< P21_0 / DSMIFn / MDAT5
    IOPORT_PIN_P211_PFC_00_TRACEDATA0      = (0x00U << IOPORT_PFC_OFFSET), ///< P21_1 / TRACE / TRACEDATA0
    IOPORT_PIN_P211_PFC_01_D0              = (0x01U << IOPORT_PFC_OFFSET), ///< P21_1 / BSC / D0
    IOPORT_PIN_P211_PFC_02_MTIOC6A         = (0x02U << IOPORT_PFC_OFFSET), ///< P21_1 / MTU3n / MTIOC6A
    IOPORT_PIN_P211_PFC_03_GTIOC14A        = (0x03U << IOPORT_PFC_OFFSET), ///< P21_1 / GPTn / GTIOC14A
    IOPORT_PIN_P211_PFC_04_CMTW0_TIC0      = (0x04U << IOPORT_PFC_OFFSET), ///< P21_1 / CMTWn / CMTW0_TIC0
    IOPORT_PIN_P211_PFC_05_SCK5            = (0x05U << IOPORT_PFC_OFFSET), ///< P21_1 / SCIn / SCK5
    IOPORT_PIN_P211_PFC_06_SPI_SSL20       = (0x06U << IOPORT_PFC_OFFSET), ///< P21_1 / SPIn / SPI_SSL20
    IOPORT_PIN_P211_PFC_07_IIC_SCL1        = (0x07U << IOPORT_PFC_OFFSET), ///< P21_1 / IICn / IIC_SCL1
    IOPORT_PIN_P211_PFC_08_MCLK0           = (0x08U << IOPORT_PFC_OFFSET), ///< P21_1 / DSMIFn / MCLK0
    IOPORT_PIN_P211_PFC_09_ENCIF5          = (0x09U << IOPORT_PFC_OFFSET), ///< P21_1 / ENCIF / ENCIF5
    IOPORT_PIN_P212_PFC_00_TRACEDATA1      = (0x00U << IOPORT_PFC_OFFSET), ///< P21_2 / TRACE / TRACEDATA1
    IOPORT_PIN_P212_PFC_01_D1              = (0x01U << IOPORT_PFC_OFFSET), ///< P21_2 / BSC / D1
    IOPORT_PIN_P212_PFC_02_MTIOC6B         = (0x02U << IOPORT_PFC_OFFSET), ///< P21_2 / MTU3n / MTIOC6B
    IOPORT_PIN_P212_PFC_03_GTIOC14B        = (0x03U << IOPORT_PFC_OFFSET), ///< P21_2 / GPTn / GTIOC14B
    IOPORT_PIN_P212_PFC_04_CMTW0_TIC1      = (0x04U << IOPORT_PFC_OFFSET), ///< P21_2 / CMTWn / CMTW0_TIC1
    IOPORT_PIN_P212_PFC_05_RXD5_SCL5_MISO5 = (0x05U << IOPORT_PFC_OFFSET), ///< P21_2 / SCIn / RXD5_SCL5_MISO5
    IOPORT_PIN_P212_PFC_06_SPI_MISO2       = (0x06U << IOPORT_PFC_OFFSET), ///< P21_2 / SPIn / SPI_MISO2
    IOPORT_PIN_P212_PFC_07_IIC_SDA1        = (0x07U << IOPORT_PFC_OFFSET), ///< P21_2 / IICn / IIC_SDA1
    IOPORT_PIN_P212_PFC_08_MDAT0           = (0x08U << IOPORT_PFC_OFFSET), ///< P21_2 / DSMIFn / MDAT0
    IOPORT_PIN_P212_PFC_09_ENCIF6          = (0x09U << IOPORT_PFC_OFFSET), ///< P21_2 / ENCIF / ENCIF6
    IOPORT_PIN_P213_PFC_00_TRACEDATA2      = (0x00U << IOPORT_PFC_OFFSET), ///< P21_3 / TRACE / TRACEDATA2
    IOPORT_PIN_P213_PFC_01_D2              = (0x01U << IOPORT_PFC_OFFSET), ///< P21_3 / BSC / D2
    IOPORT_PIN_P213_PFC_02_MTIOC6C         = (0x02U << IOPORT_PFC_OFFSET), ///< P21_3 / MTU3n / MTIOC6C
    IOPORT_PIN_P213_PFC_03_GTIOC15A        = (0x03U << IOPORT_PFC_OFFSET), ///< P21_3 / GPTn / GTIOC15A
    IOPORT_PIN_P213_PFC_04_TXD5_SDA5_MOSI5 = (0x04U << IOPORT_PFC_OFFSET), ///< P21_3 / SCIn / TXD5_SDA5_MOSI5
    IOPORT_PIN_P213_PFC_05_SPI_SSL33       = (0x05U << IOPORT_PFC_OFFSET), ///< P21_3 / SPIn / SPI_SSL33
    IOPORT_PIN_P213_PFC_06_MCLK1           = (0x06U << IOPORT_PFC_OFFSET), ///< P21_3 / DSMIFn / MCLK1
    IOPORT_PIN_P213_PFC_07_ENCIF7          = (0x07U << IOPORT_PFC_OFFSET), ///< P21_3 / ENCIF / ENCIF7
    IOPORT_PIN_P214_PFC_00_TRACEDATA3      = (0x00U << IOPORT_PFC_OFFSET), ///< P21_4 / TRACE / TRACEDATA3
    IOPORT_PIN_P214_PFC_01_D3              = (0x01U << IOPORT_PFC_OFFSET), ///< P21_4 / BSC / D3
    IOPORT_PIN_P214_PFC_02_MTIOC6D         = (0x02U << IOPORT_PFC_OFFSET), ///< P21_4 / MTU3n / MTIOC6D
    IOPORT_PIN_P214_PFC_03_GTIOC15B        = (0x03U << IOPORT_PFC_OFFSET), ///< P21_4 / GPTn / GTIOC15B
    IOPORT_PIN_P214_PFC_04_SS5_CTS5_RTS5   = (0x04U << IOPORT_PFC_OFFSET), ///< P21_4 / SCIn / SS5_CTS5_RTS5
    IOPORT_PIN_P214_PFC_05_SPI_SSL02       = (0x05U << IOPORT_PFC_OFFSET), ///< P21_4 / SPIn / SPI_SSL02
    IOPORT_PIN_P214_PFC_06_MDAT1           = (0x06U << IOPORT_PFC_OFFSET), ///< P21_4 / DSMIFn / MDAT1
    IOPORT_PIN_P214_PFC_07_ENCIF8          = (0x07U << IOPORT_PFC_OFFSET), ///< P21_4 / ENCIF / ENCIF8
    IOPORT_PIN_P215_PFC_00_IRQ6            = (0x00U << IOPORT_PFC_OFFSET), ///< P21_5 / IRQ / IRQ6
    IOPORT_PIN_P215_PFC_01_TRACEDATA4      = (0x01U << IOPORT_PFC_OFFSET), ///< P21_5 / TRACE / TRACEDATA4
    IOPORT_PIN_P215_PFC_02_D4              = (0x02U << IOPORT_PFC_OFFSET), ///< P21_5 / BSC / D4
    IOPORT_PIN_P215_PFC_03_MTIOC7A         = (0x03U << IOPORT_PFC_OFFSET), ///< P21_5 / MTU3n / MTIOC7A
    IOPORT_PIN_P215_PFC_04_GTIOC16A        = (0x04U << IOPORT_PFC_OFFSET), ///< P21_5 / GPTn / GTIOC16A
    IOPORT_PIN_P215_PFC_05_CMTW1_TOC1      = (0x05U << IOPORT_PFC_OFFSET), ///< P21_5 / CMTWn / CMTW1_TOC1
    IOPORT_PIN_P215_PFC_06_ADTRG1          = (0x06U << IOPORT_PFC_OFFSET), ///< P21_5 / ADCn / ADTRG1
    IOPORT_PIN_P215_PFC_07_CTS5            = (0x07U << IOPORT_PFC_OFFSET), ///< P21_5 / SCIn / CTS5
    IOPORT_PIN_P215_PFC_08_SPI_MISO0       = (0x08U << IOPORT_PFC_OFFSET), ///< P21_5 / SPIn / SPI_MISO0
    IOPORT_PIN_P215_PFC_09_MCLK2           = (0x09U << IOPORT_PFC_OFFSET), ///< P21_5 / DSMIFn / MCLK2
    IOPORT_PIN_P215_PFC_0A_ENCIF9          = (0x0AU << IOPORT_PFC_OFFSET), ///< P21_5 / ENCIF / ENCIF9
    IOPORT_PIN_P216_PFC_00_IRQ9            = (0x00U << IOPORT_PFC_OFFSET), ///< P21_6 / IRQ / IRQ9
    IOPORT_PIN_P216_PFC_01_TRACEDATA5      = (0x01U << IOPORT_PFC_OFFSET), ///< P21_6 / TRACE / TRACEDATA5
    IOPORT_PIN_P216_PFC_02_D5              = (0x02U << IOPORT_PFC_OFFSET), ///< P21_6 / BSC / D5
    IOPORT_PIN_P216_PFC_03_MTIOC7B         = (0x03U << IOPORT_PFC_OFFSET), ///< P21_6 / MTU3n / MTIOC7B
    IOPORT_PIN_P216_PFC_04_GTIOC16B        = (0x04U << IOPORT_PFC_OFFSET), ///< P21_6 / GPTn / GTIOC16B
    IOPORT_PIN_P216_PFC_05_CTS0            = (0x05U << IOPORT_PFC_OFFSET), ///< P21_6 / SCIn / CTS0
    IOPORT_PIN_P216_PFC_06_TEND            = (0x06U << IOPORT_PFC_OFFSET), ///< P21_6 / DMAC / TEND
    IOPORT_PIN_P216_PFC_07_MDAT2           = (0x07U << IOPORT_PFC_OFFSET), ///< P21_6 / DSMIFn / MDAT2
    IOPORT_PIN_P217_PFC_00_IRQ10           = (0x00U << IOPORT_PFC_OFFSET), ///< P21_7 / IRQ / IRQ10
    IOPORT_PIN_P217_PFC_01_TRACEDATA6      = (0x01U << IOPORT_PFC_OFFSET), ///< P21_7 / TRACE / TRACEDATA6
    IOPORT_PIN_P217_PFC_02_D6              = (0x02U << IOPORT_PFC_OFFSET), ///< P21_7 / BSC / D6
    IOPORT_PIN_P217_PFC_03_MTIOC7C         = (0x03U << IOPORT_PFC_OFFSET), ///< P21_7 / MTU3n / MTIOC7C
    IOPORT_PIN_P217_PFC_04_GTIOC17A        = (0x04U << IOPORT_PFC_OFFSET), ///< P21_7 / GPTn / GTIOC17A
    IOPORT_PIN_P217_PFC_05_DE0             = (0x05U << IOPORT_PFC_OFFSET), ///< P21_7 / SCIn / DE0
    IOPORT_PIN_P217_PFC_06_DREQ            = (0x06U << IOPORT_PFC_OFFSET), ///< P21_7 / DMAC / DREQ
    IOPORT_PIN_P217_PFC_07_MCLK3           = (0x07U << IOPORT_PFC_OFFSET), ///< P21_7 / DSMIFn / MCLK3
    IOPORT_PIN_P220_PFC_00_IRQ15           = (0x00U << IOPORT_PFC_OFFSET), ///< P22_0 / IRQ / IRQ15
    IOPORT_PIN_P220_PFC_01_TRACEDATA7      = (0x01U << IOPORT_PFC_OFFSET), ///< P22_0 / TRACE / TRACEDATA7
    IOPORT_PIN_P220_PFC_02_D7              = (0x02U << IOPORT_PFC_OFFSET), ///< P22_0 / BSC / D7
    IOPORT_PIN_P220_PFC_03_MTIOC7D         = (0x03U << IOPORT_PFC_OFFSET), ///< P22_0 / MTU3n / MTIOC7D
    IOPORT_PIN_P220_PFC_04_GTIOC17B        = (0x04U << IOPORT_PFC_OFFSET), ///< P22_0 / GPTn / GTIOC17B
    IOPORT_PIN_P220_PFC_05_DE5             = (0x05U << IOPORT_PFC_OFFSET), ///< P22_0 / SCIn / DE5
    IOPORT_PIN_P220_PFC_06_MDAT3           = (0x06U << IOPORT_PFC_OFFSET), ///< P22_0 / DSMIFn / MDAT3
    IOPORT_PIN_P221_PFC_00_TRACECTL        = (0x00U << IOPORT_PFC_OFFSET), ///< P22_1 / TRACE / TRACECTL
    IOPORT_PIN_P221_PFC_01_D8              = (0x01U << IOPORT_PFC_OFFSET), ///< P22_1 / BSC / D8
    IOPORT_PIN_P221_PFC_02_ESC_LINKACT2    = (0x02U << IOPORT_PFC_OFFSET), ///< P22_1 / ETHER_ESC / ESC_LINKACT2
    IOPORT_PIN_P221_PFC_03_POE4            = (0x03U << IOPORT_PFC_OFFSET), ///< P22_1 / MTU_POE3 / POE4
    IOPORT_PIN_P221_PFC_04_SS4_CTS4_RTS4   = (0x04U << IOPORT_PFC_OFFSET), ///< P22_1 / SCIn / SS4_CTS4_RTS4
    IOPORT_PIN_P222_PFC_00_IRQ4            = (0x00U << IOPORT_PFC_OFFSET), ///< P22_2 / IRQ / IRQ4
    IOPORT_PIN_P222_PFC_01_TRACECLK        = (0x01U << IOPORT_PFC_OFFSET), ///< P22_2 / TRACE / TRACECLK
    IOPORT_PIN_P222_PFC_02_D9              = (0x02U << IOPORT_PFC_OFFSET), ///< P22_2 / BSC / D9
    IOPORT_PIN_P222_PFC_03_MTIOC8C         = (0x03U << IOPORT_PFC_OFFSET), ///< P22_2 / MTU3n / MTIOC8C
    IOPORT_PIN_P222_PFC_04_GTETRGSA        = (0x04U << IOPORT_PFC_OFFSET), ///< P22_2 / GPT_POEG / GTETRGSA
    IOPORT_PIN_P222_PFC_05_SPI_SSL12       = (0x05U << IOPORT_PFC_OFFSET), ///< P22_2 / SPIn / SPI_SSL12
    IOPORT_PIN_P222_PFC_06_ENCIF10         = (0x06U << IOPORT_PFC_OFFSET), ///< P22_2 / ENCIF / ENCIF10
    IOPORT_PIN_P223_PFC_00_D10             = (0x00U << IOPORT_PFC_OFFSET), ///< P22_3 / BSC / D10
    IOPORT_PIN_P223_PFC_01_MTIOC8D         = (0x01U << IOPORT_PFC_OFFSET), ///< P22_3 / MTU3n / MTIOC8D
    IOPORT_PIN_P223_PFC_02_GTETRGSB        = (0x02U << IOPORT_PFC_OFFSET), ///< P22_3 / GPT_POEG / GTETRGSB
    IOPORT_PIN_P223_PFC_03_ENCIF11         = (0x03U << IOPORT_PFC_OFFSET), ///< P22_3 / ENCIF / ENCIF11
    IOPORT_PIN_P224_PFC_00_D11             = (0x00U << IOPORT_PFC_OFFSET), ///< P22_4 / BSC / D11
    IOPORT_PIN_P225_PFC_00_D12             = (0x00U << IOPORT_PFC_OFFSET), ///< P22_5 / BSC / D12
    IOPORT_PIN_P225_PFC_01_CTS4            = (0x01U << IOPORT_PFC_OFFSET), ///< P22_5 / SCIn / CTS4
    IOPORT_PIN_P226_PFC_00_D13             = (0x00U << IOPORT_PFC_OFFSET), ///< P22_6 / BSC / D13
    IOPORT_PIN_P226_PFC_01_DE4             = (0x01U << IOPORT_PFC_OFFSET), ///< P22_6 / SCIn / DE4
    IOPORT_PIN_P226_PFC_02_IIC_SCL1        = (0x02U << IOPORT_PFC_OFFSET), ///< P22_6 / IICn / IIC_SCL1
    IOPORT_PIN_P227_PFC_00_D14             = (0x00U << IOPORT_PFC_OFFSET), ///< P22_7 / BSC / D14
    IOPORT_PIN_P227_PFC_01_SCK0            = (0x01U << IOPORT_PFC_OFFSET), ///< P22_7 / SCIn / SCK0
    IOPORT_PIN_P227_PFC_02_IIC_SDA1        = (0x02U << IOPORT_PFC_OFFSET), ///< P22_7 / IICn / IIC_SDA1
    IOPORT_PIN_P230_PFC_00_IRQ5            = (0x00U << IOPORT_PFC_OFFSET), ///< P23_0 / IRQ / IRQ5
    IOPORT_PIN_P230_PFC_01_D15             = (0x01U << IOPORT_PFC_OFFSET), ///< P23_0 / BSC / D15
    IOPORT_PIN_P230_PFC_02_SPI_MOSI2       = (0x02U << IOPORT_PFC_OFFSET), ///< P23_0 / SPIn / SPI_MOSI2
    IOPORT_PIN_P231_PFC_00_NMI             = (0x00U << IOPORT_PFC_OFFSET), ///< P23_1 / IRQ / NMI
    IOPORT_PIN_P231_PFC_01_D16             = (0x01U << IOPORT_PFC_OFFSET), ///< P23_1 / BSC / D16
    IOPORT_PIN_P231_PFC_02_WE0_DQMLL       = (0x02U << IOPORT_PFC_OFFSET), ///< P23_1 / BSC / WE0_DQMLL
    IOPORT_PIN_P231_PFC_03_MTCLKA          = (0x03U << IOPORT_PFC_OFFSET), ///< P23_1 / MTU3 / MTCLKA
    IOPORT_PIN_P232_PFC_00_IRQ8            = (0x00U << IOPORT_PFC_OFFSET), ///< P23_2 / IRQ / IRQ8
    IOPORT_PIN_P232_PFC_01_D17             = (0x01U << IOPORT_PFC_OFFSET), ///< P23_2 / BSC / D17
    IOPORT_PIN_P232_PFC_02_WE1_DQMLU       = (0x02U << IOPORT_PFC_OFFSET), ///< P23_2 / BSC / WE1_DQMLU
    IOPORT_PIN_P232_PFC_03_MTCLKB          = (0x03U << IOPORT_PFC_OFFSET), ///< P23_2 / MTU3 / MTCLKB
    IOPORT_PIN_P233_PFC_00_D18             = (0x00U << IOPORT_PFC_OFFSET), ///< P23_3 / BSC / D18
    IOPORT_PIN_P233_PFC_01_WE3_DQMUU_AH    = (0x01U << IOPORT_PFC_OFFSET), ///< P23_3 / BSC / WE3_DQMUU_AH
    IOPORT_PIN_P233_PFC_02_MTCLKC          = (0x02U << IOPORT_PFC_OFFSET), ///< P23_3 / MTU3 / MTCLKC
    IOPORT_PIN_P233_PFC_03_RXD0_SCL0_MISO0 = (0x03U << IOPORT_PFC_OFFSET), ///< P23_3 / SCIn / RXD0_SCL0_MISO0
    IOPORT_PIN_P234_PFC_00_D19             = (0x00U << IOPORT_PFC_OFFSET), ///< P23_4 / BSC / D19
    IOPORT_PIN_P234_PFC_01_CS5             = (0x01U << IOPORT_PFC_OFFSET), ///< P23_4 / BSC / CS5
    IOPORT_PIN_P234_PFC_02_MTCLKD          = (0x02U << IOPORT_PFC_OFFSET), ///< P23_4 / MTU3 / MTCLKD
    IOPORT_PIN_P235_PFC_00_D20             = (0x00U << IOPORT_PFC_OFFSET), ///< P23_5 / BSC / D20
    IOPORT_PIN_P235_PFC_01_CS2             = (0x01U << IOPORT_PFC_OFFSET), ///< P23_5 / BSC / CS2
    IOPORT_PIN_P235_PFC_02_MTIOC8A         = (0x02U << IOPORT_PFC_OFFSET), ///< P23_5 / MTU3n / MTIOC8A
    IOPORT_PIN_P235_PFC_03_TXD0_SDA0_MOSI0 = (0x03U << IOPORT_PFC_OFFSET), ///< P23_5 / SCIn / TXD0_SDA0_MOSI0
    IOPORT_PIN_P236_PFC_00_D21             = (0x00U << IOPORT_PFC_OFFSET), ///< P23_6 / BSC / D21
    IOPORT_PIN_P236_PFC_01_MTIOC8B         = (0x01U << IOPORT_PFC_OFFSET), ///< P23_6 / MTU3n / MTIOC8B
    IOPORT_PIN_P236_PFC_02_SS0_CTS0_RTS0   = (0x02U << IOPORT_PFC_OFFSET), ///< P23_6 / SCIn / SS0_CTS0_RTS0
    IOPORT_PIN_P237_PFC_00_ETH2_RXD0       = (0x00U << IOPORT_PFC_OFFSET), ///< P23_7 / ETHER_ETHn / ETH2_RXD0
    IOPORT_PIN_P237_PFC_01_D22             = (0x01U << IOPORT_PFC_OFFSET), ///< P23_7 / BSC / D22
    IOPORT_PIN_P237_PFC_02_D11             = (0x02U << IOPORT_PFC_OFFSET), ///< P23_7 / BSC / D11
    IOPORT_PIN_P237_PFC_03_BS              = (0x03U << IOPORT_PFC_OFFSET), ///< P23_7 / BSC / BS
    IOPORT_PIN_P237_PFC_04_MTIOC0A         = (0x04U << IOPORT_PFC_OFFSET), ///< P23_7 / MTU3n / MTIOC0A
    IOPORT_PIN_P237_PFC_05_GTETRGA         = (0x05U << IOPORT_PFC_OFFSET), ///< P23_7 / GPT_POEG / GTETRGA
    IOPORT_PIN_P237_PFC_06_SCK1            = (0x06U << IOPORT_PFC_OFFSET), ///< P23_7 / SCIn / SCK1
    IOPORT_PIN_P237_PFC_07_MCLK4           = (0x07U << IOPORT_PFC_OFFSET), ///< P23_7 / DSMIFn / MCLK4
    IOPORT_PIN_P237_PFC_08_ENCIF12         = (0x08U << IOPORT_PFC_OFFSET), ///< P23_7 / ENCIF / ENCIF12
    IOPORT_PIN_P240_PFC_00_ETH2_RXD1       = (0x00U << IOPORT_PFC_OFFSET), ///< P24_0 / ETHER_ETHn / ETH2_RXD1
    IOPORT_PIN_P240_PFC_01_D23             = (0x01U << IOPORT_PFC_OFFSET), ///< P24_0 / BSC / D23
    IOPORT_PIN_P240_PFC_02_D12             = (0x02U << IOPORT_PFC_OFFSET), ///< P24_0 / BSC / D12
    IOPORT_PIN_P240_PFC_03_CKE             = (0x03U << IOPORT_PFC_OFFSET), ///< P24_0 / BSC / CKE
    IOPORT_PIN_P240_PFC_04_MTIOC0B         = (0x04U << IOPORT_PFC_OFFSET), ///< P24_0 / MTU3n / MTIOC0B
    IOPORT_PIN_P240_PFC_05_GTETRGB         = (0x05U << IOPORT_PFC_OFFSET), ///< P24_0 / GPT_POEG / GTETRGB
    IOPORT_PIN_P240_PFC_06_RXD1_SCL1_MISO1 = (0x06U << IOPORT_PFC_OFFSET), ///< P24_0 / SCIn / RXD1_SCL1_MISO1
    IOPORT_PIN_P240_PFC_07_DREQ            = (0x07U << IOPORT_PFC_OFFSET), ///< P24_0 / DMAC / DREQ
    IOPORT_PIN_P240_PFC_08_MDAT4           = (0x08U << IOPORT_PFC_OFFSET), ///< P24_0 / DSMIFn / MDAT4
    IOPORT_PIN_P240_PFC_09_ENCIF13         = (0x09U << IOPORT_PFC_OFFSET), ///< P24_0 / ENCIF / ENCIF13
    IOPORT_PIN_P241_PFC_00_ETH2_RXCLK      = (0x00U << IOPORT_PFC_OFFSET), ///< P24_1 / ETHER_ETHn / ETH2_RXCLK
    IOPORT_PIN_P241_PFC_01_D24             = (0x01U << IOPORT_PFC_OFFSET), ///< P24_1 / BSC / D24
    IOPORT_PIN_P241_PFC_02_D13             = (0x02U << IOPORT_PFC_OFFSET), ///< P24_1 / BSC / D13
    IOPORT_PIN_P241_PFC_03_CAS             = (0x03U << IOPORT_PFC_OFFSET), ///< P24_1 / BSC / CAS
    IOPORT_PIN_P241_PFC_04_MTIOC0C         = (0x04U << IOPORT_PFC_OFFSET), ///< P24_1 / MTU3n / MTIOC0C
    IOPORT_PIN_P241_PFC_05_GTETRGC         = (0x05U << IOPORT_PFC_OFFSET), ///< P24_1 / GPT_POEG / GTETRGC
    IOPORT_PIN_P241_PFC_06_POE8            = (0x06U << IOPORT_PFC_OFFSET), ///< P24_1 / MTU_POE3 / POE8
    IOPORT_PIN_P241_PFC_07_MCLK5           = (0x07U << IOPORT_PFC_OFFSET), ///< P24_1 / DSMIFn / MCLK5
    IOPORT_PIN_P241_PFC_08_ENCIF14         = (0x08U << IOPORT_PFC_OFFSET), ///< P24_1 / ENCIF / ENCIF14
    IOPORT_PIN_P242_PFC_00_ETH2_RXD2       = (0x00U << IOPORT_PFC_OFFSET), ///< P24_2 / ETHER_ETHn / ETH2_RXD2
    IOPORT_PIN_P242_PFC_01_D25             = (0x01U << IOPORT_PFC_OFFSET), ///< P24_2 / BSC / D25
    IOPORT_PIN_P242_PFC_02_D14             = (0x02U << IOPORT_PFC_OFFSET), ///< P24_2 / BSC / D14
    IOPORT_PIN_P242_PFC_03_RAS             = (0x03U << IOPORT_PFC_OFFSET), ///< P24_2 / BSC / RAS
    IOPORT_PIN_P242_PFC_04_MTIOC0D         = (0x04U << IOPORT_PFC_OFFSET), ///< P24_2 / MTU3n / MTIOC0D
    IOPORT_PIN_P242_PFC_05_GTETRGD         = (0x05U << IOPORT_PFC_OFFSET), ///< P24_2 / GPT_POEG / GTETRGD
    IOPORT_PIN_P242_PFC_06_TXD1_SDA1_MOSI1 = (0x06U << IOPORT_PFC_OFFSET), ///< P24_2 / SCIn / TXD1_SDA1_MOSI1
    IOPORT_PIN_P242_PFC_07_MDAT5           = (0x07U << IOPORT_PFC_OFFSET), ///< P24_2 / DSMIFn / MDAT5
    IOPORT_PIN_P242_PFC_08_ENCIF15         = (0x08U << IOPORT_PFC_OFFSET), ///< P24_2 / ENCIF / ENCIF15

    /** Marks end of enum - used by parameter checking */
    IOPORT_PERIPHERAL_END
} ioport_pin_pfc_t;

/** Options to configure pin functions  */
typedef enum e_ioport_cfg_options
{
    IOPORT_CFG_PORT_DIRECTION_HIZ          = 0x00000000 << IOPORT_PM_OFFSET, ///< Sets the pin direction to Hi-Z
    IOPORT_CFG_PORT_DIRECTION_INPUT        = 0x00000001 << IOPORT_PM_OFFSET, ///< Sets the pin direction to input (default)
    IOPORT_CFG_PORT_DIRECTION_OUTPUT       = 0x00000002 << IOPORT_PM_OFFSET, ///< Sets the pin direction to output
    IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT = 0x00000003 << IOPORT_PM_OFFSET, ///< Sets the pin direction to output (data is input to input buffer)
    IOPORT_CFG_PORT_OUTPUT_LOW             = 0x00000000 << IOPORT_P_OFFSET,  ///< Sets the pin level to low
    IOPORT_CFG_PORT_OUTPUT_HIGH            = 0x00000001 << IOPORT_P_OFFSET,  ///< Sets the pin level to high
    IOPORT_CFG_PORT_GPIO               = 0x00000000 << IOPORT_PMC_OFFSET,    ///< Enables pin to operate as an GPIO pin
    IOPORT_CFG_PORT_PERI               = 0x00000001 << IOPORT_PMC_OFFSET,    ///< Enables pin to operate as a peripheral pin
    IOPORT_CFG_DRIVE_LOW               = 0x00000000 << IOPORT_DRCTL_OFFSET,  ///< Sets pin drive output to low
    IOPORT_CFG_DRIVE_MID               = 0x00000001 << IOPORT_DRCTL_OFFSET,  ///< Sets pin drive output to medium
    IOPORT_CFG_DRIVE_HIGH              = 0x00000002 << IOPORT_DRCTL_OFFSET,  ///< Sets pin drive output to high
    IOPORT_CFG_DRIVE_UHIGH             = 0x00000003 << IOPORT_DRCTL_OFFSET,  ///< Sets pin drive output to ultra high
    IOPORT_CFG_PULLUP_DOWN_DISABLE     = 0x00000000 << IOPORT_DRCTL_OFFSET,  ///< Disables the pin's pull-up / pull-down
    IOPORT_CFG_PULLUP_ENABLE           = 0x00000004 << IOPORT_DRCTL_OFFSET,  ///< Enables the pin's internal pull-up
    IOPORT_CFG_PULLDOWN_ENABLE         = 0x00000008 << IOPORT_DRCTL_OFFSET,  ///< Enables the pin's pull-down
    IOPORT_CFG_SCHMITT_TRIGGER_DISABLE = 0x00000000 << IOPORT_DRCTL_OFFSET,  ///< Disables schmitt trigger input
    IOPORT_CFG_SCHMITT_TRIGGER_ENABLE  = 0x00000010 << IOPORT_DRCTL_OFFSET,  ///< Enables schmitt trigger input
    IOPORT_CFG_SLEW_RATE_SLOW          = 0x00000000 << IOPORT_DRCTL_OFFSET,  ///< Sets the slew rate to slow
    IOPORT_CFG_SLEW_RATE_FAST          = 0x00000020 << IOPORT_DRCTL_OFFSET,  ///< Sets the slew rate to fast
    IOPORT_CFG_REGION_SAFETY           = 0x00000000 << IOPORT_RSELP_OFFSET,  ///< Selects safety region
    IOPORT_CFG_REGION_NSAFETY          = 0x00000001 << IOPORT_RSELP_OFFSET,  ///< Selects non safety region
    IOPORT_CFG_PIM_TTL                 = 0x00000020,                         ///< This macro has been unsupported
    IOPORT_CFG_NMOS_ENABLE             = 0x00000040,                         ///< This macro has been unsupported
    IOPORT_CFG_PMOS_ENABLE             = 0x00000080,                         ///< This macro has been unsupported
    IOPORT_CFG_DRIVE_HS_HIGH           = 0x00000800,                         ///< This macro has been unsupported
    IOPORT_CFG_DRIVE_MID_IIC           = 0x00000C00,                         ///< This macro has been unsupported
    IOPORT_CFG_EVENT_RISING_EDGE       = 0x00001000,                         ///< This macro has been unsupported
    IOPORT_CFG_EVENT_FALLING_EDGE      = 0x00002000,                         ///< This macro has been unsupported
    IOPORT_CFG_EVENT_BOTH_EDGES        = 0x00003000,                         ///< This macro has been unsupported
    IOPORT_CFG_IRQ_ENABLE              = 0x00004000,                         ///< This macro has been unsupported
    IOPORT_CFG_ANALOG_ENABLE           = 0x00008000,                         ///< This macro has been unsupported
    IOPORT_CFG_PERIPHERAL_PIN          = 0x00010000                          ///< This macro has been unsupported
} ioport_cfg_options_t;

/*==============================================
 * POE3 API Overrides
 *==============================================*/

/** POE3 states. */
typedef enum e_poe3_state
{
    POE3_STATE_NO_DISABLE_REQUEST           = 0,                ///< Timer output is not disabled by POE3
    POE3_STATE_POE0_HIGH_IMPEDANCE_REQUEST  = 1U,               ///< Timer output disabled due to POE0# pin
    POE3_STATE_POE4_HIGH_IMPEDANCE_REQUEST  = 1U << 1,          ///< Timer output disabled due to POE4# pin
    POE3_STATE_POE8_HIGH_IMPEDANCE_REQUEST  = 1U << 2,          ///< Timer output disabled due to POE8# pin
    POE3_STATE_POE10_HIGH_IMPEDANCE_REQUEST = 1U << 3,          ///< Timer output disabled due to POE10# pin
    POE3_STATE_POE11_HIGH_IMPEDANCE_REQUEST = 1U << 4,          ///< Timer output disabled due to POE11# pin

    POE3_STATE_SOFTWARE_STOP_DISABLE_REQUEST    = 1U << 5,      ///< Timer output disabled due to poe3_api_t::outputDisable()
    POE3_STATE_OSCILLATION_STOP_DISABLE_REQUEST = 1U << 6,      ///< Timer output disabled due to main oscillator stop

    POE3_STATE_DSMIF0_ERROR_REQUEST = 1U << 7,                  ///< Timer output disabled due to DSMIF0 error
    POE3_STATE_DSMIF1_ERROR_REQUEST = 1U << 8,                  ///< Timer output disabled due to DSMIF1 error

    POE3_STATE_OUTPUT_SHORT_CIRCUIT_1_ERROR_REQUEST = 1U << 9,  ///< Timer output disabled due to output short circuit 1
    POE3_STATE_OUTPUT_SHORT_CIRCUIT_2_ERROR_REQUEST = 1U << 10, ///< Timer output disabled due to output short circuit 2
} poe3_state_t;

/*==============================================
 * POEG API Overrides
 *==============================================*/

/** POEG states. */
typedef enum e_poeg_state
{
    POEG_STATE_NO_DISABLE_REQUEST                = 0,       ///< GPT output is not disabled by POEG
    POEG_STATE_PIN_DISABLE_REQUEST               = 1U << 0, ///< GPT output disabled due to GTETRG pin level
    POEG_STATE_GPT_OR_COMPARATOR_DISABLE_REQUEST = 1U << 1, ///< GPT output disabled due to high speed analog comparator or GPT
    POEG_STATE_OSCILLATION_STOP_DISABLE_REQUEST  = 1U << 2, ///< GPT output disabled due to main oscillator stop
    POEG_STATE_SOFTWARE_STOP_DISABLE_REQUEST     = 1U << 3, ///< GPT output disabled due to poeg_api_t::outputDisable()

    /** GPT output disable request active from the GTETRG pin. If a filter is used, this flag represents the state of
     * the filtered input. */
    POEG_STATE_PIN_DISABLE_REQUEST_ACTIVE = 1U << 16,
    POEG_STATE_DSMIF0_DISABLE_REQUEST     = 1U << 24,       ///< GPT output disabled due to DSMIF0 error 0
    POEG_STATE_DSMIF1_DISABLE_REQUEST     = 1U << 25,       ///< GPT output disabled due to DSMIF1 error 0
} poeg_state_t;

/** Triggers that will disable GPT output pins. */
typedef enum e_poeg_trigger
{
    /** Software disable is always supported with POEG. Select this option if no other triggers are used. */
    POEG_TRIGGER_SOFTWARE         = 0U,
    POEG_TRIGGER_PIN              = 1U << 0, ///< Disable GPT output based on GTETRG input level
    POEG_TRIGGER_GPT_OUTPUT_LEVEL = 1U << 1, ///< Disable GPT output based on GPT output pin levels
    POEG_TRIGGER_OSCILLATION_STOP = 1U << 2, ///< Disable GPT output based on main oscillator stop
    POEG_TRIGGER_ACMPHS0          = 1U << 4, ///< Disable GPT output based on ACMPHS0 comparator result
    POEG_TRIGGER_ACMPHS1          = 1U << 5, ///< Disable GPT output based on ACMPHS1 comparator result
    POEG_TRIGGER_ACMPHS2          = 1U << 6, ///< Disable GPT output based on ACMPHS2 comparator result
    POEG_TRIGGER_ACMPHS3          = 1U << 7, ///< Disable GPT output based on ACMPHS3 comparator result
    POEG_TRIGGER_ACMPHS4          = 1U << 8, ///< Disable GPT output based on ACMPHS4 comparator result
    POEG_TRIGGER_ACMPHS5          = 1U << 9, ///< Disable GPT output based on ACMPHS5 comparator result

    /** The GPT output pins can be disabled when DSMIF error occurs (LLPP only). */
    POEG_TRIGGER_DERR0E = 1U << 22,          ///< Permit output disabled by DSMIF0 error detection
    POEG_TRIGGER_DERR1E = 1U << 23,          ///< Permit output disabled by DSMIF1 error detection
} poeg_trigger_t;

/*==============================================
 * Transfer API Overrides
 *==============================================*/

/** Events that can trigger a callback function. */
typedef enum e_transfer_event
{
    TRANSFER_EVENT_TRANSFER_END   = 0, ///< Transfer has completed.
    TRANSFER_EVENT_TRANSFER_ERROR = 1, ///< Transfer error has occurred.
} transfer_event_t;

/** Transfer mode describes what will happen when a transfer request occurs. */
typedef enum e_transfer_mode
{
    /** Normal mode. */
    TRANSFER_MODE_NORMAL = 0,

    /** Block mode. */
    TRANSFER_MODE_BLOCK = 1
} transfer_mode_t;

/** Transfer size specifies the size of each individual transfer. */
typedef enum e_transfer_size
{
    TRANSFER_SIZE_1_BYTE  = 0,         ///< Each transfer transfers a 8-bit value
    TRANSFER_SIZE_2_BYTE  = 1,         ///< Each transfer transfers a 16-bit value
    TRANSFER_SIZE_4_BYTE  = 2,         ///< Each transfer transfers a 32-bit value
    TRANSFER_SIZE_8_BYTE  = 3,         ///< Each transfer transfers a 64-bit value
    TRANSFER_SIZE_16_BYTE = 4,         ///< Each transfer transfers a 128-bit value
    TRANSFER_SIZE_32_BYTE = 5,         ///< Each transfer transfers a 256-bit value
    TRANSFER_SIZE_64_BYTE = 6          ///< Each transfer transfers a 512-bit value
} transfer_size_t;

/** Address mode specifies whether to modify (increment or decrement) pointer after each transfer. */
typedef enum e_transfer_addr_mode
{
    /** Address pointer is incremented by associated @ref transfer_size_t after each transfer. */
    TRANSFER_ADDR_MODE_INCREMENTED = 0,

    /** Address pointer remains fixed after each transfer. */
    TRANSFER_ADDR_MODE_FIXED = 1
} transfer_addr_mode_t;

/** Callback function parameter data. */
typedef struct st_transfer_callback_args_t
{
    transfer_event_t event;            ///< Event code
    void const     * p_context;        ///< Placeholder for user data. Set in transfer_api_t::open function in ::transfer_cfg_t.
} transfer_callback_args_t;

/** This structure specifies the properties of the transfer. */
typedef struct st_transfer_info
{
    /** Select what happens to destination pointer after each transfer. */
    transfer_addr_mode_t dest_addr_mode;

    /** Select what happens to source pointer after each transfer. */
    transfer_addr_mode_t src_addr_mode;

    /** Select mode from @ref transfer_mode_t. */
    transfer_mode_t mode;

    /** Source pointer. */
    void const * volatile p_src;

    /** Destination pointer. */
    void * volatile p_dest;

    /** Length of each transfer. */
    volatile uint32_t length;

    /** Select number of source bytes to transfer at once. */
    transfer_size_t src_size;

    /** Select number of destination bytes to transfer at once. */
    transfer_size_t dest_size;

    /** Next1 Register set settings */
    void const * p_next1_src;
    void       * p_next1_dest;
    uint32_t     next1_length;
} transfer_info_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
