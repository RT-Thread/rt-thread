/*
  ******************************************************************************
  * @file    HAL_DAC.c
  * @version V1.0.0
  * @date    2020
  * @brief   DAC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (DAC).
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  *           @ Peripheral Control functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

 /*********************************************************************************
* Function    : HAL_DAC_IRQHandler
* Description : This function uses the interruption of DMA  underrun.
* Input       : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module
* Output      : 
* Author      : CWT                         Data : 2020年
**********************************************************************************/
void HAL_DAC_IRQHandler(DAC_HandleTypeDef *hdac)
{
    if((hdac->Instance->SR&DAC_SR_DMAUDR1)==DAC_SR_DMAUDR1||(hdac->Instance->SR &DAC_SR_DMAUDR2)==DAC_SR_DMAUDR2)
    {
        //clear the DMA underrun
        hdac->Instance->SR|=DAC_SR_DMAUDR1|DAC_SR_DMAUDR2;   
    }
}
/*********************************************************************************
* Function    : HAL_DAC_MspInit
* Description : Initialize the DAC MSP.
* Input       : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module
* Output      : 
* Author      : CWT                         Data : 2020年
**********************************************************************************/

__weak void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac)
{
    /* NOTE : This function should not be modified, when the callback is needed,
    the HAL_DAC_MspInit can be implemented in the user file
    */
    /* For Example */
    if(hdac->Instance==DAC)
    { 
        /* Enable DAC clock */
        System_Module_Enable(EN_DAC);
        GPIO_InitTypeDef GPIO_InitStructure;   	
        /* Initialization GPIO */
        /**DAC1 GPIO Configuration    
        PB1  ------> DAC_OUT1 
        PB0  ------> DAC_OUT2 
        */
        GPIO_InitStructure.Pin = GPIO_PIN_1|GPIO_PIN_0;	
        GPIO_InitStructure.Pull=GPIO_NOPULL;
        GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
        
        /* Enable the DAC DMA underrun interrupt */
        hdac->Instance->CR |= DAC_CR_DMAUDRIE1|DAC_CR_DMAUDRIE2;
        NVIC_ClearPendingIRQ(DAC_IRQn);
        NVIC_SetPriority(DAC_IRQn, 5);
        NVIC_EnableIRQ(DAC_IRQn);
    }
}

/*********************************************************************************
* Function    : HAL_DAC_MspDeInit
* Description : DAC MSP De-Initialization.
* Input       : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module
* Output      : 
* Author      : CWT                         Data : 2020年
**********************************************************************************/
void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac)
{
    if(hdac->Instance==DAC)
    {
        /* USER CODE BEGIN DAC1_MspDeInit 0 */

        /* USER CODE END DAC1_MspDeInit 0 */
        /* Peripheral clock disable */
        System_Module_Disable(EN_DAC);
        /**DAC1 GPIO Configuration    
        PB1  ------> DAC_OUT1 
        PB0  ------> DAC_OUT2 
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_1);
        /* DAC1 DMA DeInit */
        HAL_DMA_DeInit(hdac->DMA_Handle1);
        HAL_DMA_DeInit(hdac->DMA_Handle2);
        /* USER CODE BEGIN DAC1_MspDeInit 1 */

        /* USER CODE END DAC1_MspDeInit 1 */
    }

}

/*********************************************************************************
* Function    : HAL_DAC_Init
* Description :	Initializes the CAN peripheral according to the specified  parameters in the DAC_HandleTypeDef..
* Input       : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef *hdac)
{
    uint8_t InitStatus = HAL_ERROR;
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;

    System_Module_Reset(RST_DAC);
    HAL_DAC_MspInit(hdac);
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DAC_DeInit
* Description :	Deinitialize the DAC peripheral registers to their default reset values.
* Input       : hdac : pointer to a DAC_HandleTypeDef structure that contains
*                      the configuration information for DAC module
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DAC_DeInit(DAC_HandleTypeDef* hdac)
{
    /* Check DAC handle */
    if (hdac == NULL)
    {
        return HAL_ERROR;
    }
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    HAL_DAC_MspDeInit(hdac);

    /* Return function status */
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DAC_ConfigChannel
* Description :	Configures the selected DAC channel.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               sConfig:DAC configuration structure
*               Channel:This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DAC_ConfigChannel(DAC_HandleTypeDef* hdac, DAC_ChannelConfTypeDef* sConfig, uint32_t Channel)
{
    uint32_t tmpreg1, tmpreg2;
    uint32_t tickstart = 0U;
    uint32_t ConnectOnChipPeripheral=0U;
    /* Check the DAC parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_TRIGGER(sConfig->DAC_Trigger)) return HAL_ERROR;
    if(!IS_DAC_OUTPUT_BUFFER_STATE(sConfig->DAC_OutputBuffer)) return HAL_ERROR;
    if(!IS_DAC_CHIP_CONNECTION(sConfig->DAC_ConnectOnChipPeripheral)) return HAL_ERROR;
    if(!IS_DAC_TRIMMING(sConfig->DAC_UserTrimming)) return HAL_ERROR;
    if ((sConfig->DAC_UserTrimming) == DAC_TRIMMING_USER)
    {
        if(!IS_DAC_TRIMMINGVALUE(sConfig->DAC_TrimmingValue)) return HAL_ERROR;
    }
    if(!IS_DAC_SAMPLEANDHOLD(sConfig->DAC_SampleAndHold)) return HAL_ERROR;
    if ((sConfig->DAC_SampleAndHold) == DAC_SAMPLEANDHOLD_ENABLE)
    {
        if(!IS_DAC_SAMPLETIME(sConfig->DAC_SampleAndHoldConfig.DAC_SampleTime)) return HAL_ERROR;
        if(!IS_DAC_HOLDTIME(sConfig->DAC_SampleAndHoldConfig.DAC_HoldTime)) return HAL_ERROR;
        if(!IS_DAC_REFRESHTIME(sConfig->DAC_SampleAndHoldConfig.DAC_RefreshTime)) return HAL_ERROR;
    }
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR;



    if (sConfig->DAC_SampleAndHold == DAC_SAMPLEANDHOLD_ENABLE)
    /* Sample on old configuration */
    {
        /* SampleTime */
        if (Channel == DAC_CHANNEL_1)
        {
            hdac->Instance->SHSR1 = sConfig->DAC_SampleAndHoldConfig.DAC_SampleTime;
        }
        else /* Channel 2 */

            hdac->Instance->SHSR2 = sConfig->DAC_SampleAndHoldConfig.DAC_SampleTime;
    
        /* HoldTime */
        MODIFY_REG(hdac->Instance->SHHR, DAC_SHHR_THOLD1 << (Channel & 0x10UL), (sConfig->DAC_SampleAndHoldConfig.DAC_HoldTime) << (Channel & 0x10UL));
        /* RefreshTime */
        MODIFY_REG(hdac->Instance->SHRR, DAC_SHRR_TREFRESH1 << (Channel & 0x10UL), (sConfig->DAC_SampleAndHoldConfig.DAC_RefreshTime) << (Channel & 0x10UL));
    }

    if (sConfig->DAC_UserTrimming == DAC_TRIMMING_USER)
    /* USER TRIMMING */
    {
        /* Get the DAC CCR value */
        tmpreg1 = hdac->Instance->CCR;
        /* Clear trimming value */
        tmpreg1 &= ~(((uint32_t)(DAC_CCR_OTRIM1)) << (Channel & 0x10UL));
        /* Configure for the selected trimming offset */
        tmpreg2 = sConfig->DAC_TrimmingValue;
        /* Calculate CCR register value depending on DAC_Channel */
        tmpreg1 |= tmpreg2 << (Channel & 0x10UL);
        /* Write to DAC CCR */
        hdac->Instance->CCR = tmpreg1;
    }
    else
    {
        /*  factory trimming in NVR,read to DAC_CCR */
        uint32_t OTRIM=*(uint32_t *)(0x80248);
        uint32_t OTRIM_high=(OTRIM&0xffff0000)>>16;
        uint32_t OTRIM_low=(OTRIM&0xffff);
        if (OTRIM_low==((~OTRIM_high)&0xffff))
            {
                tmpreg1=(OTRIM_low&0x1f)|(((OTRIM_low&0x3E0)>>5)<<16);
                hdac->Instance->CCR = tmpreg1;  
            }
    }


    /* Get the DAC MCR value */
    tmpreg1 = hdac->Instance->MCR;
    /* Clear DAC_MCR_MODEx bits */
    tmpreg1 &= ~(((uint32_t)(DAC_MCR_MODE1)) << (Channel & 0x10UL));
    /* Configure for the selected DAC channel: mode, buffer output & on chip peripheral connect */
    ConnectOnChipPeripheral=sConfig->DAC_ConnectOnChipPeripheral;
    if((sConfig->DAC_SampleAndHold == DAC_SAMPLEANDHOLD_ENABLE)&&(sConfig->DAC_OutputBuffer==DAC_OUTPUTBUFFER_DISABLE))
    {
        ConnectOnChipPeripheral=(!ConnectOnChipPeripheral);
    }
    tmpreg2 = (sConfig->DAC_SampleAndHold | sConfig->DAC_OutputBuffer | ConnectOnChipPeripheral); 
    /* Calculate MCR register value depending on DAC_Channel */
    tmpreg1 |= tmpreg2 << (Channel & 0x10UL);
    /* Write to DAC MCR */
    hdac->Instance->MCR = tmpreg1;

    /* DAC in normal operating mode hence clear DAC_CR_CENx bit */
    CLEAR_BIT(hdac->Instance->CR, DAC_CR_CEN1 << (Channel & 0x10UL));

    /* Get the DAC CR value */
    tmpreg1 = hdac->Instance->CR;
    /* Clear TENx, TSELx, WAVEx and MAMPx bits */
    tmpreg1 &= ~(((uint32_t)(DAC_CR_MAMP1 | DAC_CR_WAVE1 | DAC_CR_TSEL1 | DAC_CR_TEN1)) << (Channel & 0x10UL));
    /* Configure for the selected DAC channel: trigger */
    /* Set TSELx and TENx bits according to DAC_Trigger value */
    tmpreg2 = sConfig->DAC_Trigger;
    /* Calculate CR register value depending on DAC_Channel */
    tmpreg1 |= tmpreg2 << (Channel & 0x10UL);
    /* Write to DAC CR */
    hdac->Instance->CR = tmpreg1;

    /* Disable wave generation */
    hdac->Instance->CR &= ~(DAC_CR_WAVE1 << (Channel & 0x10UL));


    /* Return function status */
    return HAL_OK;  
}

/*********************************************************************************
* Function    : HAL_DAC_Start
* Description :	 Enables DAC and starts conversion of channel.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               Channel:This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef *hdac, uint32_t Channel)
{
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR; 
      uint32_t tmp1 = 0U, tmp2 = 0U;
    
    if (Channel == DAC_CHANNEL_1)
    {
        hdac->Instance->CR|=DAC_CR_EN1;  
        tmp1 = hdac->Instance->CR & DAC_CR_TEN1;
        tmp2 = hdac->Instance->CR & DAC_CR_TSEL1;
         /* Check if software trigger enabled */
    if((tmp1 ==  DAC_CR_TEN1) && (tmp2 ==  DAC_CR_TSEL1))
    {
        /* Enable the selected DAC software conversion */
        hdac->Instance->SWTRIGR|=DAC_SWTRIGR_SWTRIG1;
    }
    }
    else
    {
        hdac->Instance->CR|=DAC_CR_EN2; 
        tmp1 = hdac->Instance->CR & DAC_CR_TEN2;
        tmp2 = hdac->Instance->CR & DAC_CR_TSEL2;    
         /* Check if software trigger enabled */
    if((tmp1 == DAC_CR_TEN2) && (tmp2 == DAC_CR_TSEL2))
    {
        /* Enable the selected DAC software conversion */
        hdac->Instance->SWTRIGR|=DAC_SWTRIGR_SWTRIG2;
    }
    }
    /* Return function status */
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DAC_Stop
* Description :	Disables DAC and stop conversion of channel.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               Channel:This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR; 
  
    /* Disable the Peripheral */
    if (Channel == DAC_CHANNEL_1)
    {
        hdac->Instance->CR&=~DAC_CR_EN1;  
    }
    else
    {
        hdac->Instance->CR&=~DAC_CR_EN2;  
    }
 
    /* Return function status */
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DAC_Start_DMA
* Description :	Enables DAC and starts conversion of channel.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               Channel:This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2 @arg DAC_CHANNEL_Dual
*               pData: The destination peripheral Buffer address.
*               Length: The length of data to be transferred from memory to DAC peripheral
*               Alignment: Specifies the data alignment for DAC channel.This parameter can be one of the following values:
                            @arg DAC_ALIGN_8B_R   @arg DAC_ALIGN_12B_L   @arg DAC_ALIGN_12B_R  
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t *pData, uint32_t Length, uint32_t Alignment)
{
    HAL_StatusTypeDef status;
    uint32_t DstAddr = 0U;
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR; 
    if(!IS_DAC_ALIGN(Alignment)) return HAL_ERROR;  
    
    if (Channel == DAC_CHANNEL_1)
    {
        /* Enable the DAC DMA underrun interrupt */
        /* Enable the selected DAC channel2 DMA request */
        hdac->Instance->CR |= DAC_CR_EN1|DAC_CR_DMAEN1|DAC_CR_DMAUDRIE1;   
        /* Case of use of channel 1 */
        switch (Alignment)
        {
            case DAC_ALIGN_12B_R:
            /* Get DHR12R1 address */
            DstAddr = (uint32_t)&hdac->Instance->DHR12R1;
            break;
            case DAC_ALIGN_12B_L:
            /* Get DHR12L1 address */
            DstAddr = (uint32_t)&hdac->Instance->DHR12L1;
            break;
            case DAC_ALIGN_8B_R:
            /* Get DHR8R1 address */
            DstAddr = (uint32_t)&hdac->Instance->DHR8R1;
            break;
            default:
            break;
        }
        status = HAL_DMA_Start_IT(hdac->DMA_Handle1, (uint32_t)pData, DstAddr, Length); 
    }
    else if(Channel == DAC_CHANNEL_2)
    {
        /* Enable the DAC DMA underrun interrupt */
        /* Enable the selected DAC channel2 DMA request */
        hdac->Instance->CR |= DAC_CR_EN2|DAC_CR_DMAEN2|DAC_CR_DMAUDRIE2;   
      
        /* Case of use of channel 1 */
        switch (Alignment)
        {
            case DAC_ALIGN_12B_R:
            /* Get DHR12R1 address */
            DstAddr = (uint32_t)&hdac->Instance->DHR12R2;
            break;
            case DAC_ALIGN_12B_L:
            /* Get DHR12L1 address */
            DstAddr = (uint32_t)&hdac->Instance->DHR12L2;
            break;
            case DAC_ALIGN_8B_R:
            /* Get DHR8R1 address */
            DstAddr = (uint32_t)&hdac->Instance->DHR8R2;
            break;
            default:
            break;
        }
        status = HAL_DMA_Start_IT(hdac->DMA_Handle2, (uint32_t)pData, DstAddr, Length); 
    }
    else/* DualChannel */
    {
        hdac->Instance->CR |= DAC_CR_EN1|DAC_CR_DMAEN1|DAC_CR_DMAUDRIE1|DAC_CR_EN2 ;   
        /* Case of use of channel_1 DMA change two DAC channel */
        switch (Alignment)
        {
            case DAC_ALIGN_12B_R:
            /* Get DHR12R1 address */
            DstAddr = (uint32_t)&hdac->Instance->DHR12RD;
            break;
            case DAC_ALIGN_12B_L:
            /* Get DHR12L1 address */
            DstAddr = (uint32_t)&hdac->Instance->DHR12LD;
            break;
            case DAC_ALIGN_8B_R:
            /* Get DHR8R1 address */
            DstAddr = (uint32_t)&hdac->Instance->DHR8RD;
            break;
            default:
            break;
        }
        status = HAL_DMA_Start_IT(hdac->DMA_Handle1, (uint32_t)pData, DstAddr, Length); 
    }
    /* Return function status */
    return status;
}

/*********************************************************************************
* Function    : HAL_DAC_Stop_DMA
* Description :	Disables DAC and stop conversion of channel.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               Channel:This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2 @arg DAC_CHANNEL_Dual
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR; 
  
    /* Disable the selected DAC channel DMA request */
    /* Disable the DMA Channel */
    /* Channel1 is used */
    if(Channel == DAC_CHANNEL_1)
    { 
        hdac->Instance->CR &= ~DAC_CR_DMAEN1;
        /* Disable the Peripheral */
        hdac->Instance->CR&=~DAC_CR_EN1;
        status = HAL_DMA_Abort(hdac->DMA_Handle1);
    }
  
    else if(Channel == DAC_CHANNEL_2) /* Channel2 is used for */
    { 
        hdac->Instance->CR &= ~DAC_CR_DMAEN2;
        hdac->Instance->CR&=~DAC_CR_EN2;
        status = HAL_DMA_Abort(hdac->DMA_Handle2); 
    }
    else
    {
        hdac->Instance->CR &= ~DAC_CR_DMAEN1;
        hdac->Instance->CR &= ~DAC_CR_DMAEN2;
        /* Disable the Peripheral */
        hdac->Instance->CR&=~DAC_CR_EN1;
        hdac->Instance->CR&=~DAC_CR_EN2;
        status = HAL_DMA_Abort(hdac->DMA_Handle1)|HAL_DMA_Abort(hdac->DMA_Handle2);
    }
  
    /* Return function status */
    return status;
}

/*********************************************************************************
* Function    : HAL_DAC_SetChannelValue
* Description :	Set the specified data holding register value for DAC channel.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               Channel:This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @argDAC_CHANNEL_2
*               Alignment: Specifies the data alignment for DAC channel.This parameter can be one of the following values:
*                             @arg DAC_ALIGN_8B_R   @arg DAC_ALIGN_12B_L   @arg DAC_ALIGN_12B_R  
*                 Data:The destination peripheral Buffer address.          
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR; 
    if(!IS_DAC_ALIGN(Alignment)) return HAL_ERROR; 
    
    tmp = (uint32_t)hdac->Instance;
    if (Channel == DAC_CHANNEL_1)
    {
        tmp += DAC_DHR12R1_ALIGNMENT(Alignment);
    }
    else
    {
        tmp += DAC_DHR12R2_ALIGNMENT(Alignment);
    }
    
    /* Calculate and set dual DAC data holding register value */
    if (Alignment == DAC_ALIGN_12B_L)
    {
        Data = (uint32_t)Data << 4;
    }
  
    /* Set the DAC channel selected data holding register */
    *(__IO uint32_t *) tmp = Data;

    /* Return function status */
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DACEx_DualSetValue
* Description :	Set the specified data holding register value for dual DAC channel.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               Alignment: Specifies the data alignment for DAC channel.This parameter can be one of the following values:
*                             @arg DAC_ALIGN_8B_R   @arg DAC_ALIGN_12B_L   @arg DAC_ALIGN_12B_R  
*               Datax:The destination peripheral Buffer address.          
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DACEx_DualSetValue(DAC_HandleTypeDef *hdac, uint32_t Alignment, uint32_t Data1, uint32_t Data2)
{
    uint32_t data, tmp;
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_ALIGN(Alignment)) return HAL_ERROR; 

    /* Calculate and set dual DAC data holding register value */
    if (Alignment == DAC_ALIGN_12B_L)
    {
        data = ((uint32_t)Data2 << 20U) | (Data1<<4);
    }
    else
    {
        data = ((uint32_t)Data2 << 16U) | Data1;
    }

    tmp = (uint32_t)hdac->Instance;
    tmp += DAC_DHR12RD_ALIGNMENT(Alignment);

    /* Set the dual DAC selected data holding register */
    *(__IO uint32_t *)tmp = data;

    /* Return function status */
    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_DAC_GetValue
* Description :	Returns the last data output value of the selected DAC channel.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               Channel:This parameter can be one of the following values:  @arg  DAC_CHANNEL_1   @arg DAC_CHANNEL_2     
* Output      : The selected DAC channel data output value.
* Author      : CWT                         Data : 2020年
**********************************************************************************/
uint32_t HAL_DAC_GetValue(DAC_HandleTypeDef* hdac, uint32_t Channel)
{
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR; 
  
    /* Returns the DAC channel data output register value */
    if(Channel == DAC_CHANNEL_1)
    {
        return hdac->Instance->DOR1;
    }
    else
    {
        return hdac->Instance->DOR2;
    }

}


/*********************************************************************************
* Function    : HAL_DACEx_DualGetValue
* Description :	Return the last data output value of the selected DAC channel.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.      
* Output      : The selected DAC channel data output value.
* Author      : CWT                         Data : 2020年
**********************************************************************************/
uint32_t HAL_DACEx_DualGetValue(DAC_HandleTypeDef *hdac)
{
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    uint32_t tmp = 0U;

    tmp |= hdac->Instance->DOR1;

    tmp |= hdac->Instance->DOR2 << 16U;

    /* Returns the DAC channel data output register value */
    return tmp;
}

/*********************************************************************************
* Function    :HAL_DACEx_TriangleWaveGenerate
* Description :	Enable or disable the selected DAC channel wave generation.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               Channel:The selected DAC channel.   This parameter can be one of the following values:
*                       @arg DAC_CHANNEL_1: DAC Channel1 selected
*                       @arg DAC_CHANNEL_2: DAC Channel2 selected
*              Amplitude:  Amplitude Select max triangle amplitude.
*                          This parameter can be one of the following values:
*                         @arg DAC_TRIANGLEAMPLITUDE_1: Select max triangle amplitude of 1
*                         @arg DAC_TRIANGLEAMPLITUDE_3: Select max triangle amplitude of 3
*                         @arg DAC_TRIANGLEAMPLITUDE_7: Select max triangle amplitude of 7
*                         @arg DAC_TRIANGLEAMPLITUDE_15: Select max triangle amplitude of 15
*                         @arg DAC_TRIANGLEAMPLITUDE_31: Select max triangle amplitude of 31
*                         @arg DAC_TRIANGLEAMPLITUDE_63: Select max triangle amplitude of 63
*                         @arg DAC_TRIANGLEAMPLITUDE_127: Select max triangle amplitude of 127
*                         @arg DAC_TRIANGLEAMPLITUDE_255: Select max triangle amplitude of 255
*                         @arg DAC_TRIANGLEAMPLITUDE_511: Select max triangle amplitude of 511
*                         @arg DAC_TRIANGLEAMPLITUDE_1023: Select max triangle amplitude of 1023
*                         @arg DAC_TRIANGLEAMPLITUDE_2047: Select max triangle amplitude of 2047
*                         @arg DAC_TRIANGLEAMPLITUDE_4095: Select max triangle amplitude of 4095
* Author      : CWT                         Data : 2020年
**********************************************************************************/

HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude)
{
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR;
    if(!IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude)) return HAL_ERROR;
    /* Enable the triangle wave generation for the selected DAC channel */
    MODIFY_REG(hdac->Instance->CR, ((DAC_CR_WAVE1) | (DAC_CR_MAMP1)) << (Channel & 0x10UL), (DAC_CR_WAVE1_1 | Amplitude) << (Channel & 0x10UL));

    /* Return function status */
    return HAL_OK;
}


  
  /*********************************************************************************
* Function    : HAL_DACEx_NoiseWaveGenerate
* Description :	Enable or disable the selected DAC channel wave generation
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               Channel:The selected DAC channel.   This parameter can be one of the following values:
*                       @arg DAC_CHANNEL_1: DAC Channel1 selected
*                       @arg DAC_CHANNEL_2: DAC Channel2 selected
*            Amplitude: Amplitude Unmask DAC channel LFSR for noise wave generation.
*                        This parameter can be one of the following values:
*                        @arg DAC_LFSRUNMASK_BIT0: Unmask DAC channel LFSR bit0 for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS1_0: Unmask DAC channel LFSR bit[1:0] for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS2_0: Unmask DAC channel LFSR bit[2:0] for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS3_0: Unmask DAC channel LFSR bit[3:0] for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS4_0: Unmask DAC channel LFSR bit[4:0] for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS5_0: Unmask DAC channel LFSR bit[5:0] for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS6_0: Unmask DAC channel LFSR bit[6:0] for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS7_0: Unmask DAC channel LFSR bit[7:0] for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS8_0: Unmask DAC channel LFSR bit[8:0] for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS9_0: Unmask DAC channel LFSR bit[9:0] for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS10_0: Unmask DAC channel LFSR bit[10:0] for noise wave generation
*                        @arg DAC_LFSRUNMASK_BITS11_0: Unmask DAC channel LFSR bit[11:0] for noise wave generation
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude)
{
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR;
    if(!IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude)) return HAL_ERROR;
    /* Enable the noise wave generation for the selected DAC channel */
    MODIFY_REG(hdac->Instance->CR, ((DAC_CR_WAVE1) | (DAC_CR_MAMP1)) << (Channel & 0x10UL), (DAC_CR_WAVE1_0 | Amplitude) << (Channel & 0x10UL));
    /* Return function status */
    return HAL_OK;
}


/*********************************************************************************
* Function    : HAL_DACEx_SelfCalibrate
* Description :	SRun the self calibration of one DAC channel.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               sConfig:sConfig DAC channel configuration structure
*               Channel:The selected DAC channel.   This parameter can be one of the following values:
*                       @arg DAC_CHANNEL_1: DAC Channel1 selected
*                       @arg DAC_CHANNEL_2: DAC Channel2 selected
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DACEx_SelfCalibrate(DAC_HandleTypeDef *hdac, DAC_ChannelConfTypeDef *sConfig, uint32_t Channel)
{
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR;

    HAL_StatusTypeDef status = HAL_OK;

    __IO uint32_t tmp;
    uint32_t trimmingvalue;
    uint32_t laststatus=0;
    uint32_t nowstatus=0;
    
    SET_BIT((hdac->Instance->CR), (DAC_CR_EN1 << (Channel & 0x10UL)));
    tmp = (uint32_t)hdac->Instance;
    if (Channel == DAC_CHANNEL_1)
    {
        tmp += DAC_DHR12R1_ALIGNMENT(DAC_ALIGN_12B_R);
    }
    else
    {
        tmp += DAC_DHR12R2_ALIGNMENT(DAC_ALIGN_12B_R);
    }

    *(__IO uint32_t *) tmp = 0x0800U;

    /* Enable the selected DAC channel calibration */
    /* i.e. set DAC_CR_CENx bit */
    SET_BIT((hdac->Instance->CR), (DAC_CR_CEN1 << (Channel & 0x10UL)));

    /* Init trimming counter */
    /* Medium value ,trimmingvalue:0-31(0x1f)*/
    for(trimmingvalue=0;trimmingvalue<32;trimmingvalue++)
    {
        /* Set candidate trimming */
        MODIFY_REG(hdac->Instance->CCR, (DAC_CCR_OTRIM1 << (Channel & 0x10UL)), (trimmingvalue << (Channel & 0x10UL)));
        System_Delay_MS(1);
        laststatus=nowstatus;
        nowstatus=(hdac->Instance->SR & (DAC_SR_CAL_FLAG1 << (Channel & 0x10UL)))>>(DAC_SR_CAL_FLAG1_Pos +Channel);
        /* tOFFTRIMmax delay x ms as per datasheet (electrical characteristics */
        /* i.e. minimum time needed between two calibration steps */
        if (nowstatus==1&&laststatus==0)
        {
            break;
        }
    }
    
    /* Disable the selected DAC channel calibration */
    /* i.e. clear DAC_CR_CENx bit */
    CLEAR_BIT((hdac->Instance->CR), (DAC_CR_CEN1 << (Channel & 0x10UL)));

    /* Disable the selected DAC channel */
    CLEAR_BIT((hdac->Instance->CR), (DAC_CR_EN1 << (Channel & 0x10UL)));

    sConfig->DAC_TrimmingValue = trimmingvalue;
    sConfig->DAC_UserTrimming = DAC_TRIMMING_USER;

    return status;
}


/*********************************************************************************
* Function    : HAL_DACEx_SetUserTrimming
* Description :	Set the trimming mode and trimming value (user trimming mode applied).
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               sConfig:sConfig DAC channel configuration structure
*               Channel:The selected DAC channel.   This parameter can be one of the following values:
*                       @arg DAC_CHANNEL_1: DAC Channel1 selected
*                       @arg DAC_CHANNEL_2: DAC Channel2 selected
*               NewTrimmingValue: DAC new trimming value
* Output      : HAL status
* Author      : CWT                         Data : 2020年
**********************************************************************************/
HAL_StatusTypeDef HAL_DACEx_SetUserTrimming(DAC_HandleTypeDef *hdac, DAC_ChannelConfTypeDef *sConfig, uint32_t Channel, uint32_t NewTrimmingValue)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR;
    if(!IS_DAC_Calibration_TRIM(NewTrimmingValue)) return HAL_ERROR;
    
    /* Check the DAC handle allocation */
    if (hdac == NULL)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Set new trimming */
        MODIFY_REG(hdac->Instance->CCR, (DAC_CCR_OTRIM1 << (Channel & 0x10UL)), (NewTrimmingValue << (Channel & 0x10UL)));
        /* Update trimming mode */
        sConfig->DAC_UserTrimming = DAC_TRIMMING_USER;
        sConfig->DAC_TrimmingValue = NewTrimmingValue;
    }
    return status;
}


/*********************************************************************************
* Function    : HAL_DACEx_GetTrimOffset
* Description :	Return the DAC trimming value.
* Input       : hdac : hdac pointer to a DAC_HandleTypeDef structure that contains
*                     the configuration information for the specified DAC.
*               Channel:The selected DAC channel.   This parameter can be one of the following values:
*                       @arg DAC_CHANNEL_1: DAC Channel1 selected
*                       @arg DAC_CHANNEL_2: DAC Channel2 selected
* Output      : Trimming value : range: 0->31
* Author      : CWT                         Data : 2020年
**********************************************************************************/
uint32_t HAL_DACEx_GetTrimOffset(DAC_HandleTypeDef *hdac, uint32_t Channel)
{
    /* Check the parameters */
    if(!IS_DAC_ALL_PERIPH(hdac->Instance)) return HAL_ERROR;
    if(!IS_DAC_CHANNEL(Channel)) return HAL_ERROR;

    /* Retrieve trimming  */
    return ((hdac->Instance->CCR & (DAC_CCR_OTRIM1 << (Channel & 0x10UL))) >> (Channel & 0x10UL));
}
