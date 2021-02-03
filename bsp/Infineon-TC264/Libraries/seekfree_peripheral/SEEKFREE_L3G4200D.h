/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		L3G4200D
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
						SCL                 查看SEEKFREE_SIMIIC文件内的SEEKFREE_SCL宏定义
						SDA                 查看SEEKFREE_SIMIIC文件内的SEEKFREE_SDA宏定义
					------------------------------------ 
 ********************************************************************************************************************/



#ifndef _SEEKFREE_L3G4200D_H
#define _SEEKFREE_L3G4200D_H

#include "common.h"



//----------L3G4200D内部寄存器地址---------
#define L3G4200D_ID             0x69
#define WHO_AM_I_4200           0x0F
#define CTRL_REG1_4200          0x20
#define CTRL_REG2_4200          0x21
#define CTRL_REG3_4200          0x22
#define CTRL_REG4_4200          0x23
#define CTRL_REG5_4200          0x24
#define REFERENCE_4200          0x25
#define OUT_TEMP_4200           0x26
#define STATUS_REG_4200         0x27
#define OUT_X_L_4200            0x28
#define OUT_X_H_4200            0x29
#define OUT_Y_L_4200            0x2A
#define OUT_Y_H_4200            0x2B
#define OUT_Z_L_4200            0x2C
#define OUT_Z_H_4200            0x2D
#define FIFO_CTRL_REG_4200      0x2E
#define FIFO_SRC_REG_4200       0x2F
#define INT1_CFG_4200           0x30
#define INT1_SRC_4200           0x31
#define INT1_TSH_XH_4200        0x32
#define INT1_TSH_XL_4200        0x33
#define INT1_TSH_YH_4200        0x34
#define INT1_TSH_YL_4200        0x35
#define INT1_TSH_ZH_4200        0x36
#define INT1_TSH_ZL_4200        0x37
#define INT1_DURATION_4200      0x38


#define	L3G4200_DEV_ADD	        0xD2>>1	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改




extern int16 gyro_x, gyro_y, gyro_z;


void l3g4200d_init(void);
void get_l3g4200d(void);






#endif
