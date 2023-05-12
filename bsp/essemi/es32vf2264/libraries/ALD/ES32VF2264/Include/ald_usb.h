/**
  *********************************************************************************
  *
  * @file    ald_usb.h
  * @brief   Header file of USB module driver.
  *
  * @version V1.0
  * @date    25 Feb. 2022
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          25 Feb. 2022    AE Team         The first version
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
  **********************************************************************************
  */

#ifndef __ALD_USB_H__
#define __ALD_USB_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include "ald_utils.h"
#include "ald_dma.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup USB
  * @{
  */

/** @defgroup USB_Public_Macros USB Public Macros
  * @{
  */
/*  Power  */
#define ALD_USB_POWER_RESET                 0x00000008U
#define ALD_USB_POWER_RESUME                0x00000004U
#define ALD_USB_POWER_SUSPEND               0x00000002U
#define ALD_USB_POWER_ISOUDT                0x00000080U
#define ALD_USB_POWER_SUSPENDEN             0x00000001U

/*  DPDMCON  */
#define ALD_USB_DPDMCON_DPPUD               0x00000018U
#define ALD_USB_DPDMCON_DPPUD_FLOAT         0x00000000U
#define ALD_USB_DPDMCON_DPPUD_UP            0x00000008U
#define ALD_USB_DPDMCON_DPPUD_DOWN          0x00000010U
#define ALD_USB_DPDMCON_DMPUD               0x00000006U
#define ALD_USB_DPDMCON_DMPUD_FLOAT         0x00000000U
#define ALD_USB_DPDMCON_DMPUD_UP            0x00000002U
#define ALD_USB_DPDMCON_DMPUD_DOWN          0x00000004U
#define ALD_USB_DPDMCON_PHYPWREN            0x00000001U

/*  SWCID  */
#define ALD_USB_SWCID_HOST                  0x00000002U
#define ALD_USB_SWCID_CIDCTRL               0x00000001U

/*  SWVBUS  */
#define ALD_USB_SWVBUS_VALTH                0x00000008U
#define ALD_USB_SWVBUS_SESVALTH             0x00000004U
#define ALD_USB_SWVBUS_SESENDTH             0x00000002U
#define ALD_USB_SWVBUS_SIGCTRL              0x00000001U

/*  SWTMODE  */
#define ALD_USB_SWTMODE_EN                  0x00000001U

/*  DEVCON  */
#define ALD_USB_DEVCON_FSDEV                0x00000040U
#define ALD_USB_DEVCON_LSDEV                0x00000020U
#define ALD_USB_DEVCON_HOST                 0x00000004U
#define ALD_USB_DEVCON_HOSTREQ              0x00000002U
#define ALD_USB_DEVCON_SESSION              0x00000001U

/*  CSR0L_TXCSRL  */
#define ALD_USB_CSR0L_NAKTO                 0x00000080U
#define ALD_USB_CSR0L_STATUSPKT             0x00000040U
#define ALD_USB_CSR0L_REQPKT                0x00000020U
#define ALD_USB_CSR0L_ERROR                 0x00000010U
#define ALD_USB_CSR0L_SETUPPKT              0x00000008U
#define ALD_USB_CSR0L_STALLED               0x00000004U
#define ALD_USB_CSR0L_TXRDY                 0x00000002U
#define ALD_USB_CSR0L_RXRDY                 0x00000001U

#define ALD_USB_CSR0L_SETENDC               0x00000080U
#define ALD_USB_CSR0L_RXRDYC                0x00000040U
#define ALD_USB_CSR0L_STALL                 0x00000020U
#define ALD_USB_CSR0L_SETEND                0x00000010U
#define ALD_USB_CSR0L_DATAEND               0x00000008U

#define ALD_USB_TXCSRL_NAKTO                0x00000080U
#define ALD_USB_TXCSRL_CLRDT                0x00000040U
#define ALD_USB_TXCSRL_STALLED              0x00000020U
#define ALD_USB_TXCSRL_FLUSH                0x00000008U
#define ALD_USB_TXCSRL_ERROR                0x00000004U
#define ALD_USB_TXCSRL_FIFONE               0x00000002U
#define ALD_USB_TXCSRL_TXRDY                0x00000001U

#define ALD_USB_TXCSRL_STALL                0x00000010U
#define ALD_USB_TXCSRL_UNDRUN               0x00000004U

/*  CSR0H_TXCSRH  */
#define ALD_USB_CSR0H_FLUSH                 0x00000001U

#define ALD_USB_TXCSRH_AUTOSET              0x00000080U
#define ALD_USB_TXCSRH_ISO                  0x00000040U
#define ALD_USB_TXCSRH_MODE                 0x00000020U
#define ALD_USB_TXCSRH_FDT                  0x00000008U

/*  RXCSRL  */
#define ALD_USB_RXCSRL_CLRDT                0x00000080U
#define ALD_USB_RXCSRL_STALLED              0x00000040U
#define ALD_USB_RXCSRL_REQPKT               0x00000020U
#define ALD_USB_RXCSRL_FLUSH                0x00000010U
#define ALD_USB_RXCSRL_DATAERR_NAKTO        0x00000008U
#define ALD_USB_RXCSRL_ERROR                0x00000004U
#define ALD_USB_RXCSRL_FULL                 0x00000002U
#define ALD_USB_RXCSRL_RXRDY                0x00000001U

#define ALD_USB_RXCSRL_STALL                0x00000020U
#define ALD_USB_RXCSRL_DATAERR              0x00000008U
#define ALD_USB_RXCSRL_OVERRUN              0x00000004U

/*  RXCSRH  */
#define ALD_USB_RXCSRL_AUTOCLR              0x00000080U
#define ALD_USB_RXCSRL_AUTOREQ              0x00000040U

#define ALD_USB_RXCSRL_ISO                  0x00000040U

/*  TXTYPE  */
#define ALD_USB_TXTYPE_PROTOCOL             0x00000030U
#define ALD_USB_TXTYPE1_PROTOCOL_CTRL       0x00000000U
#define ALD_USB_TXTYPE_PROTOCOL_ISO         0x00000010U
#define ALD_USB_TXTYPE_PROTOCOL_BULK        0x00000020U
#define ALD_USB_TXTYPE_PROTOCOL_INT         0x00000030U
#define ALD_USB_TXTYPE_TEPN_1               0x00000001U
#define ALD_USB_TXTYPE_TEPN_2               0x00000002U
#define ALD_USB_TXTYPE_TEPN_3               0x00000003U
#define ALD_USB_TXTYPE_TEPN_4               0x00000004U
#define ALD_USB_TXTYPE_TEPN_5               0x00000005U
#define ALD_USB_TXTYPE_TEPN_6               0x00000006U

/*  RXTYPE  */
#define ALD_USB_RXTYPE_PROTOCOL_ISO         0x00000010U
#define ALD_USB_RXTYPE_PROTOCOL_BULK        0x00000020U
#define ALD_USB_RXTYPE_PROTOCOL_INT         0x00000030U
#define ALD_USB_RXTYPE_TEPN_1               0x00000001U
#define ALD_USB_RXTYPE_TEPN_2               0x00000002U
#define ALD_USB_RXTYPE_TEPN_3               0x00000003U
#define ALD_USB_RXTYPE_TEPN_4               0x00000004U
#define ALD_USB_RXTYPE_TEPN_5               0x00000005U
#define ALD_USB_RXTYPE_TEPN_6               0x00000006U

/*  TXFIFO2  */
#define ALD_USB_TXFIFO2_MAXPKTSIZE_1024     0x000000E0U
#define ALD_USB_TXFIFO2_MAXPKTSIZE_512      0x000000C0U
#define ALD_USB_TXFIFO2_MAXPKTSIZE_256      0x000000A0U
#define ALD_USB_TXFIFO2_MAXPKTSIZE_128      0x00000080U
#define ALD_USB_TXFIFO2_MAXPKTSIZE_64       0x00000060U
#define ALD_USB_TXFIFO2_MAXPKTSIZE_32       0x00000040U
#define ALD_USB_TXFIFO2_MAXPKTSIZE_16       0x00000020U
#define ALD_USB_TXFIFO2_DPB                 0x00000010U
#define ALD_USB_TXFIFO2_ADDRH               0x00000007U

/*  RXFIFO2  */
#define ALD_USB_RXFIFO2_MAXPKTSIZE_1024     0x000000E0U
#define ALD_USB_RXFIFO2_MAXPKTSIZE_512      0x000000C0U
#define ALD_USB_RXFIFO2_MAXPKTSIZE_256      0x000000A0U
#define ALD_USB_RXFIFO2_MAXPKTSIZE_128      0x00000080U
#define ALD_USB_RXFIFO2_MAXPKTSIZE_64       0x00000060U
#define ALD_USB_RXFIFO2_MAXPKTSIZE_32       0x00000040U
#define ALD_USB_RXFIFO2_MAXPKTSIZE_16       0x00000020U
#define ALD_USB_RXFIFO2_DPB                 0x00000010U

/*  TXIER  */
#define ALD_USB_TXIER_EP6IE                 0x00000040U
#define ALD_USB_TXIER_EP5IE                 0x00000020U
#define ALD_USB_TXIER_EP4IE                 0x00000010U
#define ALD_USB_TXIER_EP3IE                 0x00000008U
#define ALD_USB_TXIER_EP2IE                 0x00000004U
#define ALD_USB_TXIER_EP1IE                 0x00000002U
#define ALD_USB_TXIER_EP0IE                 0x00000001U

/*  RXIER  */
#define ALD_USB_RXIER_EP6IE                 0x00000040U
#define ALD_USB_RXIER_EP5IE                 0x00000020U
#define ALD_USB_RXIER_EP4IE                 0x00000010U
#define ALD_USB_RXIER_EP3IE                 0x00000008U
#define ALD_USB_RXIER_EP2IE                 0x00000004U
#define ALD_USB_RXIER_EP1IE                 0x00000002U

/*  TXIDR  */
#define ALD_USB_TXIDR_EP6ID                 0x00000040U
#define ALD_USB_TXIDR_EP5ID                 0x00000020U
#define ALD_USB_TXIDR_EP4ID                 0x00000010U
#define ALD_USB_TXIDR_EP3ID                 0x00000008U
#define ALD_USB_TXIDR_EP2ID                 0x00000004U
#define ALD_USB_TXIDR_EP1ID                 0x00000002U
#define ALD_USB_TXIDR_EP0ID                 0x00000001U

/*  RXIDR  */
#define ALD_USB_RXIDR_EP6ID                 0x00000040U
#define ALD_USB_RXIDR_EP5ID                 0x00000020U
#define ALD_USB_RXIDR_EP4ID                 0x00000010U
#define ALD_USB_RXIDR_EP3ID                 0x00000008U
#define ALD_USB_RXIDR_EP2ID                 0x00000004U
#define ALD_USB_RXIDR_EP1ID                 0x00000002U

/*  TXIVS  */
#define ALD_USB_TXIVS_EP6IVS                0x00000040U
#define ALD_USB_TXIVS_EP5IVS                0x00000020U
#define ALD_USB_TXIVS_EP4IVS                0x00000010U
#define ALD_USB_TXIVS_EP3IVS                0x00000008U
#define ALD_USB_TXIVS_EP2IVS                0x00000004U
#define ALD_USB_TXIVS_EP1IVS                0x00000002U
#define ALD_USB_TXIVS_EP0IVS                0x00000001U

/*  RXIVS  */
#define ALD_USB_RXIVS_EP6IVS                0x00000040U
#define ALD_USB_RXIVS_EP5IVS                0x00000020U
#define ALD_USB_RXIVS_EP4IVS                0x00000010U
#define ALD_USB_RXIVS_EP3IVS                0x00000008U
#define ALD_USB_RXIVS_EP2IVS                0x00000004U
#define ALD_USB_RXIVS_EP1IVS                0x00000002U

/*  TXRIF  */
#define ALD_USB_TXRIF_EP6RIF                0x00000040U
#define ALD_USB_TXRIF_EP5RIF                0x00000020U
#define ALD_USB_TXRIF_EP4RIF                0x00000010U
#define ALD_USB_TXRIF_EP3RIF                0x00000008U
#define ALD_USB_TXRIF_EP2RIF                0x00000004U
#define ALD_USB_TXRIF_EP1RIF                0x00000002U
#define ALD_USB_TXRIF_EP0RIF                0x00000001U

/*  RXRIF  */
#define ALD_USB_RXRIF_EP6RIF                0x00000040U
#define ALD_USB_RXRIF_EP5RIF                0x00000020U
#define ALD_USB_RXRIF_EP4RIF                0x00000010U
#define ALD_USB_RXRIF_EP3RIF                0x00000008U
#define ALD_USB_RXRIF_EP2RIF                0x00000004U
#define ALD_USB_RXRIF_EP1RIF                0x00000002U

/*  TXIFM  */
#define ALD_USB_TXIFM_EP6IFM                0x00000040U
#define ALD_USB_TXIFM_EP5IFM                0x00000020U
#define ALD_USB_TXIFM_EP4IFM                0x00000010U
#define ALD_USB_TXIFM_EP3IFM                0x00000008U
#define ALD_USB_TXIFM_EP2IFM                0x00000004U
#define ALD_USB_TXIFM_EP1IFM                0x00000002U
#define ALD_USB_TXIFM_EP0IFM                0x00000001U

/*  RXIFM  */
#define ALD_USB_RXIFM_EP6IFM                0x00000040U
#define ALD_USB_RXIFM_EP5IFM                0x00000020U
#define ALD_USB_RXIFM_EP4IFM                0x00000010U
#define ALD_USB_RXIFM_EP3IFM                0x00000008U
#define ALD_USB_RXIFM_EP2IFM                0x00000004U
#define ALD_USB_RXIFM_EP1IFM                0x00000002U

/*  TXICR  */
#define ALD_USB_TXICR_EP6ICR                0x00000040U
#define ALD_USB_TXICR_EP5ICR                0x00000020U
#define ALD_USB_TXICR_EP4ICR                0x00000010U
#define ALD_USB_TXICR_EP3ICR                0x00000008U
#define ALD_USB_TXICR_EP2ICR                0x00000004U
#define ALD_USB_TXICR_EP1ICR                0x00000002U
#define ALD_USB_TXICR_EP0ICR                0x00000001U

/*  RXICR  */
#define ALD_USB_RXICR_EP6ICR                0x00000040U
#define ALD_USB_RXICR_EP5ICR                0x00000020U
#define ALD_USB_RXICR_EP4ICR                0x00000010U
#define ALD_USB_RXICR_EP3ICR                0x00000008U
#define ALD_USB_RXICR_EP2ICR                0x00000004U
#define ALD_USB_RXICR_EP1ICR                0x00000002U

/*  IER  */
#define ALD_USB_IER_STATUS                  0x000000FFU
#define ALD_USB_IER_SESREQIE                0x00000040U
#define ALD_USB_IER_DISCONIE                0x00000020U
#define ALD_USB_IER_CONIE                   0x00000010U
#define ALD_USB_IER_SOFIE                   0x00000008U
#define ALD_USB_IER_BABIE                   0x00000004U
#define ALD_USB_IER_RESIE                   0x00000002U

/*  IDR  */
#define ALD_USB_IDR_STATUS                  0x000000FFU
#define ALD_USB_IDR_SESREQID                0x00000040U
#define ALD_USB_IDR_DISCONID                0x00000020U
#define ALD_USB_IDR_CONID                   0x00000010U
#define ALD_USB_IDR_SOFID                   0x00000008U
#define ALD_USB_IDR_BABID                   0x00000004U
#define ALD_USB_IDR_RESID                   0x00000002U

/*  IVS  */
#define ALD_USB_IVS_SESREQIVS               0x00000040U
#define ALD_USB_IVS_DISCONIVS               0x00000020U
#define ALD_USB_IVS_CONIVS                  0x00000010U
#define ALD_USB_IVS_SOFIVS                  0x00000008U
#define ALD_USB_IVS_BABIVS                  0x00000004U
#define ALD_USB_IVS_RESIVS                  0x00000002U

/*  RIF  */
#define ALD_USB_RIF_SESREQRIF               0x00000040U
#define ALD_USB_RIF_DISCONRIF               0x00000020U
#define ALD_USB_RIF_CONRIF                  0x00000010U
#define ALD_USB_RIF_SOFRIF                  0x00000008U
#define ALD_USB_RIF_BABRIF                  0x00000004U
#define ALD_USB_RIF_RESRIF                  0x00000002U

/*  IFM  */
#define ALD_USB_IFM_SESREQIFM               0x00000040U
#define ALD_USB_IFM_DISCONIFM               0x00000020U
#define ALD_USB_IFM_CONIFM                  0x00000010U
#define ALD_USB_IFM_SOFIFM                  0x00000008U
#define ALD_USB_IFM_BABIFM                  0x00000004U
#define ALD_USB_IFM_RESIFM                  0x00000002U

/*  ICR  */
#define ALD_USB_ICR_SESREQICR               0x00000040U
#define ALD_USB_ICR_DISCONICR               0x00000020U
#define ALD_USB_ICR_CONICR                  0x00000010U
#define ALD_USB_ICR_SOFICR                  0x00000008U
#define ALD_USB_ICR_BABICR                  0x00000004U
#define ALD_USB_ICR_RESICR                  0x00000002U


#define ALD_MAX_NAK_LIMIT                   255U
#define ALD_DISABLE_NAK_LIMIT               0U

#define ALD_USB_RX_EPSTATUS_SHIFT           16U
#define ALD_USB_INTEP_RX_SHIFT              16U

#define ALD_MAX_PACKET_SIZE_EP0     64U

#define ALD_USB_TXTYPE1_PROTO_M     0x00000030U
#define ALD_USB_TXTYPE1_PROTO_CTRL  0x00000000U
#define ALD_USB_TXTYPE1_PROTO_ISOC  0x00000010U
#define ALD_USB_TXTYPE1_PROTO_BULK  0x00000020U
#define ALD_USB_TXTYPE1_PROTO_INT   0x00000030U

#define ALD_USB_FIFO_SZ_8           0x00000000U
#define ALD_USB_FIFO_SZ_16          0x00000001U
#define ALD_USB_FIFO_SZ_32          0x00000002U
#define ALD_USB_FIFO_SZ_64          0x00000003U
#define ALD_USB_FIFO_SZ_128         0x00000004U
#define ALD_USB_FIFO_SZ_256         0x00000005U
#define ALD_USB_FIFO_SZ_512         0x00000006U
#define ALD_USB_FIFO_SZ_1024        0x00000007U
#define ALD_USB_FIFO_SZ_2048        0x00000008U
#define ALD_USBFIFOSizeToBytes(x)   (8 << (x))

#define ALD_USB_TRANS_OUT           0x00000102U
#define ALD_USB_TRANS_IN            0x00000102U
#define ALD_USB_TRANS_IN_LAST       0x0000010aU
#define ALD_USB_TRANS_SETUP         0x0000110aU
#define ALD_USB_TRANS_STATUS        0x00000142U

#define ALD_USB_RX_EPSTATUS_SHIFT   16U
#define ALD_USB_INTEP_RX_SHIFT      16U

#define ALD_USB_UNDEF_SPEED         0x80000000U
#define ALD_USB_HIGH_SPEED          0x00000002U
#define ALD_USB_FULL_SPEED          0x00000001U
#define ALD_USB_LOW_SPEED           0x00000000U

#define ALD_USB_EP_AUTO_SET         0x00000001
#define ALD_USB_EP_AUTO_REQUEST     0x00000002
#define ALD_USB_EP_AUTO_CLEAR       0x00000004
#define ALD_USB_EP_DUAL_BUFFERING   0x00000008
#define ALD_USB_EP_DMA_MODE_0       0x00000008
#define ALD_USB_EP_DMA_MODE_1       0x00000010
#define ALD_USB_EP_DIS_NYET         0x00000020

#define ALD_USB_EP_MODE_ISOC        0x00000000  // Isochronous endpoint
#define ALD_USB_EP_MODE_BULK        0x00000100  // Bulk endpoint
#define ALD_USB_EP_MODE_INT         0x00000200  // Interrupt endpoint
#define ALD_USB_EP_MODE_CTRL        0x00000300  // Control endpoint
#define ALD_USB_EP_MODE_MASK        0x00000300  // Mode Mask
#define ALD_USB_EP_SPEED_LOW        0x00000000  // Low Speed
#define ALD_USB_EP_SPEED_FULL       0x00001000  // Full Speed
#define ALD_USB_EP_SPEED_HIGH       0x00004000  // High Speed
#define ALD_USB_EP_HOST_IN          0x00000000  // Host IN endpoint
#define ALD_USB_EP_HOST_OUT         0x00002000  // Host OUT endpoint
#define ALD_USB_EP_DEV_IN           0x00002000  // Device IN endpoint
#define ALD_USB_EP_DEV_OUT          0x00000000  // Device OUT endpoint

#define ALD_USB_INTCTRL_ALL     0x000003FFU
#define ALD_USB_INTCTRL_STATUS  0x000000FFU
#define ALD_USB_INTCTRL_VBUS_ERR    0x00000080U
#define ALD_USB_INTCTRL_SESSION 0x00000040U
#define ALD_USB_INTCTRL_SESSION_END 0x00000040U
#define ALD_USB_INTCTRL_DISCONNECT  0x00000020U
#define ALD_USB_INTCTRL_CONNECT 0x00000010U
#define ALD_USB_INTCTRL_SOF     0x00000008U
#define ALD_USB_INTCTRL_BABBLE  0x00000004U
#define ALD_USB_INTCTRL_RESET   0x00000004U
#define ALD_USB_INTCTRL_RESUME  0x00000002U
#define ALD_USB_INTCTRL_SUSPEND 0x00000001U
#define ALD_USB_INTCTRL_MODE_DETECT 0x00000200U
#define ALD_USB_INTCTRL_POWER_FAULT 0x00000100U


#define ALD_USB_INTEP_ALL       0xFFFFFFFFU
#define ALD_USB_INTEP_HOST_IN   0x001E0000U
#define ALD_USB_INTEP_HOST_IN_15    0x80000000U
#define ALD_USB_INTEP_HOST_IN_14    0x40000000U
#define ALD_USB_INTEP_HOST_IN_13    0x20000000U
#define ALD_USB_INTEP_HOST_IN_12    0x10000000U
#define ALD_USB_INTEP_HOST_IN_11    0x08000000U
#define ALD_USB_INTEP_HOST_IN_10    0x04000000U
#define ALD_USB_INTEP_HOST_IN_9 0x02000000U
#define ALD_USB_INTEP_HOST_IN_8 0x01000000U
#define ALD_USB_INTEP_HOST_IN_7 0x00800000U
#define ALD_USB_INTEP_HOST_IN_6 0x00400000U
#define ALD_USB_INTEP_HOST_IN_5 0x00200000U
#define ALD_USB_INTEP_HOST_IN_4 0x00100000U
#define ALD_USB_INTEP_HOST_IN_3 0x00080000U
#define ALD_USB_INTEP_HOST_IN_2 0x00040000U
#define ALD_USB_INTEP_HOST_IN_1 0x00020000U
#define ALD_USB_INTEP_DEV_OUT   0x001E0000U
#define ALD_USB_INTEP_DEV_OUT_15    0x80000000U
#define ALD_USB_INTEP_DEV_OUT_14    0x40000000U
#define ALD_USB_INTEP_DEV_OUT_13    0x20000000U
#define ALD_USB_INTEP_DEV_OUT_12    0x10000000U
#define ALD_USB_INTEP_DEV_OUT_11    0x08000000U
#define ALD_USB_INTEP_DEV_OUT_10    0x04000000U
#define ALD_USB_INTEP_DEV_OUT_9 0x02000000U
#define ALD_USB_INTEP_DEV_OUT_8 0x01000000U
#define ALD_USB_INTEP_DEV_OUT_7 0x00800000U
#define ALD_USB_INTEP_DEV_OUT_6 0x00400000U
#define ALD_USB_INTEP_DEV_OUT_5 0x00200000U
#define ALD_USB_INTEP_DEV_OUT_4 0x00100000U
#define ALD_USB_INTEP_DEV_OUT_3 0x00080000U
#define ALD_USB_INTEP_DEV_OUT_2 0x00040000U
#define ALD_USB_INTEP_DEV_OUT_1 0x00020000U
#define ALD_USB_INTEP_HOST_OUT  0x0000001EU
#define ALD_USB_INTEP_HOST_OUT_15   0x00008000U
#define ALD_USB_INTEP_HOST_OUT_14   0x00004000U
#define ALD_USB_INTEP_HOST_OUT_13   0x00002000U
#define ALD_USB_INTEP_HOST_OUT_12   0x00001000U
#define ALD_USB_INTEP_HOST_OUT_11   0x00000800U
#define ALD_USB_INTEP_HOST_OUT_10   0x00000400U
#define ALD_USB_INTEP_HOST_OUT_9    0x00000200U
#define ALD_USB_INTEP_HOST_OUT_8    0x00000100U
#define ALD_USB_INTEP_HOST_OUT_7    0x00000080U
#define ALD_USB_INTEP_HOST_OUT_6    0x00000040U
#define ALD_USB_INTEP_HOST_OUT_5    0x00000020U
#define ALD_USB_INTEP_HOST_OUT_4    0x00000010U
#define ALD_USB_INTEP_HOST_OUT_3    0x00000008U
#define ALD_USB_INTEP_HOST_OUT_2    0x00000004U
#define ALD_USB_INTEP_HOST_OUT_1    0x00000002U
#define ALD_USB_INTEP_DEV_IN    0x0000001EU
#define ALD_USB_INTEP_DEV_IN_15 0x00008000U
#define ALD_USB_INTEP_DEV_IN_14 0x00004000U
#define ALD_USB_INTEP_DEV_IN_13 0x00002000U
#define ALD_USB_INTEP_DEV_IN_12 0x00001000U
#define ALD_USB_INTEP_DEV_IN_11 0x00000800U
#define ALD_USB_INTEP_DEV_IN_10 0x00000400U
#define ALD_USB_INTEP_DEV_IN_9  0x00000200U
#define ALD_USB_INTEP_DEV_IN_8  0x00000100U
#define ALD_USB_INTEP_DEV_IN_7  0x00000080U
#define ALD_USB_INTEP_DEV_IN_6  0x00000040U
#define ALD_USB_INTEP_DEV_IN_5  0x00000020U
#define ALD_USB_INTEP_DEV_IN_4  0x00000010U
#define ALD_USB_INTEP_DEV_IN_3  0x00000008U
#define ALD_USB_INTEP_DEV_IN_2  0x00000004U
#define ALD_USB_INTEP_DEV_IN_1  0x00000002U
#define ALD_USB_INTEP_0     0x00000001U


#define ALD_USB_UNDEF_SPEED     0x80000000U
#define ALD_USB_HIGH_SPEED      0x00000002U
#define ALD_USB_FULL_SPEED      0x00000001U
#define ALD_USB_LOW_SPEED       0x00000000U

#define ALD_USB_HOST_IN_STATUS  0x114F0000U
#define ALD_USB_HOST_IN_PID_ERROR   0x10000000U
#define ALD_USB_HOST_IN_NOT_COMP    0x01000000U
#define ALD_USB_HOST_IN_STALL   0x00400000U
#define ALD_USB_HOST_IN_DATA_ERROR  0x00080000U
#define ALD_USB_HOST_IN_NAK_TO  0x00080000U
#define ALD_USB_HOST_IN_ERROR   0x00040000U
#define ALD_USB_HOST_IN_FIFO_FULL   0x00020000U
#define ALD_USB_HOST_IN_PKTRDY  0x00010000U
#define ALD_USB_HOST_OUT_STATUS 0x000000A7U
#define ALD_USB_HOST_OUT_NAK_TO 0x00000080U
#define ALD_USB_HOST_OUT_NOT_COMP   0x00000080U
#define ALD_USB_HOST_OUT_STALL  0x00000020U
#define ALD_USB_HOST_OUT_ERROR  0x00000004U
#define ALD_USB_HOST_OUT_FIFO_NE    0x00000002U
#define ALD_USB_HOST_OUT_PKTPEND    0x00000001U
#define ALD_USB_HOST_EP0_NAK_TO 0x00000080U
#define ALD_USB_HOST_EP0_STATUS 0x00000040U
#define ALD_USB_HOST_EP0_ERROR  0x00000010U
#define ALD_USB_HOST_EP0_RX_STALL   0x00000004U
#define ALD_USB_HOST_EP0_RXPKTRDY   0x00000001U
#define ALD_USB_DEV_RX_PID_ERROR    0x01000000U
#define ALD_USB_DEV_RX_SENT_STALL   0x00400000U
#define ALD_USB_DEV_RX_DATA_ERROR   0x00080000U
#define ALD_USB_DEV_RX_OVERRUN  0x00040000U
#define ALD_USB_DEV_RX_FIFO_FULL    0x00020000U
#define ALD_USB_DEV_RX_PKT_RDY  0x00010000U
#define ALD_USB_DEV_TX_NOT_COMP 0x00000080U
#define ALD_USB_DEV_TX_SENT_STALL   0x00000020U
#define ALD_USB_DEV_TX_UNDERRUN 0x00000004U
#define ALD_USB_DEV_TX_FIFO_NE  0x00000002U
#define ALD_USB_DEV_TX_TXPKTRDY 0x00000001U
#define ALD_USB_DEV_EP0_SETUP_END   0x00000010U
#define ALD_USB_DEV_EP0_SENT_STALL  0x00000004U
#define ALD_USB_DEV_EP0_IN_PKTPEND  0x00000002U
#define ALD_USB_DEV_EP0_OUT_PKTRDY  0x00000001U


#define ALD_USB_EP_0        0x00000000U
#define ALD_USB_EP_1        0x00000001U
#define ALD_USB_EP_2        0x00000002U
#define ALD_USB_EP_3        0x00000003U
#define ALD_USB_EP_4        0x00000004U
#define ALD_USB_EP_5        0x00000005U
#define ALD_USB_EP_6        0x00000006U
#define ALD_USB_EP_7        0x00000007U
#define ALD_NUM_USB_EP      8U

#define ALD_USB_FIFO_SZ_8       0x00000000U
#define ALD_USB_FIFO_SZ_16      0x00000001U
#define ALD_USB_FIFO_SZ_32      0x00000002U
#define ALD_USB_FIFO_SZ_64      0x00000003U
#define ALD_USB_FIFO_SZ_128     0x00000004U
#define ALD_USB_FIFO_SZ_256     0x00000005U
#define ALD_USB_FIFO_SZ_512     0x00000006U
#define ALD_USB_FIFO_SZ_1024    0x00000007U
#define ALD_USB_FIFO_SZ_2048    0x00000008U

#define ALD_USB_TRANS_OUT       0x00000102U
#define ALD_USB_TRANS_IN        0x00000102U
#define ALD_USB_TRANS_IN_LAST   0x0000010aU
#define ALD_USB_TRANS_SETUP     0x0000110aU
#define ALD_USB_TRANS_STATUS    0x00000142U
#define ALD_USB_DMA_EP_CFG_TX   0x00000001U
#define ALD_USB_DMA_EP_CFG_RX_DEV   0x00000002U
#define ALD_USB_DMA_EP_CFG_RX_HOST  0x00000004U
#define ALD_USB_DMA_EP_TX_MSK   0x94U
#define ALD_USB_DMA_EP_RX_DEV_MSK   0xA8U
#define ALD_USB_DMA_EP_RX_HOST_MSK  0xE8U

#define ALD_USB_INTLPM_ERROR    0x00000020U
#define ALD_USB_INTLPM_RESUME   0x00000010U
#define ALD_USB_INTLPM_INCOMPLETE   0x00000008U
#define ALD_USB_INTLPM_ACK      0x00000004U
#define ALD_USB_INTLPM_NYET     0x00000002U
#define ALD_USB_INTLPM_STALL    0x00000001U


#define ALD_USB_DEV_LPM_NAK     0x00000010U
#define ALD_USB_DEV_LPM_NONE    0x00000000U
#define ALD_USB_DEV_LPM_EN      0x0000000cU
#define ALD_USB_DEV_LPM_EXTONLY 0x00000004U

#define ALD_USB_HOST_LPM_RMTWAKE    0x00000100U
#define ALD_USB_HOST_LPM_L1     0x00000001U

#define ALD_USB_DEV_LPM_LS_RMTWAKE  0x00000100U
#define ALD_USB_DEV_LPM_LS_L1   0x00000001U

#define ALD_USB_HOST_PWRFLT_LOW 0x00000010U
#define ALD_USB_HOST_PWRFLT_HIGH    0x00000030U
#define ALD_USB_HOST_PWRFLT_EP_NONE 0x00000000U
#define ALD_USB_HOST_PWRFLT_EP_TRI  0x00000140U
#define ALD_USB_HOST_PWRFLT_EP_LOW  0x00000240U
#define ALD_USB_HOST_PWRFLT_EP_HIGH 0x00000340U
#define ALD_USB_HOST_PWREN_MAN_LOW  0x00000000U
#define ALD_USB_HOST_PWREN_MAN_HIGH 0x00000001U
#define ALD_USB_HOST_PWREN_AUTOLOW  0x00000002U
#define ALD_USB_HOST_PWREN_AUTOHIGH 0x00000003U
#define ALD_USB_HOST_PWREN_FILTER   0x00010000U


/**
  * @}
  */


/**
  * @defgroup USB_Public_Types USB Public Types
  * @{
  */

/**
  * @brief USB DP/DM line push-up or push-down
  */
typedef enum {
    ALD_USB_DPDM_FLOATING     = 0x0U,   /**< Floating */
    ALD_USB_DPDM_PUSH_UP      = 0x1U,   /**< Push-Up */
    ALD_USB_DPDM_PUSH_DOWN    = 0x2U,   /**< Push-Down */
} ald_dpdm_push_t;


/**
  * @}
  */

/** @addtogroup USB_Public_Functions
  * @{
  */

/** @addtogroup USB_Public_Functions_Group1
  * @{
  */
/* Base functions */
extern uint32_t ald_usb_frame_number_get(void);
extern void ald_usb_otg_session_request(bool start);
extern uint32_t ald_usb_mode_get(void);
extern uint32_t ald_usb_mode_host_req(void);
extern uint32_t ald_usb_mode_host_req_clear(void);
extern void ald_usb_high_speed_enable(bool enable);
extern uint32_t ald_usb_device_speed_get(void);
extern uint32_t ald_usb_num_ep_get( void);
extern void ald_usb_control_reset(void);
void ald_usb_dppud_set(ald_dpdm_push_t pupd);
void ald_usb_dmpud_set(ald_dpdm_push_t pupd);
void ald_usb_swcid_cidctrl(uint8_t cid);
void ald_usb_swcid_host(uint8_t host);

/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group2
  * @{
  */
/* Device functions */
extern uint8_t ald_usb_dev_get_addr(void);
extern void ald_usb_dev_set_addr(uint8_t addr);
extern void ald_usb_dev_connect(void);
extern void ald_usb_dev_disconnect(void);
extern void ald_usb_dev_suspend_enable(void);
extern void ald_usb_dev_ep_config(uint32_t ep_idx, uint32_t p_max, uint32_t flags);
extern void ald_usb_dev_ep_get_config(uint32_t ep_idx, uint32_t *p_max, uint32_t *flags);
extern void ald_usb_dev_ep_data_ack(uint32_t ep_idx, bool last);
extern void ald_usb_dev_ep_stall(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_dev_ep_stall_clear(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_dev_ep_status_clear(uint32_t ep_idx, uint32_t flags);

/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group3
  * @{
  */
/* Host functions */
extern uint32_t ald_usb_host_addr_get(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_host_addr_set(uint32_t ep_idx, uint32_t addr, uint32_t flags);
extern void ald_usb_host_ep_config(uint32_t ep_idx, uint32_t p_max, uint32_t nak_val, uint32_t t_ep, uint32_t flags);
extern void ald_usb_host_ep_data_ack(uint32_t ep_idx);
extern void ald_usb_host_ep_data_toggle(uint32_t ep_idx, bool toggle, uint32_t flags);
extern void ald_usb_host_ep_status_clear(uint32_t ep_idx, uint32_t flags);
extern uint32_t ald_usb_host_hub_addr_get(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_host_hub_addr_set(uint32_t ep_idx, uint32_t addr, uint32_t flags);
extern void ald_usb_host_pwr_disable(void);
extern void ald_usb_host_pwr_enable(void);
extern void ald_usb_host_pwr_config(uint32_t flags);
extern void ald_usb_host_pwr_fault_disable(void);
extern void ald_usb_host_pwr_fault_enable(void);
extern void ald_usb_host_request_in(uint32_t ep_idx);
extern void ald_usb_host_request_in_clear(uint32_t ep_idx);
extern void ald_usb_host_request_status(void);
extern void ald_usb_host_reset(bool start);
extern void ald_usb_host_resume(bool start);
extern void ald_usb_host_suspend(void);
extern uint32_t ald_usb_host_speed_get(void);
extern void ald_usb_host_ep_speed_set(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_host_ep_ping(uint32_t ep_idx, bool enable);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group4
  * @{
  */
/* Endpoint functions */
extern uint32_t ald_usb_ep_data_avail(uint32_t ep_idx);
extern int32_t ald_usb_ep_data_get(uint32_t ep_idx, uint8_t *data, uint32_t *size);
extern int32_t ald_usb_ep_data_put(uint32_t ep_idx, uint8_t *data, uint32_t size);
extern int32_t ald_usb_ep_data_send(uint32_t ep_idx, uint32_t tx_type);
extern void ald_usb_ep_data_toggle_clear(uint32_t ep_idx, uint32_t flags);
extern void ald_usb_ep_req_packet_count(uint32_t ep_idx, uint32_t count);
extern uint32_t ald_usb_ep_status(uint32_t ep_idx);
extern void ald_usb_ep_dma_config(uint32_t ep_idx, uint32_t flag, type_func_t en);

/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group5
  * @{
  */
/* FIFO functions */
extern uint32_t ald_usb_fifo_addr_get(uint32_t ep_idx);
extern void ald_usb_fifo_config_get(uint32_t ep_idx, uint32_t *addr, uint32_t *size, uint32_t flags);
extern void ald_usb_fifo_config_set(uint32_t ep_idx, uint32_t addr, uint32_t size, uint32_t flags);
extern void ald_usb_fifo_flush(uint32_t ep_idx, uint32_t flags);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group6
  * @{
  */
/* Interrupt functions */
extern void ald_usb_int_disable(uint32_t flags);
extern void ald_usb_int_enable(uint32_t flags);
extern uint32_t ald_usb_int_status_get(void);
extern void ald_usb_int_disable_ep(uint32_t flags);
extern void ald_usb_int_enable_ep(uint32_t flags);
extern uint32_t ald_usb_int_status_ep_get(void);
extern void ald_usb_int_register(void);
extern void ald_usb_int_unregister(void);
extern uint32_t ald_usb_int_num_get(void);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group7
  * @{
  */
/* DMA functions */
extern void ald_usb_dma_channel_config(uint8_t ch, uint32_t addr, uint32_t count, uint32_t ctrl);
extern void ald_usb_dma_mult_recv_start(uint32_t ep_idx);
extern void ald_usb_dma_channel_start(uint8_t ch);
extern void ald_usb_dma_channel_stop(uint8_t ch);
extern uint32_t ald_usb_dma_get_interrupt_flag(void);
extern uint32_t ald_usb_dma_get_channel_error(uint8_t ch);
extern void ald_usb_dma_clear_channel_error(uint8_t ch);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group8
  * @{
  */
/* LPM functions */
extern void ald_usb_host_lpm_send(uint32_t addr, uint32_t ep_idx);
extern void ald_usb_host_lpm_config(uint32_t resume_time, uint32_t config);
extern uint32_t ald_usb_lpm_remote_wake_is_enable(void);
extern void ald_usb_host_lpm_resume(void);
extern void ald_usb_dev_lpm_remote_wake(void);
extern void ald_usb_dev_lpm_config(uint32_t config);
extern void ald_usb_dev_lpm_enable(void);
extern void ald_usb_dev_lpm_disable(void);
extern uint32_t ald_usb_lpm_link_status_get(void);
extern uint32_t ald_usb_lpm_ep_get(void);
extern uint32_t ald_usb_lpm_int_status_get(void);
extern void ald_usb_lpm_int_disable(uint32_t ints);
extern void ald_usb_lpm_int_enable(uint32_t ints);
/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group9
  * @{
  */
/* usb swvbus control functions */
extern void ald_usb_swvbus_sigctl_set(uint8_t sigctl);
extern uint8_t ald_usb_swvbus_sigctl_get(void);
extern void ald_usb_swvbus_sesendth_set(uint8_t thd);
extern uint8_t ald_usb_swvbus_sesendth_get(void);
extern void ald_usb_swvbus_sesvalth_set(uint8_t thd);
extern uint8_t ald_usb_swvbus_valth_get(void);
extern void ald_usb_swvbus_valth_set(uint8_t thd);
extern uint8_t ald_usb_swvbus_valth_get(void);

/**
  * @}
  */

/** @addtogroup USB_Public_Functions_Group10
  * @{
  */
/* usb init functions */
extern void ald_usb_host_components_init(void);
extern void ald_usb_device_components_init(void);

/**
  * @}
  */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __ALD_USB_H__ */
