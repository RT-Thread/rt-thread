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
 * 程序清单：这是一个 SPI 设备使用例程
 * 例程导出了 spi_io_sample 命令到控制终端
 * 命令调用格式：spi_io_sample
 * 程序功能：通过SPI设备先读取数据，然后每个字符加1后输出。
*/

#include <rtthread.h>
#include <rtdevice.h>

#define SPI_DEVICE_NAME     "spi00"
#define BUF_LEN             16

static void spi_io_sample(int argc, char *argv[])
{
    struct rt_spi_device * spi_dev;          /* spi设备的句柄 */
    struct rt_spi_configuration spi_config;
    rt_uint8_t i,buffer[BUF_LEN] = { 0U };
    rt_err_t s_stat;
    rt_err_t result;
    
     /* 查找 spi设备 获取spi设备句柄 */
    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_DEVICE_NAME);
    
    if (spi_dev == RT_NULL)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", SPI_DEVICE_NAME);
        return;
    }
    
    
    /* 清空配置结构体 */
    rt_memset(&spi_config,0,sizeof(struct rt_spi_configuration));
    
    spi_config.mode &= ~RT_SPI_SLAVE; /* 主机模式 */
    spi_config.mode &= ~RT_SPI_3WIRE; /* 4线，双向传输 */
    spi_config.mode |= RT_SPI_CPHA;   /* 第二边沿采样 */
    spi_config.mode |= RT_SPI_CPOL;   /* 空闲高电平 */
    spi_config.mode |= RT_SPI_NO_CS;  /* 禁用软件从机选择管理 */
    spi_config.mode |= RT_SPI_MSB;    /* 高位在前 */
    
    spi_config.data_width = 8;        /* 数据长度：8 */
    
    spi_config.max_hz = 2000000;      /* 最快时钟频率 */
    
    /* 配置SPI设备 */
    s_stat = rt_spi_configure(spi_dev,&spi_config);
    
    if(s_stat != RT_EOK)
    {
        rt_kprintf(" spi config fail !\n ");
        return;
    }
    
    
    /* 获取总线 ，防止总线被多个线程同时使用 */
    result = rt_spi_take_bus(spi_dev);
    
    if (result != RT_EOK)
    {
        rt_kprintf(" %s take spi bus  failed! \n", SPI_DEVICE_NAME);
        return;
    }
    
    /* 选中片选 */
    result = rt_spi_take(spi_dev);
    
    if (result != RT_EOK)
    {
        rt_kprintf(" %s take spi cs  failed! \n", SPI_DEVICE_NAME);
        return;
    }
    
    
    /*接收一次数据*/
    result = rt_spi_recv(spi_dev,buffer,BUF_LEN);
    
    if(result != BUF_LEN)
    {
        rt_kprintf("receive fail. \n buffer is : %s \n:",buffer);
            
        for( i = 0 ; i < BUF_LEN ; i++)
         rt_kprintf(" %x",(unsigned int)buffer[i]);
            
        rt_kprintf("\n");
        
        return;
    }
    
    rt_kprintf("receive successful. \n buffer is : %s \n:",buffer);
            
    for( i = 0 ; i < BUF_LEN ; i++)
    rt_kprintf(" %x",(unsigned int)buffer[i]);
            
    rt_kprintf("\n");
    
    /* 将接收到的数据加1 */
    for( i = 0 ; i < BUF_LEN ; i++)
      buffer[i]++;
    
    /*发送数据*/
    result = rt_spi_send(spi_dev,buffer,BUF_LEN);
    
    if(result != BUF_LEN)
    {
        rt_kprintf("send fail. \n buffer is : %s \n:",buffer);
            
        for( i = 0 ; i < BUF_LEN ; i++)
         rt_kprintf(" %x",(unsigned int)buffer[i]);
            
        rt_kprintf("\n");
        
        return;
    }
    
    rt_kprintf("send successful. \n buffer is : %s \n:",buffer);
            
    for( i = 0 ; i < BUF_LEN ; i++)
    rt_kprintf(" %x",(unsigned int)buffer[i]);
            
    rt_kprintf("\n");
   
    /* 释放片选 */
    result = rt_spi_release(spi_dev);
    
    if (result != RT_EOK)
    {
        rt_kprintf(" %s release spi cs failed! \n", SPI_DEVICE_NAME);
        return;
    } 
    
    /* 释放总线 */
    result = rt_spi_release_bus(spi_dev);
    
    if (result != RT_EOK)
    {
        rt_kprintf(" %s release spi bus  failed! \n", SPI_DEVICE_NAME);
        return;
    }
    
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(spi_io_sample, spi  sample);
