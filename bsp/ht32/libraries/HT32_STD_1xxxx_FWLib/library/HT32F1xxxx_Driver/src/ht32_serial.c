/*********************************************************************************************************//**
 * @file    ht32_serial.c
 * @version $Rev:: 2794         $
 * @date    $Date:: 2022-11-25 #$
 * @brief   This file provides all the Low level serial routines for HT32.
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
#include "ht32_board.h"

#if (_RETARGET == 1)

/** @addtogroup HT32_Peripheral_Driver HT32 Peripheral Driver
  * @{
  */

/** @defgroup SERIAL SERIAL
  * @brief Serial related functions
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup SERIAL_Exported_Functions Serial exported functions
  * @{
  */

#ifdef RETARGET_IS_UART

#if (RETARGET_INT_MODE == 1)
__ALIGN4 static u8 uSerialBuffer[RETARGET_INT_BUFFER_SIZE];
static vu32 uReadIndex;
static vu32 uWriteIndex;

#define IS_BUFFER_FULL(LEN)        (((uWriteIndex + LEN) >= RETARGET_INT_BUFFER_SIZE) ? ((uWriteIndex + LEN - RETARGET_INT_BUFFER_SIZE) == uReadIndex) : ((uWriteIndex + LEN) == uReadIndex))
#define IS_BUFFER_EMPTY()          (uReadIndex == uWriteIndex)
#define BUFFER_FREE_LEN()          ((uWriteIndex >= uReadIndex) ? (RETARGET_INT_BUFFER_SIZE - uWriteIndex + uReadIndex - 1) : (uReadIndex - uWriteIndex - 1))

/*********************************************************************************************************//**
 * @brief UART IRQ handler.
 * @retval None
 ************************************************************************************************************/
void RETARGET_UART_IRQHandler(void)
{
  if (((RETARGET_USART_PORT->SR) & USART_FLAG_TXDE))
  {
    if (IS_BUFFER_EMPTY())
    {
      RETARGET_USART_PORT->IER &= ~USART_INT_TXDE;
    }
    else
    {
      RETARGET_USART_PORT->DR = uSerialBuffer[uReadIndex++];
      if (uReadIndex == RETARGET_INT_BUFFER_SIZE)
      {
        uReadIndex = 0;
      }
    }
  }

}
#endif

/*********************************************************************************************************//**
 * @brief Put char to USART.
 * @param ch: The char put to USART.
 * @retval The char put to USART.
 ************************************************************************************************************/
u32 SERIAL_PutChar(u32 ch)
{
#if (RETARGET_INT_MODE == 1)

  while (IS_BUFFER_FULL(1));

  uSerialBuffer[uWriteIndex++] = ch;
  if (uWriteIndex == RETARGET_INT_BUFFER_SIZE)
  {
    uWriteIndex = 0;
  }
  RETARGET_USART_PORT->IER |= USART_INT_TXDE;

#else

  USART_SendData(RETARGET_USART_PORT, (u8)ch);
  while (USART_GetFlagStatus(RETARGET_USART_PORT, USART_FLAG_TXC) == RESET)
  {
  }

#endif

  return ch;
}

/*********************************************************************************************************//**
 * @brief Get char from USART.
 * @retval The char got from USART.
 ************************************************************************************************************/
u32 SERIAL_GetChar(void)
{
  #if (LIBCFG_USART_V01)
  while (USART_GetFlagStatus(RETARGET_USART_PORT, USART_FLAG_RXDNE) == RESET)
  {
  }
  #else
  while (USART_GetFlagStatus(RETARGET_USART_PORT, USART_FLAG_RXDR) == RESET)
  {
  }
  #endif
  return USART_ReceiveData(RETARGET_USART_PORT);
}
#endif


#ifdef RETARGET_IS_USB
/* Private types -------------------------------------------------------------------------------------------*/
/** @defgroup SERIAL_Private_TypesDefinitions Serial private types definitions
  * @{
  */
typedef struct _VCP_LINE_CODING
{
  u32 dwDTERate;      //Bit rate;
  u8  bCharFormat;    //Stop bits:
                      //0 = 1   Stop bit
                      //1 = 1.5 Stop bit
                      //2 = 2   Stop bit
  u8  bParityType;    //parity:
                      //0 = None
                      //1 = Odd
                      //2 = Even
                      //3 = Mark
                      //4 = Space
  u8  bDataBits;      //Number of data bits (7, 8, 9)
} USBDClass_VCP_LINE_CODING;
/**
  * @}
  */

/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup SERIAL_Private_Define Serial private definitions
  * @{
  */
#define CLASS_REQ_20_SET_LINE_CODING        (0x20)
#define CLASS_REQ_21_GET_LINE_CODING        (0x21)
#define CLASS_REQ_22_SET_CONTROL_LINE_STATE (0x22)

#ifndef RETARGET_TXBUFFER_SIZE
  #define RETARGET_TXBUFFER_SIZE (1)
#endif

#define RETARGET_USB_MODE_BLOCK                    (0)
#define RETARGET_USB_MODE_NONBLOCK                 (1)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------------------------------------*/
/** @defgroup SERIAL_Private_Macro Serial private macros
  * @{
  */
#define IS_BUFFER_FULL(LEN)        (((uWriteIndex + LEN) >= RETARGET_BUFFER_SIZE) ? ((uWriteIndex + LEN - RETARGET_BUFFER_SIZE)  == uReadIndex) : ((uWriteIndex + LEN) == uReadIndex))
#define IS_BUFFER_EMPTY()          (uReadIndex == uWriteIndex)
#define BUFFER_FREE_LEN()          ((uWriteIndex >= uReadIndex) ? (RETARGET_BUFFER_SIZE - uWriteIndex + uReadIndex - 1) : (uReadIndex - uWriteIndex - 1))
/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/
/** @defgroup SERIAL_Private_Variable Serial private variables
  * @{
  */
static USBDClass_VCP_LINE_CODING USBDClassVCPLineCoding;
__ALIGN4 static u8 uSerialBuffer[RETARGET_BUFFER_SIZE];
static vu32 uReadIndex;
static vu32 uWriteIndex;
static vu32 uDTRState = 0;
static vu32 gIsINEmpty = TRUE;

static u32 TxCount = 0;
__ALIGN4 static u8 TxBuffer[RETARGET_TXBUFFER_SIZE];
/**
  * @}
  */

#if (RETARGET_RX_EPT == RETARGET_TX_EPT)
  #error USB Endpoint of retarget Rx and Tx must different. Please check RETARGET_RX_EPT/RETARGET_TX_EPT "ht32_retarget_usbdconf.h".
#endif

#if (RETARGET_CTRL_EPT == RETARGET_TX_EPT)
  #error USB Endpoint of retarget Control and Tx must different. Please check RETARGET_CTRL_EPT/RETARGET_TX_EPT "ht32_retarget_usbdconf.h".
#endif

#if (RETARGET_CTRL_EPT == RETARGET_RX_EPT)
  #error USB Endpoint of retarget Control and Rx must different. Please check RETARGET_CTRL_EPT/RETARGET_RX_EPT "ht32_retarget_usbdconf.h".
#endif

#ifdef _RERATGET1_ERR
  #error Endpoint 1 already used by other USB class. Retarget can not overwrite it.
#endif

#ifdef _RERATGET2_ERR
  #error Endpoint 2 already used by other USB class. Retarget can not overwrite it.
#endif

#ifdef _RERATGET3_ERR
  #error Endpoint 3 already used by other USB class. Retarget can not overwrite it.
#endif

#ifdef _RERATGET4_ERR
  #error Endpoint 4 already used by other USB class. Retarget can not overwrite it.
#endif

#ifdef _RERATGET5_ERR
  #error Endpoint 5 already used by other USB class. Retarget can not overwrite it.
#endif

#ifdef _RERATGET6_ERR
  #error Endpoint 6 already used by other USB class. Retarget can not overwrite it.
#endif

#ifdef _RERATGET7_ERR
  #error Endpoint 7 already used by other USB class. Retarget can not overwrite it.
#endif

/*********************************************************************************************************//**
 * @brief Put char to USB.
 * @param ch: The char put to USB.
 * @retval The char put to USB.
 ************************************************************************************************************/
u32 SERIAL_PutChar(u32 ch)
{
  #if (RETARGET_TXBUFFER_SIZE > 63)
    #error RETARGET_TXBUFFER_SIZE shall less than 63 (define in ht32fxxxxx_conf.h).
  #endif

  #if (RETARGET_USB_MODE == RETARGET_USB_MODE_BLOCK)
  while (uDTRState == 0);   /* Wait until user open the virtual COM port by PC UI such as Hyper Terminal    */
  #elif (RETARGET_USB_MODE == RETARGET_USB_MODE_NONBLOCK)
  if (uDTRState == 0)       /* Drop data if USB or terminal software is not ready                           */
  {
    return ch;
  }
  #endif

  TxBuffer[TxCount++] = ch;

  if (TxCount == RETARGET_TXBUFFER_SIZE)
  {
    TxCount = 0;

    while (gIsINEmpty == FALSE)
    {
      #if (RETARGET_USB_MODE == RETARGET_USB_MODE_NONBLOCK)
      if (uDTRState == 0)
      {
        return ch;
      }
      #endif
    }

    gIsINEmpty = FALSE;
    USBDCore_EPTWriteINData((USBD_EPTn_Enum)RETARGET_TX_EPT, (u32 *)&TxBuffer, RETARGET_TXBUFFER_SIZE);
  }

  return ch;
}

/*********************************************************************************************************//**
 * @brief Get char from USB.
 * @retval The char got from USB.
 ************************************************************************************************************/
u32 SERIAL_GetChar(void)
{
  u32 value = 0;

  while (IS_BUFFER_EMPTY());
  value = uSerialBuffer[uReadIndex++];
  if (uReadIndex == RETARGET_BUFFER_SIZE)
  {
    uReadIndex = 0;
  }

  return value;
}

/*********************************************************************************************************//**
 * @brief Flush the Tx Buffer
 * @retval None
 ************************************************************************************************************/
void SERIAL_Flush(void)
{
  do
  {
    #if (RETARGET_USB_MODE == RETARGET_USB_MODE_NONBLOCK)
    if (uDTRState == 0)
    {
      return;
    }
    #endif
  } while (USBDCore_EPTGetTransferCount((USBD_EPTn_Enum)RETARGET_TX_EPT, USBD_TCR_0));

  gIsINEmpty = FALSE;
  USBDCore_EPTWriteINData((USBD_EPTn_Enum)RETARGET_TX_EPT, (u32 *)&TxBuffer, TxCount);
  TxCount = 0;
}

#ifdef NON_USB_IN_APP
#include "ht32_retarget_desc.c"
__ALIGN4 USBDCore_TypeDef gUSBCore;
USBD_Driver_TypeDef gUSBDriver;

/*********************************************************************************************************//**
 * @brief This function handles USB interrupt.
 * @retval None
 ************************************************************************************************************/
void USB_IRQHandler(void)
{
  USBDCore_IRQHandler(&gUSBCore);
}

/*********************************************************************************************************//**
 * @brief USB Class initialization.
 * @param pClass: pointer of USBDCore_Class_TypeDef
 * @retval None
 ************************************************************************************************************/
void USBDClass_Init(USBDCore_Class_TypeDef *pClass)
{
  pClass->CallBack_ClassRequest = SERIAL_USBDClass_Request;
  pClass->CallBack_EPTn[RETARGET_RX_EPT] = SERIAL_USBDClass_RXHandler;
  pClass->CallBack_EPTn[RETARGET_TX_EPT] = SERIAL_USBDClass_TXHandler;
  return;
}

#if (LIBCFG_CKCU_USB_PLL)
/*********************************************************************************************************//**
 * @brief  Configure USB PLL
 * @retval None
 ************************************************************************************************************/
void USBPLL_Configuration(void)
{
  if ((HT_CKCU->GCCR & (1 << 11)) == 0)
  {
    CKCU_HSICmd(ENABLE);
  }

  { /* USB PLL configuration                                                                                */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    CKCU_PLLInitTypeDef PLLInit;

    PLLInit.ClockSource = CKCU_PLLSRC_HSI;
    #if (LIBCFG_CKCU_USB_PLL_96M)
    PLLInit.CFG = CKCU_USBPLL_8M_96M;
    #else
    PLLInit.CFG = CKCU_USBPLL_8M_48M;
    #endif
    PLLInit.BYPASSCmd = DISABLE;
    CKCU_USBPLLInit(&PLLInit);
  }

  CKCU_USBPLLCmd(ENABLE);

  while (CKCU_GetClockReadyStatus(CKCU_FLAG_USBPLLRDY) == RESET);
  CKCU_USBClockConfig(CKCU_CKUSBPLL);
}
#endif

/*********************************************************************************************************//**
 * @brief Configure USB for retarget.
 * @retval None
 ************************************************************************************************************/
void SERIAL_USBDInit(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.USBD = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  #if (LIBCFG_CKCU_USB_PLL)
  USBPLL_Configuration();
  #else
  {
  u32 uPLL;
  uPLL = CKCU_GetPLLFrequency();
  // uPLL=48000000, CKCU_USBPRE_DIV1
  // uPLL=96000000, CKCU_USBPRE_DIV2
  // uPLL=144000000, CKCU_USBPRE_DIV3
  CKCU_SetUSBPrescaler((CKCU_USBPRE_TypeDef)((uPLL / 48000000) - 1));
  #endif

#if (LIBCFG_CKCU_HSI_NO_AUTOTRIM)
#else
  /* !!! NOTICE !!!
     Must turn on if the USB clock source is from HSI (PLL clock Source)
  */
  #if (RETARGET_HSI_ATM)
  CKCU_HSIAutoTrimClkConfig(CKCU_ATC_USB);
  CKCU_HSIAutoTrimCmd(ENABLE);
  #endif
#endif

  gUSBCore.pDriver = (u32 *)&gUSBDriver;                /* Initiate memory pointer of USB driver            */
  USBDDesc_Init(&gUSBCore.Device.Desc);                 /* Initiate memory pointer of descriptor            */
  USBDClass_Init(&gUSBCore.Class);                      /* Initiate USB Class layer                         */
  USBDCore_Init(&gUSBCore);                             /* Initiate USB Core layer                          */
  NVIC_EnableIRQ(USB_IRQn);                             /* Enable USB device interrupt                      */
  USBD_DPpullupCmd(ENABLE);

  #if (RETARGET_USB_MODE == RETARGET_USB_MODE_BLOCK)
  USBDCore_MainRoutine(&gUSBCore);                      /* USB core main routine                            */
  while (USBDCore_GetStatus() != USB_STATE_CONFIGURED);
  #else
  gUSBCore.Info.CurrentFeature.Bits.bSelfPowered = TRUE;
  USBDCore_MainRoutine(&gUSBCore);                      /* USB core main routine                            */
  #endif
}
#endif

/*********************************************************************************************************//**
 * @brief USB Device Class Request for USB retarget
 * @param pDev: pointer of USB Device
 * @retval None
 ************************************************************************************************************/
void SERIAL_USBDClass_Request(USBDCore_Device_TypeDef *pDev)
{
  u8 USBCmd = *((u8 *)(&(pDev->Request.bRequest)));
  u16 len = *((u16 *)(&(pDev->Request.wLength)));
  u32 inf = pDev->Request.wIndex;
  u32 uIsCmdOK = 0;

  if (inf != 11)
  {
    return;
  }

  if (USBCmd == CLASS_REQ_22_SET_CONTROL_LINE_STATE)
  {
    if (len == 0)
    {
      uDTRState = pDev->Request.wValueL & 0x1;
      pDev->Transfer.pData = 0;
      pDev->Transfer.sByteLength = 0;
      pDev->Transfer.Action = USB_ACTION_DATAOUT;
    }
  }
  else
  {
    if (USBCmd == CLASS_REQ_20_SET_LINE_CODING)
    {
      pDev->Transfer.Action = USB_ACTION_DATAOUT;
      uIsCmdOK = 1;
    }
    else if (USBCmd == CLASS_REQ_21_GET_LINE_CODING)
    {
      pDev->Transfer.Action = USB_ACTION_DATAIN;
      uIsCmdOK = 1;
    }

    if (uIsCmdOK == 1)
    {
      pDev->Transfer.pData = (uc8*)&USBDClassVCPLineCoding;
      pDev->Transfer.sByteLength = (sizeof(USBDClassVCPLineCoding) > pDev->Request.wLength) ? (pDev->Request.wLength) : (sizeof(USBDClassVCPLineCoding));
    }
  }

  return;
}

/*********************************************************************************************************//**
 * @brief USB Class Received handler
 * @param EPTn: USB Endpoint number
 *   @arg USBD_EPT0 ~ USBD_EPT7
 * @retval None
************************************************************************************************************/
void SERIAL_USBDClass_RXHandler(USBD_EPTn_Enum EPTn)
{
  u32 uLen;
  u32 uFreeLen = BUFFER_FREE_LEN();
  u8 uTempBuffer[64];
  u32 i;

  /* Read Receive data                                                                                      */
  uLen = USBDCore_EPTReadOUTData(EPTn, (u32*)uTempBuffer, 64);

  if (uLen > uFreeLen)
  {
    uLen = uFreeLen;
  }

  for (i = 0; i < uLen; i++)
  {
    uSerialBuffer[uWriteIndex++] = uTempBuffer[i];
    if (uWriteIndex == RETARGET_BUFFER_SIZE)
    {
      uWriteIndex = 0;
    }
  }

  return;
}

/*********************************************************************************************************//**
 * @brief USB Class Tx handler
 * @param EPTn: USB Endpoint number
 *   @arg USBD_EPT0 ~ USBD_EPT7
 * @retval None
************************************************************************************************************/
void SERIAL_USBDClass_TXHandler(USBD_EPTn_Enum EPTn)
{
  gIsINEmpty = TRUE;
  return;
}

#endif
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
#endif
