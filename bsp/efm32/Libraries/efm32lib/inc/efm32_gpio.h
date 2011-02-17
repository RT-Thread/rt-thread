/***************************************************************************//**
 * @file
 * @brief General Purpose IO (GPIO) peripheral API for EFM32.
 * @author Energy Micro AS
 * @version 1.3.0
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
#ifndef __EFM32_GPIO_H
#define __EFM32_GPIO_H

#include <stdbool.h>
#include "efm32.h"
#include "efm32_bitband.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EFM32_Library
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
static __INLINE void GPIO_DbgSWDClkEnable(bool enable)
{
  BITBAND_Peripheral(&(GPIO->ROUTE), _GPIO_ROUTE_SWCLKPEN_SHIFT, (unsigned int) enable);
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
static __INLINE void GPIO_DbgSWDIOEnable(bool enable)
{
  BITBAND_Peripheral(&(GPIO->ROUTE), _GPIO_ROUTE_SWDIOPEN_SHIFT, (unsigned int) enable);
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
static __INLINE void GPIO_DbgSWOEnable(bool enable)
{
  BITBAND_Peripheral(&(GPIO->ROUTE), _GPIO_ROUTE_SWOPEN_SHIFT, (unsigned int) enable);
}


void GPIO_DriveModeSet(GPIO_Port_TypeDef port, GPIO_DriveMode_TypeDef mode);

/***************************************************************************//**
 * @brief
 *   Enable/disable input sensing.
 *
 * @details
 *   Disabling input sensing if not used, can save some energy consumption.
 *
 * @param[in] val
 *   Logical OR of one or more of:
 *   @li GPIO_INSENSE_INTSENSE - interrupt input sensing.
 *   @li GPIO_INSENSE_PRSSENSE - peripheral reflex system input sensing.
 *
 * @param[in] mask
 *   Mask containing logical OR of bits similar as for @p val used to indicate
 *   which input sense options to disable/enable.
 ******************************************************************************/
static __INLINE void GPIO_InputSenseSet(uint32_t val, uint32_t mask)
{
  GPIO->INSENSE = (GPIO->INSENSE & ~mask) | (val & mask);
}


/***************************************************************************//**
 * @brief
 *   Clear one or more pending GPIO interrupts.
 *
 * @param[in] flags
 *   GPIO interrupt sources to clear.
 ******************************************************************************/
static __INLINE void GPIO_IntClear(uint32_t flags)
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
static __INLINE void GPIO_IntDisable(uint32_t flags)
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
static __INLINE void GPIO_IntEnable(uint32_t flags)
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
static __INLINE uint32_t GPIO_IntGet(void)
{
  return(GPIO->IF);
}


/**************************************************************************//**
 * @brief
 *   Set one or more pending GPIO interrupts from SW.
 *
 * @param[in] flags
 *   GPIO interrupt sources to set to pending.
 *****************************************************************************/
static __INLINE void GPIO_IntSet(uint32_t flags)
{
  GPIO->IFS = flags;
}


/***************************************************************************//**
 * @brief
 *   Locks the GPIO configuration.
 ******************************************************************************/
static __INLINE void GPIO_Lock(void)
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
static __INLINE void GPIO_Unlock(void)
{
  GPIO->LOCK = GPIO_LOCK_LOCKKEY_UNLOCK;
}


/** @} (end addtogroup GPIO) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32_GPIO_H */
