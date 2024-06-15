/*********************************************************************************************************//**
 * @file    ht32_usbd_core.h
 * @version $Rev:: 2555         $
 * @date    $Date:: 2022-03-15 #$
 * @brief   The header file of standard protocol related function for HT32 USB Device Library.
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
// <<< Use Configuration Wizard in Context Menu >>>

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_USBD_CORE_H
#define __HT32_USBD_CORE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/

/** @addtogroup HT32_USBD_Library
  * @{
  */

/** @addtogroup USBDCore
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Settings USB Device Core settings
  * @{
  */
/* USBD Debug mode                                                                                          */
//<e0.0> Enable USB Debug mode
//<o1.0> Dump USB Debug data
#ifndef USBDCORE_DEBUG
  #define USBDCORE_DEBUG                  (0)       /*!< Enable USB Debug mode                              */
  #define USBDCORE_DEBUG_DATA             (0)       /*!< Dump USB Debug data                                */
#endif
/**
  * @}
  */

/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Exported_Type USB Device Core exported types
  * @{
  */
/**
 * @brief USB Device Request.
 */
typedef __PACKED_H struct
{
  uc8 bmRequestType;
  uc8 bRequest;
  uc8 wValueL;
  uc8 wValueH;
  uc16 wIndex;
  uc16 wLength;
} __PACKED_F USBDCore_Request_TypeDef;

/**
 * @brief USB Descriptor.
 */
typedef struct
{
  uc8 *pDeviceDesc;                                 /*!< Device Descriptor                                  */
  uc8 *pConfnDesc;                                  /*!< Configuration Descriptor                           */
  uc8 **ppStringDesc;                               /*!< String Descriptor                                  */
  u32 uStringDescNumber;                            /*!< Count of String Descriptor                         */
} USBDCore_Desc_TypeDef;

/**
 * @brief STALL, control IN or control OUT.
 */
typedef enum
{
  USB_ACTION_STALL   = 0,
  USB_ACTION_DATAIN  = 1,
  USB_ACTION_DATAOUT = 2,
} USBDCore_Action_Enum;

/**
 * @brief Call back function.
 */
typedef struct
{
  void (*func)  (u32 uPara);                        /*!< Call back function pointer                         */
  u32 uPara;                                        /*!< Parameter of call back function                    */
} USBDCore_CallBack_TypeDef;

/**
 * @brief Parameter for control IN/OUT Transfer.
 */
typedef struct
{
  u8 uBuffer[2];                                    /*!< Temporary buffer                                   */
  uc8 *pData;                                       /*!< Pointer of control IN/OUT Data                     */
  s32 sByteLength;                                  /*!< Total length for control IN/OUT Transfer           */
  USBDCore_Action_Enum Action;                      /*!< STALL, control IN or control OUT                   */
  USBDCore_CallBack_TypeDef CallBack_OUT;           /*!< Call back function pointer for Control OUT         */
} USBDCore_Transfer_TypeDef;

/**
 * @brief USB Device.
 */
typedef struct
{
  USBDCore_Request_TypeDef  Request;                /*!< USB Device Request                                 */
  USBDCore_Desc_TypeDef     Desc;                   /*!< USB Descriptor                                     */
  USBDCore_Transfer_TypeDef Transfer;               /*!< Parameter for control IN/OUT Transfer              */
} USBDCore_Device_TypeDef;

/**
 * @brief Bit access for CurrentFeature.
 */
typedef __PACKED_H struct _FEATURE_TYPEBIT
{
  unsigned bSelfPowered  :1;                        /*!< Remote Wakeup feature                              */
  unsigned bRemoteWakeup :1;                        /*!< Self Powered                                       */
} __PACKED_F USBDCore_Feature_TypeBit;

/**
 * @brief For Set/ClearFeature and GetStatus request.
 */
typedef __PACKED_H union _FEATURE_TYPEDEF
{
  u8 uByte;                                         /*!< Byte access for CurrentFeature                     */
  USBDCore_Feature_TypeBit Bits;                    /*!< Bit access for CurrentFeature                      */
} __PACKED_F USBDCore_Feature_TypeDef;

/**
 * @brief Device State.
 */
typedef enum
{
  USB_STATE_UNCONNECTED   = 0,
  USB_STATE_ATTACHED      = 1,
  USB_STATE_POWERED       = 2,
  USB_STATE_SUSPENDED     = 3,
  USB_STATE_DEFAULT       = 4,
  USB_STATE_ADDRESS       = 5,
  USB_STATE_CONFIGURED    = 6,
} USBDCore_Status_Enum;

/**
 * @brief USB Device information.
 */
typedef struct
{
  u8 uCurrentConfiguration;                         /*!< For Set/GetConfiguration request                   */
  u8 uCurrentInterface;                             /*!< For Set/GetInterface request                       */
  volatile USBDCore_Status_Enum CurrentStatus;      /*!< Device State                                       */
  USBDCore_Status_Enum LastStatus;                  /*!< Device State before SUSPEND                        */
  USBDCore_Feature_TypeDef CurrentFeature;          /*!< For Set/ClearFeature and GetStatus request         */
  u32 uIsDiscardClearFeature;                       /*!< Discard ClearFeature flag for Mass Storage         */
} USBDCore_Info_TypeDef;

typedef void (*USBDCore_CallBackClass_Typedef)  (USBDCore_Device_TypeDef *pDev);
typedef void (*USBDCore_CallBackVendor_Typedef) (USBDCore_Device_TypeDef *pDev);
typedef void (*USBDCore_CallBackEPTn_Typedef)   (USBD_EPTn_Enum EPTn);

/**
 * @brief USB Class call back function.
 */
typedef struct
{
  USBDCore_CallBack_TypeDef      CallBack_MainRoutine;        /*!< Class main routine call back function    */
  USBDCore_CallBack_TypeDef      CallBack_Reset;              /*!< Class RESET call back function           */
  USBDCore_CallBack_TypeDef      CallBack_StartOfFrame;       /*!< Class SOF call back function             */
  USBDCore_CallBackClass_Typedef CallBack_ClassGetDescriptor; /*!< Class Get Descriptor call back function  */
  USBDCore_CallBackClass_Typedef CallBack_ClassSetInterface;  /*!< Set Interface call back function         */
  USBDCore_CallBackClass_Typedef CallBack_ClassGetInterface;  /*!< Get Interface call back function         */
  USBDCore_CallBackClass_Typedef CallBack_ClassRequest;       /*!< Class Request call back function         */
  USBDCore_CallBackVendor_Typedef CallBack_VendorRequest;     /*!< Vendor Request call back function        */
  USBDCore_CallBackEPTn_Typedef  CallBack_EPTn[MAX_EP_NUM];   /*!< Endpoint n call back function            */
} USBDCore_Class_TypeDef;

/**
 * @brief USB Device Power related call back function.
 */
typedef struct
{
  USBDCore_CallBack_TypeDef      CallBack_Suspend;
} USBDCore_Power_TypeDef;

/**
 * @brief Major structure of USB Library.
 */
typedef struct
{
  USBDCore_Device_TypeDef   Device;       /*!< USB Device                                                   */
  USBDCore_Info_TypeDef     Info;         /*!< USB Device information                                       */
  USBDCore_Class_TypeDef    Class;        /*!< USB Class call back function                                 */
  u32                       *pDriver;     /*!< USB Device Driver initialization structure                   */
  USBDCore_Power_TypeDef    Power;        /*!< USB Device Power related call back function                  */
} USBDCore_TypeDef;

/*----------------------------------------------------------------------------------------------------------*/
/* Variable architecture of USB Library                                                                     */
/*----------------------------------------------------------------------------------------------------------*/
/* USBCore - USBDCore_TypeDef                                   Major structure of USB Library              */
/*   USBCore.Device - USBDCore_Device_TypeDef                   USB Device                                  */
/*     USBCore.Device.Request - USBDCore_Request_TypeDef        USB Device Request                          */
/*       USBCore.Device.Request.bmRequestType                                                               */
/*       USBCore.Device.Request.bRequest                                                                    */
/*       USBCore.Device.Request.wValueL                                                                     */
/*       USBCore.Device.Request.wValueH                                                                     */
/*       USBCore.Device.Request.wIndex                                                                      */
/*       USBCore.Device.Request.wLength                                                                     */
/*     USBCore.Device.Desc - USBDCore_Desc_TypeDef              USB Descriptor                              */
/*       USBCore.Device.Desc.pDeviceDesc                        Device Descriptor                           */
/*       USBCore.Device.Desc.pConfnDesc                         Configuration Descriptor                    */
/*       USBCore.Device.Desc.pStringDesc[DESC_NUM_STRING]       String Descriptor                           */
/*       USBCore.Device.Desc.uStringDescNumber                  Count of String Descriptor                  */
/*     USBCore.Device.Transfer - USBDCore_Transfer_TypeDef      Parameter for control IN/OUT Transfer       */
/*       USBCore.Device.Transfer.uBuffer[2]                     Temporary buffer                            */
/*       USBCore.Device.Transfer.pData                          Pointer of control IN/OUT Data              */
/*       USBCore.Device.Transfer.sByteLength                    Total length for control IN/OUT Transfer    */
/*       USBCore.Device.Transfer.Action - USBDCore_Action_Enum  STALL, control IN or control OUT            */
/*       USBCore.Device.Transfer.CallBack_OUT.func(uPara)       Call back function pointer for Control OUT  */
/*       USBCore.Device.Transfer.CallBack_OUT.uPara             Parameter of Control OUT call back function */
/*                                                                                                          */
/*   USBCore.Info - USBDCore_Info_TypeDef                       USB Device information                      */
/*     USBCore.Info.uCurrentConfiguration                       For Set/GetConfiguration request            */
/*     USBCore.Info.uCurrentInterface                           For Set/GetInterface request                */
/*     USBCore.Info.CurrentStatus - USBDCore_Status_Enum        Device State                                */
/*     USBCore.Info.LastStatus - USBDCore_Status_Enum           Device State before SUSPEND                 */
/*     USBCore.Info.CurrentFeature - USBDCore_Feature_TypeDef   For Set/ClearFeature and GetStatus request  */
/*       USBCore.Info.CurrentFeature.uByte                      Byte access for CurrentFeature              */
/*       USBCore.Info.CurrentFeature.Bits.bRemoteWakeup         Remote Wakeup feature                       */
/*       USBCore.Info.CurrentFeature.Bits.bSelfPowered          Self Powered                                */
/*     USBCore.Info.uIsDiscardClearFeature                      Discard ClearFeature flag for Mass Storage  */
/*                                                                                                          */
/*   USBCore.Class - USBDCore_Class_TypeDef                     USB Class call back function                */
/*     USBCore.Class.CallBack_MainRoutine.func(uPara)           Class main routine call back function       */
/*     USBCore.Class.CallBack_MainRoutine.uPara                 Parameter of class main routine             */
/*     USBCore.Class.CallBack_Reset.func(uPara)                 Class RESET call back function              */
/*     USBCore.Class.CallBack_Reset.uPara                       Parameter of RESET call back function       */
/*     USBCore.Class.CallBack_StartOfFrame.func(uPara)          Class SOF call back function                */
/*     USBCore.Class.CallBack_StartOfFrame.uPara                Parameter of SOF call back function         */
/*     USBCore.Class.CallBack_ClassGetDescriptor(pDev)          Class Get Descriptor call back function     */
/*     USBCore.Class.CallBack_ClassSetInterface(pDev)           Set Interface call back function            */
/*     USBCore.Class.CallBack_ClassGetInterface(pDev)           Get Interface call back function            */
/*     USBCore.Class.CallBack_ClassRequest(pDev)                Class Request call back function            */
/*     USBCore.Class.CallBack_EPTn[MAX_EP_NUM](EPTn)            Endpoint n call back function               */
/*                                                                                                          */
/*   USBCore.pDriver                                            USB Device Driver initialization structure  */
/*                                                                                                          */
/*   USBCore.Power - USBDCore_Power_TypeDef                     USB Device Power related call back function */
/*     USBCore.Power.CallBack_Suspend.func(uPara)               System low power function for SUSPEND       */
/*     USBCore.Power.CallBack_Suspend.uPara                     Parameter of system low power function      */
/*----------------------------------------------------------------------------------------------------------*/

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Exported_Constant USB Device Core exported constants
  * @{
  */

/** @defgroup USBDCore_Descriptor Definitions for USB descriptor
  * @{
  */
#define DESC_TYPE_01_DEV                  (0x1)
#define DESC_TYPE_02_CONFN                (0x2)
#define DESC_TYPE_03_STR                  (0x3)
#define DESC_TYPE_04_INF                  (0x4)
#define DESC_TYPE_05_EPT                  (0x5)
#define DESC_TYPE_06_DEV_QLF              (0x6)
#define DESC_TYPE_08_INF_PWR              (0x8)

#define DESC_CLASS_00_BY_INF              (0x00)
#define DESC_CLASS_01_AUDIO               (0x01)
#define DESC_CLASS_02_CDC_CTRL            (0x02)
#define DESC_CLASS_03_HID                 (0x03)
#define DESC_CLASS_05_PHY                 (0x05)
#define DESC_CLASS_06_STILL_IMG           (0x06)
#define DESC_CLASS_07_PRINTER             (0x07)
#define DESC_CLASS_08_MASS_STORAGE        (0x08)
#define DESC_CLASS_09_HUB                 (0x09)
#define DESC_CLASS_0A_CDC_DATA            (0x0A)
#define DESC_CLASS_0B_SMART_CARD          (0x0B)
#define DESC_CLASS_0E_VIDEO               (0x0E)
#define DESC_CLASS_0F_PHD                 (0x0F)
#define DESC_CLASS_FF_VENDOR              (0xFF)

#define DESC_LEN_DEV                      ((u32)(18))
#define DESC_LEN_CONFN                    ((u32)(9))
#define DESC_LEN_INF                      ((u32)(9))
#define DESC_LEN_EPT                      ((u32)(7))
/**
  * @}
  */

/** @defgroup USBDCore_Request Definitions for USB Request
  * @{
  */
#define REQ_DIR_00_H2D                    (0 << 7)
#define REQ_DIR_01_D2H                    (1 << 7)

#define REQ_TYPE_00_STD                   (0 << 5)
#define REQ_TYPE_01_CLS                   (1 << 5)
#define REQ_TYPE_02_VND                   (2 << 5)

#define REQ_REC_00_DEV                    (0)
#define REQ_REC_01_INF                    (1)
#define REQ_REC_02_EPT                    (2)
/**
  * @}
  */

/**
 * @brief For USBDCore_EPTReadOUTData function.
 */
#define USB_DISCARD_OUT_DATA              (0)

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Exported_Macro USB Device Core exported macros
  * @{
  */
#define __DBG_USBPrintf(...)
#define __DBG_USBDump(a, b)

#if (USBDCORE_DEBUG == 1)
  #ifndef RETARGET_IS_USB
    extern u32 __DBG_USBCount;
    #undef __DBG_USBPrintf
    #define __DBG_USBPrintf printf
    #if (USBDCORE_DEBUG_DATA == 1)
      #undef __DBG_USBDump
      void __DBG_USBDump(uc8 *memory, u32 len);
    #endif
  #endif
#endif

/**
 * @brief Convert Half-Word to Byte for descriptor.
 */
#define DESC_H2B(Val)                     ((u8)(Val & 0x00FF)), ((u8)((Val & 0xFF00) >> 8))

/**
 * @brief Padding 0 automatically for String descriptor.
 */
#define DESC_CHAR(c)                      (c), (0)

/**
 * @brief Calculate String length for String descriptor.
 */
#define DESC_STRLEN(n)                    (n * 2 + 2)

/**
 * @brief Calculate power for Configuration descriptor.
 */
#define DESC_POWER(mA)                    (mA / 2)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup USBDCore_Exported_Functions USB Device Core exported functions
  * @{
  */
#define USBDCore_DeInit                 API_USB_DEINIT
#define USBDCore_EPTReset               API_USB_EPTn_RESET
#define USBDCore_EPTGetBufferLen        API_USB_EPTn_GET_BUFFLEN
#define USBDCore_EPTGetTransferCount    API_USB_EPTn_GET_CNT
#define USBDCore_EPTSetSTALL            API_USB_EPTn_SET_HALT
#define USBDCore_EPTWaitSTALLSent       API_USB_EPTn_WAIT_STALL_SENT
#define USBDCore_EPTClearDataToggle     API_USB_EPTn_CLR_DTG

#define USBDCore_EPTWriteINData         API_USB_EPTn_WRITE_IN
#define USBDCore_EPTReadOUTData         API_USB_EPTn_READ_OUT
#define USBDCore_EPTReadMemory          API_USB_EPTn_READ_MEM

void USBDCore_Init(USBDCore_TypeDef *pCore);
void USBDCore_IRQHandler(USBDCore_TypeDef *pCore);
void USBDCore_MainRoutine(USBDCore_TypeDef *pCore);
u32  USBDCore_IsSuspend(USBDCore_TypeDef *pCore);
u32  USBDCore_GetRemoteWakeUpFeature(USBDCore_TypeDef *pCore);
void USBDCore_TriggerRemoteWakeup(void);
USBDCore_Status_Enum USBDCore_GetStatus(void);

void USBDCore_EPTReset(USBD_EPTn_Enum USBD_EPTn);
u32  USBDCore_EPTGetBufferLen(USBD_EPTn_Enum USBD_EPTn);
u32  USBDCore_EPTGetTransferCount(USBD_EPTn_Enum USBD_EPTn, USBD_TCR_Enum type);
void USBDCore_EPTSetSTALL(USBD_EPTn_Enum USBD_EPTn);
void USBDCore_EPTWaitSTALLSent(USBD_EPTn_Enum USBD_EPTn);
void USBDCore_EPTClearDataToggle(USBD_EPTn_Enum USBD_EPTn);

u32  USBDCore_EPTWriteINData(USBD_EPTn_Enum USBD_EPTn, u32 *pFrom, u32 len);
u32  USBDCore_EPTReadOUTData(USBD_EPTn_Enum USBD_EPTn, u32 *pTo, u32 len);
u32  USBDCore_EPTReadMemory(USBD_EPTn_Enum USBD_EPTn, u32 *pTo, u32 len);
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

#endif /* __HT32_USBD_CORE_H -------------------------------------------------------------------------------*/
