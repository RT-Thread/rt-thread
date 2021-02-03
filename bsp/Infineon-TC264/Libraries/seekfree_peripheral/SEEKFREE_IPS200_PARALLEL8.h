
/*/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		2.0寸IPS屏幕
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
						模块管脚            	单片机管脚
						D0       		查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D0_PIN 宏定义
						D1             	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D1_PIN 宏定义
						D2            	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D2_PIN 宏定义
						D3             	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D3_PIN 宏定义
						D4            	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D4_PIN 宏定义
						D5         		查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D5_PIN 宏定义
						D6           	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D6_PIN 宏定义
						D7           	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_D7_PIN 宏定义
                                                                                            
						BL          	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_BL_PIN 宏定义
						CS            	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_CS_PIN 宏定义
						RD            	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_RD_PIN 宏定义
						WR           	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_WR_PIN 宏定义
						RS          	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_RS_PIN 宏定义
						RST            	查看SEEKFREE_IPS200_PARALLEL8.H文件内的IPS200_RST_PIN 宏定义

						电源引脚
						VCC 3.3V电源
						GND 电源地
						最大分辨率240*320
					------------------------------------ 

 ********************************************************************************************************************/

#ifndef _SEEKFREE_IPS200PARALLEL8_H
#define _SEEKFREE_IPS200PARALLEL8_H

#include "common.h"
#include "SEEKFREE_FONT.h"

     
//-------常用颜色在SEEKFREE_FONT.h文件中定义----------
//#define RED          	    0xF800	//红色
//#define BLUE         	    0x001F  //蓝色
//#define YELLOW       	    0xFFE0	//黄色
//#define GREEN        	    0x07E0	//绿色
//#define WHITE        	    0xFFFF	//白色
//#define BLACK        	    0x0000	//黑色 
//#define GRAY  			0X8430 	//灰色
//#define BROWN 			0XBC40 	//棕色
//#define PURPLE    		0XF81F	//紫色
//#define PINK    		    0XFE19	//粉色


#define IPS200_BGCOLOR      WHITE	//背景颜色
#define IPS200_PENCOLOR     RED		//画笔颜色


//引脚只能选择B C D这三个端口中的引脚，便于使用快速GPIO以提高显示速度
#define IPS200_RD_PIN  		P15_3
#define IPS200_WR_PIN  		P15_5
#define IPS200_RS_PIN  		P15_1
#define IPS200_RST_PIN 		P15_0
#define IPS200_CS_PIN  		P15_2
#define IPS200_BL_PIN  		P15_4





//D0-D3四个数据引脚必须连续 例如C0-C3,C1-C4等等，
//D4-D7四个数据引脚必须连续 例如B0-B3,B1-B4等等。
//可以连接到不同端口的意思就是屏幕的D0-D3与C1-C4连接，D4-D7与B2-B5连接。
//切换引脚后注意修改IPS200_DATA_PORT1和IPS200_DATA_PORT2宏定义
#define IPS200_D0_PIN 		P11_9
#define IPS200_D1_PIN 		P11_10
#define IPS200_D2_PIN 		P11_11
#define IPS200_D3_PIN 		P11_12
#define IPS200_D4_PIN 		P13_0
#define IPS200_D5_PIN 		P13_1
#define IPS200_D6_PIN 		P13_2
#define IPS200_D7_PIN 		P13_3

//定义数据端口所在PORT，切换引脚后务必根据引脚所在PORT进行更改
#define IPS200_DATA_PORT1    3       //0：P00端口  1：P02端口  2：P10端口  3：P11端口  4：P13端口  5：P14端口  6：P15端口  7：P20端口  8：P21端口  9：P22端口  10：P23端口  11：P32端口  12：P33端口

#define IPS200_DATAPORT1 	(((Ifx_P *)IfxPort_cfg_indexMap[IPS200_DATA_PORT1].module)->OUT.U)	    //宏定义数据口GPIO的输出寄存器
#define DATA_START_NUM1		(IPS200_D0_PIN&0x1f)  //宏定义数据引脚的起始编号


#define IPS200_DATA_PORT2    4       //0：P00端口  1：P02端口  2：P10端口  3：P11端口  4：P13端口  5：P14端口  6：P15端口  7：P20端口  8：P21端口  9：P22端口  10：P23端口  11：P32端口  12：P33端口
                            
#define IPS200_DATAPORT2 	(((Ifx_P *)IfxPort_cfg_indexMap[IPS200_DATA_PORT2].module)->OUT.U)		//宏定义数据口GPIO的输出寄存器
#define DATA_START_NUM2		(IPS200_D4_PIN&0x1f)  //宏定义数据引脚的起始编号









#define IPS200_BL(x)		gpio_set(IPS200_BL_PIN,x)
#define IPS200_CS(x)       	gpio_set(IPS200_CS_PIN,x)
#define IPS200_RD(x)       	gpio_set(IPS200_RD_PIN,x)
#define IPS200_WR(x)       	gpio_set(IPS200_WR_PIN,x)
#define IPS200_RS(x)       	gpio_set(IPS200_RS_PIN,x)
#define IPS200_RST(x)      	gpio_set(IPS200_RST_PIN,x)


#define IPS200_W 240
#define IPS200_H 320


//定义显示方向
//0 竖屏模式
//1 竖屏模式  旋转180°
//2 横屏模式
//3 横屏模式  旋转180°
#define IPS200_DISPLAY_DIR 0

#if (0==IPS200_DISPLAY_DIR || 1==IPS200_DISPLAY_DIR)
#define	IPS200_X_MAX	IPS200_W	//液晶X方宽度
#define IPS200_Y_MAX	IPS200_H   //液晶Y方宽度
     
#elif (2==IPS200_DISPLAY_DIR || 3==IPS200_DISPLAY_DIR)
#define	IPS200_X_MAX	IPS200_H	//液晶X方宽度
#define IPS200_Y_MAX	IPS200_W   //液晶Y方宽度
     
#else
#error "IPS200_DISPLAY_DIR 定义错误"
     
#endif


void ips200_init(void); //初始化硬件
void ips200_w_data(uint8 dat);
void ips200_wr_reg(uint8 com);
void ips200_wr_data(uint8 dat);
void ips200_wr_data16(uint16 dat);
void ips200_w_reg(uint8 com,uint8 dat);
void ips200_address_set(uint16 x1,uint16 y1,uint16 x2,uint16 y2);
void ips200_clear(uint16 color);
void ips200_drawpoint(uint16 x,uint16 y,uint16 color);
void ips200_showchar(uint16 x,uint16 y,const int8 dat);
void ips200_showstr(uint16 x,uint16 y,const int8 dat[]);


void ips200_showint8(uint16 x,uint16 y,int8 dat);
void ips200_showuint8(uint16 x,uint16 y,uint8 dat);
void ips200_showint16(uint16 x,uint16 y,int16 dat);
void ips200_showuint16(uint16 x,uint16 y,uint16 dat);
void ips200_showint32(uint16 x,uint16 y,int dat,uint8 num);
void ips200_showfloat(uint16 x,uint16 y,double dat,int8 num,int8 pointnum);
void ips200_showimage(uint16 x,uint16 y,uint16 w,uint16 l,const unsigned char *p);

void ips200_displayimage032(uint8 *p, uint16 width, uint16 height);
void ips200_displayimage032_zoom(uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage032_zoom1(uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_zoom1(uint16 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_grayscale_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage7725(uint8 *p, uint16 width, uint16 height);
void ips200_display_chinese(uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, uint16 color);

#endif

