/*
 * File      : dma.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */

#ifndef _DMA_H_
#define _DMA_H_
/*********************************************************************************************************
**   头文件
*********************************************************************************************************/
#include <stdlib.h>
#include <rtdef.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C"{
#endif
#define RT_DMA_CHANNEL(n)       (n)
#ifndef RT_DMA_MAX_NODES
#	define RT_DMA_MAX_NODES        8
#endif

/*********************************************************************************************************
**   DMA 状态定义
*********************************************************************************************************/
#define RT_DMA_STATUS_IDLE     0                                        /*  DMA 处于空闲模式            */
#define RT_DMA_STATUS_BUSY     1                                        /*  DMA 处于正在工作            */
#define RT_DMA_STATUS_ERROR    2                                        /*  DMA 处于错误状态            */

/*********************************************************************************************************
**   DMA 地址方向定义
*********************************************************************************************************/
#define RT_DMA_ADDR_INC        0                                        /*  地址增长方式                */
#define RT_DMA_ADDR_FIX        1                                        /*  地址不变                    */
#define RT_DMA_ADDR_DEC        2                                        /*  地址减少方式                */

/*********************************************************************************************************
**   DMA 传输方向定义
*********************************************************************************************************/
#define RT_DMA_MEM_TO_MEM       0
#define RT_DMA_MEM_TO_DEV       1
#define RT_DMA_DEV_TO_MEM       2
#define RT_DMA_DEV_TO_DEV       3
#define RT_DMA_TRANS_NONE       4

/*********************************************************************************************************
**   DMA 总线宽度
*********************************************************************************************************/
#define RT_DMA_BUSWIDTH_UNDEFINED   0
#define RT_DMA_BUSWIDTH_1_BYTE      1
#define RT_DMA_BUSWIDTH_2_BYTES     2
#define RT_DMA_BUSWIDTH_4_BYTES     4
#define RT_DMA_BUSWIDTH_8_BYTES     8

/*********************************************************************************************************
**   DMA 传输 时间
*********************************************************************************************************/
#define RT_DMA_EVENT_COMPLETE   0x01
#define RT_DMA_EVENT_ERROR      0x02


/*********************************************************************************************************
**   数据结构
*********************************************************************************************************/
struct rt_dma_channel;
struct dma_message;
struct dma_config;
struct dma_ops
{
    void        (*reset)(struct rt_dma_channel *dmac);
    rt_size_t   (*trans)(struct rt_dma_channel *dmac,struct dma_message *message);
    int         (*status)(struct rt_dma_channel *dmac);
    int         (*configure)(struct rt_dma_channel *dmac,struct dma_config *config);
};

struct dma_message
{
    rt_uint8_t  *src_addr;                          /*  源端缓冲区地址              */
    rt_uint8_t  *dst_addr;                          /*  目的端缓冲区地址            */
    rt_uint8_t  src_option;                         /*  源端地址方向控制            */
    rt_uint8_t  dst_option;                         /*  目的地址方向控制            */
    rt_size_t   t_size;                             /*  传输的字节数                */

    rt_uint32_t t_mode;                             /*  传输模式, 自定义            */

    void 	(*complete_cb)(void *data,void *pbuf);
    void	*complete_arg;
};


struct dma_config
{
    rt_uint32_t direction;
    rt_uint32_t src_addr_width;
    rt_uint32_t dst_addr_width;
    rt_uint32_t src_maxburst;
    rt_uint32_t dst_maxburst;
};

struct rt_dma_channel
{
    int ch;
    rt_list_t               list;               /* channel list     */

    struct dma_config       config;
    struct dma_ops         *ops;

    struct dma_message      msg_list[RT_DMA_MAX_NODES];
    rt_uint16_t get_index;
    rt_uint16_t put_index;

    void       (*start)(struct rt_dma_channel *dmac,struct dma_message *msg);        /* 启动传输 回调函数 */
    void       (*complete)(struct rt_dma_channel *dmac,struct dma_message *msg);     /* 传输完成 回调函数 */

    void       *user_data;          /* 自定义数据   */
};


/*********************************************************************************************************
**   函数申明
*********************************************************************************************************/
rt_err_t rt_dma_drv_install(struct rt_dma_channel *dmac, struct dma_ops *ops,struct dma_config *config,void* user_data);
struct rt_dma_channel   *rt_dma_get_channel(int id);
struct dma_message      *rt_dma_get_current_message (struct rt_dma_channel *dmac);
rt_err_t  rt_dma_reset (struct rt_dma_channel *dmac);
rt_err_t  rt_dma_trans_message (struct rt_dma_channel *dmac,struct dma_message* message);
rt_err_t  rt_dma_configture (struct rt_dma_channel *dmac,struct dma_config *config);
rt_err_t rt_dma_contex_service (struct rt_dma_channel *dmac,rt_uint32_t event);



#ifdef __cplusplus
}
#endif

#endif /* _DMA_H_ */
