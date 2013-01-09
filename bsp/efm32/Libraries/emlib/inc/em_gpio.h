/***************************************************************************//**
 * @file
 * @brief General Purpose IO (GPIO) peripheral API
 * @author Energy Micro AS
 * @version 3.0.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
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
#ifndef __EM_GPIO_H
#define __EM_GPIO_H

#include <stdbool.h>
#include "em_part.h"
#include "em_bitband.h"
#include "em_assert.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup GPIO
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** GPIO ports identificator. */
typedef enum
{
  gpioPortA = 0, /**< Port A */
  gpioPortB = 1, /**< Port B */
  gpioPortC = 2, /**< Port C */
  gpioPortD = 3, /**< Port D */
  gpioPortE = 4, /**< Port E */
  gpioPortF = 5  /**< Port F */
} GPIO_Port_TypeDef;

/** GPIO drive mode. */
typedef enum
{
  /** Default 6mA */
  gpioDriveModeStandard = GPIO_P_CTRL_DRIVEMODE_STANDARD,
  /** 0.5 mA */
  gpioDriveModeLowest   = GPIO_P_CTRL_DRIVEMODE_LOWEST,
  /** 20 mA */
  gpioDriveModeHigh     = GPIO_P_CTRL_DRIVEMODE_HIGH,
  /** 2 mA */
  gpioDriveModeLow      = GPIO_P_CTRL_DRIVEMODE_LOW
} GPIO_DriveMode_TypeDef;

/** Pin mode. For more details on each mode, please refer to the EFM32
 * reference manual. */
typedef enum
{
  /** Input disabled. Pullup if DOUT is set. */
  gpioModeDisabled                  = _GPIO_P_MODEL_MODE0_DISABLED,
  /** Input enabled. Filter if DOUT is set */
  gpioModeInput                     = _GPIO_P_MODEL_MODE0_INPUT,
  /** Input enabled. DOUT determines pull direction */
  gpioModeInputPull                 = _GPIO_P_MODEL_MODE0_INPUTPULL,
  /** Input enabled with filter. DOUT determines pull direction */
  gpioModeInputPullFilter           = _GPIO_P_MODEL_MODE0_INPUTPULLFILTER,
  /** Push-pull output */
  gpioModePushPull                  = _GPIO_P_MODEL_MODE0_PUSHPULL,
  /** Push-pull output with drive-strength set by DRIVEMODE */
  gpioModePushPullDrive             = _GPIO_P_MODEL_MODE0_PUSHPULLDRIVE,
  /** Wired-or output */
  gpioModeWiredOr                   = _GPIO_P_MODEL_MODE0_WIREDOR,
  /** Wired-or output with pull-down */
  gpioModeWiredOrPullDown           = _GPIO_P_MODEL_MODE0_WIREDORPULLDOWN,
  /** Open-drain output */
  gpioModeWiredAnd                  = _GPIO_P_MODEL_MODE0_WIREDAND,
  /** Open-drain output with filter */
  gpioModeWiredAndFilter            = _GPIO_P_MODEL_MODE0_WIREDANDFILTER,
  /** Open-drain output with pullup */
  gpioModeWiredAndPullUp            = _GPIO_P_MODEL_MODE0_WIREDANDPULLUP,
  /** Open-drain output with filter and pullup */
  gpioModeWiredAndPullUpFilter      = _GPIO_P_MODEL_MODE0_WIREDANDPULLUPFILTER,
  /** Open-drain output with drive-strength set by DRIVEMODE */
  gpioModeWiredAndDrive             = _GPIO_P_MODEL_MODE0_WIREDANDDRIVE,
  /** Open-drain output with filter and drive-strength set by DRIVEMODE */
  gpioModeWiredAndDriveFilter       = _GPIO_P_MODEL_MODE0_WIREDANDDRIVEFILTER,
  /** Open-drain output with pullup and drive-strength set by DRIVEMODE */
  gpioModeWiredAndDrivePullUp       = _GPIO_P_MODEL_MODE0_WIREDANDDRIVEPULLUP,
  /** Open-drain output with filter, pullup and drive-strength set by DRIVEMODE */
  gpioModeWiredAndDrivePullUpFilter = _GPIO_P_MODEL_MODE0_WIREDANDDRIVEPULLUPFILTER
} GPIO_Mode_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void GPIO_DbgLocationSet(unsigned int location);
#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
__STATIC_INLINE void GPIO_EM4SetPinRetention(bool enable);
#endif

/***************************************************************************//**
 * @brief
 *   Enable/disable serial wire clock pin.
 *
 * @note
 *   Disabling SWDClk will disable the debug interface, which may result in
 *   a lockout if done early in startup (before debugger is able to halt core).
 *
 * @param[in] enable
 *   @li false - disable serial wire clock.
 *   @li true - enable serial wire clock (default after reset).
 ******************************************************************************/
__STATIC_INLINE void GPIO_DbgSWDClkEnable(bool enable)
{
  BITBAND_Peripheral(&(GPIO->ROUTE), _GPIO_ROUTE_SWCLKPEN_SHIFT, (unsigned int)enable);
}


/***************************************************************************//**
 * @brief
 *   Enable/disable serial wire data pin.
 *
 * @note
 *   Disabling SWDClk will disable the debug interface, which may result in
 *   a lockout if done early in startup (before debugger is able to halt core).
 *
 * @param[in] enable
 *   @li false - disable serial wire data pin.
 *   @li true - enable serial wire data pin (default after reset).
 ******************************************************************************/
__STATIC_INLINE void GPIO_DbgSWDIOEnable(bool enable)
{
  BITBAND_Peripheral(&(GPIO->ROUTE), _GPIO_ROUTE_SWDIOPEN_SHIFT, (unsigned int)enable);
}


/***************************************************************************//**
 * @brief
 *   Enable/Disable serial wire output pin.
 *
 * @note
 *   Enabling this pin is not sufficient to fully enable serial wire output
 *   which is also dependent on issues outside the GPIO module. Please refer to
 *   DBG_SWOEnable().
 *
 * @param[in] enable
 *   @li false - disable serial wire viewer pin (default after reset).
 *   @li true - enable serial wire viewer pin.
 ******************************************************************************/
__STATIC_INLINE void GPIO_DbgSWOEnable(bool enable)
{
  BITBAND_Peripheral(&(GPIO->ROUTE), _GPIO_ROUTE_SWOPEN_SHIFT, (unsigned int)enable);
}


void GPIO_DriveModeSet(GPIO_Port_TypeDef port, GPIO_DriveMode_TypeDef mode);


#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
/**************************************************************************//**
 * @brief
 *   Disable GPIO pin wake-up from EM4.
 *
 * @param[in] pinmask
 *   Bitmask containing the bitwise logic OR of which GPIO pin(s) to disable.
 *   Refer to Reference Manuals for pinmask to GPIO port/pin mapping.
 *****************************************************************************/
__STATIC_INLINE void GPIO_EM4DisablePinWakeup(uint32_t pinmask)
{
  EFM_ASSERT((pinmask & ~_GPIO_EM4WUEN_MASK) == 0);

  GPIO->EM4WUEN &= ~pinmask;
}


/**************************************************************************//**
 * @brief
 *   Enable GPIO pin wake-up from EM4. When the function exits,
 *   EM4 mode can be safely entered.
 *
 * @note
 *   It is assumed that the GPIO pin modes are set correctly.
 *   Valid modes are @ref gpioModeInput and @ref gpioModeInputPull.
 *
 * @param[in] pinmask
 *   Bitmask containing the bitwise logic OR of which GPIO pin(s) to enable.
 *   Refer to Reference Manuals for pinmask to GPIO port/pin mapping.
 * @param[in] polaritymask
 *   Bitmask containing the bitwise logic OR of GPIO pin(s) wake-up polarity.
 *   Refer to Reference Manuals for pinmask to GPIO port/pin mapping.
 *****************************************************************************/
__STATIC_INLINE void GPIO_EM4EnablePinWakeup(uint32_t pinmask,
                                             uint32_t polaritymask)
{
  EFM_ASSERT((pinmask & ~_GPIO_EM4WUEN_MASK) == 0);
  EFM_ASSERT((polaritymask & ~_GPIO_EM4WUPOL_MASK) == 0);

  GPIO->EM4WUPOL &= ~pinmask;               /* Set wakeup polarity */
  GPIO->EM4WUPOL |= pinmask & polaritymask;
  GPIO->EM4WUEN  |= pinmask;                /* Enable wakeup */

  GPIO_EM4SetPinRetention(true);            /* Enable pin retention */

  GPIO->CMD = GPIO_CMD_EM4WUCLR;            /* Clear wake-up logic */
}

/**************************************************************************//**
 * @brief
 *   Check which GPIO pin(s) that caused a wake-up from EM4.
 *
 * @return
 *   Bitmask containing the bitwise logic OR of which GPIO pin(s) caused the
 *   wake-up. Refer to Reference Manuals for pinmask to GPIO port/pin mapping.
 *****************************************************************************/
__STATIC_INLINE uint32_t GPIO_EM4GetPinWakeupCause(void)
{
  return GPIO->EM4WUCAUSE & _GPIO_EM4WUCAUSE_MASK;
}


/**************************************************************************//**
 * @brief
 *   Enable GPIO pin retention of output enable, output value, pull enable and
 *   pull direction in EM4.
 *
 * @param[in] enable
 *   @li true - enable EM4 pin retention.
 *   @li false - disable EM4 pin retention.
 *****************************************************************************/
__STATIC_INLINE void GPIO_EM4SetPinRetention(bool enable)
{
  if (enable)
  {
    GPIO->CTRL |= GPIO_CTRL_EM4RET;
  }
  else
  {
    GPIO->CTRL &= ~GPIO_CTRL_EM4RET;
  }
}
#endif


/***************************************************************************//**
 * @brief
 *   Enable/disable input sensing.
 *
 * @details
 *   Disabling input sensing if not used, can save some energy consumption.
 *
 * @param[in] val
 *   Bitwise logic OR of one or more of:
 *   @li GPIO_INSENSE_INTSENSE - interrupt input sensing.
 *   @li GPIO_INSENSE_PRSSENSE - peripheral reflex system input sensing.
 *
 * @param[in] mask
 *   Mask containing bitwise logic OR of bits similar as for @p val used to indicate
 *   which input sense options to disable/enable.
 ******************************************************************************/
__STATIC_INLINE void GPIO_InputSenseSet(uint32_t val, uint32_t mask)
{
  GPIO->INSENSE = (GPIO->INSENSE & ~mask) | (val & mask);
}


/***************************************************************************//**
 * @brief
 *   Clear one or more pending GPIO interrupts.
 *
 * @param[in] flags
 *   Bitwise logic OR of GPIO interrupt sources to clear.
 ******************************************************************************/
__STATIC_INLINE void GPIO_IntClear(uint32_t flags)
{
  GPIO->IFC = flags;
}


void GPIO_IntConfig(GPIO_Port_TypeDef port,
                    unsigned int pin,
                    bool risingEdge,
                    bool fallingEdge,
                    bool enable);


/***************************************************************************//**
 * @brief
 *   Disable one or more GPIO interrupts.
 *
 * @param[in] flags
 *   GPIO interrupt sources to disable.
 ******************************************************************************/
__STATIC_INLINE void GPIO_IntDisable(uint32_t flags)
{
  GPIO->IEN &= ~flags;
}


/***************************************************************************//**
 * @brief
 *   Enable one or more GPIO interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using GPIO_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] flags
 *   GPIO interrupt sources to enable.
 ******************************************************************************/
__STATIC_INLINE void GPIO_IntEnable(uint32_t flags)
{
  GPIO->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending GPIO interrupts.
 *
 * @return
 *   GPIO interrupt sources pending.
 ******************************************************************************/
__STATIC_INLINE uint32_t GPIO_IntGet(void)
{
  return(GPIO->IF);
}


/***************************************************************************//**
 * @brief
 *   Get enabled and pending GPIO interrupt flags.
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note
 *   Interrupt flags are not cleared by the use of this function.
 *
 * @return
 *   Pending and enabled GPIO interrupt sources.
 *   The return value is the bitwise AND combination of
 *   - the OR combination of enabled interrupt sources in GPIO_IEN register
 *     and
 *   - the OR combination of valid interrupt flags in GPIO_IF register.
 ******************************************************************************/
__STATIC_INLINE uint32_t GPIO_IntGetEnabled(void)
{
  uint32_t tmp;

  /* Store GPIO->IEN in temporary variable in order to define explicit order
   * of volatile accesses. */
  tmp = GPIO->IEN;

  /* Bitwise AND of pending and enabled interrupts */
  return GPIO->IF & tmp;
}


/**************************************************************************//**
 * @brief
 *   Set one or more pending GPIO interrupts from SW.
 *
 * @param[in] flags
 *   GPIO interrupt sources to set to pending.
 *****************************************************************************/
__STATIC_INLINE void GPIO_IntSet(uint32_t flags)
{
  GPIO->IFS = flags;
}


/***************************************************************************//**
 * @brief
 *   Locks the GPIO configuration.
 ******************************************************************************/
__STATIC_INLINE void GPIO_Lock(void)
{
  GPIO->LOCK = GPIO_LOCK_LOCKKEY_LOCK;
}


unsigned int GPIO_PinInGet(GPIO_Port_TypeDef port, unsigned int pin);
void GPIO_PinModeSet(GPIO_Port_TypeDef port,
                     unsigned int pin,
                     GPIO_Mode_TypeDef mode,
                     unsigned int out);
void GPIO_PinOutClear(GPIO_Port_TypeDef port, unsigned int pin);
unsigned int GPIO_PinOutGet(GPIO_Port_TypeDef port, unsigned int pin);
void GPIO_PinOutSet(GPIO_Port_TypeDef port, unsigned int pin);
void GPIO_PinOutToggle(GPIO_Port_TypeDef port, unsigned int pin);

uint32_t GPIO_PortInGet(GPIO_Port_TypeDef port);
void GPIO_PortOutClear(GPIO_Port_TypeDef port, uint32_t pins);
uint32_t GPIO_PortOutGet(GPIO_Port_TypeDef port);
void GPIO_PortOutSet(GPIO_Port_TypeDef port, uint32_t pins);
void GPIO_PortOutSetVal(GPIO_Port_TypeDef port, uint32_t val, uint32_t mask);
void GPIO_PortOutToggle(GPIO_Port_TypeDef port, uint32_t pins);

/***************************************************************************//**
 * @brief
 *   Unlocks the GPIO configuration.
 ******************************************************************************/
__STATIC_INLINE void GPIO_Unlock(void)
{
  GPIO->LOCK = GPIO_LOCK_LOCKKEY_UNLOCK;
}


/** @} (end addtogroup GPIO) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_GPIO_H */
