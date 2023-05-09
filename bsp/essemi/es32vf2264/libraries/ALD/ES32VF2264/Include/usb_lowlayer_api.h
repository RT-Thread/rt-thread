/**
  *********************************************************************************
  *
  * @file    usb_lowlayer_api.h
  * @brief   USB Lower Layer API.
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

#ifndef __USB_LOWLAYER_API_H__
#define __USB_LOWLAYER_API_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "usb_library_config.h"

#if (defined(ES32VF2264) || defined(ES32VF2664))
#ifdef USB_DRIVER_ALD
#include "type.h"
#include "ald_dma.h"
#include "ald_usb.h"
#endif      /*  USB_DRIVER_ALD  */
#endif      /*  defined(ES32VF2264) || defined(ES32VF2664)  */

#if defined (USB_DRIVER_ALD)
/* System functions */
// #if (defined(ES32VF2664) || defined(ES32VF2264))
// #define map_delay_ms                ald_delay_ms
// #define map_dma_handle_t            dma_handle_t
// #define map_dma_config_struct       dma_config_t
// #define EXT_DMA                     DMA
// #define map_dma_config_auto         ald_dma_config_auto
// #define DMA_DATA_DST_INC_NONE       DMA_DATA_INC_NONE
// #define DMA_DATA_DST_INC_BYTE       DMA_DATA_INC_BYTE
// #define DMA_DATA_SRC_INC_NONE       DMA_DATA_INC_NONE
// #define DMA_DATA_SRC_INC_BYTE       DMA_DATA_INC_BYTE
// #else
// #endif
#if (defined(ES32VF2664) || defined(ES32VF2264))
#include "ald_utils.h"
#define map_delay_ms                md_delay_1ms
#define map_dma_handle_t            dma_handle_t
#define map_dma_config_struct       dma_config_t
#define EXT_DMA                     DMA
#define map_dma_config_auto         ald_dma_config_auto
#define DMA_DATA_DST_INC_NONE       DMA_DATA_INC_NONE
#define DMA_DATA_DST_INC_BYTE       DMA_DATA_INC_BYTE
#define DMA_DATA_SRC_INC_NONE       DMA_DATA_INC_NONE
#define DMA_DATA_SRC_INC_BYTE       DMA_DATA_INC_BYTE
#else
#endif
#ifdef ES32VF2664
#undef map_delay_ms
#define map_delay_ms                ald_delay_ms
#endif

/* low level layer init functions */
#define map_usb_host_components_init        ald_usb_host_components_init
#define map_usb_device_components_init      ald_usb_device_components_init

/* Base functions */
#define map_usb_frame_number_get            ald_usb_frame_number_get
#define map_usb_otg_session_request         ald_usb_otg_session_request
#define map_usb_mode_get                    ald_usb_mode_get
#define map_usb_high_speed_enable           ald_usb_high_speed_enable
#define map_usb_device_speed_get            ald_usb_device_speed_get
#define map_usb_num_ep_get                  ald_usb_num_ep_get
#define map_usb_control_reset               ald_usb_control_reset

/* Device functions */
#define map_usb_dev_get_addr                ald_usb_dev_get_addr
#define map_usb_dev_set_addr                ald_usb_dev_set_addr
#define map_usb_dev_connect                 ald_usb_dev_connect
#define map_usb_dev_disconnect              ald_usb_dev_disconnect
#define map_usb_dev_ep_config               ald_usb_dev_ep_config
#define map_usb_dev_ep_get_config           ald_usb_dev_ep_get_config
#define map_usb_dev_ep_data_ack             ald_usb_dev_ep_data_ack
#define map_usb_dev_ep_stall                ald_usb_dev_ep_stall
#define map_usb_dev_ep_stall_clear          ald_usb_dev_ep_stall_clear
#define map_usb_dev_ep_status_clear         ald_usb_dev_ep_status_clear

/* Host functions */
#define map_usb_host_addr_get               ald_usb_host_addr_get
#define map_usb_host_addr_set               ald_usb_host_addr_set
#define map_usb_host_ep_config              ald_usb_host_ep_config
#define map_usb_host_ep_data_ack            ald_usb_host_ep_data_ack
#define map_usb_host_ep_data_toggle         ald_usb_host_ep_data_toggle
#define map_usb_host_ep_status_clear        ald_usb_host_ep_status_clear
#define map_usb_host_hub_addr_get           ald_usb_host_hub_addr_get
#define map_usb_host_hub_addr_set           ald_usb_host_hub_addr_set
#define map_usb_host_pwr_disable            ald_usb_host_pwr_disable
#define map_usb_host_pwr_enable             ald_usb_host_pwr_enable
#define map_usb_host_pwr_config             ald_usb_host_pwr_config
#define map_usb_host_pwr_fault_disable      ald_usb_host_pwr_fault_disable
#define map_usb_host_pwr_fault_enable       ald_usb_host_pwr_fault_enable
#define map_usb_host_request_in             ald_usb_host_request_in
#define map_usb_host_request_in_clear       ald_usb_host_request_in_clear
#define map_usb_host_request_status         ald_usb_host_request_status
#define map_usb_host_reset                  ald_usb_host_reset
#define map_usb_host_resume                 ald_usb_host_resume
#define map_usb_host_suspend                ald_usb_host_suspend
#define map_usb_host_speed_get              ald_usb_host_speed_get
#define map_usb_host_ep_speed_set           ald_usb_host_ep_speed_set
#define map_usb_host_ep_ping                ald_usb_host_ep_ping

/* Endpoint functions */
#define map_usb_ep_data_avail               ald_usb_ep_data_avail
#define map_usb_ep_data_get                 ald_usb_ep_data_get
#define map_usb_ep_data_put                 ald_usb_ep_data_put
#define map_usb_ep_data_send                ald_usb_ep_data_send
#define map_usb_ep_data_toggle_clear        ald_usb_ep_data_toggle_clear
#define map_usb_ep_req_packet_count         ald_usb_ep_req_packet_count
#define map_usb_ep_status                   ald_usb_ep_status
#define map_usb_ep_dma_config               ald_usb_ep_dma_config

/* FIFO functions */
#define map_usb_fifo_addr_get               ald_usb_fifo_addr_get
#define map_usb_fifo_config_get             ald_usb_fifo_config_get
#define map_usb_fifo_config_set             ald_usb_fifo_config_set
#define map_usb_fifo_flush                  ald_usb_fifo_flush

/* Interrupt functions */
#define map_usb_int_disable                 ald_usb_int_disable
#define map_usb_int_enable                  ald_usb_int_enable
#define map_usb_int_status_get              ald_usb_int_status_get
#define map_usb_int_disable_ep              ald_usb_int_disable_ep
#define map_usb_int_enable_ep               ald_usb_int_enable_ep
#define map_usb_int_status_ep_get           ald_usb_int_status_ep_get
#define map_usb_int_register                ald_usb_int_register
#define map_usb_int_unregister              ald_usb_int_unregister
#define map_usb_int_num_get                 ald_usb_int_num_get

/* DMA functions */
#define map_usb_dma_channel_config          ald_usb_dma_channel_config
#define map_usb_dma_mult_recv_start         ald_usb_dma_mult_recv_start
#define map_usb_dma_channel_start           ald_usb_dma_channel_start
#define map_usb_dma_channel_stop            ald_usb_dma_channel_stop
#define map_usb_dma_get_interrupt_flag      ald_usb_dma_get_interrupt_flag
#define map_usb_dma_get_channel_error       ald_usb_dma_get_channel_error
#define map_usb_dma_clear_channel_error     ald_usb_dma_clear_channel_error

/* LPM functions */
#define map_usb_host_lpm_send               ald_usb_host_lpm_send
#define map_usb_host_lpm_config             ald_usb_host_lpm_config
#define map_usb_lpm_remote_wake_is_enable   ald_usb_lpm_remote_wake_is_enable
#define map_usb_host_lpm_resume             ald_usb_host_lpm_resume
#define map_usb_dev_lpm_remote_wake         ald_usb_dev_lpm_remote_wake
#define map_usb_dev_lpm_config              ald_usb_dev_lpm_config
#define map_usb_dev_lpm_enable              ald_usb_dev_lpm_enable
#define map_usb_dev_lpm_disable             ald_usb_dev_lpm_disable
#define map_usb_lpm_link_status_get         ald_usb_lpm_link_status_get
#define map_usb_lpm_ep_get                  ald_usb_lpm_ep_get
#define map_usb_lpm_int_status_get          ald_usb_lpm_int_status_get
#define map_usb_lpm_int_disable             ald_usb_lpm_int_disable
#define map_usb_lpm_int_enable              ald_usb_lpm_int_enable

#elif defined (USB_DRIVER_MD)
#ifdef USE_ASSERT
#define assert_param(x)     \
do {                        \
    if (!(x)) {             \
        __disable_irq();    \
        while (1)           \
            ;               \
    }                       \
} while (0)
#else
#define assert_param(x)
#endif

#define USB_INTCTRL_ALL             0x000003FFU
#define USB_INTCTRL_STATUS          0x000000FFU
#define USB_INTCTRL_VBUS_ERR        0x00000080U
#define USB_INTCTRL_SESSION         0x00000040U
#define USB_INTCTRL_SESSION_END     0x00000040U
#define USB_INTCTRL_DISCONNECT      0x00000020U
#define USB_INTCTRL_CONNECT         0x00000010U
#define USB_INTCTRL_SOF             0x00000008U
#define USB_INTCTRL_BABBLE          0x00000004U
#define USB_INTCTRL_RESET           0x00000004U
#define USB_INTCTRL_RESUME          0x00000002U
#define USB_INTCTRL_SUSPEND         0x00000001U
#define USB_INTCTRL_MODE_DETECT     0x00000200U
#define USB_INTCTRL_POWER_FAULT     0x00000100U

#define USB_INTEP_ALL               0xFFFFFFFFU
#define USB_INTEP_HOST_IN           0xFFFE0000U
#define USB_INTEP_HOST_IN_15        0x80000000U
#define USB_INTEP_HOST_IN_14        0x40000000U
#define USB_INTEP_HOST_IN_13        0x20000000U
#define USB_INTEP_HOST_IN_12        0x10000000U
#define USB_INTEP_HOST_IN_11        0x08000000U
#define USB_INTEP_HOST_IN_10        0x04000000U
#define USB_INTEP_HOST_IN_9         0x02000000U
#define USB_INTEP_HOST_IN_8         0x01000000U
#define USB_INTEP_HOST_IN_7         0x00800000U
#define USB_INTEP_HOST_IN_6         0x00400000U
#define USB_INTEP_HOST_IN_5         0x00200000U
#define USB_INTEP_HOST_IN_4         0x00100000U
#define USB_INTEP_HOST_IN_3         0x00080000U
#define USB_INTEP_HOST_IN_2         0x00040000U
#define USB_INTEP_HOST_IN_1         0x00020000U
#define USB_INTEP_DEV_OUT           0xFFFE0000U
#define USB_INTEP_DEV_OUT_15        0x80000000U
#define USB_INTEP_DEV_OUT_14        0x40000000U
#define USB_INTEP_DEV_OUT_13        0x20000000U
#define USB_INTEP_DEV_OUT_12        0x10000000U
#define USB_INTEP_DEV_OUT_11        0x08000000U
#define USB_INTEP_DEV_OUT_10        0x04000000U
#define USB_INTEP_DEV_OUT_9         0x02000000U
#define USB_INTEP_DEV_OUT_8         0x01000000U
#define USB_INTEP_DEV_OUT_7         0x00800000U
#define USB_INTEP_DEV_OUT_6         0x00400000U
#define USB_INTEP_DEV_OUT_5         0x00200000U
#define USB_INTEP_DEV_OUT_4         0x00100000U
#define USB_INTEP_DEV_OUT_3         0x00080000U
#define USB_INTEP_DEV_OUT_2         0x00040000U
#define USB_INTEP_DEV_OUT_1         0x00020000U
#define USB_INTEP_HOST_OUT          0x0000FFFEU
#define USB_INTEP_HOST_OUT_15       0x00008000U
#define USB_INTEP_HOST_OUT_14       0x00004000U
#define USB_INTEP_HOST_OUT_13       0x00002000U
#define USB_INTEP_HOST_OUT_12       0x00001000U
#define USB_INTEP_HOST_OUT_11       0x00000800U
#define USB_INTEP_HOST_OUT_10       0x00000400U
#define USB_INTEP_HOST_OUT_9        0x00000200U
#define USB_INTEP_HOST_OUT_8        0x00000100U
#define USB_INTEP_HOST_OUT_7        0x00000080U
#define USB_INTEP_HOST_OUT_6        0x00000040U
#define USB_INTEP_HOST_OUT_5        0x00000020U
#define USB_INTEP_HOST_OUT_4        0x00000010U
#define USB_INTEP_HOST_OUT_3        0x00000008U
#define USB_INTEP_HOST_OUT_2        0x00000004U
#define USB_INTEP_HOST_OUT_1        0x00000002U
#define USB_INTEP_DEV_IN            0x0000FFFEU
#define USB_INTEP_DEV_IN_15         0x00008000U
#define USB_INTEP_DEV_IN_14         0x00004000U
#define USB_INTEP_DEV_IN_13         0x00002000U
#define USB_INTEP_DEV_IN_12         0x00001000U
#define USB_INTEP_DEV_IN_11         0x00000800U
#define USB_INTEP_DEV_IN_10         0x00000400U
#define USB_INTEP_DEV_IN_9          0x00000200U
#define USB_INTEP_DEV_IN_8          0x00000100U
#define USB_INTEP_DEV_IN_7          0x00000080U
#define USB_INTEP_DEV_IN_6          0x00000040U
#define USB_INTEP_DEV_IN_5          0x00000020U
#define USB_INTEP_DEV_IN_4          0x00000010U
#define USB_INTEP_DEV_IN_3          0x00000008U
#define USB_INTEP_DEV_IN_2          0x00000004U
#define USB_INTEP_DEV_IN_1          0x00000002U
#define USB_INTEP_0                 0x00000001U

#define USB_UNDEF_SPEED             0x80000000U
#define USB_HIGH_SPEED              0x00000002U
#define USB_FULL_SPEED              0x00000001U
#define USB_LOW_SPEED               0x00000000U

#define USB_HOST_IN_STATUS          0x114F0000U
#define USB_HOST_IN_PID_ERROR       0x10000000U
#define USB_HOST_IN_NOT_COMP        0x01000000U
#define USB_HOST_IN_STALL           0x00400000U
#define USB_HOST_IN_DATA_ERROR      0x00080000U
#define USB_HOST_IN_NAK_TO          0x00080000U
#define USB_HOST_IN_ERROR           0x00040000U
#define USB_HOST_IN_FIFO_FULL       0x00020000U
#define USB_HOST_IN_PKTRDY          0x00010000U
#define USB_HOST_OUT_STATUS         0x000000A7U
#define USB_HOST_OUT_NAK_TO         0x00000080U
#define USB_HOST_OUT_NOT_COMP       0x00000080U
#define USB_HOST_OUT_STALL          0x00000020U
#define USB_HOST_OUT_ERROR          0x00000004U
#define USB_HOST_OUT_FIFO_NE        0x00000002U
#define USB_HOST_OUT_PKTPEND        0x00000001U
#define USB_HOST_EP0_NAK_TO         0x00000080U
#define USB_HOST_EP0_STATUS         0x00000040U
#define USB_HOST_EP0_ERROR          0x00000010U
#define USB_HOST_EP0_RX_STALL       0x00000004U
#define USB_HOST_EP0_RXPKTRDY       0x00000001U
#define USB_DEV_RX_PID_ERROR        0x01000000U
#define USB_DEV_RX_SENT_STALL       0x00400000U
#define USB_DEV_RX_DATA_ERROR       0x00080000U
#define USB_DEV_RX_OVERRUN          0x00040000U
#define USB_DEV_RX_FIFO_FULL        0x00020000U
#define USB_DEV_RX_PKT_RDY          0x00010000U
#define USB_DEV_TX_NOT_COMP         0x00000080U
#define USB_DEV_TX_SENT_STALL       0x00000020U
#define USB_DEV_TX_UNDERRUN         0x00000004U
#define USB_DEV_TX_FIFO_NE          0x00000002U
#define USB_DEV_TX_TXPKTRDY         0x00000001U
#define USB_DEV_EP0_SETUP_END       0x00000010U
#define USB_DEV_EP0_SENT_STALL      0x00000004U
#define USB_DEV_EP0_IN_PKTPEND      0x00000002U
#define USB_DEV_EP0_OUT_PKTRDY      0x00000001U

#define USB_EP_AUTO_SET             0x00000001U
#define USB_EP_AUTO_REQUEST         0x00000002U
#define USB_EP_AUTO_CLEAR           0x00000004U
#define USB_EP_DUAL_BUFFERING       0x00000008U
#define USB_EP_DMA_MODE_0           0x00000008U
#define USB_EP_DMA_MODE_1           0x00000010U
#define USB_EP_DIS_NYET             0x00000020U
#define USB_EP_MODE_ISOC            0x00000000U
#define USB_EP_MODE_BULK            0x00000100U
#define USB_EP_MODE_INT             0x00000200U
#define USB_EP_MODE_CTRL            0x00000300U
#define USB_EP_MODE_MASK            0x00000300U
#define USB_EP_SPEED_LOW            0x00000000U
#define USB_EP_SPEED_FULL           0x00001000U
#define USB_EP_SPEED_HIGH           0x00004000U
#define USB_EP_HOST_IN              0x00000000U
#define USB_EP_HOST_OUT             0x00002000U
#define USB_EP_DEV_IN               0x00002000U
#define USB_EP_DEV_OUT              0x00000000U

#define USB_HOST_PWRFLT_LOW         0x00000010U
#define USB_HOST_PWRFLT_HIGH        0x00000030U
#define USB_HOST_PWRFLT_EP_NONE     0x00000000U
#define USB_HOST_PWRFLT_EP_TRI      0x00000140U
#define USB_HOST_PWRFLT_EP_LOW      0x00000240U
#define USB_HOST_PWRFLT_EP_HIGH     0x00000340U
#define USB_HOST_PWREN_MAN_LOW      0x00000000U
#define USB_HOST_PWREN_MAN_HIGH     0x00000001U
#define USB_HOST_PWREN_AUTOLOW      0x00000002U
#define USB_HOST_PWREN_AUTOHIGH     0x00000003U
#define USB_HOST_PWREN_FILTER       0x00010000U

#define USB_HOST_LPM_RMTWAKE        0x00000100U
#define USB_HOST_LPM_L1             0x00000001U

#define USB_DEV_LPM_NAK             0x00000010U
#define USB_DEV_LPM_NONE            0x00000000U
#define USB_DEV_LPM_EN              0x0000000cU
#define USB_DEV_LPM_EXTONLY         0x00000004U

#define USB_DEV_LPM_LS_RMTWAKE      0x00000100U
#define USB_DEV_LPM_LS_L1           0x00000001U

#define USB_INTLPM_ERROR            0x00000020U
#define USB_INTLPM_RESUME           0x00000010U
#define USB_INTLPM_INCOMPLETE       0x00000008U
#define USB_INTLPM_ACK              0x00000004U
#define USB_INTLPM_NYET             0x00000002U
#define USB_INTLPM_STALL            0x00000001U

#define USB_CLOCK_INTERNAL          0x00000200U
#define USB_CLOCK_EXTERNAL          0x00000300U

#define USB_ULPI_EXTVBUS            0x00000001U
#define USB_ULPI_EXTVBUS_IND        0x00000002U

#define MAX_NAK_LIMIT               31U
#define DISABLE_NAK_LIMIT           0U

#define MAX_PACKET_SIZE_EP0         64U

#define USB_EP_0                0x00000000U
#define USB_EP_1                0x00000010U
#define USB_EP_2                0x00000020U
#define USB_EP_3                0x00000030U
#define USB_EP_4                0x00000040U
#define USB_EP_5                0x00000050U
#define USB_EP_6                0x00000060U
#define USB_EP_7                0x00000070U
#define NUM_USB_EP              8U

#define IndexToUSBEP(x)         ((x) << 4)
#define USBEPToIndex(x)         ((x) >> 4)

#define USB_FIFO_SZ_8           0x00000000U
#define USB_FIFO_SZ_16          0x00000001U
#define USB_FIFO_SZ_32          0x00000002U
#define USB_FIFO_SZ_64          0x00000003U
#define USB_FIFO_SZ_128         0x00000004U
#define USB_FIFO_SZ_256         0x00000005U
#define USB_FIFO_SZ_512         0x00000006U
#define USB_FIFO_SZ_1024        0x00000007U
#define USB_FIFO_SZ_2048        0x00000008U
#define USBFIFOSizeToBytes(x)   (8U << (x))

#define USB_TRANS_OUT           0x00000102U
#define USB_TRANS_IN            0x00000102U
#define USB_TRANS_IN_LAST       0x0000010aU
#define USB_TRANS_SETUP         0x0000110aU
#define USB_TRANS_STATUS        0x00000142U

#define USB_DUAL_MODE_HOST      0x00000001U
#define USB_DUAL_MODE_DEVICE    0x00000081U
#define USB_DUAL_MODE_NONE      0x00000080U
#define USB_OTG_MODE_ASIDE_HOST 0x0000001dU
#define USB_OTG_MODE_ASIDE_NPWR 0x00000001U
#define USB_OTG_MODE_ASIDE_SESS 0x00000009U
#define USB_OTG_MODE_ASIDE_AVAL 0x00000011U
#define USB_OTG_MODE_ASIDE_DEV  0x00000019U
#define USB_OTG_MODE_BSIDE_HOST 0x0000009dU
#define USB_OTG_MODE_BSIDE_DEV  0x00000099U
#define USB_OTG_MODE_BSIDE_NPWR 0x00000081U
#define USB_OTG_MODE_NONE       0x00000080U

#define DMA_DST_INC_8           0x00000000U
#define DMA_DST_INC_16          0x40000000U
#define DMA_DST_INC_32          0x80000000U
#define DMA_DST_INC_NONE        0xc0000000U
#define DMA_SRC_INC_8           0x00000000U
#define DMA_SRC_INC_16          0x04000000U
#define DMA_SRC_INC_32          0x08000000U
#define DMA_SRC_INC_NONE        0x0c000000U
#define DMA_SIZE_8              0x00000000U
#define DMA_SIZE_16             0x11000000U
#define DMA_SIZE_32             0x22000000U
#define DMA_DST_PROT_PRIV       0x00200000U
#define DMA_SRC_PROT_PRIV       0x00040000U
#define DMA_ARB_1               0x00000000U
#define DMA_ARB_2               0x00004000U
#define DMA_ARB_4               0x00008000U
#define DMA_ARB_8               0x0000c000U
#define DMA_ARB_16              0x00010000U
#define DMA_ARB_32              0x00014000U
#define DMA_ARB_64              0x00018000U
#define DMA_ARB_128             0x0001c000U
#define DMA_ARB_256             0x00020000U
#define DMA_ARB_512             0x00024000U
#define DMA_ARB_1024            0x00028000U
#define DMA_NEXT_USEBURST       0x00000008U
#define USB_DMA_INT_CH8         0x00000080U
#define USB_DMA_INT_CH7         0x00000040U
#define USB_DMA_INT_CH6         0x00000020U
#define USB_DMA_INT_CH5         0x00000010U
#define USB_DMA_INT_CH4         0x00000008U
#define USB_DMA_INT_CH3         0x00000004U
#define USB_DMA_INT_CH2         0x00000002U
#define USB_DMA_INT_CH1         0x00000001U
#define USB_DMA_STATUS_ERROR    0x00000100U
#define USB_DMA_CFG_BURST_NONE  0x00000000U
#define USB_DMA_CFG_BURST_4     0x00000200U
#define USB_DMA_CFG_BURST_8     0x00000400U
#define USB_DMA_CFG_BURST_16    0x00000600U
#define USB_DMA_CFG_INT_EN      0x00000008U
#define USB_DMA_CFG_MODE_0      0x00000000U
#define USB_DMA_CFG_MODE_1      0x00000004U
#define USB_DMA_CFG_DIR_RX      0x00000000U
#define USB_DMA_CFG_DIR_TX      0x00000002U
#define USB_DMA_CFG_EN          0x00000001U
#define USB_MODE_HOST_VBUS      0x00000004U
#define USB_MODE_HOST           0x00000002U
#define USB_MODE_DEV_VBUS       0x00000005U
#define USB_MODE_DEV            0x00000003U
#define USB_MODE_OTG            0x00000000U
#define DMA_ATTR_USEBURST       0x00000001U
#define DMA_ATTR_ALTSELECT      0x00000002U
#define DMA_ATTR_HIGH_PRIORITY  0x00000004U
#define DMA_ATTR_REQMASK        0x00000008U
#define DMA_ATTR_ALL            0x0000000FU
#define USB_DMA_EP_CFG_TX       0x00000001U
#define USB_DMA_EP_CFG_RX_DEV   0x00000002U
#define USB_DMA_EP_CFG_RX_HOST  0x00000004U
#define USB_DMA_EP_TX_MSK       0x94U
#define USB_DMA_EP_RX_DEV_MSK   0xA8U
#define USB_DMA_EP_RX_HOST_MSK  0xE8U

#else

/* System API */
#define map_usb_re_config           md_usb_re_config
#define map_delay_ms                md_usb_system_delayms
#define map_usb_controller_reset    md_usb_controller_reset
#define map_usb_control_reset       md_usb_controller_reset
#define map_usb_controller_enable   md_usb_controller_enable
#define map_usb_controller_disable  md_usb_controller_disable
#define map_usb_clk_phy_enable      md_usb_clk_phy_enable
#define map_usb_clk_phy_disable     md_usb_clk_phy_disable
#define map_usb_int_num_get         md_usb_nvic_number_get
#define map_usb_int_register        md_usb_nvic_enable
#define map_usb_int_unregister      md_usb_nvic_disable

/* DMA API */
#define EXT_DMA                     DMA
#define DMA_DATA_DST_INC_NONE       ALD_DMA_DATA_DINC_DISABLE
#define DMA_DATA_DST_INC_BYTE       ALD_DMA_DATA_DINC_ENABLE
#define DMA_DATA_SRC_INC_NONE       ALD_DMA_DATA_SINC_DISABLE
#define DMA_DATA_SRC_INC_BYTE       ALD_DMA_DATA_SINC_ENABLE
#define map_dma_handle_t            ald_dma_handle_t
#define map_dma_config_struct       ald_dma_deinit_struct
#define map_dma_config_basic        ald_dma_config_basic

/* USB Base API */
/* Host Mode */
#define map_usb_host_reset              md_usb_hos_reset
#define map_usb_host_resume             md_usb_hos_resume
#define map_usb_host_suspend            md_usb_hos_suspend
#define map_usb_host_request_status     md_usb_hos_request_status
#define map_usb_host_request_in         md_usb_hos_request_in
#define map_usb_host_request_in_clear   md_usb_hos_request_in_clear
#define map_usb_host_speed_get          md_usb_hos_speed_get
#define map_usb_host_addr_get           md_usb_hos_addr_get
#define map_usb_host_addr_set           md_usb_hos_addr_set
#define map_usb_host_hub_addr_get       md_usb_hos_hub_addr_get
#define map_usb_host_hub_addr_set       md_usb_hos_hub_addr_set
/* Device Mode */
#define map_usb_dev_set_addr            md_usb_dev_addr_set
#define map_usb_dev_get_addr            md_usb_dev_addr_get
#define map_usb_dev_connect             md_usb_dev_connect
#define map_usb_dev_disconnect          md_usb_dev_disconnect
/* Host/Device Mode */
#define map_usb_frame_number_get        md_usb_hosdev_frame_get
#define map_usb_int_disable             md_usb_hosdev_int_disable
#define map_usb_int_enable              md_usb_hosdev_int_enable
#define map_usb_int_status_get          md_usb_hosdev_int_status
#define map_usb_mode_get                md_usb_hosdev_mode_get
/* otg Mode */
#define map_usb_otg_session_request     md_usb_otg_session_request
#define map_usb_mode_force_host         md_usb_force_host_mode
#define map_usb_mode_force_device       md_usb_force_device_mode
#define map_usb_mode_force_otg          md_usb_force_otg_mode
#define map_usb_mode_config             md_usb_mode_config

/* USB Endpoint API */
/* Host Mode */
#define map_usb_host_ep_config          md_usb_hos_endpoint_config_set
#define map_usb_host_ep_data_ack        md_usb_hos_endpoint_data_ack
#define map_usb_host_ep_data_toggle     md_usb_hos_endpoint_data_toggle
#define map_usb_host_ep_status_clear    md_usb_hos_endpoint_status_clear
#define map_usb_host_ep_speed_set       md_usb_hos_endpoint_speed
#define map_usb_host_ep_ping            md_usb_hos_endpoint_ping
/* Device Mode */
#define map_usb_dev_ep_config           md_usb_dev_endpoint_config_set
#define map_usb_dev_ep_get_config       md_usb_dev_endpoint_config_get
#define map_usb_dev_ep_data_ack         md_usb_dev_endpoint_ack
#define map_usb_dev_ep_stall            md_usb_dev_endpoint_stall
#define map_usb_dev_ep_stall_clear      md_usb_dev_endpoint_stall_clear
#define map_usb_dev_ep_status_clear     md_usb_dev_endpoint_status_clear
/* Host/Device Mode */
#define map_usb_ep_data_avail           md_usb_hosdev_endpoint_datavai
#define map_usb_ep_data_get             md_usb_hosdev_endpoint_data_get
#define map_usb_ep_data_put             md_usb_hosdev_endpoint_data_put
#define map_usb_ep_data_send            md_usb_hosdev_endpoint_data_send
#define map_usb_ep_data_toggle_clear    md_usb_hosdev_endpoint_data_togglec
#define map_usb_ep_req_packet_count     md_usb_hosdev_endpoint_pkcount_set
#define map_usb_ep_status               md_usb_hosdev_endpoint_status
#define map_usb_int_disable_ep          md_usb_hosdev_endpoint_int_disable
#define map_usb_int_enable_ep           md_usb_hosdev_endpoint_int_enable
#define map_usb_int_status_ep_get       md_usb_hosdev_endpoint_int_status
#define map_usb_num_ep_get              md_usb_endpoint_number_get

/* USB FIFO API */
#define map_usb_fifo_addr_get           md_usb_hosdev_fifo_addr_get
#define map_usb_fifo_config_get         md_usb_hosdev_fifo_config_get
#define map_usb_fifo_config_set         md_usb_hosdev_fifo_config_set
#define map_usb_fifo_flush              md_usb_hosdev_fifo_flush

/* Not Support API By USB_DRIVER_MD */
#define map_usb_host_pwr_disable            md_usb_hos_pwr_disable
#define map_usb_host_pwr_enable             md_usb_hos_pwr_enable
#define map_usb_host_pwr_config             md_usb_hos_pwr_config
#define map_usb_host_pwr_fault_disabl       md_usb_hos_pwrfault_disable
#define map_usb_host_pwr_fault_enable       md_usb_hos_pwrfault_enable
#define map_usb_host_lpm_send               md_usb_hos_lpm_send
#define map_usb_host_lpm_config             md_usb_hos_lpm_config
#define map_usb_lpm_remote_wake_is_enable   md_usb_lpm_remotewake_is_enabled
#define map_usb_host_lpm_resume             md_usb_hos_lpm_resume
#define map_usb_dev_lpm_remote_wake         md_usb_dev_lpm_remotewake
#define map_usb_dev_lpm_config              md_usb_dev_lpm_config
#define map_usb_dev_lpm_enable              md_usb_dev_lpm_enable
#define map_usb_dev_lpm_disable             md_usb_dev_lpm_disable
#define map_usb_lpm_link_status_get         md_usb_lpm_link_state_get
#define map_usb_lpm_ep_get                  md_usb_lpm_endpoint_get
#define map_usb_lpm_int_status_get          md_usb_lpm_status
#define map_usb_lpm_int_disable             md_usb_lpm_int_disable
#define map_usb_lpm_int_enable              md_usb_lpm_int_enable
#define map_usb_dma_channel_config          md_usb_dma_channel_config
#define map_usb_dma_mult_recv_start         md_usb_dma_mult_recv_start
#define map_usb_dma_channel_start           md_usb_dma_channel_start
#define map_usb_dma_channel_stop            md_usb_dma_channel_stop
#define map_usb_dma_get_interrupt_flag      md_usb_dma_get_interrupt_flag
#define map_usb_dma_get_channel_error       md_usb_dma_get_channel_error
#define map_usb_dma_clear_channel_error     md_usb_dma_clear_channel_error
#define map_usb_ep_dma_config               md_usb_ep_dma_config


/* SYSTEM API. */
extern void     md_usb_system_int_disable(void);
extern void     md_usb_system_int_enable(void);
extern void     md_usb_re_config(bool Device);  /* Weak defination */
extern void     md_usb_system_delayms(uint32_t delayms);  /* Weak defination */
extern void     md_usb_systic_disable(void);
extern void     md_usb_controller_reset(void);
extern void     md_usb_controller_enable(void);
extern void     md_usb_controller_disable(void);
extern void     md_usb_clk_phy_enable(void);
extern void     md_usb_clk_phy_disable(void);
extern uint32_t md_usb_nvic_number_get(void);
extern void     md_usb_nvic_config(uint32_t NvicNum);  /* Weak defination */
extern void     md_usb_nvic_enable(void);
extern void     md_usb_nvic_disable(void);

/* USB basic API */
/* Host Mode */
extern void     md_usb_hos_reset(bool bStart);
extern void     md_usb_hos_resume(bool bStart);
extern void     md_usb_hos_suspend(void);
extern void     md_usb_hos_request_status(void);
extern void     md_usb_hos_request_in(uint32_t ui32Endpoint);
extern void     md_usb_hos_request_in_clear(uint32_t ui32Endpoint);
extern uint32_t md_usb_hos_speed_get(void);
extern uint32_t md_usb_hos_addr_get(uint32_t ui32Endpoint, uint32_t ui32Flags);
extern void     md_usb_hos_addr_set(uint32_t ui32Endpoint,
                                    uint32_t ui32Addr,
                                    uint32_t ui32Flags);
extern uint32_t md_usb_hos_hub_addr_get(uint32_t ui32Endpoint,
                                        uint32_t ui32Flags);
extern void     md_usb_hos_hub_addr_set(uint32_t ui32Endpoint,
                                        uint32_t ui32Addr,
                                        uint32_t ui32Flags);
/* Device Mode */
extern void     md_usb_dev_addr_set(uint8_t ui32Address);
extern uint8_t  md_usb_dev_addr_get(void);
extern void     md_usb_dev_connect(void);
extern void     md_usb_dev_disconnect(void);
extern uint32_t md_usb_dev_speed_get(void);
/* Host/Device Mode */
extern uint32_t md_usb_hosdev_frame_get(void);
extern void     md_usb_hosdev_int_disable(uint32_t ui32IntFlags);
extern void     md_usb_hosdev_int_enable(uint32_t ui32IntFlags);
extern uint32_t md_usb_hosdev_int_status(void);
extern uint32_t md_usb_hosdev_mode_get(void);
/* otg Mode */
extern void     md_usb_otg_session_request(bool bStart);
extern void     md_usb_force_host_mode(void);
extern void     md_usb_force_device_mode(void);
extern void     md_usb_force_otg_mode(void);
extern void     md_usb_mode_config(uint32_t ui32Mode);

/* USB endpoint API */
/* Host Mode */
extern void     md_usb_hos_endpoint_config_set(uint32_t ui32Endpoint,
                                                uint32_t ui32MaxPacketSize,
                                                uint32_t ui32NAKPollInterval,
                                                uint32_t ui32TargetEndpoint,
                                                uint32_t ui32Flags);
extern void     md_usb_hos_endpoint_data_ack(uint32_t ui32Endpoint);
extern void     md_usb_hos_endpoint_data_toggle(uint32_t ui32Endpoint, bool bDataToggle, uint32_t ui32Flags);
extern void     md_usb_hos_endpoint_status_clear(uint32_t ui32Endpoint, uint32_t ui32Flags);
extern void     md_usb_hos_endpoint_speed(uint32_t ui32Endpoint, uint32_t ui32Flags);
extern void     md_usb_hos_endpoint_ping(uint32_t ui32Endpoint, bool bEnable);
/* Device Mode */
extern void     md_usb_dev_endpoint_config_set(uint32_t ui32Endpoint, uint32_t ui32MaxPacketSize, uint32_t ui32Flags);
extern void     md_usb_dev_endpoint_config_get(uint32_t ui32Endpoint, uint32_t *pui32MaxPacketSize, uint32_t *pui32Flags);
extern void     md_usb_dev_endpoint_ack(uint32_t ui32Endpoint, bool bIsLastPacket);
extern void     md_usb_dev_endpoint_stall(uint32_t ui32Endpoint, uint32_t ui32Flags);
extern void     md_usb_dev_endpoint_stall_clear(uint32_t ui32Endpoint, uint32_t ui32Flags);
extern void     md_usb_dev_endpoint_status_clear(uint32_t ui32Endpoint, uint32_t ui32Flags);
/* Host/Device Mode */
extern uint32_t md_usb_hosdev_endpoint_datavai(uint32_t ui32Endpoint);
extern int32_t  md_usb_hosdev_endpoint_data_get(uint32_t ui32Endpoint, uint8_t *pui8Data, uint32_t *pui32Size);
extern int32_t  md_usb_hosdev_endpoint_data_put(uint32_t ui32Endpoint, uint8_t *pui8Data, uint32_t ui32Size);
extern int32_t  md_usb_hosdev_endpoint_data_send(uint32_t ui32Endpoint, uint32_t ui32TransType);
extern void     md_usb_hosdev_endpoint_data_togglec(uint32_t ui32Endpoint, uint32_t ui32Flags);
extern void     md_usb_hosdev_endpoint_pkcount_set(uint32_t ui32Endpoint, uint32_t ui32Count);
extern uint32_t md_usb_hosdev_endpoint_status(uint32_t ui32Endpoint);
extern void     md_usb_hosdev_endpoint_int_disable(uint32_t ui32IntFlags);
extern void     md_usb_hosdev_endpoint_int_enable(uint32_t ui32IntFlags);
extern uint32_t md_usb_hosdev_endpoint_int_status(void);
extern uint32_t md_usb_endpoint_number_get(void);

/* USB FIFO API.*/
extern uint32_t md_usb_hosdev_fifo_addr_get(uint32_t ui32Endpoint);
extern void     md_usb_hosdev_fifo_config_get(uint32_t ui32Endpoint, uint32_t *pui32FIFOAddress, uint32_t *pui32FIFOSize, uint32_t ui32Flags);
extern void     md_usb_hosdev_fifo_config_set(uint32_t ui32Endpoint, uint32_t ui32FIFOAddress, uint32_t ui32FIFOSize, uint32_t ui32Flags);
extern void     md_usb_hosdev_fifo_flush(uint32_t ui32Endpoint, uint32_t ui32Flags);

/* Not Support API By USB_DRIVER_MD */
extern void     md_usb_hos_pwr_disable(void);
extern void     md_usb_hos_pwr_enable(void);
extern void     md_usb_hos_pwr_config(uint32_t ui32Flags);
extern void     md_usb_hos_pwrfault_disable(void);
extern void     md_usb_hos_pwrfault_enable(void);
extern void     md_usb_hos_lpm_send(uint32_t ui32Address, uint32_t uiEndpoint);
extern void     md_usb_hos_lpm_config(uint32_t ui32ResumeTime, uint32_t ui32Config);
extern bool     md_usb_lpm_remotewake_is_enabled(void);
extern void     md_usb_hos_lpm_resume(void);
extern void     md_usb_dev_lpm_remotewake(void);
extern void     md_usb_dev_lpm_config(uint32_t ui32Config);
extern void     md_usb_dev_lpm_enable(void);
extern void     md_usb_dev_lpm_disable(void);
extern uint32_t md_usb_lpm_link_state_get(void);
extern uint32_t md_usb_lpm_endpoint_get(void);
extern uint32_t md_usb_lpm_status(void);
extern void     md_usb_lpm_int_disable(uint32_t ui32Ints);
extern void     md_usb_lpm_int_enable(uint32_t ui32Ints);
/* DMA functions */
extern void     md_usb_dma_channel_config(uint8_t ch, uint32_t addr, uint32_t count, uint32_t ctrl);
extern void     md_usb_dma_mult_recv_start(uint32_t ep_idx);
extern void     md_usb_dma_channel_start(uint8_t ch);
extern void     md_usb_dma_channel_stop(uint8_t ch);
extern uint32_t md_usb_dma_get_interrupt_flag(void);
extern uint32_t md_usb_dma_get_channel_error(uint8_t ch);
extern void     md_usb_dma_clear_channel_error(uint8_t ch);
extern void     md_usb_ep_dma_config(uint32_t ep_idx, uint32_t flag, uint8_t en);

#endif

#ifdef __cplusplus
}
#endif

#endif
