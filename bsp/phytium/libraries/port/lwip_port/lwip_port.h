/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: lwip_port.h
 * Created Date: 2023-11-28 17:22:15
 * Last Modified: 2023-12-07 11:18:28
 * Description:  This file is for
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 *  1.0   liuzhihong  2023/11/28        first release
 *  2.0   huangjin    2025/06/11        add support for xmac_msg
 */
#ifndef LWIP_PORT_H
#define LWIP_PORT_H

#ifdef BSP_USING_ETH
#include "drv_xmac.h"
#define LWIP_PORT_INTERFACE_SGMII  FXMAC_OS_INTERFACE_SGMII
#define LWIP_PORT_INTERFACE_RGMII  FXMAC_OS_INTERFACE_RGMII
#elif defined(BSP_USING_ETH_MSG)
#include "drv_xmac_msg.h"
#define LWIP_PORT_INTERFACE_SGMII  FXMAC_MSG_OS_INTERFACE_SGMII
#define LWIP_PORT_INTERFACE_RGMII  FXMAC_MSG_OS_INTERFACE_RGMII
#endif

#endif