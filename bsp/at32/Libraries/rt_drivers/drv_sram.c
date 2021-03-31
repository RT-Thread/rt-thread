/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-04      Leo      first version
 */

#include <board.h>
#include <rtthread.h>
#include "drv_sram.h"

#ifdef BSP_USING_SRAM

#define DRV_DEBUG
#define LOG_TAG             "drv.sram"
#include <drv_log.h>

uint16_t RT_TxBuffer[RT_BUFFER_SIZE];
uint16_t RT_RxBuffer[RT_BUFFER_SIZE];
uint32_t WriteReadStatus = 0, Index = 0;


#ifdef RT_USING_MEMHEAP_AS_HEAP
static struct rt_memheap system_heap;
#endif



static int rt_hw_sram_Init(void)
{
    int result = RT_EOK;
    XMC_Bank1_Type *XMC;
    XMC_NORSRAMInitType  XMC_NORSRAMInitStructure;
    XMC_NORSRAMTimingInitType  p;

    /* Init XMC pin */
    at32_msp_xmc_init(XMC);

    /*-- FSMC Configuration ------------------------------------------------------*/
    p.XMC_AdrOpTime         = 0x04;
    p.XMC_AdrHoldTime       = 0x04;
    p.XMC_DataOpTime        = 0x0a;
    p.XMC_IntervalBetweenOP = 0x0;
    p.XMC_CLKPsc            = 0x0;
    p.XMC_DataStableTime    = 0x0;
    p.XMC_Mode              = XMC_Mode_A;

    XMC_NORSRAMInitStructure.XMC_Bank                   = XMC_Bank1_NORSRAM3;
    XMC_NORSRAMInitStructure.XMC_DataAdrMux             = XMC_DataAdrMux_Disable;
    XMC_NORSRAMInitStructure.XMC_Dev                    = XMC_Dev_SRAM;
    XMC_NORSRAMInitStructure.XMC_BusType                = XMC_BusType_16b;
    XMC_NORSRAMInitStructure.XMC_EnableBurstMode        = XMC_BurstMode_Disable;
    XMC_NORSRAMInitStructure.XMC_EnableAsynWait         = XMC_AsynWait_Disable;
    XMC_NORSRAMInitStructure.XMC_WaitSignalLv           = XMC_WaitSignalLv_Low;
    XMC_NORSRAMInitStructure.XMC_EnableBurstModeSplit   = XMC_BurstModeSplit_Disable;
    XMC_NORSRAMInitStructure.XMC_WaitSignalConfig       = XMC_WaitSignalConfig_BeforeWaitState;
    XMC_NORSRAMInitStructure.XMC_EnableWrite            = XMC_WriteOperation_Enable;
    XMC_NORSRAMInitStructure.XMC_EnableWaitSignal       = XMC_WaitSignal_Disable;
    XMC_NORSRAMInitStructure.XMC_EnableWriteTiming      = XMC_WriteTiming_Disable;
    XMC_NORSRAMInitStructure.XMC_WriteBurstSyn          = XMC_WriteBurstSyn_Disable;
    XMC_NORSRAMInitStructure.XMC_RWTimingStruct         = &p;
    XMC_NORSRAMInitStructure.XMC_WTimingStruct          = &p;

    XMC_NORSRAMInit(&XMC_NORSRAMInitStructure);

    /*!< Enable FSMC Bank1_SRAM Bank */
    XMC_NORSRAMCmd(XMC_Bank1_NORSRAM3, ENABLE);

#ifdef RT_USING_MEMHEAP_AS_HEAP
        /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SRAM is initialized to the heap */
        rt_memheap_init(&system_heap, "sram", (void *)EXT_SRAM_BEGIN, SRAM_LENGTH);
#endif

    return result;
}
INIT_BOARD_EXPORT(rt_hw_sram_Init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
/**
  * @brief  Writes a Half-word buffer to the FSMC SRAM memory.
  * @param  pBuffer : pointer to buffer.
  * @param  WriteAddr : SRAM memory internal address from which the data will be
  *         written.
  * @param  NumHalfwordToWrite : number of half-words to write.
  * @retval None
  */
static void SRAM_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{
  for(; NumHalfwordToWrite != 0; NumHalfwordToWrite--) /*!< while there is data to write */
  {
    /*!< Transfer data to the memory */
    *(uint16_t *) (EXT_SRAM_BEGIN + WriteAddr) = *pBuffer++;

    /*!< Increment the address*/
    WriteAddr += 2;
  }
}

/**
  * @brief  Reads a block of data from the FSMC SRAM memory.
  * @param  pBuffer : pointer to the buffer that receives the data read from the
  *         SRAM memory.
  * @param  ReadAddr : SRAM memory internal address to read from.
  * @param  NumHalfwordToRead : number of half-words to read.
  * @retval None
  */
static void SRAM_ReadBuffer(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead)
{
  for(; NumHalfwordToRead != 0; NumHalfwordToRead--) /*!< while there is data to read */
  {
    /*!< Read a half-word from the memory */
    *pBuffer++ = *(__IO uint16_t*) (EXT_SRAM_BEGIN + ReadAddr);

    /*!< Increment the address*/
    ReadAddr += 2;
  }
}

/**
  * @brief  Fill the global buffer
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferSize: size of the buffer to fill
  * @param  Offset: first value to fill on the Buffer
  */
static void Fill_Buffer(uint16_t *pBuffer, uint16_t BufferLenght, uint32_t Offset)
{
    uint16_t IndexTmp = 0;

    /* Put in global buffer same values */
    for (IndexTmp = 0; IndexTmp < BufferLenght; IndexTmp++ )
    {
        pBuffer[IndexTmp] = IndexTmp + Offset;
    }
}

int sram_test(void)
{
    /* Write data to XMC SRAM memory */
    /* Fill the buffer to send */
    Fill_Buffer(RT_TxBuffer, RT_BUFFER_SIZE, 0x3212);
    SRAM_WriteBuffer(RT_TxBuffer, RT_WRITE_READ_ADDR, RT_BUFFER_SIZE);


    /* Read data from XMC SRAM memory */
    SRAM_ReadBuffer(RT_RxBuffer, RT_WRITE_READ_ADDR, RT_BUFFER_SIZE);

    /* Read back SRAM memory and check content correctness */
    for (Index = 0x00; (Index < RT_BUFFER_SIZE) && (WriteReadStatus == 0); Index++)
    {
        if (RT_RxBuffer[Index] != RT_TxBuffer[Index])
        {
            WriteReadStatus = Index + 1;
        }
    }

    if(WriteReadStatus == 0)
    {
        LOG_D("SRAM test success!");
    }
    else
    {
        LOG_E("SRAM test failed!");
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(sram_test, sram test)
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_SRAM */
