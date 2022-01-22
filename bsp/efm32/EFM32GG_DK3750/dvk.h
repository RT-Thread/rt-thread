/**************************************************************************//**
 * @file
 * @brief EFM32GG_DK3750 board support package API
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
#ifndef __DVK_H
#define __DVK_H

/***************************************************************************//**
 * @addtogroup BSP
 * @{
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "efm32.h"
#include "dvk_bcregisters.h"

#ifdef __cplusplus
extern "C" {
#endif

/** DVK board control access method */
typedef enum
{
  DVK_Init_EBI,    /**< Use EBI to interface board control functionality */
  DVK_Init_SPI,    /**< Use SPI to interface board control functionality */
  DVK_Init_DIRECT, /**< No board control, only GPIO */
  DVK_Init_OFF,    /**< Disabled */
} DVK_Init_TypeDef;

extern DVK_Init_TypeDef dvkOperationMode;

/** Bus control access */
typedef enum
{
  DVK_BusControl_OFF,    /**< Board control disable */
  DVK_BusControl_DIRECT, /**< GPIO direct drive (n/a) */
  DVK_BusControl_SPI,    /**< Configure Board controller for SPI mode */
  DVK_BusControl_EBI,    /**< Configure Board controller for EBI mode */
} DVK_BusControl_TypeDef;


/** Display Control */
typedef enum
{
  DVK_Display_EBI,          /**< SSD2119 TFT controller driven by EFM32GG EBI interface */
  DVK_Display_SPI,          /**< SSD2119 TFT controller driven by EFM32GG SPI interface */
  DVK_Display_BC,           /**< SSD2119 TFT controller driven by board controller (AEM) */
  DVK_Display_PowerEnable,  /**< SSD2119 Enable power  */
  DVK_Display_PowerDisable, /**< SSD2119 Disable power  */
  DVK_Display_ResetAssert,  /**< Hold SSD2119 in reset */
  DVK_Display_ResetRelease, /**< Release SSD2119 in reset */
  DVK_Display_Mode8080,     /**< Configure SSD2119 for 8080 mode of operation  */
  DVK_Display_ModeGeneric,  /**< Configure SSD2119 for Generic+SPI mode of operation */
} DVK_Display_TypeDef;


/** SPI control */
typedef enum
{
  DVK_SPI_Audio,    /**< Configure switchable SPI interface to Audio I2S */
  DVK_SPI_Ethernet, /**< Configure switchable SPI interface to Ethernet */
  DVK_SPI_Display,  /**< Configure switchable SPI interface to SSD2119 */
  DVK_SPI_OFF,      /**< Disable SPI interface */
} DVK_SpiControl_TypeDef;


/** Peripherals control structure */
typedef enum
{
  DVK_RS232_SHUTDOWN, /**< Disable RS232 */
  DVK_RS232_UART,     /**< UART control of RS232 */
  DVK_RS232_LEUART,   /**< LEUART control of RS232 */
  DVK_I2C,            /**< I2C */
  DVK_ETH,            /**< Ethernet */
  DVK_I2S,            /**< Audio I2S */
  DVK_TRACE,          /**< ETM Trace */
  DVK_TOUCH,          /**< Display touch interface */
  DVK_AUDIO_IN,       /**< Audio In */
  DVK_AUDIO_OUT,      /**< Audio Out */
  DVK_ANALOG_DIFF,    /**< Analog DIFF */
  DVK_ANALOG_SE,      /**< Analog SE */
  DVK_MICROSD,        /**< MicroSD SPI interace */
  DVK_TFT,            /**< SSD2119 TFT controller */
} DVK_Peripheral_TypeDef;


/* Initalize DVK board for access to external PSRAM, Flash and BC registers */
void DVK_init(DVK_Init_TypeDef mode);
void DVK_disable(void);

/* Board controller control API */
void DVK_busControlMode(DVK_BusControl_TypeDef mode);
void DVK_peripheralAccess(DVK_Peripheral_TypeDef perf, bool enable);
void DVK_spiControl(DVK_SpiControl_TypeDef device);

/* Board controller access function  */
uint16_t DVK_getPushButtons(void);
uint16_t DVK_getJoystick(void);
uint16_t DVK_getDipSwitch(void);
void DVK_setLEDs(uint16_t leds);
uint16_t DVK_getLEDs(void);

/* Miscellaneous */
void DVK_setEnergyMode(uint16_t energyMode);
void DVK_displayControl(DVK_Display_TypeDef option);

/* Board controller interrupt support */
void DVK_enableInterrupt(uint16_t flags);
void DVK_disableInterrupt(uint16_t flags);
uint16_t DVK_getInterruptFlags(void);
void DVK_clearInterruptFlags(uint16_t flags);

/* EBI access */
bool DVK_EBI_init(void);
void DVK_EBI_disable(void);
void DVK_EBI_extendedAddressRange(bool enable);
__STATIC_INLINE void DVK_EBI_writeRegister(volatile uint16_t *addr, uint16_t data);
__STATIC_INLINE uint16_t DVK_EBI_readRegister(volatile uint16_t *addr);

/* SPI access */
bool DVK_SPI_init(void);
void DVK_SPI_disable(void);
uint16_t DVK_SPI_readRegister(volatile uint16_t *addr);
void DVK_SPI_writeRegister(volatile uint16_t *addr, uint16_t data);

/* MCU-plug-in-board (BRD3600) API */
void DVK_BRD3600A_init(void);
void DVK_BRD3600A_deInit(void);
void DVK_BRD3600A_usbStatusLEDEnable(int enable);
void DVK_BRD3600A_usbVBUSSwitchEnable(int enable);
int  DVK_BRD3600A_usbVBUSGetOCFlagState(void);


/* For "backward compatibility" with DVK */
/** DVK_enablePeripheral() backward compatibility */
#define DVK_enablePeripheral(X)     DVK_peripheralAccess(X, true)
/** DVK_disablePeripheral() backward compatibility */
#define DVK_disablePeripheral(X)    DVK_peripheralAccess(X, false)

/**************************************************************************//**
 * @brief Write data into 16-bit board control register using mem.mapped EBI
 * @param addr Address of board controller register
 * @param data Data to write into register
 *****************************************************************************/
__STATIC_INLINE void DVK_EBI_writeRegister(volatile uint16_t *addr, uint16_t data)
{
  *addr = data;
}


/**************************************************************************//**
 * @brief Read data from 16-bit board control register using memory mapped EBI
 * @param addr Register to read from
 * @return Value of board controller register
 *****************************************************************************/
__STATIC_INLINE uint16_t DVK_EBI_readRegister(volatile uint16_t *addr)
{
  return *addr;
}


/**************************************************************************//**
 * @brief Read data from 16-bit board control register
 * @param addr Register to read
 * @return Value of board controller register
 *****************************************************************************/
__STATIC_INLINE uint16_t DVK_readRegister(volatile uint16_t *addr)
{
  if (dvkOperationMode == DVK_Init_EBI)
  {
    return DVK_EBI_readRegister(addr);
  }
  else
  {
    return DVK_SPI_readRegister(addr);
  }
}


/**************************************************************************//**
 * @brief Write data into 16-bit board control register
 * @param addr Address to board control register
 * @param data Data to write into register
 *****************************************************************************/
__STATIC_INLINE void DVK_writeRegister(volatile uint16_t *addr, uint16_t data)
{
  if (dvkOperationMode == DVK_Init_EBI)
  {
    DVK_EBI_writeRegister(addr, data);
  }
  else
  {
    DVK_SPI_writeRegister(addr, data);
  }
}

#ifdef __cplusplus
}
#endif

/** @} (end group BSP) */

#endif
