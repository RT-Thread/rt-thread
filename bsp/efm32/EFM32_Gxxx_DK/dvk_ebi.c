/**************************************************************************//**
 * @file
 * @brief EBI implementation of Board Control interface
 *        This implementation works for devices w/o LCD display on the
 *        MCU module, specifically the EFM32_G2xx_DK development board
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
#include "efm32.h"
#include "em_ebi.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "dvk.h"
#include "dvk_bcregisters.h"

/***************************************************************************//**
 * @addtogroup BSP
 * @{
 ******************************************************************************/

#if defined(EBI_PRESENT)
/**************************************************************************//**
 * @brief Configure EBI (external bus interface) for Board Control register
 * access
 *****************************************************************************/
void DVK_EBI_configure(void)
{
  EBI_Init_TypeDef ebiConfig = EBI_INIT_DEFAULT;

  /* Run time check if we have EBI on-chip capability on this device */
  switch ((DEVINFO->PART & _DEVINFO_PART_DEVICE_NUMBER_MASK) >>
          _DEVINFO_PART_DEVICE_NUMBER_SHIFT)
  {
  /* Only device types EFM32G 280/290/880 and 890 have EBI capability */
  case 280:
  case 290:
  case 880:
  case 890:
    break;
  default:
    /* This device do not have EBI capability - use SPI to interface DVK */
    /* With high probability your project has been configured for an */
    /* incorrect part number. */
    while (1) ;
  }

  /* Enable clocks */
  CMU_ClockEnable(cmuClock_EBI, true);
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure mode - disable SPI, enable EBI */
  GPIO_PinModeSet(gpioPortC, 13, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortC, 12, gpioModePushPull, 0);

  /* Configure GPIO pins as push pull */
  /* EBI AD9..15 */
  GPIO_PinModeSet(gpioPortA, 0, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortA, 1, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortA, 2, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortA, 3, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortA, 4, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortA, 5, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortA, 6, gpioModePushPull, 0);

  /* EBI AD8 */
  GPIO_PinModeSet(gpioPortA, 15, gpioModePushPull, 0);

  /* EBI CS0-CS3 */
  GPIO_PinModeSet(gpioPortD, 9, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortD, 10, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortD, 11, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortD, 12, gpioModePushPull, 0);

  /* EBI AD0..7 */
  GPIO_PinModeSet(gpioPortE, 8, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 9, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 10, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 11, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 12, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 13, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 14, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 15, gpioModePushPull, 0);

  /* EBI ARDY/ALEN/Wen/Ren */
  GPIO_PinModeSet(gpioPortF, 2, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortF, 3, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortF, 4, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortF, 5, gpioModePushPull, 0);

  /* Configure EBI controller, changing default values */
  ebiConfig.mode = ebiModeD16A16ALE;
  /* Enable bank 0 address map 0x80000000, FPGA Flash */
  /* Enable bank 1 address map 0x84000000, FPGA SRAM */
  /* Enable bank 2 address map 0x88000000, FPGA TFT Display (SSD2119) */
  /* Enable bank 3 address map 0x8c000000, FPGA Board Control Registers */
  ebiConfig.banks = EBI_BANK0|EBI_BANK1|EBI_BANK2|EBI_BANK3;
  ebiConfig.csLines = EBI_CS0|EBI_CS1|EBI_CS2|EBI_CS3;

  /* Address Setup and hold time */
  ebiConfig.addrHoldCycles = 3;
  ebiConfig.addrSetupCycles = 3;

  /* Read cycle times */
  ebiConfig.readStrobeCycles = 7;
  ebiConfig.readHoldCycles = 3;
  ebiConfig.readSetupCycles = 3;

  /* Write cycle times */
  ebiConfig.writeStrobeCycles = 7;
  ebiConfig.writeHoldCycles = 3;
  ebiConfig.writeSetupCycles = 3;

  /* Polarity values are default */

  /* Configure EBI */
  EBI_Init(&ebiConfig);
}


/**************************************************************************//**
 * @brief Initialize EBI
 * access
*  @return true on success, false on failure
 *****************************************************************************/
bool DVK_EBI_init(void)
{
  uint16_t     ebiMagic;
  int          retry = 10;

  /* Disable all GPIO pins and register  */
  DVK_EBI_disable();
  /* Configure EBI */
  DVK_EBI_configure();
  /* Verify that EBI access is working, if not kit is in SPI mode and needs to
   * be configured for EBI access */
  ebiMagic = DVK_EBI_readRegister(BC_MAGIC);
  while ((ebiMagic != BC_MAGIC_VALUE) && retry)
  {
    DVK_EBI_disable();
    /* Enable SPI interface */
    DVK_SPI_init();
    /* Set EBI mode - after this SPI access will no longer be available */
    ebiMagic = DVK_SPI_readRegister(BC_MAGIC);
    DVK_SPI_writeRegister(BC_CFG, BC_CFG_EBI);
    /* Disable SPI */
    DVK_SPI_disable();

    /* Now setup EBI again */
    DVK_EBI_configure();
    /* Wait until ready */
    ebiMagic = DVK_EBI_readRegister(BC_MAGIC);
    if (ebiMagic == BC_MAGIC_VALUE) break;

    retry--;
  }
  if ( ! retry ) return false;

  DVK_EBI_writeRegister(BC_LED, retry);
  return true;
}

/**************************************************************************//**
 * @brief Disable EBI interface, free all GPIO pins
 *****************************************************************************/
void DVK_EBI_disable(void)
{
  /* Disable EBI and SPI _BC_BUS_CONNECT */
  GPIO_PinModeSet(gpioPortC, 12, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortC, 13, gpioModeDisabled, 0);

  /* Configure GPIO pins as disabled */
  GPIO_PinModeSet(gpioPortA, 0, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 1, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 2, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 3, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 4, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 5, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 6, gpioModeDisabled, 0);

  GPIO_PinModeSet(gpioPortA, 15, gpioModeDisabled, 0);

  GPIO_PinModeSet(gpioPortD, 9, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortD, 10, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortD, 11, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortD, 12, gpioModeDisabled, 0);

  GPIO_PinModeSet(gpioPortE, 8, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 9, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 10, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 11, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 12, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 13, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 14, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 15, gpioModeDisabled, 0);

  GPIO_PinModeSet(gpioPortF, 2, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortF, 3, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortF, 4, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortF, 5, gpioModeDisabled, 0);

  /* Disable EBI controller */
#if 0
  EBI_Disable();
#endif
  /* Disable EBI clock in CMU */
  CMU_ClockEnable(cmuClock_EBI, false);

}

/**************************************************************************//**
 * @brief Write data into 16-bit board control register
 * @param addr Address to board control register
 * @param data Data to write into register
 *****************************************************************************/
void DVK_EBI_writeRegister(volatile uint16_t *addr, uint16_t data)
{
  *addr = data;
}

/**************************************************************************//**
 * @brief Write data into 16-bit board control register
 * @param addr Register to read from
 *****************************************************************************/
uint16_t DVK_EBI_readRegister(volatile uint16_t *addr)
{
  return *addr;
}
#endif

/** @} (end group BSP) */
