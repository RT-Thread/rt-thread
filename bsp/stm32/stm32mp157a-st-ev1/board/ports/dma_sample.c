/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-10     thread-liu   first version
 */

#include <board.h>

#if defined(BSP_USING_DMA)

#define BUFFER_SIZE 32        /* DMA max buffer size */

static DMA_HandleTypeDef hdma_memtomem_dma1_stream5 = {0}; /* Using dma1 stream5 to test */

static const rt_uint32_t DMA_Src_Buffer[BUFFER_SIZE] =
{
    0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
    0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
    0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
    0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
    0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
    0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
    0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
    0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80
};
static rt_uint32_t DMA_Dst_Buffer[BUFFER_SIZE];

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;

    for (i = 0; i < buflen; i += 16)
    {
        rt_kprintf("%08X: ", i);

        for (j = 0; j < 16; j++)
        {
            if (i + j < buflen)
            {
                rt_kprintf("%02X ", buf[i + j]);
            }
            else
            {
                rt_kprintf("   ");
            }
        }
        rt_kprintf(" ");

        for (j = 0; j < 16; j++)
        {
            if (i + j < buflen)
            {
                rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        rt_kprintf("\n");
    }
}

void DMA1_Stream5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&hdma_memtomem_dma1_stream5);
    
    /* leave interrupt */
    rt_interrupt_leave();
}

static void MX_DMA_Init(void)
{
    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_DMAMUX_CLK_ENABLE();

    /* Configure DMA request hdma_memtomem_dma1_stream5 on DMA1_Stream5 */
    hdma_memtomem_dma1_stream5.Instance = DMA1_Stream5;
    hdma_memtomem_dma1_stream5.Init.Request = DMA_REQUEST_MEM2MEM;
    hdma_memtomem_dma1_stream5.Init.Direction = DMA_MEMORY_TO_MEMORY;
    hdma_memtomem_dma1_stream5.Init.PeriphInc = DMA_PINC_ENABLE;
    hdma_memtomem_dma1_stream5.Init.MemInc = DMA_MINC_ENABLE;
    hdma_memtomem_dma1_stream5.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_memtomem_dma1_stream5.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_memtomem_dma1_stream5.Init.Mode = DMA_NORMAL;
    hdma_memtomem_dma1_stream5.Init.Priority = DMA_PRIORITY_LOW;
    hdma_memtomem_dma1_stream5.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_memtomem_dma1_stream5.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_memtomem_dma1_stream5.Init.MemBurst = DMA_MBURST_INC4;
    hdma_memtomem_dma1_stream5.Init.PeriphBurst = DMA_PBURST_INC4;
    if (HAL_DMA_Init(&hdma_memtomem_dma1_stream5) != HAL_OK)
    {
        Error_Handler();
    }

    /* DMA interrupt init */
    /* DMA1_Stream5_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
}

static void TransferComplete(DMA_HandleTypeDef *DmaHandle)
{
    rt_kprintf("dma dst buffer :\n");
    dump_hex((rt_uint8_t *)DMA_Dst_Buffer, sizeof(DMA_Dst_Buffer));

    rt_kprintf("============ dma transfer success ============\n");
    
    rt_memset(DMA_Dst_Buffer, 0x00, sizeof(DMA_Dst_Buffer));
}

static void TransferError(DMA_HandleTypeDef *DmaHandle)
{
    rt_kprintf("============ dma transfer error ============\n");
}

static int rt_hw_dma_init(void)
{
    rt_err_t result = RT_EOK;
    
    MX_DMA_Init();
    /* Select Callbacks functions called after Transfer complete and Transfer error */
    HAL_DMA_RegisterCallback(&hdma_memtomem_dma1_stream5, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);
    HAL_DMA_RegisterCallback(&hdma_memtomem_dma1_stream5, HAL_DMA_XFER_ERROR_CB_ID, TransferError);

    return result;
}
INIT_APP_EXPORT(rt_hw_dma_init);

static int dma_transfer_test()
{
    rt_kprintf("============ dma travsfer start ============\n");
    
    rt_kprintf("dma src buffer :\n");
    dump_hex((rt_uint8_t *)DMA_Src_Buffer, sizeof(DMA_Src_Buffer));

    if (HAL_DMA_Start_IT(&hdma_memtomem_dma1_stream5, (rt_uint32_t)&DMA_Src_Buffer, (rt_uint32_t)&DMA_Dst_Buffer, BUFFER_SIZE) != HAL_OK)
    {
        /* Transfer Error */
        return -RT_ERROR;
    }

    return RT_EOK;
}

int dma_sample(int argc, char **argv)
{
    if (argc > 1)
    {
        if (!rt_strcmp(argv[1], "start"))
        {
           rt_kprintf("dma test start\n");
           dma_transfer_test();
           return RT_EOK;
        }
        else
        {
            goto _exit;
        }
    }
_exit:
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("dma_sample start         - start dma \n");
    }
    
    return RT_EOK;
}
MSH_CMD_EXPORT(dma_sample, dma test);

#endif /* USE_DMA_SAMPLE */
