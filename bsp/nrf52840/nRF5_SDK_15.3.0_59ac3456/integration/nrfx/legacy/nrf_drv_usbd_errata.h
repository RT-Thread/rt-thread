/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef NRF_DRV_USBD_ERRATA_H__
#define NRF_DRV_USBD_ERRATA_H__

#include "nrfx.h"

#ifndef NRFX_USBD_ERRATA_ENABLE
 #ifdef NRF_DRV_USBD_ERRATA_ENABLE
  #define NRFX_USBD_ERRATA_ENABLE NRF_DRV_USBD_ERRATA_ENABLE
 #endif
#endif

#include "../src/nrfx_usbd_errata.h"

#ifndef NRF_DRV_USBD_ERRATA_ENABLE
#define NRF_DRV_USBD_ERRATA_ENABLE NRFX_USBD_ERRATA_ENABLE
#endif

#define nrf_drv_usbd_errata_type_52840 			nrfx_usbd_errata_type_52840
#define nrf_drv_usbd_errata_type_52840_proto1	nrfx_usbd_errata_type_52840_proto1
#define nrf_drv_usbd_errata_type_52840_fp1		nrfx_usbd_errata_type_52840_fp1
#define nrf_drv_usbd_errata_type_52840_fp2		nrfx_usbd_errata_type_52840_fp2
#define nrf_drv_usbd_errata_104					nrfx_usbd_errata_104
#define nrf_drv_usbd_errata_154					nrfx_usbd_errata_154
#define nrf_drv_usbd_errata_166					nrfx_usbd_errata_166
#define nrf_drv_usbd_errata_171					nrfx_usbd_errata_171
#define nrf_drv_usbd_errata_187					nrfx_usbd_errata_187
#define nrf_drv_usbd_errata_sizeepout_rw		nrfx_usbd_errata_sizeepout_rw
#define nrf_drv_usb_errata_199					nrfx_usb_errata_199

#endif /* NRF_DRV_USBD_ERRATA_H__ */
