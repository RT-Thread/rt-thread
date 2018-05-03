/**************************************************************************//**
 * @file
 * @brief DVK Peripheral Board Control, prototypes and definitions
 * @author Energy Micro AS
 * @version 2.0.1
 ******************************************************************************
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
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
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
 *****************************************************************************/

#ifndef __DVK_BOARDCONTROL_H
#define __DVK_BOARDCONTROL_H

/***************************************************************************//**
 * @addtogroup BSP
 * @{
 ******************************************************************************/

#include <stdint.h>
#include "dvk_bcregisters.h"

/** Periperhal access switches */
typedef enum
{
  DVK_ACCEL          = BC_PERCTRL_ACCEL,
  DVK_AMBIENT        = BC_PERCTRL_AMBIENT,
  DVK_POTMETER       = BC_PERCTRL_POTMETER,
  DVK_RS232A         = BC_PERCTRL_RS232A,
  DVK_RS232B         = BC_PERCTRL_RS232B,
  DVK_SPI            = BC_PERCTRL_SPI,
  DVK_I2C            = BC_PERCTRL_I2C,
  DVK_IRDA           = BC_PERCTRL_IRDA,
  DVK_ANALOG_SE      = BC_PERCTRL_ANALOG_SE,
  DVK_ANALOG_DIFF    = BC_PERCTRL_ANALOG_DIFF,
  DVK_AUDIO_OUT      = BC_PERCTRL_AUDIO_OUT,
  DVK_AUDIO_IN       = BC_PERCTRL_AUDIO_IN,
  DVK_ACCEL_GSEL     = BC_PERCTRL_ACCEL_GSEL,
  DVK_ACCEL_SELFTEST = BC_PERCTRL_ACCEL_SELFTEST,
  DVK_RS232_SHUTDOWN = BC_PERCTRL_RS232_SHUTDOWN,
  DVK_IRDA_SHUTDOWN  = BC_PERCTRL_IRDA_SHUTDOWN
} DVKPeripheral;

/* Peripheral Control */
void DVK_enablePeripheral(DVKPeripheral peri);
void DVK_disablePeripheral(DVKPeripheral peri);
void DVK_enableBus(void);
void DVK_disableBus(void);

/* Read board controllers */
uint16_t DVK_getPushButtons(void);
uint16_t DVK_getJoystick(void);
uint16_t DVK_getDipSwitch(void);

/* Report AEM status */
void DVK_setEnergyMode(uint16_t energyMode);

/* User LEDs */
void DVK_setLEDs(uint16_t leds);
uint16_t DVK_getLEDs(void);

/* Interrupt callback */
void DVK_enableInterrupt(uint16_t flags);
void DVK_disableInterrupt(uint16_t flags);

uint16_t DVK_getInterruptFlags(void);
void DVK_clearInterruptFlags(uint16_t flags);

/** @} (end group BSP) */

#endif

