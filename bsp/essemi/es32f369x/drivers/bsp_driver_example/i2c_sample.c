/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-15     liuhy       first implementation.
 */
/*
 * 程序清单：这是一个 I2C 设备使用例程
 * 例程导出了 i2c_io_sample 命令到控制终端
 * 命令调用格式：i2c_io_sample
 * 命令解释：使用默认的I2C总线设备i2c0
 * 程序功能：通过 I2C 设备接收数据并打印，然后将接收的字符加1输出。
*/

#include <rtthread.h>
#include <rtdevice.h>

#define I2C_BUS_NAME          "i2c0"  /* I2C总线设备名称 */
#define SLAVE_ADDR                  0x2D    /* 从机地址 */
#define STR_LEN                       16    /* 接收发送的数据长度 */

static void i2c_io_sample(int argc, char *argv[])
{
    
    struct rt_i2c_bus_device *i2c_bus = RT_NULL;     /* I2C总线设备句柄 */
    struct rt_i2c_msg temp_msg;                             /* I2C消息 */
    rt_uint8_t buffer[STR_LEN] = { 0U }; 
    rt_uint32_t i,num_msg;
    rt_size_t s_stat;
    
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(I2C_BUS_NAME);    /* 通过名字获取I2C总线设备的句柄 */
    
    if( i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find i2c device :%s !\n",I2C_BUS_NAME);
        
        return;
    }
    
        /*初始化消息*/
        temp_msg.addr = SLAVE_ADDR;  /* 从机地址 */
        temp_msg.len  = STR_LEN;     /* 传输的数据长度 */
        temp_msg.buf = buffer;       /* 读写缓存器 */
    
        num_msg = 1;             /* 传输一条消息 */
    
        temp_msg.flags = RT_I2C_RD;             /* I2C读 */
        s_stat = rt_i2c_transfer(i2c_bus,&temp_msg,num_msg);   /* 传输消息 */
        
        rt_thread_mdelay(400); 
        
        if( s_stat == num_msg )
        {
            rt_kprintf("receive successful. \n receive messege : %s \n:",buffer);
            
            for( i = 0 ; i < STR_LEN ; i++)
            rt_kprintf(" %x",(unsigned int)buffer[i]);
            
            rt_kprintf("\n");
        }
        else
        {
            rt_kprintf("device s% recieve fail \n buffer : s%\n",I2C_BUS_NAME,buffer);
            return;
        }
        
        for( i = 0 ; i < STR_LEN ; i++)
        buffer[i]++;
    
        temp_msg.flags = RT_I2C_WR;             /* I2C写 */
        s_stat = rt_i2c_transfer(i2c_bus,&temp_msg,num_msg);   /* 传输一条 */
        
        rt_thread_mdelay(400);
        
        if( s_stat == num_msg )
        {
            rt_kprintf(" send successful \n messege : %s \n:",buffer);
            
            for( i = 0 ; i < STR_LEN ; i++)
            rt_kprintf(" %x",(unsigned int)buffer[i]);
            
            rt_kprintf("\n");
        }
        else
        {
            rt_kprintf("device s% send fail \n",I2C_BUS_NAME);
            return;
        }
        
        return;
    
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(i2c_io_sample, i2c io sample);
