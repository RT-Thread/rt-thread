/**************************************************************************//**
 * @file     usbd.c
 * @version  V3.00
 * @brief    M2354 series USBD driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <string.h>
#include "NuMicro.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup USBD_Driver USBD Driver
  @{
*/


/** @addtogroup USBD_EXPORTED_FUNCTIONS USBD Exported Functions
  @{
*/

/* Global variables for Control Pipe */
uint8_t g_USBD_au8SetupPacket[8] = {0UL};       /*!< Setup packet buffer */
volatile uint8_t g_USBD_u8RemoteWakeupEn = 0UL; /*!< Remote wake up function enable flag */

/**
 * @cond HIDDEN_SYMBOLS
 */
static uint8_t *s_USBD_pu8CtrlInPointer = 0;
static uint8_t *s_USBD_pu8CtrlOutPointer = 0;
static volatile uint32_t s_USBD_u32CtrlInSize = 0UL;
static volatile uint32_t s_USBD_u32CtrlOutSize = 0UL;
static volatile uint32_t s_USBD_u32CtrlOutSizeLimit = 0UL;
static volatile uint32_t s_USBD_u32UsbAddr = 0UL;
static volatile uint32_t s_USBD_u32UsbConfig = 0UL;
static volatile uint32_t s_USBD_u32CtrlMaxPktSize = 8UL;
static volatile uint32_t s_USBD_u32UsbAltInterface = 0UL;
static volatile uint8_t  s_USBD_u8CtrlInZeroFlag = 0UL;
/**
 * @endcond
 */

const S_USBD_INFO_T *g_USBD_sInfo;                  /*!< A pointer for USB information structure */

VENDOR_REQ g_USBD_pfnVendorRequest       = NULL;    /*!< USB Vendor Request Functional Pointer */
CLASS_REQ g_USBD_pfnClassRequest         = NULL;    /*!< USB Class Request Functional Pointer */
SET_INTERFACE_REQ g_USBD_pfnSetInterface = NULL;    /*!< USB Set Interface Functional Pointer */
SET_CONFIG_CB g_USBD_pfnSetConfigCallback = NULL;   /*!< USB Set configuration callback function pointer */
uint32_t g_USBD_u32EpStallLock           = 0UL;     /*!< Bit map flag to lock specified EP when SET_FEATURE */

/**
  * @brief      This function makes USBD module to be ready to use
  *
  * @param[in]  param           The structure of USBD information.
  * @param[in]  pfnClassReq     USB Class request callback function.
  * @param[in]  pfnSetInterface USB Set Interface request callback function.
  *
  * @return     None
  *
  * @details    This function will enable USB controller, USB PHY transceiver and pull-up resistor of USB_D+ pin. USB PHY will drive SE0 to bus.
  */
void USBD_Open(const S_USBD_INFO_T *param, CLASS_REQ pfnClassReq, SET_INTERFACE_REQ pfnSetInterface)
{
    USBD_T *pUSBD;

    if((__PC() & NS_OFFSET) == NS_OFFSET)
    {
        pUSBD = USBD_NS;
    }
    else
    {
        pUSBD = USBD;
    }

    g_USBD_sInfo = param;
    g_USBD_pfnClassRequest = pfnClassReq;
    g_USBD_pfnSetInterface = pfnSetInterface;

    /* get EP0 maximum packet size */
    s_USBD_u32CtrlMaxPktSize = g_USBD_sInfo->gu8DevDesc[7];

    /* Initial USB engine */
#ifdef SUPPORT_LPM
    pUSBD->ATTR = 0x7D0UL | USBD_LPMACK;
#else
    pUSBD->ATTR = 0x7D0UL;
#endif
    /* Force SE0 */
    USBD_SET_SE0();
}

/**
  * @brief    This function makes USB host to recognize the device
  *
  * @param    None
  *
  * @return   None
  *
  * @details  Enable WAKEUP, FLDET, USB and BUS interrupts. Disable software-disconnect function after 100ms delay with SysTick timer.
  */
void USBD_Start(void)
{
    /* Disable software-disconnect function */
    USBD_CLR_SE0();

    /* Clear USB-related interrupts before enable interrupt */
    USBD_CLR_INT_FLAG(USBD_INT_BUS | USBD_INT_USB | USBD_INT_FLDET | USBD_INT_WAKEUP);

    /* Enable USB-related interrupts. */
    USBD_ENABLE_INT(USBD_INT_BUS | USBD_INT_USB | USBD_INT_FLDET | USBD_INT_WAKEUP);
}

/**
  * @brief      Get the received SETUP packet
  *
  * @param[in]  buf A buffer pointer used to store 8-byte SETUP packet.
  *
  * @return     None
  *
  * @details    Store SETUP packet to a user-specified buffer.
  *
  */
void USBD_GetSetupPacket(uint8_t *buf)
{
    USBD_MemCopy(buf, g_USBD_au8SetupPacket, 8UL);
}

/**
  * @brief    Process SETUP packet
  *
  * @param    None
  *
  * @return   None
  *
  * @details  Parse SETUP packet and perform the corresponding action.
  *
  */
void USBD_ProcessSetupPacket(void)
{
    /* Get SETUP packet from USB buffer */
    USBD_MemCopy(g_USBD_au8SetupPacket, (uint8_t *)USBD_BUF_BASE, 8UL);

    /* Check the request type */
    switch(g_USBD_au8SetupPacket[0] & 0x60UL)
    {
        case REQ_STANDARD:   /* Standard */
        {
            USBD_StandardRequest();
            break;
        }
        case REQ_CLASS:   /* Class */
        {
            if(g_USBD_pfnClassRequest != NULL)
            {
                g_USBD_pfnClassRequest();
            }
            break;
        }
        case REQ_VENDOR:   /* Vendor */
        {
            if(g_USBD_pfnVendorRequest != NULL)
            {
                g_USBD_pfnVendorRequest();
            }
            break;
        }
        default:   /* reserved */
        {
            /* Setup error, stall the device */
            USBD_SET_EP_STALL(EP0);
            USBD_SET_EP_STALL(EP1);
            break;
        }
    }
}

/**
  * @brief    Process GetDescriptor request
  *
  * @param    None
  *
  * @return   None
  *
  * @details  Parse GetDescriptor request and perform the corresponding action.
  *
  */
void USBD_GetDescriptor(void)
{
    uint32_t u32Len;

    s_USBD_u8CtrlInZeroFlag = (uint8_t)0UL;
    u32Len = 0UL;
    u32Len = g_USBD_au8SetupPacket[7];
    u32Len <<= 8UL;
    u32Len += g_USBD_au8SetupPacket[6];

    switch(g_USBD_au8SetupPacket[3])
    {
        /* Get Device Descriptor */
        case DESC_DEVICE:
        {
            u32Len = USBD_Minimum(u32Len, (uint32_t)LEN_DEVICE);
            USBD_PrepareCtrlIn((uint8_t *)g_USBD_sInfo->gu8DevDesc, u32Len);
            break;
        }
        /* Get Configuration Descriptor */
        case DESC_CONFIG:
        {
            uint32_t u32TotalLen;

            u32TotalLen = g_USBD_sInfo->gu8ConfigDesc[3];
            u32TotalLen = g_USBD_sInfo->gu8ConfigDesc[2] + (u32TotalLen << 8UL);

            if(u32Len > u32TotalLen)
            {
                u32Len = u32TotalLen;
                if((u32Len % s_USBD_u32CtrlMaxPktSize) == 0UL)
                {
                    s_USBD_u8CtrlInZeroFlag = (uint8_t)1UL;
                }
            }
            USBD_PrepareCtrlIn((uint8_t *)g_USBD_sInfo->gu8ConfigDesc, u32Len);
            break;
        }
        /* Get BOS Descriptor */
        case DESC_BOS:
        {
            if(g_USBD_sInfo->gu8BosDesc == 0)
            {
                USBD_SET_EP_STALL(EP0);
                USBD_SET_EP_STALL(EP1);
            }
            else
            {
                u32Len = USBD_Minimum(u32Len, LEN_BOS + LEN_BOSCAP);
                USBD_PrepareCtrlIn((uint8_t *)g_USBD_sInfo->gu8BosDesc, u32Len);
            }
            break;
        }
        /* Get HID Descriptor */
        case DESC_HID:
        {
            /* CV3.0 HID Class Descriptor Test,
               Need to indicate index of the HID Descriptor within gu8ConfigDescriptor, specifically HID Composite device. */
            uint32_t u32ConfigDescOffset;   /* u32ConfigDescOffset is configuration descriptor offset (HID descriptor start index) */
            u32Len = USBD_Minimum(u32Len, LEN_HID);
            u32ConfigDescOffset = g_USBD_sInfo->gu32ConfigHidDescIdx[g_USBD_au8SetupPacket[4]];
            USBD_PrepareCtrlIn((uint8_t *)&g_USBD_sInfo->gu8ConfigDesc[u32ConfigDescOffset], u32Len);
            break;
        }
        /* Get Report Descriptor */
        case DESC_HID_RPT:
        {
            if(u32Len > g_USBD_sInfo->gu32HidReportSize[g_USBD_au8SetupPacket[4]])
            {
                u32Len = g_USBD_sInfo->gu32HidReportSize[g_USBD_au8SetupPacket[4]];
                if((u32Len % s_USBD_u32CtrlMaxPktSize) == 0UL)
                {
                    s_USBD_u8CtrlInZeroFlag = (uint8_t)1UL;
                }
            }
            USBD_PrepareCtrlIn((uint8_t *)g_USBD_sInfo->gu8HidReportDesc[g_USBD_au8SetupPacket[4]], u32Len);
            break;
        }
        /* Get String Descriptor */
        case DESC_STRING:
        {
            /* Get String Descriptor */
            if(g_USBD_au8SetupPacket[2] < 4UL)
            {
                if(u32Len > g_USBD_sInfo->gu8StringDesc[g_USBD_au8SetupPacket[2]][0])
                {
                    u32Len = g_USBD_sInfo->gu8StringDesc[g_USBD_au8SetupPacket[2]][0];
                    if((u32Len % s_USBD_u32CtrlMaxPktSize) == 0UL)
                    {
                        s_USBD_u8CtrlInZeroFlag = (uint8_t)1UL;
                    }
                }
                USBD_PrepareCtrlIn((uint8_t *)g_USBD_sInfo->gu8StringDesc[g_USBD_au8SetupPacket[2]], u32Len);
                break;
            }
            else
            {
                /* Not support. Reply STALL. */
                USBD_SET_EP_STALL(EP0);
                USBD_SET_EP_STALL(EP1);
                break;
            }
        }
        default:
            /* Not support. Reply STALL. */
            USBD_SET_EP_STALL(EP0);
            USBD_SET_EP_STALL(EP1);
            break;
    }
}

/**
  * @brief    Process standard request
  *
  * @param    None
  *
  * @return   None
  *
  * @details  Parse standard request and perform the corresponding action.
  *
  */
void USBD_StandardRequest(void)
{
    uint32_t u32Addr;
    USBD_T *pUSBD;
    OTG_T *pOTG;

    if((__PC() & NS_OFFSET) == NS_OFFSET)
    {
        pUSBD = USBD_NS;
        pOTG = OTG_NS;
    }
    else
    {
        pUSBD = USBD;
        pOTG = OTG;
    }

    /* clear global variables for new request */
    s_USBD_pu8CtrlInPointer = 0;
    s_USBD_u32CtrlInSize = 0UL;

    if((g_USBD_au8SetupPacket[0] & 0x80UL) == 0x80UL)    /* request data transfer direction */
    {
        /* Device to host */
        switch(g_USBD_au8SetupPacket[1])
        {
            case GET_CONFIGURATION:
            {
                /* Return current configuration setting */
                /* Data stage */
                u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
                M8(u32Addr) = (uint8_t)s_USBD_u32UsbConfig;
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 1UL);
                /* Status stage */
                USBD_PrepareCtrlOut(0, 0UL);
                break;
            }
            case GET_DESCRIPTOR:
            {
                USBD_GetDescriptor();
                USBD_PrepareCtrlOut(0, 0UL); /* For status stage */
                break;
            }
            case GET_INTERFACE:
            {
                /* Return current interface setting */
                /* Data stage */
                u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
                M8(u32Addr) = (uint8_t)s_USBD_u32UsbAltInterface;
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 1UL);
                /* Status stage */
                USBD_PrepareCtrlOut(0, 0UL);
                break;
            }
            case GET_STATUS:
            {
                /* Device */
                if(g_USBD_au8SetupPacket[0] == 0x80UL)
                {
                    uint8_t u8Tmp;

                    u8Tmp = (uint8_t)0UL;
                    if((g_USBD_sInfo->gu8ConfigDesc[7] & 0x40UL) == 0x40UL)
                    {
                        u8Tmp |= (uint8_t)1UL; /* Self-Powered/Bus-Powered. */
                    }
                    if((g_USBD_sInfo->gu8ConfigDesc[7] & 0x20UL) == 0x20UL)
                    {
                        u8Tmp |= (uint8_t)(g_USBD_u8RemoteWakeupEn << 1UL); /* Remote wake up */
                    }

                    u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
                    M8(u32Addr) = u8Tmp;

                }
                /* Interface */
                else if(g_USBD_au8SetupPacket[0] == 0x81UL)
                {
                    u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
                    M8(u32Addr) = (uint8_t)0UL;
                }
                /* Endpoint */
                else if(g_USBD_au8SetupPacket[0] == 0x82UL)
                {
                    uint8_t ep = (uint8_t)(g_USBD_au8SetupPacket[4] & 0xFUL);
                    u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
                    M8(u32Addr) = (uint8_t)(USBD_GetStall(ep) ? 1UL : 0UL);
                }

                u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1UL;
                M8(u32Addr) = (uint8_t)0UL;
                /* Data stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 2UL);
                /* Status stage */
                USBD_PrepareCtrlOut(0, 0UL);
                break;
            }
            default:
            {
                /* Setup error, stall the device */
                USBD_SET_EP_STALL(EP0);
                USBD_SET_EP_STALL(EP1);
                break;
            }
        }
    }
    else
    {
        /* Host to device */
        switch(g_USBD_au8SetupPacket[1])
        {
            case CLEAR_FEATURE:
            {
                if(g_USBD_au8SetupPacket[2] == FEATURE_ENDPOINT_HALT)
                {
                    uint32_t epNum, i;

                    /* EP number stall is not allow to be clear in MSC class "Error Recovery Test".
                       a flag: g_USBD_u32EpStallLock is added to support it */
                    epNum = (uint8_t)(g_USBD_au8SetupPacket[4] & 0xFUL);
                    for(i = 0UL; i < USBD_MAX_EP; i++)
                    {
                        if(((pUSBD->EP[i].CFG & 0xFUL) == epNum) && ((g_USBD_u32EpStallLock & (1UL << i)) == 0UL))
                        {
                            pUSBD->EP[i].CFGP &= ~USBD_CFGP_SSTALL_Msk;
                            pUSBD->EP[i].CFG &= ~USBD_CFG_DSQSYNC_Msk;
                        }
                    }
                }
                else if(g_USBD_au8SetupPacket[2] == FEATURE_DEVICE_REMOTE_WAKEUP)
                {
                    g_USBD_u8RemoteWakeupEn = (uint8_t)0UL;
                }

                /* Status stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 0UL);
                break;
            }
            case SET_ADDRESS:
            {
                s_USBD_u32UsbAddr = g_USBD_au8SetupPacket[2];

                /* DATA IN for end of setup */
                /* Status Stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 0UL);
                break;
            }
            case SET_CONFIGURATION:
            {
                s_USBD_u32UsbConfig = g_USBD_au8SetupPacket[2];

                if(g_USBD_pfnSetConfigCallback)
                {
                    g_USBD_pfnSetConfigCallback();
                }

                /* DATA IN for end of setup */
                /* Status stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 0UL);
                break;
            }
            case SET_FEATURE:
            {
                if((g_USBD_au8SetupPacket[0] & 0xFUL) == 0UL)   /* 0: device */
                {
                    if((g_USBD_au8SetupPacket[2] == 3UL) && (g_USBD_au8SetupPacket[3] == 0UL)) /* 3: HNP enable */
                    {
                        pOTG->CTL |= (OTG_CTL_HNPREQEN_Msk | OTG_CTL_BUSREQ_Msk);
                    }
                }
                if(g_USBD_au8SetupPacket[2] == FEATURE_ENDPOINT_HALT)
                {
                    USBD_SetStall((uint8_t)(g_USBD_au8SetupPacket[4] & 0xFUL));
                }
                else if(g_USBD_au8SetupPacket[2] == FEATURE_DEVICE_REMOTE_WAKEUP)
                {
                    g_USBD_u8RemoteWakeupEn = (uint8_t)1UL;
                }

                /* Status stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 0UL);
                break;
            }
            case SET_INTERFACE:
            {
                s_USBD_u32UsbAltInterface = g_USBD_au8SetupPacket[2];
                if(g_USBD_pfnSetInterface != NULL)
                {
                    g_USBD_pfnSetInterface(s_USBD_u32UsbAltInterface);
                }

                /* Status stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 0UL);
                break;
            }
            default:
            {
                /* Setup error, stall the device */
                USBD_SET_EP_STALL(EP0);
                USBD_SET_EP_STALL(EP1);
                break;
            }
        }
    }
}

/**
  * @brief      Prepare the first Control IN pipe
  *
  * @param[in]  pu8Buf  The pointer of data sent to USB host.
  * @param[in]  u32Size The IN transfer size.
  *
  * @return     None
  *
  * @details    Prepare data for Control IN transfer.
  *
  */
void USBD_PrepareCtrlIn(uint8_t pu8Buf[], uint32_t u32Size)
{
    uint32_t u32Addr;

    if(u32Size > s_USBD_u32CtrlMaxPktSize)
    {
        /* Data size > MXPLD */
        s_USBD_pu8CtrlInPointer = pu8Buf + s_USBD_u32CtrlMaxPktSize;
        s_USBD_u32CtrlInSize = u32Size - s_USBD_u32CtrlMaxPktSize;
        USBD_SET_DATA1(EP0);
        u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
        USBD_MemCopy((uint8_t *)u32Addr, pu8Buf, s_USBD_u32CtrlMaxPktSize);
        USBD_SET_PAYLOAD_LEN(EP0, s_USBD_u32CtrlMaxPktSize);
    }
    else
    {
        /* Data size <= MXPLD */
        s_USBD_pu8CtrlInPointer = 0;
        s_USBD_u32CtrlInSize = 0UL;
        USBD_SET_DATA1(EP0);
        u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
        USBD_MemCopy((uint8_t *)u32Addr, pu8Buf, u32Size);
        USBD_SET_PAYLOAD_LEN(EP0, u32Size);
    }
}

/**
  * @brief    Repeat Control IN pipe
  *
  * @param    None
  *
  * @return   None
  *
  * @details  This function processes the remained data of Control IN transfer.
  *
  */
void USBD_CtrlIn(void)
{
    uint32_t u32Addr;

    if(s_USBD_u32CtrlInSize)
    {
        /* Process remained data */
        if(s_USBD_u32CtrlInSize > s_USBD_u32CtrlMaxPktSize)
        {
            /* Data size > MXPLD */
            u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
            USBD_MemCopy((uint8_t *)u32Addr, (uint8_t *)s_USBD_pu8CtrlInPointer, s_USBD_u32CtrlMaxPktSize);
            USBD_SET_PAYLOAD_LEN(EP0, s_USBD_u32CtrlMaxPktSize);
            s_USBD_pu8CtrlInPointer += s_USBD_u32CtrlMaxPktSize;
            s_USBD_u32CtrlInSize -= s_USBD_u32CtrlMaxPktSize;
        }
        else
        {
            /* Data size <= MXPLD */
            u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
            USBD_MemCopy((uint8_t *)u32Addr, (uint8_t *)s_USBD_pu8CtrlInPointer, s_USBD_u32CtrlInSize);
            USBD_SET_PAYLOAD_LEN(EP0, s_USBD_u32CtrlInSize);
            s_USBD_pu8CtrlInPointer = 0;
            s_USBD_u32CtrlInSize = 0UL;
        }
    }
    else /* No more data for IN token */
    {
        /* In ACK for Set address */
        if((g_USBD_au8SetupPacket[0] == REQ_STANDARD) && (g_USBD_au8SetupPacket[1] == SET_ADDRESS))
        {
            u32Addr = USBD_GET_ADDR();
            if((u32Addr != s_USBD_u32UsbAddr) && (u32Addr == 0UL))
            {
                USBD_SET_ADDR(s_USBD_u32UsbAddr);
            }
        }

        /* For the case of data size is integral times maximum packet size */
        if(s_USBD_u8CtrlInZeroFlag)
        {
            USBD_SET_PAYLOAD_LEN(EP0, 0UL);
            s_USBD_u8CtrlInZeroFlag = (uint8_t)0UL;
        }
    }
}

/**
  * @brief      Prepare the first Control OUT pipe
  *
  * @param[in]  pu8Buf  The pointer of data received from USB host.
  * @param[in]  u32Size The OUT transfer size.
  *
  * @return     None
  *
  * @details    This function is used to prepare the first Control OUT transfer.
  *
  */
void USBD_PrepareCtrlOut(uint8_t *pu8Buf, uint32_t u32Size)
{
    s_USBD_pu8CtrlOutPointer = pu8Buf;
    s_USBD_u32CtrlOutSize = 0UL;
    s_USBD_u32CtrlOutSizeLimit = u32Size;
    USBD_SET_PAYLOAD_LEN(EP1, s_USBD_u32CtrlMaxPktSize);
}

/**
  * @brief    Repeat Control OUT pipe
  *
  * @param    None
  *
  * @return   None
  *
  * @details  This function processes the successive Control OUT transfer.
  *
  */
void USBD_CtrlOut(void)
{
    uint32_t u32Size;
    uint32_t u32Addr;

    if(s_USBD_u32CtrlOutSize < s_USBD_u32CtrlOutSizeLimit)
    {
        u32Size = USBD_GET_PAYLOAD_LEN(EP1);
        u32Addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP1);
        USBD_MemCopy((uint8_t *)s_USBD_pu8CtrlOutPointer, (uint8_t *)u32Addr, u32Size);
        s_USBD_pu8CtrlOutPointer += u32Size;
        s_USBD_u32CtrlOutSize += u32Size;

        if(s_USBD_u32CtrlOutSize < s_USBD_u32CtrlOutSizeLimit)
        {
            USBD_SET_PAYLOAD_LEN(EP1, s_USBD_u32CtrlMaxPktSize);
        }
    }
}

/**
  * @brief    Reset software flags
  *
  * @param    None
  *
  * @return   None
  *
  * @details  This function resets all variables for protocol and resets USB device address to 0.
  *
  */
void USBD_SwReset(void)
{
    uint32_t i, u32CFG;
    USBD_T *pUSBD;

    if((__PC() & NS_OFFSET) == NS_OFFSET)
    {
        pUSBD = USBD_NS;
    }
    else
    {
        pUSBD = USBD;
    }

    /* Reset all variables for protocol */
    s_USBD_pu8CtrlInPointer = 0;
    s_USBD_u32CtrlInSize = 0UL;
    s_USBD_pu8CtrlOutPointer = 0;
    s_USBD_u32CtrlOutSize = 0UL;
    s_USBD_u32CtrlOutSizeLimit = 0UL;
    g_USBD_u32EpStallLock = 0UL;
    memset(g_USBD_au8SetupPacket, 0, 8UL);

    for(i = 0UL; i < USBD_MAX_EP; i++)
    {
        if(!USBD_IS_DB_MODE(i))
        {
            /* Reset PID DATA0 */
            pUSBD->EP[i].CFG &= ~USBD_CFG_DSQSYNC_Msk;
        }
        else
        {
            /* Reset double buffer setting */
            u32CFG = pUSBD->EP[i].CFG;
            pUSBD->EP[i].CFG = u32CFG;
        }
    }

    /* Reset USB device address */
    USBD_SET_ADDR(0UL);
}

/**
 * @brief       USBD Set Vendor Request
 *
 * @param[in]   pfnVendorReq    Vendor Request Callback Function
 *
 * @return      None
 *
 * @details     This function is used to set USBD vendor request callback function
 */
void USBD_SetVendorRequest(VENDOR_REQ pfnVendorReq)
{
    g_USBD_pfnVendorRequest = pfnVendorReq;
}

/**
 * @brief       The callback function which called when get SET CONFIGURATION request
 *
 * @param[in]   pfnSetConfigCallback    Callback function pointer for SET CONFIGURATION request
 *
 * @return      None
 *
 * @details     This function is used to set the callback function which will be called at SET CONFIGURATION request.
 */
void USBD_SetConfigCallback(SET_CONFIG_CB pfnSetConfigCallback)
{
    g_USBD_pfnSetConfigCallback = pfnSetConfigCallback;
}


/**
 * @brief       EP stall lock function to avoid stall clear by USB SET FEATURE request.
 *
 * @param[in]   u32EpBitmap    Use bitmap to select which endpoints will be locked
 *
 * @return      None
 *
 * @details     This function is used to lock relative endpoint to avoid stall clear by SET FEATURE request.
 *              If ep stall locked, user needs to reset USB device or re-configure device to clear it.
 */
void USBD_LockEpStall(uint32_t u32EpBitmap)
{
    g_USBD_u32EpStallLock = u32EpBitmap;
}

/**@}*/ /* end of group USBD_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group USBD_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif
