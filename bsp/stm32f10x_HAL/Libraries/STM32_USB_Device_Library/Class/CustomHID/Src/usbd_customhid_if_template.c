/**
  ******************************************************************************
  * @file    usbd_customhid_if_template.c
  * @author  MCD Application Team
  * @version V2.4.2
  * @date    11-December-2015
  * @brief   USB Device Custom HID interface file.
  *		     This template should be copied to the user folder, renamed and customized
  *          following user needs.
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_customhid_if_template.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static int8_t TEMPLATE_CUSTOM_HID_Init     (void);
static int8_t TEMPLATE_CUSTOM_HID_DeInit   (void);
static int8_t TEMPLATE_CUSTOM_HID_OutEvent (uint8_t event_idx, uint8_t state);
/* Private variables ---------------------------------------------------------*/
USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_template_fops = 
{
  TEMPLATE_CUSTOM_HID_ReportDesc,
  TEMPLATE_CUSTOM_HID_Init,
  TEMPLATE_CUSTOM_HID_DeInit,
  TEMPLATE_CUSTOM_HID_OutEvent,
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  TEMPLATE_CUSTOM_HID_Init
  *         Initializes the CUSTOM HID media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t TEMPLATE_CUSTOM_HID_Init(void)
{

  return (0);
}

/**
  * @brief  TEMPLATE_CUSTOM_HID_DeInit
  *         DeInitializes the CUSTOM HID media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t TEMPLATE_CUSTOM_HID_DeInit(void)
{
  /*
     Add your deinitialization code here 
  */  
  return (0);
}


/**
  * @brief  TEMPLATE_CUSTOM_HID_Control
  *         Manage the CUSTOM HID class events       
  * @param  event_idx: event index
  * @param  state: event state
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t TEMPLATE_CUSTOM_HID_OutEvent  (uint8_t event_idx, uint8_t state)
{ 

  return (0);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
