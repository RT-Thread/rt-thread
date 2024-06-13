/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _USB_CH32_USBFS_REG_H
#define _USB_CH32_USBFS_REG_H

#define __IO volatile /* defines 'read / write' permissions */

/* USBOTG_FS Registers */
typedef struct
{
    __IO uint8_t BASE_CTRL;
    __IO uint8_t UDEV_CTRL;
    __IO uint8_t INT_EN;
    __IO uint8_t DEV_ADDR;
    __IO uint8_t Reserve0;
    __IO uint8_t MIS_ST;
    __IO uint8_t INT_FG;
    __IO uint8_t INT_ST;
    __IO uint16_t RX_LEN;
    __IO uint16_t Reserve1;
    __IO uint8_t UEP4_1_MOD;
    __IO uint8_t UEP2_3_MOD;
    __IO uint8_t UEP5_6_MOD;
    __IO uint8_t UEP7_MOD;
    __IO uint32_t UEP0_DMA;
    __IO uint32_t UEP1_DMA;
    __IO uint32_t UEP2_DMA;
    __IO uint32_t UEP3_DMA;
    __IO uint32_t UEP4_DMA;
    __IO uint32_t UEP5_DMA;
    __IO uint32_t UEP6_DMA;
    __IO uint32_t UEP7_DMA;
    __IO uint16_t UEP0_TX_LEN;
    __IO uint8_t UEP0_TX_CTRL;
    __IO uint8_t UEP0_RX_CTRL;
    __IO uint16_t UEP1_TX_LEN;
    __IO uint8_t UEP1_TX_CTRL;
    __IO uint8_t UEP1_RX_CTRL;
    __IO uint16_t UEP2_TX_LEN;
    __IO uint8_t UEP2_TX_CTRL;
    __IO uint8_t UEP2_RX_CTRL;
    __IO uint16_t UEP3_TX_LEN;
    __IO uint8_t UEP3_TX_CTRL;
    __IO uint8_t UEP3_RX_CTRL;
    __IO uint16_t UEP4_TX_LEN;
    __IO uint8_t UEP4_TX_CTRL;
    __IO uint8_t UEP4_RX_CTRL;
    __IO uint16_t UEP5_TX_LEN;
    __IO uint8_t UEP5_TX_CTRL;
    __IO uint8_t UEP5_RX_CTRL;
    __IO uint16_t UEP6_TX_LEN;
    __IO uint8_t UEP6_TX_CTRL;
    __IO uint8_t UEP6_RX_CTRL;
    __IO uint16_t UEP7_TX_LEN;
    __IO uint8_t UEP7_TX_CTRL;
    __IO uint8_t UEP7_RX_CTRL;
    __IO uint32_t Reserve2;
    __IO uint32_t OTG_CR;
    __IO uint32_t OTG_SR;
} USBOTG_FS_TypeDef;

typedef struct __attribute__((packed)) {
    __IO uint8_t BASE_CTRL;
    __IO uint8_t HOST_CTRL;
    __IO uint8_t INT_EN;
    __IO uint8_t DEV_ADDR;
    __IO uint8_t Reserve0;
    __IO uint8_t MIS_ST;
    __IO uint8_t INT_FG;
    __IO uint8_t INT_ST;
    __IO uint16_t RX_LEN;
    __IO uint16_t Reserve1;
    __IO uint8_t Reserve2;
    __IO uint8_t HOST_EP_MOD;
    __IO uint16_t Reserve3;
    __IO uint32_t Reserve4;
    __IO uint32_t Reserve5;
    __IO uint32_t HOST_RX_DMA;
    __IO uint32_t HOST_TX_DMA;
    __IO uint32_t Reserve6;
    __IO uint32_t Reserve7;
    __IO uint32_t Reserve8;
    __IO uint32_t Reserve9;
    __IO uint32_t Reserve10;
    __IO uint16_t Reserve11;
    __IO uint16_t HOST_SETUP;
    __IO uint8_t HOST_EP_PID;
    __IO uint8_t Reserve12;
    __IO uint8_t Reserve13;
    __IO uint8_t HOST_RX_CTRL;
    __IO uint16_t HOST_TX_LEN;
    __IO uint8_t HOST_TX_CTRL;
    __IO uint8_t Reserve14;
    __IO uint32_t Reserve15;
    __IO uint32_t Reserve16;
    __IO uint32_t Reserve17;
    __IO uint32_t Reserve18;
    __IO uint32_t Reserve19;
    __IO uint32_t OTG_CR;
    __IO uint32_t OTG_SR;
} USBOTGH_FS_TypeDef;

typedef struct
{
    __IO uint8_t BASE_CTRL;     /*!< 0x40008000 */
    __IO uint8_t HOST_CTRL;     /*!< 0x40008001 */
    __IO uint8_t INT_EN;        /*!< 0x40008002 */
    __IO uint8_t DEV_ADDR;      /*!< 0x40008003 */
    __IO uint8_t USB_STATUS0;   /*!< 0x40008004 */
    __IO uint8_t MIS_ST;        /*!< 0x40008005 */
    __IO uint8_t INT_FG;        /*!< 0x40008006 */
    __IO uint8_t INT_ST;        /*!< 0x40008007 */
    __IO uint8_t RX_LEN;        /*!< 0x40008008 */
    __IO uint8_t Reserve1;      /*!< 0x40008009 */
    __IO uint8_t Reserve2;      /*!< 0x4000800a */
    __IO uint8_t Reserve3;      /*!< 0x4000800b */
    __IO uint8_t UEP4_1_MOD;    /*!< 0x4000800c */
    __IO uint8_t HOST_EP_MOD;   /*!< 0x4000800d */
    __IO uint8_t UEP567_MOD;    /*!< 0x4000800e */
    __IO uint8_t Reserve4;      /*!< 0x4000800f */
    __IO uint16_t UEP0_DMA;     /*!< 0x40008010 */
    __IO uint16_t Reserve5;     /*!< 0x40008012 */
    __IO uint16_t UEP1_DMA;     /*!< 0x40008014 */
    __IO uint16_t Reserve6;     /*!< 0x40008016 */
    __IO uint16_t HOST_RX_DMA;  /*!< 0x40008018 */
    __IO uint16_t Reserve7;     /*!< 0x4000801a */
    __IO uint16_t HOST_TX_DMA;  /*!< 0x4000801c */
    __IO uint16_t Reserve8;     /*!< 0x4000801e */
    __IO uint8_t UEP0_T_LEN;    /*!< 0x40008020 */
    __IO uint8_t Reserve9;      /*!< 0x40008021 */
    __IO uint8_t UEP0_CTRL;     /*!< 0x40008022 */
    __IO uint8_t Reserve10;     /*!< 0x40008023 */
    __IO uint8_t UEP1_T_LEN;    /*!< 0x40008024 */
    __IO uint8_t Reserve11;     /*!< 0x40008025 */
    __IO uint8_t HOST_SETUP;    /*!< 0x40008026 */
    __IO uint8_t Reserve12;     /*!< 0x40008027 */
    __IO uint8_t HOST_EP_PID;   /*!< 0x40008028 */
    __IO uint8_t Reserve13;     /*!< 0x40008029 */
    __IO uint8_t HOST_RX_CTRL;  /*!< 0x4000802a */
    __IO uint8_t Reserve14;     /*!< 0x4000802b */
    __IO uint8_t HOST_TX_LEN;   /*!< 0x4000802c */
    __IO uint8_t Reserve15;     /*!< 0x4000802d */
    __IO uint8_t HOST_TX_CTRL;  /*!< 0x4000802e */
    __IO uint8_t Reserve16;     /*!< 0x4000802f */
    __IO uint8_t UEP4_T_LEN;    /*!< 0x40008030 */
    __IO uint8_t Reserve17;     /*!< 0x40008031 */
    __IO uint8_t UEP4_CTRL;     /*!< 0x40008032 */
    __IO uint8_t Reserve18[33]; /*!< 0x40008033 */
    __IO uint16_t UEP5_DMA;     /*!< 0x40008054 */
    __IO uint16_t Reserve19;    /*!< 0x40008056 */
    __IO uint16_t UEP6_DMA;     /*!< 0x40008058 */
    __IO uint16_t Reserve20;    /*!< 0x4000805a */
    __IO uint16_t UEP7_DMA;     /*!< 0x4000805c */
    __IO uint8_t Reserve21[6];  /*!< 0x4000805e */
    __IO uint8_t UEP5_T_LEN;    /*!< 0x40008064 */
    __IO uint8_t Reserve22;     /*!< 0x40008065 */
    __IO uint8_t UEP5_CTRL;     /*!< 0x40008066 */
    __IO uint8_t Reserve23;     /*!< 0x40008067 */
    __IO uint8_t UEP6_T_LEN;    /*!< 0x40008068 */
    __IO uint8_t Reserve24;     /*!< 0x40008069 */
    __IO uint8_t UEP6_CTRL;     /*!< 0x4000806a */
    __IO uint8_t Reserve25;     /*!< 0x4000806b */
    __IO uint8_t UEP7_T_LEN;    /*!< 0x4000806c */
    __IO uint8_t Reserve26;     /*!< 0x4000806d */
    __IO uint8_t UEP7_CTRL;     /*!< 0x4000806e */
} USB_FS_TypeDef;

#define USBFS_BASE ((uint32_t)0x50000000)

#define USBFS_DEVICE ((USBOTG_FS_TypeDef *)USBFS_BASE)
#define USBFS_HOST   ((USBOTGH_FS_TypeDef *)USBFS_BASE)

/******************* GLOBAL ******************/

/* BASE USB_CTRL */
#define USBFS_BASE_CTRL_OFFSET 0x00 // USB base control
#define USBFS_UC_HOST_MODE     0x80 // enable USB host mode: 0=device mode, 1=host mode
#define USBFS_UC_LOW_SPEED     0x40 // enable USB low speed: 0=12Mbps, 1=1.5Mbps
#define USBFS_UC_DEV_PU_EN     0x20 // USB device enable and internal pullup resistance enable
#define USBFS_UC_SYS_CTRL1     0x20 // USB system control high bit
#define USBFS_UC_SYS_CTRL0     0x10 // USB system control low bit
#define USBFS_UC_SYS_CTRL_MASK 0x30 // bit mask of USB system control
// UC_HOST_MODE & UC_SYS_CTRL1 & UC_SYS_CTRL0: USB system control
//   0 00: disable USB device and disable internal pullup resistance
//   0 01: enable USB device and disable internal pullup resistance, need external pullup resistance
//   0 1x: enable USB device and enable internal pullup resistance
//   1 00: enable USB host and normal status
//   1 01: enable USB host and force UDP/UDM output SE0 state
//   1 10: enable USB host and force UDP/UDM output J state
//   1 11: enable USB host and force UDP/UDM output resume or K state
#define USBFS_UC_INT_BUSY  0x08 // enable automatic responding busy for device mode or automatic pause for host mode during interrupt flag UIF_TRANSFER valid
#define USBFS_UC_RESET_SIE 0x04 // force reset USB SIE, need software clear
#define USBFS_UC_CLR_ALL   0x02 // force clear FIFO and count of USB
#define USBFS_UC_DMA_EN    0x01 // DMA enable and DMA interrupt enable for USB

/* USB INT EN */
#define USBFS_INT_EN_OFFSET 0x02
#define USBFS_UIE_DEV_SOF   0x80 // enable interrupt for SOF received for USB device mode
#define USBFS_UIE_DEV_NAK   0x40 // enable interrupt for NAK responded for USB device mode
#define USBFS_UIE_FIFO_OV   0x10 // enable interrupt for FIFO overflow
#define USBFS_UIE_HST_SOF   0x08 // enable interrupt for host SOF timer action for USB host mode
#define USBFS_UIE_SUSPEND   0x04 // enable interrupt for USB suspend or resume event
#define USBFS_UIE_TRANSFER  0x02 // enable interrupt for USB transfer completion
#define USBFS_UIE_DETECT    0x01 // enable interrupt for USB device detected event for USB host mode
#define USBFS_UIE_BUS_RST   0x01 // enable interrupt for USB bus reset event for USB device mode
/* USB_DEV_ADDR */
#define USBFS_DEV_ADDR_OFFSET 0x03
#define USBFS_UDA_GP_BIT      0x80 // general purpose bit
#define USBFS_USB_ADDR_MASK   0x7F // bit mask for USB device address

/* USB_STATUS */
#define USBFS_USB_STATUS_OFFSET 0x04

/* USB_MIS_ST */
#define USBFS_MIS_ST_OFFSET  0x05
#define USBFS_UMS_SOF_PRES   0x80 // RO, indicate host SOF timer presage status
#define USBFS_UMS_SOF_ACT    0x40 // RO, indicate host SOF timer action status for USB host
#define USBFS_UMS_SIE_FREE   0x20 // RO, indicate USB SIE free status
#define USBFS_UMS_R_FIFO_RDY 0x10 // RO, indicate USB receiving FIFO ready status (not empty)
#define USBFS_UMS_BUS_RESET  0x08 // RO, indicate USB bus reset status
#define USBFS_UMS_SUSPEND    0x04 // RO, indicate USB suspend status
#define USBFS_UMS_DM_LEVEL   0x02 // RO, indicate UDM level saved at device attached to USB host
#define USBFS_UMS_DEV_ATTACH 0x01 // RO, indicate device attached status on USB host

/* USB_INT_FG */
#define USBFS_INT_FG_OFFSET 0x06
#define USBFS_U_IS_NAK      0x80 // RO, indicate current USB transfer is NAK received
#define USBFS_U_TOG_OK      0x40 // RO, indicate current USB transfer toggle is OK
#define USBFS_U_SIE_FREE    0x20 // RO, indicate USB SIE free status
#define USBFS_UIF_FIFO_OV   0x10 // FIFO overflow interrupt flag for USB, direct bit address clear or write 1 to clear
#define USBFS_UIF_HST_SOF   0x08 // host SOF timer interrupt flag for USB host, direct bit address clear or write 1 to clear
#define USBFS_UIF_SUSPEND   0x04 // USB suspend or resume event interrupt flag, direct bit address clear or write 1 to clear
#define USBFS_UIF_TRANSFER  0x02 // USB transfer completion interrupt flag, direct bit address clear or write 1 to clear
#define USBFS_UIF_DETECT    0x01 // device detected event interrupt flag for USB host mode, direct bit address clear or write 1 to clear
#define USBFS_UIF_BUS_RST   0x01 // bus reset event interrupt flag for USB device mode, direct bit address clear or write 1 to clear

/* USB_INT_ST */
#define USBFS_INT_ST_OFFSET   0x07
#define USBFS_UIS_IS_SETUP    0x80 // RO, indicate current USB transfer is setup received for USB device mode
#define USBFS_UIS_IS_NAK      0x80 // RO, indicate current USB transfer is NAK received for USB device mode
#define USBFS_UIS_TOG_OK      0x40 // RO, indicate current USB transfer toggle is OK
#define USBFS_UIS_TOKEN1      0x20 // RO, current token PID code bit 1 received for USB device mode
#define USBFS_UIS_TOKEN0      0x10 // RO, current token PID code bit 0 received for USB device mode
#define USBFS_UIS_TOKEN_MASK  0x30 // RO, bit mask of current token PID code received for USB device mode
#define USBFS_UIS_TOKEN_OUT   0x00
#define USBFS_UIS_TOKEN_SOF   0x10
#define USBFS_UIS_TOKEN_IN    0x20
#define USBFS_UIS_TOKEN_SETUP 0x30
// UIS_TOKEN1 & UIS_TOKEN0: current token PID code received for USB device mode
//   00: OUT token PID received
//   01: SOF token PID received
//   10: IN token PID received
//   11: SETUP token PID received
#define USBFS_UIS_ENDP_MASK 0x0F // RO, bit mask of current transfer endpoint number for USB device mode
/* USB_RX_LEN */
#define USBFS_RX_LEN_OFFSET 0x08

/******************* DEVICE ******************/

/* UDEV_CTRL */
#define USBFS_UDEV_CTRL_OFFSET 0x01
#define USBFS_UD_PD_DIS        0x80 // disable USB UDP/UDM pulldown resistance: 0=enable pulldown, 1=disable
#define USBFS_UD_DP_PIN        0x20 // ReadOnly: indicate current UDP pin level
#define USBFS_UD_DM_PIN        0x10 // ReadOnly: indicate current UDM pin level
#define USBFS_UD_LOW_SPEED     0x04 // enable USB physical port low speed: 0=full speed, 1=low speed
#define USBFS_UD_GP_BIT        0x02 // general purpose bit
#define USBFS_UD_PORT_EN       0x01 // enable USB physical port I/O: 0=disable, 1=enable

/* UEP4_1_MOD */
#define USBFS_UEP4_1_MOD_OFFSET 0x0C
#define USBFS_UEP1_RX_EN        0x80 // enable USB endpoint 1 receiving (OUT)
#define USBFS_UEP1_TX_EN        0x40 // enable USB endpoint 1 transmittal (IN)
#define USBFS_UEP1_BUF_MOD      0x10 // buffer mode of USB endpoint 1
// UEPn_RX_EN & UEPn_TX_EN & UEPn_BUF_MOD: USB endpoint 1/2/3 buffer mode, buffer start address is UEPn_DMA
//   0 0 x:  disable endpoint and disable buffer
//   1 0 0:  64 bytes buffer for receiving (OUT endpoint)
//   1 0 1:  dual 64 bytes buffer by toggle bit bUEP_R_TOG selection for receiving (OUT endpoint), total=128bytes
//   0 1 0:  64 bytes buffer for transmittal (IN endpoint)
//   0 1 1:  dual 64 bytes buffer by toggle bit bUEP_T_TOG selection for transmittal (IN endpoint), total=128bytes
//   1 1 0:  64 bytes buffer for receiving (OUT endpoint) + 64 bytes buffer for transmittal (IN endpoint), total=128bytes
//   1 1 1:  dual 64 bytes buffer by bUEP_R_TOG selection for receiving (OUT endpoint) + dual 64 bytes buffer by bUEP_T_TOG selection for transmittal (IN endpoint), total=256bytes
#define USBFS_UEP4_RX_EN 0x08 // enable USB endpoint 4 receiving (OUT)
#define USBFS_UEP4_TX_EN 0x04 // enable USB endpoint 4 transmittal (IN)
// UEP4_RX_EN & UEP4_TX_EN: USB endpoint 4 buffer mode, buffer start address is UEP0_DMA
//   0 0:  single 64 bytes buffer for endpoint 0 receiving & transmittal (OUT & IN endpoint)
//   1 0:  single 64 bytes buffer for endpoint 0 receiving & transmittal (OUT & IN endpoint) + 64 bytes buffer for endpoint 4 receiving (OUT endpoint), total=128bytes
//   0 1:  single 64 bytes buffer for endpoint 0 receiving & transmittal (OUT & IN endpoint) + 64 bytes buffer for endpoint 4 transmittal (IN endpoint), total=128bytes
//   1 1:  single 64 bytes buffer for endpoint 0 receiving & transmittal (OUT & IN endpoint)
//           + 64 bytes buffer for endpoint 4 receiving (OUT endpoint) + 64 bytes buffer for endpoint 4 transmittal (IN endpoint), total=192bytes

/* UEP2_3_MOD */
#define USBFS_UEP2_3_MOD_OFFSET 0x0D
#define USBFS_UEP3_RX_EN        0x80 // enable USB endpoint 3 receiving (OUT)
#define USBFS_UEP3_TX_EN        0x40 // enable USB endpoint 3 transmittal (IN)
#define USBFS_UEP3_BUF_MOD      0x10 // buffer mode of USB endpoint 3
#define USBFS_UEP2_RX_EN        0x08 // enable USB endpoint 2 receiving (OUT)
#define USBFS_UEP2_TX_EN        0x04 // enable USB endpoint 2 transmittal (IN)
#define USBFS_UEP2_BUF_MOD      0x01 // buffer mode of USB endpoint 2

/* UEP5_6_MOD */
#define USBFS_UEP5_6_MOD_OFFSET 0x0E
#define USBFS_UEP6_RX_EN        0x80 // enable USB endpoint 6 receiving (OUT)
#define USBFS_UEP6_TX_EN        0x40 // enable USB endpoint 6 transmittal (IN)
#define USBFS_UEP6_BUF_MOD      0x10 // buffer mode of USB endpoint 6
#define USBFS_UEP5_RX_EN        0x08 // enable USB endpoint 5 receiving (OUT)
#define USBFS_UEP5_TX_EN        0x04 // enable USB endpoint 5 transmittal (IN)
#define USBFS_UEP5_BUF_MOD      0x01 // buffer mode of USB endpoint 5

/* UEP7_MOD */
#define USBFS_UEP7_MOD_OFFSET 0x0F
#define USBFS_UEP7_RX_EN      0x08 // enable USB endpoint 7 receiving (OUT)
#define USBFS_UEP7_TX_EN      0x04 // enable USB endpoint 7 transmittal (IN)
#define USBFS_UEP7_BUF_MOD    0x01 // buffer mode of USB endpoint 7

/* USB_DMA */
#define USBFS_UEPx_DMA_OFFSET(n) (0x10 + 4 * (n)) // endpoint x DMA buffer address
#define USBFS_UEP0_DMA_OFFSET    0x10 // endpoint 0 DMA buffer address
#define USBFS_UEP1_DMA_OFFSET    0x14 // endpoint 1 DMA buffer address
#define USBFS_UEP2_DMA_OFFSET    0x18 // endpoint 2 DMA buffer address
#define USBFS_UEP3_DMA_OFFSET    0x1c // endpoint 3 DMA buffer address
#define USBFS_UEP4_DMA_OFFSET    0x20 // endpoint 4 DMA buffer address
#define USBFS_UEP5_DMA_OFFSET    0x24 // endpoint 5 DMA buffer address
#define USBFS_UEP6_DMA_OFFSET    0x28 // endpoint 6 DMA buffer address
#define USBFS_UEP7_DMA_OFFSET    0x2c // endpoint 7 DMA buffer address
/* USB_EP_CTRL */
#define USBFS_UEPx_T_LEN_OFFSET(n)   (0x30 + 4 * (n)) // endpoint x DMA buffer address
#define USBFS_UEPx_TX_CTRL_OFFSET(n) (0x30 + 4 * (n) + 2) // endpoint x DMA buffer address
#define USBFS_UEPx_RX_CTRL_OFFSET(n) (0x30 + 4 * (n) + 3) // endpoint x DMA buffer address

#define USBFS_UEP_AUTO_TOG 0x08 // enable automatic toggle after successful transfer completion on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle
#define USBFS_UEP_R_TOG    0x04 // expected data toggle flag of USB endpoint X receiving (OUT): 0=DATA0, 1=DATA1
#define USBFS_UEP_T_TOG    0x04 // prepared data toggle flag of USB endpoint X transmittal (IN): 0=DATA0, 1=DATA1

#define USBFS_UEP_R_RES1      0x02 // handshake response type high bit for USB endpoint X receiving (OUT)
#define USBFS_UEP_R_RES0      0x01 // handshake response type low bit for USB endpoint X receiving (OUT)
#define USBFS_UEP_R_RES_MASK  0x03 // bit mask of handshake response type for USB endpoint X receiving (OUT)
#define USBFS_UEP_R_RES_ACK   0x00
#define USBFS_UEP_R_RES_TOUT  0x01
#define USBFS_UEP_R_RES_NAK   0x02
#define USBFS_UEP_R_RES_STALL 0x03
// RB_UEP_R_RES1 & RB_UEP_R_RES0: handshake response type for USB endpoint X receiving (OUT)
//   00: ACK (ready)
//   01: no response, time out to host, for non-zero endpoint isochronous transactions
//   10: NAK (busy)
//   11: STALL (error)
#define USBFS_UEP_T_RES1      0x02 // handshake response type high bit for USB endpoint X transmittal (IN)
#define USBFS_UEP_T_RES0      0x01 // handshake response type low bit for USB endpoint X transmittal (IN)
#define USBFS_UEP_T_RES_MASK  0x03 // bit mask of handshake response type for USB endpoint X transmittal (IN)
#define USBFS_UEP_T_RES_ACK   0x00
#define USBFS_UEP_T_RES_TOUT  0x01
#define USBFS_UEP_T_RES_NAK   0x02
#define USBFS_UEP_T_RES_STALL 0x03
// bUEP_T_RES1 & bUEP_T_RES0: handshake response type for USB endpoint X transmittal (IN)
//   00: DATA0 or DATA1 then expecting ACK (ready)
//   01: DATA0 or DATA1 then expecting no response, time out from host, for non-zero endpoint isochronous transactions
//   10: NAK (busy)
//   11: TALL (error)

/******************* HOST ******************/

#define USBFS_UHOST_CTRL_OFFSET 0x01 // USB host physical prot control
#define USBFS_UH_PD_DIS         0x80 // disable USB UDP/UDM pulldown resistance: 0=enable pulldown, 1=disable
#define USBFS_UH_DP_PIN         0x20 // ReadOnly: indicate current UDP pin level
#define USBFS_UH_DM_PIN         0x10 // ReadOnly: indicate current UDM pin level
#define USBFS_UH_LOW_SPEED      0x04 // enable USB port low speed: 0=full speed, 1=low speed
#define USBFS_UH_BUS_RESET      0x02 // control USB bus reset: 0=normal, 1=force bus reset
#define USBFS_UH_PORT_EN        0x01 // enable USB port: 0=disable, 1=enable port, automatic disabled if USB device detached

#define USBFS_UH_EP_MOD_OFFSET USBFS_UEP2_3_MOD_OFFSET
#define USBFS_UH_EP_TX_EN      0x40 // enable USB host OUT endpoint transmittal
#define USBFS_UH_EP_TBUF_MOD   0x10 // buffer mode of USB host OUT endpoint
// bUH_EP_TX_EN & bUH_EP_TBUF_MOD: USB host OUT endpoint buffer mode, buffer start address is UH_TX_DMA
//   0 x:  disable endpoint and disable buffer
//   1 0:  64 bytes buffer for transmittal (OUT endpoint)
//   1 1:  dual 64 bytes buffer by toggle bit bUH_T_TOG selection for transmittal (OUT endpoint), total=128bytes
#define USBFS_UH_EP_RX_EN    0x08 // enable USB host IN endpoint receiving
#define USBFS_UH_EP_RBUF_MOD 0x01 // buffer mode of USB host IN endpoint
// bUH_EP_RX_EN & bUH_EP_RBUF_MOD: USB host IN endpoint buffer mode, buffer start address is UH_RX_DMA
//   0 x:  disable endpoint and disable buffer
//   1 0:  64 bytes buffer for receiving (IN endpoint)
//   1 1:  dual 64 bytes buffer by toggle bit bUH_R_TOG selection for receiving (IN endpoint), total=128bytes

#define USBFS_UH_RX_DMA_OFFSET USBFS_UEPx_DMA_OFFSET(2) // host rx endpoint buffer high address
#define USBFS_UH_TX_DMA_OFFSET USBFS_UEPx_DMA_OFFSET(3) // host tx endpoint buffer high address

#define USBFS_UH_SETUP_OFFSET USBFS_UEPx_TX_CTRL_OFFSET(1)
#define USBFS_UH_PRE_PID_EN   0x0400 // USB host PRE PID enable for low speed device via hub
#define USBFS_UH_SOF_EN       0x04 // USB host automatic SOF enable

#define USBFS_UH_EP_PID_OFFSET USBFS_UEPx_T_LEN_OFFSET(2)
#define USBFS_UH_TOKEN_MASK    0xF0 // bit mask of token PID for USB host transfer
#define USBFS_UH_ENDP_MASK     0x0F // bit mask of endpoint number for USB host transfer

#define USBFS_UH_RX_CTRL_OFFSET USBFS_UEPx_RX_CTRL_OFFSET(2) // host receiver endpoint control
#define USBFS_UH_R_AUTO_TOG     0x08 // enable automatic toggle after successful transfer completion: 0=manual toggle, 1=automatic toggle
#define USBFS_UH_R_TOG          0x04 // expected data toggle flag of host receiving (IN): 0=DATA0, 1=DATA1
#define USBFS_UH_R_RES          0x01 // prepared handshake response type for host receiving (IN): 0=ACK (ready), 1=no response, time out to device, for isochronous transactions

#define USBFS_UH_TX_LEN_OFFSET USBFS_UEPx_T_LEN_OFFSET(3)

#define USBFS_UH_TX_CTRL_OFFSET USBFS_UEPx_TX_CTRL_OFFSET(3) // host transmittal endpoint control
#define USBFS_UH_T_AUTO_TOG     0x08 // enable automatic toggle after successful transfer completion: 0=manual toggle, 1=automatic toggle
#define USBFS_UH_T_TOG          0x04 // prepared data toggle flag of host transmittal (SETUP/OUT): 0=DATA0, 1=DATA1
#define USBFS_UH_T_RES          0x01 // expected handshake response type for host transmittal (SETUP/OUT): 0=ACK (ready), 1=no response, time out from device, for isochronous transactions

#endif
