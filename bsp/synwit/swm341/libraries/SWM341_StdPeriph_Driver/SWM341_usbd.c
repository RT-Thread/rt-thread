/******************************************************************************************************************************************
* 文件名称: SWM341_usbd.c
* 功能说明: SWM341单片机的USB设备功能驱动库
* 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.1.0      2020年11月3日
* 升级记录:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
*******************************************************************************************************************************************/
#include <string.h>
#include "SWM341.h"
#include "SWM341_usbd.h"


USBD_Info_t USBD_Info;


static uint8_t *CtrlIn_Ptr = 0;
static uint8_t *CtrlOut_Ptr = 0;
static volatile uint32_t CtrlIn_Size = 0;
static volatile uint32_t CtrlOut_Size = 0;
static volatile uint32_t CtrlOut_Limit = 0;


/******************************************************************************************************************************************
* 函数名称: USBD_Init()
* 功能说明: USB Device 初始化
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_Init(void)
{
    uint8_t  ep_reg = 0, ep_nbr, ep_dir, ep_type, cfg, intf, alt;
    uint16_t ep_pksz;
    uint8_t  *pCfg = USBD_Info.DescConfig;
    uint32_t total_len = pCfg[2] + (pCfg[3] << 8);
    uint32_t epie = 0x00010001;

    SYS->USBCR = 0;
    for(int i = 0; i < CyclesPerUs; i++) __NOP();
    SYS->USBCR |= (1 << SYS_USBCR_RST48M_Pos); __DSB();
    SYS->USBCR |= (1 << SYS_USBCR_RST12M_Pos); __DSB();
    SYS->USBCR |= (1 << SYS_USBCR_RSTPLL_Pos); __DSB();

    SYS->USBCR &= ~SYS_USBCR_ROLE_Msk;
    SYS->USBCR |= (USBD_Info.Mode << SYS_USBCR_ROLE_Pos);

    SYS->USBCR |= (1 << SYS_USBCR_VBUS_Pos);

    SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_USB_Pos);

    USBD_EPConfig(ep_reg++, 0, USB_EP_IN,  USB_EP_CTRL, USBD_Info.CtrlPkSiz, 0, 0, 0);  // Control In
    USBD_EPConfig(ep_reg++, 0, USB_EP_OUT, USB_EP_CTRL, USBD_Info.CtrlPkSiz, 0, 0, 0);  // Control Out

    while(pCfg < (USBD_Info.DescConfig + total_len))
    {
        switch(pCfg[1])
        {
        case USB_DESC_CONFIG:
            cfg  = pCfg[5];
            break;

        case USB_DESC_INTERFACE:
            intf = pCfg[2];
            alt  = pCfg[3];
            break;

        case USB_DESC_ENDPOINT:
            ep_nbr  = pCfg[2] & 0x0F;
            ep_dir  = pCfg[2] & USB_EP_IN;
            ep_type = pCfg[3] & 0x03;
            ep_pksz = pCfg[4] + (pCfg[5] << 8);

            USBD_EPConfig(ep_reg++, ep_nbr, ep_dir, ep_type, ep_pksz, cfg, intf, alt);

            epie |= (1 << ep_nbr) << (ep_dir ? 0 : 16);
            break;
        }

        pCfg += pCfg[0];
    }

    USBD->FFTHR = (0xFFF << 16) | (0x000 << 0);  // 无用

    USBD->DEVCR = (USBD_Info.Speed << USBD_DEVCR_SPEED_Pos)  |
                  (1               << USBD_DEVCR_DEVICE_Pos) |
                  (1               << USBD_DEVCR_CSRDONE_Pos);

    USBD->DEVIE = (1 << USBD_DEVIE_RST_Pos)   |
                  (1 << USBD_DEVIE_SETUP_Pos) |
                  (1 << USBD_DEVIE_SETCFG_Pos);

    USBD->EPIE = epie;

    SYS->USBPHYCR &= ~SYS_USBPHYCR_OPMODE_Msk;
    SYS->USBPHYCR |= (0 << SYS_USBPHYCR_OPMODE_Pos);    //Normal Operation
}


/******************************************************************************************************************************************
* 函数名称: USBD_EPConfig()
* 功能说明: USB Device Endpoint Configure
* 输    入: uint8_t ep_reg        Endpoint Register
*           uint8_t ep_nbr      Endpoint Number used by host
*           uint8_t ep_dir      Endpoint Direction, 0 Out  1 In
*           uint8_t ep_type     Endpoint Type,      0 Control   1  Isochronous   2 Bulk   3 Interrupt
*           uint16_t ep_pksz    Maximum packet size in byte
*           uint8_t cfg         Configuration number to which this endpoint belongs
*           uint8_t intf        Interface number to which this endpoint belongs
*           uint8_t alt         Alternate setting to which this endpoint belongs
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_EPConfig(uint8_t ep_reg, uint8_t ep_nbr, uint8_t ep_dir, uint8_t ep_type, uint16_t ep_pksz, uint8_t cfg, uint8_t intf, uint8_t alt)
{
    ep_dir = ep_dir ? 1 : 0;    // for USB_EP_IN、USB_EP_OUT

    USBD->EPCFG[ep_reg] = (ep_nbr  << USBD_EPCFG_EPNR_Pos) |
                          (ep_dir  << USBD_EPCFG_DIR_Pos)  |
                          (ep_type << USBD_EPCFG_TYPE_Pos) |
                          (cfg     << USBD_EPCFG_CFG_Pos)  |
                          (intf    << USBD_EPCFG_INTF_Pos) |
                          (alt     << USBD_EPCFG_ALT_Pos)  |
                          (ep_pksz << USBD_EPCFG_PKSZ_Pos);

    if(ep_dir == USB_EP_OUT)
    {
        USBD->OUTEP[ep_nbr].RXCR = 0;
        USBD->OUTEP[ep_nbr].RXCR = USBD_RXCR_FLUSHFF_Msk;
    }
    else
    {
        USBD->INEP[ep_nbr].TXCR = 0;
        USBD->INEP[ep_nbr].TXCR = USBD_TXCR_FLUSHFF_Msk;
    }
}


/******************************************************************************************************************************************
* 函数名称: USBD_Open()
* 功能说明: USB Device 打开
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_Open(void)
{
    NVIC_EnableIRQ(USB_IRQn);
}

/******************************************************************************************************************************************
* 函数名称: USBD_Close()
* 功能说明: USB Device 关闭
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_Close(void)
{
    NVIC_DisableIRQ(USB_IRQn);
}


void USBD_StandardRequest(USB_Setup_Packet_t * pSetup);
void USBD_GetDescriptor(USB_Setup_Packet_t * pSetup);

static USB_Setup_Packet_t Setup_Packet;
USB_Setup_Packet_t * pUSB_Setup = &Setup_Packet;
/******************************************************************************************************************************************
* 函数名称: USBD_ProcessSetupPacket()
* 功能说明: 处理Setup包
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_ProcessSetupPacket(void)
{
    ((volatile uint32_t *)pUSB_Setup)[0] = USBD->SETUPD1;
    ((volatile uint32_t *)pUSB_Setup)[1] = USBD->SETUPD2;

    switch(pUSB_Setup->bRequestType & 0x60)
    {
    case USB_REQ_STANDARD:
        USBD_StandardRequest(pUSB_Setup);
        break;

    case USB_REQ_CLASS:
        if(USBD_Info.pClassRequest_Callback != NULL)
        {
            USBD_Info.pClassRequest_Callback(pUSB_Setup);
        }
        break;

    case USB_REQ_VENDOR:
        if(USBD_Info.pVendorRequest_Callback != NULL)
        {
            USBD_Info.pVendorRequest_Callback(pUSB_Setup);
        }
        break;

    default:
        /* Setup error, stall the device */
        USBD_Stall0();
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: USBD_StandardRequest()
* 功能说明: 处理标准请求
* 输    入: 无
* 输    出: 无
* 注意事项: GetDescriptor、SetDescriptor、SyncFrame之外的标准命令USB模块自动处理，无需用户代码参与
******************************************************************************************************************************************/
void USBD_StandardRequest(USB_Setup_Packet_t * pSetup)
{
    if(pSetup->bRequestType & 0x80)     // Device to host
    {
        switch(pSetup->bRequest)
        {
        case USB_GET_DESCRIPTOR:
            USBD_GetDescriptor(pSetup);

            /* Status stage */
            USBD_RxReady(0);
            break;

        default:
            /* Setup error, stall the device */
            USBD_Stall0();
            break;
        }
    }
    else                                // Host to device
    {
        switch(pSetup->bRequest)
        {
        default:
            /* Setup error, stall the device */
            USBD_Stall0();
            break;
        }
    }
}

/******************************************************************************************************************************************
* 函数名称: USBD_GetDescriptor()
* 功能说明: 处理标准请求GetDescriptor
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_GetDescriptor(USB_Setup_Packet_t * pSetup)
{
#define min(a, b)   ((a)<(b) ? (a) : (b))

    switch(pSetup->wValue >> 8)
    {
    case USB_DESC_DEVICE:
        USBD_PrepareCtrlIn(USBD_Info.DescDevice, min(pSetup->wLength, USBD_Info.DescDevice[0]));
        break;

    case USB_DESC_CONFIG:
    {
        uint16_t total_len = USBD_Info.DescConfig[2] + (USBD_Info.DescConfig[3] << 8);
        USBD_PrepareCtrlIn(USBD_Info.DescConfig, min(pSetup->wLength, total_len));
        break;
    }

    case USB_DESC_STRING:
    {
        uint8_t index = pSetup->wValue & 0xFF;
        if(index < 6)
        {
            USBD_PrepareCtrlIn(USBD_Info.DescString[index], min(pSetup->wLength, USBD_Info.DescString[index][0]));
        }
        else if((index == 0xEE) && USBD_Info.DescOSString)
        {
            USBD_PrepareCtrlIn(USBD_Info.DescOSString, min(pSetup->wLength, USBD_Info.DescOSString[0]));
        }
        else
        {
            /* Not support. Reply STALL. */
            USBD_Stall0();
        }
        break;
    }

    case USB_DESC_BOS:
    {
        uint16_t total_len = USBD_Info.DescBOS[2] + (USBD_Info.DescBOS[3] << 8);
        USBD_PrepareCtrlIn(USBD_Info.DescBOS, min(pSetup->wLength, total_len));
        break;
    }

    case USB_DESC_HID:
    {
        uint8_t  index   = pSetup->wIndex & 0xFF;
        uint16_t offset  = USBD_Info.DescHIDOffset[index];
        uint8_t *descHID = &USBD_Info.DescConfig[offset];
        USBD_PrepareCtrlIn(descHID, min(pSetup->wLength, descHID[0]));
        break;
    }

    case USB_DESC_HID_RPT:
    {
        uint8_t  index   = pSetup->wIndex & 0xFF;
        uint16_t offset  = USBD_Info.DescHIDOffset[index];
        uint8_t *descHID = &USBD_Info.DescConfig[offset];
        uint16_t report_len = descHID[7] + (descHID[8] << 8);
        USBD_PrepareCtrlIn(USBD_Info.DescHIDReport[index], min(pSetup->wLength, report_len));
        break;
    }

    default:
        /* Not support. Reply STALL.*/
        USBD_Stall0();
        break;
    }
}

/******************************************************************************************************************************************
* 函数名称: USBD_PrepareCtrlIn()
* 功能说明: Prepare the first Control IN pipe
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_PrepareCtrlIn(uint8_t buf[], uint32_t size)
{
    CtrlIn_Ptr = buf;
    CtrlIn_Size = size;

    USBD_CtrlIn();
}

/******************************************************************************************************************************************
* 函数名称: USBD_CtrlIn()
* 功能说明: Repeat Control IN pipe. This function processes the remained data of Control IN transfer
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_CtrlIn(void)
{
    static uint8_t ZeroLenPk = 0;

    if(CtrlIn_Size)
    {
        /* Process remained data */
        if(CtrlIn_Size > USBD_Info.CtrlPkSiz)
        {
            USBD_TxWrite(0, CtrlIn_Ptr, USBD_Info.CtrlPkSiz);

            CtrlIn_Ptr += USBD_Info.CtrlPkSiz;
            CtrlIn_Size -= USBD_Info.CtrlPkSiz;
        }
        else
        {
            USBD_TxWrite(0, CtrlIn_Ptr, CtrlIn_Size);

            if(CtrlIn_Size == USBD_Info.CtrlPkSiz)
            {
                ZeroLenPk = 1;
            }

            CtrlIn_Ptr = 0;
            CtrlIn_Size = 0;
        }
    }
    else
    {
        /* For the case of data size is integral times maximum packet size */
        if(ZeroLenPk)
        {
            ZeroLenPk = 0;
            USBD_TxWrite(0, 0, 0);
        }
    }
}

/******************************************************************************************************************************************
* 函数名称: USBD_PrepareCtrlOut()
* 功能说明: Prepare the first Control OUT pipe
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_PrepareCtrlOut(uint8_t *buf, uint32_t size)
{
    CtrlOut_Ptr = buf;
    CtrlOut_Size = 0u;
    CtrlOut_Limit = size;

    USBD_RxReady(0);
}

/******************************************************************************************************************************************
* 函数名称: USBD_CtrlOut()
* 功能说明: Repeat Control OUT pipe. This function processes the successive Control OUT transfer
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_CtrlOut(void)
{
    if(CtrlOut_Size < CtrlOut_Limit)
    {
        uint16_t size = USBD_RxRead(CtrlOut_Ptr, CtrlOut_Limit - CtrlOut_Size);

        CtrlOut_Ptr += size;
        CtrlOut_Size += size;

        if(CtrlOut_Size < CtrlOut_Limit)
        {
            USBD_RxReady(0);
        }
    }
}


/******************************************************************************************************************************************
* 函数名称: USBD_TxWrite()
* 功能说明: 将要发送到主机的数据写入端点的FIFO
* 输    入: uint8_t  epnr         endpoint number
*           uint8_t *data           要写入FIFO的数据
*           uint16_t size           要写入数据的个数
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void USBD_TxWrite(uint8_t epnr, uint8_t *data, uint16_t size)
{
    __disable_irq();

    USBD->INEP[epnr].TXCR = (1 << USBD_TXCR_FLUSHFF_Pos);

    USBD->INEP[epnr].TXTRSZ = size;
    if(size) USBD_memcpy((uint8_t *)USBD->TXBUF[epnr], data, size);
    USBD->INEP[epnr].TXCR = (1 << USBD_TXCR_FFRDY_Pos);

    __enable_irq();
}

/******************************************************************************************************************************************
* 函数名称: USBD_RxRead()
* 功能说明: 读取接收到的数据
* 输    入: uint8_t *buff         读取到的数据存入buff
*           uint16_t size           buff大小
* 输    出: uint16_t              实际读取到数据的个数
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t USBD_RxRead(uint8_t *buff, uint16_t size)
{
    __disable_irq();

    uint16_t real_size = (USBD->RXSR & USBD_RXSR_TRSZ_Msk) >> USBD_RXSR_TRSZ_Pos;

    if(size > real_size)
        size = real_size;

    USBD_memcpy(buff, (uint8_t *)USBD->RXBUF, size);

    __enable_irq();

    return size;
}

/******************************************************************************************************************************************
* 函数名称: USBD_memcpy()
* 功能说明: 访问 USB Buffer 的 memcpy
* 输    入: void *destin          目的地址
*           void *source            源地址
*           uint32_t nByte          拷贝字节数
* 输    出: 无
* 注意事项: 访问 USB Buffer 必须使用 USBD_memcpy，不能使用库函数 memcpy
******************************************************************************************************************************************/
void USBD_memcpy(uint8_t *destin, uint8_t *source, uint32_t nByte)
{
    while(nByte > 3)
    {
        *((uint32_t *)destin) = *((uint32_t *)source);
        destin += 4;
        source += 4;
        nByte  -= 4;
    }

    while(nByte > 1)
    {
        *((uint16_t *)destin) = *((uint16_t *)source);
        destin += 2;
        source += 2;
        nByte  -= 2;
    }

    while(nByte > 0)
    {
        *destin = *source;
        destin += 1;
        source += 1;
        nByte  -= 1;
    }
}
