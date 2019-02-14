/**
  *********************************************************************************
  *
  * @file    ald_flash.c
  * @brief   FLASH module driver.
  *
  * @version V1.0
  * @date    20 Nov 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  *
  *********************************************************************************
  * @verbatim
  ==============================================================================
                    ##### FLASH Peripheral features #####
  ==============================================================================
  [..]
  Base address is 0x00000000

  [..]
  FLASH have just one programme mode , word programme.
  word programme can programme 8 bytes once ;

  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) programme flash using flash_write(uint32_t addr, uint8_t *buf, uint16_t len)
       (++) call the function and supply all the three paraments is needs, addr means
            the first address to write in this operation, buf is a pointer to the data which
        need writing to flash.

   (#) erase flash using flash_erase(uint32_t addr, uint16_t len)
       (++) call the function and supply two paraments, addr is the first address to erase,
            len is the length to erase

   (#) read flash using flash_read(uint32_t *ram_addr, uint32_t addr, uint16_t len)
       (++) read the flash and save to a buffer, ram_addr is the buffer's first address,
            addr is the start reading address in flash, len is the length need read

    @endverbatim
  */

#include "ald_flash.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup FLASH FLASH
  * @brief FLASH module driver
  * @{
  */

#ifdef ALD_FLASH

/** @addtogroup FLASH_Private_Types
  * @{
  */

/* opration buffer, global variable*/
static uint8_t write_buf[FLASH_PAGE_SIZE];
static op_cmd_type OP_CMD = OP_FLASH;

#if defined ( __ICCARM__ )
    #define __RAMFUNC       __ramfunc
#else
    #define __RAMFUNC
#endif

/**
  * @}
  */

/** @defgroup Flash_Private_Functions Flash Private Functions
  *  @brief   Flash Private functions
  * @{
  */

/**
  * @brief  Unlock the flash.
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC static ald_status_t flash_unlock(void)
{
    uint16_t i;
    uint16_t op_cmd = OP_CMD;

    if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_BUSY_MSK))
        return ERROR;

    FLASH_REG_UNLOCK();
    FLASH_IAP_ENABLE();
    FLASH_REQ();

    for (i = 0; i < 0xFFFF; i++)
    {
        if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_FLASHACK_MSK))
            break;
    }

    return i == 0xFFFF ? ERROR : OK;
}

/**
  * @brief  Lock the flash.
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC static ald_status_t flash_lock(void)
{
    uint16_t i;
    uint16_t op_cmd = OP_CMD;

    FLASH_REG_UNLOCK();
    WRITE_REG(MSC->FLASHCR, 0x0);

    for (i = 0; i < 0xFFFF; i++)
    {
        if (!(READ_BIT(MSC->FLASHSR, MSC_FLASHSR_FLASHACK_MSK)))
            break;
    }

    return i == 0xFFFF ? ERROR : OK;
}

/**
  * @brief  Erase one page.
  * @param  addr: The erased page's address
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC static ald_status_t flash_page_erase(uint32_t addr)
{
    uint32_t i;
    uint16_t op_cmd = OP_CMD;

    __disable_irq();
    if (flash_unlock() != OK)
        goto end;

    if (op_cmd == OP_FLASH)
    {
        CLEAR_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK);
        MODIFY_REG(MSC->FLASHADDR, MSC_FLASHADDR_ADDR_MSK, FLASH_PAGE_ADDR(addr) << MSC_FLASHADDR_ADDR_POSS);
    }
    else
    {
        SET_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK);
        MODIFY_REG(MSC->FLASHADDR, MSC_FLASHADDR_ADDR_MSK, INFO_PAGE_ADDR(addr) << MSC_FLASHADDR_ADDR_POSS);
    }

    WRITE_REG(MSC->FLASHCMD, FLASH_CMD_PE);

    for (i = 0; i < 0xFFFF; i++)
    {
        if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_BUSY_MSK))
            continue;
        if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_ADDR_OV_MSK))
            goto end;
        if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_WRP_FLAG_MSK))
            goto end;
        if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_SERA_MSK))
            break;
    }

    if (i == 0xFFFF)
        goto end;

    if (flash_lock() == ERROR)
        goto end;

    __enable_irq();
    return OK;
end:

    if (flash_lock() == ERROR)
        while (1);

    __enable_irq();
    return ERROR;
}

/**
  * @brief  Programme a word.
  * @param  addr: The word's address, it is must word align.
  * @param  data: The 8 bytes data be write.
  * @param  len: The number of data be write.
  * @param  fifo: Choose if use fifo.
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC static ald_status_t flash_word_program(uint32_t addr, uint32_t data[], uint32_t len, uint32_t fifo)
{
    uint16_t i;
    uint16_t prog_len;
    uint32_t *p_data = data;
    uint16_t op_cmd = OP_CMD;

    __disable_irq();
    if (flash_unlock() != OK)
        goto end;

    if (op_cmd == OP_FLASH)
        CLEAR_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK);
    else
        SET_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK);

    MODIFY_REG(MSC->FLASHADDR, MSC_FLASHADDR_ADDR_MSK, addr << MSC_FLASHADDR_ADDR_POSS);
    MODIFY_REG(MSC->FLASHCR, MSC_FLASHCR_FIFOEN_MSK, fifo << MSC_FLASHCR_FIFOEN_POS);

    for (prog_len = 0; prog_len < len; prog_len++)
    {
        if (fifo)
        {
            WRITE_REG(MSC->FLASHFIFO, p_data[0]);
            WRITE_REG(MSC->FLASHFIFO, p_data[1]);
        }
        else
        {
            WRITE_REG(MSC->FLASHDL, p_data[0]);
            WRITE_REG(MSC->FLASHDH, p_data[1]);
            WRITE_REG(MSC->FLASHCMD, FLASH_CMD_WP);
        }

        p_data += 2;

        for (i = 0; i < 0xFFFF; i++)
        {
            if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_BUSY_MSK))
                continue;
            if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_PROG_MSK))
                break;
        }
    }
    if (i == 0xFFFF)
        goto end;

    if (flash_lock() == ERROR)
        goto end;

    __enable_irq();
    return OK;
end:
    if (flash_lock() == ERROR)
        while (1);

    __enable_irq();
    return ERROR;
}

/**
  * @brief  Read data from flash, and store in buffer.
  * @param  ram_addr: The stored buffer's address.
  * @param  addr: The start address in flash to read.
  * @param  len: The length of byte to read.
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC static ald_status_t __flash_read(uint32_t ram_addr[], uint32_t addr, uint32_t len)
{
    uint32_t i;

    if (!len)
        return ERROR;

    for (i = 0; i < len; i++)
    {
        ram_addr[i] = ((uint32_t *)addr)[i];
    }

    return OK;
}

/**
  * @brief  Check whether the flash between the given address section
  *         have been writen, if it have been writen, return TRUE, else
  *         return FALSE.
  * @param  begin_addr: The begin address.
  * @param  end_addr: The end address.
  * @retval The check result
  *         - TRUE
  *         - FALSE
  */
__RAMFUNC static type_bool_t page_have_writen(uint32_t begin_addr, uint32_t end_addr)
{
    uint8_t *addr_to_read;
    uint8_t value;
    uint32_t index;

    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(begin_addr));
    assert_param(IS_FLASH_ADDRESS(end_addr));

    addr_to_read = (uint8_t *)begin_addr;
    index        = begin_addr;
    value        = 0xFF;

    if (begin_addr > end_addr)
        return FALSE;

    while (index++ <= end_addr)
    {
        value = *addr_to_read++;

        if (value != 0xFF)
            break;
    }

    return value == 0xFF ? FALSE : TRUE;
}

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions FLASH Exported Functions
  * @verbatim
 ===============================================================================
              ##### Flash oprate functions #####
 ===============================================================================
  [..]
    This section provides functions allowing to operate flash, such as read and write.

    @endverbatim
  * @{
  */

/**
  * @brief  Write the give bytes to the given address section.
  * @param  addr: The start address to write.
  * @param  buf: The bytes' address.
  * @param  len: The length to write,and multiple of 2.
  * @retval Status, see @ref ald_status_t.
  */

__RAMFUNC ald_status_t flash_write(uint32_t addr, uint8_t *buf, uint16_t len)
{
    uint32_t index = 0;
    uint32_t para = 0;
    uint32_t index2 = 0;
    uint32_t start_write_addr;
    uint32_t end_write_addr;
    uint32_t start_word_addr;
    uint32_t end_word_addr;
    uint16_t len_to_write;
    uint32_t len_index;
    type_bool_t need_erase_page;

    assert_param(IS_FLASH_ADDRESS(addr));
    assert_param(IS_FLASH_ADDRESS(addr + len - 1));

    len_to_write = len;

    while (len_to_write > 0)
    {
        need_erase_page = FALSE;

        for (index = 0; index < FLASH_PAGE_SIZE; index++)
            write_buf[index] = 0xFF;

        start_write_addr = addr + (len - len_to_write);
        end_write_addr   = addr + len - 1;
        end_write_addr   = FLASH_PAGE_ADDR(start_write_addr) == FLASH_PAGE_ADDR(end_write_addr)
                           ? end_write_addr : FLASH_PAGEEND_ADDR(start_write_addr);
        need_erase_page  = page_have_writen(FLASH_WORD_ADDR(start_write_addr),
                                            FLASH_WORDEND_ADDR(end_write_addr));

        if (need_erase_page)
        {
            if (ERROR == __flash_read((uint32_t *)write_buf, FLASH_PAGE_ADDR(start_write_addr),
                                      FLASH_PAGE_SIZE >> 2))
                return ERROR;

            if (ERROR == flash_page_erase(FLASH_PAGE_ADDR(start_write_addr)))
                return ERROR;

            para   = end_write_addr & (FLASH_PAGE_SIZE - 1);
            index  = start_write_addr & (FLASH_PAGE_SIZE - 1);
            index2 = len - len_to_write;

            while (index <= para)
                write_buf[index++] = buf[index2++];

            index2     = 0;
            index      = FLASH_PAGE_ADDR(start_write_addr);
            para       = FLASH_PAGE_ADDR(start_write_addr) + FLASH_PAGE_SIZE;
            len_index  = FLASH_PAGE_SIZE;
        }
        else
        {
            para   = end_write_addr & (FLASH_PAGE_SIZE - 1);
            index  = start_write_addr & (FLASH_PAGE_SIZE - 1);
            index2 = len - len_to_write;

            while (index <= para)
                write_buf[index++] = buf[index2++];

            start_word_addr = FLASH_WORD_ADDR(start_write_addr);
            end_word_addr   = FLASH_WORDEND_ADDR(end_write_addr);
            index2          = (FLASH_WORD_ADDR(start_word_addr) - FLASH_PAGE_ADDR(start_word_addr));
            index           = start_word_addr;
            len_index       = end_word_addr - start_word_addr + 1;
        }

        if (ERROR == flash_word_program(index, (uint32_t *)(write_buf + index2), (len_index >> 3), FLASH_FIFO))
            return ERROR;

        len_to_write = len_to_write - (end_write_addr - start_write_addr + 1);
    }

    return OK;
}

/**
  * @brief  erase The flash between the given address section.
  * @param  addr: The start address to erase.
  * @param  len: The length to erase.
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC ald_status_t flash_erase(uint32_t addr, uint16_t len)
{
    int32_t index;
    int32_t para;
    int32_t start_erase_addr;
    int32_t end_erase_addr;
    uint16_t len_not_erase;
    uint32_t len_index;
    type_bool_t page_need_save;

    assert_param(IS_FLASH_ADDRESS(addr));
    assert_param(IS_FLASH_ADDRESS(addr + len - 1));

    len_not_erase = len;

    while (len_not_erase > 0)
    {
        page_need_save = FALSE;

        start_erase_addr = addr + len - len_not_erase;
        end_erase_addr   = addr + len - 1;
        end_erase_addr   = (FLASH_PAGE_ADDR(start_erase_addr) == FLASH_PAGE_ADDR(end_erase_addr))
                           ? end_erase_addr : FLASH_PAGEEND_ADDR(start_erase_addr);

        if (start_erase_addr != FLASH_PAGE_ADDR(start_erase_addr))
        {
            if (page_have_writen(FLASH_PAGE_ADDR(start_erase_addr), (start_erase_addr - 1)))
                page_need_save = TRUE;
        }
        if (end_erase_addr != FLASH_PAGEEND_ADDR(end_erase_addr))
        {
            if (page_have_writen((end_erase_addr + 1), FLASH_PAGEEND_ADDR(end_erase_addr)))
                page_need_save = TRUE;
        }

        if (page_need_save)
        {
            if (ERROR == __flash_read((uint32_t *)write_buf, FLASH_PAGE_ADDR(start_erase_addr),
                                      FLASH_PAGE_SIZE >> 2))
            {
                __enable_irq();
                return ERROR;
            }
        }

        if (ERROR == flash_page_erase(FLASH_PAGE_ADDR(start_erase_addr)))
        {
            __enable_irq();
            return ERROR;
        }

        if (page_need_save)
        {
            para  = end_erase_addr & (FLASH_PAGE_SIZE - 1);
            index = start_erase_addr & (FLASH_PAGE_SIZE - 1);

            while (index <= para)
                write_buf[index++] = 0xFF;

            index     = FLASH_PAGE_ADDR(start_erase_addr);
            len_index = FLASH_PAGE_SIZE;
            if (ERROR == flash_word_program(index, (uint32_t *)write_buf, (len_index >> 3), FLASH_FIFO))
            {
                __enable_irq();
                return ERROR;
            }
        }
        len_not_erase = len_not_erase - (end_erase_addr - start_erase_addr + 1);
    }

    return OK;
}

/**
  * @brief  read the specified length bytes from flash, and store to the specified area.
  * @param  ram_addr: the specified area to store the reading bytes.
  * @param  addr: the start address.
  * @param  len: the length to read.
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC ald_status_t flash_read(uint32_t *ram_addr, uint32_t addr, uint16_t len)
{
    uint32_t temp;

    assert_param(IS_4BYTES_ALIGN(ram_addr));
    assert_param(IS_FLASH_ADDRESS(addr));
    assert_param(IS_FLASH_ADDRESS(addr + len - 1));

    temp = (uint32_t)ram_addr;

    if (((temp & 0x3) != 0) || (((addr) & 0x3) != 0))
        return ERROR;

    return __flash_read(ram_addr, addr, len) == ERROR ? ERROR : OK;
}

/**
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */
