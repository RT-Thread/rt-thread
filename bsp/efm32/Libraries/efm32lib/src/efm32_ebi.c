/***************************************************************************//**
 * @file
 * @brief External Bus Interface (EBI) peripheral API for EFM32
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
#include "efm32_ebi.h"
#if defined(EBI_COUNT) && (EBI_COUNT > 0)
#include "efm32_assert.h"
#include "efm32_bitband.h"

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup EBI
 * @brief EBI External Bus Interface Peripheral API
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Configure and enable External Bus Interface
 *
 * @param[in] ebiInit
 *   EBI configuration structure
 *
 * @note
 *   GPIO lines must be configured as PUSH_PULL for correct operation
 *   GPIO and EBI clocks must be enabled in the CMU
 ******************************************************************************/
void EBI_Init(const EBI_Init_TypeDef *ebiInit)
{
  uint32_t ctrl = 0x00000000UL;

  /* Set polarity of address ready */
  EBI_PolaritySet(ebiLineARDY, ebiInit->ardyPolarity);
  /* Set polarity of address latch enable */
  EBI_PolaritySet(ebiLineALE, ebiInit->alePolarity);
  /* Set polarity of write enable */
  EBI_PolaritySet(ebiLineWE, ebiInit->wePolarity);
  /* Set polarity of read enable */
  EBI_PolaritySet(ebiLineRE, ebiInit->rePolarity);
  /* Set polarity of chip select lines */
  EBI_PolaritySet(ebiLineCS, ebiInit->csPolarity);

  /* Configure EBI mode */
  switch (ebiInit->mode)
  {
  case ebiModeD8A8:
    ctrl |= EBI_CTRL_MODE_D8A8;
    /* Make sure Address Latch is disabled */
    EBI->ROUTE &= ~(_EBI_ROUTE_ALEPEN_MASK);
    break;
  case ebiModeD16A16ALE:
    ctrl |= EBI_CTRL_MODE_D16A16ALE;
    /* Addres Latch Enable */
    EBI->ROUTE |= EBI_ROUTE_ALEPEN;
    break;
  case ebiModeD8A24ALE:
    ctrl |= EBI_CTRL_MODE_D8A24ALE;
    /* Addres Latch Enable */
    EBI->ROUTE |= EBI_ROUTE_ALEPEN;
    break;
  default:
    break;
  }
  /* Configure use of adress ready */
  if (ebiInit->ardyEnable)
  {
    ctrl |= (1 << _EBI_CTRL_ARDYEN_SHIFT);
  }
  /* Configure timeout disable, when address ready is enabled */
  if (ebiInit->ardyDisableTimeout)
  {
    ctrl |= (1 << _EBI_CTRL_ARDYTODIS_SHIFT);
  }
  EBI->CTRL = ctrl;

  /* Configure timing */
  EBI_ReadTimingSet(ebiInit->readSetupCycles,
                    ebiInit->readStrobeCycles,
                    ebiInit->readHoldCycles);
  EBI_WriteTimingSet(ebiInit->writeSetupCycles,
                     ebiInit->writeStrobeCycles,
                     ebiInit->writeHoldCycles);
  EBI_AddressTimingSet(ebiInit->addrSetupCycles,
                       ebiInit->addrHoldCycles);

  /* Enable chip select lines */
  EBI_ChipSelectEnable(ebiInit->csLines, true);
  /* Enable EBI pins ADxx, WEn, REn */
  EBI->ROUTE |= EBI_ROUTE_EBIPEN;

  /* Enable banks */
  if (ebiInit->enable)
  {
    EBI_BankEnable(ebiInit->banks, true);
  }
}


/***************************************************************************//**
 * @brief
 *   Disable External Bus Interface
 ******************************************************************************/
void EBI_Disable(void)
{
  /* Disable banks */
  EBI->CTRL = _EBI_ROUTE_RESETVALUE;
  /* Disable pins */
  EBI->ROUTE = _EBI_ROUTE_RESETVALUE;
}


/***************************************************************************//**
 * @brief
 *   Enable or disable EBI Bank
 *
 * @param[in] banks
 *   Banks to reconfigure, mask of EBI_BANK<n> flags
 *
 * @param[in] enable
 *   True to enable, false to disable
 ******************************************************************************/
void EBI_BankEnable(uint32_t banks, bool enable)
{
  if (banks & EBI_BANK0)
  {
    BITBAND_Peripheral(&(EBI->CTRL), _EBI_CTRL_BANK0EN_SHIFT, enable);
  }
  if (banks & EBI_BANK1)
  {
    BITBAND_Peripheral(&(EBI->CTRL), _EBI_CTRL_BANK1EN_SHIFT, enable);
  }
  if (banks & EBI_BANK2)
  {
    BITBAND_Peripheral(&(EBI->CTRL), _EBI_CTRL_BANK2EN_SHIFT, enable);
  }
  if (banks & EBI_BANK3)
  {
    BITBAND_Peripheral(&(EBI->CTRL), _EBI_CTRL_BANK3EN_SHIFT, enable);
  }
}


/***************************************************************************//**
 * @brief
 *   Return base address of EBI bank
 *
 * @param[in] bank
 *   Banks to reconfigure, mask of EBI_BANK<n> flags
 *
 * @return
 *   Absolute address of bank
 ******************************************************************************/
uint32_t EBI_BankAddress(uint32_t bank)
{
  switch (bank)
  {
  case EBI_BANK0:
    return(EBI_MEM_BASE);

  case EBI_BANK1:
    return(EBI_MEM_BASE + 0x04000000UL);

  case EBI_BANK2:
    return(EBI_MEM_BASE + 0x08000000UL);

  case EBI_BANK3:
    return(EBI_MEM_BASE + 0x0C000000UL);

  default:
    EFM_ASSERT(0);
    break;
  }
  return 0;
}


/***************************************************************************//**
 * @brief
 *   Enable or disable EBI Chip Select
 *
 * @param[in] cs
 *   ChipSelect lines to reconfigure, mask of EBI_CS<n> flags
 *
 * @param[in] enable
 *   True to enable, false to disable
 ******************************************************************************/
void EBI_ChipSelectEnable(uint32_t cs, bool enable)
{
  if (cs & EBI_CS0)
  {
    BITBAND_Peripheral(&(EBI->ROUTE), _EBI_ROUTE_CS0PEN_SHIFT, enable);
  }
  if (cs & EBI_CS1)
  {
    BITBAND_Peripheral(&(EBI->ROUTE), _EBI_ROUTE_CS1PEN_SHIFT, enable);
  }
  if (cs & EBI_CS2)
  {
    BITBAND_Peripheral(&(EBI->ROUTE), _EBI_ROUTE_CS2PEN_SHIFT, enable);
  }
  if (cs & EBI_CS3)
  {
    BITBAND_Peripheral(&(EBI->ROUTE), _EBI_ROUTE_CS3PEN_SHIFT, enable);
  }
}


/***************************************************************************//**
 * @brief
 *   Configure EBI pin polarity
 *
 * @param[in] line
 *   Which pin/line to configure
 *
 * @param[in] polarity
 *   Active high, or active low
 ******************************************************************************/
void EBI_PolaritySet(EBI_Line_TypeDef line, EBI_Polarity_TypeDef polarity)
{
  switch (line)
  {
  case ebiLineARDY:
    EBI->POLARITY = (EBI->POLARITY & ~(_EBI_POLARITY_ARDYPOL_MASK))
                    | ((uint32_t) polarity << _EBI_POLARITY_ARDYPOL_SHIFT);
    break;
  case ebiLineALE:
    EBI->POLARITY = (EBI->POLARITY & ~(_EBI_POLARITY_ALEPOL_MASK))
                    | ((uint32_t) polarity << _EBI_POLARITY_ALEPOL_SHIFT);
    break;
  case ebiLineWE:
    EBI->POLARITY = (EBI->POLARITY & ~(_EBI_POLARITY_WEPOL_MASK))
                    | ((uint32_t) polarity << _EBI_POLARITY_WEPOL_SHIFT);
    break;
  case ebiLineRE:
    EBI->POLARITY = (EBI->POLARITY & ~(_EBI_POLARITY_REPOL_MASK))
                    | ((uint32_t) polarity << _EBI_POLARITY_REPOL_SHIFT);
    break;
  case ebiLineCS:
    EBI->POLARITY = (EBI->POLARITY & ~(_EBI_POLARITY_CSPOL_MASK))
                    | ((uint32_t) polarity << _EBI_POLARITY_CSPOL_SHIFT);
    break;
  default:
    break;
  }
}


/***************************************************************************//**
 * @brief
 *   Configure timing values of read bus accesses
 *
 * @param[in] setupCycles
 *   Number of clock cycles for address setup before REn is asserted
 *
 * @param[in] strobeCycles
 *   The number of cycles the REn is held active. After the specified number of
 *   cycles, data is read. If set to 0, 1 cycle is inserted by HW
 *
 * @param[in] holdCycles
 *   The number of cycles CSn is held active after the REn is dessarted
 ******************************************************************************/
void EBI_ReadTimingSet(int setupCycles, int strobeCycles, int holdCycles)
{
  uint32_t readTiming;

  /* Check that timings are within limits */
  EFM_ASSERT(setupCycles < 4);
  EFM_ASSERT(strobeCycles < 16);
  EFM_ASSERT(holdCycles < 4);

  /* Configure timing values */
  readTiming = (setupCycles << _EBI_RDTIMING_RDSETUP_SHIFT) |
               (strobeCycles << _EBI_RDTIMING_RDSTRB_SHIFT) |
               (holdCycles << _EBI_RDTIMING_RDHOLD_SHIFT);

  EBI->RDTIMING = (EBI->RDTIMING &
                   ~(_EBI_RDTIMING_RDSETUP_MASK |
                     _EBI_RDTIMING_RDSTRB_MASK |
                     _EBI_RDTIMING_RDHOLD_MASK)) | readTiming;
}


/***************************************************************************//**
 * @brief
 *   Configure timing values of write bus accesses
 *
 * @param[in] setupCycles
 *   Number of clock cycles for address setup before WEn is asserted
 *
 * @param[in] strobeCycles
 *   Number of cycles WEn is held active. If set to 0, 1 cycle is inserted by HW
 *
 * @param[in] holdCycles
 *   Number of cycles CSn is held active after the WEn is deasserted
 ******************************************************************************/
void EBI_WriteTimingSet(int setupCycles, int strobeCycles, int holdCycles)
{
  uint32_t writeTiming;

  /* Check that timings are within limits */
  EFM_ASSERT(setupCycles < 4);
  EFM_ASSERT(strobeCycles < 16);
  EFM_ASSERT(holdCycles < 4);

  /* Configure timing values */
  writeTiming = (setupCycles << _EBI_WRTIMING_WRSETUP_SHIFT) |
                (strobeCycles << _EBI_WRTIMING_WRSTRB_SHIFT) |
                (holdCycles << _EBI_WRTIMING_WRHOLD_SHIFT);

  EBI->WRTIMING = (EBI->WRTIMING &
                   ~(_EBI_WRTIMING_WRSETUP_MASK |
                     _EBI_WRTIMING_WRSTRB_MASK |
                     _EBI_WRTIMING_WRHOLD_MASK)) | writeTiming;
}


/***************************************************************************//**
 * @brief
 *   Configure timing values of address latch bus accesses
 *
 * @param[in] setupCycles
 *   Sets the number of cycles the address is held after ALE is asserted
 *
 * @param[in] holdCycles
 *   Sets the number of cycles the address is driven onto the ADDRDAT bus before
 *   ALE is asserted. If set 0, 1 cycle is inserted by HW
 ******************************************************************************/
void EBI_AddressTimingSet(int setupCycles, int holdCycles)
{
  uint32_t addressLatchTiming;

  /* Check that timing values are within limits */
  EFM_ASSERT(setupCycles < 4);
  EFM_ASSERT(holdCycles < 4);

  /* Configure address latch timing values */
  addressLatchTiming = (setupCycles << _EBI_ADDRTIMING_ADDRSETUP_SHIFT) |
                       (holdCycles << _EBI_ADDRTIMING_ADDRHOLD_SHIFT);

  EBI->ADDRTIMING = (EBI->ADDRTIMING &
                     ~(_EBI_ADDRTIMING_ADDRSETUP_MASK |
                       _EBI_ADDRTIMING_ADDRHOLD_MASK)) | addressLatchTiming;
}

/** @} (end addtogroup EBI) */
/** @} (end addtogroup EFM32_Library) */

#endif /* defined(EBI_COUNT) && (EBI_COUNT > 0) */
