/*!
    \file  usbh_hcs.c
    \brief this file implements functions for opening and closing host channels

    \version 2014-12-26, V1.0.0, firmware for GD32F10x
    \version 2017-06-20, V2.0.0, firmware for GD32F10x
    \version 2018-07-31, V2.1.0, firmware for GD32F10x    
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#include "usbh_hcs.h"

static uint16_t usbh_freechannel_get (usb_core_handle_struct *pudev);

/*!
    \brief      open a channel
    \param[in]  pudev: pointer to usb device
    \param[in]  channel_num: host channel number which is in (0..7)
    \param[in]  dev_addr: USB device address allocated to attached device
    \param[in]  dev_speed: USB device speed (Full speed/Low speed)
    \param[in]  ep_type: endpoint type (bulk/int/ctl)
    \param[in]  ep_mps: max packet size
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_channel_open (usb_core_handle_struct *pudev, 
                           uint8_t  channel_num,
                           uint8_t  dev_addr,
                           uint8_t  dev_speed,
                           uint8_t  ep_type,
                           uint16_t ep_mps)
{
    usb_hostchannel_struct *puhc = &pudev->host.host_channel[channel_num];
    uint16_t channel_info = puhc->info;

    puhc->endp_id   = (uint8_t)channel_info & 0x7FU;
    puhc->endp_in   = (uint8_t)(channel_info & 0x80U) >> 7U;
    puhc->endp_type = ep_type;
    puhc->endp_mps  = ep_mps;
    puhc->dev_addr  = dev_addr;
    puhc->dev_speed = dev_speed;

    puhc->data_tg_in  = 0U;
    puhc->data_tg_out = 0U;

    usb_hostchannel_init(pudev, channel_num);

    return (uint8_t)HC_OK;
}

/*!
    \brief      modify a channel
    \param[in]  pudev: pointer to usb device
    \param[in]  channel_num: host channel number which is in (0..7)
    \param[in]  dev_addr: USB Device address allocated to attached device
    \param[in]  dev_speed: USB device speed (full speed / low speed)
    \param[in]  ep_type: endpoint type (bulk/int/ctl)
    \param[in]  ep_mps: max packet size
    \param[out] none
    \retval     operation status
*/
uint8_t usbh_channel_modify (usb_core_handle_struct *pudev,
                             uint8_t  channel_num,
                             uint8_t  dev_addr,
                             uint8_t  dev_speed,
                             uint8_t  ep_type,
                             uint16_t ep_mps)
{
    usb_hostchannel_struct *puhc = &pudev->host.host_channel[channel_num];

    if (0U != dev_addr) {
        puhc->dev_addr = dev_addr;
    }

    if ((puhc->endp_mps != ep_mps) && (0U != ep_mps)) {
        puhc->endp_mps = ep_mps; 
    }

    if ((puhc->dev_speed != dev_speed) && (0U != dev_speed)) {
        puhc->dev_speed = dev_speed;
    }

    usb_hostchannel_init(pudev, channel_num);

    return (uint8_t)HC_OK;
}

/*!
    \brief      allocate a new channel for the pipe
    \param[in]  pudev: pointer to usb device
    \param[in]  ep_addr: endpoint for which the channel to be allocated
    \param[out] none
    \retval     host channel number
*/
uint8_t usbh_channel_alloc (usb_core_handle_struct *pudev, uint8_t ep_addr)
{
    uint16_t hc_num = usbh_freechannel_get(pudev);

    if ((uint16_t)HC_ERROR != hc_num) {
        pudev->host.host_channel[hc_num].info = HC_USED | ep_addr;
    }

    return (uint8_t)hc_num;
}

/*!
    \brief      free the usb host channel
    \param[in]  pudev: pointer to usb device
    \param[in]  index: channel number to be freed  which is in (0..7)
    \param[out] none
    \retval     host operation status
*/
uint8_t usbh_channel_free (usb_core_handle_struct *pudev, uint8_t index)
{
    if (index < HC_MAX) {
        pudev->host.host_channel[index].info &= HC_USED_MASK;
    }

    return USBH_OK;
}

/*!
    \brief      free all usb host channel
    \param[in]  pudev: pointer to usb device
    \param[out] none
    \retval     host operation status
*/
uint8_t usbh_allchannel_dealloc (usb_core_handle_struct *pudev)
{
    uint8_t index;

    for (index = 2U; index < HC_MAX; index ++) {
        pudev->host.host_channel[index].info = 0U;
    }

    return USBH_OK;
}

/*!
    \brief      get a free channel number for allocation to a device endpoint
    \param[in]  pudev: pointer to usb device
    \param[out] none
    \retval     free channel number
*/
static uint16_t usbh_freechannel_get (usb_core_handle_struct *pudev)
{
    uint8_t index = 0U;

    for (index = 0U; index < HC_MAX; index++) {
        if (0U == (pudev->host.host_channel[index].info & HC_USED)) {
            return (uint16_t)index;
        }
    }

    return HC_ERROR;
}

