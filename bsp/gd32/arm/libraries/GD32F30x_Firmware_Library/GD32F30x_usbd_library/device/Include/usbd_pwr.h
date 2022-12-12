/*!
    \file    usbd_pwr.h
    \brief   USB device power management functions prototype

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

#ifndef __USBD_PWR_H
#define __USBD_PWR_H

#include "usbd_core.h"

/* static inline function definitions */
/*!
    \brief      first operation of USB wakeup is to wakeup MCU
    \param[in]  udev: pointer to USB core instance
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void resume_mcu (usb_dev *udev)
{
    udev->drv_handler->suspend_leave();
}

/*!
    \brief      set USB device to suspend mode
    \param[in]  udev: pointer to USB core instance
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usbd_to_suspend (usb_dev *udev)
{
    udev->drv_handler->suspend();
}

/* function declarations */
/* start to remote wakeup */
void usbd_remote_wakeup_active (usb_dev *udev);

#endif /* __USBD_PWR_H */
