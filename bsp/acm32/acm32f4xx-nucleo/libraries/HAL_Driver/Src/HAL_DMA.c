/*
  ******************************************************************************
  * @file    HAL_DMA.c
  * @version V1.0.0
  * @date    2020
  * @brief   DMA HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Direct Memory Access (DMA) peripheral:
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/**************** Used in cycle mode ****************/
static DMA_LLI_InitTypeDef Cycle_Channel[DMA_CHANNEL_NUM];

/*********************************************************************************
* Function    : HAL_DMA_IRQHandler
* Description : This function handles DMA interrupt request.
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Output      : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
__weak void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma)
{
    uint32_t lu32_Channel_Index;
    
    /* Get DMA Channel number */
    lu32_Channel_Index = ((uint32_t)(hdma->Instance) - (uint32_t)(DMA_Channel0)) / 0x20;

    /* Channel has been interrupted */
    if (DMA->INT_STATUS & (1 << lu32_Channel_Index))
    {
        /* Transfer complete interrupt */
        if (DMA->INT_TC_STATUS & (1 << lu32_Channel_Index))
        {
            DMA->INT_TC_CLR |= (1 << lu32_Channel_Index);

            if (NULL != hdma->DMA_ITC_Callback)
            {
                hdma->DMA_ITC_Callback();
            }
        }
        
        /* Transfer error interrupt */
        if (DMA->INT_ERR_STATUS & (1 << lu32_Channel_Index))
        {
            DMA->INT_ERR_CLR |= (1 << lu32_Channel_Index);

            if (NULL != hdma->DMA_IE_Callback)
            {
                hdma->DMA_IE_Callback();
            }
        }
    }
}

/*********************************************************************************
* Function    : HAL_DMA_Init
* Description : DMA initial with parameters. 
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Output      : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma) 
{
#if (USE_FULL_ASSERT == 1)
    /* Check DMA Parameter */
    if (!IS_DMA_ALL_INSTANCE(hdma->Instance))                 return HAL_ERROR;
    if (!IS_DMA_DATA_FLOW(hdma->Init.Data_Flow))              return HAL_ERROR;
    if (!IS_DMA_REQUEST_ID(hdma->Init.Request_ID))            return HAL_ERROR;
    if (!IS_DMA_SRC_WIDTH(hdma->Init.Source_Width))           return HAL_ERROR;
    if (!IS_DMA_DST_WIDTH(hdma->Init.Desination_Width))       return HAL_ERROR;
#endif

    /* Enable DMA Module */
    System_Module_Enable(EN_DMA);
    
    /* Enable External Interrupt */
    NVIC_ClearPendingIRQ(DMA_IRQn);
    NVIC_EnableIRQ(DMA_IRQn);

    /* Default Little-Endian、Enable DMA */
    DMA->CONFIG = DMA_CONFIG_EN;

    /* Clear Channel Config */
    hdma->Instance->CONFIG = 0x00000000; 
    
    if (hdma->Init.Data_Flow == DMA_DATA_FLOW_M2P) 
    {
        hdma->Init.Request_ID <<= DMA_CHANNEL_CONFIG_DEST_PERIPH_POS;
    }
    else if (hdma->Init.Data_Flow == DMA_DATA_FLOW_P2M) 
    {
        hdma->Init.Request_ID <<= DMA_CHANNEL_CONFIG_SRC_PERIPH_POS;
    }

    hdma->Instance->CONFIG = hdma->Init.Data_Flow | hdma->Init.Request_ID;
    
    /* Config Channel Control */
    hdma->Instance->CTRL = DMA_CHANNEL_CTRL_ITC;
    /* Source or Desination address increase */
    hdma->Instance->CTRL |= (hdma->Init.Desination_Inc | hdma->Init.Source_Inc);
    /* Source or Desination date width */
    hdma->Instance->CTRL |= (hdma->Init.Desination_Width | hdma->Init.Source_Width);

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DMA_DeInit
* Description : DMA De-initial with parameters. 
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Output      : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma) 
{
#if (USE_FULL_ASSERT == 1)
    /* Check DMA Parameter */
    if (!IS_DMA_ALL_INSTANCE(hdma->Instance))                 return HAL_ERROR;
    if (!IS_DMA_DATA_FLOW(hdma->Init.Data_Flow))              return HAL_ERROR;
    if (!IS_DMA_REQUEST_ID(hdma->Init.Request_ID))            return HAL_ERROR;
    if (!IS_DMA_SRC_WIDTH(hdma->Init.Source_Width))           return HAL_ERROR;
    if (!IS_DMA_DST_WIDTH(hdma->Init.Desination_Width))       return HAL_ERROR;
#endif

    /* Reset DMA Module */
    System_Module_Reset(RST_DMA);
    
    /* Disable DMA Module */
    System_Module_Disable(EN_DMA);
    
    /* Disable Interrupt */
    NVIC_ClearPendingIRQ(DMA_IRQn);
    NVIC_DisableIRQ(DMA_IRQn);
    
    hdma->DMA_IE_Callback = NULL;
    hdma->DMA_ITC_Callback = NULL;

    memset(&hdma->Init, 0, sizeof(hdma->Init));
    
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DMA_NormalMode_Start
* Description : DMA transfer start. 
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Input       : fu32_SrcAddr: source address
* Input       : fu32_DstAddr: desination address
* Input       : fu32_Size:    transfer size (This parameter can be a 12-bit Size)
* Output      : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_DMA_NormalMode_Start(DMA_HandleTypeDef *hdma, uint32_t fu32_SrcAddr, uint32_t fu32_DstAddr, uint32_t fu32_Size)
{
#if (USE_FULL_ASSERT == 1)
    /* Check DMA Parameter */
    if (!IS_DMA_ALL_INSTANCE(hdma->Instance))    return HAL_ERROR;
#endif
    
    if (fu32_Size > 0xFFF) 
    {
        return HAL_ERROR;
    }

    /* Set source address and desination address */
    hdma->Instance->SRC_ADDR  = fu32_SrcAddr;
    hdma->Instance->DEST_ADDR = fu32_DstAddr;

    /* Set Transfer Size */
    hdma->Instance->CTRL = (hdma->Instance->CTRL & (~0xFFF)) | fu32_Size;

    /* DMA Channel Enable */
    hdma->Instance->CONFIG |= DMA_CHANNEL_CONFIG_EN;

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DMA_NormalMode_Start_IT
* Description : DMA transfer start with interrupt. 
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Input       : fu32_SrcAddr: source address
* Input       : fu32_DstAddr: desination address
* Input       : fu32_Size:    transfer size (This parameter can be a 12-bit Size)
* Output      : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_DMA_NormalMode_Start_IT(DMA_HandleTypeDef *hdma, uint32_t fu32_SrcAddr, uint32_t fu32_DstAddr, uint32_t fu32_Size)
{
#if (USE_FULL_ASSERT == 1)
    /* Check DMA Parameter */
    if (!IS_DMA_ALL_INSTANCE(hdma->Instance))    return HAL_ERROR;
#endif

    /* Set source address and desination address */
    hdma->Instance->SRC_ADDR  = fu32_SrcAddr;
    hdma->Instance->DEST_ADDR = fu32_DstAddr;

    /* Set Transfer Size and enable LLI interrupt */
    hdma->Instance->CTRL = (hdma->Instance->CTRL & (~0xFFF)) | fu32_Size;

    /* DMA Channel Enable and enable transfer error interrupt and transfer complete interrupt*/
    hdma->Instance->CONFIG |= DMA_CHANNEL_CONFIG_ITC | DMA_CHANNEL_CONFIG_IE | DMA_CHANNEL_CONFIG_EN;

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DMA_CycleMode_Start
* Description : DMA Cycle transfer start. 
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Input       : fu32_SrcAddr: source address
* Input       : fu32_DstAddr: desination address
* Input       : fu32_Size:    transfer size (This parameter can be a 12-bit Size)
* Output      : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_DMA_CycleMode_Start(DMA_HandleTypeDef *hdma, uint32_t fu32_SrcAddr, uint32_t fu32_DstAddr, uint32_t fu32_Size)
{
    uint32_t lu32_Channel_Index;

#if (USE_FULL_ASSERT == 1)
    /* Check DMA Parameter */
    if (!IS_DMA_ALL_INSTANCE(hdma->Instance))    return HAL_ERROR;
#endif

    /* Get DMA Channel number */
    lu32_Channel_Index = ((uint32_t)(hdma->Instance) - (uint32_t)(DMA_Channel0)) / 0x20;
    
    /* Set source address and desination address */
    hdma->Instance->SRC_ADDR  = fu32_SrcAddr;
    hdma->Instance->DEST_ADDR = fu32_DstAddr;

    /* Set Next Link */
    hdma->Instance->LLI = (uint32_t)&Cycle_Channel[lu32_Channel_Index];

    /* Set Transfer Size */
    hdma->Instance->CTRL = (hdma->Instance->CTRL & (~0xFFF)) | fu32_Size;

    /* The list point to oneself */
    Cycle_Channel[lu32_Channel_Index].SrcAddr = fu32_SrcAddr;
    Cycle_Channel[lu32_Channel_Index].DstAddr = fu32_DstAddr;
    Cycle_Channel[lu32_Channel_Index].Next    = &Cycle_Channel[lu32_Channel_Index];
    Cycle_Channel[lu32_Channel_Index].Control = (hdma->Instance->CTRL & (~0xFFF)) | fu32_Size;

    /* DMA Channel Enable */
    hdma->Instance->CONFIG |= DMA_CHANNEL_CONFIG_EN;

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DMA_CycleMode_Start_IT
* Description : DMA Cycle transfer start with interrupt. 
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Input       : fu32_SrcAddr: source address
* Input       : fu32_DstAddr: desination address
* Input       : fu32_Size:    transfer size (This parameter can be a 12-bit Size)
* Output      : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_DMA_CycleMode_Start_IT(DMA_HandleTypeDef *hdma, uint32_t fu32_SrcAddr, uint32_t fu32_DstAddr, uint32_t fu32_Size)
{
    uint32_t lu32_Channel_Index;

#if (USE_FULL_ASSERT == 1)
    /* Check DMA Parameter */
    if (!IS_DMA_ALL_INSTANCE(hdma->Instance))    return HAL_ERROR;
#endif

    /* Get DMA Channel number */
    lu32_Channel_Index = ((uint32_t)(hdma->Instance) - (uint32_t)(DMA_Channel0)) / 0x20;
    
    /* Set source address and desination address */
    hdma->Instance->SRC_ADDR  = fu32_SrcAddr;
    hdma->Instance->DEST_ADDR = fu32_DstAddr;

    /* Set Next Link */
    hdma->Instance->LLI = (uint32_t)&Cycle_Channel[lu32_Channel_Index];

    /* Set Transfer Size */
    hdma->Instance->CTRL = (hdma->Instance->CTRL & (~0xFFF)) | fu32_Size;

    /* The list point to oneself */
    Cycle_Channel[lu32_Channel_Index].SrcAddr = fu32_SrcAddr;
    Cycle_Channel[lu32_Channel_Index].DstAddr = fu32_DstAddr;
    Cycle_Channel[lu32_Channel_Index].Next    = &Cycle_Channel[lu32_Channel_Index];
    Cycle_Channel[lu32_Channel_Index].Control = (hdma->Instance->CTRL & (~0xFFF)) | fu32_Size;

    /* DMA Channel Enable and enable transfer error interrupt and transfer complete interrupt*/
    hdma->Instance->CONFIG |= DMA_CHANNEL_CONFIG_ITC | DMA_CHANNEL_CONFIG_IE | DMA_CHANNEL_CONFIG_EN;

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DMA_Start
* Description : DMA transfer start. 
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Input       : fu32_SrcAddr: source address
* Input       : fu32_DstAddr: desination address
* Input       : fu32_Size:    transfer size (This parameter can be a 12-bit Size)
* Output      : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t fu32_SrcAddr, uint32_t fu32_DstAddr, uint32_t fu32_Size)
{
    /* Check DMA Parameter */
    if (!IS_DMA_MODE(hdma->Init.Mode))    return HAL_ERROR;
        
    if (hdma->Init.Mode == DMA_NORMAL)
    {
        return HAL_DMA_NormalMode_Start(hdma, fu32_SrcAddr, fu32_DstAddr, fu32_Size);
    }
    else
    {
        return HAL_DMA_CycleMode_Start(hdma, fu32_SrcAddr, fu32_DstAddr, fu32_Size);
    }
}

/*********************************************************************************
* Function    : HAL_DMA_Start_IT
* Description : DMA transfer start with interrupt. 
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Input       : fu32_SrcAddr: source address
* Input       : fu32_DstAddr: desination address
* Input       : fu32_Size:    transfer size (This parameter can be a 12-bit Size)
* Output      : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t fu32_SrcAddr, uint32_t fu32_DstAddr, uint32_t fu32_Size)
{
    /* Check DMA Parameter */
    if (!IS_DMA_MODE(hdma->Init.Mode))    return HAL_ERROR;

    if (hdma->Init.Mode == DMA_NORMAL)
    {
        return HAL_DMA_NormalMode_Start_IT(hdma, fu32_SrcAddr, fu32_DstAddr, fu32_Size);
    }
    else
    {
        return HAL_DMA_CycleMode_Start_IT(hdma, fu32_SrcAddr, fu32_DstAddr, fu32_Size);
    }
}

/*********************************************************************************
* Function    : HAL_DMA_Abort
* Description : Abort the DMA Transfer 
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Output      : 
* Author      : Chris_Kyle                         Data : 2020
**********************************************************************************/
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma)
{
    uint32_t lu32_Channel_Index;

#if (USE_FULL_ASSERT == 1)
    /* Check DMA Parameter */
    if (!IS_DMA_ALL_INSTANCE(hdma->Instance))    return HAL_ERROR;
#endif

    /* Get DMA Channel number */
    lu32_Channel_Index = ((uint32_t)(hdma->Instance) - (uint32_t)(DMA_Channel0)) / 0x20;

    /* DMA Channel Disable */
    hdma->Instance->CONFIG &= ~(1 << 0);

    /* Clear TC ERR Falg */
    DMA->INT_TC_CLR  |= (1 << lu32_Channel_Index);
    DMA->INT_ERR_CLR |= (1 << lu32_Channel_Index);

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DMA_GetState
* Description : Returns the DMA state..
* Input       : hdma : pointer to a DMA_HandleTypeDef structure that contains
*                      the configuration information for DMA module
* Output      : 
* Author      :                          Data : 2021
**********************************************************************************/
HAL_StatusTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma)
{
    uint32_t lu32_Channel_Index;
    HAL_StatusTypeDef States = HAL_ERROR;
    
    /* Get DMA Channel number */
    lu32_Channel_Index = ((uint32_t)(hdma->Instance) - (uint32_t)(DMA_Channel0)) / 0x20;

    /* Transfer complete interrupt */
    if (DMA->RAW_INT_TC_STATUS & (1 << lu32_Channel_Index))
    {
        DMA->INT_TC_CLR |= (1 << lu32_Channel_Index);

        States = HAL_OK;
    }
    
    /* Transfer error interrupt */
    if (DMA->RAW_INT_ERR_STATUS & (1 << lu32_Channel_Index))
    {
        DMA->INT_ERR_CLR |= (1 << lu32_Channel_Index);

        States = HAL_ERROR;
    }
    
    return States;
}
