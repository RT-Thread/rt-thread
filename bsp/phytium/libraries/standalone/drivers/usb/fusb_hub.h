/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fusb_hub.h
 * Date: 2022-02-11 13:33:09
 * LastEditTime: 2022-02-17 17:49:20
 * Description:  This files is for definition of USB hub device function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#ifndef  FUSB_HUB_H
#define  FUSB_HUB_H

/***************************** Include Files *********************************/

#include "fusb.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/
enum
{
    FUSB_HUB_SUBCLASS_DEFAULT = 0x0
};

enum
{
    FUSB_HUB_PROTOCOL_FULL_SPEED = 0x0,
    FUSB_HUB_PROTOCOL_HIGH_SPEED_WITH_SINGLE_TT = 0x1,
    FUSB_HUB_PROTOCOL_HIGH_SPEED_WITH_MULTIPLE_TT = 0x2
};

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
/* USB Hub的初始化函数，由应用程序注册到FUSB框架中 */
void FUsbHubInit(FUsbDev *dev);

#ifdef __cplusplus
}
#endif


#endif
