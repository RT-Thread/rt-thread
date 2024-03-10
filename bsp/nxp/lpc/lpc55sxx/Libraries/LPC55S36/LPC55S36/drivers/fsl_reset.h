/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_RESET_H_
#define _FSL_RESET_H_

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup reset
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief reset driver version 2.0.0. */
#define FSL_RESET_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*!
 * @brief Enumeration for peripheral reset control bits
 *
 * Defines the enumeration for peripheral reset control bits in PRESETCTRL/ASYNCPRESETCTRL registers
 */
typedef enum _SYSCON_RSTn
{
    kROM_RST_SHIFT_RSTn        = (0 | (1U)),  /**< ROM reset control       .*/
    kSRAM_CTRL1_RST_SHIFT_RSTn = (0 | (3U)),  /**< SRAM Controller 1 reset control       .*/
    kSRAM_CTRL2_RST_SHIFT_RSTn = (0 | (4U)),  /**< SRAM Controller 2 reset control       .*/
    kSRAM_CTRL3_RST_SHIFT_RSTn = (0 | (5U)),  /**< SRAM Controller 3 reset control       .*/
    kSRAM_CTRL4_RST_SHIFT_RSTn = (0 | (6U)),  /**< SRAM Controller 4 reset control       .*/
    kFLASH_RST_SHIFT_RSTn      = (0 | (7U)),  /**< FLASH reset control     .*/
    kFMC_RST_SHIFT_RSTn        = (0 | (8U)),  /**< FMC reset control       .*/
    kFLEXSPI_RST_SHIFT_RSTn    = (0 | (10U)), /**< FLEXSPI reset control   .*/
    kMUX_RST_SHIFT_RSTn        = (0 | (11U)), /**< MUX reset control       .*/
    kIOCON_RST_SHIFT_RSTn      = (0 | (13U)), /**< IOCON reset control     .*/
    kGPIO0_RST_SHIFT_RSTn      = (0 | (14U)), /**< GPIO0 reset control     .*/
    kGPIO1_RST_SHIFT_RSTn      = (0 | (15U)), /**< GPIO1 reset control     .*/
    kGPIO2_RST_SHIFT_RSTn      = (0 | (16U)), /**< GPIO2 reset control     .*/
    kGPIO3_RST_SHIFT_RSTn      = (0 | (17U)), /**< GPIO3 reset control     .*/
    kPINT_RST_SHIFT_RSTn       = (0 | (18U)), /**< PINT reset control      .*/
    kGINT_RST_SHIFT_RSTn       = (0 | (19U)), /**< GINT reset control      .*/
    kDMA0_RST_SHIFT_RSTn       = (0 | (20U)), /**< DMA0 reset control      .*/
    kCRC_RST_SHIFT_RSTn        = (0 | (21U)), /**< CRC reset control    .*/
    kWWDT_RST_SHIFT_RSTn       = (0 | (22U)), /**< WWDT reset control      .*/
    kRTC_RST_SHIFT_RSTn        = (0 | (23U)), /**< RTC reset control       .*/
    kMAILBOX_RST_SHIFT_RSTn    = (0 | (26U)), /**< MAILBOX reset control   .*/
    kADC0_RST_SHIFT_RSTn       = (0 | (27U)), /**< ADC0 reset control      .*/
    kADC1_RST_SHIFT_RSTn       = (0 | (28U)), /**< ADC1 reset control      .*/
    kDAC0_RST_SHIFT_RSTn       = (0 | (29U)), /**< DAC0 reset control      .*/

    kMRT_RST_SHIFT_RSTn      = (0x10000 | (0U)),  /**< MRT reset control       .*/
    kOSTIMER_RST_SHIFT_RSTn  = (0x10000 | (1U)),  /**< OSTIMER reset control   .*/
    kSCT_RST_SHIFT_RSTn      = (0x10000 | (2U)),  /**< SCT reset control       .*/
    kMCAN_RST_SHIFT_RSTn     = (0x10000 | (7U)),  /**< MCAN reset control      .*/
    kUTICK_RST_SHIFT_RSTn    = (0x10000 | (10U)), /**< UTICK reset control     .*/
    kFC0_RST_SHIFT_RSTn      = (0x10000 | (11U)), /**< FC0 reset control       .*/
    kFC1_RST_SHIFT_RSTn      = (0x10000 | (12U)), /**< FC1 reset control       .*/
    kFC2_RST_SHIFT_RSTn      = (0x10000 | (13U)), /**< FC2 reset control       .*/
    kFC3_RST_SHIFT_RSTn      = (0x10000 | (14U)), /**< FC3 reset control       .*/
    kFC4_RST_SHIFT_RSTn      = (0x10000 | (15U)), /**< FC4 reset control       .*/
    kFC5_RST_SHIFT_RSTn      = (0x10000 | (16U)), /**< FC5 reset control       .*/
    kFC6_RST_SHIFT_RSTn      = (0x10000 | (17U)), /**< FC6 reset control       .*/
    kFC7_RST_SHIFT_RSTn      = (0x10000 | (18U)), /**< FC7 reset control       .*/
    kDMIC_RST_SHIFT_RSTn     = (0x10000 | (19U)), /**< DMIC reset control      .*/
    kCTIMER2_RST_SHIFT_RSTn  = (0x10000 | (22U)), /**< TIMER2 reset control    .*/
    kUSB0_DEV_RST_SHIFT_RSTn = (0x10000 | (25U)), /**< USB0_DEV reset control  .*/
    kCTIMER0_RST_SHIFT_RSTn  = (0x10000 | (26U)), /**< TIMER0 reset control    .*/
    kCTIMER1_RST_SHIFT_RSTn  = (0x10000 | (27U)), /**< TIMER1 reset control    .*/

    kDMA1_RST_SHIFT_RSTn       = (0x20000 | (1U)),  /**< DMA1 reset control      .*/
    kCMP_RST_SHIFT_RSTn        = (0x20000 | (2U)),  /**< CMP reset control      .*/
    kFREQME_RST_SHIFT_RSTn     = (0x20000 | (8U)),  /**< FREQME reset control    .*/
    kCDOG_RST_SHIFT_RSTn       = (0x20000 | (11U)), /**< Code Watchdog reset control */
    kRNG_RST_SHIFT_RSTn        = (0x20000 | (13U)), /**< RNG reset control       .*/
    kSYSCTL_RST_SHIFT_RSTn     = (0x20000 | (15U)), /**< SYSCTL reset control    .*/
    kUSB0HMR_RST_SHIFT_RSTn    = (0x20000 | (16U)), /**< USB0HMR reset control    */
    kUSB0HSL_RST_SHIFT_RSTn    = (0x20000 | (17U)), /**< USB0HSL reset control     */
    kCSS_RST_SHIFT_RSTn        = (0x20000 | (18U)), /**< CSS reset control       .*/
    kPOWERQUAD_RST_SHIFT_RSTn  = (0x20000 | (19U)), /**< PowerQuad reset control        .*/
    kCTIMER3_RST_SHIFT_RSTn    = (0x20000 | (21U)), /**< TIMER3 reset control    .*/
    kCTIMER4_RST_SHIFT_RSTn    = (0x20000 | (22U)), /**< TIMER4 reset control    .*/
    kPUF_RST_SHIFT_RSTn        = (0x20000 | (23U)), /**< PUF reset control */
    kPKC_RST_SHIFT_RSTn        = (0x20000 | (24U)), /**< PKC reset control       .*/
    kANACTRL_RST_SHIFT_RSTn    = (0x20000 | (27U)), /**< ANACTRL reset control   .*/
    kHSLSPI_RST_SHIFT_RSTn     = (0x20000 | (28U)), /**< HS LSPI reset control    */
    kGPIOSEC_RST_SHIFT_RSTn    = (0x20000 | (29U)), /**< GPIO_SEC reset control  .*/
    kGPIOSECINT_RST_SHIFT_RSTn = (0x20000 | (30U)), /**< GPIO secure int reset control  .*/

    kI3C0_RST_SHIFT_RSTn   = (0x30000 | (0U)),  /**< I3C0 reset control      .*/
    kENC0_RST_SHIFT_RSTn   = (0x30000 | (3U)),  /**< ENC0 reset control      .*/
    kENC1_RST_SHIFT_RSTn   = (0x30000 | (4U)),  /**< ENC1 reset control      .*/
    kPWM0_RST_SHIFT_RSTn   = (0x30000 | (5U)),  /**< PWM0 reset control      .*/
    kPWM1_RST_SHIFT_RSTn   = (0x30000 | (6U)),  /**< PWM1 reset control      .*/
    kAOI0_RST_SHIFT_RSTn   = (0x30000 | (7U)),  /**< AOI0 reset control      .*/
    kAOI1_RST_SHIFT_RSTn   = (0x30000 | (8U)),  /**< AOI1 reset control      .*/
    kFTM0_RST_SHIFT_RSTn   = (0x30000 | (9U)),  /**< FTM0 reset control      .*/
    kDAC1_RST_SHIFT_RSTn   = (0x30000 | (10U)), /**< DAC1 reset control      .*/
    kDAC2_RST_SHIFT_RSTn   = (0x30000 | (11U)), /**< DAC2 reset control      .*/
    kOPAMP0_RST_SHIFT_RSTn = (0x30000 | (12U)), /**< OPAMP0 reset control    .*/
    kOPAMP1_RST_SHIFT_RSTn = (0x30000 | (13U)), /**< OPAMP1 reset control    .*/
    kOPAMP2_RST_SHIFT_RSTn = (0x30000 | (14U)), /**< OPAMP2 reset control    .*/
    kHSCMP0_RST_SHIFT_RSTn = (0x30000 | (15U)), /**< HSCMP0 reset control    .*/
    kHSCMP1_RST_SHIFT_RSTn = (0x30000 | (16U)), /**< HSCMP1 reset control    .*/
    kHSCMP2_RST_SHIFT_RSTn = (0x30000 | (17U)), /**< HSCMP2 reset control    .*/
    kVREF_RST_SHIFT_RSTn   = (0x30000 | (18U)), /**< VREF reset control      .*/
} SYSCON_RSTn_t;

/** Array initializers with peripheral reset bits **/
#define ADC_RSTS                                   \
    {                                              \
        kADC0_RST_SHIFT_RSTn, kADC1_RST_SHIFT_RSTn \
    } /* Reset bits for ADC peripheral */
#define MCAN_RSTS            \
    {                        \
        kMCAN_RST_SHIFT_RSTn \
    } /* Reset bits for CAN peripheral */
#define CRC_RSTS            \
    {                       \
        kCRC_RST_SHIFT_RSTn \
    } /* Reset bits for CRC peripheral */
#define CTIMER_RSTS                                                                                         \
    {                                                                                                       \
        kCTIMER0_RST_SHIFT_RSTn, kCTIMER1_RST_SHIFT_RSTn, kCTIMER2_RST_SHIFT_RSTn, kCTIMER3_RST_SHIFT_RSTn, \
            kCTIMER4_RST_SHIFT_RSTn                                                                         \
    } /* Reset bits for CTIMER peripheral */
#define DMA_RSTS_N                                 \
    {                                              \
        kDMA0_RST_SHIFT_RSTn, kDMA1_RST_SHIFT_RSTn \
    } /* Reset bits for DMA peripheral */

#define FLEXCOMM_RSTS                                                                                            \
    {                                                                                                            \
        kFC0_RST_SHIFT_RSTn, kFC1_RST_SHIFT_RSTn, kFC2_RST_SHIFT_RSTn, kFC3_RST_SHIFT_RSTn, kFC4_RST_SHIFT_RSTn, \
            kFC5_RST_SHIFT_RSTn, kFC6_RST_SHIFT_RSTn, kFC7_RST_SHIFT_RSTn, kHSLSPI_RST_SHIFT_RSTn                \
    } /* Reset bits for FLEXCOMM peripheral */
#define GINT_RSTS                                  \
    {                                              \
        kGINT_RST_SHIFT_RSTn, kGINT_RST_SHIFT_RSTn \
    } /* Reset bits for GINT peripheral. GINT0 & GINT1 share same slot */
#define GPIO_RSTS_N                                                                                \
    {                                                                                              \
        kGPIO0_RST_SHIFT_RSTn, kGPIO1_RST_SHIFT_RSTn, kGPIO2_RST_SHIFT_RSTn, kGPIO3_RST_SHIFT_RSTn \
    } /* Reset bits for GPIO peripheral */
#define INPUTMUX_RSTS       \
    {                       \
        kMUX_RST_SHIFT_RSTn \
    } /* Reset bits for INPUTMUX peripheral */
#define IOCON_RSTS            \
    {                         \
        kIOCON_RST_SHIFT_RSTn \
    } /* Reset bits for IOCON peripheral */
#define FLASH_RSTS                                 \
    {                                              \
        kFLASH_RST_SHIFT_RSTn, kFMC_RST_SHIFT_RSTn \
    } /* Reset bits for Flash peripheral */
#define MRT_RSTS            \
    {                       \
        kMRT_RST_SHIFT_RSTn \
    } /* Reset bits for MRT peripheral */
#define PINT_RSTS                                          \
    {                                                      \
        kPINT_RST_SHIFT_RSTn, kGPIO_SEC_INT_RST_SHIFT_RSTn \
    } /* Reset bits for PINT peripheral */
#define CDOG_RSTS            \
    {                        \
        kCDOG_RST_SHIFT_RSTn \
    } /* Reset bits for CDOG peripheral */
#define RNG_RSTS            \
    {                       \
        kRNG_RST_SHIFT_RSTn \
    } /* Reset bits for RNG peripheral */
#define SCT_RSTS            \
    {                       \
        kSCT_RST_SHIFT_RSTn \
    } /* Reset bits for SCT peripheral */
#define USB0D_RST                \
    {                            \
        kUSB0_DEV_RST_SHIFT_RSTn \
    } /* Reset bits for USB0D peripheral */
#define USB0HMR_RST             \
    {                           \
        kUSB0HMR_RST_SHIFT_RSTn \
    } /* Reset bits for USB0HMR peripheral */
#define USB0HSL_RST             \
    {                           \
        kUSB0HSL_RST_SHIFT_RSTn \
    } /* Reset bits for USB0HSL peripheral */
#define UTICK_RSTS            \
    {                         \
        kUTICK_RST_SHIFT_RSTn \
    } /* Reset bits for UTICK peripheral */
#define WWDT_RSTS            \
    {                        \
        kWWDT_RST_SHIFT_RSTn \
    } /* Reset bits for WWDT peripheral */
#define OSTIMER_RSTS            \
    {                           \
        kOSTIMER_RST_SHIFT_RSTn \
    } /* Reset bits for OSTIMER peripheral */
#define I3C_RSTS             \
    {                        \
        kI3C0_RST_SHIFT_RSTn \
    } /* Reset bits for I3C peripheral */
#define ENC_RSTS                                   \
    {                                              \
        kENC0_RST_SHIFT_RSTn, kENC1_RST_SHIFT_RSTn \
    } /* Reset bits for ENC peripheral */
#define PWM_RSTS                                   \
    {                                              \
        kPWM0_RST_SHIFT_RSTn, kPWM1_RST_SHIFT_RSTn \
    } /* Reset bits for PWM peripheral */
#define AOI_RSTS                                   \
    {                                              \
        kAOI0_RST_SHIFT_RSTn, kAOI1_RST_SHIFT_RSTn \
    } /* Reset bits for AOI peripheral */
#define DAC_RSTS                                   \
    {                                              \
        kDAC0_RST_SHIFT_RSTn, kDAC1_RST_SHIFT_RSTn \
    } /* Reset bits for DAC peripheral */
#define OPAMP_RSTS                                                             \
    {                                                                          \
        kOPAMP0_RST_SHIFT_RSTn, kOPAMP1_RST_SHIFT_RSTn, kOPAMP2_RST_SHIFT_RSTn \
    } /* Reset bits for OPAMP peripheral */
#define HSCMP_RSTS                                                             \
    {                                                                          \
        kHSCMP0_RST_SHIFT_RSTn, kHSCMP1_RST_SHIFT_RSTn, kHSCMP2_RST_SHIFT_RSTn \
    } /* Reset bits for HSCMP peripheral */
#define POWERQUAD_RSTS            \
    {                             \
        kPOWERQUAD_RST_SHIFT_RSTn \
    } /* Reset bits for Powerquad peripheral */
typedef SYSCON_RSTn_t reset_ip_name_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Assert reset to peripheral.
 *
 * Asserts reset signal to specified peripheral module.
 *
 * @param peripheral Assert reset to this peripheral. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
void RESET_SetPeripheralReset(reset_ip_name_t peripheral);

/*!
 * @brief Clear reset to peripheral.
 *
 * Clears reset signal to specified peripheral module, allows it to operate.
 *
 * @param peripheral Clear reset to this peripheral. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
void RESET_ClearPeripheralReset(reset_ip_name_t peripheral);

/*!
 * @brief Reset peripheral module.
 *
 * Reset peripheral module.
 *
 * @param peripheral Peripheral to reset. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
void RESET_PeripheralReset(reset_ip_name_t peripheral);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_RESET_H_ */
