/********************************** (C) COPYRIGHT *******************************
* File Name          : system_ch32v30x.h
* Author             : WCH
* Version            : V1.0.0
* Date               : 2022/08/20
* Description        : CH32V30x Device Peripheral Access Layer System Header File.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

#ifndef __CH32V30x_USB_H
#define __CH32V30x_USB_H

#ifdef __cplusplus
 extern "C" {
#endif

/*******************************************************************************/
/* Header File */
#include "stdint.h"

/*******************************************************************************/
/* USB Communication Related Macro Definition */
/* USB Endpoint0 Size */
#ifndef DEFAULT_ENDP0_SIZE
#define DEFAULT_ENDP0_SIZE          8          // default maximum packet size for endpoint 0
#endif
#ifndef MAX_PACKET_SIZE
#define MAX_PACKET_SIZE             64         // maximum packet size
#endif

/* USB PID */
#ifndef USB_PID_SETUP
#define USB_PID_NULL                0x00
#define USB_PID_SOF                 0x05
#define USB_PID_SETUP               0x0D
#define USB_PID_IN                  0x09
#define USB_PID_OUT                 0x01
#define USB_PID_NYET                0x06
#define USB_PID_ACK                 0x02
#define USB_PID_NAK                 0x0A
#define USB_PID_STALL               0x0E
#define USB_PID_DATA0               0x03
#define USB_PID_DATA1               0x0B
#define USB_PID_DATA2               0x07
#define USB_PID_MDATA               0x0F
#define USB_PID_PRE                 0x0C
#endif

/* USB standard device request code */
#ifndef USB_GET_DESCRIPTOR
#define USB_GET_STATUS              0x00
#define USB_CLEAR_FEATURE           0x01
#define USB_SET_FEATURE             0x03
#define USB_SET_ADDRESS             0x05
#define USB_GET_DESCRIPTOR          0x06
#define USB_SET_DESCRIPTOR          0x07
#define USB_GET_CONFIGURATION       0x08
#define USB_SET_CONFIGURATION       0x09
#define USB_GET_INTERFACE           0x0A
#define USB_SET_INTERFACE           0x0B
#define USB_SYNCH_FRAME             0x0C
#endif

#define DEF_STRING_DESC_LANG        0x00
#define DEF_STRING_DESC_MANU        0x01
#define DEF_STRING_DESC_PROD        0x02
#define DEF_STRING_DESC_SERN        0x03

/* USB hub class request code */
#ifndef HUB_GET_DESCRIPTOR
#define HUB_GET_STATUS              0x00
#define HUB_CLEAR_FEATURE           0x01
#define HUB_GET_STATE               0x02
#define HUB_SET_FEATURE             0x03
#define HUB_GET_DESCRIPTOR          0x06
#define HUB_SET_DESCRIPTOR          0x07
#endif

/* USB HID class request code */
#ifndef HID_GET_REPORT
#define HID_GET_REPORT              0x01
#define HID_GET_IDLE                0x02
#define HID_GET_PROTOCOL            0x03
#define HID_SET_REPORT              0x09
#define HID_SET_IDLE                0x0A
#define HID_SET_PROTOCOL            0x0B
#endif

/* USB CDC Class request code */
#ifndef CDC_GET_LINE_CODING
#define CDC_GET_LINE_CODING         0x21                                      /* This request allows the host to find out the currently configured line coding */
#define CDC_SET_LINE_CODING         0x20                                      /* Configures DTE rate, stop-bits, parity, and number-of-character */
#define CDC_SET_LINE_CTLSTE         0x22                                      /* This request generates RS-232/V.24 style control signals */
#define CDC_SEND_BREAK              0x23                                      /* Sends special carrier modulation used to specify RS-232 style break */
#endif

/* Bit Define for USB Request Type */
#ifndef USB_REQ_TYP_MASK
#define USB_REQ_TYP_IN              0x80
#define USB_REQ_TYP_OUT             0x00
#define USB_REQ_TYP_READ            0x80
#define USB_REQ_TYP_WRITE           0x00
#define USB_REQ_TYP_MASK            0x60
#define USB_REQ_TYP_STANDARD        0x00
#define USB_REQ_TYP_CLASS           0x20
#define USB_REQ_TYP_VENDOR          0x40
#define USB_REQ_TYP_RESERVED        0x60
#define USB_REQ_RECIP_MASK          0x1F
#define USB_REQ_RECIP_DEVICE        0x00
#define USB_REQ_RECIP_INTERF        0x01
#define USB_REQ_RECIP_ENDP          0x02
#define USB_REQ_RECIP_OTHER         0x03
#define USB_REQ_FEAT_REMOTE_WAKEUP  0x01
#define USB_REQ_FEAT_ENDP_HALT      0x00
#endif

/* USB Descriptor Type */
#ifndef USB_DESCR_TYP_DEVICE
#define USB_DESCR_TYP_DEVICE        0x01
#define USB_DESCR_TYP_CONFIG        0x02
#define USB_DESCR_TYP_STRING        0x03
#define USB_DESCR_TYP_INTERF        0x04
#define USB_DESCR_TYP_ENDP          0x05
#define USB_DESCR_TYP_QUALIF        0x06
#define USB_DESCR_TYP_SPEED         0x07
#define USB_DESCR_TYP_OTG           0x09
#define USB_DESCR_TYP_BOS           0X0F
#define USB_DESCR_TYP_HID           0x21
#define USB_DESCR_TYP_REPORT        0x22
#define USB_DESCR_TYP_PHYSIC        0x23
#define USB_DESCR_TYP_CS_INTF       0x24
#define USB_DESCR_TYP_CS_ENDP       0x25
#define USB_DESCR_TYP_HUB           0x29
#endif

/* USB Device Class */
#ifndef USB_DEV_CLASS_HUB
#define USB_DEV_CLASS_RESERVED      0x00
#define USB_DEV_CLASS_AUDIO         0x01
#define USB_DEV_CLASS_COMMUNIC      0x02
#define USB_DEV_CLASS_HID           0x03
#define USB_DEV_CLASS_MONITOR       0x04
#define USB_DEV_CLASS_PHYSIC_IF     0x05
#define USB_DEV_CLASS_POWER         0x06
#define USB_DEV_CLASS_IMAGE         0x06
#define USB_DEV_CLASS_PRINTER       0x07
#define USB_DEV_CLASS_STORAGE       0x08
#define USB_DEV_CLASS_HUB           0x09
#define USB_DEV_CLASS_VEN_SPEC      0xFF
#endif

/* USB Hub Class Request */
#ifndef HUB_GET_HUB_DESCRIPTOR
#define HUB_CLEAR_HUB_FEATURE       0x20
#define HUB_CLEAR_PORT_FEATURE      0x23
#define HUB_GET_BUS_STATE           0xA3
#define HUB_GET_HUB_DESCRIPTOR      0xA0
#define HUB_GET_HUB_STATUS          0xA0
#define HUB_GET_PORT_STATUS         0xA3
#define HUB_SET_HUB_DESCRIPTOR      0x20
#define HUB_SET_HUB_FEATURE         0x20
#define HUB_SET_PORT_FEATURE        0x23
#endif

/* Hub Class Feature Selectors */
#ifndef HUB_PORT_RESET
#define HUB_C_HUB_LOCAL_POWER       0
#define HUB_C_HUB_OVER_CURRENT      1
#define HUB_PORT_CONNECTION         0
#define HUB_PORT_ENABLE             1
#define HUB_PORT_SUSPEND            2
#define HUB_PORT_OVER_CURRENT       3
#define HUB_PORT_RESET              4
#define HUB_PORT_POWER              8
#define HUB_PORT_LOW_SPEED          9
#define HUB_C_PORT_CONNECTION       16
#define HUB_C_PORT_ENABLE           17
#define HUB_C_PORT_SUSPEND          18
#define HUB_C_PORT_OVER_CURRENT     19
#define HUB_C_PORT_RESET            20
#endif

/* USB UDisk */
#ifndef USB_BO_CBW_SIZE
#define USB_BO_CBW_SIZE             0x1F
#define USB_BO_CSW_SIZE             0x0D
#endif
#ifndef USB_BO_CBW_SIG0
#define USB_BO_CBW_SIG0             0x55
#define USB_BO_CBW_SIG1             0x53
#define USB_BO_CBW_SIG2             0x42
#define USB_BO_CBW_SIG3             0x43
#define USB_BO_CSW_SIG0             0x55
#define USB_BO_CSW_SIG1             0x53
#define USB_BO_CSW_SIG2             0x42
#define USB_BO_CSW_SIG3             0x53
#endif


/******************************************************************************/
/* USBHS Clock Configuration Related Macro Definition */
#define USB_CLK_SRC                 0x80000000
#define USBHS_PLL_ALIVE             0x40000000
#define USBHS_PLL_CKREF_MASK        0x30000000
#define USBHS_PLL_CKREF_3M          0x00000000
#define USBHS_PLL_CKREF_4M          0x10000000
#define USBHS_PLL_CKREF_8M          0x20000000
#define USBHS_PLL_CKREF_5M          0x30000000
#define USBHS_PLL_SRC               0x08000000
#define USBHS_PLL_SRC_PRE_MASK      0x07000000
#define USBHS_PLL_SRC_PRE_DIV1      0x00000000
#define USBHS_PLL_SRC_PRE_DIV2      0x01000000
#define USBHS_PLL_SRC_PRE_DIV3      0x02000000
#define USBHS_PLL_SRC_PRE_DIV4      0x03000000
#define USBHS_PLL_SRC_PRE_DIV5      0x04000000
#define USBHS_PLL_SRC_PRE_DIV6      0x05000000
#define USBHS_PLL_SRC_PRE_DIV7      0x06000000
#define USBHS_PLL_SRC_PRE_DIV8      0x07000000


/*******************************************************************************/
/* USBHS Related Register Macro Definition */

/* R8_USB_CTRL */
#define USBHS_UC_HOST_MODE          0x80
#define USBHS_UC_SPEED_TYPE         0x60
#define USBHS_UC_SPEED_LOW          0x40
#define USBHS_UC_SPEED_FULL         0x00
#define USBHS_UC_SPEED_HIGH         0x20
#define USBHS_UC_DEV_PU_EN          0x10
#define USBHS_UC_INT_BUSY           0x08
#define USBHS_UC_RESET_SIE          0x04
#define USBHS_UC_CLR_ALL            0x02
#define USBHS_UC_DMA_EN             0x01

/* R8_USB_INT_EN */
#define USBHS_UIE_DEV_NAK           0x80
#define USBHS_UIE_ISO_ACT           0x40
#define USBHS_UIE_SETUP_ACT         0x20
#define USBHS_UIE_FIFO_OV           0x10
#define USBHS_UIE_SOF_ACT           0x08
#define USBHS_UIE_SUSPEND           0x04
#define USBHS_UIE_TRANSFER          0x02
#define USBHS_UIE_DETECT            0x01
#define USBHS_UIE_BUS_RST           0x01

/* R16_USB_DEV_AD */
#define USBHS_MASK_USB_ADDR         0x7F

/* R16_USB_FRAME_NO */
#define USBHS_MICRO_FRAME_NUM       0xE000
#define USBHS_SOF_FRAME_NUM         0x07FF

/* R8_USB_SUSPEND */
#define USBHS_USB_LINESTATE         0x30
#define USBHS_USB_WAKEUP_ST         0x04
#define USBHS_USB_SYS_MOD           0x03

/* R8_USB_SPEED_TYPE */
#define USBHS_USB_SPEED_TYPE        0x03
#define USBHS_USB_SPEED_LOW         0x02
#define USBHS_USB_SPEED_FULL        0x00
#define USBHS_USB_SPEED_HIGH        0x01

/* R8_USB_MIS_ST */
#define USBHS_UMS_SOF_PRES          0x80
#define USBHS_UMS_SOF_ACT           0x40
#define USBHS_UMS_SIE_FREE          0x20
#define USBHS_UMS_R_FIFO_RDY        0x10
#define USBHS_UMS_BUS_RESET         0x08
#define USBHS_UMS_SUSPEND           0x04
#define USBHS_UMS_DEV_ATTACH        0x02
#define USBHS_UMS_SPLIT_CAN         0x01

/* R8_USB_INT_FG */
#define USBHS_UIF_ISO_ACT           0x40
#define USBHS_UIF_SETUP_ACT         0x20
#define USBHS_UIF_FIFO_OV           0x10
#define USBHS_UIF_HST_SOF           0x08
#define USBHS_UIF_SUSPEND           0x04
#define USBHS_UIF_TRANSFER          0x02
#define USBHS_UIF_DETECT            0x01
#define USBHS_UIF_BUS_RST           0x01

/* R8_USB_INT_ST */
#define USBHS_UIS_IS_NAK            0x80
#define USBHS_UIS_TOG_OK            0x40
#define USBHS_UIS_TOKEN_MASK        0x30
#define USBHS_UIS_TOKEN_OUT         0x00
#define USBHS_UIS_TOKEN_SOF         0x10
#define USBHS_UIS_TOKEN_IN          0x20
#define USBHS_UIS_TOKEN_SETUP       0x30
#define USBHS_UIS_ENDP_MASK         0x0F
#define USBHS_UIS_H_RES_MASK        0x0F

/* R16_USB_RX_LEN */
#define USBHS_USB_RX_LEN            0xFFFF

/* R32_UEP_CONFIG */
#define USBHS_UEP15_R_EN            0x80000000
#define USBHS_UEP14_R_EN            0x40000000
#define USBHS_UEP13_R_EN            0x20000000
#define USBHS_UEP12_R_EN            0x10000000
#define USBHS_UEP11_R_EN            0x08000000
#define USBHS_UEP10_R_EN            0x04000000
#define USBHS_UEP9_R_EN             0x02000000
#define USBHS_UEP8_R_EN             0x01000000
#define USBHS_UEP7_R_EN             0x00800000
#define USBHS_UEP6_R_EN             0x00400000
#define USBHS_UEP5_R_EN             0x00200000
#define USBHS_UEP4_R_EN             0x00100000
#define USBHS_UEP3_R_EN             0x00080000
#define USBHS_UEP2_R_EN             0x00040000
#define USBHS_UEP1_R_EN             0x00020000
#define USBHS_UEP0_R_EN             0x00010000
#define USBHS_UEP15_T_EN            0x00008000
#define USBHS_UEP14_T_EN            0x00004000
#define USBHS_UEP13_T_EN            0x00002000
#define USBHS_UEP12_T_EN            0x00001000
#define USBHS_UEP11_T_EN            0x00000800
#define USBHS_UEP10_T_EN            0x00000400
#define USBHS_UEP9_T_EN             0x00000200
#define USBHS_UEP8_T_EN             0x00000100
#define USBHS_UEP7_T_EN             0x00000080
#define USBHS_UEP6_T_EN             0x00000040
#define USBHS_UEP5_T_EN             0x00000020
#define USBHS_UEP4_T_EN             0x00000010
#define USBHS_UEP3_T_EN             0x00000008
#define USBHS_UEP2_T_EN             0x00000004
#define USBHS_UEP1_T_EN             0x00000002
#define USBHS_UEP0_T_EN             0x00000001

/* R32_UEP_TYPE */
#define USBHS_UEP15_R_TYPE          0x80000000
#define USBHS_UEP14_R_TYPE          0x40000000
#define USBHS_UEP13_R_TYPE          0x20000000
#define USBHS_UEP12_R_TYPE          0x10000000
#define USBHS_UEP11_R_TYPE          0x08000000
#define USBHS_UEP10_R_TYPE          0x04000000
#define USBHS_UEP9_R_TYPE           0x02000000
#define USBHS_UEP8_R_TYPE           0x01000000
#define USBHS_UEP7_R_TYPE           0x00800000
#define USBHS_UEP6_R_TYPE           0x00400000
#define USBHS_UEP5_R_TYPE           0x00200000
#define USBHS_UEP4_R_TYPE           0x00100000
#define USBHS_UEP3_R_TYPE           0x00080000
#define USBHS_UEP2_R_TYPE           0x00040000
#define USBHS_UEP1_R_TYPE           0x00020000
#define USBHS_UEP0_R_TYPE           0x00010000
#define USBHS_UEP15_T_TYPE          0x00008000
#define USBHS_UEP14_T_TYPE          0x00004000
#define USBHS_UEP13_T_TYPE          0x00002000
#define USBHS_UEP12_T_TYPE          0x00001000
#define USBHS_UEP11_T_TYPE          0x00000800
#define USBHS_UEP10_T_TYPE          0x00000400
#define USBHS_UEP9_T_TYPE           0x00000200
#define USBHS_UEP8_T_TYPE           0x00000100
#define USBHS_UEP7_T_TYPE           0x00000080
#define USBHS_UEP6_T_TYPE           0x00000040
#define USBHS_UEP5_T_TYPE           0x00000020
#define USBHS_UEP4_T_TYPE           0x00000010
#define USBHS_UEP3_T_TYPE           0x00000008
#define USBHS_UEP2_T_TYPE           0x00000004
#define USBHS_UEP1_T_TYPE           0x00000002
#define USBHS_UEP0_T_TYPE           0x00000001

/* R32_UEP_BUF_MOD */
#define USBHS_UEP15_ISO_BUF_MOD     0x80000000
#define USBHS_UEP14_ISO_BUF_MOD     0x40000000
#define USBHS_UEP13_ISO_BUF_MOD     0x20000000
#define USBHS_UEP12_ISO_BUF_MOD     0x10000000
#define USBHS_UEP11_ISO_BUF_MOD     0x08000000
#define USBHS_UEP10_ISO_BUF_MOD     0x04000000
#define USBHS_UEP9_ISO_BUF_MOD      0x02000000
#define USBHS_UEP8_ISO_BUF_MOD      0x01000000
#define USBHS_UEP7_ISO_BUF_MOD      0x00800000
#define USBHS_UEP6_ISO_BUF_MOD      0x00400000
#define USBHS_UEP5_ISO_BUF_MOD      0x00200000
#define USBHS_UEP4_ISO_BUF_MOD      0x00100000
#define USBHS_UEP3_ISO_BUF_MOD      0x00080000
#define USBHS_UEP2_ISO_BUF_MOD      0x00040000
#define USBHS_UEP1_ISO_BUF_MOD      0x00020000
#define USBHS_UEP0_ISO_BUF_MOD      0x00010000
#define USBHS_UEP15_BUF_MOD         0x00008000
#define USBHS_UEP14_BUF_MOD         0x00004000
#define USBHS_UEP13_BUF_MOD         0x00002000
#define USBHS_UEP12_BUF_MOD         0x00001000
#define USBHS_UEP11_BUF_MOD         0x00000800
#define USBHS_UEP10_BUF_MOD         0x00000400
#define USBHS_UEP9_BUF_MOD          0x00000200
#define USBHS_UEP8_BUF_MOD          0x00000100
#define USBHS_UEP7_BUF_MOD          0x00000080
#define USBHS_UEP6_BUF_MOD          0x00000040
#define USBHS_UEP5_BUF_MOD          0x00000020
#define USBHS_UEP4_BUF_MOD          0x00000010
#define USBHS_UEP3_BUF_MOD          0x00000008
#define USBHS_UEP2_BUF_MOD          0x00000004
#define USBHS_UEP1_BUF_MOD          0x00000002
#define USBHS_UEP0_BUF_MOD          0x00000001

/* R32_UEP0_DMA */
#define USBHS_UEP0_DMA              0x0000FFFF

/* R32_UEPn_TX_DMA, n=1-15 */
#define USBHS_UEPn_TX_DMA           0x0000FFFF

/* R32_UEPn_RX_DMA, n=1-15 */
#define USBHS_UEPn_RX_DMA           0x0000FFFF

/* R16_UEPn_MAX_LEN, n=0-15 */
#define USBHS_UEPn_MAX_LEN          0x07FF

/* R16_UEPn_T_LEN, n=0-15 */
#define USBHS_UEPn_T_LEN            0x07FF

/* R8_UEPn_TX_CTRL, n=0-15 */
#define USBHS_UEP_T_TOG_AUTO        0x20
#define USBHS_UEP_T_TOG_MASK        0x18
#define USBHS_UEP_T_TOG_DATA0       0x00
#define USBHS_UEP_T_TOG_DATA1       0x08
#define USBHS_UEP_T_TOG_DATA2       0x10
#define USBHS_UEP_T_TOG_MDATA       0x18
#define USBHS_UEP_T_RES_MASK        0x03
#define USBHS_UEP_T_RES_ACK         0x00
#define USBHS_UEP_T_RES_NYET        0x01
#define USBHS_UEP_T_RES_NAK         0x02
#define USBHS_UEP_T_RES_STALL       0x03

/* R8_UEPn_TX_CTRL, n=0-15 */
#define USBHS_UEP_R_TOG_AUTO        0x20
#define USBHS_UEP_R_TOG_MASK        0x18
#define USBHS_UEP_R_TOG_DATA0       0x00
#define USBHS_UEP_R_TOG_DATA1       0x08
#define USBHS_UEP_R_TOG_DATA2       0x10
#define USBHS_UEP_R_TOG_MDATA       0x18
#define USBHS_UEP_R_RES_MASK        0x03
#define USBHS_UEP_R_RES_ACK         0x00
#define USBHS_UEP_R_RES_NYET        0x01
#define USBHS_UEP_R_RES_NAK         0x02
#define USBHS_UEP_R_RES_STALL       0x03

/* R8_UHOST_CTRL */
#define USBHS_UH_SOF_EN             0x80
#define USBHS_UH_SOF_FREE           0x40
#define USBHS_UH_PHY_SUSPENDM       0x10
#define USBHS_UH_REMOTE_WKUP        0x08
#define USBHS_UH_TX_BUS_RESUME      0x04
#define USBHS_UH_TX_BUS_SUSPEND     0x02
#define USBHS_UH_TX_BUS_RESET       0x01

/* R32_UH_CONFIG */
#define USBHS_UH_EP_RX_EN           0x00040000
#define USBHS_UH_EP_TX_EN           0x00000008

/* R32_UH_EP_TYPE */
#define USBHS_UH_EP_RX_TYPE         0x00040000
#define USBHS_UH_EP_TX_TYPE         0x00000008

/* R32_UH_RX_DMA */
#define USBHS_UH_RX_DMA             0x0000FFFC

/* R32_UH_TX_DMA */
#define USBHS_UH_TX_DMA             0x0000FFFF

/* R16_UH_RX_MAX_LEN */
#define USBHS_UH_RX_MAX_LEN         0x07FF

/* R8_UH_EP_PID */
#define USBHS_UH_TOKEN_MASK         0xF0
#define USBHS_UH_ENDP_MASK          0x0F

/* R8_UH_RX_CTRL */
#define USBHS_UH_R_DATA_NO          0x40
#define USBHS_UH_R_TOG_AUTO         0x20
#define USBHS_UH_R_TOG_MASK         0x18
#define USBHS_UH_R_TOG_DATA0        0x00
#define USBHS_UH_R_TOG_DATA1        0x08
#define USBHS_UH_R_TOG_DATA2        0x10
#define USBHS_UH_R_TOG_MDATA        0x18
#define USBHS_UH_R_RES_NO           0x04
#define USBHS_UH_R_RES_MASK         0x03
#define USBHS_UH_R_RES_ACK          0x00
#define USBHS_UH_R_RES_NYET         0x01
#define USBHS_UH_R_RES_NAK          0x02
#define USBHS_UH_R_RES_STALL        0x03

/* R16_UH_TX_LEN */
#define USBHS_UH_TX_LEN             0x07FF

/* R8_UH_TX_CTRL */
#define USBHS_UH_T_DATA_NO          0x40
#define USBHS_UH_T_AUTO_TOG         0x20
#define USBHS_UH_T_TOG_MASK         0x18
#define USBHS_UH_T_TOG_DATA0        0x00
#define USBHS_UH_T_TOG_DATA1        0x08
#define USBHS_UH_T_TOG_DATA2        0x10
#define USBHS_UH_T_TOG_MDATA        0x18
#define USBHS_UH_T_RES_NO           0x04
#define USBHS_UH_T_RES_MASK         0x03
#define USBHS_UH_T_RES_ACK          0x00
#define USBHS_UH_T_RES_NYET         0x01
#define USBHS_UH_T_RES_NAK          0x02
#define USBHS_UH_T_RES_STALL        0x03

/* R16_UH_SPLIT_DATA */
#define USBHS_UH_SPLIT_DATA         0x0FFF


/*******************************************************************************/
/* USBFS Related Register Macro Definition */

/* R8_USB_CTRL */
#define USBFS_UC_HOST_MODE          0x80
#define USBFS_UC_LOW_SPEED          0x40
#define USBFS_UC_DEV_PU_EN          0x20
#define USBFS_UC_SYS_CTRL_MASK      0x30
#define USBFS_UC_SYS_CTRL0          0x00
#define USBFS_UC_SYS_CTRL1          0x10
#define USBFS_UC_SYS_CTRL2          0x20
#define USBFS_UC_SYS_CTRL3          0x30
#define USBFS_UC_INT_BUSY           0x08
#define USBFS_UC_RESET_SIE          0x04
#define USBFS_UC_CLR_ALL            0x02
#define USBFS_UC_DMA_EN             0x01

/* R8_USB_INT_EN */
#define USBFS_UIE_DEV_SOF           0x80
#define USBFS_UIE_DEV_NAK           0x40
#define USBFS_UIE_FIFO_OV           0x10
#define USBFS_UIE_HST_SOF           0x08
#define USBFS_UIE_SUSPEND           0x04
#define USBFS_UIE_TRANSFER          0x02
#define USBFS_UIE_DETECT            0x01
#define USBFS_UIE_BUS_RST           0x01

/* R8_USB_DEV_AD */
#define USBFS_UDA_GP_BIT            0x80
#define USBFS_USB_ADDR_MASK         0x7F

/* R8_USB_MIS_ST */
#define USBFS_UMS_SOF_PRES          0x80
#define USBFS_UMS_SOF_ACT           0x40
#define USBFS_UMS_SIE_FREE          0x20
#define USBFS_UMS_R_FIFO_RDY        0x10
#define USBFS_UMS_BUS_RESET         0x08
#define USBFS_UMS_SUSPEND           0x04
#define USBFS_UMS_DM_LEVEL          0x02
#define USBFS_UMS_DEV_ATTACH        0x01

/* R8_USB_INT_FG */
#define USBFS_U_IS_NAK              0x80    // RO, indicate current USB transfer is NAK received
#define USBFS_U_TOG_OK              0x40    // RO, indicate current USB transfer toggle is OK
#define USBFS_U_SIE_FREE            0x20    // RO, indicate USB SIE free status
#define USBFS_UIF_FIFO_OV           0x10    // FIFO overflow interrupt flag for USB, direct bit address clear or write 1 to clear
#define USBFS_UIF_HST_SOF           0x08    // host SOF timer interrupt flag for USB host, direct bit address clear or write 1 to clear
#define USBFS_UIF_SUSPEND           0x04    // USB suspend or resume event interrupt flag, direct bit address clear or write 1 to clear
#define USBFS_UIF_TRANSFER          0x02    // USB transfer completion interrupt flag, direct bit address clear or write 1 to clear
#define USBFS_UIF_DETECT            0x01    // device detected event interrupt flag for USB host mode, direct bit address clear or write 1 to clear
#define USBFS_UIF_BUS_RST           0x01    // bus reset event interrupt flag for USB device mode, direct bit address clear or write 1 to clear

/* R8_USB_INT_ST */
#define USBFS_UIS_IS_NAK            0x80      // RO, indicate current USB transfer is NAK received for USB device mode
#define USBFS_UIS_TOG_OK            0x40      // RO, indicate current USB transfer toggle is OK
#define USBFS_UIS_TOKEN_MASK        0x30      // RO, bit mask of current token PID code received for USB device mode
#define USBFS_UIS_TOKEN_OUT         0x00
#define USBFS_UIS_TOKEN_SOF         0x10
#define USBFS_UIS_TOKEN_IN          0x20
#define USBFS_UIS_TOKEN_SETUP       0x30
// bUIS_TOKEN1 & bUIS_TOKEN0: current token PID code received for USB device mode
//   00: OUT token PID received
//   01: SOF token PID received
//   10: IN token PID received
//   11: SETUP token PID received
#define USBFS_UIS_ENDP_MASK         0x0F      // RO, bit mask of current transfer endpoint number for USB device mode
#define USBFS_UIS_H_RES_MASK        0x0F      // RO, bit mask of current transfer handshake response for USB host mode: 0000=no response, time out from device, others=handshake response PID received

/* R32_USB_OTG_CR */
#define USBFS_CR_SESS_VTH           0x20
#define USBFS_CR_VBUS_VTH           0x10
#define USBFS_CR_OTG_EN             0x08
#define USBFS_CR_IDPU               0x04
#define USBFS_CR_CHARGE_VBUS        0x02
#define USBFS_CR_DISCHAR_VBUS       0x01

/* R32_USB_OTG_SR */
#define USBFS_SR_ID_DIG             0x08
#define USBFS_SR_SESS_END           0x04
#define USBFS_SR_SESS_VLD           0x02
#define USBFS_SR_VBUS_VLD           0x01

/* R8_UDEV_CTRL */
#define USBFS_UD_PD_DIS             0x80      // disable USB UDP/UDM pulldown resistance: 0=enable pulldown, 1=disable
#define USBFS_UD_DP_PIN             0x20      // ReadOnly: indicate current UDP pin level
#define USBFS_UD_DM_PIN             0x10      // ReadOnly: indicate current UDM pin level
#define USBFS_UD_LOW_SPEED          0x04      // enable USB physical port low speed: 0=full speed, 1=low speed
#define USBFS_UD_GP_BIT             0x02      // general purpose bit
#define USBFS_UD_PORT_EN            0x01      // enable USB physical port I/O: 0=disable, 1=enable

/* R8_UEP4_1_MOD */
#define USBFS_UEP1_RX_EN            0x80      // enable USB endpoint 1 receiving (OUT)
#define USBFS_UEP1_TX_EN            0x40      // enable USB endpoint 1 transmittal (IN)
#define USBFS_UEP1_BUF_MOD          0x10      // buffer mode of USB endpoint 1
#define USBFS_UEP4_RX_EN            0x08      // enable USB endpoint 4 receiving (OUT)
#define USBFS_UEP4_TX_EN            0x04      // enable USB endpoint 4 transmittal (IN)
#define USBFS_UEP4_BUF_MOD          0x01

/* R8_UEP2_3_MOD */
#define USBFS_UEP3_RX_EN            0x80      // enable USB endpoint 3 receiving (OUT)
#define USBFS_UEP3_TX_EN            0x40      // enable USB endpoint 3 transmittal (IN)
#define USBFS_UEP3_BUF_MOD          0x10      // buffer mode of USB endpoint 3
#define USBFS_UEP2_RX_EN            0x08      // enable USB endpoint 2 receiving (OUT)
#define USBFS_UEP2_TX_EN            0x04      // enable USB endpoint 2 transmittal (IN)
#define USBFS_UEP2_BUF_MOD          0x01      // buffer mode of USB endpoint 2

/* R8_UEP5_6_MOD */
#define USBFS_UEP6_RX_EN            0x80      // enable USB endpoint 6 receiving (OUT)
#define USBFS_UEP6_TX_EN            0x40      // enable USB endpoint 6 transmittal (IN)
#define USBFS_UEP6_BUF_MOD          0x10      // buffer mode of USB endpoint 6
#define USBFS_UEP5_RX_EN            0x08      // enable USB endpoint 5 receiving (OUT)
#define USBFS_UEP5_TX_EN            0x04      // enable USB endpoint 5 transmittal (IN)
#define USBFS_UEP5_BUF_MOD          0x01      // buffer mode of USB endpoint 5

/* R8_UEP7_MOD */
#define USBFS_UEP7_RX_EN            0x08      // enable USB endpoint 7 receiving (OUT)
#define USBFS_UEP7_TX_EN            0x04      // enable USB endpoint 7 transmittal (IN)
#define USBFS_UEP7_BUF_MOD          0x01      // buffer mode of USB endpoint 7

/* R8_UEPn_TX_CTRL */
#define USBFS_UEP_T_AUTO_TOG        0x08      // enable automatic toggle after successful transfer completion on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle
#define USBFS_UEP_T_TOG             0x04      // prepared data toggle flag of USB endpoint X transmittal (IN): 0=DATA0, 1=DATA1
#define USBFS_UEP_T_RES_MASK        0x03      // bit mask of handshake response type for USB endpoint X transmittal (IN)
#define USBFS_UEP_T_RES_ACK         0x00
#define USBFS_UEP_T_RES_NONE        0x01
#define USBFS_UEP_T_RES_NAK         0x02
#define USBFS_UEP_T_RES_STALL       0x03
// bUEP_T_RES1 & bUEP_T_RES0: handshake response type for USB endpoint X transmittal (IN)
//   00: DATA0 or DATA1 then expecting ACK (ready)
//   01: DATA0 or DATA1 then expecting no response, time out from host, for non-zero endpoint isochronous transactions
//   10: NAK (busy)
//   11: STALL (error)
// host aux setup

/* R8_UEPn_RX_CTRL, n=0-7 */
#define USBFS_UEP_R_AUTO_TOG        0x08      // enable automatic toggle after successful transfer completion on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle
#define USBFS_UEP_R_TOG             0x04      // expected data toggle flag of USB endpoint X receiving (OUT): 0=DATA0, 1=DATA1
#define USBFS_UEP_R_RES_MASK        0x03      // bit mask of handshake response type for USB endpoint X receiving (OUT)
#define USBFS_UEP_R_RES_ACK         0x00
#define USBFS_UEP_R_RES_NONE        0x01
#define USBFS_UEP_R_RES_NAK         0x02
#define USBFS_UEP_R_RES_STALL       0x03
// RB_UEP_R_RES1 & RB_UEP_R_RES0: handshake response type for USB endpoint X receiving (OUT)
//   00: ACK (ready)
//   01: no response, time out to host, for non-zero endpoint isochronous transactions
//   10: NAK (busy)
//   11: STALL (error)

/* R8_UHOST_CTRL */
#define USBFS_UH_PD_DIS             0x80      // disable USB UDP/UDM pulldown resistance: 0=enable pulldown, 1=disable
#define USBFS_UH_DP_PIN             0x20      // ReadOnly: indicate current UDP pin level
#define USBFS_UH_DM_PIN             0x10      // ReadOnly: indicate current UDM pin level
#define USBFS_UH_LOW_SPEED          0x04      // enable USB port low speed: 0=full speed, 1=low speed
#define USBFS_UH_BUS_RESET          0x02      // control USB bus reset: 0=normal, 1=force bus reset
#define USBFS_UH_PORT_EN            0x01      // enable USB port: 0=disable, 1=enable port, automatic disabled if USB device detached

/* R32_UH_EP_MOD */
#define USBFS_UH_EP_TX_EN           0x40      // enable USB host OUT endpoint transmittal
#define USBFS_UH_EP_TBUF_MOD        0x10      // buffer mode of USB host OUT endpoint
// bUH_EP_TX_EN & bUH_EP_TBUF_MOD: USB host OUT endpoint buffer mode, buffer start address is UH_TX_DMA
//   0 x:  disable endpoint and disable buffer
//   1 0:  64 bytes buffer for transmittal (OUT endpoint)
//   1 1:  dual 64 bytes buffer by toggle bit bUH_T_TOG selection for transmittal (OUT endpoint), total=128bytes
#define USBFS_UH_EP_RX_EN           0x08      // enable USB host IN endpoint receiving
#define USBFS_UH_EP_RBUF_MOD        0x01      // buffer mode of USB host IN endpoint
// bUH_EP_RX_EN & bUH_EP_RBUF_MOD: USB host IN endpoint buffer mode, buffer start address is UH_RX_DMA
//   0 x:  disable endpoint and disable buffer
//   1 0:  64 bytes buffer for receiving (IN endpoint)
//   1 1:  dual 64 bytes buffer by toggle bit bUH_R_TOG selection for receiving (IN endpoint), total=128bytes

/* R16_UH_SETUP */
#define USBFS_UH_PRE_PID_EN         0x0400      // USB host PRE PID enable for low speed device via hub
#define USBFS_UH_SOF_EN             0x0004      // USB host automatic SOF enable

/* R8_UH_EP_PID */
#define USBFS_UH_TOKEN_MASK         0xF0      // bit mask of token PID for USB host transfer
#define USBFS_UH_ENDP_MASK          0x0F      // bit mask of endpoint number for USB host transfer

/* R8_UH_RX_CTRL */
#define USBFS_UH_R_AUTO_TOG         0x08      // enable automatic toggle after successful transfer completion: 0=manual toggle, 1=automatic toggle
#define USBFS_UH_R_TOG              0x04      // expected data toggle flag of host receiving (IN): 0=DATA0, 1=DATA1
#define USBFS_UH_R_RES              0x01      // prepared handshake response type for host receiving (IN): 0=ACK (ready), 1=no response, time out to device, for isochronous transactions

/* R8_UH_TX_CTRL */
#define USBFS_UH_T_AUTO_TOG         0x08      // enable automatic toggle after successful transfer completion: 0=manual toggle, 1=automatic toggle
#define USBFS_UH_T_TOG              0x04      // prepared data toggle flag of host transmittal (SETUP/OUT): 0=DATA0, 1=DATA1
#define USBFS_UH_T_RES              0x01      // expected handshake response type for host transmittal (SETUP/OUT): 0=ACK (ready), 1=no response, time out from device, for isochronous transactions


/*******************************************************************************/
/* Struct Definition */

/* USB Setup Request */
typedef struct __attribute__((packed)) _USB_SETUP_REQ
{
    uint8_t  bRequestType;
    uint8_t  bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} USB_SETUP_REQ, *PUSB_SETUP_REQ;

/* USB Device Descriptor */
typedef struct __attribute__((packed)) _USB_DEVICE_DESCR
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdUSB;
    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubClass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t  iManufacturer;
    uint8_t  iProduct;
    uint8_t  iSerialNumber;
    uint8_t  bNumConfigurations;
} USB_DEV_DESCR, *PUSB_DEV_DESCR;

/* USB Configuration Descriptor */
typedef struct __attribute__((packed)) _USB_CONFIG_DESCR
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t wTotalLength;
    uint8_t  bNumInterfaces;
    uint8_t  bConfigurationValue;
    uint8_t  iConfiguration;
    uint8_t  bmAttributes;
    uint8_t  MaxPower;
} USB_CFG_DESCR, *PUSB_CFG_DESCR;

/* USB Interface Descriptor */
typedef struct __attribute__((packed)) _USB_INTERF_DESCR
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bInterfaceNumber;
    uint8_t  bAlternateSetting;
    uint8_t  bNumEndpoints;
    uint8_t  bInterfaceClass;
    uint8_t  bInterfaceSubClass;
    uint8_t  bInterfaceProtocol;
    uint8_t  iInterface;
} USB_ITF_DESCR, *PUSB_ITF_DESCR;

/* USB Endpoint Descriptor */
typedef struct __attribute__((packed)) _USB_ENDPOINT_DESCR
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bEndpointAddress;
    uint8_t  bmAttributes;
    uint8_t  wMaxPacketSizeL;
    uint8_t  wMaxPacketSizeH;
    uint8_t  bInterval;
} USB_ENDP_DESCR, *PUSB_ENDP_DESCR;

/* USB Configuration Descriptor Set */
typedef struct __attribute__((packed)) _USB_CONFIG_DESCR_LONG
{
    USB_CFG_DESCR  cfg_descr;
    USB_ITF_DESCR  itf_descr;
    USB_ENDP_DESCR endp_descr[ 1 ];
} USB_CFG_DESCR_LONG, *PUSB_CFG_DESCR_LONG;

/* USB HUB Descriptor */
typedef struct __attribute__((packed)) _USB_HUB_DESCR
{
    uint8_t  bDescLength;
    uint8_t  bDescriptorType;
    uint8_t  bNbrPorts;
    uint8_t  wHubCharacteristicsL;
    uint8_t  wHubCharacteristicsH;
    uint8_t  bPwrOn2PwrGood;
    uint8_t  bHubContrCurrent;
    uint8_t  DeviceRemovable;
    uint8_t  PortPwrCtrlMask;
} USB_HUB_DESCR, *PUSB_HUB_DESCR;

/* USB HID Descriptor */
typedef struct __attribute__((packed)) _USB_HID_DESCR
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdHID;
    uint8_t  bCountryCode;
    uint8_t  bNumDescriptors;
    uint8_t  bDescriptorTypeX;
    uint8_t  wDescriptorLengthL;
    uint8_t  wDescriptorLengthH;
} USB_HID_DESCR, *PUSB_HID_DESCR;

/* USB UDisk */
typedef struct __attribute__((packed)) _UDISK_BOC_CBW
{
    uint32_t mCBW_Sig;
    uint32_t mCBW_Tag;
    uint32_t mCBW_DataLen;
    uint8_t  mCBW_Flag;
    uint8_t  mCBW_LUN;
    uint8_t  mCBW_CB_Len;
    uint8_t  mCBW_CB_Buf[ 16 ];
} UDISK_BOC_CBW, *PXUDISK_BOC_CBW;

/* USB UDisk */
typedef struct __attribute__((packed)) _UDISK_BOC_CSW
{
    uint32_t mCBW_Sig;
    uint32_t mCBW_Tag;
    uint32_t mCSW_Residue;
    uint8_t  mCSW_Status;
} UDISK_BOC_CSW, *PXUDISK_BOC_CSW;


#ifdef __cplusplus
}
#endif

#endif /* __CH32V30x_USB_H */
