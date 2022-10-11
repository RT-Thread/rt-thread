/**************************************************************************//**
 * @file     hub.h
 * @version  V1.00
 * @brief    USB Host hub class driver header file.
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#ifndef _USBH_HUB_H_
#define _USBH_HUB_H_


/// @cond HIDDEN_SYMBOLS


/*--------------------------------------------------------------------------*/
/*   Hub class feature selectors (Table 11-17)                              */
/*--------------------------------------------------------------------------*/
#define FS_C_HUB_LOCAL_POWER           0
#define FS_C_HUB_OVER_CURRENT          1

#define FS_PORT_CONNECTION             0
#define FS_PORT_ENABLE                 1
#define FS_PORT_SUSPEND                2
#define FS_PORT_OVER_CURRENT           3
#define FS_PORT_RESET                  4
#define FS_PORT_POWER                  8
#define FS_C_PORT_CONNECTION           16
#define FS_C_PORT_ENABLE               17
#define FS_C_PORT_SUSPEND              18
#define FS_C_PORT_OVER_CURRENT         19
#define FS_C_PORT_RESET                20

/*--------------------------------------------------------------------------*/
/*   Hub/Port staus and change bits                                         */
/*--------------------------------------------------------------------------*/
#define HUB_S_LOCAL_POWER              (1UL << 0)
#define HUB_S_OVERCURRENT              (1UL << 1)

#define HUB_C_LOCAL_POWER              (1UL << 0)
#define HUB_C_OVERCURRENT              (1UL << 1)

#define PORT_S_CONNECTION              (1UL << 0)
#define PORT_S_ENABLE                  (1UL << 1)
#define PORT_S_SUSPEND                 (1UL << 2)
#define PORT_S_OVERCURRENT             (1UL << 3)
#define PORT_S_RESET                   (1UL << 4)
#define PORT_S_PORT_POWER              (1UL << 8)
#define PORT_S_LOW_SPEED               (1UL << 9)
#define PORT_S_HIGH_SPEED              (1UL << 10)
#define PORT_S_TEST                    (1UL << 11)
#define PORT_S_INDICATOR               (1UL << 12)

#define PORT_C_CONNECTION              (1UL << 0)
#define PORT_C_ENABLE                  (1UL << 1)
#define PORT_C_SUSPEND                 (1UL << 2)
#define PORT_C_OVERCURRENT             (1UL << 3)
#define PORT_C_RESET                   (1UL << 4)


/*--------------------------------------------------------------------------*/
/*   Hub descriptor                                                         */
/*--------------------------------------------------------------------------*/
typedef struct __attribute__((__packed__))
{
    uint8_t  bDescLength;
    uint8_t  bDescriptorType;
    uint8_t  bNbrPorts;
    uint16_t wHubCharacteristics;
    uint8_t  bPwrOn2PwrGood;
    uint8_t  bHubContrCurrent;
    uint8_t  bDeviceRemovble;
    uint8_t  PortPwrCtrlMask[16];
}
DESC_HUB_T;

/*
 *   wHubCharacteristics bit field mask
 */
#define HUB_CHAR_LPSM                  0x0003   /* 00b: global port power, 01b: per port power, 1x: reserved */
#define HUB_CHAR_COMPOUND              0x0004   /* 1: is part of a compond device, 0: is not.       */
#define HUB_CHAR_OCPM                  0x0018   /* 00b: global over-current protection, 01b: per port, 1x: reserved  */
#define HUB_CHAR_TTTT                  0x0060   /* TT think time. 00b: 8FS, 01b: 16FS, 10b: 24FS, 11b: 32FS  */
#define HUB_CHAR_PORTIND               0x0080   /* 1: port indicator (LED) supported, 0: not      */

/* port indicator status selectors */
#define HUB_LED_AUTO                   0
#define HUB_LED_AMBER                  1
#define HUB_LED_GREEN                  2
#define HUB_LED_OFF                    3


/*--------------------------------------------------------------------------*/
/*   Port reset retry and time-out settings                                 */
/*--------------------------------------------------------------------------*/
#define HUB_DEBOUNCE_TIME              800      /* Hub connect/disconnect de-bounce time in ms     */
#define PORT_RESET_RETRY               3        /* port reset retry times                          */
#define PORT_RESET_TIME_MS             50       /* port reset time (ms)                            */
#define PORT_RESET_RETRY_INC_MS        250      /* increased reset time (ms) after reset failed    */


#define HUB_STATUS_MAX_BYTE            2        /* maximum number of interrupt-in status bytes     */
/* 2 can support up to 16 port hubs                */
/* 4 can support up to 32 port hubs                */
/* Note!! If modeifed to 4, "uint16_t sc_bitmap"   */
/*        MUST be changed as "uint32_t sc_bitmap"  */
typedef struct hub_dev_t
{
    IFACE_T    *iface;                 /*!< Interface device of this hub          \hideinitializer */
    UTR_T      *utr;                   /*!< Interrupt in UTR of this hub          \hideinitializer */
    // uint8_t    buff[HUB_STATUS_MAX_BYTE];   /*!< Interrupt in buffer              \hideinitializer */
    uint16_t   sc_bitmap;              /*!< Hub and Port Status Change Bitmap     \hideinitializer */
    uint8_t    bNbrPorts;              /*!< Number of ports                       \hideinitializer */
    uint8_t    bPwrOn2PwrGood;         /*!< Hub power on to power good time       \hideinitializer */
    char       pos_id[MAX_HUB_DEVICE + 1]; /*!< Hub position identifier           \hideinitializer */
    int (*port_reset)(struct hub_dev_t *hub, int port);       /*!< Port reset function                   \hideinitializer */
    UDEV_T     *children;              /*!< Child device list.                    \hideinitializer */
} HUB_DEV_T;


/// @endcond

#endif  /* _USBH_HUB_H_ */
