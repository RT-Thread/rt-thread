/*
 * Copyright 2023, NXP
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
/*! @brief reset driver version 2.4.0 */
#define FSL_RESET_DRIVER_VERSION (MAKE_VERSION(2, 4, 0))
/*@}*/

/*!
 * @brief Enumeration for peripheral reset control bits
 *
 * Defines the enumeration for peripheral reset control bits in PRESETCTRL/ASYNCPRESETCTRL registers
 */
typedef enum _SYSCON_RSTn
{
    kINPUTMUX0_RST_SHIFT_RSTn = (0U | (0U)),          /*!< INPUTMUX0 reset control */
    kI3C0_RST_SHIFT_RSTn      = (0U | (1U)),          /*!< I3C0      reset control */
    kCTIMER0_RST_SHIFT_RSTn   = (0U | (2U)),          /*!< CTIMER0   reset control */
    kCTIMER1_RST_SHIFT_RSTn   = (0U | (3U)),          /*!< CTIMER1   reset control */
    kCTIMER2_RST_SHIFT_RSTn   = (0U | (4U)),          /*!< CTIMER2   reset control */
    kCTIMER3_RST_SHIFT_RSTn   = (0U | (5U)),          /*!< CTIMER3   reset control */
    kCTIMER4_RST_SHIFT_RSTn   = (0U | (6U)),          /*!< CTIMER4   reset control */
    kFREQME_RST_SHIFT_RSTn    = (0U | (7U)),          /*!< FREQME    reset control */
    kUTICK0_RST_SHIFT_RSTn    = (0U | (8U)),          /*!< UTICK0    reset control */
    kDMA_RST_SHIFT_RSTn       = (0U | (10U)),         /*!< DMA       reset control */
    kAOI0_RST_SHIFT_RSTn      = (0U | (11U)),         /*!< AOI0      reset control */
    kCRC0_RST_SHIFT_RSTn      = (0U | (12U)),         /*!< CRC0      reset control */
    kEIM0_RST_SHIFT_RSTn      = (0U | (13U)),         /*!< EIM0      reset control */
    kERM0_RST_SHIFT_RSTn      = (0U | (14U)),         /*!< ERM0      reset control */
    kAOI1_RST_SHIFT_RSTn      = (0U | (16U)),         /*!< AOI1      reset control */
    kFLEXIO0_RST_SHIFT_RSTn   = (0U | (17U)),         /*!< FLEXIO0   reset control */
    kLPI2C0_RST_SHIFT_RSTn    = (0U | (18U)),         /*!< LPI2C0    reset control */
    kLPI2C1_RST_SHIFT_RSTn    = (0U | (19U)),         /*!< LPI2C1    reset control */
    kLPSPI0_RST_SHIFT_RSTn    = (0U | (20U)),         /*!< LPSPI0    reset control */
    kLPSPI1_RST_SHIFT_RSTn    = (0U | (21U)),         /*!< LPSPI1    reset control */
    kLPUART0_RST_SHIFT_RSTn   = (0U | (22U)),         /*!< LPUART0   reset control */
    kLPUART1_RST_SHIFT_RSTn   = (0U | (23U)),         /*!< LPUART1   reset control */
    kLPUART2_RST_SHIFT_RSTn   = (0U | (24U)),         /*!< LPUART2   reset control */
    kLPUART3_RST_SHIFT_RSTn   = (0U | (25U)),         /*!< LPUART3   reset control */
    kLPUART4_RST_SHIFT_RSTn   = (0U | (26U)),         /*!< LPUART4   reset control */
    kUSB0_RST_SHIFT_RSTn      = (0U | (27U)),         /*!< USB0      reset control */
    kQDC0_RST_SHIFT_RSTn      = (0U | (28U)),         /*!< QDC0      reset control */
    kQDC1_RST_SHIFT_RSTn      = (0U | (29U)),         /*!< QDC1      reset control */
    kFLEXPWM0_RST_SHIFT_RSTn  = (0U | (30U)),         /*!< FLEXPWM0  reset control */
    kFLEXPWM1_RST_SHIFT_RSTn  = (0U | (31U)),         /*!< FLEXPWM1  reset control */
    kOSTIMER0_RST_SHIFT_RSTn  = ((1U << 8U) | (0U)),  /*!< OSTIMER0  reset control */
    kADC0_RST_SHIFT_RSTn      = ((1U << 8U) | (1U)),  /*!< ADC0      reset control */
    kADC1_RST_SHIFT_RSTn      = ((1U << 8U) | (2U)),  /*!< ADC1      reset control */
    kCMP1_RST_SHIFT_RSTn      = ((1U << 8U) | (4U)),  /*!< CMP1      reset control */
    kDAC0_RST_SHIFT_RSTn      = ((1U << 8U) | (5U)),  /*!< DAC0      reset control */
    kOPAMP0_RST_SHIFT_RSTn    = ((1U << 8U) | (6U)),  /*!< OPAMP0    reset control */
    kPORT0_RST_SHIFT_RSTn     = ((1U << 8U) | (7U)),  /*!< PORT0     reset control */
    kPORT1_RST_SHIFT_RSTn     = ((1U << 8U) | (8U)),  /*!< PORT1     reset control */
    kPORT2_RST_SHIFT_RSTn     = ((1U << 8U) | (9U)),  /*!< PORT2     reset control */
    kPORT3_RST_SHIFT_RSTn     = ((1U << 8U) | (10U)), /*!< PORT3     reset control */
    kPORT4_RST_SHIFT_RSTn     = ((1U << 8U) | (11U)), /*!< PORT4     reset control */
    kFLEXCAN0_RST_SHIFT_RSTn  = ((1U << 8U) | (12U)), /*!< FLEXCAN0  reset control */
    kLPI2C2_RST_SHIFT_RSTn    = ((1U << 8U) | (13U)), /*!< LPI2C2    reset control */
    kLPI2C3_RST_SHIFT_RSTn    = ((1U << 8U) | (14U)), /*!< LPI2C3    reset control */
    kGPIO0_RST_SHIFT_RSTn     = ((1U << 8U) | (20U)), /*!< GPIO0     reset control */
    kGPIO1_RST_SHIFT_RSTn     = ((1U << 8U) | (21U)), /*!< GPIO1     reset control */
    kGPIO2_RST_SHIFT_RSTn     = ((1U << 8U) | (22U)), /*!< GPIO2     reset control */
    kGPIO3_RST_SHIFT_RSTn     = ((1U << 8U) | (23U)), /*!< GPIO3     reset control */
    kGPIO4_RST_SHIFT_RSTn     = ((1U << 8U) | (24U)), /*!< GPIO4     reset control */
    NotAvail_RSTn             = (0xFFFFU),            /*!< No         reset control */
} SYSCON_RSTn_t;

/** Array initializers with peripheral reset bits **/
#define AOI_RSTS                                   \
    {                                              \
        kAOI0_RST_SHIFT_RSTn, kAOI1_RST_SHIFT_RSTn \
    } /* Reset bits for ADC peripheral */
#define ADC_RSTS                                   \
    {                                              \
        kADC0_RST_SHIFT_RSTn, kADC1_RST_SHIFT_RSTn \
    } /* Reset bits for ADC peripheral */
#define CRC_RSTS             \
    {                        \
        kCRC0_RST_SHIFT_RSTn \
    } /* Reset bits for CRC peripheral */
#define CTIMER_RSTS                                                                                         \
    {                                                                                                       \
        kCTIMER0_RST_SHIFT_RSTn, kCTIMER1_RST_SHIFT_RSTn, kCTIMER2_RST_SHIFT_RSTn, kCTIMER3_RST_SHIFT_RSTn, \
            kCTIMER4_RST_SHIFT_RSTn                                                                         \
    } /* Reset bits for CTIMER peripheral */
#define DAC_RSTS_N           \
    {                        \
        kDAC0_RST_SHIFT_RSTn \
    } /* Reset bits for DAC peripheral */
#define DMA_RSTS_N          \
    {                       \
        kDMA_RST_SHIFT_RSTn \
    } /* Reset bits for DMA peripheral */
#define EIM_RSTS_N           \
    {                        \
        kEIM0_RST_SHIFT_RSTn \
    } /* Reset bits for EIM peripheral */
#define ERM_RSTS_N           \
    {                        \
        kERM0_RST_SHIFT_RSTn \
    } /* Reset bits for ERM peripheral */
#define FLEXCAN_RSTS_N           \
    {                            \
        kFLEXCAN0_RST_SHIFT_RSTn \
    } /* Reset bits for FLEXCAN peripheral */
#define FLEXIO_RSTS_N           \
    {                           \
        kFLEXIO0_RST_SHIFT_RSTn \
    } /* Reset bits for FLEXIO peripheral */
#define FLEXPWM_RSTS_N                                     \
    {                                                      \
        kFLEXPWM0_RST_SHIFT_RSTn, kFLEXPWM1_RST_SHIFT_RSTn \
    } /* Reset bits for FLEXPWM peripheral */
#define FREQME_RSTS_N          \
    {                          \
        kFREQME_RST_SHIFT_RSTn \
    } /* Reset bits for FREQME peripheral */
#define GPIO_RSTS_N                                                                                 \
    {                                                                                               \
        kGPIO0_RST_SHIFT_RSTn, kGPIO1_RST_SHIFT_RSTn, kGPIO2_RST_SHIFT_RSTn, kGPIO3_RST_SHIFT_RSTn, \
            kGPIO4_RST_SHIFT_RSTn                                                                   \
    } /* Reset bits for GPIO peripheral */
#define I3C_RSTS             \
    {                        \
        kI3C0_RST_SHIFT_RSTn \
    } /* Reset bits for I3C peripheral */
#define INPUTMUX_RSTS             \
    {                             \
        kINPUTMUX0_RST_SHIFT_RSTn \
    } /* Reset bits for INPUTMUX peripheral */
#define LPUART_RSTS                                                                                         \
    {                                                                                                       \
        kLPUART0_RST_SHIFT_RSTn, kLPUART1_RST_SHIFT_RSTn, kLPUART2_RST_SHIFT_RSTn, kLPUART3_RST_SHIFT_RSTn, \
            kLPUART4_RST_SHIFT_RSTn                                                                         \
    } /* Reset bits for LPUART peripheral */
#define LPSPI_RSTS                                     \
    {                                                  \
        kLPSPI0_RST_SHIFT_RSTn, kLPSPI1_RST_SHIFT_RSTn \
    } /* Reset bits for LPSPI peripheral */
#define LPI2C_RSTS                                                                                     \
    {                                                                                                  \
        kLPI2C0_RST_SHIFT_RSTn, kLPI2C1_RST_SHIFT_RSTn, kLPI2C2_RST_SHIFT_RSTn, kLPI2C3_RST_SHIFT_RSTn \
    } /* Reset bits for LPI2C peripheral */
#define LPCMP_RSTS                          \
    {                                       \
        NotAvail_RSTn, kCMP1_RST_SHIFT_RSTn \
    } /* Reset bits for LPCMP peripheral */
#define OPAMP_RSTS             \
    {                          \
        kOPAMP0_RST_SHIFT_RSTn \
    } /* Reset bits for OPAMP peripheral */
#define OSTIMER_RSTS             \
    {                            \
        kOSTIMER0_RST_SHIFT_RSTn \
    } /* Reset bits for OSTIMER peripheral */
#define PORT_RSTS_N                                                                                 \
    {                                                                                               \
        kPORT0_RST_SHIFT_RSTn, kPORT1_RST_SHIFT_RSTn, kPORT2_RST_SHIFT_RSTn, kPORT3_RST_SHIFT_RSTn, \
            kPORT4_RST_SHIFT_RSTn                                                                   \
    } /* Reset bits for PORT peripheral */
#define EQDC_RSTS                                  \
    {                                              \
        kQDC0_RST_SHIFT_RSTn, kQDC1_RST_SHIFT_RSTn \
    } /* Reset bits for EQDC peripheral */
#define UTICK_RSTS             \
    {                          \
        kUTICK0_RST_SHIFT_RSTn \
    } /* Reset bits for UTICK peripheral */

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

/*!
 * @brief Release peripheral module.
 *
 * Release peripheral module.
 *
 * @param peripheral Peripheral to release. The enum argument contains encoding of reset register
 *                   and reset bit position in the reset register.
 */
static inline void RESET_ReleasePeripheralReset(reset_ip_name_t peripheral)
{
    RESET_SetPeripheralReset(peripheral);
}

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_RESET_H_ */
