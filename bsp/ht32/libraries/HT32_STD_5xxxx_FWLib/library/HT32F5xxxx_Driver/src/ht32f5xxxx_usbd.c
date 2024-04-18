/*********************************************************************************************************//**
 * @file    ht32f5xxxx_usbd.c
 * @version $Rev:: 7335         $
 * @date    $Date:: 2023-11-09 #$
 * @brief   The USB Device Peripheral Driver.
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32f5xxxx_usbdchk.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup USBDevice USB Device
  * @brief USB Device driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup USBDevice_Private_Constant USB Device private constants
  * @{
  */
#define TCR_MASK                    (0x1FF)
#define EPLEN_MASK                  ((u32)0x000FFC00)
#define EPBUFA_MASK                 ((u32)0x000003FF)
#define ISR_EPn_OFFSET              (8)

/* USB Control and Status Register (USBCSR)                                                                 */
#define FRES                        ((u32)0x00000002)   /* Force USB Reset                                  */
#define PDWN                        ((u32)0x00000004)   /* Power Down                                       */
#define LPMODE                      ((u32)0x00000008)   /* Low-power Mode                                   */
#define GENRSM                      ((u32)0x00000020)   /* Generate Resume                                  */
#define ADRSET                      ((u32)0x00000100)   /* Device Address Setting                           */
#define SRAMRSTC                    ((u32)0x00000200)   /* USB SRAM reset condition                         */
#define DPPUEN                      ((u32)0x00000400)   /* DP Pull Up Enable                                */
#define DPWKEN                      ((u32)0x00000800)   /* DP Wake Up Enable                                */

#define EPDIR_IN                    (1)
#define EPDIR_OUT                   (0)
/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/
/** @defgroup USBDevice_Private_Variable USB Device private variables
  * @{
  */
static u32 gIsFirstPowered = TRUE;
/**
  * @}
  */

/* Private macro -------------------------------------------------------------------------------------------*/
/** @defgroup USBDevice_Private_Macro USB Device private macros
  * @{
  */
#ifndef USBDCore_LowPower
  #define USBDCore_LowPower()      PWRCU_DeepSleep1(PWRCU_SLEEP_ENTRY_WFE)
#endif
/**
 * @brief Convert Byte length to Word length
 */
#define ByteLen2WordLen(n)      ((n + 3) >> 2)
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
static void _USBD_CopyMemory(u32 *pFrom, u32 *pTo, u32 len);
static HT_USBEP_TypeDef * _USBD_GetEPTnAddr(USBD_EPTn_Enum USBD_EPTn);
static void _delay(u32 nCount);

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup USBDevice_Exported_Functions USB Device exported functions
  * @{
  */
/*********************************************************************************************************//**
  * @brief  Pre initialization for USBD_Init function.
  * @param  pDriver: USB initialization structure
  * @retval None
  ***********************************************************************************************************/
void USBD_PreInit(USBD_Driver_TypeDef *pDriver)
{
  pDriver->uInterruptMask = _UIER_ALL;

  pDriver->ept[USBD_EPT0].CFGR.word = _EP0_CFG;
  pDriver->ept[USBD_EPT0].IER       = _EP0_IER;

  #if (_EP1_ENABLE == 1)
  pDriver->ept[USBD_EPT1].CFGR.word = _EP1_CFG;
  pDriver->ept[USBD_EPT1].IER       = _EP1_IER;
  #endif

  #if (_EP2_ENABLE == 1)
  pDriver->ept[USBD_EPT2].CFGR.word = _EP2_CFG;
  pDriver->ept[USBD_EPT2].IER       = _EP2_IER;
  #endif

  #if (_EP3_ENABLE == 1)
  pDriver->ept[USBD_EPT3].CFGR.word = _EP3_CFG;
  pDriver->ept[USBD_EPT3].IER       = _EP3_IER;
  #endif

  #if (_EP4_ENABLE == 1)
  pDriver->ept[USBD_EPT4].CFGR.word = _EP4_CFG;
  pDriver->ept[USBD_EPT4].IER       = _EP4_IER;
  #endif

  #if (_EP5_ENABLE == 1)
  pDriver->ept[USBD_EPT5].CFGR.word = _EP5_CFG;
  pDriver->ept[USBD_EPT5].IER       = _EP5_IER;
  #endif

  #if (_EP6_ENABLE == 1)
  pDriver->ept[USBD_EPT6].CFGR.word = _EP6_CFG;
  pDriver->ept[USBD_EPT6].IER       = _EP6_IER;
  #endif

  #if (_EP7_ENABLE == 1)
  pDriver->ept[USBD_EPT7].CFGR.word = _EP7_CFG;
  pDriver->ept[USBD_EPT7].IER       = _EP7_IER;
  #endif

  #if (LIBCFG_USBD_V2)
  #if (_EP8_ENABLE == 1)
  pDriver->ept[USBD_EPT8].CFGR.word = _EP8_CFG;
  pDriver->ept[USBD_EPT8].IER       = _EP8_IER;
  #endif

  #if (_EP9_ENABLE == 1)
  pDriver->ept[USBD_EPT9].CFGR.word = _EP9_CFG;
  pDriver->ept[USBD_EPT9].IER       = _EP9_IER;
  #endif
  #endif
  return;
}

/*********************************************************************************************************//**
  * @brief  USB Device Peripheral initialization.
  * @param  pDriver: USB initialization structure
  * @retval None
  ***********************************************************************************************************/
void USBD_Init(u32 *pDriver)
{
  USBD_Driver_TypeDef *pDrv = (USBD_Driver_TypeDef *)pDriver;

  /* Init USB Device Driver struct                                                                          */
  USBD_PreInit(pDrv);

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Device Internal DP pull up.
  * @param  NewState: ENABLE or DISABLE
  * @retval None
  ***********************************************************************************************************/
void USBD_DPpullupCmd(ControlStatus NewState)
{
  (NewState == ENABLE)?(HT_USB->CSR |= DPPUEN):(HT_USB->CSR &= ~DPPUEN);
}

/*********************************************************************************************************//**
  * @brief  USB Device Wake Up when DP is high level.
  * @param  NewState: ENABLE or DISABLE
  * @retval None
  ***********************************************************************************************************/
void USBD_DPWakeUpCmd(ControlStatus NewState)
{
  (NewState == ENABLE)?(HT_USB->CSR |= DPWKEN):(HT_USB->CSR &= ~DPWKEN);
}

/*********************************************************************************************************//**
  * @brief  USB Device Peripheral deinitialization.
  * @retval None
  ***********************************************************************************************************/
void USBD_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.USBD = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);

  return;
}

/*********************************************************************************************************//**
  * @brief  USB power up procedure.
  * @retval None
  ***********************************************************************************************************/
void USBD_PowerUp(u32 *pDriver, u32 uIsSelfPowered)
{
  USBD_Driver_TypeDef *pDrv = (USBD_Driver_TypeDef *)pDriver;

  if (gIsFirstPowered == TRUE)
  {
    gIsFirstPowered = FALSE;

    if (HT_USB->CSR & 0x40)
    {
      HT_USB->CSR = (DPPUEN | LPMODE | PDWN);
      while((HT_USB->ISR & URSTIE) == 0);
      HT_USB->ISR = 0xFFFFFFFF;
      if (uIsSelfPowered == FALSE)
      {
        USBDCore_LowPower();
      }
      USBD_EnableINT(pDrv->uInterruptMask);
    }
    else
    {
      HT_USB->CSR = (DPWKEN | DPPUEN | LPMODE | PDWN);
      while((HT_USB->ISR & URSTIE) == 0);
      HT_USB->ISR = 0xFFFFFFFF;
      if (uIsSelfPowered == FALSE)
      {
        USBDCore_LowPower();
      }
      USBD_DPWakeUpCmd(DISABLE);
      USBD_EnableINT(pDrv->uInterruptMask);
      USBD_DPpullupCmd(DISABLE);
      _delay(200);
      USBD_DPpullupCmd(ENABLE);
    }
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  Enter USB Device Power Down mode.
  * @retval None
  ***********************************************************************************************************/
void USBD_PowerOff(void)
{
  HT_USB->CSR |= (LPMODE | PDWN);
  return;
}

/*********************************************************************************************************//**
  * @brief  Exit USB Device Power Down mode.
  * @retval None
  ***********************************************************************************************************/
void USBD_PowerOn(void)
{
  HT_USB->CSR |= 0x00001000;
  HT_USB->CSR &= 0x00001400;
  return;
}

/*********************************************************************************************************//**
  * @brief  USB SRAM reset condition.
  * @param  NewState: ENABLE or DISABLE
  * @retval None
  ***********************************************************************************************************/
void USBD_SRAMResetConditionCmd(ControlStatus NewState)
{
  (NewState == ENABLE)?(HT_USB->CSR |= SRAMRSTC):(HT_USB->CSR &= ~SRAMRSTC);
}

/*********************************************************************************************************//**
  * @brief  Disable Default pull resistance of D+ and D-.
  * @retval None
  ***********************************************************************************************************/
void USBD_DisableDefaultPull(void)
{
  HT_USB->CSR = FRES; // Clear PDWN and keep FRES = 1
}

/*********************************************************************************************************//**
  * @brief  Generate a resume request to USB Host for Remote Wakeup function.
  * @retval None
  ***********************************************************************************************************/
void USBD_RemoteWakeup(void)
{
  HT_USB->CSR |= GENRSM;
  return;
}

/*********************************************************************************************************//**
  * @brief  Read Endpoint0 SETUP data from USB Buffer.
  * @param  pBuffer: Buffer for save SETUP data
  * @retval None
  ***********************************************************************************************************/
void USBD_ReadSETUPData(u32 *pBuffer)
{
  u32 *pSrc = (u32 *)HT_USB_SRAM_BASE;

  *pBuffer = *pSrc;
  *(pBuffer + 1) = *(pSrc + 1);
  return;
}

/*********************************************************************************************************//**
  * @brief  Set USB Device address.
  * @param  address: USB address which specified by Host
  * @retval None
  ***********************************************************************************************************/
void USBD_SetAddress(u32 address)
{
  HT_USB->CSR   |= ADRSET;
  HT_USB->DEVAR = address;
  return;
}

/*********************************************************************************************************//**
  * @brief  Enable USB Device interrupt.
  * @param  INTFlag: USB Device global interrupt flag
  *         @arg UGIE  | SOFIE  | URSTIE | RSMIE  | SUSPIE | ESOFIE
  *              EP0IE | EP1IE  | EP2IE  | EP3IE  | EP4IE  | EP5IE  | EP6IE  | EP7IE  | EP8IE  | EP9IE
  * @retval None
  ***********************************************************************************************************/
void USBD_EnableINT(u32 INTFlag)
{
  HT_USB->IER |= INTFlag;
  return;
}

/*********************************************************************************************************//**
  * @brief  Disable USB Device interrupt.
  * @param  INTFlag: USB Device global interrupt flag
  *         @arg UGIE  | SOFIE  | URSTIE | RSMIE  | SUSPIE | ESOFIE
  *              EP0IE | EP1IE  | EP2IE  | EP3IE  | EP4IE  | EP5IE  | EP6IE  | EP7IE  | EP8IE  | EP9IE
  * @retval None
  ***********************************************************************************************************/
void USBD_DisableINT(u32 INTFlag)
{
  HT_USB->IER &= (~INTFlag);
  return;
}

/*********************************************************************************************************//**
  * @brief  Get active USB Device interrupt flag.
  * @retval USB ISR Flag
  ***********************************************************************************************************/
u32 USBD_GetINT(void)
{
  u32 IER = HT_USB->IER | FRESIE;
  return (HT_USB->ISR & IER);
}

/*********************************************************************************************************//**
  * @brief  Clear USB Device interrupt flag.
  * @param  INTFlag: USB Device global interrupt flag
  *         @arg SOFIF | URSTIF | RSMIF | SUSPIF | ESOFIF
  *              EP0IF | EP1IF  | EP2IF | EP3IF  | EP4IF | EP5IF | EP6IF | EP7IF | EP8IF | EP9IF
  * @retval None
  ***********************************************************************************************************/
void USBD_ClearINT(u32 INTFlag)
{
  HT_USB->ISR = INTFlag;
  return;
}

/*********************************************************************************************************//**
  * @brief  Get USB Endpoint number by interrupt flag.
  * @param  INTFlag: USB Device global interrupt flag
  *         @arg SOFIF | URSTIF | RSMIF | SUSPIF | ESOFIF
  *              EP0IF | EP1IF  | EP2IF | EP3IF  | EP4IF | EP5IF | EP6IF | EP7IF | EP8IF | EP9IF
  * @retval USB Endpoint number from USBD_EPT1 ~ USBD_EPT9
  ***********************************************************************************************************/
USBD_EPTn_Enum USBD_GetEPTnINTNumber(u32 INTFlag)
{
  s32 i;
  for (i = MAX_EP_NUM - 1; i > 0; i--)
  {
    if ((INTFlag >> (i + ISR_EPn_OFFSET)) & SET)
    {
      return (USBD_EPTn_Enum)i;
    }
  }

  return USBD_NOEPT;
}

/*********************************************************************************************************//**
  * @brief  USB Device Peripheral initialization for Endpoint.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @param  pDriver: USB initialization structure
  * @retval None
  ***********************************************************************************************************/
void USBD_EPTInit(USBD_EPTn_Enum USBD_EPTn, u32 *pDriver)
{
  USBD_Driver_TypeDef *pDrv = (USBD_Driver_TypeDef *)pDriver;
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);

  USBEPn->CFGR = pDrv->ept[USBD_EPTn].CFGR.word;
  USBEPn->IER  = pDrv->ept[USBD_EPTn].IER;

  USBEPn->ISR = 0xFFFFFFFF;

  USBD_EPTReset(USBD_EPTn);

  return;
}

/*********************************************************************************************************//**
  * @brief  Reset Endpoint Status.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval None
  ***********************************************************************************************************/
void USBD_EPTReset(USBD_EPTn_Enum USBD_EPTn)
{
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);
  USBEPn->CSR = (USBEPn->CSR) & (DTGTX | DTGRX | NAKRX);
  return;
}

/*********************************************************************************************************//**
  * @brief  Enable Interrupt for Endpoint.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @param  INTFlag: Interrupt flag
  *         @arg OTRXIE | ODRXIE | ODOVIE | ITRXIE | IDTXIE | NAKIE | STLIE | UERIE |
  *              STRXIE | SDRXIE | SDERIE | ZLRXIE
  * @retval None
  ***********************************************************************************************************/
void USBD_EPTEnableINT(USBD_EPTn_Enum USBD_EPTn, u32 INTFlag)
{
  _USBD_GetEPTnAddr(USBD_EPTn)->IER = INTFlag;
  return;
}

/*********************************************************************************************************//**
  * @brief  Get active USB Device Endpoint interrupt.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval USB Endpoint ISR Flag
  ***********************************************************************************************************/
u32 USBD_EPTGetINT(USBD_EPTn_Enum USBD_EPTn)
{
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);
  u32 IER = USBEPn->IER;
  return (USBEPn->ISR & IER);
}

/*********************************************************************************************************//**
  * @brief  Clear Interrupt for Endpoint.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @param  INTFlag: Interrupt flag
  *         @arg OTRXIF | ODRXIF | ODOVIF | ITRXIF | IDTXIF | NAKIF | STLIF | UERIF |
  *              STRXIF | SDRXIF | SDERIF | ZLRXIF
  * @retval None
  ***********************************************************************************************************/
void USBD_EPTClearINT(USBD_EPTn_Enum USBD_EPTn, u32 INTFlag)
{
  _USBD_GetEPTnAddr(USBD_EPTn)->ISR = INTFlag;
  return;
}

/*********************************************************************************************************//**
  * @brief  Get Endpoint n Halt status (STLTX or STLRX).
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval Endpoint Halt Status (1: Endpoint is Halt, 0: Endpoint is not Halt)
  ***********************************************************************************************************/
u32 USBD_EPTGetHalt(USBD_EPTn_Enum USBD_EPTn)
{
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);
  USBD_EPTCFGR_Bit *CFGR = (USBD_EPTCFGR_Bit *)(&(USBEPn->CFGR));
  if (CFGR->EPDIR == EPDIR_IN)
  {
    return (((USBEPn->CSR) & STLTX) ? 1 : 0);
  }
  else
  {
    return (((USBEPn->CSR) & STLRX) ? 1 : 0);
  }
}

/*********************************************************************************************************//**
  * @brief  Send STALL on Endpoint n.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval None
  ***********************************************************************************************************/
void USBD_EPTSendSTALL(USBD_EPTn_Enum USBD_EPTn)
{
  _USBD_GetEPTnAddr(USBD_EPTn)->CSR = STLTX;
  return;
}

/*********************************************************************************************************//**
  * @brief  Set Endpoint n Halt status (STLTX or STLRX).
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval None
  ***********************************************************************************************************/
void USBD_EPTSetHalt(USBD_EPTn_Enum USBD_EPTn)
{
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);

#if 1
  /* Clean STLIF flag, for USBD_EPTWaitSTALLSent function                                                   */
  USBEPn->ISR = STLIF;
  USBEPn->CSR = (~(USBEPn->CSR)) & (STLTX | STLRX);
#else
  USBD_EPTCFGR_Bit *CFGR = (USBD_EPTCFGR_Bit *)(&(USBEPn->CFGR));
  if (CFGR->EPDIR == EPDIR_IN)
  {
    /* Clean STLIF flag, for USBD_EPTWaitSTALLSent function                                                 */
    USBEPn->ISR = STLIF;
    /* Set only when STLTX = 0                                                                              */
    USBEPn->CSR = (~(USBEPn->CSR)) & STLTX;
  }
  else
  {
    /* Set only when STLRX = 0                                                                              */
    USBEPn->CSR = (~(USBEPn->CSR)) & STLRX;
  }
#endif

  return;
}

/*********************************************************************************************************//**
  * @brief  Clear Endpoint n Halt status (STLTX or STLRX).
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval None
  ***********************************************************************************************************/
void USBD_EPTClearHalt(USBD_EPTn_Enum USBD_EPTn)
{
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);

#if 1
  USBEPn->CSR = (USBEPn->CSR) & (STLTX | STLRX);
#else
  USBD_EPTCFGR_Bit *CFGR = (USBD_EPTCFGR_Bit *)(&(USBEPn->CFGR));
  if (CFGR->EPDIR == EPDIR_IN)
  {
    /* Clear only when STLTX = 1                                                                            */
    USBEPn->CSR = (USBEPn->CSR) & STLTX;
  }
  else
  {
    /* Clear only when STLRX = 1                                                                            */
    USBEPn->CSR = (USBEPn->CSR) & STLRX;
  }
#endif

  return;
}

/*********************************************************************************************************//**
  * @brief  Wait until STALL transmission is finished
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval None
  ***********************************************************************************************************/
void USBD_EPTWaitSTALLSent(USBD_EPTn_Enum USBD_EPTn)
{
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);
  USBD_EPTCFGR_Bit *CFGR = (USBD_EPTCFGR_Bit *)(&(USBEPn->CFGR));
  u32 uSTALLState = (CFGR->EPDIR == EPDIR_IN) ? ((USBEPn->CSR) & STLTX) : ((USBEPn->CSR) & STLRX);

  if (uSTALLState)
  {
    while ((USBEPn->ISR & STLIF) == 0);
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  Clear Endpoint n Data toggle bit (DTGTX or DTGRX).
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval None
  ***********************************************************************************************************/
void USBD_EPTClearDTG(USBD_EPTn_Enum USBD_EPTn)
{
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);

#if 1
  USBEPn->CSR = (USBEPn->CSR) & (DTGTX | DTGRX);
#else
  USBD_EPTCFGR_Bit *CFGR = (USBD_EPTCFGR_Bit *)(&(USBEPn->CFGR));
  if (CFGR->EPDIR == EPDIR_IN)
  {
    /* Clear only when DTGTX = 1                                                                            */
    USBEPn->CSR = (USBEPn->CSR) & DTGTX;
  }
  else
  {
    /* Clear only when DTGRX = 1                                                                            */
    USBEPn->CSR = (USBEPn->CSR) & DTGRX;
  }
#endif
  return;
}

/*********************************************************************************************************//**
  * @brief  Get Endpoint n buffer 0 address.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval USB Endpoint buffer 0 address
  ***********************************************************************************************************/
u32 USBD_EPTGetBuffer0Addr(USBD_EPTn_Enum USBD_EPTn)
{
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);
  return (HT_USB_SRAM_BASE + (USBEPn->CFGR & EPBUFA_MASK));
}

/*********************************************************************************************************//**
  * @brief  Get Endpoint n buffer 1 address.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval USB Endpoint buffer 1 address
  ***********************************************************************************************************/
u32 USBD_EPTGetBuffer1Addr(USBD_EPTn_Enum USBD_EPTn)
{
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);
  return (HT_USB_SRAM_BASE + (USBEPn->CFGR & EPBUFA_MASK) + USBD_EPTGetBufferLen(USBD_EPTn));
}

/*********************************************************************************************************//**
  * @brief  Get Endpoint n buffer length.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval USB Endpoint buffer length
  ***********************************************************************************************************/
u32 USBD_EPTGetBufferLen(USBD_EPTn_Enum USBD_EPTn)
{
  return ((_USBD_GetEPTnAddr(USBD_EPTn)->CFGR & EPLEN_MASK) >> 10);
}

/*********************************************************************************************************//**
  * @brief  Get Endpoint n Transfer Count.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @param  USBD_TCR_n: USBD_TCR_0 or USBD_TCR_1
  * @retval Endpoint Transfer Count
  ***********************************************************************************************************/
u32 USBD_EPTGetTransferCount(USBD_EPTn_Enum USBD_EPTn, USBD_TCR_Enum USBD_TCR_n)
{
  return (((_USBD_GetEPTnAddr(USBD_EPTn)->TCR) >> USBD_TCR_n) & TCR_MASK);
}

/*********************************************************************************************************//**
  * @brief  Write IN Data from User buffer to USB buffer.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @param  pFrom: Source buffer
  * @param  len: Length for write IN data
  * @retval Total length written by this function
  ***********************************************************************************************************/
u32 USBD_EPTWriteINData(USBD_EPTn_Enum USBD_EPTn, u32 *pFrom, u32 len)
{
  u32 bufferlen = USBD_EPTGetBufferLen(USBD_EPTn);
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);
  u32 EPTnLen;
  u32 *pTo;

  EPTnLen = (USBD_EPTn == USBD_EPT0) ? USBD_EPTGetTransferCount(USBD_EPTn, USBD_CNTIN):USBD_EPTGetTransferCount(USBD_EPTn, USBD_CNTB0);

  if (len <= bufferlen && EPTnLen == 0)
  {
    pTo = (u32 *)USBD_EPTGetBuffer0Addr(USBD_EPTn);
    _USBD_CopyMemory(pFrom, pTo, ByteLen2WordLen(len));
    USBEPn->TCR = len;
    USBEPn->CSR = NAKTX;
    return len;
  }
  else
  {
    return 0;
  }
}

/*********************************************************************************************************//**
  * @brief  Read OUT Data from USB buffer to User buffer.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @param  pTo: Destination memory
  * @param  len: Length for read OUT data, set as 0 for discard current OUT data in the USB buffer
  * @retval Total length read by this function
  ***********************************************************************************************************/
u32 USBD_EPTReadOUTData(USBD_EPTn_Enum USBD_EPTn, u32 *pTo, u32 len)
{
  HT_USBEP_TypeDef *USBEPn = _USBD_GetEPTnAddr(USBD_EPTn);
  u32 EPTnLen = 0;

  if (len != 0)
  {
    EPTnLen = USBD_EPTReadMemory(USBD_EPTn, pTo, len);
  }

  if (EPTnLen != 0 || len == 0)
  {
    USBEPn->CSR = (USBEPn->CSR & NAKRX);
  }

  return EPTnLen;
}

/*********************************************************************************************************//**
  * @brief  Read memory from endpoint buffer.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @param  pTo: Destination buffer
  * @param  len: Length for read OUT data
  * @retval Total length read by this function
  ***********************************************************************************************************/
u32 USBD_EPTReadMemory(USBD_EPTn_Enum USBD_EPTn, u32 *pTo, u32 len)
{
  u32 EPTnLen = 0;
  u32 *pFrom;

  EPTnLen = (USBD_EPTn == USBD_EPT0) ? USBD_EPTGetTransferCount(USBD_EPTn, USBD_CNTOUT):USBD_EPTGetTransferCount(USBD_EPTn, USBD_CNTB0);

  if (EPTnLen <= len)
  {
    pFrom = (USBD_EPTn == USBD_EPT0) ? (u32 *)USBD_EPTGetBuffer1Addr(USBD_EPTn):(u32 *)USBD_EPTGetBuffer0Addr(USBD_EPTn);
    _USBD_CopyMemory(pFrom, pTo, ByteLen2WordLen(EPTnLen));
  }

  return EPTnLen;
}
/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/
/** @defgroup USBDevice_Private_Function USB Device private functions
  * @{
  */
/*********************************************************************************************************//**
  * @brief  Copy 32 bits memory from pFrom to pTo.
  * @param  pFrom: Source buffer
  * @param  pTo: Destination buffer
  * @param  len: Copy length
  * @retval None
  ***********************************************************************************************************/
static void _USBD_CopyMemory(u32 *pFrom, u32 *pTo, u32 len)
{
  s32 i;
  u32 uFromAligned = (((u32)pFrom & 0x3) == 0) ? 1 : 0;
  u32 uToAligned = (((u32)pTo & 0x3) == 0) ? 1 : 0;
  u8 *pFromByte = (u8 *)pFrom;
  u8 *pToByte = (u8 *)pTo;

  if (uFromAligned == 0)
  {
    if (uToAligned == 0)
    {
      for (i = len - 1; i >= 0; i--)
      {
        *pToByte++ = *pFromByte++;
        *pToByte++ = *pFromByte++;
        *pToByte++ = *pFromByte++;
        *pToByte++ = *pFromByte++;
      }
    }
    else
    {
      u32 uTemp = 0;
      for (i = 0; i < (s32)len; i++)
      {
        uTemp = *(pFromByte++) << 0;
        uTemp += *(pFromByte++) << 8;
        uTemp += *(pFromByte++) << 16;
        uTemp += *(pFromByte++) << 24;
        pTo[i] = uTemp;
      }
    }
  }
  else
  {
    if (uToAligned == 0)
    {
      u32 uTemp = 0;
      for (i = 0; i < (s32)len; i++)
      {
        uTemp = pFrom[i];
        *pToByte++ = (uTemp >>  0) & 0xFF;
        *pToByte++ = (uTemp >>  8) & 0xFF;
        *pToByte++ = (uTemp >> 16) & 0xFF;
        *pToByte++ = (uTemp >> 24) & 0xFF;
      }
    }
    else
    {
      for (i = len - 1; i >= 0; i--)
      {
        pTo[i] = pFrom[i];
      }
    }
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  Convent USBD_EPTn_Enum to USBEP_TypeDef.
  * @param  USBD_EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT9
  * @retval USBEP0 ~ USBEP9
  ***********************************************************************************************************/
static HT_USBEP_TypeDef * _USBD_GetEPTnAddr(USBD_EPTn_Enum USBD_EPTn)
{
  return ((HT_USBEP_TypeDef *)(HT_USBEP0 + USBD_EPTn));
}

/*********************************************************************************************************//**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  ***********************************************************************************************************/
static void _delay(u32 nCount)
{
  u32 i;

  for (i = 0; i < nCount; i++)
  {
  }
}
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
