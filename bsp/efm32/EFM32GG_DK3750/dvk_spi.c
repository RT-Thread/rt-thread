/**************************************************************************//**
 * @file
 * @brief EFM32GG_DK3750 board support package SPI API implementation
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

#include "efm32.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_cmu.h"
#include "dvk.h"
#include "dvk_bcregisters.h"

/* USART used for SPI access */
#define USART_USED      USART2 /**< USART used for BC register interface */
#define USART_CLK       cmuClock_USART2 /**< Clock for BC register USART */

/* GPIO pins used, please refer to DVK user guide. */
#define PORT_SPI_TX     gpioPortC /**< SPI transmit GPIO port */
#define PIN_SPI_TX      2         /**< SPI transmit GPIO pin */
#define PORT_SPI_RX     gpioPortC /**< SPI receive GPIO port */
#define PIN_SPI_RX      3         /**< SPI receive GPIO pin */
#define PORT_SPI_CLK    gpioPortC /**< SPI clock port */
#define PIN_SPI_CLK     4         /**< SPI clock pin */
#define PORT_SPI_CS     gpioPortC /**< SPI Chip Select port */
#define PIN_SPI_CS      5         /**< SPI Chip Select pin */

static volatile const uint16_t *lastAddr = 0; /**< Last register accessed */

/**************************************************************************//**
 * @brief  Initializes SPI interface for access to board controller
 *         FPGA registers
 *****************************************************************************/
static void SPI_BC_Init(void)
{
  USART_InitSync_TypeDef bcinit = USART_INITSYNC_DEFAULT;

  /* Enable module clocks */
  CMU_ClockEnable(USART_CLK, true);

  /* Configure SPI pins */
  GPIO_PinModeSet(PORT_SPI_TX, PIN_SPI_TX, gpioModePushPull, 0);
  GPIO_PinModeSet(PORT_SPI_RX, PIN_SPI_RX, gpioModeInput, 0);
  GPIO_PinModeSet(PORT_SPI_CLK, PIN_SPI_CLK, gpioModePushPull, 0);

  /* Keep CS high to not activate slave */
  GPIO_PinModeSet(PORT_SPI_CS, PIN_SPI_CS, gpioModePushPull, 1);

  /* Configure to use SPI master with manual CS */
  /* For now, configure SPI for worst case 48MHz clock in order to work for all */
  /* configurations. */
  bcinit.refFreq  = 48000000;
  bcinit.baudrate = 7000000;

  /* Initialize USART */
  USART_InitSync(USART_USED, &bcinit);

  /* Enable pins at default location */
  USART_USED->ROUTE = USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_CLKPEN;
}


/**************************************************************************//**
 * @brief  Disables GPIO pins and USART from FPGA register access
 *****************************************************************************/
static void SPI_BC_Disable(void)
{
  /* Restore and disable USART */
  USART_Reset(USART_USED);

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
 * @param addr Register offset, starting at 0
 * @param rw 0 on write, 1 on read accesses
 * @param data 16-bit data to write into register/dummy data for reads
 * @return 16-bit data received from SPI access
 *****************************************************************************/
static uint16_t SPI_BC_Access(uint8_t addr, uint8_t rw, uint16_t data)
{
  uint16_t tmp;

  /* Enable CS */
  GPIO_PinOutClear(PORT_SPI_CS, PIN_SPI_CS);

  /* Write SPI address MSB */
  USART_Tx(USART_USED, (addr & 0x3) | rw << 3);
  /* Just ignore data read back */
  USART_Rx(USART_USED);

  /* Write SPI address  LSB */
  USART_Tx(USART_USED, data & 0xFF);

  tmp = (uint16_t) USART_Rx(USART_USED);

  /* SPI data MSB */
  USART_Tx(USART_USED, data >> 8);
  tmp |= (uint16_t) USART_Rx(USART_USED) << 8;

  /* Disable CS */
  GPIO_PinOutSet(PORT_SPI_CS, PIN_SPI_CS);

  return tmp;
}


/**************************************************************************//**
 * @brief  Performs SPI write to FPGA register
 * @param  addr Address of register
 * @param  data Data to write
 *****************************************************************************/
static void SPI_BC_Write(uint8_t addr, uint16_t data)
{
  SPI_BC_Access(addr, 0, data);
}


/**************************************************************************//**
 * @brief  Performs SPI read from FPGA register
 * @param  addr Address of register
 * @return 16-bit value of board controller register
 *****************************************************************************/
static uint16_t SPI_BC_Read(uint8_t addr)
{
  return SPI_BC_Access(addr, 1, 0);
}


/**************************************************************************//**
 * @brief  Initializes DVK register access
 * @return true on success, false on failure
 *****************************************************************************/
bool DVK_SPI_init(void)
{
  uint16_t bcMagic;

  /* Enable HF and GPIO clocks */
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure SPI mode of operation */
  DVK_busControlMode(DVK_BusControl_SPI);

  SPI_BC_Init();
  /* Read "board control Magic" register to verify SPI is up and running */
  /*  if not FPGA is configured to be in EBI mode  */
  bcMagic = DVK_SPI_readRegister(&BC_REGISTER->MAGIC);
  if (bcMagic != BC_MAGIC_VALUE)
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
  SPI_BC_Disable();
}


/**************************************************************************//**
 * @brief     Perform read from DVK board control register
 * @param[in] addr Address of register to read from
 * @return    Value of board controller register
 *****************************************************************************/
uint16_t DVK_SPI_readRegister(volatile uint16_t *addr)
{
  uint16_t data;

  if (addr != lastAddr)
  {
    SPI_BC_Write(0x00, 0xFFFF & ((uint32_t) addr));             /*LSBs of address*/
    SPI_BC_Write(0x01, 0xFF & ((uint32_t) addr >> 16));         /*MSBs of address*/
    SPI_BC_Write(0x02, (0x0C000000 & (uint32_t) addr) >> 26);   /*Chip select*/
  }
  /* Read twice; when register address has changed we need two SPI transfer
   * to clock out valid data through board controller FIFOs */
  data     = SPI_BC_Read(0x03);
  data     = SPI_BC_Read(0x03);
  lastAddr = addr;
  return data;
}


/**************************************************************************//**
 * @brief Perform write to DVK board control register
 * @param addr Address of register to write to
 * @param data 16-bit to  write into register
 *****************************************************************************/
void DVK_SPI_writeRegister(volatile uint16_t *addr, uint16_t data)
{
  if (addr != lastAddr)
  {
    SPI_BC_Write(0x00, 0xFFFF & ((uint32_t) addr));             /*LSBs of address*/
    SPI_BC_Write(0x01, 0xFF & ((uint32_t) addr >> 16));         /*MSBs of address*/
    SPI_BC_Write(0x02, (0x0C000000 & (uint32_t) addr) >> 26);   /*Chip select*/
  }
  SPI_BC_Write(0x03, data);                                     /*Data*/
  lastAddr = addr;
}

/** @} (end group BSP) */
