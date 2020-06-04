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
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x.h"
#include "n32g45x_tsc.h"

/**
 * @brief  Enables or disables the TSC hardware detect init.
 * @param  TSC_Def Pointer of TSC register.
 * @param  CtrlCfg configurations.
 */
void TSC_Init(TSC_Module* TSC_Def, TSC_InitType* CtrlCfg)
{
    while (TSC_Def->CTRL & TSC_HW_DET_ST)
    {
        TSC_Def->CTRL &= (~TSC_HW_DET_ENABLE);
    };

    // waiting tsc hw for idle status.
    if (CtrlCfg->TSC_DetIntEnable)
    {
        TSC_Def->CTRL |= TSC_HW_DET_INTEN;
    }
    else
    {
        TSC_Def->CTRL &= (~TSC_HW_DET_INTEN);
    }

    if (CtrlCfg->TSC_GreatEnable)
    {
        TSC_Def->CTRL |= TSC_HW_GREAT_DET_SEL;
    }
    else
    {
        TSC_Def->CTRL &= (~TSC_HW_GREAT_DET_SEL);
    }

    if (CtrlCfg->TSC_LessEnable)
    {
        TSC_Def->CTRL |= TSC_HW_LESS_DET_SEL;
    }
    else
    {
        TSC_Def->CTRL &= (~TSC_HW_LESS_DET_SEL);
    }

    TSC_Def->CTRL &= (~(TSC_HW_DET_BITS_MASK << TSC_HW_DET_OFFSET));
    TSC_Def->CTRL |= CtrlCfg->TSC_FilterCount;

    TSC_Def->CTRL &= (~(TSC_DET_PERIOD_MASK << TSC_DET_PERIOD_OFFSET));
    TSC_Def->CTRL |= CtrlCfg->TSC_DetPeriod;
}

/**
 * @brief  Configure analog signal parameters.
 * @param  TSC_Def Pointer of TSC register.
 * @param  AnaoCfg Pointer of analog parameter structure.
 */
void TSC_SetAnaoCfg(TSC_Module* TSC_Def, TSC_AnaoCfg* AnaoCfg)
{
    if (AnaoCfg && TSC_Def)
    {
        TSC_Def->ANA_SEL &= (~(TSC_CMP_MASK << TSC_CMP_OFFSET));
        TSC_Def->ANA_SEL |= AnaoCfg->TSC_AnaoptrSpeedOption; // speed option

        TSC_Def->ANA_SEL &= (~(TSC_RESIST_SEL_MASK << TSC_RESIST_SEL_OFFSET));
        TSC_Def->ANA_SEL |= AnaoCfg->TSC_AnaoptrResisOption; // speed option
    }
}

/**
 * @brief  Configure channel parameters by channel or operation.Support configure several channels at the same time.
 * @param  TSC_Def Pointer of TSC register.
 * @param  ChnCfg Channel parameters.
 * @param  Channels Set the channels.
 */
void TSC_SetChannelCfg(TSC_Module* TSC_Def, TSC_ChnCfg* ChnCfg, uint32_t Channels)
{
    uint32_t i, j;
    uint32_t chn;

    while (TSC_Def->CTRL & TSC_HW_DET_ST)
    {
        TSC_Def->CTRL &= (~TSC_HW_DET_ENABLE);
    };

    // waiting tsc hw for idle status.
    // Set resistance
    for (i = TSC_CHN0, j = 0, chn = Channels; i <= TSC_CHN23; i <<= 1, j++)
    {
        if (chn & 0x00000001)
        {
            if ((i >= TSC_CHN0) && (i <= TSC_CHN7))
            {
                TSC_Def->RESR0 = (TSC_Def->RESR0 & (~(TSC_RES_BIT_VALID_BITS << (j * TSC_RES_BIT_OFFSET_WIDTH))))
                    | (ChnCfg->TSC_ResisValue << (j * TSC_RES_BIT_OFFSET_WIDTH));
            }
            else if ((i >= TSC_CHN8) && (i <= TSC_CHN15))
            {
                TSC_Def->RESR1 = (TSC_Def->RESR1 & (~(TSC_RES_BIT_VALID_BITS << (j * TSC_RES_BIT_OFFSET_WIDTH - 32))))
                    | (ChnCfg->TSC_ResisValue << (j * TSC_RES_BIT_OFFSET_WIDTH - 32));
            }
            else if ((i >= TSC_CHN16) && (i <= TSC_CHN23))
            {
                TSC_Def->RESR2 = (TSC_Def->RESR2 & (~(TSC_RES_BIT_VALID_BITS << (j * TSC_RES_BIT_OFFSET_WIDTH - 64))))
                    | (ChnCfg->TSC_ResisValue << (j * TSC_RES_BIT_OFFSET_WIDTH - 64));
            }
        }

        chn >>= 1;
    }

    // Set the threshold of base and delta.
    for (i = TSC_CHN0, j = 0, chn = Channels; i <= TSC_CHN23; i <<= 1, j++)
    {
        if (chn & 0x00000001)
        {
            *(__IO uint32_t*)((uint32_t)&TSC_Def->THRHD0 + TSC_CHN_ADDR_WIDTH * j) =
                (ChnCfg->TSC_Base << TSC_HW_BASE_BITS_OFFSET) | (ChnCfg->TSC_Delta << TSC_HW_DELTA_BITS_OFFSET);
        }

        chn >>= 1;
    }
}

/**
 * @brief  Get parameters of one channel.
 * @param  TSC_Def Pointer of TSC register.
 * @param  ChnCfg Channel parameters.
 * @param  Channel Set the channel.
 */
void TSC_GetChannelCfg(TSC_Module* TSC_Def, TSC_ChnCfg* ChnCfg, uint32_t Channel)
{
    uint32_t i, j;
    uint32_t chn, value;

    // waiting tsc hw for idle status.
    // Set resistance
    for (i = TSC_CHN0, j = 0, chn = Channel; i <= TSC_CHN23; i <<= 1, j++)
    {
        if (chn & 0x00000001)
        {
            if ((i >= TSC_CHN0) && (i <= TSC_CHN7))
            {
                ChnCfg->TSC_ResisValue =
                    (TSC_Def->RESR0 >> (j * TSC_RES_BIT_OFFSET_WIDTH)) & TSC_RES_BIT_VALID_BITS;
            }
            else if ((i >= TSC_CHN8) && (i <= TSC_CHN15))
            {
                ChnCfg->TSC_ResisValue =
                    (TSC_Def->RESR1 >> (j * TSC_RES_BIT_OFFSET_WIDTH - 32)) & TSC_RES_BIT_VALID_BITS;
            }
            else if ((i >= TSC_CHN16) && (i <= TSC_CHN23))
            {
                ChnCfg->TSC_ResisValue =
                    (TSC_Def->RESR2 >> (j * TSC_RES_BIT_OFFSET_WIDTH - 64)) & TSC_RES_BIT_VALID_BITS;
            }
            break; // You can only get the resistance of one channel at a time.
        }
        chn >>= 1;
    }

    // Set the threshold of base and delta.
    for (i = TSC_CHN0, j = 0, chn = Channel; i <= TSC_CHN23; i <<= 1, j++)
    {
        if (chn & 0x00000001)
        {
            value             = *(__IO uint32_t*)((uint32_t)&TSC_Def->THRHD0 + TSC_CHN_ADDR_WIDTH * j);
            ChnCfg->TSC_Base  = (value >> TSC_HW_BASE_BITS_OFFSET) & TSC_HW_BASE_BITS_WIDTH;
            ChnCfg->TSC_Delta = (value >> TSC_HW_DELTA_BITS_OFFSET) & TSC_HW_DELTA_BITS_WIDTH;
            break; // You can only get the parameter of one channel at a time.
        }
        chn >>= 1;
    }
}

/**
 * @brief  Get TSC status value.
 * @param  TSC_Def Pointer of TSC register.
 * @param  type TSC status type.
 */
uint32_t TSC_GetStatus(TSC_Module* TSC_Def, TSC_Status type)
{
    uint32_t value = 0;

    if (TSC_Def)
    {
        switch (type)
        {
        case TSC_STS_CNTVALUE:
            value = (TSC_Def->STS >> TSC_HW_CNT_VAL_OFFSET) & TSC_HW_CNT_VAL_BITS_MASK;
            break;

        case TSC_STS_LESS_DET:
            value = (TSC_Def->STS >> TSC_HW_LESS_DET_FLAG_OFFSET) & TSC_HW_LESS_DET_FLAG_MASK;
            break;

        case TSC_STS_GREAT_DET:
            value = (TSC_Def->STS >> TSC_HW_GREAT_DET_FLAG_OFFSET) & TSC_HW_GREAT_DET_FLAG_MASK;
            break;

        case TSC_STS_CHN_NUM:
            value = (TSC_Def->STS >> TSC_HW_CHN_NUM_OFFSET) & TSC_HW_CHN_NUM_FLAG_MASK;
            break;

        case TSC_DET_DET_ST:
            value = TSC_Def->CTRL & TSC_HW_DET_ST;
            break;

        default:
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
    if (Cmd != DISABLE)
    {
        // enable tsc channel
        TSC_Def->CHNEN = Channels & TSC_HW_CHN_MASK;

        /* Enable the TSC */
        TSC_Def->CTRL |= TSC_HW_DET_ENABLE;
    }
    else
    {
        /* Disable the TSC */
        while (TSC_Def->CTRL & TSC_HW_DET_ST)
        {
            // waiting tsc hw for idle status.
            TSC_Def->CTRL &= (~TSC_HW_DET_ENABLE);
        };
        TSC_Def->CHNEN &= (~TSC_HW_CHN_MASK);
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
    uint32_t i, j;

    /* Disable the TSC HW MODE */
    while (TSC_Def->CTRL & TSC_HW_DET_ST)
    {
        TSC_Def->CTRL &= (~TSC_HW_DET_ENABLE);
    };

    // waiting tsc hw for idle status.
    if ((TIMx != TIM2) && (TIMx != TIM4))
    {
        return;
    }

    for (i = TSC_CHN0, j = 0; i <= TSC_CHN23; i <<= 1, j++)
    {
        if (Channel & 0x00000001)
        {
            TSC_Def->ANA_CTRL = (TSC_Def->ANA_CTRL & (~TSC_SW_CHN_VAILD_WIDTH)) | j;
            break;
        }

        Channel >>= 1;
    }

    /* Enable the TSC SW MODE */
    if (Cmd == ENABLE)
    {
        // Select to output to specified TIMER.
        if (TIMx == TIM4)
        {
            TSC_Def->CTRL = (TSC_Def->CTRL & (~(TSC_SW_TIM_WIDTH << TSC_SW_TIM_OFFSET))) | TSC_SW_TM4_ETR_SEL;
        }
        else
        {
            TSC_Def->CTRL = (TSC_Def->CTRL & (~(TSC_SW_TIM_WIDTH << TSC_SW_TIM_OFFSET))) | TSC_SW_TM2_ETR_SEL;
        }

        TSC_Def->ANA_CTRL |= TSC_SW_CHN_ENABLE;
    }
    else
    {
        // Close output by software mode.Then  all the channels output to TIM2 and TIM4 are closed.
        TSC_Def->CTRL &= (~(TSC_SW_TIM_WIDTH << TSC_SW_TIM_OFFSET));
        TSC_Def->ANA_CTRL &= (~TSC_SW_CHN_ENABLE);
    }

    // delay time for tsc channel stabilize output
    for (i = 0; i < 2000; i++)
    {
    }
}
/******************************************************************/
/**
 * @brief    Configure the software detection mode quickly.Samples start from channel 10,
             And toggle channels periodically later.
 */
void TSC_SW_Init_Skip(void)
{
    while ((TSC->CTRL & 0x80) == TSC_CTRL_HW_DET_ST)
    {
        TSC->CTRL &= ~TSC_CTRL_HW_DET_MODE;
    }
    TSC->CTRL |= 0x00002000;    // bit13 set 1,channels output to TIMER2.
    TSC->CHNEN |= 0xFFCC00;   // select hardware channels,include TSC10-11 and TSC14-23.
    TSC->ANA_CTRL |= 0x00000020; // enable software detection.
    TSC->ANA_CTRL |= 10; // select software channel 10,Samples start from channel 10,and toggle channels periodically later.
    TSC->RESR1 = 0x77007700; // Select the internal resistance of the corresponding channel as 126K.
    TSC->RESR2 = 0x77777777; // Select the internal resistance of the corresponding channel as 126K.
}
/**
* @brief  Toggle channels by software mode quickly.Note it has been configured hardware detection disable,channels
output to TIMER2 or TIMER4 in advance and never changed. In addition,toggle channels must delay at least 30us.
* @param  Channel Select the channel.
*/
void TSC_SW_SwtichChn_Skip(uint32_t Channel)
{
    // Toggle to new channel quickly.
    TSC->ANA_CTRL = 0x20 | Channel;
}
