/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g4fr_adc.c
 * @author Nations
 * @version v1.0.4
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g4fr_adc.h"
#include "n32g4fr_rcc.h"

/** @addtogroup N32G4FR_StdPeriph_Driver
 * @{
 */

/** @addtogroup ADC
 * @brief ADC driver modules
 * @{
 */

/** @addtogroup ADC_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup ADC_Private_Defines
 * @{
 */

/* ADC DISC_NUM mask */
#define CR1_DISCNUM_Reset ((uint32_t)0xFFFF1FFF)

/* ADC DISC_EN mask */
#define CTRL1_DISC_EN_SET   ((uint32_t)0x00000800)
#define CTRL1_DISC_EN_RESET ((uint32_t)0xFFFFF7FF)

/* ADC INJ_AUTO mask */
#define CR1_JAUTO_Set   ((uint32_t)0x00000400)
#define CR1_JAUTO_Reset ((uint32_t)0xFFFFFBFF)

/* ADC INJ_DISC_EN mask */
#define CTRL1_INJ_DISC_EN_SET   ((uint32_t)0x00001000)
#define CTRL1_INJ_DISC_EN_RESET ((uint32_t)0xFFFFEFFF)

/* ADC AWDG_CH mask */
#define CTRL1_AWDG_CH_RESET ((uint32_t)0xFFFFFFE0)

/* ADC Analog watchdog enable mode mask */
#define CTRL1_AWDG_MODE_RESET ((uint32_t)0xFF3FFDFF)

/* CTRL1 register Mask */
#define CTRL1_CLR_MASK ((uint32_t)0xFFF0FEFF)

/* ADC AD_ON mask */
#define CTRL2_AD_ON_SET   ((uint32_t)0x00000001)
#define CTRL2_AD_ON_RESET ((uint32_t)0xFFFFFFFE)

/* ADC DMA mask */
#define CTRL2_DMA_SET   ((uint32_t)0x00000100)
#define CTRL2_DMA_RESET ((uint32_t)0xFFFFFEFF)

/* ADC RST_CALI mask */
#define CTRL2_RST_CALI_SET ((uint32_t)0x00000008)

/* ADC CAL mask */
#define CTRL2_CAL_SET ((uint32_t)0x00000004)

/* ADC SOFT_START mask */
#define CTRL2_SOFT_START_SET ((uint32_t)0x00400000)

/* ADC EXT_TRIG mask */
#define CTRL2_EXT_TRIG_SET   ((uint32_t)0x00100000)
#define CTRL2_EXT_TRIG_RESET ((uint32_t)0xFFEFFFFF)

/* ADC Software start mask */
#define CTRL2_EXT_TRIG_SWSTART_SET   ((uint32_t)0x00500000)
#define CTRL2_EXT_TRIG_SWSTART_RESET ((uint32_t)0xFFAFFFFF)

/* ADC INJ_EXT_SEL mask */
#define CTRL2_INJ_EXT_SEL_RESET ((uint32_t)0xFFFF8FFF)

/* ADC INJ_EXT_TRIG mask */
#define CTRL2_INJ_EXT_TRIG_SET   ((uint32_t)0x00008000)
#define CTRL2_INJ_EXT_TRIG_RESET ((uint32_t)0xFFFF7FFF)

/* ADC INJ_SWSTART mask */
#define CTRL2_INJ_SWSTART_SET ((uint32_t)0x00200000)

/* ADC injected software start mask */
#define CTRL2_INJ_EXT_TRIG_JSWSTART_SET   ((uint32_t)0x00208000)
#define CTRL2_INJ_EXT_TRIG_JSWSTART_RESET ((uint32_t)0xFFDF7FFF)

/* ADC TSPD mask */
#define CTRL2_TSVREFE_SET   ((uint32_t)0x00800000)
#define CTRL2_TSVREFE_RESET ((uint32_t)0xFF7FFFFF)

/* CTRL2 register Mask */
#define CTRL2_CLR_MASK ((uint32_t)0xFFF1F7FD)

/* ADC SQx mask */
#define SQR4_SEQ_SET ((uint32_t)0x0000001F)
#define SQR3_SEQ_SET ((uint32_t)0x0000001F)
#define SQR2_SEQ_SET ((uint32_t)0x0000001F)
#define SQR1_SEQ_SET ((uint32_t)0x0000001F)

/* RSEQ1 register Mask */
#define RSEQ1_CLR_MASK ((uint32_t)0xFF0FFFFF)

/* ADC JSQx mask */
#define JSEQ_JSQ_SET ((uint32_t)0x0000001F)

/* ADC INJ_LEN mask */
#define JSEQ_INJ_LEN_SET   ((uint32_t)0x00300000)
#define JSEQ_INJ_LEN_RESET ((uint32_t)0xFFCFFFFF)

/* ADC SAMPTx mask */
#define SAMPT1_SMP_SET ((uint32_t)0x00000007)
#define SAMPT2_SMP_SET ((uint32_t)0x00000007)

/* ADC JDATx registers offset */
#define JDAT_OFFSET ((uint8_t)0x28)

/* ADC1 DAT register base address */
#define DAT_ADDR ((uint32_t)0x4001244C)

/* ADC STS register mask */
#define ADC_STS_RESERVE_MASK    ((uint32_t)0x0000007F)    

/**
 * @}
 */

/** @addtogroup ADC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup ADC_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup ADC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup ADC_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the ADCx peripheral registers to their default reset values.
 * @param ADCx where x can be 1, 2 to select the ADC peripheral.
 */
void ADC_DeInit(ADC_Module* ADCx)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));

    if (ADCx == ADC1)
    {
        /* Enable ADC1 reset state */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC1, ENABLE);
        /* Release ADC1 from reset state */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC1, DISABLE);
    }
    else if (ADCx == ADC2)
    {
        /* Enable ADC2 reset state */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC2, ENABLE);
        /* Release ADC2 from reset state */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC2, DISABLE);
    }
}

/**
 * @brief  Initializes the ADCx peripheral according to the specified parameters
 *         in the ADC_InitStruct.
 * @param ADCx where x can be 1, 2  to select the ADC peripheral.
 * @param ADC_InitStruct pointer to an ADC_InitType structure that contains
 *         the configuration information for the specified ADC peripheral.
 */
void ADC_Init(ADC_Module* ADCx, ADC_InitType* ADC_InitStruct)
{
    uint32_t tmpreg1 = 0;
    uint8_t tmpreg2  = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcWorkMode(ADC_InitStruct->WorkMode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->MultiChEn));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ContinueConvEn));
    assert_param(IsAdcExtTrig(ADC_InitStruct->ExtTrigSelect));
    assert_param(IsAdcDatAlign(ADC_InitStruct->DatAlign));
    assert_param(IsAdcSeqLenValid(ADC_InitStruct->ChsNumber));

    /*---------------------------- ADCx CTRL1 Configuration -----------------*/
    /* Get the ADCx CTRL1 value */
    tmpreg1 = ADCx->CTRL1;
    /* Clear DUALMOD and SCAN bits */
    tmpreg1 &= CTRL1_CLR_MASK;
    /* Configure ADCx: Dual mode and scan conversion mode */
    /* Set DUALMOD bits according to WorkMode value */
    /* Set SCAN bit according to MultiChEn value */
    tmpreg1 |= (uint32_t)(ADC_InitStruct->WorkMode | ((uint32_t)ADC_InitStruct->MultiChEn << 8));
    /* Write to ADCx CTRL1 */
    ADCx->CTRL1 = tmpreg1;

    /*---------------------------- ADCx CTRL2 Configuration -----------------*/
    /* Get the ADCx CTRL2 value */
    tmpreg1 = ADCx->CTRL2;
    /* Clear CONT, ALIGN and EXTSEL bits */
    tmpreg1 &= CTRL2_CLR_MASK;
    /* Configure ADCx: external trigger event and continuous conversion mode */
    /* Set ALIGN bit according to DatAlign value */
    /* Set EXTSEL bits according to ExtTrigSelect value */
    /* Set CONT bit according to ContinueConvEn value */
    tmpreg1 |= (uint32_t)(ADC_InitStruct->DatAlign | ADC_InitStruct->ExtTrigSelect
                          | ((uint32_t)ADC_InitStruct->ContinueConvEn << 1));
    /* Write to ADCx CTRL2 */
    ADCx->CTRL2 = tmpreg1;

    /*---------------------------- ADCx RSEQ1 Configuration -----------------*/
    /* Get the ADCx RSEQ1 value */
    tmpreg1 = ADCx->RSEQ1;
    /* Clear L bits */
    tmpreg1 &= RSEQ1_CLR_MASK;
    /* Configure ADCx: regular channel sequence length */
    /* Set L bits according to ChsNumber value */
    tmpreg2 |= (uint8_t)(ADC_InitStruct->ChsNumber - (uint8_t)1);
    tmpreg1 |= (uint32_t)tmpreg2 << 20;
    /* Write to ADCx RSEQ1 */
    ADCx->RSEQ1 = tmpreg1;
}

/**
 * @brief  Fills each ADC_InitStruct member with its default value.
 * @param ADC_InitStruct pointer to an ADC_InitType structure which will be initialized.
 */
void ADC_InitStruct(ADC_InitType* ADC_InitStruct)
{
    /* Reset ADC init structure parameters values */
    /* Initialize the WorkMode member */
    ADC_InitStruct->WorkMode = ADC_WORKMODE_INDEPENDENT;
    /* initialize the MultiChEn member */
    ADC_InitStruct->MultiChEn = DISABLE;
    /* Initialize the ContinueConvEn member */
    ADC_InitStruct->ContinueConvEn = DISABLE;
    /* Initialize the ExtTrigSelect member */
    ADC_InitStruct->ExtTrigSelect = ADC_EXT_TRIGCONV_T1_CC1;
    /* Initialize the DatAlign member */
    ADC_InitStruct->DatAlign = ADC_DAT_ALIGN_R;
    /* Initialize the ChsNumber member */
    ADC_InitStruct->ChsNumber = 1;
}

/**
 * @brief  Enables or disables the specified ADC peripheral.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the ADCx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_Enable(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Set the AD_ON bit to wake up the ADC from power down mode */
        ADCx->CTRL2 |= CTRL2_AD_ON_SET;
    }
    else
    {
        /* Disable the selected ADC peripheral */
        ADCx->CTRL2 &= CTRL2_AD_ON_RESET;
    }
}

/**
 * @brief  Enables or disables the specified ADC DMA request.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC DMA transfer.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableDMA(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcDmaModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC DMA request */
        ADCx->CTRL2 |= CTRL2_DMA_SET;
    }
    else
    {
        /* Disable the selected ADC DMA request */
        ADCx->CTRL2 &= CTRL2_DMA_RESET;
    }
}

/**
 * @brief  Enables or disables the specified ADC interrupts.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_IT specifies the ADC interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_INT_ENDC End of conversion interrupt mask
 *     @arg ADC_INT_AWD Analog watchdog interrupt mask
 *     @arg ADC_INT_JENDC End of injected conversion interrupt mask
 * @param Cmd new state of the specified ADC interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_ConfigInt(ADC_Module* ADCx, uint16_t ADC_IT, FunctionalState Cmd)
{
    uint8_t itmask = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    assert_param(IsAdcInt(ADC_IT));
    /* Get the ADC IT index */
    itmask = (uint8_t)ADC_IT;
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        ADCx->CTRL1 |= itmask;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        ADCx->CTRL1 &= (~(uint32_t)itmask);
    }
}



/**
 * @brief  Starts the selected ADC calibration process.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 */
void ADC_StartCalibration(ADC_Module* ADCx)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    /* Enable the selected ADC calibration process */
    if(ADCx->CALFACT==0)
        ADCx->CTRL2 |= CTRL2_CAL_SET;
}

/**
 * @brief  Gets the selected ADC calibration status.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @return The new state of ADC calibration (SET or RESET).
 */
FlagStatus ADC_GetCalibrationStatus(ADC_Module* ADCx)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    /* Check the status of CAL bit */
    if ((ADCx->CTRL2 & CTRL2_CAL_SET) != (uint32_t)RESET)
    {
        /* CAL bit is set: calibration on going */
        bitstatus = SET;
    }
    else
    {
        /* CAL bit is reset: end of calibration */
        bitstatus = RESET;
    }
    if(ADCx->CALFACT!=0)
        bitstatus = RESET;
    /* Return the CAL bit status */
    return bitstatus;
}

/**
 * @brief  Enables or disables the selected ADC software start conversion .
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC software start conversion.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableSoftwareStartConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC conversion on external event and start the selected
           ADC conversion */
        ADCx->CTRL2 |= CTRL2_EXT_TRIG_SWSTART_SET;
    }
    else
    {
        /* Disable the selected ADC conversion on external event and stop the selected
           ADC conversion */
        ADCx->CTRL2 &= CTRL2_EXT_TRIG_SWSTART_RESET;
    }
}

/**
 * @brief  Gets the selected ADC Software start conversion Status.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @return The new state of ADC software start conversion (SET or RESET).
 */
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_Module* ADCx)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    /* Check the status of SOFT_START bit */
    if ((ADCx->CTRL2 & CTRL2_SOFT_START_SET) != (uint32_t)RESET)
    {
        /* SOFT_START bit is set */
        bitstatus = SET;
    }
    else
    {
        /* SOFT_START bit is reset */
        bitstatus = RESET;
    }
    /* Return the SOFT_START bit status */
    return bitstatus;
}

/**
 * @brief  Configures the discontinuous mode for the selected ADC regular
 *         group channel.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Number specifies the discontinuous mode regular channel
 *         count value. This number must be between 1 and 8.
 */
void ADC_ConfigDiscModeChannelCount(ADC_Module* ADCx, uint8_t Number)
{
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcSeqDiscNumberValid(Number));
    /* Get the old register value */
    tmpreg1 = ADCx->CTRL1;
    /* Clear the old discontinuous mode channel count */
    tmpreg1 &= CR1_DISCNUM_Reset;
    /* Set the discontinuous mode channel count */
    tmpreg2 = Number - 1;
    tmpreg1 |= tmpreg2 << 13;
    /* Store the new register value */
    ADCx->CTRL1 = tmpreg1;
}

/**
 * @brief  Enables or disables the discontinuous mode on regular group
 *         channel for the specified ADC
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC discontinuous mode
 *         on regular group channel.
 *         This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableDiscMode(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC regular discontinuous mode */
        ADCx->CTRL1 |= CTRL1_DISC_EN_SET;
    }
    else
    {
        /* Disable the selected ADC regular discontinuous mode */
        ADCx->CTRL1 &= CTRL1_DISC_EN_RESET;
    }
}

/**
 * @brief  Configures for the selected ADC regular channel its corresponding
 *         rank in the sequencer and its sample time.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_Channel the ADC channel to configure.
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_0 ADC Channel0 selected
 *     @arg ADC_CH_1 ADC Channel1 selected
 *     @arg ADC_CH_2 ADC Channel2 selected
 *     @arg ADC_CH_3 ADC Channel3 selected
 *     @arg ADC_CH_4 ADC Channel4 selected
 *     @arg ADC_CH_5 ADC Channel5 selected
 *     @arg ADC_CH_6 ADC Channel6 selected
 *     @arg ADC_CH_7 ADC Channel7 selected
 *     @arg ADC_CH_8 ADC Channel8 selected
 *     @arg ADC_CH_9 ADC Channel9 selected
 *     @arg ADC_CH_10 ADC Channel10 selected
 *     @arg ADC_CH_11 ADC Channel11 selected
 *     @arg ADC_CH_12 ADC Channel12 selected
 *     @arg ADC_CH_13 ADC Channel13 selected
 *     @arg ADC_CH_14 ADC Channel14 selected
 *     @arg ADC_CH_15 ADC Channel15 selected
 *     @arg ADC_CH_16 ADC Channel16 selected
 *     @arg ADC_CH_17 ADC Channel17 selected
 *     @arg ADC_CH_18 ADC Channel18 selected
 * @param Rank The rank in the regular group sequencer. This parameter must be between 1 to 16.
 * @param ADC_SampleTime The sample time value to be set for the selected channel.
 *   This parameter can be one of the following values:
 *     @arg ADC_SAMP_TIME_1CYCLES5 Sample time equal to 1.5 cycles
 *     @arg ADC_SAMP_TIME_7CYCLES5 Sample time equal to 7.5 cycles
 *     @arg ADC_SAMP_TIME_13CYCLES5 Sample time equal to 13.5 cycles
 *     @arg ADC_SAMP_TIME_28CYCLES5 Sample time equal to 28.5 cycles
 *     @arg ADC_SAMP_TIME_41CYCLES5 Sample time equal to 41.5 cycles
 *     @arg ADC_SAMP_TIME_55CYCLES5 Sample time equal to 55.5 cycles
 *     @arg ADC_SAMP_TIME_71CYCLES5 Sample time equal to 71.5 cycles
 *     @arg ADC_SAMP_TIME_239CYCLES5 Sample time equal to 239.5 cycles
 */
void ADC_ConfigRegularChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
    uint32_t tmpreg1 = 0, tmpreg2 = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcChannel(ADC_Channel));
    assert_param(IsAdcReqRankValid(Rank));
    assert_param(IsAdcSampleTime(ADC_SampleTime));

    if (ADC_Channel == ADC_CH_18)
    {
        tmpreg1 = ADCx->SAMPT3;
        tmpreg1 &= (~0x00000007);
        tmpreg1 |= ADC_SampleTime;
        ADCx->SAMPT3 = tmpreg1;
    }
    else if (ADC_Channel > ADC_CH_9) /* if ADC_CH_10 ... ADC_CH_17 is selected */
    {
        /* Get the old register value */
        tmpreg1 = ADCx->SAMPT1;
        /* Calculate the mask to clear */
        tmpreg2 = SAMPT1_SMP_SET << (3 * (ADC_Channel - 10));
        /* Clear the old channel sample time */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
        /* Set the new channel sample time */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->SAMPT1 = tmpreg1;
    }
    else /* ADC_Channel include in ADC_Channel_[0..9] */
    {
        /* Get the old register value */
        tmpreg1 = ADCx->SAMPT2;
        /* Calculate the mask to clear */
        tmpreg2 = SAMPT2_SMP_SET << (3 * ADC_Channel);
        /* Clear the old channel sample time */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
        /* Set the new channel sample time */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->SAMPT2 = tmpreg1;
    }
    /* For Rank 1 to 6 */
    if (Rank < 7)
    {
        /* Get the old register value */
        tmpreg1 = ADCx->RSEQ3;
        /* Calculate the mask to clear */
        tmpreg2 = SQR3_SEQ_SET << (5 * (Rank - 1));
        /* Clear the old SQx bits for the selected rank */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
        /* Set the SQx bits for the selected rank */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->RSEQ3 = tmpreg1;
    }
    /* For Rank 7 to 12 */
    else if (Rank < 13)
    {
        /* Get the old register value */
        tmpreg1 = ADCx->RSEQ2;
        /* Calculate the mask to clear */
        tmpreg2 = SQR2_SEQ_SET << (5 * (Rank - 7));
        /* Clear the old SQx bits for the selected rank */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
        /* Set the SQx bits for the selected rank */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->RSEQ2 = tmpreg1;
    }
    /* For Rank 13 to 16 */
    else
    {
        /* Get the old register value */
        tmpreg1 = ADCx->RSEQ1;
        /* Calculate the mask to clear */
        tmpreg2 = SQR1_SEQ_SET << (5 * (Rank - 13));
        /* Clear the old SQx bits for the selected rank */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
        /* Set the SQx bits for the selected rank */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->RSEQ1 = tmpreg1;
    }
}

/**
 * @brief  Enables or disables the ADCx conversion through external trigger.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC external trigger start of conversion.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableExternalTrigConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC conversion on external event */
        ADCx->CTRL2 |= CTRL2_EXT_TRIG_SET;
    }
    else
    {
        /* Disable the selected ADC conversion on external event */
        ADCx->CTRL2 &= CTRL2_EXT_TRIG_RESET;
    }
}

/**
 * @brief  Returns the last ADCx conversion result data for regular channel.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @return The Data conversion value.
 */
uint16_t ADC_GetDat(ADC_Module* ADCx)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    /* Return the selected ADC conversion value */
    return (uint16_t)ADCx->DAT;
}

/**
 * @brief  Returns the last ADC1 and ADC2 conversion result data in dual mode.
 * @return The Data conversion value.
 */
uint32_t ADC_GetDualModeConversionDat(ADC_Module* ADCx)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    /* Return the dual mode conversion value */
    if((ADCx==ADC1) | (ADCx==ADC2))
        return (uint32_t)ADC1->DAT;
    else
        return (uint32_t)ADC1->DAT;
}

/**
 * @brief  Enables or disables the selected ADC automatic injected group
 *         conversion after regular one.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC auto injected conversion
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableAutoInjectedConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC automatic injected group conversion */
        ADCx->CTRL1 |= CR1_JAUTO_Set;
    }
    else
    {
        /* Disable the selected ADC automatic injected group conversion */
        ADCx->CTRL1 &= CR1_JAUTO_Reset;
    }
}

/**
 * @brief  Enables or disables the discontinuous mode for injected group
 *         channel for the specified ADC
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC discontinuous mode
 *         on injected group channel.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableInjectedDiscMode(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC injected discontinuous mode */
        ADCx->CTRL1 |= CTRL1_INJ_DISC_EN_SET;
    }
    else
    {
        /* Disable the selected ADC injected discontinuous mode */
        ADCx->CTRL1 &= CTRL1_INJ_DISC_EN_RESET;
    }
}

/**
 * @brief  Configures the ADCx external trigger for injected channels conversion.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_ExternalTrigInjecConv specifies the ADC trigger to start injected conversion.
 *   This parameter can be one of the following values:
 *     @arg ADC_EXT_TRIG_INJ_CONV_T1_TRGO Timer1 TRGO event selected (for ADC1, ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T1_CC4 Timer1 capture compare4 selected (for ADC1, ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T2_TRGO Timer2 TRGO event selected (for ADC1 and ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T2_CC1 Timer2 capture compare1 selected (for ADC1 and ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T3_CC4 Timer3 capture compare4 selected (for ADC1 and ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_T4_TRGO Timer4 TRGO event selected (for ADC1 and ADC2)
 *     @arg ADC_EXT_TRIG_INJ_CONV_EXT_INT15_TIM8_CC4 External interrupt line 15 or Timer8
 *                                                       capture compare4 event selected (for ADC1 and ADC2)
 */
void ADC_ConfigExternalTrigInjectedConv(ADC_Module* ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcExtInjTrig(ADC_ExternalTrigInjecConv));
    /* Get the old register value */
    tmpregister = ADCx->CTRL2;
    /* Clear the old external event selection for injected group */
    tmpregister &= CTRL2_INJ_EXT_SEL_RESET;
    /* Set the external event selection for injected group */
    tmpregister |= ADC_ExternalTrigInjecConv;
    /* Store the new register value */
    ADCx->CTRL2 = tmpregister;
}

/**
 * @brief  Enables or disables the ADCx injected channels conversion through
 *         external trigger
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC external trigger start of
 *         injected conversion.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableExternalTrigInjectedConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC external event selection for injected group */
        ADCx->CTRL2 |= CTRL2_INJ_EXT_TRIG_SET;
    }
    else
    {
        /* Disable the selected ADC external event selection for injected group */
        ADCx->CTRL2 &= CTRL2_INJ_EXT_TRIG_RESET;
    }
}

/**
 * @brief  Enables or disables the selected ADC start of the injected
 *         channels conversion.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Cmd new state of the selected ADC software start injected conversion.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableSoftwareStartInjectedConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC conversion for injected group on external event and start the selected
           ADC injected conversion */
        ADCx->CTRL2 |= CTRL2_INJ_EXT_TRIG_JSWSTART_SET;
    }
    else
    {
        /* Disable the selected ADC conversion on external event for injected group and stop the selected
           ADC injected conversion */
        ADCx->CTRL2 &= CTRL2_INJ_EXT_TRIG_JSWSTART_RESET;
    }
}

/**
 * @brief  Gets the selected ADC Software start injected conversion Status.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @return The new state of ADC software start injected conversion (SET or RESET).
 */
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_Module* ADCx)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    /* Check the status of INJ_SWSTART bit */
    if ((ADCx->CTRL2 & CTRL2_INJ_SWSTART_SET) != (uint32_t)RESET)
    {
        /* INJ_SWSTART bit is set */
        bitstatus = SET;
    }
    else
    {
        /* INJ_SWSTART bit is reset */
        bitstatus = RESET;
    }
    /* Return the INJ_SWSTART bit status */
    return bitstatus;
}

/**
 * @brief  Configures for the selected ADC injected channel its corresponding
 *         rank in the sequencer and its sample time.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_Channel the ADC channel to configure.
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_0 ADC Channel0 selected
 *     @arg ADC_CH_1 ADC Channel1 selected
 *     @arg ADC_CH_2 ADC Channel2 selected
 *     @arg ADC_CH_3 ADC Channel3 selected
 *     @arg ADC_CH_4 ADC Channel4 selected
 *     @arg ADC_CH_5 ADC Channel5 selected
 *     @arg ADC_CH_6 ADC Channel6 selected
 *     @arg ADC_CH_7 ADC Channel7 selected
 *     @arg ADC_CH_8 ADC Channel8 selected
 *     @arg ADC_CH_9 ADC Channel9 selected
 *     @arg ADC_CH_10 ADC Channel10 selected
 *     @arg ADC_CH_11 ADC Channel11 selected
 *     @arg ADC_CH_12 ADC Channel12 selected
 *     @arg ADC_CH_13 ADC Channel13 selected
 *     @arg ADC_CH_14 ADC Channel14 selected
 *     @arg ADC_CH_15 ADC Channel15 selected
 *     @arg ADC_CH_16 ADC Channel16 selected
 *     @arg ADC_CH_17 ADC Channel17 selected
 *     @arg ADC_CH_18 ADC Channel18 selected
 * @param Rank The rank in the injected group sequencer. This parameter must be between 1 and 4.
 * @param ADC_SampleTime The sample time value to be set for the selected channel.
 *   This parameter can be one of the following values:
 *     @arg ADC_SAMP_TIME_1CYCLES5 Sample time equal to 1.5 cycles
 *     @arg ADC_SAMP_TIME_7CYCLES5 Sample time equal to 7.5 cycles
 *     @arg ADC_SAMP_TIME_13CYCLES5 Sample time equal to 13.5 cycles
 *     @arg ADC_SAMP_TIME_28CYCLES5 Sample time equal to 28.5 cycles
 *     @arg ADC_SAMP_TIME_41CYCLES5 Sample time equal to 41.5 cycles
 *     @arg ADC_SAMP_TIME_55CYCLES5 Sample time equal to 55.5 cycles
 *     @arg ADC_SAMP_TIME_71CYCLES5 Sample time equal to 71.5 cycles
 *     @arg ADC_SAMP_TIME_239CYCLES5 Sample time equal to 239.5 cycles
 */
void ADC_ConfigInjectedChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
    uint32_t tmpreg1 = 0, tmpreg2 = 0, tmpreg3 = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcChannel(ADC_Channel));
    assert_param(IsAdcInjRankValid(Rank));
    assert_param(IsAdcSampleTime(ADC_SampleTime));

    if (ADC_Channel == ADC_CH_18)
    {
        tmpreg1 = ADCx->SAMPT3;
        tmpreg1 &= (~0x00000007);
        tmpreg1 |= ADC_SampleTime;
        ADCx->SAMPT3 = tmpreg1;
    }
    else if (ADC_Channel > ADC_CH_9) /* if ADC_CH_10 ... ADC_CH_17 is selected */
    {
        /* Get the old register value */
        tmpreg1 = ADCx->SAMPT1;
        /* Calculate the mask to clear */
        tmpreg2 = SAMPT1_SMP_SET << (3 * (ADC_Channel - 10));
        /* Clear the old channel sample time */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
        /* Set the new channel sample time */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->SAMPT1 = tmpreg1;
    }
    else /* ADC_Channel include in ADC_Channel_[0..9] */
    {
        /* Get the old register value */
        tmpreg1 = ADCx->SAMPT2;
        /* Calculate the mask to clear */
        tmpreg2 = SAMPT2_SMP_SET << (3 * ADC_Channel);
        /* Clear the old channel sample time */
        tmpreg1 &= ~tmpreg2;
        /* Calculate the mask to set */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
        /* Set the new channel sample time */
        tmpreg1 |= tmpreg2;
        /* Store the new register value */
        ADCx->SAMPT2 = tmpreg1;
    }
    /* Rank configuration */
    /* Get the old register value */
    tmpreg1 = ADCx->JSEQ;
    /* Get INJ_LEN value: Number = INJ_LEN+1 */
    tmpreg3 = (tmpreg1 & JSEQ_INJ_LEN_SET) >> 20;
    /* Calculate the mask to clear: ((Rank-1)+(4-INJ_LEN-1)) */
    tmpreg2 = JSEQ_JSQ_SET << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
    /* Clear the old JSQx bits for the selected rank */
    tmpreg1 &= ~tmpreg2;
    /* Calculate the mask to set: ((Rank-1)+(4-INJ_LEN-1)) */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
    /* Set the JSQx bits for the selected rank */
    tmpreg1 |= tmpreg2;
    /* Store the new register value */
    ADCx->JSEQ = tmpreg1;
}

/**
 * @brief  Configures the sequencer length for injected channels
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param Length The sequencer length.
 *   This parameter must be a number between 1 to 4.
 */
void ADC_ConfigInjectedSequencerLength(ADC_Module* ADCx, uint8_t Length)
{
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcInjLenValid(Length));

    /* Get the old register value */
    tmpreg1 = ADCx->JSEQ;
    /* Clear the old injected sequnence lenght INJ_LEN bits */
    tmpreg1 &= JSEQ_INJ_LEN_RESET;
    /* Set the injected sequnence lenght INJ_LEN bits */
    tmpreg2 = Length - 1;
    tmpreg1 |= tmpreg2 << 20;
    /* Store the new register value */
    ADCx->JSEQ = tmpreg1;
}

/**
 * @brief  Set the injected channels conversion value offset
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_InjectedChannel the ADC injected channel to set its offset.
 *   This parameter can be one of the following values:
 *     @arg ADC_INJ_CH_1 Injected Channel1 selected
 *     @arg ADC_INJ_CH_2 Injected Channel2 selected
 *     @arg ADC_INJ_CH_3 Injected Channel3 selected
 *     @arg ADC_INJ_CH_4 Injected Channel4 selected
 * @param Offset the offset value for the selected ADC injected channel
 *   This parameter must be a 12bit value.
 */
void ADC_SetInjectedOffsetDat(ADC_Module* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcInjCh(ADC_InjectedChannel));
    assert_param(IsAdcOffsetValid(Offset));

    tmp = (uint32_t)ADCx;
    tmp += ADC_InjectedChannel;

    /* Set the selected injected channel data offset */
    *(__IO uint32_t*)tmp = (uint32_t)Offset;
}

/**
 * @brief  Returns the ADC injected channel conversion result
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_InjectedChannel the converted ADC injected channel.
 *   This parameter can be one of the following values:
 *     @arg ADC_INJ_CH_1 Injected Channel1 selected
 *     @arg ADC_INJ_CH_2 Injected Channel2 selected
 *     @arg ADC_INJ_CH_3 Injected Channel3 selected
 *     @arg ADC_INJ_CH_4 Injected Channel4 selected
 * @return The Data conversion value.
 */
uint16_t ADC_GetInjectedConversionDat(ADC_Module* ADCx, uint8_t ADC_InjectedChannel)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcInjCh(ADC_InjectedChannel));

    tmp = (uint32_t)ADCx;
    tmp += ADC_InjectedChannel + JDAT_OFFSET;

    /* Returns the selected injected channel conversion data value */
    return (uint16_t)(*(__IO uint32_t*)tmp);
}

/**
 * @brief  Enables or disables the analog watchdog on single/all regular
 *         or injected channels
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_AnalogWatchdog the ADC analog watchdog configuration.
 *   This parameter can be one of the following values:
 *     @arg ADC_ANALOG_WTDG_SINGLEREG_ENABLE Analog watchdog on a single regular channel
 *     @arg ADC_ANALOG_WTDG_SINGLEINJEC_ENABLE Analog watchdog on a single injected channel
 *     @arg ADC_ANALOG_WTDG_SINGLEREG_OR_INJEC_ENABLE Analog watchdog on a single regular or injected channel
 *     @arg ADC_ANALOG_WTDG_ALLREG_ENABLE Analog watchdog on  all regular channel
 *     @arg ADC_ANALOG_WTDG_ALLINJEC_ENABLE Analog watchdog on  all injected channel
 *     @arg ADC_ANALOG_WTDG_ALLREG_ALLINJEC_ENABLE Analog watchdog on all regular and injected channels
 *     @arg ADC_ANALOG_WTDG_NONE No channel guarded by the analog watchdog
 */
void ADC_ConfigAnalogWatchdogWorkChannelType(ADC_Module* ADCx, uint32_t ADC_AnalogWatchdog)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcAnalogWatchdog(ADC_AnalogWatchdog));
    /* Get the old register value */
    tmpregister = ADCx->CTRL1;
    /* Clear AWDEN, AWDENJ and AWDSGL bits */
    tmpregister &= CTRL1_AWDG_MODE_RESET;
    /* Set the analog watchdog enable mode */
    tmpregister |= ADC_AnalogWatchdog;
    /* Store the new register value */
    ADCx->CTRL1 = tmpregister;
}

/**
 * @brief  Configures the high and low thresholds of the analog watchdog.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param HighThreshold the ADC analog watchdog High threshold value.
 *   This parameter must be a 12bit value.
 * @param LowThreshold the ADC analog watchdog Low threshold value.
 *   This parameter must be a 12bit value.
 */
void ADC_ConfigAnalogWatchdogThresholds(ADC_Module* ADCx, uint16_t HighThreshold, uint16_t LowThreshold)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcValid(HighThreshold));
    assert_param(IsAdcValid(LowThreshold));
    /* Set the ADCx high threshold */
    ADCx->WDGHIGH = HighThreshold;
    /* Set the ADCx low threshold */
    ADCx->WDGLOW = LowThreshold;
}

/**
 * @brief  Configures the analog watchdog guarded single channel
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_Channel the ADC channel to configure for the analog watchdog.
 *   This parameter can be one of the following values:
 *     @arg ADC_CH_0 ADC Channel0 selected
 *     @arg ADC_CH_1 ADC Channel1 selected
 *     @arg ADC_CH_2 ADC Channel2 selected
 *     @arg ADC_CH_3 ADC Channel3 selected
 *     @arg ADC_CH_4 ADC Channel4 selected
 *     @arg ADC_CH_5 ADC Channel5 selected
 *     @arg ADC_CH_6 ADC Channel6 selected
 *     @arg ADC_CH_7 ADC Channel7 selected
 *     @arg ADC_CH_8 ADC Channel8 selected
 *     @arg ADC_CH_9 ADC Channel9 selected
 *     @arg ADC_CH_10 ADC Channel10 selected
 *     @arg ADC_CH_11 ADC Channel11 selected
 *     @arg ADC_CH_12 ADC Channel12 selected
 *     @arg ADC_CH_13 ADC Channel13 selected
 *     @arg ADC_CH_14 ADC Channel14 selected
 *     @arg ADC_CH_15 ADC Channel15 selected
 *     @arg ADC_CH_16 ADC Channel16 selected
 *     @arg ADC_CH_17 ADC Channel17 selected
 *     @arg ADC_CH_18 ADC Channel18 selected
 */
void ADC_ConfigAnalogWatchdogSingleChannel(ADC_Module* ADCx, uint8_t ADC_Channel)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcChannel(ADC_Channel));
    /* Get the old register value */
    tmpregister = ADCx->CTRL1;
    /* Clear the Analog watchdog channel select bits */
    tmpregister &= CTRL1_AWDG_CH_RESET;
    /* Set the Analog watchdog channel */
    tmpregister |= ADC_Channel;
    /* Store the new register value */
    ADCx->CTRL1 = tmpregister;
}

/**
 * @brief  Enables or disables the temperature sensor and Vrefint channel.
 * @param Cmd new state of the temperature sensor.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ADC_EnableTempSensorVrefint(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the temperature sensor and Vrefint channel*/
        ADC1->CTRL2 |= CTRL2_TSVREFE_SET;
            _EnVref1p2()
    }
    else
    {
        /* Disable the temperature sensor and Vrefint channel*/
        ADC1->CTRL2 &= CTRL2_TSVREFE_RESET;
        _DisVref1p2()
    }
}

/**
 * @brief  Checks whether the specified ADC flag is set or not.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ADC_FLAG_AWDG Analog watchdog flag
 *     @arg ADC_FLAG_ENDC End of conversion flag
 *     @arg ADC_FLAG_JENDC End of injected group conversion flag
 *     @arg ADC_FLAG_JSTR Start of injected group conversion flag
 *     @arg ADC_FLAG_STR Start of regular group conversion flag
 * @return The new state of ADC_FLAG (SET or RESET).
 */
FlagStatus ADC_GetFlagStatus(ADC_Module* ADCx, uint8_t ADC_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcGetFlag(ADC_FLAG));
    /* Check the status of the specified ADC flag */
    if ((ADCx->STS & ADC_FLAG) != (uint8_t)RESET)
    {
        /* ADC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_FLAG status */
    return bitstatus;
}

/**
 * @brief  Clears the ADCx's pending flags.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_FLAG specifies the flag to clear.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_FLAG_AWDG Analog watchdog flag
 *     @arg ADC_FLAG_ENDC End of conversion flag
 *     @arg ADC_FLAG_JENDC End of injected group conversion flag
 *     @arg ADC_FLAG_JSTR Start of injected group conversion flag
 *     @arg ADC_FLAG_STR Start of regular group conversion flag
 */
void ADC_ClearFlag(ADC_Module* ADCx, uint8_t ADC_FLAG)
{
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcClrFlag(ADC_FLAG));
    /* Clear the selected ADC flags */
    ADCx->STS = (~(uint32_t)ADC_FLAG & ADC_STS_RESERVE_MASK);
}

/**
 * @brief  Checks whether the specified ADC interrupt has occurred or not.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_IT specifies the ADC interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg ADC_INT_ENDC End of conversion interrupt mask
 *     @arg ADC_INT_AWD Analog watchdog interrupt mask
 *     @arg ADC_INT_JENDC End of injected conversion interrupt mask
 * @return The new state of ADC_IT (SET or RESET).
 */
INTStatus ADC_GetIntStatus(ADC_Module* ADCx, uint16_t ADC_IT)
{
    INTStatus bitstatus = RESET;
    uint32_t itmask = 0, enablestatus = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcGetInt(ADC_IT));
    /* Get the ADC IT index */
    itmask = ADC_IT >> 8;
    /* Get the ADC_IT enable bit status */
    enablestatus = (ADCx->CTRL1 & (uint8_t)ADC_IT);
    /* Check the status of the specified ADC interrupt */
    if (((ADCx->STS & itmask) != (uint32_t)RESET) && enablestatus)
    {
        /* ADC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_IT is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_IT status */
    return bitstatus;
}

/**
 * @brief  Clears the ADCx's interrupt pending bits.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_IT specifies the ADC interrupt pending bit to clear.
 *   This parameter can be any combination of the following values:
 *     @arg ADC_INT_ENDC End of conversion interrupt mask
 *     @arg ADC_INT_AWD Analog watchdog interrupt mask
 *     @arg ADC_INT_JENDC End of injected conversion interrupt mask
 */
void ADC_ClearIntPendingBit(ADC_Module* ADCx, uint16_t ADC_IT)
{
    uint8_t itmask = 0;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcInt(ADC_IT));
    /* Get the ADC IT index */
    itmask = (uint8_t)(ADC_IT >> 8);
    /* Clear the selected ADC interrupt pending bits */
    ADCx->STS = (~(uint32_t)itmask & ADC_STS_RESERVE_MASK);
}


/**
 * @brief  Initializes the ADCx peripheral according to the specified parameters
 *         in the ADC_InitStructEx.
 * @param ADCx where x can be 1, 2  to select the ADC peripheral.
 * @param ADC_InitStructEx pointer to an ADC_InitTypeEx structure that contains
 *         the configuration information for the specified ADC peripheral.
 */
void ADC_InitEx(ADC_Module* ADCx, ADC_InitTypeEx* ADC_InitStructEx)
{
    uint32_t tmpregister = 0;
    /*ADC_SAMPT3 samp time sele ,as sam 103 or 303 style*/
    if (ADC_InitStructEx->Samp303Style)
        ADCx->SAMPT3 |= ADC_SAMPT3_SAMPSEL_MSK;
    else
        ADCx->SAMPT3 &= (~ADC_SAMPT3_SAMPSEL_MSK);

    /*intial ADC_CTRL3 once initiall config*/
    tmpregister = ADCx->CTRL3;
    if (ADC_InitStructEx->VbatMinitEn)
    {
        tmpregister |= ADC_CTRL3_VABTMEN_MSK;
        _EnVref1p2()
    }
    else
    {
        tmpregister &= (~ADC_CTRL3_VABTMEN_MSK);
         _DisVref1p2()
    }

    if (ADC_InitStructEx->DeepPowerModEn)
        tmpregister |= ADC_CTRL3_DPWMOD_MSK;
    else
        tmpregister &= (~ADC_CTRL3_DPWMOD_MSK);

    if (ADC_InitStructEx->JendcIntEn)
        tmpregister |= ADC_CTRL3_JENDCAIEN_MSK;
    else
        tmpregister &= (~ADC_CTRL3_JENDCAIEN_MSK);

    if (ADC_InitStructEx->EndcIntEn)
        tmpregister |= ADC_CTRL3_ENDCAIEN_MSK;
    else
        tmpregister &= (~ADC_CTRL3_ENDCAIEN_MSK);

    if (ADC_InitStructEx->CalAtuoLoadEn)
        tmpregister |= ADC_CTRL3_CALALD_MSK;
    else
        tmpregister &= (~ADC_CTRL3_CALALD_MSK);

    if (ADC_InitStructEx->DifModCal)
        tmpregister |= ADC_CTRL3_CALDIF_MSK;
    else
        tmpregister &= (~ADC_CTRL3_CALDIF_MSK);

    tmpregister &= (~ADC_CTRL3_RES_MSK);
    tmpregister |= ADC_InitStructEx->ResBit;

    tmpregister &= (~ADC_CTRL3_CKMOD_MSK);
        if(ADC_InitStructEx->ClkMode==ADC_CTRL3_CKMOD_PLL)
    tmpregister |= ADC_CTRL3_CKMOD_MSK;

    ADCx->CTRL3 = tmpregister;
}
/**
 * @brief  Configure differential channels enable.
 * @param ADCx where x can be 1, 2  to select the ADC peripheral.
 * @param DifChs differential channels,see @ADC_dif_sel_ch_definition. eg: ADC_DIFSEL_CHS_3|ADC_DIFSEL_CHS_4
 */
void ADC_SetDifChs(ADC_Module* ADCx,uint32_t DifChs)
{
    ADCx->DIFSEL = DifChs;
}
/**
 * @brief  Checks whether the specified ADC flag is set or not.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ADC_FLAG_NEW specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ADC_FLAG_RDY ADC ready flag
 *     @arg ADC_FLAG_PD_RDY ADC powerdown ready flag
 * @return The new state of ADC_FLAG_NEW (SET or RESET).
 */
FlagStatus ADC_GetFlagStatusNew(ADC_Module* ADCx, uint8_t ADC_FLAG_NEW)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IsAdcModule(ADCx));
    assert_param(IsAdcGetFlag(ADC_FLAG_NEW));
    /* Check the status of the specified ADC flag */
    if ((ADCx->CTRL3 & ADC_FLAG_NEW) != (uint8_t)RESET)
    {
        /* ADC_FLAG_NEW is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG_NEW is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_FLAG_NEW status */
    return bitstatus;
}
/**
 * @brief  Set Adc calibration bypass or enable.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param en enable bypass calibration.
 *   This parameter can be one of the following values:
 *     @arg true bypass calibration
 *     @arg false not bypass calibration
 */
void ADC_SetBypassCalibration(ADC_Module* ADCx, FunctionalState en)
{
    uint32_t tmpregister = 0;

    tmpregister = ADCx->CTRL3;
    if (en)
        tmpregister |= ADC_CTRL3_BPCAL_MSK;
    else
        tmpregister &= (~ADC_CTRL3_BPCAL_MSK);
    ADCx->CTRL3 = tmpregister;
}
/**
 * @brief  Set Adc trans bits width.
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 * @param ResultBitNum specifies num with adc trans width.
 *   This parameter can be one of the following values:
 *     @arg ADC_RST_BIT_12 12 bit trans
 *     @arg ADC_RST_BIT_10 10 bit trans
 *     @arg ADC_RST_BIT_8 8 bit trans
 *     @arg ADC_RESULT_BIT_6 6 bit trans
 */
void ADC_SetConvResultBitNum(ADC_Module* ADCx, uint32_t ResultBitNum)
{
    uint32_t tmpregister = 0;

    tmpregister = ADCx->CTRL3;
    tmpregister &= 0xFFFFFFFC;
    tmpregister |= ResultBitNum;
    ADCx->CTRL3 = tmpregister;
    return;
}

/**
 * @brief  Set Adc Clock bits for AHB .
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 */
void ADC_AHB_Clock_Mode_Config(ADC_Module* ADCx)
{
    ADCx->CTRL3 &= ADC_CLOCK_AHB;  
}

/**
 * @brief  Set Adc Clock bits for PLL .
 * @param ADCx where x can be 1, 2, 3 or 4 to select the ADC peripheral.
 */
void ADC_PLL_Clock_Mode_Config(ADC_Module* ADCx)
{   
    ADCx->CTRL3 |= ADC_CLOCK_PLL;  
}

/**
 * @brief  Configures the ADCHCLK prescaler.
 * @param RCC_ADCHCLKPrescaler specifies the ADCHCLK prescaler.
 *   This parameter can be on of the following values:
 *     @arg RCC_ADCHCLK_DIV1 ADCHCLKPRE[3:0] = 0000, HCLK Clock Divided By 1
 *     @arg RCC_ADCHCLK_DIV2 ADCHCLKPRE[3:0] = 0001, HCLK Clock Divided By 2
 *     @arg RCC_ADCHCLK_DIV4 ADCHCLKPRE[3:0] = 0010, HCLK Clock Divided By 4
 *     @arg RCC_ADCHCLK_DIV6 ADCHCLKPRE[3:0] = 0011, HCLK Clock Divided By 6
 *     @arg RCC_ADCHCLK_DIV8 ADCHCLKPRE[3:0] = 0100, HCLK Clock Divided By 8
 *     @arg RCC_ADCHCLK_DIV10 ADCHCLKPRE[3:0] = 0101, HCLK Clock Divided By 10
 *     @arg RCC_ADCHCLK_DIV12 ADCHCLKPRE[3:0] = 0110, HCLK Clock Divided By 12
 *     @arg RCC_ADCHCLK_DIV16 ADCHCLKPRE[3:0] = 0111, HCLK Clock Divided By 16
 *     @arg RCC_ADCHCLK_DIV32 ADCHCLKPRE[3:0] = 1000, HCLK Clock Divided By 32
 *     @arg RCC_ADCHCLK_DIV32 ADCHCLKPRE[3:0] = others, HCLK Clock Divided By 32

 *     @arg RCC_ADCPLLCLK_DISABLE ADCPLLCLKPRES[4:0] = 0xxxx, ADC Pll Clock Disable
 *     @arg RCC_ADCPLLCLK_DIV1 ADCPLLCLKPRES[4:0] = 10000, Pll Clock Divided By 1
 *     @arg RCC_ADCPLLCLK_DIV2 ADCPLLCLKPRES[4:0] = 10001, Pll Clock Divided By 2
 *     @arg RCC_ADCPLLCLK_DIV4 ADCPLLCLKPRES[4:0] = 10010, Pll Clock Divided By 4
 *     @arg RCC_ADCPLLCLK_DIV6 ADCPLLCLKPRES[4:0] = 10011, Pll Clock Divided By 6
 *     @arg RCC_ADCPLLCLK_DIV8 ADCPLLCLKPRES[4:0] = 10100, Pll Clock Divided By 8
 *     @arg RCC_ADCPLLCLK_DIV10 ADCPLLCLKPRES[4:0] = 10101, Pll Clock Divided By 10
 *     @arg RCC_ADCPLLCLK_DIV12 ADCPLLCLKPRES[4:0] = 10110, Pll Clock Divided By 12
 *     @arg RCC_ADCPLLCLK_DIV16 ADCPLLCLKPRES[4:0] = 10111, Pll Clock Divided By 16
 *     @arg RCC_ADCPLLCLK_DIV32 ADCPLLCLKPRES[4:0] = 11000, Pll Clock Divided By 32
 *     @arg RCC_ADCPLLCLK_DIV64 ADCPLLCLKPRES[4:0] = 11001, Pll Clock Divided By 64
 *     @arg RCC_ADCPLLCLK_DIV128 ADCPLLCLKPRES[4:0] = 11010, Pll Clock Divided By 128
 *     @arg RCC_ADCPLLCLK_DIV256 ADCPLLCLKPRES[4:0] = 11011, Pll Clock Divided By 256
 *     @arg RCC_ADCPLLCLK_DIV256 ADCPLLCLKPRES[4:0] = others, Pll Clock Divided By 256
 */
void ADC_ConfigClk(ADC_CTRL3_CKMOD ADC_ClkMode, uint32_t RCC_ADCHCLKPrescaler)
{
    if(ADC_ClkMode==ADC_CTRL3_CKMOD_AHB){
            RCC_ConfigAdcPllClk(RCC_ADCPLLCLK_DIV1, DISABLE);
            RCC_ConfigAdcHclk(RCC_ADCHCLKPrescaler);
            ADC_AHB_Clock_Mode_Config(ADC1);
            ADC_AHB_Clock_Mode_Config(ADC2);
        }else{
            RCC_ConfigAdcPllClk(RCC_ADCHCLKPrescaler, ENABLE);
            RCC_ConfigAdcHclk(RCC_ADCHCLK_DIV1);
            ADC_PLL_Clock_Mode_Config(ADC1);
            ADC_PLL_Clock_Mode_Config(ADC2);
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
