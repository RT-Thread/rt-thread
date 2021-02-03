/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		eru_dma
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 
#ifndef _zf_eru_dma_h
#define _zf_eru_dma_h

#include "common.h"
#include "zf_eru.h"
#include "IfxDma.h"



#define CLEAR_DMA_FLAG(dma_ch)	IfxDma_clearChannelInterrupt(&MODULE_DMA, dma_ch);


#define DMA_SET_DESTINATION(dma_ch, destination_addr)	IfxDma_setChannelDestinationAddress(&MODULE_DMA, dma_ch, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), destination_addr))

uint8 eru_dma_init(IfxDma_ChannelId dma_ch, uint8 *source_addr, uint8 *destination_addr, ERU_PIN_enum eru_pin, TRIGGER_enum trigger, uint16 dma_count);
void dma_stop(IfxDma_ChannelId dma_ch);
void dma_start(IfxDma_ChannelId dma_ch);

#endif
