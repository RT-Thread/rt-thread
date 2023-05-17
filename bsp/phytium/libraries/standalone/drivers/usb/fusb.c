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
 * FilePath: fusb.c
 * Date: 2022-02-11 13:33:11
 * LastEditTime: 2022-02-18 09:22:06
 * Description:  This file is for implmentation of USB user API
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu  2022/2/8     init commit
 */

#include <string.h>

#include "fdebug.h"
#include "fsleep.h"

#include "fusb_private.h"
#include "fxhci.h"

#define FUSB_DEBUG_TAG "FUSB"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...) FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...) FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

#define FUSB_DR_DESC FUsbGenerateReqType(FUSB_REQ_DEVICE_TO_HOST, FUSB_REQ_TYPE_STANDARD, FUSB_REQ_RECP_DEV)

/*
 * Certain Lexar / Micron USB 2.0 disks will fail the FUsbGetDescriptor(FUSB_DESC_TYPE_CONFIG)
 * call due to timing issues. Work around this by making extra attempts on
 * failure.
 */
#define FUSB_GET_DESCRIPTOR_RETRIES 3

/**
 * @name: FUsbCfgInitialize
 * @msg: 初始化USB实例
 * @return {FError} 初始化错误码
 * @param {FUsb} *instance, USB实例
 * @param {const FUsbConfig} *input_config, USB输入配置
 * @note 在PCIE模式下，USB Hc实例在PCIE总线发现控制器后创建
 */
FError FUsbCfgInitialize(FUsb *instance, const FUsbConfig *input_config)
{
    FASSERT(instance && input_config);
    FError ret = FUSB_SUCCESS;

    if (input_config != &instance->config)
    {
        instance->config = *input_config;
    }

    instance->hc = NULL; /* non usb host attached */

    /* create usb hc instance, which will be add as the head of hc list */
    if (NULL == FXhciHcInit(instance, instance->config.base_addr))
    {
        ret = FUSB_ERR_ALLOCATE_FAIL;
    }

    if (FUSB_SUCCESS == ret)
    {
        instance->is_ready = FT_COMPONENT_IS_READY;
    }

    return ret;
}

/**
 * @name: FUsbDeInitialize
 * @msg: 去初始化USB实例
 * @return {*}
 * @param {FUsb} *instance, USB实例
 */
void FUsbDeInitialize(FUsb *instance)
{
    FASSERT(instance);

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FUSB_ERROR("USB not ready !!!");
        return;
    }

    instance->is_ready = 0;

    return;
}

/**
 * @name: FUsbPoll
 * @msg: 轮询所有的USB控制器连接的所有设备, 更新设备拓扑
 * @return {*}
 * @param {FUsb} *instance, USB实例
 */
void FUsbPoll(FUsb *instance)
{
    FASSERT(instance);

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FUSB_ERROR("USB not ready !!!");
        return;
    }

    if (FUsbPollPrepare)
    {
        FUsbPollPrepare(instance);
    }

    FUsbHc *controller = instance->hc;
    if (controller != NULL)
    {
        int i;
        for (i = 0; i < FUSB_MAX_DEV_NUM; i++)
        {
            if (controller->devices[i] != NULL)
            {
                controller->devices[i]->poll(controller->devices[i]);
            }
        }
    }

    return;
}

/**
 * @name: FUsbExit
 * @msg: 关闭所有的USB控制器，移除所有连接的设备
 * @return {*}
 * @param {FUsb} *instance, USB实例
 */
void FUsbExit(FUsb *instance)
{
    FASSERT(instance);

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FUSB_ERROR("USB not ready !!!");
        return;
    }

    if (FUsbExitPrepare)
    {
        FUsbExitPrepare(instance);
    }

    FUsbHc *controller = instance->hc;
    if (controller != NULL)
    {
        FASSERT(controller->shutdown);
        controller->shutdown(controller);
        FUSB_FREE(instance, instance->hc);
        instance->hc = NULL;
    }


    return;
}

/**
 * @name: FUsbMempAllocate
 * @msg: 从USB内存池分配一块内存，并清零分配的空间
 * @return {void *} 分配的内存空间，如果失败返回NULL
 * @param {FUsb} *instance, USB实例
 * @param {size_t} size, 请求分配的字节数
 * @param {size_t} align, 分配空间的对齐方式，起始地址按align字节对齐
 */
void *FUsbMempAllocate(FUsb *instance, size_t size, size_t align)
{
    FASSERT(instance);
    void *result = NULL;
    FUsbMemAllocator *allocator = &(instance->config.allocator);

    if (allocator->malloc_align)
    {
        result = allocator->malloc_align(size, align);
    }

    return result;
}

/**
 * @name: FUsbMempFree
 * @msg: 释放从USB内存池分配的空间
 * @return {*}
 * @param {FUsb} *instance, USB实例
 * @param {void} *ptr, 待释放空间的首地址
 */
void FUsbMempFree(FUsb *instance, void *ptr)
{
    FASSERT(instance);
    FUsbMemAllocator *allocator = &(instance->config.allocator);

    if ((NULL != ptr) && (allocator->free))
    {
        allocator->free(ptr);
    }

    return;
}

#ifdef FMEMP_TAG_DEBUG
void *FUsbMempAllocateTag(FUsb *instance, size_t size, size_t align, const char *file, unsigned long line, const char *msg)
{
    FASSERT(instance);
    void *result = NULL;
    FMemp *memp = &instance->memp;

    if (FUSB_DEFAULT_ALIGN == align)
    {
        result = FMempCallocTag(memp, 1, size, file, line, msg);
    }
    else
    {
        result = FMempMallocAlignTag(memp, size, align, file, line, msg);
        if (NULL != result)
        {
            memset(result, 0, size);
        }
    }

    return result;
}

void FUsbMempFreeTag(FUsb *instance, void *ptr)
{
    FASSERT(instance);
    if (NULL != ptr)
    {
        FMempFreeTag(&instance->memp, ptr);
    }

    return;
}
#endif

/**
 * @name: FUsbAllocateHc
 * @msg: 创建USB控制器实例，添加到USB实例的Hc链表中
 * @return {*}
 * @param {FUsb} *instance, USB实例
 */
FUsbHc *FUsbAllocateHc(FUsb *instance)
{
    FASSERT(instance);
    FUsbHc *controller = FUSB_ALLOCATE(instance, sizeof(FUsbHc), FUSB_DEFAULT_ALIGN);
    instance->hc = controller;


    return controller;
}

/**
 * @name: FUsbDetachHc
 * @msg: 删除USB控制器实例，从USB实例的Hc链表中删去
 * @return {*}
 * @param {FUsbHc} *controller, USB控制器实例
 */
void FUsbDetachHc(FUsbHc *controller)
{
    if (controller == NULL)
    {
        return;
    }

    FUsb *instance = controller->usb;
    FUsbDetachDev(controller, 0); /* tear down root hub tree */

    return;
}

/**
 * @name: FUsbFindValidInitFunc
 * @msg: 寻找特定USB设备的初始化函数
 * @return {*}
 * @param {FUsb} *instance, USB实例
 * @param {FUsbDevIndex} *index, 特定USB设备的索引
 */
static FUsbDevInitHandler FUsbFindValidInitFunc(FUsb *instance, const FUsbDevIndex *index)
{
    FASSERT(instance);
    u32 loop;
    FUsbDevInitFunc *func;
    FUsbDevInitHandler handler = NULL;

    for (loop = 0; loop < instance->dev_init_num; loop++)
    {
        func = &instance->dev_init[loop];
        if ((index->category == func->index.category) &&
            (index->class == func->index.class) &&
            (index->sub_class == func->index.sub_class) &&
            (index->protocol == func->index.protocol))
        {
            handler = func->handler;
        }
    }

    return handler;
}

/**
 * @name: FUsbAssignDevInitFunc
 * @msg: 指定特定USB设备的初始化函数，供创建USB设备实例时使用
 * @return {FError} 处理返回错误码
 * @param {FUsb} *instance, USB实例
 * @param {FUsbDevIndex} *index, 特定USB设备的索引
 * @param {FUsbDevInitHandler} handler, 特定USB设备的初始化函数
 */
FError FUsbAssignDevInitFunc(FUsb *instance, const FUsbDevIndex *index, FUsbDevInitHandler handler)
{
    FASSERT(instance && index && handler);
    if (FUSB_MAX_DEV_TYPE_NUM == instance->dev_init_num)
    {
        return FUSB_ERR_INVALID_PARA;
    }

    if (NULL != FUsbFindValidInitFunc(instance, index))
    {
        FUSB_WARN("Will remove device init for class 0x%x", index->class);
    }

    instance->dev_init[instance->dev_init_num].index = *index;
    instance->dev_init[instance->dev_init_num].handler = handler;
    instance->dev_init_num++;

    return FUSB_SUCCESS;
}

/**
 * @name: FUsbInitDevEntry
 * @msg: 初始化USB设备
 * @return {*}
 * @param {FUsbHc} *controller, USB Hc
 * @param {int} slot_id，slot号
 */
FUsbDev *FUsbInitDevEntry(FUsbHc *controller, int slot_id)
{
    FASSERT(controller && controller->usb);
    FASSERT(FUSB_SLOT_ID_VALID(slot_id));

    FUsb *instace = controller->usb;
    FUsbDev *dev = FUSB_ALLOCATE(instace, sizeof(FUsbDev), FUSB_DEFAULT_ALIGN);

    if (NULL == dev)
    {
        FUSB_ERROR("No memory to allocate device structure .");
        return NULL;
    }

    if (controller->devices[slot_id] != NULL)
    {
        FUSB_WARN("Warning: device %d reassigned? ", slot_id);
    }

    controller->devices[slot_id] = dev;
    dev->controller = controller;
    dev->address = FUSB_NO_DEV_ADDR;
    dev->hub = FUSB_NO_HUB;
    dev->port = FUSB_NO_PORT;
    dev->init = FUsbNopDevInit;
    dev->init(controller->devices[slot_id]);

    return dev;
}

/**
 * @name: FUsbGetAllDevEntries
 * @msg: 获取USB控制器上连接的所有USB设备实例
 * @return {size_t} 实际获取的USB设备实例数目
 * @param {FUsbHc} *controller, USB控制器实例
 * @param {FUsbDev} *devs, 放置USB设备实例的缓冲区
 * @param {size_t} max_dev_num, 最多可以获取的USB设备实例数目
 */
size_t FUsbGetAllDevEntries(FUsbHc *controller, FUsbDev *devs[], size_t max_dev_num)
{
    FASSERT(controller && devs && max_dev_num > 0);
    size_t loop;
    size_t num = 0;

    /* loop over all dev address in case there are holes */
    for (loop = 0; loop < FUSB_MAX_DEV_NUM; loop++)
    {
        if (NULL != controller->devices[loop])
        {
            devs[num] = controller->devices[loop];
            num++;

            /* get at most max_dev_num device entry before exit */
            if (num >= max_dev_num)
            {
                break;
            }
        }
    }

    return num;
}

/**
 * @name: FUsbDecodeMaxPacketSz0
 * @msg: 根据USB设备速度，选择最大包长度
 * @return {*} 输出最大包长度
 * @param {FUsbSpeed} speed, USB设备速度类型
 * @param {u8} bMaxPacketSize0, 输入最大包长度
 */
int FUsbDecodeMaxPacketSz0(FUsbSpeed speed, u8 bMaxPacketSize0)
{
    switch (speed)
    {
        case FUSB_LOW_SPEED:
            if (bMaxPacketSize0 != 8)
            {
                FUSB_ERROR("Invalid MPS0: 0x%02x ", bMaxPacketSize0);
                bMaxPacketSize0 = 8;
            }
            return bMaxPacketSize0;
        case FUSB_FULL_SPEED:
            switch (bMaxPacketSize0)
            {
                case 8:
                case 16:
                case 32:
                case 64:
                    return bMaxPacketSize0;
                default:
                    FUSB_ERROR("Invalid MPS0: 0x%02x ", bMaxPacketSize0);
                    return 8;
            }
        case FUSB_HIGH_SPEED:
            if (bMaxPacketSize0 != 64)
            {
                FUSB_ERROR("Invalid MPS0: 0x%02x ", bMaxPacketSize0);
                bMaxPacketSize0 = 64;
            }
            return bMaxPacketSize0;
        case FUSB_SUPER_SPEED:
        /* Intentional fallthrough */
        case FUSB_SUPER_SPEED_PLUS:
            if (bMaxPacketSize0 != 9)
            {
                FUSB_ERROR("Invalid MPS0: 0x%02x ", bMaxPacketSize0);
                bMaxPacketSize0 = 9;
            }
            return 1 << bMaxPacketSize0;
        default:
            return 8;
    }
}

/**
 * @name: FUsbSetFeature
 * @msg: 标准USB主机请求，使能设备/接口/端点的某个特性
 * @return {FUsbTransCode} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目
 * @param {FUsbDev} *dev, USB设备实例
 * @param {int} endp, 设备号(0x00)/接口号/端点号
 * @param {int} feature, 待使能的特性
 * @param {int} rtype, 请求类型，由FUsbGenerateReqType生成
 */
FUsbTransCode FUsbSetFeature(FUsbDev *dev, int endp, int feature, int rtype)
{
    FASSERT(dev && dev->controller && dev->controller->control);
    FUsbDevReq dr;

    dr.bmRequestType = rtype;
    dr.data_dir = FUSB_REQ_HOST_TO_DEVICE;
    dr.bRequest = FUSB_SET_FEATURE;
    dr.wValue = feature;
    dr.wIndex = endp;
    dr.wLength = 0;

    return dev->controller->control(dev, FUSB_OUT, sizeof(dr), &dr, 0, NULL);
}

/**
 * @name: FUsbGetStatus
 * @msg: 标准USB主机请求，获取设备/接口/端点的状态
 * @return {FUsbTransCode} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目
 * @param {FUsbDev} *dev, USB设备实例
 * @param {int} intf，设备号(0x00)/接口号/端点号
 * @param {int} rtype, 请求类型，由FUsbGenerateReqType生成
 * @param {int} len, Data Stage的数据长度
 * @param {void} *data, Data Stage的数据缓冲区
 */
FUsbTransCode FUsbGetStatus(FUsbDev *dev, int intf, int rtype, int len, void *data)
{
    FASSERT(dev && dev->controller && dev->controller->control);
    FUsbDevReq dr;

    dr.bmRequestType = rtype;
    dr.data_dir = FUSB_REQ_DEVICE_TO_HOST;
    dr.bRequest = FUSB_GET_STATUS;
    dr.wValue = 0;
    dr.wIndex = intf;
    dr.wLength = len;

    return dev->controller->control(dev, FUSB_IN, sizeof(dr), &dr, len, data);
}

/**
 * @name: FUsbGetDescriptor
 * @msg: 标准USB主机请求，获取指定描述符
 * @return {FUsbTransCode} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目
 * @param {FUsbDev} *dev, USB设备实例
 * @param {int} rtype, 请求类型，由FUsbGenerateReqType生成
 * @param {FUsbDescriptorType} desc_type, 描述符类型
 * @param {int} desc_idx, 描述符索引
 * @param {void} *data, Data Stage的数据缓冲区
 * @param {size_t} len, Data Stage的数据长度
 */
FUsbTransCode FUsbGetDescriptor(FUsbDev *dev, int rtype, FUsbDescriptorType desc_type, int desc_idx, void *data,
                                size_t len)
{
    FASSERT(dev && dev->controller && dev->controller->control);
    FUsbDevReq dr;
    int fail_tries = 0;
    FUsbTransCode ret = FUSB_CC_ZERO_BYTES;

    while (fail_tries++ < FUSB_GET_DESCRIPTOR_RETRIES)
    {
        dr.bmRequestType = rtype;
        dr.bRequest = FUSB_GET_DESCRIPTOR;
        dr.wValue = desc_type << 8 | desc_idx;
        dr.wIndex = 0;
        dr.wLength = len;

        ret = dev->controller->control(dev, FUSB_IN,
                                       sizeof(dr), &dr, len, data);

        if (ret == (int)len)
        {
            break;
        }

        fsleep_microsec(10);
    }

    return ret;
}

/**
 * @name: FUsbGetStringDescriptor
 * @msg: USB主机请求，获取字符串描述符
 * @return {int} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目
 * @param {FUsbDev} *dev, USB设备实例
 * @param {int} rtype, 请求类型，由FUsbGenerateReqType生成
 * @param {int} desc_type, 描述符类型
 * @param {int} desc_idx, 描述符索引
 * @param {int} lang_id, 语言类型
 * @param {void} *data, Data Stage的数据缓冲区
 * @param {size_t} len, Data Stage的数据长度
 */
FUsbTransCode FUsbGetStringDescriptor(FUsbDev *dev, int rtype, FUsbDescriptorType desc_type, int desc_idx, int lang_id, void *data, size_t len)
{
    FASSERT(dev && dev->controller && dev->controller->control);
    FUsbDevReq dr;
    int fail_tries = 0;
    FUsbTransCode ret = FUSB_CC_ZERO_BYTES;

    while (fail_tries++ < FUSB_GET_DESCRIPTOR_RETRIES)
    {
        dr.bmRequestType = rtype;
        dr.bRequest = FUSB_GET_DESCRIPTOR;
        dr.wValue = desc_type << 8 | desc_idx;
        dr.wIndex = lang_id;
        dr.wLength = len;

        ret = dev->controller->control(dev, FUSB_IN, sizeof(dr), &dr, len, data);
        if (ret == (int)len)
        {
            break;
        }

        fsleep_microsec(10);
    }

    return ret;
}

/**
 * @name: FUsbSetConfiguration
 * @msg: 标准USB主机请求，设置配置值
 * @return {FUsbTransCode} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目
 * @param {FUsbDev} *dev, USB设备实例
 */
FUsbTransCode FUsbSetConfiguration(FUsbDev *dev)
{
    FASSERT(dev && dev->controller && dev->controller->control);
    FUsbDevReq dr;

    dr.bmRequestType = 0;
    dr.bRequest = FUSB_SET_CONFIGURATION;
    dr.wValue = dev->configuration->bConfigurationValue;
    dr.wIndex = 0;
    dr.wLength = 0;

    return dev->controller->control(dev, FUSB_OUT, sizeof(dr), &dr, 0, NULL);
}

/**
 * @name: FUsbClearFeature
 * @msg: 标准USB主机请求，去使能设备/接口/端点的某个特性
 * @return {FUsbTransCode} 控制传输的返回值，小于0表示失败，大于0表示成功传输的字节数目
 * @param {FUsbDev} *dev, USB设备实例
 * @param {int} endp, 设备号(0x00)/接口号/端点号
 * @param {int} feature，待去除的特性
 * @param {int} rtype, 请求类型，由FUsbGenerateReqType生成
 */
FUsbTransCode FUsbClearFeature(FUsbDev *dev, int endp, int feature, int rtype)
{
    FASSERT(dev && dev->controller && dev->controller->control);
    FUsbDevReq dr;

    dr.bmRequestType = rtype;
    dr.data_dir = FUSB_REQ_HOST_TO_DEVICE;
    dr.bRequest = FUSB_CLEAR_FEATURE;
    dr.wValue = feature;
    dr.wIndex = endp;
    dr.wLength = 0;

    return dev->controller->control(dev, FUSB_OUT, sizeof(dr), &dr, 0, NULL) < 0;
}

/**
 * @name: FUsbSpeedtoDefaultMaxPacketSz
 * @msg: 根据设备速度获取最大包长度
 * @return {int} 最大包长度
 * @param {FUsbSpeed} speed, 设备速度类型
 */
int FUsbSpeedtoDefaultMaxPacketSz(FUsbSpeed speed)
{
    switch (speed)
    {
        case FUSB_LOW_SPEED:
            return 8;
        case FUSB_FULL_SPEED:
        case FUSB_HIGH_SPEED:
            return 64;
        case FUSB_SUPER_SPEED:
        /* Intentional fallthrough */
        case FUSB_SUPER_SPEED_PLUS:
        default:
            return 512;
    }
}

/**
 * @name: FUsbDecodeInterval
 * @msg: 获取USB传输间隔时间
 * @return {int} 传输间隔时间, 0表示失败
 * @param {FUsbSpeed} speed, USB设备速度类型
 * @param {FUsbEpType} type, 端点类型
 * @param {unsigned char} bInterval, 设置的间隔时间
 */
static int FUsbDecodeInterval(FUsbSpeed speed, const FUsbEpType type, const unsigned char bInterval)
{
    /* Normalize bInterval to log2 of microframes */
#define LOG2(a) ((sizeof(unsigned) << 3) - __builtin_clz(a) - 1)
    switch (speed)
    {
        case FUSB_LOW_SPEED:
            switch (type)
            {
                case FUSB_ISOCHRONOUS_EP:
                case FUSB_INTERRUPT_EP:
                    return LOG2(bInterval) + 3;
                default:
                    return 0;
            }
        case FUSB_FULL_SPEED:
            switch (type)
            {
                case FUSB_ISOCHRONOUS_EP:
                    return (bInterval - 1) + 3;
                case FUSB_INTERRUPT_EP:
                    return LOG2(bInterval) + 3;
                default:
                    return 0;
            }
        case FUSB_HIGH_SPEED:
            switch (type)
            {
                case FUSB_ISOCHRONOUS_EP:
                case FUSB_INTERRUPT_EP:
                    return bInterval - 1;
                default:
                    return LOG2(bInterval);
            }
        case FUSB_SUPER_SPEED:
        /* Intentional fallthrough */
        case FUSB_SUPER_SPEED_PLUS:
            switch (type)
            {
                case FUSB_ISOCHRONOUS_EP:
                case FUSB_INTERRUPT_EP:
                    return bInterval - 1;
                default:
                    return 0;
            }
        default:
            return 0;
    }
#undef LOG2
}

/**
 * @name: FUsbSetAddress
 * @msg: 获取USB设备的描述符信息，根据USB设备类型完成配置和初始化
 * @return {FUsbDevAddr} 为USB设备分配的地址，-1表示USB设备初始化失败
 * @param {FUsbHc} *controller, USB控制器实例
 * @param {FUsbSpeed} speed, USB设备速度类型
 * @param {int} hubport, USB设备连接的Hub端口号
 * @param {int} hubaddr, USB设备连接Hub的地址
 */
static FUsbDevAddr FUsbSetAddress(FUsbHc *controller, FUsbSpeed speed, int hubport, int hubaddr)
{
    FASSERT(controller);
    FUsbDev *dev = controller->set_address(controller, speed,
                                           hubport, hubaddr);
    FUsbDevIndex index;
    FUsbDevInitHandler init_handler = NULL;

    FUsb *instace = controller->usb;
    FASSERT(instace);
    if (NULL == dev)
    {
        FUSB_INFO("Set address failed.");
        return FUSB_NO_DEV_ADDR;
    }

    FASSERT(NULL == dev->descriptor);
    dev->descriptor = FUSB_ALLOCATE(instace, sizeof(*dev->descriptor), FUSB_DEFAULT_ALIGN);
    if ((NULL == dev->descriptor) || FUsbGetDescriptor(dev, FUSB_DR_DESC, FUSB_DESC_TYPE_DEVICE, 0,
            dev->descriptor, sizeof(*dev->descriptor)) != sizeof(*dev->descriptor))
    {
        FUSB_INFO("FUsbGetDescriptor(FUSB_DESC_TYPE_DEVICE) failed.");
        FUsbDetachDev(controller, dev->address);
        return FUSB_NO_DEV_ADDR;
    }

    FUSB_INFO("Found device (0x%04x:0x%04x, USB %x.%x, MPS0: %d) ",
              dev->descriptor->idVendor, dev->descriptor->idProduct,
              dev->descriptor->bcdUSB >> 8, dev->descriptor->bcdUSB & 0xff,
              dev->endpoints[0].maxpacketsize);

    FUSB_INFO("Device has %d configurations.",
              dev->descriptor->bNumConfigurations);
    if (dev->descriptor->bNumConfigurations == 0)
    {
        /* device isn't usable */
        FUSB_INFO("No usable configuration!");
        FUsbDetachDev(controller, dev->address);
        return FUSB_NO_DEV_ADDR;
    }

    u16 buf[2];
    if (FUsbGetDescriptor(dev, FUSB_DR_DESC, FUSB_DESC_TYPE_CONFIG, 0, buf, sizeof(buf)) != sizeof(buf))
    {
        FUSB_INFO("First FUsbGetDescriptor(FUSB_DESC_TYPE_CONFIG) failed.");
        FUsbDetachDev(controller, dev->address);
        return FUSB_NO_DEV_ADDR;
    }

    /* workaround for some USB devices: wait until they're ready, or
     * they send a NAK when they're not allowed to do. 1ms is enough */
    fsleep_millisec(1);
    FASSERT(NULL == dev->configuration);
    dev->configuration = FUSB_ALLOCATE(instace, buf[1], FUSB_DEFAULT_ALIGN);
    if (NULL == dev->configuration)
    {
        FUSB_INFO("Could not allocate %d bytes for FUSB_DESC_TYPE_CONFIG.", buf[1]);
        FUsbDetachDev(controller, dev->address);
        return FUSB_NO_DEV_ADDR;
    }

    if (FUsbGetDescriptor(dev, FUSB_DR_DESC, FUSB_DESC_TYPE_CONFIG, 0, dev->configuration,
                          buf[1]) != buf[1])
    {
        FUSB_INFO("FUsbGetDescriptor(FUSB_DESC_TYPE_CONFIG) failed.");
        FUsbDetachDev(controller, dev->address);
        return FUSB_NO_DEV_ADDR;
    }

    FUsbConfigurationDescriptor *cd = dev->configuration;
    if (cd->wTotalLength != buf[1])
    {
        FUSB_INFO("Configuration descriptor size changed, aborting.");
        FUsbDetachDev(controller, dev->address);
        return FUSB_NO_DEV_ADDR;
    }

    /*
     * If the device is not well known (ifnum == -1), we use the first
     * interface we encounter, as there was no need to implement something
     * else for the time being. If you need it, see the SetInterface and
     * GetInterface functions in the USB specification and set it yourself.
     */
    FUSB_INFO("Device has %x interfaces.", cd->bNumInterfaces);

    u8 *end = (void *)dev->configuration + cd->wTotalLength;
    FUsbInterfaceDescriptor *intf;
    u8 *ptr;

    /* Find our interface (or the first good one if we don't know) */
    for (ptr = (void *)dev->configuration + sizeof(*cd);; ptr += ptr[0])
    {
        if (ptr + 2 > end || !ptr[0] || ptr + ptr[0] > end)
        {
            FUSB_INFO("Couldn't find usable FUSB_DESC_TYPE_INTERFACE.");
            FUsbDetachDev(controller, dev->address);
            return FUSB_NO_DEV_ADDR;
        }

        if (ptr[1] != FUSB_DESC_TYPE_INTERFACE)
        {
            continue;
        }

        intf = (void *)ptr;
        if (intf->bLength != sizeof(*intf))
        {
            FUSB_INFO("Skipping broken FUSB_DESC_TYPE_INTERFACE.");
            continue;
        }

        FUSB_INFO("Interface %d: class 0x%x, sub 0x%x. proto 0x%x.",
                  intf->bInterfaceNumber, intf->bInterfaceClass,
                  intf->bInterfaceSubClass, intf->bInterfaceProtocol);
        ptr += sizeof(*intf);

        break;
    }

    /* Gather up all endpoints belonging to this interface */
    dev->num_endp = 1;
    for (; ptr + 2 <= end && ptr[0] && ptr + ptr[0] <= end; ptr += ptr[0])
    {
        if (ptr[1] == FUSB_DESC_TYPE_INTERFACE || ptr[1] == FUSB_DESC_TYPE_CONFIG ||
            (size_t)dev->num_endp >= ARRAY_SIZE(dev->endpoints))
        {
            break;
        }

        if (ptr[1] != FUSB_DESC_TYPE_ENDPOINT)
        {
            continue;
        }

        FUsbEndpointDescriptor *desc = (void *)ptr;
        static const char *transfertypes[4] =
        {
            "control", "isochronous", "bulk", "interrupt"
        };
        FUSB_INFO(" #Endpoint %d (%s), max packet size %x, type %s ",
                  desc->bEndpointAddress & 0x7f,
                  (desc->bEndpointAddress & 0x80) ? "in" : "out",
                  desc->wMaxPacketSize,
                  transfertypes[desc->bmAttributes & 0x3]);

        FUsbEndpoint *ep = &dev->endpoints[dev->num_endp++];
        ep->dev = dev;
        ep->endpoint = desc->bEndpointAddress;
        ep->toggle = 0;
        ep->maxpacketsize = desc->wMaxPacketSize;
        ep->direction = (desc->bEndpointAddress & 0x80) ? FUSB_IN : FUSB_OUT;
        ep->type = desc->bmAttributes & 0x3;
        ep->interval = FUsbDecodeInterval(dev->speed, ep->type,
                                          desc->bInterval);
    }

    if ((controller->finish_device_config &&
         controller->finish_device_config(dev)) ||
        FUsbSetConfiguration(dev) < 0)
    {
        FUSB_INFO("Could not finalize device configuration. ");
        FUsbDetachDev(controller, dev->address);
        return FUSB_NO_DEV_ADDR;
    }

    int class = dev->descriptor->bDeviceClass;
    if (class == 0)
    {
        class = intf->bInterfaceClass;
    }

    switch (class)
    {
        case FUSB_AUDIO_DEVICE:
            FUSB_INFO("Audio Class ");
            break;
        case FUSB_COMM_DEVICE:
            FUSB_INFO("Communication Class ");
            break;
        case FUSB_HID_DEVICE:
            FUSB_INFO("HID Class ");
            break;
        case FUSB_PHYSICAL_DEVICE:
            FUSB_INFO("Physical Class");
            break;
        case FUSB_IMAGE_DEVICE:
            FUSB_INFO("Camera Class ");
            break;
        case FUSB_PRINTER_DEVICE:
            FUSB_INFO("Printer Class");
            break;
        case FUSB_MASS_STORAGE_DEVICE:
            FUSB_INFO("Mass Storage Class ");
            break;
        case FUSB_HUB_DEVICE:
            FUSB_INFO("Hub Class ");
            break;
        default:
            FUSB_ERROR("Unsupported Class %x ", class);
            break;
    }

    index.category = FUSB_STANDARD_INTERFACE;
    index.class = class;
    index.sub_class = intf->bInterfaceSubClass;
    index.protocol = intf->bInterfaceProtocol;

    FUSB_INFO("Class: 0x%x sub-class: 0x%x, protocol: 0x%x.",
              index.class, index.sub_class, index.protocol);

    init_handler = FUsbFindValidInitFunc(instace, &index);
    if (NULL != init_handler)
    {
        dev->init = init_handler;
        dev->class = (FUsbDevClass)class;
    }
    else
    {
        FUSB_WARN("Init function for the device not found, use generic one instead !!!");
        dev->init = FUsbGenericDevInit;
    }

    return dev->address;
}

/**
 * @name: FUsbDetachDev
 * @msg: 从USB主机移除指定USB设备(USB设备驱动使用)
 * @return {*}
 * @param {FUsbHc} *controller, USB控制器实例
 * @param {int} devno, USB设备索引
 * @note Should be called by the hub drivers whenever a physical detach occurs
 * and can be called by USB class drivers if they are unsatisfied with a
 * malfunctioning device.
 */
void FUsbDetachDev(FUsbHc *controller, int devno)
{
    FUsb *instace = controller->usb;
    /* check if device exists, as we may have
       been called yet by the USB class driver */
    if (controller->devices[devno])
    {
        controller->devices[devno]->destroy(controller->devices[devno]);

        if (controller->destroy_device)
        {
            controller->destroy_device(controller, devno);
        }

        FUSB_FREE(instace, controller->devices[devno]->descriptor);
        controller->devices[devno]->descriptor = NULL;
        FUSB_FREE(instace, controller->devices[devno]->configuration);
        controller->devices[devno]->configuration = NULL;

        /* Tear down the device itself *after* destroy_device()
         * has had a chance to interrogate it. */
        FUSB_FREE(instace, controller->devices[devno]);
        controller->devices[devno] = NULL;
    }

    return;
}

/**
 * @name: FUsbAttachDev
 * @msg: 向USB主机添加USB设备(USB设备驱动使用)
 * @return {FUsbDevAddr} 分配的USB设备地址
 * @param {FUsbHc} *controller, USB控制器实例
 * @param {int} hubaddress, Hub地址
 * @param {int} port, 连接的Port
 * @param {FUsbSpeed} speed, USB设备的设置速度类型
 */
FUsbDevAddr FUsbAttachDev(FUsbHc *controller, int hubaddress, int port, FUsbSpeed speed)
{
    static const char *speeds[] = {"FULL", "LOW", "HIGH", "SUPER", "ULTRA-SUPER"};
    FUSB_INFO("%s-Speed Device ", ((size_t)speed < sizeof(speeds) / sizeof(char *))
              ? speeds[speed]
              : "Unkonwn");
    FUsbDevAddr newdev = FUsbSetAddress(controller, speed, port, hubaddress);
    if (newdev == FUSB_NO_DEV_ADDR)
    {
        return FUSB_NO_DEV_ADDR;
    }

    FUsbDev *newdev_t = controller->devices[newdev];

    /* determine responsible driver - current done in set_address */
    newdev_t->init(newdev_t);

    /* init() may have called FUsbDetachDev() yet, so check */
    return controller->devices[newdev] ? newdev : FUSB_NO_DEV_ADDR;
}

/**
 * @name: FUsbGenericDestory
 * @msg: 一般USB设备去初始化函数
 * @return {*}
 * @param {FUsbDev} *dev, USB设备实例
 */
static void FUsbGenericDestory(FUsbDev *dev)
{
    if (FUsbGenericRemove)
    {
        FUsbGenericRemove(dev);
    }

    return;
}

/**
 * @name: FUsbGenericDevInit
 * @msg: 默认的USB设备初始化函数
 * @return {*}
 * @param {FUsbDev} *dev, USB设备实例
 */
void FUsbGenericDevInit(FUsbDev *dev)
{
    dev->data = NULL;
    dev->destroy = FUsbGenericDestory;

    if (FUsbGenericCreate)
    {
        FUsbGenericCreate(dev);
    }

    if (dev->data == NULL)
    {
        FUSB_INFO("Detaching device not used by payload.");
        FUsbDetachDev(dev->controller, dev->address);
    }

    return;
}