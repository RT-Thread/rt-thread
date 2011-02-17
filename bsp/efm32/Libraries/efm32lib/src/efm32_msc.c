/***************************************************************************//**
 * @file
 * @brief On-board Flash controller module peripheral API for EFM32
 *   devices.
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
#include "efm32_msc.h"
#include "efm32_assert.h"

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup MSC
 * @brief EFM32 Flash controllre utilities.
 * @{
 ******************************************************************************/

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Enables the flash controller for writing.
 ******************************************************************************/
void MSC_Init(void)
{
  /* Enable writing to the MSC */
  MSC->WRITECTRL |= MSC_WRITECTRL_WREN;
  /* Unlock the MSC */
  MSC->LOCK = MSC_UNLOCK_CODE;
  /* Disable writing to the MSC */
  MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
}

/***************************************************************************//**
 * @brief
 *   Disables the flash controller for writing.
 ******************************************************************************/
void MSC_Deinit(void)
{
  /* Enable writing to the MSC */
  MSC->WRITECTRL |= MSC_WRITECTRL_WREN;
  /* Lock the MSC */
  MSC->LOCK = 0;
  /* Disable writing to the MSC */
  MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
}

/***************************************************************************//**
 * @brief
 *   Erases a page in flash memory.
 * @note
 *   This function MUST be executed from RAM. Failure to execute this portion
 *   of the code in RAM will result in a hardfault. For IAR, Rowley and
 *   Codesourcery this will be achieved automatically. For Keil uVision 4 you
 *   must define a section called "ram_code" and place this manually in your
 *   project's scatter file.
 * @param[in] startAddress
 *   Pointer to the flash page to erase. Must be aligned to beginning of page
 *   boundary.
 * @return
 *   Returns the status of erase operation, #msc_Return_TypeDef
 * @verbatim
 *   flashReturnOk - Operation completed successfully.
 *   flashReturnInvalidAddr - Operation tried to erase a non-flash area.
 *   flashReturnLocked - Operation tried to erase a locked area of the flash.
 *   flashReturnTimeOut - Operation timed out waiting for flash operation
 *       to complete.
 * @endverbatim
 ******************************************************************************/
#ifdef __CC_ARM  /* MDK-ARM compiler */
#pragma arm section code="ram_code"
#endif /* __CC_ARM */
msc_Return_TypeDef MSC_ErasePage(uint32_t *startAddress)
{
  int timeOut = MSC_PROGRAM_TIMEOUT;

  /* Address must be aligned to pages */
  EFM_ASSERT((((uint32_t) startAddress) & 0x1FF) == 0);

  /* Enable writing to the MSC */
  MSC->WRITECTRL |= MSC_WRITECTRL_WREN;

  /* Load address */
  MSC->ADDRB    = (uint32_t) startAddress;
  MSC->WRITECMD = MSC_WRITECMD_LADDRIM;

  /* Check for invalid address */
  if (MSC->STATUS & MSC_STATUS_INVADDR)
  {
    /* Disable writing to the MSC */
    MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
    return mscReturnInvalidAddr;
  }

  /* Check for write protected page */
  if (MSC->STATUS & MSC_STATUS_LOCKED)
  {
    /* Disable writing to the MSC */
    MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
    return mscReturnLocked;
  }

  /* Send erase page command */
  MSC->WRITECMD = MSC_WRITECMD_ERASEPAGE;

  /* Wait for the erase to complete */
  while ((MSC->STATUS & MSC_STATUS_BUSY) && (timeOut != 0))
  {
    timeOut--;
  }

  if (timeOut == 0)
  {
    /* Disable writing to the MSC */
    MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
    return mscReturnTimeOut;
  }

  /* Disable writing to the MSC */
  MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
  return mscReturnOk;
}

/***************************************************************************//**
 * @brief
 *   Writes a single word to flash memory. Data to write must be aligned to
 *   words and contain a number of bytes that is divisable by four.
 * @note
 *   The flash must be erased prior to writing a new word.
 *   This function must be run from RAM. Failure to execute this portion
 *   of the code in RAM will result in a hardfault. For IAR, Rowley and
 *   Codesourcery this will be achieved automatically. For Keil uVision 4 you
 *   must define a section called "ram_code" and place this manually in your
 *   project's scatter file.
 *
 * @param[in] address
 *   Pointer to the flash word to write to. Must be aligned to words.
 * @param[in] data
 *   Data to write to flash.
 * @param[in] numBytes
 *   Number of bytes to write from flash. NB: Must be divisable by four.
 * @return
 *   Returns the status of the write operation, #msc_Return_TypeDef
 * @verbatim
 *   flashReturnOk - Operation completed successfully.
 *   flashReturnInvalidAddr - Operation tried to erase a non-flash area.
 *   flashReturnLocked - Operation tried to erase a locked area of the flash.
 *   flashReturnTimeOut - Operation timed out waiting for flash operation
 *       to complete.
 * @endverbatim
 ******************************************************************************/
#ifdef __CC_ARM  /* MDK-ARM compiler */
#pragma arm section code="ram_code"
#endif /* __CC_ARM */
msc_Return_TypeDef MSC_WriteWord(uint32_t *address, void *data, int numBytes)
{
  int timeOut;
  int wordCount;
  int numWords;

  /* Check alignment (Must be aligned to words) */
  EFM_ASSERT(((uint32_t)address & 0x3) == 0);

  /* Check number of bytes. Must be divisable by four */
  EFM_ASSERT((numBytes & 0x3) == 0);

  /* Enable writing to the MSC */
  MSC->WRITECTRL |= MSC_WRITECTRL_WREN;

  /* Convert bytes to words */
  numWords = numBytes >> 2;

  for (wordCount = 0; wordCount < numWords; wordCount++)
  {
    /* Load address */
    MSC->ADDRB    = (uint32_t)(address + wordCount);
    MSC->WRITECMD = MSC_WRITECMD_LADDRIM;

    /* Check for invalid address */
    if (MSC->STATUS & MSC_STATUS_INVADDR)
    {
      /* Disable writing to the MSC */
      MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
      return mscReturnInvalidAddr;
    }

    /* Check for write protected page */
    if (MSC->STATUS & MSC_STATUS_LOCKED)
    {
      /* Disable writing to the MSC */
      MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
      return mscReturnLocked;
    }

    /* Wait for the MSC to be ready for a new data word */
    /* Due to the timing of this function, the MSC should allready by ready */
    timeOut = MSC_PROGRAM_TIMEOUT;
    while (((MSC->STATUS & MSC_STATUS_WDATAREADY) == 0) && (timeOut != 0))
    {
      timeOut--;
    }

    /* Check for timeout */
    if (timeOut == 0)
    {
      /* Disable writing to the MSC */
      MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
      return mscReturnTimeOut;
    }

    /* Load data into write data register */
    MSC->WDATA = *(((uint32_t *) data) + wordCount);

    /* Trigger write once */
    MSC->WRITECMD = MSC_WRITECMD_WRITEONCE;

    /* Wait for the write to complete */
    timeOut = MSC_PROGRAM_TIMEOUT;
    while ((MSC->STATUS & MSC_STATUS_BUSY) && (timeOut != 0))
    {
      timeOut--;
    }

    /* Check for timeout */
    if (timeOut == 0)
    {
      /* Disable writing to the MSC */
      MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
      return mscReturnTimeOut;
    }
  }
  /* Disable writing to the MSC */
  MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;
  return mscReturnOk;
}

/** @} (end addtogroup MSC) */
/** @} (end addtogroup EFM32_Library) */
