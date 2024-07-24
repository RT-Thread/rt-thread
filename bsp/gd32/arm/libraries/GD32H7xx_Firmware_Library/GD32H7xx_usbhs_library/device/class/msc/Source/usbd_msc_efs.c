/*!
    \file    usbh_msc_efs.c
    \brief   this file is the interface between file systems and host MSC class

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
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

#include "efs.h"
#include "usbd_msc_core.h"
#include "usbd_msc_mem.h"
#include "usbd_msc_scsi.h"
#include "usbd_msc_bbb.h"
#include "usbd_msc_efs.h"

/*!
    \brief      initialize the mass storage parameters
    \param[in]  file: file pointer
    \param[in]  opts: optional parameter, not used here
    \param[out] none
    \retval     status: 0(pass), -1(fail)
*/
int8_t if_initInterface(hwInterface* file, char* opts)
{
    file->sectorCount = usbd_mem_fops->mem_block_len[0];

    return(EFS_PASS);
}

/*!
    \brief      read a sector from the disc and store it in a user supplied buffer
    \param[in]  file: file pointer
    \param[in]  address: an LBA address, relative to the beginning of the disc
    \param[in]  buf: buffer where the data will be stored after reading
    \param[out] none
    \retval     status: 0(pass), -1(fail)
*/
int8_t if_readBuf(hwInterface* file, uint32_t address, uint8_t* buf)
{
    int8_t status = EFS_ERROR;

    if (0U == usbd_mem_fops->mem_read(0U, buf, address, 1U))
    {
        status = EFS_PASS;
    }

    return(status);
}

/*!
    \brief      write a sector of data on the disc from a user supplied buffer
    \param[in]  file: file pointer
    \param[in]  address: an LBA address, relative to the beginning of the disc
    \param[in]  buf: buffer where the data will be taken to write
    \param[out] none
    \retval     status: 0(pass), -1(fail)
*/
int8_t if_writeBuf(hwInterface* file, uint32_t address, uint8_t* buf)
{
    int8_t status = EFS_ERROR;

    if (0U == usbd_mem_fops->mem_write(0U, buf, address, 1U))
    {
        status = EFS_PASS;
    }

    return(status);
}
