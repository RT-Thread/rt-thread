/********************************** (C) COPYRIGHT  *******************************
 * File Name          : ch32v10x_usb.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2020/04/30
 * Description        : This file contains all the functions prototypes for the USB
 *                      firmware library.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#ifndef __CH32V10x_USB_H
#define __CH32V10x_USB_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
  #define NULL    0
#endif

#ifndef VOID
  #define VOID    void
#endif
#ifndef CONST
  #define CONST    const
#endif
#ifndef BOOL
typedef unsigned char BOOL;
#endif
#ifndef BOOLEAN
typedef unsigned char BOOLEAN;
#endif
#ifndef CHAR
typedef char CHAR;
#endif
#ifndef INT8
typedef char INT8;
#endif
#ifndef INT16
typedef short INT16;
#endif
#ifndef INT32
typedef long INT32;
#endif
#ifndef UINT8
typedef unsigned char UINT8;
#endif
#ifndef UINT16
typedef unsigned short UINT16;
#endif
#ifndef UINT32
typedef unsigned long UINT32;
#endif
#ifndef UINT8V
typedef unsigned char volatile UINT8V;
#endif
#ifndef UINT16V
typedef unsigned short volatile UINT16V;
#endif
#ifndef UINT32V
typedef unsigned long volatile UINT32V;
#endif

#ifndef PVOID
typedef void *PVOID;
#endif
#ifndef PCHAR
typedef char *PCHAR;
#endif
#ifndef PCHAR
typedef const char *PCCHAR;
#endif
#ifndef PINT8
typedef char *PINT8;
#endif
#ifndef PINT16
typedef short *PINT16;
#endif
#ifndef PINT32
typedef long *PINT32;
#endif
#ifndef PUINT8
typedef unsigned char *PUINT8;
#endif
#ifndef PUINT16
typedef unsigned short *PUINT16;
#endif
#ifndef PUINT32
typedef unsigned long *PUINT32;
#endif
#ifndef PUINT8V
typedef volatile unsigned char *PUINT8V;
#endif
#ifndef PUINT16V
typedef volatile unsigned short *PUINT16V;
#endif
#ifndef PUINT32V
typedef volatile unsigned long *PUINT32V;
#endif

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/*       USB  */
#define R32_USB_CONTROL      (*((PUINT32V)(0x40023400))) // USB control & interrupt enable & device address
#define R8_USB_CTRL          (*((PUINT8V)(0x40023400)))  // USB base control
#define RB_UC_HOST_MODE      0x80                        // enable USB host mode: 0=device mode, 1=host mode
#define RB_UC_LOW_SPEED      0x40                        // enable USB low speed: 0=12Mbps, 1=1.5Mbps
#define RB_UC_DEV_PU_EN      0x20                        // USB device enable and internal pullup resistance enable
#define RB_UC_SYS_CTRL1      0x20                        // USB system control high bit
#define RB_UC_SYS_CTRL0      0x10                        // USB system control low bit
#define MASK_UC_SYS_CTRL     0x30                        // bit mask of USB system control
// bUC_HOST_MODE & bUC_SYS_CTRL1 & bUC_SYS_CTRL0: USB system control
//   0 00: disable USB device and disable internal pullup resistance
//   0 01: enable USB device and disable internal pullup resistance, need external pullup resistance
//   0 1x: enable USB device and enable internal pullup resistance
//   1 00: enable USB host and normal status
//   1 01: enable USB host and force UDP/UDM output SE0 state
//   1 10: enable USB host and force UDP/UDM output J state
//   1 11: enable USB host and force UDP/UDM output resume or K state
#define RB_UC_INT_BUSY       0x08           // enable automatic responding busy for device mode or automatic pause for host mode during interrupt flag UIF_TRANSFER valid
#define RB_UC_RESET_SIE      0x04           // force reset USB SIE, need software clear
#define RB_UC_CLR_ALL        0x02           // force clear FIFO and count of USB
#define RB_UC_DMA_EN         0x01           // DMA enable and DMA interrupt enable for USB

#define R8_UDEV_CTRL         (*((PUINT8V)(0x40023401))) // USB device physical prot control
#define RB_UD_PD_DIS         0x80                       // disable USB UDP/UDM pulldown resistance: 0=enable pulldown, 1=disable
#define RB_UD_DP_PIN         0x20                       // ReadOnly: indicate current UDP pin level
#define RB_UD_DM_PIN         0x10                       // ReadOnly: indicate current UDM pin level
#define RB_UD_LOW_SPEED      0x04                       // enable USB physical port low speed: 0=full speed, 1=low speed
#define RB_UD_GP_BIT         0x02                       // general purpose bit
#define RB_UD_PORT_EN        0x01                       // enable USB physical port I/O: 0=disable, 1=enable

#define R8_UHOST_CTRL        R8_UDEV_CTRL   // USB host physical prot control
#define RB_UH_PD_DIS         0x80           // disable USB UDP/UDM pulldown resistance: 0=enable pulldown, 1=disable
#define RB_UH_DP_PIN         0x20           // ReadOnly: indicate current UDP pin level
#define RB_UH_DM_PIN         0x10           // ReadOnly: indicate current UDM pin level
#define RB_UH_LOW_SPEED      0x04           // enable USB port low speed: 0=full speed, 1=low speed
#define RB_UH_BUS_RESET      0x02           // control USB bus reset: 0=normal, 1=force bus reset
#define RB_UH_PORT_EN        0x01           // enable USB port: 0=disable, 1=enable port, automatic disabled if USB device detached

#define R8_USB_INT_EN        (*((PUINT8V)(0x40023402))) // USB interrupt enable
#define RB_UIE_DEV_SOF       0x80                       // enable interrupt for SOF received for USB device mode
#define RB_UIE_DEV_NAK       0x40                       // enable interrupt for NAK responded for USB device mode
#define RB_UIE_FIFO_OV       0x10                       // enable interrupt for FIFO overflow
#define RB_UIE_HST_SOF       0x08                       // enable interrupt for host SOF timer action for USB host mode
#define RB_UIE_SUSPEND       0x04                       // enable interrupt for USB suspend or resume event
#define RB_UIE_TRANSFER      0x02                       // enable interrupt for USB transfer completion
#define RB_UIE_DETECT        0x01                       // enable interrupt for USB device detected event for USB host mode
#define RB_UIE_BUS_RST       0x01                       // enable interrupt for USB bus reset event for USB device mode

#define R8_USB_DEV_AD        (*((PUINT8V)(0x40023403))) // USB device address
#define RB_UDA_GP_BIT        0x80                       // general purpose bit
#define MASK_USB_ADDR        0x7F                       // bit mask for USB device address

#define R32_USB_STATUS       (*((PUINT32V)(0x40023404))) // USB miscellaneous status & interrupt flag & interrupt status
#define R8_USB_MIS_ST        (*((PUINT8V)(0x40023405)))  // USB miscellaneous status
#define RB_UMS_SOF_PRES      0x80                        // RO, indicate host SOF timer presage status
#define RB_UMS_SOF_ACT       0x40                        // RO, indicate host SOF timer action status for USB host
#define RB_UMS_SIE_FREE      0x20                        // RO, indicate USB SIE free status
#define RB_UMS_R_FIFO_RDY    0x10                        // RO, indicate USB receiving FIFO ready status (not empty)
#define RB_UMS_BUS_RESET     0x08                        // RO, indicate USB bus reset status
#define RB_UMS_SUSPEND       0x04                        // RO, indicate USB suspend status
#define RB_UMS_DM_LEVEL      0x02                        // RO, indicate UDM level saved at device attached to USB host
#define RB_UMS_DEV_ATTACH    0x01                        // RO, indicate device attached status on USB host

#define R8_USB_INT_FG        (*((PUINT8V)(0x40023406))) // USB interrupt flag
#define RB_U_IS_NAK          0x80                       // RO, indicate current USB transfer is NAK received
#define RB_U_TOG_OK          0x40                       // RO, indicate current USB transfer toggle is OK
#define RB_U_SIE_FREE        0x20                       // RO, indicate USB SIE free status
#define RB_UIF_FIFO_OV       0x10                       // FIFO overflow interrupt flag for USB, direct bit address clear or write 1 to clear
#define RB_UIF_HST_SOF       0x08                       // host SOF timer interrupt flag for USB host, direct bit address clear or write 1 to clear
#define RB_UIF_SUSPEND       0x04                       // USB suspend or resume event interrupt flag, direct bit address clear or write 1 to clear
#define RB_UIF_TRANSFER      0x02                       // USB transfer completion interrupt flag, direct bit address clear or write 1 to clear
#define RB_UIF_DETECT        0x01                       // device detected event interrupt flag for USB host mode, direct bit address clear or write 1 to clear
#define RB_UIF_BUS_RST       0x01                       // bus reset event interrupt flag for USB device mode, direct bit address clear or write 1 to clear

#define R8_USB_INT_ST        (*((PUINT8V)(0x40023407))) // USB interrupt status
#define RB_UIS_IS_NAK        0x80                       // RO, indicate current USB transfer is NAK received for USB device mode
#define RB_UIS_TOG_OK        0x40                       // RO, indicate current USB transfer toggle is OK
#define RB_UIS_TOKEN1        0x20                       // RO, current token PID code bit 1 received for USB device mode
#define RB_UIS_TOKEN0        0x10                       // RO, current token PID code bit 0 received for USB device mode
#define MASK_UIS_TOKEN       0x30                       // RO, bit mask of current token PID code received for USB device mode
#define UIS_TOKEN_OUT        0x00
#define UIS_TOKEN_SOF        0x10
#define UIS_TOKEN_IN         0x20
#define UIS_TOKEN_SETUP      0x30
// bUIS_TOKEN1 & bUIS_TOKEN0: current token PID code received for USB device mode
//   00: OUT token PID received
//   01: SOF token PID received
//   10: IN token PID received
//   11: SETUP token PID received
#define MASK_UIS_ENDP        0x0F           // RO, bit mask of current transfer endpoint number for USB device mode
#define MASK_UIS_H_RES       0x0F           // RO, bit mask of current transfer handshake response for USB host mode: 0000=no response, time out from device, others=handshake response PID received

#define R8_USB_RX_LEN        (*((PUINT8V)(0x40023408)))  // USB receiving length
#define R32_USB_BUF_MODE     (*((PUINT32V)(0x4002340c))) // USB endpoint buffer mode
#define R8_UEP4_1_MOD        (*((PUINT8V)(0x4002340c)))  // endpoint 4/1 mode
#define RB_UEP1_RX_EN        0x80                        // enable USB endpoint 1 receiving (OUT)
#define RB_UEP1_TX_EN        0x40                        // enable USB endpoint 1 transmittal (IN)
#define RB_UEP1_BUF_MOD      0x10                        // buffer mode of USB endpoint 1
// bUEPn_RX_EN & bUEPn_TX_EN & bUEPn_BUF_MOD: USB endpoint 1/2/3 buffer mode, buffer start address is UEPn_DMA
//   0 0 x:  disable endpoint and disable buffer
//   1 0 0:  64 bytes buffer for receiving (OUT endpoint)
//   1 0 1:  dual 64 bytes buffer by toggle bit bUEP_R_TOG selection for receiving (OUT endpoint), total=128bytes
//   0 1 0:  64 bytes buffer for transmittal (IN endpoint)
//   0 1 1:  dual 64 bytes buffer by toggle bit bUEP_T_TOG selection for transmittal (IN endpoint), total=128bytes
//   1 1 0:  64 bytes buffer for receiving (OUT endpoint) + 64 bytes buffer for transmittal (IN endpoint), total=128bytes
//   1 1 1:  dual 64 bytes buffer by bUEP_R_TOG selection for receiving (OUT endpoint) + dual 64 bytes buffer by bUEP_T_TOG selection for transmittal (IN endpoint), total=256bytes
#define RB_UEP4_RX_EN        0x08           // enable USB endpoint 4 receiving (OUT)
#define RB_UEP4_TX_EN        0x04           // enable USB endpoint 4 transmittal (IN)
// bUEP4_RX_EN & bUEP4_TX_EN: USB endpoint 4 buffer mode, buffer start address is UEP0_DMA
//   0 0:  single 64 bytes buffer for endpoint 0 receiving & transmittal (OUT & IN endpoint)
//   1 0:  single 64 bytes buffer for endpoint 0 receiving & transmittal (OUT & IN endpoint) + 64 bytes buffer for endpoint 4 receiving (OUT endpoint), total=128bytes
//   0 1:  single 64 bytes buffer for endpoint 0 receiving & transmittal (OUT & IN endpoint) + 64 bytes buffer for endpoint 4 transmittal (IN endpoint), total=128bytes
//   1 1:  single 64 bytes buffer for endpoint 0 receiving & transmittal (OUT & IN endpoint)
//           + 64 bytes buffer for endpoint 4 receiving (OUT endpoint) + 64 bytes buffer for endpoint 4 transmittal (IN endpoint), total=192bytes

#define R8_UEP2_3_MOD        (*((PUINT8V)(0x4002340d))) // endpoint 2/3 mode
#define RB_UEP3_RX_EN        0x80                       // enable USB endpoint 3 receiving (OUT)
#define RB_UEP3_TX_EN        0x40                       // enable USB endpoint 3 transmittal (IN)
#define RB_UEP3_BUF_MOD      0x10                       // buffer mode of USB endpoint 3
#define RB_UEP2_RX_EN        0x08                       // enable USB endpoint 2 receiving (OUT)
#define RB_UEP2_TX_EN        0x04                       // enable USB endpoint 2 transmittal (IN)
#define RB_UEP2_BUF_MOD      0x01                       // buffer mode of USB endpoint 2

#define R8_UH_EP_MOD         R8_UEP2_3_MOD  //host endpoint mode
#define RB_UH_EP_TX_EN       0x40           // enable USB host OUT endpoint transmittal
#define RB_UH_EP_TBUF_MOD    0x10           // buffer mode of USB host OUT endpoint
// bUH_EP_TX_EN & bUH_EP_TBUF_MOD: USB host OUT endpoint buffer mode, buffer start address is UH_TX_DMA
//   0 x:  disable endpoint and disable buffer
//   1 0:  64 bytes buffer for transmittal (OUT endpoint)
//   1 1:  dual 64 bytes buffer by toggle bit bUH_T_TOG selection for transmittal (OUT endpoint), total=128bytes
#define RB_UH_EP_RX_EN       0x08           // enable USB host IN endpoint receiving
#define RB_UH_EP_RBUF_MOD    0x01           // buffer mode of USB host IN endpoint
// bUH_EP_RX_EN & bUH_EP_RBUF_MOD: USB host IN endpoint buffer mode, buffer start address is UH_RX_DMA
//   0 x:  disable endpoint and disable buffer
//   1 0:  64 bytes buffer for receiving (IN endpoint)
//   1 1:  dual 64 bytes buffer by toggle bit bUH_R_TOG selection for receiving (IN endpoint), total=128bytes

#define R8_UEP5_6_MOD        (*((PUINT8V)(0x4002340e))) // endpoint 5/6 mode
#define RB_UEP6_RX_EN        0x80                       // enable USB endpoint 6 receiving (OUT)
#define RB_UEP6_TX_EN        0x40                       // enable USB endpoint 6 transmittal (IN)
#define RB_UEP6_BUF_MOD      0x10                       // buffer mode of USB endpoint 6
#define RB_UEP5_RX_EN        0x08                       // enable USB endpoint 5 receiving (OUT)
#define RB_UEP5_TX_EN        0x04                       // enable USB endpoint 5 transmittal (IN)
#define RB_UEP5_BUF_MOD      0x01                       // buffer mode of USB endpoint 5

#define R8_UEP7_MOD          (*((PUINT8V)(0x4002340f))) // endpoint 7 mode
#define RB_UEP7_RX_EN        0x08                       // enable USB endpoint 7 receiving (OUT)
#define RB_UEP7_TX_EN        0x04                       // enable USB endpoint 7 transmittal (IN)
#define RB_UEP7_BUF_MOD      0x01                       // buffer mode of USB endpoint 7

#define R16_UEP0_DMA         (*((PUINT16V)(0x40023410))) // endpoint 0 DMA buffer address
#define R16_UEP1_DMA         (*((PUINT16V)(0x40023414))) // endpoint 1 DMA buffer address
#define R16_UEP2_DMA         (*((PUINT16V)(0x40023418))) // endpoint 2 DMA buffer address
#define R16_UH_RX_DMA        R16_UEP2_DMA                // host rx endpoint buffer high address
#define R16_UEP3_DMA         (*((PUINT16V)(0x4002341c))) // endpoint 3 DMA buffer address

#define R16_UEP4_DMA         (*((PUINT16V)(0x40023420))) // endpoint 4 DMA buffer address
#define R16_UEP5_DMA         (*((PUINT16V)(0x40023424))) // endpoint 5 DMA buffer address
#define R16_UEP6_DMA         (*((PUINT16V)(0x40023428))) // endpoint 6 DMA buffer address
#define R16_UEP7_DMA         (*((PUINT16V)(0x4002342c))) // endpoint 7 DMA buffer address

#define R16_UH_TX_DMA        R16_UEP3_DMA                // host tx endpoint buffer high address
#define R32_USB_EP0_CTRL     (*((PUINT32V)(0x40023430))) // endpoint 0 control & transmittal length
#define R8_UEP0_T_LEN        (*((PUINT8V)(0x40023430)))  // endpoint 0 transmittal length
#define R8_UEP0_CTRL         (*((PUINT8V)(0x40023432)))  // endpoint 0 control
#define R32_USB_EP1_CTRL     (*((PUINT32V)(0x40023434))) // endpoint 1 control & transmittal length
#define R8_UEP1_T_LEN        (*((PUINT8V)(0x40023434)))  // endpoint 1 transmittal length
#define R8_UEP1_CTRL         (*((PUINT8V)(0x40023436)))  // endpoint 1 control
#define RB_UEP_R_TOG         0x80                        // expected data toggle flag of USB endpoint X receiving (OUT): 0=DATA0, 1=DATA1
#define RB_UEP_T_TOG         0x40                        // prepared data toggle flag of USB endpoint X transmittal (IN): 0=DATA0, 1=DATA1
#define RB_UEP_AUTO_TOG      0x10                        // enable automatic toggle after successful transfer completion on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle
#define RB_UEP_R_RES1        0x08                        // handshake response type high bit for USB endpoint X receiving (OUT)
#define RB_UEP_R_RES0        0x04                        // handshake response type low bit for USB endpoint X receiving (OUT)
#define MASK_UEP_R_RES       0x0C                        // bit mask of handshake response type for USB endpoint X receiving (OUT)
#define UEP_R_RES_ACK        0x00
#define UEP_R_RES_TOUT       0x04
#define UEP_R_RES_NAK        0x08
#define UEP_R_RES_STALL      0x0C
// RB_UEP_R_RES1 & RB_UEP_R_RES0: handshake response type for USB endpoint X receiving (OUT)
//   00: ACK (ready)
//   01: no response, time out to host, for non-zero endpoint isochronous transactions
//   10: NAK (busy)
//   11: STALL (error)
#define RB_UEP_T_RES1        0x02           // handshake response type high bit for USB endpoint X transmittal (IN)
#define RB_UEP_T_RES0        0x01           // handshake response type low bit for USB endpoint X transmittal (IN)
#define MASK_UEP_T_RES       0x03           // bit mask of handshake response type for USB endpoint X transmittal (IN)
#define UEP_T_RES_ACK        0x00
#define UEP_T_RES_TOUT       0x01
#define UEP_T_RES_NAK        0x02
#define UEP_T_RES_STALL      0x03
// bUEP_T_RES1 & bUEP_T_RES0: handshake response type for USB endpoint X transmittal (IN)
//   00: DATA0 or DATA1 then expecting ACK (ready)
//   01: DATA0 or DATA1 then expecting no response, time out from host, for non-zero endpoint isochronous transactions
//   10: NAK (busy)
//   11: STALL (error)

#define R8_UH_SETUP          R8_UEP1_CTRL   // host aux setup
#define RB_UH_PRE_PID_EN     0x80           // USB host PRE PID enable for low speed device via hub
#define RB_UH_SOF_EN         0x40           // USB host automatic SOF enable

#define R32_USB_EP2_CTRL     (*((PUINT32V)(0x40023438))) // endpoint 2 control & transmittal length
#define R8_UEP2_T_LEN        (*((PUINT8V)(0x40023438)))  // endpoint 2 transmittal length
#define R8_UEP2_CTRL         (*((PUINT8V)(0x4002343a)))  // endpoint 2 control

#define R8_UH_EP_PID         R8_UEP2_T_LEN  // host endpoint and PID
#define MASK_UH_TOKEN        0xF0           // bit mask of token PID for USB host transfer
#define MASK_UH_ENDP         0x0F           // bit mask of endpoint number for USB host transfer

#define R8_UH_RX_CTRL        R8_UEP2_CTRL   // host receiver endpoint control
#define RB_UH_R_TOG          0x80           // expected data toggle flag of host receiving (IN): 0=DATA0, 1=DATA1
#define RB_UH_R_AUTO_TOG     0x10           // enable automatic toggle after successful transfer completion: 0=manual toggle, 1=automatic toggle
#define RB_UH_R_RES          0x04           // prepared handshake response type for host receiving (IN): 0=ACK (ready), 1=no response, time out to device, for isochronous transactions

#define R32_USB_EP3_CTRL     (*((PUINT32V)(0x4002343c))) // endpoint 3 control & transmittal length
#define R8_UEP3_T_LEN        (*((PUINT16V)(0x4002343c))) // endpoint 3 transmittal length
#define R8_UEP3_CTRL         (*((PUINT8V)(0x4002343e)))  // endpoint 3 control
#define R8_UH_TX_LEN         (*((PUINT16V)(0x4002343c))) //R8_UEP3_T_LEN				// host transmittal endpoint transmittal length

#define R8_UH_TX_CTRL        R8_UEP3_CTRL   // host transmittal endpoint control
#define RB_UH_T_TOG          0x40           // prepared data toggle flag of host transmittal (SETUP/OUT): 0=DATA0, 1=DATA1
#define RB_UH_T_AUTO_TOG     0x10           // enable automatic toggle after successful transfer completion: 0=manual toggle, 1=automatic toggle
#define RB_UH_T_RES          0x01           // expected handshake response type for host transmittal (SETUP/OUT): 0=ACK (ready), 1=no response, time out from device, for isochronous transactions

#define R32_USB_EP4_CTRL     (*((PUINT32V)(0x40023440))) // endpoint 4 control & transmittal length
#define R8_UEP4_T_LEN        (*((PUINT8V)(0x40023440)))  // endpoint 4 transmittal length
#define R8_UEP4_CTRL         (*((PUINT8V)(0x40023442)))  // endpoint 4 control

#define R32_USB_EP5_CTRL     (*((PUINT32V)(0x40023444))) // endpoint 5 control & transmittal length
#define R8_UEP5_T_LEN        (*((PUINT8V)(0x40023444)))  // endpoint 5 transmittal length
#define R8_UEP5_CTRL         (*((PUINT8V)(0x40023446)))  // endpoint 5 control

#define R32_USB_EP6_CTRL     (*((PUINT32V)(0x40023448))) // endpoint 6 control & transmittal length
#define R8_UEP6_T_LEN        (*((PUINT8V)(0x40023448)))  // endpoint 6 transmittal length
#define R8_UEP6_CTRL         (*((PUINT8V)(0x4002344a)))  // endpoint 6 control

#define R32_USB_EP7_CTRL     (*((PUINT32V)(0x4002344c))) // endpoint 7 control & transmittal length
#define R8_UEP7_T_LEN        (*((PUINT8V)(0x4002344c)))  // endpoint 7 transmittal length
#define R8_UEP7_CTRL         (*((PUINT8V)(0x4002344e)))  // endpoint 7 control

#ifdef __cplusplus
}
#endif

#endif //__CH32V10x_USB_H

#ifndef __USB_TYPE__
#define __USB_TYPE__

#ifdef __cplusplus
extern "C" {
#endif

/* USB constant and structure define */

/* USB PID */
#ifndef USB_PID_SETUP
  #define USB_PID_NULL     0x00  /* reserved PID */
  #define USB_PID_SOF      0x05
  #define USB_PID_SETUP    0x0D
  #define USB_PID_IN       0x09
  #define USB_PID_OUT      0x01
  #define USB_PID_ACK      0x02
  #define USB_PID_NAK      0x0A
  #define USB_PID_STALL    0x0E
  #define USB_PID_DATA0    0x03
  #define USB_PID_DATA1    0x0B
  #define USB_PID_PRE      0x0C
#endif

/* USB standard device request code */
#ifndef USB_GET_DESCRIPTOR
  #define USB_GET_STATUS           0x00
  #define USB_CLEAR_FEATURE        0x01
  #define USB_SET_FEATURE          0x03
  #define USB_SET_ADDRESS          0x05
  #define USB_GET_DESCRIPTOR       0x06
  #define USB_SET_DESCRIPTOR       0x07
  #define USB_GET_CONFIGURATION    0x08
  #define USB_SET_CONFIGURATION    0x09
  #define USB_GET_INTERFACE        0x0A
  #define USB_SET_INTERFACE        0x0B
  #define USB_SYNCH_FRAME          0x0C
#endif

/* USB hub class request code */
#ifndef HUB_GET_DESCRIPTOR
  #define HUB_GET_STATUS        0x00
  #define HUB_CLEAR_FEATURE     0x01
  #define HUB_GET_STATE         0x02
  #define HUB_SET_FEATURE       0x03
  #define HUB_GET_DESCRIPTOR    0x06
  #define HUB_SET_DESCRIPTOR    0x07
#endif

/* USB HID class request code */
#ifndef HID_GET_REPORT
  #define HID_GET_REPORT      0x01
  #define HID_GET_IDLE        0x02
  #define HID_GET_PROTOCOL    0x03
  #define HID_SET_REPORT      0x09
  #define HID_SET_IDLE        0x0A
  #define HID_SET_PROTOCOL    0x0B
#endif

/* Bit define for USB request type */
#ifndef USB_REQ_TYP_MASK
  #define USB_REQ_TYP_IN          0x80  /* control IN, device to host */
  #define USB_REQ_TYP_OUT         0x00  /* control OUT, host to device */
  #define USB_REQ_TYP_READ        0x80  /* control read, device to host */
  #define USB_REQ_TYP_WRITE       0x00  /* control write, host to device */
  #define USB_REQ_TYP_MASK        0x60  /* bit mask of request type */
  #define USB_REQ_TYP_STANDARD    0x00
  #define USB_REQ_TYP_CLASS       0x20
  #define USB_REQ_TYP_VENDOR      0x40
  #define USB_REQ_TYP_RESERVED    0x60
  #define USB_REQ_RECIP_MASK      0x1F  /* bit mask of request recipient */
  #define USB_REQ_RECIP_DEVICE    0x00
  #define USB_REQ_RECIP_INTERF    0x01
  #define USB_REQ_RECIP_ENDP      0x02
  #define USB_REQ_RECIP_OTHER     0x03
#endif

/* USB request type for hub class request */
#ifndef HUB_GET_HUB_DESCRIPTOR
  #define HUB_CLEAR_HUB_FEATURE     0x20
  #define HUB_CLEAR_PORT_FEATURE    0x23
  #define HUB_GET_BUS_STATE         0xA3
  #define HUB_GET_HUB_DESCRIPTOR    0xA0
  #define HUB_GET_HUB_STATUS        0xA0
  #define HUB_GET_PORT_STATUS       0xA3
  #define HUB_SET_HUB_DESCRIPTOR    0x20
  #define HUB_SET_HUB_FEATURE       0x20
  #define HUB_SET_PORT_FEATURE      0x23
#endif

/* Hub class feature selectors */
#ifndef HUB_PORT_RESET
  #define HUB_C_HUB_LOCAL_POWER      0
  #define HUB_C_HUB_OVER_CURRENT     1
  #define HUB_PORT_CONNECTION        0
  #define HUB_PORT_ENABLE            1
  #define HUB_PORT_SUSPEND           2
  #define HUB_PORT_OVER_CURRENT      3
  #define HUB_PORT_RESET             4
  #define HUB_PORT_POWER             8
  #define HUB_PORT_LOW_SPEED         9
  #define HUB_C_PORT_CONNECTION      16
  #define HUB_C_PORT_ENABLE          17
  #define HUB_C_PORT_SUSPEND         18
  #define HUB_C_PORT_OVER_CURRENT    19
  #define HUB_C_PORT_RESET           20
#endif

/* USB descriptor type */
#ifndef USB_DESCR_TYP_DEVICE
  #define USB_DESCR_TYP_DEVICE     0x01
  #define USB_DESCR_TYP_CONFIG     0x02
  #define USB_DESCR_TYP_STRING     0x03
  #define USB_DESCR_TYP_INTERF     0x04
  #define USB_DESCR_TYP_ENDP       0x05
  #define USB_DESCR_TYP_QUALIF     0x06
  #define USB_DESCR_TYP_SPEED      0x07
  #define USB_DESCR_TYP_OTG        0x09
  #define USB_DESCR_TYP_HID        0x21
  #define USB_DESCR_TYP_REPORT     0x22
  #define USB_DESCR_TYP_PHYSIC     0x23
  #define USB_DESCR_TYP_CS_INTF    0x24
  #define USB_DESCR_TYP_CS_ENDP    0x25
  #define USB_DESCR_TYP_HUB        0x29
#endif

/* USB device class */
#ifndef USB_DEV_CLASS_HUB
  #define USB_DEV_CLASS_RESERVED     0x00
  #define USB_DEV_CLASS_AUDIO        0x01
  #define USB_DEV_CLASS_COMMUNIC     0x02
  #define USB_DEV_CLASS_HID          0x03
  #define USB_DEV_CLASS_MONITOR      0x04
  #define USB_DEV_CLASS_PHYSIC_IF    0x05
  #define USB_DEV_CLASS_POWER        0x06
  #define USB_DEV_CLASS_PRINTER      0x07
  #define USB_DEV_CLASS_STORAGE      0x08
  #define USB_DEV_CLASS_HUB          0x09
  #define USB_DEV_CLASS_VEN_SPEC     0xFF
#endif

/* USB endpoint type and attributes */
#ifndef USB_ENDP_TYPE_MASK
  #define USB_ENDP_DIR_MASK      0x80
  #define USB_ENDP_ADDR_MASK     0x0F
  #define USB_ENDP_TYPE_MASK     0x03
  #define USB_ENDP_TYPE_CTRL     0x00
  #define USB_ENDP_TYPE_ISOCH    0x01
  #define USB_ENDP_TYPE_BULK     0x02
  #define USB_ENDP_TYPE_INTER    0x03
#endif

#ifndef USB_DEVICE_ADDR
  #define USB_DEVICE_ADDR    0x02
#endif
#ifndef DEFAULT_ENDP0_SIZE
  #define DEFAULT_ENDP0_SIZE    8  /* default maximum packet size for endpoint 0 */
#endif
#ifndef MAX_PACKET_SIZE
  #define MAX_PACKET_SIZE    64  /* maximum packet size */
#endif
#ifndef USB_BO_CBW_SIZE
  #define USB_BO_CBW_SIZE    0x1F
  #define USB_BO_CSW_SIZE    0x0D
#endif
#ifndef USB_BO_CBW_SIG0
  #define USB_BO_CBW_SIG0    0x55
  #define USB_BO_CBW_SIG1    0x53
  #define USB_BO_CBW_SIG2    0x42
  #define USB_BO_CBW_SIG3    0x43
  #define USB_BO_CSW_SIG0    0x55
  #define USB_BO_CSW_SIG1    0x53
  #define USB_BO_CSW_SIG2    0x42
  #define USB_BO_CSW_SIG3    0x53
#endif

#ifndef __PACKED
  #define __PACKED    __attribute__((packed))
#endif

typedef struct __PACKED _USB_SETUP_REQ
{
    UINT8  bRequestType;
    UINT8  bRequest;
    UINT16 wValue;
    UINT16 wIndex;
    UINT16 wLength;
} USB_SETUP_REQ, *PUSB_SETUP_REQ;

typedef struct __PACKED _USB_DEVICE_DESCR
{
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT16 bcdUSB;
    UINT8  bDeviceClass;
    UINT8  bDeviceSubClass;
    UINT8  bDeviceProtocol;
    UINT8  bMaxPacketSize0;
    UINT16 idVendor;
    UINT16 idProduct;
    UINT16 bcdDevice;
    UINT8  iManufacturer;
    UINT8  iProduct;
    UINT8  iSerialNumber;
    UINT8  bNumConfigurations;
} USB_DEV_DESCR, *PUSB_DEV_DESCR;

typedef struct __PACKED _USB_CONFIG_DESCR
{
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT16 wTotalLength;
    UINT8  bNumInterfaces;
    UINT8  bConfigurationValue;
    UINT8  iConfiguration;
    UINT8  bmAttributes;
    UINT8  MaxPower;
} USB_CFG_DESCR, *PUSB_CFG_DESCR;

typedef struct __PACKED _USB_INTERF_DESCR
{
    UINT8 bLength;
    UINT8 bDescriptorType;
    UINT8 bInterfaceNumber;
    UINT8 bAlternateSetting;
    UINT8 bNumEndpoints;
    UINT8 bInterfaceClass;
    UINT8 bInterfaceSubClass;
    UINT8 bInterfaceProtocol;
    UINT8 iInterface;
} USB_ITF_DESCR, *PUSB_ITF_DESCR;

typedef struct __PACKED _USB_ENDPOINT_DESCR
{
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT8  bEndpointAddress;
    UINT8  bmAttributes;
    UINT16 wMaxPacketSize;
    UINT8  bInterval;
} USB_ENDP_DESCR, *PUSB_ENDP_DESCR;

typedef struct __PACKED _USB_CONFIG_DESCR_LONG
{
    USB_CFG_DESCR  cfg_descr;
    USB_ITF_DESCR  itf_descr;
    USB_ENDP_DESCR endp_descr[1];
} USB_CFG_DESCR_LONG, *PUSB_CFG_DESCR_LONG;

typedef struct __PACKED _USB_HUB_DESCR
{
    UINT8 bDescLength;
    UINT8 bDescriptorType;
    UINT8 bNbrPorts;
    UINT8 wHubCharacteristicsL;
    UINT8 wHubCharacteristicsH;
    UINT8 bPwrOn2PwrGood;
    UINT8 bHubContrCurrent;
    UINT8 DeviceRemovable;
    UINT8 PortPwrCtrlMask;
} USB_HUB_DESCR, *PUSB_HUB_DESCR;

typedef struct __PACKED _USB_HID_DESCR
{
    UINT8  bLength;
    UINT8  bDescriptorType;
    UINT16 bcdHID;
    UINT8  bCountryCode;
    UINT8  bNumDescriptors;
    UINT8  bDescriptorTypeX;
    UINT8  wDescriptorLengthL;
    UINT8  wDescriptorLengthH;
} USB_HID_DESCR, *PUSB_HID_DESCR;

typedef struct __PACKED _UDISK_BOC_CBW
{ /* command of BulkOnly USB-FlashDisk */
    UINT32 mCBW_Sig;
    UINT32 mCBW_Tag;
    UINT32 mCBW_DataLen; /* uppest byte of data length, always is 0 */
    UINT8  mCBW_Flag;    /* transfer direction and etc. */
    UINT8  mCBW_LUN;
    UINT8  mCBW_CB_Len;     /* length of command block */
    UINT8  mCBW_CB_Buf[16]; /* command block buffer */
} UDISK_BOC_CBW, *PXUDISK_BOC_CBW;

typedef struct __PACKED _UDISK_BOC_CSW
{ /* status of BulkOnly USB-FlashDisk */
    UINT32 mCBW_Sig;
    UINT32 mCBW_Tag;
    UINT32 mCSW_Residue; /* return: remainder bytes */ /* uppest byte of remainder length, always is 0 */
    UINT8  mCSW_Status;                                /* return: result status */
} UDISK_BOC_CSW, *PXUDISK_BOC_CSW;

extern PUINT8 pEP0_RAM_Addr; //ep0(64)
extern PUINT8 pEP1_RAM_Addr; //ep1_out(64)+ep1_in(64)
extern PUINT8 pEP2_RAM_Addr; //ep2_out(64)+ep2_in(64)
extern PUINT8 pEP3_RAM_Addr; //ep3_out(64)+ep3_in(64)
extern PUINT8 pEP4_RAM_Addr; //ep4_out(64)+ep4_in(64)
extern PUINT8 pEP5_RAM_Addr; //ep5_out(64)+ep5_in(64)
extern PUINT8 pEP6_RAM_Addr; //ep6_out(64)+ep6_in(64)
extern PUINT8 pEP7_RAM_Addr; //ep7_out(64)+ep7_in(64)

#define pSetupReqPak        ((PUSB_SETUP_REQ)pEP0_RAM_Addr)
#define pEP0_DataBuf        (pEP0_RAM_Addr)
#define pEP1_OUT_DataBuf    (pEP1_RAM_Addr)
#define pEP1_IN_DataBuf     (pEP1_RAM_Addr + 64)
#define pEP2_OUT_DataBuf    (pEP2_RAM_Addr)
#define pEP2_IN_DataBuf     (pEP2_RAM_Addr + 64)
#define pEP3_OUT_DataBuf    (pEP3_RAM_Addr)
#define pEP3_IN_DataBuf     (pEP3_RAM_Addr + 64)
#define pEP4_OUT_DataBuf    (pEP4_RAM_Addr)
#define pEP4_IN_DataBuf     (pEP4_RAM_Addr + 64)
#define pEP5_OUT_DataBuf    (pEP5_RAM_Addr)
#define pEP5_IN_DataBuf     (pEP5_RAM_Addr + 64)
#define pEP6_OUT_DataBuf    (pEP6_RAM_Addr)
#define pEP6_IN_DataBuf     (pEP6_RAM_Addr + 64)
#define pEP7_OUT_DataBuf    (pEP7_RAM_Addr)
#define pEP7_IN_DataBuf     (pEP7_RAM_Addr + 64)

void USB_DeviceInit(void);
void USB_DevTransProcess(void);

void DevEP1_OUT_Deal(UINT8 l);
void DevEP2_OUT_Deal(UINT8 l);
void DevEP3_OUT_Deal(UINT8 l);
void DevEP4_OUT_Deal(UINT8 l);
void DevEP5_OUT_Deal(UINT8 l);
void DevEP6_OUT_Deal(UINT8 l);
void DevEP7_OUT_Deal(UINT8 l);

void DevEP1_IN_Deal(UINT8 l);
void DevEP2_IN_Deal(UINT8 l);
void DevEP3_IN_Deal(UINT8 l);
void DevEP4_IN_Deal(UINT8 l);
void DevEP5_IN_Deal(UINT8 l);
void DevEP6_IN_Deal(UINT8 l);
void DevEP7_IN_Deal(UINT8 l);

#define EP1_GetINSta()    (R8_UEP1_CTRL & UEP_T_RES_NAK)
#define EP2_GetINSta()    (R8_UEP2_CTRL & UEP_T_RES_NAK)
#define EP3_GetINSta()    (R8_UEP3_CTRL & UEP_T_RES_NAK)
#define EP4_GetINSta()    (R8_UEP4_CTRL & UEP_T_RES_NAK)
#define EP5_GetINSta()    (R8_UEP5_CTRL & UEP_T_RES_NAK)
#define EP6_GetINSta()    (R8_UEP6_CTRL & UEP_T_RES_NAK)
#define EP7_GetINSta()    (R8_UEP7_CTRL & UEP_T_RES_NAK)

#ifdef __cplusplus
}
#endif

#endif // __USB_TYPE__
