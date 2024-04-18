/*********************************************************************************************************//**
 * @file    ht32_usbd_core.c
 * @version $Rev:: 1684         $
 * @date    $Date:: 2019-05-07 #$
 * @brief   The standard protocol related function of HT32 USB Device Library.
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

#ifdef USBD_VENDOR_SUPPORT
#include "ht32_usbd_vendor.c"
#endif

/** @addtogroup HT32_USBD_Library HT32 USB Device Library
  * @{
  */

/** @defgroup USBDCore USB Device Core
  * @brief USB Device Core standard protocol related function
  * @{
  */


/* Private types -------------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Private_TypesDefinitions USB Device Core private types definitions
  * @{
  */
typedef enum
{
  Device     = 0,
  Interface  = 1,
  Endpoint   = 2,
  Other      = 3,
} USBDCore_Recipient_Enum;

typedef enum
{
  ClearFeature = 0,
  SetFeature   = 1,
} USBDCore_SetClearFeature_Enum;
/**
  * @}
  */

/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Private_Define USB Device Core private definitions
  * @{
  */
/* USBD Debug mode                                                                                          */
#if (USBDCORE_DEBUG == 1)
  #ifdef RETARGET_IS_USB
    #warning "USB debug mode can not work when retaget to USB Virtual COM. Turn off automatically."
    #undef USBDCORE_DEBUG
    #define USBDCORE_DEBUG 0
  #else
    u32 __DBG_USBCount;
    #warning "USB debug mode has been enabled which degrade the performance."
    #warning "After the debug operation, please remember to turn off USB debug mode."
  #endif
#endif

/** @defgroup USBDCore_STD Definition for standard request
  * @{
  */
#define REQ_00_GET_STAT               ((u16)(0  << 8))
#define REQ_01_CLR_FETU               ((u16)(1  << 8))
#define REQ_03_SET_FETU               ((u16)(3  << 8))
#define REQ_05_SET_ADDR               ((u16)(5  << 8))
#define REQ_06_GET_DESC               ((u16)(6  << 8))
#define REQ_07_SET_DESC               ((u16)(7  << 8))
#define REQ_08_GET_CONF               ((u16)(8  << 8))
#define REQ_09_SET_CONF               ((u16)(9  << 8))
#define REQ_10_GET_INF                ((u16)(10 << 8))
#define REQ_11_SET_INF                ((u16)(11 << 8))
#define REQ_12_SYN_FRME               ((u16)(12 << 8))
/**
  * @}
  */

#define DESC_TYPE_01_DEV              (0x1)
#define DESC_TYPE_02_CONFN            (0x2)
#define DESC_TYPE_03_STR              (0x3)
#define USB_NO_DATA                   (-1)            /*!< For Device.Transfer.sByteLength                  */
#define BMREQUEST_TYPE_MASK           (0x6 << 4)      /*!< bmRequestType[6:5]                               */
#define USB_FEATURE_REMOTE_WAKEUP     (1)

#define MAX_CONTROL_OUT_SIZE          (64)
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
static void _USBDCore_PowerHandler(USBDCore_TypeDef *pCore);
static void _USBDCore_Reset(USBDCore_TypeDef *pCore);
static void _USBDCore_Resume(USBDCore_TypeDef *pCore);
static void _USBDCore_Suspend(USBDCore_TypeDef *pCore);
static void _USBDCore_Setup(USBDCore_TypeDef *pCore);
static void _USBDCore_Standard_Request(USBDCore_TypeDef *pCore);
static void _USBDCore_Standard_GetStatus(USBDCore_TypeDef *pCore, USBDCore_Recipient_Enum recipient);
static void _USBDCore_Standard_SetClearFeature(USBDCore_TypeDef *pCore, USBDCore_Recipient_Enum recipient, USBDCore_SetClearFeature_Enum type);
static void _USBDCore_Standard_SetAddress(USBDCore_TypeDef *pCore);
static void _USBDCore_Standard_GetDescriptor(USBDCore_TypeDef *pCore);
static void _USBDCore_Standard_GetConfiguration(USBDCore_TypeDef *pCore);
static void _USBDCore_Standard_SetConfiguration(USBDCore_TypeDef *pCore);
static void _USBDCore_ControlIN(USBDCore_TypeDef *pCore);
static void _USBDCore_ControlOUT(USBDCore_TypeDef *pCore);

/* Private macro -------------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Private_Macro USB Device Core private macros
  * @{
  */
/**
 * @brief Get self powered bit from Device descriptor
 */
#define _GET_SELFPOWERED_FROM_DESC()     (((pCore->Device.Desc.pConfnDesc[7]) >> 6) & 0x01)
/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Private_Variable USB Device Core private variables
  * @{
  */
USBDCore_TypeDef *pUSBCore;
/**
  * @}
  */


/* Global Function -----------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Exported_Functions USB Device Core exported functions
  * @{
  */
/*********************************************************************************************************//**
  * @brief  USB Core initialization.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
void USBDCore_Init(USBDCore_TypeDef *pCore)
{
  pUSBCore = pCore;
  pCore->Info.CurrentStatus = USB_STATE_POWERED;
  API_USB_INIT(pCore->pDriver);
  __DBG_USBPrintf("\r\n%06ld \r\n", ++__DBG_USBCount);
  return;
}

/*********************************************************************************************************//**
  * @brief  USB Interrupt Service Routine.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
void USBDCore_IRQHandler(USBDCore_TypeDef *pCore)
{
  u32 USBISRFlag = API_USB_GET_INT();
  u32 USBEPTISRFlag;
  USBD_EPTn_Enum EPTn;

  #if (USBDCORE_DEBUG == 1)
  u32 USBAddr = HT_USB->DEVAR;
  #endif

  /*--------------------------------------------------------------------------------------------------------*/
  /* USB SOF Interrupt                                                                                      */
  /*--------------------------------------------------------------------------------------------------------*/
  if (API_USB_IS_SOF_INT(USBISRFlag))
  {
    __DBG_USBPrintf("%06ld SOF[%02d][%02lX]\r\n", ++__DBG_USBCount, pCore->Info.CurrentStatus, USBAddr);
    if (pCore->Class.CallBack_StartOfFrame.func != NULL)
    {
      pCore->Class.CallBack_StartOfFrame.func(pCore->Class.CallBack_StartOfFrame.uPara);
    }
    API_USB_CLR_SOF_INT();
  }

  /*--------------------------------------------------------------------------------------------------------*/
  /* USB SUSPEND Interrupt                                                                                  */
  /*--------------------------------------------------------------------------------------------------------*/
  if (API_USB_IS_SUSPEND_INT(USBISRFlag))
  {
    __DBG_USBPrintf("%06ld SUSPEND[%02d]\r\n", ++__DBG_USBCount, pCore->Info.CurrentStatus);
    API_USB_CLR_SUSPEND_INT();
    _USBDCore_Suspend(pCore);
  }

  /*--------------------------------------------------------------------------------------------------------*/
  /* USB RESET Interrupt                                                                                    */
  /*--------------------------------------------------------------------------------------------------------*/
  if (API_USB_IS_RESET_INT(USBISRFlag))
  {
    if (API_USB_IS_FRES_INT(USBISRFlag))
    {
      API_USB_CLR_FRES_INT();
    }
    else
    {
      __DBG_USBPrintf("%06ld RESET[%02d][%02lX]\r\n", ++__DBG_USBCount, pCore->Info.CurrentStatus, USBAddr);
      _USBDCore_Reset(pCore);
      if (pCore->Class.CallBack_Reset.func != NULL)
      {
        pCore->Class.CallBack_Reset.func(pCore->Class.CallBack_Reset.uPara);
      }
    }
    API_USB_CLR_RESET_INT();
  }

  /*--------------------------------------------------------------------------------------------------------*/
  /* USB RESUME Interrupt                                                                                   */
  /*--------------------------------------------------------------------------------------------------------*/
  if (API_USB_IS_RESUME_INT(USBISRFlag))
  {
    __DBG_USBPrintf("%06ld RESUME\r\n", ++__DBG_USBCount);
    _USBDCore_Resume(pCore);
    API_USB_CLR_RESUME_INT();
  }

  /*--------------------------------------------------------------------------------------------------------*/
  /* USB Endpoint 0 interrupt                                                                               */
  /*--------------------------------------------------------------------------------------------------------*/
  if (API_USB_IS_EPTn_INT(USBISRFlag, USBD_EPT0))
  {
    USBEPTISRFlag = API_USB_EPTn_GET_INT(USBD_EPT0);

    /*------------------------------------------------------------------------------------------------------*/
    /* Control SETUP Stage                                                                                  */
    /*------------------------------------------------------------------------------------------------------*/
    if (API_USB_IS_SETUP_INT(USBEPTISRFlag))
    {
      API_USB_READ_SETUP(&(pCore->Device.Request));               /* Read SETUP Command data from USB Buffer*/

      __DBG_USBPrintf("%06ld SETUP\t[08]\r\n", ++__DBG_USBCount);
      __DBG_USBDump((uc8 *)&(pCore->Device.Request), 8);

      _USBDCore_Setup(pCore);
      API_USB_CLR_SETUP_INT();                                    /* Clear SETUP Interrupt                  */
    }

    /*------------------------------------------------------------------------------------------------------*/
    /* Control Endpoint 0 IN                                                                                */
    /*------------------------------------------------------------------------------------------------------*/
    if (API_USB_EPTn_IS_IN_INT(USBEPTISRFlag))
    {
      __DBG_USBPrintf("%06ld EP0IN\t[%02ld]", ++__DBG_USBCount, pCore->Device.Transfer.sByteLength);

      _USBDCore_ControlIN(pCore);
      API_USB_EPTn_CLR_IN_INT(USBD_EPT0);
    }

    /*------------------------------------------------------------------------------------------------------*/
    /* Control Endpoint 0 OUT                                                                               */
    /*------------------------------------------------------------------------------------------------------*/
    if (API_USB_EPTn_IS_OUT_INT(USBEPTISRFlag))
    {
      __DBG_USBPrintf("%06ld EP0OUT\t[%02ld]", ++__DBG_USBCount, pCore->Device.Transfer.sByteLength);

      /*----------------------------------------------------------------------------------------------------*/
      /* Clear interrupt flag before USBDCore_ControlOUT is meaning since USBDCore_ControlOUT clear NAKRX   */
      /* bit which will cause another interrupt occur.                                                      */
      /*----------------------------------------------------------------------------------------------------*/
      API_USB_EPTn_CLR_OUT_INT(USBD_EPT0);
      _USBDCore_ControlOUT(pCore);
    }

    /*------------------------------------------------------------------------------------------------------*/
    /* Clear Control Endpoint 0 global interrupt                                                            */
    /*------------------------------------------------------------------------------------------------------*/
    API_USB_CLR_EPTn_INT(USBD_EPT0);

  } /* if (API_USB_IS_EP_INT(USBISRFlag, USBD_EPT0))                                                        */


  /*--------------------------------------------------------------------------------------------------------*/
  /* USB Endpoint n call back function                                                                      */
  /*--------------------------------------------------------------------------------------------------------*/
  while ((EPTn = API_USB_GET_EPT_NUM(API_USB_GET_INT())) != USBD_NOEPT)
  {
    USBEPTISRFlag = API_USB_EPTn_GET_INT((USBD_EPTn_Enum)EPTn);

    if (API_USB_EPTn_IS_INT(USBEPTISRFlag))
    {
      API_USB_EPTn_CLR_INT(EPTn);
      API_USB_CLR_EPTn_INT(EPTn);

      if (pCore->Class.CallBack_EPTn[EPTn] != NULL)
      {
        pCore->Class.CallBack_EPTn[EPTn](EPTn);
      }
    }
  } /* while ((EPTn = API_USB_GET_EPTn_NUM(API_USB_GET_INT())) != USBD_NOEPT)                               */

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Core Main Routine for application.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
void USBDCore_MainRoutine(USBDCore_TypeDef *pCore)
{
  _USBDCore_PowerHandler(pCore);

  /*--------------------------------------------------------------------------------------------------------*/
  /* Class main routine call back function                                                                  */
  /*--------------------------------------------------------------------------------------------------------*/
  if ((pCore->Class.CallBack_MainRoutine.func != NULL) && (pCore->Info.CurrentStatus == USB_STATE_CONFIGURED))
  {
    pCore->Class.CallBack_MainRoutine.func(pCore->Class.CallBack_MainRoutine.uPara);
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  Return Suspend status
  * @param  pCore: pointer of USB Device
  * @retval TRUE or FALSE
  ***********************************************************************************************************/
u32 USBDCore_IsSuspend(USBDCore_TypeDef *pCore)
{
  return ((pCore->Info.CurrentStatus == USB_STATE_SUSPENDED) ? TRUE : FALSE);
}

/*********************************************************************************************************//**
  * @brief  Return remote wake status which set by SET FEATURE standard command
  * @param  pCore: pointer of USB Device
  * @retval TRUE or FALSE
  ***********************************************************************************************************/
u32 USBDCore_GetRemoteWakeUpFeature(USBDCore_TypeDef *pCore)
{
  return (pCore->Info.CurrentFeature.Bits.bRemoteWakeup);
}

/*********************************************************************************************************//**
  * @brief  Turn on USB power and remote wakeup the Host
  * @retval None
  ***********************************************************************************************************/
void USBDCore_TriggerRemoteWakeup(void)
{
  API_USB_POWER_ON();          /* Turn on USB Power                                                         */
  API_USB_REMOTE_WAKEUP();     /* Generate Remote Wakeup request to Host (RESUME)                           */
  return;
}

/*********************************************************************************************************//**
  * @brief  Get USB Device status
  * @retval USBDCore_Status_Enum
  ***********************************************************************************************************/
USBDCore_Status_Enum USBDCore_GetStatus(void)
{
  return pUSBCore->Info.CurrentStatus;
}

/*********************************************************************************************************//**
  * @brief  Dump memory data for debug purpose.
  * @param  memory: buffer pointer to dump
  * @param  len: dump length
  * @retval None
  ***********************************************************************************************************/
#if (USBDCORE_DEBUG == 1 && USBDCORE_DEBUG_DATA == 1)
void __DBG_USBDump(uc8 *memory, u32 len)
{
  u32 i;
  for (i = 0; i < len; i++)
  {
    if (i % 8 == 0)
    {
      if (i != 0)
      {
        __DBG_USBPrintf("\r\n");
      }
      __DBG_USBPrintf("\t\t");
    }
    __DBG_USBPrintf("%02X ", *((u8 *)(memory + i)));
  }
  __DBG_USBPrintf("\r\n");

  return;
}
#endif
/**
  * @}
  */

/* Private functions ---------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Private_Function USB Device Core private functions
  * @{
  */
/*********************************************************************************************************//**
  * @brief  USB Core Power handler for application.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_PowerHandler(USBDCore_TypeDef *pCore)
{
  API_USB_POWER_UP(pCore->pDriver, pCore->Info.CurrentFeature.Bits.bSelfPowered);

  if (pCore->Info.CurrentStatus == USB_STATE_SUSPENDED)
  {
    /*------------------------------------------------------------------------------------------------------*/
    /* System Low Power call back function                                                                  */
    /*------------------------------------------------------------------------------------------------------*/
    if (pCore->Power.CallBack_Suspend.func != NULL)
    {
      __DBG_USBPrintf("%06ld >LOWPOWER\r\n", ++__DBG_USBCount);

      pCore->Power.CallBack_Suspend.func(pCore->Power.CallBack_Suspend.uPara);

      __DBG_USBPrintf("%06ld <LOWPOWER\r\n", ++__DBG_USBCount);
    }
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Reset
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Reset(USBDCore_TypeDef *pCore)
{
  USBD_Driver_TypeDef *pDrv = (USBD_Driver_TypeDef *)pCore->pDriver;

  pCore->Device.Transfer.sByteLength = USB_NO_DATA;
  pCore->Info.uCurrentConfiguration = 0;
  pCore->Info.uCurrentInterface = 0;
  pCore->Info.CurrentFeature.Bits.bRemoteWakeup = 0;
  pCore->Info.CurrentStatus = USB_STATE_DEFAULT;
  pCore->Info.uIsDiscardClearFeature = FALSE;

  API_USB_DEINIT();

  API_USB_POWER_ON();

  /* Endpoint 0 initialization                                                                              */
  API_USB_EPTn_INIT(USBD_EPT0, pCore->pDriver); // To be modify, init from desc

  /* Enable USB interrupt                                                                                   */
  API_USB_ENABLE_INT(pDrv->uInterruptMask);

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Resume
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Resume(USBDCore_TypeDef *pCore)
{
  API_USB_POWER_ON();
  pCore->Info.CurrentStatus = pCore->Info.LastStatus;
  return;
}

/*********************************************************************************************************//**
  * @brief  USB Suspend
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Suspend(USBDCore_TypeDef *pCore)
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* When Device has been suspended, Change CurrentStatus as SUSPEND and then USBDCore_PowerHandler will    */
  /* turn off chip power.                                                                                   */
  /*--------------------------------------------------------------------------------------------------------*/
  if (pCore->Info.CurrentStatus >= USB_STATE_POWERED)
  {
    API_USB_POWER_OFF();
    pCore->Info.LastStatus = pCore->Info.CurrentStatus;
    pCore->Info.CurrentStatus = USB_STATE_SUSPENDED;
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Setup Stage
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Setup(USBDCore_TypeDef *pCore)
{
  pCore->Device.Transfer.Action = USB_ACTION_STALL;
  pCore->Device.Transfer.sByteLength = 0;

  switch (pCore->Device.Request.bmRequestType & BMREQUEST_TYPE_MASK)
  {
    /*------------------------------------------------------------------------------------------------------*/
    /* Standard requests                                                                                    */
    /*------------------------------------------------------------------------------------------------------*/
    case REQ_TYPE_00_STD:
    {
      _USBDCore_Standard_Request(pCore);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* Class requests                                                                                       */
    /*------------------------------------------------------------------------------------------------------*/
    case REQ_TYPE_01_CLS:
    {
      if (pCore->Class.CallBack_ClassRequest != NULL)
      {
        pCore->Class.CallBack_ClassRequest(&(pCore->Device));
      }
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* Vendor requests                                                                                      */
    /*------------------------------------------------------------------------------------------------------*/
    case REQ_TYPE_02_VND:
    {
      if (pCore->Class.CallBack_VendorRequest != NULL)
      {
        pCore->Class.CallBack_VendorRequest(&(pCore->Device));
      }
      /* Add Vendor requests handler here....                                                               */
      #ifdef USBD_VENDOR_SUPPORT
      USBDVendor_Request(pCore);
      #endif
      break;
    }
  } /* switch (gUSBReq.bmRequestType.byte)                                                                  */

  switch (pCore->Device.Transfer.Action)
  {
    /*------------------------------------------------------------------------------------------------------*/
    /* Control IN                                                                                           */
    /*------------------------------------------------------------------------------------------------------*/
    case USB_ACTION_DATAIN:
    {
      /*----------------------------------------------------------------------------------------------------*/
      /* When the Control IN length is large than the Host required, transfer the length which specified    */
      /* by SETUP Data Packet.                                                                              */
      /*----------------------------------------------------------------------------------------------------*/
      if (pCore->Device.Transfer.sByteLength > pCore->Device.Request.wLength)
      {
        pCore->Device.Transfer.sByteLength = pCore->Device.Request.wLength;
      }
      __DBG_USBPrintf("%06ld EP0IN\t[%02ld]", __DBG_USBCount, pCore->Device.Transfer.sByteLength);

      _USBDCore_ControlIN(pCore);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* Control OUT                                                                                          */
    /*------------------------------------------------------------------------------------------------------*/
    case USB_ACTION_DATAOUT:
    {
      if (pCore->Device.Transfer.sByteLength == 0)
      {
        API_USB_EPTn_WRITE_IN(USBD_EPT0, (u32 *)0, 0);     /* Prepare ZLP ack for Control OUT               */
      }
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* STALL                                                                                                */
    /*------------------------------------------------------------------------------------------------------*/
    default:
    {
      __DBG_USBPrintf("%06ld EP0 STALL\r\n", __DBG_USBCount);

      API_USB_EPTn_SEND_STALL(USBD_EPT0);
      break;
    }
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Stand Request.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Standard_Request(USBDCore_TypeDef *pCore)
{
  u16 USBCmd = *((u16 *)(&(pCore->Device.Request)));

  switch (USBCmd)
  {
    /*------------------------------------------------------------------------------------------------------*/
    /* | bRequest             | Data transfer direction | Type                | Recipient   | Data          */
    /*------------------------------------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------------------------------------*/
    /* | 00_Get Status        | 80_Device-to-Host       | 00_Standard Request | 0_Device    | 0080h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_00_GET_STAT | REQ_DIR_01_D2H | REQ_TYPE_00_STD | REQ_REC_00_DEV):
    {
      __DBG_USBPrintf("%06ld GET DST\t[%02d]\r\n", __DBG_USBCount, pCore->Info.CurrentFeature.uByte);
      _USBDCore_Standard_GetStatus(pCore, Device);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 00_Get Status        | 80_Device-to-Host       | 00_Standard Request | 1_Interface | 0081h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_00_GET_STAT | REQ_DIR_01_D2H | REQ_TYPE_00_STD | REQ_REC_01_INF):
    {
      __DBG_USBPrintf("%06ld GET IST\t[%02d]\r\n", __DBG_USBCount, 0);
      _USBDCore_Standard_GetStatus(pCore, Interface);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 00_Get Status        | 80_Device-to-Host       | 00_Standard Request | 2_Endpoint  | 0082h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_00_GET_STAT | REQ_DIR_01_D2H | REQ_TYPE_00_STD | REQ_REC_02_EPT):
    {
      __DBG_USBPrintf("%06ld GET EST\t[%02d]\r\n", __DBG_USBCount, pCore->Device.Request.wIndex);
      _USBDCore_Standard_GetStatus(pCore, Endpoint);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 01_Clear Feature    | 00_Host-to-Device        | 00_Standard Request | 0_Device    | 0100h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_01_CLR_FETU | REQ_DIR_00_H2D | REQ_TYPE_00_STD | REQ_REC_00_DEV):
    {
      __DBG_USBPrintf("%06ld CLR DFEA\t[%02d]\r\n", __DBG_USBCount, pCore->Device.Request.wValueL);
      _USBDCore_Standard_SetClearFeature(pCore, Device, ClearFeature);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 01_Clear Feature     | 00_Host-to-Device       | 00_Standard Request | 2_Endpoint  | 0102h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_01_CLR_FETU | REQ_DIR_00_H2D | REQ_TYPE_00_STD | REQ_REC_02_EPT):
    {
      __DBG_USBPrintf("%06ld CLR EFEA\t[0x%02x]\r\n", __DBG_USBCount, pCore->Device.Request.wIndex);
      _USBDCore_Standard_SetClearFeature(pCore, Endpoint, ClearFeature);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 03_Set Feature       | 00_Host-to-Device       | 00_Standard Request | 0_Device    | 0300h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_03_SET_FETU | REQ_DIR_00_H2D | REQ_TYPE_00_STD | REQ_REC_00_DEV):
    {
      __DBG_USBPrintf("%06ld SET DFEA\t[%02d]\r\n", __DBG_USBCount, pCore->Device.Request.wValueL);
      _USBDCore_Standard_SetClearFeature(pCore, Device, SetFeature);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 03_Set Feature       | 00_Host-to-Device       | 00_Standard Request | 2_Endpoint  | 0302h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_03_SET_FETU | REQ_DIR_00_H2D | REQ_TYPE_00_STD | REQ_REC_02_EPT):
    {
      __DBG_USBPrintf("%06ld SET EFEA\t[%02d]\r\n", __DBG_USBCount, pCore->Device.Request.wIndex);
      _USBDCore_Standard_SetClearFeature(pCore, Endpoint, SetFeature);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 05_Set Address       | 00_Host-to-Device       | 00_Standard Request | 0_Device    | 0500h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_05_SET_ADDR | REQ_DIR_00_H2D | REQ_TYPE_00_STD | REQ_REC_00_DEV):
    {
      __DBG_USBPrintf("%06ld SET ADDR\t[%02d]\r\n", __DBG_USBCount, pCore->Device.Request.wValueL);
      _USBDCore_Standard_SetAddress(pCore);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 06_Get Descriptor    | 80_Device-to-Host       | 00_Standard Request | 0_Device    | 0680h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_06_GET_DESC | REQ_DIR_01_D2H | REQ_TYPE_00_STD | REQ_REC_00_DEV):
    {
      __DBG_USBPrintf("%06ld GET DDESC\t[%02X]\r\n", __DBG_USBCount, pCore->Device.Request.wValueH);
      _USBDCore_Standard_GetDescriptor(pCore);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 06_Get Descriptor    | 80_Device-to-Host       | 00_Standard Request | 1_Interface | 0681h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_06_GET_DESC | REQ_DIR_01_D2H | REQ_TYPE_00_STD | REQ_REC_01_INF):
    {
      __DBG_USBPrintf("%06ld GET IDESC\t[%02X]\r\n", __DBG_USBCount, pCore->Device.Request.wValueH);
      if (pCore->Class.CallBack_ClassGetDescriptor != NULL)
      {
        pCore->Class.CallBack_ClassGetDescriptor((USBDCore_Device_TypeDef *)&(pCore->Device));
      }
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 08_Get Configuration | 80_Host-to-Device       | 00_Standard Request | 0_Device    | 0880h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_08_GET_CONF | REQ_DIR_01_D2H | REQ_TYPE_00_STD | REQ_REC_00_DEV):
    {
      __DBG_USBPrintf("%06ld GET CONF\t[%02X]\r\n", __DBG_USBCount, pCore->Info.uCurrentConfiguration);
      _USBDCore_Standard_GetConfiguration(pCore);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 09_Set Configuration | 00_Host-to-Device       | 00_Standard Request | 0_Device    | 0900h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_09_SET_CONF | REQ_DIR_00_H2D | REQ_TYPE_00_STD | REQ_REC_00_DEV):
    {
      __DBG_USBPrintf("%06ld SET CONF\t[%02X]\r\n", __DBG_USBCount, pCore->Device.Request.wValueL);
      _USBDCore_Standard_SetConfiguration(pCore);
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 11_Set Interface     | 00_Host-to-Device       | 00_Standard Request | 1_Interface | 0B01h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_11_SET_INF | REQ_DIR_00_H2D | REQ_TYPE_00_STD | REQ_REC_01_INF):
    {
      __DBG_USBPrintf("%06ld SET INF\t[%02X]\r\n", __DBG_USBCount, pCore->Device.Request.wValueL);
      if (pCore->Class.CallBack_ClassSetInterface != NULL)
      {
        pCore->Class.CallBack_ClassSetInterface((USBDCore_Device_TypeDef *)&(pCore->Device));
      }
      break;
    }
    /*------------------------------------------------------------------------------------------------------*/
    /* | 10_Get Interface     | 80_Device-to-Host       | 00_Standard Request | 1_Interface | 0A81h         */
    /*------------------------------------------------------------------------------------------------------*/
    case (REQ_10_GET_INF | REQ_DIR_01_D2H | REQ_TYPE_00_STD | REQ_REC_01_INF):
    {
      __DBG_USBPrintf("%06ld GET INF\t[%02X]\r\n", __DBG_USBCount, pCore->Device.Request.wValueL);
      if (pCore->Class.CallBack_ClassGetInterface != NULL)
      {
        pCore->Class.CallBack_ClassGetInterface((USBDCore_Device_TypeDef *)&(pCore->Device));
      }
      break;
    }
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Standard Request - GET_STATUS.
  * @param  pCore: pointer of USB Device
  * @param  recipient: Recipient
  *         @arg Device:    0
  *         @arg Interface: 1
  *         @arg Endpoint:  2
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Standard_GetStatus(USBDCore_TypeDef *pCore, USBDCore_Recipient_Enum recipient)
{
  pCore->Device.Transfer.uBuffer[1] = 0;
  switch (recipient)
  {
    case Device:
    {
      pCore->Device.Transfer.uBuffer[0] = pCore->Info.CurrentFeature.uByte;
      break;
    }
    case Interface:
    {
      pCore->Device.Transfer.uBuffer[0] = 0;
      break;
    }
    case Endpoint:
    {
      pCore->Device.Transfer.uBuffer[0] = API_USB_EPTn_GET_HALT((USBD_EPTn_Enum)(pCore->Device.Request.wIndex & 0xF));
      break;
    }
    default:
    {
      return;
    }
  }

  pCore->Device.Transfer.pData = (uc8 *)&(pCore->Device.Transfer.uBuffer);
  pCore->Device.Transfer.sByteLength = 2;
  pCore->Device.Transfer.Action = USB_ACTION_DATAIN;

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Standard Request - SET_FEATURE / CLEAR_FEATURE.
  * @param  pCore: pointer of USB Device
  * @param  recipient: Recipient
  *         @arg Device:    0
  *         @arg Interface: 1
  *         @arg Endpoint:  2
  * @param  type:
  *         @arg ClearFeature: 0
            @arg SerFeature:   1
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Standard_SetClearFeature(USBDCore_TypeDef *pCore,
                                               USBDCore_Recipient_Enum recipient,
                                               USBDCore_SetClearFeature_Enum type)
{
  u32 i;
  switch (recipient)
  {
    case Device:
    {
      if (pCore->Device.Request.wValueL == USB_FEATURE_REMOTE_WAKEUP)
      {
        pCore->Info.CurrentFeature.Bits.bRemoteWakeup = type;
        pCore->Device.Transfer.Action = USB_ACTION_DATAIN;
      }
      break;
    }
    case Endpoint:
    {
      i = pCore->Device.Request.wIndex & 0xF;
      if (i != 0)
      {
        if (type == ClearFeature)
        {
          if (pCore->Info.uIsDiscardClearFeature == FALSE)
          {
            API_USB_EPTn_CLR_HALT((USBD_EPTn_Enum)i);
            API_USB_EPTn_CLR_DTG((USBD_EPTn_Enum)i);
          }
        }
        else
        {
          API_USB_EPTn_SET_HALT((USBD_EPTn_Enum)i);
        }
      }
      pCore->Device.Transfer.Action = USB_ACTION_DATAIN;
      break;
    }
    default:
    {
      break;
    }
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Standard Request - SET_ADDRESS.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Standard_SetAddress(USBDCore_TypeDef *pCore)
{
  API_USB_SET_ADDR(pCore->Device.Request.wValueL);
  pCore->Device.Transfer.Action = USB_ACTION_DATAIN;
  pCore->Info.CurrentStatus = USB_STATE_ADDRESS;

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Standard Request - GET_DESCRIPTOR.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Standard_GetDescriptor(USBDCore_TypeDef *pCore)
{
  u32 value = pCore->Device.Request.wValueH;
  uc8 *pTemp;

  switch (value)
  {
    case DESC_TYPE_01_DEV:
    {
      pCore->Device.Transfer.pData = pCore->Device.Desc.pDeviceDesc;
      pCore->Device.Transfer.sByteLength = *(pCore->Device.Desc.pDeviceDesc);
      pCore->Device.Transfer.Action= USB_ACTION_DATAIN;
      break;
    }
    case DESC_TYPE_02_CONFN:
    {
      pCore->Device.Transfer.pData = pCore->Device.Desc.pConfnDesc;
      pCore->Device.Transfer.sByteLength = *(u16 *)((pCore->Device.Desc.pConfnDesc) + 2);
      pCore->Device.Transfer.Action = USB_ACTION_DATAIN;
      break;
    }
    case DESC_TYPE_03_STR:
    {
      value = pCore->Device.Request.wValueL;
      if (value < pCore->Device.Desc.uStringDescNumber)
      {
        if (*(pCore->Device.Desc.ppStringDesc + value) != NULL)
        {
          pTemp = *(pCore->Device.Desc.ppStringDesc + value);
          pCore->Device.Transfer.pData = (uc8 *)(pTemp);
          pCore->Device.Transfer.sByteLength = *(pTemp);
          pCore->Device.Transfer.Action = USB_ACTION_DATAIN;
        }
      }
      break;
    }
  }

  #ifdef USBD_VENDOR_SUPPORT
  USBDVendor_StandardGetDescriptor(pCore);
  #endif

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Standard Request - GET_CONFIGURATION.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Standard_GetConfiguration(USBDCore_TypeDef *pCore)
{
  pCore->Device.Transfer.pData = &(pCore->Info.uCurrentConfiguration);
  pCore->Device.Transfer.sByteLength = 1;
  pCore->Device.Transfer.Action= USB_ACTION_DATAIN;

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Standard Request - SET_CONFIGURATION.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_Standard_SetConfiguration(USBDCore_TypeDef *pCore)
{
  u32 i;

  pCore->Info.uCurrentConfiguration = pCore->Device.Request.wValueL;
  pCore->Device.Transfer.Action= USB_ACTION_DATAIN;

  /* Endpoint n settings                                                                                    */
  for (i = 1; i < MAX_EP_NUM; i++)
  {
    API_USB_EPTn_INIT((USBD_EPTn_Enum)i, pCore->pDriver); // To be modify, init from desc
  }

  pCore->Info.CurrentStatus = USB_STATE_CONFIGURED;

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Control IN transfer.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_ControlIN(USBDCore_TypeDef *pCore)
{
  s32 EP0INLen = API_USB_GET_CTRL_IN_LEN();
  u32 len;

  if (pCore->Device.Transfer.sByteLength != USB_NO_DATA && pCore->Device.Transfer.Action == USB_ACTION_DATAIN)
  {
    if (pCore->Device.Transfer.sByteLength >= EP0INLen)
    {
      len = EP0INLen;
      pCore->Device.Transfer.sByteLength -= len;
    }
    else
    {
      len = pCore->Device.Transfer.sByteLength;
      pCore->Device.Transfer.sByteLength = USB_NO_DATA;
      pCore->Device.Transfer.Action = USB_ACTION_DATAOUT;
    }

    __DBG_USBPrintf("[%02ld]\r\n", len);
    __DBG_USBDump((uc8 *)pCore->Device.Transfer.pData, len);

    API_USB_EPTn_WRITE_IN(USBD_EPT0, (u32 *)pCore->Device.Transfer.pData, len);
    pCore->Device.Transfer.pData = pCore->Device.Transfer.pData + len;
  }
  else
  {
    __DBG_USBPrintf("[-1]\r\n");
  }

  return;
}

/*********************************************************************************************************//**
  * @brief  USB Control OUT transfer.
  * @param  pCore: pointer of USB Device
  * @retval None
  ***********************************************************************************************************/
static void _USBDCore_ControlOUT(USBDCore_TypeDef *pCore)
{
  u32 len;

  if (pCore->Device.Transfer.sByteLength != USB_NO_DATA && pCore->Device.Transfer.Action == USB_ACTION_DATAOUT)
  {
    len = API_USB_EPTn_READ_OUT(USBD_EPT0, (u32 *)pCore->Device.Transfer.pData, MAX_CONTROL_OUT_SIZE);

    __DBG_USBPrintf("[%02ld]\r\n", len);
    __DBG_USBDump((uc8 *)pCore->Device.Transfer.pData, len);

    pCore->Device.Transfer.pData = pCore->Device.Transfer.pData + len;
    pCore->Device.Transfer.sByteLength -= len;

    if (pCore->Device.Transfer.sByteLength == 0)
    {
      pCore->Device.Transfer.Action = USB_ACTION_DATAIN;
      if (pCore->Device.Transfer.CallBack_OUT.func != NULL)
      {
        pCore->Device.Transfer.CallBack_OUT.func(pCore->Device.Transfer.CallBack_OUT.uPara);
        pCore->Device.Transfer.CallBack_OUT.func = NULL;
      }
      pCore->Device.Transfer.sByteLength = USB_NO_DATA;
      API_USB_EPTn_WRITE_IN(USBD_EPT0, (u32 *)0, 0);
    }
  }
  else
  {
    __DBG_USBPrintf("[-1]\r\n");
  }

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
