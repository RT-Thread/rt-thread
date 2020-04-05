/**************************************************************************//**
 * @file     usbd.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 15/07/17 1:39p $
 * @brief    USBD driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NUC100Series.h"

#if 0
#define DBG_PRINTF      printf
#else
#define DBG_PRINTF(...)
#endif
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
uint8_t g_usbd_SetupPacket[8] = {0};
volatile uint8_t g_usbd_RemoteWakeupEn = 0; /*!< Remote wake up function enable flag */

/**
 * @cond HIDDEN_SYMBOLS
 */
static volatile uint8_t *g_usbd_CtrlInPointer = 0;
static volatile uint32_t g_usbd_CtrlInSize = 0;
static volatile uint8_t *g_usbd_CtrlOutPointer = 0;
static volatile uint32_t g_usbd_CtrlOutSize = 0;
static volatile uint32_t g_usbd_CtrlOutSizeLimit = 0;
static volatile uint32_t g_usbd_UsbAddr = 0;
static volatile uint32_t g_usbd_UsbConfig = 0;
static volatile uint32_t g_usbd_CtrlMaxPktSize = 8;
static volatile uint32_t g_usbd_UsbAltInterface = 0;
static volatile uint32_t g_usbd_CtrlOutToggle = 0;
static volatile uint8_t  g_usbd_CtrlInZeroFlag = 0;
/**
 * @endcond
 */

const S_USBD_INFO_T *g_usbd_sInfo;                  /*!< A pointer for USB information structure */

VENDOR_REQ g_usbd_pfnVendorRequest = NULL;          /*!< USB Vendor Request Functional Pointer */
CLASS_REQ g_usbd_pfnClassRequest = NULL;            /*!< USB Class Request callback function pointer */
SET_INTERFACE_REQ g_usbd_pfnSetInterface = NULL;    /*!< USB Set Interface callback function pointer */
SET_CONFIG_CB g_usbd_pfnSetConfigCallback = NULL;   /*!< USB Set configuration callback function pointer */
uint32_t g_u32EpStallLock                = 0;       /*!< Bit map flag to lock specified EP when SET_FEATURE */

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
    g_usbd_sInfo = param;
    g_usbd_pfnClassRequest = pfnClassReq;
    g_usbd_pfnSetInterface = pfnSetInterface;

    /* get EP0 maximum packet size */
    g_usbd_CtrlMaxPktSize = g_usbd_sInfo->gu8DevDesc[7];

    /* Initial USB engine */
    USBD->ATTR = 0x7D0;
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
    CLK_SysTickDelay(100000);
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
  * @param[in]  buf A buffer used to store 8-byte SETUP packet.
  *
  * @return     None
  *
  * @details    Store SETUP packet to a user-specified buffer.
  *
  */
void USBD_GetSetupPacket(uint8_t *buf)
{
    USBD_MemCopy(buf, g_usbd_SetupPacket, 8);
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
    g_usbd_CtrlOutToggle = 0;
    /* Get SETUP packet from USB buffer */
    USBD_MemCopy(g_usbd_SetupPacket, (uint8_t *)USBD_BUF_BASE, 8);
    /* Check the request type */
    switch(g_usbd_SetupPacket[0] & 0x60)
    {
    case REQ_STANDARD:   // Standard
    {
        USBD_StandardRequest();
        break;
    }
    case REQ_CLASS:   // Class
    {
        if(g_usbd_pfnClassRequest != NULL)
        {
            g_usbd_pfnClassRequest();
        }
        break;
    }
    case REQ_VENDOR:   // Vendor
    {
        if(g_usbd_pfnVendorRequest != NULL)
        {
            g_usbd_pfnVendorRequest();
        }
        break;
    }
    default:   // reserved
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

    g_usbd_CtrlInZeroFlag = (uint8_t)0;
    u32Len = 0;
    u32Len = g_usbd_SetupPacket[7];
    u32Len <<= 8;
    u32Len += g_usbd_SetupPacket[6];

    switch(g_usbd_SetupPacket[3])
    {
    // Get Device Descriptor
    case DESC_DEVICE:
    {
        u32Len = Minimum(u32Len, LEN_DEVICE);
        DBG_PRINTF("Get device desc, %d\n", u32Len);
        USBD_PrepareCtrlIn((uint8_t *)g_usbd_sInfo->gu8DevDesc, u32Len);
        USBD_PrepareCtrlOut(0, 0);
        break;
    }
    // Get Configuration Descriptor
    case DESC_CONFIG:
    {
        uint32_t u32TotalLen;

        u32TotalLen = g_usbd_sInfo->gu8ConfigDesc[3];
        u32TotalLen = g_usbd_sInfo->gu8ConfigDesc[2] + (u32TotalLen << 8);

        if(u32Len > u32TotalLen)
        {
            u32Len = u32TotalLen;
            if((u32Len % g_usbd_CtrlMaxPktSize) == 0)
            {
                g_usbd_CtrlInZeroFlag = (uint8_t)1;
            }
        }
        USBD_PrepareCtrlIn((uint8_t *)g_usbd_sInfo->gu8ConfigDesc, u32Len);
        USBD_PrepareCtrlOut(0, 0);
        break;
    }
    // Get HID Descriptor
    case DESC_HID:
    {
        u32Len = Minimum(u32Len, LEN_HID);
        USBD_PrepareCtrlIn((uint8_t *)&g_usbd_sInfo->gu8ConfigDesc[LEN_CONFIG + LEN_INTERFACE], u32Len);
        USBD_PrepareCtrlOut(0, 0);
        break;
    }
    // Get Report Descriptor
    case DESC_HID_RPT:
    {
        uint32_t u32TotalLen;
        uint32_t u32RptDescLen;

        /* Get configuration descriptor size */
        u32TotalLen = g_usbd_sInfo->gu8ConfigDesc[3];
        u32TotalLen = g_usbd_sInfo->gu8ConfigDesc[2] + (u32TotalLen << 8);

        /* Calculate the offset of HID report descriptor size to get report descriptor size.
           User may need to modify this if configuration descriptor changed. */
        u32RptDescLen = g_usbd_sInfo->gu8ConfigDesc[u32TotalLen - LEN_ENDPOINT - 1];
        u32RptDescLen = g_usbd_sInfo->gu8ConfigDesc[u32TotalLen - LEN_ENDPOINT - 2] + (u32RptDescLen << 8);

        if(u32Len > u32RptDescLen)
        {
            u32Len = u32RptDescLen;
            if((u32Len % g_usbd_CtrlMaxPktSize) == 0)
            {
                g_usbd_CtrlInZeroFlag = (uint8_t)1;
            }
        }
        USBD_PrepareCtrlIn((uint8_t *)g_usbd_sInfo->gu8HidReportDesc, u32Len);
        USBD_PrepareCtrlOut(0, 0);
        break;
    }
    // Get String Descriptor
    case DESC_STRING:
    {
        // Get String Descriptor
        if(g_usbd_SetupPacket[2] < 4)
        {
            if(u32Len > g_usbd_sInfo->gu8StringDesc[g_usbd_SetupPacket[2]][0])
            {
                u32Len = g_usbd_sInfo->gu8StringDesc[g_usbd_SetupPacket[2]][0];
                if((u32Len % g_usbd_CtrlMaxPktSize) == 0)
                {
                    g_usbd_CtrlInZeroFlag = (uint8_t)1;
                }
            }
            USBD_PrepareCtrlIn((uint8_t *)g_usbd_sInfo->gu8StringDesc[g_usbd_SetupPacket[2]], u32Len);
            USBD_PrepareCtrlOut(0, 0);
            break;
        }
        else
        {
            // Not support. Reply STALL.
            USBD_SET_EP_STALL(EP0);
            USBD_SET_EP_STALL(EP1);
            DBG_PRINTF("Unsupported string desc (%d). Stall ctrl pipe.\n", g_usbd_SetupPacket[2]);
            break;
        }
    }
    default:
        // Not support. Reply STALL.
        USBD_SET_EP_STALL(EP0);
        USBD_SET_EP_STALL(EP1);
        DBG_PRINTF("Unsupported get desc type. stall ctrl pipe\n");
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
    /* clear global variables for new request */
    g_usbd_CtrlInPointer = 0;
    g_usbd_CtrlInSize = 0;

    if(g_usbd_SetupPacket[0] & 0x80)    /* request data transfer direction */
    {
        // Device to host
        switch(g_usbd_SetupPacket[1])
        {
        case GET_CONFIGURATION:
        {
            // Return current configuration setting
            /* Data stage */
            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_UsbConfig;
            USBD_SET_DATA1(EP1);
            USBD_SET_PAYLOAD_LEN(EP1, 0);
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 1);
            /* Status stage */
            USBD_PrepareCtrlOut(0, 0);
            DBG_PRINTF("Get configuration\n");
            break;
        }
        case GET_DESCRIPTOR:
        {
            USBD_GetDescriptor();
            break;
        }
        case GET_INTERFACE:
        {
            // Return current interface setting
            /* Data stage */
            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_UsbAltInterface;
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 1);
            /* Status stage */
            USBD_PrepareCtrlOut(0, 0);
            DBG_PRINTF("Get interface\n");
            break;
        }
        case GET_STATUS:
        {
            // Device
            if(g_usbd_SetupPacket[0] == 0x80)
            {
                uint8_t u8Tmp;

                u8Tmp = 0;
                if(g_usbd_sInfo->gu8ConfigDesc[7] & 0x40) u8Tmp |= 1; // Self-Powered/Bus-Powered.
                if(g_usbd_sInfo->gu8ConfigDesc[7] & 0x20) u8Tmp |= (g_usbd_RemoteWakeupEn << 1); // Remote wake up

                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = u8Tmp;
            }
            // Interface
            else if(g_usbd_SetupPacket[0] == 0x81)
                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = 0;
            // Endpoint
            else if(g_usbd_SetupPacket[0] == 0x82)
            {
                uint8_t ep = g_usbd_SetupPacket[4] & 0xF;
                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = USBD_GetStall(ep) ? 1 : 0;
            }

            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = 0;
            /* Data stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 2);
            /* Status stage */
            USBD_PrepareCtrlOut(0, 0);
            DBG_PRINTF("Get status\n");
            break;
        }
        default:
        {
            /* Setup error, stall the device */
            USBD_SET_EP_STALL(EP0);
            USBD_SET_EP_STALL(EP1);
            DBG_PRINTF("Unknown request. stall ctrl pipe.\n");
            break;
        }
        }
    }
    else
    {
        // Host to device
        switch(g_usbd_SetupPacket[1])
        {
        case CLEAR_FEATURE:
        {
            if(g_usbd_SetupPacket[2] == FEATURE_ENDPOINT_HALT)
            {
                int32_t epNum, i;

                /* EP number stall is not allow to be clear in MSC class "Error Recovery Test".
                   a flag: g_u32EpStallLock is added to support it */
                epNum = g_usbd_SetupPacket[4] & 0xF;
                for(i = 0; i < USBD_MAX_EP; i++)
                {
                    if(((USBD->EP[i].CFG & 0xF) == epNum) && ((g_u32EpStallLock & (1 << i)) == 0))
                    {
                        USBD->EP[i].CFGP &= ~USBD_CFGP_SSTALL_Msk;
                        USBD->EP[i].CFG &= ~USBD_CFG_DSQ_SYNC_Msk;
                        DBG_PRINTF("Clr stall ep%d %x\n", i, USBD->EP[i].CFGP);
                    }
                }
            }
            else if(g_usbd_SetupPacket[2] == FEATURE_DEVICE_REMOTE_WAKEUP)
                g_usbd_RemoteWakeupEn = 0;
            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);
            DBG_PRINTF("Clear feature op %d\n", g_usbd_SetupPacket[2]);
            break;
        }
        case SET_ADDRESS:
        {
            g_usbd_UsbAddr = g_usbd_SetupPacket[2];
            DBG_PRINTF("Set addr to %d\n", g_usbd_UsbAddr);

            // DATA IN for end of setup
            /* Status Stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);
            break;
        }
        case SET_CONFIGURATION:
        {
            g_usbd_UsbConfig = g_usbd_SetupPacket[2];

            if(g_usbd_pfnSetConfigCallback)
                g_usbd_pfnSetConfigCallback();
            // DATA IN for end of setup
            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);
            DBG_PRINTF("Set config to %d\n", g_usbd_UsbConfig);
            break;
        }
        case SET_FEATURE:
        {
            if(g_usbd_SetupPacket[2] == FEATURE_ENDPOINT_HALT)
            {
                USBD_SetStall(g_usbd_SetupPacket[4] & 0xF);
                DBG_PRINTF("Set feature. stall ep %d\n", g_usbd_SetupPacket[4] & 0xF);
            }
            else if(g_usbd_SetupPacket[2] == FEATURE_DEVICE_REMOTE_WAKEUP)
            {
                g_usbd_RemoteWakeupEn = 1;
                DBG_PRINTF("Set feature. enable remote wakeup\n");
            }
            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);
            break;
        }
        case SET_INTERFACE:
        {
            g_usbd_UsbAltInterface = g_usbd_SetupPacket[2];
            if(g_usbd_pfnSetInterface != NULL)
                g_usbd_pfnSetInterface();
            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);
            DBG_PRINTF("Set interface to %d\n", g_usbd_UsbAltInterface);
            break;
        }
        default:
        {
            /* Setup error, stall the device */
            USBD_SET_EP_STALL(EP0);
            USBD_SET_EP_STALL(EP1);
            DBG_PRINTF("Unsupported request. stall ctrl pipe.\n");
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
void USBD_PrepareCtrlIn(uint8_t *pu8Buf, uint32_t u32Size)
{
    DBG_PRINTF("Prepare Ctrl In %d\n", u32Size);
    if(u32Size > g_usbd_CtrlMaxPktSize)
    {
        // Data size > MXPLD
        g_usbd_CtrlInPointer = pu8Buf + g_usbd_CtrlMaxPktSize;
        g_usbd_CtrlInSize = u32Size - g_usbd_CtrlMaxPktSize;
        USBD_SET_DATA1(EP0);
        USBD_MemCopy((uint8_t *)USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0), pu8Buf, g_usbd_CtrlMaxPktSize);
        USBD_SET_PAYLOAD_LEN(EP0, g_usbd_CtrlMaxPktSize);
    }
    else
    {
        // Data size <= MXPLD
        g_usbd_CtrlInPointer = 0;
        g_usbd_CtrlInSize = 0;
        USBD_SET_DATA1(EP0);
        USBD_MemCopy((uint8_t *)USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0), pu8Buf, u32Size);
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
    DBG_PRINTF("Ctrl In Ack. residue %d\n", g_usbd_CtrlInSize);
    if(g_usbd_CtrlInSize)
    {
        // Process remained data
        if(g_usbd_CtrlInSize > g_usbd_CtrlMaxPktSize)
        {
            // Data size > MXPLD
            USBD_MemCopy((uint8_t *)USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0), (uint8_t *)g_usbd_CtrlInPointer, g_usbd_CtrlMaxPktSize);
            USBD_SET_PAYLOAD_LEN(EP0, g_usbd_CtrlMaxPktSize);
            g_usbd_CtrlInPointer += g_usbd_CtrlMaxPktSize;
            g_usbd_CtrlInSize -= g_usbd_CtrlMaxPktSize;
        }
        else
        {
            // Data size <= MXPLD
            USBD_MemCopy((uint8_t *)USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0), (uint8_t *)g_usbd_CtrlInPointer, g_usbd_CtrlInSize);
            USBD_SET_PAYLOAD_LEN(EP0, g_usbd_CtrlInSize);
            g_usbd_CtrlInPointer = 0;
            g_usbd_CtrlInSize = 0;
        }
    }
    else // No more data for IN token
    {
        // In ACK for Set address
        if((g_usbd_SetupPacket[0] == REQ_STANDARD) && (g_usbd_SetupPacket[1] == SET_ADDRESS))
        {
            if((USBD_GET_ADDR() != g_usbd_UsbAddr) && (USBD_GET_ADDR() == 0))
            {
                USBD_SET_ADDR(g_usbd_UsbAddr);
            }
        }

        /* For the case of data size is integral times maximum packet size */
        if(g_usbd_CtrlInZeroFlag)
        {
            USBD_SET_PAYLOAD_LEN(EP0, 0);
            g_usbd_CtrlInZeroFlag = 0;
        }

        DBG_PRINTF("Ctrl In done.\n");
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
    g_usbd_CtrlOutPointer = pu8Buf;
    g_usbd_CtrlOutSize = 0;
    g_usbd_CtrlOutSizeLimit = u32Size;
    USBD_SET_PAYLOAD_LEN(EP1, g_usbd_CtrlMaxPktSize);
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

    DBG_PRINTF("Ctrl Out Ack %d\n", g_usbd_CtrlOutSize);

    if(g_usbd_CtrlOutToggle != (USBD->EPSTS & USBD_EPSTS_EPSTS1_Msk))
    {
        g_usbd_CtrlOutToggle = USBD->EPSTS & USBD_EPSTS_EPSTS1_Msk;
        if(g_usbd_CtrlOutSize < g_usbd_CtrlOutSizeLimit)
        {
            u32Size = USBD_GET_PAYLOAD_LEN(EP1);
            USBD_MemCopy((uint8_t *)g_usbd_CtrlOutPointer, (uint8_t *)USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP1), u32Size);
            g_usbd_CtrlOutPointer += u32Size;
            g_usbd_CtrlOutSize += u32Size;

            if(g_usbd_CtrlOutSize < g_usbd_CtrlOutSizeLimit)
                USBD_SET_PAYLOAD_LEN(EP1, g_usbd_CtrlMaxPktSize);
        }
    }
    else
    {
        USBD_SET_PAYLOAD_LEN(EP1, g_usbd_CtrlMaxPktSize);
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
    // Reset all variables for protocol
    g_usbd_CtrlInPointer = 0;
    g_usbd_CtrlInSize = 0;
    g_usbd_CtrlOutPointer = 0;
    g_usbd_CtrlOutSize = 0;
    g_usbd_CtrlOutSizeLimit = 0;
    g_u32EpStallLock = 0;
    memset(g_usbd_SetupPacket, 0, 8);

    // Reset USB device address
    USBD_SET_ADDR(0);
}

void USBD_SetVendorRequest(VENDOR_REQ pfnVendorReq)
{
    g_usbd_pfnVendorRequest = pfnVendorReq;
}

void USBD_SetConfigCallback(SET_CONFIG_CB pfnSetConfigCallback)
{
    g_usbd_pfnSetConfigCallback = pfnSetConfigCallback;
}


void USBD_LockEpStall(uint32_t u32EpBitmap)
{
    g_u32EpStallLock = u32EpBitmap;
}
/*@}*/ /* end of group USBD_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USBD_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/





