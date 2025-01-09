/*!
    \file    usbd_msc_scsi.h
    \brief   the header file of the usbd_msc_scsi.c file

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

#ifndef USBD_MSC_SCSI_H
#define USBD_MSC_SCSI_H

#include "usbd_core.h"

#define SENSE_LIST_DEEPTH                           4U                   /*!< sense list deepth */

#define MODE_SENSE6_LENGTH                          8U                   /*!< sense6 mode length */
#define MODE_SENSE10_LENGTH                         8U                   /*!< sense10 mode length */
#define INQUIRY_PAGE00_LENGTH                       96U                  /*!< sense page 0 inquiry length */
#define FORMAT_CAPACITIES_LENGTH                    20U                  /*!< format capacities length */

/* function declarations */
/* process SCSI commands */
int8_t scsi_process_cmd(usb_core_driver *udev, uint8_t lun, uint8_t *cmd);
/* load the last error code in the error list */
void scsi_sense_code(usb_core_driver *udev, uint8_t lun, uint8_t skey, uint8_t asc);

#endif /* USBD_MSC_SCSI_H */
