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
 * @file n32g45x_tsc.c
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x.h"
#include "n32g45x_tsc.h"

/**
* @brief  Init TSC config
* @param  TSC_Init: TSC initialize structure
* @return : TSC_ErrorTypeDef
*/
TSC_ErrorTypeDef TSC_Init(TSC_InitType* TSC_Init)
{
    uint32_t tempreg,timeout;

    assert_param(IS_TSC_DET_MODE(TSC_Init->Mode));
    assert_param(IS_TSC_DET_PERIOD(TSC_Init->Period));
    assert_param(IS_TSC_FILTER(TSC_Init->Filter));
    assert_param(IS_TSC_DET_TYPE(TSC_Init->Type));
    assert_param(IS_TSC_INT(TSC_Init->Int));
    assert_param(IS_TSC_OUT(TSC_Init->Out));
    assert_param(IS_TSC_CHN(TSC_Init->Chn));
    assert_param(IS_TSC_PAD_OPTION(TSC_Init->PadOpt));
    assert_param(IS_TSC_PAD_SPEED(TSC_Init->Speed));

    /* waiting tsc hw for idle status.*/
    timeout = 0;
    do
    {
        __TSC_HW_DISABLE();

        if(++timeout > TSC_TIMEOUT)
            return TSC_ERROR_HW_MODE;
    }while (__TSC_GET_HW_MODE());

    /*TSC_CTRL config*/
    tempreg = 0;
    if(TSC_Init->Mode == TSC_HW_DETECT_MODE)
    {
        tempreg |= TSC_Init->Period;
        tempreg |= TSC_Init->Filter;
        tempreg |= TSC_Init->Type;
        tempreg |= TSC_Init->Int;
    }
    else
        tempreg |= TSC_Init->Out;

    TSC->CTRL = tempreg;

    /*TSC_ANA_SEL config*/
    TSC->ANA_SEL = TSC_Init->PadOpt | TSC_Init->Speed;

    return TSC_ERROR_OK;
}

/**
 * @brief  Config the clock source of TSC
 * @param  TSC_ClkSource specifies the clock source of TSC
 *   This parameter can be one of the following values:
 *     @arg TSC_CLK_SRC_LSI:              TSC clock source is LSI(default)
 *     @arg TSC_CLK_SRC_LSE:              TSC clock source is LSE,and LSE is oscillator
 *     @arg TSC_CLK_SRC_LSE_BYPASS:       TSC clock source is LSE,and LSE is extennal clock
 * @retval TSC error code
 */
TSC_ErrorTypeDef TSC_ClockConfig(uint32_t TSC_ClkSource)
{
    uint32_t timeout;

    /*Enable PWR  peripheral Clock*/
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR,ENABLE);

    if(TSC_CLK_SRC_LSI == TSC_ClkSource)
    {
        /*enable LSI clock*/
        RCC_EnableLsi(ENABLE);

        /*Wait LSI stable*/
        timeout = 0;
        while(RCC_GetFlagStatus(RCC_FLAG_LSIRD) == RESET)
        {
            if(++timeout >TSC_TIMEOUT)
                return TSC_ERROR_CLOCK;
        }
    }
    else if((TSC_CLK_SRC_LSE_BYPASS==TSC_ClkSource)||(TSC_CLK_SRC_LSE==TSC_ClkSource))
    {
        if(RCC_GetFlagStatus(RCC_FLAG_LSERD)==RESET)
        {
            // Set bit 8 of PWR_CTRL1.Open PWR DBP.
            PWR_BackupAccessEnable(ENABLE);
            RCC_ConfigLse(TSC_ClkSource);
            timeout = 0;
            while(RCC_GetFlagStatus(RCC_FLAG_LSERD) == RESET)
            {
                if(++timeout >TSC_TIMEOUT)
                    return TSC_ERROR_CLOCK;
            }
        }
    }
    else
        return TSC_ERROR_PARAMETER;

    /*Enable TSC clk*/
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TSC,ENABLE);

    return TSC_ERROR_OK;
}

/**
* @brief  Configure internal charge resistor for some channels
* @param  res:  internal resistor selecte
*   This parameter can be one of the following values:
*      @arg TSC_RESR_CHN_RESIST_0:    1M OHM
*      @arg TSC_RESR_CHN_RESIST_1:    882K OHM
*      @arg TSC_RESR_CHN_RESIST_2:    756K OHM
*      @arg TSC_RESR_CHN_RESIST_3:    630K OHM
*      @arg TSC_RESR_CHN_RESIST_4:    504K OHM
*      @arg TSC_RESR_CHN_RESIST_5:    378K OHM
*      @arg TSC_RESR_CHN_RESIST_6:    252K OHM
*      @arg TSC_RESR_CHN_RESIST_7:    126K OHM
* @param  Channels: channels to be configed, as TSC_CHNEN defined
*   This parameter:bit[0:23] used,bit[24:31] must be 0
*                  bitx: TSC channel x
* @return: none
*/
TSC_ErrorTypeDef TSC_ConfigInternalResistor(uint32_t Channels, uint32_t res )
{
    uint32_t i,chn,timeout,nReg,nPos;

    assert_param(IS_TSC_CHN(Channels));
    assert_param(IS_TSC_RESISTOR_VALUE(res));

    /*Check charge resistor value */
    if(res > TSC_RESR_CHN_RESIST_125K)
        return TSC_ERROR_PARAMETER;

    /* waiting tsc hw for idle status.*/
    timeout = 0;
    do
    {
        __TSC_HW_DISABLE();

        if(++timeout > TSC_TIMEOUT)
            return TSC_ERROR_HW_MODE;
    }while (__TSC_GET_HW_MODE());

    /* Mask invalie bits*/
    chn  = Channels & TSC_CHNEN_CHN_SEL_MASK;

    /* Set resistance for each channel one by one*/
    for (i = 0; i<MAX_TSC_HW_CHN; i++)
    {
        if (chn & 0x00000001)
        {
            nReg = i >> 3;
            nPos = (i & 0x7UL)*4;
            MODIFY_REG(TSC->RESR[nReg],TSC_RESR_CHN_RESIST_MASK<<nPos,res<<nPos);
        }

        chn >>= 1;
    }

    return TSC_ERROR_OK;
}

/**
* @brief  Configure threshold value for some channels
* @param  Channels: channels to be configed, as TSC_CHNEN defined
*   This parameter:bit[0:23] used,bit[24:31] must be 0
*                  bitx: TSC channel x
* @param  base:   base value of threshold, 0-MAX_TSC_THRESHOLD_BASE
* @param  delta:  delta value of threshold,0-MAX_TSC_THRESHOLD_DELRA
* @return: None
*/
TSC_ErrorTypeDef TSC_ConfigThreshold(  uint32_t Channels, uint32_t base, uint32_t delta)
{
    uint32_t i, chn,timeout;
    assert_param(IS_TSC_CHN(Channels));
    assert_param(IS_TSC_THRESHOLD_BASE(base));
    assert_param(IS_TSC_THRESHOLD_DELTA(delta));

    /*Check the base and delta value*/
    if( (base>MAX_TSC_THRESHOLD_BASE)||(delta>MAX_TSC_THRESHOLD_DELTA))
        return TSC_ERROR_PARAMETER;

    /* waiting tsc hw for idle status.*/
    timeout = 0;
    do
    {
        __TSC_HW_DISABLE();

        if(++timeout > TSC_TIMEOUT)
            return TSC_ERROR_HW_MODE;
    }while (__TSC_GET_HW_MODE());

    /*Mask invalie bits*/
    chn = Channels & TSC_CHNEN_CHN_SEL_MASK;

    /* Set the base and delta for each channnel one by one*/
    for (i = 0; i<MAX_TSC_HW_CHN; i++)
    {
        if (chn & 0x00000001)
        {
            TSC->THRHD[i] = (base<<TSC_THRHD_BASE_SHIFT)|(delta<<TSC_THRHD_DELTA_SHIFT);
        }

        chn >>= 1;
    }

    return TSC_ERROR_OK;
}


/**
* @brief  Get parameters of one channel.
* @param  ChnCfg: Pointer of TSC_ChnCfg structure.
* @param  ChannelNum: The channel number of which we want to get parameters,must be less then MAX_TSC_HW_CHN
* @return: None
*/
TSC_ErrorTypeDef TSC_GetChannelCfg( TSC_ChnCfg* ChnCfg, uint32_t ChannelNum)
{
    uint32_t nReg,nShift;

    assert_param(IS_TSC_CHN_NUMBER(ChannelNum));

    /*Check channel number*/
    if(!(IS_TSC_CHN_NUMBER(ChannelNum)))
        return TSC_ERROR_PARAMETER;

    /* Get the base and delta value for a channel*/
    ChnCfg->TSC_Base     = (TSC->THRHD[ChannelNum] & TSC_THRHD_BASE_MASK) >> TSC_THRHD_BASE_SHIFT;
    ChnCfg->TSC_Delta    = (TSC->THRHD[ChannelNum] & TSC_THRHD_DELTA_MASK)>> TSC_THRHD_DELTA_SHIFT;

    /* Get the charge resistor type for a channel*/
    nReg = ChannelNum>>3;
    nShift = (ChannelNum & 0x7UL)*4;
    ChnCfg->TSC_Resistor = (TSC->RESR[nReg] >> nShift) & TSC_RESR_CHN_RESIST_MASK;

    return TSC_ERROR_OK;
}


/**
 * @brief  Get TSC status value.
 * @param  TSC_Def Pointer of TSC register.
 * @param  type TSC status type.
 */
uint32_t TSC_GetStatus(TSC_Module* TSC_Def, TSC_Status type)
{
    uint32_t value;

    if (TSC_Def)
    {
        switch (type)
        {
        case TSC_ALG_STS_CNTVALUE:
            value = __TSC_GET_CHN_CNT();
            break;

        case TSC_ALG_STS_LESS_DET:
            value = __TSC_GET_HW_DET_TYPE(TSC_DET_TYPE_LESS);
            break;

        case TSC_ALG_STS_GREAT_DET:
            value = __TSC_GET_HW_DET_TYPE(TSC_DET_TYPE_GREAT);
            break;

        case TSC_ALG_STS_CHN_NUM:
            value = __TSC_GET_CHN_NUMBER();
            break;

        case TSC_ALG_DET_DET_ST:
            value = __TSC_GET_HW_MODE();
            break;

        default:
            value = 0;
            break;
        }
    }

    return value;
}

/**
 * @brief  Enable/Disable hardware detection.
 * @param  TSC_Def Pointer of TSC register.
 * @param  Channels Set the channel.
 * @param  Cmd ENABLE:Enable hardware detection,DISALBE:Disable hardware detection.
 * @note You can only output one channel at a time.
 */
void TSC_Cmd(TSC_Module* TSC_Def, uint32_t Channels, FunctionalState Cmd)
{
    if(TSC_Def != TSC)
        return;

    if (Cmd != DISABLE)
    {
        // enable tsc channel
        Channels &= TSC_CHNEN_CHN_SEL_MASK;
        __TSC_CHN_CONFIG(Channels );

        /* Enable the TSC */
        __TSC_HW_ENABLE();
    }
    else
    {
        /* Disable the TSC */
        while (__TSC_GET_HW_MODE())
        {
            __TSC_HW_DISABLE();
        }

        __TSC_CHN_CONFIG(0);
    }
}

/**
 * @brief  Toggle channels to output to TIMER2/TIMER4 by software mode.
 * @param  TSC_Def Pointer of TSC register.
 * @param  Channel Set the channel.
 * @param  TIMx Select timer.
 * @param Cmd ENABLE:Enable hardware detection,DISALBE:Disable hardware detection.
 * @note It can only output to TIMER2/TIMER4 by software mode.Other channels are not valid.
 */
void TSC_SW_SwtichChn(TSC_Module* TSC_Def, uint32_t Channel, TIM_Module* TIMx, FunctionalState Cmd)
{
    uint32_t i;

    if(TSC_Def != TSC)
        return;

    /* Disable the TSC HW MODE */
    while (__TSC_GET_HW_MODE())
    {
        __TSC_HW_DISABLE();
    }

    // waiting tsc hw for idle status.
    if ((TIMx != TIM2) && (TIMx != TIM4))
    {
        return;
    }

    if (Cmd == DISABLE) // Close output by software mode
    {
        __TSC_OUT_CONFIG(TSC_OUT_PIN);
        __TSC_SW_DISABLE();
    }
    else
    {
        for (i = 0; i < MAX_TSC_HW_CHN; i++)
        {
            if (Channel & 0x00000001)
            {
                __TSC_SW_CHN_NUM_CONFIG(i);
                break;
            }

            Channel >>= 1;
        }

        // Select to output to specified TIMER.
        if (TIMx == TIM4)
        {
            __TSC_OUT_CONFIG(TSC_OUT_TIM4_ETR);
        }
        else
        {
            __TSC_OUT_CONFIG(TSC_OUT_TIM2_ETR);
        }

         __TSC_SW_ENABLE();
    }

    // delay time for tsc channel stabilize output
    for (i = 0; i < 2000; i++)
    {
    }
}

/**
 * @brief  Configure analog signal parameters.
 * @param  TSC_Def Pointer of TSC register.
 * @param  AnaoCfg Pointer of analog parameter structure.
 */
void TSC_SetAnaoCfg(TSC_Module* TSC_Def, TSC_AnaoCfg* AnaoCfg)
{
    if(TSC_Def != TSC)
        return;

    if(AnaoCfg == 0)
        return;

    __TSC_PAD_OPT_CONFIG(AnaoCfg->TSC_AnaoptrResisOption);
    __TSC_PAD_SPEED_CONFIG(AnaoCfg->TSC_AnaoptrSpeedOption);
}

/**
 * @brief  Configure channel parameters by channel or operation.Support configure several channels at the same time.
 * @param  TSC_Def Pointer of TSC register.
 * @param  ChnCfg Channel parameters.
 * @param  Channels Set the channels.
 */
void TSC_SetChannelCfg(TSC_Module* TSC_Def, TSC_ChnCfg* ChnCfg, uint32_t Channels)
{
    if(TSC_Def != TSC)
        return;

    // Set resistance
    TSC_ConfigInternalResistor(Channels, ChnCfg->TSC_Resistor);

    // Set the threshold of base and delta.
    TSC_ConfigThreshold(Channels, ChnCfg->TSC_Base, ChnCfg->TSC_Delta);
}



