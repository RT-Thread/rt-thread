/*********************************************************************************************************//**
 * @file    ht32f1xxxx_usbd.h
 * @version $Rev:: 1670         $
 * @date    $Date:: 2019-04-09 #$
 * @brief   The header file of the USB Device Driver.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F1XXXX_USBD_H
#define __HT32F1XXXX_USBD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f1xxxx_01_usbdconf.h"
#include "ht32f1xxxx_usbdinit.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup USBDevice USB Device
  * @brief USB Device driver modules
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
/** @defgroup USBDevice_Settings USB Device settings
  * @{
  */
#define MAX_EP_NUM                  (8)
/**
  * @}
  */

/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup USBDevice_Exported_Types USB Device exported types
  * @{
  */
/* USB Endpoint number                                                                                      */
typedef enum
{
  USBD_EPT0  = 0,
  USBD_EPT1  = 1,
  USBD_EPT2  = 2,
  USBD_EPT3  = 3,
  USBD_EPT4  = 4,
  USBD_EPT5  = 5,
  USBD_EPT6  = 6,
  USBD_EPT7  = 7,
  USBD_NOEPT = -1,
} USBD_EPTn_Enum;

typedef enum
{
  USBD_TCR_0 = 0,
  USBD_TCR_1 = 16,
} USBD_TCR_Enum;

typedef enum
{
  USBD_NAK = 0,
  USBD_ACK = 1
} USBD_Handshake_Enum;

/* Endpoint CFGR Register                                                                                   */
typedef struct _EPTCFGR_BIT
{
  vu32 EPBUFA: 10;
  vu32 EPLEN : 10;
  vu32 _RES0 :  3;
  vu32 SDBS  :  1;
  vu32 EPADR :  4;
  vu32 EPDIR :  1;
  vu32 EPTYPE:  1;
  vu32 _RES1 :  1;
  vu32 EPEN  :  1;
} USBD_EPTCFGR_Bit;

typedef union _EPTCFGR_TYPEDEF
{
  USBD_EPTCFGR_Bit bits;
  u32 word;
} USBD_EPTCFGR_TypeDef;

/* Endpoint CFGR and IER Register                                                                           */
typedef struct
{
  USBD_EPTCFGR_TypeDef CFGR;
  u32 IER;
} USBD_EPTInit_TypeDef;

/* Endpoint 0 ~ MAX_EP_NUM                                                                                  */
typedef struct
{
  u32 uInterruptMask;
  USBD_EPTInit_TypeDef ept[MAX_EP_NUM];
} USBD_Driver_TypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup USBDevice_Exported_Constants USB Device exported constants
  * @{
  */

/* USB Interrupt Enable Register (USBIER)                                                                   */
#define UGIE                        ((u32)0x00000001)   /*!< USB global Interrupt Enable                    */
#define SOFIE                       ((u32)0x00000002)   /*!< Start Of Frame Interrupt Enable                */
#define URSTIE                      ((u32)0x00000004)   /*!< USB Reset Interrupt Enable                     */
#define RSMIE                       ((u32)0x00000008)   /*!< Resume Interrupt Enable                        */
#define SUSPIE                      ((u32)0x00000010)   /*!< Suspend Interrupt Enable                       */
#define ESOFIE                      ((u32)0x00000020)   /*!< Expected Start Of Frame Interrupt Enable       */
#define FRESIE                      ((u32)0x00000040)   /*!< Force USB Reset Control Interrupt Enable       */
#define EP0IE                       ((u32)0x00000100)   /*!< Endpoint 0 Interrupt Enable                    */
#define EP1IE                       ((u32)0x00000200)   /*!< Endpoint 1 Interrupt Enable                    */
#define EP2IE                       ((u32)0x00000400)   /*!< Endpoint 2 Interrupt Enable                    */
#define EP3IE                       ((u32)0x00000800)   /*!< Endpoint 3 Interrupt Enable                    */
#define EP4IE                       ((u32)0x00001000)   /*!< Endpoint 4 Interrupt Enable                    */
#define EP5IE                       ((u32)0x00002000)   /*!< Endpoint 5 Interrupt Enable                    */
#define EP6IE                       ((u32)0x00004000)   /*!< Endpoint 6 Interrupt Enable                    */
#define EP7IE                       ((u32)0x00008000)   /*!< Endpoint 7 Interrupt Enable                    */

/* USB Interrupt Status Register (USBISR)                                                                   */
#define SOFIF                       ((u32)0x00000002)   /*!< Start Of Frame Interrupt Flag                  */
#define URSTIF                      ((u32)0x00000004)   /*!< USB Reset Interrupt Flag                       */
#define RSMIF                       ((u32)0x00000008)   /*!< Resume Interrupt Flag                          */
#define SUSPIF                      ((u32)0x00000010)   /*!< Suspend Interrupt Flag                         */
#define ESOFIF                      ((u32)0x00000020)   /*!< Expected Start Of Frame Interrupt Flag         */
#define FRESIF                      ((u32)0x00000040)   /*!< Force USB Reset Control Interrupt Flag         */
#define EP0IF                       ((u32)0x00000100)   /*!< Endpoint 0 Interrupt flag                      */
#define EP1IF                       ((u32)0x00000200)   /*!< Endpoint 1 Interrupt flag                      */
#define EP2IF                       ((u32)0x00000400)   /*!< Endpoint 2 Interrupt flag                      */
#define EP3IF                       ((u32)0x00000800)   /*!< Endpoint 3 Interrupt flag                      */
#define EP4IF                       ((u32)0x00001000)   /*!< Endpoint 4 Interrupt flag                      */
#define EP5IF                       ((u32)0x00002000)   /*!< Endpoint 5 Interrupt flag                      */
#define EP6IF                       ((u32)0x00004000)   /*!< Endpoint 6 Interrupt flag                      */
#define EP7IF                       ((u32)0x00008000)   /*!< Endpoint 7 Interrupt flag                      */
#define EPnIF                       ((u32)0x0000FF00)   /*!< Endpoint n Interrupt flag                      */

/* USB Endpoint n Interrupt Enable Register (USBEPnIER)                                                     */
#define OTRXIE                      ((u32)0x00000001)   /*!< OUT Token Received Interrupt Enable            */
#define ODRXIE                      ((u32)0x00000002)   /*!< OUT Data Received Interrupt Enable             */
#define ODOVIE                      ((u32)0x00000004)   /*!< OUT Data Buffer Overrun Interrupt Enable       */
#define ITRXIE                      ((u32)0x00000008)   /*!< IN Token Received Interrupt Enable             */
#define IDTXIE                      ((u32)0x00000010)   /*!< IN Data Transmitted Interrupt Enable           */
#define NAKIE                       ((u32)0x00000020)   /*!< NAK Transmitted Interrupt Enable               */
#define STLIE                       ((u32)0x00000040)   /*!< STALL Transmitted Interrupt Enable             */
#define UERIE                       ((u32)0x00000080)   /*!< USB Error Interrupt Enable                     */
#define STRXIE                      ((u32)0x00000100)   /*!< SETUP Token Received Interrupt Enable          */
#define SDRXIE                      ((u32)0x00000200)   /*!< SETUP Data Received Interrupt Enable           */
#define SDERIE                      ((u32)0x00000400)   /*!< SETUP Data Error Interrupt Enable              */
#define ZLRXIE                      ((u32)0x00000800)   /*!< Zero Length Data Received Interrupt Enable     */

/* USB Endpoint n Interrupt Status Register (USBEPnISR)                                                     */
#define OTRXIF                      ((u32)0x00000001)   /*!< OUT Token Received Interrupt Flag              */
#define ODRXIF                      ((u32)0x00000002)   /*!< OUT Data Received Interrupt Flag               */
#define ODOVIF                      ((u32)0x00000004)   /*!< OUT Data Buffer Overrun Interrupt Flag         */
#define ITRXIF                      ((u32)0x00000008)   /*!< IN Token Received Interrupt Flag               */
#define IDTXIF                      ((u32)0x00000010)   /*!< IN Data Transmitted Interrupt Flag             */
#define NAKIF                       ((u32)0x00000020)   /*!< NAK Transmitted Interrupt Flag                 */
#define STLIF                       ((u32)0x00000040)   /*!< STALL Transmitted Interrupt Flag               */
#define UERIF                       ((u32)0x00000080)   /*!< USB Error Interrupt Flag                       */
#define STRXIF                      ((u32)0x00000100)   /*!< SETUP Token Received Interrupt Flag            */
#define SDRXIF                      ((u32)0x00000200)   /*!< SETUP Data Received Interrupt Flag             */
#define SDERIF                      ((u32)0x00000400)   /*!< SETUP Data Error Interrupt Flag                */
#define ZLRXIF                      ((u32)0x00000800)   /*!< Zero Length Data Received Interrupt Flag       */

/* USB Endpoint n Control and Status Register (USBEPnCSR)                                                   */
#define DTGTX                       ((u32)0x00000001)   /*!< Data Toggle Status, for IN transfer            */
#define NAKTX                       ((u32)0x00000002)   /*!< NAK Status, for IN transfer                    */
#define STLTX                       ((u32)0x00000004)   /*!< STALL Status, for IN transfer                  */
#define DTGRX                       ((u32)0x00000008)   /*!< Data Toggle Status, for OUT transfer           */
#define NAKRX                       ((u32)0x00000010)   /*!< NAK Status, for OUT transfer                   */
#define STLRX                       ((u32)0x00000020)   /*!< STALL Status, for OUT transfer                 */

/* For USBD_EPTGetTranssferCount function                                                                   */
#define USBD_CNTB0                  (USBD_TCR_0)
#define USBD_CNTB1                  (USBD_TCR_1)
#define USBD_CNTIN                  (USBD_TCR_0)
#define USBD_CNTOUT                 (USBD_TCR_1)
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------------------------------------*/
/** @defgroup USBDevice_Exported_Macro USB Device exported macro
  * @{
  */
/* API macro for USB Core - Global event and operation                                                      */
#define API_USB_INIT(driver)                      (USBD_Init(driver))
#define API_USB_DEINIT()                          (USBD_DeInit())
#define API_USB_POWER_UP(driver, power)           (USBD_PowerUp(driver, power))
#define API_USB_POWER_OFF()                       (USBD_PowerOff())
#define API_USB_POWER_ON()                        (USBD_PowerOn())
#define API_USB_REMOTE_WAKEUP()                   (USBD_RemoteWakeup())
#define API_USB_READ_SETUP(buffer)                (USBD_ReadSETUPData((u32 *)(buffer)))
#define API_USB_SET_ADDR(addr)                    (USBD_SetAddress(addr))
#define API_USB_GET_CTRL_IN_LEN()                 (USBD_EPTGetBufferLen(USBD_EPT0))
#define API_USB_ENABLE_INT(flag)                  (USBD_EnableINT(flag))
#define API_USB_GET_INT()                         (USBD_GetINT())
#define API_USB_GET_EPT_NUM(flag)                 (USBD_GetEPTnINTNumber(flag))
#define API_USB_IS_SETUP_INT(flag)                (flag & SDRXIF)
#define API_USB_CLR_SETUP_INT()                   (USBD_EPTClearINT(USBD_EPT0, SDRXIF))
#define API_USB_IS_RESET_INT(flag)                (flag & URSTIF)
#define API_USB_CLR_RESET_INT()                   (USBD_ClearINT(URSTIF))
#define API_USB_IS_SOF_INT(flag)                  (flag & SOFIF)
#define API_USB_CLR_SOF_INT()                     (USBD_ClearINT(SOFIF))
#define API_USB_IS_FRES_INT(flag)                 (flag & FRESIF)
#define API_USB_CLR_FRES_INT()                    (USBD_ClearINT(FRESIF))
#define API_USB_IS_RESUME_INT(flag)               (flag & RSMIF)
#define API_USB_CLR_RESUME_INT()                  (USBD_ClearINT(RSMIF))
#define API_USB_IS_SUSPEND_INT(flag)              (flag & SUSPIF)
#define API_USB_CLR_SUSPEND_INT()                 (USBD_ClearINT(SUSPIF))
#define API_USB_IS_EPTn_INT(flag, EPTn)           (flag & (EP0IF << EPTn))
#define API_USB_CLR_EPTn_INT(EPTn)                (USBD_ClearINT(EP0IF << EPTn))

/* API macro for USB Core - Endpoint event and operation                                                    */
#define API_USB_EPTn_INIT(EPTn, driver)           (USBD_EPTInit(EPTn, driver))
#define API_USB_EPTn_RESET(EPTn)                  (USBD_EPTReset(EPTn))
#define API_USB_EPTn_SEND_STALL(EPTn)             (USBD_EPTSendSTALL(EPTn))
#define API_USB_EPTn_GET_INT(EPTn)                (USBD_EPTGetINT(EPTn))
#define API_USB_EPTn_IS_IN_INT(flag)              (flag & IDTXIF)
#define API_USB_EPTn_CLR_IN_INT(EPTn)             (USBD_EPTClearINT(EPTn, IDTXIF))
#define API_USB_EPTn_IS_OUT_INT(flag)             (flag & ODRXIF)
#define API_USB_EPTn_CLR_OUT_INT(EPTn)            (USBD_EPTClearINT(EPTn, ODRXIF))
#define API_USB_EPTn_IS_INT(flag)                 (flag & (ODRXIF | IDTXIF))
#define API_USB_EPTn_CLR_INT(EPTn)                (USBD_EPTClearINT(EPTn, (ODRXIF | IDTXIF)))
#define API_USB_EPTn_GET_HALT(EPTn)               (USBD_EPTGetHalt(EPTn))
#define API_USB_EPTn_SET_HALT(EPTn)               (USBD_EPTSetHalt(EPTn))
#define API_USB_EPTn_CLR_HALT(EPTn)               (USBD_EPTClearHalt(EPTn))
#define API_USB_EPTn_WAIT_STALL_SENT(EPTn)        (USBD_EPTWaitSTALLSent(EPTn))
#define API_USB_EPTn_CLR_DTG(EPTn)                (USBD_EPTClearDTG(EPTn))
#define API_USB_EPTn_GET_BUFFLEN(EPTn)            (USBD_EPTGetBufferLen(EPTn))
#define API_USB_EPTn_GET_CNT(EPTn, type)          (USBD_EPTGetTransferCount(EPTn, type))
#define API_USB_EPTn_WRITE_IN(EPTn, from, len)    (USBD_EPTWriteINData(EPTn, from, len))
#define API_USB_EPTn_READ_OUT(EPTn, to, len)      (USBD_EPTReadOUTData(EPTn, to, len))
#define API_USB_EPTn_READ_MEM(EPTn, to, len)      (USBD_EPTReadMemory(EPTn, to, len))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup USBDevice_Exported_Functions USB Device exported functions
  * @{
  */
void USBD_Init(u32 *pDriver);
void USBD_PreInit(USBD_Driver_TypeDef *pDriver);
void USBD_DPpullupCmd(ControlStatus NewState);
void USBD_DPWakeUpCmd(ControlStatus NewState);
void USBD_DeInit(void);
void USBD_PowerUp(u32 *pDriver, u32 uIsSelfPowered);
void USBD_PowerOff(void);
void USBD_PowerOn(void);
void USBD_SRAMResetConditionCmd(ControlStatus NewState);
void USBD_DisableDefaultPull(void);
void USBD_RemoteWakeup(void);
void USBD_ReadSETUPData(u32 *pBuffer);
void USBD_SetAddress(u32 address);
void USBD_EnableINT(u32 INTFlag);
void USBD_DisableINT(u32 INTFlag);
u32  USBD_GetINT(void);
void USBD_ClearINT(u32 INTFlag);
USBD_EPTn_Enum USBD_GetEPTnINTNumber(u32 INTFlag);

void USBD_EPTInit(USBD_EPTn_Enum USBD_EPTn, u32 *pDriver);
void USBD_EPTReset(USBD_EPTn_Enum USBD_EPTn);
void USBD_EPTEnableINT(USBD_EPTn_Enum USBD_EPTn, u32 INTFlag);
u32  USBD_EPTGetINT(USBD_EPTn_Enum USBD_EPTn);
void USBD_EPTClearINT(USBD_EPTn_Enum USBD_EPTn, u32 INTFlag);
void USBD_EPTSendSTALL(USBD_EPTn_Enum USBD_EPTn);
u32  USBD_EPTGetHalt(USBD_EPTn_Enum USBD_EPTn);
void USBD_EPTSetHalt(USBD_EPTn_Enum USBD_EPTn);
void USBD_EPTClearHalt(USBD_EPTn_Enum USBD_EPTn);
void USBD_EPTWaitSTALLSent(USBD_EPTn_Enum USBD_EPTn);
void USBD_EPTClearDTG(USBD_EPTn_Enum USBD_EPTn);
u32  USBD_EPTGetBuffer0Addr(USBD_EPTn_Enum USBD_EPTn);
u32  USBD_EPTGetBuffer1Addr(USBD_EPTn_Enum USBD_EPTn);
u32  USBD_EPTGetBufferLen(USBD_EPTn_Enum USBD_EPTn);
u32  USBD_EPTGetTransferCount(USBD_EPTn_Enum USBD_EPTn, USBD_TCR_Enum USBD_TCR_0or1);
u32  USBD_EPTWriteINData(USBD_EPTn_Enum USBD_EPTn, u32 *pFrom, u32 len);
u32  USBD_EPTReadOUTData(USBD_EPTn_Enum USBD_EPTn, u32 *pTo, u32 len);
u32  USBD_EPTReadMemory(USBD_EPTn_Enum USBD_EPTn, u32 *pTo, u32 len);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
