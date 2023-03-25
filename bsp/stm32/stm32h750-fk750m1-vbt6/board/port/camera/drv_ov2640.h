
/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-03-24     spaceman          the first version
 */

#ifndef __DRV_OV2640_H__
#define __DRV_OV2640_H__

#include <rtthread.h>
#include <lcd_port.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  OV2640 ID
 */
#define OV2640_ID1      0x2640U
#define OV2640_ID2      0x2642U

#define OV2640_Enable  1
#define OV2640_Disable 0

// 用于设置输出的格式，被 ov2640_set_pixformat() 引用
#define Pixformat_RGB565 0
#define Pixformat_JPEG   1

// OV2640的特效模式，被 ov2640_set_effect() 引用
#define OV2640_Effect_Normal      0 // 正常模式
#define OV2640_Effect_Negative    1 // 负片模式，也就是颜色全部取反
#define OV2640_Effect_BW          2 // 黑白模式
#define OV2640_Effect_BW_Negative 3 // 黑白模式+负片模式

// 1. 定义OV2640实际输出的图像大小，可以根据实际的应用或者显示屏进行调整（同时也要修改配置参数里的时钟分频）
// 2. 这两个参数不会影响帧率，且不能超过对应模式的最大尺寸
// 3. SVGA模式下，输出图像最大分辨率为 800*600,  最大帧率30帧
// 4. UXGA模式下，输出图像最大分辨率为 1600*1200,最大帧率15帧
// 5. 要设置的图像长、宽必须能被4整除！
// 6. 要设置的图像长、宽比必须满足4:3，不然画面会被拉伸畸变
#define OV2640_Width  400 // 图像长度
#define OV2640_Height 300 // 图像宽度

// 1. 定义要显示的画面大小，数值一定要能被4整除！！
// 2. RGB565格式下，最终会由DCMI将OV2640输出的4:3图像裁剪为适应屏幕的比例
// 3. 此处的分辨率不能超过 OV2640_Width 和 OV2640_Height
// 4. 分辨率太高时，需要修改PCLK的时钟速度，详细计算说明可参考 dcmi_ov2640_cfg.h 里的 0xd3 寄存器配置
#define Display_Width  LCD_WIDTH
#define Display_Height LCD_HEIGHT

// 1.RGB565模式下，需要 图像分辨率*2 的大小
// 2.JPG模式下，需要的缓冲区大小并不是固定的，例如 640*480分辨率，JPG图像大概要占30K，
//   缓冲区预留2倍左右大小即可，用户可根据实际情况去设置,
#define OV2640_BufferSize Display_Width *Display_Height * 2 / 4 // DMA传输数据大小（32位宽）
// #define  OV2640_BufferSize       100*1024/4   // DMA传输数据大小（32位宽）

#define OV2640_SEL_Registers 0xFF // 寄存器组选择寄存器
#define OV2640_SEL_DSP       0x00 // 设置为0x00时，选择  DSP    寄存器组
#define OV2640_SEL_SENSOR    0x01 // 设置为0x01时，选择  SENSOR 寄存器组

// DSP 寄存器组 (0xFF = 0x00)
#define OV2640_DSP_RESET  0xE0 // 可选择复位 控制器、SCCB单元、JPEG单元、DVP接口单元等
#define OV2640_DSP_BPADDR 0x7C // 间接寄存器访问:地址
#define OV2640_DSP_BPDATA 0x7D // 间接寄存器访问:数据

// SENSOR 寄存器组 (0xFF = 0x01)
#define OV2640_SENSOR_COM7  0x12 // 公共控制,系统复位、摄像头分辨率选择、缩放模式、颜色彩条设置
#define OV2640_SENSOR_REG04 0x04 // 寄存器组4,可设置摄像头扫描方向等
#define OV2640_SENSOR_PIDH  0x0a // ID高字节
#define OV2640_SENSOR_PIDL  0x0b // ID低字节

void ov2640_set_pixformat(struct rt_i2c_bus_device *bus, rt_uint8_t pixformat);

rt_err_t ov2640_set_framesize(struct rt_i2c_bus_device *bus, rt_uint16_t width, rt_uint16_t height);

rt_err_t ov2640_set_horizontal_mirror(struct rt_i2c_bus_device *bus, rt_uint8_t configstate);
rt_err_t ov2640_set_vertical_flip(struct rt_i2c_bus_device *bus, rt_uint8_t configstate);

void ov2640_set_saturation(struct rt_i2c_bus_device *bus, rt_int8_t saturation);
void ov2640_set_brightness(struct rt_i2c_bus_device *bus, rt_int8_t brightness);
void ov2640_set_contrast(struct rt_i2c_bus_device *bus, rt_int8_t contrast);
void ov2640_set_effect(struct rt_i2c_bus_device *bus, rt_uint8_t effect_mode);

#ifdef __cplusplus
}
#endif

#endif
