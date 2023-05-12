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
 * FilePath: fusb_dev.c
 * Date: 2022-02-11 13:33:11
 * LastEditTime: 2022-02-18 09:18:45
 * Description:  This files is for USB device function implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include <string.h>
#include "fdebug.h"
#include "fusb_private.h"

#define FUSB_DEBUG_TAG "FUSB-DEV"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...)  FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...)  FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

#define FUSB_DR_DESC FUsbGenerateReqType(FUSB_REQ_DEVICE_TO_HOST, FUSB_REQ_TYPE_STANDARD, FUSB_REQ_RECP_DEV)

#define FUSB_SKIP_BYTES(desc, bytes)    ((FUsbDescriptor *) ((u8 *) (desc) + (bytes)))
#define FUSB_CONFIG_DESC_SIZE           512     /* best guess */

static void FUsbNopDevDestory(FUsbDev *dev)
{
    FUsbNopDevInit(dev);
    dev->address = FUSB_NO_DEV_ADDR;
    dev->hub = FUSB_NO_HUB;
    dev->port = FUSB_NO_PORT;
}

static void FUsbNopDevPoll(FUsbDev *dev)
{
    return;
}

/**
 * @name: FUsbNopDevInit
 * @msg: 默认的USB设备初始化函数
 * @return {*}
 * @param {FUsbDev} *dev, USB设备实例
 */
void FUsbNopDevInit(FUsbDev *dev)
{
    dev->descriptor = NULL;
    dev->configuration = NULL;
    dev->destroy = FUsbNopDevDestory;
    dev->poll = FUsbNopDevPoll;
}

static inline boolean FUsbParserIsValid(const FUsbConfigParser *parser)
{
    FASSERT(parser);
    return parser->is_valid;
}

static FError FUsbParserDescriptor(FUsbConfigParser *parser)
{
    FASSERT(parser && parser->buf);
    const FUsbDescriptor *cur_pos = parser->buf;
    const FUsbDescriptor *desc_end;
    FUsbDescriptorType last_desc_type = FUSB_DESC_TYPE_NONE;
    FUsbDescriptorType desc_type;
    u8 desc_len, exp_len, alt_len;
    FError ret = FUSB_SUCCESS;

    while (FUSB_SKIP_BYTES(cur_pos, FUSB_DESCRIPTOR_HEADER_SIZE) < parser->end_pos)
    {
        /* get length and type of descriptor */
        desc_len = cur_pos->header.len;
        desc_type = cur_pos->header.type;

        desc_end = FUSB_SKIP_BYTES(cur_pos, desc_len);
        if (desc_end > parser->end_pos)
        {
            FUSB_ERROR("Parse descriptor out of boundary !!!");
            parser->err_pos = cur_pos;
            ret = FUSB_ERR_DESC_PARSE_ERR;
            goto err_handle;
        }

        exp_len = 0;
        alt_len = 0;
        switch (desc_type)
        {
            case FUSB_DESC_TYPE_CONFIG:
                if (FUSB_DESC_TYPE_NONE != last_desc_type)
                {
                    FUSB_ERROR("Configuration descriptor must be the first !!!");
                    parser->err_pos = cur_pos;
                    ret = FUSB_ERR_DESC_PARSE_ERR;
                    goto err_handle;
                }
                exp_len = sizeof(FUsbConfigurationDescriptor);
                break;
            case FUSB_DESC_TYPE_INTERFACE:
                if (FUSB_DESC_TYPE_NONE == last_desc_type)
                {
                    FUSB_ERROR("Interface descriptor must not be the first !!!");
                    parser->err_pos = cur_pos;
                    ret = FUSB_ERR_DESC_PARSE_ERR;
                    goto err_handle;
                }
                exp_len = sizeof(FUsbInterfaceDescriptor);
                break;
            case FUSB_DESC_TYPE_ENDPOINT:
                if ((FUSB_DESC_TYPE_NONE == last_desc_type) ||
                    (FUSB_DESC_TYPE_CONFIG == last_desc_type))
                {
                    FUSB_ERROR("Endpoint descriptor must follow interface descriptor !!!");
                    parser->err_pos = cur_pos;
                    ret = FUSB_ERR_DESC_PARSE_ERR;
                    goto err_handle;
                }
                break;
            default:
                FUSB_DEBUG("Descriptor %d not handled !!!", desc_type);
                break;
        }

        if (((exp_len != 0) && (desc_len != exp_len)) &&
            ((alt_len == 0) || (desc_len != alt_len)))
        {
            FUSB_ERROR("Descriptor %d invalid !!!", desc_type);
            parser->err_pos = cur_pos;
            ret = FUSB_ERR_DESC_PARSE_ERR;
            goto err_handle;
        }

        last_desc_type = desc_type;
        cur_pos = desc_end;
    }

    if (cur_pos != parser->end_pos)
    {
        parser->err_pos = cur_pos;
        ret = FUSB_ERR_DESC_PARSE_ERR;
        goto err_handle;
    }

err_handle:
    if (FUSB_SUCCESS == ret)
    {
        parser->is_valid = TRUE;
    }

    return ret;
}

/**
 * @name: FUsbSetupConfigParser
 * @msg: 配置USB配置描述符解析器
 * @return {*}
 * @param {FUsbDev} *dev, USB设备实例
 * @param {void} *buf, 配置描述符缓冲区
 * @param {u32} buf_len, 配置描述符缓冲区长度
 */
FError FUsbSetupConfigParser(FUsbDev *dev, const void *buf, u32 buf_len)
{
    FASSERT(dev && buf && (buf_len > 0));
    const FUsbConfigurationDescriptor *config_desc;
    FUsbConfigParser *parser = &dev->config_parser;

    memset(parser, 0, sizeof(*parser));

    parser->buf = buf;
    parser->buf_len = buf_len;
    parser->is_valid = FALSE;
    parser->end_pos = FUSB_SKIP_BYTES(parser->buf, parser->buf_len);
    parser->next_pos = parser->buf;
    parser->cur_desc = NULL;
    parser->err_pos = parser->buf;

    if ((parser->buf_len < sizeof(u32)) || (parser->buf_len > FUSB_CONFIG_DESC_SIZE))
    {
        FUSB_ERROR("Invalid buffer length !!!");
        return FUSB_ERR_INVALID_DATA;
    }

    /* input buffer must start with config desc */
    config_desc = (FUsbConfigurationDescriptor *)parser->buf;
    if ((config_desc->bLength != sizeof(FUsbConfigurationDescriptor)) ||
        (config_desc->bDescriptorType != FUSB_DESC_TYPE_CONFIG) ||
        (config_desc->wTotalLength > parser->buf_len))
    {
        FUSB_ERROR("Invalid configuration descriptor !!!");
        return FUSB_ERR_INVALID_DATA;
    }

    /* adjust end position */
    if (config_desc->wTotalLength < parser->buf_len)
    {
        parser->end_pos = FUSB_SKIP_BYTES(parser->buf, config_desc->wTotalLength);
    }

    return FUsbParserDescriptor(parser);
}

/**
 * @name: FUsbRevokeConfigParser
 * @msg: 去初始化USB配置描述符解析器
 * @return {*}
 * @param {FUsbDev} *dev, USB设备实例
 */
void FUsbRevokeConfigParser(FUsbDev *dev)
{
    FASSERT(dev);
    memset(&dev->config_parser, 0, sizeof(dev->config_parser));
    return;
}

/**
 * @name: FUsbGetDescriptorFromParser
 * @msg: 从配置描述符解析器中获取指定类型的描述符（端点描述符/接口描述符）
 * @return {const FUsbDescriptor *} 获取的描述符
 * @param {FUsbConfigParser} *parser, 配置描述符解析器
 * @param {FUsbDescriptorType} type, 获取描述符的类型
 */
const FUsbDescriptor *FUsbGetDescriptorFromParser(FUsbConfigParser *parser, FUsbDescriptorType type)
{
    FASSERT(parser);
    if (!FUsbParserIsValid(parser))
    {
        FUSB_ERROR("Config parse is not valid !!!");
        return NULL;
    }

    const FUsbDescriptor *result = NULL;
    FUsbDescriptorType desc_type;
    u8 desc_len;
    const FUsbDescriptor *desc_end;

    /* travesal all descriptors */
    while (parser->next_pos < parser->end_pos)
    {
        desc_len = parser->next_pos->header.len;
        desc_type = parser->next_pos->header.type;

        desc_end = FUSB_SKIP_BYTES(parser->next_pos, desc_len);
        if (desc_end > parser->end_pos)
        {
            break;
        }

        if ((FUSB_DESC_TYPE_ENDPOINT == type) &&
            (FUSB_DESC_TYPE_INTERFACE == desc_type))
        {
            break;    /* there is no chance to find endpoint desc after interface desc */
        }

        if (type == desc_type)
        {
            /* target desc found !!! */
            result = parser->next_pos;
            parser->next_pos = desc_end;
            break;
        }

        parser->next_pos = desc_end;/* check next one */
    }

    if (NULL != result)
    {
        parser->err_pos = result;
    }

    parser->cur_desc = result;
    return result;
}

/**
 * @name: FUsbSetupStringParser
 * @msg: 初始化字符串描述符解析器
 * @return {*}
 * @param {FUsbDev} *dev, USB设备实例
 */
void FUsbSetupStringParser(FUsbDev *dev)
{
    FASSERT(dev);
    FUsbStringParser *parser = &dev->string_parser;

    if (NULL != parser->usb_str)
    {
        FUSB_WARN("String descriptor exists, might cause memory leakage !!!");
    }

    parser->usb_str = NULL;
    memset(parser->str_buf, 0, sizeof(parser->str_buf));

    return;
}

/**
 * @name: FUsbRevokeStringParser
 * @msg: 去初始化字符串描述符解析器
 * @return {*}
 * @param {FUsbDev} *dev, USB设备实例
 */
void FUsbRevokeStringParser(FUsbDev *dev)
{
    FASSERT(dev);
    FUsbStringParser *parser = &dev->string_parser;
    FASSERT(dev->controller && dev->controller->usb);
    FUsb *instance = dev->controller->usb;

    if (NULL != parser->usb_str)
    {
        FUSB_FREE(instance, parser->usb_str);
        parser->usb_str = NULL;
    }

    return;
}

/**
 * @name: FUsbSearchStringDescriptor
 * @msg: 检索字符串描述符，保存在FUsbStringParser结构中
 * @return {*}
 * @param {FUsb} *instance, USB实例
 * @param {FUsbDev} *dev, USB设备实例
 * @param {u8} id, 要获取字符串描述符的ID
 */
FError FUsbSearchStringDescriptor(FUsb *instance, FUsbDev *dev, u8 id)
{
    FASSERT(instance && dev);
    FUsbStringParser *parser = &dev->string_parser;
    const FUsbStringDescriptor *usb_str = NULL;
    u8 total_len;
    u8 char_num;
    u16 character;

    /* re-malloc usb string desc buffer with length 4 */
    if (NULL != parser->usb_str)
    {
        FUSB_FREE(instance, parser->usb_str);
        parser->usb_str = NULL;
    }

    parser->usb_str = FUSB_ALLOCATE(instance, FUSB_USBSTR_MIN_LEN, FUSB_DEFAULT_ALIGN);
    if (NULL == parser->usb_str)
    {
        return FUSB_ERR_ALLOCATE_FAIL;
    }

    /* get header of string for the full length */
    if (FUsbGetStringDescriptor(dev, FUSB_DR_DESC, FUSB_DESC_TYPE_STRING, id, FUSB_DEFAULT_LANG_ID,
                                parser->usb_str, FUSB_USBSTR_MIN_LEN) < 0)
    {
        FUSB_ERROR("Parse string descriptor failed (len: %d) !!!", FUSB_USBSTR_MIN_LEN);
        return FUSB_ERR_DESC_PARSE_ERR;
    }

    /* check if string descriptor header is valid */
    total_len = parser->usb_str->len;
    if ((total_len < FUSB_DESCRIPTOR_HEADER_SIZE) ||
        ((total_len & 1) != 0) ||
        (parser->usb_str->type != FUSB_DESC_TYPE_STRING))
    {
        FUSB_ERROR("Get invalid string descriptor (len: %d) !!!", FUSB_USBSTR_MIN_LEN);
        return FUSB_ERR_DESC_PARSE_ERR;
    }

    /* return if no need to get more */
    if (total_len <= FUSB_USBSTR_MIN_LEN)
    {
        return FUSB_SUCCESS;
    }

    /* re-malloc usb string desc buffer with full length */
    FASSERT(parser->usb_str);
    FUSB_FREE(instance, parser->usb_str);
    parser->usb_str = NULL;

    parser->usb_str = FUSB_ALLOCATE(instance, total_len, FUSB_DEFAULT_ALIGN);
    if (NULL == parser->usb_str)
    {
        return FUSB_ERR_ALLOCATE_FAIL;
    }

    /* get the whole string descriptor */
    if (FUsbGetStringDescriptor(dev, FUSB_DR_DESC, FUSB_DESC_TYPE_STRING, id,  FUSB_DEFAULT_LANG_ID,
                                parser->usb_str, total_len) < 0)
    {
        FUSB_ERROR("Parse string descriptor failed (len: %d)!!!", total_len);
        return FUSB_ERR_DESC_PARSE_ERR;
    }

    if ((parser->usb_str->len < FUSB_DESCRIPTOR_HEADER_SIZE) ||
        ((parser->usb_str->len & 1) != 0) ||
        (parser->usb_str->type != FUSB_DESC_TYPE_STRING))
    {
        FUSB_ERROR("Get invalid string descriptor (len: %d) !!!", total_len);
        return FUSB_ERR_DESC_PARSE_ERR;
    }

    /* convert into ASCII string */
    usb_str = parser->usb_str;
    char_num = (usb_str->len - FUSB_DESCRIPTOR_HEADER_SIZE) / 2; /* in 16-bit way */

    if (char_num >= FUSB_STRDESC_BUF_MAX - 1)
    {
        return FUSB_ERR_NOT_SUPPORT;
    }

    for (u8 i = 0; i < char_num; i++)
    {
        character = usb_str->string[i];
        if (character < ' '     /* 0x20 */
            || character > '~') /* 0x7E */
        {
            character = '_';
        }

        parser->str_buf[i] = (char)character;
    }

    parser->str_buf[char_num] = '\0';
    return FUSB_SUCCESS;
}

/**
 * @name: FUsbGetString
 * @msg: 获取刚刚检索到的字符串描述符内容
 * @return {const char *}, 字符串描述符中的内容
 * @param {FUsbDev} *dev, USB设备实例
 */
const char *FUsbGetString(const FUsbDev *const dev)
{
    FASSERT(dev);
    return (const char *)dev->string_parser.str_buf;
}