/**************************************************************************//**
 * @file     nu_hsusbd.h
 * @version  V3.00
 * @brief    M460 series HSUSBD driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 ****************************************************************************/
#ifndef __NU_HSUSBD_H__
#define __NU_HSUSBD_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup HSUSBD_Driver HSUSBD Driver
  @{
*/

/** @addtogroup HSUSBD_EXPORTED_CONSTANTS HSUSBD Exported Constants
  @{
*/
/** @cond HIDDEN_SYMBOLS */
#define HSUSBD_MAX_EP     12ul

#define Maximum(a,b)    (a)>(b) ? (a) : (b)
#define Minimum(a,b)    (((a)<(b)) ? (a) : (b))


#define CEP     0xfful    /*!< Control Endpoint  \hideinitializer */
#define EPA     0ul       /*!< Endpoint A  \hideinitializer */
#define EPB     1ul       /*!< Endpoint B  \hideinitializer */
#define EPC     2ul       /*!< Endpoint C  \hideinitializer */
#define EPD     3ul       /*!< Endpoint D  \hideinitializer */
#define EPE     4ul       /*!< Endpoint E  \hideinitializer */
#define EPF     5ul       /*!< Endpoint F  \hideinitializer */
#define EPG     6ul       /*!< Endpoint G  \hideinitializer */
#define EPH     7ul       /*!< Endpoint H  \hideinitializer */
#define EPI     8ul       /*!< Endpoint I  \hideinitializer */
#define EPJ     9ul       /*!< Endpoint J  \hideinitializer */
#define EPK     10ul      /*!< Endpoint K  \hideinitializer */
#define EPL     11ul      /*!< Endpoint L  \hideinitializer */

/** @endcond HIDDEN_SYMBOLS */
/********************* Bit definition of CEPCTL register **********************/
#define HSUSBD_CEPCTL_NAKCLR                    ((uint32_t)0x00000000ul)      /*!<NAK clear  \hideinitializer */
#define HSUSBD_CEPCTL_STALL                     ((uint32_t)0x00000002ul)      /*!<Stall  \hideinitializer */
#define HSUSBD_CEPCTL_ZEROLEN                   ((uint32_t)0x00000004ul)      /*!<Zero length packet  \hideinitializer */
#define HSUSBD_CEPCTL_FLUSH                     ((uint32_t)0x00000008ul)      /*!<CEP flush  \hideinitializer */

/********************* Bit definition of EPxRSPCTL register **********************/
#define HSUSBD_EP_RSPCTL_FLUSH                  ((uint32_t)0x00000001ul)      /*!<Buffer Flush  \hideinitializer */
#define HSUSBD_EP_RSPCTL_MODE_AUTO              ((uint32_t)0x00000000ul)      /*!<Auto-Validate Mode  \hideinitializer */
#define HSUSBD_EP_RSPCTL_MODE_MANUAL            ((uint32_t)0x00000002ul)      /*!<Manual-Validate Mode  \hideinitializer */
#define HSUSBD_EP_RSPCTL_MODE_FLY               ((uint32_t)0x00000004ul)      /*!<Fly Mode  \hideinitializer */
#define HSUSBD_EP_RSPCTL_MODE_MASK              ((uint32_t)0x00000006ul)      /*!<Mode Mask  \hideinitializer */
#define HSUSBD_EP_RSPCTL_TOGGLE                 ((uint32_t)0x00000008ul)      /*!<Clear Toggle bit  \hideinitializer */
#define HSUSBD_EP_RSPCTL_HALT                   ((uint32_t)0x00000010ul)      /*!<Endpoint halt  \hideinitializer */
#define HSUSBD_EP_RSPCTL_ZEROLEN                ((uint32_t)0x00000020ul)      /*!<Zero length packet IN  \hideinitializer */
#define HSUSBD_EP_RSPCTL_SHORTTXEN              ((uint32_t)0x00000040ul)      /*!<Packet end  \hideinitializer */
#define HSUSBD_EP_RSPCTL_DISBUF                 ((uint32_t)0x00000080ul)      /*!<Disable buffer  \hideinitializer */

/********************* Bit definition of EPxCFG register **********************/
#define HSUSBD_EP_CFG_VALID                     ((uint32_t)0x00000001ul)      /*!<Endpoint Valid  \hideinitializer */
#define HSUSBD_EP_CFG_TYPE_BULK                 ((uint32_t)0x00000002ul)      /*!<Endpoint type - bulk  \hideinitializer */
#define HSUSBD_EP_CFG_TYPE_INT                  ((uint32_t)0x00000004ul)      /*!<Endpoint type - interrupt  \hideinitializer */
#define HSUSBD_EP_CFG_TYPE_ISO                  ((uint32_t)0x00000006ul)      /*!<Endpoint type - isochronous  \hideinitializer */
#define HSUSBD_EP_CFG_TYPE_MASK                 ((uint32_t)0x00000006ul)      /*!<Endpoint type mask  \hideinitializer */
#define HSUSBD_EP_CFG_DIR_OUT                   ((uint32_t)0x00000000ul)      /*!<OUT endpoint  \hideinitializer */
#define HSUSBD_EP_CFG_DIR_IN                    ((uint32_t)0x00000008ul)      /*!<IN endpoint  \hideinitializer */

/********************* Bit definition of BCDC register **********************/
#define HSUSBD_BCDC_DETMOD_IDLE                 ((uint32_t)0x00000000ul)      /*!<Idle  \hideinitializer */
#define HSUSBD_BCDC_DETMOD_VBUS                 ((uint32_t)0x00000002ul)      /*!<Vbus detect  \hideinitializer */
#define HSUSBD_BCDC_DETMOD_DCD                  ((uint32_t)0x00000004ul)      /*!<Data contact detect  \hideinitializer */
#define HSUSBD_BCDC_DETMOD_PD                   ((uint32_t)0x00000006ul)      /*!<Primary detect  \hideinitializer */
#define HSUSBD_BCDC_DETMOD_SD                   ((uint32_t)0x00000008ul)      /*!<Secondary detect  \hideinitializer */
#define HSUSBD_BCDC_DETSTS_VBUS_UNREACH         ((uint32_t)0x00000000ul)      /*!<Vbus unreach  \hideinitializer */
#define HSUSBD_BCDC_DETSTS_VBUS_REACH           ((uint32_t)0x00000010ul)      /*!<Vbus reach  \hideinitializer */
#define HSUSBD_BCDC_DETSTS_DCD_DATA_UNCONTACT   ((uint32_t)0x00000000ul)      /*!<Data pin uncontact  \hideinitializer */
#define HSUSBD_BCDC_DETSTS_DCD_DATA_CONTACT     ((uint32_t)0x00000010ul)      /*!<Data pin contact  \hideinitializer */
#define HSUSBD_BCDC_DETSTS_PD_SDP_NUSP          ((uint32_t)0x00000000ul)      /*!<SDP or NUSP  \hideinitializer */
#define HSUSBD_BCDC_DETSTS_PD_DCP_CDP           ((uint32_t)0x00000010ul)      /*!<DCP or CDP  \hideinitializer */
#define HSUSBD_BCDC_DETSTS_SD_CDP               ((uint32_t)0x00000000ul)      /*!<CDP  \hideinitializer */
#define HSUSBD_BCDC_DETSTS_SD_DCP               ((uint32_t)0x00000010ul)      /*!<DCP  \hideinitializer */

#define HSUSBD_TIMEOUT      SystemCoreClock     /*!< 1 second time-out \hideinitializer */
#define HSUSBD_TIMEOUT_ERR  (-2L)               /*!< HSUSBD operation abort due to timeout error \hideinitializer */

/*@}*/ /* end of group HSUSBD_EXPORTED_CONSTANTS */

/** @addtogroup HSUSBD_EXPORTED_STRUCT HSUSBD Exported Struct
  @{
*/


typedef struct HSUSBD_CMD_STRUCT
{
    uint8_t  bmRequestType;
    uint8_t  bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;

} S_HSUSBD_CMD_T; /*!<USB Setup Packet Structure */




typedef struct s_hsusbd_info
{
    uint8_t *gu8DevDesc;            /*!< Device descriptor */
    uint8_t *gu8ConfigDesc;         /*!< Config descriptor */
    uint8_t **gu8StringDesc;        /*!< Pointer for USB String Descriptor pointers */
    uint8_t *gu8QualDesc;           /*!< Qualifier descriptor */
    uint8_t *gu8FullConfigDesc;     /*!< Full Speed Config descriptor */
    uint8_t *gu8HSOtherConfigDesc;  /*!< Other Speed Config descriptor */
    uint8_t *gu8FSOtherConfigDesc;  /*!< Other Speed Config descriptor */
    uint8_t *gu8BosDesc;            /*!< Pointer for USB BOS Descriptor */
    uint8_t **gu8HidReportDesc;     /*!< Pointer for HID Report descriptor */
    uint32_t *gu32HidReportSize;    /*!< Pointer for HID Report descriptor Size */
    uint32_t *gu32ConfigHidDescIdx; /*!< Pointer for HID Descriptor start index */

} S_HSUSBD_INFO_T; /*!<USB Information Structure */


/*@}*/ /* end of group HSUSBD_EXPORTED_STRUCT */

/** @cond HIDDEN_SYMBOLS */
extern uint32_t g_u32HsEpStallLock;
extern uint8_t volatile g_hsusbd_Configured;
extern uint8_t g_hsusbd_ShortPacket;
extern uint8_t g_hsusbd_CtrlZero;
extern uint8_t g_hsusbd_UsbAddr;
extern uint32_t volatile g_hsusbd_DmaDone;
extern uint32_t g_hsusbd_CtrlInSize;
extern S_HSUSBD_INFO_T gsHSInfo;
extern S_HSUSBD_CMD_T gUsbCmd;
extern int32_t g_HBI_i32ErrCode;
/** @endcond HIDDEN_SYMBOLS */


/** @addtogroup HSUSBD_EXPORTED_FUNCTIONS HSUSBD Exported Functions
  @{
*/

#define HSUSBD_ENABLE_USB()               ((uint32_t)(HSUSBD->PHYCTL |= (HSUSBD_PHYCTL_PHYEN_Msk|HSUSBD_PHYCTL_DPPUEN_Msk))) /*!<Enable USB  \hideinitializer */
#define HSUSBD_DISABLE_USB()              ((uint32_t)(HSUSBD->PHYCTL &= ~HSUSBD_PHYCTL_DPPUEN_Msk)) /*!<Disable USB  \hideinitializer */
#define HSUSBD_ENABLE_PHY()               ((uint32_t)(HSUSBD->PHYCTL |= HSUSBD_PHYCTL_PHYEN_Msk)) /*!<Enable PHY  \hideinitializer */
#define HSUSBD_DISABLE_PHY()              ((uint32_t)(HSUSBD->PHYCTL &= ~HSUSBD_PHYCTL_PHYEN_Msk)) /*!<Disable PHY  \hideinitializer */
#define HSUSBD_SET_SE0()                  ((uint32_t)(HSUSBD->PHYCTL &= ~HSUSBD_PHYCTL_DPPUEN_Msk)) /*!<Enable SE0, Force USB PHY Transceiver to Drive SE0  \hideinitializer */
#define HSUSBD_CLR_SE0()                  ((uint32_t)(HSUSBD->PHYCTL |= HSUSBD_PHYCTL_DPPUEN_Msk)) /*!<Disable SE0  \hideinitializer */
#define HSUSBD_SET_ADDR(addr)             (HSUSBD->FADDR = (addr)) /*!<Set USB address  \hideinitializer */
#define HSUSBD_GET_ADDR()                 ((uint32_t)(HSUSBD->FADDR)) /*!<Get USB address  \hideinitializer */
#define HSUSBD_ENABLE_USB_INT(intr)       (HSUSBD->GINTEN = (intr)) /*!<Enable USB Interrupt  \hideinitializer */
#define HSUSBD_ENABLE_BUS_INT(intr)       (HSUSBD->BUSINTEN = (intr)) /*!<Enable BUS Interrupt  \hideinitializer */
#define HSUSBD_GET_BUS_INT_FLAG()         (HSUSBD->BUSINTSTS)        /*!<Get Bus interrupt flag  \hideinitializer */
#define HSUSBD_CLR_BUS_INT_FLAG(flag)     (HSUSBD->BUSINTSTS = (flag)) /*!<Clear Bus interrupt flag  \hideinitializer */
#define HSUSBD_ENABLE_CEP_INT(intr)       (HSUSBD->CEPINTEN = (intr)) /*!<Enable CEP Interrupt  \hideinitializer */
#define HSUSBD_CLR_CEP_INT_FLAG(flag)     (HSUSBD->CEPINTSTS = (flag)) /*!<Clear CEP interrupt flag  \hideinitializer */
#define HSUSBD_SET_CEP_STATE(flag)        (HSUSBD->CEPCTL = (flag)) /*!<Set CEP state  \hideinitializer */
#define HSUSBD_START_CEP_IN(size)         (HSUSBD->CEPTXCNT = (size)) /*!<Start CEP IN Transfer  \hideinitializer */
#define HSUSBD_SET_MAX_PAYLOAD(ep, size)  (HSUSBD->EP[(ep)].EPMPS = (size)) /*!<Set EPx Maximum Packet Size  \hideinitializer */
#define HSUSBD_ENABLE_EP_INT(ep, intr)    (HSUSBD->EP[(ep)].EPINTEN = (intr)) /*!<Enable EPx Interrupt  \hideinitializer */
#define HSUSBD_GET_EP_INT_FLAG(ep)        (HSUSBD->EP[(ep)].EPINTSTS) /*!<Get EPx interrupt flag  \hideinitializer */
#define HSUSBD_CLR_EP_INT_FLAG(ep, flag)  (HSUSBD->EP[(ep)].EPINTSTS = (flag)) /*!<Clear EPx interrupt flag  \hideinitializer */
#define HSUSBD_SET_DMA_LEN(len)           (HSUSBD->DMACNT = (len)) /*!<Set DMA transfer length  \hideinitializer */
#define HSUSBD_SET_DMA_ADDR(addr)         (HSUSBD->DMAADDR = (addr)) /*!<Set DMA transfer address  \hideinitializer */
#define HSUSBD_SET_DMA_READ(epnum)        (HSUSBD->DMACTL = (HSUSBD->DMACTL & ~HSUSBD_DMACTL_EPNUM_Msk) | HSUSBD_DMACTL_DMARD_Msk | (epnum) | 0x100) /*!<Set DMA transfer type to read \hideinitializer */
#define HSUSBD_SET_DMA_WRITE(epnum)       (HSUSBD->DMACTL = (HSUSBD->DMACTL & ~(HSUSBD_DMACTL_EPNUM_Msk | HSUSBD_DMACTL_DMARD_Msk | 0x100)) | (epnum)) /*!<Set DMA transfer type to write \hideinitializer */
#define HSUSBD_ENABLE_DMA()               (HSUSBD->DMACTL |= HSUSBD_DMACTL_DMAEN_Msk) /*!<Enable DMA transfer  \hideinitializer */
#define HSUSBD_IS_ATTACHED()              ((uint32_t)(HSUSBD->PHYCTL & HSUSBD_PHYCTL_VBUSDET_Msk)) /*!<Check cable connect state  \hideinitializer */
#define HSUSBD_ENABLE_BCD()               ((uint32_t)(HSUSBD->BCDC |= HSUSBD_BCDC_BCDEN_Msk)) /*!<Enable BCD  \hideinitializer */
#define HSUSBD_DISABLE_BCD()              ((uint32_t)(HSUSBD->BCDC &= ~HSUSBD_BCDC_BCDEN_Msk)) /*!<Disable BCD  \hideinitializer */
#define HSUSBD_ENABLE_LPM()               ((uint32_t)(HSUSBD->LPMCSR |= HSUSBD_LPMCSR_LPMEN_Msk)) /*!<Enable LPM  \hideinitializer */
#define HSUSBD_DISABLE_LPM()              ((uint32_t)(HSUSBD->LPMCSR &= ~HSUSBD_LPMCSR_LPMEN_Msk)) /*!<Disable LPM  \hideinitializer */

/**
  * @brief  HSUSBD_memcpy, Copy bytes hardware limitation
  * @param[in]  u8Dst   Destination pointer.
  * @param[in]  u8Src   Source pointer.
  * @param[in]  u32Size Copy size.
  * @retval None.
  */
__STATIC_INLINE void HSUSBD_MemCopy(uint8_t u8Dst[], uint8_t u8Src[], uint32_t u32Size)
{
    uint32_t i = 0ul;

    while (u32Size--)
    {
        u8Dst[i] = u8Src[i];
        i++;
    }
}

/**
  * @brief  HSUSBD_ResetDMA
  * @param  None
  * @retval None.
  */
__STATIC_INLINE void HSUSBD_ResetDMA(void)
{
    HSUSBD->DMACNT = 0ul;
    HSUSBD->DMACTL = 0x80ul;
    HSUSBD->DMACTL = 0x00ul;
}
/**
  * @brief  HSUSBD_SetEpBufAddr, Set Endpoint buffer address
  * @param[in]  u32Ep      Endpoint Number
  * @param[in]  u32Base    Buffer Start Address
  * @param[in]  u32Len     Buffer length
  * @retval None.
  */
__STATIC_INLINE void HSUSBD_SetEpBufAddr(uint32_t u32Ep, uint32_t u32Base, uint32_t u32Len)
{
    if (u32Ep == CEP)
    {
        HSUSBD->CEPBUFST = u32Base;
        HSUSBD->CEPBUFEND   = u32Base + u32Len - 1ul;
    }
    else
    {
        HSUSBD->EP[u32Ep].EPBUFST = u32Base;
        HSUSBD->EP[u32Ep].EPBUFEND = u32Base + u32Len - 1ul;
    }
}

/**
  * @brief  HSUSBD_ConfigEp, Config Endpoint
  * @param[in]  u32Ep      USB endpoint
  * @param[in]  u32EpNum   Endpoint number
  * @param[in]  u32EpType  Endpoint type
  * @param[in]  u32EpDir   Endpoint direction
  * @retval None.
  */
__STATIC_INLINE void HSUSBD_ConfigEp(uint32_t u32Ep, uint32_t u32EpNum, uint32_t u32EpType, uint32_t u32EpDir)
{
    if (u32EpType == HSUSBD_EP_CFG_TYPE_BULK)
    {
        HSUSBD->EP[u32Ep].EPRSPCTL = (HSUSBD_EP_RSPCTL_FLUSH | HSUSBD_EP_RSPCTL_MODE_AUTO);
    }
    else if (u32EpType == HSUSBD_EP_CFG_TYPE_INT)
    {
        HSUSBD->EP[u32Ep].EPRSPCTL = (HSUSBD_EP_RSPCTL_FLUSH | HSUSBD_EP_RSPCTL_MODE_MANUAL);
    }
    else if (u32EpType == HSUSBD_EP_CFG_TYPE_ISO)
    {
        HSUSBD->EP[u32Ep].EPRSPCTL = (HSUSBD_EP_RSPCTL_FLUSH | HSUSBD_EP_RSPCTL_MODE_FLY);
    }

    HSUSBD->EP[u32Ep].EPCFG = (u32EpType | u32EpDir | HSUSBD_EP_CFG_VALID | (u32EpNum << 4));
}

/**
  * @brief       Set USB endpoint stall state
  * @param[in]   u32Ep  The USB endpoint ID.
  * @return      None
  * @details     Set USB endpoint stall state for the specified endpoint ID. Endpoint will respond STALL token automatically.
  */
__STATIC_INLINE void HSUSBD_SetEpStall(uint32_t u32Ep)
{
    if (u32Ep == CEP)
    {
        HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALL);
    }
    else
    {
        HSUSBD->EP[u32Ep].EPRSPCTL = (HSUSBD->EP[u32Ep].EPRSPCTL & 0xf7ul) | HSUSBD_EP_RSPCTL_HALT;
    }
}

/**
 * @brief       Set USB endpoint stall state
 *
 * @param[in]   u32EpNum         USB endpoint
 * @return      None
 *
 * @details     Set USB endpoint stall state, endpoint will return STALL token.
 */
__STATIC_INLINE void HSUSBD_SetStall(uint32_t u32EpNum)
{
    uint32_t i;

    if (u32EpNum == 0ul)
    {
        HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALL);
    }
    else
    {
        for (i = 0ul; i < HSUSBD_MAX_EP; i++)
        {
            if (((HSUSBD->EP[i].EPCFG & 0xf0ul) >> 4) == u32EpNum)
            {
                HSUSBD->EP[i].EPRSPCTL = (HSUSBD->EP[i].EPRSPCTL & 0xf7ul) | HSUSBD_EP_RSPCTL_HALT;
            }
        }
    }
}

/**
  * @brief       Clear USB endpoint stall state
  * @param[in]   u32Ep  The USB endpoint ID.
  * @return      None
  * @details     Clear USB endpoint stall state for the specified endpoint ID. Endpoint will respond ACK/NAK token.
  */
__STATIC_INLINE void  HSUSBD_ClearEpStall(uint32_t u32Ep)
{
    HSUSBD->EP[u32Ep].EPRSPCTL = HSUSBD_EP_RSPCTL_TOGGLE;
}

/**
 * @brief       Clear USB endpoint stall state
 *
 * @param[in]   u32EpNum         USB endpoint
 * @return      None
 *
 * @details     Clear USB endpoint stall state, endpoint will return ACK/NAK token.
 */
__STATIC_INLINE void HSUSBD_ClearStall(uint32_t u32EpNum)
{
    uint32_t i;

    for (i = 0ul; i < HSUSBD_MAX_EP; i++)
    {
        if (((HSUSBD->EP[i].EPCFG & 0xf0ul) >> 4) == u32EpNum)
        {
            HSUSBD->EP[i].EPRSPCTL = HSUSBD_EP_RSPCTL_TOGGLE;
        }
    }
}

/**
  * @brief       Get USB endpoint stall state
  * @param[in]   u32Ep  The USB endpoint ID.
  * @retval      0      USB endpoint is not stalled.
  * @retval      Others USB endpoint is stalled.
  * @details     Get USB endpoint stall state of the specified endpoint ID.
  */
__STATIC_INLINE uint32_t HSUSBD_GetEpStall(uint32_t u32Ep)
{
    return (HSUSBD->EP[u32Ep].EPRSPCTL & HSUSBD_EP_RSPCTL_HALT);
}

/**
 * @brief       Get USB endpoint stall state
 *
 * @param[in]   u32EpNum         USB endpoint
 * @retval      0: USB endpoint is not stalled.
 * @retval      non-0: USB endpoint is stalled.
 *
 * @details     Get USB endpoint stall state.
 */
__STATIC_INLINE uint32_t HSUSBD_GetStall(uint32_t u32EpNum)
{
    uint32_t i;
    uint32_t val = 0ul;

    for (i = 0ul; i < HSUSBD_MAX_EP; i++)
    {
        if (((HSUSBD->EP[i].EPCFG & 0xf0ul) >> 4) == u32EpNum)
        {
            val = (HSUSBD->EP[i].EPRSPCTL & HSUSBD_EP_RSPCTL_HALT);
            break;
        }
    }
    return val;
}


/*-------------------------------------------------------------------------------------------*/
typedef void (*HSUSBD_VENDOR_REQ)(void); /*!<USB Vendor request callback function */
typedef void (*HSUSBD_CLASS_REQ)(void); /*!<USB Class request callback function */
typedef void (*HSUSBD_SET_INTERFACE_REQ)(uint32_t u32AltInterface); /*!<USB Standard request "Set Interface" callback function */

void HSUSBD_Open(S_HSUSBD_INFO_T *param, HSUSBD_CLASS_REQ pfnClassReq, HSUSBD_SET_INTERFACE_REQ pfnSetInterface);
void HSUSBD_Start(void);
void HSUSBD_ProcessSetupPacket(void);
void HSUSBD_StandardRequest(void);
void HSUSBD_UpdateDeviceState(void);
void HSUSBD_PrepareCtrlIn(uint8_t pu8Buf[], uint32_t u32Size);
void HSUSBD_CtrlIn(void);
void HSUSBD_CtrlOut(uint8_t pu8Buf[], uint32_t u32Size);
void HSUSBD_SwReset(void);
void HSUSBD_SetVendorRequest(HSUSBD_VENDOR_REQ pfnVendorReq);



/*@}*/ /* end of group HSUSBD_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group HSUSBD_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /*__NU_HSUSBD_H__ */
