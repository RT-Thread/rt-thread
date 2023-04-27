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
 * FilePath: fusb_debug.c
 * Date: 2022-02-11 13:33:11
 * LastEditTime: 2022-02-18 09:18:04
 * Description:  This files is for implmentation of USB debug utilities
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include "fdebug.h"

#include "fusb_private.h"

#define FUSB_DEBUG_TAG "FUSB_DEBUG"
#define FUSB_ERROR(format, ...)   FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...)    FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...)    FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

static inline boolean FUsbIsValidStringIndex(u8 id)
{
    return (0 != id) && (0xff != id);
}

/**
 * @name: FUsbDumpAllDescriptors
 * @msg: 打印USB设备的描述符信息（设备描述符，配置描述符和接口描述符）
 * @return {*}
 * @param {FUsbDev} *dev, USB设备实例，已完成初始化
 */
void FUsbDumpAllDescriptors(FUsbDev *dev)
{
    FError ret = FUSB_SUCCESS;
    if ((NULL == dev) || (NULL == dev->configuration))
    {
        return;
    }

    const FUsbDeviceDescriptor *dev_desc = NULL;
    const FUsbConfigurationDescriptor *config_desc = NULL;
    const FUsbInterfaceDescriptor *if_desc = NULL;
    FASSERT(dev->controller && dev->controller->usb);
    FUsb *instance = dev->controller->usb;
    u8 if_num = 0;
    u8 func_id = 0;
    FUsbConfigParser *parser = &dev->config_parser;

    dev_desc = dev->descriptor;
    config_desc = dev->configuration;

    /* init descriptor parser in each dump */
    ret = FUsbSetupConfigParser(dev, config_desc, config_desc->wTotalLength);
    FUsbSetupStringParser(dev);
    if (FUSB_SUCCESS != ret)
    {
        return;
    }

    if (FUsbIsValidStringIndex(dev_desc->iManufacturer))
    {
        ret = FUsbSearchStringDescriptor(instance, dev, dev_desc->iManufacturer);
        if (FUSB_SUCCESS == ret)
        {
            printf("	Manufacturer: %s\r\n", FUsbGetString(dev));
        }
    }

    if (FUsbIsValidStringIndex(dev_desc->iProduct))
    {
        ret = FUsbSearchStringDescriptor(instance, dev, dev_desc->iProduct);
        if (FUSB_SUCCESS == ret)
        {
            printf("	Product: %s\r\n", FUsbGetString(dev));
        }
    }

    if (FUsbIsValidStringIndex(dev_desc->iSerialNumber))
    {
        ret = FUsbSearchStringDescriptor(instance, dev, dev_desc->iSerialNumber);
        if (FUSB_SUCCESS == ret)
        {
            printf("	Serial No.: %s\r\n", FUsbGetString(dev));
        }
    }

    while (NULL != (if_desc = (const FUsbInterfaceDescriptor *)FUsbGetDescriptorFromParser(parser, FUSB_DESC_TYPE_INTERFACE)))
    {
        if (if_desc->bInterfaceNumber > if_num)
        {
            if_num = if_desc->bInterfaceNumber;
        }

        if (if_desc->bInterfaceNumber != if_num)
        {
            FUSB_INFO("Alternate setting %u ignored", if_desc->bInterfaceNumber);
            continue;
        }

        if (FUsbIsValidStringIndex(if_desc->iInterface))
        {
            ret = FUsbSearchStringDescriptor(instance, dev, if_desc->iInterface);
            if (FUSB_SUCCESS == ret)
            {
                printf("	Interface: %s\r\n", FUsbGetString(dev));
            }
        }

    }

    /* revoke descriptor parser after used */
    FUsbRevokeConfigParser(dev);
    FUsbRevokeStringParser(dev);

    return;
}

/**
 * @name: FUsbDumpDeviceDescriptor
 * @msg: 打印设备描述符信息
 * @return {*}
 * @param {FUsbDeviceDescriptor} *descriptor, 设备描述符
 */
void FUsbDumpDeviceDescriptor(const FUsbDeviceDescriptor *descriptor)
{
    if (NULL != descriptor)
    {
        FUSB_INFO("");
        FUSB_INFO("===Device Descriptor");
        FUSB_INFO("	bLength: %d", descriptor->bLength);
        FUSB_INFO("	bDescriptorType: %d", descriptor->bDescriptorType);
        FUSB_INFO("	bcdUSB: 0x%x", descriptor->bcdUSB);
        FUSB_INFO("	bDeviceClass: %d", descriptor->bDeviceClass);
        FUSB_INFO("	bDeviceSubClass: %d", descriptor->bDeviceSubClass);
        FUSB_INFO("	bDeviceProtocol: %d", descriptor->bDeviceProtocol);
        FUSB_INFO("	bMaxPacketSize0: %d", descriptor->bMaxPacketSize0);
        FUSB_INFO("	idVendor: 0x%x", descriptor->idVendor);
        FUSB_INFO("	idProduct: 0x%x", descriptor->idProduct);
        FUSB_INFO("	bcdDevice: 0x%x", descriptor->bcdDevice);
        FUSB_INFO("	iManufacturer: %d", descriptor->iManufacturer);
        FUSB_INFO("	iSerialNumber: %d", descriptor->iSerialNumber);
        FUSB_INFO("	bNumConfigurations: %d", descriptor->bNumConfigurations);
        FUSB_INFO("");
    }
}

/**
 * @name: FUsbDumpConfigDescriptor
 * @msg: 打印配置描述符信息
 * @return {*}
 * @param {FUsbConfigurationDescriptor} *descriptor, 配置描述符
 */
void FUsbDumpConfigDescriptor(const FUsbConfigurationDescriptor *descriptor)
{
    if (NULL != descriptor)
    {
        FUSB_INFO("");
        FUSB_INFO("===Configure Descriptor");
        FUSB_INFO("	bLength: %d", descriptor->bLength);
        FUSB_INFO("	bDescriptorType: %d", descriptor->bDescriptorType);
        FUSB_INFO("	wTotalLength: %d", descriptor->wTotalLength);
        FUSB_INFO("	bNumInterfaces: %d", descriptor->bNumInterfaces);   /* 该配置下有多少个接口描述符 */
        FUSB_INFO("	bConfigurationValue: %d", descriptor->bConfigurationValue); /* 该配置描述符的配置号信息 */
        FUSB_INFO("	iConfiguration: %d", descriptor->iConfiguration);
        FUSB_INFO("	bmAttributes: 0x%x", descriptor->bmAttributes);
        FUSB_INFO("		remote-weakup: %s",
                  (descriptor->bmAttributes & FUSB_CONFIG_DESC_ATTR_REMOTE_WEAKUP) ? "yes" : "no");
        FUSB_INFO("		self-power: %s",
                  (descriptor->bmAttributes & FUSB_CONFIG_DESC_ATTR_SELF_POWER) ? "yes" : "no");
        FUSB_INFO("		usb1.0-compatible: %s",
                  (descriptor->bmAttributes & FUSB_CONFIG_DESC_ATTR_USB1_COMPATIABLE) ? "yes" : "no");
        FUSB_INFO("	max power: %dmA", 2 * (descriptor->bMaxPower));
        FUSB_INFO("	");
    }
}

/**
 * @name: FUsbDumpInterfaceDescriptor
 * @msg: 打印接口描述符信息
 * @return {*}
 * @param {FUsbInterfaceDescriptor} *descriptor, 接口描述符
 */
void FUsbDumpInterfaceDescriptor(const FUsbInterfaceDescriptor *descriptor)
{
    if (NULL != descriptor)
    {
        FUSB_INFO("");
        FUSB_INFO("===Interface Descriptor");
        FUSB_INFO("	bLength: %d", descriptor->bLength);
        FUSB_INFO("	bDescriptorType: %d", descriptor->bDescriptorType);
        FUSB_INFO("	bInterfaceNumber: %d", descriptor->bInterfaceNumber);
        FUSB_INFO("	bAlternateSetting: %d", descriptor->bAlternateSetting);
        FUSB_INFO("	bNumEndpoints: %d", descriptor->bNumEndpoints);
        FUSB_INFO("	bInterfaceClass: %d", descriptor->bInterfaceClass);
        FUSB_INFO("	bInterfaceSubClass: %d", descriptor->bInterfaceSubClass);
        FUSB_INFO("	bInterfaceProtocol: %d", descriptor->bInterfaceProtocol);
        FUSB_INFO("	iInterface: %d", descriptor->iInterface);
        FUSB_INFO("	");
    }
}

/**
 * @name: FUsbDumpEndpointDescriptor
 * @msg: 打印端点描述符信息
 * @return {*}
 * @param {FUsbEndpointDescriptor} *descriptor, 端点描述符
 */
void FUsbDumpEndpointDescriptor(const FUsbEndpointDescriptor *descriptor)
{
    if (NULL != descriptor)
    {
        FUSB_INFO("");
        FUSB_INFO("===Endpoint Descriptor");
        FUSB_INFO("	bLength: %d", descriptor->bLength);
        FUSB_INFO("	bDescriptorType: %d", descriptor->bDescriptorType);
        FUSB_INFO("	bEndpointAddress: %d", descriptor->bEndpointAddress);
        FUSB_INFO("		ep num: %d", FUSB_EP_DESC_EP_NUM(descriptor->bEndpointAddress));
        FUSB_INFO("		ep dir: %s",
                  (FUSB_EP_DESC_EP_DIR_IN & descriptor->bEndpointAddress) ? "IN" : "OUT");
        FUSB_INFO("	bmAttributes: 0x%x", descriptor->bmAttributes);
        FUSB_INFO("		trans type: %d ([0]-%s, [1]-%s, [2]-%s, [3]-%s)",
                  FUSB_EP_DESC_TRANS_TYPE(descriptor->bmAttributes),
                  "control", "isochronous", "bulk", "interrupt");
        FUSB_INFO("	wMaxPacketSize: %d", descriptor->wMaxPacketSize);
        FUSB_INFO("	bInterval: %d", descriptor->bInterval);
        FUSB_INFO("	");
    }
}