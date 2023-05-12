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
 * FilePath: fusb_private.h
 * Date: 2022-02-11 13:33:11
 * LastEditTime: 2022-02-18 09:21:22
 * Description:  This files is for definition of internal function interface
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#ifndef  FUSB_PRIVATE_H
#define  FUSB_PRIVATE_H

/***************************** Include Files *********************************/
#ifdef __aarch64__
    #include "faarch64.h"
#else
    #include "fcp15.h"
#endif

#include "fkernel.h"
#include "fio.h"
#include "fassert.h"
#include "fusb.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FUSB_REG32_GET_BITS(x, a, b)                  (u32)((((u32)(x)) & GENMASK(a, b)) >> b)
#define FUSB_REG32_SET_BITS(x, a, b)                  (u32)((((u32)(x)) << b) & GENMASK(a, b))
#define FUSB_REG64_GET_BITS(x, a, b)                  (u64)((((u64)(x)) & GENMASK_ULL(a, b)) >> b)
#define FUSB_REG64_SET_BITS(x, a, b)                  (u64)((((u64)(x)) << b) & GENMASK_ULL(a, b))

/************************** Function Prototypes ******************************/
/* 创建USB控制器实例，添加到USB实例的Hc链表中 */
FUsbHc *FUsbAllocateHc(FUsb *instance);

/* 删除USB控制器实例，从USB实例的Hc链表中删去 */
void FUsbDetachHc(FUsbHc *controller);

/* 初始化USB设备 */
FUsbDev *FUsbInitDevEntry(FUsbHc *controller, int slot_id);

/* 根据USB设备速度，选择最大包长度 */
int FUsbDecodeMaxPacketSz0(FUsbSpeed speed, u8 bMaxPacketSize0);

/* 据设备速度获取最大包长度 */
int FUsbSpeedtoDefaultMaxPacketSz(FUsbSpeed speed);

/* 配置USB配置描述符解析器 */
FError FUsbSetupConfigParser(FUsbDev *dev, const void *buf, u32 buf_len);

/* 去初始化USB配置描述符解析器 */
void FUsbRevokeConfigParser(FUsbDev *dev);

/* 初始化字符串描述符解析器 */
void FUsbSetupStringParser(FUsbDev *dev);

/* 去初始化字符串描述符解析器 */
void FUsbRevokeStringParser(FUsbDev *dev);

/* 检索字符串描述符，保存在FUsbStringParser结构中 */
FError FUsbSearchStringDescriptor(FUsb *instance, FUsbDev *dev, u8 id);

/* 获取刚刚检索到的字符串描述符内容 */
const char *FUsbGetString(const FUsbDev *const dev);

/* 从配置描述符解析器中获取指定类型的描述符（端点描述符/接口描述符） */
const FUsbDescriptor *FUsbGetDescriptorFromParser(FUsbConfigParser *parser, FUsbDescriptorType type);

/* 默认的USB设备初始化函数 */
void FUsbNopDevInit(FUsbDev *dev);

/* 默认的USB设备初始化函数 */
void FUsbGenericDevInit(FUsbDev *dev);

/* 打印设备描述符信息 */
void FUsbDumpDeviceDescriptor(const FUsbDeviceDescriptor *descriptor);

/* 打印配置描述符信息 */
void FUsbDumpConfigDescriptor(const FUsbConfigurationDescriptor *descriptor);

/* 打印接口描述符信息 */
void FUsbDumpInterfaceDescriptor(const FUsbInterfaceDescriptor *descriptor);

/* 打印端点描述符信息 */
void FUsbDumpEndpointDescriptor(const FUsbEndpointDescriptor *descriptor);

#ifdef __cplusplus
}
#endif

#endif