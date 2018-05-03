/**************************************************************************//**
 * @file
 * @brief EFM32GG_DK3750 board support package EBI API implementation
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
#include "em_ebi.h"
#include "em_cmu.h"
#include "dvk.h"
#include "dvk_bcregisters.h"

#if defined(EBI_PRESENT)
/**************************************************************************//**
 * @brief Configure EFM32GG_DK3750 EBI (external bus interface) access for
 *    - 0x80000000: Board Control registers (Xilinx Spartan FPGA)
 *    - 0x84000000: TFT memory mapped drive (URT/SSD2119 controller)
 *    - 0x88000000: PSRAM external memory (Micron MT45W2MW16PGA-70 IT)
 *    - 0x8c000000: NOR flash (Spansion flash S29GLxxx_FBGA)
 * @return true if successful, false if board controller access failed
 *****************************************************************************/
bool DVK_EBI_init(void)
{
  EBI_Init_TypeDef ebiConfig = EBI_INIT_DEFAULT;

  /* Enable clocks */
  CMU_ClockEnable(cmuClock_EBI, true);
  CMU_ClockEnable(cmuClock_GPIO, true);

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

  /* EBI A16-A22 */
  GPIO_PinModeSet(gpioPortB, 0, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortB, 1, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortB, 2, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortB, 3, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortB, 4, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortB, 5, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortB, 6, gpioModePushPull, 0);

  /* EBI CS0-CS3 */
  GPIO_PinModeSet(gpioPortD, 9, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortD, 10, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortD, 11, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortD, 12, gpioModePushPull, 1);

  /* EBI AD0..7 */
  GPIO_PinModeSet(gpioPortE, 8, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 9, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 10, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 11, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 12, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 13, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 14, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 15, gpioModePushPull, 0);

  /* EBI ARDY/WEN/REN/ALE */
  /* ARDY on Port F Pin 2 is not used                 */
  /* GPIO_PinModeSet(gpioPortF, 2, gpioModeInput, 0); */
  GPIO_PinModeSet(gpioPortF, 8, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortF, 9, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, 11, gpioModePushPull, 0);

  /* EBI Byte Lane 0 support BL0/BL1 */
  GPIO_PinModeSet(gpioPortF, 6, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortF, 7, gpioModePushPull, 0);

  /* ---------------------------------------------------- */
  /* External 4MB PSRAM, Bank 2, Base Address 0x88000000  */
  /* Micron MT45W2MW16PGA-70 IT, 32Mb Cellular RAM        */
  /* ---------------------------------------------------- */
  ebiConfig.banks        = EBI_BANK2;
  ebiConfig.csLines      = EBI_CS2;
  ebiConfig.mode         = ebiModeD16A16ALE;
  ebiConfig.alePolarity  = ebiActiveHigh;
  ebiConfig.blEnable     = true;
  ebiConfig.noIdle       = true;
  ebiConfig.ardyEnable   = false;
  ebiConfig.addrHalfALE  = true;
  ebiConfig.readPrefetch = true;
  ebiConfig.aLow         = ebiALowA16;
  ebiConfig.aHigh        = ebiAHighA23;
  ebiConfig.location     = ebiLocation1;

  /* Address Setup and hold time */
  ebiConfig.addrHoldCycles  = 0;
  ebiConfig.addrSetupCycles = 0;

  /* Read cycle times */
  ebiConfig.readStrobeCycles = 4;
  ebiConfig.readHoldCycles   = 0;
  ebiConfig.readSetupCycles  = 0;

  /* Write cycle times */
  ebiConfig.writeStrobeCycles = 2;
  ebiConfig.writeHoldCycles   = 0;
  ebiConfig.writeSetupCycles  = 0;

  /* Configure EBI bank 2 - external PSRAM */
  EBI_Init(&ebiConfig);

  /* --------------------------------------------------------- */
  /* Board Control Registers, Bank 0, Base Address 0x80000000  */
  /* FPGA Xilinx Spartan XC6SLX9 CSG324                        */
  /* --------------------------------------------------------- */
  ebiConfig.banks       = EBI_BANK0;
  ebiConfig.csLines     = EBI_CS0;
  ebiConfig.mode        = ebiModeD16A16ALE;;
  ebiConfig.alePolarity = ebiActiveHigh;
  /* keep blEnable */
  ebiConfig.blEnable     = false;
  ebiConfig.addrHalfALE  = true;
  ebiConfig.readPrefetch = false;
  ebiConfig.noIdle       = true;

  /* keep alow/ahigh configuration */
  /* ebiConfig.aLow = ebiALowA0; - needs to be set for PSRAM */
  /* ebiConfig.aHigh = ebiAHighA0; - needs to be set for PSRAM */

  /* Address Setup and hold time */
  ebiConfig.addrHoldCycles  = 3;
  ebiConfig.addrSetupCycles = 3;

  /* Read cycle times */
  ebiConfig.readStrobeCycles = 7;
  ebiConfig.readHoldCycles   = 3;
  ebiConfig.readSetupCycles  = 3;

  /* Write cycle times */
  ebiConfig.writeStrobeCycles = 7;
  ebiConfig.writeHoldCycles   = 3;
  ebiConfig.writeSetupCycles  = 3;

  /* Configure EBI bank 0 */
  EBI_Init(&ebiConfig);

  /* ----------------------------------------------------- */
  /* TFT-LCD Registers, Bank1, Base Address 0x84000000     */
  /* URT USMH_8252MD_320X240_RGB                           */
  /* Solomon Systech SSD 2119                              */
  /* ----------------------------------------------------- */
  ebiConfig.banks   = EBI_BANK1;
  ebiConfig.csLines = EBI_CS1;

  /* Address Setup and hold time */
  ebiConfig.addrHoldCycles  = 1;
  ebiConfig.addrSetupCycles = 1;

  /* Read cycle times */
  ebiConfig.readStrobeCycles = 7;
  ebiConfig.readHoldCycles   = 3;
  ebiConfig.readSetupCycles  = 3;

  /* Write cycle times */
  ebiConfig.writeStrobeCycles = 2;
  ebiConfig.writeHoldCycles   = 1;
  ebiConfig.writeSetupCycles  = 1;

  /* Configure EBI bank 1 */
  EBI_Init(&ebiConfig);

  /* ----------------------------------------- */
  /* NOR Flash, Bank3, Base Address 0x8c000000 */
  /* Spansion flash S29GLxxx_FBGA              */
  /* ----------------------------------------- */
  ebiConfig.banks       = EBI_BANK3;
  ebiConfig.csLines     = EBI_CS3;
  ebiConfig.mode        = ebiModeD16A16ALE;;
  ebiConfig.alePolarity = ebiActiveHigh;

  /* keep blEnable */
  ebiConfig.blEnable     = true;
  ebiConfig.addrHalfALE  = true;
  ebiConfig.readPrefetch = false;
  ebiConfig.noIdle       = true;

  /* Address Setup and hold time */
  ebiConfig.addrHoldCycles  = 0;
  ebiConfig.addrSetupCycles = 0;

  /* Read cycle times */
  ebiConfig.readStrobeCycles = 5;
  ebiConfig.readHoldCycles   = 0;
  ebiConfig.readSetupCycles  = 0;

  /* Write cycle times */
  ebiConfig.writeStrobeCycles = 5;
  ebiConfig.writeHoldCycles   = 0;
  ebiConfig.writeSetupCycles  = 0;

  /* Configure EBI bank 3 */
  EBI_Init(&ebiConfig);

  /* Enable extended address range */
  DVK_EBI_extendedAddressRange(true);

  /* Verify connectivity to Board Control registers */
  if (BC_REGISTER->MAGIC != 0xef32)
  {
    return false;
  }
  else
  {
    return true;
  }
}


/**************************************************************************//**
 * @brief Disable EFM32GG_DK3750 EBI board support package functionality
 *****************************************************************************/
void DVK_EBI_disable(void)
{
  /* Configure GPIO pins as push pull */
  /* EBI AD9..15 */
  GPIO_PinModeSet(gpioPortA, 0, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 1, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 2, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 3, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 4, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 5, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortA, 6, gpioModeDisabled, 0);

  /* EBI AD8 */
  GPIO_PinModeSet(gpioPortA, 15, gpioModeDisabled, 0);

  /* EBI A16-A22 */
  GPIO_PinModeSet(gpioPortB, 0, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortB, 1, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortB, 2, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortB, 3, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortB, 4, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortB, 5, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortB, 6, gpioModeDisabled, 0);

  /* EBI CS0-CS3 */
  GPIO_PinModeSet(gpioPortD, 9, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortD, 10, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortD, 11, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortD, 12, gpioModeDisabled, 0);

  /* EBI AD0..7 */
  GPIO_PinModeSet(gpioPortE, 8, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 9, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 10, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 11, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 12, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 13, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 14, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortE, 15, gpioModeDisabled, 0);

  /* EBI ARDY/WEN/REN/ALE */
  /* ARDY on Port F Pin 2 is not used                 */
  /* GPIO_PinModeSet(gpioPortF, 2, gpioModeDisabled, 0); */
  GPIO_PinModeSet(gpioPortF, 8, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortF, 9, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortC, 11, gpioModeDisabled, 0);

  /* EBI Byte Lane 0 support BL0/BL1 */
  GPIO_PinModeSet(gpioPortF, 6, gpioModeDisabled, 0);
  GPIO_PinModeSet(gpioPortF, 7, gpioModeDisabled, 0);

  /* Reset EBI configuration */
  EBI_Disable();
  /* Turn off EBI clock */
  CMU_ClockEnable(cmuClock_EBI, false);
}


/**************************************************************************//**
 * @brief Configure EBI extended Address Range
 *
 * @param[in] enable
 *   Controls extended address range mode
 *****************************************************************************/
void DVK_EBI_extendedAddressRange(bool enable)
{
  if (enable)
  {
    BC_REGISTER->EBI_CTRL = 0x0001;
  }
  else
  {
    BC_REGISTER->EBI_CTRL = 0x0000;
  }
}

#endif

/** @} (end group BSP) */

