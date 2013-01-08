/**************************************************************************//**
 * @file
 * @brief EFM32GG_DK3750 board support package
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

/**************************************************************************//**
 * @addtogroup BSP
 * @{
 *****************************************************************************/

#include "efm32.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "dvk.h"
#include "dvk_bcregisters.h"

/** Keep intialization mode */
DVK_Init_TypeDef dvkOperationMode;

/**************************************************************************//**
 * @brief Initialize EFM32GG_DK3750 board support package functionality
 * @param[in] mode Initialize in EBI or SPI mode
 *****************************************************************************/
void DVK_init(DVK_Init_TypeDef mode)
{
  bool ret = false;

  if (mode == DVK_Init_EBI)
  {
    dvkOperationMode = mode;
    DVK_busControlMode(DVK_BusControl_EBI);
    ret = DVK_EBI_init();
  }
  if (mode == DVK_Init_SPI)
  {
    dvkOperationMode = mode;
    DVK_busControlMode(DVK_BusControl_SPI);
    ret = DVK_SPI_init();
  }

  if (ret == false)
  {
    /* Unable to access board control, this is an abornomal situation. */
    /* Try to restart kit and reprogram EFM32 with a standard example */
    /* as this is most likely caused by a peripheral misconfiguration. */
    while (1) ;
  }

  DVK_setEnergyMode(0);
}


/**************************************************************************//**
 * @brief Disable EFM32GG_DK3750 board support package functionality
 *****************************************************************************/
void DVK_disable(void)
{
  if (dvkOperationMode == DVK_Init_EBI)
  {
    DVK_EBI_disable();
  }
  if (dvkOperationMode == DVK_Init_SPI)
  {
    DVK_SPI_disable();
  }
  DVK_busControlMode(DVK_BusControl_OFF);
}


/**************************************************************************//**
 * @brief Configure Board Controller bus decode logic
 * @param[in] mode Mode of operation for decode logic
 *****************************************************************************/
void DVK_busControlMode(DVK_BusControl_TypeDef mode)
{
  /* Configure GPIO pins for Board Bus mode */
  /* Note: Inverter on GPIO lines to BC, so signals are active low */
  CMU_ClockEnable(cmuClock_GPIO, true);

  switch (mode)
  {
  case DVK_BusControl_OFF:
    /* Configure board for OFF mode on PB15 MCU_EBI_CONNECT */
    GPIO_PinModeSet(gpioPortB, 15, gpioModePushPull, 1);
    /* Configure board for OFF mode on PD13 MCU_SPI_CONNECT */
    GPIO_PinModeSet(gpioPortD, 13, gpioModePushPull, 1);
    break;
  case DVK_BusControl_DIRECT:
    /* Configure board for DIRECT on PB15 MCU_EBI_CONNECT */
    GPIO_PinModeSet(gpioPortB, 15, gpioModePushPull, 0);
    /* Configure board for DIRECT on PD13 MCU_SPI_CONNECT */
    GPIO_PinModeSet(gpioPortD, 13, gpioModePushPull, 0);
    break;
  case DVK_BusControl_SPI:
    /* Configure board for SPI mode on PB15 MCU_EBI_CONNECT */
    GPIO_PinModeSet(gpioPortB, 15, gpioModePushPull, 1);
    /* Configure board for SPI mode on PD13 MCU_SPI_CONNECT */
    GPIO_PinModeSet(gpioPortD, 13, gpioModePushPull, 0);
    break;
  case DVK_BusControl_EBI:
  default:
    /* Configure board for EBI mode on PB15 MCU_EBI_CONNECT */
    GPIO_PinModeSet(gpioPortB, 15, gpioModePushPull, 0);
    /* Configure board for EBI mode on PD13 MCU_SPI_CONNECT */
    GPIO_PinModeSet(gpioPortD, 13, gpioModePushPull, 1);
    break;
  }
}


/**************************************************************************//**
 * @brief Set board LEDs
 *
 * @param[in] leds
 *    16 bits enabling or disabling individual board LEDs
 *****************************************************************************/
void DVK_setLEDs(uint16_t leds)
{
  DVK_writeRegister(&BC_REGISTER->UIF_LEDS, leds);
}


/**************************************************************************//**
 * @brief Get board LED configuration
 *
 * @return
 *    16 bits of LED status
 *****************************************************************************/
uint16_t DVK_getLEDs(void)
{
  return DVK_readRegister(&BC_REGISTER->UIF_LEDS);
}


/**************************************************************************//**
 * @brief DK3750 Peripheral Access Control
 *    Enable or disable access to on-board peripherals through switches
 *    and SPI switch where applicable. Turn off conflicting peripherals when
 *    enabling another.
 * @param[in] perf
 *    Which peripheral to configure
 * @param[in] enable
 *    If true, sets up access to peripheral, if false disables it
 *****************************************************************************/
void DVK_peripheralAccess(DVK_Peripheral_TypeDef perf, bool enable)
{
  uint16_t perfControl;

  perfControl = DVK_readRegister(&BC_REGISTER->PERICON);

  /* Enable or disable the specificed peripheral by setting board control switch */
  if (enable)
  {
    switch (perf)
    {
    case DVK_RS232_SHUTDOWN:
      perfControl |= (1 << BC_PERICON_RS232_SHUTDOWN_SHIFT);
      break;

    case DVK_RS232_UART:
      perfControl &= ~(1 << BC_PERICON_RS232_SHUTDOWN_SHIFT);
      perfControl &= ~(1 << BC_PERICON_RS232_LEUART_SHIFT);
      perfControl |= (1 << BC_PERICON_RS232_UART_SHIFT);
      break;

    case DVK_RS232_LEUART:
      perfControl &= ~(1 << BC_PERICON_RS232_SHUTDOWN_SHIFT);
      perfControl &= ~(1 << BC_PERICON_RS232_UART_SHIFT);
      perfControl |= (1 << BC_PERICON_RS232_LEUART_SHIFT);
      break;

    case DVK_I2C:
      perfControl |= (1 << BC_PERICON_I2C_SHIFT);
      break;

    case DVK_ETH:
      /* Enable SPI interface */
      DVK_spiControl(DVK_SPI_Ethernet);

      /* Enable Ethernet analog switches */
      perfControl |= (1 << BC_PERICON_I2S_ETH_SHIFT);
      perfControl |= (1 << BC_PERICON_I2S_ETH_SEL_SHIFT);

      /* Disable Analog Diff Input - pins PD0 and PD1 is shared */
      perfControl &= ~(1 << BC_PERICON_ANALOG_DIFF_SHIFT);
      /* Disable Touch Inputs - pin PD3 is shared */
      perfControl &= ~(1 << BC_PERICON_TOUCH_SHIFT);
      /* Disable Analog SE Input - pin PD2 is shared */
      perfControl &= ~(1 << BC_PERICON_ANALOG_SE_SHIFT);
      break;

    case DVK_I2S:
      /* Direct SPI interface to I2S DAC */
      DVK_spiControl(DVK_SPI_Audio);

      /* Also make surea Audio out is connected for I2S operation */
      perfControl |= (1 << BC_PERICON_AUDIO_OUT_SHIFT);
      perfControl |= (1 << BC_PERICON_AUDIO_OUT_SEL_SHIFT);
      perfControl |= (1 << BC_PERICON_I2S_ETH_SHIFT);
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SEL_SHIFT);

      /* Disable Analog Diff Input - pins PD0 and PD1 is shared */
      perfControl &= ~(1 << BC_PERICON_ANALOG_DIFF_SHIFT);
      /* Disable Touch Inputs - pin PD3 is shared */
      perfControl &= ~(1 << BC_PERICON_TOUCH_SHIFT);
      /* Disable Analog SE Input - pin PD2 is shared */
      perfControl &= ~(1 << BC_PERICON_ANALOG_SE_SHIFT);
      break;

    case DVK_TRACE:
      perfControl |= (1 << BC_PERICON_TRACE_SHIFT);
      break;

    case DVK_TOUCH:
      perfControl |= (1 << BC_PERICON_TOUCH_SHIFT);
      /* Disconnect SPI switch, pin PD3 is shared */
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SHIFT);
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SEL_SHIFT);
      DVK_spiControl(DVK_SPI_OFF);
      break;

    case DVK_AUDIO_IN:
      perfControl |= (1 << BC_PERICON_AUDIO_IN_SHIFT);
      break;

    case DVK_AUDIO_OUT:
      perfControl &= ~(1 << BC_PERICON_AUDIO_OUT_SEL_SHIFT);
      perfControl |= (1 << BC_PERICON_AUDIO_OUT_SHIFT);
      break;

    case DVK_ANALOG_DIFF:
      perfControl |= (1 << BC_PERICON_ANALOG_DIFF_SHIFT);
      /* Disconnect SPI switch, pin PD0 and PD1 is shared */
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SHIFT);
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SEL_SHIFT);
      DVK_spiControl(DVK_SPI_OFF);
      break;

    case DVK_ANALOG_SE:
      perfControl |= (1 << BC_PERICON_ANALOG_SE_SHIFT);
      /* Disconnect SPI switch, pin PD2 is shared */
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SHIFT);
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SEL_SHIFT);
      DVK_spiControl(DVK_SPI_OFF);
      break;

    case DVK_MICROSD:
      perfControl |= (1 << BC_PERICON_SPI_SHIFT);
      break;

    case DVK_TFT:
      /* Enable SPI to SSD2119 */
      DVK_spiControl(DVK_SPI_Display);
      /* Enable SPI analog switch */
      perfControl |= (1 << BC_PERICON_I2S_ETH_SHIFT);
      /* Disable Analog Diff Input - pins D0 and D1 is shared */
      perfControl &= ~(1 << BC_PERICON_ANALOG_DIFF_SHIFT);
      /* Disable Touch Inputs - pin D3 is shared */
      perfControl &= ~(1 << BC_PERICON_TOUCH_SHIFT);
      /* Disable Analog SE Input - pin D2 is shared */
      perfControl &= ~(1 << BC_PERICON_ANALOG_SE_SHIFT);
      break;
    }
  }
  else
  {
    switch (perf)
    {
    case DVK_RS232_SHUTDOWN:
      perfControl &= ~(1 << BC_PERICON_RS232_SHUTDOWN_SHIFT);
      break;

    case DVK_RS232_UART:
      perfControl |= (1 << BC_PERICON_RS232_SHUTDOWN_SHIFT);
      perfControl &= ~(1 << BC_PERICON_RS232_UART_SHIFT);
      break;

    case DVK_RS232_LEUART:
      perfControl |= (1 << BC_PERICON_RS232_SHUTDOWN_SHIFT);
      perfControl &= ~(1 << BC_PERICON_RS232_LEUART_SHIFT);
      break;

    case DVK_I2C:
      perfControl &= ~(1 << BC_PERICON_I2C_SHIFT);
      break;

    case DVK_ETH:
      /* Disable SPI interface */
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SHIFT);
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SEL_SHIFT);
      DVK_spiControl(DVK_SPI_OFF);
      break;

    case DVK_I2S:
      /* Disable SPI interface and audio out */
      perfControl &= ~(1 << BC_PERICON_AUDIO_OUT_SHIFT);
      perfControl &= ~(1 << BC_PERICON_AUDIO_OUT_SEL_SHIFT);
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SHIFT);
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SEL_SHIFT);
      DVK_spiControl(DVK_SPI_OFF);
      break;

    case DVK_TRACE:
      perfControl &= ~(1 << BC_PERICON_TRACE_SHIFT);
      break;

    case DVK_TOUCH:
      perfControl &= ~(1 << BC_PERICON_TOUCH_SHIFT);
      break;

    case DVK_AUDIO_IN:
      perfControl &= ~(1 << BC_PERICON_AUDIO_IN_SHIFT);
      break;

    case DVK_AUDIO_OUT:
      perfControl &= ~(1 << BC_PERICON_AUDIO_OUT_SEL_SHIFT);
      perfControl &= ~(1 << BC_PERICON_AUDIO_OUT_SHIFT);
      break;

    case DVK_ANALOG_DIFF:
      perfControl &= ~(1 << BC_PERICON_ANALOG_DIFF_SHIFT);
      break;

    case DVK_ANALOG_SE:
      perfControl &= ~(1 << BC_PERICON_ANALOG_SE_SHIFT);
      break;

    case DVK_MICROSD:
      perfControl &= ~(1 << BC_PERICON_SPI_SHIFT);
      break;

    case DVK_TFT:
      /* Disable SPI interface */
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SHIFT);
      perfControl &= ~(1 << BC_PERICON_I2S_ETH_SEL_SHIFT);
      DVK_spiControl(DVK_SPI_OFF);
      break;
    }
  }
  /* Write back register */
  DVK_writeRegister(&BC_REGISTER->PERICON, perfControl);
}


/**************************************************************************//**
 * @brief Get status of push buttons on kit
 *
 * @return
 *    Button state, each bit representing each push button PB0-PB4
 *****************************************************************************/
uint16_t DVK_getPushButtons(void)
{
  uint16_t tmp;

  tmp = DVK_readRegister(&BC_REGISTER->UIF_PB);

  return (~tmp) & 0x000F;
}


/**************************************************************************//**
 * @brief Configure SPI for correct peripheral
 *
 * @param[in] device
 *    Device to enable SPI bus for
 *****************************************************************************/
void DVK_spiControl(DVK_SpiControl_TypeDef device)
{
  switch (device)
  {
  case DVK_SPI_Audio:
    DVK_writeRegister(&BC_REGISTER->SPI_DEMUX, BC_SPI_DEMUX_SLAVE_AUDIO);
    break;

  case DVK_SPI_Ethernet:
    DVK_writeRegister(&BC_REGISTER->SPI_DEMUX, BC_SPI_DEMUX_SLAVE_ETHERNET);
    break;

  case DVK_SPI_Display:
    DVK_writeRegister(&BC_REGISTER->SPI_DEMUX, BC_SPI_DEMUX_SLAVE_DISPLAY);
    break;

  case DVK_SPI_OFF:
    USART_Reset(USART1);
    CMU_ClockEnable(cmuClock_USART1, false);
    break;
  }
}


/**************************************************************************//**
 * @brief Inform AEM/Board Controller about what energy mode we are currently
 *        entering. This information can be used for better visual feedback of
 *        EFM32GG activity for the board controller and PC applications
 * @param energyMode What energy mode we are going to use next
 *****************************************************************************/
void DVK_setEnergyMode(uint16_t energyMode)
{
  DVK_writeRegister(&BC_REGISTER->EM, energyMode);
}


/**************************************************************************//**
 * @brief Enable "Control" buttons/joystick/dip switch interrupts
 * @param flags Board control interrupt flags, INTEN_<something>
 *****************************************************************************/
void DVK_enableInterrupt(uint16_t flags)
{
  uint16_t tmp;

  /* Add flags to interrupt enable register */
  tmp  = DVK_readRegister(&BC_REGISTER->INTEN);
  tmp |= flags;
  DVK_writeRegister(&BC_REGISTER->INTEN, tmp);
}


/**************************************************************************//**
 * @brief Disable "Control" buttons/joystick/dip switch interrupts
 * @param flags Board control interrupt flags, BC_INTEN_<something>
 *****************************************************************************/
void DVK_disableInterrupt(uint16_t flags)
{
  uint16_t tmp;

  /* Clear flags from interrupt enable register */
  tmp   = DVK_readRegister(&BC_REGISTER->INTEN);
  flags = ~(flags);
  tmp  &= flags;
  DVK_writeRegister(&BC_REGISTER->INTEN, tmp);
}


/**************************************************************************//**
 * @brief Clear interrupts
 * @param flags Board control interrupt flags, BC_INTEN_<something>
 *****************************************************************************/
void DVK_clearInterruptFlags(uint16_t flags)
{
  uint16_t tmp;
  tmp  = DVK_readRegister(&BC_REGISTER->INTFLAG);
  tmp &= ~(flags);
  DVK_writeRegister(&BC_REGISTER->INTFLAG, tmp);
}


/**************************************************************************//**
 * @brief Read interrupt flags
 * @return Returns currently triggered interrupts
 *****************************************************************************/
uint16_t DVK_getInterruptFlags(void)
{
  return DVK_readRegister(&BC_REGISTER->INTFLAG);
}


/**************************************************************************//**
 * @brief Get joystick button status
 * @return Joystick controller status
 *****************************************************************************/
uint16_t DVK_getJoystick(void)
{
  uint16_t joyStick = 0;

  joyStick = ~(DVK_readRegister(&BC_REGISTER->UIF_JOYSTICK)) & 0x001f;

  return joyStick;
}


/**************************************************************************//**
 * @brief Get dipswitch status
 *        The DIP switches are free for user programmable purposes
 * @return Dip switch
 *****************************************************************************/
uint16_t DVK_getDipSwitch(void)
{
  return DVK_readRegister(&BC_REGISTER->UIF_DIP) & 0x000f;
}


/**************************************************************************//**
 * @brief Configure display control
 *****************************************************************************/
void DVK_displayControl(DVK_Display_TypeDef option)
{
  uint16_t tmp;

  switch (option)
  {
  case DVK_Display_EBI:
    DVK_writeRegister(&BC_REGISTER->ARB_CTRL, BC_ARB_CTRL_EBI);
    break;

  case DVK_Display_SPI:
    DVK_writeRegister(&BC_REGISTER->ARB_CTRL, BC_ARB_CTRL_SPI);
    break;

  case DVK_Display_BC:
    DVK_writeRegister(&BC_REGISTER->ARB_CTRL, BC_ARB_CTRL_BC);
    break;

  case DVK_Display_PowerEnable:
    tmp  = DVK_readRegister(&BC_REGISTER->DISPLAY_CTRL);
    tmp |= (BC_DISPLAY_CTRL_POWER_ENABLE);
    DVK_writeRegister(&BC_REGISTER->DISPLAY_CTRL, tmp);
    break;

  case DVK_Display_PowerDisable:
    tmp  = DVK_readRegister(&BC_REGISTER->DISPLAY_CTRL);
    tmp &= ~(BC_DISPLAY_CTRL_POWER_ENABLE);
    DVK_writeRegister(&BC_REGISTER->DISPLAY_CTRL, tmp);
    break;

  case DVK_Display_ResetAssert:
    tmp  = DVK_readRegister(&BC_REGISTER->DISPLAY_CTRL);
    tmp |= (BC_DISPLAY_CTRL_RESET);
    DVK_writeRegister(&BC_REGISTER->DISPLAY_CTRL, tmp);
    break;

  case DVK_Display_ResetRelease:
    tmp  = DVK_readRegister(&BC_REGISTER->DISPLAY_CTRL);
    tmp &= ~(BC_DISPLAY_CTRL_RESET);
    DVK_writeRegister(&BC_REGISTER->DISPLAY_CTRL, tmp);
    break;

  case DVK_Display_Mode8080:
    tmp  = DVK_readRegister(&BC_REGISTER->DISPLAY_CTRL);
    tmp &= ~(BC_DISPLAY_CTRL_MODE_GENERIC);
    DVK_writeRegister(&BC_REGISTER->DISPLAY_CTRL, tmp);
    break;

  case DVK_Display_ModeGeneric:
    tmp  = DVK_readRegister(&BC_REGISTER->DISPLAY_CTRL);
    tmp |= (BC_DISPLAY_CTRL_MODE_GENERIC);
    DVK_writeRegister(&BC_REGISTER->DISPLAY_CTRL, tmp);
    break;

  default:
    /* Unknown command */
    while (1) ;
  }
}

/** @} (end group BSP) */
