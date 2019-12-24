/**
******************************************************************************
* @file    HAL_spi.c
* @author  AE Team
* @version V1.0.0
* @date    28/7/2017
* @brief   This file provides all the SPI firmware functions.
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
* <h2><center>&copy; COPYRIGHT 2015 MindMotion</center></h2>
*/ 

/* Includes ------------------------------------------------------------------*/
#include "HAL_spi.h"


/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup SPI 
* @brief SPI driver modules
* @{
*/ 

/** @defgroup SPI_Private_TypesDefinitions
* @{
*/

/**
* @}
*/ 


/** @defgroup SPI_Private_Defines
* @{
*/



/* SPI SPIENE mask */
#define GCTL_SPIEN_Set          ((uint16_t)0x0001)
#define GCTL_SPIEN_Reset        ((uint16_t)0xFFFE)
/* SPI registers Masks */
#define GCTL_CLEAR_Mask       ((uint16_t)0xF000)
#define CCTL_CLEAR_Mask       ((uint16_t)0xFFC0)
#define SPBRG_CLEAR_Mask      ((uint16_t)0x0000)
#define SPI_DataSize_Mask     ((uint16_t)0xFCFF)
/**
* @}
*/

/** @defgroup SPI_Private_Macros
* @{
*/

/**
* @}
*/

/** @defgroup SPI_Private_Variables
* @{
*/

/**
* @}
*/

/** @defgroup SPI_Private_FunctionPrototypes
* @{
*/

/**
* @}
*/

/** @defgroup SPI_Private_Functions
* @{
*/

/**
* @brief  Deinitializes the SPIx peripheral registers to their default
*   reset values .
* @param SPIx: where x can be 0, 1 to select the SPI peripheral.
* @retval : None
*/
void SPI_DeInit(SPI_TypeDef* SPIx)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    
    switch (*(uint32_t*)&SPIx)
    {
    case SPI1_BASE:
        /* Enable SPI1 reset state */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
        /* Release SPI1 from reset state */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
        break;
    case SPI2_BASE:
        /* Enable SPI2 reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
        /* Release SPI1 from reset state */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
        break;
        
        
    default:
        break;
    }
}

/**
* @brief  Initializes the SPIx peripheral according to the specified 
*   parameters in the SPI_InitStruct.
* @param SPIx: where x can be 0, 1 to select the SPI peripheral.
* @param SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
*   contains the configuration information for the specified
*   SPI peripheral.
* @retval : None
*/
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
    uint32_t tmpreg = 0;
    
    /* check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));   
    
    /* Check the SPI parameters */
    assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
    assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
    assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
    assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
    assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
    assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
    assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
    assert_param(IS_SPI_DATAWIDRH(SPI_InitStruct->SPI_DataWidth));
    assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->SPI_CRCPolynomial));
    /*---------------------------- SPIx GCTL Configuration ------------------------*/
    /* Get the SPIx GCTL value */
    tmpreg = SPIx->GCTL;
    /* Clear csn_sel, dmamode, txtlf, rxtlf,data_sel, rxen, txen, mm, int_en, spien bits */
    tmpreg &= GCTL_CLEAR_Mask;
    /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
    master/salve mode, CPOL and CPHA */
    /* Set dat_sel bits according to SPI_DataSize value */
    /* Set csn and csn_sel bits according to SPI_NSS value */
    /* Set mm bit according to SPI_Mode value */
    tmpreg |= (uint32_t)((uint32_t) SPI_InitStruct->SPI_DataSize  |  SPI_InitStruct->SPI_NSS | 
                         SPI_InitStruct->SPI_Mode  );
    /* Write to SPIx GCTL */
    SPIx->GCTL = tmpreg;
    /*---------------------------- SPIx CCTL Configuration ------------------------*/	
    tmpreg = SPIx->CCTL;
    /* Clear spilen, lsbfe, CPOL, CPHA bits */
    tmpreg &= CCTL_CLEAR_Mask;
    /* Set Spilen bit according to SPI_DataWidth value */
    /* Set LSBFirst bit according to SPI_FirstBit value */
    /* Set CPOL bit according to SPI_CPOL value */
    /* Set CPHA bit according to SPI_CPHA value */
    tmpreg |= (uint16_t)( SPI_InitStruct->SPI_FirstBit   |  SPI_InitStruct->SPI_CPOL | 
                         SPI_InitStruct->SPI_CPHA) ;
    
    /* Write to SPIx CCTL */
    SPIx->CCTL = tmpreg|0x18;
    /*---------------------------- SPIx SPBRG Configuration ------------------------*/	
    tmpreg = SPIx->SPBRG;
    /* Clear spbrg bits */
    tmpreg &= (uint16_t)SPBRG_CLEAR_Mask;	
    /* Set BR bits according to SPI_BaudRatePrescaler value */
    tmpreg |= (uint16_t) SPI_InitStruct->SPI_BaudRatePrescaler;
    /* Write to SPIx SPBRG */
    SPIx->SPBRG = tmpreg;
    
    if((SPI_InitStruct->SPI_DataWidth)!=SPI_DataWidth_8b)
    {
        SPIx->CCTL|=1<<2;//lsbfe
        SPIx->CCTL|=1<<3;//spilen
    }
    SPIx->EXTCTL=SPI_InitStruct->SPI_DataWidth;
}

/**
* @brief  Fills each SPI_InitStruct member with its default value.
* @param SPI_InitStruct : pointer to a SPI_InitTypeDef structure
*   which will be initialized.
* @retval : None
*/
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
    /*--------------- Reset SPI init structure parameters values -----------------*/
    
    /* initialize the SPI_Mode member */
    SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
    /* initialize the SPI_DataSize member */
    SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
    /* Initialize the SPILEN member */
    SPI_InitStruct->SPI_DataWidth = SPI_DataWidth_8b;
    /* Initialize the SPI_CPOL member */
    SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
    /* Initialize the SPI_CPHA member */
    SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
    /* Initialize the SPI_NSS member */
    SPI_InitStruct->SPI_NSS = SPI_NSS_Soft;
    /* Initialize the SPI_BaudRatePrescaler member */
    SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    /* Initialize the SPI_FirstBit member */
    SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
    
}


/**
* @brief  Enables or disables the specified SPI peripheral.
* @param SPIx: where x can be 0, 1 to select the SPI peripheral.
* @param NewState: new state of the SPIx peripheral. 
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected SPI peripheral */
        SPIx->GCTL |= GCTL_SPIEN_Set;
    }
    else
    {
        /* Disable the selected SPI peripheral */
        SPIx->GCTL &= GCTL_SPIEN_Reset;
    }
}


/**
* @brief  Enables or disables the specified SPIinterrupts.
* @param SPIx: where x can be :
*   0, 1  in SPI mode 
* @param SPI_IT: specifies the SPI interrupt source to be 
*   enabled or disabled. 
*   This parameter can be one of the following values:
* @arg SPI_IT_TX: Tx buffer empty interrupt mask
* @arg SPI_IT_RX: Rx buffer  interrupt mask
* @arg SPI_IT_UNDERRUN: under Error interrupt mask in slave mode
* @arg SPI_IT_RXOVER: RX OVER Error interrupt mask 
* @arg SPI_IT_RXMATCH: spectials rx data numbers  interrupt mask 
* @arg SPI_IT_RXFULL: Rx buffer full interrupt mask 
* @arg SPI_IT_TXEPT: Tx buffer empty interrupt mask 
* @param NewState: new state of the specified SPI interrupt.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void SPI_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SPI_CONFIG_IT(SPI_IT));
    
    if (NewState != DISABLE)
    {
        /* Enable the selected SPI Global interrupt */
        SPIx->GCTL |= SPI_INT_EN;
        /* Enable the selected SPI interrupt */
        SPIx->INTEN |= SPI_IT;
    }
    else
    {
        /* Disable the selected SPI interrupt */
        SPIx->INTEN &= (uint16_t)~SPI_IT;
        /* Disable the selected SPI Global interrupt */
        SPIx->GCTL &= (uint16_t)~SPI_INT_EN;
    }
    
}

/**
* @brief  Enables or disables the SPIx DMA interface.
* @param SPIx: where x can be :
*   0, 1 in SPI mode 
* @param SPI_DMAReq: specifies the SPI DMA transfer request 
*   to be enabled or disabled. 
*   This parameter can be any combination of the following values:
* @arg SPI_DMAReq_EN: DMA transfer request enable
* @param NewState: new state of the selected SPI DMA transfer 
*   request.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void SPI_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_DMAReq, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SPI_DMAREQ(SPI_DMAReq));
    if (NewState != DISABLE)
    {
        /* Enable the selected SPI DMA requests */
        SPIx->GCTL |= SPI_DMAReq;
    }
    else
    {
        /* Disable the selected SPI DMA requests */
        SPIx->GCTL &= (uint32_t)~SPI_DMAReq;
    }
}

/**
* @brief  configure tn Fifo trigger level bit.
* @param SPIx: where x can be :
*   0, 1 in SPI mode 
* @param SPI_FifoTriggerValue: specifies the Fifo trigger level 
*   This parameter can be any combination of the following values:
* SPI_TXTLF : SPI TX FIFO Trigger value set
* SPI_RXTLF : SPI RX FIFO Trigger value set
* @param NewState: new state of the selected SPI DMA transfer 
*   request.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void SPI_FifoTrigger(SPI_TypeDef* SPIx, uint16_t SPI_FifoTriggerValue, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SPI_FIFOTRIGGER(SPI_FifoTriggerValue));
    
    if (NewState != DISABLE)
    {
        /* Enable the selected SPI DMA requests */
        SPIx->GCTL |= SPI_FifoTriggerValue;
    }
    else
    {
        /* Disable the selected SPI DMA requests */
        SPIx->GCTL &= (uint32_t)~SPI_FifoTriggerValue;
    }
}

/**
* @brief  Transmits a Data through the SPIx peripheral.
* @param SPIx: where x can be :
*   0, 1 in SPI mode 
* @param Data : Data to be transmitted..
* @retval : None
*/
void SPI_SendData(SPI_TypeDef* SPIx, uint32_t Data)
{
    uint8_t temp;
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    
    /* Write in the TXREG register the data to be sent */
    temp=SPIx->EXTCTL;
    SPIx->TXREG = Data;
    if(temp>0x8||temp==0) SPIx->TXREG  = Data>>8;
    if(temp>0x10||temp==0) SPIx->TXREG = Data>>16;
    if(temp>0x18||temp==0) SPIx->TXREG = Data>>24;
}


/**
* @brief  Returns the most recent received data by the SPIx peripheral. 
* @param SPIx: where x can be :
*   0, 1 in SPI mode 
* @retval : The value of the received data.
*/
uint32_t SPI_ReceiveData(SPI_TypeDef* SPIx)
{
    
    uint32_t temp=0;
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    temp=temp;
    temp |=(uint32_t)SPIx->RXREG;
    if(SPIx->EXTCTL>8||SPIx->EXTCTL==0)    temp |=(uint32_t) (SPIx->RXREG)<<8;
    if(SPIx->EXTCTL>16||SPIx->EXTCTL==0)  	temp |=(uint32_t)( SPIx->RXREG)<<16;
    if(SPIx->EXTCTL>24||SPIx->EXTCTL==0)	temp |=(uint32_t)( SPIx->RXREG)<<24;
    
    return temp;
}

/**
* @brief Slave chip csn single by selected 
* @param SPIx: where x can be 0, 1 to select the SPI peripheral.
* @param SPI_CSInternalSelected: specifies the SPI CS internal selected.
*   This parameter can be one of the following values: 
* @arg SPI_CS_BIT0: cs bit 0 selected  
* @arg SPI_CS_BIT1: cs bit 1 selected  
* @arg SPI_CS_BIT2: cs bit 2 selected  
* @arg SPI_CS_BIT3: cs bit 3 selected  
* @arg SPI_CS_BIT4: cs bit 4 selected  
* @arg SPI_CS_BIT5: cs bit 5 selected  
* @arg SPI_CS_BIT6: cs bit 6 selected  
* @arg SPI_CS_BIT7: cs bit 7 selected 
* @param NewState: new state of the selected SPI CS pin 
*   request.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void SPI_CSInternalSelected(SPI_TypeDef* SPIx, uint16_t SPI_CSInternalSelected,FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_CS(SPI_CSInternalSelected));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    
    if (NewState != DISABLE)
    {
        /* selected cs pin according SCSR Value */
        SPIx->SCSR &= SPI_CSInternalSelected;
    }
    else
    {
        /* release cs pin according SCSR Value*/
        SPIx->SCSR |= ~SPI_CSInternalSelected;
    }
}


/**
* @brief  Configures internally by software the NSS pin for the selected 
*   SPI.
* @param SPIx: where x can be 1, 2 to select the SPI peripheral.
* @param SPI_NSSInternalSoft: specifies the SPI NSS internal state.
*   This parameter can be one of the following values:
* @arg SPI_NSSInternalSoft_Set: Set NSS pin internally
* @arg SPI_NSSInternalSoft_Reset: Reset NSS pin internally
* @retval : None
*/
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));
    if (SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset)
    {
        /* Set NSS pin internally by software */
        SPIx->GCTL |= SPI_NSSInternalSoft_Set;
    }
    else
    {
        /* Reset NSS pin internally by software */
        SPIx->GCTL &= SPI_NSSInternalSoft_Reset;
    }
}



/**
* @brief  Configures the data size for the selected SPI.
* @param SPIx: where x can be 0, 1 to select the SPI peripheral.
* @param SPI_DataSize: specifies the SPI data size.
*   This parameter can be one of the following values:
* @arg SPI_DataSize_32b: Set data frame format to 32bit
* @arg SPI_DataSize_16b: Set data frame format to 16bit
* @arg SPI_DataSize_8b: Set data frame format to 8bit
* @retval : None
*/
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DATASIZE(SPI_DataSize));
    /* Clear data_sel bit */
    SPIx->GCTL &= SPI_DataSize_Mask;
    /* Set new data_sel bit value */
    SPIx->GCTL |= SPI_DataSize;
}



/**
* @brief  Selects the data transfer direction in bi-directional mode
*   for the specified SPI.
* @param SPIx: where x can be 0, 1 to select the SPI peripheral.
* @param SPI_Direction: specifies the data transfer direction in
*   bi-directional mode. 
*   This parameter can be one of the following values:
* @arg SPI_Direction_Tx: Selects Tx transmission direction
* @arg SPI_Direction_Rx: Selects Rx receive direction
@arg SPI_Disable_Tx: Selects Rx receive direction
@arg SPI_Disable_Rx: Selects Rx receive direction
* @retval : None
*/
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DIRECTION(SPI_Direction));
    
    /* Set the Tx  only mode */
    if(SPI_Direction==SPI_Direction_Tx)
    {
        SPIx->GCTL |= SPI_Direction_Tx;
    }
    /* Set the  Rx  only mode */
    if(SPI_Direction==SPI_Direction_Rx)
    {
        SPIx->GCTL |= SPI_Direction_Rx;
    }
    /* Disable the  Tx  only mode */
    if(SPI_Direction==SPI_Disable_Tx)
    {
        SPIx->GCTL &= SPI_Disable_Tx;
    }
    /* Disable the  Rx  only mode */
    if(SPI_Direction==SPI_Disable_Rx)
    {
        SPIx->GCTL &= SPI_Disable_Rx;
    }
}

/**
* @brief  Checks whether the specified SPI flag is set or not.
* @param SPIx: where x can be :
*   0, 1 in SPI mode 
* @param SPI_FLAG: specifies the SPI flag to check. 
*   This parameter can be one of the following values:
* @arg SPI_FLAG_RXAVL: Rx buffer has bytes flag
* @arg SPI_FLAG_TXEPT:  Tx  buffer  and tx shifter empty flag
* @retval : The new state of SPI_FLAG (SET or RESET).
*/
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_GET_FLAG(SPI_FLAG));
    if(SPIx->EXTCTL==8)
    {
        /* Check the status of the specified SPI flag */
        if ((SPIx->CSTAT & SPI_FLAG) != (uint16_t)RESET)
        {
            /* SPI_FLAG is set */
            bitstatus = SET;
        }
        else
        {
            /* SPI_FLAG is reset */
            bitstatus = RESET;
        }
        /* Return the SPI_FLAG status */
        return  bitstatus;
    }
    else
    {
        uint8_t number; 
        if(SPIx->EXTCTL>0&&SPIx->EXTCTL<=8)
            number=1;
        else if(SPIx->EXTCTL<=16)
            number=2;
        else if(SPIx->EXTCTL<=24)
            number=3;
        else if(SPIx->EXTCTL<=31||SPIx->EXTCTL==0)
            number=4;
        if(((SPIx->CSTAT&0xf00)>>8)>=number)
        {
            return SET;
        }
        else
        {
            return RESET;
        }	
    }
}

/**
* @brief  Checks whether the specified SPI interrupt has occurred or not.
* @param SPIx: where x can be :
*  0, 1 in SPI mode 
* @param SPI_IT: specifies the SPI interrupt source to check. 
*   This parameter can be one of the following values:
* @arg SPI_IT_TX: Tx buffer empty interrupt
* @arg SPI_IT_RX: Rx buffer  interrupt
* @arg SPI_IT_UNDERRUN: under Error interrupt in slave mode
* @arg SPI_IT_RXOVER: RX OVER Error interrupt
* @arg SPI_IT_RXMATCH: spectials rx data numbers  interrupt 
* @arg SPI_IT_RXFULL: Rx buffer full interrupt
* @arg SPI_IT_TXEPT: Tx buffer  and tx shifter empty interrupt  
* @retval : The new state of SPI_IT (SET or RESET).
*/
ITStatus SPI_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_IT)
{
    ITStatus bitstatus = RESET;
    
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_GET_IT(SPI_IT));
    /* Check the status of the specified SPI interrupt */
    if ((SPIx->INTSTAT & SPI_IT) != (uint16_t)RESET)
    {
        /* SPI_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* SPI_IT is reset */
        bitstatus = RESET;
    }
    /* Return the SPI_IT status */
    return bitstatus;
}

/**
* @brief  Clears the SPIx  Error  interrupt pending bit.
* @param SPIx: where x can be :
*   0, 1 in SPI mode 
* @param SPI_IT: specifies the SPI interrupt pending bit to clear.
* @arg SPI_IT_TX: Tx buffer empty interrupt
* @arg SPI_IT_RX: Rx buffer  interrupt
* @arg SPI_IT_UNDERRUN: under Error interrupt in slave mode
* @arg SPI_IT_RXOVER: RX OVER Error interrupt
* @arg SPI_IT_RXMATCH: spectials rx data numbers  interrupt 
* @arg SPI_IT_RXFULL: Rx buffer full interrupt
* @arg SPI_IT_TXEPT: Tx buffer  and tx shifter empty interrupt  
*   This function clears only ERR intetrrupt pending bit.   
* @retval : None
*/
void SPI_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_IT)
{
    
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_CLEAR_IT(SPI_IT));
    
    /* Clear the selected SPI IT INTERRUPT */
    SPIx->INTCLR |= (uint16_t)SPI_IT;
}


/**
* @brief  SPI Hole a count Received bytes in next receive process.
* @param SPIx: where x can be 0, 1 in SPI mode 
* @param Number: specifies the SPI receive Number.
*   This parament can be 1-65535.  
*   This function can use only in SPI master single receive mode. 
* @retval : None
*/
void SPI_RxBytes(SPI_TypeDef* SPIx, uint16_t Number)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    /*set the received bytes in next receive process */
    SPIx->RXDNR = Number;
}

/**
* @brief  slave mode tx data transmit phase adjust set.
* @param SPIx: where x can be 0, 1 in SPI mode 
* @param AdjustValue: specifies the SPI receive Number.
*   This parament can be : 
*   SPI_SlaveAdjust_FAST:  fast speed use
*   SPI_SlaveAdjust_LOW:   low speed use
*   This function can use only in SPI master single receive mode. 
* @retval : None
*/
void SPI_SlaveAdjust(SPI_TypeDef* SPIx, uint16_t AdjustValue)
{
    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_SlaveAdjust(AdjustValue));
    /*set the AdjustValue according to txedge bit of CCTL register*/
    SPIx->CCTL |= AdjustValue;
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
