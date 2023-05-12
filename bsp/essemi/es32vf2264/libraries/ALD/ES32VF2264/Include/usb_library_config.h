/**
  *********************************************************************************
  *
  * @file    usb_library_config.h
  * @brief   USB Library configure.
  *
  * @version V1.0
  * @date    12 Nov 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          12 Nov 2019     AE Team         The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  * THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
  * NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
  * NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  * A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. EASTSOFT SHALL NOT, UNDER ANY
  * CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
  * DAMAGES, FOR ANY REASON WHATSOEVER.
  *
  *********************************************************************************
  */

#ifndef __USB_LIBRARY_CONFIG_H__
#define __USB_LIBRARY_CONFIG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#undef USB_DEBUG
#define USB_DEBUG


#if (defined(ES32VF2664) || defined(ES32VF2264) )
#define USB_DMA_N_SUPPORT   /* USB Built-in DMA is not supported, using external DMA automatic */
#define USB_DRIVER_ALD
#endif


//#define USB_DEBUG

/* USB Device Endpoints Assignment */
#define AUDIO_EP_OUT        USB_EP_1
#define BULK_EP_IN          USB_EP_1
#define BULK_EP_OUT         USB_EP_1
#define CDC0_EP_CTRL        USB_EP_1
#define CDC0_EP_IN          USB_EP_2
#define CDC0_EP_OUT         USB_EP_2
#define CDC1_EP_CTRL        USB_EP_3
#define CDC1_EP_IN          USB_EP_4
#define CDC1_EP_OUT         USB_EP_4
#define HID_GAME_EP_IN      USB_EP_1
#define HID_KEYB_EP_IN      USB_EP_2
#define HID_KEYB_EP_OUT     USB_EP_2
#define HID_MOUSE_EP_IN     USB_EP_1
#define MSC_EP_IN           USB_EP_1
#define MSC_EP_OUT          USB_EP_1
#define PRINTER_EP_IN       USB_EP_2
#define PRINTER_EP_OUT      USB_EP_2

/* USB External DMA Channel Assignment */
#if defined(ES32VF2264) || defined(ES32VF2664)
#define USBD_E_DMA_MSC_TX_CH    3
#define USBD_E_DMA_MSC_RX_CH    4
#define USBD_E_DMA_AUDIO_RX_CH  5
#define USBD_E_DMA_BULK_TX_CH   3
#define USBD_E_DMA_BULK_RX_CH   4
#endif


#ifdef __cplusplus
}
#endif

#endif
