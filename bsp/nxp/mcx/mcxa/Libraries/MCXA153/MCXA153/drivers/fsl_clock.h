/*
 * Copyright 2023, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_common.h"

/*! @addtogroup clock */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 1.0.0. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/*! @brief Configure whether driver controls clock
 *
 * When set to 0, peripheral drivers will enable clock in initialize function
 * and disable clock in de-initialize function. When set to 1, peripheral
 * driver will not control the clock, application could control the clock out of
 * the driver.
 *
 * @note All drivers share this feature switcher. If it is set to 1, application
 * should handle clock enable and disable for all drivers.
 */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
#define FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL 0U
#endif

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (96000000U)
#endif

/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
/*------------------------------------------------------------------------------
 clock_ip_name_t definition:
------------------------------------------------------------------------------*/
#define CLK_GATE_REG_OFFSET(value) (((uint32_t)(value)) >> 16U)
#define CLK_GATE_BIT_SHIFT(value)  (((uint32_t)(value)) & 0x0000FFFFU)

#define REG_PWM0SUBCTL (250U)

/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
typedef enum _clock_ip_name
{
    kCLOCK_GateINPUTMUX0   = (0x00000U | (0U)),                /*!< Clock gate name: INPUTMUX0     */
    kCLOCK_InputMux        = (0x00000U | (0U)),                /*!< Clock gate name: INPUTMUX0     */
    kCLOCK_GateI3C0        = (0x00000U | (1U)),                /*!< Clock gate name: I3C0          */
    kCLOCK_GateCTIMER0     = (0x00000U | (2U)),                /*!< Clock gate name: CTIMER0       */
    kCLOCK_GateCTIMER1     = (0x00000U | (3U)),                /*!< Clock gate name: CTIMER1       */
    kCLOCK_GateCTIMER2     = (0x00000U | (4U)),                /*!< Clock gate name: CTIMER2       */
    kCLOCK_GateFREQME      = (0x00000U | (5U)),                /*!< Clock gate name: FREQME        */
    kCLOCK_GateUTICK0      = (0x00000U | (6U)),                /*!< Clock gate name: UTICK0        */
    kCLOCK_GateWWDT0       = (0x00000U | (7U)),                /*!< Clock gate name: WWDT0         */
    kCLOCK_GateDMA         = (0x00000U | (8U)),                /*!< Clock gate name: DMA           */
    kCLOCK_GateAOI0        = (0x00000U | (9U)),                /*!< Clock gate name: AOI0          */
    kCLOCK_GateCRC         = (0x00000U | (10U)),               /*!< Clock gate name: CRC           */
    kCLOCK_Crc0            = (0x00000U | (10U)),               /*!< Clock gate name: CRC           */
    kCLOCK_GateEIM         = (0x00000U | (11U)),               /*!< Clock gate name: EIM           */
    kCLOCK_GateERM         = (0x00000U | (12U)),               /*!< Clock gate name: ERM           */
    kCLOCK_GateLPI2C0      = (0x00000U | (16U)),               /*!< Clock gate name: LPI2C0        */
    kCLOCK_GateLPSPI0      = (0x00000U | (17U)),               /*!< Clock gate name: LPSPI0        */
    kCLOCK_GateLPSPI1      = (0x00000U | (18U)),               /*!< Clock gate name: LPSPI1        */
    kCLOCK_GateLPUART0     = (0x00000U | (19U)),               /*!< Clock gate name: LPUART0       */
    kCLOCK_GateLPUART1     = (0x00000U | (20U)),               /*!< Clock gate name: LPUART1       */
    kCLOCK_GateLPUART2     = (0x00000U | (21U)),               /*!< Clock gate name: LPUART2       */
    kCLOCK_GateUSB0        = (0x00000U | (22U)),               /*!< Clock gate name: USB0          */
    kCLOCK_GateQDC0        = (0x00000U | (23U)),               /*!< Clock gate name: QDC0          */
    kCLOCK_GateFLEXPWM0    = (0x00000U | (24U)),               /*!< Clock gate name: FLEXPWM0      */
    kCLOCK_GateOSTIMER0    = (0x00000U | (25U)),               /*!< Clock gate name: OSTIMER0      */
    kCLOCK_GateADC0        = (0x00000U | (26U)),               /*!< Clock gate name: ADC0          */
    kCLOCK_GateCMP0        = (0x00000U | (27U)),               /*!< Clock gate name: CMP0          */
    kCLOCK_GateCMP1        = (0x00000U | (28U)),               /*!< Clock gate name: CMP1          */
    kCLOCK_GatePORT0       = (0x00000U | (29U)),               /*!< Clock gate name: PORT0         */
    kCLOCK_GatePORT1       = (0x00000U | (30U)),               /*!< Clock gate name: PORT1         */
    kCLOCK_GatePORT2       = (0x00000U | (31U)),               /*!< Clock gate name: PORT2         */
    kCLOCK_GatePORT3       = ((0x10U << 16U) | (0U)),          /*!< Clock gate name: PORT3         */
    kCLOCK_GateATX0        = ((0x10U << 16U) | (1U)),          /*!< Clock gate name: ATX0          */
    kCLOCK_GateMTR         = ((0x10U << 16U) | (2U)),          /*!< Clock gate name: MTR           */
    kCLOCK_GateTCU         = ((0x10U << 16U) | (3U)),          /*!< Clock gate name: TCU           */
    kCLOCK_GateEZRAMC_RAMA = ((0x10U << 16U) | (4U)),          /*!< Clock gate name: EZRAMC_RAMA   */
    kCLOCK_GateGPIO0       = ((0x10U << 16U) | (5U)),          /*!< Clock gate name: GPIO0         */
    kCLOCK_GateGPIO1       = ((0x10U << 16U) | (6U)),          /*!< Clock gate name: GPIO1         */
    kCLOCK_GateGPIO2       = ((0x10U << 16U) | (7U)),          /*!< Clock gate name: GPIO2         */
    kCLOCK_GateGPIO3       = ((0x10U << 16U) | (8U)),          /*!< Clock gate name: GPIO3         */
    kCLOCK_GateROMCP       = ((0x10U << 16U) | (9U)),          /*!< Clock gate name: ROMCP         */
    kCLOCK_GatePWMSM0      = ((REG_PWM0SUBCTL << 16U) | (0U)), /*!< Clock gate name: FlexPWM SM0   */
    kCLOCK_GatePWMSM1      = ((REG_PWM0SUBCTL << 16U) | (1U)), /*!< Clock gate name: FlexPWM SM1   */
    kCLOCK_GatePWMSM2      = ((REG_PWM0SUBCTL << 16U) | (2U)), /*!< Clock gate name: FlexPWM SM2   */
    kCLOCK_GateNotAvail    = (0xFFFFFFFFU),                    /**< Clock gate name: None          */
} clock_ip_name_t;

/*! @brief Clock ip name array for AOI. */
#define AOI_CLOCKS      \
    {                   \
        kCLOCK_GateAOI0 \
    }
/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS     \
    {                  \
        kCLOCK_GateCRC \
    }
/*! @brief Clock ip name array for CTIMER. */
#define CTIMER_CLOCKS                                              \
    {                                                              \
        kCLOCK_GateCTIMER0, kCLOCK_GateCTIMER1, kCLOCK_GateCTIMER2 \
    }
/*! @brief Clock ip name array for DMA. */
#define DMA_CLOCKS     \
    {                  \
        kCLOCK_GateDMA \
    }
/*! @brief Clock gate name array for EDMA. */
#define EDMA_CLOCKS    \
    {                  \
        kCLOCK_GateDMA \
    }
/*! @brief Clock ip name array for ERM. */
#define ERM_CLOCKS     \
    {                  \
        kCLOCK_GateERM \
    }
/*! @brief Clock ip name array for EIM. */
#define EIM_CLOCKS     \
    {                  \
        kCLOCK_GateEIM \
    }
/*! @brief Clock ip name array for FREQME. */
#define FREQME_CLOCKS     \
    {                     \
        kCLOCK_GateFREQME \
    }
/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                                                            \
    {                                                                          \
        kCLOCK_GateGPIO0, kCLOCK_GateGPIO1, kCLOCK_GateGPIO2, kCLOCK_GateGPIO3 \
    }
/*! @brief Clock ip name array for I3C */
#define I3C_CLOCKS      \
    {                   \
        kCLOCK_GateI3C0 \
    }
/*! @brief Clock ip name array for INPUTMUX. */
#define INPUTMUX_CLOCKS      \
    {                        \
        kCLOCK_GateINPUTMUX0 \
    }
/*! @brief Clock ip name array for GPIO. */
#define LPCMP_CLOCKS                     \
    {                                    \
        kCLOCK_GateCMP0, kCLOCK_GateCMP1 \
    }
/*! @brief Clock ip name array for LPADC. */
#define LPADC_CLOCKS    \
    {                   \
        kCLOCK_GateADC0 \
    }
/*! @brief Clock ip name array for LPUART. */
#define LPUART_CLOCKS                                              \
    {                                                              \
        kCLOCK_GateLPUART0, kCLOCK_GateLPUART1, kCLOCK_GateLPUART2 \
    }
/*! @brief Clock ip name array for LPI2C. */
#define LPI2C_CLOCKS      \
    {                     \
        kCLOCK_GateLPI2C0 \
    }
/*! @brief Clock ip name array for LSPI. */
#define LPSPI_CLOCKS                         \
    {                                        \
        kCLOCK_GateLPSPI0, kCLOCK_GateLPSPI1 \
    }
/*! @brief Clock ip name array for MTR. */
#define MTR_CLOCKS     \
    {                  \
        kCLOCK_GateMTR \
    }
/*! @brief Clock ip name array for OSTIMER. */
#define OSTIMER_CLOCKS      \
    {                       \
        kCLOCK_GateOSTIMER0 \
    }

/*! @brief Clock ip name array for PWM. */
#define PWM_CLOCKS                                                  \
    {                                                               \
        {                                                           \
            kCLOCK_GatePWMSM0, kCLOCK_GatePWMSM1, kCLOCK_GatePWMSM2 \
        }                                                           \
    }
/*! @brief Clock ip name array for QDC. */
#define QDC_CLOCKS      \
    {                   \
        kCLOCK_GateQDC0 \
    }
/*! @brief Clock ip name array for UTICK. */
#define UTICK_CLOCKS      \
    {                     \
        kCLOCK_GateUTICK0 \
    }
/*! @brief Clock ip name array for WWDT. */
#define WWDT_CLOCKS      \
    {                    \
        kCLOCK_GateWWDT0 \
    }

/*! @brief Peripherals clock source definition. */
#define BUS_CLK kCLOCK_BusClk

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_MainClk,    /*!< MAIN_CLK                   */
    kCLOCK_CoreSysClk, /*!< Core/system clock(CPU_CLK) */
    kCLOCK_SYSTEM_CLK, /*!< AHB clock                  */
    kCLOCK_BusClk,     /*!< Bus clock (AHB clock)      */
    kCLOCK_ExtClk,     /*!< External Clock             */
    kCLOCK_FroHf,      /*!< FRO192                     */
    kCLOCK_FroHfDiv,   /*!< Divided by FRO192          */
    kCLOCK_Clk48M,     /*!< CLK48M                     */
    kCLOCK_Fro12M,     /*!< FRO12M                     */
    kCLOCK_Clk1M,      /*!< CLK1M                      */
    kCLOCK_Fro16K,     /*!< FRO16K                     */
    kCLOCK_Clk16K0,    /*!< CLK16K[0]                  */
    kCLOCK_Clk16K1,    /*!< CLK16K[1]                  */
    kCLOCK_SLOW_CLK,   /*!< SYSTEM_CLK divided by 4    */
} clock_name_t;

/*! @brief Clock Mux Switches
 *  The encoding is as follows each connection identified is 32bits wide while 24bits are valuable
 *  starting from LSB upwards
 *
 *  [4 bits for choice, 0 means invalid choice] [8 bits mux ID]*
 *
 */

#define CLK_ATTACH_REG_OFFSET(value) (((uint32_t)(value)) >> 16U)
#define CLK_ATTACH_CLK_SEL(value)    (((uint32_t)(value)) & 0x0000FFFFU)
#define CLK_ATTACH_MUX(reg, sel)     ((((uint32_t)(reg)) << 16U) | (sel))

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_select_name
{
    kCLOCK_SelI3C0_FCLK = (0x0A0U), /*!< I3C0_FCLK clock selection */
    kCLOCK_SelCTIMER0   = (0x0A8U), /*!< CTIMER0   clock selection */
    kCLOCK_SelCTIMER1   = (0x0B0U), /*!< CTIMER1   clock selection */
    kCLOCK_SelCTIMER2   = (0x0B8U), /*!< CTIMER2   clock selection */
    kCLOCK_SelLPI2C0    = (0x0C8U), /*!< LPI2C0    clock selection */
    kCLOCK_SelLPSPI0    = (0x0D0U), /*!< LPSPI0    clock selection */
    kCLOCK_SelLPSPI1    = (0x0D8U), /*!< LPSPI1    clock selection */
    kCLOCK_SelLPUART0   = (0x0E0U), /*!< LPUART0   clock selection */
    kCLOCK_SelLPUART1   = (0x0E8U), /*!< LPUART1   clock selection */
    kCLOCK_SelLPUART2   = (0x0F0U), /*!< LPUART2   clock selection */
    kCLOCK_SelUSB0      = (0x0F8U), /*!< USB0      clock selection */
    kCLOCK_SelLPTMR0    = (0x100U), /*!< LPTMR0    clock selection */
    kCLOCK_SelOSTIMER0  = (0x108U), /*!< OSTIMER0  clock selection */
    kCLOCK_SelADC0      = (0x110U), /*!< ADC0      clock selection */
    kCLOCK_SelCMP0_RR   = (0x120U), /*!< CMP0_RR   clock selection */
    kCLOCK_SelCMP1_RR   = (0x130U), /*!< CMP1_RR   clock selection */
    kCLOCK_SelTRACE     = (0x138U), /*!< TRACE clock selection     */
    kCLOCK_SelCLKOUT    = (0x140U), /*!< CLKOUT    clock selection */
    kCLOCK_SelSYSTICK   = (0x148U), /*!< SYSTICK   clock selection */
    kCLOCK_SelSCGSCS    = (0x200U), /*!< SCG SCS   clock selection */
    kCLOCK_SelMax       = (0x200U), /*!< MAX       clock selection */
} clock_select_name_t;

/*!
 * @brief The enumerator of clock attach Id.
 */
typedef enum _clock_attach_id
{
    kCLK_IN_to_MAIN_CLK  = CLK_ATTACH_MUX(kCLOCK_SelSCGSCS, 1U), /*!< Attach clk_in to MAIN_CLK.     */
    kFRO12M_to_MAIN_CLK  = CLK_ATTACH_MUX(kCLOCK_SelSCGSCS, 2U), /*!< Attach FRO_12M to MAIN_CLK.    */
    kFRO_HF_to_MAIN_CLK  = CLK_ATTACH_MUX(kCLOCK_SelSCGSCS, 3U), /*!< Attach FRO_HF to MAIN_CLK.     */
    kCLK_16K_to_MAIN_CLK = CLK_ATTACH_MUX(kCLOCK_SelSCGSCS, 4U), /*!< Attach CLK_16K[1] to MAIN_CLK. */
    kNONE_to_MAIN_CLK    = CLK_ATTACH_MUX(kCLOCK_SelSCGSCS, 7U), /*!< Attach NONE to MAIN_CLK.       */

    kFRO12M_to_I3C0FCLK     = CLK_ATTACH_MUX(kCLOCK_SelI3C0_FCLK, 0U), /*!< Attach FRO12M to I3C0FCLK.     */
    kFRO_HF_DIV_to_I3C0FCLK = CLK_ATTACH_MUX(kCLOCK_SelI3C0_FCLK, 2U), /*!< Attach FRO_HF_DIV to I3C0FCLK. */
    kCLK_IN_to_I3C0FCLK     = CLK_ATTACH_MUX(kCLOCK_SelI3C0_FCLK, 3U), /*!< Attach CLK_IN to I3C0FCLK.     */
    kCLK_1M_to_I3C0FCLK     = CLK_ATTACH_MUX(kCLOCK_SelI3C0_FCLK, 5U), /*!< Attach CLK_1M to I3C0FCLK.     */
    kNONE_to_I3C0FCLK       = CLK_ATTACH_MUX(kCLOCK_SelI3C0_FCLK, 7U), /*!< Attach NONE to I3C0FCLK.       */

    kFRO12M_to_CTIMER0  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER0, 0U), /*!< Attach FRO12M to CTIMER0.  */
    kFRO_HF_to_CTIMER0  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER0, 1U), /*!< Attach FRO_HF to CTIMER0.  */
    kCLK_IN_to_CTIMER0  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER0, 3U), /*!< Attach CLK_IN to CTIMER0.  */
    kCLK_16K_to_CTIMER0 = CLK_ATTACH_MUX(kCLOCK_SelCTIMER0, 4U), /*!< Attach CLK_16K to CTIMER0. */
    kCLK_1M_to_CTIMER0  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER0, 5U), /*!< Attach CLK_1M to CTIMER0.  */
    kNONE_to_CTIMER0    = CLK_ATTACH_MUX(kCLOCK_SelCTIMER0, 7U), /*!< Attach NONE to CTIMER0.    */

    kFRO12M_to_CTIMER1  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER1, 0U), /*!< Attach FRO12M to CTIMER1.  */
    kFRO_HF_to_CTIMER1  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER1, 1U), /*!< Attach FRO_HF to CTIMER1.  */
    kCLK_IN_to_CTIMER1  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER1, 3U), /*!< Attach CLK_IN to CTIMER1.  */
    kCLK_16K_to_CTIMER1 = CLK_ATTACH_MUX(kCLOCK_SelCTIMER1, 4U), /*!< Attach CLK_16K to CTIMER1. */
    kCLK_1M_to_CTIMER1  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER1, 5U), /*!< Attach CLK_1M to CTIMER1.  */
    kNONE_to_CTIMER1    = CLK_ATTACH_MUX(kCLOCK_SelCTIMER1, 7U), /*!< Attach NONE to CTIMER1.    */

    kFRO12M_to_CTIMER2  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER2, 0U), /*!< Attach FRO12M to CTIMER2.  */
    kFRO_HF_to_CTIMER2  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER2, 1U), /*!< Attach FRO_HF to CTIMER2.  */
    kCLK_IN_to_CTIMER2  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER2, 3U), /*!< Attach CLK_IN to CTIMER2.  */
    kCLK_16K_to_CTIMER2 = CLK_ATTACH_MUX(kCLOCK_SelCTIMER2, 4U), /*!< Attach CLK_16K to CTIMER2. */
    kCLK_1M_to_CTIMER2  = CLK_ATTACH_MUX(kCLOCK_SelCTIMER2, 5U), /*!< Attach CLK_1M to CTIMER2.  */
    kNONE_to_CTIMER2    = CLK_ATTACH_MUX(kCLOCK_SelCTIMER2, 7U), /*!< Attach NONE to CTIMER2.    */

    kFRO12M_to_LPI2C0     = CLK_ATTACH_MUX(kCLOCK_SelLPI2C0, 0U), /*!< Attach FRO12M to LPI2C0.     */
    kFRO_HF_DIV_to_LPI2C0 = CLK_ATTACH_MUX(kCLOCK_SelLPI2C0, 2U), /*!< Attach FRO_HF_DIV to LPI2C0. */
    kCLK_IN_to_LPI2C0     = CLK_ATTACH_MUX(kCLOCK_SelLPI2C0, 3U), /*!< Attach CLK_IN to LPI2C0.     */
    kCLK_1M_to_LPI2C0     = CLK_ATTACH_MUX(kCLOCK_SelLPI2C0, 5U), /*!< Attach CLK_1M to LPI2C0.     */
    kNONE_to_LPI2C0       = CLK_ATTACH_MUX(kCLOCK_SelLPI2C0, 7U), /*!< Attach NONE to LPI2C0.       */

    kFRO12M_to_LPSPI0     = CLK_ATTACH_MUX(kCLOCK_SelLPSPI0, 0U), /*!< Attach FRO12M to LPSPI0.     */
    kFRO_HF_DIV_to_LPSPI0 = CLK_ATTACH_MUX(kCLOCK_SelLPSPI0, 2U), /*!< Attach FRO_HF_DIV to LPSPI0. */
    kCLK_IN_to_LPSPI0     = CLK_ATTACH_MUX(kCLOCK_SelLPSPI0, 3U), /*!< Attach CLK_IN to LPSPI0.     */
    kCLK_1M_to_LPSPI0     = CLK_ATTACH_MUX(kCLOCK_SelLPSPI0, 5U), /*!< Attach CLK_1M to LPSPI0.     */
    kNONE_to_LPSPI0       = CLK_ATTACH_MUX(kCLOCK_SelLPSPI0, 7U), /*!< Attach NONE to LPSPI0.       */

    kFRO12M_to_LPSPI1     = CLK_ATTACH_MUX(kCLOCK_SelLPSPI1, 0U), /*!< Attach FRO12M to LPSPI1.     */
    kFRO_HF_DIV_to_LPSPI1 = CLK_ATTACH_MUX(kCLOCK_SelLPSPI1, 2U), /*!< Attach FRO_HF_DIV to LPSPI1. */
    kCLK_IN_to_LPSPI1     = CLK_ATTACH_MUX(kCLOCK_SelLPSPI1, 3U), /*!< Attach CLK_IN to LPSPI1.     */
    kCLK_1M_to_LPSPI1     = CLK_ATTACH_MUX(kCLOCK_SelLPSPI1, 5U), /*!< Attach CLK_1M to LPSPI1.     */
    kNONE_to_LPSPI1       = CLK_ATTACH_MUX(kCLOCK_SelLPSPI1, 7U), /*!< Attach NONE to LPSPI1.       */

    kFRO12M_to_LPUART0     = CLK_ATTACH_MUX(kCLOCK_SelLPUART0, 0U), /*!< Attach FRO12M to LPUART0.     */
    kFRO_HF_DIV_to_LPUART0 = CLK_ATTACH_MUX(kCLOCK_SelLPUART0, 2U), /*!< Attach FRO_HF_DIV to LPUART0. */
    kCLK_IN_to_LPUART0     = CLK_ATTACH_MUX(kCLOCK_SelLPUART0, 3U), /*!< Attach CLK_IN to LPUART0.     */
    kCLK_16K_to_LPUART0    = CLK_ATTACH_MUX(kCLOCK_SelLPUART0, 4U), /*!< Attach CLK_16K to LPUART0.    */
    kCLK_1M_to_LPUART0     = CLK_ATTACH_MUX(kCLOCK_SelLPUART0, 5U), /*!< Attach CLK_1M to LPUART0.     */
    kNONE_to_LPUART0       = CLK_ATTACH_MUX(kCLOCK_SelLPUART0, 7U), /*!< Attach NONE to LPUART0.       */

    kFRO12M_to_LPUART1     = CLK_ATTACH_MUX(kCLOCK_SelLPUART1, 0U), /*!< Attach FRO12M to LPUART1.     */
    kFRO_HF_DIV_to_LPUART1 = CLK_ATTACH_MUX(kCLOCK_SelLPUART1, 2U), /*!< Attach FRO_HF_DIV to LPUART1. */
    kCLK_IN_to_LPUART1     = CLK_ATTACH_MUX(kCLOCK_SelLPUART1, 3U), /*!< Attach CLK_IN to LPUART1.     */
    kCLK_16K_to_LPUART1    = CLK_ATTACH_MUX(kCLOCK_SelLPUART1, 4U), /*!< Attach CLK_16K to LPUART1.    */
    kCLK_1M_to_LPUART1     = CLK_ATTACH_MUX(kCLOCK_SelLPUART1, 5U), /*!< Attach CLK_1M to LPUART1.     */
    kNONE_to_LPUART1       = CLK_ATTACH_MUX(kCLOCK_SelLPUART1, 7U), /*!< Attach NONE to LPUART1.       */

    kFRO12M_to_LPUART2     = CLK_ATTACH_MUX(kCLOCK_SelLPUART2, 0U), /*!< Attach FRO12M to LPUART2.     */
    kFRO_HF_DIV_to_LPUART2 = CLK_ATTACH_MUX(kCLOCK_SelLPUART2, 2U), /*!< Attach FRO_HF_DIV to LPUART2. */
    kCLK_IN_to_LPUART2     = CLK_ATTACH_MUX(kCLOCK_SelLPUART2, 3U), /*!< Attach CLK_IN to LPUART2.     */
    kCLK_16K_to_LPUART2    = CLK_ATTACH_MUX(kCLOCK_SelLPUART2, 4U), /*!< Attach CLK_16K to LPUART2.    */
    kCLK_1M_to_LPUART2     = CLK_ATTACH_MUX(kCLOCK_SelLPUART2, 5U), /*!< Attach CLK_1M to LPUART2.     */
    kNONE_to_LPUART2       = CLK_ATTACH_MUX(kCLOCK_SelLPUART2, 7U), /*!< Attach NONE to LPUART2.       */

    kCLK_48M_to_USB0 = CLK_ATTACH_MUX(kCLOCK_SelUSB0, 1U), /*!< Attach FRO12M to USB0. */
    kCLK_IN_to_USB0  = CLK_ATTACH_MUX(kCLOCK_SelUSB0, 2U), /*!< Attach CLK_IN to USB0. */
    kNONE_to_USB0    = CLK_ATTACH_MUX(kCLOCK_SelUSB0, 3U), /*!< Attach NONE to USB0.   */

    kFRO12M_to_LPTMR0     = CLK_ATTACH_MUX(kCLOCK_SelLPTMR0, 0U), /*!< Attach FRO12M to LPTMR0.     */
    kFRO_HF_DIV_to_LPTMR0 = CLK_ATTACH_MUX(kCLOCK_SelLPTMR0, 2U), /*!< Attach FRO_HF_DIV to LPTMR0. */
    kCLK_IN_to_LPTMR0     = CLK_ATTACH_MUX(kCLOCK_SelLPTMR0, 3U), /*!< Attach CLK_IN to LPTMR0.     */
    kCLK_1M_to_LPTMR0     = CLK_ATTACH_MUX(kCLOCK_SelLPTMR0, 5U), /*!< Attach CLK_1M to LPTMR0.     */
    kNONE_to_LPTMR0       = CLK_ATTACH_MUX(kCLOCK_SelLPTMR0, 7U), /*!< Attach NONE to LPTMR0.       */

    kCLK_16K_to_OSTIMER = CLK_ATTACH_MUX(kCLOCK_SelOSTIMER0, 0U), /*!< Attach FRO16K to OSTIMER0. */
    kCLK_1M_to_OSTIMER  = CLK_ATTACH_MUX(kCLOCK_SelOSTIMER0, 2U), /*!< Attach CLK_1M to OSTIMER0. */
    kNONE_to_OSTIMER    = CLK_ATTACH_MUX(kCLOCK_SelOSTIMER0, 3U), /*!< Attach NONE to OSTIMER0.   */

    kFRO12M_to_ADC0 = CLK_ATTACH_MUX(kCLOCK_SelADC0, 0U), /*!< Attach FRO12M to ADC0. */
    kFRO_HF_to_ADC0 = CLK_ATTACH_MUX(kCLOCK_SelADC0, 1U), /*!< Attach FRO_HF to ADC0. */
    kCLK_IN_to_ADC0 = CLK_ATTACH_MUX(kCLOCK_SelADC0, 3U), /*!< Attach CLK_IN to ADC0. */
    kCLK_1M_to_ADC0 = CLK_ATTACH_MUX(kCLOCK_SelADC0, 5U), /*!< Attach CLK_1M to ADC0. */
    kNONE_to_ADC0   = CLK_ATTACH_MUX(kCLOCK_SelADC0, 7U), /*!< Attach NONE to ADC0.   */

    kFRO12M_to_CMP0     = CLK_ATTACH_MUX(kCLOCK_SelCMP0_RR, 0U), /*!< Attach FRO12M to CMP0.     */
    kFRO_HF_DIV_to_CMP0 = CLK_ATTACH_MUX(kCLOCK_SelCMP0_RR, 2U), /*!< Attach FRO_HF_DIV to CMP0. */
    kCLK_IN_to_CMP0     = CLK_ATTACH_MUX(kCLOCK_SelCMP0_RR, 3U), /*!< Attach CLK_IN to CMP0.     */
    kCLK_1M_to_CMP0     = CLK_ATTACH_MUX(kCLOCK_SelCMP0_RR, 5U), /*!< Attach CLK_1M to CMP0.     */
    kNONE_to_CMP0       = CLK_ATTACH_MUX(kCLOCK_SelCMP0_RR, 7U), /*!< Attach NONE to CMP0.       */

    kFRO12M_to_CMP1     = CLK_ATTACH_MUX(kCLOCK_SelCMP1_RR, 0U), /*!< Attach FRO12M to CMP1.     */
    kFRO_HF_DIV_to_CMP1 = CLK_ATTACH_MUX(kCLOCK_SelCMP1_RR, 2U), /*!< Attach FRO_HF_DIV to CMP1. */
    kCLK_IN_to_CMP1     = CLK_ATTACH_MUX(kCLOCK_SelCMP1_RR, 3U), /*!< Attach CLK_IN to CMP1.     */
    kCLK_1M_to_CMP1     = CLK_ATTACH_MUX(kCLOCK_SelCMP1_RR, 5U), /*!< Attach CLK_1M to CMP1.     */
    kNONE_to_CMP1       = CLK_ATTACH_MUX(kCLOCK_SelCMP1_RR, 7U), /*!< Attach NONE to CMP1.       */

    kCPU_CLK_to_TRACE = CLK_ATTACH_MUX(kCLOCK_SelTRACE, 0U), /*!< Attach CPU_CLK to TRACE. */
    kCLK_1M_to_TRACE  = CLK_ATTACH_MUX(kCLOCK_SelTRACE, 1U), /*!< Attach CLK_1M to TRACE.  */
    kCLK_16K_to_TRACE = CLK_ATTACH_MUX(kCLOCK_SelTRACE, 2U), /*!< Attach CLK_16K to TRACE. */
    kNONE_to_TRACE    = CLK_ATTACH_MUX(kCLOCK_SelTRACE, 3U), /*!< Attach NONE to TRACE.    */

    kFRO12M_to_CLKOUT     = CLK_ATTACH_MUX(kCLOCK_SelCLKOUT, 0U), /*!< Attach FRO12M to CLKOUT.     */
    kFRO_HF_DIV_to_CLKOUT = CLK_ATTACH_MUX(kCLOCK_SelCLKOUT, 1U), /*!< Attach FRO_HF_DIV to CLKOUT. */
    kCLK_IN_to_CLKOUT     = CLK_ATTACH_MUX(kCLOCK_SelCLKOUT, 2U), /*!< Attach CLK_IN to CLKOUT.     */
    kCLK_16K_to_CLKOUT    = CLK_ATTACH_MUX(kCLOCK_SelCLKOUT, 3U), /*!< Attach CLK_16K to CLKOUT.    */
    kSLOW_CLK_to_CLKOUT   = CLK_ATTACH_MUX(kCLOCK_SelCLKOUT, 6U), /*!< Attach SLOW_CLK to CLKOUT.   */
    kNONE_to_CLKOUT       = CLK_ATTACH_MUX(kCLOCK_SelCLKOUT, 7U), /*!< Attach NONE to CLKOUT.       */

    kCPU_CLK_to_SYSTICK = CLK_ATTACH_MUX(kCLOCK_SelSYSTICK, 0U), /*!< Attach CPU_CLK to SYSTICK. */
    kCLK_1M_to_SYSTICK  = CLK_ATTACH_MUX(kCLOCK_SelSYSTICK, 1U), /*!< Attach CLK_1M to SYSTICK.  */
    kCLK_16K_to_SYSTICK = CLK_ATTACH_MUX(kCLOCK_SelSYSTICK, 2U), /*!< Attach CLK_16K to SYSTICK. */
    kNONE_to_SYSTICK    = CLK_ATTACH_MUX(kCLOCK_SelSYSTICK, 3U), /*!< Attach NONE to SYSTICK.    */

    kNONE_to_NONE = (0xFFFFFFFFU), /*!< Attach NONE to NONE. */

} clock_attach_id_t;

/*! @brief Clock dividers */
typedef enum _clock_div_name
{
    kCLOCK_DivI3C0_FCLK  = (0x0A4U), /*!< I3C0_FCLK  clock divider */
    kCLOCK_DivCTIMER0    = (0x0ACU), /*!< CTIMER0    clock divider */
    kCLOCK_DivCTIMER1    = (0x0B4U), /*!< CTIMER1    clock divider */
    kCLOCK_DivCTIMER2    = (0x0BCU), /*!< CTIMER2    clock divider */
    kCLOCK_DivWWDT0      = (0x0C4U), /*!< WWDT0      clock divider */
    kCLOCK_DivLPI2C0     = (0x0CCU), /*!< LPI2C0     clock divider */
    kCLOCK_DivLPSPI0     = (0x0D4U), /*!< LPSPI0     clock divider */
    kCLOCK_DivLPSPI1     = (0x0DCU), /*!< LPSPI1     clock divider */
    kCLOCK_DivLPUART0    = (0x0E4U), /*!< LPUART0    clock divider */
    kCLOCK_DivLPUART1    = (0x0ECU), /*!< LPUART1    clock divider */
    kCLOCK_DivLPUART2    = (0x0F4U), /*!< LPUART2    clock divider */
    kCLOCK_DivLPTMR0     = (0x104U), /*!< LPTMR0     clock divider */
    kCLOCK_DivADC0       = (0x114U), /*!< ADC0       clock divider */
    kCLOCK_DivCMP0_FUNC  = (0x11CU), /*!< CMP0_FUNC  clock divider */
    kCLOCK_DivCMP0_RR    = (0x124U), /*!< CMP0_RR    clock divider */
    kCLOCK_DivCMP1_FUNC  = (0x12CU), /*!< CMP1_FUNC  clock divider */
    kCLOCK_DivCMP1_RR    = (0x134U), /*!< CMP1_RR    clock divider */
    kCLOCK_DivTRACE      = (0x13CU), /*!< TRACE      clock divider */
    kCLOCK_DivCLKOUT     = (0x144U), /*!< CLKOUT     clock divider */
    kCLOCK_DivSYSTICK    = (0x14CU), /*!< SYSTICK    clock divider */
    kCLOCK_DivFRO_HF_DIV = (0x154U), /*!< FRO_HF_DIV clock divider */
    kCLOCK_DivSLOWCLK    = (0x378U), /*!< SLOWCLK    clock divider */
    kCLOCK_DivAHBCLK     = (0x380U), /*!< System     clock divider */
    kCLOCK_DivMax        = (0x380U), /*!< MAX        clock divider */
} clock_div_name_t;

/*!
 * @brief firc trim mode.
 */
typedef enum _firc_trim_mode
{
    kSCG_FircTrimNonUpdate = SCG_FIRCCSR_FIRCTREN_MASK,
    /*!< Trim enable but not enable trim value update. In this mode, the
     trim value is fixed to the initialized value which is defined by
     trimCoar and trimFine in configure structure \ref firc_trim_config_t.*/

    kSCG_FircTrimUpdate = SCG_FIRCCSR_FIRCTREN_MASK | SCG_FIRCCSR_FIRCTRUP_MASK
    /*!< Trim enable and trim value update enable. In this mode, the trim
     value is auto update. */

} firc_trim_mode_t;

/*!
 * @brief firc trim source.
 */
typedef enum _firc_trim_src
{
    kSCG_FircTrimSrcUsb0   = 0U, /*!< USB0 start of frame (1kHz). */
    kSCG_FircTrimSrcSysOsc = 2U, /*!< System OSC.                 */
} firc_trim_src_t;

/*!
 * @brief firc trim configuration.
 */
typedef struct _firc_trim_config
{
    firc_trim_mode_t trimMode; /*!< Trim mode. */
    firc_trim_src_t trimSrc;   /*!< Trim source. */
    uint16_t trimDiv;          /*!< Divider of SOSC. */
    uint8_t trimCoar;          /*!< Trim coarse value; Irrelevant if trimMode is kSCG_TrimUpdate. */
    uint8_t trimFine;          /*!< Trim fine value; Irrelevant if trimMode is kSCG_TrimUpdate. */
} firc_trim_config_t;

/*!
 * @brief sirc trim mode.
 */
typedef enum _sirc_trim_mode
{
    kSCG_SircTrimNonUpdate = SCG_SIRCCSR_SIRCTREN_MASK,
    /*!< Trim enable but not enable trim value update. In this mode, the
     trim value is fixed to the initialized value which is defined by
     trimCoar and trimFine in configure structure \ref sirc_trim_config_t.*/

    kSCG_SircTrimUpdate = SCG_SIRCCSR_SIRCTREN_MASK | SCG_SIRCCSR_SIRCTRUP_MASK
    /*!< Trim enable and trim value update enable. In this mode, the trim
     value is auto update. */

} sirc_trim_mode_t;

/*!
 * @brief sirc trim source.
 */
typedef enum _sirc_trim_src
{
    kNoTrimSrc             = 0,  /*!< No external tirm source.    */
    kSCG_SircTrimSrcSysOsc = 2U, /*!< System OSC.                 */
} sirc_trim_src_t;

/*!
 * @brief sirc trim configuration.
 */
typedef struct _sirc_trim_config
{
    sirc_trim_mode_t trimMode; /*!< Trim mode.       */
    sirc_trim_src_t trimSrc;   /*!< Trim source.     */
    uint16_t trimDiv;          /*!< Divider of SOSC. */
    uint8_t cltrim;            /*!< Trim coarse value; Irrelevant if trimMode is kSCG_TrimUpdate. */
    uint8_t ccotrim;           /*!< Trim fine value; Irrelevant if trimMode is kSCG_TrimUpdate. */
} sirc_trim_config_t;

/*!
 * @brief SCG system OSC monitor mode.
 */
typedef enum _scg_sosc_monitor_mode
{
    kSCG_SysOscMonitorDisable = 0U,                      /*!< Monitor disabled. */
    kSCG_SysOscMonitorInt     = SCG_SOSCCSR_SOSCCM_MASK, /*!< Interrupt when the SOSC error is detected. */
    kSCG_SysOscMonitorReset =
        SCG_SOSCCSR_SOSCCM_MASK | SCG_SOSCCSR_SOSCCMRE_MASK /*!< Reset when the SOSC error is detected.     */
} scg_sosc_monitor_mode_t;

/*!
 * @brief firc trim source.
 */
typedef enum _clke_16k
{
    kCLKE_16K_SYSTEM   = VBAT_FROCLKE_CLKE(1U), /*!< To VSYS domain.     */
    kCLKE_16K_COREMAIN = VBAT_FROCLKE_CLKE(2U)  /*!< To VDD_CORE domain. */
} clke_16k_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Enable the clock for specific IP.
 * @param clk : Clock to be enabled.
 * @return  Nothing
 */
static inline void CLOCK_EnableClock(clock_ip_name_t clk)
{
    uint32_t reg_offset         = CLK_GATE_REG_OFFSET(clk);
    uint32_t bit_shift          = CLK_GATE_BIT_SHIFT(clk);
    volatile uint32_t *pClkCtrl = (volatile uint32_t *)((uint32_t)(&(MRCC0->MRCC_GLB_CC0_SET)) + reg_offset);

    if (clk == kCLOCK_GateNotAvail)
    {
        return;
    }

    /* Unlock clock configuration */
    SYSCON->CLKUNLOCK &= ~SYSCON_CLKUNLOCK_UNLOCK_MASK;

    if (reg_offset == REG_PWM0SUBCTL)
    {
        SYSCON->PWM0SUBCTL |= (1UL << bit_shift);
        MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_FLEXPWM0_MASK;
    }
    else
    {
        *pClkCtrl = (1UL << bit_shift);
    }

    /* Freeze clock configuration */
    SYSCON->CLKUNLOCK |= SYSCON_CLKUNLOCK_UNLOCK_MASK;
}

/**
 * @brief Disable the clock for specific IP.
 * @param clk : Clock to be Disabled.
 * @return  Nothing
 */
static inline void CLOCK_DisableClock(clock_ip_name_t clk)
{
    uint32_t reg_offset         = CLK_GATE_REG_OFFSET(clk);
    uint32_t bit_shift          = CLK_GATE_BIT_SHIFT(clk);
    volatile uint32_t *pClkCtrl = (volatile uint32_t *)((uint32_t)(&(MRCC0->MRCC_GLB_CC0_CLR)) + reg_offset);

    if (clk == kCLOCK_GateNotAvail)
    {
        return;
    }

    /* Unlock clock configuration */
    SYSCON->CLKUNLOCK &= ~SYSCON_CLKUNLOCK_UNLOCK_MASK;

    if (reg_offset == REG_PWM0SUBCTL)
    {
        SYSCON->PWM0SUBCTL &= ~(1UL << bit_shift);

        if (0U == (SYSCON->PWM0SUBCTL & 0xFU))
        {
            MRCC0->MRCC_GLB_CC0_CLR = MRCC_MRCC_GLB_CC0_FLEXPWM0_MASK;
        }
    }
    else
    {
        *pClkCtrl = (1UL << bit_shift);
    }

    /* Freeze clock configuration */
    SYSCON->CLKUNLOCK |= SYSCON_CLKUNLOCK_UNLOCK_MASK;
}

/**
 * @brief   Configure the clock selection muxes.
 * @param   connection  : Clock to be configured.
 * @return  Nothing
 */
void CLOCK_AttachClk(clock_attach_id_t connection);

/**
 * @brief   Get the actual clock attach id.
 * This fuction uses the offset in input attach id, then it reads the actual source value in
 * the register and combine the offset to obtain an actual attach id.
 * @param   connection  : Clock attach id to get.
 * @return  Clock source value.
 */
clock_attach_id_t CLOCK_GetClockAttachId(clock_attach_id_t connection);

/**
 * @brief   Set the clock select value.
 * This fuction set the peripheral clock select value.
 * @param   sel_name : Clock select.
 * @param   value    : value to be set.
 */
void CLOCK_SetClockSelect(clock_select_name_t sel_name, uint32_t value);

/**
 * @brief   Get the clock select value.
 * This fuction get the peripheral clock select value.
 * @param   sel_name  : Clock select.
 * @return  Clock source value.
 */
uint32_t CLOCK_GetClockSelect(clock_select_name_t sel_name);

/**
 * @brief   Setup peripheral clock dividers.
 * @param   div_name : Clock divider name
 * @param   value    : Value to be divided
 * @return  Nothing
 */
void CLOCK_SetClockDiv(clock_div_name_t div_name, uint32_t value);

/**
 * @brief   Get peripheral clock dividers.
 * @param   div_name    : Clock divider name
 * @return  peripheral clock dividers
 */
uint32_t CLOCK_GetClockDiv(clock_div_name_t div_name);

/**
 * @brief   Halt peripheral clock dividers.
 * @param   div_name    : Clock divider name
 * @return  Nothing
 */
void CLOCK_HaltClockDiv(clock_div_name_t div_name);

/**
 * @brief   Initialize the FROHF to given frequency (48,64,96,192).
 * This function turns on FIRC and select the given frequency as the source of fro_hf
 * @param   iFreq   : Desired frequency.
 * @return  returns success or fail status.
 */
status_t CLOCK_SetupFROHFClocking(uint32_t iFreq);

/**
 * @brief   Initialize the FRO12M.
 * This function turns on FRO12M.
 * @return  returns success or fail status.
 */
status_t CLOCK_SetupFRO12MClocking(void);

/**
 * @brief   Initialize the FRO16K.
 * This function turns on FRO16K.
 * @param   clk_16k_enable_mask: 0-3
 *             0b00: disable both clk_16k0 and clk_16k1
 *             0b01: only enable clk_16k0
 *             0b10: only enable clk_16k1
 *             0b11: enable both clk_16k0 and clk_16k1
 * @return  returns success or fail status.
 */
status_t CLOCK_SetupFRO16KClocking(uint8_t clk_16k_enable_mask);

/**
 * @brief   Initialize the external osc clock to given frequency.
 * @param   iFreq   : Desired frequency (must be equal to exact rate in Hz)
 * @return  returns success or fail status.
 */
status_t CLOCK_SetupExtClocking(uint32_t iFreq);

/**
 * @brief   Initialize the external reference clock to given frequency.
 * @param   iFreq   : Desired frequency (must be equal to exact rate in Hz)
 * @return  returns success or fail status.
 */
status_t CLOCK_SetupExtRefClocking(uint32_t iFreq);

/*! @brief  Return Frequency of selected clock
 *  @return Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

/*! @brief  Return Frequency of core
 *  @return Frequency of the core
 */
uint32_t CLOCK_GetCoreSysClkFreq(void);

/*! @brief  Return Frequency of I3C FCLK
 *  @return Frequency of I3C FCLK.
 */
uint32_t CLOCK_GetI3CFClkFreq(void);

/*! @brief  Return Frequency of CTimer functional Clock
 *  @return Frequency of CTimer functional Clock
 */
uint32_t CLOCK_GetCTimerClkFreq(uint32_t id);

/*! @brief  Return Frequency of LPI2C0 functional Clock
 *  @return Frequency of LPI2C0 functional Clock
 */
uint32_t CLOCK_GetLpi2cClkFreq(void);

/*! @brief  Return Frequency of LPSPI functional Clock
 *  @return Frequency of LPSPI functional Clock
 */
uint32_t CLOCK_GetLpspiClkFreq(uint32_t id);

/*! @brief  Return Frequency of LPUART functional Clock
 *  @return Frequency of LPUART functional Clock
 */
uint32_t CLOCK_GetLpuartClkFreq(uint32_t id);

/*! @brief  Return Frequency of LPTMR functional Clock
 *  @return Frequency of LPTMR functional Clock
 */
uint32_t CLOCK_GetLptmrClkFreq(void);

/*! @brief  Return Frequency of OSTIMER
 *  @return Frequency of OSTIMER Clock
 */
uint32_t CLOCK_GetOstimerClkFreq(void);

/*! @brief  Return Frequency of Adc Clock
 *  @return Frequency of Adc.
 */
uint32_t CLOCK_GetAdcClkFreq(void);

/*! @brief  Return Frequency of CMP Function Clock
 *  @return Frequency of CMP Function.
 */
uint32_t CLOCK_GetCmpFClkFreq(uint32_t id);

/*! @brief  Return Frequency of CMP Round Robin Clock
 *  @return Frequency of CMP Round Robin.
 */
uint32_t CLOCK_GetCmpRRClkFreq(uint32_t id);

/*! @brief  Return Frequency of Trace Clock
 *  @return Frequency of Trace.
 */
uint32_t CLOCK_GetTraceClkFreq(void);

/*! @brief  Return Frequency of CLKOUT Clock
 *  @return Frequency of CLKOUT.
 */
uint32_t CLOCK_GetClkoutClkFreq(void);

/*! @brief  Return Frequency of Systick Clock
 *  @return Frequency of Systick.
 */
uint32_t CLOCK_GetSystickClkFreq(void);

/*! brief  Return Frequency of Systick Clock
 *  return Frequency of Systick.
 */
uint32_t CLOCK_GetWwdtClkFreq(void);

/**
 * @brief   Setup FROHF trim.
 * @param   config   : FROHF trim value
 * @return  returns success or fail status.
 */
status_t CLOCK_FROHFTrimConfig(firc_trim_config_t config);

/**
 * @brief   Setup FRO 12M trim.
 * @param   config   : FRO 12M trim value
 * @return  returns success or fail status.
 */
status_t CLOCK_FRO12MTrimConfig(sirc_trim_config_t config);

/*!
 * @brief Sets the system OSC monitor mode.
 *
 * This function sets the system OSC monitor mode. The mode can be disabled,
 * it can generate an interrupt when the error is disabled, or reset when the error is detected.
 *
 * @param mode Monitor mode to set.
 */
void CLOCK_SetSysOscMonitorMode(scg_sosc_monitor_mode_t mode);

/*! brief Enable USB FS clock.
 * Enable USB Full Speed clock.
 */
bool CLOCK_EnableUsbfsClock(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
