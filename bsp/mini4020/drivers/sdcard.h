/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __SDCARD_H
#define __SDCARD_H

#include <rtthread.h>

#ifdef RT_USING_DFS

#include  <sep4020.h>

#define INICLK  300000
#define SDCLK   24000000    //PCLK=49.392MHz
#define MMCCLK  15000000    //PCLK=49.392MHz

/*struct of the SDC*/
struct  sd_c
{
    __IO rt_uint32_t    clk_ctl;
    __IO rt_uint32_t    soft_rst;
    __IO rt_uint32_t    arg;
    __IO rt_uint32_t    cmd;
    __IO rt_uint32_t    blk_sz;
    __IO rt_uint32_t    blk_cnt;
    __IO rt_uint32_t    trans_mode;
    __O  rt_uint32_t    response0;
    __O  rt_uint32_t    response1;
    __O  rt_uint32_t    response2;
    __O  rt_uint32_t    response3;
    __IO rt_uint32_t    rd_to_ctl;
    __IO rt_uint32_t    int_stat;
    __IO rt_uint32_t    int_stat_mask;
    __O  rt_uint32_t    rx_fifo;
    __I  rt_uint32_t    tx_fifo;
};

/*sdcard driver structure*/
struct  sd_device
{
    struct rt_device        *device;    /*rt_device*/
    struct sd_c         *sdc;       /*SDCARD register*/
    struct dfs_partition    *part;      /*dfs partitions*/
    rt_uint8_t      *sec_buf;   /*sdcard buffer*/
    rt_uint32_t     part_num;   /*partiont numbers*/
    rt_uint32_t     buf_size;   /*buffer size*/
};

#endif
#endif

