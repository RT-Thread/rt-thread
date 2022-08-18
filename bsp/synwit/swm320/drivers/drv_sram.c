/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 * 2020-07-10     lik          rewrite
 */

#include "drv_sram.h"

#ifdef BSP_USING_EXT_SRAM

#define DRV_DEBUG
#define LOG_TAG "drv.ext_sram"
#include <drv_log.h>

#ifdef RT_USING_MEMHEAP_AS_HEAP
static struct rt_memheap system_heap;
#endif

static int rt_hw_sram_init(void)
{
    SRAM_InitStructure SRAM_InitStruct;

    PORT->PORTP_SEL0 = 0xAAAAAAAA; //PP0-23 => ADDR0-23
    PORT->PORTP_SEL1 = 0xAAAA;

    PORT->PORTM_SEL0 = 0xAAAAAAAA; //PM0-15 => DATA15-0
    PORT->PORTM_INEN = 0xFFFF;

    PORT->PORTM_SEL1 = 0xAAA; //PM16 => OEN,PM17 => WEN,PM18 => NORFL_CSN,PM19 => SDRAM_CSN,PM20 => SRAM_CSN,PM21 => SDRAM_CKE

    SRAM_InitStruct.ClkDiv = SRAM_CLKDIV_8;
    SRAM_InitStruct.DataWidth = SRAM_DATAWIDTH_16;
    SRAM_Init(&SRAM_InitStruct);

#ifdef RT_USING_MEMHEAP_AS_HEAP
    /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SRAM is initialized to the heap */
    rt_memheap_init(&system_heap, "sram", (void *)EXT_SRAM_BEGIN, EXT_SRAM_SIZE);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_sram_init);

#endif /* BSP_USING_EXT_SRAM */
