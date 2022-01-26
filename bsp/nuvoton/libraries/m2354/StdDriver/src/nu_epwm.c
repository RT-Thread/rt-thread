/**************************************************************************//**
 * @file     epwm.c
 * @version  V3.00
 * @brief    M2354 series EPWM driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EPWM_Driver EPWM Driver
  @{
*/


/** @addtogroup EPWM_EXPORTED_FUNCTIONS EPWM Exported Functions
  @{
*/

/**
 * @brief Configure EPWM capture and get the nearest unit time.
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32UnitTimeNsec The unit time of counter
 * @param[in] u32CaptureEdge The condition to latch the counter. This parameter is not used
 * @return The nearest unit time in nano second.
 * @details This function is used to Configure EPWM capture and get the nearest unit time.
 */
uint32_t EPWM_ConfigCaptureChannel(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32UnitTimeNsec, uint32_t u32CaptureEdge)
{
    uint32_t u32PWMClockSrc;
    uint32_t u32NearestUnitTimeNsec = 0;
    uint32_t u32Prescale = 1U, u32CNR = 0xFFFFU;
    uint8_t u8BreakLoop = 0U;

    (void)u32CaptureEdge;

    /* clock source is from PCLK */
    if((epwm == EPWM0) || (epwm == EPWM0_NS))
    {
        u32PWMClockSrc = CLK_GetPCLK0Freq();
    }
    else /* if((epwm == EPWM1)||(epwm == EPWM1_NS)) */
    {
        u32PWMClockSrc = CLK_GetPCLK1Freq();
    }

    u32PWMClockSrc /= 1000UL;
    for(u32Prescale = 1U; u32Prescale <= 0x1000U; u32Prescale++)
    {
        u32NearestUnitTimeNsec = (1000000UL * u32Prescale) / u32PWMClockSrc;
        if(u32NearestUnitTimeNsec < u32UnitTimeNsec)
        {
            if(u32Prescale == 0x1000U)  /* limit to the maximum unit time(nano second) */
            {
                u8BreakLoop = 1U;
            }
            if(!((1000000UL * (u32Prescale + 1UL) > (u32NearestUnitTimeNsec * u32PWMClockSrc))))
            {
                u8BreakLoop = 1U;
            }
        }
        else
        {
            u8BreakLoop = 1U;
        }
        if(u8BreakLoop)
        {
            break;
        }
    }

    /* convert to real register value */
    u32Prescale = u32Prescale - 1U;
    /* every two channels share a prescaler */
    EPWM_SET_PRESCALER(epwm, u32ChannelNum, u32Prescale);

    /* set EPWM to down count type(edge aligned) */
    (epwm)->CTL1 = ((epwm)->CTL1 & ~(EPWM_CTL1_CNTTYPE0_Msk << (u32ChannelNum << 1))) | (1UL << (u32ChannelNum << 1));
    /* set EPWM to auto-reload mode */
    (epwm)->CTL1 &= ~(EPWM_CTL1_CNTMODE0_Msk << u32ChannelNum);
    EPWM_SET_CNR(epwm, u32ChannelNum, u32CNR);

    return (u32NearestUnitTimeNsec);
}

/**
 * @brief This function Configure EPWM generator and get the nearest frequency in edge aligned(up counter type) auto-reload mode
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32Frequency Target generator frequency
 * @param[in] u32DutyCycle Target generator duty cycle percentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
 * @return Nearest frequency clock in nano second
 * @note Since every two channels, (0 & 1), (2 & 3), shares a prescaler. Call this API to configure EPWM frequency may affect
 *       existing frequency of other channel.
 * @note This function is used for initial stage.
 *       To change duty cycle later, it should get the configured period value and calculate the new comparator value.
 */
uint32_t EPWM_ConfigOutputChannel(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32Frequency, uint32_t u32DutyCycle)
{
    uint32_t u32PWMClockSrc;
    uint32_t i;
    uint32_t u32Prescale = 1U, u32CNR = 0xFFFFU;

    /* clock source is from PCLK */
    if((epwm == EPWM0) || (epwm == EPWM0_NS))
    {
        u32PWMClockSrc = CLK_GetPCLK0Freq();
    }
    else /* if((epwm == EPWM1)||(epwm == EPWM1_NS)) */
    {
        u32PWMClockSrc = CLK_GetPCLK1Freq();
    }

    for(u32Prescale = 1U; u32Prescale < 0xFFFU; u32Prescale++)/* prescale could be 0~0xFFF */
    {
        i = (u32PWMClockSrc / u32Frequency) / u32Prescale;
        /* If target value is larger than CNR, need to use a larger prescaler */
        if(i <= (0x10000U))
        {
            u32CNR = i;
            break;
        }
    }
    /* Store return value here 'cos we're gonna change u32Prescale & u32CNR to the real value to fill into register */
    i = u32PWMClockSrc / (u32Prescale * u32CNR);

    /* convert to real register value */
    u32Prescale = u32Prescale - 1U;
    /* every two channels share a prescaler */
    EPWM_SET_PRESCALER(epwm, u32ChannelNum, u32Prescale);
    /* set EPWM to up counter type(edge aligned) and auto-reload mode */
    (epwm)->CTL1 = ((epwm)->CTL1 & ~((EPWM_CTL1_CNTTYPE0_Msk << (u32ChannelNum << 1)) | (EPWM_CTL1_CNTMODE0_Msk << u32ChannelNum)));

    u32CNR = u32CNR - 1U;
    EPWM_SET_CNR(epwm, u32ChannelNum, u32CNR);
    EPWM_SET_CMR(epwm, u32ChannelNum, u32DutyCycle * (u32CNR + 1UL) / 100UL);

    (epwm)->WGCTL0 = ((epwm)->WGCTL0 & ~((EPWM_WGCTL0_PRDPCTL0_Msk | EPWM_WGCTL0_ZPCTL0_Msk) << (u32ChannelNum << 1))) | \
                     (EPWM_OUTPUT_HIGH << (u32ChannelNum << 1UL << EPWM_WGCTL0_ZPCTL0_Pos));
    (epwm)->WGCTL1 = ((epwm)->WGCTL1 & ~((EPWM_WGCTL1_CMPDCTL0_Msk | EPWM_WGCTL1_CMPUCTL0_Msk) << (u32ChannelNum << 1))) | \
                     (EPWM_OUTPUT_LOW << (u32ChannelNum << 1UL << EPWM_WGCTL1_CMPUCTL0_Pos));

    return(i);
}

/**
 * @brief Start EPWM module
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to start EPWM module.
 */
void EPWM_Start(EPWM_T *epwm, uint32_t u32ChannelMask)
{
    (epwm)->CNTEN |= u32ChannelMask;
}

/**
 * @brief Stop EPWM module
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to stop EPWM module.
 */
void EPWM_Stop(EPWM_T *epwm, uint32_t u32ChannelMask)
{
    uint32_t i;
    for(i = 0UL; i < EPWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1UL << i))
        {
            (epwm)->PERIOD[i] = 0UL;
        }
    }
}

/**
 * @brief Stop EPWM generation immediately by clear channel enable bit
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to stop EPWM generation immediately by clear channel enable bit.
 */
void EPWM_ForceStop(EPWM_T *epwm, uint32_t u32ChannelMask)
{
    (epwm)->CNTEN &= ~u32ChannelMask;
}

/**
 * @brief Enable selected channel to trigger ADC
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32Condition The condition to trigger ADC. Combination of following conditions:
 *                  - \ref EPWM_TRG_ADC_EVEN_ZERO
 *                  - \ref EPWM_TRG_ADC_EVEN_PERIOD
 *                  - \ref EPWM_TRG_ADC_EVEN_ZERO_PERIOD
 *                  - \ref EPWM_TRG_ADC_EVEN_COMPARE_UP
 *                  - \ref EPWM_TRG_ADC_EVEN_COMPARE_DOWN
 *                  - \ref EPWM_TRG_ADC_ODD_ZERO
 *                  - \ref EPWM_TRG_ADC_ODD_PERIOD
 *                  - \ref EPWM_TRG_ADC_ODD_ZERO_PERIOD
 *                  - \ref EPWM_TRG_ADC_ODD_COMPARE_UP
 *                  - \ref EPWM_TRG_ADC_ODD_COMPARE_DOWN
 *                  - \ref EPWM_TRG_ADC_CH_0_FREE_CMP_UP
 *                  - \ref EPWM_TRG_ADC_CH_0_FREE_CMP_DOWN
 *                  - \ref EPWM_TRG_ADC_CH_2_FREE_CMP_UP
 *                  - \ref EPWM_TRG_ADC_CH_2_FREE_CMP_DOWN
 *                  - \ref EPWM_TRG_ADC_CH_4_FREE_CMP_UP
 *                  - \ref EPWM_TRG_ADC_CH_4_FREE_CMP_DOWN
 * @return None
 * @details This function is used to enable selected channel to trigger ADC.
 */
void EPWM_EnableADCTrigger(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32Condition)
{
    if(u32ChannelNum < 4UL)
    {
        (epwm)->EADCTS0 &= ~((EPWM_EADCTS0_TRGSEL0_Msk) << (u32ChannelNum << 3));
        (epwm)->EADCTS0 |= ((EPWM_EADCTS0_TRGEN0_Msk | u32Condition) << (u32ChannelNum << 3));
    }
    else
    {
        (epwm)->EADCTS1 &= ~((EPWM_EADCTS1_TRGSEL4_Msk) << ((u32ChannelNum - 4UL) << 3));
        (epwm)->EADCTS1 |= ((EPWM_EADCTS1_TRGEN4_Msk | u32Condition) << ((u32ChannelNum - 4UL) << 3));
    }
}

/**
 * @brief Disable selected channel to trigger ADC
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable selected channel to trigger ADC.
 */
void EPWM_DisableADCTrigger(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    if(u32ChannelNum < 4UL)
    {
        (epwm)->EADCTS0 &= ~(EPWM_EADCTS0_TRGEN0_Msk << (u32ChannelNum << 3));
    }
    else
    {
        (epwm)->EADCTS1 &= ~(EPWM_EADCTS1_TRGEN4_Msk << ((u32ChannelNum - 4UL) << 3));
    }
}

/**
 * @brief Enable and configure trigger ADC prescale
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @param[in] u32Prescale ADC prescale. Valid values are between 0 to 0xF.
 * @param[in] u32PrescaleCnt ADC prescale counter. Valid values are between 0 to 0xF.
 * @retval 0 Success.
 * @retval -1 Failed.
 * @details This function is used to enable and configure trigger ADC prescale.
 * @note User can configure only when ADC trigger prescale is disabled.
 * @note ADC prescale counter must less than ADC prescale.
 */
int32_t EPWM_EnableADCTriggerPrescale(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32Prescale, uint32_t u32PrescaleCnt)
{
    /* User can write only when PSCENn(n = 0 ~ 5) is 0 */
    if((epwm)->EADCPSCCTL & (1UL << u32ChannelNum))
        return (-1);

    if(u32ChannelNum < 4UL)
    {
        (epwm)->EADCPSC0 = ((epwm)->EADCPSC0 & ~((EPWM_EADCPSC0_EADCPSC0_Msk) << (u32ChannelNum << 3))) | \
                           (u32Prescale << (u32ChannelNum << 3));
        (epwm)->EADCPSCNT0 = ((epwm)->EADCPSCNT0 & ~((EPWM_EADCPSCNT0_PSCNT0_Msk) << (u32ChannelNum << 3))) | \
                             (u32PrescaleCnt << (u32ChannelNum << 3));
    }
    else
    {
        (epwm)->EADCPSC1 = ((epwm)->EADCPSC1 & ~((EPWM_EADCPSC1_EADCPSC4_Msk) << ((u32ChannelNum - 4UL) << 3))) | \
                           (u32Prescale << ((u32ChannelNum - 4UL) << 3));
        (epwm)->EADCPSCNT1 = ((epwm)->EADCPSCNT1 & ~((EPWM_EADCPSCNT1_PSCNT4_Msk) << ((u32ChannelNum - 4UL) << 3))) | \
                             (u32PrescaleCnt << ((u32ChannelNum - 4UL) << 3));
    }

    (epwm)->EADCPSCCTL |= EPWM_EADCPSCCTL_PSCEN0_Msk << u32ChannelNum;

    return 0;
}

/**
 * @brief Disable Trigger ADC prescale function
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable trigger ADC prescale.
 */
void EPWM_DisableADCTriggerPrescale(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->EADCPSCCTL &= ~(EPWM_EADCPSCCTL_PSCEN0_Msk << u32ChannelNum);
}

/**
 * @brief Clear selected channel trigger ADC flag
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32Condition This parameter is not used
 * @return None
 * @details This function is used to clear selected channel trigger ADC flag.
 */
void EPWM_ClearADCTriggerFlag(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32Condition)
{
    (void)u32Condition;
    (epwm)->STATUS = (EPWM_STATUS_EADCTRGF0_Msk << u32ChannelNum);
}

/**
 * @brief Get selected channel trigger ADC flag
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @retval 0 The specified channel trigger ADC to start of conversion flag is not set
 * @retval 1 The specified channel trigger ADC to start of conversion flag is set
 * @details This function is used to get EPWM trigger ADC to start of conversion flag for specified channel.
 */
uint32_t EPWM_GetADCTriggerFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    return (((epwm)->STATUS & (EPWM_STATUS_EADCTRGF0_Msk << u32ChannelNum)) ? 1UL : 0UL);
}

/**
 * @brief Enable selected channel to trigger DAC
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32Condition The condition to trigger DAC. Combination of following conditions:
 *                  - \ref EPWM_TRIGGER_DAC_ZERO
 *                  - \ref EPWM_TRIGGER_DAC_PERIOD
 *                  - \ref EPWM_TRIGGER_DAC_COMPARE_UP
 *                  - \ref EPWM_TRIGGER_DAC_COMPARE_DOWN
 * @return None
 * @details This function is used to enable selected channel to trigger DAC.
 */
void EPWM_EnableDACTrigger(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32Condition)
{
    (epwm)->DACTRGEN |= (u32Condition << u32ChannelNum);
}

/**
 * @brief Disable selected channel to trigger DAC
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable selected channel to trigger DAC.
 */
void EPWM_DisableDACTrigger(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->DACTRGEN &= ~((EPWM_TRIGGER_DAC_ZERO | EPWM_TRIGGER_DAC_PERIOD | EPWM_TRIGGER_DAC_COMPARE_UP | EPWM_TRIGGER_DAC_COMPARE_DOWN) << u32ChannelNum);
}

/**
 * @brief Clear selected channel trigger DAC flag
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. This parameter is not used
 * @param[in] u32Condition The condition to trigger DAC. This parameter is not used
 * @return None
 * @details This function is used to clear selected channel trigger DAC flag.
 */
void EPWM_ClearDACTriggerFlag(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32Condition)
{
    (void)u32ChannelNum;
    (void)u32Condition;
    (epwm)->STATUS = EPWM_STATUS_DACTRGF_Msk;
}

/**
 * @brief Get selected channel trigger DAC flag
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. This parameter is not used
 * @retval 0 The specified channel trigger DAC to start of conversion flag is not set
 * @retval 1 The specified channel trigger DAC to start of conversion flag is set
 * @details This function is used to get selected channel trigger DAC flag.
 */
uint32_t EPWM_GetDACTriggerFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (void)u32ChannelNum;
    return (((epwm)->STATUS & EPWM_STATUS_DACTRGF_Msk) ? 1UL : 0UL);
}

/**
 * @brief This function enable fault brake of selected channel(s)
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 * @param[in] u32LevelMask Output high or low while fault brake occurs, each bit represent the level of a channel
 *                         while fault brake occurs. Bit 0 represents channel 0, bit 1 represents channel 1...
 * @param[in] u32BrakeSource Fault brake source, could be one of following source
 *                  - \ref EPWM_FB_EDGE_ADCRM
 *                  - \ref EPWM_FB_EDGE_ACMP0
 *                  - \ref EPWM_FB_EDGE_ACMP1
 *                  - \ref EPWM_FB_EDGE_BKP0
 *                  - \ref EPWM_FB_EDGE_BKP1
 *                  - \ref EPWM_FB_EDGE_SYS_CSS
 *                  - \ref EPWM_FB_EDGE_SYS_BOD
 *                  - \ref EPWM_FB_EDGE_SYS_RAM
 *                  - \ref EPWM_FB_EDGE_SYS_COR
 *                  - \ref EPWM_FB_LEVEL_ADCRM
 *                  - \ref EPWM_FB_LEVEL_ACMP0
 *                  - \ref EPWM_FB_LEVEL_ACMP1
 *                  - \ref EPWM_FB_LEVEL_BKP0
 *                  - \ref EPWM_FB_LEVEL_BKP1
 *                  - \ref EPWM_FB_LEVEL_SYS_CSS
 *                  - \ref EPWM_FB_LEVEL_SYS_BOD
 *                  - \ref EPWM_FB_LEVEL_SYS_RAM
 *                  - \ref EPWM_FB_LEVEL_SYS_COR
 * @return None
 * @details This function is used to enable fault brake of selected channel(s).
 *          The write-protection function should be disabled before using this function.
 */
void EPWM_EnableFaultBrake(EPWM_T *epwm, uint32_t u32ChannelMask, uint32_t u32LevelMask, uint32_t u32BrakeSource)
{
    uint32_t i;

    for(i = 0UL; i < EPWM_CHANNEL_NUM; i++)
    {
        if(u32ChannelMask & (1UL << i))
        {
            if((u32BrakeSource == EPWM_FB_EDGE_SYS_CSS) || (u32BrakeSource == EPWM_FB_EDGE_SYS_BOD) || \
                    (u32BrakeSource == EPWM_FB_EDGE_SYS_RAM) || (u32BrakeSource == EPWM_FB_EDGE_SYS_COR) || \
                    (u32BrakeSource == EPWM_FB_LEVEL_SYS_CSS) || (u32BrakeSource == EPWM_FB_LEVEL_SYS_BOD) || \
                    (u32BrakeSource == EPWM_FB_LEVEL_SYS_RAM) || (u32BrakeSource == EPWM_FB_LEVEL_SYS_COR))
            {
                (epwm)->BRKCTL[i >> 1] |= (u32BrakeSource & (EPWM_BRKCTL0_1_SYSEBEN_Msk | EPWM_BRKCTL0_1_SYSLBEN_Msk));
                (epwm)->FAILBRK |= (u32BrakeSource & 0xFUL);
            }
            else
            {
                (epwm)->BRKCTL[i >> 1] |= u32BrakeSource;
            }
        }

        if(u32LevelMask & (1UL << i))
        {
            if((i & 0x1UL) == 0UL)
            {
                /* set brake action as high level for even channel */
                (epwm)->BRKCTL[i >> 1] &= ~EPWM_BRKCTL0_1_BRKAEVEN_Msk;
                (epwm)->BRKCTL[i >> 1] |= ((3UL) << EPWM_BRKCTL0_1_BRKAEVEN_Pos);
            }
            else
            {
                /* set brake action as high level for odd channel */
                (epwm)->BRKCTL[i >> 1] &= ~EPWM_BRKCTL0_1_BRKAODD_Msk;
                (epwm)->BRKCTL[i >> 1] |= ((3UL) << EPWM_BRKCTL0_1_BRKAODD_Pos);
            }
        }
        else
        {
            if((i & 0x1UL) == 0UL)
            {
                /* set brake action as low level for even channel */
                (epwm)->BRKCTL[i >> 1] &= ~EPWM_BRKCTL0_1_BRKAEVEN_Msk;
                (epwm)->BRKCTL[i >> 1] |= ((2UL) << EPWM_BRKCTL0_1_BRKAEVEN_Pos);
            }
            else
            {
                /* set brake action as low level for odd channel */
                (epwm)->BRKCTL[i >> 1] &= ~EPWM_BRKCTL0_1_BRKAODD_Msk;
                (epwm)->BRKCTL[i >> 1] |= ((2UL) << EPWM_BRKCTL0_1_BRKAODD_Pos);
            }
        }
    }
}

/**
 * @brief Enable capture of selected channel(s)
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to enable capture of selected channel(s).
 */
void EPWM_EnableCapture(EPWM_T *epwm, uint32_t u32ChannelMask)
{
    (epwm)->CAPINEN |= u32ChannelMask;
    (epwm)->CAPCTL |= u32ChannelMask;
}

/**
 * @brief Disable capture of selected channel(s)
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to disable capture of selected channel(s).
 */
void EPWM_DisableCapture(EPWM_T *epwm, uint32_t u32ChannelMask)
{
    (epwm)->CAPINEN &= ~u32ChannelMask;
    (epwm)->CAPCTL &= ~u32ChannelMask;
}

/**
 * @brief Enables EPWM output generation of selected channel(s)
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Set bit 0 to 1 enables channel 0 output, set bit 1 to 1 enables channel 1 output...
 * @return None
 * @details This function is used to enable EPWM output generation of selected channel(s).
 */
void EPWM_EnableOutput(EPWM_T *epwm, uint32_t u32ChannelMask)
{
    (epwm)->POEN |= u32ChannelMask;
}

/**
 * @brief Disables EPWM output generation of selected channel(s)
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Set bit 0 to 1 disables channel 0 output, set bit 1 to 1 disables channel 1 output...
 * @return None
 * @details This function is used to disable EPWM output generation of selected channel(s).
 */
void EPWM_DisableOutput(EPWM_T *epwm, uint32_t u32ChannelMask)
{
    (epwm)->POEN &= ~u32ChannelMask;
}

/**
 * @brief Enables PDMA transfer of selected channel for EPWM capture
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number.
 * @param[in] u32RisingFirst The capture order is rising, falling first. Every two channels share the same setting. Valid values are TRUE and FALSE.
 * @param[in] u32Mode Captured data transferred by PDMA interrupt type. It could be either
 *              - \ref EPWM_CAPTURE_PDMA_RISING_LATCH
 *              - \ref EPWM_CAPTURE_PDMA_FALLING_LATCH
 *              - \ref EPWM_CAPTURE_PDMA_RISING_FALLING_LATCH
 * @return None
 * @details This function is used to enable PDMA transfer of selected channel(s) for EPWM capture.
 * @note This function can only selects even or odd channel of pairs to do PDMA transfer.
 */
void EPWM_EnablePDMA(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32RisingFirst, uint32_t u32Mode)
{
    uint32_t u32IsOddCh;
    u32IsOddCh = u32ChannelNum & 0x1UL;
    (epwm)->PDMACTL = ((epwm)->PDMACTL & ~((EPWM_PDMACTL_CHSEL0_1_Msk | EPWM_PDMACTL_CAPORD0_1_Msk | EPWM_PDMACTL_CAPMOD0_1_Msk) << ((u32ChannelNum >> 1) << 3))) | \
                      (((u32IsOddCh << EPWM_PDMACTL_CHSEL0_1_Pos) | (u32RisingFirst << EPWM_PDMACTL_CAPORD0_1_Pos) | \
                        u32Mode | EPWM_PDMACTL_CHEN0_1_Msk) << ((u32ChannelNum >> 1) << 3));
}

/**
 * @brief Disables PDMA transfer of selected channel for EPWM capture
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number.
 * @return None
 * @details This function is used to enable PDMA transfer of selected channel(s) for EPWM capture.
 */
void EPWM_DisablePDMA(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->PDMACTL &= ~(EPWM_PDMACTL_CHEN0_1_Msk << ((u32ChannelNum >> 1) << 3));
}

/**
 * @brief Enable Dead zone of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32Duration Dead zone length in EPWM clock count, valid values are between 0~0xFFF, but 0 means there is no Dead zone.
 * @return None
 * @details This function is used to enable Dead zone of selected channel.
 *          The write-protection function should be disabled before using this function.
 * @note Every two channels share the same setting.
 */
void EPWM_EnableDeadZone(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32Duration)
{
    /* every two channels share the same setting */
    (epwm)->DTCTL[(u32ChannelNum) >> 1] &= ~EPWM_DTCTL0_1_DTCNT_Msk;
    (epwm)->DTCTL[(u32ChannelNum) >> 1] |= EPWM_DTCTL0_1_DTEN_Msk | u32Duration;
}

/**
 * @brief Disable Dead zone of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable Dead zone of selected channel.
 *          The write-protection function should be disabled before using this function.
 */
void EPWM_DisableDeadZone(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    /* every two channels shares the same setting */
    (epwm)->DTCTL[(u32ChannelNum) >> 1] &= ~EPWM_DTCTL0_1_DTEN_Msk;
}

/**
 * @brief Enable capture interrupt of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32Edge Rising or falling edge to latch counter.
 *              - \ref EPWM_CAPTURE_INT_RISING_LATCH
 *              - \ref EPWM_CAPTURE_INT_FALLING_LATCH
 * @return None
 * @details This function is used to enable capture interrupt of selected channel.
 */
void EPWM_EnableCaptureInt(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    (epwm)->CAPIEN |= (u32Edge << u32ChannelNum);
}

/**
 * @brief Disable capture interrupt of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32Edge Rising or falling edge to latch counter.
 *              - \ref EPWM_CAPTURE_INT_RISING_LATCH
 *              - \ref EPWM_CAPTURE_INT_FALLING_LATCH
 * @return None
 * @details This function is used to disable capture interrupt of selected channel.
 */
void EPWM_DisableCaptureInt(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    (epwm)->CAPIEN &= ~(u32Edge << u32ChannelNum);
}

/**
 * @brief Clear capture interrupt of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32Edge Rising or falling edge to latch counter.
 *              - \ref EPWM_CAPTURE_INT_RISING_LATCH
 *              - \ref EPWM_CAPTURE_INT_FALLING_LATCH
 * @return None
 * @details This function is used to clear capture interrupt of selected channel.
 */
void EPWM_ClearCaptureIntFlag(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    (epwm)->CAPIF = (u32Edge << u32ChannelNum);
}

/**
 * @brief Get capture interrupt of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @retval 0 No capture interrupt
 * @retval 1 Rising edge latch interrupt
 * @retval 2 Falling edge latch interrupt
 * @retval 3 Rising and falling latch interrupt
 * @details This function is used to get capture interrupt of selected channel.
 */
uint32_t EPWM_GetCaptureIntFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    uint32_t u32CapIf = 0UL;

    u32CapIf = ((((epwm)->CAPIF & (EPWM_CAPIF_CFLIF0_Msk << u32ChannelNum)) ? 1UL : 0UL) << 1);
    u32CapIf |= (((epwm)->CAPIF & (EPWM_CAPIF_CRLIF0_Msk << u32ChannelNum)) ? 1UL : 0UL);
    return u32CapIf;
}
/**
 * @brief Enable duty interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32IntDutyType Duty interrupt type, could be either
 *              - \ref EPWM_DUTY_INT_DOWN_COUNT_MATCH_CMP
 *              - \ref EPWM_DUTY_INT_UP_COUNT_MATCH_CMP
 * @return None
 * @details This function is used to enable duty interrupt of selected channel.
 */
void EPWM_EnableDutyInt(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32IntDutyType)
{
    (epwm)->INTEN0 |= (u32IntDutyType << u32ChannelNum);
}

/**
 * @brief Disable duty interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable duty interrupt of selected channel.
 */
void EPWM_DisableDutyInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->INTEN0 &= ~((EPWM_DUTY_INT_DOWN_COUNT_MATCH_CMP | EPWM_DUTY_INT_UP_COUNT_MATCH_CMP) << u32ChannelNum);
}

/**
 * @brief Clear duty interrupt flag of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to clear duty interrupt flag of selected channel.
 */
void EPWM_ClearDutyIntFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->INTSTS0 = (EPWM_INTSTS0_CMPUIF0_Msk | EPWM_INTSTS0_CMPDIF0_Msk) << u32ChannelNum;
}

/**
 * @brief Get duty interrupt flag of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return Duty interrupt flag of specified channel
 * @retval 0 Duty interrupt did not occur
 * @retval 1 Duty interrupt occurred
 * @details This function is used to get duty interrupt flag of selected channel.
 */
uint32_t EPWM_GetDutyIntFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    return ((((epwm)->INTSTS0 & ((EPWM_INTSTS0_CMPDIF0_Msk | EPWM_INTSTS0_CMPUIF0_Msk) << u32ChannelNum))) ? 1UL : 0UL);
}

/**
 * @brief This function enable fault brake interrupt
 * @param[in] epwm The pointer of the specified EPWM module
 * @param[in] u32BrakeSource Fault brake source.
 *              - \ref EPWM_FB_EDGE
 *              - \ref EPWM_FB_LEVEL
 * @return None
 * @details This function is used to enable fault brake interrupt.
 *          The write-protection function should be disabled before using this function.
 * @note Every two channels share the same setting.
 */
void EPWM_EnableFaultBrakeInt(EPWM_T *epwm, uint32_t u32BrakeSource)
{
    (epwm)->INTEN1 |= (0x7UL << u32BrakeSource);
}

/**
 * @brief This function disable fault brake interrupt
 * @param[in] epwm The pointer of the specified EPWM module
 * @param[in] u32BrakeSource Fault brake source.
 *              - \ref EPWM_FB_EDGE
 *              - \ref EPWM_FB_LEVEL
 * @return None
 * @details This function is used to disable fault brake interrupt.
 *          The write-protection function should be disabled before using this function.
 * @note Every two channels share the same setting.
 */
void EPWM_DisableFaultBrakeInt(EPWM_T *epwm, uint32_t u32BrakeSource)
{
    (epwm)->INTEN1 &= ~(0x7UL << u32BrakeSource);
}

/**
 * @brief This function clear fault brake interrupt of selected source
 * @param[in] epwm The pointer of the specified EPWM module
 * @param[in] u32BrakeSource Fault brake source.
 *              - \ref EPWM_FB_EDGE
 *              - \ref EPWM_FB_LEVEL
 * @return None
 * @details This function is used to clear fault brake interrupt of selected source.
 *          The write-protection function should be disabled before using this function.
 */
void EPWM_ClearFaultBrakeIntFlag(EPWM_T *epwm, uint32_t u32BrakeSource)
{
    (epwm)->INTSTS1 = (0x3fUL << u32BrakeSource);
}

/**
 * @brief This function get fault brake interrupt flag of selected source
 * @param[in] epwm The pointer of the specified EPWM module
 * @param[in] u32BrakeSource Fault brake source, could be either
 *              - \ref EPWM_FB_EDGE
 *              - \ref EPWM_FB_LEVEL
 * @return Fault brake interrupt flag of specified source
 * @retval 0 Fault brake interrupt did not occurred
 * @retval 1 Fault brake interrupt occurred
 * @details This function is used to get fault brake interrupt flag of selected source.
 */
uint32_t EPWM_GetFaultBrakeIntFlag(EPWM_T *epwm, uint32_t u32BrakeSource)
{
    return (((epwm)->INTSTS1 & (0x3fUL << u32BrakeSource)) ? 1UL : 0UL);
}

/**
 * @brief Enable period interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32IntPeriodType Period interrupt type. This parameter is not used.
 * @return None
 * @details This function is used to enable period interrupt of selected channel.
 */
void EPWM_EnablePeriodInt(EPWM_T *epwm, uint32_t u32ChannelNum,  uint32_t u32IntPeriodType)
{
    (void)u32IntPeriodType;
    (epwm)->INTEN0 |= (EPWM_INTEN0_PIEN0_Msk << u32ChannelNum);
}

/**
 * @brief Disable period interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable period interrupt of selected channel.
 */
void EPWM_DisablePeriodInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->INTEN0 &= ~(EPWM_INTEN0_PIEN0_Msk << u32ChannelNum);
}

/**
 * @brief Clear period interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to clear period interrupt of selected channel.
 */
void EPWM_ClearPeriodIntFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->INTSTS0 = (EPWM_INTSTS0_PIF0_Msk << u32ChannelNum);
}

/**
 * @brief Get period interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return Period interrupt flag of specified channel
 * @retval 0 Period interrupt did not occur
 * @retval 1 Period interrupt occurred
 * @details This function is used to get period interrupt of selected channel.
 */
uint32_t EPWM_GetPeriodIntFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    return ((((epwm)->INTSTS0 & (EPWM_INTSTS0_PIF0_Msk << u32ChannelNum))) ? 1UL : 0UL);
}

/**
 * @brief Enable zero interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to enable zero interrupt of selected channel.
 */
void EPWM_EnableZeroInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->INTEN0 |= (EPWM_INTEN0_ZIEN0_Msk << u32ChannelNum);
}

/**
 * @brief Disable zero interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable zero interrupt of selected channel.
 */
void EPWM_DisableZeroInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->INTEN0 &= ~(EPWM_INTEN0_ZIEN0_Msk << u32ChannelNum);
}

/**
 * @brief Clear zero interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to clear zero interrupt of selected channel.
 */
void EPWM_ClearZeroIntFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->INTSTS0 = (EPWM_INTSTS0_ZIF0_Msk << u32ChannelNum);
}

/**
 * @brief Get zero interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return Zero interrupt flag of specified channel
 * @retval 0 Zero interrupt did not occur
 * @retval 1 Zero interrupt occurred
 * @details This function is used to get zero interrupt of selected channel.
 */
uint32_t EPWM_GetZeroIntFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    return ((((epwm)->INTSTS0 & (EPWM_INTSTS0_ZIF0_Msk << u32ChannelNum))) ? 1UL : 0UL);
}

/**
 * @brief Enable interrupt flag accumulator of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32IntFlagCnt Interrupt flag counter. Valid values are between 0~65535.
 * @param[in] u32IntAccSrc Interrupt flag accumulator source selection.
 *              - \ref EPWM_IFA_ZERO_POINT
 *              - \ref EPWM_IFA_PERIOD_POINT
 *              - \ref EPWM_IFA_COMPARE_UP_COUNT_POINT
 *              - \ref EPWM_IFA_COMPARE_DOWN_COUNT_POINT
 * @return None
 * @details This function is used to enable interrupt flag accumulator of selected channel.
 */
void EPWM_EnableAcc(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32IntFlagCnt, uint32_t u32IntAccSrc)
{
    (epwm)->IFA[u32ChannelNum] = (((epwm)->IFA[u32ChannelNum] & ~((EPWM_IFA0_IFACNT_Msk | EPWM_IFA0_IFASEL_Msk))) | \
                                  (EPWM_IFA0_IFAEN_Msk | (u32IntAccSrc << EPWM_IFA0_IFASEL_Pos) | u32IntFlagCnt));
}

/**
 * @brief Disable interrupt flag accumulator of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to Disable interrupt flag accumulator of selected channel.
 */
void EPWM_DisableAcc(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->IFA[u32ChannelNum] = ((epwm)->IFA[u32ChannelNum] & ~(EPWM_IFA0_IFAEN_Msk));
}

/**
 * @brief Enable interrupt flag accumulator interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to enable interrupt flag accumulator interrupt of selected channel.
 */
void EPWM_EnableAccInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->AINTEN |= (1UL << (u32ChannelNum));
}

/**
 * @brief Disable interrupt flag accumulator interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable interrupt flag accumulator interrupt of selected channel.
 */
void EPWM_DisableAccInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->AINTEN &= ~(1UL << (u32ChannelNum));
}

/**
 * @brief Clear interrupt flag accumulator interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to clear interrupt flag accumulator interrupt of selected channel.
 */
void EPWM_ClearAccInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->AINTSTS = (1UL << (u32ChannelNum));
}

/**
 * @brief Get interrupt flag accumulator interrupt of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @retval 0 Accumulator interrupt did not occur
 * @retval 1 Accumulator interrupt occurred
 * @details This function is used to Get interrupt flag accumulator interrupt of selected channel.
 */
uint32_t EPWM_GetAccInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    return (((epwm)->AINTSTS & (1UL << (u32ChannelNum))) ? 1UL : 0UL);
}

/**
 * @brief Enable accumulator PDMA of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to enable accumulator interrupt trigger PDMA of selected channel.
 */
void EPWM_EnableAccPDMA(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->APDMACTL |= (1UL << (u32ChannelNum));
}

/**
 * @brief Disable accumulator PDMA of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable accumulator interrupt trigger PDMA of selected channel.
 */
void EPWM_DisableAccPDMA(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->APDMACTL &= ~(1UL << (u32ChannelNum));
}

/**
 * @brief Enable interrupt flag accumulator stop mode of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to enable interrupt flag accumulator stop mode of selected channel.
 */
void EPWM_EnableAccStopMode(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->IFA[u32ChannelNum] |= EPWM_IFA0_STPMOD_Msk;
}

/**
 * @brief Disable interrupt flag accumulator stop mode of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to disable interrupt flag accumulator stop mode of selected channel.
 */
void EPWM_DisableAccStopMode(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->IFA[u32ChannelNum] &= ~EPWM_IFA0_STPMOD_Msk;
}

/**
 * @brief Clear free trigger duty interrupt flag of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to clear free trigger duty interrupt flag of selected channel.
 */
void EPWM_ClearFTDutyIntFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->FTCI = ((EPWM_FTCI_FTCMU0_Msk | EPWM_FTCI_FTCMD0_Msk) << (u32ChannelNum >> 1));
}

/**
 * @brief Get free trigger duty interrupt flag of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return Duty interrupt flag of specified channel
 * @retval 0 Free trigger duty interrupt did not occur
 * @retval 1 Free trigger duty interrupt occurred
 * @details This function is used to get free trigger duty interrupt flag of selected channel.
 */
uint32_t EPWM_GetFTDutyIntFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    return (((epwm)->FTCI & ((EPWM_FTCI_FTCMU0_Msk | EPWM_FTCI_FTCMD0_Msk) << (u32ChannelNum >> 1))) ? 1UL : 0UL);
}

/**
 * @brief Enable load mode of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32LoadMode EPWM counter loading mode.
 *              - \ref EPWM_LOAD_MODE_IMMEDIATE
 *              - \ref EPWM_LOAD_MODE_WINDOW
 *              - \ref EPWM_LOAD_MODE_CENTER
 * @return None
 * @details This function is used to enable load mode of selected channel.
 */
void EPWM_EnableLoadMode(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32LoadMode)
{
    (epwm)->CTL0 |= (u32LoadMode << u32ChannelNum);
}

/**
 * @brief Disable load mode of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32LoadMode EPWM counter loading mode.
 *              - \ref EPWM_LOAD_MODE_IMMEDIATE
 *              - \ref EPWM_LOAD_MODE_WINDOW
 *              - \ref EPWM_LOAD_MODE_CENTER
 * @return None
 * @details This function is used to disable load mode of selected channel.
 */
void EPWM_DisableLoadMode(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32LoadMode)
{
    (epwm)->CTL0 &= ~(u32LoadMode << u32ChannelNum);
}

/**
 * @brief Configure synchronization phase of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32SyncSrc EPWM synchronize source selection.
 *              - \ref EPWM_SYNC_OUT_FROM_SYNCIN_SWSYNC
 *              - \ref EPWM_SYNC_OUT_FROM_COUNT_TO_ZERO
 *              - \ref EPWM_SYNC_OUT_FROM_COUNT_TO_COMPARATOR
 *              - \ref EPWM_SYNC_OUT_DISABLE
 * @param[in] u32Direction Phase direction. Control EPWM counter count decrement or increment  after synchronizing.
 *              - \ref EPWM_PHS_DIR_DECREMENT
 *              - \ref EPWM_PHS_DIR_INCREMENT
 * @param[in] u32StartPhase Synchronous start phase value. Valid values are between 0~65535.
 * @return None
 * @details This function is used to configure synchronization phase of selected channel.
 * @note Every two channels share the same setting.
 */
void EPWM_ConfigSyncPhase(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32SyncSrc, uint32_t u32Direction, uint32_t u32StartPhase)
{
    /* every two channels shares the same setting */
    u32ChannelNum >>= 1;
    (epwm)->SYNC = (((epwm)->SYNC & ~((EPWM_SYNC_SINSRC0_Msk << (u32ChannelNum << 1)) | (EPWM_SYNC_PHSDIR0_Msk << u32ChannelNum))) | \
                    (u32Direction << EPWM_SYNC_PHSDIR0_Pos << u32ChannelNum) | (u32SyncSrc << EPWM_SYNC_SINSRC0_Pos) << (u32ChannelNum << 1));
    (epwm)->PHS[(u32ChannelNum)] = u32StartPhase;
}


/**
 * @brief Enable SYNC phase of selected channel(s)
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to enable SYNC phase of selected channel(s).
 * @note Every two channels share the same setting.
 */
void EPWM_EnableSyncPhase(EPWM_T *epwm, uint32_t u32ChannelMask)
{
    uint32_t i;
    for(i = 0UL; i < EPWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1UL << i))
        {
            (epwm)->SYNC |= (EPWM_SYNC_PHSEN0_Msk << (i >> 1));
        }
    }
}

/**
 * @brief Disable SYNC phase of selected channel(s)
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 * @details This function is used to disable SYNC phase of selected channel(s).
 * @note Every two channels share the same setting.
 */
void EPWM_DisableSyncPhase(EPWM_T *epwm, uint32_t u32ChannelMask)
{
    uint32_t i;
    for(i = 0UL; i < EPWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1UL << i))
        {
            (epwm)->SYNC &= ~(EPWM_SYNC_PHSEN0_Msk << (i >> 1));
        }
    }
}

/**
 * @brief Enable EPWM SYNC_IN noise filter function
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ClkCnt SYNC Edge Detector Filter Count. This controls the counter number of edge detector.
 *            The valid value is 0~7.
 * @param[in] u32ClkDivSel SYNC Edge Detector Filter Clock Selection.
 *              - \ref EPWM_NF_CLK_DIV_1
 *              - \ref EPWM_NF_CLK_DIV_2
 *              - \ref EPWM_NF_CLK_DIV_4
 *              - \ref EPWM_NF_CLK_DIV_8
 *              - \ref EPWM_NF_CLK_DIV_16
 *              - \ref EPWM_NF_CLK_DIV_32
 *              - \ref EPWM_NF_CLK_DIV_64
 *              - \ref EPWM_NF_CLK_DIV_128
 * @return None
 * @details This function is used to enable EPWM SYNC_IN noise filter function.
 */
void EPWM_EnableSyncNoiseFilter(EPWM_T *epwm, uint32_t u32ClkCnt, uint32_t u32ClkDivSel)
{
    (epwm)->SYNC = ((epwm)->SYNC & ~(EPWM_SYNC_SFLTCNT_Msk | EPWM_SYNC_SFLTCSEL_Msk)) | \
                   ((u32ClkCnt << EPWM_SYNC_SFLTCNT_Pos) | (u32ClkDivSel << EPWM_SYNC_SFLTCSEL_Pos) | EPWM_SYNC_SNFLTEN_Msk);
}

/**
 * @brief Disable EPWM SYNC_IN noise filter function
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @return None
 * @details This function is used to Disable EPWM SYNC_IN noise filter function.
 */
void EPWM_DisableSyncNoiseFilter(EPWM_T *epwm)
{
    (epwm)->SYNC &= ~EPWM_SYNC_SNFLTEN_Msk;
}

/**
 * @brief Enable EPWM SYNC input pin inverse function
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @return None
 * @details This function is used to enable EPWM SYNC input pin inverse function.
 */
void EPWM_EnableSyncPinInverse(EPWM_T *epwm)
{
    (epwm)->SYNC |= EPWM_SYNC_SINPINV_Msk;
}

/**
 * @brief Disable EPWM SYNC input pin inverse function
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @return None
 * @details This function is used to Disable EPWM SYNC input pin inverse function.
 */
void EPWM_DisableSyncPinInverse(EPWM_T *epwm)
{
    (epwm)->SYNC &= (~EPWM_SYNC_SINPINV_Msk);
}

/**
 * @brief Set EPWM clock source
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @param[in] u32ClkSrcSel EPWM external clock source.
 *              - \ref EPWM_CLKSRC_EPWM_CLK
 *              - \ref EPWM_CLKSRC_TIMER0
 *              - \ref EPWM_CLKSRC_TIMER1
 *              - \ref EPWM_CLKSRC_TIMER2
 *              - \ref EPWM_CLKSRC_TIMER3
 * @return None
 * @details This function is used to set EPWM clock source.
 * @note Every two channels share the same setting.
 * @note If the clock source of EPWM counter is selected from TIMERn interrupt events, the TRGEPWM(TIMERn_TRGCTL[1], n=0,1..3) bit must be set as 1.
 */
void EPWM_SetClockSource(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32ClkSrcSel)
{
    (epwm)->CLKSRC = ((epwm)->CLKSRC & ~(EPWM_CLKSRC_ECLKSRC0_Msk << ((u32ChannelNum >> 1) << 3))) | \
                     (u32ClkSrcSel << ((u32ChannelNum >> 1) << 3));
}

/**
 * @brief Enable EPWM brake noise filter function
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32BrakePinNum Brake pin selection. Valid values are 0 or 1.
 * @param[in] u32ClkCnt SYNC Edge Detector Filter Count. This controls the counter number of edge detector
 * @param[in] u32ClkDivSel SYNC Edge Detector Filter Clock Selection.
 *              - \ref EPWM_NF_CLK_DIV_1
 *              - \ref EPWM_NF_CLK_DIV_2
 *              - \ref EPWM_NF_CLK_DIV_4
 *              - \ref EPWM_NF_CLK_DIV_8
 *              - \ref EPWM_NF_CLK_DIV_16
 *              - \ref EPWM_NF_CLK_DIV_32
 *              - \ref EPWM_NF_CLK_DIV_64
 *              - \ref EPWM_NF_CLK_DIV_128
 * @return None
 * @details This function is used to enable EPWM brake noise filter function.
 */
void EPWM_EnableBrakeNoiseFilter(EPWM_T *epwm, uint32_t u32BrakePinNum, uint32_t u32ClkCnt, uint32_t u32ClkDivSel)
{
    (epwm)->BNF = ((epwm)->BNF & ~((EPWM_BNF_BRK0FCNT_Msk | EPWM_BNF_BRK0NFSEL_Msk) << (u32BrakePinNum << 3))) | \
                  (((u32ClkCnt << EPWM_BNF_BRK0FCNT_Pos) | (u32ClkDivSel << EPWM_BNF_BRK0NFSEL_Pos) | EPWM_BNF_BRK0NFEN_Msk) << (u32BrakePinNum << 3));
}

/**
 * @brief Disable EPWM brake noise filter function
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32BrakePinNum Brake pin selection. Valid values are 0 or 1.
 * @return None
 * @details This function is used to disable EPWM brake noise filter function.
 */
void EPWM_DisableBrakeNoiseFilter(EPWM_T *epwm, uint32_t u32BrakePinNum)
{
    (epwm)->BNF &= ~(EPWM_BNF_BRK0NFEN_Msk << (u32BrakePinNum << 3));
}

/**
 * @brief Enable EPWM brake pin inverse function
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32BrakePinNum Brake pin selection. Valid values are 0 or 1.
 * @return None
 * @details This function is used to enable EPWM brake pin inverse function.
 */
void EPWM_EnableBrakePinInverse(EPWM_T *epwm, uint32_t u32BrakePinNum)
{
    (epwm)->BNF |= (EPWM_BNF_BRK0PINV_Msk << (u32BrakePinNum << 3));
}

/**
 * @brief Disable EPWM brake pin inverse function
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32BrakePinNum Brake pin selection. Valid values are 0 or 1.
 * @return None
 * @details This function is used to disable EPWM brake pin inverse function.
 */
void EPWM_DisableBrakePinInverse(EPWM_T *epwm, uint32_t u32BrakePinNum)
{
    (epwm)->BNF &= ~(EPWM_BNF_BRK0PINV_Msk << (u32BrakePinNum * (uint32_t)EPWM_BNF_BRK1NFEN_Pos));
}

/**
 * @brief Set EPWM brake pin source
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32BrakePinNum Brake pin selection. Valid values are 0 or 1.
 * @param[in] u32SelAnotherModule Select to another module. Valid values are TRUE or FALSE.
 * @return None
 * @details This function is used to set EPWM brake pin source.
 */
void EPWM_SetBrakePinSource(EPWM_T *epwm, uint32_t u32BrakePinNum, uint32_t u32SelAnotherModule)
{
    (epwm)->BNF = ((epwm)->BNF & ~(EPWM_BNF_BK0SRC_Msk << (u32BrakePinNum << 3))) | (u32SelAnotherModule << ((uint32_t)EPWM_BNF_BK0SRC_Pos + (u32BrakePinNum << 3)));
}

/**
 * @brief Set EPWM leading edge blanking function
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32TrigSrcSel Leading edge blanking source selection.
 *              - \ref EPWM_LEBCTL_SRCEN0
 *              - \ref EPWM_LEBCTL_SRCEN2
 *              - \ref EPWM_LEBCTL_SRCEN4
 *              - \ref EPWM_LEBCTL_SRCEN0_2
 *              - \ref EPWM_LEBCTL_SRCEN0_4
 *              - \ref EPWM_LEBCTL_SRCEN2_4
 *              - \ref EPWM_LEBCTL_SRCEN0_2_4
 * @param[in] u32TrigType  Leading edge blanking trigger type.
 *              - \ref EPWM_LEBCTL_TRGTYPE_RISING
 *              - \ref EPWM_LEBCTL_TRGTYPE_FALLING
 *              - \ref EPWM_LEBCTL_TRGTYPE_RISING_OR_FALLING
 * @param[in] u32BlankingCnt  Leading Edge Blanking Counter. Valid values are between 1~512.
                              This counter value decides leading edge blanking window size, and this counter clock base is ECLK.
 * @param[in] u32BlankingEnable Enable EPWM leading edge blanking function. Valid values are TRUE (ENABLE) or FALSE (DISABLE).
 *              - \ref FALSE
 *              - \ref TRUE
 * @return None
 * @details This function is used to configure EPWM leading edge blanking function that blank the false trigger from ACMP brake source which may cause by EPWM output transition.
 * @note EPWM leading edge blanking function is only used for brake source from ACMP.
 */
void EPWM_SetLeadingEdgeBlanking(EPWM_T *epwm, uint32_t u32TrigSrcSel, uint32_t u32TrigType, uint32_t u32BlankingCnt, uint32_t u32BlankingEnable)
{
    (epwm)->LEBCTL = (u32TrigType) | (u32TrigSrcSel) | (u32BlankingEnable);
    /* Blanking window size = LEBCNT + 1, so LEBCNT = u32BlankingCnt - 1 */
    (epwm)->LEBCNT = (u32BlankingCnt) - 1UL;
}

/**
 * @brief Get the time-base counter reached its maximum value flag of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return Count to max interrupt flag of specified channel
 * @retval 0 Count to max interrupt did not occur
 * @retval 1 Count to max interrupt occurred
 * @details This function is used to get the time-base counter reached its maximum value flag of selected channel.
 */
uint32_t EPWM_GetWrapAroundFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    return (((epwm)->STATUS & (EPWM_STATUS_CNTMAXF0_Msk << u32ChannelNum)) ? 1UL : 0UL);
}

/**
 * @brief Clear the time-base counter reached its maximum value flag of selected channel
 * @param[in] epwm The pointer of the specified EPWM module
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5
 * @return None
 * @details This function is used to clear the time-base counter reached its maximum value flag of selected channel.
 */
void EPWM_ClearWrapAroundFlag(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->STATUS = (EPWM_STATUS_CNTMAXF0_Msk << u32ChannelNum);
}

/**
 * @brief Enable fault detect of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @param[in] u32AfterPrescaler Fault Detect Clock Source is from prescaler output. Valid values are TRUE (after prescaler) or FALSE (before prescaler).
 * @param[in] u32ClkSel Fault Detect Clock Select.
 *              - \ref EPWM_FDCTL_FDCKSEL_CLK_DIV_1
 *              - \ref EPWM_FDCTL_FDCKSEL_CLK_DIV_2
 *              - \ref EPWM_FDCTL_FDCKSEL_CLK_DIV_4
 *              - \ref EPWM_FDCTL_FDCKSEL_CLK_DIV_8
 * @return None
 * @details This function is used to enable fault detect of selected channel.
 */
void EPWM_EnableFaultDetect(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32AfterPrescaler, uint32_t u32ClkSel)
{
    (epwm)->FDEN = ((epwm)->FDEN & ~(EPWM_FDEN_FDCKS0_Msk << (u32ChannelNum))) | \
                   ((EPWM_FDEN_FDEN0_Msk | ((u32AfterPrescaler) << EPWM_FDEN_FDCKS0_Pos)) << (u32ChannelNum));
    (epwm)->FDCTL[(u32ChannelNum)] = ((epwm)->FDCTL[(u32ChannelNum)] & ~EPWM_FDCTL0_FDCKSEL_Msk) | (u32ClkSel);
}

/**
 * @brief Disable fault detect of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @return None
 * @details This function is used to disable fault detect of selected channel.
 */
void EPWM_DisableFaultDetect(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->FDEN &= ~(EPWM_FDEN_FDEN0_Msk << (u32ChannelNum));
}

/**
 * @brief Enable fault detect output of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @return None
 * @details This function is used to enable fault detect output of selected channel.
 */
void EPWM_EnableFaultDetectOutput(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->FDEN &= ~(EPWM_FDEN_FDODIS0_Msk << (u32ChannelNum));
}

/**
 * @brief Disable fault detect output of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @return None
 * @details This function is used to disable fault detect output of selected channel.
 */
void EPWM_DisableFaultDetectOutput(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->FDEN |= (EPWM_FDEN_FDODIS0_Msk << (u32ChannelNum));
}

/**
 * @brief Enable fault detect deglitch function of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @param[in] u32DeglitchSmpCycle Deglitch Sampling Cycle. Valid values are between 0~7.
 * @return None
 * @details This function is used to enable fault detect deglitch function of selected channel.
 */
void EPWM_EnableFaultDetectDeglitch(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32DeglitchSmpCycle)
{
    (epwm)->FDCTL[(u32ChannelNum)] = ((epwm)->FDCTL[(u32ChannelNum)] & (~EPWM_FDCTL0_DGSMPCYC_Msk)) | \
                                     (EPWM_FDCTL0_FDDGEN_Msk | ((u32DeglitchSmpCycle) << EPWM_FDCTL0_DGSMPCYC_Pos));
}

/**
 * @brief Disable fault detect deglitch function of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @return None
 * @details This function is used to disable fault detect deglitch function of selected channel.
 */
void EPWM_DisableFaultDetectDeglitch(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->FDCTL[(u32ChannelNum)] &= ~EPWM_FDCTL0_FDDGEN_Msk;
}

/**
 * @brief Enable fault detect mask function of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @param[in] u32MaskCnt Transition mask counter. Valid values are between 0~0x7F.
 * @return None
 * @details This function is used to enable fault detect mask function of selected channel.
 */
void EPWM_EnableFaultDetectMask(EPWM_T *epwm, uint32_t u32ChannelNum, uint32_t u32MaskCnt)
{
    (epwm)->FDCTL[(u32ChannelNum)] = ((epwm)->FDCTL[(u32ChannelNum)] & (~EPWM_FDCTL0_TRMSKCNT_Msk)) | (EPWM_FDCTL0_FDMSKEN_Msk | (u32MaskCnt));
}

/**
 * @brief Disable fault detect mask function of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @return None
 * @details This function is used to disable fault detect mask function of selected channel.
 */
void EPWM_DisableFaultDetectMask(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->FDCTL[(u32ChannelNum)] &= ~EPWM_FDCTL0_FDMSKEN_Msk;
}

/**
 * @brief Enable fault detect interrupt of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @return None
 * @details This function is used to enable fault detect interrupt of selected channel.
 */
void EPWM_EnableFaultDetectInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->FDIEN |= (EPWM_FDIEN_FDIEN0_Msk << (u32ChannelNum));
}

/**
 * @brief Disable fault detect interrupt of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @return None
 * @details This function is used to disable fault detect interrupt of selected channel.
 */
void EPWM_DisableFaultDetectInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->FDIEN &= ~(EPWM_FDIEN_FDIEN0_Msk << (u32ChannelNum));
}

/**
 * @brief Clear fault detect interrupt of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @return None
 * @details This function is used to clear fault detect interrupt of selected channel.
 */
void EPWM_ClearFaultDetectInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    (epwm)->FDSTS = (EPWM_FDSTS_FDIF0_Msk << (u32ChannelNum));
}

/**
 * @brief Get fault detect interrupt of selected channel.
 * @param[in] epwm The pointer of the specified EPWM module.
 *                - EPWM0 : EPWM Group 0
 *                - EPWM1 : EPWM Group 1
 * @param[in] u32ChannelNum EPWM channel number. Valid values are between 0~5.
 * @retval 0 Fault detect interrupt did not occur.
 * @retval 1 Fault detect interrupt occurred.
 * @details This function is used to Get fault detect interrupt of selected channel.
 */
uint32_t EPWM_GetFaultDetectInt(EPWM_T *epwm, uint32_t u32ChannelNum)
{
    return (((epwm)->FDSTS & (EPWM_FDSTS_FDIF0_Msk << (u32ChannelNum))) ? 1UL : 0UL);
}

/**@}*/ /* end of group EPWM_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group EPWM_Driver */

/**@}*/ /* end of group Standard_Driver */

