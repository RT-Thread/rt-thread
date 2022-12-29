/**************************************************************************//**
 * @file     support.c
 * @version  V1.10
 * $Revision: 11 $
 * $Date: 14/10/03 1:54p $
 * @brief  Functions to support USB host driver.
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usb.h"

/// @cond HIDDEN_SYMBOLS


#define  USB_MEMORY_POOL_SIZE   (32*1024)
#define  USB_MEM_BLOCK_SIZE     128

#define  BOUNDARY_WORD          4


static uint32_t  _FreeMemorySize;
uint32_t  _AllocatedMemorySize;


#define USB_MEM_ALLOC_MAGIC     0x19685788    /* magic number in leading block */

typedef struct USB_mhdr
{
    uint32_t  flag;  /* 0:free, 1:allocated, 0x3:first block */
    uint32_t  bcnt;  /* if allocated, the block count of allocated memory block */
    uint32_t  magic;
    uint32_t  reserved;
}  USB_MHDR_T;

uint8_t  _USBMemoryPool[USB_MEMORY_POOL_SIZE] __attribute__((section(".usbhostlib.USBMemoryPool")))  __attribute__((aligned(USB_MEM_BLOCK_SIZE)));

static USB_MHDR_T  *_pCurrent;
uint32_t  *_USB_pCurrent = (uint32_t *) &_pCurrent;

static uint32_t  _MemoryPoolBase, _MemoryPoolEnd;


void  USB_InitializeMemoryPool()
{
    _MemoryPoolBase = (uint32_t)&_USBMemoryPool[0];
    _MemoryPoolEnd = _MemoryPoolBase + USB_MEMORY_POOL_SIZE;
    _FreeMemorySize = _MemoryPoolEnd - _MemoryPoolBase;
    _AllocatedMemorySize = 0;
    _pCurrent = (USB_MHDR_T *)_MemoryPoolBase;
    memset((char *)_MemoryPoolBase, 0, _FreeMemorySize);
}


int  USB_available_memory()
{
    return _FreeMemorySize;
}


int  USB_allocated_memory()
{
    return _AllocatedMemorySize;
}


void  *USB_malloc(int wanted_size, int boundary)
{
    USB_MHDR_T  *pPrimitivePos = _pCurrent;
    USB_MHDR_T  *pFound;
    int   found_size = -1;
    int   i, block_count;
    int   wrap = 0;
    void   *pvBuf = NULL;
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    if (wanted_size >= _FreeMemorySize)
    {
        rt_kprintf("USB_malloc - want=%d, free=%d\n", wanted_size, _FreeMemorySize);
        goto exit_USB_malloc;
    }


    if ((uint32_t)_pCurrent >= _MemoryPoolEnd)
        _pCurrent = (USB_MHDR_T *)_MemoryPoolBase;   /* wrapped */

    do
    {
        if (_pCurrent->flag)          /* is not a free block */
        {
            if (_pCurrent->magic != USB_MEM_ALLOC_MAGIC)
            {
                rt_kprintf("\nUSB_malloc - incorrect magic number! C:%x F:%x, wanted:%d, Base:0x%x, End:0x%x\n", (uint32_t)_pCurrent, _FreeMemorySize, wanted_size, (uint32_t)_MemoryPoolBase, (uint32_t)_MemoryPoolEnd);
                goto exit_USB_malloc;
            }

            if (_pCurrent->flag == 0x3)
                _pCurrent = (USB_MHDR_T *)((uint32_t)_pCurrent + _pCurrent->bcnt * USB_MEM_BLOCK_SIZE);
            else
            {
                rt_kprintf("USB_malloc warning - not the first block!\n");
                _pCurrent = (USB_MHDR_T *)((uint32_t)_pCurrent + USB_MEM_BLOCK_SIZE);
            }

            if ((uint32_t)_pCurrent > _MemoryPoolEnd)
                rt_kprintf("USB_malloc - behind limit!!\n");

            if ((uint32_t)_pCurrent == _MemoryPoolEnd)
            {
                //rt_kprintf("USB_alloc - warp!!\n");
                wrap = 1;
                _pCurrent = (USB_MHDR_T *)_MemoryPoolBase;   /* wrapped */
            }

            found_size = -1;          /* reset the accumlator */
        }
        else                         /* is a free block */
        {
            if (found_size == -1)     /* the leading block */
            {
                pFound = _pCurrent;
                block_count = 1;

                if (boundary > BOUNDARY_WORD)
                    found_size = 0;    /* not use the data area of the leading block */
                else
                    found_size = USB_MEM_BLOCK_SIZE - sizeof(USB_MHDR_T);

                /* check boundary -
                 * If boundary > BOUNDARY_WORD, the start of next block should
                 * be the beginning address of allocated memory. Thus, we check
                 * the boundary of the next block. The leading block will be
                 * used as a header only.
                 */
                if ((boundary > BOUNDARY_WORD) &&
                        ((((uint32_t)_pCurrent) + USB_MEM_BLOCK_SIZE >= _MemoryPoolEnd) ||
                         ((((uint32_t)_pCurrent) + USB_MEM_BLOCK_SIZE) % boundary != 0)))
                    found_size = -1;   /* violate boundary, reset the accumlator */
            }
            else                      /* not the leading block */
            {
                found_size += USB_MEM_BLOCK_SIZE;
                block_count++;
            }

            if (found_size >= wanted_size)
            {
                pFound->bcnt = block_count;
                pFound->magic = USB_MEM_ALLOC_MAGIC;
                _FreeMemorySize -= block_count * USB_MEM_BLOCK_SIZE;
                _AllocatedMemorySize += block_count * USB_MEM_BLOCK_SIZE;
                _pCurrent = pFound;
                for (i = 0; i < block_count; i++)
                {
                    _pCurrent->flag = 1;     /* allocate block */
                    _pCurrent = (USB_MHDR_T *)((uint32_t)_pCurrent + USB_MEM_BLOCK_SIZE);
                }
                pFound->flag = 0x3;

                if (boundary > BOUNDARY_WORD)
                {
                    pvBuf = (void *)((uint32_t)pFound + USB_MEM_BLOCK_SIZE);
                    goto exit_USB_malloc;
                }
                else
                {
                    //USB_debug("USB_malloc(%d,%d):%x\tsize:%d, C:0x%x, %d\n", wanted_size, boundary, (uint32_t)pFound + sizeof(USB_MHDR_T), block_count * USB_MEM_BLOCK_SIZE, _pCurrent, block_count);
                    pvBuf = (void *)((uint32_t)pFound + sizeof(USB_MHDR_T));
                    goto exit_USB_malloc;
                }
            }

            /* advance to the next block */
            _pCurrent = (USB_MHDR_T *)((uint32_t)_pCurrent + USB_MEM_BLOCK_SIZE);
            if ((uint32_t)_pCurrent >= _MemoryPoolEnd)
            {
                wrap = 1;
                _pCurrent = (USB_MHDR_T *)_MemoryPoolBase;   /* wrapped */
                found_size = -1;     /* reset accumlator */
            }
        }
    }
    while ((wrap == 0) || (_pCurrent < pPrimitivePos));

    rt_kprintf("USB_malloc - No free memory!\n");

exit_USB_malloc:

    rt_hw_interrupt_enable(level);

    return pvBuf;
}


void  USB_free(void *alloc_addr)
{
    USB_MHDR_T  *pMblk;
    uint32_t  addr = (uint32_t)alloc_addr;
    int     i, count;
    rt_base_t level;

    //rt_kprintf("USB_free: 0x%x\n", (int)alloc_addr);

    level = rt_hw_interrupt_disable();

    if ((addr < _MemoryPoolBase) || (addr >= _MemoryPoolEnd))
    {
        if (addr)
        {
            rt_kprintf("[%s]Wrong!!\n", __func__);
        }
        goto Exit_USB_free;
    }

    //rt_kprintf("USB_free:%x\n", (int32_t)addr+USB_MEM_BLOCK_SIZE);

    /* get the leading block address */
    if (addr % USB_MEM_BLOCK_SIZE == 0)
        addr -= USB_MEM_BLOCK_SIZE;
    else
        addr -= sizeof(USB_MHDR_T);

    if (addr % USB_MEM_BLOCK_SIZE != 0)
    {
        rt_kprintf("USB_free fatal error on address: %x!!\n", (uint32_t)alloc_addr);
        goto Exit_USB_free;
    }

    pMblk = (USB_MHDR_T *)addr;
    if (pMblk->flag == 0)
    {
        rt_kprintf("USB_free(), warning - try to free a free block: %x\n", (uint32_t)alloc_addr);
        goto Exit_USB_free;
    }
    if (pMblk->magic != USB_MEM_ALLOC_MAGIC)
    {
        rt_kprintf("USB_free(), warning - try to free an unknow block at address:%x.\n", addr);
        goto Exit_USB_free;
    }

    //_pCurrent = pMblk;

    //rt_kprintf("+ 0x%x, %d\n", (int)pMblk, pMblk->bcnt);

    count = pMblk->bcnt;
    for (i = 0; i < count; i++)
    {
        pMblk->flag = 0;     /* release block */
        pMblk = (USB_MHDR_T *)((uint32_t)pMblk + USB_MEM_BLOCK_SIZE);
    }

    _FreeMemorySize += count * USB_MEM_BLOCK_SIZE;
    _AllocatedMemorySize -= count * USB_MEM_BLOCK_SIZE;


Exit_USB_free:

    rt_hw_interrupt_enable(level);

    return;
}


/// @endcond HIDDEN_SYMBOLS

