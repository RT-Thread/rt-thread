/*!
 * @file        usbd_class_msc.h
 *
 * @brief       MSC Class handler file head file
 *
 * @version     V1.0.0
 *
 * @date        2021-12-06
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
#ifndef __CLASS_MSC_
#define __CLASS_MSC_

/* Includes */
#include "usbd_core.h"

/** @addtogroup USB_Driver_Library USB Driver Library
  @{
*/

/** @addtogroup Core_Device Core Device
  @{
*/

/** @addtogroup Class
  @{
*/

/** @addtogroup MSC
  @{
*/

/** @defgroup MSC_Macros Macros
  @{
*/

#define BOT_GET_MAX_LUN              0xFE
#define BOT_RESET                    0xFF

/**@} end of group MSC_Macros */

/** @defgroup MSC_Enumerations Enumerations
  @{
*/

/**@} end of group MSC_Enumerations */

/** @defgroup MSC_Structures Structures
  @{
*/

/**@} end of group MSC_Structures */

/** @defgroup MSC_Variables Variables
  @{
*/

/**@} end of group MSC_Variables */

/** @defgroup MSC_Functions Functions
  @{
*/

void USBD_MSC_ClassHandler(USBD_DevReqData_T* reqData);

#endif

/**@} end of group MSC_Functions */
/**@} end of group MSC */
/**@} end of group Class */
/**@} end of group Core_Device */
/**@} end of group USB_Driver_Library */
