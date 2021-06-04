/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0 
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-15     liuhy       first implementation.
 */
/*
 * 程序清单：这是一个 I2C 设备使用例程
 * 例程导出了 i2c_e2_sample 命令到控制终端
 * 命令调用格式：i2c_e2_sample
 * 命令解释：使用默认的I2C总线设备i2c0
 * 程序功能：通过 I2C 设备写读e2prom，ST24C04WP。
*/
                         
/*ST24C04WP 有2个Block ：Block0 的从机地址为：0x50,Block1 的从机地址为：0x51
            一个Block有 256字节，一页16字节,写只可在一页内(超过一页的范围后,会回到页的开始),读无页限制*/
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_I2C

#define I2C_BUS_NAME    "i2c0"                   /*I2C总线设备名称 */
#define SLAVE_ADDR      0x50                     /*从机地址*/
#define MEM_ADDR        0x00                     /*从机的起始储存地址,范围：0x00到0xEF(例程写读范围：2页)*/
#define ADDR_LEN        1                        /*定义从机储存地址的长度，默认8位,1字节*/
#define STR_LEN         16                       /*接收发送的页数据长度 ,最大16*/     

static rt_uint8_t mem_addr,rx_buffer[33] = { 0U };  /*读两页,需要32字节，字符串结束'\0'*/                 
/*第一个字节' '用来放 E2PROM 的内存地址,最后一个字节'\0'作为子串的结束，不存入e2prom*/
static rt_uint8_t tx_buffer1[STR_LEN + ADDR_LEN + 1] = " e2prom example !\0";                                          
static rt_uint8_t tx_buffer2[STR_LEN + ADDR_LEN + 1] = " ABCDEFGH12345678\0";  

static void i2c_e2_sample(int argc, char *argv[])
{
    struct rt_i2c_bus_device *i2c_bus = RT_NULL;     /* I2C总线设备句柄 */
    struct rt_i2c_msg i2c_msg[2];                    /* I2C消息 */
    rt_size_t s_stat;
    
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(I2C_BUS_NAME);    /* 通过名字获取I2C总线设备的句柄 */
    
    if( i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find i2c device :%s !\n",I2C_BUS_NAME);
        return;
    }
         
        /*写T24C04WP
                如果  (MEM_ADDR & 0x0F) + STR_LEN <= 16, 写的范围为：(MEM_ADDR        , MEM_ADDR + STR_LEN        )
                                                                     (0x10 + MEM_ADDR , 0x10 + MEM_ADDR + STR_LEN )
                如果  (MEM_ADDR & 0x0F) + STR_LEN >  16, 超出范围的部分会在页内循环写。*/
        tx_buffer1[0] = MEM_ADDR;
    
        /*初始化消息*/
        i2c_msg[0].addr = SLAVE_ADDR;                /* 从机地址 */
        i2c_msg[0].len  = ADDR_LEN + STR_LEN ;       /* 写入的长度，地址+数据 */
        i2c_msg[0].buf = tx_buffer1;                 /* 待写入第一段数据 */
        i2c_msg[0].flags = RT_I2C_WR;                /* I2C写 */   
        s_stat = rt_i2c_transfer(i2c_bus,i2c_msg,1);   /* 写入第一段数据 */
    
        if( s_stat == 1 )rt_kprintf("write successful. \nmessage: %s\n",&tx_buffer1[1]);
                    else rt_kprintf("device %s write fail \n",I2C_BUS_NAME);
        
        tx_buffer2[0] = MEM_ADDR + 0x10;     /*加一页*/
        i2c_msg[0].buf = tx_buffer2;         /* 待写入第二段数据 */
        s_stat = rt_i2c_transfer(i2c_bus,i2c_msg,1);   /* 写入第二段数据 */
    
        if( s_stat == 1 )rt_kprintf("write successful. \nmessage: %s\n",&tx_buffer2[1]);
                    else rt_kprintf("device %s write fail \n",I2C_BUS_NAME);
    
        /*读T24C04WP  读2页的数据。读数据需要2条消息：第一条消息：发送读取的地址。
                                                      第二条消息：读取具体的数据。*/
       
        mem_addr = MEM_ADDR & 0xF0;   /*从页的开始读*/
        
        i2c_msg[0].len = ADDR_LEN;        
        i2c_msg[0].buf = &mem_addr;
        
        i2c_msg[1].addr = SLAVE_ADDR;          /* 从机地址 */                     
        i2c_msg[1].len  = 32;                  /* 读取的数据长度：2*16 */
        i2c_msg[1].buf = rx_buffer;            /* 数据存放地址 */
        i2c_msg[1].flags = RT_I2C_RD;          /* I2C读 */
        s_stat = rt_i2c_transfer(i2c_bus,i2c_msg,2);   /* 读已写的2页 */
        
        if( s_stat == 2 )rt_kprintf(" read successful \n messege : %s \n",rx_buffer);
                    else
            rt_kprintf("read  fail \n");
        
        return;
    
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(i2c_e2_sample, i2c e2prom sample);

#endif
