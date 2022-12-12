/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v10x_usb_host.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2020/04/30
 * Description        : This file provides all the USB firmware functions.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "ch32v10x_usb_host.h"
#include "debug.h"

/******************************** HOST DEVICE **********************************/
UINT8       UsbDevEndp0Size;
UINT8       FoundNewDev;
_RootHubDev ThisUsbDev;

PUINT8       pHOST_RX_RAM_Addr;
PUINT8       pHOST_TX_RAM_Addr;
extern UINT8 Com_Buffer[128];

__attribute__((aligned(4))) const UINT8 SetupGetDevDescr[] = {USB_REQ_TYP_IN, USB_GET_DESCRIPTOR, 0x00, USB_DESCR_TYP_DEVICE, 0x00, 0x00, sizeof(USB_DEV_DESCR), 0x00};

__attribute__((aligned(4))) const UINT8 SetupGetCfgDescr[] = {USB_REQ_TYP_IN, USB_GET_DESCRIPTOR, 0x00, USB_DESCR_TYP_CONFIG, 0x00, 0x00, 0x04, 0x00};

__attribute__((aligned(4))) const UINT8 SetupSetUsbAddr[] = {USB_REQ_TYP_OUT, USB_SET_ADDRESS, USB_DEVICE_ADDR, 0x00, 0x00, 0x00, 0x00, 0x00};

__attribute__((aligned(4))) const UINT8 SetupSetUsbConfig[] = {USB_REQ_TYP_OUT, USB_SET_CONFIGURATION, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

__attribute__((aligned(4))) const UINT8 SetupSetUsbInterface[] = {USB_REQ_RECIP_INTERF, USB_SET_INTERFACE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

__attribute__((aligned(4))) const UINT8 SetupClrEndpStall[] = {USB_REQ_TYP_OUT | USB_REQ_RECIP_ENDP, USB_CLEAR_FEATURE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/*********************************************************************
 * @fn      DisableRootHubPort( )
 *
 * @brief  Disable root hub
 *
 * @return  none
 */
void DisableRootHubPort(void)
{
#ifdef FOR_ROOT_UDISK_ONLY
    CH103DiskStatus = DISK_DISCONNECT;

#endif

#ifndef DISK_BASE_BUF_LEN
    ThisUsbDev.DeviceStatus = ROOT_DEV_DISCONNECT;
    ThisUsbDev.DeviceAddress = 0x00;

#endif
}

/*********************************************************************
 * @fn      AnalyzeRootHub
 *
 * @brief  Analyze root hub state.
 *
 * @return  Error
 */
UINT8 AnalyzeRootHub(void)
{
    UINT8 s;

    s = ERR_SUCCESS;

    if(R8_USB_MIS_ST & RB_UMS_DEV_ATTACH)
    {
#ifdef DISK_BASE_BUF_LEN
        if(CH103DiskStatus == DISK_DISCONNECT

#else
        if(ThisUsbDev.DeviceStatus == ROOT_DEV_DISCONNECT

#endif
           || (R8_UHOST_CTRL & RB_UH_PORT_EN) == 0x00)
        {
            DisableRootHubPort();

#ifdef DISK_BASE_BUF_LEN
            CH103DiskStatus = DISK_CONNECT;

#else
            ThisUsbDev.DeviceSpeed = R8_USB_MIS_ST & RB_UMS_DM_LEVEL ? 0 : 1;
            ThisUsbDev.DeviceStatus = ROOT_DEV_CONNECTED;

#endif
            s = ERR_USB_CONNECT;
        }
    }

#ifdef DISK_BASE_BUF_LEN
    else if(CH103DiskStatus >= DISK_CONNECT)
    {
#else
    else if(ThisUsbDev.DeviceStatus >= ROOT_DEV_CONNECTED)
    {

#endif
        DisableRootHubPort();
        if(s == ERR_SUCCESS)
            s = ERR_USB_DISCON;
    }

    return (s);
}

/*********************************************************************
 * @fn      SetHostUsbAddr
 *
 * @brief  Set USB host address
 *
 * @param   addr -  host address
 *
 * @return  none
 */
void SetHostUsbAddr(UINT8 addr)
{
    R8_USB_DEV_AD = (R8_USB_DEV_AD & RB_UDA_GP_BIT) | (addr & MASK_USB_ADDR);
}

#ifndef FOR_ROOT_UDISK_ONLY
/*********************************************************************
 * @fn      SetUsbSpeed
 *
 * @brief  Set USB speed.
 *
 * @param   FullSpeed - USB speed.
 *
 * @return  none
 */
void SetUsbSpeed(UINT8 FullSpeed)
{
    if(FullSpeed)
    {
        R8_USB_CTRL &= ~RB_UC_LOW_SPEED;
        R8_UH_SETUP &= ~RB_UH_PRE_PID_EN;
    }
    else
    {
        R8_USB_CTRL |= RB_UC_LOW_SPEED;
    }
}
#endif

/*********************************************************************
 * @fn      ResetRootHubPort( )
 *
 * @brief   Reset root hub
 *
 * @return  none
 */
void ResetRootHubPort(void)
{
    UsbDevEndp0Size = DEFAULT_ENDP0_SIZE;
    SetHostUsbAddr(0x00);
    R8_UHOST_CTRL &= ~RB_UH_PORT_EN;
    SetUsbSpeed(1);
    R8_UHOST_CTRL = (R8_UHOST_CTRL & ~RB_UH_LOW_SPEED) | RB_UH_BUS_RESET;
    Delay_Ms(15);
    R8_UHOST_CTRL = R8_UHOST_CTRL & ~RB_UH_BUS_RESET;
    Delay_Us(250);
    R8_USB_INT_FG = RB_UIF_DETECT;
}

/*********************************************************************
 * @fn      EnableRootHubPort( )
 *
 * @brief   Enable root hub.
 *
 * @return  ERROR
 */
UINT8 EnableRootHubPort(void)
{
#ifdef DISK_BASE_BUF_LEN
    if(CH103DiskStatus < DISK_CONNECT)
        CH103DiskStatus = DISK_CONNECT;

#else
    if(ThisUsbDev.DeviceStatus < ROOT_DEV_CONNECTED)
        ThisUsbDev.DeviceStatus = ROOT_DEV_CONNECTED;

#endif
    if(R8_USB_MIS_ST & RB_UMS_DEV_ATTACH)
    {
#ifndef DISK_BASE_BUF_LEN
        if((R8_UHOST_CTRL & RB_UH_PORT_EN) == 0x00)
        {
            ThisUsbDev.DeviceSpeed = (R8_USB_MIS_ST & RB_UMS_DM_LEVEL) ? 0 : 1;
            if(ThisUsbDev.DeviceSpeed == 0)
                R8_UHOST_CTRL |= RB_UH_LOW_SPEED;
        }

#endif
        R8_UHOST_CTRL |= RB_UH_PORT_EN;
        return (ERR_SUCCESS);
    }

    return (ERR_USB_DISCON);
}

/*********************************************************************
 * @fn      WaitUSB_Interrupt
 *
 * @brief   Wait USB Interrput.
 *
 * @return  ERROR
 */
UINT8 WaitUSB_Interrupt(void)
{
    UINT16 i;

    for(i = WAIT_USB_TOUT_200US; i != 0 && (R8_USB_INT_FG & RB_UIF_TRANSFER) == 0; i--)
    {
        ;
    }
    return ((R8_USB_INT_FG & RB_UIF_TRANSFER) ? ERR_SUCCESS : ERR_USB_UNKNOWN);
}

/*********************************************************************
 * @fn      USBHostTransact
 *
 * @brief   USB host transport transaction
 * @param   endp_pid: endpoint and PID
 *          tog: Synchronization flag
 *          timeout: timeout times
 *
 * @return  EEROR:
 *                         ERR_USB_UNKNOWN
 *          ERR_USB_DISCON
 *          ERR_USB_CONNECT
 *          ERR_SUCCESS
 */
UINT8 USBHostTransact(UINT8 endp_pid, UINT8 tog, UINT32 timeout)
{
    UINT8  TransRetry;
    UINT8  s, r;
    UINT16 i;

    R8_UH_RX_CTRL = R8_UH_TX_CTRL = tog;
    TransRetry = 0;

    do
    {
        R8_UH_EP_PID = endp_pid;
        R8_USB_INT_FG = RB_UIF_TRANSFER;
        for(i = WAIT_USB_TOUT_200US; i != 0 && (R8_USB_INT_FG & RB_UIF_TRANSFER) == 0; i--)
            ;
        R8_UH_EP_PID = 0x00;
        if((R8_USB_INT_FG & RB_UIF_TRANSFER) == 0)
        {
            return (ERR_USB_UNKNOWN);
        }

        if(R8_USB_INT_FG & RB_UIF_DETECT)
        {
            R8_USB_INT_FG = RB_UIF_DETECT;
            s = AnalyzeRootHub();

            if(s == ERR_USB_CONNECT)
                FoundNewDev = 1;

#ifdef DISK_BASE_BUF_LEN

            if(CH103DiskStatus == DISK_DISCONNECT)
                return (ERR_USB_DISCON);
            if(CH103DiskStatus == DISK_CONNECT)
                return (ERR_USB_CONNECT);

#else
            if(ThisUsbDev.DeviceStatus == ROOT_DEV_DISCONNECT)
                return (ERR_USB_DISCON);
            if(ThisUsbDev.DeviceStatus == ROOT_DEV_CONNECTED)
                return (ERR_USB_CONNECT);

#endif
            Delay_Us(200);
        }

        if(R8_USB_INT_FG & RB_UIF_TRANSFER)
        {
            if(R8_USB_INT_ST & RB_UIS_TOG_OK)
                return (ERR_SUCCESS);
            r = R8_USB_INT_ST & MASK_UIS_H_RES;
            if(r == USB_PID_STALL)
                return (r | ERR_USB_TRANSFER);

            if(r == USB_PID_NAK)
            {
                if(timeout == 0)
                    return (r | ERR_USB_TRANSFER);
                if(timeout < 0xFFFF)
                    timeout--;
                --TransRetry;
            }
            else
                switch(endp_pid >> 4)
                {
                    case USB_PID_SETUP:

                    case USB_PID_OUT:
                        if(r)
                            return (r | ERR_USB_TRANSFER);
                        break;

                    case USB_PID_IN:
                        if(r == USB_PID_DATA0 && r == USB_PID_DATA1)
                        {
                        }
                        else if(r)
                            return (r | ERR_USB_TRANSFER);
                        break;

                    default:
                        return (ERR_USB_UNKNOWN);
                }
        }
        else
        {
            R8_USB_INT_FG = 0xFF;
        }
        Delay_Us(15);
    } while(++TransRetry < 3);

    return (ERR_USB_TRANSFER);
}

/*********************************************************************
 * @fn      HostCtrlTransfer
 *
 * @brief  Host control transport.
 *
 * @param   DataBuf : Receive or send data buffer.
 *          RetLen  : Data length.
 *
 * @return  ERR_USB_BUF_OVER IN
 *          ERR_SUCCESS
 */
UINT8 HostCtrlTransfer(PUINT8 DataBuf, PUINT8 RetLen)
{
    UINT16 RemLen = 0;
    UINT8  s, RxLen, RxCnt, TxCnt;
    PUINT8 pBuf;
    PUINT8 pLen;

    pBuf = DataBuf;
    pLen = RetLen;
    Delay_Us(200);
    if(pLen)
        *pLen = 0;

    R8_UH_TX_LEN = sizeof(USB_SETUP_REQ);
    s = USBHostTransact(USB_PID_SETUP << 4 | 0x00, 0x00, 200000 / 20);
    if(s != ERR_SUCCESS)
        return (s);
    R8_UH_RX_CTRL = R8_UH_TX_CTRL = RB_UH_R_TOG | RB_UH_R_AUTO_TOG | RB_UH_T_TOG | RB_UH_T_AUTO_TOG;
    R8_UH_TX_LEN = 0x01;
    RemLen = pSetupReq->wLength;

    if(RemLen && pBuf)
    {
        if(pSetupReq->bRequestType & USB_REQ_TYP_IN)
        {
            while(RemLen)
            {
                Delay_Us(200);
                s = USBHostTransact(USB_PID_IN << 4 | 0x00, R8_UH_RX_CTRL, 200000 / 20);
                if(s != ERR_SUCCESS)
                    return (s);
                RxLen = R8_USB_RX_LEN < RemLen ? R8_USB_RX_LEN : RemLen;
                RemLen -= RxLen;
                if(pLen)
                    *pLen += RxLen;

                for(RxCnt = 0; RxCnt != RxLen; RxCnt++) {
                    *pBuf = pHOST_RX_RAM_Addr[RxCnt];
                    pBuf++;
                }

                if(R8_USB_RX_LEN == 0 || (R8_USB_RX_LEN & (UsbDevEndp0Size - 1)))
                    break;
            }
            R8_UH_TX_LEN = 0x00;
        }
        else
        {
            while(RemLen)
            {
                Delay_Us(200);
                R8_UH_TX_LEN = RemLen >= UsbDevEndp0Size ? UsbDevEndp0Size : RemLen;

                for(TxCnt = 0; TxCnt != R8_UH_TX_LEN; TxCnt++){
                    pHOST_TX_RAM_Addr[TxCnt] = *pBuf;
                    pBuf++;
                }

                s = USBHostTransact(USB_PID_OUT << 4 | 0x00, R8_UH_TX_CTRL, 200000 / 20);
                if(s != ERR_SUCCESS)
                    return (s);
                RemLen -= R8_UH_TX_LEN;
                if(pLen)
                    *pLen += R8_UH_TX_LEN;
            }
        }
    }

    Delay_Us(200);
    s = USBHostTransact((R8_UH_TX_LEN ? USB_PID_IN << 4 | 0x00 : USB_PID_OUT << 4 | 0x00), RB_UH_R_TOG | RB_UH_T_TOG, 200000 / 20);
    if(s != ERR_SUCCESS)
        return (s);
    if(R8_UH_TX_LEN == 0)
        return (ERR_SUCCESS);
    if(R8_USB_RX_LEN == 0)
        return (ERR_SUCCESS);

    return (ERR_USB_BUF_OVER);
}

/*********************************************************************
 * @fn      CopySetupReqPkg
 *
 * @brief  Copy setup request package.
 *
 * @param   pReqPkt: setup request package address.
 *
 * @return  none
 */
void CopySetupReqPkg(const UINT8 *pReqPkt)
{
    UINT8 i;

    for(i = 0; i != sizeof(USB_SETUP_REQ); i++) {
        ((PUINT8)pSetupReq)[i] = *pReqPkt;
        pReqPkt++;
    }
}

/*********************************************************************
 * @fn      CtrlGetDeviceDescr
 *
 * @brief  Get device descrptor.
 *
 * @param   DataBuf: Data buffer.
 *
 * @return  ERR_USB_BUF_OVER
 *          ERR_SUCCESS
 */
UINT8 CtrlGetDeviceDescr(PUINT8 DataBuf)
{
    UINT8 s;
    UINT8 len;

    UsbDevEndp0Size = DEFAULT_ENDP0_SIZE;
    CopySetupReqPkg(SetupGetDevDescr);
    s = HostCtrlTransfer(DataBuf, &len);

    if(s != ERR_SUCCESS)
        return (s);
    UsbDevEndp0Size = ((PUSB_DEV_DESCR)DataBuf)->bMaxPacketSize0;
    if(len < ((PUSB_SETUP_REQ)SetupGetDevDescr)->wLength)
        return (ERR_USB_BUF_OVER);

    return (ERR_SUCCESS);
}

/*********************************************************************
 * @fn      CtrlGetConfigDescr
 *
 * @brief  Get configration descrptor.
 *
 * @param   DataBuf: Data buffer.
 *
 * @return  ERR_USB_BUF_OVER
 *          ERR_SUCCESS
 */
UINT8 CtrlGetConfigDescr(PUINT8 DataBuf)
{
    UINT8 s;
    UINT8 len;

    CopySetupReqPkg(SetupGetCfgDescr);
    s = HostCtrlTransfer(DataBuf, &len);
    if(s != ERR_SUCCESS)
        return (s);
    if(len < ((PUSB_SETUP_REQ)SetupGetCfgDescr)->wLength)
        return (ERR_USB_BUF_OVER);

    len = ((PUSB_CFG_DESCR)DataBuf)->wTotalLength;
    CopySetupReqPkg(SetupGetCfgDescr);
    pSetupReq->wLength = len;
    s = HostCtrlTransfer(DataBuf, &len);
    if(s != ERR_SUCCESS)
        return (s);

    return (ERR_SUCCESS);
}

/*********************************************************************
 * @fn      CtrlSetUsbAddress
 *
 * @brief   Set USB device address.
 *
 * @param   addr: Device address.
 *
 * @return  ERR_SUCCESS
 */
UINT8 CtrlSetUsbAddress(UINT8 addr)
{
    UINT8 s;

    CopySetupReqPkg(SetupSetUsbAddr);
    pSetupReq->wValue = addr;
    s = HostCtrlTransfer(NULL, NULL);
    if(s != ERR_SUCCESS)
        return (s);
    SetHostUsbAddr(addr);
    Delay_Ms(10);

    return (ERR_SUCCESS);
}

/*********************************************************************
 * @fn      CtrlSetUsbConfig
 *
 * @brief   Set usb configration.
 *
 * @param   cfg: Configration Value.
 *
 * @return  ERR_SUCCESS
 */
UINT8 CtrlSetUsbConfig(UINT8 cfg)
{
    CopySetupReqPkg(SetupSetUsbConfig);
    pSetupReq->wValue = cfg;
    return (HostCtrlTransfer(NULL, NULL));
}

/*********************************************************************
 * @fn      CtrlClearEndpStall
 *
 * @brief   Clear endpoint STALL.
 *
 * @param   endp: Endpoint address.
 *
 * @return  ERR_SUCCESS
 */
UINT8 CtrlClearEndpStall(UINT8 endp)
{
    CopySetupReqPkg(SetupClrEndpStall);
    pSetupReq->wIndex = endp;
    return (HostCtrlTransfer(NULL, NULL));
}

/*********************************************************************
 * @fn      CtrlSetUsbIntercace
 *
 * @brief   Set USB Interface configration.
 *
 * @param   cfg: Configration value.
 *
 * @return  ERR_SUCCESS
 */
UINT8 CtrlSetUsbIntercace(UINT8 cfg)
{
    CopySetupReqPkg(SetupSetUsbInterface);
    pSetupReq->wValue = cfg;
    return (HostCtrlTransfer(NULL, NULL));
}

/*********************************************************************
 * @fn      USB_HostInit
 *
 * @brief   Initializes USB host mode.
 *
 * @return  ERR_SUCCESS
 */
void USB_HostInit(void)
{
    R8_USB_CTRL = RB_UC_HOST_MODE;
    R8_UHOST_CTRL = 0;
    R8_USB_DEV_AD = 0x00;
    R8_UH_EP_MOD = RB_UH_EP_TX_EN | RB_UH_EP_RX_EN;
    R16_UH_RX_DMA = (UINT16)(UINT32)pHOST_RX_RAM_Addr;
    R16_UH_TX_DMA = (UINT16)(UINT32)pHOST_TX_RAM_Addr;

    R8_UH_RX_CTRL = 0x00;
    R8_UH_TX_CTRL = 0x00;
    R8_USB_CTRL = RB_UC_HOST_MODE | RB_UC_INT_BUSY | RB_UC_DMA_EN;
    R8_UH_SETUP = RB_UH_SOF_EN;
    R8_USB_INT_FG = 0xFF;
    DisableRootHubPort();
    R8_USB_INT_EN = RB_UIE_TRANSFER | RB_UIE_DETECT;

    FoundNewDev = 0;
}

/*********************************************************************
 * @fn      InitRootDevice
 *
 * @brief   Initializes USB root hub.
 *
 * @param   DataBuf: Data buffer.
 *
 * @return  ERROR
 */
UINT8 InitRootDevice(PUINT8 DataBuf)
{
    UINT8 i, s;
    UINT8 cfg, dv_cls, if_cls;

    ResetRootHubPort();

    for(i = 0, s = 0; i < 100; i++)
    {
        Delay_Ms(1);
        if(EnableRootHubPort() == ERR_SUCCESS)
        {
            i = 0;
            s++;
            if(s > 100)
                break;
        }
    }

    if(i)
    {
        DisableRootHubPort();
        return (ERR_USB_DISCON);
    }

    SetUsbSpeed(ThisUsbDev.DeviceSpeed);

    s = CtrlGetDeviceDescr(DataBuf);

    if(s == ERR_SUCCESS)
    {
        ThisUsbDev.DeviceVID = ((PUSB_DEV_DESCR)DataBuf)->idVendor;
        ThisUsbDev.DevicePID = ((PUSB_DEV_DESCR)DataBuf)->idProduct;
        dv_cls = ((PUSB_DEV_DESCR)DataBuf)->bDeviceClass;

        s = CtrlSetUsbAddress(((PUSB_SETUP_REQ)SetupSetUsbAddr)->wValue);

        if(s == ERR_SUCCESS)
        {
            ThisUsbDev.DeviceAddress = ((PUSB_SETUP_REQ)SetupSetUsbAddr)->wValue;

            s = CtrlGetConfigDescr(DataBuf);

            if(s == ERR_SUCCESS)
            {
                cfg = ((PUSB_CFG_DESCR)DataBuf)->bConfigurationValue;
                if_cls = ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceClass;

                if((dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_STORAGE))
                {
#ifdef FOR_ROOT_UDISK_ONLY
                    CH103DiskStatus = DISK_USB_ADDR;
                    return (ERR_SUCCESS);
                }
                else
                    return (ERR_USB_UNSUPPORT);

#else
                    s = CtrlSetUsbConfig(cfg);

                    if(s == ERR_SUCCESS)
                    {
                        ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                        ThisUsbDev.DeviceType = USB_DEV_CLASS_STORAGE;
                        SetUsbSpeed(1);
                        return (ERR_SUCCESS);
                    }
                }
                else if((dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_PRINTER) && ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceSubClass == 0x01)
                {
                    s = CtrlSetUsbConfig(cfg);
                    if(s == ERR_SUCCESS)
                    {
                        ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                        ThisUsbDev.DeviceType = USB_DEV_CLASS_PRINTER;
                        SetUsbSpeed(1);
                        return (ERR_SUCCESS);
                    }
                }
                else if((dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_HID) && ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceSubClass <= 0x01)
                {
                    if_cls = ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceProtocol;
                    s = CtrlSetUsbConfig(cfg);
                    if(s == ERR_SUCCESS)
                    {
                        ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                        if(if_cls == 1)
                        {
                            ThisUsbDev.DeviceType = DEV_TYPE_KEYBOARD;
                            SetUsbSpeed(1);
                            return (ERR_SUCCESS);
                        }
                        else if(if_cls == 2)
                        {
                            ThisUsbDev.DeviceType = DEV_TYPE_MOUSE;
                            SetUsbSpeed(1);
                            return (ERR_SUCCESS);
                        }
                        s = ERR_USB_UNSUPPORT;
                    }
                }
                else
                {
                    s = CtrlSetUsbConfig(cfg);
                    if(s == ERR_SUCCESS)
                    {
                        ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                        ThisUsbDev.DeviceType = DEV_TYPE_UNKNOW;
                        SetUsbSpeed(1);
                        return (ERR_SUCCESS);
                    }
                }

#endif
            }
        }
    }

#ifdef FOR_ROOT_UDISK_ONLY
    CH103DiskStatus = DISK_CONNECT;

#else
    ThisUsbDev.DeviceStatus = ROOT_DEV_FAILED;

#endif

    SetUsbSpeed(1);

    return (s);
}

/*********************************************************************
 * @fn      HubGetPortStatus
 *
 * @brief   查询HUB端口状态,返回在Com_Buffer中
 *
 * @param   UINT8 HubPortIndex
 *
 * @return  ERR_SUCCESS 成功
 *          ERR_USB_BUF_OVER 长度错误
 */
UINT8 HubGetPortStatus(UINT8 HubPortIndex)
{
    UINT8 s;
    UINT8 len;

    pSetupReq->bRequestType = HUB_GET_PORT_STATUS;
    pSetupReq->bRequest = HUB_GET_STATUS;
    pSetupReq->wValue = 0x0000;
    pSetupReq->wIndex = 0x0000 | HubPortIndex;
    pSetupReq->wLength = 0x0004;
    s = HostCtrlTransfer(Com_Buffer, &len); // 执行控制传输
    if(s != ERR_SUCCESS)
    {
        return (s);
    }
    if(len < 4)
    {
        return (ERR_USB_BUF_OVER); // 描述符长度错误
    }

    return (ERR_SUCCESS);
}

/*********************************************************************
 * @fn      HubSetPortFeature
 *
 * @brief   设置HUB端口特性
 *
 * @param   UINT8 HubPortIndex
 *          UINT8 FeatureSelt
 *
 * @return  ERR_SUCCESS 成功
 */
UINT8 HubSetPortFeature(UINT8 HubPortIndex, UINT8 FeatureSelt)
{
    pSetupReq->bRequestType = HUB_SET_PORT_FEATURE;
    pSetupReq->bRequest = HUB_SET_FEATURE;
    pSetupReq->wValue = 0x0000 | FeatureSelt;
    pSetupReq->wIndex = 0x0000 | HubPortIndex;
    pSetupReq->wLength = 0x0000;
    return (HostCtrlTransfer(NULL, NULL)); // 执行控制传输
}

/*********************************************************************
 * @fn      HubClearPortFeature
 *
 * @brief   清除HUB端口特性
 *
 * @param   UINT8 HubPortIndex
 *          UINT8 FeatureSelt
 *
 * @return  ERR_SUCCESS 成功
 */
UINT8 HubClearPortFeature(UINT8 HubPortIndex, UINT8 FeatureSelt)
{
    pSetupReq->bRequestType = HUB_CLEAR_PORT_FEATURE;
    pSetupReq->bRequest = HUB_CLEAR_FEATURE;
    pSetupReq->wValue = 0x0000 | FeatureSelt;
    pSetupReq->wIndex = 0x0000 | HubPortIndex;
    pSetupReq->wLength = 0x0000;
    return (HostCtrlTransfer(NULL, NULL)); // 执行控制传输
}
