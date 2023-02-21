/*!
 * @file        drv_usb_device.h
 *
 * @brief       This file contains all the prototypes,enumeration and macros for USBD peripheral
 *
 * @version     V1.0.1
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
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
#ifndef __DRV_USB_DEVICE_H_
#define __DRV_USB_DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(APM32F070xB) || defined(APM32F072x8) || defined(APM32F072xB)
#define APM32F0xx_USB
#endif

/* Includes */
#ifdef APM32F0xx_USB
#include "apm32f0xx.h"
#include "apm32f0xx_pmu.h"
#include "apm32f0xx_eint.h"
#include "apm32f0xx_gpio.h"
#include "apm32f0xx_rcm.h"
#include "apm32f0xx_misc.h"
#include "usb_config.h"
#endif

/** @addtogroup USB_Driver_Library USB Driver Library
  @{
*/

/** @addtogroup USBD_Driver
  @{
*/

/** @defgroup Driver_Macros Macros
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

/**@} end of group Driver_Macros */

/** @defgroup Driver_Macros_Functions Macros Functions
  @{
*/

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
#define USBD2_Enable()               (USBD->SWITCH = BIT_SET)

/*!
 * @brief       Disable USBD2 peripheral
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD2_Disable()              (USBD->SWITCH = BIT_RESET)

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

#ifdef APM32F0xx_USB
/*!
 * @brief       Read EP Tx address pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx address pointer
 */
#define USBD_ReadEPTxAddrPointer(ep) (uint16_t *)((USBD->BUFFTB + ep * 8) + USBD_PMA_ADDR)

/*!
 * @brief       Read EP Tx count pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx count pointer
 */
#define USBD_ReadEPTxCntPointer(ep)  (uint16_t *)((USBD->BUFFTB + ep * 8 + 2) + USBD_PMA_ADDR)

/*!
 * @brief       Read EP Rx address pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx address pointer
 */
#define USBD_ReadEPRxAddrPointer(ep) (uint16_t *)((USBD->BUFFTB + ep * 8 + 4) + USBD_PMA_ADDR)

/*!
 * @brief       Read EP Rx count pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx count pointer
 */
#define USBD_ReadEPRxCntPointer(ep)  (uint16_t *)((USBD->BUFFTB + ep * 8 + 6) + USBD_PMA_ADDR)

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
 * @brief       Read EP Tx Buffer Pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx Buffer Pointer
 */
#define USBD_ReadEPTxBufferPointer(ep)   (uint16_t *)(USBD_ReadEPTxAddr(ep) + USBD_PMA_ADDR)

/*!
 * @brief       Read EP Rx Buffer Pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx Buffer Pointer
 */
#define USBD_ReadEPRxBufferPointer(ep)   (uint16_t *)(USBD_ReadEPRxAddr(ep) + USBD_PMA_ADDR)

/*!
 * @brief       Set EP Tx Count
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
 * @brief       Set BESL Value
 *
 * @param       val: 4-bits BESL Value to be set
 *
 * @retval      None
 */
#define USBD_SetBESL(val)            (USBD->LPMCTRLSTS_B.BESL = val)

/*!
 * @brief       Set bRemoteWakew Value
 *
 * @param       val: 1-bit bRemoteWakew Value to be set
 *
 * @retval      None
 */
#define USBD_SetRemoteWakeVal(val)   (USBD->LPMCTRLSTS_B.REMWAKE = val)

/*!
 * @brief       Enable LPM ACK
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_EnableAckLPM()          (USBD->LPMCTRLSTS_B.LPMACKEN = 1)

/*!
 * @brief       Disable LPM ACK
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_DisableAckLPM()         (USBD->LPMCTRLSTS_B.LPMACKEN = 0)

/*!
 * @brief       Disable LPM
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_EnableLPM()             (USBD->LPMCTRLSTS_B.LPMEN = 1)

/*!
 * @brief       Disable LPM
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_DisableLPM()            (USBD->LPMCTRLSTS_B.LPMEN = 0)

/*!
 * @brief       Enable Pull-up of DP line
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_EnablePullUpDP()        (USBD->BCD_B.DPPUCTRL = 1)

/*!
 * @brief       Disable Pull-up of DP line
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_DisablePullUpDP()       (USBD->BCD_B.DPPUCTRL = 0)

/*!
 * @brief       Read DM Pull-up Detection Status Flag
 *
 * @param       None
 *
 * @retval      DM Pull-up Detection Status Flag
 */
#define USBD_DMPullUpStatus()        (USBD->BCD_B.DMPUDFLG)

/*!
 * @brief       Read Secondary Detection Status Flag
 *
 * @param       None
 *
 * @retval      Secondary Detection Status Flag
 */
#define USBD_SDStatus()              (USBD->BCD_B.SDFLG)

/*!
 * @brief       Read Primary Detection Status Flag
 *
 * @param       None
 *
 * @retval      Primary Detection Status Flag
 */
#define USBD_PDStatus()              (USBD->BCD_B.PDFLG)

/*!
 * @brief       Read Data Contact Detection Status Flag
 *
 * @param       None
 *
 * @retval      Data Contact Detection Status Flag
 */
#define USBD_DCDStatus()             (USBD->BCD_B.DCDFLG)

/*!
 * @brief       Enable Secondary Detection Mode
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_EnableSDMode()          (USBD->BCD_B.SDEN = 1)

/*!
 * @brief       Disable Secondary Detection Mode
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_DisableSDMode()         (USBD->BCD_B.SDEN = 0)

/*!
 * @brief       Enable Primary Detection Mode
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_EnablePDMode()          (USBD->BCD_B.PDEN = 1)

/*!
 * @brief       Disable Primary Detection Mode
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_DisablePDMode()         (USBD->BCD_B.PDEN = 0)

/*!
 * @brief       Enable Data Contact Detection Mode
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_EnableDCDMode()         (USBD->BCD_B.DCDEN = 1)

/*!
 * @brief       Disable Data Contact Detection Mode
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_DisableDCDMode()        (USBD->BCD_B.DCDEN = 0)

/*!
 * @brief       Enable Battery Charging Detector
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_EnableBCD()             (USBD->BCD_B.BCDEN = 1)

/*!
 * @brief       Disable Battery Charging Detector
 *
 * @param       None
 *
 * @retval      None
 */
#define USBD_DisableBCD()            (USBD->BCD_B.BCDEN = 0)

#else //!< APM32F10x_USB
/*!
 * @brief       Read EP Tx address pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx address pointer
 */
#define USBD_ReadEPTxAddrPointer(ep) (uint16_t *)((USBD->BUFFTB + ep * 8) * 2 + USBD_PMA_ADDR)

/*!
 * @brief       Read EP Tx count pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx count pointer
 */
#define USBD_ReadEPTxCntPointer(ep)  (uint16_t *)((USBD->BUFFTB + ep * 8 + 2) * 2 + USBD_PMA_ADDR)

/*!
 * @brief       Read EP Rx address pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx address pointer
 */
#define USBD_ReadEPRxAddrPointer(ep) (uint16_t *)((USBD->BUFFTB + ep * 8 + 4) * 2 + USBD_PMA_ADDR)

/*!
 * @brief       Read EP Rx count pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx count pointer
 */
#define USBD_ReadEPRxCntPointer(ep)  (uint16_t *)((USBD->BUFFTB + ep * 8 + 6) * 2 + USBD_PMA_ADDR)

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
 * @brief       Read EP Tx Buffer Pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Tx Buffer Pointer
 */
#define USBD_ReadEPTxBufferPointer(ep)   (uint32_t *)(((uint32_t)USBD_ReadEPTxAddr(ep) << 1) + USBD_PMA_ADDR)

/*!
 * @brief       Read EP Rx Buffer Pointer
 *
 * @param       ep:     EP number
 *
 * @retval      EP Rx Buffer Pointer
 */
#define USBD_ReadEPRxBufferPointer(ep)   (uint32_t *)(((uint32_t)USBD_ReadEPRxAddr(ep) << 1) + USBD_PMA_ADDR)

/*!
 * @brief       Set EP Tx Count
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

#endif

/**@} end of group Driver_Macros_Functions */

/** @defgroup Driver_Enumerations Enumerations
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
} USBD_EP_BIT_T;

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
    USBD_EP_7,
} USBD_EP_T;

/**
 * @brief   Endpoint status
 */
typedef enum
{
    USBD_EP_STATUS_DISABLE   = ((uint32_t)0),
    USBD_EP_STATUS_STALL     = ((uint32_t)1),
    USBD_EP_STATUS_NAK       = ((uint32_t)2),
    USBD_EP_STATUS_VALID     = ((uint32_t)3),
} USBD_EP_STATUS_T;

/**
 * @brief   USBD Endpoint type for register
 */
typedef enum
{
    USBD_REG_EP_TYPE_BULK,
    USBD_REG_EP_TYPE_CONTROL,
    USBD_REG_EP_TYPE_ISO,
    USBD_REG_EP_TYPE_INTERRUPT
} USBD_REG_EP_TYPE_T;

/**@} end of group Driver_Enumerations */

/** @defgroup Driver_Functions Functions
  @{
*/

void USBD_SetEPType(uint8_t ep, USBD_REG_EP_TYPE_T type);

void USBD_SetEPKind(uint8_t ep);
void USBD_ResetEPKind(uint8_t ep);

void USBD_ResetEPRxFlag(uint8_t ep);
void USBD_ResetEPTxFlag(uint8_t ep);

void USBD_ToggleTx(uint8_t ep);
void USBD_ToggleRx(uint8_t ep);
void USBD_ResetTxToggle(uint8_t ep);
void USBD_ResetRxToggle(uint8_t ep);

void USBD_SetEpAddr(uint8_t ep, uint8_t addr);

void USBD_SetEPTxStatus(uint8_t ep, USBD_EP_STATUS_T status);
void USBD_SetEPRxStatus(uint8_t ep, USBD_EP_STATUS_T status);
void USBD_SetEPTxRxStatus(uint8_t ep, USBD_EP_STATUS_T txStatus, USBD_EP_STATUS_T rxStatus);

void USBD_SetEPRxCnt(uint8_t ep, uint32_t cnt);

void USBD_WriteDataToEP(uint8_t ep, uint8_t* wBuf, uint32_t wLen);
void USBD_ReadDataFromEP(uint8_t ep, uint8_t* rBuf, uint32_t rLen);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_USB_DEVICE_H */

/**@} end of group Driver_Functions */
/**@} end of group USBD_Driver */
/**@} end of group USB_Driver_Library */
