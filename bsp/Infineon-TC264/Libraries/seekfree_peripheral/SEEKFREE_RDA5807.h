/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		MPU6050
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
						软件IIC
                        SCL                 查看SEEKFREE_IIC文件内的SEEKFREE_SCL宏定义
						SDA                 查看SEEKFREE_IIC文件内的SEEKFREE_SDA宏定义

                        硬件IIC
                        SCL                 查看init_mpu6050_hardware函数内IIC初始化时所带参数
						SDA                 查看init_mpu6050_hardware函数内IIC初始化时所带参数
					------------------------------------
					注意事项：RDA5807的SCL与SDA都需要串联1K电阻然后在与单片机连接，否则可能无法通信
 ********************************************************************************************************************/


#ifndef _FM5807_H
#define _FM5807_H
#include "common.h"
#include "SEEKFREE_FONT.h"






#define RAD5807_DELAY_TIME 200


void rda5807_init(float freq);
void rda5807_set_transimt(void);
void rda5807_set_idle(void);
void rda5807_set_channel(float freq);
void rda5807_channel_config(uint16 reg_chn);
uint8 rda5807_read_rssi(void);


#endif


