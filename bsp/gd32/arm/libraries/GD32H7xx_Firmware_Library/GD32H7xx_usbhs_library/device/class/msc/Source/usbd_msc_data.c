/*!
    \file    usbd_msc_data.c
    \brief   USB MSC vital inquiry pages and sense data

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

#include "usbd_msc_data.h"

/* USB mass storage page 0 inquiry data */
const uint8_t msc_page00_inquiry_data[] =
{
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    (INQUIRY_PAGE00_LENGTH - 4U),
    0x80U,
    0x83U,
};

/* USB mass storage sense 6 data */
const uint8_t msc_mode_sense6_data[] =
{
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U
};

/* USB mass storage sense 10 data */
const uint8_t msc_mode_sense10_data[] =
{
    0x00U,
    0x06U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U
};
