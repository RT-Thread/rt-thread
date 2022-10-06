/**
 *  \file       tsc_adc.h
 *
 *  \brief      This file contains the function prototypes for the device
 *              abstraction layer for Touch Screen. It also contains some
 *              related macro definitions and some files to be included.
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

#ifndef _TSCADC_H_
#define _TSCADC_H_

#include "hw_tsc_adc_ss.h"


#define TSCADC_FORCE_IDLE                      (0)
 
#define TSCADC_NO_IDLE                         (1)
 
#define TSCADC_SMART_IDLE                      (2)

#define TSCADC_SMART_IDLE_WAKEUP               (3)

#define TSCADC_ASYNC_HW_PEN_EVENT_INT           TSC_ADC_SS_IRQSTATUS_RAW_HW_PEN_EVENT

#define TSCADC_SYNC_PEN_EVENT_INT               TSC_ADC_SS_IRQSTATUS_RAW_PEN_IRQ

#define TSCADC_FIFO0_UNDER_FLOW_INT             TSC_ADC_SS_IRQSTATUS_RAW_FIFO0_UNDERFLOW

#define TSCADC_FIFO1_UNDER_FLOW_INT             TSC_ADC_SS_IRQSTATUS_RAW_FIFO1_UNDERFLOW

#define TSCADC_END_OF_SEQUENCE_INT              TSC_ADC_SS_IRQSTATUS_RAW_END_OF_SEQUENCE

#define TSCADC_FIFO0_THRESHOLD_INT              TSC_ADC_SS_IRQSTATUS_RAW_FIFO0_THRESHOLD

#define TSCADC_FIFO1_THRESHOLD_INT              TSC_ADC_SS_IRQSTATUS_RAW_FIFO1_THRESHOLD

#define TSCADC_FIFO0_OVER_RUN_INT               TSC_ADC_SS_IRQSTATUS_RAW_FIFO0_OVERRUN

#define TSCADC_FIFO1_OVER_RUN_INT               TSC_ADC_SS_IRQSTATUS_RAW_FIFO1_OVERRUN

#define TSCADC_OUT_OF_RANGE_INT                 TSC_ADC_SS_IRQSTATUS_RAW_OUT_OF_RANGE

#define TSCADC_PEN_UP_EVENT_INT                 TSC_ADC_SS_IRQSTATUS_RAW_PEN_UP_EVENT

#define TSCADC_FIFO_0                           (0)

#define TSCADC_FIFO_1                           (1)

#define TSCADC_FOUR_WIRE_MODE                   (1)

#define TSCADC_FIVE_WIRE_MODE                   (2)

#define TSCADC_GENERAL_PURPOSE_MODE             (0) 

#define TSCADC_PEN_IRQ_0                        (0)

#define TSCADC_PEN_IRQ_1                        (1)

#define TSCADC_SINGLE_ENDED_OPER_MODE           (0)

#define TSCADC_DIFFERENTIAL_OPER_MODE           (1)

#define TSCADC_TWO_SAMPLES_AVG                  (1)

#define TSCADC_FOUR_SAMPLES_AVG                 (2)

#define TSCADC_EIGHT_SAMPLES_AVG                (3)

#define TSCADC_SIXTEEN_SAMPLES_AVG              (4)

#define TSCADC_ONE_SHOT_SOFTWARE_ENABLED        (0)

#define TSCADC_CONTINIOUS_SOFTWARE_ENABLED      (1)

#define TSCADC_ONE_SHOT_HARDWARE_SYNC           (2)

#define TSCADC_CONTINIOUS_HARDWARE_SYNC         (3)

#define TSCADC_WAKEUP_DISABLE                   (0)

#define TSCADC_WAKEUO_ENABLE                    (1)

#define TSCADC_HW_INPUT_EVENT                   (1)

#define TSCADC_PEN_TOUCH                        (0) 

#define TSCADC_TRANSISTOR_DISABLE               (0)

#define TSCADC_TRANSISTOR_ENABLE                (1)

#define TSCADC_INTERNAL_AC_BIAS                 (0)

#define TSCADC_EXTERNAL_AC_BIAS                 (1)

#define TSCADC_MODULE_DISABLE                   (0)

#define TSCADC_MODULE_ENABLE                    (1)

#define TSCADC_NEGATIVE_REF_VSSA                (0) 

#define TSCADC_NEGATIVE_REF_XNUR                (1)   

#define TSCADC_NEGATIVE_REF_YNLR                (2)   

#define TSCADC_NEGATIVE_REF_ADCREFM             (3)

#define TSCADC_POSITIVE_REF_VDDA                (0)

#define TSCADC_POSITIVE_REF_XPUL                (1)  

#define TSCADC_POSITIVE_REF_YPLL                (2)

#define TSCADC_POSITIVE_REF_ADCREFP             (3)

#define TSCADC_POSITIVE_INP_CHANNEL1            (0)
 
#define TSCADC_POSITIVE_INP_CHANNEL2            (1) 

#define TSCADC_POSITIVE_INP_CHANNEL3            (2)   

#define TSCADC_POSITIVE_INP_CHANNEL4            (3)   

#define TSCADC_POSITIVE_INP_CHANNEL5            (4)   

#define TSCADC_POSITIVE_INP_CHANNEL6            (5) 

#define TSCADC_POSITIVE_INP_CHANNEL7            (6) 

#define TSCADC_POSITIVE_INP_CHANNEL8            (7) 

#define TSCADC_POSITIVE_INP_ADCREFM             (8) 

#define TSCADC_NEGATIVE_INP_CHANNEL1            (0)    

#define TSCADC_NEGATIVE_INP_CHANNEL2            (1)  

#define TSCADC_NEGATIVE_INP_CHANNEL3            (2)  

#define TSCADC_NEGATIVE_INP_CHANNEL4            (3) 

#define TSCADC_NEGATIVE_INP_CHANNEL5            (4) 

#define TSCADC_NEGATIVE_INP_CHANNEL6            (5) 

#define TSCADC_NEGATIVE_INP_CHANNEL7            (6) 

#define TSCADC_NEGATIVE_INP_CHANNEL8            (7)

#define TSCADC_NEGATIVE_INP_ADCREFM             (8)

#define TSCADC_XPPSW_PIN_ON                     (1) 

#define TSCADC_XPPSW_PIN_OFF                    (0)

#define TSCADC_XNNSW_PIN_ON                     (1) 

#define TSCADC_XNNSW_PIN_OFF                    (0)

#define TSCADC_YPPSW_PIN_ON                     (1)

#define TSCADC_YPPSW_PIN_OFF                    (0)

#define TSCADC_YNNSW_PIN_ON                     (1)

#define TSCADC_YNNSW_PIN_OFF                    (0)

#define TSCADC_XNPSW_PIN_ON                     (1)

#define TSCADC_XNPSW_PIN_OFF                    (0)

#define TSCADC_YPNSW_PIN_ON                     (1)

#define TSCADC_YPNSW_PIN_OFF                    (0)

#define TSCADC_WPNSW_PIN_ON                     (1)

#define TSCADC_WPNSW_PIN_OFF                    (0)   


void TSCADCSetADCPowerDown(unsigned int baseAdd);
unsigned int TSCADCGetRevision(unsigned int baseAdd);
unsigned int TSCADCEventIrqStatus(unsigned int baseAdd);
void TSCADCStepConfigProtectionEnable(unsigned int baseAdd);
void TSCADCStepConfigProtectionDisable(unsigned int baseAdd);
void TSCADCTSChargeStepOpenDelayConfig(unsigned int baseAdd,
                                    unsigned int openDelay);
unsigned int TSCADCSequencerFSMBusyStatus(unsigned int baseAdd);
unsigned int TSCADCSequencerCurrentStepID(unsigned int baseAdd);
void TSCADCTSModeConfig(unsigned int baseAdd, unsigned int tsMode);
void TSCADCIdleModeSet(unsigned int baseAdd, unsigned int idleMode);
void TSCADCHWEventMapSet(unsigned int baseAdd, unsigned int hwEvent);
unsigned int TSCADCSequencerPenIrqStatusRead(unsigned int baseAdd, 
                                          unsigned int penIRQSel);
void TSCADCTSStepModeConfig(unsigned int baseAdd, unsigned int stepSel,
	                 unsigned int mode);
void TSCADCDMAFIFOEnable(unsigned int baseAdd, unsigned char fifoSel);
void TSCADCDMAFIFODisable(unsigned int baseAdd, unsigned char fifoSel);
void TSCADCADCBiasConfig(unsigned int baseAdd, unsigned int adcBiasSel);
void TSCADCIntStatusClear(unsigned int baseAdd, unsigned int intFlag);
void TSCADCEventInterruptEnable(unsigned int baseAdd, unsigned int event);
void TSCADCEventInterruptDisable(unsigned int baseAdd, unsigned int event);
void TSCADCTSStepFIFOSelConfig(unsigned int baseAdd, unsigned int stepSel,
	                    unsigned int FIFOSel);
void TSCADCTSStepSampleDelayConfig(unsigned int baseAdd, unsigned int stepSel,
	                        unsigned int delay);
void TSCADCTSStepOpenDelayConfig(unsigned int baseAdd, unsigned int stepSel,
                              unsigned int delay);


void TSCADCTSStepAverageConfig(unsigned int baseAdd, unsigned int stepSel,
	                       unsigned int average);
void TSCADCTSStepConfig(unsigned int baseAdd, unsigned int stepSelect,
		     unsigned int adcNegativeRef, unsigned int adcPositiveInp,
                     unsigned int adcNegativeInp, unsigned int adcPositiveRef);

void TSCADCConfigureAFEClock(unsigned int baseAdd, unsigned int moduleClk,
                          unsigned int inputClk);
void TSCADCADCOutputRangeConfig(unsigned int baseAdd, unsigned short lowVal,
	                     unsigned short highVal);
void TSCADCTSStepOperationModeControl(unsigned int baseAdd, unsigned int mode,
                                   unsigned int stepSelect);
void TSCADCTSStepAnalogSupplyConfig(unsigned int baseAdd, unsigned int xppsw,
                                 unsigned int xnpsw, unsigned int yppsw,
                                 unsigned int stepSelect);
void TSCADCTSStepAnalogGroundConfig(unsigned int baseAdd, unsigned int xnnsw,
                                 unsigned int ypnsw, unsigned int ynnsw,
                                 unsigned int wpnsw, unsigned int stepSelect);
void TSCADCChargeStepAnalogSupplyConfig(unsigned int baseAdd, unsigned int xppsw,
                                     unsigned int xnpsw, unsigned int yppsw);
void TSCADCChargeStepAnalogSupplyConfig(unsigned int baseAdd, unsigned int xppsw,
                                     unsigned int xnpsw, unsigned int yppsw);
void TSCADCIdleStepConfig(unsigned int baseAdd, unsigned int adcNegativeRef,
                       unsigned int adcPositiveInp, unsigned int adcNegativeInp, 
                       unsigned int adcPositiveRef);
void TSCADCConfigureMisc(unsigned int baseAdd, unsigned char spareInputVal,
		      unsigned char spareOutputVal);
void TSCADCConfigureStepEnable(unsigned int baseAdd, unsigned int stepSel,
	                    unsigned int stepEn_Dis);
void TSCADCIdleStepAnalogSupplyConfig(unsigned int baseAdd, unsigned int xppsw,
                                   unsigned int xnpsw, unsigned int yppsw);
void TSCADCIdleStepAnalogGroundConfig(unsigned int baseAdd, unsigned int xnnsw,
                                   unsigned int ypnsw, unsigned int ynnsw,
                                   unsigned int wpnsw);
void TSCADCChargeStepConfig(unsigned int baseAdd, unsigned int adcNegativeRef,
                         unsigned int adcPositiveInp,unsigned int adcNegativeInp,
                         unsigned int adcPositiveRef);
void TSCADCChargeStepAnalogGroundConfig(unsigned int baseAdd, unsigned int xnnsw,
                                     unsigned int ypnsw, unsigned int ynnsw,
                                     unsigned int wpnsw);
void TSCADCModuleStateSet(unsigned int baseAdd, unsigned int enableModule);
void TSCADCRawIntStatusSet(unsigned int baseAdd, unsigned int intFlag);
void TSCADCStepIDTagConfig(unsigned int baseAdd, unsigned int enableStepIDTag);
unsigned int TSCADCFIFOADCDataRead(unsigned int baseAdd, unsigned int FIFOSel);
unsigned int TSCADCIsDMAFIFOEnabled(unsigned int baseAdd, unsigned int fifoSel);
unsigned int TSCADCIntStatusRead(unsigned int baseAdd, unsigned int intFlag);
void TSCADCWakeUpPenEventConfig(unsigned int baseAdd, unsigned int enableWakeUp);
unsigned int TSCADCFIFOWordCountRead(unsigned int baseAdd, unsigned int FIFOSel);
unsigned int TSCADCFIFOChannelIDRead(unsigned int baseAdd, unsigned int FIFOSel);
void TSCADCIdleStepOperationModeControl(unsigned int baseAdd, unsigned int mode);
void TSCADCTSStepOutOfRangeCheckEnable(unsigned int baseAdd, unsigned int stepSel);
void TSCADCTSStepOutOfRangeCheckDisable(unsigned int baseAdd, unsigned int stepSel);
unsigned int TSCADCRawIntStatusRead(unsigned int baseAdd, unsigned int intFlag);
void TSCADCChargeStepOperationModeControl(unsigned int baseAdd, unsigned int mode);
void TSCADCTSTransistorConfig(unsigned int baseAdd, unsigned int enableTSTransistor);
void TSCADCConfigHWEventPrempt(unsigned int baseAdd, unsigned int enableHWEventPreempt);
void TSCADCFIFOIRQThresholdLevelConfig(unsigned int baseAdd, unsigned char FIFOSel,
                                    unsigned char numberOfSamples);
void TSCADCFIFODMAThresholdLevelConfig(unsigned int baseAdd, 
                                    unsigned int FIFOSel, 
                                    unsigned int numberOfSamples);

unsigned int TSCADCIntStatus(unsigned int baseAdd);

void TSCADCSetADCPowerUp(unsigned int baseAdd);

typedef struct {
                   signed int x;
                   signed int y;
               }POINT;


typedef struct {
                   signed int Divider;
                   signed int An;
                   signed int Bn;
                   signed int Cn;
                   signed int Dn;
                   signed int En;
                   signed int Fn;
               }MATRIX;

#endif
