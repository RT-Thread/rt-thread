/********************************** (C) COPYRIGHT  *******************************
 * File Name          : ch32v10x_usb_host.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2020/04/30
 * Description        : This file contains all the functions prototypes for the USB
 *                      Host firmware library.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#ifndef __CH32V10x_USBHOST_H
#define __CH32V10x_USBHOST_H

#include "ch32v10x_usb.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ERR_SUCCESS            0x00
#define ERR_USB_CONNECT        0x15
#define ERR_USB_DISCON         0x16
#define ERR_USB_BUF_OVER       0x17
#define ERR_USB_DISK_ERR       0x1F
#define ERR_USB_TRANSFER       0x20
#define ERR_USB_UNSUPPORT      0xFB
#define ERR_USB_UNKNOWN        0xFE
#define ERR_AOA_PROTOCOL       0x41

#define ROOT_DEV_DISCONNECT    0
#define ROOT_DEV_CONNECTED     1
#define ROOT_DEV_FAILED        2
#define ROOT_DEV_SUCCESS       3
#define DEV_TYPE_KEYBOARD      (USB_DEV_CLASS_HID | 0x20)
#define DEV_TYPE_MOUSE         (USB_DEV_CLASS_HID | 0x30)
#define DEF_AOA_DEVICE         0xF0
#define DEV_TYPE_UNKNOW        0xFF

#define HUB_MAX_PORTS          4
#define WAIT_USB_TOUT_200US    3000

typedef struct
{
    UINT8  DeviceStatus;
    UINT8  DeviceAddress;
    UINT8  DeviceSpeed;
    UINT8  DeviceType;
    UINT16 DeviceVID;
    UINT16 DevicePID;
    UINT8  GpVar[4];
    UINT8  GpHUBPortNum;
} _RootHubDev;

extern _RootHubDev ThisUsbDev;
extern UINT8       UsbDevEndp0Size;
extern UINT8       FoundNewDev;

extern PUINT8 pHOST_RX_RAM_Addr;
extern PUINT8 pHOST_TX_RAM_Addr;
#define pSetupReq    ((PUSB_SETUP_REQ)pHOST_TX_RAM_Addr)

extern const UINT8 SetupGetDevDescr[];
extern const UINT8 SetupGetCfgDescr[];
extern const UINT8 SetupSetUsbAddr[];
extern const UINT8 SetupSetUsbConfig[];
extern const UINT8 SetupSetUsbInterface[];
extern const UINT8 SetupClrEndpStall[];

void  DisableRootHubPort(void);
UINT8 AnalyzeRootHub(void);
void  SetHostUsbAddr(UINT8 addr);
void  SetUsbSpeed(UINT8 FullSpeed);
void  ResetRootHubPort(void);
UINT8 EnableRootHubPort(void);
void  SelectHubPort(UINT8 HubPortIndex);
UINT8 WaitUSB_Interrupt(void);
UINT8 USBHostTransact(UINT8 endp_pid, UINT8 tog, UINT32 timeout);
UINT8 HostCtrlTransfer(PUINT8 DataBuf, PUINT8 RetLen);
void  CopySetupReqPkg(const UINT8 *pReqPkt);
UINT8 CtrlGetDeviceDescr(PUINT8 DataBuf);
UINT8 CtrlGetConfigDescr(PUINT8 DataBuf);
UINT8 CtrlSetUsbAddress(UINT8 addr);
UINT8 CtrlSetUsbConfig(UINT8 cfg);
UINT8 CtrlClearEndpStall(UINT8 endp);
UINT8 CtrlSetUsbIntercace(UINT8 cfg);

void  USB_HostInit(void);
UINT8 InitRootDevice(PUINT8 DataBuf);
UINT8 HubGetPortStatus(UINT8 HubPortIndex);                       // 查询HUB端口状态,返回在TxBuffer中
UINT8 HubSetPortFeature(UINT8 HubPortIndex, UINT8 FeatureSelt);   // 设置HUB端口特性
UINT8 HubClearPortFeature(UINT8 HubPortIndex, UINT8 FeatureSelt); // 清除HUB端口特性
#ifdef __cplusplus
}
#endif

#endif /* __CH32V10x_USBHOST_H */
