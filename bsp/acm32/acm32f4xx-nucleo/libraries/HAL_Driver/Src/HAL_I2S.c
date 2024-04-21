/*
  ******************************************************************************
  * @file    HAL_I2S.c
  * @version V1.0.0
  * @date    2020
  * @brief   I2S HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Integrated Interchip Sound (I2S) peripheral:
  *           + Initialization functions
  *           + IO operation functions
  *           + Peripheral State 
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

/*********************************************************************************
* Function    : HAL_I2S_IRQHandler
* Description : This function handles I2S interrupt request.
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
void HAL_I2S_IRQHandler(I2S_HandleTypeDef *hi2s)
{
    /* Tx Buffer empty */
    if (hi2s->Instance->STATUS & I2S_STATUS_TXBE) 
    {
        if (hi2s->u32_Tx_Count < hi2s->u32_Tx_Size) 
        {
            hi2s->Instance->DAT = hi2s->u32_Tx_Buffer[hi2s->u32_Tx_Count++];
        }
        else 
        {
            hi2s->Instance->IE &= ~I2S_DIE_TBEIE;
            
            hi2s->I2S_Status = HAL_I2S_STATE_READY;
        }
    }
    
    /* Rx Buffer not empty */
    if (hi2s->Instance->STATUS & I2S_STATUS_RXBNE) 
    {
        if (hi2s->u32_Rx_Count < hi2s->u32_Rx_Size) 
        {
            hi2s->u32_Tx_Buffer[hi2s->u32_Rx_Count++] = hi2s->Instance->DAT;
        }
        else 
        {
            /* Disable I2S */
            hi2s->Instance->CTL &= ~I2S_CTL_I2SEN;
    
            hi2s->Instance->IE &= ~I2S_DIE_RBNEIE;

            hi2s->I2S_Status = HAL_I2S_STATE_READY;
        }
    }
}

/*********************************************************************************
* Function    : HAL_I2S_MspInit
* Description : 
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
__weak void HAL_I2S_MspInit(I2S_HandleTypeDef *hi2s)
{
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */
    GPIO_InitTypeDef GPIO_Handle; 
        
    if (hi2s->Instance == I2S1) 
    {
        /* Enable Clock */
        System_Module_Enable(EN_I2S1);
        System_Module_Enable(EN_GPIOAB);

        /* I2S1 WS   PortA Pin4 */
        /* I2S1 CLK  PortA Pin5 */
        /* I2S1 MCK  PortA Pin6 */
        /* I2S1 SD   PortA Pin7 */
        GPIO_Handle.Pin       = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_Handle.Mode      = GPIO_MODE_AF_PP;
        GPIO_Handle.Pull      = GPIO_PULLUP;
        GPIO_Handle.Alternate = GPIO_FUNCTION_8;
        HAL_GPIO_Init(GPIOA, &GPIO_Handle);

        /* Clear Pending Interrupt */
        NVIC_ClearPendingIRQ(I2S_IRQn);
        
        /* Enable External Interrupt */
        NVIC_EnableIRQ(I2S_IRQn);
    }
}

/*********************************************************************************
* Function    : HAL_I2S_MspDeInit
* Description : 
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
__weak void HAL_I2S_MspDeInit(I2S_HandleTypeDef *hi2s)
{
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */
    if (hi2s->Instance == I2S1) 
    {
        /* I2S1 WS   PortA Pin4 */
        /* I2S1 CLK  PortA Pin5 */
        /* I2S1 MCK  PortA Pin6 */
        /* I2S1 SD   PortA Pin7 */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

        /* Clear Pending Interrupt */
        NVIC_ClearPendingIRQ(I2S_IRQn);
        
        /* Disable External Interrupt */
        NVIC_DisableIRQ(I2S_IRQn);
    }
}

/*********************************************************************************
* Function    : HAL_I2S_Init
* Description : Initializes the I2S according to the specified parameters
*               in the I2S_InitTypeDef and create the associated handle.
* Input       : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                     the configuration information for I2S module
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_I2S_Init(I2S_HandleTypeDef *hi2s)
{
#if (USE_FULL_ASSERT == 1)
    /* Check I2S Parameter */
    if (!IS_I2S_MODE(hi2s->Init.u32_Mode))                 return HAL_ERROR;
    if (!IS_I2S_STANDARD(hi2s->Init.u32_Standard))         return HAL_ERROR;
    if (!IS_I2S_DATAFORMAT(hi2s->Init.u32_DataFormat))     return HAL_ERROR;
    if (!IS_I2S_MCLK_OUTPUT(hi2s->Init.u32_MCLKOutput))    return HAL_ERROR;
    if (!IS_I2S_MCLK_CPOL(hi2s->Init.u32_CPOL))            return HAL_ERROR;
    if (!IS_I2S_OF(hi2s->Init.u32_FreqOF))                 return HAL_ERROR;
    if (!IS_I2S_DIV(hi2s->Init.u32_FreqDIV))               return HAL_ERROR;
#endif

    /* Init the low level hardware : GPIO, CLOCK, CORTEX...etc */
    HAL_I2S_MspInit(hi2s);
    
    /* Clear Config */
    hi2s->Instance->CTL = 0x00000000;
    hi2s->Instance->PSC = 0x00000000;

    /* Mode、Standard、CPOL、Dataformat */
    hi2s->Instance->CTL = hi2s->Init.u32_Mode | hi2s->Init.u32_Standard | hi2s->Init.u32_CPOL | hi2s->Init.u32_DataFormat;
    /* Frequency */
    hi2s->Instance->PSC = hi2s->Init.u32_MCLKOutput | hi2s->Init.u32_FreqOF | hi2s->Init.u32_FreqDIV;

    /* I2S Enable */
    if (hi2s->Init.u32_Mode != I2S_MODE_MASTER_RX) 
    {
        hi2s->Instance->CTL |= I2S_CTL_I2SEN;
    }
    
    /* I2S Status ready */
    hi2s->I2S_Status = HAL_I2S_STATE_READY;

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_I2S_DeInit
* Description : DeInitializes the I2S peripheral
* Input       : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                     the configuration information for I2S module
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_I2S_DeInit(I2S_HandleTypeDef *hi2s)
{
    /* Check the I2S handle allocation */
    if (hi2s == NULL)
    {
        return HAL_ERROR;
    }

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
    HAL_I2S_MspDeInit(hi2s);
    
    System_Module_Reset(RST_I2S1);

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_I2S_Transmit
* Description : Transmit an amount of data in blocking mode
* Input       : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                     the configuration information for I2S module
* Input       : fp32_Data: 32-bit pointer to data buffer.
* Input       : Size: number of data sample to be sent
* Input       : fu32_Timeout: Timeout duration
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_I2S_Transmit(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size, uint32_t fu32_Timeout)
{
    uint32_t i;

    uint32_t lu32_Timeout;

    /* Parameter Check */
    if ((fp32_Data == NULL) || (fu32_Size == 0U))
    {
        return  HAL_ERROR;
    }
    
    /* I2S Ready? */
    if (hi2s->I2S_Status != HAL_I2S_STATE_READY) 
    {
        return  HAL_BUSY;
    }
    
    hi2s->I2S_Status = HAL_I2S_STATE_BUSY_TX;
    
    /* transmit */
    for (i = 0; i < fu32_Size; i++)
    {
        hi2s->Instance->DAT = fp32_Data[i];

        /* have no timeout */
        if (fu32_Timeout == 0) 
        {
            while(!(hi2s->Instance->STATUS & I2S_STATUS_TXBE));
        }
        else 
        {
            lu32_Timeout = fu32_Timeout * 0xFF;

            while(!(hi2s->Instance->STATUS & I2S_STATUS_TXBE))
            {
                if (lu32_Timeout-- == 0) 
                {
                    hi2s->I2S_Status = HAL_I2S_STATE_READY;
                    
                    return HAL_TIMEOUT;
                }
            }
        }
    }

    /* Wait for the last Byte */
    while (hi2s->Instance->STATUS & I2S_STATUS_TRANS);
    
    hi2s->I2S_Status = HAL_I2S_STATE_READY;

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_I2S_Receive
* Description : Receive an amount of data in blocking mode
* Input       : hi2s pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module
* Input       : fp32_Data: a 32-bit pointer to data buffer.
* Input       : Size: number of data sample to be Receive
* Input       : fu32_Timeout: Timeout duration
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_I2S_Receive(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size, uint32_t fu32_Timeout)
{
    uint32_t i;

    uint32_t lu32_Timeout;
    
    /* Parameter Check */
    if ((fp32_Data == NULL) || (fu32_Size == 0U))
    {
        return  HAL_ERROR;
    }

    /* I2S Ready? */
    if (hi2s->I2S_Status != HAL_I2S_STATE_READY) 
    {
        return  HAL_BUSY;
    }

    hi2s->I2S_Status = HAL_I2S_STATE_BUSY_RX;

    /* I2S Enable */
    hi2s->Instance->CTL |= I2S_CTL_I2SEN;
    
    /* Receive */
    for (i = 0; i < fu32_Size; i++)
    {
        /* have no timeout */
        if (fu32_Timeout == 0) 
        {
            while(!(hi2s->Instance->STATUS & I2S_STATUS_RXBNE));
            fp32_Data[i] = hi2s->Instance->DAT;
        }
        else 
        {
            lu32_Timeout = fu32_Timeout * 0xFF;

            while(!(hi2s->Instance->STATUS & I2S_STATUS_RXBNE))
            {
                if (lu32_Timeout-- == 0) 
                {
                    hi2s->I2S_Status = HAL_I2S_STATE_READY;

                    return HAL_TIMEOUT;
                }
            }

            fp32_Data[i] = hi2s->Instance->DAT;
        }
    }

    /* Disable I2S */
    hi2s->Instance->CTL &= ~I2S_CTL_I2SEN;

    hi2s->I2S_Status = HAL_I2S_STATE_READY;

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_I2S_Transmit_IT
* Description : Transmit an amount of data in non-blocking mode with Interrupt
* Input       : hi2s pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module
* Input       : fp32_Data: a 32-bit pointer to data buffer.
* Input       : Size: number of data sample to be send
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_I2S_Transmit_IT(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size)
{
    /* Parameter Check */
    if ((fp32_Data == NULL) || (fu32_Size == 0U))
    {
        return  HAL_ERROR;
    }

    /* I2S Ready? */
    if (hi2s->I2S_Status != HAL_I2S_STATE_READY) 
    {
        return  HAL_BUSY;
    }

    hi2s->I2S_Status = HAL_I2S_STATE_BUSY_TX;
    
    hi2s->u32_Tx_Buffer = fp32_Data;
    hi2s->u32_Tx_Size   = fu32_Size;
    hi2s->u32_Tx_Count  = 0;
    
    hi2s->Instance->IE |= I2S_DIE_TBEIE;
    
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_I2S_Receive_IT
* Description : Receive an amount of data in non-blocking mode with Interrupt
* Input       : hi2s pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module
* Input       : fp32_Data: a 32-bit pointer to data buffer.
* Input       : Size: number of data sample to be Receive
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_I2S_Receive_IT(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size)
{
    uint32_t lu32_Tempvalue;
    
    /* Parameter Check */
    if ((fp32_Data == NULL) || (fu32_Size == 0U))
    {
        return  HAL_ERROR;
    }

    /* I2S Ready? */
    if (hi2s->I2S_Status != HAL_I2S_STATE_READY) 
    {
        return  HAL_BUSY;
    }
    
    /* Clear Rx Buffer */
    while (hi2s->Instance->STATUS & I2S_STATUS_RXBNE) 
    {
        lu32_Tempvalue = hi2s->Instance->DAT;
    }

    hi2s->I2S_Status = HAL_I2S_STATE_BUSY_RX;

    hi2s->u32_Rx_Buffer = fp32_Data;
    hi2s->u32_Rx_Size   = fu32_Size;
    hi2s->u32_Rx_Count  = 0;

    hi2s->Instance->IE |= I2S_DIE_RBNEIE;

    /* I2S Enable */
    hi2s->Instance->CTL |= I2S_CTL_I2SEN;

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_I2S_Transmit_DMA
* Description : Transmit an amount of data in non-blocking mode with DMA
* Input       : hi2s: pointer to a I2S_HandleTypeDef structure that contains
*                     the configuration information for I2S module
* Input       : fp32_Data: 32-bit pointer to data buffer.
* Input       : Size: number of data sample to be sent
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_I2S_Transmit_DMA(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size)
{
    /* Parameter Check */
    if ((fp32_Data == NULL) || (fu32_Size == 0U))
    {
        return  HAL_ERROR;
    }

    /* DMA transfer complete */
    if (!(hi2s->I2S_Status & I2S_STATUS_TRANS))
    {
        hi2s->I2S_Status = HAL_I2S_STATE_READY;
    }

    /* I2S Ready? */
    if (hi2s->I2S_Status != HAL_I2S_STATE_READY) 
    {
        return  HAL_BUSY;
    }

    hi2s->I2S_Status = HAL_I2S_STATE_BUSY_TX;

    hi2s->Instance->IE |= I2S_DIE_DMATEN;

    HAL_DMA_Start_IT(hi2s->HDMA_Tx, (uint32_t)fp32_Data, (uint32_t)&hi2s->Instance->DAT, fu32_Size);
    
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_I2S_Receive_DMA
* Description : Receive an amount of data in non-blocking mode with DMA
* Input       : hi2s pointer to a I2S_HandleTypeDef structure that contains
*               the configuration information for I2S module
* Input       : fp32_Data: a 32-bit pointer to data buffer.
* Input       : Size: number of data sample to be Receive
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_I2S_Receive_DMA(I2S_HandleTypeDef *hi2s, uint32_t *fp32_Data, uint32_t fu32_Size)
{
    /* Parameter Check */
    if ((fp32_Data == NULL) || (fu32_Size == 0U))
    {
        return  HAL_ERROR;
    }

    /* DMA transfer complete */
    if (!(hi2s->I2S_Status & I2S_STATUS_TRANS))
    {
        hi2s->I2S_Status = HAL_I2S_STATE_READY;
    }

    /* I2S Ready? */
    if (hi2s->I2S_Status != HAL_I2S_STATE_READY) 
    {
        return  HAL_BUSY;
    }

    hi2s->I2S_Status = HAL_I2S_STATE_BUSY_RX;

    hi2s->Instance->IE |= I2S_DIE_DMATEN;

    HAL_DMA_Start_IT(hi2s->HDMA_Rx, (uint32_t)&hi2s->Instance->DAT, (uint32_t)fp32_Data, fu32_Size);

    return HAL_OK;
}

