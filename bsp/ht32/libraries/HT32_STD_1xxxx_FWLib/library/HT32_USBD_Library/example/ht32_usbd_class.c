/*********************************************************************************************************//**
 * @file    example/ht32_usbd_class.c
 * @version $Rev:: 11           $
 * @date    $Date:: 2017-05-15 #$
 * @brief   The USB Device Class.
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
#include "ht32_usbd_core.h"
#include "ht32_usbd_class.h"

/** @addtogroup HT32_USBD_Library HT32 USB Device Library
  * @{
  */

/** @defgroup USBDClass USB Device Class
  * @brief USB Device Class
  * @{
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup USBDClass_Private_Define USB Device Class private definitions
  * @{
  */
#define CLASS_REQ_01_CMD1                 (u16)(0x1 << 8)
#define CLASS_REQ_02_CMD2                 (u16)(0x2 << 8)
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
static void USBDClass_MainRoutine(u32 uPara);
static void USBDClass_ClassProcess(void);
static void USBDClass_EPT1Process(void);
static void USBDClass_EPT2Process(void);

static void USBDClass_Reset(u32 uPara);
static void USBDClass_StartOfFrame(u32 uPara);

static void USBDClass_Standard_GetDescriptor(USBDCore_Device_TypeDef *pDev);
static void USBDClass_Standard_SetInterface(USBDCore_Device_TypeDef *pDev);
static void USBDClass_Standard_GetInterface(USBDCore_Device_TypeDef *pDev);

static void USBDClass_Request(USBDCore_Device_TypeDef *pDev);

static void USBDClass_CMD1(USBDCore_Device_TypeDef *pDev);
static void USBDClass_CMD2(USBDCore_Device_TypeDef *pDev);

static void USBDClass_Endpoint1(USBD_EPTn_Enum EPTn);
static void USBDClass_Endpoint2(USBD_EPTn_Enum EPTn);
static void USBDClass_Endpoint3(USBD_EPTn_Enum EPTn);
static void USBDClass_Endpoint4(USBD_EPTn_Enum EPTn);
static void USBDClass_Endpoint5(USBD_EPTn_Enum EPTn);
static void USBDClass_Endpoint6(USBD_EPTn_Enum EPTn);
static void USBDClass_Endpoint7(USBD_EPTn_Enum EPTn);

/* Global Function -----------------------------------------------------------------------------------------*/
/** @defgroup USBDClass_Exported_Functions USB Device Class exported functions
  * @{
  */
/*********************************************************************************************************//**
  * @brief  USB Class initialization.
  * @param  pClass: pointer of USBDCore_Class_TypeDef
  * @retval None
  ***********************************************************************************************************/
void USBDClass_Init(USBDCore_Class_TypeDef *pClass)
{
  pClass->CallBack_MainRoutine.func = USBDClass_MainRoutine;
  //pClass->CallBack_MainRoutine.uPara = (u32)NULL;

  pClass->CallBack_Reset.func = USBDClass_Reset;
  pClass->CallBack_Reset.uPara = (u32)NULL;

  pClass->CallBack_StartOfFrame.func = USBDClass_StartOfFrame;
  pClass->CallBack_StartOfFrame.uPara = (u32)NULL;

  pClass->CallBack_ClassGetDescriptor = USBDClass_Standard_GetDescriptor;
  pClass->CallBack_ClassSetInterface = USBDClass_Standard_SetInterface;
  pClass->CallBack_ClassGetInterface = USBDClass_Standard_GetInterface;

  pClass->CallBack_ClassRequest = USBDClass_Request;
  pClass->CallBack_EPTn[1] = USBDClass_Endpoint1;
  pClass->CallBack_EPTn[2] = USBDClass_Endpoint2;
  pClass->CallBack_EPTn[3] = USBDClass_Endpoint3;
  pClass->CallBack_EPTn[4] = USBDClass_Endpoint4;
  pClass->CallBack_EPTn[5] = USBDClass_Endpoint5;
  pClass->CallBack_EPTn[6] = USBDClass_Endpoint6;
  pClass->CallBack_EPTn[7] = USBDClass_Endpoint7;

  #ifdef RETARGET_IS_USB
  pClass->CallBack_EPTn[RETARGET_RX_EPT] = SERIAL_USBDClass_RXHandler;
  #endif

  return;
}
/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/
/** @defgroup USBDClass_Private_Functions USB Device Class private functions
  * @{
  */
/*********************************************************************************************************//**
  * @brief  USB Class main routine.
  * @param  uPara: Parameter for Class main routine
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_MainRoutine(u32 uPara)
{
  USBDClass_ClassProcess();
  USBDClass_EPT1INProcess();
  USBDClass_EPT2OUTProcess();

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Process for application.
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_ClassProcess(void)
{
  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Endpoint 1 Process for application.
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_EPT1Process(void)
{
  if (gIsEP1 == TRUE)
  {
    gIsEP1 = FALSE;
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Endpoint 2 Process for application.
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_EPT2Process(void)
{
  if (gIsEP2 == TRUE)
  {
    gIsEP2 = FALSE;
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Reset.
  * @param  uPara: Parameter for Class Reset.
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Reset(u32 uPara)
{

}

/*********************************************************************************************************//**
  * @brief  USB Class Start of Frame.
  * @param  uPara: Parameter for Class Start of Frame.
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_StartOfFrame(u32 uPara)
{

}

/*********************************************************************************************************//**
  * @brief  USB Device Class Request
  * @param  pDev: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Request(USBDCore_Device_TypeDef *pDev)
{
  u16 uUSBCmd = *((u16 *)(&(pDev->Request)));

#ifdef RETARGET_IS_USB
  SERIAL_USBDClass_Request(pDev);
#endif

  switch (uUSBCmd)
  {
    /*------------------------------------------------------------------------------------------------------*/
    /* | bRequest             | Data transfer direction | Type                | Recipient   | Data          */
    /*------------------------------------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------------------------------------*/
    /* | 01_CMD1              | 80_Device-to-Host       | 20_Class Request    | 1_Interface | 01A1h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (CLASS_REQ_01_CMDID0 | REQ_DIR_01_D2H | REQ_TYPE_01_CLS | REQ_REC_01_INF):
    {
      __DBG_USBPrintf("%06ld CMD0\t[%02d][%02d]\r\n", __DBG_USBCount, pDev->Request.wValueH, pDev->Request.wLength );
      USBDClass_RequestCMD1(pDev);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 02_CMD2              | 00_Host-to-Device       | 20_Class Request    | 1_Interface | 0221h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (CLASS_REQ_02_GET_IDLE | REQ_DIR_00_H2D | REQ_TYPE_01_CLS | REQ_REC_01_INF):
    {
      __DBG_USBPrintf("%06ld CMD1\t[%02d][%02d]\r\n", __DBG_USBCount, pDev->Request.wValueH, pDev->Request.wLength );
      USBDClass_RequestCMD2(pDev);
      break;
    }
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Device Class Standard Request - GET_DESCRIPTOR
  * @param  pDev: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Standard_GetDescriptor(USBDCore_Device_TypeDef *pDev)
{
  u32 type = pDev->Request.wValueH;

  switch (type)
  {
    case DESC_TYPE_01_XXX
    {
      pDev->Transfer.pData = (uc8 *)(__BUFFER_POINTER__);
      pDev->Transfer.sByteLength = DESC_LEN_XXX;
      pDev->Transfer.Action = USB_ACTION_DATAIN;
      break;
    }
    case DESC_TYPE_02_XXX:
    {
      pDev->Transfer.pData = (uc8 *)(__BUFFER_POINTER__);
      pDev->Transfer.sByteLength = DESC_LEN_XXX;
      pDev->Transfer.Action = USB_ACTION_DATAIN;
      break;
    }
  } /* switch (type)                                                                                        */

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Device Class Standard Request - SET_INTERFACE
  * @param  pDev: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Standard_SetInterface(USBDCore_Device_TypeDef *pDev)
{

}

/*********************************************************************************************************//**
  * @brief  USB Device Class Standard Request - GET_INTERFACE
  * @param  pDev: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Standard_GetInterface(USBDCore_Device_TypeDef *pDev)
{

}



/*********************************************************************************************************//**
  * @brief  USB Device Class Request - CMD1
  * @param  pDev: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_CMD1(USBDCore_Device_TypeDef *pDev)
{
  /* Add your own Class request function here....
     For example....

  u32 uReportID  = pDev->Request.wValueL;
  u32 uInterface = pDev->Request.wIndex;

  pDev->Transfer.pData = (uc8 *)&(__IDLE_DURATION_BUFFER[uReportID]);
  pDev->Transfer.sByteLength = 1;
  pDev->Transfer.Action= USB_ACTION_DATAIN;

  */
  return;
}

/*********************************************************************************************************//**
  * @brief  USB Device Class Request - CMD2
  * @param  pDev: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_CMD2(USBDCore_Device_TypeDef *pDev)
{
  /* Add your own Class request function here....
     For example....

  u32 uReportID  = pDev->Request.wValueL;
  u32 uInterface = pDev->Request.wIndex;

  pDev->Transfer.pData = (uc8 *)&(__IDLE_DURATION_BUFFER[uReportID]);
  pDev->Transfer.sByteLength = 1;
  pDev->Transfer.Action= USB_ACTION_DATAIN;

  */
  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Endpoint handler
  * @param  EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT7
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Endpoint1(USBD_EPTn_Enum EPTn)
{
  gIsEP1 = TRUE;

  __DBG_USBPrintf("%06ld EP1\t[%02d]", ++__DBG_USBCount, (int)USBDCore_EPTGetBufferLen(EPTn));

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Endpoint handler
  * @param  EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT7
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Endpoint2(USBD_EPTn_Enum EPTn)
{
  gIsEP2 = TRUE;
  __DBG_USBPrintf("%06ld EP2\t[%02d]", ++__DBG_USBCount, (int)USBDCore_EPTGetBufferLen(EPTn));

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Endpoint handler
  * @param  EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT7
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Endpoint3(USBD_EPTn_Enum EPTn)
{
  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Endpoint handler
  * @param  EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT7
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Endpoint4(USBD_EPTn_Enum EPTn)
{
  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Endpoint handler
  * @param  EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT7
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Endpoint5(USBD_EPTn_Enum EPTn)
{
  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Endpoint handler
  * @param  EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT7
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Endpoint6(USBD_EPTn_Enum EPTn)
{
  return;
}

/*********************************************************************************************************//**
  * @brief  USB Class Endpoint handler
  * @param  EPTn: USB Endpoint number
  *         @arg USBD_EPT0 ~ USBD_EPT7
  * @retval None
  ***********************************************************************************************************/
static void USBDClass_Endpoint7(USBD_EPTn_Enum EPTn)
{
  return;
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
