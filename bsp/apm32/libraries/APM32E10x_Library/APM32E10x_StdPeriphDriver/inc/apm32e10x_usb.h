/*!
 * @file        apm32e10x_usb.h
 *
 * @brief       This file contains all the prototypes,enumeration and macros for USBD peripheral
 *
 * @version     V1.0.2
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32E10X_USBD_H_
#define __APM32E10X_USBD_H_

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup USBD_Driver
  @{
*/

/** @defgroup USBD_Macros Macros
  @{
*/

/* USBD packet memory area base address */
#define USBD_PMA_ADDR            (0x40006000L)

/* Endpoint register mask value default */
#define USBD_EP_MASK_DEFAULT     (USBD_EP_BIT_CTFR | USBD_EP_BIT_SETUP | USBD_EP_BIT_TYPE | USBD_EP_BIT_KIND | USBD_EP_BIT_CTFT |USBD_EP_BIT_ADDR)

/**
 * @brief   USBD interrupt source
 */
#define USBD_INT_ESOF            0X100
#define USBD_INT_SOF             0X200
#define USBD_INT_RST             0X400
#define USBD_INT_SUS             0x800
#define USBD_INT_WKUP            0X1000
#define USBD_INT_ERR             0X2000
#define USBD_INT_PMAOU           0X4000
#define USBD_INT_CTR             0X8000
#define USBD_INT_ALL             0XFF00

/*!
 * @brief       Set CTRL register
 *
 * @param       val:    Register value
 *
 * @retval      None
 *
 */
#define USBD_SetRegCTRL(val)         (USBD->CTRL = val)

/*!
 * @brief       Set INTSTS register
 *
 * @param       val:    Register value
 *
 * @retval      None
 */
#define USBD_SetRegINTSTS(val)       (USBD->INTSTS = val)

/*!
 * @brief       Set force reset
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_SetForceReset()         (USBD->CTRL_B.FORRST = BIT_SET)

/*!
 * @brief       Reset force reset
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_ResetForceReset()       (USBD->CTRL_B.FORRST = BIT_RESET)

/*!
 * @brief       Set power down
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_SetPowerDown()          (USBD->CTRL_B.PWRDOWN = BIT_SET)

/*!
 * @brief       Reset power down
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_ResetPowerDown()        (USBD->CTRL_B.PWRDOWN = BIT_RESET)

/*!
 * @brief       Set low power mode
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_SetLowerPowerMode()     (USBD->CTRL_B.LPWREN = BIT_SET)

/*!
 * @brief       Ret low power mode
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_ResetLowerPowerMode()   (USBD->CTRL_B.LPWREN = BIT_RESET)

/*!
 * @brief       Set force suspend
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_SetForceSuspend()       (USBD->CTRL_B.FORSUS = BIT_SET)

/*!
 * @brief       Reset force suspend
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_ResetForceSuspend()     (USBD->CTRL_B.FORSUS = BIT_RESET)

/*!
 * @brief       Read force suspend status
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_ReadForceSuspend()      (USBD->CTRL_B.FORSUS)

/*!
 * @brief       Set resume
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_SetResume()             (USBD->CTRL_B.WUPREQ = BIT_SET)

/*!
 * @brief       Reset resume
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_ResetResume()           (USBD->CTRL_B.WUPREQ = BIT_RESET)

/*!
 * @brief       Enable interrupt
 *
 * @param       int:    Interrupt source
 *
 * @retval      None
 */
#define USBD_EnableInterrupt(int)    (USBD->CTRL |= int)

/*!
 * @brief       Disable interrupt
 *
 * @param       int:    Interrupt source
 *
 * @retval      None
 */
#define USBD_DisableInterrupt(int)   (USBD->CTRL &= (uint32_t)~int)

/*!
 * @brief       Read the specified interrupt flag status
 *
 * @param       int:    Interrupt source
 *
 * @retval      Flag status.0 or not 0
 */
#define USBD_ReadIntFlag(int)        (USBD->INTSTS & int)

/*!
 * @brief       Clear the specified interrupt flag status
 *
 * @param       int:    Interrupt source
 *
 * @retval      None
 */
#define USBD_ClearIntFlag(int)       (USBD->INTSTS &= (uint32_t)~int)

/*!
 * @brief       Read DOT field value in INTSTS rigister
 *
 * @param       None
 *
 * @retval      DOT field value
 */
#define USBD_ReadDir()               (USBD->INTSTS_B.DOT)

/*!
 * @brief       Read EPID field value in INTSTS rigister
 *
 * @param       None
 *
 * @retval      EPIDfield value
 */
#define USBD_ReadEP()                ((USBD_EP_T)(USBD->INTSTS_B.EPID))

/*!
 * @brief       Read EP type
 *
 * @param       ep:     EP number
 *
 * @retval      EP type
 */
#define USBD_ReadEPType(ep)          (USBD->EP[ep].EP_B.TYPE)

/*!
 * @brief       Read EP Tx status
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx status
 */
#define USBD_ReadEPTxStatus(ep)      ((USBD_EP_STATUS_T)(USBD->EP[ep].EP_B.TXSTS))

/*!
 * @brief       Read EP Rx status
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx status
 */
#define USBD_ReadEPRxStatus(ep)      ((USBD_EP_STATUS_T)(USBD->EP[ep].EP_B.RXSTS))

/*!
 * @brief       Read EP Tx address pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx address pointer
 */
#define USBD_ReadEPTxAddrPointer(ep) (uint32_t *)((USBD->BUFFTB + ep * 8) * 2 + USBD_PMA_ADDR)


/*!
 * @brief       Read EP Tx count pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx count pointer
 */
#define USBD_ReadEPTxCntPointer(ep)  (uint32_t *)((USBD->BUFFTB + ep * 8 + 2) * 2 + USBD_PMA_ADDR)

/*!
 * @brief       Read EP Rx address pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx address pointer
 */
#define USBD_ReadEPRxAddrPointer(ep) (uint32_t *)((USBD->BUFFTB + ep * 8 + 4) * 2 + USBD_PMA_ADDR)

/*!
 * @brief       Read EP Rx count pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx count pointer
 */
#define USBD_ReadEPRxCntPointer(ep)  (uint32_t *)((USBD->BUFFTB + ep * 8 + 6) * 2 + USBD_PMA_ADDR)

/*!
 * @brief       Set EP Tx addr
 *
 * @param       ep:     EP number
 *
 * @param       addr:   Tx addr
 *
 * @retval      None
 */
#define USBD_SetEPTxAddr(ep, addr)   (*USBD_ReadEPTxAddrPointer(ep) = (addr >> 1) << 1)

/*!
 * @brief       Set EP Rx addr
 *
 * @param       ep:     EP number
 *
 * @param       addr:   Rx addr
 *
 * @retval      None
 */
#define USBD_SetEPRxAddr(ep, addr)   (*USBD_ReadEPRxAddrPointer(ep) = (addr >> 1) << 1)

/*!
 * @brief       Read EP Tx addr
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx addr
 */
#define USBD_ReadEPTxAddr(ep)        ((uint16_t)*USBD_ReadEPTxAddrPointer(ep))

/*!
 * @brief       Read EP Rx addr
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx addr
 */
#define USBD_ReadEPRxAddr(ep)        ((uint16_t)*USBD_ReadEPRxAddrPointer(ep))

/*!
 * @brief       Set EP Rx Count
 *
 * @param       ep:     EP number
 *
 * @param       cnt:    Tx count
 *
 * @retval      None
 */
#define USBD_SetEPTxCnt(ep, cnt)     (*USBD_ReadEPTxCntPointer(ep) = cnt)

/*!
 * @brief       Read EP Tx count
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx count
 */
#define USBD_ReadEPTxCnt(ep)        ((uint16_t)*USBD_ReadEPTxCntPointer(ep) & 0x3ff)

/*!
 * @brief       Read EP Rx count
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx count
 */
#define USBD_ReadEPRxCnt(ep)        ((uint16_t)*USBD_ReadEPRxCntPointer(ep) & 0x3ff)

/*!
 * @brief       Read SETUP field value in EP register
 *
 * @param       ep:     EP number
 *
 * @retval      SETUP field value
 */
#define USBD_ReadEPSetup(ep)         (USBD->EP[ep].EP_B.SETUP)

/*!
 * @brief       Set buffer table value
 *
 * @param       tab:    Buffer table value
 *
 * @retval      None
 */
#define USBD_SetBufferTable(tab)     (USBD->BUFFTB_B.BUFFTB = tab)

/*!
 * @brief       Set device address
 *
 * @param       addr:   Device address
 *
 * @retval      None
 */
#define USBD_SetDeviceAddr(addr)     (USBD->ADDR_B.ADDR = addr)

/*!
 * @brief       Read CTFR field value in EP register
 *
 * @param       ep: Endpoint number
 *
 * @retval      CTFR field value
 */
#define USBD_ReadEPRxFlag(ep)        (USBD->EP[ep].EP_B.CTFR)

/*!
 * @brief       Read CTFT field value in EP register
 *
 * @param       ep: Endpoint number
 *
 * @retval      CTFT field value
 */
#define USBD_ReadEPTxFlag(ep)        (USBD->EP[ep].EP_B.CTFT)

/*!
 * @brief       Enable USBD peripheral
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_Enable()                (USBD->ADDR_B.USBDEN = BIT_SET)

/*!
 * @brief       Disable USBD peripheral
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_Disable()               (USBD->ADDR_B.USBDEN = BIT_RESET)

/*!
 * @brief       Enable USBD2 peripheral
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD2_Enable()               (USBD->USB_SWITCH = BIT_SET)

/*!
 * @brief       Disable USBD2 peripheral
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD2_Disable()              (USBD->USB_SWITCH = BIT_RESET)

/*!
 * @brief       Read RXDPSTS field value in FRANUM register
 *
 * @param       None
 *
 * @retval      RXDPSTS field value
 */
#define USBD_ReadRDPS()              (USBD->FRANUM_B.RXDPSTS)

/*!
 * @brief       Read RXDMSTS field value in FRANUM register
 *
 * @param       None
 *
 * @retval      RXDMSTS field value
 */
#define USBD_ReadRDMS()              (USBD->FRANUM_B.RXDMSTS)

/*!
 * @brief       Read LOCK field value in FRANUM register
 *
 * @param       None
 *
 * @retval      LOCK field value
 */
#define USBD_ReadLOCK()              (USBD->FRANUM_B.LOCK)

/*!
 * @brief       Read LSOFNUM field value in FRANUM register
 *
 * @param       None
 *
 * @retval      LSOFNUM field value
 */
#define USBD_ReadLSOF()              (USBD->FRANUM_B.LSOFNUM)

/*!
 * @brief       Read FRANUM field value in FRANUM register
 *
 * @param       None
 *
 * @retval      FRANUM field value
 */
#define USBD_ReadFRANUM()              (USBD->FRANUM_B.FRANUM)

/**@} end of group USBD_Macros */

/** @defgroup USBD_Enumerations Enumerations
  @{
*/

/**
 * @brief   USBD Endpoint register bit definition
 */
typedef enum
{
    USBD_EP_BIT_ADDR     = (uint32_t)(BIT0 | BIT1 | BIT2 | BIT3),
    USBD_EP_BIT_TXSTS    = (uint32_t)(BIT4 | BIT5),
    USBD_EP_BIT_TXDTOG   = (uint32_t)(BIT6),
    USBD_EP_BIT_CTFT     = (uint32_t)(BIT7),
    USBD_EP_BIT_KIND     = (uint32_t)(BIT8),
    USBD_EP_BIT_TYPE     = (uint32_t)(BIT9 | BIT10),
    USBD_EP_BIT_SETUP    = (uint32_t)(BIT11),
    USBD_EP_BIT_RXSTS    = (uint32_t)(BIT12 | BIT13),
    USBD_EP_BIT_RXDTOG   = (uint32_t)(BIT14),
    USBD_EP_BIT_CTFR     = (uint32_t)(BIT15)
}USBD_EP_BIT_T;

/**
 * @brief   Endpoint id
 */
typedef enum
{
    USBD_EP_0,
    USBD_EP_1,
    USBD_EP_2,
    USBD_EP_3,
    USBD_EP_4,
    USBD_EP_5,
    USBD_EP_6,
    USBD_EP_7
}USBD_EP_T;

/**
 * @brief   Endpoint status
 */
typedef enum
{
    USBD_EP_STATUS_DISABLE   = ((uint32_t)0),
    USBD_EP_STATUS_STALL     = ((uint32_t)1),
    USBD_EP_STATUS_NAK       = ((uint32_t)2),
    USBD_EP_STATUS_VALID     = ((uint32_t)3)
}USBD_EP_STATUS_T;

/**
 * @brief   USBD Endpoint type
 */
typedef enum
{
    USBD_EP_TYPE_BULK,
    USBD_EP_TYPE_CONTROL,
    USBD_EP_TYPE_ISO,
    USBD_EP_TYPE_INTERRUPT
}USBD_EP_TYPE_T;

/**@} end of group USBD_Enumerations */

/** @defgroup USBD_Functions Functions
  @{
*/

void USBD_SetEPType(USBD_EP_T ep, USBD_EP_TYPE_T type);

void USBD_SetEPKind(USBD_EP_T ep);
void USBD_ResetEPKind(USBD_EP_T ep);

void USBD_ResetEPRxFlag(USBD_EP_T ep);
void USBD_ResetEPTxFlag(USBD_EP_T ep);

void USBD_ToggleTx(USBD_EP_T ep);
void USBD_ToggleRx(USBD_EP_T ep);
void USBD_ResetTxToggle(USBD_EP_T ep);
void USBD_ResetRxToggle(USBD_EP_T ep);

void USBD_SetEpAddr(USBD_EP_T ep, uint8_t addr);

void USBD_SetEPTxStatus(USBD_EP_T ep, USBD_EP_STATUS_T status);
void USBD_SetEPRxStatus(USBD_EP_T ep, USBD_EP_STATUS_T status);
void USBD_SetEPRxTxStatus(USBD_EP_T ep, USBD_EP_STATUS_T txStatus, USBD_EP_STATUS_T rxStatus);

void USBD_SetEPRxCnt(USBD_EP_T ep, uint32_t cnt);

void USBD_WriteDataToEP(USBD_EP_T ep, uint8_t *wBuf, uint32_t wLen);
void USBD_ReadDataFromEP(USBD_EP_T ep, uint8_t *rBuf, uint32_t rLen);

/**@} end of group USBD_Functions */
/**@} end of group USBD_Driver */
/**@} end of group APM32E10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_USBD_H */
