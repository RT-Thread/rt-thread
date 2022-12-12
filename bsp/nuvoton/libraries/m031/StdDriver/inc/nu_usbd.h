
/**************************************************************************//**
 * @file     usbd.H
 * @version  V1.00
 * $Revision: 9 $
 * $Date: 18/07/13 3:05p $
 * @brief    M031 series USB driver header file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_USBD_H__
#define __NU_USBD_H__

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

/** @addtogroup USBD_EXPORTED_STRUCT USBD Exported Struct
  @{
*/
typedef struct s_usbd_info
{
    uint8_t *gu8DevDesc;            /*!< Pointer for USB Device Descriptor          */
    uint8_t *gu8ConfigDesc;         /*!< Pointer for USB Configuration Descriptor   */
    uint8_t **gu8StringDesc;        /*!< Pointer for USB String Descriptor pointers */
    uint8_t **gu8HidReportDesc;     /*!< Pointer for USB HID Report Descriptor      */
    uint8_t *gu8BosDesc;            /*!< Pointer for USB BOS Descriptor             */
    uint32_t *gu32HidReportSize;    /*!< Pointer for HID Report descriptor Size */
    uint32_t *gu32ConfigHidDescIdx; /*!< Pointer for HID Descriptor start index */

} S_USBD_INFO_T;  /*!< Device description structure */

extern const S_USBD_INFO_T gsInfo;

/*@}*/ /* end of group USBD_EXPORTED_STRUCTS */




/** @addtogroup USBD_EXPORTED_CONSTANTS USBD Exported Constants
  @{
*/
#define USBD_BUF_BASE   (USBD_BASE+0x100ul)  /*!< USBD buffer base address \hideinitializer */
#define USBD_MAX_EP     8ul /*!< Total EP number \hideinitializer */

#define EP0     0ul       /*!< Endpoint 0 \hideinitializer */
#define EP1     1ul       /*!< Endpoint 1 \hideinitializer */
#define EP2     2ul       /*!< Endpoint 2 \hideinitializer */
#define EP3     3ul       /*!< Endpoint 3 \hideinitializer */
#define EP4     4ul       /*!< Endpoint 4 \hideinitializer */
#define EP5     5ul       /*!< Endpoint 5 \hideinitializer */
#define EP6     6ul       /*!< Endpoint 6 \hideinitializer */
#define EP7     7ul       /*!< Endpoint 7 \hideinitializer */

/** @cond HIDDEN_SYMBOLS */
/* USB Request Type */
#define REQ_STANDARD        0x00ul
#define REQ_CLASS           0x20ul
#define REQ_VENDOR          0x40ul

/* USB Standard Request */
#define GET_STATUS          0x00ul
#define CLEAR_FEATURE       0x01ul
#define SET_FEATURE         0x03ul
#define SET_ADDRESS         0x05ul
#define GET_DESCRIPTOR      0x06ul
#define SET_DESCRIPTOR      0x07ul
#define GET_CONFIGURATION   0x08ul
#define SET_CONFIGURATION   0x09ul
#define GET_INTERFACE       0x0Aul
#define SET_INTERFACE       0x0Bul
#define SYNC_FRAME          0x0Cul

/* USB Descriptor Type */
#define DESC_DEVICE         0x01ul
#define DESC_CONFIG         0x02ul
#define DESC_STRING         0x03ul
#define DESC_INTERFACE      0x04ul
#define DESC_ENDPOINT       0x05ul
#define DESC_QUALIFIER      0x06ul
#define DESC_OTHERSPEED     0x07ul
#define DESC_IFPOWER        0x08ul
#define DESC_OTG            0x09ul
#define DESC_BOS            0x0Ful
#define DESC_CAPABILITY     0x10ul

/* USB Device Capability Type */
#define CAP_WIRELESS        0x01ul
#define CAP_USB20_EXT       0x02ul

/* USB HID Descriptor Type */
#define DESC_HID            0x21ul
#define DESC_HID_RPT        0x22ul

/* USB Descriptor Length */
#define LEN_DEVICE          18ul
#define LEN_QUALIFIER       10ul
#define LEN_CONFIG          9ul
#define LEN_INTERFACE       9ul
#define LEN_ENDPOINT        7ul
#define LEN_OTG             5ul
#define LEN_BOS             5ul
#define LEN_HID             9ul
#define LEN_CCID            0x36ul
#define LEN_BOSCAP          7ul

/*!<USB Endpoint Type */
#define EP_ISO              0x01
#define EP_BULK             0x02
#define EP_INT              0x03

#define EP_INPUT            0x80
#define EP_OUTPUT           0x00

/* USB Feature Selector */
#define FEATURE_DEVICE_REMOTE_WAKEUP    0x01ul
#define FEATURE_ENDPOINT_HALT           0x00ul
/** @endcond HIDDEN_SYMBOLS */

/******************************************************************************/
/*                USB Specific Macros                                         */
/******************************************************************************/

#define USBD_WAKEUP_EN          USBD_INTEN_WKEN_Msk         /*!< USB Wake-up Enable                      \hideinitializer */
#define USBD_DRVSE0             USBD_SE0_SE0_Msk            /*!< Drive SE0                               \hideinitializer */
#define USBD_L1RESUME           USBD_ATTR_L1RESUME_Msk      /*!< LPM L1 Resume                           \hideinitializer */
#define USBD_L1SUSPEND          USBD_ATTR_L1SUSPEND_Msk     /*!< LPM L1 Suspend                          \hideinitializer */
#define USBD_LPMACK             USBD_ATTR_LPMACK_Msk        /*!< LPM Enable                              \hideinitializer */
#define USBD_BYTEM              USBD_ATTR_BYTEM_Msk         /*!< CPU Access USB SRAM Size Mode Selection \hideinitializer */
#define USBD_DPPU_EN            USBD_ATTR_DPPUEN_Msk        /*!< USB D+ Pull-up Enable                   \hideinitializer */
#define USBD_USB_EN             USBD_ATTR_USBEN_Msk         /*!< USB Enable                              \hideinitializer */
#define USBD_RWAKEUP            USBD_ATTR_RWAKEUP_Msk       /*!< Remote Wake-up                          \hideinitializer */
#define USBD_PHY_EN             USBD_ATTR_PHYEN_Msk         /*!< PHY Enable                              \hideinitializer */

#define USBD_INT_BUS            USBD_INTEN_BUSIEN_Msk       /*!< USB Bus Event Interrupt                 \hideinitializer */
#define USBD_INT_USB            USBD_INTEN_USBIEN_Msk       /*!< USB Event Interrupt                     \hideinitializer */
#define USBD_INT_FLDET          USBD_INTEN_VBDETIEN_Msk     /*!< USB VBUS Detection Interrupt            \hideinitializer */
#define USBD_INT_VBDET          USBD_INTEN_VBDETIEN_Msk     /*!< USB VBUS Detection Interrupt            \hideinitializer */
#define USBD_INT_WAKEUP         (USBD_INTEN_NEVWKIEN_Msk | USBD_INTEN_WKEN_Msk)     /*!< USB No-Event-Wake-Up Interrupt   \hideinitializer */

#define USBD_INTSTS_SOF         USBD_INTSTS_SOFIF_Msk       /*!< USB Start of Frame Interrupt Status     \hideinitializer */
#define USBD_INTSTS_WAKEUP      USBD_INTSTS_NEVWKIF_Msk     /*!< USB No-Event-Wake-Up Interrupt Status   \hideinitializer */
#define USBD_INTSTS_FLDET       USBD_INTSTS_VBDETIF_Msk     /*!< USB Float Detect Interrupt Status       \hideinitializer */
#define USBD_INTSTS_VBDET       USBD_INTSTS_VBDETIF_Msk     /*!< USB Float Detect Interrupt Status       \hideinitializer */
#define USBD_INTSTS_BUS         USBD_INTSTS_BUSIF_Msk       /*!< USB Bus Event Interrupt Status          \hideinitializer */
#define USBD_INTSTS_USB         USBD_INTSTS_USBIF_Msk       /*!< USB Event Interrupt Status              \hideinitializer */
#define USBD_INTSTS_SETUP       USBD_INTSTS_SETUP_Msk       /*!< USB Setup Event                         \hideinitializer */
#define USBD_INTSTS_EP0         USBD_INTSTS_EPEVT0_Msk      /*!< USB Endpoint 0 Event                    \hideinitializer */
#define USBD_INTSTS_EP1         USBD_INTSTS_EPEVT1_Msk      /*!< USB Endpoint 1 Event                    \hideinitializer */
#define USBD_INTSTS_EP2         USBD_INTSTS_EPEVT2_Msk      /*!< USB Endpoint 2 Event                    \hideinitializer */
#define USBD_INTSTS_EP3         USBD_INTSTS_EPEVT3_Msk      /*!< USB Endpoint 3 Event                    \hideinitializer */
#define USBD_INTSTS_EP4         USBD_INTSTS_EPEVT4_Msk      /*!< USB Endpoint 4 Event                    \hideinitializer */
#define USBD_INTSTS_EP5         USBD_INTSTS_EPEVT5_Msk      /*!< USB Endpoint 5 Event                    \hideinitializer */
#define USBD_INTSTS_EP6         USBD_INTSTS_EPEVT6_Msk      /*!< USB Endpoint 6 Event                    \hideinitializer */
#define USBD_INTSTS_EP7         USBD_INTSTS_EPEVT7_Msk      /*!< USB Endpoint 7 Event                    \hideinitializer */

#define USBD_STATE_USBRST       USBD_ATTR_USBRST_Msk        /*!< USB Bus Reset                           \hideinitializer */
#define USBD_STATE_SUSPEND      USBD_ATTR_SUSPEND_Msk       /*!< USB Bus Suspend                         \hideinitializer */
#define USBD_STATE_RESUME       USBD_ATTR_RESUME_Msk        /*!< USB Bus Resume                          \hideinitializer */
#define USBD_STATE_TIMEOUT      USBD_ATTR_TOUT_Msk          /*!< USB Bus Timeout                         \hideinitializer */
#define USBD_STATE_L1RESUME     USBD_ATTR_L1RESUME_Msk      /*!< USB Bus L1RESUME                        \hideinitializer */
#define USBD_STATE_L1SUSPEND    USBD_ATTR_L1SUSPEND_Msk     /*!< USB BUS L1SUSPEND                       \hideinitializer */

#define USBD_CFGP_SSTALL        USBD_CFGP_SSTALL_Msk        /*!< Set Stall                               \hideinitializer */
#define USBD_CFGP_CLRRDY        USBD_CFGP_CLRRDY_Msk

#define USBD_CFG_CSTALL         USBD_CFG_CSTALL_Msk         /*!< Clear Stall                             \hideinitializer */
#define USBD_CFG_EPMODE_DISABLE (0ul << USBD_CFG_STATE_Pos) /*!< Endpoint Disable                        \hideinitializer */
#define USBD_CFG_EPMODE_OUT     (1ul << USBD_CFG_STATE_Pos) /*!< Out Endpoint                            \hideinitializer */
#define USBD_CFG_EPMODE_IN      (2ul << USBD_CFG_STATE_Pos) /*!< In Endpoint                             \hideinitializer */
#define USBD_CFG_TYPE_ISO       (1ul << USBD_CFG_ISOCH_Pos) /*!< Isochronous                             \hideinitializer */



/*@}*/ /* end of group USBD_EXPORTED_CONSTANTS */


/** @addtogroup USBD_EXPORTED_FUNCTIONS USBD Exported Functions
  @{
*/

/**
  * @brief      Compare two input numbers and return maximum one.
  *
  * @param[in]  a   First number to be compared.
  * @param[in]  b   Second number to be compared.
  *
  * @return     Maximum value between a and b.
  *
  * @details    If a > b, then return a. Otherwise, return b.
  * \hideinitializer
  */
#define USBD_Maximum(a,b)        ((a)>(b) ? (a) : (b))


/**
  * @brief      Compare two input numbers and return minimum one
  *
  * @param[in]  a   First number to be compared
  * @param[in]  b   Second number to be compared
  *
  * @return     Minimum value between a and b
  *
  * @details    If a < b, then return a. Otherwise, return b.
  * \hideinitializer
  */
#define USBD_Minimum(a,b)        ((a)<(b) ? (a) : (b))


/**
  * @brief    Enable USB
  *
  * @param    None
  *
  * @return   None
  *
  * @details  To set USB ATTR control register to enable USB and PHY.
  * \hideinitializer
  */
#define USBD_ENABLE_USB()           ((uint32_t)(USBD->ATTR |= 0x7D0))

/**
  * @brief    Disable USB
  *
  * @param    None
  *
  * @return   None
  *
  * @details  To set USB ATTR control register to disable USB.
  * \hideinitializer
  */
#define USBD_DISABLE_USB()          ((uint32_t)(USBD->ATTR &= ~USBD_USB_EN))

/**
  * @brief    Enable USB PHY
  *
  * @param    None
  *
  * @return   None
  *
  * @details  To set USB ATTR control register to enable USB PHY.
  * \hideinitializer
  */
#define USBD_ENABLE_PHY()           ((uint32_t)(USBD->ATTR |= USBD_PHY_EN))

/**
  * @brief    Disable USB PHY
  *
  * @param    None
  *
  * @return   None
  *
  * @details  To set USB ATTR control register to disable USB PHY.
  * \hideinitializer
  */
#define USBD_DISABLE_PHY()          ((uint32_t)(USBD->ATTR &= ~USBD_PHY_EN))

/**
  * @brief    Enable SE0. Force USB PHY transceiver to drive SE0.
  *
  * @param    None
  *
  * @return   None
  *
  * @details  Set DRVSE0 bit of USB_DRVSE0 register to enable software-disconnect function. Force USB PHY transceiver to drive SE0 to bus.
  * \hideinitializer
  */
#define USBD_SET_SE0()              ((uint32_t)(USBD->SE0 |= USBD_DRVSE0))

/**
  * @brief    Disable SE0
  *
  * @param    None
  *
  * @return   None
  *
  * @details  Clear DRVSE0 bit of USB_DRVSE0 register to disable software-disconnect function.
  * \hideinitializer
  */
#define USBD_CLR_SE0()              ((uint32_t)(USBD->SE0 &= ~USBD_DRVSE0))

/**
  * @brief       Set USB device address
  *
  * @param[in]   addr The USB device address.
  *
  * @return      None
  *
  * @details     Write USB device address to USB_FADDR register.
  * \hideinitializer
  */
#define USBD_SET_ADDR(addr)         (USBD->FADDR = (addr))

/**
  * @brief    Get USB device address
  *
  * @param    None
  *
  * @return   USB device address
  *
  * @details  Read USB_FADDR register to get USB device address.
  * \hideinitializer
  */
#define USBD_GET_ADDR()             ((uint32_t)(USBD->FADDR))

/**
  * @brief      Enable USB interrupt function
  *
  * @param[in]  intr The combination of the specified interrupt enable bits.
  *             Each bit corresponds to a interrupt enable bit.
  *             This parameter decides which interrupts will be enabled.
  *             (USBD_INT_WAKEUP, USBD_INT_FLDET, USBD_INT_USB, USBD_INT_BUS)
  *
  * @return     None
  *
  * @details    Enable USB related interrupt functions specified by intr parameter.
  * \hideinitializer
  */
#define USBD_ENABLE_INT(intr)       (USBD->INTEN |= (intr))

/**
  * @brief    Get interrupt status
  *
  * @param    None
  *
  * @return   The value of USB_INTSTS register
  *
  * @details  Return all interrupt flags of USB_INTSTS register.
  * \hideinitializer
  */
#define USBD_GET_INT_FLAG()         ((uint32_t)(USBD->INTSTS))

/**
  * @brief      Clear USB interrupt flag
  *
  * @param[in]  flag The combination of the specified interrupt flags.
  *             Each bit corresponds to a interrupt source.
  *             This parameter decides which interrupt flags will be cleared.
  *             (USBD_INTSTS_WAKEUP, USBD_INTSTS_FLDET, USBD_INTSTS_BUS, USBD_INTSTS_USB)
  *
  * @return     None
  *
  * @details    Clear USB related interrupt flags specified by flag parameter.
  * \hideinitializer
  */
#define USBD_CLR_INT_FLAG(flag)     (USBD->INTSTS = (flag))

/**
  * @brief    Get endpoint status
  *
  * @param    None
  *
  * @return   The value of USB_EPSTS register.
  *
  * @details  Return all endpoint status.
  * \hideinitializer
  */
#define USBD_GET_EP_FLAG()          ((uint32_t)(USBD->EPSTS))

/**
  * @brief    Get USB bus state
  *
  * @param    None
  *
  * @return   The value of USB_ATTR[3:0].
  *           Bit 0 indicates USB bus reset status.
  *           Bit 1 indicates USB bus suspend status.
  *           Bit 2 indicates USB bus resume status.
  *           Bit 3 indicates USB bus time-out status.
  *
  * @details  Return USB_ATTR[3:0] for USB bus events.
  * \hideinitializer
  */
#define USBD_GET_BUS_STATE()        ((uint32_t)(USBD->ATTR & 0xf))

/**
  * @brief    Check cable connection state
  *
  * @param    None
  *
  * @retval   0 USB cable is not attached.
  * @retval   1 USB cable is attached.
  *
  * @details  Check the connection state by FLDET bit of USB_FLDET register.
  * \hideinitializer
  */
#define USBD_IS_ATTACHED()          ((uint32_t)(USBD->VBUSDET & USBD_VBUSDET_VBUSDET_Msk))

/**
  * @brief      Stop USB transaction of the specified endpoint ID
  *
  * @param[in]  ep The USB endpoint ID. M451 Series supports 8 hardware endpoint ID. This parameter could be 0 ~ 7.
  *
  * @return     None
  *
  * @details    Write 1 to CLRRDY bit of USB_CFGPx register to stop USB transaction of the specified endpoint ID.
  * \hideinitializer
  */
#define USBD_STOP_TRANSACTION(ep)   (*((__IO uint32_t *) ((uint32_t)&USBD->EP[0].CFGP + (uint32_t)((ep) << 4))) |= USBD_CFGP_CLRRDY_Msk)

/**
  * @brief      Set USB DATA1 PID for the specified endpoint ID
  *
  * @param[in]  ep The USB endpoint ID. M451 Series supports 8 hardware endpoint ID. This parameter could be 0 ~ 7.
  *
  * @return     None
  *
  * @details    Set DSQ_SYNC bit of USB_CFGx register to specify the DATA1 PID for the following IN token transaction.
  *             Base on this setting, hardware will toggle PID between DATA0 and DATA1 automatically for IN token transactions.
  * \hideinitializer
  */
#define USBD_SET_DATA1(ep)          (*((__IO uint32_t *) ((uint32_t)&USBD->EP[0].CFG + (uint32_t)((ep) << 4))) |= USBD_CFG_DSQSYNC_Msk)

/**
  * @brief      Set USB DATA0 PID for the specified endpoint ID
  *
  * @param[in]  ep The USB endpoint ID. M451 Series supports 8 hardware endpoint ID. This parameter could be 0 ~ 7.
  *
  * @return     None
  *
  * @details    Clear DSQ_SYNC bit of USB_CFGx register to specify the DATA0 PID for the following IN token transaction.
  *             Base on this setting, hardware will toggle PID between DATA0 and DATA1 automatically for IN token transactions.
  * \hideinitializer
  */
#define USBD_SET_DATA0(ep)          (*((__IO uint32_t *) ((uint32_t)&USBD->EP[0].CFG + (uint32_t)((ep) << 4))) &= (~USBD_CFG_DSQSYNC_Msk))

/**
  * @brief      Set USB payload size (IN data)
  *
  * @param[in]  ep The USB endpoint ID. M451 Series supports 8 hardware endpoint ID. This parameter could be 0 ~ 7.
  *
  * @param[in]  size The transfer length.
  *
  * @return     None
  *
  * @details    This macro will write the transfer length to USB_MXPLDx register for IN data transaction.
  * \hideinitializer
  */
#define USBD_SET_PAYLOAD_LEN(ep, size)  (*((__IO uint32_t *) ((uint32_t)&USBD->EP[0].MXPLD + (uint32_t)((ep) << 4))) = (size))

/**
  * @brief      Get USB payload size (OUT data)
  *
  * @param[in]  ep The USB endpoint ID. M451 Series supports 8 endpoint ID. This parameter could be 0 ~ 7.
  *
  * @return     The value of USB_MXPLDx register.
  *
  * @details    Get the data length of OUT data transaction by reading USB_MXPLDx register.
  * \hideinitializer
  */
#define USBD_GET_PAYLOAD_LEN(ep)        ((uint32_t)*((__IO uint32_t *) ((uint32_t)&USBD->EP[0].MXPLD + (uint32_t)((ep) << 4))))

/**
  * @brief      Configure endpoint
  *
  * @param[in]  ep The USB endpoint ID. M451 Series supports 8 hardware endpoint ID. This parameter could be 0 ~ 7.
  *
  * @param[in]  config The USB configuration.
  *
  * @return     None
  *
  * @details    This macro will write config parameter to USB_CFGx register of specified endpoint ID.
  * \hideinitializer
  */
#define USBD_CONFIG_EP(ep, config)      (*((__IO uint32_t *) ((uint32_t)&USBD->EP[0].CFG + (uint32_t)((ep) << 4))) = (config))

/**
  * @brief      Set USB endpoint buffer
  *
  * @param[in]  ep The USB endpoint ID. M451 Series supports 8 hardware endpoint ID. This parameter could be 0 ~ 7.
  *
  * @param[in]  offset The SRAM offset.
  *
  * @return     None
  *
  * @details    This macro will set the SRAM offset for the specified endpoint ID.
  * \hideinitializer
  */
#define USBD_SET_EP_BUF_ADDR(ep, offset)    (*((__IO uint32_t *) ((uint32_t)&USBD->EP[0].BUFSEG + (uint32_t)((ep) << 4))) = (offset))

/**
  * @brief      Get the offset of the specified USB endpoint buffer
  *
  * @param[in]  ep The USB endpoint ID. M451 Series supports 8 hardware endpoint ID. This parameter could be 0 ~ 7.
  *
  * @return     The offset of the specified endpoint buffer.
  *
  * @details    This macro will return the SRAM offset of the specified endpoint ID.
  * \hideinitializer
  */
#define USBD_GET_EP_BUF_ADDR(ep)        ((uint32_t)*((__IO uint32_t *) ((uint32_t)&USBD->EP[0].BUFSEG + (uint32_t)((ep) << 4))))

/**
  * @brief       Set USB endpoint stall state
  *
  * @param[in]   ep  The USB endpoint ID. M451 Series supports 8 hardware endpoint ID. This parameter could be 0 ~ 7.
  *
  * @return      None
  *
  * @details     Set USB endpoint stall state for the specified endpoint ID. Endpoint will respond STALL token automatically.
  * \hideinitializer
  */
#define USBD_SET_EP_STALL(ep)        (*((__IO uint32_t *) ((uint32_t)&USBD->EP[0ul].CFGP + (uint32_t)((ep) << 4))) |= USBD_CFGP_SSTALL_Msk)

/**
  * @brief       Clear USB endpoint stall state
  *
  * @param[in]   ep  The USB endpoint ID. M451 Series supports 8 hardware endpoint ID. This parameter could be 0 ~ 7.
  *
  * @return      None
  *
  * @details     Clear USB endpoint stall state for the specified endpoint ID. Endpoint will respond ACK/NAK token.
  * \hideinitializer
  */
#define USBD_CLR_EP_STALL(ep)        (*((__IO uint32_t *) ((uint32_t)&USBD->EP[0].CFGP + (uint32_t)((ep) << 4))) &= ~USBD_CFGP_SSTALL_Msk)

/**
  * @brief       Get USB endpoint stall state
  *
  * @param[in]   ep  The USB endpoint ID. M451 Series supports 8 hardware endpoint ID. This parameter could be 0 ~ 7.
  *
  * @retval      0      USB endpoint is not stalled.
  * @retval      Others USB endpoint is stalled.
  *
  * @details     Get USB endpoint stall state of the specified endpoint ID.
  * \hideinitializer
  */
#define USBD_GET_EP_STALL(ep)        (*((__IO uint32_t *) ((uint32_t)&USBD->EP[0].CFGP + (uint32_t)((ep) << 4))) & USBD_CFGP_SSTALL_Msk)

/**
  * @brief      To support byte access between USB SRAM and system SRAM
  *
  * @param[in]  dest Destination pointer.
  *
  * @param[in]  src  Source pointer.
  *
  * @param[in]  size Byte count.
  *
  * @return     None
  *
  * @details    This function will copy the number of data specified by size and src parameters to the address specified by dest parameter.
  *
  */
__STATIC_INLINE void USBD_MemCopy(uint8_t dest[], uint8_t src[], uint32_t size)
{
    uint32_t volatile i = 0ul;

    while (size--)
    {
        dest[i] = src[i];
        i++;
    }
}

/**
  * @brief       Set USB endpoint stall state
  *
  * @param[in]   epnum  USB endpoint number
  *
  * @return      None
  *
  * @details     Set USB endpoint stall state. Endpoint will respond STALL token automatically.
  *
  */
__STATIC_INLINE void USBD_SetStall(uint8_t epnum)
{
    uint32_t u32CfgAddr;
    uint32_t u32Cfg;
    uint32_t i;

    for (i = 0ul; i < USBD_MAX_EP; i++)
    {
        u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&USBD->EP[0].CFG; /* USBD_CFG0 */
        u32Cfg = *((__IO uint32_t *)(u32CfgAddr));

        if ((u32Cfg & 0xful) == epnum)
        {
            u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&USBD->EP[0].CFGP; /* USBD_CFGP0 */
            u32Cfg = *((__IO uint32_t *)(u32CfgAddr));

            *((__IO uint32_t *)(u32CfgAddr)) = (u32Cfg | USBD_CFGP_SSTALL);
            break;
        }
    }
}

/**
  * @brief       Clear USB endpoint stall state
  *
  * @param[in]   epnum  USB endpoint number
  *
  * @return      None
  *
  * @details     Clear USB endpoint stall state. Endpoint will respond ACK/NAK token.
  */
__STATIC_INLINE void USBD_ClearStall(uint8_t epnum)
{
    uint32_t u32CfgAddr;
    uint32_t u32Cfg;
    uint32_t i;

    for (i = 0ul; i < USBD_MAX_EP; i++)
    {
        u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&USBD->EP[0].CFG; /* USBD_CFG0 */
        u32Cfg = *((__IO uint32_t *)(u32CfgAddr));

        if ((u32Cfg & 0xful) == epnum)
        {
            u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&USBD->EP[0].CFGP; /* USBD_CFGP0 */
            u32Cfg = *((__IO uint32_t *)(u32CfgAddr));

            *((__IO uint32_t *)(u32CfgAddr)) = (u32Cfg & ~USBD_CFGP_SSTALL);
            break;
        }
    }
}

/**
  * @brief       Get USB endpoint stall state
  *
  * @param[in]   epnum  USB endpoint number
  *
  * @retval      0      USB endpoint is not stalled.
  * @retval      Others USB endpoint is stalled.
  *
  * @details     Get USB endpoint stall state.
  *
  */
__STATIC_INLINE uint32_t USBD_GetStall(uint8_t epnum)
{
    uint32_t u32CfgAddr;
    uint32_t u32Cfg;
    uint32_t i;

    for (i = 0ul; i < USBD_MAX_EP; i++)
    {
        u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&USBD->EP[0].CFG; /* USBD_CFG0 */
        u32Cfg = *((__IO uint32_t *)(u32CfgAddr));

        if ((u32Cfg & 0xful) == epnum)
        {
            u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&USBD->EP[0].CFGP; /* USBD_CFGP0 */
            break;
        }
    }

    return ((*((__IO uint32_t *)(u32CfgAddr))) & USBD_CFGP_SSTALL);
}


extern volatile uint8_t g_usbd_RemoteWakeupEn;


typedef void (*VENDOR_REQ)(void);           /*!< Functional pointer type definition for Vendor class */
typedef void (*CLASS_REQ)(void);            /*!< Functional pointer type declaration for USB class request callback handler */
typedef void (*SET_INTERFACE_REQ)(uint32_t u32AltInterface);    /*!< Functional pointer type declaration for USB set interface request callback handler */
typedef void (*SET_CONFIG_CB)(void);       /*!< Functional pointer type declaration for USB set configuration request callback handler */


/*--------------------------------------------------------------------*/
void USBD_Open(const S_USBD_INFO_T *param, CLASS_REQ pfnClassReq, SET_INTERFACE_REQ pfnSetInterface);
void USBD_Start(void);
void USBD_GetSetupPacket(uint8_t *buf);
void USBD_ProcessSetupPacket(void);
void USBD_StandardRequest(void);
void USBD_PrepareCtrlIn(uint8_t pu8Buf[], uint32_t u32Size);
void USBD_CtrlIn(void);
void USBD_PrepareCtrlOut(uint8_t *pu8Buf, uint32_t u32Size);
void USBD_CtrlOut(void);
void USBD_SwReset(void);
void USBD_SetVendorRequest(VENDOR_REQ pfnVendorReq);
void USBD_SetConfigCallback(SET_CONFIG_CB pfnSetConfigCallback);
void USBD_LockEpStall(uint32_t u32EpBitmap);

/*@}*/ /* end of group USBD_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USBD_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_USBD_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
