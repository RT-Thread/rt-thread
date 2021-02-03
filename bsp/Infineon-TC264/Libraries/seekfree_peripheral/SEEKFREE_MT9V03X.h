/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		总钻风
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 * @note		
					接线定义：
					------------------------------------ 
					模块管脚            			单片机管脚
					SDA(51的RX)         		查看SEEKFREE_MT9V03X.h文件中的MT9V03X_COF_UART_TX宏定义
					SCL(51的TX)         		查看SEEKFREE_MT9V03X.h文件中的MT9V03X_COF_UART_RX宏定义
					场中断(VSY)         		查看SEEKFREE_MT9V03X.h文件中的MT9V03X_VSYNC_PIN宏定义
					行中断(HREF)				程序没有使用，因此不连接
					像素中断(PCLK)      		查看SEEKFREE_MT9V03X.h文件中的MT9V03X_PCLK_PIN宏定义
					数据口(D0-D7)			查看SEEKFREE_MT9V03X.h文件中的MT9V03X_DATA_PIN宏定义
					------------------------------------ 
	
					默认分辨率是           			188*120
					默认FPS                 50帧
 ********************************************************************************************************************/



#ifndef _SEEKFREE_MT9V03X_h
#define _SEEKFREE_MT9V03X_h

#include "common.h"
#include "IfxDma_cfg.h"
#include "zf_uart.h"

//配置摄像头参数
#define MT9V03X_W               188             	//图像宽度 	范围1-188
#define MT9V03X_H               120             	//图像高度	范围1-120



//--------------------------------------------------------------------------------------------------
//引脚配置
//--------------------------------------------------------------------------------------------------
#define MT9V03X_COF_UART        UART_1         		//配置摄像头所使用到的串口
#define MT9V03X_COF_UART_TX     UART1_TX_P02_2
#define MT9V03X_COF_UART_RX     UART1_RX_P02_3

#define MT9V03X_VSYNC_PIN       ERU_CH3_REQ6_P02_0  //场中断引脚	可选范围参考ERU_PIN_enum枚举 不可与像素引脚选择为同一个通道，或者是共用中断的通道
													//例如场中断选择ERU_CH3 那么像素引脚就不能选择ERU_CH7，因为3和7的中断是共用的。

#define MT9V03X_DATA_PIN        P00_0  				//定义D0数据引脚  假设D0定义为P00_0 那么D1所使用的引脚则为P00_1，依次类推
													//可设置参数P00_0、P02_0、P15_0，不能设置为其他参数

#define MT9V03X_PCLK_PIN        ERU_CH2_REQ14_P02_1 //定义像素时钟引脚 可选范围参考ERU_PIN_enum枚举 不可与场中断引脚选择为同一个通道，或者是共用中断的通道
													//例如场中断选择ERU_CH3 那么像素引脚就不能选择ERU_CH7，因为3和7的中断是共用的。

#define MT9V03X_DMA_CH			IfxDma_ChannelId_5	//定义使用的DMA通道 0-47可选  通道号越大优先级越低

//摄像头命令枚举
typedef enum
{
    INIT = 0,               //摄像头初始化命令
    AUTO_EXP,               //自动曝光命令
    EXP_TIME,               //曝光时间命令
    FPS,                    //摄像头帧率命令
    SET_COL,                //图像列命令
    SET_ROW,                //图像行命令
    LR_OFFSET,              //图像左右偏移命令
    UD_OFFSET,              //图像上下偏移命令
    GAIN,                   //图像偏移命令
    CONFIG_FINISH,          //非命令位，主要用来占位计数
    
    COLOR_GET_WHO_AM_I = 0xEF,
    SET_EXP_TIME = 0XF0,    //单独设置曝光时间命令
    GET_STATUS,             //获取摄像头配置命令
    GET_VERSION,            //固件版本号命令
	
    SET_ADDR = 0XFE,        //寄存器地址命令
    SET_DATA                //寄存器数据命令
}CMD;
     
     
     
extern uint8    receive[3];         //仅用于接收配置信息时所用  禁止用户使用该变量
extern uint8    receive_num;        //仅用于接收配置信息时所用  禁止用户使用该变量
extern vuint8   uart_receive_flag;  //仅用于接收配置信息时所用  禁止用户使用该变量


extern uint8    mt9v03x_finish_flag;//一场图像采集完成标志位
extern uint8    mt9v03x_image[MT9V03X_H][MT9V03X_W];

void mt9v03x_uart_callback(void);
void set_config(UARTN_enum uartn, int16 buff[CONFIG_FINISH-1][2]);
void get_config(UARTN_enum uartn, int16 buff[CONFIG_FINISH-1][2]);
uint16 get_version(UARTN_enum uartn);
uint16 set_exposure_time(UARTN_enum uartn, uint16 light);

void mt9v03x_init(void);
void mt9v03x_vsync(void);
void mt9v03x_dma(void);
void seekfree_sendimg_03x(UARTN_enum uartn, uint8 *image, uint16 width, uint16 height);
void seekfree_sendimg_03x_usb_cdc(uint8 *image, uint16 width, uint16 height);



#endif

