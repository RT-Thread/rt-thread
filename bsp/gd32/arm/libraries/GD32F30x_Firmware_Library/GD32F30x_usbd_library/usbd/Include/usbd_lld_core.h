/*!
    \file    usbd_lld_core.h
    \brief   USB device low level driver core

    \version 2020-08-01, V3.0.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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

#ifndef __USBD_LLD_CORE_H
#define __USBD_LLD_CORE_H

#include "usbd_lld_regs.h"
#include "usbd_core.h"

/* double buffer endpoint direction enumeration */
enum dbuf_ep_dir
{
    DBUF_EP_IN,               /*!< double buffer in direction */
    DBUF_EP_OUT,              /*!< double buffer out direction */
    DBUF_EP_ERR,              /*!< double buffer error direction */
};

/* USBD endpoint ram struct */
typedef struct
{
    __IO uint32_t tx_addr;    /*!< transmission address */
    __IO uint32_t tx_count;   /*!< transmission count */
    __IO uint32_t rx_addr;    /*!< reception address */
    __IO uint32_t rx_count;   /*!< reception count */
} usbd_ep_ram;

extern struct _usb_handler usbd_drv_handler;

/* USB core driver struct */
typedef struct
{
    usb_basic  basic;
    usb_dev   *dev;
} usb_core_drv;

extern usb_core_drv usbd_core;

/* function declarations */
/* free buffer used from application by toggling the SW_BUF byte */
void user_buffer_free (uint8_t ep_num, uint8_t dir);

#endif /* __USBD_LLD_CORE_H */
