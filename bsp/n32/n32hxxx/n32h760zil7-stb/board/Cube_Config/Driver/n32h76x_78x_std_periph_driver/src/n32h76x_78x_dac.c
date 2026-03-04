/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_dac.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "string.h"
#include "n32h76x_78x_dac.h"
#include "n32h76x_78x_rcc.h"


/** DAC_Private_Types Definitions **/


/* DCH registers offsets */
#define DR8DACx_OFFSET ((uint32_t)0x00000010U)
#define DR8DACy_OFFSET ((uint32_t)0x0000001CU)
#define DR8D_OFFSET    ((uint32_t)0x00000028U)

/* DATO register offset */
#define DATOx_OFFSET   ((uint32_t)0x00000008U)
#define DATOy_OFFSET   ((uint32_t)0x0000000CU)


/* bit data handler */
#define BIT_JUDGE_AND_HANDLER(IS_ENABLE, BIT_MASK)    (((IS_ENABLE) != DISABLE ) ? (BIT_MASK) : (0x00000000U))


/** DAC Driving Functions Declaration **/

/**
*\*\name    DAC_DeInit.
*\*\fun     Reset the DAC registers.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\return  none
**/
void DAC_DeInit(DACX DACx)
{
    if(IS_DAC12(DACx))
    {
        RCC_EnableAPB1PeriphReset2(RCC_APB1_PERIPHRST_DAC12);
    }
    else if(IS_DAC34(DACx))
    {
        RCC_EnableAHB2PeriphReset1(RCC_AHB2_PERIPHRST_DAC34);
    }
    else if(IS_DAC56(DACx))
    {
        RCC_EnableAHB2PeriphReset1(RCC_AHB2_PERIPHRST_DAC56);
    }
    else
    {
        /*no process */
    }
}

/**
*\*\name    DAC_StructInit.
*\*\fun     Fills all DAC_StructInit member with default value.
*\*\param   DAC_StructInit :
*\*\          - DAC_Trigger
*\*\          - DAC_Trigger2
*\*\          - DAC_WaveGeneration
*\*\          - DAC_LFSRUnmask_TriangleAmplitude
*\*\          - DAC_OutputBuffer
*\*\          - DAC_TriggerEnable
*\*\          - DAC_DMADoubleDataMode
*\*\          - DAC_SignedFormat
*\*\          - DAC_ConnectOnChipPeripheral
*\*\          - DAC_ConnectExternalPin
*\*\return  none
**/
void DAC_StructInit(DAC_InitType* DAC_InitStruct)
{
    /* Initialize the DAC_Trigger member */
    DAC_InitStruct->DAC_Trigger = DAC_Trigger_Software;
    /* Initialize the DAC_Trigger2 member */
    DAC_InitStruct->DAC_Trigger2 = DAC_Trigger2_Software;
    /* Initialize the DAC_WaveGeneration member */
    DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
    /* Initialize the DAC_LFSRUnmask_TriangleAmplitude member */
    DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    /* Initialize the DAC_OutputBuffer member */
    DAC_InitStruct->DAC_OutputBuffer = DISABLE;
    /* Initialize the DAC_TriggerEnable member */
    DAC_InitStruct->DAC_TriggerEnable = DISABLE;
    /* Initialize the DAC_DMADoubleDataMode member */
    DAC_InitStruct->DAC_DMADoubleDataMode = DISABLE;
    /* Initialize the DAC_SignedFormat member */
    DAC_InitStruct->DAC_SignedFormat = DISABLE;
    /* Initialize the DAC_ConnectOnChipPeripheral member */
    DAC_InitStruct->DAC_ConnectOnChipPeripheral = DISABLE;
    /* Initialize the DAC_ConnectExternalPin member */
    DAC_InitStruct->DAC_ConnectExternalPin = DISABLE;
}

/**
*\*\name    DAC_BaseAddrGet.
*\*\fun     Get the specified DAC base address.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\return   DAC_Module* :
*\*\          - DAC12
*\*\          - DAC34
*\*\          - DAC56
**/
static DAC_Module* DAC_BaseAddrGet(DACX DACx)
{
    DAC_Module* DAC_TEMP = NULL;

    if(IS_DAC12(DACx))
    {
        DAC_TEMP = (DAC_Module*)DAC12;
    }
    else if(IS_DAC34(DACx))
    {
        DAC_TEMP = (DAC_Module*)DAC34;
    }
    else if(IS_DAC56(DACx))
    {
        DAC_TEMP = (DAC_Module*)DAC56;
    }
    else
    {
        /* no process */
    }

    return DAC_TEMP;
}
/**
*\*\name    DAC_Init.
*\*\fun     Enables or disables the specified DAC.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   DAC_InitStruct :
*\*\          - DAC_Trigger
*\*\             - DAC_Trigger_Software
*\*\             - DAC_Trigger_ATIM1_TRGO
*\*\             - DAC_Trigger_ATIM2_TRGO
*\*\             - DAC_Trigger_ATIM3_TRGO
*\*\             - DAC_Trigger_ATIM4_TRGO
*\*\             - DAC_Trigger_GTIMA1_TRGO
*\*\             - DAC_Trigger_GTIMA2_TRGO
*\*\             - DAC_Trigger_GTIMA3_TRGO
*\*\             - DAC_Trigger_GTIMA4_TRGO
*\*\             - DAC_Trigger_GTIMA5_TRGO
*\*\             - DAC_Trigger_GTIMA6_TRGO
*\*\             - DAC_Trigger_GTIMA7_TRGO
*\*\             - DAC_Trigger_GTIMB1_TRGO
*\*\             - DAC_Trigger_GTIMB2_TRGO
*\*\             - DAC_Trigger_GTIMB3_TRGO
*\*\             - DAC_Trigger_EXTI5
*\*\             - DAC_Trigger_EXTI7
*\*\             - DAC_Trigger_EXTI9
*\*\             - DAC_Trigger_SHRTIM1_RST_TRG1
*\*\             - DAC_Trigger_SHRTIM1_RST_TRG2
*\*\             - DAC_Trigger_SHRTIM1_RST_TRG3
*\*\             - DAC_Trigger_SHRTIM1_RST_TRG4
*\*\             - DAC_Trigger_SHRTIM1_RST_TRG5
*\*\             - DAC_Trigger_SHRTIM1_RST_TRG6
*\*\             - DAC_Trigger_SHRTIM1_RST_TRGO123
*\*\             - DAC_Trigger_SHRTIM2_RST_TRG1
*\*\             - DAC_Trigger_SHRTIM2_RST_TRG2
*\*\             - DAC_Trigger_SHRTIM2_RST_TRG3
*\*\             - DAC_Trigger_SHRTIM2_RST_TRG4
*\*\             - DAC_Trigger_SHRTIM2_RST_TRG5
*\*\             - DAC_Trigger_SHRTIM2_RST_TRG6
*\*\             - DAC_Trigger_SHRTIM2_RST_TRGO123
*\*\          - DAC_Trigger2
*\*\             - DAC_Trigger2_Software
*\*\             - DAC_Trigger2_ATIM1_TRGO
*\*\             - DAC_Trigger2_ATIM2_TRGO
*\*\             - DAC_Trigger2_ATIM3_TRGO
*\*\             - DAC_Trigger2_ATIM4_TRGO
*\*\             - DAC_Trigger2_GTIMA1_TRGO
*\*\             - DAC_Trigger2_GTIMA2_TRGO
*\*\             - DAC_Trigger2_GTIMA3_TRGO
*\*\             - DAC_Trigger2_GTIMA4_TRGO
*\*\             - DAC_Trigger2_GTIMA5_TRGO
*\*\             - DAC_Trigger2_GTIMA6_TRGO
*\*\             - DAC_Trigger2_GTIMA7_TRGO
*\*\             - DAC_Trigger2_GTIMB1_TRGO
*\*\             - DAC_Trigger2_GTIMB2_TRGO
*\*\             - DAC_Trigger2_GTIMB3_TRGO
*\*\             - DAC_Trigger2_EXTI6
*\*\             - DAC_Trigger2_EXTI8
*\*\             - DAC_Trigger2_EXTI10
*\*\             - DAC_Trigger2_SHRTIM1_STEP_TRG1
*\*\             - DAC_Trigger2_SHRTIM1_STEP_TRG2
*\*\             - DAC_Trigger2_SHRTIM1_STEP_TRG3
*\*\             - DAC_Trigger2_SHRTIM1_STEP_TRG4
*\*\             - DAC_Trigger2_SHRTIM1_STEP_TRG5
*\*\             - DAC_Trigger2_SHRTIM1_STEP_TRG6
*\*\             - DAC_Trigger2_SHRTIM2_STEP_TRG1
*\*\             - DAC_Trigger2_SHRTIM2_STEP_TRG2
*\*\             - DAC_Trigger2_SHRTIM2_STEP_TRG3
*\*\             - DAC_Trigger2_SHRTIM2_STEP_TRG4
*\*\             - DAC_Trigger2_SHRTIM2_STEP_TRG5
*\*\             - DAC_Trigger2_SHRTIM2_STEP_TRG6
*\*\          - DAC_LFSRUnmask_TriangleAmplitude
*\*\             - DAC_LFSRUnmask_Bit0
*\*\             - DAC_LFSRUnmask_Bits1_0
*\*\             - DAC_LFSRUnmask_Bits2_0
*\*\             - DAC_LFSRUnmask_Bits3_0
*\*\             - DAC_LFSRUnmask_Bits4_0
*\*\             - DAC_LFSRUnmask_Bits5_0
*\*\             - DAC_LFSRUnmask_Bits6_0
*\*\             - DAC_LFSRUnmask_Bits7_0
*\*\             - DAC_LFSRUnmask_Bits8_0
*\*\             - DAC_LFSRUnmask_Bits9_0
*\*\             - DAC_LFSRUnmask_Bits10_0
*\*\             - DAC_LFSRUnmask_Bits11_0
*\*\             - DAC_TriangleAmplitude_1
*\*\             - DAC_TriangleAmplitude_3
*\*\             - DAC_TriangleAmplitude_7
*\*\             - DAC_TriangleAmplitude_15
*\*\             - DAC_TriangleAmplitude_31
*\*\             - DAC_TriangleAmplitude_63
*\*\             - DAC_TriangleAmplitude_127
*\*\             - DAC_TriangleAmplitude_255
*\*\             - DAC_TriangleAmplitude_511
*\*\             - DAC_TriangleAmplitude_1023
*\*\             - DAC_TriangleAmplitude_2047
*\*\             - DAC_TriangleAmplitude_4095
*\*\          - DAC_WaveGeneration
*\*\             - DAC_WaveGeneration_None
*\*\             - DAC_WaveGeneration_Noise
*\*\             - DAC_WaveGeneration_Triangle
*\*\             - DAC_WaveGeneration_SAWTOOTH_INC
*\*\             - DAC_WaveGeneration_SAWTOOTH_DEC
*\*\          - DAC_OutputBuffer
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - DAC_TriggerEnable
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - DAC_DMADoubleDataMode
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - DAC_SignedFormat
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - DAC_ConnectOnChipPeripheral
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - DAC_ConnectExternalPin
*\*\             - ENABLE
*\*\             - DISABLE
*\*\return  none
*\*\note   when DACx is DAC3/DAC4/DAC5/DAC6, DAC_OutputBuffer,the params of DAC_ConnectOnChipPeripheral,DAC_ConnectExternalPin will be ignored.
**/
void DAC_Init(DACX DACx, DAC_InitType* DAC_InitStruct)
{
    __IO uint32_t tmpreg1;
    uint8_t  shift_bit;
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);
    /* Operate DAC_SELCTRL Regersiter */
    tmpreg1 = DAC_Base->SELCTRL;

    if(IS_DAC135(DACx))
    {
        shift_bit = 0U;
        tmpreg1 &= ~(DACx_SELCTRL_SINCSEL_MASK | DACx_SELCTRL_MAxSEL_MASK | DACx_SELCTRL_TxSEL_MASK);
    }
    else
    {
        shift_bit = 16U;
        tmpreg1 &= ~(DACy_SELCTRL_SINCSEL_MASK | DACy_SELCTRL_MAySEL_MASK | DACy_SELCTRL_TySEL_MASK);
    }

    /*mask/amplitude,DAC_Trigger,DAC_Trigger2 */
    tmpreg1 |= ((DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude << shift_bit) | (DAC_InitStruct->DAC_Trigger << shift_bit) | (DAC_InitStruct->DAC_Trigger2 << shift_bit) );
    DAC_Base->SELCTRL = tmpreg1;

    /* Operate DAC_GCTRL Regersiter */
    tmpreg1 = DAC_Base->GCTRL;
    tmpreg1 &= (~DAC_GCTRL_FREQ_MODE_MASK);
    tmpreg1 |= DAC_HIGH_FREQ_MODE_BELOW_80M;
    DAC_Base->GCTRL = tmpreg1;

    /* Operate DAC_CTRL Regersiter */
    tmpreg1 = DAC_Base->CTRL;

    if(IS_DAC12(DACx))
    {
        if(IS_DAC13(DACx))
        {
            shift_bit = 0;
            tmpreg1 &= ~(DACx_CTRL_BUFF_EN_MASK | DACx_CTRL_TRIGGER_EN_MASK | DACx_CTRL_DMADOUBLEMODE_EN_MASK | DACx_CTRL_SINGFORMAT_EN_MASK | \
                         DACx_CTRL_WAVE_TYPE_MASK | DACx_CTRL_OUTPUT_TO_ONCHAIP_EN_MASK | DACx_CTRL_OUTPUT_TO_EXTPIN_EN_MASK );
        }
        else
        {
            shift_bit = 16;
            tmpreg1 &= ~(DACy_CTRL_BUFF_EN_MASK | DACy_CTRL_TRIGGER_EN_MASK | DACy_CTRL_DMADOUBLEMODE_EN_MASK | DACy_CTRL_SINGFORMAT_EN_MASK | \
                         DACy_CTRL_WAVE_TYPE_MASK | DACy_CTRL_OUTPUT_TO_ONCHAIP_EN_MASK | DACy_CTRL_OUTPUT_TO_EXTPIN_EN_MASK );
        }

        tmpreg1 |= ((BIT_JUDGE_AND_HANDLER(DAC_InitStruct->DAC_OutputBuffer, DACx_CTRL_BUFF_EN_MASK) << shift_bit) | \
                    (BIT_JUDGE_AND_HANDLER(DAC_InitStruct->DAC_TriggerEnable, DACx_CTRL_TRIGGER_EN_MASK) << shift_bit)  | \
                    (BIT_JUDGE_AND_HANDLER(DAC_InitStruct->DAC_DMADoubleDataMode, DACx_CTRL_DMADOUBLEMODE_EN_MASK) << shift_bit) | \
                    (BIT_JUDGE_AND_HANDLER(DAC_InitStruct->DAC_SignedFormat, DACx_CTRL_SINGFORMAT_EN_MASK) << shift_bit) | \
                    (DAC_InitStruct->DAC_WaveGeneration << (shift_bit)) | \
                    (BIT_JUDGE_AND_HANDLER(DAC_InitStruct->DAC_ConnectOnChipPeripheral, DACx_CTRL_OUTPUT_TO_ONCHAIP_EN_MASK) << shift_bit) | \
                    (BIT_JUDGE_AND_HANDLER(DAC_InitStruct->DAC_ConnectExternalPin, DACx_CTRL_OUTPUT_TO_EXTPIN_EN_MASK) << shift_bit) );
    }
    else
    {
        if(IS_DAC135(DACx))
        {
            shift_bit = 0;
            tmpreg1 &= ~(DACx_CTRL_TRIGGER_EN_MASK | DACx_CTRL_DMADOUBLEMODE_EN_MASK | DACx_CTRL_SINGFORMAT_EN_MASK | \
                         DACx_CTRL_WAVE_TYPE_MASK );
        }
        else
        {
            shift_bit = 16;
            tmpreg1 &= ~( DACy_CTRL_TRIGGER_EN_MASK | DACy_CTRL_DMADOUBLEMODE_EN_MASK | DACy_CTRL_SINGFORMAT_EN_MASK | DACy_CTRL_WAVE_TYPE_MASK );
        }

        tmpreg1 |= ((BIT_JUDGE_AND_HANDLER(DAC_InitStruct->DAC_TriggerEnable, DACx_CTRL_TRIGGER_EN_MASK) << shift_bit)  | \
                    (BIT_JUDGE_AND_HANDLER(DAC_InitStruct->DAC_DMADoubleDataMode, DACx_CTRL_DMADOUBLEMODE_EN_MASK) << shift_bit) | \
                    (BIT_JUDGE_AND_HANDLER(DAC_InitStruct->DAC_SignedFormat, DACx_CTRL_SINGFORMAT_EN_MASK) << shift_bit) | \
                    (DAC_InitStruct->DAC_WaveGeneration << (shift_bit))  );
    }

    DAC_Base->CTRL = tmpreg1;
}


/**
*\*\name    DAC_Enable.
*\*\fun     Enables or disables the specified DAC.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DAC_Enable(DACX DACx, FunctionalState Cmd)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACx_CTRL_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACx_CTRL_EN_MASK);
        }
    }
    else
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACy_CTRL_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACy_CTRL_EN_MASK);
        }
    }
}

/**
*\*\name    DAC_DmaEnable.
*\*\fun     Enables or disables the specified DAC DMA request.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DAC_DmaEnable(DACX DACx, FunctionalState Cmd)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACx_CTRL_DMA_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACx_CTRL_DMA_EN_MASK);
        }
    }
    else
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACy_CTRL_DMA_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACy_CTRL_DMA_EN_MASK);
        }
    }
}

/**
*\*\name    DAC_SoftTrgEnable.
*\*\fun     Enables or disables software trigger of the selected DAC.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DAC_SoftTrgEnable(DACX DACx, FunctionalState Cmd)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        if (Cmd != DISABLE)
        {
            DAC_Base->SOTTR |= (DACx_CTRL_TRIGxEN_MASK);
        }
        else
        {
            DAC_Base->SOTTR &= ~(DACx_CTRL_TRIGxEN_MASK);
        }
    }
    else
    {
        if (Cmd != DISABLE)
        {
            DAC_Base->SOTTR |= (DACy_CTRL_TRIGyEN_MASK);
        }
        else
        {
            DAC_Base->SOTTR &= ~(DACy_CTRL_TRIGyEN_MASK);
        }
    }
}
/**
*\*\name    DAC_SoftTrgSawStepEnable.
*\*\fun     Enables or disables software trigger step signal of the selected DAC sawtooth wave .
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DAC_SoftTrgSawStepEnable(DACX DACx, FunctionalState Cmd)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        if (Cmd != DISABLE)
        {
            DAC_Base->SOTTR |= (DACx_CTRL_TRIGxSTEPEN_MASK);
        }
        else
        {
            DAC_Base->SOTTR &= ~(DACx_CTRL_TRIGxSTEPEN_MASK);
        }
    }
    else
    {
        if (Cmd != DISABLE)
        {
            DAC_Base->SOTTR |= (DACy_CTRL_TRIGySTEPEN_MASK);
        }
        else
        {
            DAC_Base->SOTTR &= ~(DACy_CTRL_TRIGySTEPEN_MASK);
        }
    }
}

/**
*\*\name    DAC_DualSoftwareTrgEnable.
*\*\fun     Enables or disables simultaneously the two DAC software triggers.
*\*\param   DACx :
*\*\          - DAC12
*\*\          - DAC34
*\*\          - DAC56
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DAC_DualSoftwareTrgEnable(DAC_Module *Dual_DACx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable software trigger for both DAC channels */
        Dual_DACx->SOTTR |= DACx_CTRL_TRIGALLEN_MASK;
    }
    else
    {
        /* Disable software trigger for both DAC channels */
        Dual_DACx->SOTTR &= (~DACx_CTRL_TRIGALLEN_MASK);
    }
}
/**
*\*\name    DAC_DualSoftwareTrgEnable.
*\*\fun     Enables or disables software trigger step signal of simultaneously two DACs sawtooth wave .
*\*\param   DACx :
*\*\          - DAC12
*\*\          - DAC34
*\*\          - DAC56
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DAC_DualSoftwareTrgSawStepEnable(DAC_Module *Dual_DACx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable software trigger sawtooth step sign for both DAC channels */
        Dual_DACx->SOTTR |= DACy_CTRL_TRIGALLSTEPEN_MASK;
    }
    else
    {
        /* Disable software trigger sawtooth step sign for both DAC channels */
        Dual_DACx->SOTTR &= (~DACy_CTRL_TRIGALLSTEPEN_MASK);
    }
}

/**
*\*\name    DAC_WaveGenerationConfig.
*\*\fun     Configure the selected DAC wave generation. .
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   DAC_Wave :
*\*\          - DAC_WaveGeneration_None
*\*\          - DAC_WaveGeneration_Noise
*\*\          - DAC_WaveGeneration_Triangle
*\*\          - DAC_WaveGeneration_SAWTOOTH_INC
*\*\          - DAC_WaveGeneration_SAWTOOTH_DEC
*\*\return  none
**/
void DAC_WaveGenerationConfig(DACX DACx, uint32_t DAC_Wave)
{
    __IO uint32_t tempreg;
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);
    tempreg = DAC_Base->CTRL;

    if(IS_DAC135(DACx))
    {
        tempreg &= ~(DACx_CTRL_WAVE_TYPE_MASK);
        tempreg |= (DAC_Wave);
    }
    else
    {
        tempreg &= ~(DACy_CTRL_WAVE_TYPE_MASK);
        tempreg |= (DAC_Wave << 16);
    }

    DAC_Base->CTRL = tempreg;
}

/**
*\*\name    DAC_SetData.
*\*\fun     Set the data holding register value for the specified DAC.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   DAC_Align :
*\*\          - DAC_ALIGN_R_8BIT
*\*\          - DAC_ALIGN_L_12BIT
*\*\          - DAC_ALIGN_R_12BIT
*\*\param   Data : Data to be loaded in the selected data holding register.
*\*\return  none
**/
void DAC_SetData(DACX DACx, uint32_t DAC_Align, uint16_t Data)
{
    __IO uint32_t tempreg;
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);
    tempreg = (uint32_t)DAC_Base;

    if(IS_DAC135(DACx))
    {
        tempreg += DR8DACx_OFFSET;
    }
    else
    {
        tempreg += DR8DACy_OFFSET;
    }

    tempreg += DAC_Align;

    /* Set the DACx selected data holding register */
    *(__IO uint32_t*)tempreg = Data;
}

/**
*\*\name    DAC_SetDualChData.
*\*\fun     Set the data holding register value for the specified dual-DAC.
*\*\param   DACx :
*\*\          - DAC12
*\*\          - DAC34
*\*\          - DAC56
*\*\param   DAC_Align :
*\*\          - DAC_ALIGN_R_8BIT
*\*\          - DAC_ALIGN_L_12BIT
*\*\          - DAC_ALIGN_R_12BIT
*\*\param   Data2 : Data to be loaded in the selected DACy data holding register.
*\*\param   Data1 : Data to be loaded in the selected DACx data holding register.
*\*\return  none
**/
void DAC_SetDualChData(DAC_Module *Dual_DACx, uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
{
    __IO uint32_t tempreg;
    uint32_t data;

    /* Calculate and set dual DAC data holding register value */
    if (DAC_Align == DAC_ALIGN_R_8BIT)
    {
        data = ((uint32_t)Data2 << 8) | Data1;
    }
    else
    {
        data = ((uint32_t)Data2 << 16) | Data1;
    }

    tempreg = (uint32_t)Dual_DACx;
    tempreg += DR8D_OFFSET + DAC_Align;

    /* Set the dual DAC selected data holding register */
    *(__IO uint32_t*)tempreg = data;
}

/**
*\*\name    DAC_GetOutputDataVal.
*\*\fun     Get the last data output value of the selected DAC .
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\return  The selected DAC data output value.
**/
uint16_t DAC_GetOutputDataVal(DACX DACx)
{
    uint32_t tempreg;
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);
    tempreg = (uint32_t)DAC_Base;

    if(IS_DAC135(DACx))
    {
        tempreg += DATOx_OFFSET;
    }
    else
    {
        tempreg += DATOy_OFFSET;
    }

    /* Returns the DACx data output register value */
    return (uint16_t)(*(__IO uint32_t*)tempreg);
}
/**
*\*\name    DAC_SetSawtoothResetValue.
*\*\fun     Set the swatooth waveform generation reset data.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   ResetValue:
*\*\          - the value is range from 0- 0xfff;
*\*\return  none
**/
void DAC_SetSawtoothResetValue(DACX DACx, uint16_t ResetValue)
{
    __IO uint32_t tempreg;
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    tempreg = DAC_Base->STRST;

    if(IS_DAC135(DACx))
    {
        tempreg &= (~DAC_STRST_STRSTDATAx_MASK);
        tempreg |= (uint32_t)ResetValue;
    }
    else
    {
        tempreg &= (~DAC_STRST_STRSTDATAy_MASK);
        tempreg |= ((uint32_t)ResetValue << 16);
    }

    DAC_Base->STRST = tempreg;
}
/**
*\*\name    DAC_SetSawtoothStepValue.
*\*\fun     Set the swatooth waveform generation step data.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   StepData:
*\*\          - the value is range from 0- 0xfff;
*\*\return  none
**/
void DAC_SetSawtoothStepValue(DACX DACx, uint16_t StepData)
{
    __IO uint32_t tempreg;
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    tempreg = DAC_Base->STINC;

    if(IS_DAC135(DACx))
    {
        tempreg &= (~DAC_STINC_STINCDATAx_MASK);
        tempreg |= (uint32_t)StepData;
    }
    else
    {
        tempreg &= (~DAC_STINC_STINCDATAy_MASK);
        tempreg |= ((uint32_t)StepData << 16);
    }

    DAC_Base->STINC = tempreg;
}

/**
*\*\name    DAC_CaliEnable.
*\*\fun     Enables or disables the specified DACx calibration function.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\note   only DACx enable buffer function and the function couldn't be used in DAC3/4/5/6.
*\*\return  none
**/
void DAC_CaliEnable(DACX DACx, FunctionalState Cmd)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACx_CTRL_CALIBATE_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACx_CTRL_CALIBATE_EN_MASK);
        }
    }
    else
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACy_CTRL_CALIBATE_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACy_CTRL_CALIBATE_EN_MASK);
        }
    }
}
/**
*\*\name    DAC_ConnetToOnChipEnable.
*\*\fun     Enables or disables the DACx output connected to on the chip.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\note   The function couldn't be used in DAC3/4/5/6.
*\*\return  none
**/
void DAC_ConnetToOnChipEnable(DACX DACx, FunctionalState Cmd)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACx_CTRL_OUTPUT_TO_ONCHAIP_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACx_CTRL_OUTPUT_TO_ONCHAIP_EN_MASK);
        }
    }
    else
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACy_CTRL_OUTPUT_TO_ONCHAIP_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACy_CTRL_OUTPUT_TO_ONCHAIP_EN_MASK);
        }
    }
}
/**
*\*\name    DAC_ConnetToExternalPinEnable.
*\*\fun     Enables or disables the DACx output connected to external pin.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\note   The function couldn't be used in DAC3/4/5/6.
*\*\return  none
**/
void DAC_ConnetToExternalPinEnable(DACX DACx, FunctionalState Cmd)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACx_CTRL_OUTPUT_TO_EXTPIN_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACx_CTRL_OUTPUT_TO_EXTPIN_EN_MASK);
        }
    }
    else
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACy_CTRL_OUTPUT_TO_EXTPIN_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACy_CTRL_OUTPUT_TO_EXTPIN_EN_MASK);
        }
    }
}
/**
*\*\name    DAC_DMADoubleDataModeEnable.
*\*\fun     Enables or disables the DACx DMA double data mode.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DAC_DMADoubleDataModeEnable(DACX DACx, FunctionalState Cmd)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACx_CTRL_DMADOUBLEMODE_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACx_CTRL_DMADOUBLEMODE_EN_MASK);
        }
    }
    else
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACy_CTRL_DMADOUBLEMODE_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACy_CTRL_DMADOUBLEMODE_EN_MASK);
        }
    }
}
/**
*\*\name    DAC_SignFormatModeEnable.
*\*\fun     Enables or disables the DACx signed format mode.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DAC_SignFormatModeEnable(DACX DACx, FunctionalState Cmd)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACx_CTRL_SINGFORMAT_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACx_CTRL_SINGFORMAT_EN_MASK);
        }
    }
    else
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACy_CTRL_SINGFORMAT_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACy_CTRL_SINGFORMAT_EN_MASK);
        }
    }
}
/**
*\*\name    DAC_HighDriveAbilityEnable.
*\*\fun     Enables or disables the DACx high driver ability output.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note   The function couldn't be used in DAC3/4/5/6.
**/
void DAC_HighDriveAbilityEnable(DACX DACx, FunctionalState Cmd)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACx_CTRL_HIGH_DRIVER_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACx_CTRL_HIGH_DRIVER_EN_MASK);
        }
    }
    else
    {
        if(Cmd != DISABLE)
        {
            DAC_Base->CTRL |= DACy_CTRL_HIGH_DRIVER_EN_MASK;
        }
        else
        {
            DAC_Base->CTRL &= ~(DACy_CTRL_HIGH_DRIVER_EN_MASK);
        }
    }
}

/**
*\*\name    DAC_GetFlagSts.
*\*\fun     Get the specified DAC status flag.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   DAC_FLAG:
*\*\        When DACx == DAC1/2, DAC_FLAG can be as follow:
*\*\          - DAC_FLAG_DMAUDR
*\*\          - DAC_FLAG_CALCOMPLETE
*\*\          - DAC_FLAG_DORSTAT
*\*\          - DAC_FLAG_TROVC
*\*\        When DACx == DAC3/4/5/6, DAC_FLAG can be as follow:
*\*\          - DAC_FLAG_DMAUDR
*\*\          - DAC_FLAG_DORSTAT
*\*\          - DAC_FLAG_TROVC
*\*\          - DAC_FLAG_VFLAGCOMP
*\*\return   FlagStatus :
*\*\          - SET
*\*\          - RESET
**/
FlagStatus DAC_GetFlagSts(DACX DACx, uint32_t DAC_FLAG)
{
    __IO uint32_t tempreg;
    FlagStatus status ;

    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);
    tempreg = DAC_Base->STS;

    if(IS_DAC135(DACx))
    {
        status = ((tempreg & DAC_FLAG) != 0) ? SET : RESET;
    }
    else
    {
        status = ((tempreg & (DAC_FLAG << 16)) != 0) ? SET : RESET;
    }

    return status;
}
/**
*\*\name    DAC_ClearFlag.
*\*\fun     Clear the specified DAC status flag.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   DAC_FLAG:
*\*\          - DAC_FLAG_DMAUDR
*\*\          - DAC_FLAG_TROVC
*\*\return   none
**/
void DAC_ClearFlag(DACX DACx, uint32_t DAC_FLAG)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        DAC_Base->STS = DAC_FLAG;
    }
    else
    {
        DAC_Base->STS = (DAC_FLAG << 16u);
    }
}
/**
*\*\name    DAC_ConfigInt.
*\*\fun     Enables or disables the specified DAC interrupts.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   DAC_IT:
*\*\          - DAC_INT_DMAUDRIEN
*\*\          - DAC_INT_TROVIEN
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DAC_ConfigInt(DACX DACx, uint32_t DAC_IT, FunctionalState Cmd)
{
    __IO uint32_t tempreg;
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);
    tempreg = DAC_Base->CTRL;

    if(IS_DAC135(DACx))
    {
        if(Cmd != DISABLE)
        {
            tempreg |= DAC_IT;
        }
        else
        {
            tempreg &= (~DAC_IT);
        }
    }
    else
    {
        if(Cmd != DISABLE)
        {
            tempreg |= (DAC_IT << 16u);
        }
        else
        {
            tempreg &= (~(DAC_IT << 16u) );
        }
    }

    DAC_Base->CTRL = tempreg;
}
/**
*\*\name    DAC_GetIntSts.
*\*\fun     Get the specified DAC interrupts flag.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   DAC_IT:
*\*\          - DAC_INTFLAG_DMAUDR
*\*\          - DAC_INTFLAG_TROVC
*\*\return   FlagStatus :
*\*\          - SET
*\*\          - RESET
**/
FlagStatus DAC_GetIntSts(DACX DACx, uint32_t DAC_IT)
{
    __IO uint32_t tempreg;
    FlagStatus status ;

    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);
    tempreg = DAC_Base->STS;

    if(IS_DAC135(DACx))
    {
        status = ((tempreg & DAC_IT) != 0u) ? SET : RESET;
    }
    else
    {
        status = ((tempreg & (DAC_IT << 16u) ) != 0u) ? SET : RESET;
    }

    return status;
}
/**
*\*\name    DAC_ClearITPendingBit.
*\*\fun     Clears the DACx interrupt pending bit.
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\          - DAC3
*\*\          - DAC4
*\*\          - DAC5
*\*\          - DAC6
*\*\param   DAC_IT:
*\*\          - DAC_INTFLAG_DMAUDR
*\*\          - DAC_INTFLAG_TROVC
*\*\return   FlagStatus :
*\*\          - SET
*\*\          - RESET
**/
void DAC_ClearITPendingBit(DACX DACx, uint32_t DAC_IT)
{
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);

    if(IS_DAC135(DACx))
    {
        DAC_Base->STS = DAC_IT;
    }
    else
    {
        DAC_Base->STS = (DAC_IT << 16u);
    }
}


/**
*\*\name    DAC_ConfigClkPrescaler.
*\*\fun     Configures the DAC_CLK prescaler.
*\*\param   DACx :
*\*\          - DAC12
*\*\          - DAC34
*\*\          - DAC56
*\*\param   Prescaler:
*\*\          - when DACx is DAC12 , the value range from 1 - 0xff
*\*\          - when DACx is DAC34 or DAC56 ,the value range from 1 - 0x1f
*\*\return   none
**/
void DAC_ConfigClkPrescaler(DAC_Module* DACx, uint8_t Prescaler)
{
    if(DACx == DAC12)
    {
        DACx->GCTRL &= (~DAC12_GCTRL_PCS_MASK);
    }
    else
    {
        DACx->GCTRL &= (~DAC3456_GCTRL_PCS_MASK);
    }

    DACx->GCTRL |= (((uint32_t)Prescaler - 1u) << 16u);
}


/**
*\*\name    DAC_SetHighFrequencyMode.
*\*\fun     Configures the high frequency interface mode for the selected DAC.
*\*\param   DACx :
*\*\          - DAC12
*\*\param   mode:
*\*\          - DAC_HIGH_FREQ_MODE_DISABLE
*\*\          - DAC_HIGH_FREQ_MODE_BELOW_80M
*\*\          - DAC_HIGH_FREQ_MODE_BELOW_160M
*\*\          - DAC_HIGH_FREQ_MODE_ABOVE_160M
*\*\return   none
**/
void DAC_SetHighFrequencyMode(DAC_Module* DACx, uint32_t mode)
{
    uint32_t tempreg;
    tempreg = DACx->GCTRL;

    tempreg &= (~DAC_GCTRL_FREQ_MODE_MASK);
    tempreg |= mode;

    DACx->GCTRL = tempreg;
}

/**
*\*\name    DAC_SetUserTrimming.
*\*\fun     Config the offset trimming value for the selected DAC .
*\*\param   DACx :
*\*\          - DAC1
*\*\          - DAC2
*\*\param   TrimmingValue: DAC new trimming value
*\*\          - the data is range from 0 - 31
*\*\return   none
*\*\note   The function couldn't be used in DAC3/4/5/6.
**/
void DAC_SetUserTrimming(DACX DACx, uint8_t TrimmingValue)
{
    __IO uint32_t tempreg;
    DAC_Module* DAC_Base = DAC_BaseAddrGet(DACx);
    tempreg = DAC_Base->CALC;

    if(IS_DAC135(DACx))
    {
        tempreg &= (~DAC_CALC_OTRIMxVALUE_MASK);
        tempreg |= (uint32_t)TrimmingValue;
    }
    else
    {
        tempreg &= (~DAC_CALC_OTRIMyVALUE_MASK);
        tempreg |= (((uint32_t)TrimmingValue) << 16u);
    }

    DAC_Base->CALC = tempreg ;
}



