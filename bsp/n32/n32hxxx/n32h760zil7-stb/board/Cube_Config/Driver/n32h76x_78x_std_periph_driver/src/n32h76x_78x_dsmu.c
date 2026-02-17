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
 * @file n32h76x_78x_dsmu.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_dsmu.h"
#include "n32h76x_78x_rcc.h"

#ifndef NULL
    #define NULL          0
#endif

/** DSMU Private variables **/
static __IO uint32_t    gDSMU_ChannelInitStatus = 0U;

/**  DSMU_Private_Functions DSMU Private Functions **/
static uint32_t DSMU_GetChannelNumber(const DSMU_Channel_Submodule *DSMU_Channely);

/**
*\*\name   DSMU_DeInit.
*\*\fun    Deinitialize the DSMU.
*\*\param  none.
*\*\return none.
**/
void DSMU_DeInit(void)
{
    /* Reset DSMU by RCC*/
    RCC_EnableAPB2PeriphReset2(RCC_APB2_PERIPHRST_DSMU);

    /* Reset initial status of all channels */
    gDSMU_ChannelInitStatus = 0U;
}

/**
*\*\name   DSMU_ChannelInit.
*\*\fun    Initialize the DSMU channel according to the specified parameters
*\*\param  DSMU_Channely
*\*\          - DSMU_Channel0
*\*\          - DSMU_Channel1
*\*\          - DSMU_Channel2
*\*\          - DSMU_Channel3
*\*\          - DSMU_Channel4
*\*\          - DSMU_Channel5
*\*\          - DSMU_Channel6
*\*\          - DSMU_Channel7
*\*\param  DSMU_ChannelyInitStruct
*\*\          - OutputClock:
*\*\             - Activation:
*\*\                - DISABLE
*\*\                - ENABLE
*\*\             - Selection:
*\*\                - DSMU_CHANNEL_OUTPUT_CLOCK_SYSTEM
*\*\                - DSMU_CHANNEL_OUTPUT_CLOCK_AUDIO
*\*\             - Divider:
*\*\                - This parameter must be a number between Min_Data = 2 and Max_Data = 256.
*\*\          - Input:
*\*\             - Multiplexer:
*\*\                - DSMU_CHANNEL_EXTERNAL_INPUTS
*\*\                - DSMU_CHANNEL_ADC_OUTPUT
*\*\                - DSMU_CHANNEL_INTERNAL_REGISTER
*\*\             - DataPacking:
*\*\                - DSMU_CHANNEL_STANDARD_MODE
*\*\                - DSMU_CHANNEL_INTERLEAVED_MODE
*\*\                - DSMU_CHANNEL_DUAL_MODE
*\*\             - Pins:
*\*\                - DSMU_CHANNEL_SAME_CHANNEL_PINS
*\*\                - DSMU_CHANNEL_FOLLOWING_CHANNEL_PINS
*\*\          - SerialInterface:
*\*\             - Type:
*\*\                - DSMU_CHANNEL_SPI_RISING
*\*\                - DSMU_CHANNEL_SPI_FALLING
*\*\                - DSMU_CHANNEL_MANCHESTER_RISING
*\*\                - DSMU_CHANNEL_MANCHESTER_FALLING
*\*\             - SpiClock:
*\*\                - DSMU_CHANNEL_SPI_CLOCK_EXTERNAL
*\*\                - DSMU_CHANNEL_SPI_CLOCK_INTERNAL
*\*\                - DSMU_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_FALLING
*\*\                - DSMU_CHANNEL_SPI_CLOCK_INTERNAL_DIV2_RISING
*\*\          - Awd:
*\*\             - FilterOrder:
*\*\                - DSMU_AWD_FASTSINC_ORDER
*\*\                - DSMU_AWD_SINC1_ORDER
*\*\                - DSMU_AWD_SINC2_ORDER
*\*\                - DSMU_AWD_SINC3_ORDER
*\*\             - Oversampling:
*\*\                - This parameter must be a number between Min_Data = 1 and Max_Data = 32.
*\*\          - Offset:
*\*\             - This parameter must be a number between Min_Data = -8388608 and Max_Data = 8388607.
*\*\          - RightBitShift:
*\*\             - This parameter must be a number between Min_Data = 0 and Max_Data = 31.
*\*\return ErrorStatus:
*\*\          - SUCCESS
*\*\          - ERROR
**/
ErrorStatus DSMU_ChannelInit(DSMU_Channel_Submodule* DSMU_Channely, DSMU_Channel_InitType* DSMU_ChannelInitStruct)
{
    uint32_t tReg;
    ErrorStatus status = SUCCESS;

    /* Check DSMU Channel handle */
    if(DSMU_ChannelInitStruct == NULL)
    {
        status = ERROR;
    }
    else
    {
        /* Configure output serial clock and enable global DSMU interface only for first channel */
        if(0U == gDSMU_ChannelInitStatus)
        {
            /* Disable the DSMU global interface */
            DSMU_Channel0->CHCFG1 &= ~(DSMU_CHYCFG1_DSMUEN);

            /* Reset clock source and divider */
            tReg = DSMU_Channel0->CHCFG1;
            tReg &= ~(DSMU_CHYCFG1_CLKOUTSRC | DSMU_CHYCFG1_CLKOUTDIV);

            /* Set the output serial clock source */
            tReg |= DSMU_ChannelInitStruct->OutputClock.Selection;

            if(DSMU_ChannelInitStruct->OutputClock.Activation != DISABLE)
            {
                /* Set the output clock divider */
                tReg |= ((DSMU_ChannelInitStruct->OutputClock.Divider - 1U) << REG_BIT16_OFFSET);
            }

            /* Write register */
            DSMU_Channel0->CHCFG1 = tReg;

            /* Enable the DSMU global interface */
            DSMU_Channel0->CHCFG1 |= DSMU_CHYCFG1_DSMUEN;
        }

        /* Disable current channel */
        DSMU_Channely->CHCFG1 &= ~(DSMU_CHYCFG1_CHEN);

        /* Config register DSMU_CHCFG1 */
        tReg = DSMU_Channely->CHCFG1;
        tReg &= ~( DSMU_CHYCFG1_DATPACK     \
                   |  DSMU_CHYCFG1_DATMUX      \
                   |  DSMU_CHYCFG1_CHINSEL     \
                   |  DSMU_CHYCFG1_SITP        \
                   |  DSMU_CHYCFG1_SPICLKSEL   );

        /* Set channel input parameters */
        tReg |= ( DSMU_ChannelInitStruct->Input.Multiplexer \
                  | DSMU_ChannelInitStruct->Input.DataPacking \
                  | DSMU_ChannelInitStruct->Input.Pins    );

        /* Set serial interface parameters */
        tReg |= ( DSMU_ChannelInitStruct->SerialInterface.Type      \
                  | DSMU_ChannelInitStruct->SerialInterface.SpiClock  );

        /* Write register */
        DSMU_Channely->CHCFG1 = tReg;

        /* Set analog watchdog parameters */
        tReg  = DSMU_Channely->CHAWDSCDET;
        tReg &= ~(DSMU_CHYAWDSCDET_AWDFORD | DSMU_CHYAWDSCDET_AWDFOSR);
        tReg |= (  DSMU_ChannelInitStruct->Awd.FilterOrder  \
                   | ((DSMU_ChannelInitStruct->Awd.Oversampling - 1U) << REG_BIT16_OFFSET));
        DSMU_Channely->CHAWDSCDET = tReg;

        /* Set channel offset and right bit shift */
        tReg  = DSMU_Channely->CHCFG2;
        tReg &= ~(DSMU_CHYCFG2_CALOFFSET | DSMU_CHYCFG2_DATRBS);
        tReg |= (((uint32_t) DSMU_ChannelInitStruct->Offset << REG_BIT8_OFFSET)  \
                 | (DSMU_ChannelInitStruct->RightBitShift << REG_BIT3_OFFSET));
        DSMU_Channely->CHCFG2 = tReg;

        /* Enable DSMU channel */
        DSMU_Channely->CHCFG1 |= DSMU_CHYCFG1_CHEN;

        /* Set channel initialize status */
        gDSMU_ChannelInitStatus |= 1UL << DSMU_GetChannelNumber(DSMU_Channely);
    }

    return status;
}

/**
*\*\name   DSMU_InitChannelStruct.
*\*\fun    Set the initialize structure of DSMU channel to default value.
*\*\param  DSMU_ChannelyInitStruct
*\*\          - OutputClock:
*\*\             - Activation
*\*\             - Selection
*\*\             - Divider
*\*\          - Input:
*\*\             - Multiplexer
*\*\             - DataPacking
*\*\             - Pins
*\*\          - SerialInterface
*\*\             - Type
*\*\             - SpiClock
*\*\          - Awd:
*\*\             - FilterOrder
*\*\             - Oversampling
*\*\          - Offset
*\*\          - RightBitShift
*\*\return none.
**/
void DSMU_InitChannelStruct(DSMU_Channel_InitType* DSMU_ChannelInitStruct)
{
    DSMU_ChannelInitStruct->OutputClock.Activation = DISABLE;
    DSMU_ChannelInitStruct->OutputClock.Selection = DSMU_CHANNEL_OUTPUT_CLOCK_SYSTEM;
    DSMU_ChannelInitStruct->OutputClock.Divider = 2U;

    DSMU_ChannelInitStruct->Input.Multiplexer = DSMU_CHANNEL_EXTERNAL_INPUTS;
    DSMU_ChannelInitStruct->Input.DataPacking = DSMU_CHANNEL_STANDARD_MODE;
    DSMU_ChannelInitStruct->Input.Pins = DSMU_CHANNEL_SAME_CHANNEL_PINS;

    DSMU_ChannelInitStruct->SerialInterface.Type = DSMU_CHANNEL_SPI_RISING;
    DSMU_ChannelInitStruct->SerialInterface.SpiClock = DSMU_CHANNEL_SPI_CLOCK_EXTERNAL;

    DSMU_ChannelInitStruct->Awd.FilterOrder = DSMU_AWD_FASTSINC_ORDER;
    DSMU_ChannelInitStruct->Awd.Oversampling = 1U;

    DSMU_ChannelInitStruct->Offset = 0;
    DSMU_ChannelInitStruct->RightBitShift = 0U;
}

/**
*\*\name   DSMU_ChannelDeInit.
*\*\fun    Deinitialize the DSMU channel
*\*\param  DSMU_Channely
*\*\          - DSMU_Channel0
*\*\          - DSMU_Channel1
*\*\          - DSMU_Channel2
*\*\          - DSMU_Channel3
*\*\          - DSMU_Channel4
*\*\          - DSMU_Channel5
*\*\          - DSMU_Channel6
*\*\          - DSMU_Channel7
*\*\return None.
**/
void DSMU_ChannelDeInit(DSMU_Channel_Submodule* DSMU_Channely)
{
    /* Disable the DSMU channel */
    DSMU_Channely->CHCFG1 &= ~(DSMU_CHYCFG1_CHEN);

    /* Clear channel initialize status */
    gDSMU_ChannelInitStatus &= ~(1U << DSMU_GetChannelNumber(DSMU_Channely));

    /* Disable global DSMU at deinit of last channel */
    if(0U == gDSMU_ChannelInitStatus)
    {
        DSMU_Channel0->CHCFG1 &= ~(DSMU_CHYCFG1_DSMUEN);
    }
}

/**
*\*\name   DSMU_ChannelCkAbEnable.
*\*\fun    Enable clock absence detection
*\*\param  DSMU_Channely
*\*\          - DSMU_Channel0
*\*\          - DSMU_Channel1
*\*\          - DSMU_Channel2
*\*\          - DSMU_Channel3
*\*\          - DSMU_Channel4
*\*\          - DSMU_Channel5
*\*\          - DSMU_Channel6
*\*\          - DSMU_Channel7
*\*\return none
**/
void DSMU_ChannelCkAbEnable(DSMU_Channel_Submodule* DSMU_Channely)
{
    /* Enable clock absence detection */
    DSMU_Channely->CHCFG1 |= DSMU_CHYCFG1_CLKABEN;
}

/**
*\*\name   DSMU_ChannelCkAbDisable.
*\*\fun    Disable clock absence detection
*\*\param  DSMU_Channely
*\*\          - DSMU_Channel0
*\*\          - DSMU_Channel1
*\*\          - DSMU_Channel2
*\*\          - DSMU_Channel3
*\*\          - DSMU_Channel4
*\*\          - DSMU_Channel5
*\*\          - DSMU_Channel6
*\*\          - DSMU_Channel7
*\*\return  none
**/
void DSMU_ChannelCkAbDisable(DSMU_Channel_Submodule* DSMU_Channely)
{
    uint32_t channel;

    /* Disable clock absence detection */
    DSMU_Channely->CHCFG1 &= ~DSMU_CHYCFG1_CLKABEN;

    /* Clear clock absence flag */
    channel = DSMU_GetChannelNumber(DSMU_Channely);
    DSMU_Filter0->FLTINTCLR = (1UL << (REG_BIT16_OFFSET + channel));
}

/**
*\*\name   DSMU_ChannelScdStart.
*\*\fun    This function allows to start short circuit detection and assignment break signal.
*\*\param  DSMU_Channely
*\*\          - DSMU_Channel0
*\*\          - DSMU_Channel1
*\*\          - DSMU_Channel2
*\*\          - DSMU_Channel3
*\*\          - DSMU_Channel4
*\*\          - DSMU_Channel5
*\*\          - DSMU_Channel6
*\*\          - DSMU_Channel7
*\*\param  Threshold Short circuit detector threshold.
              - This parameter must be a number between Min_Data = 0 and Max_Data = 255.
*\*\param  BreakSignal Break signals assigned to short circuit event.
*\*\          - DSMU_NO_BREAK_SIGNAL
*\*\          - DSMU_BREAK_SIGNAL_0
*\*\          - DSMU_BREAK_SIGNAL_1
*\*\          - DSMU_BREAK_SIGNAL_2
*\*\          - DSMU_BREAK_SIGNAL_3
*\*\return none
*\*\note   Same mode has to be used for all channels
**/
void DSMU_ChannelScdStart(DSMU_Channel_Submodule* DSMU_Channely,
                          uint32_t Threshold, uint32_t BreakSignal)
{
    uint32_t tReg;

    /* Configure threshold and break signals */
    tReg  = DSMU_Channely->CHAWDSCDET;
    tReg &= ~(DSMU_CHYAWDSCDET_BKSCDET | DSMU_CHYAWDSCDET_SCDETTH);
    tReg |= ((BreakSignal << REG_BIT12_OFFSET) | Threshold);
    DSMU_Channely->CHAWDSCDET = tReg;

    /* Start short circuit detection */
    DSMU_Channely->CHCFG1 |= DSMU_CHYCFG1_SCDETEN;
}

/**
*\*\name   DSMU_ChannelScdStop.
*\*\fun    This function allows to stop short circuit detection.
*\*\param  DSMU_Channely
*\*\          - DSMU_Channel0
*\*\          - DSMU_Channel1
*\*\          - DSMU_Channel2
*\*\          - DSMU_Channel3
*\*\          - DSMU_Channel4
*\*\          - DSMU_Channel5
*\*\          - DSMU_Channel6
*\*\          - DSMU_Channel7
*\*\return  none
**/
void DSMU_ChannelScdStop(DSMU_Channel_Submodule* DSMU_Channely)
{
    uint32_t channel;

    /* Stop short circuit detection */
    DSMU_Channely->CHCFG1 &= ~(DSMU_CHYCFG1_SCDETEN);

    /* Clear short circuit detection flag */
    channel = DSMU_GetChannelNumber(DSMU_Channely);
    DSMU_Filter0->FLTINTCLR = (1UL << (REG_BIT24_OFFSET + channel));
}

/**
*\*\name   DSMU_ChannelGetAwdValue.
*\*\fun    This function allows to get analog watchdog value for current channel.
*\*\param  DSMU_Channely
*\*\          - DSMU_Channel0
*\*\          - DSMU_Channel1
*\*\          - DSMU_Channel2
*\*\          - DSMU_Channel3
*\*\          - DSMU_Channel4
*\*\          - DSMU_Channel5
*\*\          - DSMU_Channel6
*\*\          - DSMU_Channel7
*\*\return Channel analog watchdog value.
**/
int16_t DSMU_ChannelGetAwdValue(const DSMU_Channel_Submodule* DSMU_Channely)
{
    return (int16_t)(DSMU_Channely->CHAWDDAT);
}

/**
*\*\name   DSMU_ChannelModifyOffset.
*\*\fun    This function allows to modify channel offset value.
*\*\param  DSMU_Channely
*\*\          - DSMU_Channel0
*\*\          - DSMU_Channel1
*\*\          - DSMU_Channel2
*\*\          - DSMU_Channel3
*\*\          - DSMU_Channel4
*\*\          - DSMU_Channel5
*\*\          - DSMU_Channel6
*\*\          - DSMU_Channel7
*\*\param  Offset DFSDM channel offset.
              - This parameter must be a number between Min_Data = -8388608 and Max_Data = 8388607.
*\*\return none.
**/
void DSMU_ChannelModifyOffset(DSMU_Channel_Submodule* DSMU_Channely, int32_t Offset)
{
    uint32_t tReg;

    tReg  = DSMU_Channely->CHCFG2;
    tReg &= (~(DSMU_CHYCFG2_CALOFFSET));
    tReg |= ((uint32_t) Offset << REG_BIT8_OFFSET);
    DSMU_Channely->CHCFG2 = tReg;
}

/**
*\*\name   DSMU_ChannelWriteData.
*\*\fun    This function allows to write data into input data register.
*\*\param  DSMU_Channely
*\*\          - DSMU_Channel0
*\*\          - DSMU_Channel1
*\*\          - DSMU_Channel2
*\*\          - DSMU_Channel3
*\*\          - DSMU_Channel4
*\*\          - DSMU_Channel5
*\*\          - DSMU_Channel6
*\*\          - DSMU_Channel7
*\*\param  data New data write by CPU.
*\*\return none.
**/
void DSMU_ChannelWriteData(DSMU_Channel_Submodule* DSMU_Channely, uint32_t data)
{
    DSMU_Channely->CHDATIN = data;
}

/**
*\*\name   DSMU_FilterInit.
*\*\fun    Initialize the DSMU filter according to the specified parameters
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  DSMU_FilterInitStruct
*\*\          - RegularParam:
*\*\             - DmaMode:
*\*\                - DISABLE
*\*\                - ENABLE
*\*\             - FastMode:
*\*\                - DISABLE
*\*\                - ENABLE
*\*\             - Trigger:
*\*\                - DSMU_FILTER_SW_TRIGGER
*\*\                - DSMU_FILTER_SYNC_TRIGGER
*\*\          - InjectedParam:
*\*\             - ScanMode:
*\*\                - DISABLE
*\*\                - ENABLE
*\*\             - DmaMode:
*\*\                - DISABLE
*\*\                - ENABLE
*\*\             - Trigger:
*\*\                - DSMU_FILTER_SW_TRIGGER
*\*\                - DSMU_FILTER_SYNC_TRIGGER
*\*\                - DSMU_FILTER_EXT_TRIGGER
*\*\             - ExtTrigger:
*\*\                - DSMU_FILTER_EXT_TRIG_ATIM1_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_ATIM2_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_ATIM3_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_ATIM4_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_GTIMB1_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_GTIMB2_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_GTIMB3_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_GTIMA1_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_GTIMA2_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_GTIMA3_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_GTIMA4_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_GTIMA5_TRGO
*\*\                - DSMU_FILTER_EXT_TRIG_ATIM1_TRGO2
*\*\                - DSMU_FILTER_EXT_TRIG_ATIM3_TRGO2
*\*\                - DSMU_FILTER_EXT_TRIG_SHRTIM1_ADC_TRG1
*\*\                - DSMU_FILTER_EXT_TRIG_SHRTIM1_ADC_TRG2
*\*\                - DSMU_FILTER_EXT_TRIG_SHRTIM1_ADC_TRG3
*\*\                - DSMU_FILTER_EXT_TRIG_SHRTIM1_ADC_TRG4
*\*\                - DSMU_FILTER_EXT_TRIG_SHRTIM2_ADC_TRG1
*\*\                - DSMU_FILTER_EXT_TRIG_SHRTIM2_ADC_TRG2
*\*\                - DSMU_FILTER_EXT_TRIG_SHRTIM2_ADC_TRG3
*\*\                - DSMU_FILTER_EXT_TRIG_SHRTIM2_ADC_TRG4
*\*\                - DSMU_FILTER_EXT_TRIG_EXTI6
*\*\                - DSMU_FILTER_EXT_TRIG_EXTI7
*\*\                - DSMU_FILTER_EXT_TRIG_EXTI8
*\*\                - DSMU_FILTER_EXT_TRIG_EXTI9
*\*\                - DSMU_FILTER_EXT_TRIG_EXTI10
*\*\                - DSMU_FILTER_EXT_TRIG_EXTI11
*\*\                - DSMU_FILTER_EXT_TRIG_EXTI12
*\*\                - DSMU_FILTER_EXT_TRIG_EXTI13
*\*\                - DSMU_FILTER_EXT_TRIG_EXTI14
*\*\                - DSMU_FILTER_EXT_TRIG_EXTI15
*\*\          - FilterParam:
*\*\             - SincOrder:
*\*\                - DSMU_FILTER_FASTSINC_ORDER
*\*\                - DSMU_FILTER_SINC1_ORDER
*\*\                - DSMU_FILTER_SINC2_ORDER
*\*\                - DSMU_FILTER_SINC3_ORDER
*\*\                - DSMU_FILTER_SINC4_ORDER
*\*\                - DSMU_FILTER_SINC5_ORDER
*\*\             - Oversampling:
*\*\                - This parameter must be a number between Min_Data = 1 and Max_Data = 1024.
*\*\             - IntOversampling:
*\*\                - This parameter must be a number between Min_Data = 1 and Max_Data = 256.
*\*\return  ErrorStatus.
*\*\          - SUCCESS
*\*\          - ERROR
**/
ErrorStatus DSMU_FilterInit(DSMU_Filter_Submodule* DSMU_Filterx,
                            DSMU_Filter_InitType* DSMU_FilterInitStruct)
{
    uint32_t tReg;
    ErrorStatus status = SUCCESS;

    /* Check parameters compatibility */
    if ((DSMU_Filterx == DSMU_Filter0) &&
            ((DSMU_FilterInitStruct->RegularParam.Trigger  == DSMU_FILTER_SYNC_TRIGGER) ||
             (DSMU_FilterInitStruct->InjectedParam.Trigger == DSMU_FILTER_SYNC_TRIGGER)))
    {
        status = ERROR;
    }
    else
    {
        /* Disable the filter */
        DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_DFLTEN);

        /* Config FLTCTRL1 register */
        tReg  = DSMU_Filterx->FLTCTRL1;
        tReg &= ~( DSMU_FLTXCTRL1_FAST      \
                   |  DSMU_FLTXCTRL1_RDMAEN    \
                   |  DSMU_FLTXCTRL1_RSYNC     \
                   |  DSMU_FLTXCTRL1_JEXTEN    \
                   |  DSMU_FLTXCTRL1_JEXTSEL   \
                   |  DSMU_FLTXCTRL1_JDMAEN    \
                   |  DSMU_FLTXCTRL1_JSCAN     \
                   |  DSMU_FLTXCTRL1_JSYNC     );

        /* Set regular parameters */
        if(DSMU_FilterInitStruct->RegularParam.FastMode != DISABLE)
        {
            tReg |= DSMU_FLTXCTRL1_FAST;
        }

        if(DSMU_FilterInitStruct->RegularParam.DmaMode != DISABLE)
        {
            tReg |= DSMU_FLTXCTRL1_RDMAEN;
        }

        /* Set injected parameters */
        if(DSMU_FilterInitStruct->InjectedParam.Trigger == DSMU_FILTER_EXT_TRIGGER)
        {
            tReg |= DSMU_FilterInitStruct->InjectedParam.ExtTrigger;
        }

        if(DSMU_FilterInitStruct->InjectedParam.ScanMode != DISABLE)
        {
            tReg |= DSMU_FLTXCTRL1_JSCAN;
        }

        if(DSMU_FilterInitStruct->InjectedParam.DmaMode != DISABLE)
        {
            tReg |= DSMU_FLTXCTRL1_JDMAEN;
        }

        /* Write register */
        DSMU_Filterx->FLTCTRL1 = tReg;

        /* Set filter parameters */
        tReg  = DSMU_Filterx->FLTFCTRL;
        tReg &= ~(DSMU_FLTXFCTRL_FORD | DSMU_FLTXFCTRL_FOSR | DSMU_FLTXFCTRL_IOSR);
        tReg |= (  DSMU_FilterInitStruct->FilterParam.SincOrder   \
                   | ((DSMU_FilterInitStruct->FilterParam.Oversampling - 1U) << REG_BIT16_OFFSET) \
                   | (DSMU_FilterInitStruct->FilterParam.IntOversampling - 1U));
        DSMU_Filterx->FLTFCTRL = tReg;

        /* Enable DSMU filter */
        DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_DFLTEN;
    }

    return status;
}

/**
*\*\name   DSMU_InitFilterStruct.
*\*\fun    Set the initialize structure of DSMU filter to default value.
*\*\param  DSMU_FilterInitStruct
*\*\          - RegularParam:
*\*\             - DmaMode
*\*\             - FastMode
*\*\             - Trigger
*\*\          - InjectedParam:
*\*\             - ScanMode
*\*\             - DmaMode
*\*\             - Trigger
*\*\             - ExtTrigger
*\*\          - FilterParam:
*\*\             - SincOrder
*\*\             - Oversampling
*\*\             - IntOversampling
*\*\return none.
**/
void DSMU_InitFilterStruct(DSMU_Filter_InitType* DSMU_FilterInitStruct)
{
    DSMU_FilterInitStruct->RegularParam.Trigger = DSMU_FILTER_SW_TRIGGER;
    DSMU_FilterInitStruct->RegularParam.FastMode = DISABLE;
    DSMU_FilterInitStruct->RegularParam.DmaMode = DISABLE;

    DSMU_FilterInitStruct->InjectedParam.Trigger = DSMU_FILTER_SW_TRIGGER;
    DSMU_FilterInitStruct->InjectedParam.ScanMode = DISABLE;
    DSMU_FilterInitStruct->InjectedParam.DmaMode = DISABLE;
    DSMU_FilterInitStruct->InjectedParam.ExtTrigger = DSMU_FILTER_EXT_TRIG_ATIM1_TRGO;

    DSMU_FilterInitStruct->FilterParam.SincOrder = DSMU_FILTER_FASTSINC_ORDER;
    DSMU_FilterInitStruct->FilterParam.Oversampling = 1U;
    DSMU_FilterInitStruct->FilterParam.IntOversampling = 1U;
}

/**
*\*\name   DSMU_FilterEnable.
*\*\fun    Enable or Disable the DSMU filter.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return None.
**/
void DSMU_FilterEnable(DSMU_Filter_Submodule* DSMU_Filterx, FunctionalState Cmd)
{
    if( Cmd != DISABLE)
    {
        DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_DFLTEN;
    }
    else
    {
        DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_DFLTEN);
    }
}

/**
*\*\name   DSMU_FilterConfigRegChannel.
*\*\fun    This function allows to select regular channel and
*\*\       config continuous mode for regular conversion.
*\*\param  DSMU_Filterx:
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  ChannelSelect:
*\*\          - DSMU_CHANNEL_SELECT_0
*\*\          - DSMU_CHANNEL_SELECT_1
*\*\          - DSMU_CHANNEL_SELECT_2
*\*\          - DSMU_CHANNEL_SELECT_3
*\*\          - DSMU_CHANNEL_SELECT_4
*\*\          - DSMU_CHANNEL_SELECT_5
*\*\          - DSMU_CHANNEL_SELECT_6
*\*\          - DSMU_CHANNEL_SELECT_7
*\*\param  ContinuousMode Enable/disable continuous mode for regular conversion.
*\*\          - DSMU_CONTINUOUS_CONV_OFF
*\*\          - DSMU_CONTINUOUS_CONV_ON
*\*\return  none
**/
void DSMU_FilterConfigRegChannel(DSMU_Filter_Submodule* DSMU_Filterx,
                                 uint32_t  ChannelSelect,
                                 uint32_t  ContinuousMode)
{
    /* Configure channel and continuous mode for regular conversion */
    DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_RCH | DSMU_FLTXCTRL1_RCONT);
    DSMU_Filterx->FLTCTRL1 |= ((ChannelSelect & DSMU_FLTXCTRL1_RCH) | ContinuousMode);
}

/**
*\*\name   DSMU_FilterConfigInjChannel.
*\*\fun    This function allows to select channels for injected conversion.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  ChannelSelect:
*\*\          - DSMU_CHANNEL_SELECT_0
*\*\          - DSMU_CHANNEL_SELECT_1
*\*\          - DSMU_CHANNEL_SELECT_2
*\*\          - DSMU_CHANNEL_SELECT_3
*\*\          - DSMU_CHANNEL_SELECT_4
*\*\          - DSMU_CHANNEL_SELECT_5
*\*\          - DSMU_CHANNEL_SELECT_6
*\*\          - DSMU_CHANNEL_SELECT_7
*\*\return  none
**/
void DSMU_FilterConfigInjChannel(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t ChannelSelect)
{
    /* Configure channel for injected conversion */
    DSMU_Filterx->FLTJCHG = (ChannelSelect & DSMU_FLTXJCHG_JCHG);
}

/**
*\*\name   DSMU_FilterGetRegularValue.
*\*\fun    This function allows to get regular conversion value.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  Channel Corresponding channel number of regular conversion.
*\*\return Regular conversion value
**/
int32_t DSMU_FilterGetRegularValue(const DSMU_Filter_Submodule* DSMU_Filterx,
                                   uint32_t* Channel)
{
    uint32_t reg;
    int32_t  value;

    /* Get value of data register for regular channel */
    reg = DSMU_Filterx->FLTRDATA;

    /* Extract channel and regular conversion value */
    *Channel = (reg & DSMU_FLTXRDAT_RDATCH);

    /* Regular conversion value is a signed value located on 24 MSB of register */
    /* So after applying a mask on these bits we have to perform a division by 256 (2 raised to the power of 8) */
    reg &= DSMU_FLTXRDAT_RDAT;
    value = ((int32_t)reg) / 256;

    /* return regular conversion value */
    return value;
}

/**
*\*\name   DSMU_FilterGetInjectedValue.
*\*\fun    This function allows to get injected conversion value.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  Channel Corresponding channel number of injected conversion.
*\*\return Injected conversion value
**/
int32_t DSMU_FilterGetInjectedValue(const DSMU_Filter_Submodule* DSMU_Filterx,
                                    uint32_t* Channel)
{
    uint32_t reg;
    int32_t  value;

    /* Get value of data register for injected channel */
    reg = DSMU_Filterx->FLTJDATA;

    /* Extract channel and injected conversion value */
    *Channel = (reg & DSMU_FLTXJDAT_JDATCH);

    /* Injected conversion value is a signed value located on 24 MSB of register */
    /* So after applying a mask on these bits we have to perform a division by 256 (2 raised to the power of 8) */
    reg &= DSMU_FLTXJDAT_JDAT;
    value = ((int32_t)reg) / 256;

    /* return regular conversion value */
    return value;
}

/**
*\*\name   DSMU_FilterAwdStart.
*\*\fun    This function allows to start filter analog watchdog.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  awdParam DSMU filter analog watchdog parameters.
*\*\          - DataSource:
*\*\            - DSMU_FILTER_AWD_FILTER_DATA
*\*\            - DSMU_FILTER_AWD_CHANNEL_DATA
*\*\          - ChannelSelect:
*\*\            - DSMU_CHANNEL_SELECT_0
*\*\            - DSMU_CHANNEL_SELECT_1
*\*\            - DSMU_CHANNEL_SELECT_2
*\*\            - DSMU_CHANNEL_SELECT_3
*\*\            - DSMU_CHANNEL_SELECT_4
*\*\            - DSMU_CHANNEL_SELECT_5
*\*\            - DSMU_CHANNEL_SELECT_6
*\*\            - DSMU_CHANNEL_SELECT_7
*\*\          - HighThreshold:
*\*\             - This parameter must be a number between Min_Data = -8388608 and Max_Data = 8388607.
*\*\          - LowThreshold:
*\*\             - This parameter must be a number between Min_Data = -8388608 and Max_Data = 8388607.
*\*\          - HighBreakSignal:
*\*\            - DSMU_NO_BREAK_SIGNAL
*\*\            - DSMU_BREAK_SIGNAL_0
*\*\            - DSMU_BREAK_SIGNAL_1
*\*\            - DSMU_BREAK_SIGNAL_2
*\*\            - DSMU_BREAK_SIGNAL_3
*\*\          - LowBreakSignal:
*\*\            - DSMU_NO_BREAK_SIGNAL
*\*\            - DSMU_BREAK_SIGNAL_0
*\*\            - DSMU_BREAK_SIGNAL_1
*\*\            - DSMU_BREAK_SIGNAL_2
*\*\            - DSMU_BREAK_SIGNAL_3
*\*\return  none
**/
void DSMU_FilterAwdStart(DSMU_Filter_Submodule* DSMU_Filterx,
                         DSMU_Filter_AwdParamType* awdParam)
{
    uint32_t tReg;

    /* Set analog watchdog data source */
    tReg  = DSMU_Filterx->FLTCTRL1;
    tReg &= ~(DSMU_FLTXCTRL1_AWDFSEL);
    tReg |= awdParam->DataSource;
    DSMU_Filterx->FLTCTRL1 = tReg;

    /* Set thresholds and break signals */
    tReg  = DSMU_Filterx->FLTAWDHT;
    tReg &= ~(DSMU_FLTXAWDHT_AWDHT | DSMU_FLTXAWDHT_BKAWDHT);
    tReg |= (((uint32_t) awdParam->HighThreshold << REG_BIT8_OFFSET) \
             |            awdParam->HighBreakSignal    );
    DSMU_Filterx->FLTAWDHT = tReg;

    tReg  = DSMU_Filterx->FLTAWDLT;
    tReg &= ~(DSMU_FLTXAWDLT_AWDLT | DSMU_FLTXAWDLT_BKAWDLT);
    tReg |= (((uint32_t) awdParam->LowThreshold << REG_BIT8_OFFSET) \
             |            awdParam->LowBreakSignal    );
    DSMU_Filterx->FLTAWDLT = tReg;

    /* Set channels and interrupt for analog watchdog */
    tReg  = DSMU_Filterx->FLTCTRL2;
    tReg &= ~(DSMU_FLTXCTRL2_AWDCH);
    tReg |= (awdParam->ChannelSelect & DSMU_FLTXCTRL2_AWDCH);
    DSMU_Filterx->FLTCTRL2 = tReg;
}

/**
*\*\name   DSMU_FilterAwdStop.
*\*\fun    This function allows to stop filter analog watchdog.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\return  none
**/
void DSMU_FilterAwdStop(DSMU_Filter_Submodule* DSMU_Filterx)
{
    /* Reset channels for analog watchdog and deactivate interrupt */
    DSMU_Filterx->FLTCTRL2 &= ~(DSMU_FLTXCTRL2_AWDCH);

    /* Clear all analog watchdog flags */
    DSMU_Filterx->FLTAWDCLR = (DSMU_FLTXAWDCLR_CLRAWDHTF | DSMU_FLTXAWDCLR_CLRAWDLTF);

    /* Reset thresholds and break signals */
    DSMU_Filterx->FLTAWDHT &= ~(DSMU_FLTXAWDHT_AWDHT | DSMU_FLTXAWDHT_BKAWDHT);
    DSMU_Filterx->FLTAWDLT &= ~(DSMU_FLTXAWDLT_AWDLT | DSMU_FLTXAWDLT_BKAWDLT);

    /* Reset analog watchdog data source */
    DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_AWDFSEL);
}

/**
*\*\name   DSMU_FilterExdStart.
*\*\fun    This function allows to start extreme detector feature.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  ChannelSelect:
*\*\          - DSMU_CHANNEL_SELECT_0
*\*\          - DSMU_CHANNEL_SELECT_1
*\*\          - DSMU_CHANNEL_SELECT_2
*\*\          - DSMU_CHANNEL_SELECT_3
*\*\          - DSMU_CHANNEL_SELECT_4
*\*\          - DSMU_CHANNEL_SELECT_5
*\*\          - DSMU_CHANNEL_SELECT_6
*\*\          - DSMU_CHANNEL_SELECT_7
*\*\return  none
**/
void DSMU_FilterExdStart(DSMU_Filter_Submodule* DSMU_Filterx,
                         uint32_t ChannelSelect)
{
    uint32_t tReg;

    /* Set channels for extreme detector */
    tReg  = DSMU_Filterx->FLTCTRL2;
    tReg &= ~(DSMU_FLTXCTRL2_EXDETCH);
    tReg |= (ChannelSelect & DSMU_FLTXCTRL2_EXDETCH);
    DSMU_Filterx->FLTCTRL2 = tReg;
}

/**
*\*\name   DSMU_FilterExdStop.
*\*\fun    This function allows to stop extreme detector feature.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\return  none
**/
void DSMU_FilterExdStop(DSMU_Filter_Submodule* DSMU_Filterx)
{
    __IO uint32_t     reg1;
    __IO uint32_t     reg2;

    /* Reset channels for extreme detector */
    DSMU_Filterx->FLTCTRL2 &= ~(DSMU_FLTXCTRL2_EXDETCH);

    /* Clear extreme detector values */
    reg1 = DSMU_Filterx->FLTEXDETMAX;
    reg2 = DSMU_Filterx->FLTEXDETMIN;
    (void)(reg1); /* To avoid GCC warning */
    (void)(reg2); /* To avoid GCC warning */
}

/**
*\*\name   DSMU_FilterGetExdMaxValue.
*\*\fun    This function allows to get extreme detector maximum value.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  Channel Corresponding channel.
*\*\return Extreme detector maximum value
*\*\          - This value is between Min_Data = -8388608 and Max_Data = 8388607.
**/
int32_t DSMU_FilterGetExdMaxValue(const DSMU_Filter_Submodule* DSMU_Filterx,
                                  uint32_t* Channel)
{
    uint32_t reg;
    int32_t  value;

    /* Get value of extreme detector maximum register */
    reg = DSMU_Filterx->FLTEXDETMAX;

    /* Extract channel and extreme detector maximum value */
    *Channel = (reg & DSMU_FLTXEXDETMAX_EXDETMAXCH);

    /* Extreme detector maximum value is a signed value located on 24 MSB of register */
    /* So after applying a mask on these bits we have to perform a division by 256 (2 raised to the power of 8) */
    reg &= DSMU_FLTXEXDETMAX_EXDETMAX;
    value = ((int32_t)reg) / 256;

    /* return extreme detector maximum value */
    return value;
}

/**
*\*\name   DSMU_FilterGetExdMinValue.
*\*\fun    This function allows to get extreme detector minimum value.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  Channel Corresponding channel.
*\*\return Extreme detector minimum value
*\*\          - This value is between Min_Data = -8388608 and Max_Data = 8388607.
**/
int32_t DSMU_FilterGetExdMinValue(const DSMU_Filter_Submodule* DSMU_Filterx,
                                  uint32_t* Channel)
{
    uint32_t reg;
    int32_t  value;

    /* Get value of extreme detector minimum register */
    reg = DSMU_Filterx->FLTEXDETMIN;

    /* Extract channel and extreme detector minimum value */
    *Channel = (reg & DSMU_FLTXEXDETMIN_EXDETMINCH);

    /* Extreme detector minimum value is a signed value located on 24 MSB of register */
    /* So after applying a mask on these bits we have to perform a division by 256 (2 raised to the power of 8) */
    reg &= DSMU_FLTXEXDETMIN_EXDETMIN;
    value = ((int32_t)reg) / 256;

    /* return extreme detector minimum value */
    return value;
}

/**
*\*\name   DSMU_FilterGetConvTimeValue.
*\*\fun    This function allows to get conversion time value.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\return Conversion time value
*\*\note   To get time in second, this value has to be divided by DSMU clock frequency.
**/
uint32_t DSMU_FilterGetConvTimeValue(const DSMU_Filter_Submodule* DSMU_Filterx)
{
    uint32_t reg;
    uint32_t value;

    /* Get value of conversion timer register */
    reg = DSMU_Filterx->FLTCOVTIM;

    /* Extract conversion time value */
    value = ((reg & DSMU_FLTXCOVTIM_COVCNT) >> REG_BIT4_OFFSET);

    /* return extreme detector minimum value */
    return value;
}

/**
*\*\name   DSMU_RegConvStart.
*\*\fun    This function allows to really start regular conversion.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  Trigger
*\*\          - DSMU_FILTER_SW_TRIGGER
*\*\          - DSMU_FILTER_SYNC_TRIGGER
*\*\return None
**/
void DSMU_RegConvStart(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t Trigger)
{
    /* Check regular trigger */
    if(Trigger == DSMU_FILTER_SYNC_TRIGGER) /* Synchronous with DSMU_FLT0 */
    {
        /* DSMU filter0 can not be start with synchronous triger */
        if(DSMU_Filterx != DSMU_Filter0)
        {
            /* Disable DSMU filter */
            DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_DFLTEN);

            /* Set RSYNC bit in DSMU_FLTXCTRL1 register */
            DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_RSYNC;

            /* Enable DSMU  filter */
            DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_DFLTEN;
        }
    }
    else /* Software trigger */
    {
        /* Enable DSMU  filter */
        DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_DFLTEN;

        /* Software start of regular conversion */
        DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_RSWSTART;
    }
}

/**
*\*\name   DSMU_RegConvStop.
*\*\fun    This function allows to really stop regular conversion.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  Trigger
*\*\          - DSMU_FILTER_SW_TRIGGER
*\*\          - DSMU_FILTER_SYNC_TRIGGER
*\*\return None
**/
void DSMU_RegConvStop(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t Trigger)
{
    /* Disable DSMU filter */
    DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_DFLTEN);

    /* If regular trigger was synchronous, reset RSYNC bit in DSMU_FLTXCTRL1 register */
    if(Trigger == DSMU_FILTER_SYNC_TRIGGER)
    {
        DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_RSYNC);
    }

    /* Enable DSMU filter */
    DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_DFLTEN;
}

/**
*\*\name   DSMU_InjConvStart.
*\*\fun    This function allows to really start injected conversion.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  Trigger
*\*\          - DSMU_FILTER_SW_TRIGGER
*\*\          - DSMU_FILTER_SYNC_TRIGGER
*\*\          - DSMU_FILTER_EXT_TRIGGER
*\*\param  TiggerEdge
*\*\          - DSMU_FILTER_EXT_TRIG_DISABLE
*\*\          - DSMU_FILTER_EXT_TRIG_RISING_EDGE
*\*\          - DSMU_FILTER_EXT_TRIG_FALLING_EDGE
*\*\          - DSMU_FILTER_EXT_TRIG_BOTH_EDGES
*\*\return None
**/
void DSMU_InjConvStart(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t Trigger, uint32_t TiggerEdge)
{
    uint32_t tReg;

    /* Check injected trigger */
    if(Trigger == DSMU_FILTER_SW_TRIGGER)
    {
        /* Enable DSMU  filter */
        DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_DFLTEN;

        /* Software start of injected conversion */
        DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_JSWSTART;
    }
    else /* external or synchronous trigger */
    {
        /* Disable DSMU filter */
        DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_DFLTEN);

        /* Get current register value*/
        tReg  = DSMU_Filterx->FLTCTRL1;

        /* Clear JSYNC and JEXTEN[1:0] bits first */
        tReg &= ~(DSMU_FLTXCTRL1_JEXTEN | DSMU_FLTXCTRL1_JSYNC);

        /* Config JSYNC and JEXTEN[1:0] as expected */
        if(Trigger == DSMU_FILTER_SYNC_TRIGGER)
        {
            /* Set JSYNC bit in DSMU_FLTXCTRL1 register */
            tReg |= DSMU_FLTXCTRL1_JSYNC;
        }
        else /* external trigger */
        {
            /* Set JEXTEN[1:0] bits in DSMU_FLTXCTRL1 register */
            tReg |= TiggerEdge;
        }

        /* Write back */
        DSMU_Filterx->FLTCTRL1 = tReg;

        /* Enable DSMU filter */
        DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_DFLTEN;
    }
}

/**
*\*\name   DSMU_InjConvStop.
*\*\fun    This function allows to really stop injected conversion.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param  Trigger
*\*\          - DSMU_FILTER_SW_TRIGGER
*\*\          - DSMU_FILTER_SYNC_TRIGGER
*\*\          - DSMU_FILTER_EXT_TRIGGER
*\*\return None
**/
void DSMU_InjConvStop(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t Trigger)
{
    /* Disable DSMU filter */
    DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_DFLTEN);

    /* If injected trigger was synchronous, reset JSYNC bit in DSMU_FLTXCTRL1 register */
    if(Trigger == DSMU_FILTER_SYNC_TRIGGER)
    {
        DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_JSYNC);
    }
    else if(Trigger == DSMU_FILTER_EXT_TRIGGER)
    {
        /* Reset JEXTEN[1:0] bits in DSMU_FLTXCTRL1 register */
        DSMU_Filterx->FLTCTRL1 &= ~(DSMU_FLTXCTRL1_JEXTEN);
    }
    else
    {
        /* Nothing to do */
    }

    /* Enable DSMU filter */
    DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_DFLTEN;
}

/**
*\*\name   DSMU_GetFlagStatus.
*\*\fun    Checks whether the DSMU flag has set or not.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param   DSMU_Flag:
*\*\          This parameter must be one of the following:
*\*\          - DSMU_FLAG_SHORT_CIRCUIT_CH0
*\*\          - DSMU_FLAG_SHORT_CIRCUIT_CH1
*\*\          - DSMU_FLAG_SHORT_CIRCUIT_CH2
*\*\          - DSMU_FLAG_SHORT_CIRCUIT_CH3
*\*\          - DSMU_FLAG_SHORT_CIRCUIT_CH4
*\*\          - DSMU_FLAG_SHORT_CIRCUIT_CH5
*\*\          - DSMU_FLAG_SHORT_CIRCUIT_CH6
*\*\          - DSMU_FLAG_SHORT_CIRCUIT_CH7
*\*\          - DSMU_FLAG_CLOCK_ABSENCE_CH0
*\*\          - DSMU_FLAG_CLOCK_ABSENCE_CH1
*\*\          - DSMU_FLAG_CLOCK_ABSENCE_CH2
*\*\          - DSMU_FLAG_CLOCK_ABSENCE_CH3
*\*\          - DSMU_FLAG_CLOCK_ABSENCE_CH4
*\*\          - DSMU_FLAG_CLOCK_ABSENCE_CH5
*\*\          - DSMU_FLAG_CLOCK_ABSENCE_CH6
*\*\          - DSMU_FLAG_CLOCK_ABSENCE_CH7
*\*\          - DSMU_FLAG_REGULAR_ACTIVE
*\*\          - DSMU_FLAG_INJECT_ACTIVE
*\*\          - DSMU_FLAG_ANALOG_WATCHDOG
*\*\          - DSMU_FLAG_REGULAR_OVERRUN
*\*\          - DSMU_FLAG_INJECT_OVERRUN
*\*\          - DSMU_FLAG_REGULAR_END
*\*\          - DSMU_FLAG_INJECT_END
*\*\return FlagStatus:
*\*\          - SET
*\*\          - RESET
*\*\note: DSMU_FLAG_SHORT_CIRCUIT_CH0~7 and DSMU_FLAG_CLOCK_ABSENCE_CH0~7 only exist in DSMU_Filter0->FLTSTS.
**/
FlagStatus DSMU_GetFlagStatus(DSMU_Filter_Submodule* DSMU_Filterx,
                              uint32_t DSMU_Flag)
{
    FlagStatus bitstatus;
    uint32_t tFLTSTS;

    if(DSMU_Flag > DSMU_FLAG_REGULAR_ACTIVE)
    {
        tFLTSTS = DSMU_Filter0->FLTSTS;
    }
    else
    {
        tFLTSTS = DSMU_Filterx->FLTSTS;
    }

    if ((tFLTSTS & DSMU_Flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
*\*\name   DSMU_ClearFlag.
*\*\fun    Clears flags of the specified DSMU.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param   DSMU_FlagClear :
*\*\          This parameter must be one of the following:
*\*\          - DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH0
*\*\          - DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH1
*\*\          - DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH2
*\*\          - DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH3
*\*\          - DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH4
*\*\          - DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH5
*\*\          - DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH6
*\*\          - DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH7
*\*\          - DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH0
*\*\          - DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH1
*\*\          - DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH2
*\*\          - DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH3
*\*\          - DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH4
*\*\          - DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH5
*\*\          - DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH6
*\*\          - DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH7
*\*\          - DSMU_CLEAR_FLAG_REGULAR_OVERRUN
*\*\          - DSMU_CLEAR_FLAG_INJECT_OVERRUN
*\*\return    none.
*\*\note: DSMU_CLEAR_FLAG_SHORT_CIRCUIT_CH0~7 and DSMU_CLEAR_FLAG_CLOCK_ABSENCE_CH0~7 only exist in DSMU_Filter0->FLTINTCLR.
**/
void DSMU_ClearFlag(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t DSMU_FlagClear)
{
    __IO uint32_t *pINTCLR;

    if(DSMU_FlagClear > DSMU_CLEAR_FLAG_REGULAR_OVERRUN)
    {
        pINTCLR = &(DSMU_Filter0->FLTINTCLR);
    }
    else
    {
        pINTCLR = &(DSMU_Filterx->FLTINTCLR);
    }

    /* Clear the selected DSMU flags */
    *pINTCLR = (DSMU_FlagClear & DSMU_CLEAR_FLAG_ALL);
}

/**
*\*\name   DSMU_GetAwdFlagStatus.
*\*\fun    Checks whether the DSMU analog watchdog flag has set or not.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param   DSMU_AwdFlag :
*\*\          - DSMU_AWD_FLAG_HIGH_THRESHLOD_CH0
*\*\          - DSMU_AWD_FLAG_HIGH_THRESHLOD_CH1
*\*\          - DSMU_AWD_FLAG_HIGH_THRESHLOD_CH2
*\*\          - DSMU_AWD_FLAG_HIGH_THRESHLOD_CH3
*\*\          - DSMU_AWD_FLAG_HIGH_THRESHLOD_CH4
*\*\          - DSMU_AWD_FLAG_HIGH_THRESHLOD_CH5
*\*\          - DSMU_AWD_FLAG_HIGH_THRESHLOD_CH6
*\*\          - DSMU_AWD_FLAG_HIGH_THRESHLOD_CH7
*\*\          - DSMU_AWD_FLAG_LOW_THRESHOLD_CH0
*\*\          - DSMU_AWD_FLAG_LOW_THRESHOLD_CH1
*\*\          - DSMU_AWD_FLAG_LOW_THRESHOLD_CH2
*\*\          - DSMU_AWD_FLAG_LOW_THRESHOLD_CH3
*\*\          - DSMU_AWD_FLAG_LOW_THRESHOLD_CH4
*\*\          - DSMU_AWD_FLAG_LOW_THRESHOLD_CH5
*\*\          - DSMU_AWD_FLAG_LOW_THRESHOLD_CH6
*\*\          - DSMU_AWD_FLAG_LOW_THRESHOLD_CH7
*\*\return FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus DSMU_GetAwdFlagStatus(DSMU_Filter_Submodule* DSMU_Filterx,
                                 uint32_t DSMU_AwdFlag)
{
    FlagStatus bitstatus;

    if ((DSMU_Filterx->FLTAWDSTS & DSMU_AwdFlag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
*\*\name   DSMU_ClearAwdFlag.
*\*\fun    Clears analog watch dog flag of the specified DSMU.
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param   DSMU_AwdFlagClear :
*\*\          - DSMU_CLEAR_AWD_FLAG_HIGH_THRESHLOD_CH0
*\*\          - DSMU_CLEAR_AWD_FLAG_HIGH_THRESHLOD_CH1
*\*\          - DSMU_CLEAR_AWD_FLAG_HIGH_THRESHLOD_CH2
*\*\          - DSMU_CLEAR_AWD_FLAG_HIGH_THRESHLOD_CH3
*\*\          - DSMU_CLEAR_AWD_FLAG_HIGH_THRESHLOD_CH4
*\*\          - DSMU_CLEAR_AWD_FLAG_HIGH_THRESHLOD_CH5
*\*\          - DSMU_CLEAR_AWD_FLAG_HIGH_THRESHLOD_CH6
*\*\          - DSMU_CLEAR_AWD_FLAG_HIGH_THRESHLOD_CH7
*\*\          - DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH0
*\*\          - DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH1
*\*\          - DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH2
*\*\          - DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH3
*\*\          - DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH4
*\*\          - DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH5
*\*\          - DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH6
*\*\          - DSMU_CLEAR_AWD_FLAG_LOW_THRESHOLD_CH7
*\*\return    none.
**/
void DSMU_ClearAwdFlag(DSMU_Filter_Submodule* DSMU_Filterx, uint32_t DSMU_AwdFlagClear)
{
    /* Clear the selected DSMU watch dog flag */
    DSMU_Filterx->FLTAWDCLR = (DSMU_AwdFlagClear & DSMU_CLEAR_AWD_FLAG_ALL);
}

/**
*\*\name   DSMU_ConfigInt
*\*\fun    Enables or disables interrupt
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param   DSMU_Int:
*\*\          This parameter must be one of the following:
*\*\          - DSMU_INT_CLOCK_ABSENCE
*\*\          - DSMU_INT_SHORT_CIRCUIT
*\*\          - DSMU_INT_ANALOG_WATCHDOG
*\*\          - DSMU_INT_REGULAR_OVERRUN
*\*\          - DSMU_INT_INJECT_OVERRUN
*\*\          - DSMU_INT_REGULAR_END
*\*\          - DSMU_INT_INJECT_END
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note: DSMU_INT_CLOCK_ABSENCE and DSMU_INT_SHORT_CIRCUIT only exist in DSMU_Filter0->FLTCTRL2.
**/
void DSMU_ConfigInt(DSMU_Filter_Submodule* DSMU_Filterx,
                    uint32_t DSMU_Int, FunctionalState Cmd)
{
    __IO uint32_t *pCTRL2;

    if(DSMU_Int > DSMU_INT_ANALOG_WATCHDOG)
    {
        pCTRL2 = &(DSMU_Filter0->FLTCTRL2);
    }
    else
    {
        pCTRL2 = &(DSMU_Filterx->FLTCTRL2);
    }

    if (Cmd != DISABLE)
    {
        /* Enable the Interrupt sources */
        *pCTRL2 |= DSMU_Int;
    }
    else
    {
        /* Disable the Interrupt sources */
        *pCTRL2 &= (~DSMU_Int);
    }
}

/**
*\*\name    DSMU_ConfigRegChDMA
*\*\fun     Enables or disables regular channel DMA
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DSMU_ConfigRegChDMA(DSMU_Filter_Submodule* DSMU_Filterx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Interrupt sources */
        DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_RDMAEN;
    }
    else
    {
        /* Disable the Interrupt sources */
        DSMU_Filterx->FLTCTRL1 &= (~DSMU_FLTXCTRL1_RDMAEN);
    }
}

/**
*\*\name    DSMU_ConfigInjChDMA
*\*\fun     Enables or disables injected channel DMA
*\*\param  DSMU_Filterx
*\*\          - DSMU_Filter0
*\*\          - DSMU_Filter1
*\*\          - DSMU_Filter2
*\*\          - DSMU_Filter3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DSMU_ConfigInjChDMA(DSMU_Filter_Submodule* DSMU_Filterx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Interrupt sources */
        DSMU_Filterx->FLTCTRL1 |= DSMU_FLTXCTRL1_JDMAEN;
    }
    else
    {
        /* Disable the Interrupt sources */
        DSMU_Filterx->FLTCTRL1 &= (~DSMU_FLTXCTRL1_JDMAEN);
    }
}

/**
*\*\fun  This function allows to get the channel number from channel instance.
*\*\param  DSMU_Channely
*\*\          - DSMU_Channel0
*\*\          - DSMU_Channel1
*\*\          - DSMU_Channel2
*\*\          - DSMU_Channel3
*\*\          - DSMU_Channel4
*\*\          - DSMU_Channel5
*\*\          - DSMU_Channel6
*\*\          - DSMU_Channel7
*\*\return Channel number.
**/
static uint32_t DSMU_GetChannelNumber(const DSMU_Channel_Submodule* DSMU_Channely)
{
    uint32_t ChannelNum;

    /* Get channel from instance */
    if(DSMU_Channely == DSMU_Channel0)
    {
        ChannelNum = 0;
    }
    else if(DSMU_Channely == DSMU_Channel1)
    {
        ChannelNum = 1;
    }
    else if(DSMU_Channely == DSMU_Channel2)
    {
        ChannelNum = 2;
    }
    else if(DSMU_Channely == DSMU_Channel3)
    {
        ChannelNum = 3;
    }
    else if(DSMU_Channely == DSMU_Channel4)
    {
        ChannelNum = 4;
    }
    else if(DSMU_Channely == DSMU_Channel5)
    {
        ChannelNum = 5;
    }
    else if(DSMU_Channely == DSMU_Channel6)
    {
        ChannelNum = 6;
    }
    else /* DSMU_Channel7 */
    {
        ChannelNum = 7;
    }

    return ChannelNum;
}



