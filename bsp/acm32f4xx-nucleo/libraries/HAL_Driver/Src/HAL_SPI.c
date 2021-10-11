/*
  ******************************************************************************
  * @file    HAL_Spi.c
  * @version V1.0.0
  * @date    2020
  * @brief   SPI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Serial Peripheral Interface (SPI) peripheral.
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
*/
#include  "ACM32Fxx_HAL.h" 

#define SPI_RX_TIMEOUT    2000
#define SPI_TX_DMA_TIMEOUT    2000
volatile uint32_t lu32_ReceiveTimeOut = SPI_RX_TIMEOUT;
volatile uint32_t lu32_TX_DMA_TimeOut = SPI_TX_DMA_TIMEOUT;
/************************************************************************
 * function   : HAL_SPI_IRQHandler
 * Description: This function handles SPI interrupt request.
 * input      : hspi : pointer to a SPI_HandleTypeDef structure that contains
 *                     the configuration information for SPI module
 ************************************************************************/
__weak void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi)
{
    uint8_t lu8_TempValue = 0;
    
    uint32_t lu32_Length = 0;
    
    /* 
      NOTE : This function should be modified by the user.
    */    
    if ( (hspi->Instance->STATUS & SPI_STATUS_RX_NOT_EMPTY) && ((hspi->Instance->IE) & SPI_STATUS_RX_NOT_EMPTY) )
    {
        /* In master mode */
        if (hspi->Instance->CTL & SPI_CTL_MST_MODE)
        {
            while (hspi->Instance->STATUS & SPI_STATUS_RX_NOT_EMPTY)
            {
                hspi->Rx_Buffer[hspi->Rx_Count++] = hspi->Instance->DAT;
                
                if (hspi->Rx_Count >= hspi->Rx_Size) 
                {
                    /* Wait Transmit Done */
                    while (!(hspi->Instance->STATUS & SPI_STATUS_RX_BATCH_DONE));
                    
                    /* Clear Batch Done Flag  */
                    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_RX_BATCH_DONE);
                    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);

                    /* Rx Disable */
                    hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);

                    /* Receive End */
                    hspi->Instance->CS &= (~SPI_CS_CS0);


                    /* Disable Rx Not Empty Interrupt */
                    CLEAR_BIT(hspi->Instance->IE, SPI_STATUS_RX_NOT_EMPTY);
                    
                    if(hspi->Instance == SPI1)
                        NVIC_ClearPendingIRQ(SPI1_IRQn);
                    else if(hspi->Instance == SPI2)
                        NVIC_ClearPendingIRQ(SPI2_IRQn);
                    else if(hspi->Instance == SPI3)
                        NVIC_ClearPendingIRQ(SPI3_IRQn);
                    else if(hspi->Instance == SPI4)
                        NVIC_ClearPendingIRQ(SPI4_IRQn);
                    
                    /* Clear Batch Done Flag  */
                    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_RX_BATCH_DONE);
                    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);
                    
                    /* Set machine is DILE */
                    hspi->RxState = SPI_RX_STATE_IDLE;
                }
            }
        }
        /* In Slave mode */
        else 
        {
            while ((hspi->Rx_Count < hspi->Rx_Size) && (lu32_ReceiveTimeOut > 0) )   
            {
                if (hspi->Instance->STATUS & SPI_STATUS_RX_NOT_EMPTY) 
                {
                    hspi->Rx_Buffer[hspi->Rx_Count++] = hspi->Instance->DAT;
                    lu32_ReceiveTimeOut = SPI_RX_TIMEOUT;       //If recieve data, Reset the timeout value  
                }
                else
                {
                    lu32_ReceiveTimeOut--;   
                }
                
            }

            /* Rx Disable */
            hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);
            
            /* Disable Rx Not Empty Interrupt */
            CLEAR_BIT(hspi->Instance->IE, SPI_STATUS_RX_NOT_EMPTY);
            
            if(hspi->Instance == SPI1)
                NVIC_ClearPendingIRQ(SPI1_IRQn);
            else if(hspi->Instance == SPI2)
                NVIC_ClearPendingIRQ(SPI2_IRQn);
            else if(hspi->Instance == SPI3)
                NVIC_ClearPendingIRQ(SPI3_IRQn);
            else if(hspi->Instance == SPI4)
                NVIC_ClearPendingIRQ(SPI4_IRQn);
            
            /* Clear Batch Done Flag  */
            SET_BIT(hspi->Instance->STATUS, SPI_STATUS_RX_BATCH_DONE);
            SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);
            
            /* Set machine is DILE */
            hspi->RxState = SPI_RX_STATE_IDLE;
        }
    }
    
    if ( (hspi->Instance->STATUS & SPI_STATUS_TX_FIFO_HALF_EMPTY) && ((hspi->Instance->IE) & SPI_IE_TX_FIFO_HALF_EMPTY_EN) )
    {
        while (hspi->Tx_Count < hspi->Tx_Size)   
        {
            if (!(hspi->Instance->STATUS & SPI_STATUS_TX_FIFO_FULL))
            {
                hspi->Instance->DAT = hspi->Tx_Buffer[hspi->Tx_Count++];
            }
            else
            {
                break;   
            }
            
        }
        /* Clear Tx FIFO half empty Flag  */
        SET_BIT(hspi->Instance->STATUS, SPI_STATUS_TX_FIFO_HALF_EMPTY);
        if(hspi->Tx_Count == hspi->Tx_Size)
        {
            /* Disable Tx FIFO half empty Interrupt  */
            CLEAR_BIT(hspi->Instance->IE, SPI_IE_TX_FIFO_HALF_EMPTY_EN);
        }                
    }
    if ((hspi->Instance->STATUS & SPI_STATUS_TX_BATCH_DONE) && ((hspi->Instance->IE) & SPI_IE_TX_BATCH_DONE_EN) )     
    {
        /* Clear Batch Done Flag  */
        SET_BIT(hspi->Instance->STATUS, SPI_STATUS_TX_BATCH_DONE);
        SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);

        /* Disable TX Batch Done Interrupt */
        CLEAR_BIT(hspi->Instance->IE, SPI_STATUS_TX_BATCH_DONE);
        /* Disable Tx FIFO half empty Interrupt  */
        CLEAR_BIT(hspi->Instance->IE, SPI_IE_TX_FIFO_HALF_EMPTY_EN);
            
        if(hspi->Instance == SPI1)
            NVIC_ClearPendingIRQ(SPI1_IRQn);
        else if(hspi->Instance == SPI2)
            NVIC_ClearPendingIRQ(SPI2_IRQn);
        else if(hspi->Instance == SPI3)
            NVIC_ClearPendingIRQ(SPI3_IRQn);
        else if(hspi->Instance == SPI4)
            NVIC_ClearPendingIRQ(SPI4_IRQn);
        
        lu32_TX_DMA_TimeOut = SPI_TX_DMA_TIMEOUT;   
        while (hspi->Instance->STATUS & SPI_STATUS_TX_BUSY)
        {
             lu32_TX_DMA_TimeOut--;
             if(0 == lu32_TX_DMA_TimeOut) 
             {
                 break;  
             }
        }

        /* Tx Disable */
        hspi->Instance->TX_CTL &= (~SPI_TX_CTL_EN);  
        hspi->Instance->TX_CTL &= (~SPI_TX_CTL_DMA_REQ_EN);         
        
        if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
        {
            /* Transmit End */
            hspi->Instance->CS &= (~SPI_CS_CS0);
        }
        
        /* Tx Disable */
        hspi->Instance->TX_CTL &= (~SPI_TX_CTL_EN);

        hspi->TxState = SPI_TX_STATE_IDLE;
    }

    if ( (hspi->Instance->STATUS & SPI_STATUS_RX_BATCH_DONE) && ((hspi->Instance->IE) & SPI_STATUS_RX_BATCH_DONE) )         
    {
        /* Clear Batch Done Flag  */
        SET_BIT(hspi->Instance->STATUS, SPI_STATUS_RX_BATCH_DONE);
        SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);

        /* Disable RX Batch Done Interrupt */
        CLEAR_BIT(hspi->Instance->IE, SPI_STATUS_RX_BATCH_DONE);

        if(hspi->Instance == SPI1)
            NVIC_ClearPendingIRQ(SPI1_IRQn);
        else if(hspi->Instance == SPI2)
            NVIC_ClearPendingIRQ(SPI2_IRQn);
        else if(hspi->Instance == SPI3)
            NVIC_ClearPendingIRQ(SPI3_IRQn);
        else if(hspi->Instance == SPI4)
            NVIC_ClearPendingIRQ(SPI4_IRQn);

        /* Rx Disable */
        hspi->Instance->RX_CTL &= (~SPI_RX_CTL_DMA_REQ_EN); 
        hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);

        if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
        {
            /* Receive End */
            hspi->Instance->CS &= (~SPI_CS_CS0);
        }

        hspi->RxState = SPI_RX_STATE_IDLE;
    }
}

/************************************************************************
 * function   : HAL_SPI_MspInit
 * Description: 
 * input      : hspi : pointer to a SPI_HandleTypeDef structure that contains
 *                     the configuration information for SPI module
 ************************************************************************/
__weak void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */
    GPIO_InitTypeDef GPIO_Handle; 
    
    /* SPI1 */
    if (hspi->Instance == SPI1)
    {
    }
    /* SPI2 */
    else if (hspi->Instance == SPI2) 
    {
    }
    /* SPI3 */
    else if (hspi->Instance == SPI3)
    {
        /* Enable Clock */
        System_Module_Enable(EN_SPI3);
        
        /* SPI3 CS   PortA Pin15 */
        /* SPI3 CLK  PortC Pin10 */
        /* SPI3 MOSI PortC Pin12 */
        /* SPI3 MISO PortC Pin11 */
        GPIO_Handle.Pin            = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
        GPIO_Handle.Mode           = GPIO_MODE_AF_PP;
        GPIO_Handle.Pull           = GPIO_PULLUP;
        GPIO_Handle.Alternate      = GPIO_FUNCTION_3;
        HAL_GPIO_Init(GPIOC, &GPIO_Handle);

        GPIO_Handle.Pin            = GPIO_PIN_15;
        GPIO_Handle.Mode           = GPIO_MODE_AF_PP;
        GPIO_Handle.Pull           = GPIO_PULLUP;
        GPIO_Handle.Alternate      = GPIO_FUNCTION_5;
        HAL_GPIO_Init(GPIOA, &GPIO_Handle);
        
        if (hspi->Init.X_Mode == SPI_4X_MODE) 
        {
            /* SPI3 IO3 PortC Pin8 */
            /* SPI3 IO2 PortC Pin9 */
            GPIO_Handle.Pin            = GPIO_PIN_8 | GPIO_PIN_9;
            GPIO_Handle.Mode           = GPIO_MODE_AF_PP;
            GPIO_Handle.Pull           = GPIO_PULLUP;
            GPIO_Handle.Alternate       = GPIO_FUNCTION_3;
            HAL_GPIO_Init(GPIOC, &GPIO_Handle);
        }
        
        /* Clear Pending Interrupt */
        NVIC_ClearPendingIRQ(SPI3_IRQn);
        
        /* Enable External Interrupt */
        NVIC_EnableIRQ(SPI3_IRQn);
    }
}

/************************************************************************
 * function   : HAL_SPI_MspDeInit
 * Description: SPI De-Initialize the SPI clock, GPIO, IRQ.
 * input      : hspi : pointer to a SPI_HandleTypeDef structure that contains
 *                     the configuration information for SPI module
 ************************************************************************/
__weak void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */
    
    /* SPI1 */
    if (hspi->Instance == SPI1)
    {
    }
    /* SPI2 */
    else if (hspi->Instance == SPI2) 
    {
    }
    /* SPI3 */
    else if (hspi->Instance == SPI3)
    {
        /* Disable Clock */
        System_Module_Disable(EN_SPI3);
        
        /* Reset the used GPIO to analog */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_15);

        if (hspi->Init.X_Mode == SPI_4X_MODE) 
        {
            HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8 | GPIO_PIN_9);
        }
        
        /* Clear Pending Interrupt */
        NVIC_ClearPendingIRQ(SPI3_IRQn);
        
        /* Disable External Interrupt */
        NVIC_DisableIRQ(SPI3_IRQn);
    }
}

/************************************************************************
 * function   : HAL_SPI_Init 
 * Description: SPI initial with parameters. 
 * input      : hspi : pointer to a SPI_HandleTypeDef structure that contains
 *                     the configuration information for SPI module
 ************************************************************************/
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
{
    /* Check SPI Parameter */
    if (!IS_SPI_ALL_INSTANCE(hspi->Instance))                         return HAL_ERROR;
    if (!IS_SPI_ALL_MODE(hspi->Init.SPI_Mode))                        return HAL_ERROR;
    if (!IS_SPI_WORK_MODE(hspi->Init.SPI_Work_Mode))                  return HAL_ERROR;
    if (!IS_SPI_X_MODE(hspi->Init.X_Mode))                            return HAL_ERROR;
    if (!IS_SPI_FIRST_BIT(hspi->Init.First_Bit))                      return HAL_ERROR;
    if (!IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRate_Prescaler))    return HAL_ERROR;

    /* Init the low level hardware : GPIO, CLOCK, NVIC */
    HAL_SPI_MspInit(hspi);
    
    /* Automatic change direction */
    hspi->Instance->CTL |= (SPI_CTL_IO_MODE);
    
    /* Set SPI Work mode */
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        SET_BIT(hspi->Instance->CTL, SPI_CTL_MST_MODE);
    }
    else 
    {
        CLEAR_BIT(hspi->Instance->CTL, SPI_CTL_MST_MODE);
        
        hspi->Instance->BATCH = (hspi->Instance->BATCH & (~0x000FFFFFU)) | (1 << 0);
        
        hspi->Instance->TX_CTL |= SPI_TX_CTL_MODE | (0x88 << 8);  // dummy data = 0x88  
        
        if (hspi->Init.X_Mode != SPI_1X_MODE) 
        {
            hspi->Instance->CTL |= SPI_CTL_SFILTER;
        }
        
        /* Slave Alternate Enable */
        hspi->Instance->CTL |= SPI_CTL_SLAVE_EN;
        
        /* Slave Mode Enable Rx By Default */
        hspi->Instance->RX_CTL |= SPI_RX_CTL_EN;
    }

    /* Set SPI First Bit */
    if (hspi->Init.First_Bit == SPI_FIRSTBIT_LSB)
        SET_BIT(hspi->Instance->CTL, SPI_CTL_LSB_FIRST);
    else
        CLEAR_BIT(hspi->Instance->CTL, SPI_CTL_LSB_FIRST);

    /* Set SPI Work Mode */
    hspi->Instance->CTL = ((hspi->Instance->CTL) & (~(SPI_CTL_CPHA | SPI_CTL_CPOL))) | (hspi->Init.SPI_Work_Mode);
    
    /* Set SPI X_Mode */
    hspi->Instance->CTL = ((hspi->Instance->CTL) & (~SPI_CTL_X_MODE)) | (hspi->Init.X_Mode);

    /* Set SPI BaudRate Prescaler */
    hspi->Instance->BAUD = ((hspi->Instance->BAUD) & (~0x0000FFFF)) | (hspi->Init.BaudRate_Prescaler);

    /* Disable All Interrupt */
    hspi->Instance->IE = 0x00000000;

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_SPI_DeInit 
 * Description: De-Initialize the SPI peripheral. 
 * input      : hspi : pointer to a SPI_HandleTypeDef structure that contains
 *                     the configuration information for SPI module
 * return     : HAL_StatusTypeDef : HAL status
 ************************************************************************/
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi)
{
    /* Check the SPI handle allocation */
    if (hspi == NULL)
    {
    return HAL_ERROR;
    }

    /* Check SPI Instance parameter */
    if (!IS_SPI_ALL_INSTANCE(hspi->Instance))   return HAL_ERROR;

    hspi->RxState = SPI_RX_STATE_IDLE;
    hspi->TxState = SPI_TX_STATE_IDLE;

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
    HAL_SPI_MspDeInit(hspi);

    hspi->Rx_Size = 0;
    hspi->Tx_Size = 0;
    hspi->Rx_Count = 0;
    hspi->Tx_Count = 0;

    return HAL_OK;
}

/************************************************************************
 * function   : HAL_SPI_Transmit
 * Description: Transmits an amount of data in blocking mode.
 * input      : hspi  : pointer to a SPI_HandleTypeDef structure that contains
 *                      the configuration information for SPI module
 *              pData : Pointer to data buffer
 *              Size  : Amount of data to be sent
 *              Timeout : Transmit Timeout
 ************************************************************************/
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i;
    HAL_StatusTypeDef Status = HAL_OK;
    __IO uint32_t uiTimeout;

    /* Check SPI Parameter */
    if (!IS_SPI_ALL_INSTANCE(hspi->Instance))    return HAL_ERROR;
    if(!Size)    return HAL_ERROR;
    if (pData == NULL)    return HAL_ERROR;
    
    hspi->Tx_Count = 0;
    hspi->Tx_Size = Size;
    hspi->Tx_Buffer = pData;
    
    uiTimeout = Timeout;

    /* Clear Batch Done Flag  */
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_TX_BATCH_DONE);
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);
    
    /* Clear TX FIFO */
    SET_BIT(hspi->Instance->TX_CTL, SPI_TX_CTL_FIFO_RESET);
    CLEAR_BIT(hspi->Instance->TX_CTL, SPI_TX_CTL_FIFO_RESET);
    
    /* Set Data Size */
    hspi->Instance->BATCH = Size;
    
    /* Tx Enable */
    hspi->Instance->TX_CTL |= SPI_TX_CTL_EN;

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {
        /* Transmit Start */
        hspi->Instance->CS |= SPI_CS_CS0;
    }
    else
    {
        /* Rx Disable */
        hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);
    }
    
    while(hspi->Tx_Size > 0)
    {
        /* Wait Tx FIFO Not Full */
        while (hspi->Instance->STATUS & SPI_STATUS_TX_FIFO_FULL)
        {
            if(uiTimeout)
            {
                uiTimeout--;
                if (uiTimeout == 0)
                {
                    Status = HAL_TIMEOUT;
                    goto End;
                }
            }
        }        
        hspi->Instance->DAT = hspi->Tx_Buffer[hspi->Tx_Count++];
        hspi->Tx_Size--;
        uiTimeout = Timeout;
    }
    
    if (hspi->Init.SPI_Mode == SPI_MODE_SLAVE) 
    {
        /* Wait Transmit Done */
        while (!(hspi->Instance->STATUS & SPI_STATUS_TX_BUSY));
        while (hspi->Instance->STATUS & SPI_STATUS_TX_BUSY)
        {
            if(uiTimeout)
            {
                uiTimeout--;
                if (uiTimeout == 0)
                {
                    Status = HAL_TIMEOUT;
                    goto End;
                }
            }
        }
    }
    else
    {
        /* Wait Transmit Done */
        while (!(hspi->Instance->STATUS & SPI_STATUS_TX_BATCH_DONE));
        Status = HAL_OK;
    }
    
End:
    /* Clear Batch Done Flag  */
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_TX_BATCH_DONE);
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);

    /* Tx Disable */
    hspi->Instance->TX_CTL &= (~SPI_TX_CTL_EN);
    
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER)  
    {
        /* Transmit End */
        hspi->Instance->CS &= (~SPI_CS_CS0);
    }

    return Status;
}

/************************************************************************
 * function   : HAL_SPI_Transmit_DMA
 * Description: Transmits an amount of data in blocking mode with DMA.
 * input      : hspi  : pointer to a SPI_HandleTypeDef structure that contains
 *                      the configuration information for SPI module
 *              pData : Pointer to data buffer
 *              Size  : Amount of data to be sent
 ************************************************************************/
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    /* Check SPI Parameter */
    if (!IS_SPI_ALL_INSTANCE(hspi->Instance))    return HAL_ERROR;
    
    /* Rx machine is running */
    if (hspi->TxState != SPI_TX_STATE_IDLE) 
    {
        return HAL_ERROR;
    }
    /* Set machine is Sending */
    hspi->TxState = SPI_TX_STATE_SENDING;


    /* Clear Batch Done Flag  */
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_TX_BATCH_DONE);
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);
    
    /* Enable Tx Batch Done Interrupt */
    SET_BIT(hspi->Instance->IE, SPI_STATUS_TX_BATCH_DONE);
    
    /* Set Data Size */
    hspi->Instance->BATCH = Size;
    
    /* Tx FIFO */
    hspi->Instance->TX_CTL &= ~SPI_TX_CTL_DMA_LEVEL;
    hspi->Instance->TX_CTL |= SPI_TX_CTL_DMA_LEVEL_0;    

    /* Tx Enable */
    hspi->Instance->TX_CTL |= SPI_TX_CTL_EN;
    
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        /* Transmit Start */
        hspi->Instance->CS |= SPI_CS_CS0;
    }
    else
    {
        /* Rx Disable */
        hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);
    }
    
    HAL_DMA_Start(hspi->HDMA_Tx, (uint32_t)pData, (uint32_t)&hspi->Instance->DAT, Size);

    hspi->Instance->TX_CTL |= SPI_TX_CTL_DMA_REQ_EN;  
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_SPI_Receive
 * Description: Receive an amount of data in blocking mode.
 * input      : hspi  : pointer to a SPI_HandleTypeDef structure that contains
 *                      the configuration information for SPI module
 *              pData : Pointer to data buffer
 *              Size  : Amount of data to be Receive
 *              Timeout  : Receive Timeout
 ************************************************************************/
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i;
    HAL_StatusTypeDef Status = HAL_OK;
    __IO uint32_t uiTimeout;
    
    /* Check SPI Parameter */
    if (!IS_SPI_ALL_INSTANCE(hspi->Instance))    return HAL_ERROR;
    if (pData == NULL)    return HAL_ERROR;
    
    hspi->Rx_Count = 0;
    hspi->Rx_Size = Size;
    hspi->Rx_Buffer = pData;
    uiTimeout = Timeout;
    
    if (hspi->Init.SPI_Mode == SPI_MODE_SLAVE) 
    {
        hspi->Instance->BATCH = 1;
        /* Rx Enable */
        hspi->Instance->RX_CTL |= SPI_RX_CTL_EN;
        
        while ( hspi->Rx_Size > 0) 
        { 
            while (READ_BIT(hspi->Instance->STATUS, SPI_STATUS_RX_FIFO_EMPTY))
            {
                if(uiTimeout)
                {
                    uiTimeout--;
                    if (uiTimeout == 0) 
                    {
                        /* Rx Disable */
                        hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);
                        return HAL_TIMEOUT;
                    }
                }
            }           
            
            hspi->Rx_Buffer[hspi->Rx_Count++] = hspi->Instance->DAT;
            hspi->Rx_Size--;
            uiTimeout = Timeout;
        }

        /* Rx Disable */
        hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);

        return HAL_OK;
    }

    /* Clear Batch Done Flag  */
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_RX_BATCH_DONE);
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);
    
    /* Set Data Size */
    hspi->Instance->BATCH = Size;
    
    /* Rx Enable */
    hspi->Instance->RX_CTL |= SPI_RX_CTL_EN;
    
    /* Receive Start */
    hspi->Instance->CS |= SPI_CS_CS0;
    
    while(hspi->Rx_Size > 0)
    {
        /* have no timeout */
        if (uiTimeout == 0) 
        {
            /* Wait Rx FIFO Not Empty */
            while (hspi->Instance->STATUS & SPI_STATUS_RX_FIFO_EMPTY);
        }
        else
        {
            while (hspi->Instance->STATUS & SPI_STATUS_RX_FIFO_EMPTY)
            {
                if (uiTimeout-- == 0) 
                {
                    Status = HAL_TIMEOUT;
                    goto End; 
                }
            }
        }
        
        hspi->Rx_Buffer[hspi->Rx_Count++] = hspi->Instance->DAT;
        hspi->Rx_Size--;
    }

    Status = HAL_OK;
    
    /* Wait Transmit Done */
    while (!(hspi->Instance->STATUS & SPI_STATUS_RX_BATCH_DONE));

End:   
    /* Clear Batch Done Flag  */
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_RX_BATCH_DONE);
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);

    /* Rx Disable */
    hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);

    /* Receive End */
    hspi->Instance->CS &= (~SPI_CS_CS0);
    
    return Status;
}

/************************************************************************
 * function   : HAL_SPI_Receive_DMA
 * Description: Receive an amount of data in blocking mode with DMA.
 * input      : hspi  : pointer to a SPI_HandleTypeDef structure that contains
 *                      the configuration information for SPI module
 *              pData : Pointer to data buffer
 *              Size  : Amount of data to be Receive
 ************************************************************************/
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    /* Check SPI Parameter */
    if (!IS_SPI_ALL_INSTANCE(hspi->Instance))    return HAL_ERROR;
    
    /* Rx machine is running */
    if (hspi->RxState != SPI_RX_STATE_IDLE) 
    {
        return HAL_ERROR;
    }
    /* Set Slave machine is receiving */
    hspi->RxState = SPI_RX_STATE_RECEIVING;


    /* Clear Batch Done Flag  */
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_RX_BATCH_DONE);
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);

    /* Enable Rx Batch Done Interrupt */
    SET_BIT(hspi->Instance->IE, SPI_STATUS_RX_BATCH_DONE);

    /* Set Data Size */
    hspi->Instance->BATCH = Size;

    /* Rx Enable */
    hspi->Instance->RX_CTL |= SPI_RX_CTL_EN;
    /* Rx FIFO */
    hspi->Instance->RX_CTL |= SPI_RX_CTL_DMA_LEVEL_0;

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {
        /* Receive Start */
        hspi->Instance->CS |= SPI_CS_CS0;
    }

    HAL_DMA_Start(hspi->HDMA_Rx, (uint32_t)&hspi->Instance->DAT, (uint32_t)pData, Size);
    
    hspi->Instance->RX_CTL |= SPI_RX_CTL_DMA_REQ_EN; 
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_SPI_Wire_Config
 * Description: SPI Wire Config
 * input      : hspi  : pointer to a SPI_HandleTypeDef structure that contains
 *                      the configuration information for SPI module
 *              Mode : This parameter can be a value of @ref X_MODE
 ************************************************************************/
HAL_StatusTypeDef HAL_SPI_Wire_Config(SPI_HandleTypeDef *hspi, uint32_t X_Mode)
{
    /* Check SPI Parameter */
    if (!IS_SPI_ALL_INSTANCE(hspi->Instance))    return HAL_ERROR;
    
    /* Set SPI X_Mode */
    hspi->Instance->CTL = ((hspi->Instance->CTL) & (~SPI_CTL_X_MODE)) | X_Mode;
    
    return HAL_OK;
}
/************************************************************************
 * function   : HAL_SPI_Transmit_IT
 * Description: Transmit an amount of data in blocking mode with interrupt.
 * input      : hspi  : pointer to a SPI_HandleTypeDef structure that contains
 *                      the configuration information for SPI module
 *              pData : Pointer to data buffer
 ************************************************************************/
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    /* Check SPI Parameter */
    if (!IS_SPI_ALL_INSTANCE(hspi->Instance))    return HAL_ERROR;
    
    /* Tx machine is running */
    if (hspi->TxState != SPI_TX_STATE_IDLE) 
    {
        return HAL_ERROR;
    }
    
    hspi->Tx_Size   = Size;
    hspi->Tx_Buffer = pData; 
    hspi->Tx_Count = 0;   

    /* Set machine is Sending */
    hspi->TxState = SPI_TX_STATE_SENDING;
    
    /* Clear TX FIFO */
    SET_BIT(hspi->Instance->TX_CTL, SPI_TX_CTL_FIFO_RESET);
    CLEAR_BIT(hspi->Instance->TX_CTL, SPI_TX_CTL_FIFO_RESET);
    
    /* Clear Batch Done Flag  */
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_TX_BATCH_DONE);
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);
    
    /* Set Data Size */
    hspi->Instance->BATCH = Size;

    /* Tx Enable */
    hspi->Instance->TX_CTL |= SPI_TX_CTL_EN;

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        /* Transmit Start */
        hspi->Instance->CS |= SPI_CS_CS0;
    }
    else
    {
        /* Rx Disable */
        hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);
    }
    
    while (hspi->Tx_Count < hspi->Tx_Size)   
    {
        if (!(hspi->Instance->STATUS & SPI_STATUS_TX_FIFO_FULL))
            hspi->Instance->DAT = hspi->Tx_Buffer[hspi->Tx_Count++];
        else
            break;           
    }
    /* Clear Tx FIFO half empty Flag  */
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_TX_FIFO_HALF_EMPTY);


    /* Enable Tx FIFO half empty Interrupt and Tx batch done Interrupt*/
    SET_BIT(hspi->Instance->IE, (SPI_IE_TX_FIFO_HALF_EMPTY_EN | SPI_IE_TX_BATCH_DONE_EN));

    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_SPI_Receive_IT
 * Description: Receive an amount of data in blocking mode with interrupt.
 * input      : hspi  : pointer to a SPI_HandleTypeDef structure that contains
 *                      the configuration information for SPI module
 *              pData : Pointer to data buffer
 ************************************************************************/
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint32_t Size)
{
    /* Check SPI Parameter */
    if (!IS_SPI_ALL_INSTANCE(hspi->Instance))    return HAL_ERROR;
    
    /* Rx machine is running */
    if (hspi->RxState != SPI_RX_STATE_IDLE) 
    {
        return HAL_ERROR;
    }
    
    /* Set Slave machine is receiving */
    hspi->RxState = SPI_RX_STATE_RECEIVING;
    
    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER)
    {
        /* Clear Batch Done Flag  */
        SET_BIT(hspi->Instance->STATUS, SPI_STATUS_RX_BATCH_DONE);
        SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);
        
        /* Set Data Size */
        hspi->Instance->BATCH = Size;
        
        /* Rx Enable */
        hspi->Instance->RX_CTL |= SPI_RX_CTL_EN;
        
        /* Receive Start */
        hspi->Instance->CS |= SPI_CS_CS0;
    }
    else
    {
        /* Reset BATCH register */
        hspi->Instance->BATCH = 1;
        hspi->Instance->RX_CTL |= SPI_RX_CTL_EN;   
    }

    hspi->Rx_Size   = Size;
    hspi->Rx_Buffer = pData; 
    hspi->Rx_Count = 0;   
    lu32_ReceiveTimeOut = SPI_RX_TIMEOUT;   

    /* Enable Rx FIFO Not Empty Interrupt */
    SET_BIT(hspi->Instance->IE, SPI_STATUS_RX_NOT_EMPTY);
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_SPI_TransmitReceive
 * Description: Transmits and recieve an amount of data in blocking mode.
 * input      : hspi  : pointer to a SPI_HandleTypeDef structure that contains
 *                      the configuration information for SPI module
 *              pTxData : Pointer to transmit data buffer
 *              pRxData : Pointer to recieve data buffer
 *              Size  : Amount of data to be sent
 *              Timeout  : TransmitReceive Timeout
 ************************************************************************/
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint32_t Size, uint32_t Timeout)
{
    uint32_t i;
    __IO uint32_t TxFlag = 1U, uiTimeout;
    HAL_StatusTypeDef Status = HAL_OK;

    /* Check SPI Parameter */
    if (!IS_SPI_ALL_INSTANCE(hspi->Instance))    return HAL_ERROR;
    if ((pTxData == NULL)||(pRxData == NULL))    return HAL_ERROR;
    
    hspi->Tx_Count = 0;
    hspi->Rx_Count = 0;
    hspi->Tx_Buffer = pTxData;
    hspi->Rx_Buffer = pRxData;
    hspi->Tx_Size = Size;   
    hspi->Rx_Size = Size;   
    uiTimeout = Timeout;
    
    /* Clear Batch Done Flag  */
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_TX_BATCH_DONE);
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);

    /* Tx Enable */
    hspi->Instance->TX_CTL |= SPI_TX_CTL_EN;

    /* Rx Enable */
    hspi->Instance->RX_CTL |= SPI_RX_CTL_EN;

    /* Clear TX FIFO */
    SET_BIT(hspi->Instance->TX_CTL, SPI_TX_CTL_FIFO_RESET);
    CLEAR_BIT(hspi->Instance->TX_CTL, SPI_TX_CTL_FIFO_RESET);
    
        
    if (hspi->Init.SPI_Mode == SPI_MODE_SLAVE) 
    {        
        hspi->Instance->DAT = hspi->Tx_Buffer[hspi->Tx_Count++];
        hspi->Tx_Size--;
        TxFlag = 0;
    }
    else
    {       
        /* Set Data Size */
        hspi->Instance->BATCH = hspi->Tx_Size;

        /* Transmit Start */
        hspi->Instance->CS |= SPI_CS_CS0;
        TxFlag = 1;
    }
    
    while((hspi->Tx_Size>0) || (hspi->Rx_Size>0))
    {
        if (hspi->Init.SPI_Mode == SPI_MODE_SLAVE) 
        {
            /* Wait Rx FIFO Not Empty */
            if((!(hspi->Instance->STATUS & SPI_STATUS_RX_FIFO_EMPTY)) && (hspi->Rx_Size>0))
            {
                hspi->Rx_Buffer[hspi->Rx_Count++] = hspi->Instance->DAT;
                hspi->Rx_Size--;
                TxFlag = 1U;
            }        
            /* Wait Tx FIFO Not Full */
            if((!(hspi->Instance->STATUS & SPI_STATUS_TX_FIFO_FULL)) && (hspi->Tx_Size>0) && (TxFlag == 1U))
            {
                hspi->Instance->DAT = hspi->Tx_Buffer[hspi->Tx_Count++];
                hspi->Tx_Size--;
                TxFlag = 0;
            }
        }
        else
        {
            /* Wait Tx FIFO Not Full */
            if((!(hspi->Instance->STATUS & SPI_STATUS_TX_FIFO_FULL)) && (hspi->Tx_Size>0) && (TxFlag == 1U))
            {
                hspi->Instance->DAT = hspi->Tx_Buffer[hspi->Tx_Count++];
                hspi->Tx_Size--;
                TxFlag = 0;
            }
            
            /* Wait Rx FIFO Not Empty */
            if((!(hspi->Instance->STATUS & SPI_STATUS_RX_FIFO_EMPTY)) && (hspi->Rx_Size>0))
            {
                hspi->Rx_Buffer[hspi->Rx_Count++] = hspi->Instance->DAT;
                hspi->Rx_Size--;
                TxFlag = 1U;
            }
        }
        
        /* Wait Timeout */
        if(uiTimeout)
        {
            uiTimeout--;
            if(uiTimeout == 0)
            {
                Status = HAL_TIMEOUT;
                goto End;
            }
        }
    }        
    /* Wait Transmit Done */
    while (!(hspi->Instance->STATUS & SPI_STATUS_TX_BATCH_DONE));
    
    Status = HAL_OK;

End:    
    /* Clear Batch Done Flag  */
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_TX_BATCH_DONE);
    SET_BIT(hspi->Instance->STATUS, SPI_STATUS_BATCH_DONE);

    /* Tx Disable */
    hspi->Instance->TX_CTL &= (~SPI_TX_CTL_EN);
    
    /* Rx Disable */
    hspi->Instance->RX_CTL &= (~SPI_RX_CTL_EN);

    if (hspi->Init.SPI_Mode == SPI_MODE_MASTER) 
    {
        /* Transmit End */
        hspi->Instance->CS &= (~SPI_CS_CS0);
    }

    return Status;
}

/************************************************************************
 * function   : HAL_SPI_GetTxState
 * Description: Get Tx state.
 * input      : hspi  : pointer to a SPI_HandleTypeDef structure that contains
 *                      the configuration information for SPI module
 ************************************************************************/
uint8_t HAL_SPI_GetTxState(SPI_HandleTypeDef *hspi)
{
    return hspi->TxState;
}

/************************************************************************
 * function   : HAL_SPI_GetRxState
 * Description: Get Rx state.
 * input      : hspi  : pointer to a SPI_HandleTypeDef structure that contains
 *                      the configuration information for SPI module
 ************************************************************************/
uint8_t HAL_SPI_GetRxState(SPI_HandleTypeDef *hspi)
{
    return hspi->RxState;
}


























