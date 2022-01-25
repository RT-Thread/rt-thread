/**
 * @file
 * @brief      Flash Controler driver.
 * @details    This driver can be used to operate on the embedded flash memory.
 */

/* ****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2019-06-05 16:53:29 -0500 (Wed, 05 Jun 2019) $
 * $Revision: 43696 $
 *
 *************************************************************************** */

#ifndef _FLC_H_
#define _FLC_H_

/* **** Includes **** */
#include "flc_regs.h"
#include "mxc_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup flc Flash Controller
 * @ingroup periphlibs
 * @{
 */

/***** Definitions *****/

/// Bit mask that can be used to find the starting address of a page in flash
#define MXC_FLASH_PAGE_MASK         ~(MXC_FLASH_PAGE_SIZE - 1)

/// Calculate the address of a page in flash from the page number
#define MXC_FLASH_PAGE_ADDR(page)   (MXC_FLASH_MEM_BASE + ((unsigned long)page * MXC_FLASH_PAGE_SIZE))

/***** Function Prototypes *****/

/**
 * @brief      Initializes the flash controller for erase/write operations
 * @param      sys_cfg      Reserved for future use.  Use NULL as this parameter's value.  
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if unsuccessful.
 */
int FLC_Init(const sys_cfg_flc_t *sys_cfg);
  
/**
 * @brief      Checks if Flash controller is busy.
 * @details    Reading or executing from flash is not possible if flash is busy
 *             with an erase or write operation.
 * @return     If non-zero, flash operation is in progress
 */
int FLC_Busy(void);
  
/**
 * @brief      Erases the entire flash array.
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if unsuccessful.
 */
int FLC_MassErase(void);

/**
 * @brief      Erases the page of flash at the specified address.
 * @param      address  Any address within the page to erase.
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if unsuccessful.
 */
int FLC_PageErase(uint32_t address);

/**
 * @brief      Page erase from start to end address.
 * @note       All data within the selected pages will be erased.
 * @param      start  Any address within the first page to erase.
 * @param      end    Any address within the last page to erase.
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if unsuccessful.
 */
int FLC_Erase(uint32_t start, uint32_t end);

/**
 * @brief      Erase from start to end address.  Restoring any flash page contents outside the given range.
 * @param      start    Starting address to erase, inclusive.
 * @param      end      Ending address to erase, exclusive.
 * @param      buffer   Data buffer to restore data in beginning and ending pages.
 * @param      length   Length of given buffer.
 * 
 * @note       Buffer should be appropriate size to store all of the data remaining in the 
 * first and last pages. length should be greater than or equal to 
 * (start % MXC_FLASH_PAGE_SIZE) and ((MXC_FLASH_PAGE_SIZE - (end % MXC_FLASH_PAGE_SIZE)) % MXC_FLASH_PAGE_SIZE).
 * 
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if unsuccessful.
 */
int FLC_BufferErase(uint32_t start, uint32_t end, uint8_t *buffer, unsigned length);

/**
 * @brief      Writes the specified 32-bit value to flash.
 * @param      address  32-bit aligned address in flash to write.
 * @param      data     value to be written to flash.
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if
 *             unsuccessful.
 */
int FLC_Write32(uint32_t address, uint32_t data);

/**
 * @brief      Writes the specified 128-bits of data to flash.
 * @param      address  128-bit aligned address in flash to write.
 * @param      data     pointer to data to be written to flash.
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if
 *             unsuccessful.
 */
int FLC_Write128(uint32_t address, uint32_t *data);

/**
 * @brief      Writes data to flash.
 * @param      address  Address in flash to start writing from.
 * @param      length   Number of bytes to be written.
 * @param      buffer   Pointer to data to be written to flash.
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if
 *             unsuccessful.
 */
int FLC_Write(uint32_t address, uint32_t length, uint8_t *buffer);

/**
 * @brief      Enable flash interrupts
 * @param      mask   Interrupts to enable
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if
 *             unsuccessful.
 */
int FLC_EnableInt(uint32_t mask);

/**
 * @brief      Disable flash interrupts
 * @param      mask   Interrupts to disable
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if
 *             unsuccessful.
 */
int FLC_DisableInt(uint32_t mask);

/**
 * @brief      Retrieve flash interrupt flags
 * @return     Mask of active flags.
 */
int FLC_GetFlags(void);

/**
 * @brief      Clear flash interrupt flags
 * @note       Provide the bit position to clear, even if the flag is write-0-to-clear
 * @param      mask Mask of flags to clear
 * @return     #E_NO_ERROR if successful, @ref MXC_Error_Codes "error" if
 *             unsuccessful.
 */
int FLC_ClearFlags(uint32_t mask);

/**
 * @brief      Unlock info block
 *
 * @return     #E_NO_ERROR If function is successful.
 */
int FLC_UnlockInfoBlock(void);

/**
 * @brief      Lock info block
 *
 * @return     #E_NO_ERROR If function is successful.
 */
int FLC_LockInfoBlock(void);
/**@} end of group flc */

#ifdef __cplusplus
}
#endif

#endif /* _FLC_H_ */
