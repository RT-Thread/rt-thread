/**************************************************************************//**
 * @file
 * @brief SPI implementation of Board Control interface
 *        This implementation use the USART2 SPI interface to control board
 *        control registers. It works
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

/***************************************************************************//**
 * @addtogroup BSP
 * @{
 ******************************************************************************/

#include <stdio.h>
#include "efm32.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "dvk.h"
#include "dvk_bcregisters.h"

#ifdef _EFM32_TINY_FAMILY

/* USART used for SPI access */
#define USART_USED                USART0
#define USART_CLK                 cmuClock_USART0

/* GPIO pins used, please refer to DVK user guide. */
#define PIN_SPIBUS_CONNECT        13
#define PORT_SPIBUS_CONNECT       gpioPortC
#define PIN_SPI_TX                10
#define PORT_SPI_TX               gpioPortE
#define PIN_SPI_RX                11
#define PORT_SPI_RX               gpioPortE
#define PIN_SPI_CLK               12
#define PORT_SPI_CLK              gpioPortE
#define PIN_SPI_CS                13
#define PORT_SPI_CS               gpioPortE

#else

/* USART used for SPI access */
#define USART_USED                USART2
#define USART_CLK                 cmuClock_USART2

/* GPIO pins used, please refer to DVK user guide. */
#define PIN_SPIBUS_CONNECT        13
#define PORT_SPIBUS_CONNECT       gpioPortC
#define PIN_EBIBUS_CONNECT        12
#define PORT_EBIBUS_CONNECT       gpioPortC
#define PIN_SPI_TX                2
#define PORT_SPI_TX               gpioPortC
#define PIN_SPI_RX                3
#define PORT_SPI_RX               gpioPortC
#define PIN_SPI_CLK               4
#define PORT_SPI_CLK              gpioPortC
#define PIN_SPI_CS                5
#define PORT_SPI_CS               gpioPortC

#endif

static volatile uint16_t *lastAddr = NULL;

/**************************************************************************//**
 * @brief  Initializes SPI interface for access to FPGA registers
 *         for board control
 *****************************************************************************/
static void spiInit(void)
{
  USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;

  /* Enable module clocks */
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(USART_CLK, true);

  /* Configure SPI bus connect pins, DOUT set to 0, disable EBI */
  GPIO_PinModeSet(PORT_SPIBUS_CONNECT, PIN_SPIBUS_CONNECT, gpioModePushPull, 0);
  GPIO_PinModeSet(PORT_EBIBUS_CONNECT, PIN_EBIBUS_CONNECT, gpioModePushPull, 1);

  /* Configure SPI pins */
  GPIO_PinModeSet(PORT_SPI_TX, PIN_SPI_TX, gpioModePushPull, 0);
  GPIO_PinModeSet(PORT_SPI_RX, PIN_SPI_RX, gpioModePushPull, 0);
  GPIO_PinModeSet(PORT_SPI_CLK, PIN_SPI_CLK, gpioModePushPull, 0);
  /* Keep CS high to not activate slave */
  GPIO_PinModeSet(PORT_SPI_CS, PIN_SPI_CS, gpioModePushPull, 1);

  /* Configure to use SPI master with manual CS */
  /* For now, configure SPI for worst case 32MHz clock in order to work for all */
  /* configurations. */
  init.refFreq = 32000000;
  init.baudrate = 7000000;
  USART_InitSync(USART_USED, &init);

  /* Enable pins at default location */
  USART_USED->ROUTE = USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_CLKPEN;
}

/**************************************************************************//**
 * @brief  Disables GPIO pins and USART from FPGA register access
 *****************************************************************************/
static void spiDisable(void)
{
  USART_Reset(USART_USED);

  /* Disable LCD_SELECT */
  GPIO_PinModeSet(gpioPortD, 13, gpioModeDisabled, 0);

  /* Disable SPI pins */
  GPIO_PinModeSet(PORT_SPIBUS_CONNECT, 13, gpioModeDisabled, 0);
  GPIO_PinModeSet(PORT_SPIBUS_CONNECT, 12, gpioModeDisabled, 0);
  GPIO_PinModeSet(PORT_SPI_TX, PIN_SPI_TX, gpioModeDisabled, 0);
  GPIO_PinModeSet(PORT_SPI_RX, PIN_SPI_RX, gpioModeDisabled, 0);
  GPIO_PinModeSet(PORT_SPI_CLK, PIN_SPI_CLK, gpioModeDisabled, 0);
  GPIO_PinModeSet(PORT_SPI_CS, PIN_SPI_CS, gpioModeDisabled, 0);

  /* Disable USART clock - we can't disable GPIO or HFPER as we don't know who else
   * might be using it */
  CMU_ClockEnable(USART_CLK, false);
}

/**************************************************************************//**
 * @brief  Perform SPI Transfer
 *****************************************************************************/
static uint16_t spiAccess(uint8_t spiaddr, uint8_t rw, uint16_t spidata)
{
  uint16_t      tmp;

  GPIO_PinOutClear(PORT_SPI_CS, PIN_SPI_CS);

  /* For every byte sent, one is received */

  /* Write SPI address */
  USART_Tx(USART_USED, (spiaddr & 0x3) | rw << 3);
  /* Just ignore data read back */
  USART_Rx(USART_USED);

  /* SPI data LSB */
  USART_Tx(USART_USED, spidata & 0xFF);
  tmp = (uint16_t)USART_Rx(USART_USED);

  /* SPI data MSB */
  USART_Tx(USART_USED, spidata >> 8);
  tmp |= (uint16_t)USART_Rx(USART_USED) << 8;

  GPIO_PinOutSet(PORT_SPI_CS, PIN_SPI_CS);

  return tmp;
}

/**************************************************************************//**
 * @brief  Performs SPI write to FPGA register
 * @param spiadr Address of register
 * @param spidata Data to write
 *****************************************************************************/
static void spiWrite(uint8_t spiadr, uint16_t spidata)
{
  spiAccess(spiadr, 0, spidata);
}

/**************************************************************************//**
 * @brief  Performs SPI read from FPGA register
 * @param spiadr Address of register
 * @param spidata Dummy data
 *****************************************************************************/
static uint16_t spiRead(uint8_t spiadr, uint16_t spidata)
{
  return spiAccess(spiadr, 1, spidata);
}

/**************************************************************************//**
 * @brief  Initializes DVK register access
*  @return true on success, false on failure
 *****************************************************************************/
bool DVK_SPI_init(void)
{
  uint16_t spiMagic;

  spiInit();
  /* Read "board control Magic" register to verify SPI is up and running */
  /*  if not FPGA is configured to be in EBI mode  */

  spiMagic = DVK_SPI_readRegister(BC_MAGIC);
  if(spiMagic != BC_MAGIC_VALUE)
  {
    return false;
  }
  else
  {
    return true;
  }
}

/**************************************************************************//**
 * @brief  Disable and free up resources used by SPI board control access
 *****************************************************************************/
void DVK_SPI_disable(void)
{
  spiDisable();
}

/**************************************************************************//**
 * @brief  Perform read from DVK board control register
 * @param  addr Address of register to read from
 *****************************************************************************/
uint16_t DVK_SPI_readRegister(volatile uint16_t *addr)
{
  uint16_t data;

  if (addr != lastAddr)
  {
    spiWrite(0x00, 0xFFFF & ((uint32_t) addr));             /*LSBs of address*/
    spiWrite(0x01, 0xFF & ((uint32_t) addr >> 16));         /*MSBs of address*/
    spiWrite(0x02, (0x0C000000 & (uint32_t) addr) >> 26);   /*Chip select*/
  }
  /* Read twice */
  data     = spiRead(0x03, 0);
  data     = spiRead(0x03, 0);
  lastAddr = addr;
  return data;
}

/**************************************************************************//**
 * @brief  Perform write to DVK board control register
 * @param addr Address of register to write to
 * @param data 16-bit to  write into register
 *****************************************************************************/
void DVK_SPI_writeRegister(volatile uint16_t *addr, uint16_t data)
{
  if (addr != lastAddr)
  {
    spiWrite(0x00, 0xFFFF & ((uint32_t) addr));             /*LSBs of address*/
    spiWrite(0x01, 0xFF & ((uint32_t) addr >> 16));         /*MSBs of address*/
    spiWrite(0x02, (0x0C000000 & (uint32_t) addr) >> 26);   /*Chip select*/
  }
  spiWrite(0x03, data);                                     /*Data*/
  lastAddr = addr;
}

/** @} (end group BSP) */
