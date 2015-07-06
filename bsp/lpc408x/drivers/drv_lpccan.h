/*
 * File      : drv_lpccan.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-06-30     aubrcool@qq.com first version
 */

#ifndef DRV_LPCCAN_H_
#define DRV_LPCCAN_H_
#include <rthw.h>
#include <rtdevice.h>

#define LPC_CAN_AF_STD_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,0,0,0,0xFFFFFFFF)
#define LPC_CAN_AF_EXT_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,1,0,0,0xFFFFFFFF)
#define LPC_CAN_AF_STD_GRP_INIT(id1,id2) \
     RT_CAN_FILTER_ITEM_INIT(id1,0,0,1,id2)
#define LPC_CAN_AF_EXT_GRP_INIT(id1,id2) \
     RT_CAN_FILTER_ITEM_INIT(id1,1,0,1,id2)

#endif /*DRV_LPCCAN_H_*/
