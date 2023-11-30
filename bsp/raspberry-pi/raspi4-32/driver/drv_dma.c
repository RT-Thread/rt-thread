/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-12-02     bigmagic       first version
 */
#include "drv_dma.h"
#include "raspi4.h"
#include <rtthread.h>

volatile unsigned int __attribute__((aligned(256))) dma_disc[32];
//https://www.raspberrypi.org/forums/viewtopic.php?f=72&t=10276
static struct rt_semaphore dma_sem;

//DMA 0 1 2 3 4 5 6
typedef struct _dma_ctrl_block
{
    unsigned int TI;                   // Transfer information
    unsigned int SOURCE_AD;            // source address
    unsigned int DEST_AD;              // destination address
    unsigned int TXFR_LEN;             // transfer length
    unsigned int STRIDE;               // 2D mode stride
    struct _dma_ctrl_block *NEXTCONBK; // Next control block address
    unsigned int DEBUG;
    unsigned int reserved1;

} dma_ctrl_block_t;

//DMA 7 8 9 10
typedef struct _dma_lite_ctrl_block
{
    unsigned int TI;                        // Transfer information
    unsigned int SOURCE_AD;                 // source address
    unsigned int DEST_AD;                   // destination address
    unsigned int TXFR_LEN;                  // transfer length
    struct _dma_lite_ctrl_block *NEXTCONBK; // Next control block address
    unsigned int DEBUG;
    unsigned int reserved1;
    unsigned int reserved2;

} dma_lite_ctrl_block_t;

//DMA 11 12 13 14 15
typedef struct _dma4_ctrl_block
{
    unsigned int TI;                    // Transfer information
    unsigned int SOURCE_AD0;            // source address0
    unsigned int SOURCE_AD1;            // source address1
    unsigned int DEST_AD0;              // destination address0
    unsigned int DEST_AD1;              // destination address1
    unsigned int TXFR_LEN;              // transfer length
    unsigned int STRIDE;                // 2D mode stride
    struct _dma4_ctrl_block *NEXTCONBK; // Next control block address
} dma4_ctrl_block_t;

static dma_lite_ctrl_block_t *ctr_blocks;

static void dma_irq(int irq, void *param)
{
    if (DMA_INT_STATUS_REG & DMA_INT7)
    {
        DMA_CS(7) = DMA_CS_INT;
        rt_sem_release(&dma_sem);
    }
}

//dma 7 8 9 10:XLENGTH
rt_err_t dma_memcpy(void *src, void *dst, unsigned int size, unsigned int dch, unsigned int timeout)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, dst, size);

    /* Stop DMA, if it was already started */
    DMA_CS(dch) = DMA_CS_RESET;

    /* Clear DMA status flags */
    DMA_CS(dch) = DMA_CS_INT | DMA_CS_END; /* Interrupted flag & Transmission ended flag*/
    //cb info
    ctr_blocks->TI = DMA_TI_SRC_INC | DMA_TI_DEST_INC | DMA_TI_INTEN;
    ctr_blocks->SOURCE_AD = (unsigned int)src;
    ctr_blocks->DEST_AD = (unsigned int)dst;
    ctr_blocks->TXFR_LEN = size;
    ctr_blocks->NEXTCONBK = 0;
    ctr_blocks->reserved1 = 0;
    ctr_blocks->reserved2 = 0;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, ctr_blocks, sizeof(dma_lite_ctrl_block_t) * 8);

    DMA_CONBLK_AD(dch) = (rt_uint32_t)ctr_blocks;
    DMA_CS(dch) = DMA_CS_INT | DMA_CS_END | DMA_CS_ACTIVE;

    if(rt_sem_take(&dma_sem, timeout) != RT_EOK)
    {
        rt_kprintf("dma transfer timeout!\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

void dma_init(unsigned char dch)
{
    rt_sem_init(&dma_sem, "dma_sem", 0, RT_IPC_FLAG_FIFO);

    ctr_blocks = (dma_lite_ctrl_block_t *)&dma_disc[0]; //rt_malloc(sizeof(DMA_Lite_Control_Block));
    //Make sure DMA channel is enabled by
    //writing the corresponding bit in DMA_ENABLE in the DMA register to 1
    DMA_ENABLE_REG = (1 << dch);

    rt_hw_interrupt_install(IRQ_DMA7_DMA8, dma_irq, RT_NULL, "dma_irq");
    rt_hw_interrupt_umask(IRQ_DMA7_DMA8);
}
