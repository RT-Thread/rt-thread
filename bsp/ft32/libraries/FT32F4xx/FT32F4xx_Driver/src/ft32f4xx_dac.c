/**
  ******************************************************************************
  * @file               ft32f4xx_dac.c
  * @author             FMD xzhang
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the comparators (DAC1 DAC2 ) peripheral:
  *                      + DAC triangle
  *                      + DAC Noise wave
  * @version            V1.0.0
  * @data                   2025-03-20
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_dac.h"
/* Exported types ------------------------------------------------------------*/
/** @defgroup DAC_Exported_Types DAC Exported Types
  * @{

  ==============================================================================
              ##### Initialization and de-initialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the DAC.
      (+) De-initialize the DAC.
*/
/*
  * @brief  Initialize the DAC peripheral according to the specified parameters
  *         in the DAC_InitStruct and initialize the associated handle.
  * @param  DAC_1_2_Selection: the selected  DAC
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1 : DAC1 selected
  *            @arg DAC_CHANNEL_2 : DAC2 selected
  *            @arg DAC_CHANNEL_D12:DAC1 and DAC2 selected
  * @param  DAC_InitStruct: pointer to a DAC_InitTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval
*/
void DAC_Init(uint32_t DAC_1_2_Selection, DAC_InitTypeDef* DAC_InitStruct)
{
    uint16_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_DAC_1_2_PERIPH(DAC_1_2_Selection));
    assert_param(IS_DAC_BUFFER(DAC_InitStruct -> DAC_OutputBuffer));
    assert_param(IS_DAC_TRIGGER(DAC_InitStruct -> DAC_trigger));

    /*!< Configure : DAC_Trigger / DAC_OutputBuffer/DAC_Input_sel/DAC_Output_sel*/
    tmpreg = (uint16_t)((DAC_InitStruct ->DAC_Trigger | DAC_InitStruct -> DAC_OutputBuffer | DAC_InitStruct ->DAC_Input_sel |  DAC_InitStruct -> DAC_Output_sel));

    if (DAC_1_2_Selection == DAC_CHANNEL_1)           //config DAC1
    {
        /*!< Write to DAC_CSR register */
        COMP_OPAM_DAC -> DAC_CR |= (uint32_t) tmpreg;
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_2)      //config DAC2
    {
        /*!< Write to DAC_CSR register */
        COMP_OPAM_DAC -> DAC_CR |= (uint32_t)(tmpreg << 16);
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_D12)    //config DAC1 and DAC2 sametime
    {
        /*!< Write to DAC_CSR register */
        COMP_OPAM_DAC -> DAC_CR |= (uint32_t)((tmpreg << 16) | tmpreg);
    }
}


/**
  * @brief  Deinitializes DAC peripheral registers to their default reset values.
  * @note   Deinitializes DAC_CR DAC_SR
  * @param  DAC_1_2_Selection: the selected  DAC
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1 : DAC1 selected
  *            @arg DAC_CHANNEL_2 : DAC2 selected
  *            @arg DAC_CHANNEL_D12:DAC1 and DAC2 selected
  * @retval None
  */
void DAC_DeInit(uint32_t DAC_1_2_Selection)
{
    /* Check the parameters */
    assert_param(IS_DAC_1_2_PERIPH(DAC_1_2_Selection));

    if (DAC_1_2_Selection == DAC_CHANNEL_1)
    {
        /*!< Write to DAC_CSR register */
        COMP_OPAM_DAC -> DAC_CR &= 0xffff0000;
        /*DAC_SR:RC_W1*/
        COMP_OPAM_DAC -> DAC_SR |= DMAUDR1;
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_2)
    {
        /*!< Write to DAC_CSR register */
        COMP_OPAM_DAC -> DAC_CR &= 0x0000ffff;
        /*DAC_SR:RC_W1*/
        COMP_OPAM_DAC -> DAC_SR |= DMAUDR2;
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_D12)
    {
        /*!< Write to DAC_CSR register */
        COMP_OPAM_DAC -> DAC_CR &= 0x00000000;
        COMP_OPAM_DAC -> DAC_SR |= DMAUDR1 | DMAUDR2;
    }
}
/**
  * @brief  Enables DAC and starts conversion of channel by soft trriger once.
  *         the configuration information for the specified DAC.
  * @param  DAC_1_2_Selection The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_D12:DAC1 and DAC2 selected
  * @retval
  */
void DAC_Start(uint32_t DAC_1_2_Selection)
{
    /* Check the parameters */
    assert_param(IS_DAC_1_2_PERIPH(DAC_1_2_Selection));

    /* Enable the Peripheral */
    if (DAC_1_2_Selection == DAC_CHANNEL_D12)
    {
        COMP_OPAM_DAC -> DAC_CR |= EN1 | EN2;
    }
    else
    {
        /*Enable DAC1 or DAC2*/
        COMP_OPAM_DAC -> DAC_CR |= (EN1 << (DAC_1_2_Selection & 0x10UL)) ;
    }
    //software trriger mode
    if (DAC_1_2_Selection == DAC_CHANNEL_1)
    {
        /* Check if software trigger enabled */
        if (((COMP_OPAM_DAC -> DAC_CR)  & (TEN1 | DAC_CR_TSEL1_Msk)) == DAC_TRIGGER_SOFTWARE)
        {
            /* Enable the selected DAC1 software conversion */
            COMP_OPAM_DAC -> DAC_SWTRIGR |= SWTRIGR1;
        }
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_2)
    {
        /* Check if software trigger enabled */
        if (((COMP_OPAM_DAC -> DAC_CR) & (TEN2 | DAC_CR_TSEL2_Msk)) == (DAC_TRIGGER_SOFTWARE << (DAC_1_2_Selection & 0x10UL)))
        {
            /* Enable the selected DAC2 software conversion */
            COMP_OPAM_DAC -> DAC_SWTRIGR |= SWTRIGR2;
        }
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_D12)
    {
        /* Check if software trigger enabled */
        if (((COMP_OPAM_DAC -> DAC_CR)  & (TEN1 | DAC_CR_TSEL1_Msk | TEN2 | DAC_CR_TSEL2_Msk)) == (DAC_TRIGGER_SOFTWARE | (DAC_TRIGGER_SOFTWARE << 0x10UL)))
        {
            /* Enable the selected DAC1 DAC2 software conversion */
            COMP_OPAM_DAC -> DAC_SWTRIGR |= SWTRIGR1;
            COMP_OPAM_DAC -> DAC_SWTRIGR |= SWTRIGR2;
        }
    }
}
/**
  * @brief  Disables DAC and stop conversion of channel.
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_D12:DAC1 and DAC2 selected
  * @retval
  */
void DAC_STOP(uint32_t DAC_1_2_Selection)
{
    /* Check the parameters */
    assert_param(IS_DAC_1_2_PERIPH(DAC_1_2_Selection));

    if (DAC_1_2_Selection == DAC_CHANNEL_1)
    {
        /* disable the Peripheral */
        COMP_OPAM_DAC -> DAC_CR &= ~EN1;
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_2)
    {
        /* disable the Peripheral */
        COMP_OPAM_DAC -> DAC_CR &= ~EN2;
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_D12)
    {
        /* disable the Peripheral */
        COMP_OPAM_DAC -> DAC_CR &= (~EN1 & ~EN2);
    }
}

/**
  * @brief  Set the specified data holding register value for DAC channel.
  * @param  DAC_1_2_Selection:  The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_D12: DAC Channel2 selected
  * @param  Alignment: Specifies the data alignment.
  *          This parameter can be one of the following values:
  *            @arg DAC_ALIGN_8B_R: 8bit right data alignment selected
  *            @arg DAC_ALIGN_12B_L: 12bit left data alignment selected
  *            @arg DAC_ALIGN_12B_R: 12bit right data alignment selected
  * @param  Data :Data to be loaded in the selected data holding register.
  * @retval
  */
void DAC_SetValue(uint32_t DAC_1_2_Selection, uint32_t Alignment, uint32_t Data)
{

    /* Check the parameters */
    assert_param(IS_DAC_1_2_PERIPH(DAC_1_2_Selection));
    assert_param(IS_DAC_ALIGN(Alignment));

    if (DAC_1_2_Selection == DAC_CHANNEL_1)         //Data to DAC1
    {
        if (Alignment == DAC_ALIGN_12B_R)   //Data to DHR12R1
        {
            COMP_OPAM_DAC -> DAC_DHR12R1 = Data;
        }
        else if (Alignment == DAC_ALIGN_12B_L) //Data to DHR12L1
        {
            COMP_OPAM_DAC -> DAC_DHR12L1 = Data;
        }
        else if (Alignment == DAC_ALIGN_8B_R) //Data to DHR8R1
        {
            COMP_OPAM_DAC -> DAC_DHR8R1 = Data;
        }
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_2)      //Data to DAC2
    {
        if (Alignment == DAC_ALIGN_12B_R)   //Data to DHR12R2
        {
            COMP_OPAM_DAC -> DAC_DHR12R2 = Data;
        }
        else if (Alignment == DAC_ALIGN_12B_L) //Data to DHR12L2
        {
            COMP_OPAM_DAC -> DAC_DHR12L2 = Data;
        }
        else if (Alignment == DAC_ALIGN_8B_R) //Data to DHR8R2
        {
            COMP_OPAM_DAC -> DAC_DHR8R2 = Data;
        }
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_D12)      //Data to DAC double
    {
        if (Alignment == DAC_ALIGN_12B_R)   //Data to DHR12RD
        {
            COMP_OPAM_DAC -> DAC_DHR12RD = Data;
        }
        else if (Alignment == DAC_ALIGN_12B_L) //Data to DHR12LD
        {
            COMP_OPAM_DAC -> DAC_DHR12LD = Data;
        }
        else if (Alignment == DAC_ALIGN_8B_R) //Data to DHR8RD
        {
            COMP_OPAM_DAC -> DAC_DHR8RD = Data;
        }
    }
}


/**
  * @brief  Return the last data output value of the selected DAC channel.
  * @param  DAC_1_2_Selection The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  * @retval The selected DAC channel data output value.
  */
uint32_t DAC_GetValue(uint32_t DAC_1_2_Selection)
{
    uint32_t result ;

    /* Check the parameters */
    assert_param(IS_DAC_1_2_PERIPH(DAC_1_2_Selection));
    /*delay to read for wait DAC */
    Delay_read();

    if (DAC_1_2_Selection == DAC_CHANNEL_1)
    {
        result = COMP_OPAM_DAC -> DAC_DOR1 ;
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_2)
    {
        result = COMP_OPAM_DAC -> DAC_DOR2 ;
    }
    /* Returns the DAC channel data output register value */
    return result;
}




/**
  * @brief  Enables DAC DMA mode and enable DMA under interrupt.
  * @param  DAC_1_2_Selection The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_D12:DAC1 and DAC2 selected
  * @param  NewState: new state of the DAC 's DMA interrupt.
  *          This parameter can be: ENABLE or DISABLE .
  * @retval
  */
void DAC_Start_DMA(uint32_t DAC_1_2_Selection, FunctionalState NewState)
{
    assert_param(IS_DAC_1_2_PERIPH(DAC_1_2_Selection));

    if (DAC_1_2_Selection == DAC_CHANNEL_1)
    {
        /* Enable the selected DAC channel1 DMA request */
        COMP_OPAM_DAC -> DAC_CR |= DMAEN1;

        if (NewState != DISABLE)
        {
            /* Enable the DAC DMA underrun interrupt */
            COMP_OPAM_DAC -> DAC_CR |= DMAUDRIE1;
        }
        else if (NewState == DISABLE)
        {
            /* Disable the DAC DMA underrun interrupt */
            COMP_OPAM_DAC -> DAC_CR &= ~DMAUDRIE1;
        }
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_2)
    {
        /* Enable the selected DAC channel1 DMA request */
        COMP_OPAM_DAC -> DAC_CR |= DMAEN2;
        /* Enable the DAC DMA underrun interrupt */
        if (NewState != DISABLE)
        {
            COMP_OPAM_DAC -> DAC_CR |= DMAUDRIE2;
        }
        else if (NewState == DISABLE)
        {
            /* Disable the DAC DMA underrun interrupt */
            COMP_OPAM_DAC -> DAC_CR &= ~DMAUDRIE2;
        }
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_D12)
    {
        COMP_OPAM_DAC -> DAC_CR |= DMAEN1 | DMAEN2;

        if (NewState != DISABLE)
        {
            COMP_OPAM_DAC -> DAC_CR |= DMAUDRIE1 | DMAUDRIE2;
        }
        else if (NewState == DISABLE)
        {
            /* Disable the DAC DMA underrun interrupt */
            COMP_OPAM_DAC -> DAC_CR &= (~DMAUDRIE1) & (~DMAUDRIE2);
        }
    }
}


/**
  * @brief  Disable DAC DMA mode and disable DMA under interrupt.
  * @param  DAC_1_2_Selection The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_D12:DAC1 and DAC2 selected
  * @retval
  */
void DAC_Stop_DMA(uint32_t DAC_1_2_Selection)
{
    assert_param(IS_DAC_1_2_PERIPH(DAC_1_2_Selection));

    if (DAC_1_2_Selection == DAC_CHANNEL_1)
    {
        /* Disable the selected DAC channel1 DMA request */
        COMP_OPAM_DAC -> DAC_CR &= ~DMAEN1;
        /* Disable the DAC DMA underrun interrupt */
        COMP_OPAM_DAC -> DAC_CR &= ~DMAUDRIE1;
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_2)
    {
        /* Disable the selected DAC channel1 DMA request */
        COMP_OPAM_DAC -> DAC_CR &= ~DMAEN2;
        /* Disable the DAC DMA underrun interrupt */
        COMP_OPAM_DAC -> DAC_CR &= ~DMAUDRIE2;
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_D12)
    {
        /* Disable the selected DAC channel1 DMA request */
        COMP_OPAM_DAC -> DAC_CR &= ~DMAEN1 & ~DMAEN2;
        /* Disable the DAC DMA underrun interrupt */
        COMP_OPAM_DAC -> DAC_CR &= (~DMAUDRIE1) & (~DMAUDRIE2);
    }
}


/**
  * @brief  Enable or disable the selected DAC channel wave generation ,DAC_Init and DAC_Start used firstly.
  * @param  DAC_1_2_Selection The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  *            @arg DAC_CHANNEL_D12:DAC1 and DAC2 selected
  * @param  Amplitude Select max triangle amplitude.
  *          This parameter can be one of the following values:
  *            @arg DAC_TRIANGLEAMPLITUDE_1: Select max triangle amplitude of 1
  *            @arg DAC_TRIANGLEAMPLITUDE_3: Select max triangle amplitude of 3
  *            @arg DAC_TRIANGLEAMPLITUDE_7: Select max triangle amplitude of 7
  *            @arg DAC_TRIANGLEAMPLITUDE_15: Select max triangle amplitude of 15
  *            @arg DAC_TRIANGLEAMPLITUDE_31: Select max triangle amplitude of 31
  *            @arg DAC_TRIANGLEAMPLITUDE_63: Select max triangle amplitude of 63
  *            @arg DAC_TRIANGLEAMPLITUDE_127: Select max triangle amplitude of 127
  *            @arg DAC_TRIANGLEAMPLITUDE_255: Select max triangle amplitude of 255
  *            @arg DAC_TRIANGLEAMPLITUDE_511: Select max triangle amplitude of 511
  *            @arg DAC_TRIANGLEAMPLITUDE_1023: Select max triangle amplitude of 1023
  *            @arg DAC_TRIANGLEAMPLITUDE_2047: Select max triangle amplitude of 2047
  *            @arg DAC_TRIANGLEAMPLITUDE_4095: Select max triangle amplitude of 4095
  * @retval
  */
void DAC_TriangleWaveGenerate(uint32_t DAC_1_2_Selection, uint32_t Amplitude)
{
    /* Check the parameters */
    assert_param(IS_DAC_1_2_PERIPH(DAC_1_2_Selection));
    assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude));

    if (DAC_1_2_Selection == DAC_CHANNEL_1)
    {
        /* enable DAC1 triangle */
        COMP_OPAM_DAC -> DAC_CR |= WAVE1_1;
        COMP_OPAM_DAC -> DAC_CR |= Amplitude;
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_2)
    {
        /* enable DAC2 triangle */
        COMP_OPAM_DAC -> DAC_CR |= WAVE2_1;
        COMP_OPAM_DAC -> DAC_CR |= Amplitude << (DAC_1_2_Selection & 0x10UL);
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_D12)
    {
        /* enable DAC1 2 triangle */
        COMP_OPAM_DAC -> DAC_CR |= WAVE1_1 | WAVE2_1;
        COMP_OPAM_DAC -> DAC_CR |= ((Amplitude << (DAC_CHANNEL_2 & 0x10UL)) | Amplitude);
    }
}


/**
  * @brief  Enable or disable the selected DAC channel wave generation.
  * @param  DAC_1_2_Selection The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  *            @arg DAC_CHANNEL_2: DAC Channel2 selected
  * @param  Amplitude Unmask DAC channel LFSR for noise wave generation.
  *          This parameter can be one of the following values:
  *            @arg DAC_LFSRUNMASK_BIT0: Unmask DAC channel LFSR bit0 for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS1_0: Unmask DAC channel LFSR bit[1:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS2_0: Unmask DAC channel LFSR bit[2:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS3_0: Unmask DAC channel LFSR bit[3:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS4_0: Unmask DAC channel LFSR bit[4:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS5_0: Unmask DAC channel LFSR bit[5:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS6_0: Unmask DAC channel LFSR bit[6:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS7_0: Unmask DAC channel LFSR bit[7:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS8_0: Unmask DAC channel LFSR bit[8:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS9_0: Unmask DAC channel LFSR bit[9:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS10_0: Unmask DAC channel LFSR bit[10:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS11_0: Unmask DAC channel LFSR bit[11:0] for noise wave generation
  * @retval
  */
void DAC_NoiseWaveGenerate(uint32_t DAC_1_2_Selection, uint32_t Amplitude)
{
    /* Check the parameters */
    assert_param(IS_DAC_1_2_PERIPH(DAC_1_2_Selection));
    assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude));

    if (DAC_1_2_Selection == DAC_CHANNEL_1)
    {
        /* enable DAC1 noise wave  */
        COMP_OPAM_DAC -> DAC_CR |= WAVE1_0;
        COMP_OPAM_DAC -> DAC_CR |= Amplitude;
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_2)
    {
        /* enable DAC2 noise wave  */
        COMP_OPAM_DAC -> DAC_CR |= WAVE2_0;
        COMP_OPAM_DAC -> DAC_CR |= Amplitude << (DAC_1_2_Selection & 0x10UL);
    }
    else if (DAC_1_2_Selection == DAC_CHANNEL_D12)
    {
        /* enable DAC1 2 noise wave  */
        COMP_OPAM_DAC -> DAC_CR |= WAVE1_0 | WAVE2_0;
        COMP_OPAM_DAC -> DAC_CR |= ((Amplitude << (DAC_CHANNEL_2 & 0x10UL)) | Amplitude);
    }
}

/**
  * @}
  */
void Delay_read(void)
{
    int m;
    for (m = 0; m < 15; m++)
    {
        __ASM("nop");
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

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
