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

#ifndef __SENDWAVE_H
#define __SENDWAVE_H

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
  extern "C" {
#endif
#endif // __cplusplus

/* 定义各通道 */
#define     CH1     0
#define     CH2     1
#define     CH3     2
#define     CH4     3
#define     CH5     4
#define     CH6     5
#define     CH7     6
#define     CH8     7
#define     CH9     8
#define     CH10    9
#define     CH11    10
#define     CH12    11
#define     CH13    12
#define     CH14    13
#define     CH15    14
#define     CH16    15

/* 信息帧数据结构定义 */
typedef struct {
    uint8_t year;           // 0~99 -> 2000 ~ 2099, 7 bit
    uint8_t month;          // 1 ~ 12, 4 bit
    uint8_t day;            // 1 ~ 31, 5 bit
    uint8_t hour;           // 0 ~ 23, 5 bit
    uint8_t min;            // 0 ~ 59, 6 bit
    uint8_t sec;            // 0 ~ 59, 6 bit
    uint16_t msec;          // 0 ~ 999, 10 bit
    uint32_t sampleRate;    // 0 ~ 2000000, 21 bit
} ws_timestamp_t;

/* 公共函数声明 */
char ws_point_int8(char *buffer, char channel, int8_t value);
char ws_point_int16(char *buffer, char channel, int16_t value);
char ws_point_int32(char *buffer, char channel, int32_t value);
char ws_point_float(char *buffer, char channel, float value);
void ws_frame_init(char *buffer);
char ws_frame_length(const char *buffer);
char ws_add_int8(char *buffer, char channel, int8_t value);
char ws_add_int16(char *buffer, char channel, int16_t value);
char ws_add_int32(char *buffer, char channel, int32_t value);
char ws_add_float(char *buffer, char channel, float value);
char ws_send_timestamp(char *buffer, ws_timestamp_t* ts);

#ifdef __cplusplus
#if __cplusplus
  }
#endif
#endif // __cplusplus

#endif // __SENDWAVE_H

/* end of file sendwave.h */
