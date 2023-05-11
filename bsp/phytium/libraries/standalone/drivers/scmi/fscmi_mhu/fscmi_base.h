/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
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
 * FilePath: fscmi_base.h
 * Date: 2022-12-31 21:38:51
 * LastEditTime: 2022-12-31 21:38:51
 * Description:  This file is for base protocol message
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0 liushengming 2023/01/04 init
 */



#ifndef FSCMI_BASE_PROTOCOL_H
#define FSCMI_BASE_PROTOCOL_H

#include "ftypes.h"
#include "ferror_code.h"
#include "fparameters.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FSCMI_BASE_PROTOCOL_VERSION                            0x0
#define FSCMI_BASE_PROTOCOL_ATTRIBUTES                         0x1
#define FSCMI_BASE_PROTOCOL_MESSAGE_ATTRIBUTES                 0x2
#define FSCMI_BASE_PROTOCOL_DISCOVER_VENDOR                    0x3
#define FSCMI_BASE_PROTOCOL_DISCOVER_SUB_VENDOR                0x4
#define FSCMI_BASE_PROTOCOL_DISCOVER_IMPLEMENTATION_VERSION    0x5
#define FSCMI_BASE_PROTOCOL_DISCOVER_LIST_PROTOCOLS            0x6
#define FSCMI_BASE_PROTOCOL_DISCOVER_AGENT                     0x7
#define FSCMI_BASE_PROTOCOL_NOTIFY_ERRORS                      0x8
#define FSCMI_BASE_PROTOCOL_SET_DEVICE_PERMISSIONS             0x9
#define FSCMI_BASE_PROTOCOL_SET_PROTOCOL_PERMISSIONS           0xa
#define FSCMI_BASE_PROTOCOL_RESET_AGENT_CONFIGURATION          0xb

FError FScmiBaseInit(FScmi *instance_p);

#ifdef __cplusplus
}
#endif


#endif

