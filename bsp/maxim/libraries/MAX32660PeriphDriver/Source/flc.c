/**
 * @file flc.h
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

/* **** Includes **** */
#include <string.h>
#include "mxc_config.h"
#include "mxc_sys.h"
#include "flc.h"
#include "flc_regs.h"


/* **** Definitions **** */

/* **** Globals **** */

/* **** Functions **** */

// *****************************************************************************
#if defined (__ICCARM__)
#pragma section=".flashprog"
#endif
#if defined ( __GNUC__ )
__attribute__ ((section(".flashprog")))
#endif
static int prepare_flc(void)
{
    // Set flash clock divider to generate a 1MHz clock from the APB clock
    MXC_FLC->clkdiv = SystemCoreClock / 1000000;

    /* Check if the flash controller is busy */
    if (FLC_Busy()) {
        return E_BUSY;
    }

    /* Clear stale errors */
    if (MXC_FLC->intr & MXC_F_FLC_INTR_AF) {
        MXC_FLC->intr &= ~MXC_F_FLC_INTR_AF;
    }

    /* Unlock flash */
    MXC_FLC->cn = (MXC_FLC->cn & ~MXC_F_FLC_CN_UNLOCK) | MXC_S_FLC_CN_UNLOCK_UNLOCKED;

    return E_NO_ERROR;
}

// *****************************************************************************
#if defined (__ICCARM__)
// IAR memory section declaration for the in-system flash programming functions to be loaded in RAM.
#pragma section=".flashprog"
#endif
#if defined ( __GNUC__ )
__attribute__ ((section(".flashprog")))
#endif
int FLC_Init(const sys_cfg_flc_t *sys_cfg)
{
  SYS_FLC_Init(sys_cfg);

  return E_NO_ERROR;
}

// *****************************************************************************
#if defined (__ICCARM__)
// IAR memory section declaration for the in-system flash programming functions to be loaded in RAM.
#pragma section=".flashprog"
#endif
#if defined ( __GNUC__ )
__attribute__ ((section(".flashprog")))
#endif
int FLC_Busy(void)
{
    return (MXC_FLC->cn & (MXC_F_FLC_CN_WR | MXC_F_FLC_CN_ME | MXC_F_FLC_CN_PGE));
}

// *****************************************************************************
#if defined (__ICCARM__)
#pragma section=".flashprog"
#endif
#if defined ( __GNUC__ )
__attribute__ ((section(".flashprog")))
#endif
int FLC_MassErase(void)
{
    int err;

    if ((err = prepare_flc()) != E_NO_ERROR)
        return err;

    /* Write mass erase code */
    MXC_FLC->cn = (MXC_FLC->cn & ~MXC_F_FLC_CN_ERASE_CODE) | MXC_S_FLC_CN_ERASE_CODE_ERASEALL;

    /* Issue mass erase command */
    MXC_FLC->cn |= MXC_F_FLC_CN_ME;

    /* Wait until flash operation is complete */
    while (FLC_Busy());
    /* Lock flash */
    MXC_FLC->cn &= ~MXC_F_FLC_CN_UNLOCK;

    /* Check access violations */
    if (MXC_FLC->intr & MXC_F_FLC_INTR_AF) {
        MXC_FLC->intr &= ~MXC_F_FLC_INTR_AF;
        return E_BAD_STATE;
    }

    SYS_Flash_Operation();

    return E_NO_ERROR;
}

// *****************************************************************************
#if defined (__ICCARM__)
#pragma section=".flashprog"
#endif
#if defined ( __GNUC__ )
__attribute__ ((section(".flashprog")))
#endif
int FLC_PageErase(uint32_t address)
{
    int err;

    if ((err = prepare_flc()) != E_NO_ERROR)
        return err;

    // Align address on page boundary
    address = address - (address % MXC_FLASH_PAGE_SIZE);

    /* Write page erase code */
    MXC_FLC->cn = (MXC_FLC->cn & ~MXC_F_FLC_CN_ERASE_CODE) | MXC_S_FLC_CN_ERASE_CODE_ERASEPAGE;
    /* Issue page erase command */
    MXC_FLC->addr = address;
    MXC_FLC->cn |= MXC_F_FLC_CN_PGE;

    /* Wait until flash operation is complete */
    while (FLC_Busy());

    /* Lock flash */
    MXC_FLC->cn &= ~MXC_F_FLC_CN_UNLOCK;

    /* Check access violations */
    if (MXC_FLC->intr & MXC_F_FLC_INTR_AF) {
        MXC_FLC->intr &= ~MXC_F_FLC_INTR_AF;
        return E_BAD_STATE;
    }

    SYS_Flash_Operation();

    return E_NO_ERROR;
}

// *****************************************************************************
#if defined (__ICCARM__)
#pragma section=".flashprog"
#endif
#if defined ( __GNUC__ )
__attribute__ ((section(".flashprog")))
#endif
int FLC_Erase(uint32_t start, uint32_t end)
{
    int retval;
    uint32_t addr;

    // Align start and end on page boundaries
    start = start - (start % MXC_FLASH_PAGE_SIZE);
    end = end - (end % MXC_FLASH_PAGE_SIZE);

    for (addr = start; addr <= end; addr += MXC_FLASH_PAGE_SIZE) {
        retval = FLC_PageErase(addr);
        if (retval != E_NO_ERROR)  {
            return retval;
        }
    }

    return E_NO_ERROR;
}

// *****************************************************************************
#if defined (__ICCARM__)
#pragma section=".flashprog"
#endif
#if defined ( __GNUC__ )
__attribute__ ((section(".flashprog")))
#endif
int FLC_BufferErase(uint32_t start, uint32_t end, uint8_t *buffer, unsigned length)
{
    int retval;
    uint32_t start_align, start_len, end_align, end_len;

    // Align start and end on page boundaries, calculate length of data to buffer
    start_align = start - (start % MXC_FLASH_PAGE_SIZE);
    start_len = (start % MXC_FLASH_PAGE_SIZE);
    end_align = end - (end % MXC_FLASH_PAGE_SIZE);
    end_len = ((MXC_FLASH_PAGE_SIZE - (end % MXC_FLASH_PAGE_SIZE)) % MXC_FLASH_PAGE_SIZE);

    // Make sure the length of buffer is sufficient
    if ((length < start_len) || (length < end_len)) {
        return E_BAD_PARAM;
    }


    // Start and end address are in the same page
    if (start_align == end_align) {
        if (length < (start_len + end_len)) {
            return E_BAD_PARAM;
        }

        // Buffer first page data and last page data, erase and write
        memcpy(buffer, (void*)start_align, start_len);
        memcpy(&buffer[start_len], (void*)end, end_len);
        retval = FLC_PageErase(start_align);
        if (retval != E_NO_ERROR) {
            return retval;
        }

        retval = FLC_Write(start_align, start_len, buffer);
        if (retval != E_NO_ERROR) {
            return retval;
        }
        retval = FLC_Write(end, end_len, &buffer[start_len]);
        if (retval != E_NO_ERROR) {
            return retval;
        }

        return E_NO_ERROR;
    }

    // Buffer, erase, and write the data in the first page
    memcpy(buffer, (void*)start_align, start_len);
    retval = FLC_PageErase(start_align);
    if (retval != E_NO_ERROR) {
        return retval;
    }

    retval = FLC_Write(start_align, start_len, buffer);
    if (retval != E_NO_ERROR) {
        return retval;
    }

    // Buffer, erase, and write the data in the last page
    memcpy(buffer, (void*)end, end_len);
    retval = FLC_PageErase(end_align);
    if (retval != E_NO_ERROR) {
        return retval;
    }

    retval = FLC_Write(end, end_len, buffer);
    if (retval != E_NO_ERROR) {
        return retval;
    }

    // Erase the remaining pages
    if (start_align != end_align) {
        return FLC_Erase((start_align + MXC_FLASH_PAGE_SIZE), (end_align - MXC_FLASH_PAGE_SIZE));
    }

    return E_NO_ERROR;
}

// *****************************************************************************
#if defined (__ICCARM__)
#pragma section=".flashprog"
#endif
#if defined ( __GNUC__ )
__attribute__ ((section(".flashprog")))
#endif
int FLC_Write32(uint32_t address, uint32_t data)
{
    int err;

    // Address checked if it is byte addressable
    if (address & 0x3) {
        return E_BAD_PARAM;
    }

    if ((err = prepare_flc()) != E_NO_ERROR)
        return err;

    // write in 32-bit units
    MXC_FLC->cn |= MXC_F_FLC_CN_WDTH;
    MXC_FLC->cn &= ~MXC_F_FLC_CN_BRST;

    // write the data
    MXC_FLC->addr = address;
    MXC_FLC->data[0] = data;
    MXC_FLC->cn |= MXC_F_FLC_CN_WR;


    /* Wait until flash operation is complete */
    while (FLC_Busy()) {}

    /* Lock flash */
    MXC_FLC->cn &= ~MXC_F_FLC_CN_UNLOCK;

    /* Check access violations */
    if (MXC_FLC->intr & MXC_F_FLC_INTR_AF) {
        MXC_FLC->intr &= ~MXC_F_FLC_INTR_AF;
        return E_BAD_STATE;
    }

    SYS_Flash_Operation();

    return E_NO_ERROR;
}

// *****************************************************************************
#if defined (__ICCARM__)
#pragma section=".flashprog"
#endif
#if defined ( __GNUC__ )
__attribute__ ((section(".flashprog")))
#endif
int FLC_Write128(uint32_t address, uint32_t *data)
{
    int err;

    // Address checked if it is word addressable
    if (address & 0xF) {
        return E_BAD_PARAM;
    }

    if ((err = prepare_flc()) != E_NO_ERROR)
        return err;

    // write 128-bits
    MXC_FLC->cn &= ~MXC_F_FLC_CN_WDTH;

    // write the data
    MXC_FLC->addr = address;
    memcpy((void*)&MXC_FLC->data[0], data, 16);
    MXC_FLC->cn |= MXC_F_FLC_CN_WR;

    /* Wait until flash operation is complete */
    while (FLC_Busy());

    /* Lock flash */
    MXC_FLC->cn &= ~MXC_F_FLC_CN_UNLOCK;

    /* Check access violations */
    if (MXC_FLC->intr & MXC_F_FLC_INTR_AF) {
        MXC_FLC->intr &= ~MXC_F_FLC_INTR_AF;
        return E_BAD_STATE;
    }

    SYS_Flash_Operation();

    return E_NO_ERROR;
}

// *****************************************************************************
#if defined (__ICCARM__)
#pragma section=".flashprog"
#endif
#if defined ( __GNUC__ )
__attribute__ ((section(".flashprog")))
#endif
int FLC_Write(uint32_t address, uint32_t length, uint8_t *buffer)
{
    int err;
    uint32_t bytes_written;
    uint8_t current_data[4];

    if ((err = prepare_flc()) != E_NO_ERROR)
        return err;

    // write in 32-bit units until we are 128-bit aligned
    MXC_FLC->cn &= ~MXC_F_FLC_CN_BRST;
    MXC_FLC->cn |= MXC_F_FLC_CN_WDTH;

    // Align the address and read/write if we have to
    if (address & 0x3) {

        // Figure out how many bytes we have to write to round up the address
        bytes_written = 4 - (address & 0x3);

        // Save the data currently in the flash
        memcpy(current_data, (void*)(address & (~0x3)), 4);

        // Modify current_data to insert the data from buffer
        memcpy(&current_data[4-bytes_written], buffer, bytes_written);

        // Write the modified data
        MXC_FLC->addr = address - (address % 4);
        memcpy((void*)&MXC_FLC->data[0], &current_data, 4);
        MXC_FLC->cn |= MXC_F_FLC_CN_WR;

        /* Wait until flash operation is complete */
        while (FLC_Busy());

        address += bytes_written;
        length -= bytes_written;
        buffer += bytes_written;
    }

    while ( (length >= 4) && ((address & 0xF) != 0) ) {
        MXC_FLC->addr = address;
        memcpy((void*)&MXC_FLC->data[0], buffer, 4);
        MXC_FLC->cn |= MXC_F_FLC_CN_WR;

        /* Wait until flash operation is complete */
        while (FLC_Busy());

        address += 4;
        length -= 4;
        buffer += 4;
    }

    if (length >= 16) {

        // write in 128-bit bursts while we can
        MXC_FLC->cn &= ~MXC_F_FLC_CN_WDTH;

        while (length >= 16) {
            MXC_FLC->addr = address;
            memcpy((void*)&MXC_FLC->data[0], buffer, 16);
            MXC_FLC->cn |= MXC_F_FLC_CN_WR;

            /* Wait until flash operation is complete */
            while (FLC_Busy());

            address += 16;
            length -= 16;
            buffer += 16;
    }

        // Return to 32-bit writes.
        MXC_FLC->cn |= MXC_F_FLC_CN_WDTH;
    }

        while (length >= 4) {
            MXC_FLC->addr = address;
            memcpy((void*)&MXC_FLC->data[0], buffer, 4);
            MXC_FLC->cn |= MXC_F_FLC_CN_WR;

            /* Wait until flash operation is complete */
            while (FLC_Busy());

            address += 4;
            length -= 4;
            buffer += 4;
        }

    if (length > 0) {
        // Save the data currently in the flash
        memcpy(current_data, (void*)(address), 4);

        // Modify current_data to insert the data from buffer
        memcpy(current_data, buffer, length);

        MXC_FLC->addr = address;
        memcpy((void*)&MXC_FLC->data[0], current_data, 4);
        MXC_FLC->cn |= MXC_F_FLC_CN_WR;

        /* Wait until flash operation is complete */
        while (FLC_Busy());
    }

    /* Lock flash */
    MXC_FLC->cn &= ~MXC_F_FLC_CN_UNLOCK;

    /* Check access violations */
    if (MXC_FLC->intr & MXC_F_FLC_INTR_AF) {
        MXC_FLC->intr &= ~MXC_F_FLC_INTR_AF;
        return E_BAD_STATE;
    }

    SYS_Flash_Operation();

    return E_NO_ERROR;
}

int FLC_EnableInt(uint32_t mask)
{
  uint32_t tmp;

  mask &= (MXC_F_FLC_INTR_DONEIE |  MXC_F_FLC_INTR_AFIE);
  if (!mask) {
    /* No bits set? Wasn't something we can enable. */
    return E_BAD_PARAM;
  }

  /* Careful with access_fail bit, as it is W0C */
  tmp = MXC_FLC->intr | MXC_F_FLC_INTR_AF;
  /* Don't lose done flag */
  tmp &= ~(MXC_F_FLC_INTR_DONE);
  /* Apply enables and write back */
  MXC_FLC->intr = (tmp | mask);

  return E_NO_ERROR;
}

int FLC_DisableInt(uint32_t mask)
{
  uint32_t tmp;

  mask &= (MXC_F_FLC_INTR_DONEIE |  MXC_F_FLC_INTR_AFIE);
  if (!mask) {
    /* No bits set? Wasn't something we can disable. */
    return E_BAD_PARAM;
  }

  /* Careful with access_fail bit, as it is W0C */
  tmp = MXC_FLC->intr | MXC_F_FLC_INTR_AF;
  /* Don't lose done flag */
  tmp &= ~(MXC_F_FLC_INTR_DONE);
  /* Apply disables and write back */
  MXC_FLC->intr = (tmp & ~mask);

  return E_NO_ERROR;
}

int FLC_GetFlags(void)
{
  return (MXC_FLC->intr & (MXC_F_FLC_INTR_DONE | MXC_F_FLC_INTR_AF));
}

int FLC_ClearFlags(uint32_t mask)
{
  mask &= (MXC_F_FLC_INTR_DONE | MXC_F_FLC_INTR_AF);
  if (!mask) {
    /* No bits set? Wasn't something we can clear. */
    return E_BAD_PARAM;
  }

  // Both bits are write zero clear
  MXC_FLC->intr ^= mask;

  return E_NO_ERROR;
}

int FLC_UnlockInfoBlock()
{
    MXC_FLC->acntl = 0x3a7f5ca3;
    MXC_FLC->acntl = 0xa1e34f20;
    MXC_FLC->acntl = 0x9608b2c1;
    return E_NO_ERROR;
}

int FLC_LockInfoBlock()
{
    MXC_FLC->acntl = 0xDEADBEEF;
    return E_NO_ERROR;
}
