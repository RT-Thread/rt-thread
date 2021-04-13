/***************************************************************************//**
 * @file
 * @brief Flash controller (MSC) Peripheral API
 * @author Energy Micro AS
 * @version 3.0.0
 *******************************************************************************
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
#include "em_msc.h"
#if defined (_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
#include "em_cmu.h"
#endif
#include "em_assert.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup MSC
 * @brief Flash controller (MSC) Peripheral API
 * @{
 ******************************************************************************/

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Enables the flash controller for writing.
 * @note
 *   IMPORTANT: This function must be called before flash operations when
 *   AUXHFRCO clock has been changed from default 14MHz band.
 ******************************************************************************/
void MSC_Init(void)
{
#if defined (_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
  uint32_t freq, cycles;
#endif
  /* Enable writing to the MSC */
  MSC->WRITECTRL |= MSC_WRITECTRL_WREN;
  /* Unlock the MSC */
  MSC->LOCK = MSC_UNLOCK_CODE;
  /* Disable writing to the MSC */
  MSC->WRITECTRL &= ~MSC_WRITECTRL_WREN;

#if defined (_EFM32_TINY_FAMILY) || defined(_EFM32_GIANT_FAMILY)
  /* Configure MSC->TIMEBASE according to selected frequency */
  freq = CMU_ClockFreqGet(cmuClock_AUX);

  if( freq > 7000000)
  {
    /* Calculate number of clock cycles for 1us as base period */
    freq = (freq * 11) / 10;
    cycles = (freq / 1000000) + 1;

    /* Configure clock cycles for flash timing */
    MSC->TIMEBASE = (MSC->TIMEBASE & ~(_MSC_TIMEBASE_BASE_MASK|
                                       _MSC_TIMEBASE_PERIOD_MASK))|
                     MSC_TIMEBASE_PERIOD_1US|
                     (cycles << _MSC_TIMEBASE_BASE_SHIFT);
  }
  else
  {
    /* Calculate number of clock cycles for 5us as base period */
    freq = (freq * 5 * 11) / 10;
    cycles = (freq / 1000000) + 1;

    /* Configure clock cycles for flash timing */
    MSC->TIMEBASE = (MSC->TIMEBASE & ~(_MSC_TIMEBASE_BASE_MASK|
                                       _MSC_TIMEBASE_PERIOD_MASK))|
                     MSC_TIMEBASE_PERIOD_5US|
                     (cycles << _MSC_TIMEBASE_BASE_SHIFT);
  }
#endif
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
#if defined( __ICCARM__ )
/* Suppress warnings originating from use of EFM_ASSERT():              */
/* "Call to a non __ramfunc function from within a __ramfunc function"  */
/* "Possible rom access from within a __ramfunc function"               */
#pragma diag_suppress=Ta022
#pragma diag_suppress=Ta023
#endif
msc_Return_TypeDef MSC_ErasePage(uint32_t *startAddress)
{
  int timeOut = MSC_PROGRAM_TIMEOUT;

  /* Address must be aligned to pages */
  EFM_ASSERT((((uint32_t)startAddress) & 0x1FF) == 0);

  /* Enable writing to the MSC */
  MSC->WRITECTRL |= MSC_WRITECTRL_WREN;

  /* Load address */
  MSC->ADDRB    = (uint32_t)startAddress;
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
#if defined( __ICCARM__ )
#pragma diag_default=Ta022
#pragma diag_default=Ta023
#endif

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
#if defined( __ICCARM__ )
/* Suppress warnings originating from use of EFM_ASSERT():              */
/* "Call to a non __ramfunc function from within a __ramfunc function"  */
/* "Possible rom access from within a __ramfunc function"               */
#pragma diag_suppress=Ta022
#pragma diag_suppress=Ta023
#endif
msc_Return_TypeDef MSC_WriteWord(uint32_t *address, void const *data, int numBytes)
{
  int timeOut;
  int wordCount;
  int numWords;

  /* Check alignment (Must be aligned to words) */
  EFM_ASSERT(((uint32_t) address & 0x3) == 0);

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
    /* Due to the timing of this function, the MSC should already by ready */
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
    MSC->WDATA = *(((uint32_t *)data) + wordCount);

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
#if defined( __ICCARM__ )
#pragma diag_default=Ta022
#pragma diag_default=Ta023
#endif


#if defined(_EFM32_GIANT_FAMILY)
/***************************************************************************//**
 * @brief
 *   Erase entire flash in one operation
 * @note
 *   This command will erase the entire contents of the device.
 *   Use with care, both a debug session and all contents of the flash will be
 *   lost. The lock bit, MLW will prevent this operation from executing and
 *   might prevent successful mass erase.
 ******************************************************************************/
#ifdef __CC_ARM  /* MDK-ARM compiler */
#pragma arm section code="ram_code"
#endif /* __CC_ARM */
msc_Return_TypeDef MSC_MassErase(void)
{
  /* Enable writing to the MSC */
  MSC->WRITECTRL |= MSC_WRITECTRL_WREN;

  /* Unlock device mass erase */
  MSC->MASSLOCK = MSC_MASSLOCK_LOCKKEY_UNLOCK;

  /* Erase first 512K block */
  MSC->WRITECMD = MSC_WRITECMD_ERASEMAIN0;

  /* Waiting for erase to complete */
  while ((MSC->STATUS & MSC_STATUS_BUSY)){}

#if FLASH_SIZE >= (512*1024)
  /* Erase second 512K block */
  MSC->WRITECMD = MSC_WRITECMD_ERASEMAIN1;

  /* Waiting for erase to complete */
  while ((MSC->STATUS & MSC_STATUS_BUSY)){}
#endif

  /* Restore mass erase lock */
  MSC->MASSLOCK = MSC_MASSLOCK_LOCKKEY_LOCK;

  /* This will only successfully return if calling function is also in SRAM */
  return mscReturnOk;
}
#endif

/** @} (end addtogroup MSC) */
/** @} (end addtogroup EM_Library) */
