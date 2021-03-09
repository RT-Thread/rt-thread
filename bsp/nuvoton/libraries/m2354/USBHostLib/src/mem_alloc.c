/**************************************************************************//**
 * @file     mem_alloc.c
 * @version  V1.10
 * @brief   USB host library memory allocation functions.
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2019-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NuMicro.h"

#include "usb.h"


/// @cond HIDDEN_SYMBOLS

//#define MEM_DEBUG

#ifdef MEM_DEBUG
#define mem_debug       rt_kprintf
#else
#define mem_debug(...)
#endif

#ifdef __ICCARM__
#pragma data_alignment=32
static uint8_t  _mem_pool[MEM_POOL_UNIT_NUM][MEM_POOL_UNIT_SIZE];
#else
static uint8_t _mem_pool[MEM_POOL_UNIT_NUM][MEM_POOL_UNIT_SIZE] __attribute__((aligned(32)));
#endif
static uint8_t  _unit_used[MEM_POOL_UNIT_NUM];

static volatile int  _usbh_mem_used;
static volatile int  _usbh_max_mem_used;
static volatile int  _mem_pool_used;


UDEV_T * g_udev_list;

uint8_t  _dev_addr_pool[128];
static volatile int  _device_addr;

/*--------------------------------------------------------------------------*/
/*   Memory alloc/free recording                                            */
/*--------------------------------------------------------------------------*/

void usbh_memory_init(void)
{
    if(sizeof(TD_T) > MEM_POOL_UNIT_SIZE)
    {
        USB_error("TD_T - MEM_POOL_UNIT_SIZE too small!\n");
        while(1);
    }

    if(sizeof(ED_T) > MEM_POOL_UNIT_SIZE)
    {
        USB_error("ED_T - MEM_POOL_UNIT_SIZE too small!\n");
        while(1);
    }

    _usbh_mem_used = 0L;
    _usbh_max_mem_used = 0L;

    memset(_unit_used, 0, sizeof(_unit_used));
    _mem_pool_used = 0;

    g_udev_list = NULL;

    memset(_dev_addr_pool, 0, sizeof(_dev_addr_pool));
    _device_addr = 1;
}

uint32_t  usbh_memory_used(void)
{
    rt_kprintf("USB static memory: %d/%d, heap used: %d\n", _mem_pool_used, MEM_POOL_UNIT_NUM, _usbh_mem_used);
    return _usbh_mem_used;
}

static void  memory_counter(int size)
{
    _usbh_mem_used += size;
    if (_usbh_mem_used > _usbh_max_mem_used)
        _usbh_max_mem_used = _usbh_mem_used;
}

void * usbh_alloc_mem(int size)
{
    void  *p;

    p = malloc(size);
    if (p == NULL)
    {
        USB_error("usbh_alloc_mem failed! %d\n", size);
        return NULL;
    }

    memset(p, 0, size);
    memory_counter(size);
    return p;
}

void usbh_free_mem(void *p, int size)
{
    free(p);
    memory_counter(0-size);
}


/*--------------------------------------------------------------------------*/
/*   USB device allocate/free                                               */
/*--------------------------------------------------------------------------*/

UDEV_T * alloc_device(void)
{
    UDEV_T  *udev;

    udev = malloc(sizeof(*udev));
    if (udev == NULL)
    {
        USB_error("alloc_device failed!\n");
        return NULL;
    }
    memset(udev, 0, sizeof(*udev));
    memory_counter(sizeof(*udev));
    udev->cur_conf = -1;                    /* must! used to identify the first SET CONFIGURATION */
    udev->next = g_udev_list;               /* chain to global device list */
    g_udev_list = udev;
    return udev;
}

void free_device(UDEV_T *udev)
{
    UDEV_T  *d;

    if (udev == NULL)
        return;

    if (udev->cfd_buff != NULL)
        usbh_free_mem(udev->cfd_buff, MAX_DESC_BUFF_SIZE);

    /*
     *  Remove it from the global device list
     */
    if (g_udev_list == udev)
    {
        g_udev_list = g_udev_list->next;
    }
    else
    {
        d = g_udev_list;
        while (d != NULL)
        {
            if (d->next == udev)
            {
                d->next = udev->next;
                break;
            }
            d = d->next;
        }
    }

    free(udev);
    memory_counter(-sizeof(*udev));
}

int  alloc_dev_address(void)
{
    _device_addr++;

    if (_device_addr >= 128)
        _device_addr = 1;

    while (1)
    {
        if (_dev_addr_pool[_device_addr] == 0)
        {
            _dev_addr_pool[_device_addr] = 1;
            return _device_addr;
        }
        _device_addr++;
        if (_device_addr >= 128)
            _device_addr = 1;
    }
}

void  free_dev_address(int dev_addr)
{
    if (dev_addr < 128)
        _dev_addr_pool[dev_addr] = 0;
}

/*--------------------------------------------------------------------------*/
/*   UTR (USB Transfer Request) allocate/free                               */
/*--------------------------------------------------------------------------*/

UTR_T * alloc_utr(UDEV_T *udev)
{
    UTR_T  *utr;

    utr = malloc(sizeof(*utr));
    if (utr == NULL)
    {
        USB_error("alloc_utr failed!\n");
        return NULL;
    }
    memory_counter(sizeof(*utr));
    memset(utr, 0, sizeof(*utr));
    utr->udev = udev;
    mem_debug("[ALLOC] [UTR] - 0x%x\n", (int)utr);
    return utr;
}

void free_utr(UTR_T *utr)
{
    if (utr == NULL)
        return;

    mem_debug("[FREE] [UTR] - 0x%x\n", (int)utr);
    free(utr);
    memory_counter(0-(int)sizeof(*utr));
}

/*--------------------------------------------------------------------------*/
/*   OHCI ED allocate/free                                                  */
/*--------------------------------------------------------------------------*/

ED_T * alloc_ohci_ED(void)
{
    int    i;
    ED_T   *ed;

    for (i = 0; i < MEM_POOL_UNIT_NUM; i++)
    {
        if (_unit_used[i] == 0)
        {
            _unit_used[i] = 1;
            _mem_pool_used++;
            ed = (ED_T *)&_mem_pool[i];
            memset(ed, 0, sizeof(*ed));
            mem_debug("[ALLOC] [ED] - 0x%x\n", (int)ed);
            return ed;
        }
    }
    USB_error("alloc_ohci_ED failed!\n");
    return NULL;
}

void free_ohci_ED(ED_T *ed)
{
    int      i;

    for (i = 0; i < MEM_POOL_UNIT_NUM; i++)
    {
        if ((uint32_t)&_mem_pool[i] == (uint32_t)ed)
        {
            mem_debug("[FREE]  [ED] - 0x%x\n", (int)ed);
            _unit_used[i] = 0;
            _mem_pool_used--;
            return;
        }
    }
    USB_debug("free_ohci_ED - not found! (ignored in case of multiple UTR)\n");
}

/*--------------------------------------------------------------------------*/
/*   OHCI TD allocate/free                                                  */
/*--------------------------------------------------------------------------*/
TD_T * alloc_ohci_TD(UTR_T *utr)
{
    int    i;
    TD_T   *td;

    for (i = 0; i < MEM_POOL_UNIT_NUM; i++)
    {
        if (_unit_used[i] == 0)
        {
            _unit_used[i] = 1;
            _mem_pool_used++;
            td = (TD_T *)&_mem_pool[i];

            memset(td, 0, sizeof(*td));
            td->utr = utr;
            mem_debug("[ALLOC] [TD] - 0x%x\n", (int)td);
            return td;
        }
    }
    USB_error("alloc_ohci_TD failed!\n");
    return NULL;
}

void free_ohci_TD(TD_T *td)
{
    int   i;

    for (i = 0; i < MEM_POOL_UNIT_NUM; i++)
    {
        if ((uint32_t)&_mem_pool[i] == (uint32_t)td)
        {
            mem_debug("[FREE]  [TD] - 0x%x\n", (int)td);
            _unit_used[i] = 0;
            _mem_pool_used--;
            return;
        }
    }
    USB_error("free_ohci_TD - not found!\n");
}

/// @endcond HIDDEN_SYMBOLS

/*** (C) COPYRIGHT 2019-2020 Nuvoton Technology Corp. ***/

