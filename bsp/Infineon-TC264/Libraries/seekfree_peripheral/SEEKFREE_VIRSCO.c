/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		虚拟示波器协议
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note		    示波器下载地址：https://pan.baidu.com/s/198CMXTZsbI3HAEqNXDngBw（包含清华直立方案资料）
 ********************************************************************************************************************/



#include "zf_uart.h"
#include "SEEKFREE_VIRSCO.h"


uint8 virtual_scope_data[10];

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CRC校验（内部使用，用户无需关心）
//  @param      Buf             需要进行CRC计算的数据地址
//  @param      CRC_CNT         需要进行CRC计算的数据个数
//  @return     void		
//  @since      v1.0		
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
uint16 CRC_CHECK(uint8 *Buf, uint8 CRC_CNT)
{
    uint16 CRC_Temp;
    uint8 i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      虚拟示波器数据转换函数
//  @param      data1       要发送的第一个数据
//  @param      data2       要发送的第二个数据
//  @param      data3       要发送的第三个数据
//  @param      data4       要发送的第四个数据
//  @param      *dat        转换之后存放数据的地址
//  @return     void		
//  @since      v1.0		
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void data_conversion(int16 data1, int16 data2, int16 data3, int16 data4, uint8 *dat)
{
    uint16 CRC16 = 0;
    
    dat[0] = (uint8)((uint16)data1&0xff);
    dat[1] = (uint8)((uint16)data1>>8);
    
    dat[2] = (uint8)((uint16)data2&0xff);
    dat[3] = (uint8)((uint16)data2>>8);
    
    dat[4] = (uint8)((uint16)data3&0xff);
    dat[5] = (uint8)((uint16)data3>>8);
    
    dat[6] = (uint8)((uint16)data4&0xff);
    dat[7] = (uint8)((uint16)data4>>8);

    CRC16  = CRC_CHECK(dat,8);
    dat[8] = (uint8)(CRC16&0xff);
    dat[9] = (uint8)(CRC16>>8);
    
    //uart_putbuff(UART_0,dat,10);  //数据转换完成后，使用串口发送将数组的内容发送出去
}

