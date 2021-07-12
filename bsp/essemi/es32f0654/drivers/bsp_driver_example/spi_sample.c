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
 * 程序清单：这是一个 SPI 设备使用例程
 * 例程导出了 spi_io_sample 命令到控制终端
 * 命令调用格式：spi_io_sample
 * 程序功能：通过SPI设备先读取数据，然后每个字符加1后输出。
*/

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_SPI

#define SPI_DEVICE_NAME     "spi00"
#define BUF_LEN             16

static void spi_io_sample(int argc, char *argv[])
{
    struct rt_spi_device * spi_dev;          /* spi设备的句柄 */
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
    
    /* 配置SPI设备 */
    s_stat = rt_spi_configure(spi_dev,&(spi_dev->config));
    
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

#endif
