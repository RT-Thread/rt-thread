/*
 * File      : drv_sdram.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
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
 * 2015-08-03     xiaonong     The first version for STM32F7
 */

#include "drv_sdram.h"

static SDRAM_HandleTypeDef sdramHandle;
static FMC_SDRAM_TimingTypeDef Timing;
static FMC_SDRAM_CommandTypeDef Command;

/**
  * @brief  Initializes SDRAM MSP.
  * @param  hsdram: SDRAM handle
  * @param  Params
  * @retval None
  */
static void SDRAM_MspInit(SDRAM_HandleTypeDef  *hsdram, void *Params)
{  
  static DMA_HandleTypeDef dma_handle;
  GPIO_InitTypeDef gpio_init_structure;
  
  /* Enable FMC clock */
  __HAL_RCC_FMC_CLK_ENABLE();
  
  /* Enable chosen DMAx clock */
  SDRAM_DMA_CLK_ENABLE();

  /* Enable GPIOs clock */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  
  /* Common GPIO configuration */
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FAST;
  gpio_init_structure.Alternate = GPIO_AF12_FMC;
  
  /* GPIOC configuration */
  gpio_init_structure.Pin   = GPIO_PIN_3;
  HAL_GPIO_Init(GPIOC, &gpio_init_structure);

  /* GPIOD configuration */
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_8 | GPIO_PIN_9 |
                              GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);

  /* GPIOE configuration */  
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7| GPIO_PIN_8 | GPIO_PIN_9 |\
                              GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                              GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &gpio_init_structure);
  
  /* GPIOF configuration */  
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4 |\
                              GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |\
                              GPIO_PIN_15;
  HAL_GPIO_Init(GPIOF, &gpio_init_structure);
  
  /* GPIOG configuration */  
  gpio_init_structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4| GPIO_PIN_5 | GPIO_PIN_8 |\
                              GPIO_PIN_15;
  HAL_GPIO_Init(GPIOG, &gpio_init_structure);

  /* GPIOH configuration */  
  gpio_init_structure.Pin   = GPIO_PIN_3 | GPIO_PIN_5;
  HAL_GPIO_Init(GPIOH, &gpio_init_structure); 
  
  /* Configure common DMA parameters */
  dma_handle.Init.Channel             = SDRAM_DMA_CHANNEL;
  dma_handle.Init.Direction           = DMA_MEMORY_TO_MEMORY;
  dma_handle.Init.PeriphInc           = DMA_PINC_ENABLE;
  dma_handle.Init.MemInc              = DMA_MINC_ENABLE;
  dma_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  dma_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  dma_handle.Init.Mode                = DMA_NORMAL;
  dma_handle.Init.Priority            = DMA_PRIORITY_HIGH;
  dma_handle.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
  dma_handle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  dma_handle.Init.MemBurst            = DMA_MBURST_SINGLE;
  dma_handle.Init.PeriphBurst         = DMA_PBURST_SINGLE; 
  
  dma_handle.Instance = SDRAM_DMA_STREAM;
  
   /* Associate the DMA handle */
  __HAL_LINKDMA(hsdram, hdma, dma_handle);
  
  /* Deinitialize the stream for new transfer */
  HAL_DMA_DeInit(&dma_handle);
  
  /* Configure the DMA stream */
  HAL_DMA_Init(&dma_handle); 
  
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(SDRAM_DMA_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(SDRAM_DMA_IRQn);
}

/**
  * @brief  DeInitializes SDRAM MSP.
  * @param  hsdram: SDRAM handle
  * @param  Params
  * @retval None
  */
static void SDRAM_MspDeInit(SDRAM_HandleTypeDef  *hsdram, void *Params)
{  
    static DMA_HandleTypeDef dma_handle;
  
    /* Disable NVIC configuration for DMA interrupt */
    HAL_NVIC_DisableIRQ(SDRAM_DMA_IRQn);

    /* Deinitialize the stream for new transfer */
    dma_handle.Instance = SDRAM_DMA_STREAM;
    HAL_DMA_DeInit(&dma_handle);

    /* GPIO pins clock, FMC clock and DMA clock can be shut down in the applications
       by surcharging this __weak function */ 
}

/**
  * @brief  Programs the SDRAM device.
  * @param  RefreshCount: SDRAM refresh counter value 
  * @retval None
  */
static void SDRAM_InitializationSequence(uint32_t RefreshCount)
{
  __IO uint32_t tmpmrd = 0;
  
  /* Step 1: Configure a clock configuration enable command */
  Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

  /* Step 2: Insert 100 us minimum delay */ 
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
  // HAL_Delay(1);
	/* interrupt is not enable, just to delay some time. */
	for (tmpmrd = 0; tmpmrd < 0xfffff; tmpmrd ++)
		;

  /* Step 3: Configure a PALL (precharge all) command */ 
  Command.CommandMode            = FMC_SDRAM_CMD_PALL;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);  
  
  /* Step 4: Configure an Auto Refresh command */ 
  Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 8;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);
  
  /* Step 5: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |\
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |\
                     SDRAM_MODEREG_CAS_LATENCY_2           |\
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |\
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
  
  Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);
  
  /* Step 6: Set the refresh rate counter */
  /* Set the device refresh rate */
  HAL_SDRAM_ProgramRefreshRate(&sdramHandle, RefreshCount); 
}

/**
  * @brief  Reads an amount of data from the SDRAM memory in polling mode.
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read  
  * @param  uwDataSize: Size of read data from the memory
  * @retval SDRAM status
  */
rt_err_t SDRAM_ReadData(uint32_t Address, uint32_t *Data, uint32_t DataSize)
{
  if(HAL_SDRAM_Read_32b(&sdramHandle, (uint32_t *)Address, Data, DataSize) != HAL_OK)
  {
    return RT_ERROR;
  }
  else
  {
    return RT_EOK;
  } 
}

/**
  * @brief  Reads an amount of data from the SDRAM memory in DMA mode.
  * @param  uwStartAddress: Read start address
  * @param  pData: Pointer to data to be read  
  * @param  uwDataSize: Size of read data from the memory
  * @retval SDRAM status
  */
rt_err_t SDRAM_ReadDataDMA(uint32_t Address, uint32_t *Data, uint32_t DataSize)
{
  if(HAL_SDRAM_Read_DMA(&sdramHandle, (uint32_t *)Address, Data, DataSize) != HAL_OK)
  {
    return RT_ERROR;
  }
  else
  {
    return RT_EOK;
  }     
}

/**
  * @brief  Writes an amount of data to the SDRAM memory in polling mode.
  * @param  uwStartAddress: Write start address
  * @param  pData: Pointer to data to be written  
  * @param  uwDataSize: Size of written data from the memory
  * @retval SDRAM status
  */
rt_err_t SDRAM_WriteData(uint32_t Address, uint32_t *Data, uint32_t DataSize) 
{
  if(HAL_SDRAM_Write_32b(&sdramHandle, (uint32_t *)Address, Data, DataSize) != HAL_OK)
  {
    return RT_ERROR;
  }
  else
  {
    return RT_EOK;
  }
}

/**
  * @brief  Writes an amount of data to the SDRAM memory in DMA mode.
  * @param  Address: Write start address
  * @param  Data: Pointer to data to be written  
  * @param  DataSize: Size of written data from the memory
  * @retval SDRAM status
  */
rt_err_t SDRAM_WriteDataDMA(uint32_t Address, uint32_t *Data, uint32_t DataSize) 
{
  if(HAL_SDRAM_Write_DMA(&sdramHandle, (uint32_t *)Address, Data, DataSize) != HAL_OK)
  {
    return RT_ERROR;
  }
  else
  {
    return RT_EOK;
  } 
}


/**
  * @brief  Initializes the SDRAM device.
  * @retval SDRAM status
  */
rt_err_t sdram_hw_init(void)
{ 
  static uint8_t sdramstatus = RT_ERROR;
  /* SDRAM device configuration */
  sdramHandle.Instance = FMC_SDRAM_DEVICE;
    
  /* Timing configuration for 100Mhz as SD clock frequency (System clock is up to 200Mhz) */
  Timing.LoadToActiveDelay    = 2;
  Timing.ExitSelfRefreshDelay = 7;
  Timing.SelfRefreshTime      = 4;
  Timing.RowCycleDelay        = 7;
  Timing.WriteRecoveryTime    = 2;
  Timing.RPDelay              = 2;
  Timing.RCDDelay             = 2;
  
  sdramHandle.Init.SDBank             = FMC_SDRAM_BANK1;
  sdramHandle.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_8;
  sdramHandle.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;
  sdramHandle.Init.MemoryDataWidth    = SDRAM_MEMORY_WIDTH;
  sdramHandle.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  sdramHandle.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_2;
  sdramHandle.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  sdramHandle.Init.SDClockPeriod      = SDCLOCK_PERIOD;
  sdramHandle.Init.ReadBurst          = FMC_SDRAM_RBURST_ENABLE;
  sdramHandle.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_0;
  
  /* SDRAM controller initialization */

  SDRAM_MspInit(&sdramHandle, NULL); /* __weak function can be rewritten by the application */

  if(HAL_SDRAM_Init(&sdramHandle, &Timing) != HAL_OK)
  {
    sdramstatus = RT_ERROR;
  }
  else
  {
    sdramstatus = RT_EOK;
  }
  
  /* SDRAM initialization sequence */
  SDRAM_InitializationSequence(REFRESH_COUNT);
  
  return sdramstatus;
}

/**
  * @brief  DeInitializes the SDRAM device.
  * @retval SDRAM status
  */
rt_err_t sdram_hw_deinit(void)
{ 
  static uint8_t sdramstatus = RT_ERROR;
  /* SDRAM device de-initialization */
  sdramHandle.Instance = FMC_SDRAM_DEVICE;

  if(HAL_SDRAM_DeInit(&sdramHandle) != HAL_OK)
  {
    sdramstatus = RT_ERROR;
  }
  else
  {
    sdramstatus = RT_EOK;
  }
  
  /* SDRAM controller de-initialization */
  SDRAM_MspDeInit(&sdramHandle, NULL);
  
  return sdramstatus;
}

/**
  * @brief  Handles SDRAM DMA transfer interrupt request.
  * @retval None
  */
void SDRAM_DMA_IRQHandler(void)
{
  HAL_DMA_IRQHandler(sdramHandle.hdma); 
}

static int rt_sdram_hw_init(void)
{
    return (int)sdram_hw_init();
}
INIT_BOARD_EXPORT(rt_sdram_hw_init);
