/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA8P1
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA8P1) */

#ifndef BSP_OVERRIDE_H
#define BSP_OVERRIDE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#if __has_include("r_lpm_device_types.h")
 #include "r_lpm_device_types.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Define overrides required for this MCU. */

#define BSP_OVERRIDE_CGC_DIVIDER_CFG_T
#define BSP_OVERRIDE_CGC_SYS_CLOCK_DIV_T
#define BSP_OVERRIDE_GROUP_IRQ_T
#define BSP_OVERRIDE_IOPORT_PERIPHERAL_T
#define BSP_OVERRIDE_LVD_PERIPHERAL_T

/* Override definitions. */

/* Private definition to set enumeration values. */
#define IOPORT_PRV_PFS_PSEL_OFFSET    (24)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** System clock divider values - The individually selectable divider of each of the system clocks, ICLK, BCLK, FCLK,
 * PCLKS A-D.  */
typedef enum e_cgc_sys_clock_div
{
    CGC_SYS_CLOCK_DIV_1  = 0,          ///< System clock divided by 1
    CGC_SYS_CLOCK_DIV_2  = 1,          ///< System clock divided by 2
    CGC_SYS_CLOCK_DIV_4  = 2,          ///< System clock divided by 4
    CGC_SYS_CLOCK_DIV_8  = 3,          ///< System clock divided by 8
    CGC_SYS_CLOCK_DIV_16 = 4,          ///< System clock divided by 16
    CGC_SYS_CLOCK_DIV_32 = 5,          ///< System clock divided by 32
    CGC_SYS_CLOCK_DIV_64 = 6,          ///< System clock divided by 64
    CGC_SYS_CLOCK_DIV_3  = 8,          ///< System clock divided by 3
    CGC_SYS_CLOCK_DIV_6  = 9,          ///< System clock divided by 6
    CGC_SYS_CLOCK_DIV_12 = 10,         ///< System clock divided by 12
    CGC_SYS_CLOCK_DIV_24 = 11,         ///< System clock divided by 24
} cgc_sys_clock_div_t;

/** Clock configuration structure - Used as an input parameter to the @ref cgc_api_t::systemClockSet and @ref cgc_api_t::systemClockGet
 * functions. */
typedef struct st_cgc_divider_cfg
{
    union
    {
        uint32_t sckdivcr_w;                   ///< System clock Division control register

        struct
        {
            cgc_sys_clock_div_t pclkd_div : 4; ///< Divider value for PCLKD
            cgc_sys_clock_div_t pclkc_div : 4; ///< Divider value for PCLKC
            cgc_sys_clock_div_t pclkb_div : 4; ///< Divider value for PCLKB
            cgc_sys_clock_div_t pclka_div : 4; ///< Divider value for PCLKA
            cgc_sys_clock_div_t bclk_div  : 4; ///< Divider value for BCLK
            cgc_sys_clock_div_t pclke_div : 4; ///< Divider value for PCLKE
            cgc_sys_clock_div_t iclk_div  : 4; ///< Divider value for ICLK
            cgc_sys_clock_div_t fclk_div  : 4; ///< Divider value for FCLK
        } sckdivcr_b;
    };

    union
    {
        uint16_t sckdivcr2;                      ///< System clock Division control register 2

        struct
        {
            cgc_sys_clock_div_t cpuclk_div  : 4; ///< Divider value for CPUCLK0
            cgc_sys_clock_div_t cpuclk1_div : 4; ///< Divider value for CPUCLK1
            cgc_sys_clock_div_t npuclk_div  : 4; ///< Divider value for NPUCLK
            cgc_sys_clock_div_t mriclk_div  : 4; ///< Divider value for MRICLK
        } sckdivcr2_b;
    };
} cgc_divider_cfg_t;

/* Which interrupts can have callbacks registered. */
typedef enum e_bsp_grp_irq
{
    BSP_GRP_IRQ_IWDT_ERROR       = 0,  ///< IWDT underflow/refresh error has occurred
    BSP_GRP_IRQ_WDT_ERROR        = 1,  ///< WDT underflow/refresh error has occurred
    BSP_GRP_IRQ_LVD1             = 2,  ///< Voltage monitoring 1 interrupt
    BSP_GRP_IRQ_LVD2             = 3,  ///< Voltage monitoring 2 interrupt
    BSP_GRP_IRQ_SOSC_STOP_DETECT = 5,  ///< Sub Oscillation stop is detected
    BSP_GRP_IRQ_OSC_STOP_DETECT  = 6,  ///< Oscillation stop is detected
    BSP_GRP_IRQ_NMI_PIN          = 7,  ///< NMI Pin interrupt
    BSP_GRP_IRQ_MPU_BUS_TZF      = 12, ///< MPU Bus or TrustZone Filter Error
    BSP_GRP_IRQ_COMMON_MEMORY    = 13, ///< SRAM ECC or SRAM Parity Error
    BSP_GRP_IRQ_LOCAL_MEMORY     = 14, ///< Local Memory Error
    BSP_GRP_IRQ_LOCKUP           = 15, ///< LockUp Error
    BSP_GRP_IRQ_FPU              = 16, ///< FPU Exception
    BSP_GRP_IRQ_MRC              = 17, ///< MRAM Code read error
    BSP_GRP_IRQ_MRE              = 18, ///< MRAM Extra read error
    BSP_GRP_IRQ_IPC              = 20, ///< IPC Interrupt
} bsp_grp_irq_t;

/** Superset of all peripheral functions.  */
typedef enum e_ioport_peripheral
{
    /** Pin will functions as an IO pin */
    IOPORT_PERIPHERAL_IO = 0x00,

    /** Pin will function as a DEBUG pin */
    IOPORT_PERIPHERAL_DEBUG = (0x00UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an AGT peripheral pin */
    IOPORT_PERIPHERAL_AGT = (0x01UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an AGT peripheral pin */
    IOPORT_PERIPHERAL_AGTW = (0x01UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an AGT peripheral pin */
    IOPORT_PERIPHERAL_AGT1 = (0x18UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT0 = (0x02UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT1 = (0x03UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI peripheral pin */
    IOPORT_PERIPHERAL_SCI0_2_4_6_8 = (0x04UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI peripheral pin */
    IOPORT_PERIPHERAL_SCI1_3_5_7_9 = (0x05UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a SPI peripheral pin */
    IOPORT_PERIPHERAL_SPI = (0x06UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a IIC peripheral pin */
    IOPORT_PERIPHERAL_IIC = (0x07UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a KEY peripheral pin */
    IOPORT_PERIPHERAL_KEY = (0x08UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a clock/comparator/RTC peripheral pin */
    IOPORT_PERIPHERAL_CLKOUT_COMP_RTC = (0x09UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAC/ADC peripheral pin */
    IOPORT_PERIPHERAL_CAC_AD = (0x0AUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a BUS peripheral pin */
    IOPORT_PERIPHERAL_BUS = (0x0BUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CTSU peripheral pin */
    IOPORT_PERIPHERAL_CTSU = (0x0CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CMPHS peripheral pin */
    IOPORT_PERIPHERAL_ACMPHS = (0x0CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a segment LCD peripheral pin */
    IOPORT_PERIPHERAL_LCDC = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

#if BSP_FEATURE_SCI_UART_DE_IS_INVERTED

    /** Pin will function as an SCI peripheral DEn pin */
    IOPORT_PERIPHERAL_DE_SCI1_3_5_7_9 = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI DEn peripheral pin */
    IOPORT_PERIPHERAL_DE_SCI0_2_4_6_8 = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),
#else

    /** Pin will function as an SCI peripheral DEn pin */
    IOPORT_PERIPHERAL_DE_SCI0_2_4_6_8 = (0x0DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SCI DEn peripheral pin */
    IOPORT_PERIPHERAL_DE_SCI1_3_5_7_9 = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),
#endif

    /** Pin will function as a DALI peripheral pin */
    IOPORT_PERIPHERAL_DALI = (0x0EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CEU peripheral pin */
    IOPORT_PERIPHERAL_CEU = (0x0FUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAN peripheral pin */
    IOPORT_PERIPHERAL_CAN = (0x10UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a QSPI peripheral pin */
    IOPORT_PERIPHERAL_QSPI = (0x11UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SSI peripheral pin */
    IOPORT_PERIPHERAL_SSI = (0x12UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a USB full speed peripheral pin */
    IOPORT_PERIPHERAL_USB_FS = (0x13UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a USB high speed peripheral pin */
    IOPORT_PERIPHERAL_USB_HS = (0x14UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT2 = (0x14UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an SD/MMC peripheral pin */
    IOPORT_PERIPHERAL_SDHI_MMC = (0x15UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT3 = (0x15UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an Ethernet MMI peripheral pin */
    IOPORT_PERIPHERAL_ETHER_MII = (0x16UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a GPT peripheral pin */
    IOPORT_PERIPHERAL_GPT4 = (0x16UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as an Ethernet RMMI peripheral pin */
    IOPORT_PERIPHERAL_ETHER_RMII = (0x17UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PDC peripheral pin */
    IOPORT_PERIPHERAL_PDC = (0x18UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a graphics LCD peripheral pin */
    IOPORT_PERIPHERAL_LCD_GRAPHICS = (0x19UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CAC peripheral pin */
    IOPORT_PERIPHERAL_CAC = (0x19UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a debug trace peripheral pin */
    IOPORT_PERIPHERAL_TRACE = (0x1AUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a OSPI peripheral pin */
    IOPORT_PERIPHERAL_OSPI = (0x1CUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a CEC peripheral pin */
    IOPORT_PERIPHERAL_CEC = (0x1DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PGAOUT peripheral pin */
    IOPORT_PERIPHERAL_PGAOUT0 = (0x1DUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PGAOUT peripheral pin */
    IOPORT_PERIPHERAL_PGAOUT1 = (0x1EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a ULPT peripheral pin */
    IOPORT_PERIPHERAL_ULPT = (0x1EUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a MIPI DSI peripheral pin */
    IOPORT_PERIPHERAL_MIPI = (0x1FUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a RGMII peripheral pin */
    IOPORT_PERIPHERAL_ETHER_RGMII = (0x18UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a ETHERNET slave controller peripheral pin */
    IOPORT_PERIPHERAL_ESC = (0x1AUL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a PDM peripheral pin */
    IOPORT_PERIPHERAL_PDM = (0x1BUL << IOPORT_PRV_PFS_PSEL_OFFSET),
} ioport_peripheral_t;

/** The thresholds supported by each MCU are in the MCU User's Manual as well as
 *  in the r_lvd module description on the stack tab of the RA project. */
typedef enum
{
    LVD_THRESHOLD_MONITOR_LEVEL_3_86V = 0x03UL, ///< 3.86V
    LVD_THRESHOLD_MONITOR_LEVEL_3_14V = 0x04UL, ///< 3.14V
    LVD_THRESHOLD_MONITOR_LEVEL_3_10V = 0x05UL, ///< 3.10V
    LVD_THRESHOLD_MONITOR_LEVEL_3_08V = 0x06UL, ///< 3.08V
    LVD_THRESHOLD_MONITOR_LEVEL_2_85V = 0x07UL, ///< 2.85V
    LVD_THRESHOLD_MONITOR_LEVEL_2_83V = 0x08UL, ///< 2.83V
    LVD_THRESHOLD_MONITOR_LEVEL_2_80V = 0x09UL, ///< 2.80V
    LVD_THRESHOLD_MONITOR_LEVEL_2_62V = 0x0AUL, ///< 2.62V
    LVD_THRESHOLD_MONITOR_LEVEL_2_33V = 0x0BUL, ///< 2.33V
    LVD_THRESHOLD_MONITOR_LEVEL_1_90V = 0x0CUL, ///< 1.90V
    LVD_THRESHOLD_MONITOR_LEVEL_1_86V = 0x0DUL, ///< 1.86V
    LVD_THRESHOLD_MONITOR_LEVEL_1_74V = 0x0EUL, ///< 1.74V
    LVD_THRESHOLD_MONITOR_LEVEL_1_71V = 0x0FUL, ///< 1.71V
    LVD_THRESHOLD_NOT_AVAILABLE       = 0xFFUL, ///< Not Used
} lvd_threshold_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
