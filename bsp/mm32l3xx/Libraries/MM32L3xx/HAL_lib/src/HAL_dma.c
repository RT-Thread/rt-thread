/**
******************************************************************************
* @file    HAL_dma.c
* @author  AE Team
* @version V1.0.0
* @date    28/7/2017
* @brief   This file provides all the DMA firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2017 MindMotion</center></h2>
*/ 

/* Includes ------------------------------------------------------------------*/
#include "HAL_dma.h"


/** @addtogroup StdPeriph_Driver
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

/* DMA ENABLE mask */
#define CCR_ENABLE_Set          ((uint32_t)0x00000001)
#define CCR_ENABLE_Reset        ((uint32_t)0xFFFFFFFE)

/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_Channel1_IT_Mask    ((uint32_t)0x0000000F)
#define DMA1_Channel2_IT_Mask    ((uint32_t)0x000000F0)
#define DMA1_Channel3_IT_Mask    ((uint32_t)0x00000F00)
#define DMA1_Channel4_IT_Mask    ((uint32_t)0x0000F000)
#define DMA1_Channel5_IT_Mask    ((uint32_t)0x000F0000)
#define DMA1_Channel6_IT_Mask    ((uint32_t)0x00F00000)
#define DMA1_Channel7_IT_Mask    ((uint32_t)0x0F000000)






/* DMA registers Masks */
#define CCR_CLEAR_Mask           ((uint32_t)0xFFFF800F)

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
*   values.
* @param DMAy_Channelx: where y can be 1 or 2 to select the DMA and
*   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the 
*   DMA Channel.
* @retval : None
*/
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
    /* Disable the selected DMAy Channelx */
    DMAy_Channelx->CCR &= CCR_ENABLE_Reset;
    /* Reset DMAy Channelx control register */
    DMAy_Channelx->CCR  = 0;
    
    /* Reset DMAy Channelx remaining bytes register */
    DMAy_Channelx->CNDTR = 0;
    
    /* Reset DMAy Channelx peripheral address register */
    DMAy_Channelx->CPAR  = 0;
    
    /* Reset DMAy Channelx memory address register */
    DMAy_Channelx->CMAR = 0;
    switch (*(uint32_t*)&DMAy_Channelx)
    {
    case DMA1_Channel1_BASE:
        /* Reset interrupt pending bits for DMA1 Channel1 */
        DMA1->IFCR |= DMA1_Channel1_IT_Mask;
        break;
    case DMA1_Channel2_BASE:
        /* Reset interrupt pending bits for DMA1 Channel2 */
        DMA1->IFCR |= DMA1_Channel2_IT_Mask;
        break;
    case DMA1_Channel3_BASE:
        /* Reset interrupt pending bits for DMA1 Channel3 */
        DMA1->IFCR |= DMA1_Channel3_IT_Mask;
        break;
    case DMA1_Channel4_BASE:
        /* Reset interrupt pending bits for DMA1 Channel4 */
        DMA1->IFCR |= DMA1_Channel4_IT_Mask;
        break;
    case DMA1_Channel5_BASE:
        /* Reset interrupt pending bits for DMA1 Channel5 */
        DMA1->IFCR |= DMA1_Channel5_IT_Mask;
        break;
    case DMA1_Channel6_BASE:
        /* Reset interrupt pending bits for DMA1 Channel6 */
        DMA1->IFCR |= DMA1_Channel6_IT_Mask;
        break;
    case DMA1_Channel7_BASE:
        /* Reset interrupt pending bits for DMA1 Channel7 */
        DMA1->IFCR |= DMA1_Channel7_IT_Mask;
        break;
        
    default:
        break;
    }
}

/**
* @brief  Initializes the DMAy Channelx according to the specified
*   parameters in the DMA_InitStruct.
* @param DMAy_Channelx: where y can be 1 or 2 to select the DMA and 
*   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the 
*   DMA Channel.
* @param DMA_InitStruct: pointer to a DMA_InitTypeDef structure that
*   contains the configuration information for the specified
*   DMA Channel.
* @retval : None
*/
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
    assert_param(IS_DMA_DIR(DMA_InitStruct->DMA_DIR));
    assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
    assert_param(IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc));
    assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));   
    assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(DMA_InitStruct->DMA_PeripheralDataSize));
    assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitStruct->DMA_MemoryDataSize));
    assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
    assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
    assert_param(IS_DMA_M2M_STATE(DMA_InitStruct->DMA_M2M));
    /*--------------------------- DMAy Channelx CCR Configuration -----------------*/
    /* Get the DMAy_Channelx CCR value */
    tmpreg = DMAy_Channelx->CCR;
    /* Clear MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
    tmpreg &= CCR_CLEAR_Mask;
    /* Configure DMAy Channelx: data transfer, data size, priority level and mode */
    /* Set DIR bit according to DMA_DIR value */
    /* Set CIRC bit according to DMA_Mode value */
    /* Set PINC bit according to DMA_PeripheralInc value */
    /* Set MINC bit according to DMA_MemoryInc value */
    /* Set PSIZE bits according to DMA_PeripheralDataSize value */
    /* Set MSIZE bits according to DMA_MemoryDataSize value */
    /* Set PL bits according to DMA_Priority value */
    /* Set the MEM2MEM bit according to DMA_M2M value */
    tmpreg |= DMA_InitStruct->DMA_DIR | DMA_InitStruct->DMA_Mode |
        DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
            DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
                DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_M2M;
    /* Write to DMAy Channelx CCR */
    DMAy_Channelx->CCR = tmpreg;
    /*--------------------------- DMAy Channelx CNDTR Configuration ---------------*/
    /* Write to DMAy Channelx CNDTR */
    DMAy_Channelx->CNDTR = DMA_InitStruct->DMA_BufferSize;
    /*--------------------------- DMAy Channelx CPAR Configuration ----------------*/
    /* Write to DMAy Channelx CPAR */
    DMAy_Channelx->CPAR = DMA_InitStruct->DMA_PeripheralBaseAddr;
    /*--------------------------- DMAy Channelx CMAR Configuration ----------------*/
    /* Write to DMAy Channelx CMAR */
    DMAy_Channelx->CMAR = DMA_InitStruct->DMA_MemoryBaseAddr;
}

/**
* @brief  Fills each DMA_InitStruct member with its default value.
* @param DMA_InitStruct : pointer to a DMA_InitTypeDef structure
*   which will be initialized.
* @retval : None
*/
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct)
{
    /*-------------- Reset DMA init structure parameters values ------------------*/
    /* Initialize the DMA_PeripheralBaseAddr member */
    DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
    /* Initialize the DMA_MemoryBaseAddr member */
    DMA_InitStruct->DMA_MemoryBaseAddr = 0;
    /* Initialize the DMA_DIR member */
    DMA_InitStruct->DMA_DIR = DMA_DIR_PeripheralSRC;
    /* Initialize the DMA_BufferSize member */
    DMA_InitStruct->DMA_BufferSize = 0;
    /* Initialize the DMA_PeripheralInc member */
    DMA_InitStruct->DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /* Initialize the DMA_MemoryInc member */
    DMA_InitStruct->DMA_MemoryInc = DMA_MemoryInc_Disable;
    /* Initialize the DMA_PeripheralDataSize member */
    DMA_InitStruct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    /* Initialize the DMA_MemoryDataSize member */
    DMA_InitStruct->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    /* Initialize the DMA_Mode member */
    DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;
    /* Initialize the DMA_Priority member */
    DMA_InitStruct->DMA_Priority = DMA_Priority_Low;
    /* Initialize the DMA_M2M member */
    DMA_InitStruct->DMA_M2M = DMA_M2M_Disable;
}

/**
* @brief  Enables or disables the specified DMAy Channelx.
* @param DMAy_Channelx: where y can be 1 or 2 to select the DMA and 
*   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the 
*   DMA Channel.
* @param NewState: new state of the DMAy Channelx. 
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected DMAy Channelx */
        DMAy_Channelx->CCR |= CCR_ENABLE_Set;
    }
    else
    {
        /* Disable the selected DMAy Channelx */
        DMAy_Channelx->CCR &= CCR_ENABLE_Reset;
    }
}

/**
* @brief  Enables or disables the specified DMAy Channelx interrupts.
* @param DMAy_Channelx: where y can be 1 or 2 to select the DMA and 
*   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the 
*   DMA Channel.
* @param DMA_IT: specifies the DMA interrupts sources to be enabled
*   or disabled. 
*   This parameter can be any combination of the following values:
* @arg DMA_IT_TC:  Transfer complete interrupt mask
* @arg DMA_IT_HT:  Half transfer interrupt mask
* @arg DMA_IT_TE:  Transfer error interrupt mask
* @param NewState: new state of the specified DMA interrupts.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
    assert_param(IS_DMA_CONFIG_IT(DMA_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected DMA interrupts */
        DMAy_Channelx->CCR |= DMA_IT;
    }
    else
    {
        /* Disable the selected DMA interrupts */
        DMAy_Channelx->CCR &= ~DMA_IT;
    }
}

/**
* @brief  Returns the number of remaining data units in the current
*   DMAy Channelx transfer.
* @param DMAy_Channelx: where y can be 1 or 2 to select the DMA and 
*   x can be 1 to 7 for DMA1 and 1 to 5 for DMA2 to select the 
*   DMA Channel.
* @retval : The number of remaining data units in the current DMAy Channelx
*   transfer.
*/
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Channelx));
    /* Return the number of remaining data units for DMAy Channelx */
    return ((uint16_t)(DMAy_Channelx->CNDTR));
}

/**
* @brief  Checks whether the specified DMAy Channelx flag is set or not.
* @param DMA_FLAG: specifies the flag to check.
*   This parameter can be one of the following values:
* @arg DMA1_FLAG_GL1: DMA1 Channel1 global flag.
* @arg DMA1_FLAG_TC1: DMA1 Channel1 transfer complete flag.
* @arg DMA1_FLAG_HT1: DMA1 Channel1 half transfer flag.
* @arg DMA1_FLAG_TE1: DMA1 Channel1 transfer error flag.
* @arg DMA1_FLAG_GL2: DMA1 Channel2 global flag.
* @arg DMA1_FLAG_TC2: DMA1 Channel2 transfer complete flag.
* @arg DMA1_FLAG_HT2: DMA1 Channel2 half transfer flag.
* @arg DMA1_FLAG_TE2: DMA1 Channel2 transfer error flag.
* @arg DMA1_FLAG_GL3: DMA1 Channel3 global flag.
* @arg DMA1_FLAG_TC3: DMA1 Channel3 transfer complete flag.
* @arg DMA1_FLAG_HT3: DMA1 Channel3 half transfer flag.
* @arg DMA1_FLAG_TE3: DMA1 Channel3 transfer error flag.
* @arg DMA1_FLAG_GL4: DMA1 Channel4 global flag.
* @arg DMA1_FLAG_TC4: DMA1 Channel4 transfer complete flag.
* @arg DMA1_FLAG_HT4: DMA1 Channel4 half transfer flag.
* @arg DMA1_FLAG_TE4: DMA1 Channel4 transfer error flag.
* @arg DMA1_FLAG_GL5: DMA1 Channel5 global flag.
* @arg DMA1_FLAG_TC5: DMA1 Channel5 transfer complete flag.
* @arg DMA1_FLAG_HT5: DMA1 Channel5 half transfer flag.
* @arg DMA1_FLAG_TE5: DMA1 Channel5 transfer error flag.
* @arg DMA1_FLAG_GL6: DMA1 Channel6 global flag.
* @arg DMA1_FLAG_TC6: DMA1 Channel6 transfer complete flag.
* @arg DMA1_FLAG_HT6: DMA1 Channel6 half transfer flag.
* @arg DMA1_FLAG_TE6: DMA1 Channel6 transfer error flag.
* @arg DMA1_FLAG_GL7: DMA1 Channel7 global flag.
* @arg DMA1_FLAG_TC7: DMA1 Channel7 transfer complete flag.
* @arg DMA1_FLAG_HT7: DMA1 Channel7 half transfer flag.
* @arg DMA1_FLAG_TE7: DMA1 Channel7 transfer error flag.
* @retval : The new state of DMA_FLAG (SET or RESET).
*/
FlagStatus DMA_GetFlagStatus(uint32_t DMA_FLAG)
{
    FlagStatus bitstatus = RESET;
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_DMA_GET_FLAG(DMA_FLAG));
    
    /* Get DMA1 ISR register value */
    tmpreg = DMA1->ISR ;
    
    /* Check the status of the specified DMA flag */
    if ((tmpreg & DMA_FLAG) != (uint32_t)RESET)
    {
        /* DMA_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* DMA_FLAG is reset */
        bitstatus = RESET;
    }
    
    /* Return the DMA_FLAG status */
    return  bitstatus;
}

/**
* @brief  Clears the DMAy Channelx's pending flags.
* @param DMA_FLAG: specifies the flag to clear.
*   This parameter can be any combination (for the same DMA) of 
*   the following values:
* @arg DMA1_FLAG_GL1: DMA1 Channel1 global flag.
* @arg DMA1_FLAG_TC1: DMA1 Channel1 transfer complete flag.
* @arg DMA1_FLAG_HT1: DMA1 Channel1 half transfer flag.
* @arg DMA1_FLAG_TE1: DMA1 Channel1 transfer error flag.
* @arg DMA1_FLAG_GL2: DMA1 Channel2 global flag.
* @arg DMA1_FLAG_TC2: DMA1 Channel2 transfer complete flag.
* @arg DMA1_FLAG_HT2: DMA1 Channel2 half transfer flag.
* @arg DMA1_FLAG_TE2: DMA1 Channel2 transfer error flag.
* @arg DMA1_FLAG_GL3: DMA1 Channel3 global flag.
* @arg DMA1_FLAG_TC3: DMA1 Channel3 transfer complete flag.
* @arg DMA1_FLAG_HT3: DMA1 Channel3 half transfer flag.
* @arg DMA1_FLAG_TE3: DMA1 Channel3 transfer error flag.
* @arg DMA1_FLAG_GL4: DMA1 Channel4 global flag.
* @arg DMA1_FLAG_TC4: DMA1 Channel4 transfer complete flag.
* @arg DMA1_FLAG_HT4: DMA1 Channel4 half transfer flag.
* @arg DMA1_FLAG_TE4: DMA1 Channel4 transfer error flag.
* @arg DMA1_FLAG_GL5: DMA1 Channel5 global flag.
* @arg DMA1_FLAG_TC5: DMA1 Channel5 transfer complete flag.
* @arg DMA1_FLAG_HT5: DMA1 Channel5 half transfer flag.
* @arg DMA1_FLAG_TE5: DMA1 Channel5 transfer error flag.
* @arg DMA1_FLAG_GL6: DMA1 Channel6 global flag.
* @arg DMA1_FLAG_TC6: DMA1 Channel6 transfer complete flag.
* @arg DMA1_FLAG_HT6: DMA1 Channel6 half transfer flag.
* @arg DMA1_FLAG_TE6: DMA1 Channel6 transfer error flag.
* @arg DMA1_FLAG_GL7: DMA1 Channel7 global flag.
* @arg DMA1_FLAG_TC7: DMA1 Channel7 transfer complete flag.
* @arg DMA1_FLAG_HT7: DMA1 Channel7 half transfer flag.
* @arg DMA1_FLAG_TE7: DMA1 Channel7 transfer error flag.
* @retval : None
*/
void DMA_ClearFlag(uint32_t DMA_FLAG)
{
    /* Check the parameters */
    assert_param(IS_DMA_CLEAR_FLAG(DMA_FLAG));
    
    /* Clear the selected DMA flags */
    DMA1->IFCR = DMA_FLAG;
}

/**
* @brief  Checks whether the specified DMAy Channelx interrupt has 
*   occurred or not.
* @param DMA_IT: specifies the DMA interrupt source to check. 
*   This parameter can be one of the following values:
* @arg DMA1_IT_GL1: DMA1 Channel1 global interrupt.
* @arg DMA1_IT_TC1: DMA1 Channel1 transfer complete interrupt.
* @arg DMA1_IT_HT1: DMA1 Channel1 half transfer interrupt.
* @arg DMA1_IT_TE1: DMA1 Channel1 transfer error interrupt.
* @arg DMA1_IT_GL2: DMA1 Channel2 global interrupt.
* @arg DMA1_IT_TC2: DMA1 Channel2 transfer complete interrupt.
* @arg DMA1_IT_HT2: DMA1 Channel2 half transfer interrupt.
* @arg DMA1_IT_TE2: DMA1 Channel2 transfer error interrupt.
* @arg DMA1_IT_GL3: DMA1 Channel3 global interrupt.
* @arg DMA1_IT_TC3: DMA1 Channel3 transfer complete interrupt.
* @arg DMA1_IT_HT3: DMA1 Channel3 half transfer interrupt.
* @arg DMA1_IT_TE3: DMA1 Channel3 transfer error interrupt.
* @arg DMA1_IT_GL4: DMA1 Channel4 global interrupt.
* @arg DMA1_IT_TC4: DMA1 Channel4 transfer complete interrupt.
* @arg DMA1_IT_HT4: DMA1 Channel4 half transfer interrupt.
* @arg DMA1_IT_TE4: DMA1 Channel4 transfer error interrupt.
* @arg DMA1_IT_GL5: DMA1 Channel5 global interrupt.
* @arg DMA1_IT_TC5: DMA1 Channel5 transfer complete interrupt.
* @arg DMA1_IT_HT5: DMA1 Channel5 half transfer interrupt.
* @arg DMA1_IT_TE5: DMA1 Channel5 transfer error interrupt.
* @arg DMA1_IT_GL6: DMA1 Channel6 global interrupt.
* @arg DMA1_IT_TC6: DMA1 Channel6 transfer complete interrupt.
* @arg DMA1_IT_HT6: DMA1 Channel6 half transfer interrupt.
* @arg DMA1_IT_TE6: DMA1 Channel6 transfer error interrupt.
* @arg DMA1_IT_GL7: DMA1 Channel7 global interrupt.
* @arg DMA1_IT_TC7: DMA1 Channel7 transfer complete interrupt.
* @arg DMA1_IT_HT7: DMA1 Channel7 half transfer interrupt.
* @arg DMA1_IT_TE7: DMA1 Channel7 transfer error interrupt.
* @retval : The new state of DMA_IT (SET or RESET).
*/
ITStatus DMA_GetITStatus(uint32_t DMA_IT)
{
    ITStatus bitstatus = RESET;
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_DMA_GET_IT(DMA_IT));
    
    /* Get DMA1 ISR register value */
    tmpreg = DMA1->ISR ;
    
    /* Check the status of the specified DMA interrupt */
    if ((tmpreg & DMA_IT) != (uint32_t)RESET)
    {
        /* DMA_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* DMA_IT is reset */
        bitstatus = RESET;
    }
    /* Return the DMA_IT status */
    return  bitstatus;
}

/**
* @brief  Clears the DMAy Channelx’s interrupt pending bits.
* @param DMA_IT: specifies the DMA interrupt pending bit to clear.
*   This parameter can be any combination (for the same DMA) of
*   the following values:
* @arg DMA1_IT_GL1: DMA1 Channel1 global interrupt.
* @arg DMA1_IT_TC1: DMA1 Channel1 transfer complete interrupt.
* @arg DMA1_IT_HT1: DMA1 Channel1 half transfer interrupt.
* @arg DMA1_IT_TE1: DMA1 Channel1 transfer error interrupt.
* @arg DMA1_IT_GL2: DMA1 Channel2 global interrupt.
* @arg DMA1_IT_TC2: DMA1 Channel2 transfer complete interrupt.
* @arg DMA1_IT_HT2: DMA1 Channel2 half transfer interrupt.
* @arg DMA1_IT_TE2: DMA1 Channel2 transfer error interrupt.
* @arg DMA1_IT_GL3: DMA1 Channel3 global interrupt.
* @arg DMA1_IT_TC3: DMA1 Channel3 transfer complete interrupt.
* @arg DMA1_IT_HT3: DMA1 Channel3 half transfer interrupt.
* @arg DMA1_IT_TE3: DMA1 Channel3 transfer error interrupt.
* @arg DMA1_IT_GL4: DMA1 Channel4 global interrupt.
* @arg DMA1_IT_TC4: DMA1 Channel4 transfer complete interrupt.
* @arg DMA1_IT_HT4: DMA1 Channel4 half transfer interrupt.
* @arg DMA1_IT_TE4: DMA1 Channel4 transfer error interrupt.
* @arg DMA1_IT_GL5: DMA1 Channel5 global interrupt.
* @arg DMA1_IT_TC5: DMA1 Channel5 transfer complete interrupt.
* @arg DMA1_IT_HT5: DMA1 Channel5 half transfer interrupt.
* @arg DMA1_IT_TE5: DMA1 Channel5 transfer error interrupt.
* @arg DMA1_IT_GL6: DMA1 Channel6 global interrupt.
* @arg DMA1_IT_TC6: DMA1 Channel6 transfer complete interrupt.
* @arg DMA1_IT_HT6: DMA1 Channel6 half transfer interrupt.
* @arg DMA1_IT_TE6: DMA1 Channel6 transfer error interrupt.
* @arg DMA1_IT_GL7: DMA1 Channel7 global interrupt.
* @arg DMA1_IT_TC7: DMA1 Channel7 transfer complete interrupt.
* @arg DMA1_IT_HT7: DMA1 Channel7 half transfer interrupt.
* @arg DMA1_IT_TE7: DMA1 Channel7 transfer error interrupt.
* @retval : None
*/
void DMA_ClearITPendingBit(uint32_t DMA_IT)
{
    /* Check the parameters */
    assert_param(IS_DMA_CLEAR_IT(DMA_IT));
    
    /* Clear the selected DMA interrupt pending bits */
    DMA1->IFCR = DMA_IT;
    
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

/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
