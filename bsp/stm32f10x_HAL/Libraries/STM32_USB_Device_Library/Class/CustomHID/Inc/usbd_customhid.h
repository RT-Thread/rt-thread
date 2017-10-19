/**
  ******************************************************************************
  * @file    usbd_customhid.h
  * @author  MCD Application Team
  * @version V2.4.2
  * @date    11-December-2015
  * @brief   header file for the usbd_customhid.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __USB_CUSTOMHID_H
#define __USB_CUSTOMHID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_ioreq.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */
  
/** @defgroup USBD_CUSTOM_HID
  * @brief This file is the Header file for USBD_customhid.c
  * @{
  */ 


/** @defgroup USBD_CUSTOM_HID_Exported_Defines
  * @{
  */ 
#define CUSTOM_HID_EPIN_ADDR                 0x81
#define CUSTOM_HID_EPIN_SIZE                 0x02

#define CUSTOM_HID_EPOUT_ADDR                0x01
#define CUSTOM_HID_EPOUT_SIZE                0x02

#define USB_CUSTOM_HID_CONFIG_DESC_SIZ       41
#define USB_CUSTOM_HID_DESC_SIZ              9

#define CUSTOM_HID_DESCRIPTOR_TYPE           0x21
#define CUSTOM_HID_REPORT_DESC               0x22


#define CUSTOM_HID_REQ_SET_PROTOCOL          0x0B
#define CUSTOM_HID_REQ_GET_PROTOCOL          0x03

#define CUSTOM_HID_REQ_SET_IDLE              0x0A
#define CUSTOM_HID_REQ_GET_IDLE              0x02

#define CUSTOM_HID_REQ_SET_REPORT            0x09
#define CUSTOM_HID_REQ_GET_REPORT            0x01
/**
  * @}
  */ 


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */
typedef enum
{
  CUSTOM_HID_IDLE = 0,
  CUSTOM_HID_BUSY,
}
CUSTOM_HID_StateTypeDef; 

typedef struct _USBD_CUSTOM_HID_Itf
{
  uint8_t                  *pReport;
  int8_t (* Init)          (void);
  int8_t (* DeInit)        (void);
  int8_t (* OutEvent)      (uint8_t, uint8_t );   

}USBD_CUSTOM_HID_ItfTypeDef;

typedef struct
{
  uint8_t              Report_buf[USBD_CUSTOMHID_OUTREPORT_BUF_SIZE];
  uint32_t             Protocol;   
  uint32_t             IdleState;  
  uint32_t             AltSetting;
  uint32_t             IsReportAvailable;  
  CUSTOM_HID_StateTypeDef     state;  
}
USBD_CUSTOM_HID_HandleTypeDef; 
/**
  * @}
  */ 



/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */ 

extern USBD_ClassTypeDef  USBD_CUSTOM_HID;
#define USBD_CUSTOM_HID_CLASS    &USBD_CUSTOM_HID
/**
  * @}
  */ 

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */ 
uint8_t USBD_CUSTOM_HID_SendReport (USBD_HandleTypeDef *pdev, 
                                 uint8_t *report,
                                 uint16_t len);



uint8_t  USBD_CUSTOM_HID_RegisterInterface  (USBD_HandleTypeDef   *pdev, 
                                             USBD_CUSTOM_HID_ItfTypeDef *fops);

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif  /* __USB_CUSTOMHID_H */
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
