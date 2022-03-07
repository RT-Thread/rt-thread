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
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef __USBD_CLASS_MSC
#define __USBD_CLASS_MSC

#include "usbd_core.h"


#define BOT_GET_MAX_LUN              0xFE
#define BOT_RESET                    0xFF

void USBD_MSC_ClassHandler(USBD_DevReqData_T *reqData);

#endif
