/**
 *  \file tsc_adc.c
 *
 *  \brief TOUCH SCREEN APIs.
 *
 *  This file contains the device abstraction layer APIs for
 *  Touch Screen. 
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "hw_types.h"
#include "tsc_adc.h"

/*************************************************************************
 		API FUNCTION DEFINITIONS
*************************************************************************/

/**
 * \brief   This API gets the revision information of the Touch Screen Module.
 *
 * \param   baseAdd	Base Address of the TouchScreen Module Registers.
 *
 * \return  returns the revision ID.
 *
 **/
unsigned int TSCADCGetRevision(unsigned int baseAdd)
{
    return (HWREG(baseAdd + TSC_ADC_SS_REVISION ));
}

/**
 * \brief   This API sets the idle mode of TSCADC Module.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   idleMode   idle mode to set.\n
 *
 *          idle mode can take following macros.\n
 *
 * 		       0 - TSCADC_FORCE_IDLE
 * 		       1 - TSCADC_NO_IDLE
 * 		       2 - TSCADC_SMART_IDLE
 * 		       3 - TSCADC_SMART_IDLE_WAKEUP
 *
 * \return  None 
 *
 **/
void TSCADCIdleModeSet(unsigned int baseAdd, unsigned int idleMode)
{
    HWREG(baseAdd + TSC_ADC_SS_SYSCONFIG) &= 
                                  ~TSC_ADC_SS_SYSCONFIG_IDLEMODE;

    HWREG(baseAdd + TSC_ADC_SS_SYSCONFIG) |= (idleMode <<
		                    TSC_ADC_SS_SYSCONFIG_IDLEMODE_SHIFT);
}

/**
 * \brief   This function asserts the specified interrupts.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   intFlag   It determines which interrupts needs to be asserted.\n
 *
 *          intFlag can take following macro values.\n
 *
 *          TSCADC_ASYNC_HW_PEN_EVENT_INT.\n
 *          TSCADC_SYNC_PEN_EVENT_INT.\n
 *          TSCADC_FIFO0_UNDER_FLOW_INT.\n
 *          TSCADC_FIFO1_UNDER_FLOW_INT.\n
 *          TSCADC_END_OF_SEQUENCE_INT.\n
 *          TSCADC_FIFO0_THRESHOLD_INT.\n
 *          TSCADC_FIFO1_THRESHOLD_INT.\n
 *          TSCADC_FIFO0_OVER_RUN_INT.\n
 *          TSCADC_FIFO1_OVER_RUN_INT.\n
 *          TSCADC_OUT_OF_RANGE_INT.\n
 *          TSCADC_PEN_UP_EVENT_INT.\n
 *
 * \return  None 
 *
 **/
void TSCADCRawIntStatusSet(unsigned int baseAdd, unsigned int intFlag)
{
    HWREG(baseAdd + TSC_ADC_SS_IRQSTATUS_RAW) |= intFlag;
}

/**
 * \brief   This API returns the required interrupt pending status.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   intFlag   It is status of the required interrupts to be read.\n
 *
 *          intFlag can take following macro values.\n
 *
 *          TSCADC_ASYNC_HW_PEN_EVENT_INT.\n
 *          TSCADC_SYNC_PEN_EVENT_INT.\n
 *          TSCADC_FIFO0_UNDER_FLOW_INT.\n
 *          TSCADC_FIFO1_UNDER_FLOW_INT.\n
 *          TSCADC_END_OF_SEQUENCE_INT.\n
 *          TSCADC_FIFO0_THRESHOLD_INT.\n
 *          TSCADC_FIFO1_THRESHOLD_INT.\n
 *          TSCADC_FIFO0_OVER_RUN_INT.\n
 *          TSCADC_FIFO1_OVER_RUN_INT.\n
 *          TSCADC_OUT_OF_RANGE_INT.\n
 *          TSCADC_PEN_UP_EVENT_INT.\n
 *
 * \return  Raw status of the specified interrupts. 
 *
 **/
unsigned int TSCADCRawIntStatusRead(unsigned int baseAdd, unsigned int intFlag)
{
    return ((HWREG(baseAdd + TSC_ADC_SS_IRQSTATUS_RAW) & intFlag));
}

/**
 * \brief   This API returns the pending interrupt status.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 *
 **/
unsigned int TSCADCRawIntStatus(unsigned int baseAdd)
{
    return ((HWREG(baseAdd + TSC_ADC_SS_IRQSTATUS_RAW)));
}

/**
 * \brief   This API clears the status of the specified interrupts.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   intFlag   It determines which interrupts status need to be
 *                    cleared.\n
 *
 *          intFlag can take following macro values.\n
 *
 *          TSCADC_ASYNC_HW_PEN_EVENT_INT.\n
 *          TSCADC_SYNC_PEN_EVENT_INT.\n
 *          TSCADC_FIFO0_UNDER_FLOW_INT.\n
 *          TSCADC_FIFO1_UNDER_FLOW_INT.\n
 *          TSCADC_END_OF_SEQUENCE_INT.\n
 *          TSCADC_FIFO0_THRESHOLD_INT.\n
 *          TSCADC_FIFO1_THRESHOLD_INT.\n
 *          TSCADC_FIFO0_OVER_RUN_INT.\n
 *          TSCADC_FIFO1_OVER_RUN_INT.\n
 *          TSCADC_OUT_OF_RANGE_INT.\n
 *          TSCADC_PEN_UP_EVENT_INT.\n
 *
 * \return  None 
 *
 **/
void TSCADCIntStatusClear(unsigned int baseAdd, unsigned int intFlag)
{
    HWREG(baseAdd + TSC_ADC_SS_IRQSTATUS) =  intFlag;
}

/**
 * \brief   This API returns the status of the specified interrupts.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   intFlag   It specifies the interrupts whose status needs to
 *                    returned.
 *
 *          intFlag can take following macro values.\n
 *
 *          TSCADC_ASYNC_HW_PEN_EVENT_INT.\n
 *          TSCADC_SYNC_PEN_EVENT_INT.\n
 *          TSCADC_FIFO0_UNDER_FLOW_INT.\n
 *          TSCADC_FIFO1_UNDER_FLOW_INT.\n
 *          TSCADC_END_OF_SEQUENCE_INT.\n
 *          TSCADC_FIFO0_THRESHOLD_INT.\n
 *          TSCADC_FIFO1_THRESHOLD_INT.\n
 *          TSCADC_FIFO0_OVER_RUN_INT.\n
 *          TSCADC_FIFO1_OVER_RUN_INT.\n
 *          TSCADC_OUT_OF_RANGE_INT.\n
 *          TSCADC_PEN_UP_EVENT_INT.\n
 *          
 * \return  The interrupt status of specified interrupts. 
 *
 **/
unsigned int TSCADCIntStatusRead(unsigned int baseAdd, unsigned int intFlag)
{
    return ((HWREG(baseAdd + TSC_ADC_SS_IRQSTATUS) & intFlag));
}

/**
 * \brief   This API returns the interrupt status.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 *
 * \return  The status of the interrupts.
 *
 **/
unsigned int TSCADCIntStatus(unsigned int baseAdd)
{
    return (HWREG(baseAdd + TSC_ADC_SS_IRQSTATUS));
}

/**
 * \brief   This API enables the interrupt for the given event.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   event      event for which the interrupt to be enabled.
 *
 *          event can take following macro values.\n
 *
 *          TSCADC_ASYNC_HW_PEN_EVENT_INT.\n
 *          TSCADC_SYNC_PEN_EVENT_INT.\n
 *          TSCADC_FIFO0_UNDER_FLOW_INT.\n
 *          TSCADC_FIFO1_UNDER_FLOW_INT.\n
 *          TSCADC_END_OF_SEQUENCE_INT.\n
 *          TSCADC_FIFO0_THRESHOLD_INT.\n
 *          TSCADC_FIFO1_THRESHOLD_INT.\n
 *          TSCADC_FIFO0_OVER_RUN_INT.\n
 *          TSCADC_FIFO1_OVER_RUN_INT.\n
 *          TSCADC_OUT_OF_RANGE_INT.\n
 *          TSCADC_PEN_UP_EVENT_INT.\n
 *
 * \return  None 
 *
 **/
void TSCADCEventInterruptEnable(unsigned int baseAdd, unsigned int event)
{
    HWREG(baseAdd + TSC_ADC_SS_IRQENABLE_SET) |= event;
}

/**
 * \brief   This API disables the interrupt for the given event.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   event      Event for which the interrupt to be disabled.
 *
 *          event can take following macro values.\n
 *
 *          TSCADC_ASYNC_HW_PEN_EVENT_INT.\n
 *          TSCADC_SYNC_PEN_EVENT_INT.\n
 *          TSCADC_FIFO0_UNDER_FLOW_INT.\n
 *          TSCADC_FIFO1_UNDER_FLOW_INT.\n
 *          TSCADC_END_OF_SEQUENCE_INT.\n
 *          TSCADC_FIFO0_THRESHOLD_INT.\n
 *          TSCADC_FIFO1_THRESHOLD_INT.\n
 *          TSCADC_FIFO0_OVER_RUN_INT.\n
 *          TSCADC_FIFO1_OVER_RUN_INT.\n
 *          TSCADC_OUT_OF_RANGE_INT.\n
 *          TSCADC_PEN_UP_EVENT_INT.\n
 *
 * \return  None 
 *
 **/
void TSCADCEventInterruptDisable(unsigned int baseAdd, unsigned int event)
{
    HWREG(baseAdd + TSC_ADC_SS_IRQENABLE_CLR) = event;
}

/**
 * \brief   This API enables/disables the Wake Up Generation for HW Pen event.
 * 	    Enabling the Wake Up Generation shall generate an asynchronous 
 * 	    Wake UP using the SWAKEup Protocol if it detects a touch
 * 	    even if the Module and the clocks are off.
 *
 * \param   baseAdd       Base Address of the TouchScreen Module Registers.
 * \param   enableWakeUp    Whether Wake Up Generation for HW Pen Event
 * 			   is to be enabled.\n
 *
 *          enableWakeUp can take following values.\n
 *
 *           TSCADC_WAKEUP_DISABLE - Wakeup is disabled.\n
 *           TSCADC_WAKEUP_ENABLE  - Wakeup is enabled .\n
 *
 * \return  None 
 *
 **/
void TSCADCWakeUpPenEventConfig(unsigned int baseAdd, unsigned int enableWakeUp)
{
    HWREG(baseAdd + TSC_ADC_SS_IRQWAKEUP) = enableWakeUp;
}

/**
 * \brief   This API enables the DMA for the given FIFO.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   fifoSel    FIFO for which the DMA to be enabled.\n
 *
 *          fifoSel can take following macros.\n
 *
 *          TSCADC_FIFO_0.\n
 *          TSCADC_FIFO_1.\n 
 *
 * \return  None 
 *
 **/
void TSCADCDMAFIFOEnable(unsigned int baseAdd, unsigned char fifoSel)
{
    HWREG(baseAdd + TSC_ADC_SS_DMAENABLE_SET) |= 0x1 << fifoSel;
}

/**
 * \brief   This API Disables the DMA for the given FIFO.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   fifoSel    FIFO for which the DMA to be Disabled.
 *
 *          fifoSel can take following macros.\n
 *
 *          TSCADC_FIFO_0.\n
 *          TSCADC_FIFO_1.\n 
 *
 * \return  None 
 *
 **/
void TSCADCDMAFIFODisable(unsigned int baseAdd, unsigned char fifoSel)
{
    HWREG(baseAdd + TSC_ADC_SS_DMAENABLE_CLR) |= 0x1 << fifoSel;
}

/**
 * \brief   This API reads the DMA enable status for the given FIFO.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   fifoSel    FIFO for which the DMA status to be read.
 *
 *          fifoSel can take following values.\n
 *
 *          TSCADC_FIFO_0.\n
 *          TSCADC_FIFO_1.\n 
 *
 * \return  returns the DMA Enable Status
 * 	    TRUE - Enabled
 * 	    FALSE - Disabled
 *
 **/
unsigned int TSCADCIsDMAFIFOEnabled(unsigned int baseAdd, unsigned int fifoSel)
{
    return ((HWREG(baseAdd + TSC_ADC_SS_DMAENABLE_SET) >> fifoSel) & 0x1);
}

/**
 * \brief   This API enables/disables the HW event preemption.
 *
 * \param   baseAdd 	   	   Base Address of the TouchScreen Module
 * 				   Registers.
 * \param   enableHWEventPreempt   whether Hardware Event Preemption is to
 * 				   be enabled.
 *
 *          enableHWEventPreempt can take following macros.\n
 * 
 *          0 - Preemption is disabled.\n
 *          1 - Preemption is Enabled.\n
 *
 * \return  None 
 *
 **/
void TSCADCConfigHWEventPrempt(unsigned int baseAdd, unsigned int enableHWEventPreempt)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) &= 
                             ~TSC_ADC_SS_CTRL_HW_EVENT_MAPPING;

    HWREG(baseAdd + TSC_ADC_SS_CTRL) |= enableHWEventPreempt <<
	                      TSC_ADC_SS_CTRL_HW_EVENT_MAPPING_SHIFT;
}

/**
 * \brief   This API maps the HW event to Pen Touch or Hardware Event Input
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   hwEvent   Input Event to which the HW event is to be mapped. Possible
 * 		      Events are.\n
 *
 *          hwEvent can take following macros.\n
 * 
 *          TSCADC_HW_INPUT_EVENT.\n
 *          TSCADC_PEN_TOUCH.\n
 *
 * \return  None 
 *
 **/
void TSCADCHWEventMapSet(unsigned int baseAdd, unsigned int hwEvent)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) &= ~TSC_ADC_SS_CTRL_HW_EVENT_MAPPING;
    HWREG(baseAdd + TSC_ADC_SS_CTRL) |=  hwEvent << 
                                   TSC_ADC_SS_CTRL_HW_EVENT_MAPPING_SHIFT;
}

/**
 * \brief   This API Enables/Disables the Touch Screen Transistors
 *
 * \param   baseAdd             Base Address of the TouchScreen Module Registers.
 * \param   enableTSTransistor   whether the Touch Screen Transistors are to be
 * 			         Enabled.\n
 *
 *          enableTSTransistor can take following values.\n
 *
 *          TSCADC_TRANSISTOR_DISABLE - Disables the transistor.\n
 *          TSCADC_TRANSISTOR_ENABLE  - Enables the transistor.\n
 *
 * \return  None 
 *
 **/
void TSCADCTSTransistorConfig(unsigned int baseAdd, unsigned int enableTSTransistor)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) &= ~TSC_ADC_SS_CTRL_TOUCH_SCREEN_ENABLE;

    HWREG(baseAdd + TSC_ADC_SS_CTRL) |= enableTSTransistor <<
                                   TSC_ADC_SS_CTRL_TOUCH_SCREEN_ENABLE_SHIFT;
}

/**
 * \brief   This API configures the Touch Screen for 4 Wire/5 Wire mode
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   tsMode     Selects the TS mode to be configured.\n
 *
 *          tsMode can take following macros.\n
 *
 *          TSCADC_FOUR_WIRE_MODE.\n
 *          TSCADC_FIVE_WIRE_MODE.\n
 *          TSCADC_GENERAL_PURPOSE_MODE.\n
 *
 * \return  None 
 *
 **/
void TSCADCTSModeConfig(unsigned int baseAdd, unsigned int tsMode)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) &= ~TSC_ADC_SS_CTRL_AFE_PEN_CTRL;

    HWREG(baseAdd + TSC_ADC_SS_CTRL) |= tsMode << 
                                   TSC_ADC_SS_CTRL_AFE_PEN_CTRL_SHIFT;
}

/**
 * \brief   This API sets the ADC Power Down
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 *
 * \return  None 
 *
 **/
void TSCADCSetADCPowerDown(unsigned int baseAdd)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) &= ~TSC_ADC_SS_CTRL_POWER_DOWN;
    HWREG(baseAdd + TSC_ADC_SS_CTRL) |= TSC_ADC_SS_CTRL_POWER_DOWN_AFEPOWERDOWN << \
										TSC_ADC_SS_CTRL_POWER_DOWN_SHIFT;
}

/**
 * \brief   This API sets the ADC Power Up
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 *
 * \return  None 
 *
 **/
void TSCADCSetADCPowerUp(unsigned int baseAdd)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) &= ~TSC_ADC_SS_CTRL_POWER_DOWN;
}

/**
 * \brief   This API select the ADC BIAS for the AFE
 *
 * \param   baseAdd     Base Address of the TouchScreen Module Registers.
 * \param   adcBiasSel   Select internal or external ADC Bias.
 *    
 *          adcBiasSel can take following values.\n
 *            
 *	    TSCADC_INTERNAL_AC_BIAS - Internal ac bias.\n
 *	    TSCADC_EXTERNAL_AC_BIAS - External ac bias.\n
 * \return  None 
 *
 **/
void TSCADCBiasConfig(unsigned int baseAdd, unsigned int adcBiasSel)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) &= ~TSC_ADC_SS_CTRL_ADC_BIAS_SELECT;
    HWREG(baseAdd + TSC_ADC_SS_CTRL) |= adcBiasSel << 
                                   TSC_ADC_SS_CTRL_ADC_BIAS_SELECT_SHIFT;
}

/**
 * \brief   This API enables the protection of Step Config Registers. 
 *
 * \param   baseAdd    Base Address of the TouchScreen Module Registers.
 *
 * \return  None 
 *
 **/
void TSCADCStepConfigProtectionEnable(unsigned int baseAdd)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) &=
                              ~TSC_ADC_SS_CTRL_STEPCONFIG_WRITEPROTECT_N;
}

/**
 * \brief   This API disables the protection of Step Config Registers. 
 *
 * \param   baseAdd    Base Address of the TouchScreen Module Registers.
 *
 * \return  None 
 *
 **/
void TSCADCStepConfigProtectionDisable(unsigned int baseAdd)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) |= 
                      TSC_ADC_SS_CTRL_STEPCONFIG_WRITEPROTECT_N;
}

/**
 * \brief   This API enables/disables the channel ID store along with the
 * 	     captured ADC data 
 *
 * \param   baseAdd	      Base Address of the TouchScreen Module Registers.
 * \param   enableStepIDTag   Whether or not step ID is to be stored.
 *
 * \return  None 
 *
 **/
void TSCADCStepIDTagConfig(unsigned int baseAdd, unsigned int enableStepIDTag)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) &= ~TSC_ADC_SS_CTRL_STERP_ID_TAG;
    HWREG(baseAdd + TSC_ADC_SS_CTRL) |= enableStepIDTag <<
	                                 TSC_ADC_SS_CTRL_STERP_ID_TAG_SHIFT;
}

/**
 * \brief   This API Enables/Disables the TSCADC Module 
 *
 * \param   baseAdd       Base Address of the TouchScreen Module Registers.
 * \param   enableModule   Whether the module is to be enabled.
 *
 *          enableModule can take following values.\n
 *
 *          TSCADC_MODULE_DISABLE - Disables  module.\n
 *          TSCADC_MODULE_ENABLE  - Enables the module.\n
 *
 * \return  None 
 *
 **/
void TSCADCModuleStateSet(unsigned int baseAdd, unsigned int enableModule)
{
    HWREG(baseAdd + TSC_ADC_SS_CTRL) &= ~TSC_ADC_SS_CTRL_ENABLE;
    HWREG(baseAdd + TSC_ADC_SS_CTRL) |= enableModule;
}

/**
 * \brief   This API reads the PEN_IRQ Status of the Sequencer 
 *
 * \param   baseAdd    Base Address of the TouchScreen Module Registers.
 * \param   penIRQSel   Penirq for which the status is to be read.
 *
 *          penIRQSel can take following macros.\n
 *
 *          TSCADC_PEN_IRQ_0.\n
 *          TSCADC_PEN_IRQ_1.\n
 *
 * \return  returns the IRQ status 
 *
 **/
unsigned int TSCADCSequencerPenIrqStatusRead(unsigned int baseAdd, 
                                          unsigned int penIRQSel)
{
    if (TSCADC_PEN_IRQ_0 == penIRQSel) 
    {
         return ((HWREG(baseAdd + TSC_ADC_SS_ADCSTAT) &
		   TSC_ADC_SS_ADCSTAT_PEN_IRQ0) 
                  >>  TSC_ADC_SS_ADCSTAT_PEN_IRQ0_SHIFT);
    } 
    else 
    {    
         return ((HWREG(baseAdd + TSC_ADC_SS_ADCSTAT) &
		   TSC_ADC_SS_ADCSTAT_PEN_IRQ1) 
                  >>  TSC_ADC_SS_ADCSTAT_PEN_IRQ1_SHIFT);
    }
}

/**
 * \brief   This API reads the Sequencer Busy Status 
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 *
 * \return  returns the Sequencer Status 
 *
 **/
unsigned int TSCADCSequencerFSMBusyStatus(unsigned int baseAdd)
{
    return ((HWREG(baseAdd + TSC_ADC_SS_ADCSTAT) & 
              TSC_ADC_SS_ADCSTAT_FSM_BUSY ) >>
	      TSC_ADC_SS_ADCSTAT_FSM_BUSY_SHIFT);
}

/**
 * \brief   This API reads the STEP ID currently being executed by
 * 	    the sequencer 
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 *
 * \return  returns the Step ID  
 *
 **/
unsigned int TSCADCSequencerCurrentStepID(unsigned int baseAdd)
{
    return (HWREG(baseAdd +  TSC_ADC_SS_ADCSTAT) & TSC_ADC_SS_ADCSTAT_STEPID);
}

/**
 * \brief   This API sets the Minimum amd Maximum values for ADC output data
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   lowVal     Minimum threshold value for ADC Output.
 * \param   highVal    Maximum threshold value for ADC output.
 *
 * \return  none  
 *
 **/
void TSCADCOutputRangeConfig(unsigned int baseAdd, unsigned short lowVal,
	                     unsigned short highVal)
{
    HWREG(baseAdd + TSC_ADC_SS_ADCRANGE) &= 
                        ~TSC_ADC_SS_ADCRANGE_LOW_RANGE_DATA;

    HWREG(baseAdd + TSC_ADC_SS_ADCRANGE) |= lowVal;

    HWREG(baseAdd + TSC_ADC_SS_ADCRANGE) &= 
                        ~TSC_ADC_SS_ADCRANGE_HIGH_RANGE_DATA;

    HWREG(baseAdd + TSC_ADC_SS_ADCRANGE) |= highVal <<
	               TSC_ADC_SS_ADCRANGE_HIGH_RANGE_DATA_SHIFT;
}

/**
 * \brief   This API sets the AFE clock 
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   clkDiv     Divider Value.
 *
 * \return  none  
 *
 **/
void TSCADCConfigureAFEClock(unsigned int baseAdd, unsigned int moduleClk,
                          unsigned int inputClk)
{
    unsigned int clkDiv;
    
    clkDiv = moduleClk / inputClk;    

    HWREG(baseAdd + TSC_ADC_SS_ADC_CLKDIV) &=
                        ~TSC_ADC_SS_ADC_CLKDIV_ADC_CLK_DIV;

    HWREG(baseAdd + TSC_ADC_SS_ADC_CLKDIV) = (clkDiv - 1);
}

/**
 * \brief   This API Controls spare in values sent to AFE and captures spare out
 * 	     from AFE 
 *
 * \param   baseAdd         Base Address of the TouchScreen Module Registers.
 * \param   spareOutputVal   Spare Output Pins.
 * \param   spareInputVal    Spare Input Pins.
 *
 * \return  none  
 *
 **/
void TSCADCConfigureMisc(unsigned int baseAdd, unsigned char spareInputVal,
		      unsigned char spareOutputVal)
{
    HWREG(baseAdd + TSC_ADC_SS_ADC_MISC) &=
                          ~TSC_ADC_SS_ADC_MISC_AFE_SPARE_INPUT;
 
    HWREG(baseAdd + TSC_ADC_SS_ADC_MISC) |= spareInputVal;

    HWREG(baseAdd + TSC_ADC_SS_ADC_MISC) &=
                           ~TSC_ADC_SS_ADC_MISC_AFE_SPARE_OUTPUT;
                              
    HWREG(baseAdd + TSC_ADC_SS_ADC_MISC) |= spareOutputVal <<
	                    TSC_ADC_SS_ADC_MISC_AFE_SPARE_OUTPUT_SHIFT;
}

/**
 * \brief   This API Enables/Disables the given step. 
 *
 * \param   baseAdd     Base Address of the TouchScreen Module Registers.
 * \param   stepEn_Dis   Enables/Disables the Step.\n
 *            
 *          stepEn_Dis can take '0' or '1'
 *
 *          0 - Disables the step.\n
 *          1 - Enables the step.\n  
 *           
 * \param   stepSel      Select the step.\n
 *
 *          stepSel can take any value bteween 1 to 16.\n
 *
 * \return  none  
 *
 **/
void TSCADCConfigureStepEnable(unsigned int baseAdd, unsigned int stepSel,
	                    unsigned int stepEn_Dis)
{
    HWREG(baseAdd + TSC_ADC_SS_STEPENABLE) &= ~(1 << stepSel);
    HWREG(baseAdd + TSC_ADC_SS_STEPENABLE) |= stepEn_Dis << stepSel;
}

/**
 * \brief   This API configures ADC to single ended or differential operation
 *          mode. 
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   mode       It is the value which determines whether to
 *                     configure ADC to single ended or differential
 *                     operation mode.
 *
 *          mode can take following macros.
 *
 *          TSCADC_ADC_SINGLE_ENDED_OPER_MODE.\n
 *          TSCADC_ADC_DIFFERENTIAL_OPER_MODE.\n  
 * 
 * \return  none  
 *
 **/
void TSCADCIdleStepOperationModeControl(unsigned int baseAdd, unsigned int mode)
{
    if(mode)
    {
         HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= 
                             TSC_ADC_SS_IDLECONFIG_DIFF_CNTRL;
    }
    else
    {
         HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= 
                           ~TSC_ADC_SS_IDLECONFIG_DIFF_CNTRL;
    }
}

/**
 * \brief   This API configure the reference volatage and Input to Idle Step 
 *
 * \param   baseAdd	 	Base Address of the TouchScreen Module Registers.
 * \param   adcNegativeRef	Selects the ADC Negative Reference Voltage.\n
 *
 *          adcNegativeRef can take following values.\n
 *
 *           TSCADC_NEGATIVE_REF_VSSA.\n                
 *           TSCADC_NEGATIVE_REF_XNUR.\n                
 *           TSCADC_NEGATIVE_REF_YNLR.\n                
 *           TSCADC_NEGATIVE_REF_ADCREFM.\n                
 *  
 * \param   adcPositiveInput 	Selects the Positive Analog Input Source.\n
 *
 *           adcPositiveInput can take following values.\n   
 *
 *           TSCADC_POSITIVE_INP_CHANNEL1.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL2.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL3.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL4.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL5.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL6.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL7.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL8.\n
 *           TSCADC_POSITIVE_INP_ADCREFM.\n
 *            
 * \param   adcNegativeInput 	Selects the Negative Analog Input Source.\n
 *
 *          adcNegativeInput can take following values.\n
 *
 *          TSCADC_NEGATIVE_INP_CHANNEL1.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL2.\n           
 *          TSCADC_NEGATIVE_INP_CHANNEL3.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL4.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL5.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL6.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL8.\n            
 *          TSCADC_NEGATIVE_INP_ADCREFRM.\n
 *            
 * \param   adcPositiveRef 	Selects the ADC Positive Reference Voltage.\n
 *
 *          adcPositiveRef can take following values.\n
 *
 *          TSCADC_POSITIVE_REF_VDDA.\n                
 *          TSCADC_POSITIVE_REF_XNUR.\n                
 *          TSCADC_POSITIVE_REF_YNLR.\n                
 *          TSCADC_POSITIVE_REF_ADCREFP.\n
 *
 * \return  none  
 *
 **/
void TSCADCIdleStepConfig(unsigned int baseAdd, unsigned int adcNegativeRef,
                       unsigned int adcPositiveInp, unsigned int adcNegativeInp, 
                       unsigned int adcPositiveRef)
{

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= 
                          ~TSC_ADC_SS_IDLECONFIG_SEL_RFM_SWC;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= adcNegativeRef <<
	                   TSC_ADC_SS_IDLECONFIG_SEL_RFM_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= ~TSC_ADC_SS_IDLECONFIG_SEL_INP_SWC;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= adcPositiveInp <<
	                   TSC_ADC_SS_IDLECONFIG_SEL_INP_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= 
                          ~TSC_ADC_SS_IDLECONFIG_SEL_INM_SWM;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= adcNegativeInp <<
	                   TSC_ADC_SS_IDLECONFIG_SEL_INM_SWM_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= 
                          ~TSC_ADC_SS_IDLECONFIG_SEL_RFP_SWC;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= adcPositiveRef <<
	                   TSC_ADC_SS_IDLECONFIG_SEL_RFP_SWC_SHIFT;
}

/**
 * \brief   This API configure the Idle Step Transistor Biasing for
 *          xnpsw,xppsw and yppsw pins through which analog supply
 *          is provided to the touch screen. 
 *
 * \param   baseAdd 	Base Address of the TouchScreen Module Registers.
 * \param   xnpsw 	XNPSW pin SW configuration.\n
 *
 *          xnpsw can take following values.\n
 *
 *          TSCADC_XPPSW_PIN_ON.\n
 *          TSCADC_XPPSW_PIN_OFF.\n                                          
 *
 * \param   xnpsw 	YPPSW pin SW configuration.\n
 *
 *          yppsw can take following values.\n
 *
 *          TSCADC_XNPSW_PIN_ON.\n
 *          TSCADC_XNPSW_PIN_OFF.\n
 *                     
 * \param   yppsw 	YPPSW pin SW configuration.\n
 *
 *          xppsw can take following values.\n
 *
 *          TSCADC_YPPSW_PIN_ON.\n
 *          TSCADC_YPPSW_PIN_OFF.\n                     
 *
 * \return  none  
 *
 **/
void TSCADCIdleStepAnalogSupplyConfig(unsigned int baseAdd, unsigned int xppsw,
                                   unsigned int xnpsw, unsigned int yppsw)
{
    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= ~TSC_ADC_SS_IDLECONFIG_XPPSW_SWC;
    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= ~TSC_ADC_SS_IDLECONFIG_XNPSW_SWC;
    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= ~TSC_ADC_SS_IDLECONFIG_YPPSW_SWC;
		  
    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= xppsw << 
                                TSC_ADC_SS_IDLECONFIG_XPPSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= xnpsw << 
                                TSC_ADC_SS_IDLECONFIG_XNPSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= yppsw << 
                                TSC_ADC_SS_IDLECONFIG_YPPSW_SWC_SHIFT;
}


/**
 * \brief   This API configure the Idle Step Transistor Biasing for
 *          xnnsw, ypnsw, ynnsw and wpnsw pins through which analog ground
 *          is provided to the touch screen. 
 *
 * \param   baseAdd 	Base Address of the TouchScreen Module Registers.
 * \param   xnnsw 	XNNSW pin SW configuration.\n
 *           
 *          xnnsw can take following values.\n
 *
 *          TSCADC_XNNSW_PIN_ON.\n
 *          TSCADC_XNNSW_PIN_OFF.\n                                        
 *
 * \param   ypnsw 	YPNSW pin SW configuration.\n
 *
 *           ypnsw can take following values.\n
 *
 *           TSCADC_YPNSW_PIN_ON.\n
 *           TSCADC_YPNSW_PIN_OFF.\n
 *
 * \param   ynnsw 	YNNSW pin SW configuration.\n
 *
 *          ynnsw can take following values.\n
 *
 *          TSCADC_YNNSW_PIN_ON.\n
 *          TSCADC_YNNSW_PIN_OFF.\n
 *                     
 * \param   wpnsw 	WPNSW pin SW configuration.\n
 *          
 *          wpnsw can take following values.\n
 *
 *          TSCADC_WPNSW_PIN_ON.\n
 *          TSCADC_WPNSW_PIN_OFF.\n                      
 *
 * \return  none  
 *
 **/
void TSCADCIdleStepAnalogGroundConfig(unsigned int baseAdd, unsigned int xnnsw,
                                   unsigned int ypnsw, unsigned int ynnsw,
                                   unsigned int wpnsw)
{
    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= ~TSC_ADC_SS_IDLECONFIG_XNNSW_SWC;
    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= ~TSC_ADC_SS_IDLECONFIG_YPNSW_SWC;
    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= ~TSC_ADC_SS_IDLECONFIG_YNNSW_SWC;
    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) &= ~TSC_ADC_SS_IDLECONFIG_WPNSW_SWC;
		  
    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= xnnsw << 
                                TSC_ADC_SS_IDLECONFIG_XNNSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= ypnsw << 
                                TSC_ADC_SS_IDLECONFIG_YPNSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= ynnsw << 
                                TSC_ADC_SS_IDLECONFIG_YNNSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_IDLECONFIG) |= wpnsw << 
                                TSC_ADC_SS_IDLECONFIG_WPNSW_SWC_SHIFT;
}


/**
 * \brief   This API configures ADC to single ended or differential operation
 *          mode. 
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   mode      It is the value which determines whether to
 *                    configure ADC to single ended or differential
 *                    operation mode.
 *
 *          mode can take following macros.
 *
 *          TSCADC_ADC_SINGLE_ENDED_OPER_MODE.\n
 *          TSCADC_ADC_DIFFERENTIAL_OPER_MODE.\n  
 * 
 * \return  none  
 *
 **/
void TSCADCChargeStepOperationModeControl(unsigned int baseAdd, unsigned int mode)
{
    if(mode)
    {
         HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= 
                           TSC_ADC_SS_TS_CHARGE_STEPCONFIG_DIFF_CNTRL;
    }
    else
    {
         HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                          ~TSC_ADC_SS_TS_CHARGE_STEPCONFIG_DIFF_CNTRL;
    }
}


/**
 * \brief  This API configures the Touch Screen ChargeStep 
 *
 * \param   baseAdd	 	Base Address of the TouchScreen Module Registers.
 * \param   adcNegativeRef	Selects the ADC Negative Reference Voltage.\n
 *
 *          adcNegativeRef can take following values.\n
 *
 *           TSCADC_NEGATIVE_REF_VSSA.\n                
 *           TSCADC_NEGATIVE_REF_XNUR.\n                
 *           TSCADC_NEGATIVE_REF_YNLR.\n                
 *           TSCADC_NEGATIVE_REF_ADCREFM.\n                
 *  
 * \param   adcPositiveInput 	Selects the Positive Analog Input Source.\n
 *
 *           adcPositiveInput can take following values.\n   
 *
 *           TSCADC_POSITIVE_INP_CHANNEL1.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL2.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL3.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL4.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL5.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL6.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL7.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL8.\n
 *           TSCADC_POSITIVE_INP_ADCREFM.\n
 *            
 * \param   adcNegativeInput 	Selects the Negative Analog Input Source.\n
 *
 *          adcNegativeInput can take following values.\n
 *
 *          TSCADC_NEGATIVE_INP_CHANNEL1.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL2.\n           
 *          TSCADC_NEGATIVE_INP_CHANNEL3.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL4.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL5.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL6.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL8.\n            
 *          TSCADC_NEGATIVE_INP_ADCREFRM.\n
 *            
 * \param   adcPositiveRef 	Selects the ADC Positive Reference Voltage.\n
 *
 *          adcPositiveRef can take following values.\n
 *
 *          TSCADC_POSITIVE_REF_VDDA.\n                
 *          TSCADC_POSITIVE_REF_XPUL.\n                
 *          TSCADC_POSITIVE_REF_YPLL.\n                
 *          TSCADC_POSITIVE_REF_ADCREFP.\n
 * 
 * \return  none  
 *
 **/
void TSCADCChargeStepConfig(unsigned int baseAdd, unsigned int adcNegativeRef,
                         unsigned int adcPositiveInp,unsigned int adcNegativeInp,
                         unsigned int adcPositiveRef)
{
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                         ~TSC_ADC_SS_TS_CHARGE_STEPCONFIG_SEL_RFM_SWC;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= adcNegativeRef <<
		         TSC_ADC_SS_TS_CHARGE_STEPCONFIG_SEL_RFM_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                         ~TSC_ADC_SS_TS_CHARGE_STEPCONFIG_SEL_INP_SWC;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= adcPositiveInp <<
		         TSC_ADC_SS_TS_CHARGE_STEPCONFIG_SEL_INP_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                        ~TSC_ADC_SS_TS_CHARGE_STEPCONFIG_SEL_INM_SWM;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= adcNegativeInp <<
		         TSC_ADC_SS_TS_CHARGE_STEPCONFIG_SEL_INM_SWM_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                         ~TSC_ADC_SS_TS_CHARGE_STEPCONFIG_SEL_RFP_SWC;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= adcPositiveRef <<
		         TSC_ADC_SS_TS_CHARGE_STEPCONFIG_SEL_RFP_SWC_SHIFT;
}

/**
 * \brief   This API configure the TouchScreen ChargeStep Transistor Biasing for
 *          xnpsw,xppsw and yppsw pins through which analog supply
 *          is provided to the touch screen. 
 *
 * \param   baseAdd 	Base Address of the TouchScreen Module Registers.
 * \param   xnpsw 	XNPSW pin SW configuration.\n
 *
 *          xnpsw can take following values.\n
 *
 *          TSCADC_XPPSW_PIN_ON.\n
 *          TSCADC_XPPSW_PIN_OFF.\n                                          
 *
 * \param   xnppsw 	XNPSW pin SW configuration.\n
 *
 *          xnpsw can take following values.\n
 *
 *          TSCADC_XNPSW_PIN_ON.\n
 *          TSCADC_XNPSW_PIN_OFF.\n
 *                     
 * \param   yppsw 	YPPSW pin SW configuration.\n
 *
 *          yppsw can take following values.\n
 *
 *          TSCADC_YPPSW_PIN_ON.\n
 *          TSCADC_YPPSW_PIN_OFF.\n                     
 *
 * \return  none 
 *
 **/
void TSCADCChargeStepAnalogSupplyConfig(unsigned int baseAdd, unsigned int xppsw,
                                     unsigned int xnpsw, unsigned int yppsw)
{
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                             ~ TSC_ADC_SS_TS_CHARGE_STEPCONFIG_XPPSW_SWC;
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                             ~ TSC_ADC_SS_TS_CHARGE_STEPCONFIG_XNPSW_SWC;
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                             ~ TSC_ADC_SS_TS_CHARGE_STEPCONFIG_YPPSW_SWC;
		  
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= xppsw << 
                                TSC_ADC_SS_TS_CHARGE_STEPCONFIG_XPPSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= xnpsw << 
                                TSC_ADC_SS_TS_CHARGE_STEPCONFIG_XNPSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= yppsw << 
                                TSC_ADC_SS_TS_CHARGE_STEPCONFIG_YPPSW_SWC_SHIFT;
}

/**
 * \brief   This API configure the TouchScreen ChargeStep Transistor Biasing for
 *          xnnsw, ypnsw, ynnsw and wpnsw pins through which analog ground
 *          is provided to the touch screen. 
 *
 * \param   baseAdd 	Base Address of the TouchScreen Module Registers.
 * \param   xnnsw 	XNNSW pin SW configuration.\n
 *           
 *          xnnsw can take following values.\n
 *
 *          TSCADC_XNNSW_PIN_ON.\n
 *          TSCADC_XNNSW_PIN_OFF.\n                                        
 *
 * \param   ypnsw 	YPNSW pin SW configuration.\n
 *
 *          ypnsw can take following values.\n
 *
 *          TSCADC_YPNSW_PIN_ON.\n
 *          TSCADC_YPNSW_PIN_OFF.\n
 *
 * \param   ynnsw 	YNNSW pin SW configuration.\n
 *
 *          ynnsw can take following values.\n
 *
 *          TSCADC_YNNSW_PIN_ON.\n
 *          TSCADC_YNNSW_PIN_OFF.\n
 *                     
 * \param   wpnsw 	WPNSW pin SW configuration.\n
 *          
 *          wpnsw can take following values.\n
 *
 *          TSCADC_WPNSW_PIN_ON.\n
 *          TSCADC_WPNSW_PIN_OFF.\n                      
 *
 * \return  none  
 *
 **/
void TSCADCChargeStepAnalogGroundConfig(unsigned int baseAdd, unsigned int xnnsw,
                                     unsigned int ypnsw, unsigned int ynnsw,
                                     unsigned int wpnsw)
{
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                           ~TSC_ADC_SS_TS_CHARGE_STEPCONFIG_XNNSW_SWC;
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                           ~TSC_ADC_SS_TS_CHARGE_STEPCONFIG_YPNSW_SWC;
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                           ~TSC_ADC_SS_TS_CHARGE_STEPCONFIG_YNNSW_SWC;
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) &= 
                           ~TSC_ADC_SS_TS_CHARGE_STEPCONFIG_WPNSW_SWC;
		  
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= xnnsw << 
                                TSC_ADC_SS_TS_CHARGE_STEPCONFIG_XNNSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= ypnsw << 
                                TSC_ADC_SS_TS_CHARGE_STEPCONFIG_YPNSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= ynnsw << 
                                TSC_ADC_SS_TS_CHARGE_STEPCONFIG_YNNSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_STEPCONFIG) |= wpnsw << 
                                TSC_ADC_SS_TS_CHARGE_STEPCONFIG_WPNSW_SWC_SHIFT;
}

/**
 * \brief   This API configures the open delay for Touch Screen ChargeStep 
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   delayVal   Open delay value
 *
 * \return  none  
 *
 **/
void TSCADCTSChargeStepOpenDelayConfig(unsigned int baseAdd,
                                    unsigned int openDelay)
{
    HWREG(baseAdd + TSC_ADC_SS_TS_CHARGE_DELAY) = openDelay;
}

/**
 * \brief   This API configures ADC to single ended or differential operation
 *          mode. 
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   mode       It is the value which determines whether to
 *                     configure ADC to single ended or differential
 *                     operation mode.
 *
 *          mode can take following macros.
 *
 *          TSCADC_SINGLE_ENDED_OPER_MODE.\n
 *          TSCADC_DIFFERENTIAL_OPER_MODE.\n
 *
 *  \param  stepSelect   It is the value which determines which step config
 *                       register to be configured.\n
 *
 *
 *          stepSelect can take any value between 0 to 15.\n
 *          
 * 
 * \return  none  
 *
 **/
void TSCADCTSStepOperationModeControl(unsigned int baseAdd, unsigned int mode,
                                   unsigned int stepSelect)
{
    if(mode)
    {
         HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) |= 
                                      TSC_ADC_SS_STEPCONFIG_DIFF_CNTRL;  
    }
    else
    {
         HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &= 
                                    ~TSC_ADC_SS_STEPCONFIG_DIFF_CNTRL;
    }
}

/**
 * \brief  This API configures the reference voltage and input for 
 *         given Step (other than Idle and Touch Screen charge Step) 
 *
 * \param   baseAdd	 	Base Address of the TouchScreen Module Registers.
 *
 * \param   stepSelect	 	Step to be configured.
 *
 * \param   adcNegativeRef	Selects the ADC Negative Reference Voltage.\n
 *
 *          adcNegativeRef can take following values.\n
 *
 *           TSCADC_NEGATIVE_REF_VSSA.\n                
 *           TSCADC_NEGATIVE_REF_XNUR.\n                
 *           TSCADC_NEGATIVE_REF_YNLR.\n                
 *           TSCADC_NEGATIVE_REF_ADCREFM.\n                
 *  
 * \param   adcPositiveInput 	Selects the Positive Analog Input Source.\n
 *
 *           adcPositiveInput can take following values.\n   
 *
 *           TSCADC_POSITIVE_INP_CHANNEL1.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL2.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL3.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL4.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL5.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL6.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL7.\n            
 *           TSCADC_POSITIVE_INP_CHANNEL8.\n
 *           TSCADC_POSITIVE_INP_ADCREFM.\n
 *            
 * \param   adcNegativeInput 	Selects the Negative Analog Input Source.\n
 *
 *          adcNegativeInput can take following values.\n
 *
 *          TSCADC_NEGATIVE_INP_CHANNEL1.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL2.\n           
 *          TSCADC_NEGATIVE_INP_CHANNEL3.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL4.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL5.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL6.\n            
 *          TSCADC_NEGATIVE_INP_CHANNEL8.\n            
 *          TSCADC_NEGATIVE_INP_ADCREFM.\n
 *            
 * \param   adcPositiveRef 	Selects the ADC Positive Reference Voltage.\n
 *
 *          adcPositiveRef can take following values.\n
 *
 *          TSCADC_POSITIVE_REF_VDDA.\n                
 *          TSCADC_POSITIVE_REF_XNUR.\n                
 *          TSCADC_POSITIVE_REF_YNLR.\n                
 *          TSCADC_POSITIVE_REF_ADCREFP.\n
 *
 * \return  none  
 *
 * Note: stepSelect can take any integer value b/w 0 to 15
 *
 **/
void TSCADCTSStepConfig(unsigned int baseAdd, unsigned int stepSelect,
		        unsigned int adcNegativeRef, unsigned int adcPositiveInp,
                        unsigned int adcNegativeInp, unsigned int adcPositiveRef)
{

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &=
                                   ~TSC_ADC_SS_STEPCONFIG_SEL_RFM_SWC;
		
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) |= 
                   adcNegativeRef << TSC_ADC_SS_STEPCONFIG_SEL_RFM_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &=
	                           ~TSC_ADC_SS_STEPCONFIG_SEL_INP_SWC;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) |=
	       adcPositiveInp << TSC_ADC_SS_STEPCONFIG_SEL_INP_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &=
                                   ~TSC_ADC_SS_STEPCONFIG_SEL_INM_SWM;
 
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) |= 
                         adcNegativeInp << TSC_ADC_SS_STEPCONFIG_SEL_INM_SWM_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &=
	                           ~TSC_ADC_SS_STEPCONFIG_SEL_RFP_SWC;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) |= 
                          adcPositiveRef << TSC_ADC_SS_STEPCONFIG_SEL_RFP_SWC_SHIFT;
}

/**
 * \brief   This API configure the TouchScreen Step Transistor Biasing for
 *          xnpsw,xppsw and yppsw pins through which analog supply
 *          is provided to the touch screen. 
 *
 * \param   baseAdd 	Base Address of the TouchScreen Module Registers.
 * \param   stepSelect	Step to be configured
 *
 * \param   xppsw 	XPPSW pin SW configuration.\n
 *
 *          xppsw can take following values.\n
 *
 *          TSCADC_XPPSW_PIN_ON.\n
 *          TSCADC_XPPSW_PIN_OFF.\n                                          
 *
 * \param   xnpsw 	XNPSW pin SW configuration.\n
 *
 *          xnpsw can take following values.\n
 *
 *          TSCADC_XNPSW_PIN_ON.\n
 *          TSCADC_XNPSW_PIN_OFF.\n
 *                     
 * \param   yppsw 	YPPSW pin SW configuration.\n
 *
 *          yppsw can take following values.\n
 *
 *          TSCADC_YPPSW_PIN_ON.\n
 *          TSCADC_YPPSW_PIN_OFF.\n 
 *
 * \return  none  
 *
 * Note: stepSelect can take any integer value b/w 0 to 15
 **/
void TSCADCTSStepAnalogSupplyConfig(unsigned int baseAdd, unsigned int xppsw,
                                 unsigned int xnpsw, unsigned int yppsw,
                                 unsigned int stepSelect)
{
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &= 
                           ~TSC_ADC_SS_STEPCONFIG_XPPSW_SWC;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &= 
                           ~TSC_ADC_SS_STEPCONFIG_XNPSW_SWC;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &= 
                           ~TSC_ADC_SS_STEPCONFIG_YPPSW_SWC;
		  
    HWREG(baseAdd +  TSC_ADC_SS_STEPCONFIG(stepSelect)) |= xppsw << 
                            TSC_ADC_SS_STEPCONFIG_XPPSW_SWC_SHIFT;

    HWREG(baseAdd +  TSC_ADC_SS_STEPCONFIG(stepSelect)) |= xnpsw << 
                            TSC_ADC_SS_STEPCONFIG_XNPSW_SWC_SHIFT;

    HWREG(baseAdd +  TSC_ADC_SS_STEPCONFIG(stepSelect)) |= yppsw << 
                            TSC_ADC_SS_STEPCONFIG_YPPSW_SWC_SHIFT;
}

/**
 * \brief   This API configure the TouchScreen Step Transistor Biasing for
 *          xnnsw, ypnsw, ynnsw and wpnsw pins through which analog ground
 *          is provided to the touch screen. 
 *
 * \param   baseAdd 	Base Address of the TouchScreen Module Registers.
 * \param   stepSelect	Step to be configured.
 *
 * \param   xnnsw 	XNNSW pin SW configuration.\n
 *           
 *          xnnsw can take following values.\n
 *
 *          TSCADC_XNNSW_PIN_ON.\n
 *          TSCADC_XNNSW_PIN_OFF.\n                                        
 *
 * \param   ypnsw 	YPNSW pin SW configuration.\n
 *
 *          ypnsw can take following values.\n
 *
 *          TSCADC_YPNSW_PIN_ON.\n
 *          TSCADC_YPNSW_PIN_OFF.\n
 *
 * \param   ynnsw 	YNNSW pin SW configuration.\n
 *
 *          ynnsw can take following values.\n
 *
 *          TSCADC_YNNSW_PIN_ON.\n
 *          TSCADC_YNNSW_PIN_OFF.\n
 *                     
 * \param   wpnsw 	WPNSW pin SW configuration.\n
 *          
 *          wpnsw can take following values.\n
 *
 *          TSCADC_WPNSW_PIN_ON.\n
 *          TSCADC_WPNSW_PIN_OFF.\n 
 *
 * \return  none  
 *
 * Note: stepSelect can take any integer value b/w 0 to 15
 **/
void TSCADCTSStepAnalogGroundConfig(unsigned int baseAdd, unsigned int xnnsw,
                                 unsigned int ypnsw, unsigned int ynnsw,
                                 unsigned int wpnsw, unsigned int stepSelect)
{
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &= 
                           ~TSC_ADC_SS_STEPCONFIG_XNNSW_SWC;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &= 
                           ~TSC_ADC_SS_STEPCONFIG_YPNSW_SWC;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &= 
                           ~TSC_ADC_SS_STEPCONFIG_YNNSW_SWC;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) &= 
                           ~TSC_ADC_SS_STEPCONFIG_WPNSW_SWC;
		  
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) |= xnnsw << 
                                TSC_ADC_SS_STEPCONFIG_XNNSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) |= ypnsw << 
                                TSC_ADC_SS_STEPCONFIG_YPNSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) |= ynnsw << 
                                TSC_ADC_SS_STEPCONFIG_YNNSW_SWC_SHIFT;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSelect)) |= wpnsw << 
                                TSC_ADC_SS_STEPCONFIG_WPNSW_SWC_SHIFT;
}

/**
 * \brief  This API Enables the ADC Out of Range  check
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   stepSel    Step to be configured
 *
 * \return  none  
 *
 **/
void TSCADCTSStepOutOfRangeCheckEnable(unsigned int baseAdd, unsigned int stepSel)
{
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSel)) |= 
                          TSC_ADC_SS_STEPCONFIG_RANGE_CHECK; 
}

/**
 * \brief  This API Disables the ADC Out of Range  check
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   stepSel    Step to be configured
 *
 * \return  none  
 *
 **/
void TSCADCTSStepOutOfRangeCheckDisable(unsigned int baseAdd, unsigned int stepSel)
{
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSel)) &= 
                         ~TSC_ADC_SS_STEPCONFIG_RANGE_CHECK; 
}

/**
 * \brief  This API selects the FIFO to store the ADC data
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   stepSel    Step to be configured
 * \param   FIFOSel    Selects the FIFO.\n
 *
 *          FIFOSel can take following macros.\n
 * 
 *          TSCADC_FIFO_0.\n
 *          TSCADC_FIFO_1.\n
 *
 * \return  none  
 *
 **/
void TSCADCTSStepFIFOSelConfig(unsigned int baseAdd, unsigned int stepSel,
	                    unsigned int FIFOSel)
{
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSel)) &= 
                          ~TSC_ADC_SS_STEPCONFIG_FIFO_SELECT;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSel)) |= 
                           FIFOSel << TSC_ADC_SS_STEPCONFIG_FIFO_SELECT_SHIFT;
}

/**
 * \brief  This API Configures the number of samples to average
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   stepSel    Step to be configured
 * \param   average    Number of Samples to average.\n
 *
 *          average can take following values.\n
 *
 *          TSCADC_TWO_SAMPLES_AVG.\n
 *          TSCADC_FOUR_SAMPLES_AVG.\n
 *          TSCADC_EIGHT_SAMPLES_AVG.\n
 *          TSCADC_SIXTEEN_SAMPLES_AVG.\n
 *
 * \return  none  
 *
 **/
void TSCADCTSStepAverageConfig(unsigned int baseAdd, unsigned int stepSel,
	                       unsigned int average)
{
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSel))
	        &= ~TSC_ADC_SS_STEPCONFIG_AVERAGING;

    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSel))
	        |= average <<  TSC_ADC_SS_STEPCONFIG_AVERAGING_SHIFT;
}

/**
 * \brief  This API Configures the Step Config Mode
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   stepSel    Step to be configured
 * \param   mode       Selects the Step Mode.
 *
 *          mode can take following macros.\n
 *
 *          TSCADC_ONE_SHOT_SOFTWARE_ENABLED.\n
 *          TSCADC_CONTINIOUS_SOFTWARE_ENABLED.\n
 *          TSCADC_ONE_SHOT_HARDWARE_SYNC.\n
 *          TSCADC_CONTINIOUS_HARDWARE_SYNC.\n
 *
 * \return  none  
 *
 **/
void TSCADCTSStepModeConfig(unsigned int baseAdd, unsigned int stepSel,
	                 unsigned int mode)
{
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSel))
	       &= ~TSC_ADC_SS_STEPCONFIG_MODE;
    HWREG(baseAdd + TSC_ADC_SS_STEPCONFIG(stepSel))
	       |= mode << TSC_ADC_SS_STEPCONFIG_MODE_SHIFT;
}

/**
 * \brief   This API Configures the Step Config Sample Delay
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   stepSel    Step to be configured
 * \param   delay      Sample Delay value
 *
 * \return  none  
 *
 **/
void TSCADCTSStepSampleDelayConfig(unsigned int baseAdd, unsigned int stepSel,
	                        unsigned int delay)
{
    HWREG(baseAdd + TSC_ADC_SS_STEPDELAY(stepSel)) &= 
                   ~TSC_ADC_SS_STEPDELAY_SAMPLE_DELAY;
    HWREG(baseAdd + TSC_ADC_SS_STEPDELAY(stepSel)) |= delay <<
                                TSC_ADC_SS_STEPDELAY_SAMPLE_DELAY_SHIFT;
}

/**
 * \brief   This API Configures the Step Config Open Delay
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   stepSel    Step to be configured
 * \param   delay      Open Delay value
 *
 * \return  none  
 *
 **/
void TSCADCTSStepOpenDelayConfig(unsigned int baseAdd, unsigned int stepSel,
                              unsigned int delay)
{
    HWREG(baseAdd + TSC_ADC_SS_STEPDELAY(stepSel)) &= 
                         ~TSC_ADC_SS_STEPDELAY_OPEN_DELAY;
    HWREG(baseAdd + TSC_ADC_SS_STEPDELAY(stepSel)) |= delay;
}

/**
 * \brief   This API gets the Channel ID which captured the data.
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   FIFOSel    Selects the FIFO
 *
 * \return  returns the channel ID  
 *
 **/
unsigned int TSCADCFIFOChannelIDRead(unsigned int baseAdd, unsigned int FIFOSel)
{
    return ((HWREG(baseAdd + TSC_ADC_SS_FIFODATA(FIFOSel)) &
		                TSC_ADC_SS_FIFODATA_ADCCHLNID) 
                      >> TSC_ADC_SS_FIFODATA_ADCCHLNID_SHIFT);
}

/**
 * \brief   This API gets the ADC Sampled data
 *
 * \param   baseAdd   Base Address of the TouchScreen Module Registers.
 * \param   FIFOSel    Selects the FIFO.\n
 *
 * \return  returns the channel ID  
 *
 **/
unsigned int TSCADCFIFOADCDataRead(unsigned int baseAdd, unsigned int FIFOSel)
{
    return (HWREG(baseAdd + TSC_ADC_SS_FIFODATA(FIFOSel)) &
		                TSC_ADC_SS_FIFODATA_ADC_DATA);
}

/**
 * \brief   This API gets the Number Of Words Currently in FIFO.
 *
 * \param   baseAdd  Base Address of the TouchScreen Module Registers.
 * \param   FIFOSel   Selects the FIFO
 *
 * \return  returns the channel ID  
 *
 **/
unsigned int TSCADCFIFOWordCountRead(unsigned int baseAdd, unsigned int FIFOSel)
{
    return(HWREG(baseAdd + TSC_ADC_SS_FIFOCOUNT(FIFOSel)));
}

/**
 * \brief  This API sets the FIFO threshold Level to generate interrupt request.
 *
 * \param   baseAdd	      Base Address of the TouchScreen Module Registers.
 *
 * \param   FIFOSel           It is the value which determines the whether to
 *                            to configure the threshold level for FIFO0 or 
 *                            FIFO1.\n
 *
 *          FIFOSel can take following macros.\n
 *              
 *          TSCADC_FIFO_0.\n
 *          TSCADC_FIFO_1.\n
 *
 * \param   numberOfSamples   It is the threshold level to be configured.
 *
 * \return  none 
 *
 **/
void TSCADCFIFOIRQThresholdLevelConfig(unsigned int baseAdd, unsigned char FIFOSel,
                                    unsigned char numberOfSamples)
{
    HWREG(baseAdd + TSC_ADC_SS_FIFOTHRESHOLD(FIFOSel)) = numberOfSamples - 1;
}

/**
 * \brief   This API sets the FIFO threshold level to generate the DMA request.
 *
 * \param   baseAdd	      Base Address of the TouchScreen Module Registers.
 * \param   numberOfSamples   Selects the FIFO
 *
 * \return  none 
 *
 **/
void TSCADCFIFODMAThresholdLevelConfig(unsigned int baseAdd, 
                                    unsigned int FIFOSel, 
                                    unsigned int numberOfSamples)
{
    HWREG(baseAdd + TSC_ADC_SS_DMAREQ(FIFOSel)) = numberOfSamples - 1;
}
