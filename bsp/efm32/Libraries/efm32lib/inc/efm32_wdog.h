/***************************************************************************//**
 * @file
 * @brief Watchdog (WDOG) peripheral API for EFM32.
 * @author Energy Micro AS
 * @version 2.3.2
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#ifndef __EFM32_WDOG_H
#define __EFM32_WDOG_H

#include <stdbool.h>
#include "efm32.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup WDOG
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Watchdog clock selection. */
typedef enum
{
  wdogClkSelULFRCO = _WDOG_CTRL_CLKSEL_ULFRCO,   /**< Ultra low frequency (1 kHz) clock */
  wdogClkSelLFRCO  = _WDOG_CTRL_CLKSEL_LFRCO,    /**< Low frequency RC oscillator */
  wdogClkSelLFXO   = _WDOG_CTRL_CLKSEL_LFXO      /**< Low frequency crystal oscillator */
} WDOG_ClkSel_TypeDef;

/** Watchdog period selection. */
typedef enum
{
  wdogPeriod_9    = 0x0, /**< 9 clock periods */
  wdogPeriod_17   = 0x1, /**< 17 clock periods */
  wdogPeriod_33   = 0x2, /**< 33 clock periods */
  wdogPeriod_65   = 0x3, /**< 65 clock periods */
  wdogPeriod_129  = 0x4, /**< 129 clock periods */
  wdogPeriod_257  = 0x5, /**< 257 clock periods */
  wdogPeriod_513  = 0x6, /**< 513 clock periods */
  wdogPeriod_1k   = 0x7, /**< 1025 clock periods */
  wdogPeriod_2k   = 0x8, /**< 2049 clock periods */
  wdogPeriod_4k   = 0x9, /**< 4097 clock periods */
  wdogPeriod_8k   = 0xA, /**< 8193 clock periods */
  wdogPeriod_16k  = 0xB, /**< 16385 clock periods */
  wdogPeriod_32k  = 0xC, /**< 32769 clock periods */
  wdogPeriod_64k  = 0xD, /**< 65537 clock periods */
  wdogPeriod_128k = 0xE, /**< 131073 clock periods */
  wdogPeriod_256k = 0xF  /**< 262145 clock periods */
} WDOG_PeriodSel_TypeDef;

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** Watchdog initialization structure. */
typedef struct
{
  /** Enable watchdog when init completed. */
  bool                   enable;

  /** Counter shall keep running during debug halt. */
  bool                   debugRun;

  /** Counter shall keep running when in EM2. */
  bool                   em2Run;

  /** Counter shall keep running when in EM3. */
  bool                   em3Run;

  /** Block EMU from entering EM4. */
  bool                   em4Block;

  /** Block SW from disabling LFRCO/LFXO oscillators. */
  bool                   swoscBlock;

  /** Block SW from modifying the configuration (a reset is needed to reconfigure). */
  bool                   lock;

  /** Clock source to use for watchdog. */
  WDOG_ClkSel_TypeDef    clkSel;

  /** Watchdog timeout period. */
  WDOG_PeriodSel_TypeDef perSel;
} WDOG_Init_TypeDef;

/** Suggested default config for WDOG init structure. */
#define WDOG_INIT_DEFAULT                                                                        \
  { true,               /* Start watchdog when init done */                                      \
    false,              /* WDOG not counting during debug halt */                                \
    false,              /* WDOG not counting when in EM2 */                                      \
    false,              /* WDOG not counting when in EM3 */                                      \
    false,              /* EM4 can be entered */                                                 \
    false,              /* Do not block disabling LFRCO/LFXO in CMU */                           \
    false,              /* Do not lock WDOG configuration (if locked, reset needed to unlock) */ \
    wdogClkSelULFRCO,   /* Select 1kHZ WDOG oscillator */                                        \
    wdogPeriod_256k     /* Set longest possible timeout period */                                \
  }


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void WDOG_Enable(bool enable);
void WDOG_Feed(void);
void WDOG_Init(const WDOG_Init_TypeDef *init);
void WDOG_Lock(void);

/** @} (end addtogroup WDOG) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32_WDOG_H */
