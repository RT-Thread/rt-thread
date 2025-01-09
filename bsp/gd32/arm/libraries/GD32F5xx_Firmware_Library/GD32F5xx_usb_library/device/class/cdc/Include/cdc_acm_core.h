/*!
    \file    cdc_acm_core.h
    \brief   the header file of cdc acm driver

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

#ifndef CDC_ACM_CORE_H
#define CDC_ACM_CORE_H

#include "usbd_enum.h"
#include "usb_cdc.h"

#define USB_CDC_RX_LEN      USB_CDC_DATA_PACKET_SIZE                         /*< CDC data packet size */

typedef struct {
    uint8_t data[USB_CDC_RX_LEN];                                            /*< CDC data transfer buff */
    uint8_t cmd[USB_CDC_CMD_PACKET_SIZE];                                    /*< CDC cmd packet buff */

    uint8_t packet_sent;                                                     /*< CDC data packet start send flag */
    uint8_t packet_receive;                                                  /*< CDC data packet start receive flag */
    uint32_t receive_length;                                                 /*< CDC data receive length */

    acm_line line_coding;                                                    /*< CDC line coding structure */
} usb_cdc_handler;

extern usb_desc cdc_desc;
extern usb_class_core cdc_class;

/* function declarations */
/* check CDC ACM is ready for data transfer */
uint8_t cdc_acm_check_ready(usb_dev *udev);
/* send CDC ACM data */
void cdc_acm_data_send(usb_dev *udev);
/* receive CDC ACM data */
void cdc_acm_data_receive(usb_dev *udev);

#endif /* CDC_ACM_CORE_H */
