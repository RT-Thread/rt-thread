/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#define __IO volatile
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RB_UC_HOST_MODE  0x80 // enable USB host mode: 0=device mode, 1=host mode
#define RB_UC_LOW_SPEED  0x40 // enable USB low speed: 0=12Mbps, 1=1.5Mbps
#define RB_UC_DEV_PU_EN  0x20 // USB device enable and internal pullup resistance enable
#define RB_UC_SYS_CTRL1  0x20 // USB system control high bit
#define RB_UC_SYS_CTRL0  0x10 // USB system control low bit
#define MASK_UC_SYS_CTRL 0x30 // bit mask of USB system control
#define RB_UC_INT_BUSY   0x08 // enable automatic responding busy for device mode or automatic pause for host mode during interrupt flag UIF_TRANSFER valid
#define RB_UC_RESET_SIE  0x04 // force reset USB SIE, need software clear
#define RB_UC_CLR_ALL    0x02 // force clear FIFO and count of USB
#define RB_UC_DMA_EN     0x01 // DMA enable and DMA interrupt enable for USB

#define RB_UD_PD_DIS    0x80 // disable USB UDP/UDM pulldown resistance: 0=enable pulldown, 1=disable
#define RB_UD_DP_PIN    0x20 // ReadOnly: indicate current UDP pin level
#define RB_UD_DM_PIN    0x10 // ReadOnly: indicate current UDM pin level
#define RB_UD_LOW_SPEED 0x04 // enable USB physical port low speed: 0=full speed, 1=low speed
#define RB_UD_GP_BIT    0x02 // general purpose bit
#define RB_UD_PORT_EN   0x01 // enable USB physical port I/O: 0=disable, 1=enable

#define RB_UH_PD_DIS    0x80 // disable USB UDP/UDM pulldown resistance: 0=enable pulldown, 1=disable
#define RB_UH_DP_PIN    0x20 // ReadOnly: indicate current UDP pin level
#define RB_UH_DM_PIN    0x10 // ReadOnly: indicate current UDM pin level
#define RB_UH_LOW_SPEED 0x04 // enable USB port low speed: 0=full speed, 1=low speed
#define RB_UH_BUS_RESET 0x02 // control USB bus reset: 0=normal, 1=force bus reset
#define RB_UH_PORT_EN   0x01 // enable USB port: 0=disable, 1=enable port, automatic disabled if USB device detached

#define RB_UIE_DEV_SOF  0x80 // enable interrupt for SOF received for USB device mode
#define RB_UIE_DEV_NAK  0x40 // enable interrupt for NAK responded for USB device mode
#define RB_UIE_FIFO_OV  0x10 // enable interrupt for FIFO overflow
#define RB_UIE_HST_SOF  0x08 // enable interrupt for host SOF timer action for USB host mode
#define RB_UIE_SUSPEND  0x04 // enable interrupt for USB suspend or resume event
#define RB_UIE_TRANSFER 0x02 // enable interrupt for USB transfer completion
#define RB_UIE_DETECT   0x01 // enable interrupt for USB device detected event for USB host mode
#define RB_UIE_BUS_RST  0x01 // enable interrupt for USB bus reset event for USB device mode

#define RB_UDA_GP_BIT 0x80 // general purpose bit
#define MASK_USB_ADDR 0x7F // bit mask for USB device address

#define RB_UMS_SOF_PRES   0x80 // RO, indicate host SOF timer presage status
#define RB_UMS_SOF_ACT    0x40 // RO, indicate host SOF timer action status for USB host
#define RB_UMS_SIE_FREE   0x20 // RO, indicate USB SIE free status
#define RB_UMS_R_FIFO_RDY 0x10 // RO, indicate USB receiving FIFO ready status (not empty)
#define RB_UMS_BUS_RESET  0x08 // RO, indicate USB bus reset status
#define RB_UMS_SUSPEND    0x04 // RO, indicate USB suspend status
#define RB_UMS_DM_LEVEL   0x02 // RO, indicate UDM level saved at device attached to USB host
#define RB_UMS_DEV_ATTACH 0x01 // RO, indicate device attached status on USB host

#define RB_U_IS_NAK     0x80 // RO, indicate current USB transfer is NAK received
#define RB_U_TOG_OK     0x40 // RO, indicate current USB transfer toggle is OK
#define RB_U_SIE_FREE   0x20 // RO, indicate USB SIE free status
#define RB_UIF_FIFO_OV  0x10 // FIFO overflow interrupt flag for USB, direct bit address clear or write 1 to clear
#define RB_UIF_HST_SOF  0x08 // host SOF timer interrupt flag for USB host, direct bit address clear or write 1 to clear
#define RB_UIF_SUSPEND  0x04 // USB suspend or resume event interrupt flag, direct bit address clear or write 1 to clear
#define RB_UIF_TRANSFER 0x02 // USB transfer completion interrupt flag, direct bit address clear or write 1 to clear
#define RB_UIF_DETECT   0x01 // device detected event interrupt flag for USB host mode, direct bit address clear or write 1 to clear
#define RB_UIF_BUS_RST  0x01 // bus reset event interrupt flag for USB device mode, direct bit address clear or write 1 to clear

#define RB_UIS_SETUP_ACT 0x80 // RO, indicate SETUP token & 8 bytes setup request received for USB device mode
#define RB_UIS_TOG_OK    0x40 // RO, indicate current USB transfer toggle is OK
#define RB_UIS_TOKEN1    0x20 // RO, current token PID code bit 1 received for USB device mode
#define RB_UIS_TOKEN0    0x10 // RO, current token PID code bit 0 received for USB device mode
#define MASK_UIS_TOKEN   0x30 // RO, bit mask of current token PID code received for USB device mode
#define UIS_TOKEN_OUT    0x00
#define UIS_TOKEN_SOF    0x10
#define UIS_TOKEN_IN     0x20
#define UIS_TOKEN_SETUP  0x30

#define MASK_UIS_ENDP  0x0F // RO, bit mask of current transfer endpoint number for USB device mode
#define MASK_UIS_H_RES 0x0F // RO, bit mask of current transfer handshake response for USB host mode: 0000=no response, time out from device, others=handshake response PID received

#define R8_USB_RX_LEN   (*((uint8_t *)0x40008008)) // USB receiving length
#define RB_UEP1_RX_EN   0x80                       // enable USB endpoint 1 receiving (OUT)
#define RB_UEP1_TX_EN   0x40                       // enable USB endpoint 1 transmittal (IN)
#define RB_UEP1_BUF_MOD 0x10                       // buffer mode of USB endpoint 1

#define RB_UEP4_RX_EN 0x08 // enable USB endpoint 4 receiving (OUT)
#define RB_UEP4_TX_EN 0x04 // enable USB endpoint 4 transmittal (IN)

#define RB_UEP3_RX_EN   0x80 // enable USB endpoint 3 receiving (OUT)
#define RB_UEP3_TX_EN   0x40 // enable USB endpoint 3 transmittal (IN)
#define RB_UEP3_BUF_MOD 0x10 // buffer mode of USB endpoint 3
#define RB_UEP2_RX_EN   0x08 // enable USB endpoint 2 receiving (OUT)
#define RB_UEP2_TX_EN   0x04 // enable USB endpoint 2 transmittal (IN)
#define RB_UEP2_BUF_MOD 0x01 // buffer mode of USB endpoint 2

#define RB_UEP7_RX_EN 0x20 // enable USB endpoint 7 receiving (OUT)
#define RB_UEP7_TX_EN 0x10 // enable USB endpoint 7 transmittal (IN)
#define RB_UEP6_RX_EN 0x08 // enable USB endpoint 6 receiving (OUT)
#define RB_UEP6_TX_EN 0x04 // enable USB endpoint 6 transmittal (IN)
#define RB_UEP5_RX_EN 0x02 // enable USB endpoint 5 receiving (OUT)
#define RB_UEP5_TX_EN 0x01 // enable USB endpoint 5 transmittal (IN)

#define RB_UH_EP_TX_EN    0x40 // enable USB host OUT endpoint transmittal
#define RB_UH_EP_TBUF_MOD 0x10 // buffer mode of USB host OUT endpoint

#define RB_UH_EP_RX_EN    0x08 // enable USB host IN endpoint receiving
#define RB_UH_EP_RBUF_MOD 0x01 // buffer mode of USB host IN endpoint

#define RB_UEP_R_TOG    0x80 // expected data toggle flag of USB endpoint X receiving (OUT): 0=DATA0, 1=DATA1
#define RB_UEP_T_TOG    0x40 // prepared data toggle flag of USB endpoint X transmittal (IN): 0=DATA0, 1=DATA1
#define RB_UEP_AUTO_TOG 0x10 // enable automatic toggle after successful transfer completion on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle
#define RB_UEP_R_RES1   0x08 // handshake response type high bit for USB endpoint X receiving (OUT)
#define RB_UEP_R_RES0   0x04 // handshake response type low bit for USB endpoint X receiving (OUT)
#define MASK_UEP_R_RES  0x0C // bit mask of handshake response type for USB endpoint X receiving (OUT)
#define UEP_R_RES_ACK   0x00
#define UEP_R_RES_TOUT  0x04
#define UEP_R_RES_NAK   0x08
#define UEP_R_RES_STALL 0x0C

#define RB_UEP_T_RES1   0x02 // handshake response type high bit for USB endpoint X transmittal (IN)
#define RB_UEP_T_RES0   0x01 // handshake response type low bit for USB endpoint X transmittal (IN)
#define MASK_UEP_T_RES  0x03 // bit mask of handshake response type for USB endpoint X transmittal (IN)
#define UEP_T_RES_ACK   0x00
#define UEP_T_RES_TOUT  0x01
#define UEP_T_RES_NAK   0x02
#define UEP_T_RES_STALL 0x03

#define RB_UH_PRE_PID_EN 0x80 // USB host PRE PID enable for low speed device via hub
#define RB_UH_SOF_EN     0x40 // USB host automatic SOF enable

#define R8_UH_EP_PID  R8_UEP2_T_LEN // host endpoint and PID
#define MASK_UH_TOKEN 0xF0          // bit mask of token PID for USB host transfer
#define MASK_UH_ENDP  0x0F          // bit mask of endpoint number for USB host transfer

#define R8_UH_RX_CTRL    R8_UEP2_CTRL // host receiver endpoint control
#define RB_UH_R_TOG      0x80         // expected data toggle flag of host receiving (IN): 0=DATA0, 1=DATA1
#define RB_UH_R_AUTO_TOG 0x10         // enable automatic toggle after successful transfer completion: 0=manual toggle, 1=automatic toggle
#define RB_UH_R_RES      0x04         // prepared handshake response type for host receiving (IN): 0=ACK (ready), 1=no response, time out to device, for isochronous transactions

#define R8_UH_TX_LEN R8_UEP3_T_LEN // host transmittal endpoint transmittal length

#define RB_UH_T_TOG      0x40 // prepared data toggle flag of host transmittal (SETUP/OUT): 0=DATA0, 1=DATA1
#define RB_UH_T_AUTO_TOG 0x10 // enable automatic toggle after successful transfer completion: 0=manual toggle, 1=automatic toggle
#define RB_UH_T_RES      0x01 // expected handshake response type for host transmittal (SETUP/OUT): 0=ACK (ready), 1=no response, time out from device, for isochronous transactions

#define R16_PIN_ANALOG_IE (*((uint16_t *)0x4000101A)) // RW, analog pin enable and digital input disable
#define RB_PIN_USB_IE     0x80                        // RW, USB analog I/O enable: 0=analog I/O disable, 1=analog I/O enable
#define RB_PIN_USB_DP_PU  0x40                        // RW, USB UDP internal pullup resistance enable: 0=enable/disable by RB_UC_DEV_PU_EN, 1=enable pullup, replace RB_UC_DEV_PU_EN under sleep mode
#define RB_PIN_USB2_IE    0x20                        // RW, USB2 analog I/O enable: 0=analog I/O disable, 1=analog I/O enable
#define RB_PIN_USB2_DP_PU 0x10                        // RW, USB2 UDP internal pullup resistance enable: 0=enable/disable by RB_UC_DEV_PU_EN, 1=enable pullup, replace RB_UC_DEV_PU_EN under sleep mode
/*!< USB Regs */
typedef struct
{
    __IO uint8_t USB_CTRL; /*!< 0x40008000 */
    union {
        __IO uint8_t UDEV_CTRL;  /*!< 0x40008001 */
        __IO uint8_t UHOST_CTRL; /*!< 0x40008001 */
    };
    __IO uint8_t USB_INT_EN;  /*!< 0x40008002 */
    __IO uint8_t USB_DEV_AD;  /*!< 0x40008003 */
    __IO uint8_t USB_STATUS0; /*!< 0x40008004 */
    __IO uint8_t USB_MIS_ST;  /*!< 0x40008005 */
    __IO uint8_t USB_INT_FG;  /*!< 0x40008006 */
    __IO uint8_t USB_INT_ST;  /*!< 0x40008007 */
    __IO uint8_t USB_RX_LEN;  /*!< 0x40008008 */
    __IO uint8_t Reserve1;    /*!< 0x40008009 */
    __IO uint8_t Reserve2;    /*!< 0x4000800a */
    __IO uint8_t Reserve3;    /*!< 0x4000800b */
    __IO uint8_t UEP4_1_MOD;  /*!< 0x4000800c */
    union {
        __IO uint8_t UEP2_3_MOD; /*!< 0x4000800d */
        __IO uint8_t UH_EP_MOD;  /*!< 0x4000800d */
    };
    __IO uint8_t UEP567_MOD; /*!< 0x4000800e */
    __IO uint8_t Reserve4;   /*!< 0x4000800f */
    __IO uint16_t UEP0_DMA;  /*!< 0x40008010 */
    __IO uint16_t Reserve5;  /*!< 0x40008012 */
    __IO uint16_t UEP1_DMA;  /*!< 0x40008014 */
    __IO uint16_t Reserve6;  /*!< 0x40008016 */
    union {
        __IO uint16_t UEP2_DMA;  /*!< 0x40008018 */
        __IO uint16_t UH_RX_DMA; /*!< 0x40008018 */
    };
    __IO uint16_t Reserve7; /*!< 0x4000801a */
    union {
        __IO uint16_t UEP3_DMA;  /*!< 0x4000801c */
        __IO uint16_t UH_TX_DMA; /*!< 0x4000801c */
    };
    __IO uint16_t Reserve8;  /*!< 0x4000801e */
    __IO uint8_t UEP0_T_LEN; /*!< 0x40008020 */
    __IO uint8_t Reserve9;   /*!< 0x40008021 */
    __IO uint8_t UEP0_CTRL;  /*!< 0x40008022 */
    __IO uint8_t Reserve10;  /*!< 0x40008023 */
    __IO uint8_t UEP1_T_LEN; /*!< 0x40008024 */
    __IO uint8_t Reserve11;  /*!< 0x40008025 */
    union {
        __IO uint8_t UEP1_CTRL; /*!< 0x40008026 */
        __IO uint8_t UH_SETUP;  /*!< 0x40008026 */
    };
    __IO uint8_t Reserve12; /*!< 0x40008027 */
    union {
        __IO uint8_t UEP2_T_LEN; /*!< 0x40008028 */
        __IO uint8_t UH_EP_PID;  /*!< 0x40008028 */
    };
    __IO uint8_t Reserve13; /*!< 0x40008029 */
    union {
        __IO uint8_t UEP2_CTRL;  /*!< 0x4000802a */
        __IO uint8_t UH_RX_CTRL; /*!< 0x4000802a */
    };
    __IO uint8_t Reserve14; /*!< 0x4000802b */
    union {
        __IO uint8_t UEP3_T_LEN; /*!< 0x4000802c */
        __IO uint8_t UH_TX_LEN;  /*!< 0x4000802c */
    };
    __IO uint8_t Reserve15; /*!< 0x4000802d */
    union {
        __IO uint8_t UEP3_CTRL;  /*!< 0x4000802e */
        __IO uint8_t UH_TX_CTRL; /*!< 0x4000802e */
    };
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

#ifdef __cplusplus
}
#endif
