/*****************************************************************************
 * 文件名: sendwave.c
 *   版本: V1.2
 *   作者: 官文亮
 *   日期: 2018/9/2
 *   说明: 本文件属于SerialTool软件的波形显示功能的下位机参考代码, 作用是将数
 *         值转换为SerialTool可以识别的帧, 用户需实现串口发送函数, 结合本程序
 *         即可实现串口发送波形的显示, 本程序适合SerialTool v1.1.6及后续版本.
 *
 * SerialTool源码链接: https://github.com/gztss/SerialTool
 * SerialTool安装包链接: https://github.com/gztss/SerialTool/releases
 *
 *****************************************************************************/

#include "sendwave.h"

/* 此处定义一些常量, 请勿修改! */
enum
{
    Ch_Num          = 16,       // 通道数量
    Frame_MaxBytes  = 80,       // 最大帧长度
    Frame_Head      = 0xA3,     // 帧头识别字
    Frame_PointMode = 0xA8,     // 点模式识别字
    Frame_SyncMode  = 0xA9,     // 同步模式识别字
    Frame_InfoMode  = 0xAA,     // 信息帧识别字
    Format_Int8     = 0x10,     // int8识别字
    Format_Int16    = 0x20,     // int16识别字
    Format_Int32    = 0x30,     // int32识别字
    Format_Float    = 0x00      // float识别字
};

/* 函数功能: 发送int8类型数据
 * 函数参数:
 *     buffer : 帧缓冲区, 需要4byte
 *     channel: 通道, 取值范围为0~15
 *     value  : 通道数据值, 8bit有符号整数
 *     返回值 : 数据帧长度(单位为byte)
 **/
char ws_point_int8(char *buffer, char channel, int8_t value)
{
    if ((uint8_t)channel < Ch_Num)   // 通道验证
    {
        // 帧头
        *buffer++ = Frame_Head;
        *buffer++ = Frame_PointMode;
        *buffer++ = channel | Format_Int8; // 通道及数据格式信息
        *buffer = value; // 数据添加到帧
        return 4; // 数据帧长度
    }

    return 0;
}

/* 函数功能: 发送int16类型数据
 * 函数参数:
 *     buffer : 帧缓冲区, 需要5byte
 *     channel: 通道, 取值范围为0~15
 *     value  : 通道数据值, 16bit有符号整数
 *     返回值 : 数据帧长度(单位为byte)
 **/
char ws_point_int16(char *buffer, char channel, int16_t value)
{
    if ((uint8_t)channel < Ch_Num)   // 通道验证
    {
        // 帧头
        *buffer++ = Frame_Head;
        *buffer++ = Frame_PointMode;
        *buffer++ = channel | Format_Int16; // 通道及数据格式信息
        // 数据添加到帧
        *buffer++ = (value >> 8) & 0xFF;
        *buffer = value & 0xFF;
        return 5; // 数据帧长度
    }

    return 0;
}

/* 函数功能: 发送int32类型数据
 * 函数参数:
 *     buffer : 帧缓冲区, 需要7byte
 *     channel: 通道, 取值范围为0~15
 *     value  : 通道数据值, 32bit有符号整数
 *     返回值 : 数据帧长度(单位为byte)
 **/
char ws_point_int32(char *buffer, char channel, int32_t value)
{
    if ((uint8_t)channel < Ch_Num)   // 通道验证
    {
        // 帧头
        *buffer++ = Frame_Head;
        *buffer++ = Frame_PointMode;
        *buffer++ = channel | Format_Int32; // 通道及数据格式信息
        // 数据添加到帧
        *buffer++ = (value >> 24) & 0xFF;
        *buffer++ = (value >> 16) & 0xFF;
        *buffer++ = (value >> 8) & 0xFF;
        *buffer = value & 0xFF;
        return 7; // 数据帧长度
    }

    return 0;

}

/* 函数功能: 发送float类型数据
 * 函数参数:
 *     buffer : 帧缓冲区, 需要7byte
 *     channel: 通道, 取值范围为0~15
 *     value  : 通道数据值, 类型为单精度浮点(32bit)
 *     返回值 : 数据帧长度(单位为byte)
 **/
char ws_point_float(char *buffer, char channel, float value)
{
    // 这个联合变量用来实现浮点到整形的变换
    union
    {
        float f;
        uint32_t i;
    } temp;

    if ((uint8_t)channel < Ch_Num)   // 通道验证
    {
        temp.f = value;
        // 帧头
        *buffer++ = Frame_Head;
        *buffer++ = Frame_PointMode;
        *buffer++ = channel | Format_Float; // 通道及数据格式信息
        // 数据添加到帧
        *buffer++ = (temp.i >> 24) & 0xFF;
        *buffer++ = (temp.i >> 16) & 0xFF;
        *buffer++ = (temp.i >>  8) & 0xFF;
        *buffer = temp.i & 0xFF;
        return 7; // 数据帧长度
    }

    return 0;
}

/* 函数功能: 同步发送模式缓冲区初始化
 * 函数参数:
 *     buffer : 帧缓冲区, 最多需要(Frame_MaxBytes + 3) bytes
 **/
void ws_frame_init(char *buffer)
{
    *buffer++ = Frame_Head;
    *buffer++ = Frame_SyncMode;
    *buffer = 0;
}

/* 函数功能: 获取同步模式缓冲区长度(单位bytes)
 * 函数参数:
 *     buffer : 同步模式帧缓冲区
 **/
char ws_frame_length(const char *buffer)
{
    return buffer[2] + 3;
}

/* 函数功能: 在数同步据帧中加入一个int8类型数据
 * 函数参数:
 *     buffer : 已经初始化的帧缓冲区
 *     channel: 通道, 取值范围为0~15
 *     value  : 通道数据值, 类型为int8
 *     返回值 : 0, 加入成功, 1, 帧长度已经达到上限或通道错误
 **/
char ws_add_int8(char *buffer, char channel, int8_t value)
{
    char count = buffer[2];
    char *p = buffer + count + 3; // 跳过前面数据

    count += 2;

    // 帧长度及通道验证
    if (count <= Frame_MaxBytes && (uint8_t)channel < Ch_Num)
    {
        buffer[2] = count;
        *p++ = channel | Format_Int8; // 通道及数据格式信息
        *p = value; // 数据添加到帧
        return 1;
    }

    return 0;
}

/* 函数功能: 在数同步据帧中加入一个int16类型数据
 * 函数参数:
 *     buffer : 已经初始化的帧缓冲区
 *     channel: 通道, 取值范围为0~15
 *     value  : 通道数据值, 类型为int16
 *     返回值 : 0, 加入成功, 1, 帧长度已经达到上限或通道错误
 **/
char ws_add_int16(char *buffer, char channel, int16_t value)
{
    char count = buffer[2];
    char *p = buffer + count + 3; // 跳过前面数据

    count += 3;

    // 帧长度及通道验证
    if (count <= Frame_MaxBytes && (uint8_t)channel < Ch_Num)
    {
        buffer[2] = count;
        *p++ = channel | Format_Int16; // 通道及数据格式信息
        // 数据添加到帧
        *p++ = (value >> 8) & 0xFF;
        *p = value & 0xFF;
        return 1;
    }

    return 0;
}

/* 函数功能: 在数同步据帧中加入一个int32类型数据
 * 函数参数:
 *     buffer : 已经初始化的帧缓冲区
 *     channel: 通道, 取值范围为0~15
 *     value  : 通道数据值, 类型为int32
 *     返回值 : 0, 加入成功, 1, 帧长度已经达到上限或通道错误
 **/
char ws_add_int32(char *buffer, char channel, int32_t value)
{
    char count = buffer[2];
    char *p = buffer + count + 3; // 跳过前面数据

    count += 5;

    // 帧长度及通道验证
    if (count <= Frame_MaxBytes && (uint8_t)channel < Ch_Num)
    {
        buffer[2] = count;
        *p++ = channel | Format_Int32; // 通道及数据格式信息
        // 数据添加到帧
        *p++ = (value >> 24) & 0xFF;
        *p++ = (value >> 16) & 0xFF;
        *p++ = (value >> 8) & 0xFF;
        *p = value & 0xFF;
        return 1;
    }

    return 0;
}

/* 函数功能: 在数同步据帧中加入一个float类型数据
 * 函数参数:
 *     buffer : 已经初始化的帧缓冲区
 *     channel: 通道, 取值范围为0~15
 *     value  : 通道数据值, 类型为float
 *     返回值 : 0, 加入成功, 1, 帧长度已经达到上限或通道错误
 **/
char ws_add_float(char *buffer, char channel, float value)
{
    char count = buffer[2];
    char *p = buffer + count + 3; // 跳过前面数据

    count += 5;

    // 帧长度及通道验证
    if (count <= Frame_MaxBytes && (uint8_t)channel < Ch_Num)
    {
        union
        {
            float f;
            uint32_t i;
        } temp;
        buffer[2] = count;
        temp.f = value;
        *p++ = channel | Format_Float; // 通道及数据格式信息
        // 数据添加到帧
        *p++ = (temp.i >> 24) & 0xFF;
        *p++ = (temp.i >> 16) & 0xFF;
        *p++ = (temp.i >>  8) & 0xFF;
        *p = temp.i & 0xFF;
        return 1;
    }

    return 0;
}

/* 函数功能: 发送时间戳
 * 函数参数:
 *     buffer : 帧缓冲区
 *     ts     : 时间戳
 *     返回值 : 数据帧长度, (单位: bytes)
 **/
char ws_send_timestamp(char *buffer, ws_timestamp_t* ts)
{
    uint8_t temp;

    *buffer++ = Frame_Head;
    *buffer++ = Frame_InfoMode;
    temp = (ts->year << 1) | ((ts->month >> 3) & 0x01);
    *buffer++ = (char)temp;
    temp = (ts->month << 5) | (ts->day & 0x1F);
    *buffer++ = (char)temp;
    temp = (ts->hour << 3) | ((ts->min >> 3) & 0x07);
    *buffer++ = (char)temp;
    temp = (ts->min << 5) | ((ts->sec >> 1) & 0x1F);
    *buffer++ = (char)temp;
    temp = (ts->sec << 7) | ((ts->msec >> 3) & 0x7F);
    *buffer++ = (char)temp;
    temp = (ts->msec << 5) | ((ts->sampleRate >> 16) & 0x1F);
    *buffer++ = (char)temp;
    *buffer++ = (char)((ts->sampleRate >> 8) & 0xFF);
    *buffer = (char)(ts->sampleRate & 0xFF);
    return 10;
}

/* end of file sendwave.c */
