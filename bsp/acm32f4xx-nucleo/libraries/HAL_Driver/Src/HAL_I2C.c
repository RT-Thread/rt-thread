/*
  ******************************************************************************
  * @file    HAL_I2C.c
  * @version V1.0.0
  * @date    2020
  * @brief   I2C HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Inter Integrated Circuit (I2C) peripheral:
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
*/
#include  "ACM32Fxx_HAL.h" 

/* Private functions for I2C */
static HAL_StatusTypeDef I2C_Set_Clock_Speed(I2C_HandleTypeDef *hi2c, uint32_t ClockSpeed);
static HAL_StatusTypeDef I2C_Master_Request_Write(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout);
static HAL_StatusTypeDef I2C_Master_Request_Read(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout);
static HAL_StatusTypeDef I2C_Check_Device_Ready(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout);
static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout);
/************************************************************************
 * function   : HAL_I2C_IRQHandler
 * Description: This function handles I2C interrupt request.
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 ************************************************************************/
__weak void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c)
{
    uint32_t i;
    
    /* Slave ADDR1 Interrupt */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1))
    {
        /* Clear ADDR1 Interrupt Flag */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);

        /* Slave Transmit */
        if (READ_BIT(hi2c->Instance->SR, I2C_SR_SRW))
        {
            i = 1;

            /* Wait for transmission End*/
            while(!READ_BIT(hi2c->Instance->SR, I2C_SR_MTF));
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

            /* BUS BUSY */
            while(READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY))
            {
                if (i >= hi2c->Tx_Size && hi2c->Tx_Size != 0) 
                {
                    break;
                }

                if (READ_BIT(hi2c->Instance->SR, I2C_SR_MTF)) 
                {
                    /* Clear MTF */
                    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

                }

                if (READ_BIT(hi2c->Instance->SR, I2C_SR_TXE))
                {
                    hi2c->Instance->DR = hi2c->Tx_Buffer[i++];
                    hi2c->Tx_Count++;
                }
            }
            
            /* Set Slave machine is DILE */
            hi2c->Slave_TxState = SLAVE_TX_STATE_IDLE;
        }
        /* Slave Receive */
        else 
        {
            i = 0;

            /* Wait for transmission End*/
            while(!READ_BIT(hi2c->Instance->SR, I2C_SR_MTF));
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

            /* BUS BUSY */
            while(READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY))
            {
                /* Receive Data */
                if (READ_BIT(hi2c->Instance->SR, I2C_SR_RXNE))
                {
                    hi2c->Rx_Buffer[i++] = hi2c->Instance->DR;

                    /* Wait for transmission End*/
                    while(!READ_BIT(hi2c->Instance->SR, I2C_SR_MTF));
                    /* Clear MTF */
                    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

                    hi2c->Rx_Count++;

                    if (hi2c->Rx_Size != 0) 
                    {
                        if (i >= hi2c->Rx_Size) 
                        {
                            break;
                        }
                    }
                }
            }
            
            /* Set Slave machine is DILE */
            hi2c->Slave_RxState = SLAVE_RX_STATE_IDLE;
        }

        if (hi2c->Slave_RxState == SLAVE_RX_STATE_IDLE && hi2c->Slave_TxState == SLAVE_TX_STATE_IDLE) 
        {
            /* Disable RX_ADDR1_INT_EN */
            CLEAR_BIT(hi2c->Instance->CR, I2C_CR_RX_ADDR1_INT_EN);
        }
    }
    
    /* STOP Flag Interrupt */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_STOPF))
    {
        /* Clear STOPF Interrupt Flag */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_STOPF);
        
        /* Clear STOPF */
        CLEAR_BIT(hi2c->Instance->CR, I2C_CR_STOPF_INTEN);
        
        if (hi2c->I2C_STOPF_Callback != NULL) 
        {
            hi2c->I2C_STOPF_Callback();
        }
    }
}

/************************************************************************
 * function   : HAL_I2C_MspInit
 * Description: 
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 ************************************************************************/
__weak void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */
    GPIO_InitTypeDef GPIO_Handle; 
    
    /* I2C1 */
    if (hi2c->Instance == I2C1)
    {
        /* Enable Clock */
        System_Module_Enable(EN_I2C1);
        System_Module_Enable(EN_GPIOAB);

        /* I2C1 SDA  PortB Pin7 */
        /* I2C1 SCL  PortB Pin6 */
        GPIO_Handle.Pin            = GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_Handle.Mode           = GPIO_MODE_AF_PP;
        GPIO_Handle.Pull           = GPIO_PULLUP;
        GPIO_Handle.Alternate      = GPIO_FUNCTION_6;
        HAL_GPIO_Init(GPIOB, &GPIO_Handle);
        
        /* Clear Pending Interrupt */
        NVIC_ClearPendingIRQ(I2C1_IRQn);
        
        /* Enable External Interrupt */
        NVIC_EnableIRQ(I2C1_IRQn);
    }
    /* I2C2 */
    else if (hi2c->Instance == I2C2) 
    {
    }
}

/************************************************************************
 * function   : HAL_I2C_MspDeInit
 * Description: 
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 ************************************************************************/
__weak void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */
    GPIO_InitTypeDef GPIO_Handle; 
    
    /* I2C1 */
    if (hi2c->Instance == I2C1)
    {
        /* Disable Clock */
        System_Module_Disable(EN_I2C1);

        /* I2C1 SDA  PortB Pin7 */
        /* I2C1 SCL  PortB Pin6 */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);
        /* Clear Pending Interrupt */
        NVIC_ClearPendingIRQ(I2C1_IRQn);
        
        /* Disable External Interrupt */
        NVIC_DisableIRQ(I2C1_IRQn);
    }
    /* I2C2 */
    else if (hi2c->Instance == I2C2) 
    {
    }
}

/************************************************************************
 * function   : HAL_I2C_Init
 * Description: I2c initial with parameters. 
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)
{
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))              return HAL_ERROR;
    if (!IS_I2C_ALL_MODE(hi2c->Init.I2C_Mode))             return HAL_ERROR;
    if (!IS_I2C_CLOCK_SPEED(hi2c->Init.Clock_Speed))       return HAL_ERROR;
    if (!IS_I2C_TX_AUTO_EN(hi2c->Init.Tx_Auto_En))         return HAL_ERROR;
    if (!IS_I2C_STRETCH_EN(hi2c->Init.No_Stretch_Mode))    return HAL_ERROR;

    /* Disable the selected I2C peripheral */
    CLEAR_BIT(hi2c->Instance->CR, I2C_CR_MEN); 

    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_I2C_MspInit(hi2c);

    switch (hi2c->Init.I2C_Mode)
    {
        /* Master Mode */
        case I2C_MODE_MASTER:
        {
            /* Set Master Mode */
            SET_BIT(hi2c->Instance->CR, I2C_CR_MASTER);
            
            /* Set Clock Speed */
            I2C_Set_Clock_Speed(hi2c, hi2c->Init.Clock_Speed);
            
            /* Set SDA auto change the direction */
            if (hi2c->Init.Tx_Auto_En == TX_AUTO_EN_ENABLE)
                SET_BIT(hi2c->Instance->CR, I2C_CR_TX_AUTO_EN);
            else
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TX_AUTO_EN);
            
            /* Enable the selected I2C peripheral */
            SET_BIT(hi2c->Instance->CR, I2C_CR_MEN);
        }break;
        
        /* Slave Mode */
        case I2C_MODE_SLAVE: 
        {
            SET_BIT(hi2c->Instance->CR, I2C_CR_TXE_SEL);

            /* Set SDA auto change the direction */
            if (hi2c->Init.Tx_Auto_En == TX_AUTO_EN_ENABLE)
                SET_BIT(hi2c->Instance->CR, I2C_CR_TX_AUTO_EN);
            else
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TX_AUTO_EN);
            
            /* Set Clock Stretch Mode */
            if (hi2c->Init.No_Stretch_Mode == NO_STRETCH_MODE_NOSTRETCH)
                SET_BIT(hi2c->Instance->CR, I2C_CR_NOSTRETCH);
            else
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_NOSTRETCH);

            /* Set Address 1 */
            hi2c->Instance->SLAVE_ADDR1 = hi2c->Init.Own_Address;
            
            /* Enable the selected I2C peripheral */
            SET_BIT(hi2c->Instance->CR, I2C_CR_MEN);
        }break;
        
        default: break; 
    }

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_DeInit
 * Description: I2c De-initial with parameters. 
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c)
{
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;
    
    hi2c->Slave_RxState = SLAVE_RX_STATE_IDLE;
    hi2c->Slave_TxState = SLAVE_TX_STATE_IDLE;
    
    HAL_I2C_MspDeInit(hi2c);
    
    hi2c->Tx_Size = 0;
    hi2c->Rx_Size = 0;
    hi2c->Tx_Count = 0;
    hi2c->Rx_Count = 0;
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_Master_Transmit
 * Description: Transmits in master mode an amount of data in blocking mode.
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              DevAddress : Target device address
 *              pData      : Pointer to data buffer
 *              Size       : Amount of data to be sent
 *              Timeout    : Timeout value
************************************************************************/
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t i;
    
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;
    
    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size = Size;
    hi2c->Tx_Count = 0;
    
    /* Send Write Access Request */
    if (I2C_Master_Request_Write(hi2c, DevAddress, 0) == HAL_OK)
    {
        for (i = 0; i < hi2c->Tx_Size; i++)
        {
            /* Wait TXE Flag */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_TXE, RESET, Timeout) != HAL_OK) return HAL_ERROR;
            
            /* Send Data */
            hi2c->Instance->DR = hi2c->Tx_Buffer[hi2c->Tx_Count++];
            
            /* Wait for transmission End*/
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
            
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
            
            /* Get NACK */
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
            {
                /* Generate Stop */
                SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
                
                /* Wait for the bus to idle */
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
                
                return HAL_ERROR;
            }
        }
        
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
        
        /* Wait for the bus to idle */
         if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
    }
    else
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_Master_Receive
 * Description: Transmits in master mode an amount of data in blocking mode.
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              DevAddress : Target device address
 *              pData      : Pointer to data buffer
 *              Size       : Amount of data to be Receive
 *              Timeout    : Timeout value
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t i;

    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;
    
    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size = Size;
    hi2c->Rx_Count = 0;
    
    /* Send Read Access Request */
    if (I2C_Master_Request_Read(hi2c, DevAddress, Timeout) == HAL_OK)
    {
        /* Wait Master Transition receiving state */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_TX_RX_FLAG, RESET, Timeout) != HAL_OK) return HAL_ERROR;
        /* Clear TX_RX_FLAG */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_TX_RX_FLAG);
        /* Generate ACK */
        CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK);

        for (i = 0; i < hi2c->Rx_Size - 1; i++)
        {
            /* Wait RXNE Flag */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RXNE, RESET, Timeout) != HAL_OK) return HAL_ERROR;
            /* Read Data */
            hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
            /* Wait for transmission End*/
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
        }

        /* Prepare for Generate NACK */
        SET_BIT(hi2c->Instance->CR, I2C_CR_TACK);
        /* Prepare for Generate STOP */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);

        /* Wait RXNE Flag */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RXNE, RESET, Timeout) != HAL_OK) return HAL_ERROR;
        /* Read Data */
        hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
        /* Wait for transmission End*/
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
        /* Clear MTF */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
        
        /* Wait for the bus to idle */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;

        /* Generate ACK */
        CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK);
    }
    else
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_Slave_Transmit
 * Description: Transmits in Slave mode an amount of data in blocking mode.
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              pData      : Pointer to data buffer
 *              Size       : Amount of data to be sent
 *              Timeout    : Timeout value
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i = 0;
    
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;
    
    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size = Size;
    hi2c->Tx_Count = 0;

    /* Clear RX_ADDR1 Flag */    
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);  
    /* Match the Address 1 */
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RX_ADDR1, RESET, Timeout) != HAL_OK) return HAL_ERROR;
    /* Clear RX_ADDR1 Flag */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);

    /* Slave Transmit */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_SRW))
    {
        /* BUS BUSY */
        while(READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY))
        {
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_MTF)) 
            {
                /* Clear MTF */
                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

                hi2c->Tx_Count++;
            }

            if (READ_BIT(hi2c->Instance->SR, I2C_SR_TXE))
            {
                if (i < hi2c->Tx_Size || hi2c->Tx_Size == 0) 
                {
                    hi2c->Instance->DR = hi2c->Tx_Buffer[i++];
                }
            }
        }
        hi2c->Instance->SR = READ_REG(hi2c->Instance->SR);
    }
    else
    {
        return HAL_ERROR;
    }

    hi2c->Tx_Count--;
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_Slave_Transmit_IT
 * Description: Transmit in slave mode an amount of data in non-blocking mode with Interrupt
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              pData      : Pointer to data buffer
 *              Size       : Amount of data to be sent
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size)
{
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;

    /* Rx machine is running */
    if (hi2c->Slave_TxState != SLAVE_TX_STATE_IDLE)
        return HAL_ERROR;

    /* Set Slave machine is sending */
    hi2c->Slave_TxState = SLAVE_TX_STATE_SENDING;

    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size   = Size;
    hi2c->Tx_Count = 0;

    CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TXE_SEL);

    hi2c->Instance->DR = hi2c->Tx_Buffer[0];

    hi2c->Tx_Count++;

    /* Clear RX ADDR1 Flag */
    SET_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);
    /* RX ADDR1 Interrupt Enable */
    SET_BIT(hi2c->Instance->CR, I2C_CR_RX_ADDR1_INT_EN);
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_Slave_Receive
 * Description: Receive in Slave mode an amount of data in blocking mode.
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              pData : Pointer to data buffer
 *              Size  : Amount of data to be sent
 *              Timeout    : Timeout value
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i = 0;
    HAL_StatusTypeDef Status;
    
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;;
    
    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size = Size;
    hi2c->Rx_Count = 0;
    
    /* Match the Address 1 */
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RX_ADDR1, RESET, Timeout) != HAL_OK) return HAL_ERROR;
    /* Clear RX_ADDR1 Flag */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);
    
    /* Slave Receive */
    if (!READ_BIT(hi2c->Instance->SR, I2C_SR_SRW))
    {
        /* Wait for transmission End*/
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
        /* Clear MTF */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

        /* BUS BUSY */
        while(READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY))
        {
            /* Receive Data */
            if (READ_BIT(hi2c->Instance->SR, I2C_SR_RXNE))
            {
                hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
                
                /* Wait for transmission End*/
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Clear MTF */
                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

                if (hi2c->Rx_Size != 0) 
                {
                    if (hi2c->Rx_Count >= hi2c->Rx_Size) 
                    {
                        break;
                    }
                }
            }
        }
        
        /* Generate ACK */
        CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK);
        
        hi2c->Instance->SR = READ_REG(hi2c->Instance->SR);
    }
    /* Slave Transmit */
    else 
    {
       return HAL_ERROR;
    }

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_Slave_Receive_IT
 * Description: Receive in slave mode an amount of data in non-blocking mode with Interrupt
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              pData      : Pointer to data buffer
 *              Size       : Amount of data to be sent
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size)
{
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;

    /* Rx machine is running */
    if (hi2c->Slave_RxState != SLAVE_RX_STATE_IDLE)
        return HAL_ERROR;

    /* Set Slave machine is receiving */
    hi2c->Slave_RxState = SLAVE_RX_STATE_RECEIVING;
    
    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size   = Size;
    hi2c->Rx_Count = 0;
    
    /* Clear RX ADDR1 Flag */
    SET_BIT(hi2c->Instance->SR, I2C_SR_RX_ADDR1);
    /* RX ADDR1 Interrupt Enable */
    SET_BIT(hi2c->Instance->CR, I2C_CR_RX_ADDR1_INT_EN);
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_Slave_Receive_DMA
 * Description: Receive in slave mode an amount of data in non-blocking mode with DMA
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              pData      : Pointer to data buffer
 *              Size       : Amount of data to be sent
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size)
{
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;

    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size   = Size;
    hi2c->Rx_Count = Size;

    /* DMA Enable */
    SET_BIT(hi2c->Instance->CR, I2C_CR_DMA_EN);

    /* Clear STOPF Interrupt Flag */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_STOPF);
    /* STOPF Interrupt Enable */
    SET_BIT(hi2c->Instance->CR, I2C_CR_STOPF_INTEN);

    HAL_DMA_Start(hi2c->HDMA_Rx, (uint32_t)&hi2c->Instance->DR, (uint32_t)hi2c->Rx_Buffer, hi2c->Rx_Size);

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_Slave_Transmit_DMA
 * Description: Transmit in slave mode an amount of data in non-blocking mode with DMA
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              pData      : Pointer to data buffer
 *              Size       : Amount of data to be sent
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Size)
{
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;

    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size   = Size;
    hi2c->Tx_Count = Size;
    
    /* Must Set TXE_SEL In DMA Mode !!! */
    SET_BIT(hi2c->Instance->CR, I2C_CR_TXE_SEL);
    /* DMA Enable */
    SET_BIT(hi2c->Instance->CR, I2C_CR_DMA_EN);

    HAL_DMA_Start_IT(hi2c->HDMA_Tx, (uint32_t)hi2c->Tx_Buffer, (uint32_t)&hi2c->Instance->DR, hi2c->Tx_Size);

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_Mem_Write
 * Description: Write an amount of data in blocking mode to a specific memory address
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              DevAddress : Target device address
 *              MemAddress : MemAddress Internal memory address
 *              MemAddSize : MemAddSize Size of internal memory address
 *              pData      : Pointer to data buffer
 *              Size       : Amount of data to be sent
 *              Timeout    : Timeout value
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t i;
    
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;

    hi2c->Tx_Buffer = pData;
    hi2c->Tx_Size   = Size;
    hi2c->Tx_Count = 0;
    
    /* Bus Busy */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY)) 
        return HAL_ERROR;
    
    /* Send Write Access Request */
    if (I2C_Master_Request_Write(hi2c, DevAddress,0) == HAL_OK)
    {
        /* If Memory address size is 8Bit */
        if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
        {
            /* Send Memory Address */
            hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
        }
        /* If Memory address size is 16Bit */ 
        else
        {
            /* Send Memory Address MSB*/
            hi2c->Instance->DR = I2C_MEM_ADD_MSB(MemAddress);
            /* Wait for transmission End*/
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
            /* Send Memory Address LSB*/
            hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
        }
        
        /* Wait for transmission End*/
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
        /* Clear MTF */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
        
        /* Get NACK */
        if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
        {
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
            
            /* Wait for the bus to idle */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK)  return HAL_ERROR;
            
            return HAL_ERROR;
        }
        /* Get ACK */
        else 
        {
            for (i = 0; i < hi2c->Tx_Size; i++)
            {
                /* Wait TXE Flag */
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_TXE, RESET, Timeout)!= HAL_OK)  return HAL_ERROR;
                
                /* Send Data */
                hi2c->Instance->DR = hi2c->Tx_Buffer[hi2c->Tx_Count++];
                
                /* Wait for transmission End*/
                 if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Clear MTF */
                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
                
                /* Get NACK */
                if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
                {
                    /* Generate Stop */
                    SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
                    
                    /* Wait for the bus to idle */
                    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK)  return HAL_ERROR;
                    return HAL_ERROR;
                }
            }
            
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
            
            /* Wait for the bus to idle */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK)  return HAL_ERROR;
            /* Check Device Ready */
            while(I2C_Check_Device_Ready(hi2c, DevAddress, Timeout) != HAL_OK);
        }
    }
    else
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_Mem_Read
 * Description: Read an amount of data in blocking mode to a specific memory address
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              DevAddress : Target device address
 *              MemAddress : MemAddress Internal memory address
 *              MemAddSize : MemAddSize Size of internal memory address
 *              pData      : Pointer to data buffer
 *              Size       : Amount of data to be sent
 *              Timeout    : Timeout value
 ************************************************************************/
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t i;
    
    /* Check I2C Parameter */
    if (!IS_I2C_ALL_INSTANCE(hi2c->Instance))    return HAL_ERROR;

    hi2c->Rx_Buffer = pData;
    hi2c->Rx_Size   = Size;
    hi2c->Rx_Count = 0;
    
    /* Bus Busy */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY)) 
        return HAL_ERROR;
    
    /* Send Write Access Request */
    if (I2C_Master_Request_Write(hi2c, DevAddress,0) == HAL_OK)
    {
        /* If Memory address size is 8Bit */
        if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
        {
            /* Send Memory Address */
            hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
        }
        /* If Memory address size is 16Bit */ 
        else
        {
            /* Send Memory Address MSB*/
            hi2c->Instance->DR = I2C_MEM_ADD_MSB(MemAddress);
            /* Wait for transmission End*/
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
            /* Clear MTF */
            hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
            /* Send Memory Address LSB*/
            hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
        }
        
        /* Wait for transmission End*/
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
        /* Clear MTF */
        hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
        
        /* Get NACK */
        if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
        {
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
            
            /* Wait for the bus to idle */
            if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK)  return HAL_ERROR;
            
            return HAL_ERROR;
        }
        /* Get ACK */
        else
        {
            /* Send Write Read Request */
            if (I2C_Master_Request_Read(hi2c, DevAddress, Timeout) == HAL_OK)
            {
                /* Wait Master Transition receiving state */
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_TX_RX_FLAG, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Clear TX_RX_FLAG */
                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_TX_RX_FLAG);

                /* Generate ACK */
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK);

                for (i = 0; i < hi2c->Rx_Size - 1; i++)
                {
                    /* Wait RXNE Flag */
                    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RXNE, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                    /* Read Data */
                    hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
                    /* Wait for transmission End*/
                    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                    /* Clear MTF */
                    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
                }

                /* Prepare for Generate NACK */
                SET_BIT(hi2c->Instance->CR, I2C_CR_TACK);
                /* Prepare for Generate STOP */
                SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);

                /* Wait RXNE Flag */
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_RXNE, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Read Data */
                hi2c->Rx_Buffer[hi2c->Rx_Count++] = hi2c->Instance->DR;
                /* Wait for transmission End*/
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Clear MTF */
                hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

                /* Wait for the bus to idle */
                if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK)  return HAL_ERROR;
                /* Generate ACK */
                CLEAR_BIT(hi2c->Instance->CR, I2C_CR_TACK);
            }
            else 
            {
            /* Get NACK */
            return HAL_ERROR;
            }
        }
    }
    else
    {
    return HAL_ERROR;
    }

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_I2C_GetSlaveRxState
 * Description: Get Slave Rx State
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 * return     : Slave State
 ************************************************************************/
uint8_t HAL_I2C_GetSlaveRxState(I2C_HandleTypeDef *hi2c)
{
    return hi2c->Slave_RxState;
}

/************************************************************************
 * function   : HAL_I2C_GetSlaveTxState
 * Description: Get Slave Tx State
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 * return     : Slave State
 ************************************************************************/
uint8_t HAL_I2C_GetSlaveTxState(I2C_HandleTypeDef *hi2c)
{
    return hi2c->Slave_TxState;
}

/************************************************************************
 * function   : I2C_Set_Clock_Speed
 * Description: Set I2C Clock Speed
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 *              ClockSpeed: I2C Clock Speed
 ************************************************************************/
static HAL_StatusTypeDef I2C_Set_Clock_Speed(I2C_HandleTypeDef *hi2c, uint32_t ClockSpeed)
{
    uint32_t APB_Clock;

    APB_Clock = System_Get_APBClock();

    hi2c->Instance->CLK_DIV = APB_Clock / (4 * ClockSpeed) - 1;

    return HAL_OK;
}

/**
  * @brief  This function handles I2C Communication Timeout.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for I2C module
  * @param  Flag specifies the I2C flag to check.
  * @param  Status The new Flag status (SET or RESET).
  * @param  Timeout Timeout duration
  * @param  Tickstart Tick start value
  * @retval HAL status
  */
static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout)
{
    __IO uint32_t lu32_Timeout;
    /* have no timeout */
    if (Timeout == 0) 
    {
        while (__HAL_I2C_GET_FLAG(hi2c, Flag)==Status);
    }
    else 
    {
        lu32_Timeout = Timeout * 0xFF;
            
        while (__HAL_I2C_GET_FLAG(hi2c, Flag)==Status)
        {
            if (lu32_Timeout-- == 0) 
            {
                return HAL_ERROR;
            }
        }
    }
    return HAL_OK;
}
/************************************************************************
 * function   : I2C_Master_Request_Write
 * Description: I2C Write Access Request
 * input      : hi2c  : pointer to a I2C_HandleTypeDef structure 
 *              DevAddress: Device address
 *              Timeout: Timeout value
 ************************************************************************/
static HAL_StatusTypeDef I2C_Master_Request_Write(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout)
{
    /* Generate Start */
    SET_BIT(hi2c->Instance->CR, I2C_CR_START);

    /* Clear MTF, To Prevent Errors */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

    /* Send Device Address */
    hi2c->Instance->DR = DevAddress & 0xFE;

    /* Wait for transmission End*/
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
    /* Clear MTF */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);

    /* Get NACK */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
    {
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
        
        /* Wait for the bus to idle */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
        
        return HAL_ERROR;
    }
    /* Get ACK */
    else 
    {
        return HAL_OK;
    }
}

/************************************************************************
 * function   : I2C_Master_Request_Read
 * Description: I2C Read Access Request
 * input      : hi2c  : pointer to a I2C_HandleTypeDef structure 
 *              DevAddress: Device address
 *              Timeout: Timeout value
 ************************************************************************/
static HAL_StatusTypeDef I2C_Master_Request_Read(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout)
{
    /* Generate Start */
    SET_BIT(hi2c->Instance->CR, I2C_CR_START);

    /* Clear MTF, To Prevent Errors */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
    
    /* Send Device Address */
    hi2c->Instance->DR = DevAddress | 0x01;
    
    /* Wait for transmission End */
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
    /* Clear MTF */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
    
    /* Get NACK */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
    {
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
        
        /* Wait for the bus to idle */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
        
        return HAL_ERROR;
    }
    /* Get ACK */
    else 
    {
        return HAL_OK;
    }
}

/************************************************************************
 * function   : I2C_Check_Device_Ready
 * Description: Check Device Ready
 * input      : hi2c  : pointer to a I2C_HandleTypeDef structure 
 *              DevAddress: Device address
 *              Timeout: Timeout value
 ************************************************************************/
static HAL_StatusTypeDef I2C_Check_Device_Ready(I2C_HandleTypeDef *hi2c, uint8_t DevAddress, uint32_t Timeout)
{
    /* Bus Busy */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_BUS_BUSY)) 
        return HAL_ERROR;

    /* Generate Start */
    SET_BIT(hi2c->Instance->CR, I2C_CR_START);
    
    /* Send Device Address */
    hi2c->Instance->DR = DevAddress;
    
    /* Wait for transmission End */
    if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_MTF, RESET, Timeout) != HAL_OK) return HAL_ERROR;
    /* Clear MTF */
    hi2c->Instance->SR = READ_BIT(hi2c->Instance->SR, I2C_SR_MTF);
    
    /* Get NACK */
    if (READ_BIT(hi2c->Instance->SR, I2C_SR_RACK))
    {
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
        
        /* Wait for the bus to idle */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
        
        return HAL_ERROR;
    }
    /* Get ACK */
    else 
    {
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR, I2C_CR_STOP);
        
        /* Wait for the bus to idle */
        if(I2C_WaitOnFlagUntilTimeout(hi2c, I2C_SR_BUS_BUSY, SET, Timeout) != HAL_OK) return HAL_ERROR;
        
        return HAL_OK;
    }
}
