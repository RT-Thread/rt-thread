/*!
    \file    dfu_mem.c
    \brief   USB DFU device media access layer functions

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "dfu_mem.h"
#include "usbd_transc.h"

extern usb_core_driver usb_dfu_dev;

extern struct {
    uint8_t buf[TRANSFER_SIZE];
    uint16_t data_len;
    uint16_t block_num;
    uint32_t base_addr;
} prog;

dfu_mem_prop *mem_tab[MAX_USED_MEMORY_MEDIA] = {
    &dfu_inter_flash_cb,
    &dfu_nor_flash_cb,
    &dfu_nand_flash_cb,
};

/* The list of memory interface string descriptor pointers. This list
   can be updated whenever a memory has to be added or removed */
const uint8_t *USBD_DFU_StringDesc[MAX_USED_MEMORY_MEDIA] = {
    (const uint8_t *)INTER_FLASH_IF_STR,
    (const uint8_t *)NOR_FLASH_IF_STR,
    (const uint8_t *)NAND_FLASH_IF_STR
};

static uint8_t dfu_mem_checkaddr(uint32_t addr);

/*!
    \brief      initialize the memory media
    \param[in]  none
    \param[out] none
    \retval     MEM_OK
*/
uint8_t dfu_mem_init(void)
{
    uint32_t mem_index = 0U;

    /* initialize all supported memory medias */
    for(mem_index = 0U; mem_index < MAX_USED_MEMORY_MEDIA; mem_index++) {
        /* check if the memory media exists */
        if(NULL != mem_tab[mem_index]->mem_init) {
            mem_tab[mem_index]->mem_init();
        }
    }

    return MEM_OK;
}

/*!
    \brief      deinitialize the memory media
    \param[in]  none
    \param[out] none
    \retval     MEM_OK
*/
uint8_t dfu_mem_deinit(void)
{
    uint32_t mem_index = 0U;

    /* deinitialize all supported memory medias */
    for(mem_index = 0U; mem_index < MAX_USED_MEMORY_MEDIA; mem_index++) {
        /* check if the memory media exists */
        if(NULL != mem_tab[mem_index]->mem_deinit) {
            mem_tab[mem_index]->mem_deinit();
        }
    }

    return MEM_OK;
}

/*!
    \brief      erase a memory sector
    \param[in]  addr: memory sector address/code
    \param[out] none
    \retval     MEM_OK
*/
uint8_t dfu_mem_erase(uint32_t addr)
{
    uint32_t mem_index = dfu_mem_checkaddr(addr);

    /* check if the address is in protected area */
    if(IS_PROTECTED_AREA(addr)) {
        return MEM_FAIL;
    }

    if(mem_index < MAX_USED_MEMORY_MEDIA) {
        /* check if the operation is supported */
        if(NULL != mem_tab[mem_index]->mem_erase) {
            return mem_tab[mem_index]->mem_erase(addr);
        } else {
            return MEM_FAIL;
        }
    } else {
        return MEM_FAIL;
    }
}

/*!
    \brief      write data to sectors of memory
    \param[in]  buf: the data buffer to be write
    \param[in]  addr: memory sector address/code
    \param[in]  len: data length
    \param[out] none
    \retval     MEM_OK
*/
uint8_t dfu_mem_write(uint8_t *buf, uint32_t addr, uint32_t len)
{
    uint32_t mem_index = dfu_mem_checkaddr(addr);

    /* check if the address is in protected area */
    if(IS_PROTECTED_AREA(addr)) {
        return MEM_FAIL;
    }

    if(OB_RDPT0 == (addr & MAL_MASK_OB)) {
        option_byte_write(addr, buf);
        NVIC_SystemReset();

        return MEM_OK;
    }

    if(mem_index < MAX_USED_MEMORY_MEDIA) {
        /* check if the operation is supported */
        if(NULL != mem_tab[mem_index]->mem_write) {
            return mem_tab[mem_index]->mem_write(buf, addr, len);
        } else {
            return MEM_FAIL;
        }
    } else {
        return MEM_FAIL;
    }
}

/*!
    \brief      read data from sectors of memory
    \param[in]  buf: the data buffer to be write
    \param[in]  addr: memory sector address/code
    \param[in]  len: data length
    \param[out] none
    \retval     pointer to buffer
*/
uint8_t *dfu_mem_read(uint8_t *buf, uint32_t addr, uint32_t len)
{
    uint32_t mem_index = 0U;

    if((OB_RDPT0 != addr) && (OB_RDPT1 != addr)) {
        mem_index = dfu_mem_checkaddr(addr);
    }

    if(mem_index < MAX_USED_MEMORY_MEDIA) {
        /* check if the operation is supported */
        if(NULL != mem_tab[mem_index]->mem_read) {
            return mem_tab[mem_index]->mem_read(buf, addr, len);
        } else {
            return buf;
        }
    } else {
        return buf;
    }
}

/*!
    \brief      get the status of a given memory and store in buffer
    \param[in]  addr: memory sector address/code
    \param[in]  cmd: 0 for erase and 1 for write
    \param[in]  buffer: pointer to the buffer where the status data will be stored
    \param[out] none
    \retval     MEM_OK if all operations are OK, MEM_FAIL else
*/
uint8_t dfu_mem_getstatus(uint32_t addr, uint8_t cmd, uint8_t *buffer)
{
    uint32_t mem_index = dfu_mem_checkaddr(addr);

    if(mem_index < MAX_USED_MEMORY_MEDIA) {
        if(cmd & 0x01U) {
            POLLING_TIMEOUT_SET(mem_tab[mem_index]->write_timeout);
        } else {
            POLLING_TIMEOUT_SET(mem_tab[mem_index]->erase_timeout);
        }

        return MEM_OK;
    } else {
        return MEM_FAIL;
    }
}

/*!
    \brief      check the address is supported
    \param[in]  addr: memory sector address/code
    \param[out] none
    \retval     index of the addressed memory
*/
static uint8_t dfu_mem_checkaddr(uint32_t addr)
{
    uint8_t mem_index = 0U;

    /* check with all supported memories */
    for(mem_index = 0U; mem_index < MAX_USED_MEMORY_MEDIA; mem_index++) {
        /* if the check address is supported, return the memory index */
        if(MEM_OK == mem_tab[mem_index]->mem_checkaddr(addr)) {
            return mem_index;
        }
    }

    /* if there is no memory found, return MAX_USED_MEMORY_MEDIA */
    return (MAX_USED_MEMORY_MEDIA);
}
