/**
 **************************************************************************
 * File Name    : at32f4xx_dma.c
 * Description  : at32f4xx DMA source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_dma.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DMA
  * @brief DMA driver modules
  * @{
  */

/** @defgroup DMA_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @defgroup DMA_Private_Defines
  * @{
  */


/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_CHANNEL1_INT_MASK      ((uint32_t)(DMA_ISTS_GIF1 | DMA_ISTS_TCIF1 | DMA_ISTS_HTIF1 | DMA_ISTS_ERRIF1))
#define DMA1_CHANNEL2_INT_MASK      ((uint32_t)(DMA_ISTS_GIF2 | DMA_ISTS_TCIF2 | DMA_ISTS_HTIF2 | DMA_ISTS_ERRIF2))
#define DMA1_CHANNEL3_INT_MASK      ((uint32_t)(DMA_ISTS_GIF3 | DMA_ISTS_TCIF3 | DMA_ISTS_HTIF3 | DMA_ISTS_ERRIF3))
#define DMA1_CHANNEL4_INT_MASK      ((uint32_t)(DMA_ISTS_GIF4 | DMA_ISTS_TCIF4 | DMA_ISTS_HTIF4 | DMA_ISTS_ERRIF4))
#define DMA1_CHANNEL5_INT_MASK      ((uint32_t)(DMA_ISTS_GIF5 | DMA_ISTS_TCIF5 | DMA_ISTS_HTIF5 | DMA_ISTS_ERRIF5))
#define DMA1_CHANNEL6_INT_MASK      ((uint32_t)(DMA_ISTS_GIF6 | DMA_ISTS_TCIF6 | DMA_ISTS_HTIF6 | DMA_ISTS_ERRIF6))
#define DMA1_CHANNEL7_INT_MASK      ((uint32_t)(DMA_ISTS_GIF7 | DMA_ISTS_TCIF7 | DMA_ISTS_HTIF7 | DMA_ISTS_ERRIF7))

/* DMA2 Channelx interrupt pending bit masks */
#define DMA2_CHANNEL1_INT_MASK      ((uint32_t)(DMA_ISTS_GIF1 | DMA_ISTS_TCIF1 | DMA_ISTS_HTIF1 | DMA_ISTS_ERRIF1))
#define DMA2_CHANNEL2_INT_MASK      ((uint32_t)(DMA_ISTS_GIF2 | DMA_ISTS_TCIF2 | DMA_ISTS_HTIF2 | DMA_ISTS_ERRIF2))
#define DMA2_CHANNEL3_INT_MASK      ((uint32_t)(DMA_ISTS_GIF3 | DMA_ISTS_TCIF3 | DMA_ISTS_HTIF3 | DMA_ISTS_ERRIF3))
#define DMA2_CHANNEL4_INT_MASK      ((uint32_t)(DMA_ISTS_GIF4 | DMA_ISTS_TCIF4 | DMA_ISTS_HTIF4 | DMA_ISTS_ERRIF4))
#define DMA2_CHANNEL5_INT_MASK      ((uint32_t)(DMA_ISTS_GIF5 | DMA_ISTS_TCIF5 | DMA_ISTS_HTIF5 | DMA_ISTS_ERRIF5))

/* DMA2 FLAG mask */
#define FLAG_Mask                   ((uint32_t)0x10000000)

/* DMA registers Masks */
#define CHCTRL_CLEAR_MASK           ((uint32_t)0xFFFF800F)

/**
  * @}
  */

/** @defgroup DMA_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup DMA_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup DMA_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup DMA_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the DMAy Channelx registers to their default reset
  *         values.
  * @param  DMAy_Channelx: where y can be 1 or 2 to select the DMA and
  *   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the DMA Channel.
  * @retval None
  */
void DMA_Reset(DMA_Channel_Type* DMAy_Channelx)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));

  /* Disable the selected DMAy Channelx */
  DMAy_Channelx->CHCTRL &= (uint16_t)(~DMA_CHCTRL1_CHEN);

  /* Reset DMAy Channelx control register */
  DMAy_Channelx->CHCTRL  = 0;

  /* Reset DMAy Channelx remaining bytes register */
  DMAy_Channelx->TCNT = 0;

  /* Reset DMAy Channelx peripheral address register */
  DMAy_Channelx->CPBA  = 0;

  /* Reset DMAy Channelx memory address register */
  DMAy_Channelx->CMBA = 0;

  if (DMAy_Channelx == DMA1_Channel1)
  {
    /* Reset interrupt pending bits for DMA1 Channel1 */
    DMA1->ICLR |= DMA1_CHANNEL1_INT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel2)
  {
    /* Reset interrupt pending bits for DMA1 Channel2 */
    DMA1->ICLR |= DMA1_CHANNEL2_INT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel3)
  {
    /* Reset interrupt pending bits for DMA1 Channel3 */
    DMA1->ICLR |= DMA1_CHANNEL3_INT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel4)
  {
    /* Reset interrupt pending bits for DMA1 Channel4 */
    DMA1->ICLR |= DMA1_CHANNEL4_INT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel5)
  {
    /* Reset interrupt pending bits for DMA1 Channel5 */
    DMA1->ICLR |= DMA1_CHANNEL5_INT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel6)
  {
    /* Reset interrupt pending bits for DMA1 Channel6 */
    DMA1->ICLR |= DMA1_CHANNEL6_INT_MASK;
  }
  else if (DMAy_Channelx == DMA1_Channel7)
  {
    /* Reset interrupt pending bits for DMA1 Channel7 */
    DMA1->ICLR |= DMA1_CHANNEL7_INT_MASK;
  }
  else if (DMAy_Channelx == DMA2_Channel1)
  {
    /* Reset interrupt pending bits for DMA2 Channel1 */
    DMA2->ICLR |= DMA2_CHANNEL1_INT_MASK;
  }
  else if (DMAy_Channelx == DMA2_Channel2)
  {
    /* Reset interrupt pending bits for DMA2 Channel2 */
    DMA2->ICLR |= DMA2_CHANNEL2_INT_MASK;
  }
  else if (DMAy_Channelx == DMA2_Channel3)
  {
    /* Reset interrupt pending bits for DMA2 Channel3 */
    DMA2->ICLR |= DMA2_CHANNEL3_INT_MASK;
  }
  else if (DMAy_Channelx == DMA2_Channel4)
  {
    /* Reset interrupt pending bits for DMA2 Channel4 */
    DMA2->ICLR |= DMA2_CHANNEL4_INT_MASK;
  }
  else if (DMAy_Channelx == DMA2_Channel5)
  {
    /* Reset interrupt pending bits for DMA2 Channel5 */
    DMA2->ICLR |= DMA2_CHANNEL5_INT_MASK;
  }
}

/**
  * @brief  Initializes the DMAy Channelx according to the specified
  *         parameters in the DMA_InitStruct.
  * @param  DMAy_Channelx: where y can be 1 or 2 to select the DMA and
  *   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the DMA Channel.
  * @param  DMA_InitStruct: pointer to a DMA_InitType structure that
  *         contains the configuration information for the specified DMA Channel.
  * @retval None
  */
void DMA_Init(DMA_Channel_Type* DMAy_Channelx, DMA_InitType* DMA_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_DIR(DMA_InitStruct->DMA_Direction));
  assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
  assert_param(IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc));
  assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));
  assert_param(IS_DMA_PERIPHERAL_DATA_WIDTH(DMA_InitStruct->DMA_PeripheralDataWidth));
  assert_param(IS_DMA_MEMORY_DATA_WIDTH(DMA_InitStruct->DMA_MemoryDataWidth));
  assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
  assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
  assert_param(IS_DMA_MTOM_STATE(DMA_InitStruct->DMA_MTOM));

  /*--------------------------- DMAy Channelx CCR Configuration -----------------*/
  /* Get the DMAy_Channelx CCR value */
  tmpreg = DMAy_Channelx->CHCTRL;
  /* Clear MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
  tmpreg &= CHCTRL_CLEAR_MASK;
  /* Configure DMAy Channelx: data transfer, data size, priority level and mode */
  /* Set DIR bit according to DMA_DIR value */
  /* Set CIRC bit according to DMA_Mode value */
  /* Set PINC bit according to DMA_PeripheralInc value */
  /* Set MINC bit according to DMA_MemoryInc value */
  /* Set PSIZE bits according to DMA_PeripheralDataSize value */
  /* Set MSIZE bits according to DMA_MemoryDataSize value */
  /* Set PL bits according to DMA_Priority value */
  /* Set the MEM2MEM bit according to DMA_M2M value */
  tmpreg |= DMA_InitStruct->DMA_Direction | DMA_InitStruct->DMA_Mode |
            DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
            DMA_InitStruct->DMA_PeripheralDataWidth | DMA_InitStruct->DMA_MemoryDataWidth |
            DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_MTOM;

  /* Write to DMAy Channelx CCR */
  DMAy_Channelx->CHCTRL = tmpreg;

  /*--------------------------- DMAy Channelx CNDTR Configuration ---------------*/
  /* Write to DMAy Channelx CNDTR */
  DMAy_Channelx->TCNT = DMA_InitStruct->DMA_BufferSize;

  /*--------------------------- DMAy Channelx CPAR Configuration ----------------*/
  /* Write to DMAy Channelx CPAR */
  DMAy_Channelx->CPBA = DMA_InitStruct->DMA_PeripheralBaseAddr;

  /*--------------------------- DMAy Channelx CMAR Configuration ----------------*/
  /* Write to DMAy Channelx CMAR */
  DMAy_Channelx->CMBA = DMA_InitStruct->DMA_MemoryBaseAddr;
}

/**
  * @brief  Initializes the DMAy flexible function according to the specified
  *         parameters.
  * @param  Flex_Channelx: where x can be 1 to 7 for DMA1 or DMA2.
  * @param  Hardware_ID: Every peripheral have specified Hardware_ID.
  * @retval None
  */
void DMA_Flexible_Config(DMA_Type* DMAx,uint8_t Flex_Channelx,uint8_t Hardware_ID)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_CHANNELS(Flex_Channelx));	
  assert_param(IS_DMA_ALL_HARDWARE_ID(Hardware_ID));		
	/* Initialize the DMA flexible function */
	DMAx->DMA_SRC_SEL1 &= (uint32_t)(~DMA_FLEX_FUNCTION_EN);
	DMAx->DMA_SRC_SEL1 |= (uint32_t)(DMA_FLEX_FUNCTION_EN);
	/* Set the Hardware_ID for DMA_Channel */
	if(Flex_Channelx == Flex_Channel1)/* channel1 */
	{ 
		DMAx->DMA_SRC_SEL0 &= (uint32_t)(~0xFF);
		DMAx->DMA_SRC_SEL0 |= (uint32_t)(Hardware_ID);
	}
	else if(Flex_Channelx == Flex_Channel2)/* channel2 */
	{
		DMAx->DMA_SRC_SEL0 &= (uint32_t)(~(0xFF<<8));
		DMAx->DMA_SRC_SEL0 |= (uint32_t)((Hardware_ID<<8));
	}
	else if(Flex_Channelx == Flex_Channel3)/* channel3 */
	{
		DMAx->DMA_SRC_SEL0 &= (uint32_t)(~(0xFF<<16));
		DMAx->DMA_SRC_SEL0 |= (uint32_t)((Hardware_ID<<16));		
	}
	else if(Flex_Channelx == Flex_Channel4)/* channel5 */
	{
		DMAx->DMA_SRC_SEL0 &= (uint32_t)(~((~0x00)<<24));
		DMAx->DMA_SRC_SEL0 |= (uint32_t)((Hardware_ID<<24));			
	}	
	else if(Flex_Channelx == Flex_Channel5)/* channel5 */
	{
		DMAx->DMA_SRC_SEL1 &= (uint32_t)(~0xFF);
		DMAx->DMA_SRC_SEL1 |= (uint32_t)(Hardware_ID);		
	}	
	else if(Flex_Channelx == Flex_Channel6)/* channel6 */
	{
		DMAx->DMA_SRC_SEL1 &= (uint32_t)(~(0xFF<<8));
		DMAx->DMA_SRC_SEL1 |= (uint32_t)((Hardware_ID<<8));		
	}	
	else if(Flex_Channelx == Flex_Channel7)/* channel7 */
	{
		DMAx->DMA_SRC_SEL1 &= (uint32_t)(~(0xFF<<16));
		DMAx->DMA_SRC_SEL1 |= (uint32_t)((Hardware_ID<<16));		
	}
}

/**
  * @brief  Fills each DMA_InitStruct member with its default value.
  * @param  DMA_InitStruct : pointer to a DMA_InitType structure which will
  *         be initialized.
  * @retval None
  */
void DMA_DefaultInitParaConfig(DMA_InitType* DMA_InitStruct)
{
  /*-------------- Reset DMA init structure parameters values ------------------*/
  /* Initialize the DMA_PeripheralBaseAddr member */
  DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
  /* Initialize the DMA_MemoryBaseAddr member */
  DMA_InitStruct->DMA_MemoryBaseAddr = 0;
  /* Initialize the DMA_DIR member */
  DMA_InitStruct->DMA_Direction = DMA_DIR_PERIPHERALSRC;
  /* Initialize the DMA_BufferSize member */
  DMA_InitStruct->DMA_BufferSize = 0;
  /* Initialize the DMA_PeripheralInc member */
  DMA_InitStruct->DMA_PeripheralInc = DMA_PERIPHERALINC_DISABLE;
  /* Initialize the DMA_MemoryInc member */
  DMA_InitStruct->DMA_MemoryInc = DMA_MEMORYINC_DISABLE;
  /* Initialize the DMA_PeripheralDataSize member */
  DMA_InitStruct->DMA_PeripheralDataWidth = DMA_PERIPHERALDATAWIDTH_BYTE;
  /* Initialize the DMA_MemoryDataSize member */
  DMA_InitStruct->DMA_MemoryDataWidth = DMA_MEMORYDATAWIDTH_BYTE;
  /* Initialize the DMA_Mode member */
  DMA_InitStruct->DMA_Mode = DMA_MODE_NORMAL;
  /* Initialize the DMA_Priority member */
  DMA_InitStruct->DMA_Priority = DMA_PRIORITY_LOW;
  /* Initialize the DMA_M2M member */
  DMA_InitStruct->DMA_MTOM = DMA_MEMTOMEM_DISABLE;
}

/**
  * @brief  Enables or disables the specified DMAy Channelx.
  * @param  DMAy_Channelx: where y can be 1 or 2 to select the DMA and
  *   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the DMA Channel.
  * @param  NewState: new state of the DMAy Channelx.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_ChannelEnable(DMA_Channel_Type* DMAy_Channelx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DMAy Channelx */
    DMAy_Channelx->CHCTRL |= DMA_CHCTRL1_CHEN;
  }
  else
  {
    /* Disable the selected DMAy Channelx */
    DMAy_Channelx->CHCTRL &= (uint16_t)(~DMA_CHCTRL1_CHEN);
  }
}

/**
  * @brief  Enables or disables the specified DMAy Channelx interrupts.
  * @param  DMAy_Channelx: where y can be 1 or 2 to select the DMA and
  *   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the DMA Channel.
  * @param  DMA_INT: specifies the DMA interrupts sources to be enabled
  *   or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg DMA_INT_TC:  Transfer complete interrupt mask
  *     @arg DMA_INT_HT:  Half transfer interrupt mask
  *     @arg DMA_INT_ERR:  Transfer error interrupt mask
  * @param  NewState: new state of the specified DMA interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DMA_INTConfig(DMA_Channel_Type* DMAy_Channelx, uint32_t DMA_INT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  assert_param(IS_DMA_CONFIG_INT(DMA_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DMA interrupts */
    DMAy_Channelx->CHCTRL |= DMA_INT;
  }
  else
  {
    /* Disable the selected DMA interrupts */
    DMAy_Channelx->CHCTRL &= ~DMA_INT;
  }
}

/**
  * @brief  Sets the number of data units in the current DMAy Channelx transfer.
  * @param  DMAy_Channelx: where y can be 1 or 2 to select the DMA and
  *         x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the DMA Channel.
  * @param  DataNumber: The number of data units in the current DMAy Channelx
  *         transfer.
  * @note   This function can only be used when the DMAy_Channelx is disabled.
  * @retval None.
  */
void DMA_SetCurrDataCounter(DMA_Channel_Type* DMAy_Channelx, uint16_t DataNumber)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));

  /*--------------------------- DMAy Channelx CNDTR Configuration ---------------*/
  /* Write to DMAy Channelx CNDTR */
  DMAy_Channelx->TCNT = DataNumber;
}

/**
  * @brief  Returns the number of remaining data units in the current
  *         DMAy Channelx transfer.
  * @param  DMAy_Channelx: where y can be 1 or 2 to select the DMA and
  *   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the DMA Channel.
  * @retval The number of remaining data units in the current DMAy Channelx
  *         transfer.
  */
uint16_t DMA_GetCurrDataCounter(DMA_Channel_Type* DMAy_Channelx)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
  /* Return the number of remaining data units for DMAy Channelx */
  return ((uint16_t)(DMAy_Channelx->TCNT));
}

/**
  * @brief  Checks whether the specified DMAy Channelx flag is set or not.
  * @param  DMAy_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg DMA1_FLAG_GL1: DMA1 Channel1 global flag.
  *     @arg DMA1_FLAG_TC1: DMA1 Channel1 transfer complete flag.
  *     @arg DMA1_FLAG_HT1: DMA1 Channel1 half transfer flag.
  *     @arg DMA1_FLAG_ERR1: DMA1 Channel1 transfer error flag.
  *     @arg DMA1_FLAG_GL2: DMA1 Channel2 global flag.
  *     @arg DMA1_FLAG_TC2: DMA1 Channel2 transfer complete flag.
  *     @arg DMA1_FLAG_HT2: DMA1 Channel2 half transfer flag.
  *     @arg DMA1_FLAG_ERR2: DMA1 Channel2 transfer error flag.
  *     @arg DMA1_FLAG_GL3: DMA1 Channel3 global flag.
  *     @arg DMA1_FLAG_TC3: DMA1 Channel3 transfer complete flag.
  *     @arg DMA1_FLAG_HT3: DMA1 Channel3 half transfer flag.
  *     @arg DMA1_FLAG_ERR3: DMA1 Channel3 transfer error flag.
  *     @arg DMA1_FLAG_GL4: DMA1 Channel4 global flag.
  *     @arg DMA1_FLAG_TC4: DMA1 Channel4 transfer complete flag.
  *     @arg DMA1_FLAG_HT4: DMA1 Channel4 half transfer flag.
  *     @arg DMA1_FLAG_ERR4: DMA1 Channel4 transfer error flag.
  *     @arg DMA1_FLAG_GL5: DMA1 Channel5 global flag.
  *     @arg DMA1_FLAG_TC5: DMA1 Channel5 transfer complete flag.
  *     @arg DMA1_FLAG_HT5: DMA1 Channel5 half transfer flag.
  *     @arg DMA1_FLAG_ERR5: DMA1 Channel5 transfer error flag.
  *     @arg DMA1_FLAG_GL6: DMA1 Channel6 global flag.
  *     @arg DMA1_FLAG_TC6: DMA1 Channel6 transfer complete flag.
  *     @arg DMA1_FLAG_HT6: DMA1 Channel6 half transfer flag.
  *     @arg DMA1_FLAG_ERR6: DMA1 Channel6 transfer error flag.
  *     @arg DMA1_FLAG_GL7: DMA1 Channel7 global flag.
  *     @arg DMA1_FLAG_TC7: DMA1 Channel7 transfer complete flag.
  *     @arg DMA1_FLAG_HT7: DMA1 Channel7 half transfer flag.
  *     @arg DMA1_FLAG_ERR7: DMA1 Channel7 transfer error flag.
  *     @arg DMA2_FLAG_GL1: DMA2 Channel1 global flag.
  *     @arg DMA2_FLAG_TC1: DMA2 Channel1 transfer complete flag.
  *     @arg DMA2_FLAG_HT1: DMA2 Channel1 half transfer flag.
  *     @arg DMA2_FLAG_ERR1: DMA2 Channel1 transfer error flag.
  *     @arg DMA2_FLAG_GL2: DMA2 Channel2 global flag.
  *     @arg DMA2_FLAG_TC2: DMA2 Channel2 transfer complete flag.
  *     @arg DMA2_FLAG_HT2: DMA2 Channel2 half transfer flag.
  *     @arg DMA2_FLAG_ERR2: DMA2 Channel2 transfer error flag.
  *     @arg DMA2_FLAG_GL3: DMA2 Channel3 global flag.
  *     @arg DMA2_FLAG_TC3: DMA2 Channel3 transfer complete flag.
  *     @arg DMA2_FLAG_HT3: DMA2 Channel3 half transfer flag.
  *     @arg DMA2_FLAG_ERR3: DMA2 Channel3 transfer error flag.
  *     @arg DMA2_FLAG_GL4: DMA2 Channel4 global flag.
  *     @arg DMA2_FLAG_TC4: DMA2 Channel4 transfer complete flag.
  *     @arg DMA2_FLAG_HT4: DMA2 Channel4 half transfer flag.
  *     @arg DMA2_FLAG_ERR4: DMA2 Channel4 transfer error flag.
  *     @arg DMA2_FLAG_GL5: DMA2 Channel5 global flag.
  *     @arg DMA2_FLAG_TC5: DMA2 Channel5 transfer complete flag.
  *     @arg DMA2_FLAG_HT5: DMA2 Channel5 half transfer flag.
  *     @arg DMA2_FLAG_ERR5: DMA2 Channel5 transfer error flag.
  * @retval The new state of DMAy_FLAG (SET or RESET).
  */
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_DMA_GET_FLAG(DMAy_FLAG));

  /* Calculate the used DMAy */
  if ((DMAy_FLAG & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Get DMA2 ISR register value */
    tmpreg = DMA2->ISTS ;
  }
  else
  {
    /* Get DMA1 ISR register value */
    tmpreg = DMA1->ISTS ;
  }

  /* Check the status of the specified DMAy flag */
  if ((tmpreg & DMAy_FLAG) != (uint32_t)RESET)
  {
    /* DMAy_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* DMAy_FLAG is reset */
    bitstatus = RESET;
  }

  /* Return the DMAy_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the DMAy Channelx's pending flags.
  * @param  DMAy_FLAG: specifies the flag to clear.
  *   This parameter can be any combination (for the same DMA) of the following values:
  *     @arg DMA1_FLAG_GL1: DMA1 Channel1 global flag.
  *     @arg DMA1_FLAG_TC1: DMA1 Channel1 transfer complete flag.
  *     @arg DMA1_FLAG_HT1: DMA1 Channel1 half transfer flag.
  *     @arg DMA1_FLAG_ERR1: DMA1 Channel1 transfer error flag.
  *     @arg DMA1_FLAG_GL2: DMA1 Channel2 global flag.
  *     @arg DMA1_FLAG_TC2: DMA1 Channel2 transfer complete flag.
  *     @arg DMA1_FLAG_HT2: DMA1 Channel2 half transfer flag.
  *     @arg DMA1_FLAG_ERR2: DMA1 Channel2 transfer error flag.
  *     @arg DMA1_FLAG_GL3: DMA1 Channel3 global flag.
  *     @arg DMA1_FLAG_TC3: DMA1 Channel3 transfer complete flag.
  *     @arg DMA1_FLAG_HT3: DMA1 Channel3 half transfer flag.
  *     @arg DMA1_FLAG_ERR3: DMA1 Channel3 transfer error flag.
  *     @arg DMA1_FLAG_GL4: DMA1 Channel4 global flag.
  *     @arg DMA1_FLAG_TC4: DMA1 Channel4 transfer complete flag.
  *     @arg DMA1_FLAG_HT4: DMA1 Channel4 half transfer flag.
  *     @arg DMA1_FLAG_ERR4: DMA1 Channel4 transfer error flag.
  *     @arg DMA1_FLAG_GL5: DMA1 Channel5 global flag.
  *     @arg DMA1_FLAG_TC5: DMA1 Channel5 transfer complete flag.
  *     @arg DMA1_FLAG_HT5: DMA1 Channel5 half transfer flag.
  *     @arg DMA1_FLAG_ERR5: DMA1 Channel5 transfer error flag.
  *     @arg DMA1_FLAG_GL6: DMA1 Channel6 global flag.
  *     @arg DMA1_FLAG_TC6: DMA1 Channel6 transfer complete flag.
  *     @arg DMA1_FLAG_HT6: DMA1 Channel6 half transfer flag.
  *     @arg DMA1_FLAG_ERR6: DMA1 Channel6 transfer error flag.
  *     @arg DMA1_FLAG_GL7: DMA1 Channel7 global flag.
  *     @arg DMA1_FLAG_TC7: DMA1 Channel7 transfer complete flag.
  *     @arg DMA1_FLAG_HT7: DMA1 Channel7 half transfer flag.
  *     @arg DMA1_FLAG_ERR7: DMA1 Channel7 transfer error flag.
  *     @arg DMA2_FLAG_GL1: DMA2 Channel1 global flag.
  *     @arg DMA2_FLAG_TC1: DMA2 Channel1 transfer complete flag.
  *     @arg DMA2_FLAG_HT1: DMA2 Channel1 half transfer flag.
  *     @arg DMA2_FLAG_ERR1: DMA2 Channel1 transfer error flag.
  *     @arg DMA2_FLAG_GL2: DMA2 Channel2 global flag.
  *     @arg DMA2_FLAG_TC2: DMA2 Channel2 transfer complete flag.
  *     @arg DMA2_FLAG_HT2: DMA2 Channel2 half transfer flag.
  *     @arg DMA2_FLAG_ERR2: DMA2 Channel2 transfer error flag.
  *     @arg DMA2_FLAG_GL3: DMA2 Channel3 global flag.
  *     @arg DMA2_FLAG_TC3: DMA2 Channel3 transfer complete flag.
  *     @arg DMA2_FLAG_HT3: DMA2 Channel3 half transfer flag.
  *     @arg DMA2_FLAG_ERR3: DMA2 Channel3 transfer error flag.
  *     @arg DMA2_FLAG_GL4: DMA2 Channel4 global flag.
  *     @arg DMA2_FLAG_TC4: DMA2 Channel4 transfer complete flag.
  *     @arg DMA2_FLAG_HT4: DMA2 Channel4 half transfer flag.
  *     @arg DMA2_FLAG_ERR4: DMA2 Channel4 transfer error flag.
  *     @arg DMA2_FLAG_GL5: DMA2 Channel5 global flag.
  *     @arg DMA2_FLAG_TC5: DMA2 Channel5 transfer complete flag.
  *     @arg DMA2_FLAG_HT5: DMA2 Channel5 half transfer flag.
  *     @arg DMA2_FLAG_ERR5: DMA2 Channel5 transfer error flag.
  * @retval None
  */
void DMA_ClearFlag(uint32_t DMAy_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_FLAG(DMAy_FLAG));

  /* Calculate the used DMAy */
  if ((DMAy_FLAG & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Clear the selected DMAy flags */
    DMA2->ICLR = DMAy_FLAG;
  }
  else
  {
    /* Clear the selected DMAy flags */
    DMA1->ICLR = DMAy_FLAG;
  }
}

/**
  * @brief  Checks whether the specified DMAy Channelx interrupt has occurred or not.
  * @param  DMAy_INT: specifies the DMAy interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg DMA1_INT_GL1: DMA1 Channel1 global interrupt.
  *     @arg DMA1_INT_TC1: DMA1 Channel1 transfer complete interrupt.
  *     @arg DMA1_INT_HT1: DMA1 Channel1 half transfer interrupt.
  *     @arg DMA1_INT_ERR1: DMA1 Channel1 transfer error interrupt.
  *     @arg DMA1_INT_GL2: DMA1 Channel2 global interrupt.
  *     @arg DMA1_INT_TC2: DMA1 Channel2 transfer complete interrupt.
  *     @arg DMA1_INT_HT2: DMA1 Channel2 half transfer interrupt.
  *     @arg DMA1_INT_ERR2: DMA1 Channel2 transfer error interrupt.
  *     @arg DMA1_INT_GL3: DMA1 Channel3 global interrupt.
  *     @arg DMA1_INT_TC3: DMA1 Channel3 transfer complete interrupt.
  *     @arg DMA1_INT_HT3: DMA1 Channel3 half transfer interrupt.
  *     @arg DMA1_INT_ERR3: DMA1 Channel3 transfer error interrupt.
  *     @arg DMA1_INT_GL4: DMA1 Channel4 global interrupt.
  *     @arg DMA1_INT_TC4: DMA1 Channel4 transfer complete interrupt.
  *     @arg DMA1_INT_HT4: DMA1 Channel4 half transfer interrupt.
  *     @arg DMA1_INT_ERR4: DMA1 Channel4 transfer error interrupt.
  *     @arg DMA1_INT_GL5: DMA1 Channel5 global interrupt.
  *     @arg DMA1_INT_TC5: DMA1 Channel5 transfer complete interrupt.
  *     @arg DMA1_INT_HT5: DMA1 Channel5 half transfer interrupt.
  *     @arg DMA1_INT_ERR5: DMA1 Channel5 transfer error interrupt.
  *     @arg DMA1_INT_GL6: DMA1 Channel6 global interrupt.
  *     @arg DMA1_INT_TC6: DMA1 Channel6 transfer complete interrupt.
  *     @arg DMA1_INT_HT6: DMA1 Channel6 half transfer interrupt.
  *     @arg DMA1_INT_ERR6: DMA1 Channel6 transfer error interrupt.
  *     @arg DMA1_INT_GL7: DMA1 Channel7 global interrupt.
  *     @arg DMA1_INT_TC7: DMA1 Channel7 transfer complete interrupt.
  *     @arg DMA1_INT_HT7: DMA1 Channel7 half transfer interrupt.
  *     @arg DMA1_INT_ERR7: DMA1 Channel7 transfer error interrupt.
  *     @arg DMA2_INT_GL1: DMA2 Channel1 global interrupt.
  *     @arg DMA2_INT_TC1: DMA2 Channel1 transfer complete interrupt.
  *     @arg DMA2_INT_HT1: DMA2 Channel1 half transfer interrupt.
  *     @arg DMA2_INT_ERR1: DMA2 Channel1 transfer error interrupt.
  *     @arg DMA2_INT_GL2: DMA2 Channel2 global interrupt.
  *     @arg DMA2_INT_TC2: DMA2 Channel2 transfer complete interrupt.
  *     @arg DMA2_INT_HT2: DMA2 Channel2 half transfer interrupt.
  *     @arg DMA2_INT_ERR2: DMA2 Channel2 transfer error interrupt.
  *     @arg DMA2_INT_GL3: DMA2 Channel3 global interrupt.
  *     @arg DMA2_INT_TC3: DMA2 Channel3 transfer complete interrupt.
  *     @arg DMA2_INT_HT3: DMA2 Channel3 half transfer interrupt.
  *     @arg DMA2_INT_ERR3: DMA2 Channel3 transfer error interrupt.
  *     @arg DMA2_INT_GL4: DMA2 Channel4 global interrupt.
  *     @arg DMA2_INT_TC4: DMA2 Channel4 transfer complete interrupt.
  *     @arg DMA2_INT_HT4: DMA2 Channel4 half transfer interrupt.
  *     @arg DMA2_INT_ERR4: DMA2 Channel4 transfer error interrupt.
  *     @arg DMA2_INT_GL5: DMA2 Channel5 global interrupt.
  *     @arg DMA2_INT_TC5: DMA2 Channel5 transfer complete interrupt.
  *     @arg DMA2_INT_HT5: DMA2 Channel5 half transfer interrupt.
  *     @arg DMA2_INT_ERR5: DMA2 Channel5 transfer error interrupt.
  * @retval The new state of DMAy_INT (SET or RESET).
  */
ITStatus DMA_GetITStatus(uint32_t DMAy_INT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_DMA_GET_INT(DMAy_INT));

  /* Calculate the used DMA */
  if ((DMAy_INT & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Get DMA2 ISR register value */
    tmpreg = DMA2->ISTS;
  }
  else
  {
    /* Get DMA1 ISR register value */
    tmpreg = DMA1->ISTS;
  }

  /* Check the status of the specified DMAy interrupt */
  if ((tmpreg & DMAy_INT) != (uint32_t)RESET)
  {
    /* DMAy_INT is set */
    bitstatus = SET;
  }
  else
  {
    /* DMAy_INT is reset */
    bitstatus = RESET;
  }

  /* Return the DMA_INT status */
  return  bitstatus;
}

/**
  * @brief  Clears the DMAy Channelx's interrupt pending bits.
  * @param  DMAy_INT: specifies the DMAy interrupt pending bit to clear.
  *   This parameter can be any combination (for the same DMA) of the following values:
  *     @arg DMA1_INT_GL1: DMA1 Channel1 global interrupt.
  *     @arg DMA1_INT_TC1: DMA1 Channel1 transfer complete interrupt.
  *     @arg DMA1_INT_HT1: DMA1 Channel1 half transfer interrupt.
  *     @arg DMA1_INT_ERR1: DMA1 Channel1 transfer error interrupt.
  *     @arg DMA1_INT_GL2: DMA1 Channel2 global interrupt.
  *     @arg DMA1_INT_TC2: DMA1 Channel2 transfer complete interrupt.
  *     @arg DMA1_INT_HT2: DMA1 Channel2 half transfer interrupt.
  *     @arg DMA1_INT_ERR2: DMA1 Channel2 transfer error interrupt.
  *     @arg DMA1_INT_GL3: DMA1 Channel3 global interrupt.
  *     @arg DMA1_INT_TC3: DMA1 Channel3 transfer complete interrupt.
  *     @arg DMA1_INT_HT3: DMA1 Channel3 half transfer interrupt.
  *     @arg DMA1_INT_ERR3: DMA1 Channel3 transfer error interrupt.
  *     @arg DMA1_INT_GL4: DMA1 Channel4 global interrupt.
  *     @arg DMA1_INT_TC4: DMA1 Channel4 transfer complete interrupt.
  *     @arg DMA1_INT_HT4: DMA1 Channel4 half transfer interrupt.
  *     @arg DMA1_INT_ERR4: DMA1 Channel4 transfer error interrupt.
  *     @arg DMA1_INT_GL5: DMA1 Channel5 global interrupt.
  *     @arg DMA1_INT_TC5: DMA1 Channel5 transfer complete interrupt.
  *     @arg DMA1_INT_HT5: DMA1 Channel5 half transfer interrupt.
  *     @arg DMA1_INT_ERR5: DMA1 Channel5 transfer error interrupt.
  *     @arg DMA1_INT_GL6: DMA1 Channel6 global interrupt.
  *     @arg DMA1_INT_TC6: DMA1 Channel6 transfer complete interrupt.
  *     @arg DMA1_INT_HT6: DMA1 Channel6 half transfer interrupt.
  *     @arg DMA1_INT_ERR6: DMA1 Channel6 transfer error interrupt.
  *     @arg DMA1_INT_GL7: DMA1 Channel7 global interrupt.
  *     @arg DMA1_INT_TC7: DMA1 Channel7 transfer complete interrupt.
  *     @arg DMA1_INT_HT7: DMA1 Channel7 half transfer interrupt.
  *     @arg DMA1_INT_ERR7: DMA1 Channel7 transfer error interrupt.
  *     @arg DMA2_INT_GL1: DMA2 Channel1 global interrupt.
  *     @arg DMA2_INT_TC1: DMA2 Channel1 transfer complete interrupt.
  *     @arg DMA2_INT_HT1: DMA2 Channel1 half transfer interrupt.
  *     @arg DMA2_INT_ERR1: DMA2 Channel1 transfer error interrupt.
  *     @arg DMA2_INT_GL2: DMA2 Channel2 global interrupt.
  *     @arg DMA2_INT_TC2: DMA2 Channel2 transfer complete interrupt.
  *     @arg DMA2_INT_HT2: DMA2 Channel2 half transfer interrupt.
  *     @arg DMA2_INT_ERR2: DMA2 Channel2 transfer error interrupt.
  *     @arg DMA2_INT_GL3: DMA2 Channel3 global interrupt.
  *     @arg DMA2_INT_TC3: DMA2 Channel3 transfer complete interrupt.
  *     @arg DMA2_INT_HT3: DMA2 Channel3 half transfer interrupt.
  *     @arg DMA2_INT_ERR3: DMA2 Channel3 transfer error interrupt.
  *     @arg DMA2_INT_GL4: DMA2 Channel4 global interrupt.
  *     @arg DMA2_INT_TC4: DMA2 Channel4 transfer complete interrupt.
  *     @arg DMA2_INT_HT4: DMA2 Channel4 half transfer interrupt.
  *     @arg DMA2_INT_ERR4: DMA2 Channel4 transfer error interrupt.
  *     @arg DMA2_INT_GL5: DMA2 Channel5 global interrupt.
  *     @arg DMA2_INT_TC5: DMA2 Channel5 transfer complete interrupt.
  *     @arg DMA2_INT_HT5: DMA2 Channel5 half transfer interrupt.
  *     @arg DMA2_INT_ERR5: DMA2 Channel5 transfer error interrupt.
  * @retval None
  */
void DMA_ClearITPendingBit(uint32_t DMAy_INT)
{
  /* Check the parameters */
  assert_param(IS_DMA_CLEAR_INT(DMAy_INT));

  /* Calculate the used DMAy */
  if ((DMAy_INT & FLAG_Mask) != (uint32_t)RESET)
  {
    /* Clear the selected DMAy interrupt pending bits */
    DMA2->ICLR = DMAy_INT;
  }
  else
  {
    /* Clear the selected DMAy interrupt pending bits */
    DMA1->ICLR = DMAy_INT;
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


