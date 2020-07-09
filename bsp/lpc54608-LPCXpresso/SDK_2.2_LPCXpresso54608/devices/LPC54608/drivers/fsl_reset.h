/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright (c) 2016, NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _FSL_RESET_H_
#define _FSL_RESET_H_

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup ksdk_common
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Enumeration for peripheral reset control bits
 *
 * Defines the enumeration for peripheral reset control bits in PRESETCTRL/ASYNCPRESETCTRL registers
 */
typedef enum _SYSCON_RSTn
{
    kFLASH_RST_SHIFT_RSTn = 0 | 7U,          /**< Flash controller reset control */
    kFMC_RST_SHIFT_RSTn = 0 | 8U,            /**< Flash accelerator reset control */
    kEEPROM_RST_SHIFT_RSTn = 0 | 9U,         /**< EEPROM reset control */
    kSPIFI_RST_SHIFT_RSTn = 0 | 10U,         /**< SPIFI reset control */
    kMUX_RST_SHIFT_RSTn = 0 | 11U,           /**< Input mux reset control */
    kIOCON_RST_SHIFT_RSTn = 0 | 13U,         /**< IOCON reset control */
    kGPIO0_RST_SHIFT_RSTn = 0 | 14U,         /**< GPIO0 reset control */
    kGPIO1_RST_SHIFT_RSTn = 0 | 15U,         /**< GPIO1 reset control */
    kGPIO2_RST_SHIFT_RSTn = 0 | 16U,         /**< GPIO2 reset control */
    kGPIO3_RST_SHIFT_RSTn = 0 | 17U,         /**< GPIO3 reset control */
    kPINT_RST_SHIFT_RSTn = 0 | 18U,          /**< Pin interrupt (PINT) reset control */
    kGINT_RST_SHIFT_RSTn = 0 | 19U,          /**< Grouped interrupt (PINT) reset control. */
    kDMA_RST_SHIFT_RSTn = 0 | 20U,           /**< DMA reset control */
    kCRC_RST_SHIFT_RSTn = 0 | 21U,           /**< CRC reset control */
    kWWDT_RST_SHIFT_RSTn = 0 | 22U,          /**< Watchdog timer reset control */
    kADC0_RST_SHIFT_RSTn = 0 | 27U,          /**< ADC0 reset control */
    
    kMRT_RST_SHIFT_RSTn = 65536 | 0U,        /**< Multi-rate timer (MRT) reset control */
    kSCT0_RST_SHIFT_RSTn = 65536 | 2U,       /**< SCTimer/PWM 0 (SCT0) reset control */
    kMCAN0_RST_SHIFT_RSTn = 65536 | 7U,      /**< MCAN0 reset control */
    kMCAN1_RST_SHIFT_RSTn = 65536 | 8U,      /**< MCAN1 reset control */
    kUTICK_RST_SHIFT_RSTn = 65536 | 10U,     /**< Micro-tick timer reset control */
    kFC0_RST_SHIFT_RSTn = 65536 | 11U,       /**< Flexcomm Interface 0 reset control */
    kFC1_RST_SHIFT_RSTn = 65536 | 12U,       /**< Flexcomm Interface 1 reset control */
    kFC2_RST_SHIFT_RSTn = 65536 | 13U,       /**< Flexcomm Interface 2 reset control */
    kFC3_RST_SHIFT_RSTn = 65536 | 14U,       /**< Flexcomm Interface 3 reset control */
    kFC4_RST_SHIFT_RSTn = 65536 | 15U,       /**< Flexcomm Interface 4 reset control */
    kFC5_RST_SHIFT_RSTn = 65536 | 16U,       /**< Flexcomm Interface 5 reset control */
    kFC6_RST_SHIFT_RSTn = 65536 | 17U,       /**< Flexcomm Interface 6 reset control */
    kFC7_RST_SHIFT_RSTn = 65536 | 18U,       /**< Flexcomm Interface 7 reset control */
    kDMIC_RST_SHIFT_RSTn = 65536 | 19U,      /**< Digital microphone interface reset control */
    kCT32B2_RST_SHIFT_RSTn = 65536 | 22U,    /**< CT32B2 reset control */
    kUSB0D_RST_SHIFT_RSTn = 65536 | 25U,     /**< USB0D reset control */
    kCT32B0_RST_SHIFT_RSTn = 65536 | 26U,    /**< CT32B0 reset control */
    kCT32B1_RST_SHIFT_RSTn = 65536 | 27U,    /**< CT32B1 reset control */
    
    kLCD_RST_SHIFT_RSTn = 131072 | 2U,       /**< LCD reset control */
    kSDIO_RST_SHIFT_RSTn = 131072 | 3U,      /**< SDIO reset control */
    kUSB1H_RST_SHIFT_RSTn = 131072 | 4U,     /**< USB1H reset control */
    kUSB1D_RST_SHIFT_RSTn = 131072 | 5U,     /**< USB1D reset control */    
    kUSB1RAM_RST_SHIFT_RSTn = 131072 | 6U,   /**< USB1RAM reset control */
    kEMC_RST_SHIFT_RSTn = 131072 | 7U,       /**< EMC reset control */
    kETH_RST_SHIFT_RSTn = 131072 | 8U,       /**< ETH reset control */
    kGPIO4_RST_SHIFT_RSTn = 131072 | 9U,     /**< GPIO4 reset control */ 
    kGPIO5_RST_SHIFT_RSTn = 131072 | 10U,    /**< GPIO5 reset control */
    kAES_RST_SHIFT_RSTn = 131072 | 11U,      /**< AES reset control */
    kOTP_RST_SHIFT_RSTn = 131072 | 12U,      /**< OTP reset control */
    kRNG_RST_SHIFT_RSTn = 131072 | 13U,      /**< RNG  reset control */ 
    kFC8_RST_SHIFT_RSTn = 131072 | 14U,      /**< Flexcomm Interface 8 reset control */
    kFC9_RST_SHIFT_RSTn = 131072 | 15U,      /**< Flexcomm Interface 9 reset control */
    kUSB0HMR_RST_SHIFT_RSTn = 131072 | 16U,  /**< USB0HMR reset control */
    kUSB0HSL_RST_SHIFT_RSTn = 131072 | 17U,  /**< USB0HSL reset control */
    kSHA_RST_SHIFT_RSTn = 131072 | 18U,      /**< SHA reset control */
    kSC0_RST_SHIFT_RSTn = 131072 | 19U,      /**< SC0 reset control */
    kSC1_RST_SHIFT_RSTn = 131072 | 20U,      /**< SC1 reset control */
    
    kCT32B3_RST_SHIFT_RSTn = 67108864 | 13U, /**< CT32B3 reset control */
    kCT32B4_RST_SHIFT_RSTn = 67108864 | 14U, /**< CT32B4 reset control */
} SYSCON_RSTn_t;

/** Array initializers with peripheral reset bits **/
#define ADC_RSTS             \
    {                        \
        kADC0_RST_SHIFT_RSTn \
    } /* Reset bits for ADC peripheral */
#define AES_RSTS             \
    {                        \
        kAES_RST_SHIFT_RSTn  \
    } /* Reset bits for AES peripheral */
#define CRC_RSTS            \
    {                       \
        kCRC_RST_SHIFT_RSTn \
    } /* Reset bits for CRC peripheral */
#define CTIMER_RSTS                                                                                     \
    {                                                                                                   \
        kCT32B0_RST_SHIFT_RSTn, kCT32B1_RST_SHIFT_RSTn, kCT32B2_RST_SHIFT_RSTn, kCT32B3_RST_SHIFT_RSTn, \
            kCT32B4_RST_SHIFT_RSTn                                                                      \
    } /* Reset bits for CTIMER peripheral */
#define DMA_RSTS            \
    {                       \
        kDMA_RST_SHIFT_RSTn \
    } /* Reset bits for DMA peripheral */
#define DMIC_RSTS            \
    {                        \
        kDMIC_RST_SHIFT_RSTn \
    } /* Reset bits for DMIC peripheral */
#define EMC_RSTS             \
    {                        \
        kEMC_RST_SHIFT_RSTn  \
    } /* Reset bits for EMC peripheral */
#define ETH_RST              \
    {                        \
        kETH_RST_SHIFT_RSTn  \
    } /* Reset bits for EMC peripheral */
#define FLEXCOMM_RSTS                                                                                            \
    {                                                                                                            \
        kFC0_RST_SHIFT_RSTn, kFC1_RST_SHIFT_RSTn, kFC2_RST_SHIFT_RSTn, kFC3_RST_SHIFT_RSTn, kFC4_RST_SHIFT_RSTn, \
            kFC5_RST_SHIFT_RSTn, kFC6_RST_SHIFT_RSTn, kFC7_RST_SHIFT_RSTn, kFC8_RST_SHIFT_RSTn, kFC9_RST_SHIFT_RSTn                                       \
    } /* Reset bits for FLEXCOMM peripheral */
#define GINT_RSTS                                  \
    {                                              \
        kGINT_RST_SHIFT_RSTn, kGINT_RST_SHIFT_RSTn \
    } /* Reset bits for GINT peripheral. GINT0 & GINT1 share same slot */
#define GPIO_RSTS                                    \
    {                                                \
        kGPIO0_RST_SHIFT_RSTn, kGPIO1_RST_SHIFT_RSTn, kGPIO2_RST_SHIFT_RSTn, kGPIO3_RST_SHIFT_RSTn,  \
        kGPIO4_RST_SHIFT_RSTn, kGPIO5_RST_SHIFT_RSTn                                                 \
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
#define LCD_RSTS                                 \
    {                                            \
        kLCD_RST_SHIFT_RSTn                      \
    } /* Reset bits for LCD peripheral */
#define MRT_RSTS            \
    {                       \
        kMRT_RST_SHIFT_RSTn \
    } /* Reset bits for MRT peripheral */
#define MCAN_RSTS                                   \
    {                                               \
        kMCAN0_RST_SHIFT_RSTn,kMCAN1_RST_SHIFT_RSTn \
    } /* Reset bits for MCAN0&MACN1 peripheral */
#define OTP_RSTS            \
    {                       \
        kOTP_RST_SHIFT_RSTn \
    } /* Reset bits for OTP peripheral */
#define PINT_RSTS            \
    {                        \
        kPINT_RST_SHIFT_RSTn \
    } /* Reset bits for PINT peripheral */
#define RNG_RSTS             \
    {                        \
        kRNG_RST_SHIFT_RSTn  \
    } /* Reset bits for RNG peripheral */
#define SDIO_RST             \
    {                        \
        kSDIO_RST_SHIFT_RSTn \
    } /* Reset bits for SDIO peripheral */
#define SCT_RSTS             \
    {                        \
        kSCT0_RST_SHIFT_RSTn \
    } /* Reset bits for SCT peripheral */
#define SHA_RST              \
    {                        \
        kSHA_RST_SHIFT_RSTn  \
    } /* Reset bits for SHA peripheral */
#define USB0D_RST             \
    {                         \
        kUSB0D_RST_SHIFT_RSTn \
    } /* Reset bits for USB0D peripheral */
#define USB0HMR_RST             \
    {                           \
        kUSB0HMR_RST_SHIFT_RSTn \
    } /* Reset bits for USB0HMR peripheral */
#define USB0HSL_RST             \
    {                           \
        kUSB0HSL_RST_SHIFT_RSTn \
    } /* Reset bits for USB0HSL peripheral */
#define USB1H_RST             \
    {                         \
        kUSB1H_RST_SHIFT_RSTn \
    } /* Reset bits for USB1H peripheral */
#define USB1D_RST             \
    {                         \
        kUSB1D_RST_SHIFT_RSTn \
    } /* Reset bits for USB1D peripheral */
#define USB1RAM_RST             \
    {                           \
        kUSB1RAM_RST_SHIFT_RSTn \
    } /* Reset bits for USB1RAM peripheral */
#define UTICK_RSTS            \
    {                         \
        kUTICK_RST_SHIFT_RSTn \
    } /* Reset bits for UTICK peripheral */
#define WWDT_RSTS            \
    {                        \
        kWWDT_RST_SHIFT_RSTn \
    } /* Reset bits for WWDT peripheral */

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
